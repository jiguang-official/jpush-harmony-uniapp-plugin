# 最佳实现：jg-jpush-u 与 uni-unimp 联动

本文档描述 **极光推送 (jg-jpush-u)**、**宿主 App**、**uni-unimp（微信插件）**、**uni 小程序** 四者之间的最佳集成方式。

---

## 阅读前请先了解

建议先阅读以下官方文档，再按本文实现联动：

| 文档 | 说明 |
|------|------|
| [uni-unimp 官方文档](https://ext.dcloud.net.cn/plugin?id=17638) | uni-unimp 插件集成与 API |
| [jg-jpush-u 官方仓库](https://github.com/jiguang-official/jpush-harmony-uniapp-plugin/) | 极光推送 UTS 插件集成与 API |

## 一、架构与数据流

```
┌─────────────────┐     ┌──────────────┐     ┌─────────────┐     ┌────────────────┐
│  jg-jpush-u     │◄───►│  宿主 App    │◄───►│ uni-unimp   │◄───►│  uni 小程序    │
│  (极光推送)      │     │  (Host App)  │     │ (微信插件)   │     │ (内嵌小程序)   │
└─────────────────┘     └──────────────┘     └─────────────┘     └────────────────┘
        │                        │                    │                    │
        │ 推送/标签/事件          │ 宿主 → 小程序        │ 事件通道            │ uni.onHostEventReceive
        │                        │ mp.sendUniMPEvent   │                    │ (收 jg_callback 等)
        │                        │ 宿主 ← 小程序        │                    │ uni.sendHostEvent
        │                        │ mp.onUniMPEventReceive │                  │ (发 jg_listener_ready、mp_set_tags)
```

**约定：**

- **宿主 App**：当前 uni-app 主工程（含 jg-jpush-u、uni-unimp）。
- **uni 小程序**：通过 uni-unimp 内嵌的独立小程序工程（有独立 appid，如 `__UNI__xxxxx`）。
- 宿主与小程序之间仅通过 **事件名 + 数据** 通信，建议统一事件名常量，见下文。

---

## 二、功能一：JPush 监听 → 数据传给小程序

**目标**：极光推送收到消息/通知/自定义事件时，由宿主转发给当前已打开的 uni 小程序。

### 2.1 事件名约定

宿主 → 小程序：统一用一个事件 **`jg_callback`**，把 JPush 的 `eventName`、`eventData` 原样透传，小程序侧根据 `eventName` 自行分支。

### 2.2 宿主 App：等小程序监听完后再设置 setEventCallBack

建议顺序：**先让小程序注册好 `onHostEventReceive`，小程序再通知宿主「监听已就绪」，宿主再设置 `setEventCallBack`**，避免 JPush 事件在小程序未准备好时被发出。

在 **App.vue** 的 `onLaunch` 中：

**注意事项**：**`onUniMPEventReceive` 必须在打开 uni 小程序之前就完成监听**，否则小程序发来的事件（如 `jg_listener_ready`、`mp_set_tags`）可能收不到。本文实现方式是在宿主 `onLaunch` 里调用，保证在首次 `openUniMP` 之前就已注册。

1. 创建 uni-unimp 上下文，注册 `onUniMPEventReceive`。
2. 只做 JPush 的 `setDebug`、`init()`，**先不调用** `setEventCallBack`。
3. 在 `onUniMPEventReceive` 里收到小程序发来的 **`jg_listener_ready`** 事件后，再设置 `setEventCallBack`，并在回调里用 **`jg_callback`** 透传整包给小程序。

```javascript
// App.vue（宿主 App）
<script>
import { init, setDebug, setEventCallBack, setTags, addTags, deleteTags } from '@/uni_modules/jg-jpush-u'

// 当前已打开的小程序 appid（在打开/关闭/隐藏时维护）
let currentUniMPAppid = ''

export default {
  onLaunch() {
    const mp = uni.createUniMPContext()

    // 1）监听小程序发来的事件：mp_set_tags（功能三）、jg_listener_ready（监听就绪后再设 setEventCallBack）
    mp.onUniMPEventReceive((res) => {
      console.log('宿主收到小程序事件:', res)
      if (res.event === 'jg_listener_ready') {
        // 小程序已注册 onHostEventReceive，再设置 JPush 回调，避免漏发
        setEventCallBack({
          callback: (event) => {
            if (!currentUniMPAppid) {
              console.warn('[jg_callback] 未设置 currentUniMPAppid，跳过透传', event.eventName)
              return
            }
            const payload = { eventName: event.eventName, eventData: event.eventData }
            console.log('[jg_callback] payload:', JSON.stringify(payload))
            mp.sendUniMPEvent(currentUniMPAppid, 'jg_callback', payload, (ret) => {
              if (ret.type === 'fail') console.warn('sendUniMPEvent fail, payload:', JSON.stringify(payload), 'ret:', ret, JSON.stringify(ret))
            })
          }
        })
        return
      }
      if (res.event === 'mp_set_tags' && res.data) {
        const { action, tags } = res.data
        const seq = Date.now() % 100000
        if (action === 'set') setTags(seq, tags)
        else if (action === 'add') addTags(seq, tags)
        else if (action === 'delete') deleteTags(seq, tags)
      }
    })

    setDebug(true)
    init() // 或 init('你的appKey')
  }
}
</script>
```

**维护 currentUniMPAppid**：在打开小程序时赋值，关闭/隐藏时视需求清空或保留。例如在打开小程序的页面：

```javascript
// 打开小程序时
currentUniMPAppid = '__UNI__F0FF587'  // 你的小程序 appid
mp.openUniMP({ appid: currentUniMPAppid }, (ret) => { ... })

// 关闭/隐藏时可按业务决定是否清空
// currentUniMPAppid = ''
```

若希望多小程序实例都收推送，可维护 `currentUniMPAppid` 为数组，对每个 appid 调用一次 `sendUniMPEvent`。

### 2.3 小程序端：先监听 jg_callback，再通知宿主「监听已就绪」

按官方建议：**在 uni 小程序应用生命周期的 `onLaunch` 中监听**宿主通过 `sendUniMPEvent` 发来的事件。在小程序 **App.vue** 的 `onLaunch` 里：

1. 先调用 **`uni.onHostEventReceive`** 监听宿主发来的 **`jg_callback`**，根据 `data.eventName` 分支处理。
2. **监听完后** 给宿主发一条 **`jg_listener_ready`** 事件，宿主收到后再设置 `setEventCallBack`，避免事件在监听前就发出。

```javascript
// 小程序项目
export default {
  onLaunch() {
    uni.onHostEventReceive((event, data) => {
      if (event !== 'jg_callback' || !data) return
      const { eventName, eventData } = data
      switch (eventName) {
        case 'onNotifyMessageArrived':
          console.log('前台收到通知:', eventData)
          break
        case 'onClickMessage':
          console.log('点击通知:', eventData)
          break
        case 'onCustomMessage':
          console.log('自定义消息:', eventData)
          break
        case 'onRegister':
          console.log('RegistrationID:', eventData)
          break
        case 'onTagOperatorResult':
          console.log('标签操作结果:', eventData)
          break
        default:
          console.log('JPush 事件:', eventName, eventData)
      }
    })
    // 监听完后通知宿主：可以开始用 jg_callback 透传了
    uni.sendHostEvent('jg_listener_ready', {}, (ret) => {
      if (ret && ret.code !== 0) console.warn('jg_listener_ready fail', ret)
    })
  }
}
```

---

## 三、功能二：宿主 App 中初始化 jg-jpush-u

在 **App.vue** 的 `onLaunch` 中顺序建议：

1. `uni.createUniMPContext()` 并保存为全局可用（如 `getApp().mp`）。
2. `mp.onUniMPEventReceive(...)` 监听小程序事件（含 `jg_listener_ready`、`mp_set_tags` 等）。
3. `setDebug(true/false)`、`init()` 或 `init('appKey')`；**不要在此处** `setEventCallBack`。
4. 收到小程序的 **`jg_listener_ready`** 后，再在 `onUniMPEventReceive` 里调用 `setEventCallBack(...)`。
5. 可选：`setChannel('xxx')`、`resumePush()` 等。

---

## 四、功能三：小程序设置 Tag → 宿主 App → jg-jpush-u

**目标**：小程序内发起“设置/添加/删除标签”，宿主收到后调用 jg-jpush-u 的 `setTags` / `addTags` / `deleteTags`。

### 4.1 小程序端：发送 tag 操作事件

小程序内调用 `uni.sendHostEvent(event, data, callback)`，约定 `event` 与 `data` 格式：

```javascript
// 小程序内：设置标签（覆盖）
uni.sendHostEvent('mp_set_tags', {
  action: 'set',
  tags: ['vip', 'city_beijing']
}, (ret) => { if (ret.code !== 0) console.warn(ret) })

// 添加标签
uni.sendHostEvent('mp_set_tags', {
  action: 'add',
  tags: ['new_tag']
}, (ret) => { ... })

// 删除标签
uni.sendHostEvent('mp_set_tags', {
  action: 'delete',
  tags: ['old_tag']
}, (ret) => { ... })
```

也可拆成三个事件名：`mp_set_tags`、`mp_add_tags`、`mp_delete_tags`，宿主根据 event 分别调 `setTags` / `addTags` / `deleteTags`。

### 4.2 宿主 App：接收并调用 jg-jpush-u

在 **App.vue** 的 `onUniMPEventReceive` 中（见 2.2 节）已示例：根据 `res.event` 与 `res.data` 调用：

```javascript
import { setTags, addTags, deleteTags } from '@/uni_modules/jg-jpush-u'

mp.onUniMPEventReceive((res) => {
  const { fromAppid, event, data } = res
  if (event === 'mp_set_tags' && data && data.tags) {
    const seq = Math.floor(Date.now() / 1000) % 100000
    if (data.action === 'set') {
      setTags(seq, data.tags)
    } else if (data.action === 'add') {
      addTags(seq, data.tags)
    } else if (data.action === 'delete') {
      deleteTags(seq, data.tags)
    }
  }
})
```

标签操作结果通过 JPush 的 `onTagOperatorResult` 回调回到宿主；由于宿主已统一用 `jg_callback` 透传所有 JPush 事件，该结果会随 `setEventCallBack` 自动以 `jg_callback` 发给小程序，小程序侧在 `uni.onHostEventReceive` 里根据 `data.eventName === 'onTagOperatorResult'` 处理即可。

---

## 五、汇总：推荐文件与流程

| 步骤 | 位置 | 动作 |
|------|------|------|
| 1 | 宿主 App.vue `onLaunch` | `createUniMPContext`；`onUniMPEventReceive`（收到 `jg_listener_ready` 时再 `setEventCallBack`，收到 `mp_set_tags` 时调 tag 接口）；仅 `init` JPush，不在此处 `setEventCallBack`；维护 `currentUniMPAppid` |
| 2 | 宿主 打开小程序页 | 打开时设置 `currentUniMPAppid = 小程序appid`，关闭时按需清空 |
| 3 | JPush 回调 | 在收到 `jg_listener_ready` 后设置的 `setEventCallBack` 里，用 `jg_callback` 透传 `{ eventName, eventData }` |
| 4 | 小程序 App.vue `onLaunch` | 先 `uni.onHostEventReceive` 监听 `jg_callback`，**监听完后** `uni.sendHostEvent('jg_listener_ready', {})` 通知宿主 |
| 5 | 小程序业务页 | 需要改 tag 时 `uni.sendHostEvent('mp_set_tags', { action, tags })` |

### 5.1 事件名与常量建议

- 宿主 → 小程序：统一用 **`jg_callback`** 透传 JPush 回调；小程序根据 `data.eventName` 区分类型。
- 小程序 → 宿主：**`jg_listener_ready`** 表示小程序已注册 `onHostEventReceive`，宿主收到后再 `setEventCallBack`；**`mp_set_tags`** 表示设置/添加/删除标签。
- 小程序 appid：如 `UNI_MP_APPID = '__UNI__F0FF587'` 集中配置，避免魔法字符串。

### 5.2 注意事项

- **sendUniMPEvent** 仅在小程序已运行且未被销毁时有效；未打开小程序时不要发，或先判断再发。
- **setTags** 会覆盖现有标签，**addTags** 仅追加；按业务选择。
- 标签/别名操作结果为异步，通过 `onTagOperatorResult` / `onAliasOperatorResult` 回传，需在宿主统一处理并可选再转发给小程序。

---

## 六、参考文档

- [uni-unimp 官方文档](https://ext.dcloud.net.cn/plugin?id=17638)
- [jg-jpush-u 官方文档](https://github.com/jiguang-official/jpush-harmony-uniapp-plugin/)

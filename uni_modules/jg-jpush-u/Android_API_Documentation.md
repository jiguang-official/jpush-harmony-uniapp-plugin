# Android极光推送UTS插件API文档

## 概述

本文档描述了Android平台极光推送UTS插件的API接口，该插件基于极光推送SDK实现，提供了完整的推送功能支持。

## 核心API方法

### 1. 初始化与配置

#### init(appKey?: string)
初始化极光推送服务

**参数：**
- `appKey`: string (可选) - 极光推送应用的AppKey，如果不传入则使用manifestPlaceholders.json中配置的AppKey

**重要说明：**
- 如果使用动态AppKey（传入appKey参数），则需要在`nativeResources/android/manifestPlaceholders.json`中将`JPUSH_APPKEY`设置为空字符串：
  ```json
  {
    "JPUSH_APPKEY": "",
    "JPUSH_CHANNEL": "your_channel_name"
  }
  ```
- 如果不传入appKey参数，则使用manifestPlaceholders.json中配置的AppKey值

**示例：**
```typescript
// 使用manifestPlaceholders.json中配置的AppKey
init()

// 动态设置AppKey（需要将manifestPlaceholders.json中的JPUSH_APPKEY设置为空字符串）
init("你的appkey")
```

#### setDebug(debug: boolean)
设置调试模式

**参数：**
- `debug`: boolean - 是否开启调试模式

**示例：**
```typescript
setDebug(true)  // 开启调试模式
setDebug(false) // 关闭调试模式
```

#### setEventCallBack(param: EventCallBackParams)
设置事件回调函数

**参数：**
- `param`: EventCallBackParams - 回调参数对象

**示例：**
```typescript
setEventCallBack({
    callback: (event) => {
        console.log('收到事件:', event.eventName, event.eventData)
    }
})
```

### 2. 推送控制

#### resumePush()
恢复推送服务

**示例：**
```typescript
resumePush()
```

#### stopPush()
停止推送服务

**示例：**
```typescript
stopPush()
```

#### isPushStopped(): boolean
检查推送服务是否已停止

**返回值：**
- `boolean`: 推送服务状态

**示例：**
```typescript
const isStopped = isPushStopped()
console.log('推送服务状态:', isStopped)
```

#### getConnectionState(): boolean
获取当前 Push 长连接状态（仅 Android 支持）。连接状态变化时可通过 CONNECTION 广播或 JPushMessageReceiver 获知。

**返回值：**
- `boolean`: true 已连接，false 未连接

**示例：**
```typescript
const connected = getConnectionState()
console.log('长连接状态:', connected)
```

### 3. 设备标识管理

#### getRegistrationId(): string
获取设备的RegistrationID

**返回值：**
- `string`: 设备的唯一标识符

**示例：**
```typescript
const registrationId = getRegistrationId()
console.log('RegistrationID:', registrationId)
```

#### setChannel(channel: string)
设置应用渠道标识

**参数：**
- `channel`: string - 渠道标识

**示例：**
```typescript
setChannel("huawei")
```

### 4. 标签管理

#### setTags(sequence: Int, tags: string[])
设置标签（会覆盖现有标签）

**参数：**
- `sequence`: Int - 操作序列号
- `tags`: string[] - 标签数组

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
setTags(1, ["tag1", "tag2", "tag3"])
```

#### addTags(sequence: Int, tags: string[])
添加标签

**参数：**
- `sequence`: Int - 操作序列号
- `tags`: string[] - 要添加的标签数组

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
addTags(2, ["newTag1", "newTag2"])
```

#### deleteTags(sequence: Int, tags: string[])
删除指定标签

**参数：**
- `sequence`: Int - 操作序列号
- `tags`: string[] - 要删除的标签数组

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
deleteTags(3, ["tag1", "tag2"])
```

#### cleanTags(sequence: Int)
清除所有标签

**参数：**
- `sequence`: Int - 操作序列号

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
cleanTags(4)
```

#### getAllTags(sequence: Int)
获取所有标签

**参数：**
- `sequence`: Int - 操作序列号

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
getAllTags(5)
```

#### checkTagBindState(sequence: Int, tag: string)
验证标签绑定状态

**参数：**
- `sequence`: Int - 操作序列号
- `tag`: string - 要检查的标签

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
checkTagBindState(6, "testTag")
```

#### filterValidTags(tags: string[]): string[]
筛选有效标签（调用官方 JPushInterface.filterValidTags）。在调用 setTags/addTags 前可先过滤掉无效 tag，避免因单个无效 tag 导致整次设置失败。

**参数：**
- `tags`: string[] - 待校验的标签数组

**返回值：**
- string[] - 符合极光规则的有效标签数组（超出数量/总长限制时返回靠前的有效 tag）

**说明：**
- 无需 sequence，同步返回
- 有效字符：字母（区分大小写）、数字、下划线、汉字、特殊字符 @!#$&*+=.|
- 单 tag 长度 ≤ 40 字节（UTF-8），最多 1000 个 tag，总长 ≤ 5000 字节

**示例：**
```typescript
const input = ["tag1", "无效 tag!", "tag2"]
const valid = filterValidTags(input)
setTags(this.sequence++, valid)
```

### 5. 别名管理

#### setAlias(sequence: Int, alias: string)
设置别名

**参数：**
- `sequence`: Int - 操作序列号
- `alias`: string - 别名

**回调事件：** `onAliasOperatorResult`

**示例：**
```typescript
setAlias(7, "user123")
```

#### deleteAlias(sequence: Int)
删除别名

**参数：**
- `sequence`: Int - 操作序列号

**回调事件：** `onAliasOperatorResult`

**示例：**
```typescript
deleteAlias(8)
```

#### getAlias(sequence: Int)
获取当前别名

**参数：**
- `sequence`: Int - 操作序列号

**回调事件：** `onAliasOperatorResult`

**示例：**
```typescript
getAlias(9)
```

### 6. 手机号码管理

#### setMobileNumber(sequence: Int, mobileNumber: string)
设置手机号码

**参数：**
- `sequence`: Int - 操作序列号
- `mobileNumber`: string - 手机号码

**回调事件：** `onMobileNumberOperatorResult`

**示例：**
```typescript
setMobileNumber(10, "13800138000")
```

### 7. 通知管理

#### setLatestNotificationNumber(maxNum: Int)
设置最新通知数量

**参数：**
- `maxNum`: Int - 最大通知数量

**示例：**
```typescript
setLatestNotificationNumber(10)
```

#### setPushTime(weekDays: number[] | null, startHour: number, endHour: number)
设置允许推送的时间段。默认任何时间都允许推送；调用此 API 后，仅在该时间段内会展示通知，其余时间收到的通知会被丢弃（纯客户端逻辑，**仅对通知有效，自定义消息不受影响**）。

**参数：**
- `weekDays`: number[] | null - 允许推送的星期：0=周日、1=周一…6=周六；传 `null` 表示任何时间都可收到；传空数组 `[]` 表示任何时间都收不到
- `startHour`: number - 允许推送的开始小时（24 小时制，0-23）
- `endHour`: number - 允许推送的结束小时（24 小时制，0-23）

**示例：**
```typescript
// 周一到周五、上午 10 点到晚上 23 点允许推送
setPushTime([1, 2, 3, 4, 5], 10, 23)
// 任何时间都可收到
setPushTime(null, 0, 23)
// 任何时间都收不到通知
setPushTime([], 0, 0)
```

#### setSilenceTime(startHour: number, startMinute: number, endHour: number, endMinute: number)
设置通知静默时间。在静默时段内收到的通知不会有铃声和震动（仅对通知有效）。

**参数：**
- `startHour`: number - 静默开始-小时（24 小时制，0-23）
- `startMinute`: number - 静默开始-分钟（0-59）
- `endHour`: number - 静默结束-小时（24 小时制，0-23）
- `endMinute`: number - 静默结束-分钟（0-59）

**示例：**
```typescript
// 晚上 22:30 到次日早上 8:30 为静音时段
setSilenceTime(22, 30, 8, 30)
```

#### clearNotificationAll()
清除所有通知

**示例：**
```typescript
clearNotificationAll()
```

#### clearNotificationById(notificationId: Int)
根据通知ID清除指定通知

**参数：**
- `notificationId`: Int - 通知ID

**示例：**
```typescript
clearNotificationById(123)
```

### 7.1 本地通知（仅 Android / iOS）

通过极光 SDK 可在应用内定时触发本地通知，不依赖网络。鸿蒙暂无对应 API，调用为占位。

#### addLocalNotification(options: LocalNotificationOptions)
添加一条本地通知，需在 `init` 之后调用。

**参数（LocalNotificationOptions）：**
- `notificationId`: number - 必填，本地通知 ID，建议为正整数；为 0 或负数时 Android 上可能无法清除
- `broadcastTime`: number - 必填，触发时间（毫秒时间戳）
- `title?`: string - 通知标题
- `content?`: string - 通知内容
- `extras?`: string - 额外数据（JSON 字符串）
- `builderId?`: number - 通知栏样式编号（Android）
- `category?`: string - 分类（Android 5.2.0+）
- `priority?`: number - 优先级，-2～2（Android）
- `channelId?`: string - 通知渠道 ID（Android 8.0+）

**示例：**
```typescript
import { addLocalNotification, type LocalNotificationOptions } from '@/uni_modules/jg-jpush-u'

const opts: LocalNotificationOptions = {
  notificationId: 10001,
  broadcastTime: Date.now() + 10 * 60 * 1000, // 10 分钟后
  title: '提醒',
  content: '这是一条本地通知',
  extras: '{"key":"value"}'
}
addLocalNotification(opts)
```

#### removeLocalNotification(notificationId: number)
移除指定 ID 的本地通知。

**示例：**
```typescript
removeLocalNotification(10001)
```

#### clearLocalNotifications()
清除所有本地通知。

**示例：**
```typescript
clearLocalNotifications()
```

### 8. 生命周期管理

#### onResume()
应用恢复时调用

**示例：**
```typescript
onResume()
```

#### onPause()
应用暂停时调用

**示例：**
```typescript
onPause()
```

#### onFragmentResume(fragmentName: string)
Fragment恢复时调用

**参数：**
- `fragmentName`: string - Fragment名称

**示例：**
```typescript
onFragmentResume("MainFragment")
```

#### onFragmentPause(fragmentName: string)
Fragment暂停时调用

**参数：**
- `fragmentName`: string - Fragment名称

**示例：**
```typescript
onFragmentPause("MainFragment")
```

#### onKillProcess()
应用进程被杀死时调用

**示例：**
```typescript
onKillProcess()
```

### 9. 权限管理

#### requestPermission()
请求通知权限。官方 API 需要 Activity，建议在首屏 Activity 可见时调用（如 onReady）。若当前无 Activity 则仅打日志不调用 SDK。

**示例：**
```typescript
requestPermission()
```

#### requestRequiredPermission()
申请必须权限。建议在首屏 Activity 可见时调用（如 onReady），以便正确弹出系统权限框。若当前无 Activity 则仅打日志不调用 SDK。

**示例：**
```typescript
requestRequiredPermission()
```

#### isNotificationEnabled(): number
检查通知权限状态

**返回值：**
- `number`: 权限状态码

**示例：**
```typescript
const status = isNotificationEnabled()
console.log('通知权限状态:', status)
```

#### goToAppNotificationSettings()
跳转到应用通知设置页面

**示例：**
```typescript
goToAppNotificationSettings()
```

#### triggerNotificationStateCheck()
主动触发通知状态检查，若有变化则上报。适用于从系统设置返回等场景，用于刷新并上报当前应用通知开关状态。JPush Android SDK v5.9.0+。

**示例：**
```typescript
triggerNotificationStateCheck()
```

#### reportNotificationOpened(msgId: string, channel?: number)
上报通知打开事件，用于统计用户点击通知栏或自定义消息展示。msgId 来源于推送 Extra 中的 `EXTRA_MSG_ID`（接收推送消息时可从 intent/bundle 中获取）。JPush Android SDK v1.6.1+。第二个参数 `channel` 仅鸿蒙使用（0=厂商通道，1=极光通道），Android 忽略。

**参数：**
- `msgId`: string - 推送消息唯一 ID
- `channel`: number（可选）- 仅鸿蒙有效，Android 忽略

**示例：**
```typescript
reportNotificationOpened(msgId)  // 在用户点击通知或展示自定义消息时调用
```

### 10. 角标管理

#### setBadgeNumber(curNum: Int)
设置应用角标数量

**参数：**
- `curNum`: Int - 角标数量

**示例：**
```typescript
setBadgeNumber(5)  // 设置角标为5
```

### 11. 智能推送设置

#### setSmartPushEnable(isEnable: boolean)
设置智能推送开关

**参数：**
- `isEnable`: boolean - 是否启用智能推送

**示例：**
```typescript
setSmartPushEnable(true)
```

#### setGeofenceEnable(isEnable: boolean)
设置地理围栏开关

**参数：**
- `isEnable`: boolean - 是否启用地理围栏

**示例：**
```typescript
setGeofenceEnable(true)
```

#### setGeofenceInterval(intervalMs: number)
设置地理围栏监控周期（单位毫秒，最小 3 分钟、最大 1 天；默认 15 分钟）。JPush Android SDK v3.1.8+。

**参数：**
- `intervalMs`: number - 监控周期，毫秒

**示例：**
```typescript
setGeofenceInterval(15 * 60 * 1000)  // 15 分钟
```

#### setMaxGeofenceNumber(maxNumber: number)
设置允许保存的最大地理围栏个数（范围 1-100，默认 10）。JPush Android SDK v3.1.8+。

**参数：**
- `maxNumber`: number - 最多允许保存的围栏个数

**示例：**
```typescript
setMaxGeofenceNumber(20)
```

#### deleteGeofence(geofenceId: string)
删除指定 id 的地理围栏。JPush Android SDK v3.1.8+。

**参数：**
- `geofenceId`: string - 地理围栏 id

**示例：**
```typescript
deleteGeofence("your_geofence_id")
```

#### setDataInsightsEnable(isEnable: boolean)
设置数据洞察开关

**参数：**
- `isEnable`: boolean - 是否启用数据洞察

**示例：**
```typescript
setDataInsightsEnable(true)
```

### 12. 数据采集与扩展业务（仅 Android）

#### setCollectControl(options: CollectControlOptions | null)
设置可选个人信息采集控制。未传或未设置为 `false` 的项保持 SDK 默认（采集）。

**参数：**
- `options`: CollectControlOptions | null - 各采集项开关，`false` 表示不采集
  - `imei?: boolean` - IMEI
  - `imsi?: boolean` - IMSI
  - `mac?: boolean` - MAC
  - `ssid?: boolean` - SSID
  - `bssid?: boolean` - BSSID
  - `cell?: boolean` - 基站
  - `wifi?: boolean` - WIFI 列表

**示例：**
```typescript
setCollectControl({ mac: false, wifi: false })
```

#### setLinkMergeEnable(isEnable: boolean)
设置链路调节器开关。默认开启。

**参数：**
- `isEnable`: boolean - 是否开启

**示例：**
```typescript
setLinkMergeEnable(true)
```

#### setEnableAutoWakeup(isEnable: boolean)
设置应用自启动开关。默认开启。

**参数：**
- `isEnable`: boolean - 是否开启

**示例：**
```typescript
setEnableAutoWakeup(true)
```

#### setEnableAppTerminate(isEnable: boolean)
设置应用活跃时长统计开关。默认开启。鸿蒙端有同名接口。

**参数：**
- `isEnable`: boolean - 是否开启

**示例：**
```typescript
setEnableAppTerminate(true)
```

#### setPowerSaveMode(enable: boolean)
设置是否开启省电模式。默认关闭。

**参数：**
- `enable`: boolean - 是否开启

**示例：**
```typescript
setPowerSaveMode(false)
```

#### stopCrashHandler()
关闭 CrashLog 收集并上报。

**示例：**
```typescript
stopCrashHandler()
```

#### initCrashHandler()
开启 CrashLog 收集并上报。SDK 默认开启，若曾调用 `stopCrashHandler` 可由此恢复。

**示例：**
```typescript
initCrashHandler()
```

## 事件回调

插件支持以下事件回调：

### 1. onCustomMessage
收到自定义消息时触发

**回调数据格式：**
```json
{
    "eventName": "onCustomMessage",
    "eventData": "消息内容的JSON字符串"
}
```

### 2. onConnected
连接状态变化时触发

**回调数据格式：**
```json
{
    "eventName": "onConnected",
    "eventData": "true"  // 或 "false"
}
```

### 3. onNotifyMessageArrived
应用在前台收到通知时触发

**回调数据格式：**
```json
{
    "eventName": "onNotifyMessageArrived",
    "eventData": "通知内容的JSON字符串"
}
```

### 4. onClickMessage
用户点击通知时触发

**回调数据格式：**
```json
{
    "eventName": "onClickMessage",
    "eventData": "通知内容的JSON字符串"
}
```

### 5. onNotifyMessageDismiss
通知被清除时触发

**回调数据格式：**
```json
{
    "eventName": "onNotifyMessageDismiss",
    "eventData": "通知内容的JSON字符串"
}
```

### 6. onRegister
设备注册成功时触发

**回调数据格式：**
```json
{
    "eventName": "onRegister",
    "eventData": "registrationId字符串"
}
```

### 7. onCommandResult
命令执行结果回调

**回调数据格式：**
```json
{
    "eventName": "onCommandResult",
    "eventData": {
        "cmd": "命令类型",
        "errorCode": 0,
        "msg": "消息",
        "extra": "额外数据"
    }
}
```

### 8. onTagOperatorResult
标签操作结果回调

**回调数据格式：**
```json
{
    "eventName": "onTagOperatorResult",
    "eventData": {
        "alias": "别名",
        "tags": ["tag1", "tag2"],
        "pros": "属性",
        "checkTag": "检查的标签",
        "errorCode": 0,
        "tagCheckStateResult": "标签检查状态结果",
        "isTagCheckOperator": true,
        "sequence": 1,
        "mobileNumber": "手机号码",
        "protoType": "协议类型",
        "action": "操作类型"
    }
}
```



### 10. onAliasOperatorResult
别名操作结果回调

**回调数据格式：**
```json
{
    "eventName": "onAliasOperatorResult",
    "eventData": {
        "alias": "user123",
        "tags": ["tag1", "tag2"],
        "pros": "属性",
        "checkTag": "检查的标签",
        "errorCode": 0,
        "tagCheckStateResult": "标签检查状态结果",
        "isTagCheckOperator": false,
        "sequence": 1,
        "mobileNumber": "手机号码",
        "protoType": "协议类型",
        "action": "操作类型"
    }
}
```

### 11. onMobileNumberOperatorResult
手机号码操作结果回调

**回调数据格式：**
```json
{
    "eventName": "onMobileNumberOperatorResult",
    "eventData": {
        "alias": "别名",
        "tags": ["tag1", "tag2"],
        "pros": "属性",
        "checkTag": "检查的标签",
        "errorCode": 0,
        "tagCheckStateResult": "标签检查状态结果",
        "isTagCheckOperator": false,
        "sequence": 1,
        "mobileNumber": "13800138000",
        "protoType": "协议类型",
        "action": "操作类型"
    }
}
```

### 12. onPropertyOperatorResult
属性操作结果回调

**回调数据格式：**
```json
{
    "eventName": "onPropertyOperatorResult",
    "eventData": {
        "alias": "user123",
        "tags": ["tag1", "tag2"],
        "pros": "属性",
        "checkTag": "检查的标签",
        "errorCode": 0,
        "tagCheckStateResult": "标签检查状态结果",
        "isTagCheckOperator": false,
        "sequence": 1,
        "mobileNumber": "手机号码",
        "protoType": "协议类型",
        "action": "操作类型"
    }
}
```

### 13. onNotificationSettingsCheck
通知设置检查回调

**回调数据格式：**
```json
{
    "eventName": "onNotificationSettingsCheck",
    "eventData": {
        "isOn": true,
        "source": 1
    }
}
```

### 14. onNotifyMessageUnShow
通知未显示回调

**回调数据格式：**
```json
{
    "eventName": "onNotifyMessageUnShow",
    "eventData": "通知内容的JSON字符串"
}
```

### 15. onInAppMessageShow
应用内消息展示回调

**回调数据格式：**
```json
{
    "eventName": "onInAppMessageShow",
    "eventData": "应用内消息内容的JSON字符串"
}
```

### 16. onInAppMessageClick
应用内消息点击回调

**回调数据格式：**
```json
{
    "eventName": "onInAppMessageClick",
    "eventData": "应用内消息内容的JSON字符串"
}
```

### 17. onGeofenceReceived
拉取地理围栏列表回调

**回调数据格式：**
```json
{
    "eventName": "onGeofenceReceived",
    "eventData": "地理围栏列表的JSON字符串"
}
```

### 18. onMultiActionClicked
多操作按钮点击回调

**回调数据格式：**
```json
{
    "eventName": "onMultiActionClicked",
    "eventData": {
        "action": "按钮动作",
        "extras": "额外数据"
    }
}
```

### 19. onGeofenceRegion
触发地理围栏回调

**回调数据格式：**
```json
{
    "eventName": "onGeofenceRegion",
    "eventData": {
        "geofence": "地理围栏标识",
        "longitude": 116.397128,
        "latitude": 39.916527
    }
}
```

## 使用示例

### 完整初始化示例

```typescript
// 1. 设置事件回调
setEventCallBack({
    callback: (event) => {
        switch(event.eventName) {
            case 'onCustomMessage':
                console.log('收到自定义消息:', event.eventData)
                break
            case 'onConnected':
                console.log('连接状态:', event.eventData)
                break
            case 'onNotifyMessageArrived':
                console.log('收到通知:', event.eventData)
                break
            case 'onClickMessage':
                console.log('点击通知:', event.eventData)
                break
            case 'onNotifyMessageDismiss':
                console.log('通知被清除:', event.eventData)
                break
            case 'onRegister':
                console.log('注册成功:', event.eventData)
                break
            case 'onCommandResult':
                console.log('命令结果:', event.eventData)
                break
            case 'onTagOperatorResult':
                console.log('标签操作结果:', event.eventData)
                break

            case 'onAliasOperatorResult':
                console.log('别名操作结果:', event.eventData)
                break
            case 'onMobileNumberOperatorResult':
                console.log('手机号码操作结果:', event.eventData)
                break
            case 'onPropertyOperatorResult':
                console.log('属性操作结果:', event.eventData)
                break
            case 'onNotificationSettingsCheck':
                console.log('通知设置检查:', event.eventData)
                break
            case 'onNotifyMessageUnShow':
                console.log('通知未显示:', event.eventData)
                break
            case 'onInAppMessageShow':
                console.log('应用内消息展示:', event.eventData)
                break
            case 'onInAppMessageClick':
                console.log('应用内消息点击:', event.eventData)
                break
            case 'onGeofenceReceived':
                console.log('地理围栏列表:', event.eventData)
                break
            case 'onMultiActionClicked':
                console.log('多操作按钮点击:', event.eventData)
                break
            case 'onGeofenceRegion':
                console.log('地理围栏触发:', event.eventData)
                break
        }
    }
})

// 2. 初始化推送服务
// 方式1：使用manifestPlaceholders.json中配置的AppKey
init()

// 方式2：动态设置AppKey（需要将manifestPlaceholders.json中的JPUSH_APPKEY设置为空字符串）
// init("你的appkey")
// 3. 开启调试模式
setDebug(true)

// 4. 设置渠道
setChannel("huawei")

// 5. 获取RegistrationID
const registrationId = getRegistrationId()
console.log('RegistrationID:', registrationId)

// 6. 设置标签和别名
setTags(1, ["vip", "premium"])
setAlias(2, "user123")

// 7. 设置手机号码
setMobileNumber(3, "13800138000")

// 8. 设置智能推送
setSmartPushEnable(true)
setDataInsightsEnable(true)
```

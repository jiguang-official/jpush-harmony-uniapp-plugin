# HarmonyOS极光推送UTS插件API文档

## 概述

本文档描述了HarmonyOS平台极光推送UTS插件的API接口，该插件基于极光推送SDK实现，提供了完整的推送功能支持。

## 核心API方法

### 1. 初始化与配置

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

#### setDebug(b: boolean)
设置调试模式

**参数：**
- `b`: boolean - 是否开启调试模式

**示例：**
```typescript
setDebug(true)  // 开启调试模式
setDebug(false) // 关闭调试模式
```

#### setHeartbeatTime(heartbeatTime: number)
设置长连接心跳周期

**参数：**
- `heartbeatTime`: number - 心跳周期时间（毫秒）

**示例：**
```typescript
setHeartbeatTime(30000)  // 设置30秒心跳周期
```

#### setAppKey(appKey: string)
设置应用AppKey

**参数：**
- `appKey`: string - 极光推送应用的AppKey

**示例：**
```typescript
setAppKey("your_app_key")
```

#### setChannel(channel: string)
设置应用渠道标识

**参数：**
- `channel`: string - 渠道标识

**示例：**
```typescript
setChannel("AppGallery")
```

#### setUserRequestNotificationPermission(enable: boolean)
配置用户通知权限申请方式

**参数：**
- `enable`: boolean - 是否启用用户请求通知权限

**示例：**
```typescript
setUserRequestNotificationPermission(true)
```

#### setSmartPushEnable(enable: boolean)
设置用户分群推送开关

**参数：**
- `enable`: boolean - 是否启用智能推送

**示例：**
```typescript
setSmartPushEnable(true)
```

#### setDataInsightsEnable(enable: boolean)
设置用户洞察开关

**参数：**
- `enable`: boolean - 是否启用数据洞察

**示例：**
```typescript
setDataInsightsEnable(true)
```

#### init(context?: common.UIAbilityContext | common.AbilityStageContext)
初始化极光推送服务

**参数：**
- `context`: common.UIAbilityContext | common.AbilityStageContext | undefined - 应用上下文（可选）

**示例：**
```typescript
init()  // 使用默认上下文
// 或
init(customContext)  // 使用自定义上下文
```

### 2. 设备标识管理

#### getRegistrationId(): string
获取设备的RegistrationID

**返回值：**
- `string`: 设备的唯一标识符

**示例：**
```typescript
const registrationId = getRegistrationId()
console.log('RegistrationID:', registrationId)
```

#### setCustomMessageMaxCacheCount(maxCacheCount: number)
设置自定义消息最大缓存数量

**参数：**
- `maxCacheCount`: number - 最大缓存数量

**示例：**
```typescript
setCustomMessageMaxCacheCount(100)
```

### 3. 推送控制

#### stopPush()
停止推送服务

**示例：**
```typescript
stopPush()
```

#### resumePush()
恢复推送服务

**示例：**
```typescript
resumePush()
```

#### isPushStopped(): boolean | undefined
检查推送服务是否已停止

**返回值：**
- `boolean | undefined`: 推送服务状态

**示例：**
```typescript
const isStopped = isPushStopped()
console.log('推送服务状态:', isStopped)
```

### 4. 标签管理

#### addTags(sequence: number, tags: string[])
添加标签

**参数：**
- `sequence`: number - 操作序列号
- `tags`: string[] - 要添加的标签数组

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
addTags(1, ["tag1", "tag2"])
```

#### deleteTags(sequence: number, tags: string[])
删除指定标签

**参数：**
- `sequence`: number - 操作序列号
- `tags`: string[] - 要删除的标签数组

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
deleteTags(2, ["tag1", "tag2"])
```

#### setTags(sequence: number, tags: string[])
设置标签（会覆盖现有标签）

**参数：**
- `sequence`: number - 操作序列号
- `tags`: string[] - 标签数组

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
setTags(3, ["tag1", "tag2", "tag3"])
```

#### checkTagBindState(sequence: number, tag: string)
验证标签绑定状态

**参数：**
- `sequence`: number - 操作序列号
- `tag`: string - 要检查的标签

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
checkTagBindState(4, "testTag")
```

#### cleanTags(sequence: number)
清除所有标签

**参数：**
- `sequence`: number - 操作序列号

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
cleanTags(5)
```

#### getTags(sequence: number, curr: number)
获取标签列表

**参数：**
- `sequence`: number - 操作序列号
- `curr`: number - 当前页码

**回调事件：** `onTagOperatorResult`

**示例：**
```typescript
getTags(6, 1)
```

### 5. 别名管理

#### setAlias(sequence: number, alias: string)
设置别名

**参数：**
- `sequence`: number - 操作序列号
- `alias`: string - 别名

**回调事件：** `onAliasOperatorResult`

**示例：**
```typescript
setAlias(7, "user123")
```

#### getAlias(sequence: number)
获取当前别名

**参数：**
- `sequence`: number - 操作序列号

**回调事件：** `onAliasOperatorResult`

**示例：**
```typescript
getAlias(8)
```

#### deleteAlias(sequence: number)
删除别名

**参数：**
- `sequence`: number - 操作序列号

**回调事件：** `onAliasOperatorResult`

**示例：**
```typescript
deleteAlias(9)
```

### 6. 手机号码管理

#### setMobileNumber(sequence: number, mobileNumber: string)
设置手机号码

**参数：**
- `sequence`: number - 操作序列号
- `mobileNumber`: string - 手机号码

**回调事件：** `onMobileNumberOperatorResult`

**示例：**
```typescript
setMobileNumber(10, "13800138000")
```

### 7. 角标管理

#### setBadgeNumber(badgeNumber: number)
设置应用角标数量

**参数：**
- `badgeNumber`: number - 角标数量

**示例：**
```typescript
setBadgeNumber(5)  // 设置角标为5
```

### 8. 通知管理

#### clearNotificationById(id: number)
清除指定通知

**参数：**
- `id`: number - 通知ID

**示例：**
```typescript
clearNotificationById(123)
```

#### clearNotificationByMsgId(msgId: string)
通过消息ID清除通知

**参数：**
- `msgId`: string - 消息ID

**示例：**
```typescript
clearNotificationByMsgId("msg_123")
```

#### clearNotificationAll()
清除所有通知

**示例：**
```typescript
clearNotificationAll()
```

### 9. 消息处理

#### setClickWant(want: Want): Promise<JMessage | undefined>
设置点击通知时的Want对象

**参数：**
- `want`: Want - 通知点击时的Want对象

**返回值：**
- `Promise<JMessage | undefined>`: 消息对象

**示例：**
```typescript
const message = await setClickWant(want)
```

#### customMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean>
处理自定义消息后台数据

**参数：**
- `data`: pushCommon.PushPayload - 推送载荷数据

**返回值：**
- `Promise<boolean>`: 处理结果

**示例：**
```typescript
const result = await customMessageBackgroundData(payload)
```

#### voIPMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean>
处理VoIP消息后台数据

**参数：**
- `data`: pushCommon.PushPayload - 推送载荷数据

**返回值：**
- `Promise<boolean>`: 处理结果

**示例：**
```typescript
const result = await voIPMessageBackgroundData(payload)
```

#### extraMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean>
处理扩展消息后台数据

**参数：**
- `data`: pushCommon.PushPayload - 推送载荷数据

**返回值：**
- `Promise<boolean>`: 处理结果

**示例：**
```typescript
const result = await extraMessageBackgroundData(payload)
```

#### receiveExtraDataMessage(rNEAbility: RemoteNotificationExtensionAbility, remoteNotificationInfo: pushCommon.RemoteNotificationInfo): Promise<JMessageExtra | undefined>
接收扩展数据消息

**参数：**
- `rNEAbility`: RemoteNotificationExtensionAbility - 远程通知扩展能力
- `remoteNotificationInfo`: pushCommon.RemoteNotificationInfo - 远程通知信息

**返回值：**
- `Promise<JMessageExtra | undefined>`: 扩展消息对象

**示例：**
```typescript
const extraMessage = await receiveExtraDataMessage(rNEAbility, notificationInfo)
```

#### defaultMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean>
默认消息后台数据接收

**参数：**
- `data`: pushCommon.PushPayload - 推送载荷数据

**返回值：**
- `Promise<boolean>`: 处理结果

**示例：**
```typescript
const result = await defaultMessageBackgroundData(payload)
```

### 10. 数据上报

#### reportCustomDisplay(channel: number, msgId: string)
上报自定义消息展示

**参数：**
- `channel`: number - 渠道ID
- `msgId`: string - 消息ID

**示例：**
```typescript
reportCustomDisplay(1, "msg_123")
```

#### reportCustomClick(channel: number, msgId: string)
上报自定义消息点击

**参数：**
- `channel`: number - 渠道ID
- `msgId`: string - 消息ID

**示例：**
```typescript
reportCustomClick(1, "msg_123")
```

#### reportNotificationDisplay(channel: number, msgId: string)
上报通知展示

**参数：**
- `channel`: number - 渠道ID
- `msgId`: string - 消息ID

**示例：**
```typescript
reportNotificationDisplay(1, "msg_123")
```

#### reportNotificationClick(channel: number, msgId: string)
上报通知点击

**参数：**
- `channel`: number - 渠道ID
- `msgId`: string - 消息ID

**示例：**
```typescript
reportNotificationClick(1, "msg_123")
```

### 11. 数据收集控制

#### setListWifi(enable: boolean)
设置WiFi列表收集开关

**参数：**
- `enable`: boolean - 是否启用WiFi列表收集

**示例：**
```typescript
setListWifi(true)
```

#### setEnableAppTerminate(enable: boolean)
设置应用终止数据收集开关

**参数：**
- `enable`: boolean - 是否启用应用终止数据收集

**示例：**
```typescript
setEnableAppTerminate(true)
```

## 事件回调

插件支持以下事件回调：

### 1. onRegister
注册成功后回调rid

**回调数据格式：**
```json
{
    "eventName": "onRegister",
    "eventData": "registrationId字符串"
}
```

### 2. onConnected
长连接登陆回调

**回调数据格式：**
```json
{
    "eventName": "onConnected",
    "eventData": "true"  // 或 "false"
}
```

### 3. onCustomMessage
收到自定义消息时触发

**回调数据格式：**
```json
{
    "eventName": "onCustomMessage",
    "eventData": "消息内容的JSON字符串"
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

### 5. onTagOperatorResult
标签操作结果回调

**回调数据格式：**
```json
{
    "eventName": "onTagOperatorResult",
    "eventData": {
        "code": 0,
        "tags": ["tag1", "tag2"],
        "sequence": 1,
        "isBind": true  // 仅在checkTagBindState时存在
    }
}
```

### 6. onAliasOperatorResult
别名操作结果回调

**回调数据格式：**
```json
{
    "eventName": "onAliasOperatorResult",
    "eventData": {
        "code": 0,
        "alias": "user123",
        "sequence": 1
    }
}
```

### 7. onMobileNumberOperatorResult
手机号码操作结果回调

**回调数据格式：**
```json
{
    "eventName": "onMobileNumberOperatorResult",
    "eventData": {
        "code": 0,
        "message": "success",
        "mobileNumber": "13800138000",
        "sequence": 1
    }
}
```

### 8. onJMessageExtra
通知扩展消息回调

**回调数据格式：**
```json
{
    "eventName": "onJMessageExtra",
    "eventData": {
        "msgId": "消息ID",
        "title": "标题",
        "content": "内容",
        "extras": "自定义数据",
        "extraData": "扩展数据"
    }
}
```

### 9. onJMessageVoIP
VoIP呼叫消息回调

**回调数据格式：**
```json
{
    "eventName": "onJMessageVoIP",
    "eventData": {
        "msgId": "消息ID",
        "extraData": "VoIP自定义数据"
    }
}
```

### 10. onCommandResult
交互事件回调

**回调数据格式：**
```json
{
    "eventName": "onCommandResult",
    "eventData": {
        "cmd": 2007,  // 2007通知停止，2006恢复通知
        "errorCode": 0,
        "msg": "内容信息",
        "extra": "额外数据"
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
            case 'onRegister':
                console.log('注册成功:', event.eventData)
                break
            case 'onConnected':
                console.log('连接状态:', event.eventData)
                break
            case 'onCustomMessage':
                console.log('收到自定义消息:', event.eventData)
                break
            case 'onClickMessage':
                console.log('点击通知:', event.eventData)
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
            case 'onJMessageExtra':
                console.log('扩展消息:', event.eventData)
                break
            case 'onJMessageVoIP':
                console.log('VoIP消息:', event.eventData)
                break
            case 'onCommandResult':
                console.log('命令结果:', event.eventData)
                break
        }
    }
})

// 2. 设置应用配置
setDebug(true)

// 3. 设置推送配置
setUserRequestNotificationPermission(true)
setSmartPushEnable(true)
setDataInsightsEnable(true)
setHeartbeatTime(30000)

// 4. 初始化推送服务
init()

// 5. 获取RegistrationID
const registrationId = getRegistrationId()
console.log('RegistrationID:', registrationId)

// 6. 设置标签和别名
setTags(1, ["vip", "premium"])
setAlias(2, "user123")
```

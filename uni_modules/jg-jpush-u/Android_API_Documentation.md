# Android极光推送UTS插件API文档

## 概述

本文档描述了Android平台极光推送UTS插件的API接口，该插件基于极光推送SDK实现，提供了完整的推送功能支持。

## 核心API方法

### 1. 初始化与配置

#### init()
初始化极光推送服务

**示例：**
```typescript
init()
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
请求通知权限

**示例：**
```typescript
requestPermission()
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

#### setDataInsightsEnable(isEnable: boolean)
设置数据洞察开关

**参数：**
- `isEnable`: boolean - 是否启用数据洞察

**示例：**
```typescript
setDataInsightsEnable(true)
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
        "code": 0,
        "tags": ["tag1", "tag2"],
        "sequence": 1,
        "isBind": true  // 仅在checkTagBindState时存在
    }
}
```

### 9. onCheckTagOperatorResult
检查标签操作结果回调

**回调数据格式：**
```json
{
    "eventName": "onCheckTagOperatorResult",
    "eventData": {
        "code": 0,
        "tags": ["tag1"],
        "sequence": 1,
        "isBind": true
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
        "code": 0,
        "alias": "user123",
        "sequence": 1
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
        "code": 0,
        "message": "success",
        "mobileNumber": "13800138000",
        "sequence": 1
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
        "code": 0,
        "alias": "user123",
        "tags": ["tag1", "tag2"],
        "sequence": 1
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
            case 'onCheckTagOperatorResult':
                console.log('检查标签结果:', event.eventData)
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
init()

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

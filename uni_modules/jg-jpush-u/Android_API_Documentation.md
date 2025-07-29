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
            case 'onTagOperatorResult':
                console.log('标签操作结果:', event.eventData)
                break
            case 'onAliasOperatorResult':
                console.log('别名操作结果:', event.eventData)
                break
            case 'onMobileNumberOperatorResult':
                console.log('手机号码操作结果:', event.eventData)
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

## 注意事项

1. **初始化顺序**：必须先调用 `setEventCallBack` 设置回调，再调用 `init` 初始化
2. **序列号管理**：每个操作都需要唯一的序列号，用于区分不同的操作结果
3. **回调处理**：所有异步操作的结果都通过事件回调返回
4. **权限要求**：Android平台需要配置推送证书和权限
5. **生命周期管理**：需要在应用生命周期中调用相应的方法
6. **调试模式**：开发阶段建议开启调试模式，生产环境请关闭

## 错误码说明

- `0`: 操作成功
- 其他值: 操作失败，具体错误码请参考极光推送官方文档

## 版本信息

- 插件版本：基于极光推送SDK
- 支持平台：Android
- 最低Android版本：Android 4.0+ 
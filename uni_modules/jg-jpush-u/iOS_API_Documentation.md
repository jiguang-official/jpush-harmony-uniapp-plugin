# iOS极光推送UTS插件API文档

## 概述

本文档描述了iOS平台极光推送UTS插件的API接口，该插件基于极光推送SDK实现，提供了完整的推送功能支持。

## 数据类型

### InitPushParams
初始化推送服务的参数类型

```typescript
export type InitPushParams = {
    appkey: string,        // 极光推送应用的AppKey
    channel: string,       // 应用渠道标识
    isProduction: boolean, // 是否为生产环境
    advertisingId: string  // 广告标识符
}
```

## 核心API方法

### 1. 初始化与配置

#### initPush(param: InitPushParams)
初始化极光推送服务

**参数：**
- `param`: InitPushParams - 初始化参数

**示例：**
```typescript
initPush({
    appkey: "your_app_key",
    channel: "AppStore",
    isProduction: true,
    advertisingId: "your_advertising_id"
})
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

### 3. 标签管理

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

### 4. 别名管理

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

### 5. 手机号码管理

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

### 6. 角标管理

#### setBadgeNumber(curNum: Int)
设置应用角标数量

**参数：**
- `curNum`: Int - 角标数量

**示例：**
```typescript
setBadgeNumber(5)  // 设置角标为5
```

#### resetBadge()
重置角标数量为0

**示例：**
```typescript
resetBadge()  // 清除角标
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
initPush({
    appkey: "your_app_key",
    channel: "AppStore",
    isProduction: true,
    advertisingId: "your_advertising_id"
})

// 3. 开启调试模式
setDebug(true)

// 4. 获取RegistrationID
const registrationId = getRegistrationId()
console.log('RegistrationID:', registrationId)

// 5. 设置标签和别名
setTags(1, ["vip", "premium"])
setAlias(2, "user123")

// 6. 设置手机号码
setMobileNumber(3, "13800138000")
```

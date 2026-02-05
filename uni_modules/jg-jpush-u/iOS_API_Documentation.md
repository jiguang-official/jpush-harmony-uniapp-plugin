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

### CollectControlOptions
数据采集控制项（用于 setCollectControl）。iOS 支持 ssid、bssid、cell、gps；未传或未设为 `false` 的项保持 SDK 默认（采集）。

```typescript
export type CollectControlOptions = {
    ssid?: boolean,   // SSID 信息
    bssid?: boolean,  // BSSID 信息
    cell?: boolean,   // 基站信息
    gps?: boolean     // 经纬度信息
}
```

### LocalNotificationOptions
本地通知参数（用于 addLocalNotification）。iOS 侧使用 JPush 2.1.9+ 的 `addNotification`，会映射为 `JPushNotificationContent`（title、body、userInfo）和 `JPushNotificationTrigger`（按 `broadcastTime` 计算 timeInterval）。

```typescript
export type LocalNotificationOptions = {
    notificationId: number,  // 必填，本地通知 ID，用作 requestIdentifier，建议为正整数
    broadcastTime: number,   // 必填，触发时间（毫秒时间戳），用于计算 timeInterval
    title?: string,         // 通知标题 → content.title
    content?: string,       // 通知内容 → content.body
    extras?: string,        // 额外数据（JSON 字符串）→ content.userInfo["extras"]
    builderId?: number,     // 本平台未使用
    category?: string,      // 可选，未在当前实现中设置
    priority?: number,      // 本平台未使用
    channelId?: string     // 本平台未使用
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

同时调用极光SDK和系统接口设置角标：
- iOS 16+：使用 `UNUserNotificationCenter.setBadgeCount()`
- iOS 16以下：使用 `UIApplication.shared.applicationIconBadgeNumber`

**参数：**
- `curNum`: Int - 角标数量

**示例：**
```typescript
setBadgeNumber(5)  // 设置角标为5
```

#### resetBadge()
重置角标数量为0

同时调用极光SDK和系统接口重置角标：
- iOS 16+：使用 `UNUserNotificationCenter.setBadgeCount(0)`
- iOS 16以下：使用 `UIApplication.shared.applicationIconBadgeNumber = 0`

**示例：**
```typescript
resetBadge()  // 清除角标
```

#### getBadgeNumber(): number
获取当前应用角标数量

**返回值：**
- `number`: 当前角标数量

**示例：**
```typescript
const badge = getBadgeNumber()
console.log('当前角标数量:', badge)
```

### 7. 本地通知

通过极光 SDK 在应用内添加定时本地通知，不依赖网络。iOS 使用 JPush 2.1.9+ 的 `addNotification` / `removeNotification` 实现。

#### addLocalNotification(options: LocalNotificationOptions)
添加一条本地通知。内部会构建 `JPushNotificationContent`、`JPushNotificationTrigger`（基于 `broadcastTime` 的 timeInterval）、`JPushNotificationRequest` 并调用极光 `addNotification`。

**参数：**
- `options`: LocalNotificationOptions（见上方数据类型）
  - `notificationId`、`broadcastTime` 必填
  - `title`、`content`、`extras` 等可选

**示例：**
```typescript
import { addLocalNotification, type LocalNotificationOptions } from '@/uni_modules/jg-jpush-u'

addLocalNotification({
    notificationId: 10001,
    broadcastTime: Date.now() + 10 * 60 * 1000, // 10 分钟后
    title: '提醒',
    content: '这是一条本地通知',
    extras: '{"key":"value"}'
})
```

#### removeLocalNotification(notificationId: number)
移除指定 ID 的本地通知（对应极光 `removeNotification` 传入该 identifier）。

**示例：**
```typescript
removeLocalNotification(10001)
```

#### clearLocalNotifications()
清除所有本地通知（对应极光 `removeNotification(nil)`）。

**示例：**
```typescript
clearLocalNotifications()
```

### 8. 数据采集控制（仅 iOS 支持部分项）

#### setCollectControl(options: CollectControlOptions | null)
设置可选个人信息采集控制。iOS 支持关闭 ssid、bssid、cell、gps 的采集；未传或未设为 `false` 的项保持 SDK 默认（采集）。需在初始化前或初始化后尽早调用。

**参数：**
- `options`: CollectControlOptions | null
  - `ssid?: boolean` - 设为 `false` 不采集 SSID
  - `bssid?: boolean` - 设为 `false` 不采集 BSSID
  - `cell?: boolean` - 设为 `false` 不采集基站信息
  - `gps?: boolean` - 设为 `false` 不采集经纬度

**示例：**
```typescript
setCollectControl({ gps: false })
setCollectControl({ ssid: false, bssid: false, cell: false, gps: false })
```

### 9. 地理围栏

#### setGeofenceInterval(intervalMs: number)
设置地理围栏监控周期。参数统一为毫秒，内部会转为 iOS 的秒（对应 `setGeofenecePeriodForInside`）。默认 15 分钟检测一次。

**参数：**
- `intervalMs`: number - 监控周期，毫秒

**示例：**
```typescript
setGeofenceInterval(15 * 60 * 1000)  // 15 分钟
```

#### setMaxGeofenceNumber(maxNumber: number)
设置允许保存的最大地理围栏个数。iOS 系统最大 20，传入大于 20 时按 20 处理（对应 `setGeofeneceMaxCount`）。

**参数：**
- `maxNumber`: number - 最多允许保存的围栏个数

**示例：**
```typescript
setMaxGeofenceNumber(20)
```

#### deleteGeofence(geofenceId: string)
删除指定 id 的地理围栏（对应 `removeGeofenceWithIdentifier`）。

**参数：**
- `geofenceId`: string - 地理围栏 id

**示例：**
```typescript
deleteGeofence("your_geofence_id")
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

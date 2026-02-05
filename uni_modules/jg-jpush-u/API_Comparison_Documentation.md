# 极光推送UTS插件三平台API对比文档

## 概述

本文档对比了iOS、Android和HarmonyOS三个平台的极光推送UTS插件API接口，帮助开发者了解各平台的异同点，便于跨平台开发。

## 平台基本信息

| 平台 | 最低版本要求 | 主要特点 |
|------|-------------|----------|
| iOS | iOS 10.0+ | 基于极光推送SDK，支持iOS原生推送 |
| Android | Android 4.0+ | 基于极光推送SDK，支持多种推送渠道 |
| HarmonyOS | API 9+ | 基于极光推送SDK，支持HarmonyOS原生推送 |

## API方法对比

### 1. 初始化与配置

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 初始化推送服务 | `initPush(param: InitPushParams)` | `init()` | `init(context?)` | iOS需要参数对象，Android和HarmonyOS使用默认参数 |
| 设置调试模式 | `setDebug(debug: boolean)` | `setDebug(debug: boolean)` | `setDebug(b: boolean)` | 功能相同，参数类型一致 |
| 设置事件回调 | `setEventCallBack(param: EventCallBackParams)` | `setEventCallBack(param: EventCallBackParams)` | `setEventCallBack(param: EventCallBackParams)` | 三个平台完全一致 |
| 设置AppKey | - | - | `setAppKey(appKey: string)` | 仅HarmonyOS支持 |
| 设置渠道 | - | `setChannel(channel: string)` | `setChannel(channel: string)` | iOS在初始化时设置，Android和HarmonyOS单独设置 |
| 设置心跳周期 | - | - | `setHeartbeatTime(heartbeatTime: number)` | 仅HarmonyOS支持 |
| 设置通知权限申请方式 | - | - | `setUserRequestNotificationPermission(enable: boolean)` | 仅HarmonyOS支持 |

### 2. 设备标识管理

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 获取RegistrationID | `getRegistrationId(): string` | `getRegistrationId(): string` | `getRegistrationId(): string` | 三个平台完全一致 |
| 设置自定义消息缓存数量 | - | - | `setCustomMessageMaxCacheCount(maxCacheCount: number)` | 仅HarmonyOS支持 |

### 3. 推送控制

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 停止推送 | - | `stopPush()` | `stopPush()` | iOS不支持 |
| 恢复推送 | - | `resumePush()` | `resumePush()` | iOS不支持 |
| 检查推送状态 | - | `isPushStopped(): boolean` | `isPushStopped(): boolean \| undefined` | iOS不支持 |
| 获取推送连接状态 | - | `getConnectionState(): boolean` | `getConnectionState(): boolean \| undefined` | 仅 Android 支持 |

### 4. 标签管理

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 设置标签 | `setTags(sequence: Int, tags: string[])` | `setTags(sequence: Int, tags: string[])` | `setTags(sequence: number, tags: string[])` | 功能相同，HarmonyOS使用number类型 |
| 添加标签 | `addTags(sequence: Int, tags: string[])` | `addTags(sequence: Int, tags: string[])` | `addTags(sequence: number, tags: string[])` | 功能相同，HarmonyOS使用number类型 |
| 删除标签 | `deleteTags(sequence: Int, tags: string[])` | `deleteTags(sequence: Int, tags: string[])` | `deleteTags(sequence: number, tags: string[])` | 功能相同，HarmonyOS使用number类型 |
| 清除所有标签 | `cleanTags(sequence: Int)` | `cleanTags(sequence: Int)` | `cleanTags(sequence: number)` | 功能相同，HarmonyOS使用number类型 |
| 获取所有标签 | `getAllTags(sequence: Int)` | `getAllTags(sequence: Int)` | - | HarmonyOS不支持一次性获取所有标签 |
| 分页获取标签 | - | - | `getTags(sequence: number, curr: number)` | 仅HarmonyOS支持，需要页码参数 |
| 验证标签绑定状态 | `checkTagBindState(sequence: Int, tag: string)` | `checkTagBindState(sequence: Int, tag: string)` | `checkTagBindState(sequence: number, tag: string)` | 功能相同，HarmonyOS使用number类型 |
| 筛选有效标签 | `filterValidTags(tags: string[]): string[]` | `filterValidTags(tags: string[]): string[]` | `filterValidTags(tags: string[]): string[]` | Android/iOS 支持 |

### 5. 别名管理

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 设置别名 | `setAlias(sequence: Int, alias: string)` | `setAlias(sequence: Int, alias: string)` | `setAlias(sequence: number, alias: string)` | 功能相同，HarmonyOS使用number类型 |
| 删除别名 | `deleteAlias(sequence: Int)` | `deleteAlias(sequence: Int)` | `deleteAlias(sequence: number)` | 功能相同，HarmonyOS使用number类型 |
| 获取别名 | `getAlias(sequence: Int)` | `getAlias(sequence: Int)` | `getAlias(sequence: number)` | 功能相同，HarmonyOS使用number类型 |

### 6. 手机号码管理

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 设置手机号码 | `setMobileNumber(sequence: number, mobileNumber: string)` | `setMobileNumber(sequence: Int, mobileNumber: string)` | `setMobileNumber(sequence: number, mobileNumber: string)` | 功能相同，iOS和HarmonyOS使用number类型 |

### 7. 角标管理

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 设置角标数量 | `setBadgeNumber(curNum: Int)` | `setBadgeNumber(curNum: Int)` | `setBadgeNumber(badgeNumber: number)` | 功能相同，HarmonyOS使用number类型 |
| 重置角标 | `resetBadge()` | - | - | 仅iOS支持 |

### 8. 通知管理

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 设置允许推送时间 | - | `setPushTime(weekDays, startHour, endHour)` | - | 仅Android支持 |
| 设置通知静默时间 | - | `setSilenceTime(startHour, startMinute, endHour, endMinute)` | - | 仅Android支持 |
| 设置最新通知数量 | - | `setLatestNotificationNumber(maxNum: Int)` | - | 仅Android支持 |
| 清除所有通知 | - | `clearNotificationAll()` | `clearNotificationAll()` | iOS不支持 |
| 根据ID清除通知 | - | `clearNotificationById(notificationId: Int)` | `clearNotificationById(id: number)` | iOS不支持 |
| 根据消息ID清除通知 | - | - | `clearNotificationByMsgId(msgId: string)` | 仅HarmonyOS支持 |

### 9. 生命周期管理

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 应用恢复 | - | `onResume()` | - | 仅Android支持 |
| 应用暂停 | - | `onPause()` | - | 仅Android支持 |
| Fragment恢复 | - | `onFragmentResume(fragmentName: string)` | - | 仅Android支持 |
| Fragment暂停 | - | `onFragmentPause(fragmentName: string)` | - | 仅Android支持 |
| 进程被杀死 | - | `onKillProcess()` | - | 仅Android支持 |

### 10. 权限管理

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 请求通知权限 | - | `requestPermission()` | - | 仅Android支持 |
| 检查通知权限状态 | - | `isNotificationEnabled(): number` | - | 仅Android支持 |
| 跳转到通知设置 | - | `goToAppNotificationSettings()` | - | 仅Android支持 |
| 触发通知状态检查 | - | `triggerNotificationStateCheck()` | - | 仅Android支持 |
| 上报通知打开事件 | - | `reportNotificationOpened(msgId: string, channel?: number)` | 同左，channel 可选（0=厂商 1=极光），不传默认极光通道 | Android/鸿蒙支持 |

### 11. 智能推送设置

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 设置智能推送开关 | - | `setSmartPushEnable(isEnable: boolean)` | `setSmartPushEnable(enable: boolean)` | iOS不支持 |
| 设置地理围栏开关 | - | `setGeofenceEnable(isEnable: boolean)` | - | 仅Android支持 |
| 设置地理围栏监控周期 | `setGeofenceInterval(intervalMs: number)` | `setGeofenceInterval(intervalMs: number)` | 占位 | Android/iOS 已实现 |
| 设置最大地理围栏个数 | `setMaxGeofenceNumber(maxNumber: number)` | `setMaxGeofenceNumber(maxNumber: number)` | 占位 | Android 1-100，iOS 最大 20 |
| 删除地理围栏 | `deleteGeofence(geofenceId: string)` | `deleteGeofence(geofenceId: string)` | 占位 | Android/iOS 已实现 |
| 设置数据洞察开关 | - | `setDataInsightsEnable(isEnable: boolean)` | `setDataInsightsEnable(enable: boolean)` | iOS不支持 |

### 12. 消息处理（HarmonyOS特有）

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 设置点击Want对象 | - | - | `setClickWant(want: Want): Promise<JMessage \| undefined>` | 仅HarmonyOS支持 |
| 处理自定义消息后台数据 | - | - | `customMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean>` | 仅HarmonyOS支持 |
| 处理VoIP消息后台数据 | - | - | `voIPMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean>` | 仅HarmonyOS支持 |
| 处理扩展消息后台数据 | - | - | `extraMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean>` | 仅HarmonyOS支持 |
| 接收扩展数据消息 | - | - | `receiveExtraDataMessage(rNEAbility, remoteNotificationInfo): Promise<JMessageExtra \| undefined>` | 仅HarmonyOS支持 |
| 默认消息后台数据接收 | - | - | `defaultMessageBackgroundData(data: pushCommon.PushPayload): Promise<boolean>` | 仅HarmonyOS支持 |

### 13. 数据上报（HarmonyOS特有）

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 上报自定义消息展示 | - | - | `reportCustomDisplay(channel: number, msgId: string)` | 仅HarmonyOS支持 |
| 上报自定义消息点击 | - | - | `reportCustomClick(channel: number, msgId: string)` | 仅HarmonyOS支持 |
| 上报通知展示 | - | - | `reportNotificationDisplay(channel: number, msgId: string)` | 仅HarmonyOS支持 |
| 上报通知点击 | - | - | `reportNotificationClick(channel: number, msgId: string)` | 仅HarmonyOS支持 |

### 14. 数据收集控制（HarmonyOS特有）

| 功能 | iOS | Android | HarmonyOS | 说明 |
|------|-----|---------|-----------|------|
| 设置WiFi列表收集开关 | - | - | `setListWifi(enable: boolean)` | 仅HarmonyOS支持 |
| 设置应用终止数据收集开关 | - | - | `setEnableAppTerminate(enable: boolean)` | 仅HarmonyOS支持 |

## 事件回调对比

### 事件名称对比

| 事件类型 | iOS | Android | HarmonyOS | 说明 |
|----------|-----|---------|-----------|------|
| 自定义消息 | `onCustomMessage` | `onCustomMessage` | `onCustomMessage` | 三个平台一致 |
| 连接状态 | `onConnected` | `onConnected` | `onConnected` | 三个平台一致 |
| 收到通知 | `onNotifyMessageArrived` | `onNotifyMessageArrived` | - | HarmonyOS不支持 |
| 点击通知 | `onClickMessage` | `onClickMessage` | `onClickMessage` | 三个平台一致 |
| 通知被清除 | `onNotifyMessageDismiss` | `onNotifyMessageDismiss` | - | HarmonyOS不支持 |
| 设备注册 | - | `onRegister` | `onRegister` | iOS不支持 |
| 命令结果 | - | `onCommandResult` | `onCommandResult` | iOS不支持 |
| 标签操作结果 | `onTagOperatorResult` | `onTagOperatorResult` | `onTagOperatorResult` | 三个平台一致，包括标签设置、添加、删除、清除、获取和验证绑定状态等操作 |

| 别名操作结果 | `onAliasOperatorResult` | `onAliasOperatorResult` | `onAliasOperatorResult` | 三个平台一致 |
| 手机号码操作结果 | `onMobileNumberOperatorResult` | `onMobileNumberOperatorResult` | `onMobileNumberOperatorResult` | 三个平台一致 |
| 属性操作结果 | - | `onPropertyOperatorResult` | - | 仅Android支持 |
| 通知设置检查 | - | `onNotificationSettingsCheck` | - | 仅Android支持 |
| 通知未显示 | - | `onNotifyMessageUnShow` | - | 仅Android支持 |
| 应用内消息展示 | - | `onInAppMessageShow` | - | 仅Android支持 |
| 应用内消息点击 | - | `onInAppMessageClick` | - | 仅Android支持 |
| 地理围栏列表 | - | `onGeofenceReceived` | - | 仅Android支持 |
| 多操作按钮点击 | - | `onMultiActionClicked` | - | 仅Android支持 |
| 地理围栏触发 | - | `onGeofenceRegion` | - | 仅Android支持 |
| 扩展消息 | - | - | `onJMessageExtra` | 仅HarmonyOS支持 |
| VoIP消息 | - | - | `onJMessageVoIP` | 仅HarmonyOS支持 |

### 回调数据格式

所有平台的事件回调数据格式基本一致，都使用JSON字符串格式：

```json
{
    "eventName": "事件名称",
    "eventData": "事件数据（JSON字符串）"
}
```

## 数据类型对比

### 序列号类型

| 平台 | 序列号类型 | 说明 |
|------|-----------|------|
| iOS | `Int` | Swift的Int类型 |
| Android | `Int` | Java的int类型 |
| HarmonyOS | `number` | TypeScript的number类型 |

### 初始化参数

| 平台 | 初始化方式 | 参数类型 |
|------|-----------|----------|
| iOS | `InitPushParams`对象 | 包含appkey、channel、isProduction、advertisingId |
| Android | 无参数 | 使用默认配置 |
| HarmonyOS | 可选context参数 | 支持自定义应用上下文 |


三个平台的极光推送UTS插件在核心功能上保持一致，但在平台特有功能和API设计上存在显著差异：

1. **iOS**: 功能相对精简，专注于核心推送功能，API设计简洁
2. **Android**: 功能最全面，支持完整的生命周期管理和丰富的回调事件
3. **HarmonyOS**: 功能最丰富，支持高级消息处理、数据分析和异步操作

开发者可以根据具体需求选择合适的平台，或通过统一封装实现跨平台兼容。建议在开发初期就确定目标平台，以便充分利用各平台的特色功能。 
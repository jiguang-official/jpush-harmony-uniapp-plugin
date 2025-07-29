# Android极光推送UTS插件集成指南

## 概述

本文档详细介绍了如何在Android项目中集成极光推送UTS插件，包括环境配置、权限设置、代码集成等步骤。

## 前置条件

- Android Studio 4.0+
- Android SDK API 21+ (Android 5.0+)
- uni-app项目
- 极光推送开发者账号

## 1. 极光推送平台配置

### 1.1 创建应用

1. 登录[极光推送控制台](https://www.jiguang.cn/)
2. 创建新应用或选择现有应用
3. 记录应用的AppKey

## 2. 项目配置


### 2.1 配置manifestPlaceholders.json

在 `nativeResources/android/` 目录下创建或修改 `manifestPlaceholders.json` 文件：

```json
{
  "JPUSH_APPKEY": "your_jpush_appkey_here",
  "JPUSH_CHANNEL": "your_channel_name"
}
```

**参数说明：**
- `JPUSH_APPKEY`: 极光推送应用的AppKey（必填）
- `JPUSH_CHANNEL`: 应用渠道标识（必填，如：developer-default、huawei、xiaomi等）

**示例配置：**
```json
{
  "JPUSH_APPKEY": "0e61f6029655510c1350a80e",
  "JPUSH_CHANNEL": "developer-default"
}
```

## 3. 代码集成

### 3.1 引入插件

在需要使用推送功能的页面中引入插件：

```typescript
import { 
  init, 
  setDebug, 
  setEventCallBack, 
  getRegistrationId,
  setTags,
  setAlias,
  setMobileNumber,
  stopPush,
  resumePush
} from "@/uni_modules/jg-jpush-u"
```

### 3.2 初始化推送服务

```typescript
// 设置事件回调
setEventCallBack({
  callback: (event) => {
    console.log('收到推送事件:', event.eventName, event.eventData)
    
    switch(event.eventName) {
      case 'onCustomMessage':
        // 处理自定义消息
        console.log('收到自定义消息:', event.eventData)
        break
        
      case 'onConnected':
        // 处理连接状态变化
        console.log('连接状态:', event.eventData)
        break
        
      case 'onNotifyMessageArrived':
        // 处理前台收到通知
        console.log('收到通知:', event.eventData)
        break
        
      case 'onClickMessage':
        // 处理用户点击通知
        console.log('点击通知:', event.eventData)
        break
        
      case 'onTagOperatorResult':
        // 处理标签操作结果
        console.log('标签操作结果:', event.eventData)
        break
        
      case 'onAliasOperatorResult':
        // 处理别名操作结果
        console.log('别名操作结果:', event.eventData)
        break
        
      case 'onMobileNumberOperatorResult':
        // 处理手机号码操作结果
        console.log('手机号码操作结果:', event.eventData)
        break
    }
  }
})


// 开启调试模式（开发阶段）
setDebug(true)

// 初始化推送服务
init()

```

### 3.3 获取设备标识

```typescript
// 获取RegistrationID
const registrationId = getRegistrationId()
console.log('设备RegistrationID:', registrationId)
```

### 3.4 设置用户标识

```typescript
// 设置标签
setTags(1, ["vip", "premium"])

// 设置别名
setAlias(2, "user123")

// 设置手机号码
setMobileNumber(3, "13800138000")
```



## 4. 版本兼容性

- **最低支持版本**: Android 5.0+ (API 21+)
- **推荐版本**: Android 8.0+ (API 26+)
- **uni-app版本**: 3.0+

## 5. 相关资源

- [极光推送官方文档](https://docs.jiguang.cn/jpush/)
- [uni-app官方文档](https://uniapp.dcloud.net.cn/)
- [Android开发文档](https://developer.android.com/) 
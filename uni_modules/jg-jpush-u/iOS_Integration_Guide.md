# iOS极光推送UTS插件集成指南

## 概述

本文档详细介绍了如何在iOS项目中集成极光推送UTS插件，包括环境配置、权限设置、代码集成等步骤。

## 前置条件

- Xcode 12.0+
- iOS 9.0+
- uni-app项目
- 极光推送开发者账号
- Apple Developer账号

## 1. 极光推送平台配置

### 1.1 创建应用

1. 登录[极光推送控制台](https://www.jiguang.cn/)
2. 创建新应用或选择现有应用
3. 记录应用的AppKey



## 2. 代码集成

### 2.1 引入插件

在需要使用推送功能的页面中引入插件：

```typescript
import { 
  initPush, 
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

### 2.2 初始化推送服务

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
initPush({
  appkey: "您的极光AppKey", // 从极光推送控制台获取
  channel: "App Store",     // 渠道名称，用于统计
  isProduction: false,      // 开发环境设为false，生产环境设为true
  advertisingId: ""         // 广告标识符，可选
})
```

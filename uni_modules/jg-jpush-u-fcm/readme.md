# jg-jpush-u-fcm

## 1. 特别说明
这个插件是依附：jg-jpush-u 插件而存在，要使用这个插件就必须使用jg-jpush-u插件

## 2. 项目配置

### 2.1 配置google-services.json文件

将下载的 `google-services.json` 文件放到 `nativeResources/android/` 目录下。

## 3. 代码集成

### 3.1 引入插件(必须)

- 只需在你的代码中引入插件即可
- 为了解决名字冲突，最好重命名init：init as 不冲突的名字

```typescript
import { 
  init as initFcm
} from "@/uni_modules/jg-jpush-u-fcm"
```

## 4. 注意事项

- 确保已在Firebase控制台配置FCM
- 确保已添加google-services.json文件
- 确保已配置FCM通知图标
- 该插件仅支持Android平台
- 需要配合jg-jpush-u主插件使用

## 5. 开发文档
[UTS 语法](https://uniapp.dcloud.net.cn/tutorial/syntax-uts.html)
[UTS API插件](https://uniapp.dcloud.net.cn/plugin/uts-plugin.html)
[UTS uni-app兼容模式组件](https://uniapp.dcloud.net.cn/plugin/uts-component.html)
[UTS 标准模式组件](https://doc.dcloud.net.cn/uni-app-x/plugin/uts-vue-component.html)
[Hello UTS](https://gitcode.net/dcloud/hello-uts)
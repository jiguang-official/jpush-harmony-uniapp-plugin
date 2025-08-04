# jg-jpush-u-huawei

## 1. 特别说明
这个插件是依附：jg-jpush-u 插件而存在，要使用这个插件就必须使用jg-jpush-u插件

## 2. 项目配置

### 2.1 配置agconnect-services.json文件

将下载的 `agconnect-services.json` 文件放到 `nativeResources/android/` 目录下。

### 2.2 配置签名证书

在华为开发者联盟后台添加应用的签名证书指纹。

## 3. 代码集成

### 3.1 引入插件(必须)

- 只需在你的代码中引入插件即可
- 为了解决名字冲突，最好重命名init：init as 不冲突的名字

```typescript
import { 
  init as initHuawei
} from "@/uni_modules/jg-jpush-u-huawei"
```

## 4. 注意事项

- 确保已在华为开发者联盟配置推送服务
- 确保已添加agconnect-services.json文件
- 确保已配置签名证书指纹
- 该插件仅支持Android平台
- 需要配合jg-jpush-u主插件使用

## 5. 开发文档
[UTS 语法](https://uniapp.dcloud.net.cn/tutorial/syntax-uts.html)
[UTS API插件](https://uniapp.dcloud.net.cn/plugin/uts-plugin.html)
[UTS uni-app兼容模式组件](https://uniapp.dcloud.net.cn/plugin/uts-component.html)
[UTS 标准模式组件](https://doc.dcloud.net.cn/uni-app-x/plugin/uts-vue-component.html)
[Hello UTS](https://gitcode.net/dcloud/hello-uts)
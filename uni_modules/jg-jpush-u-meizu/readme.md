# jg-jpush-u-meizu

## 1. 特别说明
这个插件是依附：jg-jpush-u 插件而存在，要使用这个插件就必须使用jg-jpush-u插件

## 2. 项目配置

### 2.1 配置manifestPlaceholders.json

在 `nativeResources/android/` 目录下创建或修改 `manifestPlaceholders.json` 文件：

```json
{
    "MEIZU_APPKEY": "您的应用对应的魅族推送配置",
    "MEIZU_APPID": "您的应用对应的魅族 APP ID"
}
```

**参数说明：**
- `MEIZU_APPKEY`: 魅族推送服务配置信息
- `MEIZU_APPID`: 魅族平台注册的APP ID

**示例配置：**
```json
{
  "MEIZU_APPKEY": "your-meizu-push-config",
  "MEIZU_APPID": "your-meizu-app-id"
}
```

## 3. 代码集成

### 3.1 引入插件(必须)

- 只需在你的代码中引入插件即可
- 为了解决名字冲突，最好重命名init：init as 不冲突的名字

```typescript
import { 
  init as initMeizu
} from "@/uni_modules/jg-jpush-u-meizu"
```

## 4. 注意事项

- 确保已在魅族开发者平台配置推送服务
- 确保已正确配置manifestPlaceholders.json文件
- 该插件仅支持Android平台
- 需要配合jg-jpush-u主插件使用

## 5. 开发文档
[UTS 语法](https://uniapp.dcloud.net.cn/tutorial/syntax-uts.html)
[UTS API插件](https://uniapp.dcloud.net.cn/plugin/uts-plugin.html)
[UTS uni-app兼容模式组件](https://uniapp.dcloud.net.cn/plugin/uts-component.html)
[UTS 标准模式组件](https://doc.dcloud.net.cn/uni-app-x/plugin/uts-vue-component.html)
[Hello UTS](https://gitcode.net/dcloud/hello-uts)
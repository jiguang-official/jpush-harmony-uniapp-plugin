# jg-jpush-u-xiaomi

## 1. 特别说明
这个插件是依附：jg-jpush-u 插件而存在，要使用这个插件就必须使用jg-jpush-u插件

## 2. 项目配置

### 2.1 配置manifestPlaceholders.json

在 `nativeResources/android/` 目录下创建或修改 `manifestPlaceholders.json` 文件：

```json
{
    "XIAOMI_APPKEY": "您的应用对应的小米的APPKEY",
    "XIAOMI_APPID": "您的应用对应的小米的APPID"
}
```

**参数说明：**
- `XIAOMI_APPKEY`: 小米平台注册的appkey
- `XIAOMI_APPID`: 小米平台注册的appid，

**示例配置：**
```json
{
  "XIAOMI_APPKEY": "1234567890abcdef",
  "XIAOMI_APPID": "9876543210fedcba"
}
```

## 3. 代码集成

### 3.1 引入插件(必须)

- 只需在你的代码中引入插件即可,
- 为了解决名字冲突，最好重命名init：init as 不冲突的名字

```typescript
import { 
  init as initXiaomi
} from "@/uni_modules/jg-jpush-u-xiaomi"
```

## 4. 注意事项

- 确保已在小米开发者平台注册应用并获取APPKEY和APPID
- 确保已正确配置manifestPlaceholders.json文件
- 该插件仅支持Android平台
- 需要配合jg-jpush-u主插件使用

## 5. 开发文档
[UTS 语法](https://uniapp.dcloud.net.cn/tutorial/syntax-uts.html)
[UTS API插件](https://uniapp.dcloud.net.cn/plugin/uts-plugin.html)
[UTS uni-app兼容模式组件](https://uniapp.dcloud.net.cn/plugin/uts-component.html)
[UTS 标准模式组件](https://doc.dcloud.net.cn/uni-app-x/plugin/uts-vue-component.html)
[Hello UTS](https://gitcode.net/dcloud/hello-uts)
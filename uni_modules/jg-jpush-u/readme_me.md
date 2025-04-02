# jg-jpush-u
### 开发文档
[UTS 语法](https://uniapp.dcloud.net.cn/tutorial/syntax-uts.html)
[UTS API插件](https://uniapp.dcloud.net.cn/plugin/uts-plugin.html)
[UTS uni-app兼容模式组件](https://uniapp.dcloud.net.cn/plugin/uts-component.html)
[UTS 标准模式组件](https://doc.dcloud.net.cn/uni-app-x/plugin/uts-vue-component.html)
[Hello UTS](https://gitcode.net/dcloud/hello-uts)

## 集成
## 生成原生代码
在目录 harmony-configs/entry/src/main/ets/entryability 中 生成JGPushAbilityStage.ets、PushMessageAbility.ets、RemoteNotificationExtAbility.ets
- 1、生成JGPushAbilityStage.ets文件，内容如下：
```javascript
import AbilityStage from '@ohos.app.ability.AbilityStage';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { bundleManager } from '@kit.AbilityKit';

import { setChannel, setAppKey, setDebug } from '@uni_modules/jg-jpush-u';

const TAG: string = 'JPUSH-JLog-JGPushAbilityStage'


export default class JGPushAbilityStage extends AbilityStage {
  onCreate() {
    // 应用的HAP在首次加载的时，为该Module初始化操作
    hilog.info(0x0000, TAG, '%{public}s', 'JGPushAbilityStage onCreate');

    let appKey = this.getMetadata("JG_APP_KEY");
    let debug = this.getMetadata("JG_DEBUG_MODE");
    let channel = this.getMetadata("JG_CHANNEL");
    if (undefined !== appKey) {
      setAppKey(appKey)
    }

    if (undefined !== debug) {
      if ("true" === debug) {
        setDebug(true)
      }
    }

    if (undefined !== channel) {
      setChannel(channel)
    }

  }

  getMetadata(name: string): string | undefined {
    try {
      // 获取当前应用的 BundleInfo
      let bundleInfo: bundleManager.BundleInfo =
        bundleManager.getBundleInfoForSelfSync(bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
        bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA);
      // console.log(`bundleInfo: ${bundleInfo}`);
      // console.log(`bundleInfo: ${JSON.stringify(bundleInfo)}`);
      let value: string | undefined = undefined
      bundleInfo.appInfo.metadataArray.forEach((metadataArray) => {
        metadataArray.metadata.forEach((metadata) => {
          if (name === metadata.name) {
            value = metadata.value;
            return
          }
        })
        if (undefined !== value) {
          return
        }
      })
      return value
    } catch (error) {
      console.error('Failed to get metadata:', error);
    }
    return undefined

  }
}

```
- 2、生成PushMessageAbility.ets文件，内容如下：
```javascript
import { UIAbility } from '@kit.AbilityKit';
import { customMessageBackgroundData,extraMessageBackgroundData,voIPMessageBackgroundData } from '@uni_modules/jg-jpush-u';
import { pushCommon, pushService } from '@kit.PushKit';
import { hilog } from '@kit.PerformanceAnalysisKit';

const TAG: string = 'JPUSH-JLog-PushMessageAbility'

export default class PushMessageAbility extends UIAbility {
  onCreate(): void {
    try { // receiveMessage中的参数固定为BACKGROUND-------后台自定义信息接收
      pushService.receiveMessage('BACKGROUND', this, async (data: pushCommon.PushPayload) => {
        let jg = await customMessageBackgroundData(data)
        if (jg) { //如果是true为已经处理
          return
        }
      });
    } catch (e) {
      hilog.info(0x0000, TAG, '%{public}s', 'BACKGROUND fail:' + JSON.stringify(e));
    }

    try { // receiveMessage中的参数固定为IM-------拓展通知接收
      pushService.receiveMessage('IM', this, async (data) => {
        let jg = await extraMessageBackgroundData(data)
        if (jg) { //如果是true为已经处理
          return
        }
      });
    } catch (e) {
      hilog.info(0x0000, TAG, '%{public}s', 'IM fail:' + JSON.stringify(e));
    }


    try {
      pushService.receiveMessage('VoIP', this, async (data) => {
        let jg = await voIPMessageBackgroundData(data)
        if (jg) { //如果是true为已经处理
          return
        }
      });
    } catch (e) {
      hilog.info(0x0000, TAG, '%{public}s', 'VoIP fail:' + JSON.stringify(e));
    }
  }
}
```
- 3、生成RemoteNotificationExtAbility.ets文件，内容如下：
```javascript
import { pushCommon, RemoteNotificationExtensionAbility } from '@kit.PushKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { receiveExtraDataMessage } from '@uni_modules/jg-jpush-u';

const TAG: string = 'JPUSH-JLog-RemoteNotificationExtAbility'

export default class RemoteNotificationExtAbility extends RemoteNotificationExtensionAbility {
  async onReceiveMessage(remoteNotificationInfo: pushCommon.RemoteNotificationInfo): Promise<pushCommon.RemoteNotificationContent> {
    hilog.info(0x0000, TAG, 'onReceiveMessage, remoteNotificationInfo: %{public}s',
      JSON.stringify(remoteNotificationInfo));

    let jMessageExtra = await receiveExtraDataMessage(this, remoteNotificationInfo);
    hilog.info(0x0000, TAG, 'onReceiveMessage jMessageExtra:' + JSON.stringify(jMessageExtra));
    // Return the replaced message content.
    return {} //如果要修改通知可以反回有数据通知
  }

  onDestroy(): void {
    hilog.info(0x0000, TAG, 'RemoteNotificationExtAbility onDestroy.');
  }
}

```

## 配置module.json5

在目录 harmony-configs/entry/src/main/module.json5 中 
- 1、找到或添加metadata，配置极光appKey
- - JG_APP_KEY:您的极光appKey
- - JG_DEBUG_MODE:true为打印debug级 log
- - JG_CHANNEL:渠道名称
- - JG_CUSTOM_MESSAGE_MAX_CACHE_COUNT:自定义信息缓存条数
- - ```json5 
    "metadata": [ 
      {
        "name": "JG_APP_KEY",
        "value": "您的极光appKey"
      },
      {
        "name": "JG_DEBUG_MODE",
        "value": "false"
      },
      {
        "name": "JG_CHANNEL",
        "value": "channel"
      },
      {
        "name": "JG_CUSTOM_MESSAGE_MAX_CACHE_COUNT",
        "value": "10"
      }
      ]
	```
- 2、配置自定义通知，需填您的包名
- - ```json5 
    "proxyData":[{
      "uri": "datashareproxy://您的包名/PushMessage",
      "requiredWritePermission": "ohos.permission.WRITE_PRIVACY_PUSH_DATA",
      "metadata":{
        "name": "dataProperties",
        "resource": "$profile:PushMessage"
      }
    }]
	```
- 3、再配置上上面生成的ability


```json5
{
  "module": {
    "name": "entry",
    "type": "entry",
    "srcEntry": "./ets/entryability/JGPushAbilityStage.ets",
    "description": "$string:module_desc",
    "mainElement": "EntryAbility",
    "deviceTypes": [
      "phone",
      "tablet",
      "2in1"
    ],
    "deliveryWithInstall": true,
    "installationFree": false,
    "pages": "$profile:main_pages",
    "abilities": [
      {
        "name": "EntryAbility",
        "srcEntry": "./ets/entryability/EntryAbility.ets",
        "description": "$string:EntryAbility_desc",
        "icon": "$media:layered_image",
        "label": "$string:EntryAbility_label",
        "startWindowIcon": "$media:startIcon",
        "startWindowBackground": "$color:start_window_background",
        "exported": true,
        "skills": [
          {
            "entities": [
              "entity.system.home"
            ],
            "actions": [
              "action.system.home"
            ]
          }
        ]
      },
      {
        "name": "PushMessageAbility",
        "srcEntry": "./ets/entryability/PushMessageAbility.ets",
        "launchType": "singleton",
        "startWindowIcon": "$media:layered_image",
        "startWindowBackground": "$color:start_window_background",
        "skills": [
          {
            "actions": [
              "action.ohos.push.listener"
            ]
          }
        ]
      }
    ],
    "extensionAbilities": [
      {
        "name": "RemoteNotificationExtAbility",
        "type": "remoteNotification",
        "srcEntry": "./ets/entryability/RemoteNotificationExtAbility.ets",
        "description": "RemoteNotificationExtAbility test",
        "exported": false,
        "skills": [
          {
            "actions": ["action.hms.push.extension.remotenotification"]
          }
        ]
      }
    ],
    "proxyData":[{
      "uri": "datashareproxy://你的包名/PushMessage",
      "requiredWritePermission": "ohos.permission.WRITE_PRIVACY_PUSH_DATA",
      "metadata":{
        "name": "dataProperties",
        "resource": "$profile:PushMessage"
      }
    }],
    "requestPermissions": [
      {
        "name": "ohos.permission.INTERNET"
      }
    ],
	"metadata": [ 
      {
        "name": "JG_APP_KEY",
        "value": "你的极光appKey"
      },
      {
        "name": "JG_DEBUG_MODE",
        "value": "false"
      },
      {
        "name": "JG_CHANNEL",
        "value": "channel"
      },
      {
        "name": "JG_CUSTOM_MESSAGE_MAX_CACHE_COUNT",
        "value": "10"
      }
      ]
  }
}
```

## 配置profile

在目录 harmony-configs/entry/src/main/resources/base/profile/ 中 生成PushMessage.json

```json5
{
  "path": "pushmessage/t_push_message",
  "type": "rdb",
  "scope": "application"
}
```

[API](./api.md)
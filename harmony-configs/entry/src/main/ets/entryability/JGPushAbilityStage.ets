import AbilityStage from '@ohos.app.ability.AbilityStage';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { bundleManager } from '@kit.AbilityKit';

import { setChannel, setAppKey, setDebug,setCustomMessageMaxCacheCount } from '@uni_modules/jg-jpush-u';

const TAG: string = 'JPUSH-JLog-JGPushAbilityStage'


export default class JGPushAbilityStage extends AbilityStage {
  onCreate() {
    // 应用的HAP在首次加载的时，为该Module初始化操作
    hilog.info(0x0000, TAG, '%{public}s', 'JGPushAbilityStage onCreate');

    let appKey = this.getMetadata("JG_APP_KEY");
    let debug = this.getMetadata("JG_DEBUG_MODE");
    let channel = this.getMetadata("JG_CHANNEL");
	let customMessageMaxCacheCount = this.getMetadata("JG_CUSTOM_MESSAGE_MAX_CACHE_COUNT");
	    
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
	
	if (undefined !== customMessageMaxCacheCount) {
	   setCustomMessageMaxCacheCount(Number.parseInt(customMessageMaxCacheCount))
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

# API


## 使用

在需要使用的地方使用以下代码劫持掉uni原先的命令


```javascript
// #ifdef APP-HARMONY
import {
	init,
	getRegistrationId,
	setEventCallBack,
	EventCallBackParams,
	EventCallBack,
	addTags,
	getTags,
	setAlias,
	deleteAlias,
	getAlias,
	等其他方法
} from "@/uni_modules/jg-jpush-u"

// #endif

```



## 设置调试模式 API（setDebug）

### 功能说明

> * 请在 在目录 harmony-configs/entry/src/main/module.json5 中配置
- ```json5 
    "metadata": [ 
      {
        "name": "JG_DEBUG_MODE",
        "value": "true"
      }
      ]
	```
> * 可选接口

### 接口定义

```ts
    /**
     * debug log 设置，默认false
     *
     * @param debug true 为 debug，false 为非 debug
     */
    setDebug(debug: boolean)
```

### 代码示例

```json5
    "metadata": [
      {
        "name": "JG_DEBUG_MODE",
        "value": "true"
      }
      ]
```

### 参数说明

- JG_DEBUG_MODE 为 true 则会打印 debug 级别的日志，false 则只会打印 warning 级别以上的日志



## 配置极光 Appkey（setAppKey）

### 功能说明

> * 请在 在目录 harmony-configs/entry/src/main/module.json5 中配置
- ```json5 
    "metadata": [ 
        "name": "JG_APP_KEY",
        "value": "您的极光appKey"
      ]
	```
> * 必须调用的接口

### 接口定义

```ts
    /**
     * 设置appkey
     *
     * @param appKey 为平台的appkey
     */
    setAppKey(appKey: string)
```

### 代码示例

```json5
	"metadata": [ 
        "name": "JG_APP_KEY",
        "value": "您的极光appKey"
      ]
```

### 参数说明

- appKey 需要从极光控制台获取。

## 配置下载渠道（setChannel）

### 功能说明
动态配置 channel（程序包下载渠道）
- channel 指明应用程序包的下载渠道，为方便分渠道统计，具体值由你自行定义，如华为应用市场等。

> * 请在 在目录 harmony-configs/entry/src/main/module.json5 中配置
- ```json5 
    "metadata": [ 
        "name": "JG_CHANNEL",
        "value": "您的CHANNEL"
      ]
	```

### 接口定义

```
    /**
     * 配置渠道
     *
     * @param channel 渠道名称
     */
    setChannel(channel: string)
```

### 代码示例

```json5 
    "metadata": [ 
        "name": "JG_CHANNEL",
        "value": "您的CHANNEL"
      ]
	```

### 参数说明

- channel 用户业务自定义。

## 配置自定义信息缓存条数（setCustomMessageMaxCacheCount）

### 功能说明
此接口用于推送极光自定义消息（不适用于通知消息），针对部分 APP 特殊业务场景；如：当您服务端发送了100条自定义消息给到某个用户时，基于业务特性或者您自身业务处理性能考虑，您仅仅希望处理和保存最新的10条，则可以使用此接口。

> * 请在 在目录 harmony-configs/entry/src/main/module.json5 中配置
- ```json5 
    "metadata": [ 
        "name": "JG_CUSTOM_MESSAGE_MAX_CACHE_COUNT",
        "value": "10"
      ]
	```

### 接口定义

```
    /**
     * 配置自定义后台信息缓存条数
     *
     * @param maxCacheCount 缓存条数
     */
    setCustomMessageMaxCacheCount(maxCacheCount: number)
```

### 代码示例

```json5 
    "metadata": [ 
        "name": "JG_CUSTOM_MESSAGE_MAX_CACHE_COUNT",
        "value": "10"
      ]
	```

### 参数说明

- JG_CUSTOM_MESSAGE_MAX_CACHE_COUNT 缓存条数

## 开启推送业务功能 API（init）

### 功能说明
极光推送服务，调用了本 API 后，开启JPush 推送服务，将会开始收集上报SDK业务功能所必要的用户个人信息。

> * 启动时调用

### 接口定义
```ts
   /**
   * 开启推送业务功能
   * @param context 上下文
   */
    init(context: common.UIAbilityContext | common.AbilityStageContext | undefined)
```

### 代码示例

```ts
init()
```

### 参数说明

* context undefined

### 接口使用说明

- 开发者如果主动调用了 init 方法，会开启JPush推送服务。
- 考虑 APP 上线合规，开发者必须在APP用户同意了隐私政策，并且开发者确定为App用户开始提供推送服务后，再调用启用推送业务功能接口使用极光服务。
- 关于 APP 隐私政策建议和说明，具体可以参考 [如何草拟合规的隐私政策](/compliance_guide/app_compliance_guide/app_compliance_guide1)。


## 获取 RegistrationID（getRegistrationId）

### 功能说明

> * 请先[init](#init)，否则调用无效

### 接口定义
```ts
    /**
     * 反回注册的rid
     *
     */
    getRegistrationId(): string
```

### 代码示例

```
let rid = getRegistrationId()
```

### 参数说明

- 无


## 设置回调接口（setEventCallBack）

### 功能说明
这个接口是用来接收sdk数据的。如：注册结果，登陆结果，通知点击结果，设置标签别名操作结果等的回调。
接收类需要实现EventCallBackParams接口，EventCallBackParams功能可看代码例子。

> * 请在 [init](#init) 之前调用
> * 必须调用的接口

### 接口定义

```ts
    /**
     * 监听回调事件和数据
     *
     * @param callBackMsg 
     */
    setEventCallBack(callBackMsg: EventCallBackParams)
```

### 代码示例

```ts
setEventCallBack({
	callback: (eventCallBack:EventCallBack) => {
		console.log("JPUSH-", 'push vue callback eventName:' + eventCallBack.eventName);
		console.log("JPUSH-", 'push vue callback eventData:' + eventCallBack.eventData);
	}
})
```

### 参数说明

- callBackMsg: EventCallBackParams的实现


### 回调数据明细
```ts
export type EventCallBack = {
	eventName: string,
	eventData: string
}
```
| eventName     | eventData | 说明       |
|----------|------|------------|
| onRegister     | string   | 注册结果回调: rid    |
| onConnected     | string   | 长连接状态回调:boolean字符串，"true"为成功；"false"为失败     |
| onClickMessage     | string   | 通知点击事件回调：json字符串 |
| onCommandResult     | string   | 交互事件回调：json字符串 |
| onCustomMessage     | string   | 自定义信息通知回调：json字符串 |
| onJMessageExtra     | string   | 通知扩展消息回调：json字符串 |
| onJMessageVoIP     | string   | VoIP呼叫消息回调：json字符串 |
| onTagOperatorResult     | string   | 操作 tag 接口回调：json字符串 |
| onAliasOperatorResult     | string   | 操作 Alias 接口回调：json字符串 |
| onMobileNumberOperatorResult     | string   | 设置 手机号 接口回调：json字符串 |

#### 通知点击事件回调（onClickMessage）

##### json字符串定义

```ts
    /**
     * 通知点击事件回调
       {
       msgId: string //通知id
       title: string //通知标题
       content: string //通知内容
       extras: Map<string, Object> //自定义数据
       }
     */		
```

#### 交互事件回调（onCommandResult）

##### json字符串定义

```
  /**
   * 交互事件回调
   * {
   * public static CMD_PUSH_STOP = 2007 //通知停止 设置回调
   * public static CMD_PUSH_RESUME = 2006 //	通知恢复 设置回调
   *
   * cmd: number  //操作事件，2007通知停止，2006恢复通知
   * errorCode: number //0表示成功，其他为错误
   * msg: string //内容信息
   * extra: Map<string, Object>//自定义数据
   * }
   */
```

<div class="table-d" align="center" >
    <table border="1" width = "100%">
        <tr  bgcolor="#D3D3D3" >
            <th >cmd</th>
            <th >errorCode</th>
            <th>msg</th>
            <th>DESCRIPTION</th>
        </tr>
        <tr >
            <th >0</th>
            <th >失败 code</th>
            <th>失败信息</th>
            <th>注册失败</th>
        </tr>
        <tr >
            <th >2006</th>
            <th >0</th>
            <th>success</th>
            <th>onResume 设置回调</th>
        </tr>
        <tr >
            <th >2007</th>
            <th >0</th>
            <th>success</th>
            <th>onStop 设置回调</th>
        </tr>
    </table>
</div>

#### 后台自定义信息回调（onCustomMessage）

##### json字符串定义

```
  /**
   * 自定义信息通知回调
   *  回调一：冷启动调用sdk初始化后回调之前还没有回调的信息
   *  回调二：app存活时会直接回调信息
   *  想要有自定义信息回调，还需查看集成指南的自定义信息集成配置方式
   *
   *  {
   *  msgId: string //通知id
   *  title: string //通知标题
   *  content: string //通知内容
   *  contentType: string //通知内容类型
   *  extras: Record<string, Object> //通知自定义键值对
   *  ttl: number //后台下发的信息过期时间，单位秒
   *  stime: number //后台下发时间，毫秒
   * }
   */
```

#### 通知扩展消息回调（onJMessageExtra）

##### json字符串定义

```
  /**
   * 通知扩展消息回调
   *
   * {
   * msgId: string //通知id
   * title: string //通知标题
   * content: string//通知内容
   * extras: Record<string, Object>//自定义数据
   * extraData: string//通知扩展消息的自定义数据
   * }
   */
```

#### VoIP呼叫消息回调（onJMessageVoIP）

##### json字符串定义

```
   /**
   * VoIP呼叫消息回调
   * {
   * msgId: string //通知id
   * extraData: string //VoIP自定义数据
   }
   */
```

#### 操作 tag 接口回调（onTagOperatorResult）

##### json字符串定义

```ts
   /**
    * 操作 tag 接口回调
      {
      sequence: number //对应操作id，全局不要重复
      code: number //0成功，JTagMessage.CODE_TIME_OUT超时
      op: string
      tags: string[] //对应数据
      curr: number //数据当前页数，页数从1开始
      total: number //数据总页数
      msg: string
      }
    *
   */
```
#### 设置 mobileNumber 接口回调（onMobileNumberOperatorResult）

##### json字符串定义

```ts
   /**
    * 设置 mobileNumber 接口回调
      {
      sequence: number //对应操作id，全局不要重复
      code: number //0成功
      }
    *
   */
```

#### 操作 Alias 接口回调（onAliasOperatorResult）

##### json字符串定义

```ts
  /**
   * 操作 Alias 接口回调
     {
      sequence: number //对应操作id，全局不要重复
      code: number //0成功，JAliasMessage.CODE_TIME_OUT超时
      op: string
      alias: string //对应数据
      curr: number
      total: number
      msg: string
     }
   *
   */
```


## 停止通知（stopPush）

### 功能说明

> * 请先[init](#init)，否则调用无效
> * 结果在回调事件"onCommandResult"回调

### 接口定义

```
    /**
     * 停止通知
     *
     */
    stopPush()
```

### 代码示例

```
stopPush()
```

### 参数说明

- 无

## 恢复通知（resumePush）

### 功能说明

> * 请先[init](#init)，否则调用无效
> * 结果在回调事件"onCommandResult"回调

### 接口定义

```
    /**
     * 恢复通知
     *
     */
    resumePush()
```

### 代码示例

```
resumePush()
```

### 参数说明

- 无

## 通知状态查询（isPushStopped）

### 功能说明

> * 请先[init](#init)，否则调用无效

### 接口定义

```
    /**
     * 通知状态查询
     *
     */
    isPushStopped(): boolean | undefined
```

### 代码示例

```
let isPushStopped = isPushStopped()
```

### 参数说明

- 反回值：true停止，false正常，undefined没有初始化等异常情况

## 推送状态查询（getPushStatus）

### 功能说明

> * 请先[init](#init)，否则调用无效
> * iOS 6.0.0+ 通过回调返回

### 接口定义

- **Android**：`getPushStatus(): 返回值（具体类型见原生文档）`
- **iOS**：`getPushStatus(callback: (code: number, isStopped: boolean) => void): void`  
  - code 为 0 表示成功，isStopped 为 true 表示推送已停止
  - code 为 0 时， 表示成功，isStopped的值才有效

### 代码示例

```ts

// iOS
getPushStatus((code, isStopped) => {
  console.log('code:', code, 'isStopped:', isStopped)
})
```

### 参数说明

- iOS callback：code 结果码（0 表示成功），isStopped 是否已停止推送

## 标签与别名-api

### 新增标签（addTags）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onTagOperatorResult"会回调结果

#### 接口定义

```ts
    /**
     * 增加指定tag，累加逻辑，之前设置的标签依然存在
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     * @param tags     标签数组，每个tag命名长度限制为40字节，最多支持设置1000个tag，且单次操作总长度不得超过5000字节
     */
    addTags(sequence: number, tags: string[])
```

#### 代码示例

```ts
addTags(this.sequence++, ["ccc", "ddddd"])
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性。
- tags
  - 每次调用至少新增一个 tag。
  - 有效的标签组成：字母（区分大小写）、数字、下划线、汉字、特殊字符 @!#$&*+=.|。
  - 限制：每个 tag 命名长度限制为 40 字节，最多支持设置 1000 个 tag，且单次操作总长度不得超过 5000 字节。（判断长度需采用 UTF-8 编码）
单个设备最多支持设置 1000 个 tag。App 全局 tag 数量无限制。


### 删除标签（deleteTags）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onTagOperatorResult"会回调结果

#### 接口定义

```ts
    /**
     * 删除指定tag，删除逻辑，会删除指定的标签
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     * @param tags     标签数组，每个tag命名长度限制为40字节，最多支持设置1000个tag，且单次操作总长度不得超过5000字节
     */
    deleteTags(sequence: number, tags: string[])
```

#### 代码示例
```ts
  deleteTags(this.sequence++, ["ccc"])
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性。
- tags
  - 每次调用至少删除一个 tag。
  - 有效的标签组成：字母（区分大小写）、数字、下划线、汉字、特殊字符 @!#$&*+=.|。
  - 限制：每个 tag 命名长度限制为 40 字节，最多支持设置 1000 个 tag，且单次操作总长度不得超过 5000 字节。（判断长度需采用 UTF-8 编码）
单个设备最多支持设置 1000 个 tag。App 全局 tag 数量无限制。



### 设置标签（setTags）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onTagOperatorResult"会回调结果

#### 接口定义

```ts
    /**
     * 更新指定tag，覆盖逻辑，之前添加的tag会清空
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     * @param tags     标签数组，每个tag命名长度限制为40字节，最多支持设置1000个tag，且单次操作总长度不得超过5000字节
     */
    setTags(sequence: number, tags: string[])
```

#### 代码示例
```ts
setTags(this.sequence++, ["xxx", "yyy"])
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性。
- tags
  - 每次调用至少新增一个 tag。
  - 有效的标签组成：字母（区分大小写）、数字、下划线、汉字、特殊字符 @!#$&*+=.|。
  - 限制：每个 tag 命名长度限制为 40 字节，最多支持设置 1000 个 tag，且单次操作总长度不得超过 5000 字节。（判断长度需采用 UTF-8 编码）
单个设备最多支持设置 1000 个 tag。App 全局 tag 数量无限制。




### 查询指定标签的绑定状态（checkTagBindState）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onTagOperatorResult"会回调结果

#### 接口定义

```ts
    /**
     * 查询指定tag
     * 
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     * @param tag      标签，每个tag命名长度限制为40字节
     */
    checkTagBindState(sequence: number, tag: string) 
```

#### 代码示例

```ts
 checkTagBindState(this.sequence++, "ccc")
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性。
- tags
  - 被查询的 tag


### 清除所有标签（cleanTags）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onTagOperatorResult"会回调结果

#### 接口定义

```ts
    /**
     * 删除所有tag，清空逻辑，会删除所有的标签
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     */
    cleanTags(sequence: number)
```

#### 代码示例

```ts
cleanTags(this.sequence++)
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性。


### 查询所有标签（getTags）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onTagOperatorResult"会回调结果

#### 接口定义

```ts
    /**
     * 查询所有tag，获取逻辑，会获取所有标签
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     * @param curr  获取当前的页数，开始页数值为1
     */
    getTags(sequence: number, curr: number)
```

#### 代码示例

```ts
getTags(this.sequence++, 1)
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性。



### 设置别名（setAlias）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onAliasOperatorResult"会回调结果

#### 接口定义

```ts
    /**
     * 设置alias
     * 
     * 同一个应用程序内，对不同的用户，建议取不同的别名。这样，尽可能根据别名来唯一确定用户
     * 
     * 不限定一个别名只能指定一个用户
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     * @param alias    有效的别名组成：字母（区分大小写）、数字、下划线、汉字、特殊字符@!#$&*+=.|。限制：alias命名长度限制为 40 字节（判断长度需采用 UTF-8 编码）
     *                             
     */
    setAlias(sequence: number, alias: string)
```

#### 代码示例

```ts
 setAlias(this.sequence++, "gggdd")
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性，推荐每次都用不同的数字序号。
- alias
  - 每次调用设置有效的别名，覆盖之前的设置。
  - 有效的别名组成：字母（区分大小写）、数字、下划线、汉字、特殊字符 @!#$&*+=.|。
  - 限制：alias 命名长度限制为 40 字节。（判断长度需采用 UTF-8 编码）



### 查询别名（getAlias）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onAliasOperatorResult"会回调结果

#### 接口定义

```ts
    /**
     * 获取alias
     * 
     * 同一个应用程序内，对不同的用户，建议取不同的别名。这样，尽可能根据别名来唯一确定用户
     * 
     * 不限定一个别名只能指定一个用户
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     */
    getAlias(sequence: number)
```

#### 代码示例

```ts
getAlias(this.sequence++)
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性，推荐每次都用不同的数字序号。



### 删除别名（deleteAlias）

#### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onAliasOperatorResult"会回调结果
    
#### 接口定义

```ts
    /**
     * 清除alias
     *
     * 同一个应用程序内，对不同的用户，建议取不同的别名。这样，尽可能根据别名来唯一确定用户
     * 
     * 不限定一个别名只能指定一个用户
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性
     */
    deleteAlias(sequence: number)
```

#### 代码示例

```ts
deleteAlias(this.sequence++)
```

#### 参数说明

- sequence
  - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性，推荐每次都用不同的数字序号。

## 设置手机号（setMobileNumber）

### 功能说明

> * 请先[init](#init)，否则调用无效
> * 如果环境没有问题，回调事件"onMobileNumberOperatorResult"会回调结果
    

### 接口定义

```
    /**
     * 设置手机号
     *
     * @param sequence 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性，推荐每次都用不同的数字序号。
     * @param mobileNumber 手机号
     */
    setMobileNumber(sequence: number, mobileNumber: string)
```

### 代码示例

```
  setMobileNumber(this.sequence++,"155xxxxxxxx)
```

### 参数说明

- sequence
    - 用户自定义的操作序列号，同操作结果一起返回，用来标识一次操作的唯一性，推荐每次都用不同的数字序号。
- mobileNumber
    - 手机号
## 设置角标（setBadgeNumber）

### 功能说明

> * 请先[init](#init)，否则调用无效

### 接口定义

```
    /**
     * 设置角标
     *
     * @param badgeNumber 角标值
     */
    setBadgeNumber(badgeNumber: number)
```

### 代码示例

```
  setBadgeNumber(0)
```

### 参数说明

- badgeNumber
    - 角标值

  

# 扩展业务相关设置
## wifi列表采集开关（setListWifi）

### 功能说明

> * 请先[setAppKey](#setAppKey)，否则调用无效

### 接口定义

```
    /**
     * @param enable 默认为true，false-不允许采集
     *
     */
    setListWifi(enable: boolean)
```

### 代码示例

```
setListWifi(false)
```

### 参数说明

- enable
  -  默认为true，false-不允许采集
## GPS采集开关（setGPS）

### 功能说明

> * 请先[setAppKey](#setAppKey)，否则调用无效

### 接口定义

```
    /**
     * @param enable 默认为true，false-不允许采集
     *
     */
    setGPS(enable: boolean)
```

### 代码示例

```
setGPS(false)
```

### 参数说明

- enable
  -  默认为true，false-不允许采集
## 应用活跃时长统计开关（setEnableAppTerminate）

### 功能说明

> * 请先[setAppKey](#setAppKey)，否则调用无效

### 接口定义

```
    /**
     * @param enable 默认为true，false-不允许统计
     *
     */
    setEnableAppTerminate( enable: boolean)
```

### 代码示例

```
setEnableAppTerminate( false)
```

### 参数说明

- enable
  -  默认为true，false-不允许统计
/*
 *	| |    | |  \ \  / /  | |    | |   / _______|
 *	| |____| |   \ \/ /   | |____| |  / /
 *	| |____| |    \  /    | |____| |  | |   _____
 * 	| |    | |    /  \    | |    | |  | |  |____ |
 *  | |    | |   / /\ \   | |    | |  \ \______| |
 *  | |    | |  /_/  \_\  | |    | |   \_________|
 *
 * Copyright (c) 2011 ~ 2017 Shenzhen HXHG. All rights reserved.
 */

#define JPUSH_VERSION_NUMBER 5.7.0

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CLRegion;
@class UILocalNotification;
@class CLLocation;
@class UNNotificationCategory;
@class UNNotificationSettings;
@class UNNotificationRequest;
@class UNNotification;
@class UIView;
@protocol JPUSHRegisterDelegate;
@protocol JPUSHGeofenceDelegate;
@protocol JPUSHNotiInMessageDelegate;
@protocol JPUSHInAppMessageDelegate;

typedef void (^JPUSHTagsOperationCompletion)(NSInteger iResCode, NSSet *_Nullable iTags, NSInteger seq);
typedef void (^JPUSHTagValidOperationCompletion)(NSInteger iResCode, NSSet *_Nullable iTags, NSInteger seq, BOOL isBind);
typedef void (^JPUSHAliasOperationCompletion)(NSInteger iResCode, NSString *_Nullable iAlias, NSInteger seq);
typedef void (^JPUSHPropertiesOperationCompletion)(NSInteger iResCode, NSDictionary *_Nullable properties, NSInteger seq);
typedef void (^JPUSHLiveActivityTokenCompletion)(NSInteger iResCode, NSString *_Nullable iLiveActivityId, NSData *  _Nullable pushToken, NSInteger seq);

extern NSString *const kJPFNetworkIsConnectingNotification; // 正在连接中
extern NSString *const kJPFNetworkDidSetupNotification;     // 建立连接
extern NSString *const kJPFNetworkDidCloseNotification;     // 关闭连接
extern NSString *const kJPFNetworkDidRegisterNotification;  // 注册成功
extern NSString *const kJPFNetworkFailedRegisterNotification; //注册失败
extern NSString *const kJPFNetworkDidLoginNotification;     // 登录成功
extern NSString *const kJPFNetworkDidReceiveMessageNotification;         // 收到消息(非APNS)
extern NSString *const kJPFServiceErrorNotification;  // 错误提示

typedef NS_OPTIONS(NSUInteger, JPAuthorizationOptions) {
    JPAuthorizationOptionNone    = 0,   // the application may not present any UI upon a notification being received
    JPAuthorizationOptionBadge   = (1 << 0),    // the application may badge its icon upon a notification being received
    JPAuthorizationOptionSound   = (1 << 1),    // the application may play a sound upon a notification being received
    JPAuthorizationOptionAlert   = (1 << 2),    // the application may display an alert upon a notification being received
    JPAuthorizationOptionCarPlay = (1 << 3),    // The ability to display notifications in a CarPlay environment.
    JPAuthorizationOptionCriticalAlert NS_AVAILABLE_IOS(12.0) = (1 << 4) ,   //The ability to play sounds for critical alerts.
    JPAuthorizationOptionProvidesAppNotificationSettings NS_AVAILABLE_IOS(12.0) = (1 << 5) ,      //An option indicating the system should display a button for in-app notification settings.
    JPAuthorizationOptionProvisional NS_AVAILABLE_IOS(12.0) = (1 << 6) ,     //The ability to post noninterrupting notifications provisionally to the Notification Center.
    JPAuthorizationOptionAnnouncement NS_AVAILABLE_IOS(13.0) = (1 << 7) , //The ability for Siri to automatically read out messages over AirPods.
};

typedef NS_ENUM(NSUInteger, JPAuthorizationStatus) {
    JPAuthorizationNotDetermined    = 0,   // The user has not yet made a choice regarding whether the application may post user notifications.
    JPAuthorizationStatusDenied,    // The application is not authorized to post user notifications.
    JPAuthorizationStatusAuthorized,    // The application is authorized to post user notifications.
    JPAuthorizationStatusProvisional NS_AVAILABLE_IOS(12.0),    // The application is authorized to post non-interruptive user notifications.
};

/*!
 * 通知注册实体类
 */
@interface JPUSHRegisterEntity : NSObject

/*!
 * 支持的类型
 * badge,sound,alert
 */
@property (nonatomic, assign) NSInteger types;
/*!
 * 注入的类别
 * iOS10 UNNotificationCategory
 * iOS8-iOS9 UIUserNotificationCategory
 */
@property (nonatomic, strong, nullable) NSSet *categories;
@end

/*!
 * 进行删除、查找推送实体类
 */
@interface JPushNotificationIdentifier : NSObject<NSCopying, NSCoding>

@property (nonatomic, copy, nullable) NSArray<NSString *> * identifiers; // 推送的标识数组
@property (nonatomic, copy, nullable) UILocalNotification * notificationObj NS_DEPRECATED_IOS(4_0, 10_0);  // iOS10以下可以传UILocalNotification对象数据，iOS10以上无效
@property (nonatomic, assign) BOOL delivered NS_AVAILABLE_IOS(10_0); // 在通知中心显示的或待推送的标志，默认为NO，YES表示在通知中心显示的，NO表示待推送的
@property (nonatomic, copy, nullable) void (^findCompletionHandler)(NSArray * _Nullable results); // 用于查询回调，调用[findNotification:]方法前必须设置，results为返回相应对象数组，iOS10以下返回UILocalNotification对象数组；iOS10以上根据delivered传入值返回UNNotification或UNNotificationRequest对象数组（delivered传入YES，则返回UNNotification对象数组，否则返回UNNotificationRequest对象数组）

@end

/*!
 * 推送通知声音实体类
 * iOS10以上有效
 */
@interface JPushNotificationSound : NSObject <NSCopying, NSCoding>
@property (nonatomic, copy, nullable) NSString *soundName; //普通通知铃声
@property (nonatomic, copy, nullable) NSString *criticalSoundName NS_AVAILABLE_IOS(12.0); //警告通知铃声
@property (nonatomic, assign) float criticalSoundVolume NS_AVAILABLE_IOS(12.0); //警告通知铃声音量，有效值在0~1之间，默认为1
@end


/*!
 * 推送内容实体类
 */
@interface JPushNotificationContent : NSObject<NSCopying, NSCoding>

@property (nonatomic, copy) NSString *title;                // 推送标题
@property (nonatomic, copy) NSString *subtitle;             // 推送副标题
@property (nonatomic, copy) NSString *body;                 // 推送内容
@property (nonatomic, copy, nullable) NSNumber *badge;                // 角标的数字。如果不需要改变角标传@(-1)
@property (nonatomic, copy) NSString *action NS_DEPRECATED_IOS(8_0, 10_0); // 弹框的按钮显示的内容（IOS 8默认为"打开", 其他默认为"启动",iOS10以上无效）
@property (nonatomic, copy) NSString *categoryIdentifier;   // 行为分类标识
@property (nonatomic, copy) NSDictionary *userInfo;         // 本地推送时可以设置userInfo来增加附加信息，远程推送时设置的payload推送内容作为此userInfo
@property (nonatomic, copy, nullable) NSString *sound;                // 声音名称，不设置则为默认声音
@property (nonatomic, copy, nullable) JPushNotificationSound *soundSetting NS_AVAILABLE_IOS(10.0);   //推送声音实体
@property (nonatomic, copy) NSArray *attachments NS_AVAILABLE_IOS(10_0);                 // 附件，iOS10以上有效，需要传入UNNotificationAttachment对象数组类型
@property (nonatomic, copy) NSString *threadIdentifier NS_AVAILABLE_IOS(10_0); // 线程或与推送请求相关对话的标识，iOS10以上有效，可用来对推送进行分组
@property (nonatomic, copy) NSString *launchImageName NS_AVAILABLE_IOS(10_0);  // 启动图片名，iOS10以上有效，从推送启动时将会用到
@property (nonatomic, copy) NSString *summaryArgument NS_AVAILABLE_IOS(12.0);  //插入到通知摘要中的部分参数。iOS12以上有效。
@property (nonatomic, assign) NSUInteger summaryArgumentCount NS_AVAILABLE_IOS(12.0); //插入到通知摘要中的项目数。iOS12以上有效。
@property (nonatomic, copy, nullable) NSString *targetContentIdentifier NS_AVAILABLE_IOS(13.0);  // An identifier for the content of the notification used by the system to customize the scene to be activated when tapping on a notification.
//iOS15以上的新增属性 interruptionLevel为枚举UNNotificationInterruptionLevel
// The interruption level determines the degree of interruption associated with the notification
@property (nonatomic, assign) NSUInteger interruptionLevel NS_AVAILABLE_IOS(15.0);
// Relevance score determines the sorting for the notification across app notifications. The expected range is between 0.0f and 1.0f.
@property (nonatomic, assign) double relevanceScore NS_AVAILABLE_IOS(15.0);
// iOS16以上的新增属性
@property (nonatomic, copy, nullable) NSString * filterCriteria NS_AVAILABLE_IOS(16.0); // default nil

@end


/*!
 * 推送触发方式实体类
 * 注：dateComponents、timeInterval、region在iOS10以上可选择其中一个参数传入有效值，如果同时传入值会根据优先级I、II、III使其中一种触发方式生效，fireDate为iOS10以下根据时间触发时须传入的参数
 */
@interface JPushNotificationTrigger : NSObject<NSCopying, NSCoding>

@property (nonatomic, assign) BOOL repeat;                  // 设置是否重复，默认为NO
@property (nonatomic, copy) NSDate *fireDate NS_DEPRECATED_IOS(2_0, 10_0);           // 用来设置触发推送的时间，iOS10以上无效
@property (nonatomic, copy) CLRegion *region NS_AVAILABLE_IOS(8_0);                  // 用来设置触发推送的位置，iOS8以上有效，iOS10以上优先级为I，应用需要有允许使用定位的授权
@property (nonatomic, copy) NSDateComponents *dateComponents NS_AVAILABLE_IOS(10_0); // 用来设置触发推送的日期时间，iOS10以上有效，优先级为II
@property (nonatomic, assign) NSTimeInterval timeInterval NS_AVAILABLE_IOS(10_0);    // 用来设置触发推送的时间，iOS10以上有效，优先级为III

@end

/*!
 * 注册或更新推送实体类
 */
@interface JPushNotificationRequest : NSObject<NSCopying, NSCoding>

@property (nonatomic, copy) NSString *requestIdentifier;    // 推送请求标识
@property (nonatomic, copy) JPushNotificationContent *content; // 设置推送的具体内容
@property (nonatomic, copy) JPushNotificationTrigger *trigger; // 设置推送的触发方式
@property (nonatomic, copy, nullable) void (^completionHandler)(id result); // 注册或更新推送成功回调，iOS10以上成功则result为UNNotificationRequest对象，失败则result为nil;iOS10以下成功result为UILocalNotification对象，失败则result为nil

@end


/*!
 * 应用内消息内容实体
 */
@interface JPushInAppMessage : NSObject

@property (nonatomic, copy)   NSString *mesageId;    // 消息id
@property (nonatomic, copy)   NSString *title;       // 标题
@property (nonatomic, copy)   NSString *content;     // 内容
@property (nonatomic, strong) NSArray  *target;      // 目标页面
@property (nonatomic, copy)   NSString *clickAction; // 跳转地址
@property (nonatomic, strong) NSDictionary *extras;  // 附加字段

@end

@interface JPushCollectControl : NSObject

/* ssid SSID信息。设置为NO,不采集SSID信息。默认为YES。 */
@property (nonatomic, assign) BOOL ssid;
/* bssid BSSID信息。设置为NO,不采集BSSID信息。默认为YES。 */
@property (nonatomic, assign) BOOL bssid;
/* cell 基站信息。设置为NO,不采集基站信息。默认为YES。*/
@property (nonatomic, assign) BOOL cell;
/* gps 经纬度信息。设置为NO,不采集经纬度信息。默认为YES。 */
@property (nonatomic, assign) BOOL gps;

@end

/*!
 * JPush 核心头文件
 */
@interface JPUSHService : NSObject


///----------------------------------------------------
/// @name Setup 启动相关
///----------------------------------------------------


/*!
 * @abstract 启动SDK
 *
 * @param launchingOption 启动参数.
 * @param appKey 一个JPush 应用必须的,唯一的标识. 请参考 JPush 相关说明文档来获取这个标识.
 * @param channel 发布渠道. 可选.
 * @param isProduction 是否生产环境. 如果为开发状态,设置为 NO; 如果为生产状态,应改为 YES.
 *                     App 证书环境取决于profile provision的配置，此处建议与证书环境保持一致.
 *
 * @discussion 提供SDK启动必须的参数, 来启动 SDK.
 * 此接口必须在 App 启动时调用, 否则 JPush SDK 将无法正常工作.
 */
+ (void)setupWithOption:(nullable NSDictionary *)launchingOption
                 appKey:(NSString *)appKey
                channel:(nullable NSString *)channel
       apsForProduction:(BOOL)isProduction;

/*!
 * @abstract 启动SDK
 *
 * @param launchingOption 启动参数.
 * @param appKey 一个JPush 应用必须的,唯一的标识. 请参考 JPush 相关说明文档来获取这个标识.
 * @param channel 发布渠道. 可选.
 * @param isProduction 是否生产环境. 如果为开发状态,设置为 NO; 如果为生产状态,应改为 YES.
 *                     App 证书环境取决于profile provision的配置，此处建议与证书环境保持一致.
 * @param advertisingId 广告标识符（IDFA） 如果不需要使用IDFA，传nil.
 *
 * @discussion 提供SDK启动必须的参数, 来启动 SDK.
 * 此接口必须在 App 启动时调用, 否则 JPush SDK 将无法正常工作.
 */
+ (void)setupWithOption:(nullable NSDictionary *)launchingOption
                 appKey:(NSString *)appKey
                channel:(nullable NSString *)channel
       apsForProduction:(BOOL)isProduction
  advertisingIdentifier:(nullable NSString *)advertisingId;


///----------------------------------------------------
/// @name APNs about 通知相关
///----------------------------------------------------

/*!
 * @abstract 注册要处理的远程通知类型
 *
 * @param types 通知类型
 * @param categories 类别组
 *
 */
+ (void)registerForRemoteNotificationTypes:(NSUInteger)types
                                categories:(nullable NSSet *)categories;
/*!
 * @abstract 新版本的注册方法（兼容iOS10）
 *
 * @param config 注册通知配置
 * @param delegate 代理
 *
 */
+ (void)registerForRemoteNotificationConfig:(JPUSHRegisterEntity *)config delegate:(nullable id<JPUSHRegisterDelegate>)delegate;


+ (void)registerDeviceToken:(NSData *)deviceToken;

/*!
 * @abstract 上报liveactivity的启动token
 *
 * @param activityAttributes 某liveActivity定义的属性类型
 * @param pushToStartToken 对应该liveactivity的pushToStartToken，如有更新，请及时调用该方法更新pushToStartToken
 * @param completion 响应回调
 * @param seq  请求序列号
 */
+ (void)registerLiveActivity:(NSString *)activityAttributes
            pushToStartToken:(nullable NSData *)pushToStartToken
                  completion:(nullable JPUSHLiveActivityTokenCompletion)completion
                        seq:(NSInteger)seq;

/*!
 * @abstract 注册liveActivity并上报其pushToken
 * 在pushToken有变化的时候同步调用该接口。
 * 在liveActivity结束的时候，请同步调用该接口，pushToken传nil
 *
 * @param liveActivityId 标识某一个liveActivity
 * @param pushToken 对应该liveActivity的pushToken，如有更新，请及时调用该方法更新pushToken
 * @param completion 响应回调
 * @param seq  请求序列号
 */
+ (void)registerLiveActivity:(NSString *)liveActivityId
                   pushToken:(nullable NSData *)pushToken
                  completion:(nullable JPUSHLiveActivityTokenCompletion)completion
                         seq:(NSInteger)seq;

/*!
 * @abstract 处理收到的 APNs 消息
 */
+ (void)handleRemoteNotification:(NSDictionary *)remoteInfo;

/*!
 * @abstract  向极光服务器提交Token
 *
 * @param voipToken 推送使用的Voip Token
 */
+ (void)registerVoipToken:(NSData *)voipToken;


/*!
 * @abstract  处理收到的 Voip 消息
 *
 * @param remoteInfo 下发的 Voip 内容
 */
+ (void)handleVoipNotification:(NSDictionary *)remoteInfo;


/*!
* @abstract 检测通知授权状态
* @param completion 授权结果通过status值返回，详见JPAuthorizationStatus
*/
+ (void)requestNotificationAuthorization:(nullable void (^)(JPAuthorizationStatus status))completion;

/*!
* @abstract 跳转至系统设置页面，iOS8及以上有效
*/
+ (void)openSettingsForNotification:(nullable void (^)(BOOL success))completionHandler NS_AVAILABLE_IOS(8_0);

/*!
 * Tags操作接口
 * 支持增加/覆盖/删除/清空/查询操作
 * 详情请参考文档：https://docs.jiguang.cn/jpush/client/iOS/ios_api/）
 */

/**
 增加tags

 @param tags 需要增加的tags集合
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)addTags:(NSSet<NSString *> *)tags
     completion:(nullable JPUSHTagsOperationCompletion)completion
            seq:(NSInteger)seq;

/**
 覆盖tags
 调用该接口会覆盖用户所有的tags

 @param tags 需要设置的tags集合
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)setTags:(NSSet<NSString *> *)tags
     completion:(nullable JPUSHTagsOperationCompletion)completion
            seq:(NSInteger)seq;

/**
 删除指定tags

 @param tags 需要删除的tags集合
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)deleteTags:(NSSet<NSString *> *)tags
        completion:(nullable JPUSHTagsOperationCompletion)completion
               seq:(NSInteger)seq;

/**
 清空所有tags
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)cleanTags:(nullable JPUSHTagsOperationCompletion)completion
              seq:(NSInteger)seq;

/**
 查询全部tags

 @param completion 响应回调，请在回调中获取查询结果
 @param seq 请求序列号
 */
+ (void)getAllTags:(nullable JPUSHTagsOperationCompletion)completion
               seq:(NSInteger)seq;

/**
 验证tag是否绑定
 
 @param completion 响应回调，回调中查看是否绑定
 @param seq 请求序列号
 */
+ (void)validTag:(NSString *)tag
      completion:(nullable JPUSHTagValidOperationCompletion)completion
             seq:(NSInteger)seq;

/**
 设置Alias

 @param alias 需要设置的alias
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)setAlias:(NSString *)alias
      completion:(nullable JPUSHAliasOperationCompletion)completion
             seq:(NSInteger)seq;

/**
 删除alias

 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)deleteAlias:(nullable JPUSHAliasOperationCompletion)completion
                seq:(NSInteger)seq;

/**
 查询当前alias

 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)getAlias:(nullable JPUSHAliasOperationCompletion)completion
             seq:(NSInteger)seq;


/*!
 * @abstract 过滤掉无效的 tags
 *
 * @discussion 如果 tags 数量超过限制数量, 则返回靠前的有效的 tags.
 * 建议设置 tags 前用此接口校验. SDK 内部也会基于此接口来做过滤.
 */
+ (NSSet *)filterValidTags:(NSSet *)tags;


/*!
 * Property操作接口
 * 支持增加/删除/清空操作
 * 详情请参考文档：https://docs.jiguang.cn/jpush/client/iOS/ios_api/）
 */

/**
 新增/更新用户属性
 
 如果某个用户属性之前已经存在了，则会更新；不存在，则会新增
 
 @param properties  需要新增或者更新的的用户属性内容，类型为NSDictionary；
                   Key 为用户属性名称，类型必须是 NSString 类型；Value为用户属性值，只支持 NSString、NSNumber、NSDate类型，如果属性为BOOL类型，传值时请转成NSNumber类型
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)setProperties:(NSDictionary *)properties
           completion:(nullable JPUSHPropertiesOperationCompletion)completion
                  seq:(NSInteger)seq;


/**
 删除指定属性

 @param keys 需要删除的属性名称集合
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)deleteProperties:(NSSet<NSString *> *)keys
              completion:(nullable JPUSHPropertiesOperationCompletion)completion
                     seq:(NSInteger)seq;


/**
 清空所有属性
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)cleanProperties:(nullable JPUSHPropertiesOperationCompletion)completion
                    seq:(NSInteger)seq;


/*!
 * 应用内消息接口
 * 使用应用内消息需要配置以下两个接口。请在进入页面和离开页面的时候相应地配置。以下两个接口请配套调用。
 */

/**
 进入页面
 
 请与 + (void)pageLeave:(NSString *)pageName; 方法配套使用
 
 @param pageName 页面名
 @discussion 使用应用内消息功能，需要配置pageEnterTo:和pageLeave:函数。
 */
+ (void)pageEnterTo:(NSString *)pageName;


/**
 离开页面
 
 请与 + (void)pageEnterTo:(NSString *)pageName;方法配套使用
 
 @param pageName 页面名
 @discussion 使用应用内消息功能，需要配置pageEnterTo:和pageLeave:函数。
 */
+ (void)pageLeave:(NSString *)pageName;


/*!
* @abstract 设置应用内消息的代理
*
* @discussion 遵守JPUSHInAppMessageDelegate的代理对象
*
*/
+ (void)setInAppMessageDelegate:(id<JPUSHInAppMessageDelegate>)inAppMessageDelegate;


///----------------------------------------------------
/// @name Stats 统计功能
///----------------------------------------------------

/*!
 * @abstract 开始记录页面停留
 *
 * @param pageName 页面名称
 * @discussion JCore 1.1.8 版本后，如需统计页面流，请使用 JAnalytics
 */
+ (void)startLogPageView:(NSString *)pageName __attribute__((deprecated("JCore 1.1.8 版本已过期")));

/*!
 * @abstract 停止记录页面停留
 *
 * @param pageName 页面
 * @discussion JCore 1.1.8 版本后，如需统计页面流，请使用 JAnalytics
 */
+ (void)stopLogPageView:(NSString *)pageName __attribute__((deprecated("JCore 1.1.8 版本已过期")));

/*!
 * @abstract 直接上报在页面的停留时间
 *
 * @param pageName 页面
 * @param seconds 停留的秒数
 * @discussion JCore 1.1.8 版本后，如需统计页面流，请使用 JAnalytics
 */
+ (void)beginLogPageView:(NSString *)pageName duration:(int)seconds __attribute__((deprecated("JCore 1.1.8 版本已过期")));

/*!
 * @abstract 开启Crash日志收集
 *
 * @discussion 默认是关闭状态.
 */
+ (void)crashLogON;

/*!
 * @abstract 地理位置上报
 *
 * @param latitude 纬度.
 * @param longitude 经度.
 *
 */
+ (void)setLatitude:(double)latitude longitude:(double)longitude;

/*!
 * @abstract 地理位置上报
 *
 * @param location 直接传递 CLLocation * 型的地理信息
 *
 * @discussion 需要链接 CoreLocation.framework 并且 #import <CoreLocation/CoreLocation.h>
 */
+ (void)setLocation:(CLLocation *)location;

/**
 设置地理围栏的最大个数
 默认值为 10 ，iOS系统默认地理围栏最大个数为20
 @param count 个数 count
 */
+ (void)setGeofeneceMaxCount:(NSInteger)count;

/**
 设置地理围栏'圈内'类型的检测周期
 默认15分钟检测一次
 */
+ (void)setGeofenecePeriodForInside:(NSInteger)seconds;

/**
 注册地理围栏的代理

 @param delegate 代理
 @param launchOptions app启动完成是收到的字段参数
 */
+ (void)registerLbsGeofenceDelegate:(id<JPUSHGeofenceDelegate>)delegate withLaunchOptions:(nullable NSDictionary *)launchOptions;

/**
 删除地理围栏
 
 @param geofenceId 地理围栏id
 */
+ (void)removeGeofenceWithIdentifier:(NSString *)geofenceId;

///----------------------------------------------------
/// @name Local Notification 本地通知
///----------------------------------------------------
/*!
 * @abstract 注册或更新推送 (支持iOS10，并兼容iOS10以下版本)
 *
 * JPush 2.1.9新接口
 * @param request JPushNotificationRequest类型，设置推送的属性，设置已有推送的request.requestIdentifier即更新已有的推送，否则为注册新推送，更新推送仅仅在iOS10以上有效，结果通过request.completionHandler返回
 * @discussion 旧的注册本地推送接口被废弃，使用此接口可以替换
 *
 */
+ (void)addNotification:(JPushNotificationRequest *)request;

/*!
 * @abstract 移除推送 (支持iOS10，并兼容iOS10以下版本)
 *
 * JPush 2.1.9新接口
 * @param identifier JPushNotificationIdentifier类型，iOS10以上identifier设置为nil，则移除所有在通知中心显示推送和待推送请求，也可以通过设置identifier.delivered和identifier.identifiers来移除相应在通知中心显示推送或待推送请求，identifier.identifiers如果设置为nil或空数组则移除相应标志下所有在通知中心显示推送或待推送请求；iOS10以下identifier设置为nil，则移除所有推送，identifier.delivered属性无效，另外可以通过identifier.notificationObj传入特定推送对象来移除此推送。
 * @discussion 旧的所有删除推送接口被废弃，使用此接口可以替换
 *
 */
+ (void)removeNotification:(nullable JPushNotificationIdentifier *)identifier;

/*!
 * @abstract 查找推送 (支持iOS10，并兼容iOS10以下版本)
 *
 * JPush 2.1.9新接口
 * @param identifier JPushNotificationIdentifier类型，iOS10以上可以通过设置identifier.delivered和identifier.identifiers来查找相应在通知中心显示推送或待推送请求，identifier.identifiers如果设置为nil或空数组则返回相应标志下所有在通知中心显示推送或待推送请求；iOS10以下identifier.delivered属性无效，identifier.identifiers如果设置nil或空数组则返回所有未触发的推送。须要设置identifier.findCompletionHandler回调才能得到查找结果，通过(NSArray *results)返回相应对象数组。
 * @discussion 旧的查找推送接口被废弃，使用此接口可以替换
 *
 */
+ (void)findNotification:(JPushNotificationIdentifier *)identifier;

/*!
 * @abstract 本地推送，最多支持64个
 *
 * @param fireDate 本地推送触发的时间
 * @param alertBody 本地推送需要显示的内容
 * @param badge 角标的数字。如果不需要改变角标传-1
 * @param alertAction 弹框的按钮显示的内容（IOS 8默认为"打开", 其他默认为"启动"）
 * @param notificationKey 本地推送标示符
 * @param userInfo 自定义参数，可以用来标识推送和增加附加信息
 * @param soundName 自定义通知声音，设置为nil为默认声音
 *
 * @discussion 最多支持 64 个定义，此方法被[addNotification:]方法取代
 */
+ (UILocalNotification *)setLocalNotification:(NSDate *)fireDate
                                    alertBody:(NSString *)alertBody
                                        badge:(int)badge
                                  alertAction:(NSString *)alertAction
                                identifierKey:(NSString *)notificationKey
                                     userInfo:(NSDictionary *)userInfo
                                    soundName:(NSString *)soundName __attribute__((deprecated("JPush 2.1.9 版本已过期")));

/*!
 * @abstract 本地推送 (支持 iOS8 新参数)
 *
 * IOS8新参数
 * @param region 自定义参数
 * @param regionTriggersOnce 自定义参数
 * @param category 自定义参数
 * @discussion 此方法被[addNotification:]方法取代
 */
+ (UILocalNotification *)setLocalNotification:(NSDate *)fireDate
                                    alertBody:(NSString *)alertBody
                                        badge:(int)badge
                                  alertAction:(NSString *)alertAction
                                identifierKey:(NSString *)notificationKey
                                     userInfo:(NSDictionary *)userInfo
                                    soundName:(NSString *)soundName
                                       region:(CLRegion *)region
                           regionTriggersOnce:(BOOL)regionTriggersOnce
                                     category:(NSString *)category NS_AVAILABLE_IOS(8_0) __attribute__((deprecated("JPush 2.1.9 版本已过期")));

/*!
 * @abstract 前台展示本地推送
 *
 * @param notification 本地推送对象
 * @param notificationKey 需要前台显示的本地推送通知的标示符
 *
 * @discussion 默认App在前台运行时不会进行弹窗，在程序接收通知调用此接口可实现指定的推送弹窗。--iOS10以下还可继续使用，iOS10以上在[UNUserNotificationCenterDelegate willPresentNotification:withCompletionHandler:]方法中调用completionHandler(UNNotificationPresentationOptionSound | UNNotificationPresentationOptionAlert);即可
 */
+ (void)showLocalNotificationAtFront:(UILocalNotification *)notification
                       identifierKey:(NSString *)notificationKey __attribute__((deprecated("JPush 2.1.9 版本已过期")));
/*!
 * @abstract 删除本地推送定义
 *
 * @param notificationKey 本地推送标示符
 * @discussion 此方法被[removeNotification:]方法取代
 */
+ (void)deleteLocalNotificationWithIdentifierKey:(NSString *)notificationKey __attribute__((deprecated("JPush 2.1.9 版本已过期")));

/*!
 * @abstract 删除本地推送定义
 * @discussion 此方法被[removeNotification:]方法取代
 */
+ (void)deleteLocalNotification:(UILocalNotification *)localNotification __attribute__((deprecated("JPush 2.1.9 版本已过期")));

/*!
 * @abstract 获取指定通知
 *
 * @param notificationKey 本地推送标示符
 * @return 本地推送对象数组, [array count]为0时表示没找到
 * @discussion 此方法被[findNotification:]方法取代
 */
+ (NSArray *)findLocalNotificationWithIdentifier:(NSString *)notificationKey __attribute__((deprecated("JPush 2.1.9 版本已过期")));

/*!
 * @abstract 清除所有本地推送对象
 * @discussion 此方法被[removeNotification:]方法取代
 */
+ (void)clearAllLocalNotifications __attribute__((deprecated("JPush 2.1.9 版本已过期")));


///----------------------------------------------------
/// @name Server badge 服务器端 badge 功能
///----------------------------------------------------

/*!
 * @abstract 设置角标(到服务器)
 *
 * @param value 新的值. 会覆盖服务器上保存的值(这个用户)
 *
 * @discussion 本接口不会改变应用本地的角标值.
 * 本地仍须调用 UIApplication:setApplicationIconBadgeNumber 函数来设置脚标.
 *
 * 本接口用于配合 JPush 提供的服务器端角标功能.
 * 该功能解决的问题是, 服务器端推送 APNs 时, 并不知道客户端原来已经存在的角标是多少, 指定一个固定的数字不太合理.
 *
 * JPush 服务器端脚标功能提供:
 *
 * - 通过本 API 把当前客户端(当前这个用户的) 的实际 badge 设置到服务器端保存起来;
 * - 调用服务器端 API 发 APNs 时(通常这个调用是批量针对大量用户),
 *   使用 "+1" 的语义, 来表达需要基于目标用户实际的 badge 值(保存的) +1 来下发通知时带上新的 badge 值;
 */
+ (BOOL)setBadge:(NSInteger)value;

/*!
 * @abstract 重置脚标(为0)
 *
 * @discussion 相当于 [setBadge:0] 的效果.
 * 参考 [JPUSHService setBadge:] 说明来理解其作用.
 */
+ (void)resetBadge;

///----------------------------------------------------
/// @name Other Feature 其他功能
///----------------------------------------------------

/*!
 * @abstract 设置手机号码(到服务器)
 *
 * @param mobileNumber 手机号码. 会与用户信息一一对应。可为空，为空则清除号码
 * @param completion 响应回调。成功则error为空，失败则error带有错误码及错误信息
 *
 * @discussion 设置手机号码后，可实现“推送不到短信到”的通知方式，提高推送达到率。结果信息通过completion异步返回，也可将completion设置为nil不处理结果信息。
 *
 */
+ (void)setMobileNumber:(NSString *)mobileNumber completion:(nullable void (^)(NSError *error))completion;

///----------------------------------------------------
/// @name Logs and others 日志与其他
///----------------------------------------------------

/*!
 * @abstract JPush标识此设备的 registrationID
 *
 * @discussion SDK注册成功后, 调用此接口获取到 registrationID 才能够获取到.
 *
 * JPush 支持根据 registrationID 来进行推送.
 * 如果你需要此功能, 应该通过此接口获取到 registrationID 后, 上报到你自己的服务器端, 并保存下来.
 * registrationIDCompletionHandler:是新增的获取registrationID的方法，需要在block中获取registrationID,resCode为返回码,模拟器调用此接口resCode返回1011,registrationID返回nil.
 * 更多的理解请参考 JPush 的文档网站.
 */
+ (NSString *)registrationID;

+ (void)registrationIDCompletionHandler:(void(^)(int resCode,NSString * _Nullable registrationID))completionHandler;

/*!
 * @abstract 打开日志级别到 Debug
 *
 * @discussion JMessage iOS 的日志系统参考 Android 设计了级别.
 * 从低到高是: Verbose, Debug, Info, Warning, Error.
 * 对日志级别的进一步理解, 请参考 Android 相关的说明.
 *
 * SDK 默认开启的日志级别为: Info. 只显示必要的信息, 不打印调试日志.
 *
 * 请在SDK启动后调用本接口，调用本接口可打开日志级别为: Debug, 打印调试日志.
 */
+ (void)setDebugMode;

/*!
 * @abstract 关闭日志
 *
 * @discussion 关于日志级别的说明, 参考 [JPUSHService setDebugMode]
 *
 * 虽说是关闭日志, 但还是会打印 Warning, Error 日志. 这二种日志级别, 在程序运行正常时, 不应有打印输出.
 *
 * 建议在发布的版本里, 调用此接口, 关闭掉日志打印.
 */
+ (void)setLogOFF;

/*!
 数据采集控制
 
 @param control 数据采集配置。
 */
+ (void)setCollectControl:(JPushCollectControl *)control;

/*!
 * @abstract 设置心跳时间间隔
 *
 * @param interval 心跳时间间隔 单位为秒, 取值范围为[30,290]
 *
 * @discussion 请在初始化函数之前调用该接口。
 *
 */
+ (void)setHeartBeatTimeInterval:(NSInteger)interval;

/*!
 * @abstract 设置SDK地理位置权限开关
 *
 * @discussion 关闭地理位置之后，SDK地理围栏的相关功能将受到影响，默认是开启。
 *
 */
+ (void)setLocationEanable:(BOOL)isEanble;

/*!
 * @abstract 设置PUSH开关
 *
 * @discussion 关闭PUSH之后，将接收不到极光通知推送、自定义消息推送、liveActivity消息推送，默认是开启。
 *
 */
+ (void)setPushEnable:(BOOL)isEnable completion:(nullable void (^)(NSInteger iResCode))completion;

/*!
 * @abstract 设置用户分群推送功能开关
 *
 * @param isEnable YES:开启，NO:关闭，默认是开启。
 *
 */
+ (void)setSmartPushEnable:(BOOL)isEnable;

/*!
 * @abstract 设置应用数据洞察扩展功能开关
 *
 * @param isEnable YES:开启，NO:关闭，默认是开启。
 *
 */
+ (void)setDataInsightsEnable:(BOOL)isEnable;


/*!
* @abstract 设置应用内提醒消息的代理
*
* @discussion 遵守JPushNotiInMessageDelegate的代理对象
*
*/
+ (void)setNotiInMessageDelegate:(id<JPUSHNotiInMessageDelegate>)notiInMessageDelegate;



///----------------------------------------------------
///********************下列方法已过期********************
///**************请使用新版tag/alias操作接口**************
///----------------------------------------------------
/// @name Tag alias setting 设置别名与标签
///----------------------------------------------------

/*!
 * 下面的接口是可选的
 * 设置标签和(或)别名（若参数为nil，则忽略；若是空对象，则清空；详情请参考文档：https://docs.jiguang.cn/jpush/client/iOS/ios_api/）
 * setTags:alias:fetchCompletionHandle:是新的设置标签别名的方法，不再需要显示声明回调函数，只需要在block里面处理设置结果即可.
 * WARN: 使用block时需要注意循环引用问题
 */
+ (void) setTags:(NSSet *)tags
           alias:(NSString *)alias
callbackSelector:(SEL)cbSelector
          target:(id)theTarget __attribute__((deprecated("JPush 2.1.1 版本已过期")));
+ (void) setTags:(NSSet *)tags
           alias:(NSString *)alias
callbackSelector:(SEL)cbSelector
          object:(id)theTarget __attribute__((deprecated("JPush 3.0.6 版本已过期")));
+ (void) setTags:(NSSet *)tags
callbackSelector:(SEL)cbSelector
          object:(id)theTarget __attribute__((deprecated("JPush 3.0.6 版本已过期")));
+ (void)setTags:(NSSet *)tags
          alias:(NSString *)alias
fetchCompletionHandle:(void (^)(int iResCode, NSSet *iTags, NSString *iAlias))completionHandler __attribute__((deprecated("JPush 3.0.6 版本已过期")));
+ (void)  setTags:(NSSet *)tags
aliasInbackground:(NSString *)alias __attribute__((deprecated("JPush 3.0.6 版本已过期")));
+ (void)setAlias:(NSString *)alias
callbackSelector:(SEL)cbSelector
          object:(id)theTarget __attribute__((deprecated("JPush 3.0.6 版本已过期")));

@end

@class UNUserNotificationCenter;
@class UNNotificationResponse;

@protocol JPUSHRegisterDelegate <NSObject>

/*
 * @brief handle UserNotifications.framework [willPresentNotification:withCompletionHandler:]
 * @param center [UNUserNotificationCenter currentNotificationCenter] 新特性用户通知中心
 * @param notification 前台得到的的通知对象
 * @param completionHandler 该callback中的options 请使用UNNotificationPresentationOptions
 */
- (void)jpushNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(NSInteger options))completionHandler;
/*
 * @brief handle UserNotifications.framework [didReceiveNotificationResponse:withCompletionHandler:]
 * @param center [UNUserNotificationCenter currentNotificationCenter] 新特性用户通知中心
 * @param response 通知响应对象
 * @param completionHandler
 */
- (void)jpushNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler;

/*
 * @brief handle UserNotifications.framework [openSettingsForNotification:]
 * @param center [UNUserNotificationCenter currentNotificationCenter] 新特性用户通知中心
 * @param notification 当前管理的通知对象
 */
- (void)jpushNotificationCenter:(UNUserNotificationCenter *)center openSettingsForNotification:(UNNotification *)notification NS_AVAILABLE_IOS(12.0);

/**
 * 监测通知授权状态返回的结果
 * @param status 授权通知状态，详见JPAuthorizationStatus
 * @param info 更多信息，预留参数
 */
- (void)jpushNotificationAuthorization:(JPAuthorizationStatus)status withInfo:(nullable NSDictionary *)info;

@end

@protocol JPUSHGeofenceDelegate <NSObject>
/**
 触发地理围栏
 @param geofence 地理围栏触发时返回的信息
 @param error 错误信息
 */
- (void)jpushGeofenceRegion:(nullable NSDictionary *)geofence
                      error:(nullable NSError *)error;

/**
 拉取地理围栏列表的回调
 
 @param geofenceList 地理围栏列表
 */
- (void)jpushCallbackGeofenceReceived:(nullable NSArray<NSDictionary*> *)geofenceList;

/**
 进入地理围栏区域
 
 @param geofenceId 地理围栏id
 @param userInfo 地理围栏触发时返回的信息
 @param error 错误信息
 */
- (void)jpushGeofenceIdentifer:(NSString *)geofenceId didEnterRegion:(NSDictionary *_Nullable)userInfo error:(NSError *_Nullable)error __attribute__((deprecated("JPush 3.6.0 版本已过期")));

/**
 离开地理围栏区域
 
 @param geofenceId 地理围栏id
 @param userInfo 地理围栏触发时返回的信息
 @param error 错误信息
 */
- (void)jpushGeofenceIdentifer:(NSString *)geofenceId didExitRegion:(NSDictionary *_Nullable)userInfo error:(NSError *_Nullable)error __attribute__((deprecated("JPush 3.6.0 版本已过期")));

@end


@protocol JPUSHNotiInMessageDelegate <NSObject>

/**
 应用内提醒消息展示的回调
 
 @param content 应用内提醒消息的内容

 */
- (void)jPushNotiInMessageDidShowWithContent:(NSDictionary *)content;

/**
 应用内提醒消息点击的回调
 
 @param content 应用内提醒消息的内容

 */
- (void)jPushNotiInMessageDidClickWithContent:(NSDictionary *)content;

@end


@protocol JPUSHInAppMessageDelegate <NSObject>

/**
 应用内消息展示的回调
 
 @param inAppMessage 应用内消息的内容

 */
- (void)jPushInAppMessageDidShow:(JPushInAppMessage *)inAppMessage;

/**
 应用内消息点击的回调
 
 @param inAppMessage 应用内消息的内容

 */
- (void)jPushInAppMessageDidClick:(JPushInAppMessage *)inAppMessage;

@end

NS_ASSUME_NONNULL_END

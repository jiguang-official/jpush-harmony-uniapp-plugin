//
//  JPUSHSDKHelper.h
//  JPUSHSDKHelper
//
//  Created by Shuni Huang on 2025/7/29.
//

#import <Foundation/Foundation.h>
#import "JPUSHService.h"

typedef void (^JPUSHHelperTagsOperationCompletion)(NSInteger iResCode, NSArray *_Nullable iTags, NSInteger seq);
typedef void (^JPUSHHelperTagValidOperationCompletion)(NSInteger iResCode, NSArray *_Nullable iTags, NSInteger seq, BOOL isBind);

@interface JPUSHSDKHelper : NSObject

/**
 增加tags

 @param tags 需要增加的tags集合
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)addTags:(NSArray<NSString *> *)tags
     completion:(nullable JPUSHHelperTagsOperationCompletion)completion
            seq:(NSInteger)seq;

/**
 覆盖tags
 调用该接口会覆盖用户所有的tags

 @param tags 需要设置的tags集合
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)setTags:(NSArray<NSString *> *)tags
     completion:(nullable JPUSHHelperTagsOperationCompletion)completion
            seq:(NSInteger)seq;

/**
 删除指定tags

 @param tags 需要删除的tags集合
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)deleteTags:(NSArray<NSString *> *)tags
        completion:(nullable JPUSHHelperTagsOperationCompletion)completion
               seq:(NSInteger)seq;

/**
 清空所有tags
 @param completion 响应回调
 @param seq 请求序列号
 */
+ (void)cleanTags:(nullable JPUSHHelperTagsOperationCompletion)completion
              seq:(NSInteger)seq;

/**
 查询全部tags

 @param completion 响应回调，请在回调中获取查询结果
 @param seq 请求序列号
 */
+ (void)getAllTags:(nullable JPUSHHelperTagsOperationCompletion)completion
               seq:(NSInteger)seq;

/**
 验证tag是否绑定
 
 @param completion 响应回调，回调中查看是否绑定
 @param seq 请求序列号
 */
+ (void)validTag:(NSString *)tag
      completion:(nullable JPUSHHelperTagValidOperationCompletion)completion
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
+ (NSArray *)filterValidTags:(NSArray *)tags;


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
+ (void)deleteProperties:(NSArray<NSString *> *)keys
              completion:(nullable JPUSHPropertiesOperationCompletion)completion
                     seq:(NSInteger)seq;


+ (NSSet *)arrayToSet:(NSArray *)array;


@end

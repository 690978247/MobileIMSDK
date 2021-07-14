//  ----------------------------------------------------------------------
//  Copyright (C) 2020  即时通讯网(52im.net) & Jack Jiang.
//  The MobileIMSDK_TCP (MobileIMSDK v5.x TCP版) Project.
//  All rights reserved.
//
//  > Github地址: https://github.com/JackJiang2011/MobileIMSDK
//  > 文档地址:    http://www.52im.net/forum-89-1.html
//  > 技术社区：   http://www.52im.net/
//  > 技术交流群： 320837163 (http://www.52im.net/topic-qqgroup.html)
//  > 作者公众号： “即时通讯技术圈】”，欢迎关注！
//  > 联系作者：   http://www.52im.net/thread-2792-1-1.html
//
//  "即时通讯网(52im.net) - 即时通讯开发者社区!" 推荐开源工程。
//  ----------------------------------------------------------------------

#import <Foundation/Foundation.h>
#import "Protocal.h"
#import "PLoginInfoResponse.h"
#import "PErrorResponse.h"
#import "PLoginInfo.h"
#import "PKickoutInfo.h"

/*!
 * MibileIMSDK框架的协议工厂类。
 * <p>
 * 理论上这些协议都是即时通讯框架内部要用到的，上层应用可以无需理解和理会之。
 *
 * @author Jack Jiang(http://www.52im.net/thread-2792-1-1.html)
 * @since 2.1
 */
@interface ProtocalFactory : NSObject


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - 协议解析相关方法
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
* 将JSON转换而来的byte数组反序列化成Protocal类的对象.
* <p>
* <b>本方法主要由MobileIMSDK框架内部使用。</b>
*
* @param fullProtocalJASOnBytes JSON转换而来的byte数组
* @return 如果返回列化成功则返回对象，否则返回nil
*/
+ (id) parse:(NSData *)fullProtocalJASOnBytes;

/*!
 * 将JSON转换而来的byte数组反序列化成指定类的对象.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param fullProtocalJASOnBytes JSON转换而来的byte数组
 * @param clazz 类
 * @return 如果返回列化成功则返回对象，否则返回nil
 */
+ (id) parse:(NSData *)fullProtocalJASOnBytes withClass:(Class)clazz;

/*!
 * 将指定的JSON字符串反序列化成指定类的对象.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param dataContentJSONOfProtocal json字符串
 * @param clazz 类
 * @return 如果返回列化成功则返回对象，否则返回nil
 *
 */
+ (id) parseObject:(NSString *)dataContentJSONOfProtocal withClass:(Class)clazz;

/*!
 * 接收用户登陆响应消息对象（该对象由客户端接收）.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param dataContentOfProtocal
 * @return
 */
+ (PLoginInfoResponse *) parsePLoginInfoResponse:(NSString *)dataContentOfProtocal;

/*!
 * 解析错误响应消息对象（该对象由客户端接收）.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param dataContentOfProtocal
 * @return
 */
+ (PErrorResponse *) parsePErrorResponse:(NSString *) dataContentOfProtocal;

/*!
 * 解析用户被踢消息报文对象（该对象由客户端接收）.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param dataContentOfProtocal
 * @return
 */
+ (PKickoutInfo *)parsePKickoutInfo:(NSString *)dataContentOfProtocal;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - 协议组装相关方法
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * 创建用户注消登陆消息对象（该对象由客户端发出）.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param user_id
 * @param loginName
 * @return 新建的 Protocal 报文对象
 */
+ (Protocal *) createPLoginoutInfo:(NSString *) user_id;

/*!
 * 创建用户登陆消息对象（该对象由客户端发出）.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param loginInfo 登陆信息对象，详见：http://docs.52im.net/extend/docs/api/mobileimsdk/server_tcp/net/x52im/mobileimsdk/server/protocal/c/PLoginInfo.html
 * @return 新建的 Protocal 报文对象
 */
+ (Protocal *) createPLoginInfo:(PLoginInfo *)loginInfo;

/*!
 * 创建用户心跳包对象（该对象由客户端发出）.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param from_user_id
 * @return 新建的 Protocal 报文对象
 */
+ (Protocal *) createPKeepAlive:(NSString *)from_user_id;

/*!
 *  通用消息的Protocal对象新建方法（默认不需要Qos支持）。
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 *  @param dataContent  要发送的数据内容（字符串方式组织）
 *  @param from_user_id 发送人的user_id
 *  @param to_user_id   接收人的user_id
 *
 *  @return 新建的 Protocal 报文对象
 */
+ (Protocal *) createCommonData:(NSString *)dataContent fromUserId:(NSString *)from_user_id toUserId:(NSString *)to_user_id;

/*!
 *  通用消息的Protocal对象新建方法（默认不需要Qos支持）。
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 *  @param dataContent  要发送的数据内容（字符串方式组织）
 *  @param from_user_id 发送人的user_id
 *  @param to_user_id   接收人的user_id
 *
 *  @return 新建的Protocal对象
 */
+ (Protocal *) createCommonData:(NSString *)dataContent fromUserId:(NSString *)from_user_id toUserId:(NSString *)to_user_id withTypeu:(int)typeu;

/*!
 *  通用消息的Protocal对象新建方法。
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 *  @param dataContent  要发送的数据内容（字符串方式组织）
 *  @param from_user_id 发送人的user_id
 *  @param to_user_id   接收人的user_id
 *  @param QoS          是否需要QoS支持，true表示需要，否则不需要
 *  @param fingerPrint  消息指纹特征码，为nil则表示由系统自动生成指纹码，否则使用本参数指明的指纹码
 *
 *  @return 新建的 Protocal 报文对象
 */
+ (Protocal *) createCommonData:(NSString *)dataContent fromUserId:(NSString *)from_user_id toUserId:(NSString *)to_user_id qos:(bool)QoS fp:(NSString *)fingerPrint withTypeu:(int)typeu;

/*!
 * 客户端from_user_id向to_user_id发送一个QoS机制中需要的“收到消息应答包” (bridge标识默认为false).
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param from_user_id 发起方
 * @param to_user_id 接收方
 * @param recievedMessageFingerPrint 已收到的消息包指纹码
 * @return 新建的 Protocal 报文对象
 */
+ (Protocal *) createRecivedBack:(NSString *)from_user_id toUserId:(NSString *)to_user_id withFingerPrint:(NSString *)recievedMessageFingerPrint;

/*!
 * 客户端from_user_id向to_user_id发送一个QoS机制中需要的“收到消息应答包”.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param from_user_id 发起方
 * @param to_user_id 接收方
 * @param recievedMessageFingerPrint 已收到的消息包指纹码
 * @return 新建的 Protocal 报文对象
 */
+ (Protocal *) createRecivedBack:(NSString *)from_user_id toUserId:(NSString *)to_user_id withFingerPrint:(NSString *)recievedMessageFingerPrint andBridge:(bool)bridge;

/**
 * 创建用户被踢包报文对象（该对象由服务端发出）.
 * <p>
 * <b>本方法主要由MobileIMSDK框架内部使用。</b>
 *
 * @param to_user_id 接收方
 * @param code 被踢原因编码（本参数不可为空），see {@link PKickoutInfo} 中的常量定义，自定义被踢原因请使用>100的值
 * @param reason 被踢原因描述（本参数可为空）
 * @return 新建的{@link Protocal}报文对象
 * @since 6.0
 */
+ (Protocal *) createPKickout:(nonnull NSString *)to_user_id code:(int)code reason:(nullable NSString *)reason;

@end


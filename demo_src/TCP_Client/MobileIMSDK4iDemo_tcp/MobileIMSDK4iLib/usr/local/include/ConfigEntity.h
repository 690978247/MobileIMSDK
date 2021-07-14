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

/*!
 * MobileIMSDK的全局参数控制类。
 *
 * @author Jack Jiang(http://www.52im.net/thread-2792-1-1.html)
 * @version 1.0
 * @since 2.1
 */
@interface ConfigEntity : NSObject

/*! 
 * @typedef SenseMode
 * MobileIMSDK即时通讯核心框架预设的敏感度模式.
 *
 * <p>
 * 对于客户端而言，此模式决定了用户与服务端网络会话的健康模式，原则上超敏感客户端的体验越好。
 *
 * <p>
 * <b>重要说明：</b><u>客户端本模式的设定必须要与服务端的模式设制保持一致</u>，否则可能因参数的不一致而导致IM算法的不匹配，进而出现不可预知的问题。
 *
 * @author Jack Jiang, 2015-09-07
 * @version 2.1
 */
typedef enum
{
    /*!
     * 此模式下：<br>
     * * KeepAlive心跳问隔为3秒；<br>
     * * 5秒后未收到服务端心跳反馈即认为连接已断开（相当于连续2个心跳间隔(即算法最大6秒延迟后)后仍未收到服务端反馈）。
     */
    SenseMode3S,
    
    /*!
     * 此模式下：<br>
     * * KeepAlive心跳问隔为10秒；<br>
     * * 15秒后未收到服务端心跳反馈即认为连接已断开（相当于连续2个心跳间隔(即算法最大20秒延迟后)后仍未收到服务端反馈）。
     */
    SenseMode10S,
    
    /*!
     * 此模式下：<br>
     * * KeepAlive心跳问隔为15秒；<br>
     * * 20秒后未收到服务端心跳反馈即认为连接已断开（相当于连续2个心跳间隔(即算法最大30秒延迟后)后仍未收到服务端反馈）。
     * @since 5.0
     */
    SenseMode15S,
    
    /*!
     * 此模式下：<br>
     * * KeepAlive心跳问隔为30秒；<br>
     * * 35秒后未收到服务端心跳反馈即认为连接已断开（相当于连续2个心跳间隔(即算法最大60秒延迟后)后仍未收到服务端反馈）。
     */
    SenseMode30S,
    
    /*!
     * 此模式下：<br>
     * * KeepAlive心跳问隔为60秒；<br>
     * * 65秒后未收到服务端心跳反馈即认为连接已断开（相当于连续2个心跳间隔(即算法最大120秒延迟后)后仍未收到服务端反馈）。
     */
    SenseMode60S,
    
    /*!
     * 此模式下：<br>
     * * KeepAlive心跳问隔为120秒；<br>
     * *125秒后未收到服务端心跳反馈即认为连接已断开（相当于连续2个心跳间隔(即算法最大240秒延迟后)后仍未收到服务端反馈）。
     */
    SenseMode120S
} SenseMode;

/*!
 *  设置AppKey.
 *
 *  @param key AppKey字符串
 */
+ (void)registerWithAppKey:(NSString *)key;

/*!
 * 全局设置：服务端IP或域名。请在你的应用中设置本参数！
 * @warning 如需设置本参数，请在登陆前调用，否则将不起效。
 *
 * @param sIp 服务器的ip地址或域名
 */
+ (void) setServerIp:(NSString*)sIp;

/*!
 *  返回设置的服务端IP或域名。
 *
 *  @return 服务端IP或域名
 */
+ (NSString *)getServerIp;

/*!
 * 全局设置：服务端TCP服务侦听端口号，默认8901。
 * @warning 如需设置本参数，请在登陆前调用，否则将不起效。
 *
 * @param sPort 服务端的端口号
 */
+ (void) setServerPort:(int)sPort;

/*!
 *  返回设置的服务端端口号。
 *
 *  @return 服务端端口号
 */
+ (int) getServerPort;

/*!
 * 全局设置：本地TCP数据发送和侦听端口。默认是-1。
 *
 * <br>
 * 在什么场景下建议使用固定端口号呢？通常用于debug时，比如观察NAT网络下的外网端口分配情况。当然只要开发者确认使用的端口不会与其它APP冲突，则可
 * 随便指定本地端口，不会有任何影响（不影响与服务端的通信逻辑）。
 *
 * @warning 如需设置本参数，请在登陆前调用，否则将不起效。
 *
 * @param lPort 本地TCP数据发送和侦听端口号。<u>参数lPort=-1时表示不绑定固定port</u>（由系统自动分配，这意味着同时开启两个及以上本SDK的实例也不会出现端口占用
 * 冲突），否则使用指定端口
 */
+ (void) setLocalSendAndListeningPort:(int)lPort;

+ (int) getLocalSendAndListeningPort;

/*!
 * 设置MobileIMSDK即时通讯核心框架预设的敏感度模式（默认为 SenseMode15S模式）。
 *
 * <p>
 * <b>重要说明：</b><u>客户端本模式的设定必须要与服务端的模式设制保持一致</u>，否则可能因参数的不一致而导致IM算法的不匹配，进而出现不可预知的问题。
 *
 * @warning 请在登陆前调用，否则将不起效.
 *
 * @param mode 框架预设的敏感度模式
 * @see SenseMode
 */
+ (void) setSenseMode:(SenseMode)mode;

@end

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
#import "CompletionDefine.h"

/*!
 * 用于保持与服务端通信活性的Keep alive独立线程。
 * <p>
 * <b>Keep alive的目的有2个：</b><br>
 * 1、<u>防止NAT路由算法导致的端口老化</u>：<br>
 * <code>
 * 路由器的NAT路由算法存在所谓的“端口老化”概念，请参见文章：http://www.52im.net/thread-209-1-1.html。
 * </code>
 * <br>
 * 2、<u>即时探测由于网络状态的变动而导致的通信中断</u>（进而自动触发自动治愈机制）：<br>
 * <code>
 * 此种情况可的原因有（但不限于）：无线网络信号不稳定、WiFi与2G/3G/4G等同开情况下的网络切换、网络连接正常但宽带欠费被停机、手机系统的省电策略等。
 * </code>
 * <p>
 * <b>本线程的启停，目前属于MobileIMSDK算法的一部分，暂时无需也不建议由应用层自行调用。</b>
 *
 * @author Jack Jiang(http://www.52im.net/thread-2792-1-1.html)
 * @version 1.0
 */
@interface KeepAliveDaemon : NSObject

/// 获取本类的单例。使用单例访问本类的所有资源是唯一的合法途径。
+ (KeepAliveDaemon *)sharedInstance;

/*!
 * Keep Alive 心跳时间间隔（单位：毫秒），默认15000秒（即15秒）.
 * <p>
 * 心跳间隔越短则保持会话活性的健康度更佳，但将使得在大量客户端连接情况下服务端因此而增加负载，
 * 且手机将消耗更多电量和流量，所以此间隔需要权衡（建议为：>=3秒 且 <270秒(即4分半钟)）！
 * <p>
 * 说明：此参数用于设定客户端发送到服务端的心跳间隔，心跳包的作用是用来保持与服务端的会话活性（
 * 更准确的说是为了避免客户端因路由器的NAT算法而导致路由器端口老化，相关知识见此文：http://www.52im.net/thread-281-1-1.html）.
 * <p>
 * 参定此参数的同时，也需要相应设置服务端的ServerLauncher.SESION_RECYCLER_EXPIRE参数。
 *
 *  @param keepAliveTimeWithMils
 */
+ (void) setKEEP_ALIVE_INTERVAL:(int)keepAliveTimeWithMils;

/*!
 *  返回当前设置的Keep Alive 心跳时间间隔（单位：毫秒）.
 *
 *  @return
 */
+ (int) getKEEP_ALIVE_INTERVAL;

 /*!
  * 收到服务端响应心跳包的超时间时间（单位：毫秒），默认（15 * 1000 + 5000）＝ 20000 毫秒（即20秒）.
  * <p>
  * 超过这个时间客户端将判定与服务端的网络连接已断开（此间隔建议为(KEEP_ALIVE_INTERVAL * 1) + 5 秒），
  * 没有上限，但不可太长，否则将不能即时反映出与服务器端的连接断开（比如掉掉线时），请从能忍受的反应时长和即时性上做出权衡。
  * <p>受的反应时长和即时性上做出权衡。
  * <p>本参数除与{@link KeepAliveDaemon#KEEP_ALIVE_INTERVAL}有关联外，不受其它设置影响。
  *
  *  @param networkConnectionTimeout
  */
+ (void) setNETWORK_CONNECTION_TIME_OUT:(int)networkConnectionTimeout;

/*!
 *  服务端响应心跳包的超时间时间（单位：毫秒）.
 *
 *  @return 
 */
+ (int) getNETWORK_CONNECTION_TIME_OUT;

/*!
 * 心跳线程算法已判定需要与服务器的“通信通道”断开，调用此方法将进入框架的“通信通道”断开处理逻辑。
 * <p>
 * <b>本方法，目前属于MobileIMSDK框架算法的一部分，暂时无需也不建议由应用层开发者自行调用。</b>
 */
- (void)notifyConnectionLost;

/*!
 * 无条件中断本线程的运行。
 * <p>
 * <b>本线程的启停，目前属于MobileIMSDK算法的一部分，暂时无需也不建议由应用层自行调用。</b>
 */
- (void) stop;

/*!
 * 启动线程。
 * <p>
 * 无论本方法调用前线程是否已经在运行中，都会尝试首先调用 {@link #stop()}方法，以便确保线程被启动前是真正处于停止状态，这也意味着可无害调用本方法。
 * <p>
 * <b>本线程的启停，目前属于MobileIMSDK算法的一部分，暂时无需也不建议由应用层自行调用。</b>
 *
 * @param immediately true表示立即执行线程作业，否则直到 {@link #AUTO_RE$LOGIN_INTERVAL}执行间隔的到来才进行首次作业的执行
 */
- (void) start:(BOOL)immediately;

/**
 * 线程是否正在运行中。
 *
 * @return true表示是，否则线路处于停止状态
 */
- (BOOL) isKeepAliveRunning;

/**
 * 收到服务端反馈的心跳包时调用此方法：作用是更新服务端最背后的响应时间戳.
 * <p>
 * <b>本方法的调用，目前属于MobileIMSDK算法的一部分，暂时无需也不建议由应用层自行调用。</b>
 */
- (void) updateGetKeepAliveResponseFromServerTimstamp;

/**
 * 设置网络断开事件观察者.
 * <p>
 * <b>本方法的调用，目前属于MobileIMSDK算法的一部分，暂时无需也不建议由应用层自行调用。</b>
 *
 * @param networkConnectionLostObserver
 */
- (void) setNetworkConnectionLostObserver:(ObserverCompletion)networkConnLostObserver;

/*!
 *  Just for DEBUG.
 */
- (void) setDebugObserver:(ObserverCompletion)debugObserver;


@end

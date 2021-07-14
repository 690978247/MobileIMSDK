//  ----------------------------------------------------------------------
//  Copyright (C) 2020  即时通讯网(52im.net) & Jack Jiang.
//  The MobileIMSDK_X (MobileIMSDK v4.x) Project.
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
#import "MBGCDAsyncUdpSocket.h"

/*!
 * 一个本地UDP消息发送工具类。
 *
 * @author Jack Jiang, 2014-10-27
 * @version 1.0
 * @since 2.1
 */
@interface UDPUtils : NSObject

/*!
 * 发送一条UDP消息。
 *
 * @param skt GCDAsyncUdpSocket对象引用
 * @param d 要发送的比特数组
 * @return true表示成功发出，否则表示发送失败
 * @see #send(DatagramSocket, DatagramPacket)
 */
+ (BOOL) send:(MBGCDAsyncUdpSocket *) skt withData:(NSData *)d;

@end

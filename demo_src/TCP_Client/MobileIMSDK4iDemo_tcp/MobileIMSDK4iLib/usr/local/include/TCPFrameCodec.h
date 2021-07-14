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

/**
 * MobileIMSDK的TCP半包、粘包编/解码实用工具类。
 *
 * @author Jack Jiang(http://www.52im.net/thread-2792-1-1.html)
 * @since 5.0
 */
@interface TCPFrameCodec : NSObject

/**
 * @brief 为了妥善解决TCP的半包、粘包经典问题，MobileIMSDK中使用“数据包头Header+数据包体Body”的帧组织形式。
 *
 * 即帧编码格式为：Header（存放的是body数据长度，定长4个字节int整数） + Body（真正的数据内容，不定长，长度应在Header的最大值之内）。
 * <pre>
 *  以发送一个字母“A”（即body为“A”）为例，以下是编码后的完整数据帧形式：
 *  + ------ Header (4 bytes)  ------ | --------   Body (1 bytes) -------- +
 *  +     0x0000 0000 0000 0001  |              0x0041                       +
 *  + -----（内容为int整数1）  ---- | （内容为字母“A”的ASCII码） +
 * </pre>
 *
 *  @param bodyDataOfFrame 要发送的真正数据内容，必须不为空（即不为nil且length > 0）
 *  @return 如果body不为空则返回编码后的完整数据帧(Header+Body)，否则返回nil
 */
+ (NSData *)encodeFrame:(NSData *)bodyDataOfFrame;

/**
 * 解码TCP帧的Header数据，得到Body的数据长度（有关MobileIMSDK中的TCP数据包帧编码格式，请见 [TCPCodec encode:] 方法的说明）。
 *
 * @return Header数据解码得到的int整数就是该TCP帧的Body数据长度（单位：字节）
 */
+ (int)decodeBodyLength:(NSData *)headerDataOfFrame;

/**
 * 设置MobileIMSDK中的TCP数据帧Headder（头部）字节长度（默认4字节）。
 *
 * @param l TCP数据帧Headder（头部）字节长度
 */
+ (void)setTCP_FRAME_FIXED_HEADER_LENGTH:(int)l;

/**
 * 获取MobileIMSDK中的TCP数据帧Headder（头部）字节长度）。
 *
 * @return 字节长度
 */
+ (int)getTCP_FRAME_FIXED_HEADER_LENGTH;

/**
 * 设置MobileIMSDK中的TCP数据帧Body（数据体）的最大字节长度（默认最大6KB）。
 *
 * @param l TCP数据帧Body（数据体）的最大字节长度
 */
+ (void)setTCP_FRAME_MAX_BODY_LENGTH:(int)l;

/**
 * 获取MobileIMSDK中的TCP数据帧Body（数据体）的最大字节长度。
 *
 * @return 字节长度
 */
+ (int)getTCP_FRAME_MAX_BODY_LENGTH;

@end

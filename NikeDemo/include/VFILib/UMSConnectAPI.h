//
//  UMSConnectAPI.h
//  UMSConnectAPI
//
//  Created by Aaron on 2017/2/16.
//  Copyright © 2017年 Aaron. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^SuccessBlock)(id receiveData);
typedef void (^FailBlock)(NSInteger errCode,NSString*errInfo, NSError*error);

typedef enum {
    ConnectionModeDebug,
    ConnectionModeProduct,
    ConnectionModeNoSSL,
} ConnectionMode;

@interface UMSConnectAPI : NSObject
//@property (copy,nonatomic) NSString *termType;
//@property (copy,nonatomic) NSString *sn;
@property (copy,nonatomic) NSString *ip;
@property int port;
@property ConnectionMode mode;
/********获取通讯库实例*********
 *termType 设备类型
 *sn:      设备序列号
 *mode:    通讯库类型，测试环境或生产环境
 ******************************/
+(UMSConnectAPI*)shareInstanceWithMode:(ConnectionMode)mode ip:(NSString*)ip port:(int)port;

//通过以上方法获取实例之后下次可直接调用getInstance来获取UMSConnectAPI
+(UMSConnectAPI*)getInstance;
//发送认证报文
- (void)sendCertificatePacket:(NSData *)packet successCB:(SuccessBlock)successBlock errorCB:(FailBlock)failBlock;
/********发送数据*********
 *data     发送的数据
 *timeout   超时时间
 *success_cb  成功回调（返回类型为NSData）
 *errorcb  失败回调
 ******************************/
-(void)sendData:(NSData*)data timeout:(NSTimeInterval)timeout successCB:(SuccessBlock)successBlock errorCB:(FailBlock)failBlock;
//timeout 默认60秒
-(void)sendData:(NSData*)data successCB:(SuccessBlock)successBlock errorCB:(FailBlock)failBlock;

@end

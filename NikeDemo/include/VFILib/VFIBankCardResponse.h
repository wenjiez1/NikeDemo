//
//  VFIBankCardResponse.h
//  VFILibTest
//
//  Created by Verifone on 17/5/21.
//  Copyright © 2017年 Verifone. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VFIBankCardResponse : NSObject

@property (nonatomic, retain) NSString *respCode;
@property (nonatomic, retain) NSString *MID;
@property (nonatomic, retain) NSString *TID;
@property (nonatomic, retain) NSString *merchCnName;
@property (nonatomic, retain) NSString *merchEnName;
@property (nonatomic, retain) NSNumber *operNo;
@property (nonatomic, retain) NSString *issueCode;
@property (nonatomic, retain) NSString *acqCode;
@property (nonatomic, retain) NSString *cardExp;
@property (nonatomic, retain) NSString *cardNo;
@property (nonatomic, retain) NSString *orgTransType;
@property (nonatomic, retain) NSString *transType;
@property (nonatomic, retain) NSString *batchNo;
@property (nonatomic, retain) NSString *sysTrace;
@property (nonatomic, retain) NSString *authCode;
@property (nonatomic, retain) NSString *refCode;
@property (nonatomic, retain) NSDate *tranDateTime;
@property (nonatomic, retain) NSNumber *amount;
@property (nonatomic, retain) NSString *serialNo;
@property (nonatomic, retain) NSString *receipt;
@property (nonatomic, retain) NSString *TC;
@property (nonatomic, retain) NSString *TVR;
@property (nonatomic, retain) NSString *TSI;
@property (nonatomic, retain) NSString *AID;
@property (nonatomic, retain) NSString *ATC;
@property (nonatomic, retain) NSString *appLabel;
@property (nonatomic, retain) NSString *appPreName;
@property (nonatomic, retain) NSString *TAC;
@property (nonatomic, assign) BOOL isOfflineTran;
@property (nonatomic, assign) char inputMode;
@property (nonatomic, retain) NSString *AIP;
@property (nonatomic, retain) NSString *termCap;
@property (nonatomic, retain) NSString *cardSeqNo;
@property (nonatomic, retain) NSString *remark;
@property (nonatomic, retain) NSString *IAD;
@property (nonatomic, retain) NSString *unPreNo;
@property (nonatomic, retain) NSString *CVMR;
@property (nonatomic, assign) char cardType;
@property (nonatomic, assign) char noSignFlag;
@property (nonatomic, retain) NSString *cashierNo;
@property (nonatomic, retain) NSString *merchantOrderNo;//Nike商户订单流水号


typedef enum{
    CARD_TYPE_CUP   =   0x31,
    CARD_TYPE_VISA  =   0x32,
    CARD_TYPE_MASTER=   0x33,   //Master/Dinner/JCB/other foreign card
    CARD_TYPE_GIFT  =   0x34,
    CARD_TYPE_ALIPAY=   0x35,
    CARD_TYPE_WECHAT=   0x36,
}CARD_TYPE;

@end

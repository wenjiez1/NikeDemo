//
//  VFIBankSettleResponse.h
//  VFILibTest
//
//  Created by Verifone on 17/6/1.
//  Copyright © 2017年 Verifone. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VFIBankSettleResponse : NSObject

@property (nonatomic, retain) NSString *respCode;
@property (nonatomic, retain) NSString *MID;
@property (nonatomic, retain) NSString *TID;
@property (nonatomic, retain) NSString *merchCnName;
@property (nonatomic, retain) NSString *merchEnName;
@property (nonatomic, retain) NSString *operNo;
@property (nonatomic, retain) NSString *batchNo;
@property (nonatomic, retain) NSDate *tranDateTime;
@property (nonatomic, assign) char cupSettleFlag;
@property (nonatomic, retain) NSNumber *cupSaleNum;
@property (nonatomic, retain) NSNumber *cupSaleAmount;
@property (nonatomic, retain) NSNumber *cupRefundNum;
@property (nonatomic, retain) NSNumber *cupRefundAmount;
@property (nonatomic, assign) char foreignSettleFlag;
@property (nonatomic, retain) NSNumber *foreignSaleNum;
@property (nonatomic, retain) NSNumber *foreignSaleAmount;
@property (nonatomic, retain) NSNumber *foreignRefundNum;
@property (nonatomic, retain) NSNumber *foreignRefundAmount;
@property (nonatomic, retain) NSString *receipt;

@end

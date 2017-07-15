//
//  VFIBankSaleResponse.h
//  VFILib
//
//  Created by Verifone on 17/5/3.
//  Copyright © 2017年 Verifone. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VFIBankSaleResponse : NSObject

@property (nonatomic, retain) NSString *respCode;
@property (nonatomic, retain) NSString *merName;
@property (nonatomic, retain) NSString *MID;
@property (nonatomic, retain) NSString *TID;
@property (nonatomic, retain) NSNumber *operNo;
@property (nonatomic, retain) NSString *issueCode;
@property (nonatomic, retain) NSString *acqCode;
@property (nonatomic, retain) NSString *cardExp;
@property (nonatomic, retain) NSString *cardNo;
@property (nonatomic, retain) NSString *transType;
@property (nonatomic, retain) NSNumber *batchNo;
@property (nonatomic, retain) NSNumber *sysTrace;
@property (nonatomic, retain) NSString *authCode;
@property (nonatomic, retain) NSString *refCode;
@property (nonatomic, retain) NSDate *tranDateTime;
@property (nonatomic, retain) NSNumber *amount;
@property (nonatomic, retain) NSString *serialNo;
@property (nonatomic, retain) NSString *receipt;

@end

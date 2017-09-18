//
//  VFIUtils.h
//  GapTest
//
//  Created by Verifone on 17/1/9.
//  Copyright © 2017年 xintian. All rights reserved.
//

#import <Foundation/Foundation.h>

#define STX   0x02
#define ETX   0x03
#define SEPARATOR 0x1c

#define CMD_SALE "01"
#define CMD_VOID "02"
#define CMD_REFUND "03"
#define CMD_BALANCE "04"
#define CMD_SCANBAR "05"
#define CMD_SCANBAR_CLOSE "06"
#define CMD_LOGON "51"
#define CMD_SETTLE "52"
#define CMD_DOWNLOAD_CAPK "53"
#define CMD_DOWNLOAD_AID  "54"
#define CMD_REPRINT_66    "66"
#define CMD_REPRINT_69    "69"
#define CMD_GET_CARDINFO  "70"
#define CMD_RESET_DEVICE  "71"
#define CMD_SET_RSAPUBLICKEY "72"
#define CMD_TEST "99"
#define CMD_GETBATTERYCAP "C1"
#define CMD_GETAPPVER "C2"
#define CMD_GETDEVICEINFO "C3"
#define CMD_ACTIVE        "C6"
#define CMD_INACTIVE      "C7"


typedef enum{
    MainApp=0x00,
    BankApp=0x01,
    PostApp=0x88,
    GiftApp=0x20
}APPTYPE;
typedef enum
{
    TEST_REQ  = 0x01,
    TEST_RESP = 0x02,
    CASHIER_REQ = 0x03,
    CASHIER_RESP= 0x04,
    CENTER_REQ  = 0x05,
    CENTER_RESP = 0x06,
    POS_REQ = 0x07,
    POS_RESP = 0x08	
}PacketPath;

@interface VFIUtils : NSObject

+(int) VFIUtils_CalcLrc:(unsigned char*)inData withLength:(NSInteger)iDataLen;

+(bool)VFIUtils_Asc2Bcd:(unsigned char*)AscBuf to:(unsigned char*)BcdBuf with:(int)Len;

+(BOOL)VFIUtils_Bcd2Asc:(unsigned char*)BcdBuf to:(unsigned char*)AscBuf with:(unsigned short)Len;

+(BOOL)VFIUtils_GetID:(unsigned char*)ID;

+(bool)VFIUtils_isValidDataPackage:(unsigned char*)inData withLength:(NSInteger)iDataLen;

@end

@interface StringUtil : NSObject

+(NSString*) nsdata2HexStr:(NSData*) data;
+(NSData*) hexStr2NSData:(const NSString*) hexStr;

@end


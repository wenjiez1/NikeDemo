//
//  VFIDeviceMgr.h
//  VFILib
//
//  Created by Verifone on 17/1/16.
//  Copyright © 2017年 Verifone. All rights reserved.
//  Modify by wenjie/qiuyang 2017/3/24
//

#import <Foundation/Foundation.h>
#import "VFIBankCardResponse.h"
#import "VFIBankSettleResponse.h"
#import "UMSConnectAPI.h"

#define VFI_LIBVER  "01.00.01"

enum VFI_ERROR{
    // general error codes
    VFI_OK                     =  0,    /**< no error */
    VFI_UNSUPPORTED            = -1,    /**< function is not supported  */
    VFI_FAIL                   = -2,    /**< function failed (generic error) */
    VFI_TIMEOUT                = -3,    /**< timeout occured */
    VFI_INVALID_PARAM          = -4,    /**< invalid parameters passed, e.g. NULL pointer for mandatory parameter */
    VFI_INVALID_OPTION         = -5,    /**< invalid option specified */
    
    //tcp communication error code
    VFI_SOCKET_CREATE_FAIL      =-100,
    VFI_SOCKET_CONNECT_FAIL     =-101,
    VFI_SOCKET_SEND_FAIL        =-102,
    VFI_SOCKET_RECIEVE_FAIL     =-103,
    VFI_SOCKET_RECIEVE_TIMEOUT  =-104,
};
enum CARD_CATEGORY{
    TRAN_CREDIT             =   1,  //Credit/Debit
    TRAN_POSTONG            =   2,  //Alipay/Wechat
    TRAN_GIFT               =   3,  //Gift Card
};
	
@protocol VFIDeviceDelegate <NSObject>

@optional
-(void)vfi_operateDeviceResult:(char*)respCode withResultData:(NSString*)respMsg;
-(void)vfi_barDeviceCloseResult:(char*)respCode withResultData:(NSString*)respMsg;
-(void)vfi_barStartScanResult:(char*)respCode withRespMsg:(NSString*)respMsg andWithOutBarcode:(NSString*) barcode;
-(void)vfi_getCardInfoResult:(char*)respCode respMsg:(NSString*)respMsg isEncrypt:(BOOL)isEncryptData cardNo:(NSData*)pan expMonth:(NSString*)month expYear:(NSString*)year;
-(void)vfi_ResetDeviceResult:(char*)respCode withResultData:(NSString*)respData;
-(void)vfi_setRsaPublicKeyResult:(char*)respCode withResultData:(NSString*)respData;
-(void)vfi_getBatteryCapResult:(char*)respCode withRespMsg:(NSString*)respMsg withResultData:(NSString *)batteryCap;
-(void)vfi_getFirmwareVerResult:(char*)respCode withRespMsg:(NSString*)respMsg withResultData:(NSString *)firmwareVer;

/** Capture the result from the logon transaction return
 *
 *
 * \return none
 */
-(void)vfi_BankLoginResult:(char*)respCode withRespMsg:(NSString*)respMsg;

/** Capture the data from the sales transaction return
 *
 *
 * \return none
 */
-(void)vfi_BankSaleResult:(char*)respCode withRespMsg:(NSString*)respMsg andWithResponse:(VFIBankCardResponse*)response;

/** Capture the data from the void transaction return
 *
 *
 * \return none
 */
-(void)vfi_BankVoidResult:(char*)respCode withRespMsg:(NSString*)respMsg andWithResponse:(VFIBankCardResponse*)response;

/** Capture the data from the refund transaction return
 *
 *
 * \return none
 */
-(void)vfi_BankRefundResult:(char*)respCode withRespMsg:(NSString*)respMsg andWithResponse:(VFIBankCardResponse*)response;

/** Capture the data from the balance query transaction return
 *
 *
 * \return none
 */
-(void)vfi_BankBalanceResult:(char*)respCode withRespMsg:(NSString*)respMsg;

/** Capture the data from the settle transaction return
 *
 *
 * \return none
 */
-(void)vfi_BankSettleResult:(char*)respCode withRespMsg:(NSString*)respMsg andWithResponse:(VFIBankSettleResponse*)response;

/** Capture the data from the reprint transaction return
 *
 *
 * \return none
 */
-(void)vfi_BankRePrintResult:(char*)respCode withRespMsg:(NSString*)respMsg andWithResponse:(VFIBankCardResponse*)response;

/** Capture the log data
 *
 *
 * \return none
 */
-(void)vfi_LogMessage:(NSString*)logMsg;

/** Capture the data from the gift sell card transaction return
 *
 *
 * \return none
 */
-(void)vfi_GiftSellCardResult:(char*)respCode withRespMsg:(NSString*)respMsg andWithResponse:(VFIBankCardResponse*)response;

/** Capture the data from the gift void sell card transaction return
 *
 *
 * \return none
 */
-(void)vfi_GiftVoidSellCardResult:(char*)respCode withRespMsg:(NSString*)respMsg andWithResponse:(VFIBankCardResponse*)response;

@end

@interface VFIDeviceMgr : NSObject

@property (nonatomic,retain) NSString *bankServerIP;
@property (nonatomic,assign) int bankServerPort;
@property (nonatomic,assign) ConnectionMode certificateType;
@property (nonatomic,retain) NSString *posTongServerIP;
@property (nonatomic,assign) int posTongServerPort;
@property (nonatomic,retain) NSString *giftServerIP;
@property (nonatomic,assign) int giftServerPort;
@property (nonatomic,assign) bool isLogOutput;

@property(nonatomic,assign) id<VFIDeviceDelegate>delegate;

+(VFIDeviceMgr*)sharedInstance;
-(int)vfi_barDeviceClose;
-(int)vfi_barStartScan;
-(int)vfi_getCardInfo:(BOOL)isEncryptCardNo;
-(int)vfi_ResetDevice;
-(int)vfi_setRsaPublicKey:(NSString*)rsaPublicKey;
-(int)vfi_getBatteryCap;
-(int)vfi_getFirmwareVer;
-(int)vfi_getBatteryCapEx:(NSString **)respBatteryCap;
-(int)vfi_getFirmwareVerEx:(NSString **)respFirmwareVer;
-(int)vfi_getVFILibVer:(NSString **)respVFILibVer;

/** connect device
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_DeviceConnect;

/** invoke the function of E355, to do bank card logon transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_Bank_Login:(enum CARD_CATEGORY)category;

/** invoke the function of E355, to do bank card sales transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_Bank_Sale:(enum CARD_CATEGORY)category amount:(NSNumber *)amount cashierSysNo:(NSString *)cashierSysNo;

/** invoke the function of E355, to do bank card void transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_Bank_Void:(enum CARD_CATEGORY)category orgSysNo:(NSString *)systraceNo cashierSysNo:(NSString *)cashierSysNo;

/** invoke the function of E355, to do bank card refund transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_Bank_Refund:(enum CARD_CATEGORY)category amount:(NSNumber*)amount orgTranDate:(NSString*)orgTranDate orgRefNo:(NSString *)orgRefNo cashierSysNo:(NSString *)cashierSysNo;

/** invoke the function of E355, to do bank card settle transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_Bank_Settle:(enum CARD_CATEGORY)category;

/** invoke the function of E355, to do bank card rePrint transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_Bank_RePrint:(enum CARD_CATEGORY)category orgSysNo:(NSString *)systraceNo;

/** invoke the function of E355, to do bank card balance transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_Bank_Balance:(enum CARD_CATEGORY)category;

/** invoke the function of E355, to do gift card active transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_GiftSellCard:(NSNumber *)amount cashierSysNo:(NSString *)cashierSysNo;

/** invoke the function of E355, to do gift card inactive transaction
 *
 *
 * result on success: VFI_OK
 *        on failure: VFI_FAIL
 */
-(int)vfi_GiftVoidSellCard:(NSNumber *)amount cashierSysNo:(NSString *)cashierSysNo;

#pragma mark - test
-(bool)vfi_settleBankTranRespData:(NSData *)inData outRescode:(NSData *__autoreleasing *)respCode outRespMsg:(NSString *__autoreleasing *)respMsg outBankTranResp:(VFIBankCardResponse**)bankTranResp;
-(void)vfi_formBankTranPrnData:(VFIBankCardResponse**)bankCardResponse;


@end

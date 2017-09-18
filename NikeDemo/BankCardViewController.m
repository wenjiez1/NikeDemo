//
//  BankCardViewController.m
//  NikeDemo
//
//  Created by Verifone on 17/6/8.
//  Copyright © 2017年 Verifone. All rights reserved.
//

#import "BankCardViewController.h"
#import "VFIDeviceMgr.h"

@interface BankCardViewController ()<VFIDeviceDelegate,UITextFieldDelegate>{
    VFIDeviceMgr *mDeviceMgr;
}

@property (weak, nonatomic) IBOutlet UITextView *mTextView;
@property (weak, nonatomic) IBOutlet UITextField *orgSysNo;
@property (weak, nonatomic) IBOutlet UITextView *logTextView;
@property (weak, nonatomic) IBOutlet UITextField *inputAmount;
@property (weak, nonatomic) IBOutlet UITextField *orgRefNo;
@property (weak, nonatomic) IBOutlet UITextField *orgTranDate;
@property (weak, nonatomic) IBOutlet UITextField *orderNo;

@end

@implementation BankCardViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    mDeviceMgr=[VFIDeviceMgr sharedInstance];
    [mDeviceMgr setBankServerIP:@"210.22.91.77"];
    [mDeviceMgr setBankServerPort:5201];
    [mDeviceMgr setCertificateType:ConnectionModeNoSSL];
    [mDeviceMgr setPosTongServerIP:@"210.22.91.77"];
    [mDeviceMgr setPosTongServerPort:5588];
    [mDeviceMgr setGiftServerIP:@"210.22.91.77"];
    [mDeviceMgr setGiftServerPort:9210];
    mDeviceMgr.isLogOutput=YES;
    _orgSysNo.delegate=self;
    _orgRefNo.delegate=self;
    _orgTranDate.delegate=self;
    _inputAmount.delegate=self;
    _mTextView.editable=NO;
    _logTextView.editable=NO;
    _orderNo.delegate=self;
}
-(void)viewWillAppear:(BOOL)animated{
    mDeviceMgr.delegate=self;
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
-(BOOL)textFieldShouldReturn:(UITextField *)textField{
    [_orgSysNo resignFirstResponder];
    [_orgTranDate resignFirstResponder];
    [_orgRefNo resignFirstResponder];
    [_inputAmount resignFirstResponder];
    [_orderNo resignFirstResponder];
    return YES;
}
- (IBAction)BankSale:(UIButton *)sender {
    NSNumber *amount=[NSNumber numberWithInteger:[_inputAmount.text integerValue]];
    [mDeviceMgr vfi_Bank_Sale:TRAN_CREDIT amount:amount cashierSysNo:_orderNo.text];
}
-(void)vfi_BankSaleResult:(char *)respCode withRespMsg:(NSString *)respMsg andWithResponse:(VFIBankCardResponse *)response
{
    
    NSString *str=[NSString stringWithFormat:@"respCode:%s,respMsg:%@,reciept:%@",respCode,respMsg,response.receipt];
    [_mTextView setText:str];
    
}
- (IBAction)Logon:(UIButton *)sender {
    [mDeviceMgr vfi_Bank_Login:TRAN_CREDIT];
}
-(void)vfi_BankLoginResult:(char *)respCode withRespMsg:(NSString *)respMsg{
    NSString *str=[NSString stringWithFormat:@"签到\n retCode:%s,%@",respCode,respMsg];
    [_mTextView setText:str];
}

- (IBAction)Void:(UIButton *)sender {
    [mDeviceMgr vfi_Bank_Void:TRAN_CREDIT orgSysNo:_orgSysNo.text cashierSysNo:_orderNo.text];
}
-(void)vfi_BankVoidResult:(char *)respCode withRespMsg:(NSString *)respMsg andWithResponse:(VFIBankCardResponse *)response{
    NSString *str=[NSString stringWithFormat:@"撤销\nretCode:%s,%@,receipt:%@",respCode,respMsg,response.receipt];
    [_mTextView setText:str];
}
- (IBAction)BankRefund:(id)sender {
    
    NSNumber *amount=[NSNumber numberWithLong:[_inputAmount.text integerValue]];
    [mDeviceMgr vfi_Bank_Refund:TRAN_CREDIT amount:amount orgTranDate:_orgTranDate.text orgRefNo:_orgRefNo.text cashierSysNo:_orderNo.text];
}
-(void)vfi_BankRefundResult:(char *)respCode withRespMsg:(NSString *)respMsg andWithResponse:(VFIBankCardResponse *)response{
    NSString *str=[NSString stringWithFormat:@"退货\nretCode:%s,%@,receipt:%@",respCode,respMsg,response.receipt];
    [_mTextView setText:str];
}

- (IBAction)Settle:(UIButton *)sender {
    [mDeviceMgr vfi_Bank_Settle:TRAN_CREDIT];
}
-(void)vfi_BankSettleResult:(char *)respCode withRespMsg:(NSString *)respMsg andWithResponse:(VFIBankSettleResponse *)response{
    NSString *str=[NSString stringWithFormat:@"结算\n retCode:%s,%@,reciept:%@",respCode,respMsg,response.receipt];
    [_mTextView setText:str];
}
-(void)vfi_LogMessage:(NSString *)logMsg{
    static NSString *str=@"";
    str=[str stringByAppendingString:logMsg];
    [_logTextView setText:str];

}


@end

//
//  PosTongViewController.m
//  NikeDemo
//
//  Created by Verifone on 17/6/16.
//  Copyright © 2017年 Verifone. All rights reserved.
//

#import "PosTongViewController.h"
#import "VFIDeviceMgr.h"

@interface PosTongViewController ()<VFIDeviceDelegate,UITextFieldDelegate>{
    VFIDeviceMgr *deviceMgr;
}
@property (weak, nonatomic) IBOutlet UITextView *mtextView;
@property (weak, nonatomic) IBOutlet UITextField *inputAmount;
@property (weak, nonatomic) IBOutlet UITextField *orgSysNo;
@property (weak, nonatomic) IBOutlet UITextField *orgRefNo;
@property (weak, nonatomic) IBOutlet UITextField *orgTranDate;
@property (weak, nonatomic) IBOutlet UITextView *logTextView;

@end

@implementation PosTongViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    deviceMgr=[VFIDeviceMgr sharedInstance];
    [deviceMgr setPosTongServerIP:@"210.22.91.77"];
    [deviceMgr setPosTongServerPort:5588];
    _logTextView.editable=NO;
    _inputAmount.delegate=self;
    _orgRefNo.delegate=self;
    _orgSysNo.delegate=self;
    _orgTranDate.delegate=self;
    _mtextView.editable=NO;
}
-(void)viewWillAppear:(BOOL)animated{
    deviceMgr.delegate=self;
    deviceMgr.isLogOutput=YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField{
    [_inputAmount resignFirstResponder];
    [_orgTranDate resignFirstResponder];
    [_orgSysNo resignFirstResponder];
    [_orgRefNo resignFirstResponder];
    return YES;
}
- (IBAction)PosTongLogin:(id)sender {
    [deviceMgr vfi_Bank_Login:TRAN_POSTONG];
}
- (IBAction)PosTongSale:(id)sender {
    NSNumber *amount=[NSNumber numberWithInteger:[_inputAmount.text integerValue]];
    NSDate *date=[NSDate new];
    NSDateFormatter *dateFormatter=[NSDateFormatter new];
    [dateFormatter setDateFormat:@"yyyyMMddHHmmss"];
    NSString *sysNo=[dateFormatter stringFromDate:date];
    sysNo=[sysNo stringByAppendingString:@"000000"];
    [deviceMgr vfi_Bank_Sale:TRAN_POSTONG amount:amount cashierSysNo:sysNo];
}
-(void)vfi_BankSaleResult:(char *)respCode withRespMsg:(NSString *)respMsg andWithResponse:(VFIBankCardResponse *)response{
    NSString *str=[NSString stringWithFormat:@"消费\n retCode:%s,%@,reciept:%@",respCode,respMsg,response.receipt];
    [_mtextView setText:str];
}
- (IBAction)PosTongVoid:(id)sender {
    NSDate *date=[NSDate new];
    NSDateFormatter *dateFormatter=[NSDateFormatter new];
    [dateFormatter setDateFormat:@"yyyyMMddHHmmss"];
    NSString *sysNo=[dateFormatter stringFromDate:date];
    sysNo=[sysNo stringByAppendingString:@"000000"];
    [deviceMgr vfi_Bank_Void:TRAN_POSTONG orgSysNo:_orgSysNo.text cashierSysNo:sysNo];
}
-(void)vfi_BankVoidResult:(char *)respCode withRespMsg:(NSString *)respMsg andWithResponse:(VFIBankCardResponse *)response{
    NSString *str=[NSString stringWithFormat:@"撤销\nretCode:%s,%@,receipt:%@",respCode,respMsg,response.receipt];
    [_mtextView setText:str];
}
- (IBAction)PosTongRefund:(id)sender {
    NSDate *date=[NSDate new];
    NSDateFormatter *dateFormatter=[NSDateFormatter new];
    [dateFormatter setDateFormat:@"yyyyMMddHHmmss"];
    NSString *sysNo=[dateFormatter stringFromDate:date];
    sysNo=[sysNo stringByAppendingString:@"000000"];
    
    NSNumber *amount=[NSNumber numberWithInteger:[_inputAmount.text integerValue]];
    [deviceMgr vfi_Bank_Refund:TRAN_POSTONG amount:amount orgTranDate:_orgTranDate.text orgRefNo:_orgRefNo.text cashierSysNo:sysNo];
}
-(void)vfi_BankRefundResult:(char *)respCode withRespMsg:(NSString *)respMsg andWithResponse:(VFIBankCardResponse *)response{
    NSString *str=[NSString stringWithFormat:@"退货\nretCode:%s,%@,receipt:%@",respCode,respMsg,response.receipt];
    [_mtextView setText:str];
}

- (IBAction)PosTongSettle:(id)sender {
    [deviceMgr vfi_Bank_Settle:TRAN_POSTONG];
}
-(void)vfi_LogMessage:(NSString *)logMsg{
    static NSString *str=@"";
    str=[str stringByAppendingString:logMsg];
    [_logTextView setText:str];
}


@end

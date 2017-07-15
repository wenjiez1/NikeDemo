//
//  PhaseOneViewController.m
//  NikeDemo
//
//  Created by Verifone on 17/6/8.
//  Copyright © 2017年 Verifone. All rights reserved.
//

#import "PhaseOneViewController.h"
#import "VFIDeviceMgr.h"

@interface PhaseOneViewController ()<VFIDeviceDelegate>
{
    VFIDeviceMgr *deviceMgr;

}
@property (weak, nonatomic) IBOutlet UITextView *mTextView;

@end

@implementation PhaseOneViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    deviceMgr=[VFIDeviceMgr sharedInstance];
    _mTextView.editable=NO;
    UIApplication *app=[UIApplication sharedApplication];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(willResignActive) name:UIApplicationWillResignActiveNotification object:app];
}
-(void)viewWillAppear:(BOOL)animated{
    deviceMgr.delegate=self;
}
-(void)willResignActive{
    [deviceMgr vfi_ResetDevice];
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
- (IBAction)StoreRsaKey:(UIButton *)sender {
    NSString *strRsa=[NSString stringWithString:@"CF71CF5216C782B2A6C28BA09070237D555549D11643A55C4C9B6C3C13A04AD3097D663B7988A2E611F764FBAD0189BD0D7465526D5F83A4494F48E0165843810348D9D9304C9D290F0ED22D5FB8EBC257B53471EB3807795BAE644FB373EB2A9F5A803B2DFBDD4BA67F9BD7C25B8B113C8C38645303568D7EEC942D42686F35"];
    [deviceMgr vfi_setRsaPublicKey:strRsa];
}
- (IBAction)GetE355Battery:(UIButton *)sender {
    [deviceMgr vfi_getBatteryCap];
}
- (IBAction)StopScanBar:(UIButton *)sender {
    [deviceMgr vfi_barDeviceClose];
}
- (IBAction)StartScanBar:(UIButton *)sender {
    [deviceMgr vfi_barStartScan];

}
- (IBAction)GetE355AppVer:(UIButton *)sender {
    [deviceMgr vfi_getFirmwareVer];

}
- (IBAction)GetiOSLibVer:(UIButton *)sender {
    NSString *str;
    [deviceMgr vfi_getVFILibVer:&str];
    [_mTextView setText:str];
}
- (IBAction)GetCardInfo:(UIButton *)sender {
    [deviceMgr vfi_getCardInfo:NO];
}
- (IBAction)GetDeviceInfo:(UIButton *)sender {
    NSString *str;
    [deviceMgr vfi_getBatteryCapEx:&str];
    [_mTextView setText:str];
}
- (IBAction)GetFirmVer:(UIButton *)sender {
    NSString *str;
    [deviceMgr vfi_getFirmwareVerEx:&str];
    [_mTextView setText:str];
}
-(void)vfi_getBatteryCapResult:(char *)respCode withRespMsg:(NSString *)respMsg withResultData:(NSString *)batteryCap{
    NSString *str=[NSString stringWithFormat:@"respCode:%s,respMsg:%@,batteryValue:%@",respCode,respMsg,batteryCap];
    [_mTextView setText:str];
}
-(void)vfi_getFirmwareVerResult:(char *)respCode withRespMsg:(NSString *)respMsg withResultData:(NSString *)firmwareVer{
    NSString *str=[NSString stringWithFormat:@"respCode:%s,respMsg:%@,E355AppVer:%@",respCode,respMsg,firmwareVer];
    [_mTextView setText:str];
}
-(void)vfi_pinpadMSRData:(NSString *)pan expMonth:(NSString *)month expYear:(NSString *)year{
    NSString *str=[NSString stringWithFormat:@"cardNo:%@,expYear:%@,expMonth:%@",pan,year,month];
    [_mTextView setText:str];
}
- (IBAction)ClearTextView:(UIButton *)sender {
    [_mTextView setText:nil];
}
-(void)vfi_getCardInfoResult:(char *)respCode respMsg:(NSString *)respMsg isEncrypt:(BOOL)isEncryptData cardNo:(NSData *)pan expMonth:(NSString *)month expYear:(NSString *)year{
    unsigned char aucCardNo[1024]={0};
    [pan getBytes:aucCardNo length:pan.length];
    
    NSString *str=[NSString stringWithFormat:@"cardNo:%s,respCode:%s,respMsg:%@,isEncryptData=%d,month:%@,year:%@",aucCardNo,respCode,respMsg,isEncryptData,month,year];
    [_mTextView setText:str];
}
-(void)vfi_setRsaPublicKeyResult:(char *)respCode withResultData:(NSString *)respData{
    NSString *str=[NSString stringWithFormat:@"respCode:%s,respMsg:%@",respCode,respData];
    [_mTextView setText:str];
}
-(void)vfi_barStartScanResult:(char *)respCode withRespMsg:(NSString *)respMsg andWithOutBarcode:(NSString *)barcode{
    NSString *str=[NSString stringWithFormat:@"respCode:%s,respMsg:%@,barcode:%@",respCode,respMsg,barcode];
    [_mTextView setText:str];
}
-(void)vfi_operateDeviceResult:(char *)respCode withResultData:(NSString *)respMsg{
    NSString *str;
    
    str=[NSString stringWithFormat:@"respCode:%s,respMsg:%@",respCode,respMsg];
    [_mTextView setText:str];
}


@end

# SLYJPaySDK

[![CI Status](http://img.shields.io/travis/yelon21/SLYJPaySDK.svg?style=flat)](https://travis-ci.org/yelon21/SLYJPaySDK)
[![Version](https://img.shields.io/cocoapods/v/SLYJPaySDK.svg?style=flat)](http://cocoapods.org/pods/SLYJPaySDK)
[![License](https://img.shields.io/cocoapods/l/SLYJPaySDK.svg?style=flat)](http://cocoapods.org/pods/SLYJPaySDK)
[![Platform](https://img.shields.io/cocoapods/p/SLYJPaySDK.svg?style=flat)](http://cocoapods.org/pods/SLYJPaySDK)

## Example

To run the example project, clone the repo, and run `pod install` from the Example directory first.

## Requirements

## Installation

SLYJPaySDK is available through [CocoaPods](http://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod 'SLYJPaySDK', '~> 2.2.5'
```

## Author

yelon21, yl21ly@qq.com

## License

SLYJPaySDK is available under the MIT license. See the LICENSE file for more info.

##SDK接入
使用pod库安装：

在Podfile文件中加入`pod 'SLYJPaySDK', '~> 2.2.2'`并执行`pod install`，如果版本不存在，需要执行`pod repo update`进行更新本地`repo`库后重试。

同时需要在info.plist文件中加入以下`key`用户获取相应权限：

1. 添加`NSLocationWhenInUseUsageDescription`，用于sdk获取定位信息
2. 在`UISupportedInterfaceOrientations`下添加`UIInterfaceOrientationLandscapeLeft`，用于允许界面横屏（电子签名页面）
3. 添加`NSBluetoothPeripheralUsageDescription`用于通过蓝牙与MPOS通讯

##1. 说明
用户使用此SDK前需要先提供其App的包名`bundleId`到后台备案，备案后下发`appKey`给用户用于后续操作。

Xcode配置：在使用target的Build Settings标签下的Other Linker Flags选项里面添加-ObjC。

>注：此SDK仅支持真机运行，不支持模拟器运行。
>支持iOS7.1或更高版本。##2. SDK使用使用此SDK必须保持网络畅通并且App的定位权限已开启,蓝牙访问权限已开启。        在使用时候会涉及到回调，此处使用block方式。

block定义如下：

```objective-c/**
 执行响应
 
 @param responseDic 响应的数据
 @param errorType 错误码
 @param errorString 响应的错误信息，如果是nil则表示成功，否则表示失败。
 
 错误码
 
 - YJErrorTypeNoError: 无错误
 - YJErrorTypeNotPermission: 未授权
 - YJErrorTypeNormalError: 一般错误，一般指接口返回信息
 - YJErrorTypeNoUserInfo: 没有用户信息
 - YJErrorTypeUserStatusDeny: 用户当前状态，无此操作权限
 - YJErrorTypeParameterInvalid: 参数有误
 - YJErrorTypeLocationIsOff: 定位未开启
 - YJErrorTypeLocationIsLocating: 正在定位

typedef NS_ENUM(NSUInteger, YJErrorType) {
    
    YJErrorTypeNoError,
    YJErrorTypeNotPermission,
    YJErrorTypeNormalError,
    YJErrorTypeNoUserInfo,
    YJErrorTypeUserStatusDeny,
    YJErrorTypeParameterInvalid,
    YJErrorTypeLocationIsOff,
    YJErrorTypeLocationIsLocating,
};
 */
typedef void(^ResponseBlock)(NSDictionary *responseDic,YJErrorType errorType,NSString *errorString);```

###2.1 基础功能

####2.1.1 代理

如需自己实现消息提示，请设置
```
/**
 设置delegate
 
 @param delegate   delegate
 */
+ (void)setSDKDelegete:(id<YJCardPayDelegate>)delegate;
```
####2.1.1 启动百度定位引擎

只有启动定位服务才能进行正常交易

```/**
 启动百度定位引擎
 
 @param key   百度地图ak，可通过 http://lbsyun.baidu.com/apiconsole/key 进行添加
 @return BOOL 百度定位引擎启动结果
 */
+ (BOOL)startWithBaiDuKey:(NSString *)key;```
####2.1.2 授权认证
只有授权成功才能进行后续流程。
```/** 认证  @param key           下发给合作商的key @param responseBlock 回调 */+ (void)startWithKey:(NSString *)key       responseBlock:(ResponseBlock)responseBlock;```
###2.2 用户信息####2.2.1 用户信息查询
在授权成功后必须先获取用户信息，然后才能进行其他用户相关操作。

<font color=#ff0000 size=3>重要：以下情况必须调用，以达到信息同步。

<!--1. 切换用户后必须调用-->

2. 登陆成功后必须调用

<!--3. App启动后必须调用。-->

</font>
暂不支持虚拟运营商号段

```/** 获取用户信息  @param phone         用户手机号 @param responseBlock 回调 cashCardFlag:是否已绑定出款卡 certPid:身份证号 realName:用户姓名 mobileNo:用户手机号 authenFlag:认证状态
 remark:实名认证驳回原因 
 说明： authenFlag -> 0:初始状态，1：已完善信息，2：已提交实名认证，3：实名认证通过，4：认证失败，5：上传中（暂无） cashCardFlag -> 0:未绑定 1：已绑定 */+ (void)queryUserInfo:(NSString *)phone        responseBlock:(ResponseBlock)responseBlock;```
####2.2.2 用户信息保存在获取用户信息后，判定用户状态`authenFlag`为0或1或4的时候才可以进行用户信息修改保存。否则不可以保存。

```/**
 保存用户信息
 
 @param phone         用户手机号
 @param userName      用户姓名
 @param certPid       用户身份证号
 @param responseBlock 回调
 */
+ (void)saveUserInfo:(NSString *)phone
            userName:(NSString *)userName
             certPid:(NSString *)certPid
       responseBlock:(ResponseBlock)responseBlock```
####2.2.3 用户实名认证照片上传
在获取用户信息后，判定用户状态`authenFlag`为1或4的时候才可以进行用户实名认证照片上传，否则不可以保存。

**注意：实名认证照片必须实时拍照获取，不可以从相册或者其他方式获取，以防ps等作假。**

**另外：拍照完毕后，为防止图片变形失真，如果压缩必须等比例压缩且最大边长不小于600pt。**
    
```/**
 实名认证照片上传
 
 @param phone         用户手机号
 @param userImage     手持身份证正面照片
 @param frontImage    身份证正面照片
 @param backImage     身份证反面照片
 @param responseBlock 回调
 */
+ (void)uploadUserAuthenImage:(NSString *)phone
                    userImage:(UIImage *)userImage
                identityFront:(UIImage *)frontImage
                 identityBack:(UIImage *)backImage
                responseBlock:(ResponseBlock)responseBlock
```###2.3 出款卡####2.3.1 出款卡保存
绑定出款卡必须确保实名认证已完成，即：`authenFlag`为3，且绑定卡的**持卡人姓名**必须与**实名认证的姓名**一致。否则无法出款。
```/**
 绑定出款卡
 
 @param phone         用户手机号
 @param userName      持卡人姓名，必须与当前用户一致
 @param cardNo         卡号
 @param bankId         银行id
 @param bankBranchId   支行id
 @param bankProvinceId 省份id
 @param bankCityId     城市id
 @param responseBlock  回调
 */
+ (void)saveCashCardInfo:(NSString *)phone
               userName:(NSString *)userName
                 cardNo:(NSString *)cardNo
                 bankId:(NSString *)bankId
           bankBranchId:(NSString *)bankBranchId
         bankProvinceId:(NSString *)bankProvinceId
             bankCityId:(NSString *)bankCityId
          responseBlock:(ResponseBlock)responseBlock;```
####2.3.2 出款卡查询
```/**
 查询出款卡
 
 @param phone         用户手机号
 @param responseBlock 回调
 */
+ (void)queryCashCard:(NSString *)phone
        responseBlock:(ResponseBlock)responseBlock```
####2.3.3 出款卡删除
```/**
 解绑出款卡
 
 @param phone         用户手机号
 @param cardId        银行卡id
 @param responseBlock 回调
 */
+ (void)deleteCashCard:(NSString *)phone
                cardId:(NSString *)cardId
         responseBlock:(ResponseBlock)responseBlock;```
####2.3.4 可绑定银行列表查询
```/**
 获取可绑定银行列表
 
 @param phone         用户手机号
 @param responseBlock 回调
 bankId:银行id
 bankName:银行名称
 bankIcon:银行logo
 */
+ (void)queryCanBindBankList:(NSString *)phone
               responseBlock:(ResponseBlock)responseBlock;```
####2.3.5 省份列表查询
```/** 获取省份列表  @return 省份列表 @example
 [{"id":"310000","name":"上海市"}] id id name 省份名称 */+ (NSArray *)getProvinceList;```
####2.3.6 城市列表查询
```/** 获取城市列表  @param pid 省份id @return 城市列表
 
 @example 
 {"id":"310000","name":"上海市","pid":"310000"} 
 id 城市id pid 省份id name 城市名称 */+ (NSArray *)getCityListByProvinceId:(NSString *)pid;```
####2.3.7 支行列表查询
如果所查询的支行不存在，可以任意选择支行
```/**
 查询支行列表
 
 @param phone         用户手机号
 @param bankId        银行id
 @param provinceId    省份id
 @param cityId        城市id
 @param keyWord       模糊查询关键字
 @param responseBlock 回调
 
 bankBranchName:支行名称
 bankBranchId:支行id
 bankId:银行id
 bankIcon:银行logo
 */
+ (void)queryCanBindBranchBankList:(NSString *)phone
                            bankId:(NSString *)bankId
                        provinceId:(NSString *)provinceId
                            cityId:(NSString *)cityId
                           keyWord:(NSString *)keyWord
                     responseBlock:(ResponseBlock)responseBlock```###2.4 支付####2.4.1 刷卡支付发起支付必须保证实名认证已完成，即：`authenFlag`为3，并且收款方已经绑定出款卡，否则会在收款方绑定出款卡后延迟出款。
```/**
 支付
 
 @param phone          用户手机号
 @param toUserPhone    收款人手机号
 @param orderId        第三方订单id 或 者订单唯一标识
 @param amount         金额 单位为分 <=5000000
 @param payType        支付方式
 @param settlementType 结算方式
 @param responseBlock  回调
 
 typedef NS_ENUM(NSUInteger, YJPayToolType) {
 YJPayToolTypeDefault = 01,
 YJPayToolTypeCardPay = YJPayToolTypeDefault//刷卡支付
 };
 
 typedef NS_ENUM(NSUInteger, YJSettlementType) {
 YJSettlementTypeTO,//TO 结算
 YJSettlementTypeT1//T1 结算
 };
  商品类型
typedef NS_ENUM(NSUInteger, YJMerchantType) {
    YJMerchantTypeSE,//超市电器类
    YJMerchantTypeCA,//服装百货类
    YJMerchantTypeHD,//酒店餐饮类
    YJMerchantTypeJE,//珠宝娱乐类
    YJMerchantTypeCAR,//汽车消费类
};
 */
+ (void)startPay:(NSString *)phone
     toUserPhone:(NSString *)toUserPhone
         orderId:(NSString *)orderId
          amount:(NSString *)amount
         payType:(YJPayToolType)payType
  settlementType:(YJSettlementType)settlementType
    merchantType:(YJMerchantType)merchantType
   responseBlock:(ResponseBlock)responseBlock;```
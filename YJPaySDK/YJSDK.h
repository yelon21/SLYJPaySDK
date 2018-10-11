//
//  YJSDK.h
//  YJPay
//
//  Created by yelon on 16/10/26.
//  Copyright © 2016年 yelon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>
#import "YJPayDefine.h"

/**
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
typedef void(^ResponseBlock)(NSDictionary *responseDic,YJErrorType errorType,NSString *errorString);

@interface YJSDK : NSObject

+ (NSString *)version;
/**
 设置delegate
 
 @param delegate   delegate
 */
+ (void)setSDKDelegete:(id<YJCardPayDelegate>)delegate;
/**
 启动百度定位引擎
 
 @param key   百度key
 */
+ (void)startWithBaiDuKey:(NSString *)key;
/**
 认证
 
 @param key           下发给合作商的key
 @param responseBlock 回调
 */
+ (void)startWithKey:(NSString *)key
       responseBlock:(ResponseBlock)responseBlock;

#pragma mark 用户信息 相关
/**
 获取用户信息
 
 @param phone         用户手机号
 @param responseBlock 回调
 
 cashCardFlag:是否已绑定出款卡
 certPid:身份证号
 realName:用户姓名
 mobileNo:用户手机号
 authenFlag:认证状态
 
 authenFlag -> 0:初始状态，1：已完善信息，2：已提交实名认证，3：实名认证通过，4：认证失败，5：上传中（暂无）
 cashCardFlag -> 0:未绑定 1：已绑定
 */
+ (void)queryUserInfo:(NSString *)phone
        responseBlock:(ResponseBlock)responseBlock;

/**
 保存用户信息
 
 @param phone         用户手机号
 @param userName      用户姓名
 @param certPid       用户身份证号
 @param responseBlock 回调
 */
+ (void)saveUserInfo:(NSString *)phone
            userName:(NSString *)userName
             certPid:(NSString *)certPid
       responseBlock:(ResponseBlock)responseBlock;

/**
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
                responseBlock:(ResponseBlock)responseBlock;

/**
 自助实名认证状态查询
 
 如果用户信息中authenFlag 状态为0或1，可以进行此查询
 
 @param phone         用户手机号
 @param responseBlock 回调
 返回参数：
 authStatus
 0：未进行自助实名流程，可以进行人工信息保存或自助上传身份证步骤
 1：自助实名流程已完成第一步（认证了身份证），可以进行人脸识别或上传手持照片
 2：自助实名不可用
 */
+ (void)queryAutoAuthenStatus:(NSString *)phone
                responseBlock:(ResponseBlock)responseBlock;

/**
 身份证图片信息识别
 
 @param phone     用户手机号
 @param cardImage 身份证照片
 @param imageType 身份证照片类型
 @param responseBlock 回调
 */
+ (void)recognizerUser:(NSString *)phone
             cardImage:(UIImage *)cardImage
             imageType:(YJIdImageType)imageType
         responseBlock:(ResponseBlock)responseBlock;

/**
 自助实名认证保存用户信息
 
 @param phone         用户手机号
 @param cardImageHead 身份证人像面
 @param cardImageGuoHui 身份证h国徽面
 @param userName      用户姓名
 @param certPid       用户身份证号
 @param startDateString 身份证有效期始
 @param endDateString 身份证有效期止
 @param responseBlock 回调
 */
+ (void)saveAutoUserInfo:(NSString *)phone
           cardImageHead:(UIImage *)cardImageHead
         cardImageGuoHui:(UIImage *)cardImageGuoHui
                userName:(NSString *)userName
                 certPid:(NSString *)certPid
         startDateString:(NSString *)startDateString
           endDateString:(NSString *)endDateString
           responseBlock:(ResponseBlock)responseBlock;
/**
 活体验证
 
 @param phone     用户手机号
 @param fromViewController  当前ViewController
 @param responseBlock 回调
 status 对应 YJFaceResultType
 */
+ (void)verifyLivingBody:(NSString *)phone
      fromViewController:(UIViewController *)fromViewController
           responseBlock:(ResponseBlock)responseBlock;
#pragma mark 高级认证
/**
 高级认证
 
 @param phone         当前用户登录手机号
 @param userName      当前用户姓名
 @param cardNo        用户所持有信用卡号
 @param bankMobileNo  银行卡预留手机号
 @param responseBlock 回调
 */
+ (void)verifyUserCreditCardInfo:(NSString *)phone
                        userName:(NSString *)userName
                          cardNo:(NSString *)cardNo
                    bankMobileNo:(NSString *)bankMobileNo
                   responseBlock:(ResponseBlock)responseBlock;

#pragma mark 银行卡相关
#pragma mark 出款银行卡相关
/**
 获取省份列表
 
 @return 省份列表
 
@example
 {"id":"310000","name":"上海市"}
 id id
 name 省份名称
 */

+ (NSArray *)getProvinceList;

/**
 获取城市列表
 
 @param pid 省份id
 
 @return 城市列表
 @example
 {"id":"310000","name":"上海市","pid":"310000"}
 id 城市id
 pid 省份id
 name 城市名称
 */
+ (NSArray *)getCityListByProvinceId:(NSString *)pid;

/**
 获取可绑定银行列表
 
 @param phone         用户手机号
 @param responseBlock 回调
 bankId:银行id
 bankName:银行名称
 bankIcon:银行logo
 */
+ (void)queryCanBindBankList:(NSString *)phone
               responseBlock:(ResponseBlock)responseBlock;

/**
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
                     responseBlock:(ResponseBlock)responseBlock;

/**
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
          responseBlock:(ResponseBlock)responseBlock;

/**
 解绑出款卡
 
 @param phone         用户手机号
 @param cardId        银行卡id
 @param responseBlock 回调
 */
+ (void)deleteCashCard:(NSString *)phone
                cardId:(NSString *)cardId
         responseBlock:(ResponseBlock)responseBlock;

/**
 查询出款卡
 
 @param phone         用户手机号
 @param responseBlock 回调
 */
+ (void)queryCashCard:(NSString *)phone
        responseBlock:(ResponseBlock)responseBlock;

#pragma mark 支付
/**
 支付
 
 @param phone          用户手机号
 @param toUserPhone   收款人手机号
 @param orderId        第三方订单id 或 者订单唯一标识
 @param amount         金额 单位为分 <=5000000
 @param specialMerchant 精选商户
 @param payType        支付方式
 @param settlementType 结算方式
 @param merchantType   商品类型
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
**/

+ (void)startPay:(NSString *)phone
     toUserPhone:(NSString *)toUserPhone
         orderId:(NSString *)orderId
          amount:(NSString *)amount
 specialMerchant:(BOOL)specialMerchant
         payType:(YJPayToolType)payType
  settlementType:(YJSettlementType)settlementType
    merchantType:(YJMerchantType)merchantType
   responseBlock:(ResponseBlock)responseBlock;

/**
 启动终端激活
 
 @param phone        当前用户手机号
 @param terminalAmountBlock 终端金额冻结和继续事件
 @param responseBlock 回调
 terminalAmountBlock 回调两个参数 amount：金额 和 continueActionBlock继续流程的block
 当需要继续后续流程时候 调用continueActionBlockI()即可
 */
+(void)startTerminalActive:(NSString *)phone
       terminalAmountBlock:(void(^)(NSString *amount,dispatch_block_t continueActionBlock))terminalAmountBlock
             responseBlock:(ResponseBlock)responseBlock;
@end

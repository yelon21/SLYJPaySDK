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
 启动百度定位引擎
 
 @param key   百度key
 @return BOOL 百度定位引擎启动结果
 */
+ (BOOL)startWithBaiDuKey:(NSString *)key;
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
         payType:(YJPayToolType)payType
  settlementType:(YJSettlementType)settlementType
    merchantType:(YJMerchantType)merchantType
   responseBlock:(ResponseBlock)responseBlock;

@end

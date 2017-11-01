//
//  YJPayDefine.h
//  Pods
//
//  Created by yelon on 2017/10/30.
//
//

#ifndef YJPayDefine_h
#define YJPayDefine_h

#define LTLog(fmt, ...) nil
#ifndef LTLog
#define LTLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif
/**
 支付方式
 
 - YJPayToolTypeDefault: 默认方式
 - YJPayToolTypeCardPay: 刷卡支付
 */
typedef NS_ENUM(NSUInteger, YJPayToolType) {
    YJPayToolTypeDefault = 01,
    YJPayToolTypeCardPay = YJPayToolTypeDefault
};

/**
 结算方式
 
 - YJSettlementTypeTO: T0结算
 - YJSettlementTypeT1: T1结算
 */
typedef NS_ENUM(NSUInteger, YJSettlementType) {
    YJSettlementTypeTO,//TO 结算
    YJSettlementTypeT1//T1 结算
};

/**
 错误码
 
 - YJErrorTypeNoError: 无错误
 - YJErrorTypeNotPermission: 未授权
 - YJErrorTypeNormalError: 一般错误，一般指接口返回信息
 - YJErrorTypeUserInfoError: 没有用户信息
 - YJErrorTypeUserStatusDeny: 用户当前状态，无此操作权限
 - YJErrorTypeParameterInvalid: 参数有误
 - YJErrorTypeLocationIsOff: 定位未开启
 - YJErrorTypeLocationIsLocating: 正在定位
 */
typedef NS_ENUM(NSUInteger, YJErrorType) {
    
    YJErrorTypeNoError,
    YJErrorTypeNotPermission,
    YJErrorTypeNormalError,
    YJErrorTypeUserInfoError,
    YJErrorTypeUserStatusDeny,
    YJErrorTypeParameterInvalid,
    YJErrorTypeLocationIsOff,
    YJErrorTypeLocationIsLocating,
};

#define YJMessage_NotPermission @"未授权"
#define YJMessage_UserInfoError @"请先获取用户信息"

#endif /* YJPayDefine_h */

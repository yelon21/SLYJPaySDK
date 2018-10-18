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
pod 'SLYJPaySDK'
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
>支持iOS8.0或更高版本。
#
# Be sure to run `pod lib lint SLYJPaySDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'SLYJPaySDK'
  s.version          = '1.0'
  s.summary          = 'SLYJPaySDK.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: SLYJPaySDK.
                       DESC

  s.homepage         = 'https://github.com/yelon21/SLYJPaySDK'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'yelon21' => 'yl21ly@qq.com' }
  s.source           = { :git => 'https://github.com/yelon21/SLYJPaySDK.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '7.1'

  s.source_files = 'YJPaySDK/*'
  s.resource     = "Assets/*.{bundle,storyboardc,png}"
  s.vendored_libraries = '**/*.a'
  s.libraries    = "stdc++"
  
  # s.resource_bundles = {
  #   'SLYJPaySDK' => ['SLYJPaySDK/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end

import UIKit
import Flutter

@UIApplicationMain
@objc class AppDelegate: FlutterAppDelegate {
  override func application(
    _ application: UIApplication,
    didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

    let controller : FlutterViewController = window?.rootViewController as! FlutterViewController
    let сhannel = FlutterMethodChannel(name: "example.com/gomobileNative",
                                              binaryMessenger: controller.binaryMessenger)
    сhannel.setMethodCallHandler({
      [weak self] (call: FlutterMethodCall, result: FlutterResult) -> Void in
  if call.method == "getBirdsList"  {
            

    result([91, 34, 83, 112, 97, 114, 114, 111, 119, 34, 44, 34, 80, 105, 103, 101, 111, 110, 34, 44, 34, 72, 101, 114, 111, 110, 34, 93])
  }

  else if call.method == "getRandomNumber"  {
    result(13)
  }

  else if call.method == "getBirdInfo"  {
    result([123, 34, 98, 105, 114, 100, 84, 121, 112, 101, 34, 58, 34, 83, 112, 97, 114, 114, 111, 119, 34, 44, 34, 119, 104, 97, 116, 32, 105, 116, 32, 100, 111, 101, 115, 34, 58, 34, 108, 105, 107, 101, 115, 32, 116, 111, 32, 101, 97, 116, 32, 115, 101, 101, 100, 34, 125])
  }
  else {
  result(FlutterMethodNotImplemented)
  }
    })

    GeneratedPluginRegistrant.register(with: self)
    return super.application(application, didFinishLaunchingWithOptions: launchOptions)
  }
}
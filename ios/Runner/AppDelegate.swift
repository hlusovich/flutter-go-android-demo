import UIKit
import Flutter
import GomobileNative


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
      let instance = GomobileNativeGoMobileLib()

  if call.method == "getBirdsList"  {

    result(instance.getBirds())
  }

  else if call.method == "getRandomNumber"  {
    result(instance.randomNumber())
  }

  else if call.method == "getBirdInfo"  {
      let args = call.arguments as! Dictionary<String, String>
          let isDebug = args["bird"]
      result(instance.getBirdInfo(isDebug))
  }
  else {
  result(FlutterMethodNotImplemented)
  }
    })

    GeneratedPluginRegistrant.register(with: self)
    return super.application(application, didFinishLaunchingWithOptions: launchOptions)
  }
}

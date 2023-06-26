import Cocoa
import FlutterMacOS
import IOKit.ps
import GomobileNative


class MainFlutterWindow: NSWindow {
   override func awakeFromNib() {
          let flutterViewController = FlutterViewController()
    let windowFrame = self.frame
    self.contentViewController = flutterViewController
    self.setFrame(windowFrame, display: true)
  
    let channel = FlutterMethodChannel(
      name: "example.com/gomobileNative",
      binaryMessenger: flutterViewController.engine.binaryMessenger)
    channel.setMethodCallHandler { (call, result) in
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
    }

    RegisterGeneratedPlugins(registry: flutterViewController)

    super.awakeFromNib()
  }
}

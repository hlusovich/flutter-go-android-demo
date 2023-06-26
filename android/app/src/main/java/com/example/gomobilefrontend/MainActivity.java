package com.example.gomobilefrontend;

import androidx.annotation.NonNull;
import io.flutter.embedding.android.FlutterActivity;
import io.flutter.embedding.engine.FlutterEngine;
import io.flutter.plugin.common.MethodChannel;
import gomobileNative.GoMobileLib;

public class MainActivity extends FlutterActivity {
    private static final String CHANNEL = "example.com/gomobileNative";

    @Override
    public void configureFlutterEngine(@NonNull FlutterEngine flutterEngine) {

        GoMobileLib goMobileLib = new GoMobileLib();

        super.configureFlutterEngine(flutterEngine);
        new MethodChannel(flutterEngine.getDartExecutor().getBinaryMessenger(), CHANNEL)
                .setMethodCallHandler(
                        (call, result) -> {
                            if (call.method.equals("getRandomNumber")) {
                                result.success(goMobileLib.randomNumber());
                            } else if (call.method.equals("getBirdInfo")) {
                                String bird =  call.argument("bird");
                                result.success(goMobileLib.getBirdInfo(bird));
                            } else if (call.method.equals("getBirdsList")) {
                                result.success(goMobileLib.getBirds());
                            } else {
                                result.notImplemented();
                            }
                        });
    }
}
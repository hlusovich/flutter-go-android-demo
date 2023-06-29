#include "flutter_window.h"

#include <optional>

#include "flutter/generated_plugin_registrant.h"
#include <flutter/event_channel.h>
#include <flutter/event_sink.h>
#include <flutter/event_stream_handler_functions.h>
#include <flutter/method_channel.h>
#include <flutter/standard_method_codec.h>
#include <windows.h>
#include <string>
#include <initializer_list>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <flutter/binary_messenger.h>
#include <flutter/standard_method_codec.h>
#include <flutter/method_channel.h>
#include <flutter/method_result_functions.h>
#include <flutter/encodable_value.h>
#include <../standard_codec.cc>

#include <memory>



FlutterWindow::FlutterWindow(const flutter::DartProject& project)
    : project_(project) {}

FlutterWindow::~FlutterWindow() {}

 int RandomNumber() {
      return rand() % 50;
    }   

bool FlutterWindow::OnCreate() {
  if (!Win32Window::OnCreate()) {
    return false;
  }

  RECT frame = GetClientArea();

  // The size here must match the window dimensions to avoid unnecessary surface
  // creation / destruction in the startup path.
  flutter_controller_ = std::make_unique<flutter::FlutterViewController>(
      frame.right - frame.left, frame.bottom - frame.top, project_);
  // Ensure that basic setup of the controller was successful.
  if (!flutter_controller_->engine() || !flutter_controller_->view()) {
    return false;
  }
  RegisterPlugins(flutter_controller_->engine());
    const static std::string channel_name("example.com/gomobileNative");
    

      flutter::MethodChannel<> channel(
      flutter_controller_->engine()->messenger(), channel_name,
      &flutter::StandardMethodCodec::GetInstance());
  channel.SetMethodCallHandler(
      [](const flutter::MethodCall<>& call,
         std::unique_ptr<flutter::MethodResult<>> result) {
        if (call.method_name().compare("getBirdsList") == 0) {
        auto value = {91, 34, 83, 112, 97, 114, 114, 111, 119, 34, 44, 34, 80, 105, 103, 101, 111, 110, 34, 44, 34, 72, 101, 114, 111, 110, 34, 93}; 
        result->Success(value);
          }
        else if (call.method_name().compare("getRandomNumber") == 0) {
        result->Success(RandomNumber());
          }
        else if (call.method_name().compare("getBirdInfo") == 0) {
        const flutter::EncodableMap *argsList = std::get_if<flutter::EncodableMap>(call.arguments()); 
        auto bird_it = (argsList->find(flutter::EncodableValue("bird")))->second;     
        std::string bird = static_cast<std::string>(std::get<std::string>((bird_it)));

        if (bird == "Sparrow") {
            auto value  = {123, 34, 98, 105, 114, 100, 84, 121, 112, 101, 34, 58, 34, 83, 112, 97, 114, 114, 111, 119, 34, 44, 34, 119, 104, 97, 116, 32, 105, 116, 32, 100, 111, 101, 115, 34, 58, 34, 108, 105, 107, 101, 115, 32, 116, 111, 32, 101, 97, 116, 32, 115, 101, 101, 100, 34, 125};
            result->Success(value);
        }
         else if  (bird == "Pigeon") {
            auto value  = {123, 34, 98, 105, 114, 100, 84, 121, 112, 101, 34, 58, 34, 80, 105, 103, 101, 111, 110, 34, 44, 34, 119, 104, 97, 116, 32, 105, 116, 32, 100, 111, 101, 115, 34, 58, 34, 108, 105, 107, 101, 115, 32, 116, 111, 32, 101, 97, 116, 32, 118, 101, 103, 101, 116, 97, 98, 108, 101, 115, 34, 125};           
            result->Success(value);
        }
         else if  (bird == "Heron") {
             auto value  = {123, 34, 98, 105, 114, 100, 84, 121, 112, 101, 34, 58, 34, 72, 101, 114, 111, 110, 34, 44, 34, 119, 104, 97, 116, 32, 105, 116, 32, 100, 111, 101, 115, 34, 58, 34, 108, 105, 107, 101, 115, 32, 107, 117, 110, 103, 45, 102, 117, 34, 125};
             result->Success(value);
        }
        else {
                result->NotImplemented();
        }

              }
      
      });
  SetChildContent(flutter_controller_->view()->GetNativeWindow());

  flutter_controller_->engine()->SetNextFrameCallback([&]() {
    this->Show();
  });

  return true;
}

void FlutterWindow::OnDestroy() {
  if (flutter_controller_) {
    flutter_controller_ = nullptr;
  }

  Win32Window::OnDestroy();
}

LRESULT
FlutterWindow::MessageHandler(HWND hwnd, UINT const message,
                              WPARAM const wparam,
                              LPARAM const lparam) noexcept {
  // Give Flutter, including plugins, an opportunity to handle window messages.
  if (flutter_controller_) {
    std::optional<LRESULT> result =
        flutter_controller_->HandleTopLevelWindowProc(hwnd, message, wparam,
                                                      lparam);
    if (result) {
      return *result;
    }
  }

  switch (message) {
    case WM_FONTCHANGE:
      flutter_controller_->engine()->ReloadSystemFonts();
      break;
  }

  return Win32Window::MessageHandler(hwnd, message, wparam, lparam);
}




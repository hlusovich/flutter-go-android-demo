import 'dart:async';
import 'dart:io' show Platform;

import 'package:dio/dio.dart';
import 'package:gomobilefrontend/user.dart';

class TestApiService {
  final String testApiURL = Platform.isWindows ? 'http://localhost:5000' : 'http://10.0.2.2:5000';
  final Dio dio = Dio();
  TestApiService();

  FutureOr<User> getUser() async {
    try {
      final res = await dio.get('$testApiURL/user');

      final user = User.fromJson(res.data?['data']);
      return user;
    } catch (e) {
      return User.base();
    }
  }

  FutureOr<void> getHome() async {
    try {
      final res = await dio.get(testApiURL);
      print(res);
      return;
    } catch (e) {
      print(e);
      return;
    }
  }
}

import 'dart:async';

import 'package:dio/dio.dart';
import 'package:gomobilefrontend/user.dart';

class TestService {
  final String productsURL = 'http://10.0.2.2:5000';
  final Dio dio = Dio();
  TestService();

  FutureOr<User> getUser() async {
    try {
      final res = await dio.get('$productsURL/user');

      final user = User.fromJson(res.data?['data']);
      return user;
    } catch (e) {
      return User.base();
    }
  }

  FutureOr<void> getHome() async {
    try {
      final res = await dio.get(productsURL);
      print(res);
      return;
    } catch (e) {
      print(e);
      return;
    }
  }
}

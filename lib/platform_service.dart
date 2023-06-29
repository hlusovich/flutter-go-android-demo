import 'dart:convert';

import 'package:flutter/services.dart';

class PlatformService {
  static const channelName = 'example.com/gomobileNative';
  static const platformChannel = MethodChannel(channelName);
  Future<Map<String, dynamic>> getBirdInfo(String birdName) async {
    final List<dynamic> birdInfo = await platformChannel.invokeMethod('getBirdInfo', {'bird': birdName});
    return jsonDecode(utf8.decode(birdInfo.map((e) => int.tryParse(e.toString()) ?? 0).toList()));
  }

  Future<int> getRandomNumber() async {
    return await platformChannel.invokeMethod('getRandomNumber');
  }

  Future<List<String>> getBirdsList() async {
    final List<dynamic> birds = await platformChannel.invokeMethod("getBirdsList");
    final birdsParsed = jsonDecode(utf8.decode(birds.map((e) => int.tryParse(e.toString()) ?? 0).toList()));
    final List<String> result = [];
    birdsParsed.forEach((e) => result.add(e.toString()));
    return result;
  }
}

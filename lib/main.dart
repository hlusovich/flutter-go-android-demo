import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:gomobilefrontend/test_service.dart';
import 'package:gomobilefrontend/user.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'GoMobileFlutter',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Flutter with Go Mobile'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  User? user;
  static const platform = MethodChannel('example.com/gomobileNative');
  int _counter = 0;
  Map? bird;
  List<String> birdsList = [];
  String? selectedBird;

  @override
  initState() {
    _getBirdList();
  }

  Future<void> _getRandomNumber() async {
    int randomNumber;
    try {
      randomNumber = await platform.invokeMethod('getRandomNumber');
    } on PlatformException {
      randomNumber = 0;
    }

    setState(() {
      _counter = randomNumber;
    });
  }

  Future<void> _getBirdInformation() async {
    try {
      final List<int> birdInfo = await platform.invokeMethod('getBirdInfo', {'bird': selectedBird});
      print(birdInfo);
      bird = jsonDecode(utf8.decode(birdInfo));
    } on PlatformException {
      print('error');
    }

    setState(() {});
  }

  Future<void> _getBirdList() async {
    try {
      final List<int> birds = await platform.invokeMethod('getBirdsList');
      print(birds);
      List<dynamic> birdsParsed = jsonDecode(utf8.decode(birds));
      birdsList = birdsParsed.map((e) => e.toString()).toList();
    } on PlatformException {
      print('error');
    }

    setState(() {});
  }

  Future<void> _getUser() async {
    final service = TestService();
    user = await service.getUser();
    setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Text(widget.title),
            Visibility(
              visible: user != null,
              child: Row(
                children: [
                  const Icon(Icons.person_4),
                  const SizedBox(
                    width: 16.0,
                  ),
                  Text(user?.name ?? 'Default'),
                ],
              ),
            ),
          ],
        ),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            if (bird != null)
              Card(
                elevation: 5.0,
                child: Padding(
                  padding: const EdgeInsets.all(28.0),
                  child: Text(bird?['birdType'] + " " + bird?['what it does']),
                ),
              ),
            const Text(
              'The following number was generated by Go:',
            ),
            Text(
              '$_counter',
              style: Theme.of(context).textTheme.headlineMedium,
            ),
          ],
        ),
      ),
      floatingActionButton: Column(
        mainAxisSize: MainAxisSize.min,
        mainAxisAlignment: MainAxisAlignment.start,
        children: [
          Row(
            children: [
              const SizedBox(
                width: 16,
              ),
              const Text("Go code Tests"),
              const SizedBox(
                width: 16,
              ),
              FloatingActionButton(
                onPressed: _getRandomNumber,
                tooltip: 'Get a random number',
                child: const Icon(Icons.add),
              ),
              const SizedBox(
                width: 16,
              ),
              DropdownButton(
                  value: selectedBird,
                  items: birdsList
                      .map((e) => DropdownMenuItem(
                            value: e,
                            child: Text(e),
                          ))
                      .toList(),
                  onChanged: (e) {
                    selectedBird = e;
                    _getBirdInformation();
                    setState(() {});
                  })
            ],
          ),
          const SizedBox(
            height: 16,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.start,
            children: [
              const SizedBox(
                width: 16,
              ),
              const Text("Go Api Tests"),
              const SizedBox(
                width: 26,
              ),
              FloatingActionButton(
                onPressed: _getUser,
                tooltip: 'Get  user info',
                child: const Icon(Icons.person),
              ),
            ],
          ),
        ],
      ),
    );
  }
}

import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
// import 'presentation/LO/mqtt_test_page.dart';
import 'package:kp_spds/presentation/login/sign_in_page.dart';

void main() {
  runApp(const ProviderScope(child: MyApp()));
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      home: MqttTestPage(),
      debugShowCheckedModeBanner: false,
    );
  }
}
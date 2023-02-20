//
// flutter create blink_ble
// cd blink_le
// flutter pub add get
// flutter pub add flutter_reactive_ble
// android settings, app, give location permission for ble to work

// filename: main.dart
import 'package:flutter/material.dart';
import 'package:get/get.dart';
import './blecontroller.dart';

void main() => runApp(GetMaterialApp(home: Home()));

class Home extends StatelessWidget {
@override
Widget build(BuildContext context) {
final BleController ble = Get.put(BleController());
return Scaffold(
appBar: AppBar(title: const Text('Pico BLE Blink demo')),
body: Center(child: Column(children:[

SizedBox(height: 50.0),

ElevatedButton(
onPressed: ble.connect,
child: Obx(() => Text('${ble.status.value}',
style: TextStyle(
fontSize: 25, fontWeight: FontWeight.bold)))),
          
SizedBox(height: 50.0),
          
ElevatedButton(
child: Text('toggle led'),
onPressed: () {ble.toggle();}),
 
])));}}


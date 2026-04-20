import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';
import 'package:kp_spds/presentation/login/providers/sign_in_provider.dart';

class MqttTestPage extends ConsumerWidget {
  const MqttTestPage({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final mqtt = ref.watch(mqttProvider);
    final notifier = ref.read(mqttProvider.notifier);

    return Scaffold(
      appBar: AppBar(
        title: const Text("MQTT TEST"),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          children: [
            ElevatedButton(
              onPressed: () async {
                await notifier.connect(
                  "flutter_test",
                  "////",
                );
              },
              child: const Text("CONNECT HWID0001"),
            ),

            const SizedBox(height: 10),

            ElevatedButton(
              onPressed: () async {
                await notifier.switchDevice("HWID0003");
              },
              child: const Text("SWITCH TO HWID0003"),
            ),

              ElevatedButton(
              onPressed: () async {
                await notifier.switchDevice("HWID0002");
              },
              child: const Text("SWITCH TO HWID0002"),
            ),


            const SizedBox(height: 20),

            // ================= STATUS =================
            _card("STATUS", [
              "Connected: ${mqtt.connected}",
              "Status: ${mqtt.status}",
              "Mode: ${mqtt.mode}",
              "Balanceable: ${mqtt.isBalanceable}",
            ]),

            const SizedBox(height: 10),

            _card(
              "PHASE",
              mqtt.phases == null
                  ? ["No Data"]
                  : mqtt.phases!
                      .map((p) => "Phase ${p.index} = ${p.arus} A")
                      .toList(),
            ),

            const SizedBox(height: 10),

            Expanded(
              child: _card(
                "LOAD",
                mqtt.loads == null
                    ? ["No Data"]
                    : mqtt.loads!
                        .map((l) =>
                            "Load ${l.index} = ${l.arus} A (${l.phase})")
                        .toList(),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Widget _card(String title, List<String> items) {
    return Container(
      width: double.infinity,
      padding: const EdgeInsets.all(12),
      decoration: BoxDecoration(
        border: Border.all(color: Colors.white),
        borderRadius: BorderRadius.circular(8),
        color: Colors.black,
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(title,
              style: const TextStyle(
                  color: Colors.green,
                  fontWeight: FontWeight.bold)),
          const SizedBox(height: 8),
          ...items.map((e) => Text(
                e,
                style: const TextStyle(color: Colors.white),
              )),
        ],
      ),
    );
  }
}
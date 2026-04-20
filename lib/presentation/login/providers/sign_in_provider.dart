import 'package:flutter_riverpod/flutter_riverpod.dart';
import '../../../core/mqtt/mqtt_client.dart';
import '../../../data/datasource/remote/mqtt/parsing_mqtt.dart';
import '../../../data/model/threePhase_param.dart';
import '../../../data/datasource/remote/mqtt/switch_device.dart';

final mqttProvider =
    StateNotifierProvider<MqttNotifier, StateUpdate>((ref) {
  return MqttNotifier();
});

class MqttNotifier extends StateNotifier<StateUpdate> {
  MqttNotifier() : super(StateUpdate());

  final core = MqttClientCore();
Future<void> connect(String clientId, String espId) async {
  await core.connect(
    "4db5068a397f4f9bb1156a1fd4c038df.s1.eu.hivemq.cloud",
    clientId,
    8883,
  );

  final topics = MqttTopicBuilder.build(espId);

  for (final t in topics.values) {
    if (t.contains("Esp32")) {
      core.subscribe(t, (msg) {
        final parsed = MqttParser.parse(msg);
        _updateState(parsed);
      });
    }
  }
}

  void _updateState(StateUpdate update) {
    state = StateUpdate(
      connected: update.connected ?? state.connected,
      mode: update.mode ?? state.mode,
      isBalanceable: update.isBalanceable ?? state.isBalanceable,
      phases: update.phases ?? state.phases,
      loads: update.loads ?? state.loads,
      status: update.status ?? state.status,
    );
  }
  Future<void> switchDevice(String newEspId) async {
  core.disconnect(); 

  await connect("flutter_test", newEspId); 
}
}
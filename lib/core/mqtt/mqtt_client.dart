import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';
import 'dart:io';
class MqttClientCore {
  late MqttServerClient client;

  Future<void> connect(String broker, String clientId, int port) async {
    client = MqttServerClient.withPort(broker, clientId, port);
    client.secure = true;
    client.securityContext = SecurityContext.defaultContext;
    client.keepAlivePeriod = 10;
    client.autoReconnect = true;

    client.connectionMessage = MqttConnectMessage()
        .withClientIdentifier(clientId)
        .authenticateAs('Fariscoba', 'Faris123')
        .withWillTopic('PUBLISH_STATUS')
        .withWillMessage('DISCONNECTED')
        .withWillQos(MqttQos.exactlyOnce)
        .withWillRetain()
        // .keepAliveFor(3)
        .startClean();


    await client.connect();
  }

  void subscribe(String topic, Function(String msg) onMessage) {
    client.subscribe(topic, MqttQos.atLeastOnce);

    client.updates?.listen((events) {
      final rec = events[0].payload as MqttPublishMessage;
      final msg = MqttPublishPayload.bytesToStringAsString(
        rec.payload.message,
      );
      onMessage(msg);
    });
  }

  void publish(String topic, String payload, {bool retain = false}) {
    final builder = MqttClientPayloadBuilder();
    builder.addString(payload);

    client.publishMessage(
      topic,
      MqttQos.atLeastOnce,
      builder.payload!,
      retain: retain,
    );
  }

  void disconnect() {
    client.disconnect();
  }
}
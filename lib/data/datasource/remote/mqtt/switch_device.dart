class MqttTopicBuilder {
  static Map<String, String> build(String espId) {
    return {
      "subPhase": "$espId/Esp32/Phase",
      "subMode": "$espId/Esp32/Mode",
      "subStatus": "$espId/Esp32/Status",
      "subCurrent": "$espId/Esp32/Arus",
      "subBalance": "$espId/Esp32/Balanceable",
      "pubPhase": "$espId/Flutter/Phase",
      "pubMode": "$espId/Flutter/Mode",
    };
  }
}
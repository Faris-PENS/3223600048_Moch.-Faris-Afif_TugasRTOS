import 'dart:convert';
import '../../../model/threePhase_param.dart';

class MqttParser {
  static StateUpdate parse(String message) {
    final msg = message.trim().toUpperCase();

    if (msg == "CONNECTED") {
      return StateUpdate(connected: true, status: msg);
    } else if (msg == "DISCONNECT") {
      return StateUpdate(connected: false, status: msg);
    }

    dynamic payload;
    try {
      payload = jsonDecode(message);
    } catch (_) {
      return StateUpdate();
    }

    if (payload is List) {
      final loads = payload.map<LoadData>((item) {
        return LoadData(
          item["load"] - 1,
          (item["arus"] as num?)?.toDouble() ?? 0,
          null,
        );
      }).toList();

      return StateUpdate(loads: loads);
    }

  
    if (payload is Map<String, dynamic>) {
      List<PhaseData>? phases;
      List<LoadData>? loads;
      int? mode = payload["MODE"];
      bool? balance = payload["isBalanceable"];

      if (payload["phase"] is List) {
        phases = payload["phase"].map<PhaseData>((p) {
          return PhaseData(
            _phaseToIndex(p["phase"]),
            (p["arus"] as num?)?.toDouble() ?? 0,
          );
        }).toList();
      }

      if (payload["loads"] is List) {
        loads = payload["loads"].map<LoadData>((l) {
          return LoadData(
            l["load"] - 1,
            (l["arus"] as num?)?.toDouble() ?? 0,
            null,
          );
        }).toList();
      }

      if (payload["load"] != null) {
        loads = [
          LoadData(
            payload["load"] - 1,
            (payload["arus"] as num?)?.toDouble() ?? 0,
            payload["phase"] == 'N' ? null : payload["phase"],
          )
        ];
      }

      return StateUpdate(
        mode: mode,
        isBalanceable: balance,
        phases: phases,
        loads: loads,
      );
    }

    return StateUpdate();
  }

  static int _phaseToIndex(String p) {
    switch (p) {
      case 'R':
        return 0;
      case 'S':
        return 1;
      case 'T':
        return 2;
      case 'U':
        return 3;
      default:
        return -1;
    }
  }
}
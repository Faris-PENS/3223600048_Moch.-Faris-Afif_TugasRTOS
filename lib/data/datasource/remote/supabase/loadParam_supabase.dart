import 'package:flutter/material.dart';
import 'package:kp_spds/core/supabase/supabase_init.dart';
import 'package:kp_spds/data/datasource/local/session.dart';
import 'package:supabase_flutter/supabase_flutter.dart';

class LoadparamSupabase {
  final SupabaseClient _client = SupabaseInit.client;
  Future<List<Map<String, dynamic>>> fetchLoads() async {
  try {
    final esp = await LocalSession.loadSessiondevice();
    if (esp == null) return [];
    final res = await _client
        .from('loadAssets')
        .select()
        .eq('HWID', esp)
        .order('loadIndex');

    return List<Map<String, dynamic>>.from(res);
  } catch (e) {
    debugPrint("FETCH LOAD ERROR: $e");
    return [];
  }
}

Future<bool> updateLoad({
  required int loadIndex,
  required int type, 
  required String name, 
  required String Assetnumber,
  required String Location,
  required int maxAmps,
  
}) async {
  try {    
    final esp = await LocalSession.loadSessiondevice();
  
    if (esp == null) {
      return false;
    }

    final res = await _client
        .from('loadAssets')
        .update({
          'type': type,
          'name': name,
          'assetNum': Assetnumber,
          'location': Location,
          'maxAmps': maxAmps,
        })
        .eq('HWID', esp)
        .eq('loadIndex', loadIndex)
        .select();

    debugPrint("kkk: $res");

    if (res.isEmpty) {
      debugPrint("gagal");
      return true;
    } else {
      debugPrint("Load updated");
    }

    return false;
  } catch (e) {
    debugPrint("updateLoad error: $e");
    return true;
  }
}
}
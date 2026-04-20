import 'package:supabase_flutter/supabase_flutter.dart';
import 'package:kp_spds/core/supabase/supabase_init.dart';
import 'package:kp_spds/data/datasource/local/session.dart';

class UserRemoteDatasource {
  final SupabaseClient _client = SupabaseInit.client;

  Future<bool> login(String user, String pass) async {
    try {
      final res = await _client
          .from('user')
          .select()
          .eq('user', user)
          .eq('pass', pass)
          .maybeSingle();

      return res == null ? false : true;
    } catch (e) {
      return false;
    }
  }
    Future<String> insertUser({required String user, required String password}) async {
    try {
      final check = await _client
          .from('user')
          .select()
          .eq('user', user)
          .maybeSingle();
      if (check != null) {
        return 'User already exists';
      }

      final res = await _client
      .from('user')
      .insert({'user': user, 'pass': password});

      return res == null ? 'Error inserting user' : 'User inserted successfully';
    } catch (e) {
      // debugPrint('Insert user error: $e');
      return 'Error inserting user';
    }
  }

    Future<String?> changePassword({required String newPassword,required String oldPassword}) async {
    try {
      final userid = await LocalSession.loadSessionuser();
      if (userid == null) {
        return "false";
      }

      final res = await _client
          .from('user')
          .select()
          .eq('user', userid)
          .eq('pass', oldPassword)
          .maybeSingle();

      // debugPrint("CHECK RESULT: $res");
      if (res == null) {
        return "PASSWORD-SALAH";
      }

      await _client
          .from('user')
          .update({'pass': newPassword})
          .eq('user', userid);

      return "SUKSES";
    } catch (e) {
      // debugPrint("Change password error: $e");
    }
    return "FAILED";
  }



  
}
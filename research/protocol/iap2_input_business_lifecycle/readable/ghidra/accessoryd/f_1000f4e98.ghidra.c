/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000f4e98
 * original code SHA256: 02fa91e698ec270a5aac0142de6c79c336a1b62d6ebd833a32ef5f0334d6d1a1
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x27 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

undefined8 _acc_endpoint2_sendOutgoingData(long *param_1,long param_2)

{
  char *pcVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 uVar7;
  ulong uVar8;
  long lVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined *puVar12;
  long lVar13;
  ulong uVar14;
  long lVar15;
  undefined *local_c0;
  undefined8 local_b8;
  code *local_b0;
  undefined *puStack_a8;
  long *local_a0;
  long lStack_98;
  undefined4 local_90;
  char *local_8c;
  undefined2 local_84;
  long local_82;
  undefined2 local_7a;
  undefined4 local_78;
  undefined2 uStack_74;
  undefined2 uStack_72;
  undefined2 uStack_70;
  undefined2 local_6e;
  undefined8 local_6c;
  
  if (param_1 == (long *)0x0) {
    uVar7 = _logObjectForModule(0x11);
    iVar3 = _os_log_type_enabled(uVar7,0x10);
    if (iVar3 != 0) {
      _acc_endpoint2_sendOutgoingData_cold_7(uVar7);
    }
  }
  else if (param_2 == 0) {
    uVar7 = _logObjectForModule(0x11);
    iVar3 = _os_log_type_enabled(uVar7,0x10);
    if (iVar3 != 0) {
      _acc_endpoint2_sendOutgoingData_cold_6(uVar7);
    }
  }
  else {
    if (*param_1 != 0) {
      uVar5 = _CFHash(param_1[2]);
      uVar6 = _CFHash(param_2);
      puVar2 = _kCFACCUserDefaultsLoggingKey_TransportSignpost;
      uVar14 = uVar6 ^ uVar5;
      uVar7 = _acc_userDefaultsLogging_boolForKey(_kCFACCUserDefaultsLoggingKey_TransportSignpost);
      iVar3 = _gNumLogSignpostObjects;
      lVar13 = _gLogSignpostObjects;
      if ((int)uVar7 != 0) {
        if (((_gLogSignpostObjects == 0) || (_gNumLogSignpostObjects < 3)) &&
           (uVar7 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10), (int)uVar7 != 0)) {
          uVar7 = _acc_endpoint2_sendOutgoingData_cold_4(lVar13,iVar3);
        }
        if (((uVar5 != uVar6) && (uVar14 != 0xffffffffffffffff)) &&
           (iVar3 = _os_signpost_enabled(uVar7), iVar3 != 0)) {
          lVar13 = param_1[2];
          local_82 = _CFDataGetLength(param_2);
          local_90 = (undefined4)DAT_1001b30f0;
          local_84 = 0x800;
          local_8c = (char *)lVar13;
          __os_signpost_emit_with_name_impl
                    (0x100000000,uVar7,1,uVar14,"Endpoint SEND","Send outgoing data! %@, %lu bytes",
                     &local_90,0x16);
        }
        uVar7 = 0;
      }
      uVar8 = _acc_platform_packetLogging_isLogPacketDataAsMsg(uVar7);
      if (((uVar8 & 1) == 0) && (uVar8 = _platform_systemInfo_isInternalBuild(), (int)uVar8 == 0)) {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x12)) {
          puVar12 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar8 = _acc_endpoint2_sendOutgoingData_cold_3();
            puVar12 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar12 = *(undefined **)(_gLogObjects + 0x88);
        }
        iVar3 = _os_log_type_enabled(puVar12,uVar8,2);
        if (iVar3 != 0) {
          lVar9 = _CFDataGetLength(param_2);
          lVar15 = param_1[2];
          lVar13 = param_1[3];
          uVar4 = _CFDataGetLength(param_2);
          local_6c = _CFDataGetBytePtr(param_2);
          local_90 = (undefined4)DAT_1001b3b48;
          local_84 = 0x840;
          local_7a = 0x400;
          uStack_74 = 0x410;
          uStack_72 = (undefined2)uVar4;
          uStack_70 = (undefined2)((uint)uVar4 >> 0x10);
          local_6e = 0x830;
          local_8c = (char *)lVar9;
          local_82 = lVar15;
          local_78 = (int)lVar13;
          __os_log_debug_impl(0x100000000,uVar8,2,
                              "Sending %ld bytes of outgoing data for endpoint %@ (type:%{coreacc:ACCEndpoint_TransportType_t}d):\n%{coreacc:bytes}.*P"
                              ,&local_90,0x2c);
        }
      }
      else {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x12)) {
          puVar12 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar8 = _acc_endpoint2_sendOutgoingData_cold_3();
            puVar12 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar12 = *(undefined **)(_gLogObjects + 0x88);
        }
        iVar3 = _os_log_type_enabled(puVar12,uVar8,1);
        if (iVar3 != 0) {
          lVar9 = _CFDataGetLength(param_2);
          lVar15 = param_1[2];
          lVar13 = param_1[3];
          uVar4 = _CFDataGetLength(param_2);
          local_6c = _CFDataGetBytePtr(param_2);
          local_90 = (undefined4)DAT_1001b3b48;
          local_84 = 0x840;
          local_7a = 0x400;
          uStack_74 = 0x410;
          uStack_72 = (undefined2)uVar4;
          uStack_70 = (undefined2)((uint)uVar4 >> 0x10);
          local_6e = 0x830;
          local_8c = (char *)lVar9;
          local_82 = lVar15;
          local_78 = (int)lVar13;
          __os_log_impl(0x100000000,uVar8,1,
                        "Sending %ld bytes of outgoing data for endpoint %@ (type:%{coreacc:ACCEndpoint_TransportType_t}d):\n%{coreacc:bytes}.*P"
                        ,&local_90,0x2c);
        }
      }
      if ((param_1[0xe] == 0) || (lVar13 = param_1[0x11], lVar13 == 0)) {
        uVar7 = _acc_connection2_sendDataOut_internal(*param_1,param_1[2],param_2);
      }
      else {
        if (param_1[0x10] == 0) {
          (**(code **)(lVar13 + 0x10))(lVar13,*param_1,param_1[2],param_1[0xe],param_1[0xf],param_2)
          ;
        }
        else {
          _CFRetain(param_2);
          local_c0 = PTR___NSConcreteStackBlock_10022bb78;
          local_b8 = DAT_1001b3078;
          local_b0 = ___acc_endpoint2_sendOutgoingData_block_invoke;
          puStack_a8 = &___block_descriptor_48_e5_v8__0l;
          local_a0 = param_1;
          lStack_98 = param_2;
          _dispatch_async(&local_b0,param_1[0x10],&local_c0);
        }
        uVar7 = 1;
      }
      uVar10 = _acc_userDefaultsLogging_boolForKey(puVar2);
      iVar3 = _gNumLogSignpostObjects;
      lVar13 = _gLogSignpostObjects;
      if ((int)uVar10 == 0) {
        return uVar7;
      }
      if (((_gLogSignpostObjects == 0) || (_gNumLogSignpostObjects < 3)) &&
         (uVar10 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10), (int)uVar10 != 0)) {
        uVar10 = _acc_endpoint2_sendOutgoingData_cold_4(lVar13,iVar3);
      }
      if (uVar5 == uVar6) {
        return uVar7;
      }
      if (uVar14 == 0xffffffffffffffff) {
        return uVar7;
      }
      iVar3 = _os_signpost_enabled(uVar10);
      if (iVar3 == 0) {
        return uVar7;
      }
      pcVar1 = "SUCCESS";
      if ((int)uVar7 == 0) {
        pcVar1 = "ERROR";
      }
      lVar13 = param_1[2];
      uVar11 = _CFDataGetLength(param_2);
      local_90 = (undefined4)DAT_1001b3080;
      local_84 = 0x840;
      local_7a = 0x800;
      local_78 = (undefined4)uVar11;
      uStack_74 = (undefined2)((ulong)uVar11 >> 0x20);
      uStack_72 = (undefined2)((ulong)uVar11 >> 0x30);
      local_8c = pcVar1;
      local_82 = lVar13;
      __os_signpost_emit_with_name_impl
                (0x100000000,uVar10,2,uVar14,"Endpoint SEND",
                 "%s handling send outgoing data! %@, %lu bytes",&local_90,0x20);
      return uVar7;
    }
    uVar7 = _logObjectForModule(0x11);
    iVar3 = _os_log_type_enabled(uVar7,0x10);
    if (iVar3 != 0) {
      _acc_endpoint2_sendOutgoingData_cold_5(uVar7);
    }
  }
  return 0;
}


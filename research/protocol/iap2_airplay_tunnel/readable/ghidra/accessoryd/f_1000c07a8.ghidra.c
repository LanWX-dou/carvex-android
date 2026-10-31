/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000c07a8
 * original code SHA256: 2e5b176f4024ecf638ddb417a85a44345f60ad6c8953544220f1449bd72392e2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong __parseIdentificationParamsPower(long *param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined *puVar9;
  uint local_60;
  uint local_5c;
  undefined2 local_58;
  int local_56;
  int local_44;
  
  local_44 = 0;
  lVar5 = _iap2_feature_getFeature(param_1,0x10);
  if (lVar5 == 0) {
    _iap2_features_createFeature(param_1,0x10);
  }
  lVar5 = _iap2_feature_getFeature(param_1,0x10);
  if (lVar5 == 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x28)) {
      puVar9 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _logObjectForModule_cold_1();
        puVar9 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar9 = *(undefined **)(_gLogObjects + 0x138);
    }
    uVar6 = _os_log_type_enabled(puVar9,0x10);
    if ((int)uVar6 == 0) {
      return uVar6;
    }
    __parseIdentificationParamsPower_cold_10(puVar9);
    return 0;
  }
  iVar1 = _iAP2MsgGetParamID(param_3);
  if (iVar1 < 0x19) {
    if (iVar1 == 8) {
      iVar1 = _iAP2MsgGetDataAsU8(param_3,&local_44);
      if (local_44 != 0) {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x28)) {
          puVar9 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            __parseIdentificationParamsPower_cold_3();
            puVar9 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar9 = *(undefined **)(_gLogObjects + 0x138);
        }
        iVar1 = _os_log_type_enabled(puVar9,0x10);
        if (iVar1 != 0) {
          __parseIdentificationParamsPower_cold_8(puVar9);
        }
        uVar7 = 8;
        goto LAB_1000c0b78;
      }
      if ((iVar1 != 1) || ((*(uint *)(*param_1 + 0x18) & 0xfffffff7) != 0)) {
        *(int *)(lVar5 + 4) = iVar1;
        goto LAB_1000c0b80;
      }
      iVar1 = 0xd;
      uVar7 = 8;
      uVar8 = 0xd;
    }
    else {
      if ((iVar1 != 9) || (uVar2 = _iAP2MsgGetDataAsU16(param_3,&local_44), local_44 != 0))
      goto LAB_1000c0b80;
      uVar4 = __maximumCurrentAvailableFromDevice(param_1);
      if (uVar2 <= uVar4) {
        *(uint *)(lVar5 + 0xc) = uVar2;
        goto LAB_1000c0b80;
      }
      uVar7 = 9;
LAB_1000c0970:
      iVar1 = 6;
      uVar8 = 6;
    }
    _iap2_identification_addRejectParam(param_1,uVar7,uVar8);
    local_44 = iVar1;
  }
  else {
    if (iVar1 == 0x19) {
      uVar3 = _iAP2MsgGetDataAsU16(param_3,&local_44);
      if (local_44 == 0) {
        if (_gLogObjects == 0 || _gNumLogObjects < 0x28) {
          puVar9 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            __parseIdentificationParamsPower_cold_3();
            puVar9 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar9 = *(undefined **)(_gLogObjects + 0x138);
        }
        iVar1 = _os_log_type_enabled(puVar9,1);
        if (iVar1 != 0) {
          local_60 = (uint)DAT_1001b30b0;
          local_5c = uVar3;
          __os_log_impl(0x100000000,puVar9,1,"maximumSiphoningCurrent: %d!!",&local_60,8);
        }
        goto LAB_1000c0b80;
      }
      if (_gLogObjects == 0 || _gNumLogObjects < 0x28) {
        puVar9 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          __parseIdentificationParamsPower_cold_3();
          puVar9 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar9 = *(undefined **)(_gLogObjects + 0x138);
      }
      iVar1 = _os_log_type_enabled(puVar9,0x10);
      if (iVar1 != 0) {
        __parseIdentificationParamsPower_cold_2(puVar9);
      }
      uVar7 = 0x19;
    }
    else {
      if (iVar1 == 0xf0) {
        uVar2 = _iAP2MsgGetDataAsU16(param_3,&local_44);
        if (local_44 != 0) goto LAB_1000c0b80;
        uVar4 = _platform_power_getUltraHighPowerModeCurrentLimit(param_1[1]);
        if (uVar2 <= uVar4) {
          *(uint *)(lVar5 + 0x10) = uVar2;
          goto LAB_1000c0b80;
        }
        uVar7 = 0xf0;
        goto LAB_1000c0970;
      }
      if (iVar1 != 0xf1) goto LAB_1000c0b80;
      uVar2 = _iAP2MsgGetDataAsU8(param_3,&local_44);
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x28)) {
        puVar9 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          __parseIdentificationParamsPower_cold_3();
          puVar9 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar9 = *(undefined **)(_gLogObjects + 0x138);
      }
      iVar1 = _os_log_type_enabled(puVar9,1);
      if (iVar1 != 0) {
        local_60 = (uint)DAT_1001b3108;
        local_58 = 0x400;
        local_56 = local_44;
        local_5c = uVar2;
        __os_log_impl(0x100000000,puVar9,1,
                      "powerDuringSleepType during identification = %d, status = %d",&local_60,0xe);
      }
      if (local_44 == 0) {
        *(uint *)(lVar5 + 8) = uVar2;
        if (uVar2 < 2) {
          uVar7 = _logObjectForModule(0x27);
          iVar1 = _os_log_type_enabled(uVar7,1);
          if (iVar1 != 0) {
            local_60 = local_60 & 0xffff0000;
            __os_log_impl(0x100000000,uVar7,1,"identified for power during sleep over iAP2",
                          &local_60,2);
          }
          _iap2_identification_setIdentifiedForFeature(param_1,0x10);
        }
        goto LAB_1000c0b80;
      }
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x28)) {
        puVar9 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          __parseIdentificationParamsPower_cold_3();
          puVar9 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar9 = *(undefined **)(_gLogObjects + 0x138);
      }
      iVar1 = _os_log_type_enabled(puVar9,0x10);
      if (iVar1 != 0) {
        __parseIdentificationParamsPower_cold_6(puVar9);
      }
      uVar7 = 0xf1;
    }
LAB_1000c0b78:
    _iap2_identification_addRejectParam(param_1,uVar7,10);
  }
LAB_1000c0b80:
  return (ulong)(local_44 == 0);
}


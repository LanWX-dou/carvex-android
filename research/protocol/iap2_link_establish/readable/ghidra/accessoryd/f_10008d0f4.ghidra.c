/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008d0f4
 * original code SHA256: cf87494ed4d3f37279b97dda857f32018000a8a9507684e56910cdbee5251200
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */

undefined8 __acc_auth_protocol_validatePeerCertificateChain(long param_1)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  char *pcVar4;
  undefined8 uVar5;
  undefined *puVar6;
  long lVar7;
  undefined8 uVar8;
  undefined4 local_50;
  undefined4 local_4c;
  undefined2 local_48;
  undefined4 local_46;
  
  if (param_1 == 0) {
    lVar7 = 0;
  }
  else {
    lVar7 = *(long *)(param_1 + 0x580);
    if (lVar7 != 0) {
      lVar3 = param_1;
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
        puVar6 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          lVar3 = _logObjectForModule_cold_1();
          puVar6 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar6 = *(undefined **)(_gLogObjects + 0x1c8);
      }
      iVar1 = _os_log_type_enabled(puVar6,lVar3,2);
      if (iVar1 != 0) {
        __acc_auth_protocol_validatePeerCertificateChain_cold_2(lVar7,lVar3);
      }
      iVar1 = _platform_systemInfo_isInternalBuild(0);
      if ((iVar1 != 0) &&
         (uVar2 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ACCAuthProtocolPretendAuth),
         (uVar2 & 1) != 0)) {
        uVar8 = 0;
        goto LAB_10008d1f4;
      }
      if ((*(int *)(lVar7 + 0x160) != 0) &&
         ((iVar1 = _acc_auth_protocol_negotiatedMFi4Cert(param_1), iVar1 == 0 ||
          (1 < *(uint *)(lVar7 + 0x160))))) {
        iVar1 = _acc_auth_protocol_negotiatedMFi4Cert(param_1);
        if ((iVar1 == 0) ||
           (uVar8 = __acc_auth_protocol_decompressCerts(param_1,lVar7), (int)uVar8 == 0)) {
          uVar8 = __acc_auth_protocol_validateCertificateChain(param_1,lVar7);
        }
        goto LAB_10008d1f4;
      }
    }
  }
  uVar8 = 1;
LAB_10008d1f4:
  uVar2 = _platform_systemInfo_isInternalBuild();
  if (((int)uVar2 == 0) ||
     (uVar2 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ACCAuthProtocolPretendAuth),
     (uVar2 & 1) == 0)) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        uVar2 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0x1c8);
    }
    iVar1 = _os_log_type_enabled(puVar6,uVar2,1);
    if (iVar1 == 0) {
      return uVar8;
    }
    if (lVar7 == 0) {
      local_4c = 0xffffffff;
    }
    else {
      local_4c = *(undefined4 *)(lVar7 + 0x160);
    }
    local_50 = (undefined4)DAT_1001b3108;
    local_48 = 0x400;
    pcVar4 = 
    "[AccAuth] _acc_auth_protocol_validatePeerCertificateChain: peer certificateDataCount %d, errorNo %d \n"
    ;
    uVar5 = 0xe;
    local_46 = (int)uVar8;
  }
  else {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        uVar2 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0x1c8);
    }
    iVar1 = _os_log_type_enabled(puVar6,uVar2,1);
    if (iVar1 == 0) {
      return uVar8;
    }
    local_50 = (undefined4)DAT_1001b30b0;
    pcVar4 = "[AccAuth] _acc_auth_protocol_validatePeerCertificateChain: errorNo %d \n";
    uVar5 = 8;
    local_4c = (int)uVar8;
  }
  __os_log_impl(0x100000000,uVar2,1,pcVar4,&local_50,uVar5);
  return uVar8;
}


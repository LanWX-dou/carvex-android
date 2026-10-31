/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008e528
 * original code SHA256: 8f2daf6d1e9c01b65b887b23c122106ee78c8b3ddbfe807d7d58526266063a52
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x26 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */

undefined2
__acc_auth_protocol_verifyChallengeResponse
          (long param_1,long param_2,int param_3,long param_4,int param_5,long param_6,int param_7)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  long *plVar11;
  undefined *puVar12;
  long lVar13;
  undefined2 uVar14;
  undefined8 uVar15;
  undefined4 local_a0;
  int local_9c;
  undefined2 uStack_98;
  undefined2 uStack_96;
  undefined2 uStack_94;
  undefined2 local_92;
  undefined2 uStack_90;
  undefined2 uStack_8e;
  long local_8c;
  undefined2 local_84;
  long local_82;
  undefined2 local_7a;
  long local_78;
  undefined2 local_70;
  long local_6e;
  
  uVar3 = uStack_94;
  uVar1 = uStack_96;
  uVar14 = 1;
  uStack_96 = (undefined2)param_7;
  uVar2 = uStack_96;
  uStack_94 = (undefined2)((uint)param_7 >> 0x10);
  uVar4 = uStack_94;
  lVar6 = param_1;
  uStack_96 = uVar1;
  uStack_94 = uVar3;
  if (((((((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) ||
        ((param_6 == 0 || (param_7 == 0)))) ||
       ((lVar6 = _acc_auth_protocol_negotiatedMFi4Cert(), (int)lVar6 != 0 &&
        ((param_4 == 0 || (param_5 == 0)))))) ||
      (plVar11 = *(long **)(param_1 + 0x580), plVar11 == (long *)0x0)) ||
     ((((int)plVar11[0x2c] == 0 || (*plVar11 == 0)) || ((int)plVar11[1] == 0)))) goto LAB_10008e79c;
  uVar15 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
  lVar7 = _CFDataCreate(uVar15);
  lVar8 = _CFDataCreate(uVar15,param_2,param_3);
  lVar9 = _CFDataCreate(uVar15,param_6,param_7);
  lVar6 = lVar9;
  lVar13 = 0;
  if (param_4 != 0) {
    lVar6 = _CFDataCreate(uVar15,param_4,param_5);
    lVar13 = lVar6;
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
    puVar12 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      lVar6 = _logObjectForModule_cold_1();
      puVar12 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar12 = *(undefined **)(_gLogObjects + 0x1c8);
  }
  iVar5 = _os_log_type_enabled(puVar12,lVar6,2);
  if (iVar5 != 0) {
    local_a0 = (undefined4)DAT_1001b30e8;
    local_9c = 0x1d2027;
    uStack_98 = 1;
    uStack_96 = 0;
    uStack_94 = 0x400;
    local_92 = 0x905;
    uStack_90 = 0;
    uStack_8e = 0x840;
    local_84 = 0x840;
    local_7a = 0x840;
    local_70 = 0x840;
    local_8c = lVar8;
    local_82 = lVar9;
    local_78 = lVar7;
    local_6e = lVar13;
    __os_log_debug_impl(0x100000000,lVar6,2,
                        "[AccAuth] %s:%d challenge %@, response %@, peerCertObj %@, accessoryNonceObj %@ \n"
                        ,&local_a0,0x3a);
  }
  lVar6 = 0;
  if (((lVar7 == 0) || (lVar8 == 0)) || (lVar9 == 0)) {
    uVar14 = 0xc;
    if (lVar7 != 0) goto LAB_10008e770;
  }
  else {
    iVar5 = _platform_systemInfo_isInternalBuild();
    if ((iVar5 == 0) ||
       (uVar10 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ACCAuthProtocolPretendAuth),
       (uVar10 & 1) == 0)) {
      iVar5 = _acc_auth_protocol_negotiatedMFi4Cert(param_1);
      if (iVar5 == 0) {
        iVar5 = _MFAAVerifyNonceSignature(lVar7,lVar8,lVar9);
      }
      else {
        if (lVar13 == 0) {
          uVar14 = 0xc;
          goto LAB_10008e770;
        }
        iVar5 = _MFAAVerifyNonceSignatureMFi4(lVar7,lVar8,lVar13,0,lVar9);
      }
      uVar14 = 0;
      if (iVar5 == 0) {
        uVar14 = 0x50;
      }
    }
    else {
      uVar14 = 0;
    }
    iVar5 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ForceAuthFail);
    if (iVar5 != 0) {
      uVar15 = _logObjectForModule();
      iVar5 = _os_log_type_enabled(uVar15,1);
      if (iVar5 != 0) {
        local_a0 = 0x4000400;
        uStack_98 = 0x400;
        local_92 = 0x400;
        uStack_8e = 0;
        local_8c = CONCAT26(local_8c._6_2_,0x500400);
        local_9c = param_3;
        uStack_96 = uVar2;
        uStack_94 = uVar4;
        uStack_90 = uVar14;
        __os_log_impl(0x100000000,uVar15,1,
                      "[AccAuth] _verifyChallengeResponse: challengeLen %d, responseLen %d, override errorNo %d -> %d \n"
                      ,&local_a0,0x1a);
      }
      uVar14 = 0x50;
    }
LAB_10008e770:
    lVar6 = _CFRelease(lVar7);
  }
  if (lVar8 != 0) {
    lVar6 = _CFRelease(lVar8);
  }
  if (lVar9 != 0) {
    lVar6 = _CFRelease(lVar9);
  }
  if (lVar13 != 0) {
    lVar6 = _CFRelease(lVar13);
  }
LAB_10008e79c:
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
    puVar12 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      lVar6 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
      puVar12 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar12 = *(undefined **)(_gLogObjects + 0x1c8);
  }
  iVar5 = _os_log_type_enabled(puVar12,lVar6,1);
  if (iVar5 != 0) {
    local_a0 = (undefined4)DAT_1001b3100;
    uStack_98 = 0x400;
    local_92 = 0x400;
    uStack_8e = 0;
    local_9c = param_3;
    uStack_96 = uVar2;
    uStack_94 = uVar4;
    uStack_90 = uVar14;
    __os_log_impl(0x100000000,lVar6,1,
                  "[AccAuth] _verifyChallengeResponse: challengeLen %d, responseLen %d, errorNo %d \n"
                  ,&local_a0,0x14);
  }
  return uVar14;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100123204
 * original code SHA256: aa50da674227ae6fc5faeb8ef0d58a2382fa38b858c0d8fb46a2707967195fa6
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_iap2_deviceAuthentication_RequestDeviceChallengeResponse(undefined8 *param_1,long param_2)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  long lVar5;
  long lVar6;
  ulong uVar7;
  undefined8 uVar8;
  undefined *puVar9;
  char *pcVar10;
  undefined8 uVar11;
  undefined *local_f8;
  undefined8 local_f0;
  code *local_e8;
  undefined *puStack_e0;
  undefined8 *local_d8;
  undefined8 *local_d0;
  undefined8 *puStack_c8;
  undefined4 local_c0;
  uint local_bc;
  undefined2 uStack_b8;
  undefined2 uStack_b6;
  undefined2 uStack_b4;
  undefined8 local_a8;
  undefined8 *local_a0;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  undefined8 *local_80;
  undefined8 local_78;
  undefined8 local_70;
  
  uVar11 = 0;
  local_80 = &local_88;
  local_88 = 0;
  local_a0 = &local_a8;
  local_a8 = 0;
  local_78 = DAT_1001b3260;
  local_70 = 0;
  local_98 = DAT_1001b3260;
  local_90 = 0;
  if ((param_1 != (undefined8 *)0x0) && (param_2 != 0)) {
    lVar5 = _iap2_feature_getFeature(param_1,7);
    if (lVar5 != 0) {
      lVar5 = _iAP2MsgGetFirstParam(param_2,0);
      puVar1 = PTR___os_log_default_10022bbb0;
      uVar11 = DAT_1001b3108;
      while ((lVar5 != 0 && (local_80[3] == 0))) {
        uVar2 = _iAP2MsgGetParamID(lVar5);
        puVar9 = puVar1;
        if (uVar2 == 0) {
          lVar6 = _iAP2MsgGetParamValueData(lVar5);
          uVar7 = _iAP2MsgGetParamValueLen(lVar5);
          if ((lVar6 == 0) || ((int)uVar7 == 0)) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x34)) {
              if (_logObjectForModule_onceToken != -1) {
                _OUTLINED_FUNCTION_1();
                _dispatch_once();
              }
            }
            else {
              puVar9 = *(undefined **)(_gLogObjects + 0x198);
            }
            iVar3 = _os_log_type_enabled(puVar9,0);
            if (iVar3 != 0) {
              local_bc = (uint)lVar6 & 0xffff;
              uStack_b8 = 0x400;
              uStack_b6 = (undefined2)uVar7;
              uStack_b4 = (undefined2)(uVar7 >> 0x10);
              local_c0 = (int)uVar11;
              uVar8 = _OUTLINED_FUNCTION_6();
              pcVar10 = 
              "Auth challenge param malformed pChallengeBytes:%04X, challengeLength:%02X\n";
              goto LAB_1001233e4;
            }
          }
          else {
            uVar8 = _CFDataCreate(0,lVar6,uVar7 & 0xffffffff);
            local_80[3] = uVar8;
          }
        }
        else {
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x34)) {
            if (_logObjectForModule_onceToken != -1) {
              _OUTLINED_FUNCTION_1();
              _dispatch_once();
            }
          }
          else {
            puVar9 = *(undefined **)(_gLogObjects + 0x198);
          }
          iVar3 = _os_log_type_enabled(puVar9,0);
          if (iVar3 != 0) {
            uVar4 = _iAP2MsgGetMsgID(param_2);
            uStack_b8 = 0x400;
            uStack_b6 = (undefined2)uVar4;
            uStack_b4 = (undefined2)((uint)uVar4 >> 0x10);
            local_c0 = (int)uVar11;
            local_bc = uVar2;
            uVar8 = _OUTLINED_FUNCTION_6();
            pcVar10 = "Unknown Param ID: %d for Msg ID: 0x%04X - ignoring param";
LAB_1001233e4:
            __os_log_impl(uVar8,puVar9,0,pcVar10);
          }
        }
        lVar5 = _iAP2MsgGetNextParam(param_2,0,lVar5);
      }
      lVar5 = _platform_auth_createDeviceNonceSignature(local_80[3]);
      local_a0[3] = lVar5;
      if (param_1[3] != 0) {
        local_f8 = PTR___NSConcreteStackBlock_10022bb78;
        local_f0 = DAT_1001b3118;
        local_e8 = ___iap2_deviceAuthentication_RequestDeviceChallengeResponse_block_invoke;
        puStack_e0 = &DAT_100218e90;
        local_d8 = &local_a8;
        local_d0 = &local_88;
        puStack_c8 = param_1;
        _acc_protocolEndpoint_performAsync
                  (*param_1,*(undefined1 *)(param_1 + 4),param_1[3],&local_f8);
        uVar11 = 1;
        goto LAB_1001234a4;
      }
      if (local_80[3] != 0) {
        _CFRelease(local_80[3]);
        local_80[3] = 0;
        lVar5 = local_a0[3];
      }
      if (lVar5 != 0) {
        _CFRelease();
        local_a0[3] = 0;
      }
      uVar11 = _logObjectForModule();
      iVar3 = _os_log_type_enabled(uVar11,0x10);
      if (iVar3 != 0) {
        local_c0 = (undefined4)DAT_1001b3090;
        local_bc = 0x1cc512;
        uStack_b8 = 1;
        uStack_b6 = 0;
        uVar8 = _OUTLINED_FUNCTION_6();
        __os_log_error_impl(uVar8,uVar11,0x10,"%s No processing queue!",&local_c0,0xc);
      }
    }
    uVar11 = 0;
  }
LAB_1001234a4:
  __Block_object_dispose(&local_a8,8);
  __Block_object_dispose(&local_88,8);
  return uVar11;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100185d6c
 * original code SHA256: 16f9d5528a1b6c83f3bf88cbaf2eb87f18dbd88d5619e6ec221dd7498af62fba
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_accAuthentication_challengeResponse(long param_1,long param_2)

{
  undefined8 uVar1;
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  long lVar7;
  int *piVar8;
  undefined8 uVar9;
  ulong uVar10;
  undefined *puVar11;
  char *pcVar12;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  undefined8 uVar13;
  undefined8 extraout_x9;
  undefined8 extraout_x10;
  undefined *puVar14;
  long lVar15;
  undefined4 local_80;
  uint local_7c;
  undefined2 uStack_78;
  undefined2 uStack_76;
  undefined2 uStack_74;
  int local_72;
  undefined2 local_6e;
  undefined4 local_6c;
  
  lVar7 = _iAP2MsgGetFirstParam(param_2,0);
  if (param_1 == 0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  piVar8 = (int *)_iap2_feature_getFeature(param_1,0);
  puVar14 = PTR___os_log_default_10022bbb0;
  uVar1 = DAT_1001b3c10;
  uVar13 = DAT_1001b3108;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  if (*piVar8 != 0) {
    uVar13 = _logObjectForModule(0x1b);
    iVar4 = _os_log_type_enabled(uVar13,0);
    if (iVar4 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_7(*piVar8);
    uVar13 = extraout_x10;
    if (!(bool)in_ZR) {
      uVar13 = extraout_x9;
    }
    local_80 = (undefined4)DAT_1001b3090;
    local_7c = (uint)uVar13;
    uStack_78 = (undefined2)((ulong)uVar13 >> 0x20);
    uStack_76 = (undefined2)((ulong)uVar13 >> 0x30);
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_13();
    return 1;
  }
  if (lVar7 == 0) {
    iVar4 = _OUTLINED_FUNCTION_14();
    lVar15 = 0;
    if (iVar4 != 0) goto LAB_100185f98;
LAB_100186068:
    uVar13 = 0;
  }
  else {
    do {
      uVar3 = _iAP2MsgGetParamID(lVar7);
      puVar11 = puVar14;
      if (uVar3 == 0) {
        lVar15 = _iAP2MsgGetParamValueData(lVar7);
        iVar4 = _iAP2MsgGetParamValueLen(lVar7);
        if ((lVar15 == 0) || (iVar4 == 0)) {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_18(), in_NG != in_OV)) {
            in_OV = SCARRY8(_logObjectForModule_onceToken,1);
            in_NG = _logObjectForModule_onceToken + 1 < 0;
            in_ZR = _logObjectForModule_onceToken == -1;
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_1();
              _dispatch_once();
            }
          }
          else {
            puVar11 = *(undefined **)(extraout_x8 + 0xd8);
          }
          iVar6 = _os_log_type_enabled(puVar11,0);
          if (iVar6 != 0) {
            local_7c = (uint)lVar15 & 0xffff;
            local_80 = (undefined4)uVar1;
            uStack_78 = 0;
            uStack_76 = 0;
            uStack_74 = 0x400;
            local_6e = 0x400;
            local_6c = 0;
            local_72 = iVar4;
            uVar9 = _OUTLINED_FUNCTION_6();
            pcVar12 = "Cert param malformed pAccSignData:%04lX, accSignLen:%04X, paramError:%02X\n";
            goto LAB_100185f3c;
          }
          goto LAB_100185f40;
        }
        lVar15 = _CFDataCreate(0,lVar15,iVar4);
      }
      else {
        bVar2 = _gLogObjects == 0;
        in_OV = !bVar2 && SBORROW4(_gNumLogObjects,0x1c);
        in_ZR = !bVar2 && _gNumLogObjects == 0x1c;
        in_NG = bVar2 || _gNumLogObjects + -0x1c < 0;
        if (bVar2 || _gNumLogObjects < 0x1c) {
          in_OV = SCARRY8(_logObjectForModule_onceToken,1);
          in_NG = _logObjectForModule_onceToken + 1 < 0;
          in_ZR = _logObjectForModule_onceToken == -1;
          if (!(bool)in_ZR) {
            _OUTLINED_FUNCTION_1();
            _dispatch_once();
          }
        }
        else {
          puVar11 = *(undefined **)(_gLogObjects + 0xd8);
        }
        iVar4 = _os_log_type_enabled(puVar11,0);
        if (iVar4 != 0) {
          uVar5 = _iAP2MsgGetMsgID(param_2);
          local_80 = (undefined4)uVar13;
          uStack_78 = 0x400;
          uStack_76 = (undefined2)uVar5;
          uStack_74 = (undefined2)((uint)uVar5 >> 0x10);
          local_7c = uVar3;
          uVar9 = _OUTLINED_FUNCTION_6();
          pcVar12 = "Unknown Param ID: %d for Msg ID: 0x%04X - ignoring param";
LAB_100185f3c:
          __os_log_impl(uVar9,puVar11,0,pcVar12);
        }
LAB_100185f40:
        lVar15 = 0;
      }
      lVar7 = _iAP2MsgGetNextParam(param_2,0,lVar7);
    } while ((lVar7 != 0) && (lVar15 == 0));
    uVar10 = _OUTLINED_FUNCTION_14();
    if ((uVar10 & 1) != 0) {
LAB_100185f98:
      _OUTLINED_FUNCTION_18();
      if ((extraout_x8_00 == 0) || (_OUTLINED_FUNCTION_10(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_2();
        puVar14 = PTR___os_log_default_10022bbb0;
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
          puVar14 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar14 = *(undefined **)(extraout_x8_01 + 0xd8);
      }
      iVar4 = _os_log_type_enabled(puVar14,0);
      if (iVar4 != 0) {
        uVar13 = *(undefined8 *)(param_1 + 8);
        local_80 = (undefined4)DAT_1001b3088;
        local_7c = (uint)uVar13;
        uStack_78 = (undefined2)((ulong)uVar13 >> 0x20);
        uStack_76 = (undefined2)((ulong)uVar13 >> 0x30);
        uVar13 = _OUTLINED_FUNCTION_6();
        __os_log_impl(uVar13,puVar14,0,
                      "ForceAuthTimeout: %@ ignore incoming auth messages, allow timeout to occur, if any"
                      ,&local_80,0xc);
      }
      goto joined_r0x000100186004;
    }
    if ((lVar15 == 0) ||
       (iVar4 = _platform_auth_verifyNonceSignature
                          (*(undefined8 *)(piVar8 + 4),*(undefined8 *)(piVar8 + 0xe),lVar15),
       iVar4 == 0)) goto LAB_100186068;
    uVar13 = _platform_auth_createCapsFromAuthCert(*(undefined8 *)(piVar8 + 4));
    *(undefined8 *)(piVar8 + 0x10) = uVar13;
    uVar13 = 1;
  }
  __authCompleted(param_1,uVar13);
joined_r0x000100186004:
  if (lVar15 != 0) {
    _CFRelease(lVar15);
  }
  return 1;
}


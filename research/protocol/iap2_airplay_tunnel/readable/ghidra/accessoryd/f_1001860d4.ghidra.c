/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001860d4
 * original code SHA256: ed820e32b6f9cd4b54905f81c867972c421de2af8ef939e411f02d7cbcb09162
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_accAuthentication_certSerial(undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int *piVar10;
  long lVar11;
  long lVar12;
  undefined8 uVar13;
  undefined *puVar14;
  long extraout_x8;
  ulong uVar15;
  long extraout_x8_00;
  long extraout_x8_01;
  undefined8 extraout_x9;
  undefined8 extraout_x10;
  undefined *puVar16;
  long lVar17;
  undefined *local_b0;
  undefined8 local_a8;
  code *local_a0;
  undefined *puStack_98;
  undefined8 *local_90;
  long lStack_88;
  undefined4 local_80;
  uint local_7c;
  undefined2 uStack_78;
  undefined2 uStack_76;
  undefined2 uStack_74;
  int local_72;
  undefined2 uStack_6e;
  undefined2 uStack_6c;
  undefined2 uStack_6a;
  
  if (param_1 == (undefined8 *)0x0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  piVar10 = (int *)_iap2_feature_getFeature(param_1,0);
  if (piVar10 == (int *)0x0) {
    return 0;
  }
  uVar6 = (uint)*(byte *)(piVar10 + 0x12);
  cVar2 = SBORROW4(uVar6,1);
  cVar3 = (int)(uVar6 - 1) < 0;
  uVar4 = uVar6 == 1;
  if (!(bool)uVar4) {
    return 0;
  }
  if (*piVar10 != 0) {
    uVar13 = _logObjectForModule(0x1b);
    iVar7 = _os_log_type_enabled(uVar13,0);
    if (iVar7 != 0) {
      _OUTLINED_FUNCTION_7(*piVar10);
      uVar13 = extraout_x10;
      if (!(bool)uVar4) {
        uVar13 = extraout_x9;
      }
      local_80 = (undefined4)DAT_1001b3090;
      local_7c = (uint)uVar13;
      uStack_78 = (undefined2)((ulong)uVar13 >> 0x20);
      uStack_76 = (undefined2)((ulong)uVar13 >> 0x30);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_13();
    }
    return 1;
  }
  lVar11 = _iAP2MsgGetFirstParam(param_2,0);
  puVar14 = PTR___os_log_default_10022bbb0;
  uVar1 = DAT_1001b3c10;
  uVar13 = DAT_1001b3108;
  if (lVar11 != 0) {
    do {
      uVar6 = _iAP2MsgGetParamID(lVar11);
      if (uVar6 == 0) {
        lVar17 = _iAP2MsgGetParamValueData(lVar11);
        iVar7 = _iAP2MsgGetParamValueLen(lVar11);
        if ((lVar17 == 0) || (iVar7 == 0)) {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_18(), cVar3 != cVar2)) {
            _OUTLINED_FUNCTION_17();
            puVar16 = puVar14;
            if (!(bool)uVar4) {
              _OUTLINED_FUNCTION_1();
              _dispatch_once();
            }
          }
          else {
            puVar16 = *(undefined **)(extraout_x8 + 0xd8);
          }
          iVar9 = _os_log_type_enabled(puVar16,0);
          if (iVar9 != 0) {
            local_7c = (uint)lVar17 & 0xffff;
            local_80 = (undefined4)uVar1;
            uStack_78 = 0;
            uStack_76 = 0;
            uStack_74 = 0x400;
            uStack_6e = 0x400;
            uStack_6c = 0;
            uStack_6a = 0;
            local_72 = iVar7;
            __os_log_impl(0x100000000,puVar16,0,
                          "Cert serial number param malformed pAccSerNumData:%04lX, accSerNumLen:%04X, paramError:%02X\n"
                          ,&local_80,0x18);
          }
          lVar17 = 0;
        }
        else {
          lVar17 = _CFDataCreate(0,lVar17,iVar7);
        }
      }
      else {
        bVar5 = _gLogObjects == 0;
        cVar2 = !bVar5 && SBORROW4(_gNumLogObjects,0x1c);
        uVar4 = !bVar5 && _gNumLogObjects == 0x1c;
        cVar3 = bVar5 || _gNumLogObjects + -0x1c < 0;
        if (bVar5 || _gNumLogObjects < 0x1c) {
          _OUTLINED_FUNCTION_17();
          puVar16 = puVar14;
          if (!(bool)uVar4) {
            _OUTLINED_FUNCTION_1();
            _dispatch_once();
          }
        }
        else {
          puVar16 = *(undefined **)(_gLogObjects + 0xd8);
        }
        iVar7 = _os_log_type_enabled(puVar16,0);
        if (iVar7 != 0) {
          uVar8 = _iAP2MsgGetMsgID(param_2);
          local_80 = (undefined4)uVar13;
          uStack_78 = 0x400;
          uStack_76 = (undefined2)uVar8;
          uStack_74 = (undefined2)((uint)uVar8 >> 0x10);
          local_7c = uVar6;
          __os_log_impl(0x100000000,puVar16,0,
                        "Unknown Param ID: %d for Msg ID: 0x%04X - ignoring param",&local_80,0xe);
        }
        lVar17 = 0;
      }
      lVar11 = _iAP2MsgGetNextParam(param_2,0,lVar11);
    } while ((lVar11 != 0) && (lVar17 == 0));
    if (lVar17 != 0) {
      lVar11 = _CFDataGetLength(lVar17);
      uVar15 = lVar11 - 1;
      cVar2 = SBORROW8(uVar15,0x10);
      cVar3 = lVar11 + -0x11 < 0;
      uVar4 = uVar15 == 0x10;
      if (uVar15 < 0x10) {
        lVar12 = _platform_auth_createSerialNumberStringFromData(lVar17);
        lVar11 = _platform_auth_createCertDataFromSerialNumber(*(undefined8 *)(piVar10 + 2),lVar12);
        if (lVar12 != 0) {
          if (*(long *)(piVar10 + 6) != 0) {
            _CFRelease();
            piVar10[6] = 0;
            piVar10[7] = 0;
          }
          uVar13 = _CFRetain(lVar17);
          *(undefined8 *)(piVar10 + 6) = uVar13;
          if (*(long *)(piVar10 + 0xc) != 0) {
            _CFRelease();
            piVar10[0xc] = 0;
            piVar10[0xd] = 0;
          }
          uVar13 = _CFRetain(lVar12);
          *(undefined8 *)(piVar10 + 0xc) = uVar13;
          _CFRelease(lVar17);
          lVar17 = lVar12;
        }
      }
      else {
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_18(), cVar3 != cVar2)) {
          _OUTLINED_FUNCTION_17();
          puVar14 = PTR___os_log_default_10022bbb0;
          if (!(bool)uVar4) {
            _OUTLINED_FUNCTION_1();
            _dispatch_once();
            puVar14 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar14 = *(undefined **)(extraout_x8_01 + 0xd8);
        }
        iVar7 = _os_log_type_enabled(puVar14,0x10);
        if (iVar7 != 0) {
          local_80 = (undefined4)DAT_1001b3098;
          local_7c = 0x1d782b;
          uStack_78 = 1;
          uStack_76 = 0;
          uStack_74 = 0x800;
          local_72 = (int)lVar11;
          uStack_6e = (undefined2)((ulong)lVar11 >> 0x20);
          uStack_6c = (undefined2)((ulong)lVar11 >> 0x30);
          uVar13 = _OUTLINED_FUNCTION_6();
          __os_log_error_impl(uVar13,puVar14,0x10,
                              "%s Ignoring serial number data with invalid length:0x%02lX",&local_80
                              ,0x16);
        }
        lVar11 = 0;
      }
      _CFRelease(lVar17);
      if (param_1[3] != 0) {
        local_b0 = PTR___NSConcreteStackBlock_10022bb78;
        local_a8 = DAT_1001b3118;
        local_a0 = ___iap2_accAuthentication_certSerial_block_invoke;
        puStack_98 = &___block_descriptor_tmp_5;
        local_90 = param_1;
        lStack_88 = lVar11;
        _acc_protocolEndpoint_performAsync
                  (&local_a0,*param_1,*(undefined1 *)(param_1 + 4),param_1[3],&local_b0);
        return 0;
      }
      if (lVar11 != 0) {
        _CFRelease(lVar11);
      }
      puVar14 = (undefined *)_logObjectForModule(0x1b);
      uVar13 = _os_log_type_enabled(puVar14,0x10);
      if ((int)uVar13 == 0) {
        return uVar13;
      }
      local_80 = (undefined4)DAT_1001b3090;
      local_7c = 0x1d782b;
      uStack_78 = 1;
      uStack_76 = 0;
      uVar13 = _OUTLINED_FUNCTION_6();
      goto LAB_1001863e8;
    }
  }
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_18(), cVar3 != cVar2)) {
    _OUTLINED_FUNCTION_17();
    puVar14 = PTR___os_log_default_10022bbb0;
    if (!(bool)uVar4) {
      _OUTLINED_FUNCTION_1();
      _dispatch_once();
      puVar14 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar14 = *(undefined **)(extraout_x8_00 + 0xd8);
  }
  uVar13 = _os_log_type_enabled(puVar14,0x10);
  if ((int)uVar13 == 0) {
    return uVar13;
  }
  local_80 = (undefined4)DAT_1001b3090;
  local_7c = 0x1d782b;
  uStack_78 = 1;
  uStack_76 = 0;
  uVar13 = _OUTLINED_FUNCTION_6();
LAB_1001863e8:
  _OUTLINED_FUNCTION_19(uVar13,puVar14);
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10017527c
 * original code SHA256: 49d571c860b2f459b7263383a776216bcc243606af1ffeb39fa897f2a17ae2b4
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_navigation_startRouteGuidanceHandler(long param_1,long param_2)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  long lVar10;
  long extraout_x8;
  undefined8 uVar11;
  undefined8 *extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long extraout_x8_04;
  long extraout_x8_05;
  ulong uVar12;
  bool bVar13;
  undefined8 unaff_x19;
  undefined8 uVar14;
  undefined *puVar15;
  bool bVar16;
  bool bVar17;
  bool bVar18;
  undefined4 uVar19;
  undefined1 auVar20 [16];
  uint local_80;
  uint local_7c;
  undefined2 uStack_78;
  undefined2 uStack_76;
  undefined2 uStack_74;
  undefined2 local_66;
  int local_64;
  
  _OUTLINED_FUNCTION_18();
  if (extraout_x8 == 0) {
LAB_1001752c8:
    _OUTLINED_FUNCTION_9();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_18();
  }
  else {
    in_OV = SBORROW4(_gNumLogObjects,0x32);
    in_NG = _gNumLogObjects + -0x32 < 0;
    in_ZR = _gNumLogObjects == 0x32;
    if (_gNumLogObjects < 0x32) goto LAB_1001752c8;
    unaff_x19 = *(undefined8 *)(extraout_x8 + 0x188);
  }
  iVar4 = _os_log_type_enabled(unaff_x19,1);
  if (iVar4 != 0) {
    if (param_1 == 0) {
      uVar11 = 0;
    }
    else {
      uVar11 = *(undefined8 *)(param_1 + 8);
    }
    _OUTLINED_FUNCTION_70(uVar11,DAT_1001b3088);
    uVar11 = _OUTLINED_FUNCTION_6();
    __os_log_impl(uVar11,unaff_x19,1,"iAP2Navigation StartRouteGuidance Handler %@",&local_80,0xc);
  }
  if (param_1 == 0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  _OUTLINED_FUNCTION_17();
  lVar7 = _iAP2MsgGetFirstParam();
  local_64 = 0;
  _OUTLINED_FUNCTION_39();
  uVar11 = *extraout_x8_00;
  lVar8 = _CFArrayCreateMutable(uVar11,1,PTR__kCFTypeArrayCallBacks_10022bd38);
  if (lVar7 == 0) {
    bVar18 = false;
    bVar13 = false;
    bVar16 = false;
    bVar17 = false;
    uVar14 = 0;
    lVar7 = 0;
  }
  else {
    uVar14 = 0;
    bVar17 = false;
    bVar16 = false;
    bVar13 = false;
    bVar18 = false;
    iVar4 = 0;
    do {
      uVar5 = _iAP2MsgGetParamID(lVar7);
      cVar1 = SBORROW4(uVar5,5);
      cVar2 = (int)(uVar5 - 5) < 0;
      uVar3 = uVar5 == 5;
      if (uVar5 < 6) {
        uVar12 = (ulong)uVar5;
        cVar1 = SBORROW8(uVar12,5);
        cVar2 = (long)(uVar12 - 5) < 0;
        uVar3 = uVar12 == 5;
        switch(uVar12) {
        default:
          _OUTLINED_FUNCTION_80();
          local_66 = _iAP2MsgGetDataAsU16();
          if (local_64 == 0) {
            lVar10 = _CFNumberCreate(uVar11,2,&local_66);
            _CFArrayAppendValue(lVar8,lVar10);
            if (lVar10 != 0) {
              _CFRelease(lVar10);
            }
            iVar4 = iVar4 + 1;
            goto LAB_1001754ac;
          }
          _logObjectForModule();
          iVar4 = _OUTLINED_FUNCTION_65();
          if (iVar4 == 0) goto LAB_10017590c;
          _iAP2MsgGetMsgID(param_2);
          _OUTLINED_FUNCTION_28();
          local_7c = 0;
          uVar11 = _OUTLINED_FUNCTION_6();
          break;
        case 1:
          uVar12 = _iAP2MsgIsDataVoid(lVar7);
          if ((uVar12 & 1) == 0) {
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_65();
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 1;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          else {
            if ((int)uVar14 == 0) {
              uVar14 = 1;
              goto LAB_1001754ac;
            }
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_65();
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 1;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          break;
        case 2:
          uVar12 = _iAP2MsgIsDataVoid(lVar7);
          if ((uVar12 & 1) == 0) {
            uVar14 = _logObjectForModule();
            iVar4 = _os_log_type_enabled(uVar14,2);
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 2;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          else {
            if (!bVar17) {
              bVar17 = true;
              goto LAB_1001754ac;
            }
            uVar14 = _logObjectForModule();
            iVar4 = _os_log_type_enabled(uVar14,2);
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 2;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          break;
        case 3:
          uVar12 = _iAP2MsgIsDataVoid(lVar7);
          if ((uVar12 & 1) == 0) {
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_65();
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 3;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          else {
            if (!bVar16) {
              bVar16 = true;
              goto LAB_1001754ac;
            }
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_65();
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 3;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          break;
        case 4:
          uVar12 = _iAP2MsgIsDataVoid(lVar7);
          if ((uVar12 & 1) == 0) {
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_65();
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 4;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          else {
            if (!bVar13) {
              bVar13 = true;
              goto LAB_1001754ac;
            }
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_65();
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 4;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          break;
        case 5:
          uVar12 = _iAP2MsgIsDataVoid(lVar7);
          if ((uVar12 & 1) == 0) {
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_65();
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 5;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
          else {
            if (!bVar18) {
              bVar18 = true;
              goto LAB_10017547c;
            }
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_65();
            if (iVar4 == 0) goto LAB_10017590c;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_28();
            local_7c = 5;
            uVar11 = _OUTLINED_FUNCTION_6();
          }
        }
        _OUTLINED_FUNCTION_96(uVar11,uVar14);
        goto LAB_10017590c;
      }
LAB_10017547c:
      _OUTLINED_FUNCTION_18();
      if (((extraout_x8_01 == 0) || (_OUTLINED_FUNCTION_16(), cVar2 != cVar1)) &&
         (_OUTLINED_FUNCTION_9(), !(bool)uVar3)) {
        _OUTLINED_FUNCTION_8();
        _dispatch_once();
      }
      iVar6 = _OUTLINED_FUNCTION_73();
      if (iVar6 != 0) {
        _iAP2MsgGetMsgID(param_2);
        uVar19 = _OUTLINED_FUNCTION_28();
        uStack_78 = 0x400;
        uStack_76 = (undefined2)uVar19;
        uStack_74 = (undefined2)((uint)uVar19 >> 0x10);
        local_7c = uVar5;
        _OUTLINED_FUNCTION_12();
        __os_log_debug_impl();
      }
LAB_1001754ac:
      auVar20 = _OUTLINED_FUNCTION_17();
      lVar7 = _iAP2MsgGetNextParam(auVar20._0_8_,auVar20._8_8_,lVar7);
    } while (lVar7 != 0);
    in_NG = iVar4 < 0;
    in_ZR = iVar4 == 0;
    in_OV = '\0';
    lVar7 = lVar8;
    if (iVar4 < 1) {
      lVar7 = 0;
    }
  }
  uVar11 = 0;
  _OUTLINED_FUNCTION_18();
  if ((extraout_x8_02 == 0) || (_OUTLINED_FUNCTION_16(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_9();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_26();
  }
  else {
    uVar11 = *(undefined8 *)(extraout_x8_03 + 0x188);
  }
  iVar4 = _OUTLINED_FUNCTION_36();
  if (iVar4 != 0) {
    _OUTLINED_FUNCTION_70(*(undefined8 *)(param_1 + 8),DAT_1001b3088);
    uVar9 = _OUTLINED_FUNCTION_6();
    __os_log_impl(uVar9,uVar11,1,"iAP2Navigation StartRouteGuidance: %@",&local_80,0xc);
  }
  lVar10 = _iap2_feature_getFeature(param_1,0x11);
  if (lVar10 != 0) {
    local_80 = local_80 & 0xffffff00;
    iVar4 = _iap2_identification_checkRequiredMsgIDs(param_1,&_gskMsgNavigationMainList,5,&local_80)
    ;
    if (iVar4 != 0) {
      *(char *)(lVar10 + 0x10) = (char)uVar14;
      *(bool *)(lVar10 + 0x11) = bVar17;
      *(bool *)(lVar10 + 0x12) = bVar16;
      uVar3 = _iap2_identification_isIdentifiedForOutgoingMessageID(param_1,0x5204);
      *(undefined1 *)(lVar10 + 0x13) = uVar3;
      *(bool *)(lVar10 + 0x14) = bVar13;
      *(bool *)(lVar10 + 0x15) = bVar18;
      _OUTLINED_FUNCTION_18();
      if ((extraout_x8_04 == 0) || (_OUTLINED_FUNCTION_16(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_9();
        puVar15 = PTR___os_log_default_10022bbb0;
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_8();
          _dispatch_once();
          puVar15 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar15 = *(undefined **)(extraout_x8_05 + 0x188);
      }
      iVar4 = _os_log_type_enabled(puVar15,2);
      if (iVar4 != 0) {
        local_80 = (uint)DAT_1001b3088;
        local_7c = (uint)lVar8;
        uStack_78 = (undefined2)((ulong)lVar8 >> 0x20);
        uStack_76 = (undefined2)((ulong)lVar8 >> 0x30);
        uVar11 = _OUTLINED_FUNCTION_6();
        __os_log_debug_impl(uVar11,puVar15,2,
                            "iAP2Navigation StartRouteGuidance: for componentList=%@",&local_80,0xc)
        ;
      }
      uVar19 = *(undefined4 *)(lVar10 + 0x11);
      uVar11 = NEON_ushl((ulong)CONCAT16((char)((uint)uVar19 >> 0x18),
                                         (uint6)CONCAT14((char)((uint)uVar19 >> 0x10),
                                                         (uint)CONCAT12((char)((uint)uVar19 >> 8),
                                                                        (ushort)(byte)uVar19))),
                         DAT_1001b40d8,2);
      uVar5 = (uint)uVar11 | (uint)((ulong)uVar11 >> 0x20);
      _platform_navigation_startRouteGuidance
                (*(undefined8 *)(param_1 + 8),lVar7,
                 (uVar5 | uVar5 >> 0x10) & 0xff | (uint)*(byte *)(lVar10 + 0x15) << 5 |
                 (uint)*(byte *)(lVar10 + 0x10));
      uVar11 = 1;
      goto joined_r0x000100175910;
    }
  }
LAB_10017590c:
  uVar11 = 0;
joined_r0x000100175910:
  if (lVar8 != 0) {
    _CFRelease(lVar8);
  }
  return uVar11;
}


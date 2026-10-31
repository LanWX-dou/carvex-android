/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000027f4
 * original code SHA256: 712dda13112bbee0bcf7d6a5fbcdba43eb6b401de0513b58a09e721f878cd4de
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_navigation_routeGuidanceUpdateHandler(long param_1,long param_2)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  char cVar1;
  char cVar2;
  bool bVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  uint uVar14;
  long extraout_x8;
  undefined8 uVar15;
  long extraout_x8_00;
  undefined8 extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long extraout_x8_04;
  undefined8 extraout_x8_05;
  long extraout_x8_06;
  char *extraout_x9;
  undefined8 extraout_x10;
  int iVar16;
  char *pcVar17;
  long lVar18;
  undefined *puVar19;
  undefined1 auVar20 [16];
  undefined4 local_a0;
  char *local_9c;
  undefined2 local_94;
  undefined4 local_92;
  undefined2 uStack_8e;
  undefined2 uStack_8c;
  undefined2 uStack_8a;
  undefined4 local_88;
  undefined2 uStack_84;
  undefined2 uStack_82;
  undefined6 uStack_80;
  undefined2 local_7a;
  undefined8 local_78;
  undefined4 local_64;
  
  _OUTLINED_FUNCTION_18();
  if ((extraout_x8 == 0) || (_OUTLINED_FUNCTION_53(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_34();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  iVar5 = _OUTLINED_FUNCTION_38();
  if (iVar5 != 0) {
    if (param_1 == 0) {
      uVar15 = 0;
    }
    else {
      uVar15 = *(undefined8 *)(param_1 + 8);
    }
    _OUTLINED_FUNCTION_70(uVar15,DAT_1001b3088);
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_10();
    __os_log_impl();
  }
  if (param_1 == 0) {
    return 0;
  }
  lVar8 = _iap2_feature_getFeature(param_1,0x11);
  _OUTLINED_FUNCTION_18();
  if ((extraout_x8_00 == 0) || (_OUTLINED_FUNCTION_53(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_34();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  iVar5 = _OUTLINED_FUNCTION_38();
  if (iVar5 != 0) {
    _OUTLINED_FUNCTION_86();
    _OUTLINED_FUNCTION_85();
    uVar15 = extraout_x10;
    if (lVar8 != 0) {
      uVar15 = extraout_x8_01;
    }
    local_a0 = (undefined4)DAT_1001b30f0;
    local_94 = 0x820;
    local_92 = (undefined4)uVar15;
    uStack_8e = (undefined2)((ulong)uVar15 >> 0x20);
    uStack_8c = (undefined2)((ulong)uVar15 >> 0x30);
    local_9c = extraout_x9;
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_10();
    __os_log_impl();
  }
  if (param_2 == 0) {
    return 0;
  }
  if (lVar8 == 0) {
    return 0;
  }
  lVar9 = _OUTLINED_FUNCTION_95(0);
  lVar18 = *(long *)PTR__kCFNull_10022bd18;
  lVar11 = 0;
  if (lVar9 != lVar18) {
    lVar11 = lVar9;
  }
  _CFArrayGetValueAtIndex(param_2,2);
  lVar10 = _OUTLINED_FUNCTION_18();
  bVar3 = lVar10 == lVar18;
  if ((bVar3) || (lVar10 == 0)) {
    if (extraout_x8_02 == 0 || _gNumLogObjects < 0x32) {
      _OUTLINED_FUNCTION_34();
      if (!bVar3) {
        _OUTLINED_FUNCTION_8();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    _OUTLINED_FUNCTION_71();
    uVar15 = _os_log_type_enabled();
    if ((int)uVar15 != 0) {
      _OUTLINED_FUNCTION_70(*(undefined8 *)(param_1 + 8),DAT_1001b3088);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_74();
      return 0;
    }
    return uVar15;
  }
  if (extraout_x8_02 == 0 || _gNumLogObjects < 0x32) {
    _OUTLINED_FUNCTION_34();
    if (!bVar3) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_27();
  }
  else {
    param_2 = *(long *)(extraout_x8_02 + 0x188);
  }
  _OUTLINED_FUNCTION_71();
  iVar5 = _os_log_type_enabled();
  if (iVar5 != 0) {
    _OUTLINED_FUNCTION_70(*(undefined8 *)(param_1 + 8),DAT_1001b30f8);
    local_94 = 0x840;
    local_92 = (undefined4)lVar11;
    uStack_8e = (undefined2)((ulong)lVar11 >> 0x20);
    uStack_8c = (undefined2)((ulong)lVar11 >> 0x30);
    uStack_8a = 0x840;
    local_88 = (undefined4)lVar10;
    uStack_84 = (undefined2)((ulong)lVar10 >> 0x20);
    uStack_82 = (undefined2)((ulong)lVar10 >> 0x30);
    uVar15 = _OUTLINED_FUNCTION_6();
    __os_log_impl(uVar15,param_2,0,
                  "iAP2Navigation RouteGuidanceUpdate %@, create msg, componentIDs=%@ updateInfo=%@"
                  ,&local_a0,0x20);
  }
  uVar15 = _OUTLINED_FUNCTION_17(param_1 + 0x80,0x5201,*(undefined8 *)(param_1 + 200));
  if ((lVar11 == 0) || (lVar11 = _CFArrayGetCount(lVar9), lVar11 < 1)) {
    iVar5 = 0;
  }
  else {
    iVar5 = 0;
    lVar18 = 0;
    do {
      _CFArrayGetValueAtIndex(lVar9,lVar18);
      auVar20 = _OUTLINED_FUNCTION_10();
      iVar6 = ___addI16NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0);
      iVar5 = iVar5 + iVar6;
      lVar18 = lVar18 + 1;
    } while (lVar11 != lVar18);
  }
  uVar12 = _platform_navigation_routeGuidanceInfoKeyForType(1);
  _CFDictionaryGetValue(lVar10,uVar12);
  auVar20 = _OUTLINED_FUNCTION_12();
  iVar6 = ___addEnumNumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,1);
  _platform_navigation_routeGuidanceInfoKeyForType(2);
  _OUTLINED_FUNCTION_51();
  auVar20 = _OUTLINED_FUNCTION_12();
  iVar7 = ___addEnumNumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,2);
  _platform_navigation_routeGuidanceInfoKeyForType(3);
  lVar11 = _OUTLINED_FUNCTION_51();
  if (lVar11 == 0) {
LAB_100002b20:
    iVar16 = 0;
  }
  else {
    auVar20 = _OUTLINED_FUNCTION_10();
    lVar11 = _iAP2MsgAddCFStringParam(auVar20._0_8_,auVar20._8_8_,3);
    if (lVar11 == 0) goto LAB_100002b20;
    iVar16 = 1;
  }
  iVar16 = iVar5 + iVar6 + iVar7 + iVar16;
  _platform_navigation_routeGuidanceInfoKeyForType(4);
  lVar11 = _OUTLINED_FUNCTION_51();
  if (lVar11 != 0) {
    auVar20 = _OUTLINED_FUNCTION_10();
    _iAP2MsgAddCFStringParam(auVar20._0_8_,auVar20._8_8_,4);
  }
  _platform_navigation_routeGuidanceInfoKeyForType(5);
  uVar12 = _OUTLINED_FUNCTION_51();
  ___addU64NumberParameterToMsg(uVar15,5,uVar12);
  _platform_navigation_routeGuidanceInfoKeyForType(6);
  uVar12 = _OUTLINED_FUNCTION_51();
  ___addU64NumberParameterToMsg(uVar15,6,uVar12);
  _platform_navigation_routeGuidanceInfoKeyForType(7);
  _OUTLINED_FUNCTION_51();
  auVar20 = _OUTLINED_FUNCTION_10();
  ___addU32NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,7);
  _OUTLINED_FUNCTION_78();
  _platform_navigation_routeGuidanceInfoKeyForType(8);
  lVar11 = _OUTLINED_FUNCTION_51();
  if (lVar11 != 0) {
    auVar20 = _OUTLINED_FUNCTION_10();
    _iAP2MsgAddCFStringParam(auVar20._0_8_,auVar20._8_8_,8);
  }
  _platform_navigation_routeGuidanceInfoKeyForType(9);
  _OUTLINED_FUNCTION_51();
  _OUTLINED_FUNCTION_14();
  auVar20 = _OUTLINED_FUNCTION_12();
  ___addEnumNumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,9);
  _platform_navigation_routeGuidanceInfoKeyForType(10);
  _OUTLINED_FUNCTION_51();
  auVar20 = _OUTLINED_FUNCTION_10();
  ___addU32NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,10);
  _OUTLINED_FUNCTION_78();
  _platform_navigation_routeGuidanceInfoKeyForType(0xb);
  lVar11 = _OUTLINED_FUNCTION_51();
  if (lVar11 != 0) {
    auVar20 = _OUTLINED_FUNCTION_10();
    _iAP2MsgAddCFStringParam(auVar20._0_8_,auVar20._8_8_,0xb);
  }
  _platform_navigation_routeGuidanceInfoKeyForType(0xc);
  _OUTLINED_FUNCTION_51();
  _OUTLINED_FUNCTION_14();
  auVar20 = _OUTLINED_FUNCTION_12();
  ___addEnumNumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0xc);
  _OUTLINED_FUNCTION_78();
  _platform_navigation_routeGuidanceInfoKeyForType(0xd);
  lVar11 = _OUTLINED_FUNCTION_51();
  if (lVar11 != 0) {
    auVar20 = _OUTLINED_FUNCTION_10();
    _iAP2MsgAddCFU16ArrayParam(auVar20._0_8_,auVar20._8_8_,0xd);
  }
  _platform_navigation_routeGuidanceInfoKeyForType(0xe);
  _OUTLINED_FUNCTION_51();
  auVar20 = _OUTLINED_FUNCTION_10();
  ___addI16NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0xe);
  _platform_navigation_routeGuidanceInfoKeyForType(0xf);
  _OUTLINED_FUNCTION_51();
  auVar20 = _OUTLINED_FUNCTION_10();
  ___addU8NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0xf);
  _platform_navigation_routeGuidanceInfoKeyForType(0x10);
  _OUTLINED_FUNCTION_51();
  auVar20 = _OUTLINED_FUNCTION_10();
  ___addI16NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x10);
  _platform_navigation_routeGuidanceInfoKeyForType(0x11);
  _OUTLINED_FUNCTION_51();
  auVar20 = _OUTLINED_FUNCTION_10();
  ___addI16NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x11);
  _platform_navigation_routeGuidanceInfoKeyForType(0x12);
  _OUTLINED_FUNCTION_51();
  auVar20 = _OUTLINED_FUNCTION_10();
  ___addU8NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x12);
  _OUTLINED_FUNCTION_78();
  if (*(char *)(lVar8 + 0x10) != '\x01') goto LAB_100002d58;
  _platform_navigation_routeGuidanceInfoKeyForType(0x13);
  lVar11 = _OUTLINED_FUNCTION_51();
  if (lVar11 == 0) {
LAB_100002d50:
    iVar5 = 0;
  }
  else {
    auVar20 = _OUTLINED_FUNCTION_10();
    lVar11 = _iAP2MsgAddCFStringParam(auVar20._0_8_,auVar20._8_8_,0x13);
    if (lVar11 == 0) goto LAB_100002d50;
    iVar5 = 1;
  }
  iVar16 = iVar5 + iVar16;
LAB_100002d58:
  if (*(char *)(lVar8 + 0x11) == '\x01') {
    _platform_navigation_routeGuidanceInfoKeyForType(0x14);
    _OUTLINED_FUNCTION_51();
    auVar20 = _OUTLINED_FUNCTION_10();
    iVar5 = ___addU8NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x14);
    iVar16 = iVar16 + iVar5;
  }
  if (*(char *)(lVar8 + 0x14) == '\x01') {
    _platform_navigation_routeGuidanceInfoKeyForType(0x15);
    _OUTLINED_FUNCTION_51();
    auVar20 = _OUTLINED_FUNCTION_10();
    iVar5 = ___addI16NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x15);
    iVar16 = iVar16 + iVar5;
  }
  uVar14 = (uint)*(byte *)(lVar8 + 0x15);
  cVar1 = SBORROW4(uVar14,1);
  cVar2 = (int)(uVar14 - 1) < 0;
  uVar4 = uVar14 == 1;
  if ((bool)uVar4) {
    _platform_navigation_routeGuidanceInfoKeyForType(0x16);
    _OUTLINED_FUNCTION_51();
    auVar20 = _OUTLINED_FUNCTION_10();
    iVar5 = ___addU8NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x16);
    iVar16 = iVar16 + iVar5;
    _platform_navigation_routeGuidanceInfoKeyForType(0x17);
    lVar8 = _OUTLINED_FUNCTION_51();
    if (lVar8 != 0) {
      lVar11 = _CFArrayGetCount();
      cVar1 = SBORROW8(lVar11,1);
      cVar2 = lVar11 + -1 < 0;
      uVar4 = lVar11 == 1;
      if (0 < lVar11) {
        lVar11 = _CFArrayGetCount(lVar8);
        cVar1 = SBORROW8(lVar11,1);
        cVar2 = lVar11 + -1 < 0;
        uVar4 = lVar11 == 1;
        if (0 < lVar11) {
          lVar9 = 0;
          _OUTLINED_FUNCTION_39();
          do {
            local_64 = 0xaaaaaaaa;
            uVar12 = _CFArrayGetValueAtIndex(lVar8,lVar9);
            _OUTLINED_FUNCTION_18();
            if ((extraout_x8_03 == 0) || (_OUTLINED_FUNCTION_16(), cVar2 != cVar1)) {
              _OUTLINED_FUNCTION_9();
              puVar19 = PTR___os_log_default_10022bbb0;
              if (!(bool)uVar4) {
                _OUTLINED_FUNCTION_8();
                _dispatch_once();
                puVar19 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar19 = *(undefined **)(extraout_x8_04 + 0x188);
            }
            iVar5 = _os_log_type_enabled(puVar19,0);
            if (iVar5 != 0) {
              _OUTLINED_FUNCTION_28(*(undefined8 *)(param_1 + 8));
              local_9c = "iap2_navigation_routeGuidanceUpdateHandler";
              local_94 = 0x400;
              local_92 = 0x337;
              uStack_8e = 0x840;
              uStack_8c = (undefined2)extraout_x8_05;
              uStack_8a = (undefined2)((ulong)extraout_x8_05 >> 0x10);
              local_88 = (undefined4)((ulong)extraout_x8_05 >> 0x20);
              uStack_84 = 0x800;
              uStack_82 = (undefined2)lVar9;
              uStack_80 = (undefined6)((ulong)lVar9 >> 0x10);
              local_7a = 0x840;
              local_78 = uVar12;
              uVar13 = _OUTLINED_FUNCTION_6();
              __os_log_impl(uVar13,puVar19,0,"%s:%d %@, index %ld, dict = %@");
            }
            _iAP2MsgAddGroupParam(uVar15,0x17);
            local_64 = 0;
            lVar18 = _OUTLINED_FUNCTION_76();
            _CFDictionaryGetValue(uVar12,lVar18);
            if (lVar18 != 0) {
              _CFRelease(lVar18);
            }
            _OUTLINED_FUNCTION_21();
            iVar5 = ___addU8NumberParameterToMsg();
            local_64 = 1;
            lVar18 = _OUTLINED_FUNCTION_76();
            _CFDictionaryGetValue(uVar12,lVar18);
            if (lVar18 != 0) {
              _CFRelease(lVar18);
            }
            _OUTLINED_FUNCTION_21();
            iVar6 = ___addI16NumberParameterToMsg();
            local_64 = 2;
            lVar18 = _OUTLINED_FUNCTION_76();
            _CFDictionaryGetValue(uVar12,lVar18);
            if (lVar18 != 0) {
              _CFRelease(lVar18);
            }
            _OUTLINED_FUNCTION_21();
            iVar7 = ___addU32NumberParameterToMsg();
            iVar16 = iVar16 + iVar5 + iVar6 + iVar7;
            lVar9 = lVar9 + 1;
            cVar1 = SBORROW8(lVar11,lVar9);
            cVar2 = lVar11 - lVar9 < 0;
            uVar4 = lVar11 == lVar9;
          } while (!(bool)uVar4);
        }
      }
    }
    uVar12 = _platform_navigation_routeGuidanceInfoKeyForType(0x18);
    _CFDictionaryGetValue(lVar10,uVar12);
    auVar20 = _OUTLINED_FUNCTION_10();
    iVar5 = ___addU32NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x18);
    _platform_navigation_routeGuidanceInfoKeyForType(0x19);
    _OUTLINED_FUNCTION_51();
    auVar20 = _OUTLINED_FUNCTION_10();
    iVar6 = ___addU32NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x19);
    _platform_navigation_routeGuidanceInfoKeyForType(0x1a);
    _OUTLINED_FUNCTION_51();
    auVar20 = _OUTLINED_FUNCTION_10();
    iVar7 = ___addU32NumberParameterToMsg(auVar20._0_8_,auVar20._8_8_,0x1a);
    iVar16 = iVar16 + iVar5 + iVar6 + iVar7;
  }
  _OUTLINED_FUNCTION_18();
  if ((extraout_x8_06 == 0) || (_OUTLINED_FUNCTION_53(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_34();
    if (!(bool)uVar4) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  iVar5 = _OUTLINED_FUNCTION_38();
  if (iVar5 != 0) {
    pcVar17 = *(char **)(param_1 + 8);
    local_92 = _iAP2MsgGetMsgID(uVar15);
    local_a0 = (undefined4)DAT_1001b30f8;
    local_94 = 0x400;
    uStack_8e = 0x400;
    uStack_8c = (undefined2)iVar16;
    uStack_8a = (undefined2)((uint)iVar16 >> 0x10);
    local_9c = pcVar17;
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_10();
    __os_log_impl();
  }
  if (iVar16 == 0) {
    return 0;
  }
  _iap2_sessionControl_sendOutgoingMessage(param_1,uVar15);
  return 1;
}


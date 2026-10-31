/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001777c0
 * original code SHA256: 7a9e3f407e2648dda64898878b0eb9ad235b122a100381c5e63659cdbee2aabc
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_navigation_routeGuidanceManeuverUpdateHandler(long param_1,long param_2)

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
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  undefined2 extraout_w8;
  uint uVar16;
  undefined8 uVar17;
  long extraout_x8;
  undefined8 extraout_x8_00;
  undefined8 extraout_x10;
  undefined8 uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  long lVar22;
  undefined1 auVar23 [16];
  undefined4 local_80 [3];
  undefined2 local_74;
  undefined4 local_72;
  undefined2 uStack_6e;
  undefined2 uStack_6c;
  undefined2 uStack_6a;
  long local_68;
  
  uVar18 = 0x10023e000;
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_33(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_59();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_27();
  }
  _OUTLINED_FUNCTION_15();
  iVar5 = _os_log_type_enabled();
  if (iVar5 != 0) {
    if (param_1 == 0) {
      uVar17 = 0;
    }
    else {
      uVar17 = *(undefined8 *)(param_1 + 8);
    }
    _OUTLINED_FUNCTION_28(uVar17,DAT_1001b3088);
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_4();
    __os_log_impl();
  }
  if (param_1 == 0) {
    return 0;
  }
  lVar12 = _OUTLINED_FUNCTION_94();
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_33(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_59();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_26();
  }
  else {
    uVar18 = *(undefined8 *)(extraout_x8 + 0x188);
  }
  iVar5 = _OUTLINED_FUNCTION_36();
  if (iVar5 != 0) {
    _OUTLINED_FUNCTION_86();
    _OUTLINED_FUNCTION_85();
    uVar17 = extraout_x10;
    if (lVar12 != 0) {
      uVar17 = extraout_x8_00;
    }
    local_80[0] = (undefined4)DAT_1001b30f0;
    local_74 = 0x820;
    local_72 = (undefined4)uVar17;
    uStack_6e = (undefined2)((ulong)uVar17 >> 0x20);
    uStack_6c = (undefined2)((ulong)uVar17 >> 0x30);
    uVar17 = _OUTLINED_FUNCTION_6();
    __os_log_impl(uVar17,uVar18,1,"iAP2Navigation RouteGuidanceManeuverUpdate %@ navigation %s",
                  local_80,0x16);
  }
  if (param_2 == 0) {
    return 0;
  }
  if (lVar12 == 0) {
    return 0;
  }
  lVar13 = _CFArrayGetValueAtIndex(param_2,1);
  lVar22 = *(long *)PTR__kCFNull_10022bd18;
  lVar15 = 0;
  if (lVar13 != lVar22) {
    lVar15 = lVar13;
  }
  lVar14 = _CFArrayGetValueAtIndex(param_2,2);
  bVar3 = lVar14 == lVar22;
  if ((bVar3) || (lVar14 == 0)) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x32) {
      _OUTLINED_FUNCTION_9();
      if (!bVar3) {
        _OUTLINED_FUNCTION_8();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    _OUTLINED_FUNCTION_71();
    uVar18 = _os_log_type_enabled();
    if ((int)uVar18 != 0) {
      _OUTLINED_FUNCTION_28(*(undefined8 *)(param_1 + 8),DAT_1001b3088);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_74();
      return 0;
    }
    return uVar18;
  }
  if (_gLogObjects == 0 || _gNumLogObjects < 0x32) {
    _OUTLINED_FUNCTION_9();
    if (!bVar3) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  iVar5 = _OUTLINED_FUNCTION_38();
  if (iVar5 != 0) {
    _OUTLINED_FUNCTION_28(*(undefined8 *)(param_1 + 8),DAT_1001b30f8);
    local_74 = 0x840;
    local_72 = (undefined4)lVar15;
    uStack_6e = (undefined2)((ulong)lVar15 >> 0x20);
    uStack_6c = (undefined2)((ulong)lVar15 >> 0x30);
    uStack_6a = 0x840;
    local_68 = lVar14;
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_10();
    __os_log_impl();
  }
  uVar18 = _OUTLINED_FUNCTION_17(param_1 + 0x80,0x5202,*(undefined8 *)(param_1 + 200));
  if ((lVar15 == 0) || (lVar15 = _CFArrayGetCount(lVar13), lVar15 < 1)) {
    iVar5 = 0;
  }
  else {
    iVar5 = 0;
    lVar22 = 0;
    do {
      _CFArrayGetValueAtIndex(lVar13,lVar22);
      auVar23 = _OUTLINED_FUNCTION_13();
      iVar6 = ___addI16NumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,0);
      iVar5 = iVar5 + iVar6;
      lVar22 = lVar22 + 1;
    } while (lVar15 != lVar22);
  }
  _platform_navigation_maneuverInfoKeyForType(1);
  _OUTLINED_FUNCTION_57();
  auVar23 = _OUTLINED_FUNCTION_13();
  iVar6 = ___addI16NumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,1);
  _platform_navigation_maneuverInfoKeyForType(2);
  lVar15 = _OUTLINED_FUNCTION_57();
  if (lVar15 == 0) {
LAB_100177a9c:
    iVar19 = 0;
  }
  else {
    auVar23 = _OUTLINED_FUNCTION_13();
    lVar15 = _iAP2MsgAddCFStringParam(auVar23._0_8_,auVar23._8_8_,2);
    if (lVar15 == 0) goto LAB_100177a9c;
    iVar19 = 1;
  }
  _platform_navigation_maneuverInfoKeyForType(3);
  _OUTLINED_FUNCTION_57();
  auVar23 = _OUTLINED_FUNCTION_17();
  iVar7 = ___addEnumNumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,3);
  _platform_navigation_maneuverInfoKeyForType(4);
  lVar15 = _OUTLINED_FUNCTION_57();
  if (lVar15 == 0) {
LAB_100177afc:
    iVar20 = 0;
  }
  else {
    auVar23 = _OUTLINED_FUNCTION_13();
    lVar15 = _iAP2MsgAddCFStringParam(auVar23._0_8_,auVar23._8_8_,4);
    if (lVar15 == 0) goto LAB_100177afc;
    iVar20 = 1;
  }
  _platform_navigation_maneuverInfoKeyForType(5);
  _OUTLINED_FUNCTION_57();
  auVar23 = _OUTLINED_FUNCTION_13();
  iVar8 = ___addU32NumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,5);
  _platform_navigation_maneuverInfoKeyForType(6);
  lVar15 = _OUTLINED_FUNCTION_57();
  if (lVar15 == 0) {
LAB_100177b48:
    iVar21 = 0;
  }
  else {
    auVar23 = _OUTLINED_FUNCTION_13();
    lVar15 = _iAP2MsgAddCFStringParam(auVar23._0_8_,auVar23._8_8_,6);
    if (lVar15 == 0) goto LAB_100177b48;
    iVar21 = 1;
  }
  _platform_navigation_maneuverInfoKeyForType(7);
  _OUTLINED_FUNCTION_57();
  _OUTLINED_FUNCTION_14();
  auVar23 = _OUTLINED_FUNCTION_17();
  iVar9 = ___addEnumNumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,7);
  _platform_navigation_maneuverInfoKeyForType(8);
  _OUTLINED_FUNCTION_57();
  auVar23 = _OUTLINED_FUNCTION_17();
  iVar10 = ___addEnumNumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,8);
  _platform_navigation_maneuverInfoKeyForType(9);
  _OUTLINED_FUNCTION_57();
  auVar23 = _OUTLINED_FUNCTION_17();
  iVar11 = ___addEnumNumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,9);
  iVar5 = iVar5 + iVar6 + iVar19 + iVar7 + iVar20 + iVar8 + iVar21 + iVar9 + iVar10 + iVar11;
  _platform_navigation_maneuverInfoKeyForType(10);
  lVar15 = _OUTLINED_FUNCTION_57();
  if ((lVar15 != 0) && (lVar13 = _CFArrayGetCount(), 0 < lVar13)) {
    lVar22 = 0;
    do {
      _CFArrayGetValueAtIndex(lVar15,lVar22);
      auVar23 = _OUTLINED_FUNCTION_13();
      iVar6 = ___addI16NumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,10);
      iVar5 = iVar5 + iVar6;
      lVar22 = lVar22 + 1;
    } while (lVar13 != lVar22);
  }
  _platform_navigation_maneuverInfoKeyForType(0xb);
  _OUTLINED_FUNCTION_57();
  auVar23 = _OUTLINED_FUNCTION_13();
  iVar6 = ___addI16NumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,0xb);
  iVar5 = iVar5 + iVar6;
  uVar16 = (uint)*(byte *)(lVar12 + 0x12);
  cVar1 = SBORROW4(uVar16,1);
  cVar2 = (int)(uVar16 - 1) < 0;
  uVar4 = uVar16 == 1;
  if (!(bool)uVar4) goto LAB_100177c78;
  _platform_navigation_maneuverInfoKeyForType(0xd);
  lVar12 = _OUTLINED_FUNCTION_57();
  if (lVar12 == 0) {
LAB_100177c70:
    iVar6 = 0;
  }
  else {
    auVar23 = _OUTLINED_FUNCTION_13();
    lVar12 = _iAP2MsgAddCFStringParam(auVar23._0_8_,auVar23._8_8_,0xd);
    if (lVar12 == 0) goto LAB_100177c70;
    iVar6 = 1;
  }
  iVar5 = iVar6 + iVar5;
LAB_100177c78:
  iVar6 = _iap2_identification_isIdentifiedForOutgoingMessageID(param_1,0x5204);
  if (iVar6 != 0) {
    _platform_navigation_maneuverInfoKeyForType(0xc);
    lVar12 = _OUTLINED_FUNCTION_57();
    if (lVar12 != 0) {
      auVar23 = _OUTLINED_FUNCTION_13();
      iVar6 = ___addI16NumberParameterToMsg(auVar23._0_8_,auVar23._8_8_,0xc);
      iVar5 = iVar5 + iVar6;
    }
  }
  if (iVar5 != 0) {
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_33(), cVar2 != cVar1)) {
      _OUTLINED_FUNCTION_9();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_8();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    _OUTLINED_FUNCTION_15();
    iVar6 = _os_log_type_enabled();
    if (iVar6 != 0) {
      _iAP2MsgGetMsgID(uVar18);
      _OUTLINED_FUNCTION_68(DAT_1001b30f8);
      uStack_6c = (undefined2)iVar5;
      uStack_6a = (undefined2)((uint)iVar5 >> 0x10);
      uStack_6e = extraout_w8;
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_4();
      __os_log_impl();
    }
    _iap2_sessionControl_sendOutgoingMessage(param_1,uVar18);
  }
  return 1;
}


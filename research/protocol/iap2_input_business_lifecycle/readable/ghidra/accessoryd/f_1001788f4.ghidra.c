/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001788f4
 * original code SHA256: 0339b313bc68d00ef68040b2dfbdbef87160290c2d3326bdb03842a573d0afd8
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_navigation_stopRoadObjectDetectionHandler(long param_1,long param_2)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  long lVar5;
  char *pcVar6;
  undefined8 uVar7;
  long extraout_x8;
  char *extraout_x8_00;
  char *pcVar8;
  undefined8 unaff_x22;
  long lVar9;
  undefined1 auVar10 [16];
  undefined4 local_80;
  undefined8 local_7c;
  undefined2 local_74;
  char *local_72;
  undefined2 local_6a;
  undefined8 local_68;
  
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_83();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  iVar4 = _OUTLINED_FUNCTION_38();
  if (iVar4 != 0) {
    if (param_1 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = *(undefined8 *)(param_1 + 8);
    }
    _OUTLINED_FUNCTION_28(uVar7,DAT_1001b3088);
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_10();
    __os_log_impl();
  }
  if (param_1 == 0) {
    uVar7 = 0;
  }
  else {
    lVar5 = _OUTLINED_FUNCTION_94();
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
      _OUTLINED_FUNCTION_83();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_8();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_26();
    }
    else {
      unaff_x22 = *(undefined8 *)(extraout_x8 + 0x188);
    }
    iVar4 = _OUTLINED_FUNCTION_36();
    if (iVar4 != 0) {
      uVar7 = *(undefined8 *)(param_1 + 8);
      _OUTLINED_FUNCTION_86();
      local_72 = "missing!!";
      if (lVar5 != 0) {
        local_72 = extraout_x8_00;
      }
      local_68 = _obfuscatedPointer(param_2);
      local_80 = (undefined4)DAT_1001b30f8;
      local_74 = 0x820;
      local_6a = 0x800;
      local_7c = uVar7;
      uVar7 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar7,unaff_x22,1,
                    "iAP2Navigation stopRoadObjectDetection %@ navigation %s, param=%p",&local_80,
                    0x20);
    }
    uVar7 = 0;
    if ((param_2 != 0) && (lVar5 != 0)) {
      pcVar6 = (char *)_OUTLINED_FUNCTION_95(0);
      pcVar8 = *(char **)PTR__kCFNull_10022bd18;
      cVar1 = SBORROW8((long)pcVar6,(long)pcVar8);
      cVar2 = (long)pcVar6 - (long)pcVar8 < 0;
      uVar3 = pcVar6 == pcVar8;
      pcVar8 = (char *)0x0;
      if (!(bool)uVar3) {
        pcVar8 = pcVar6;
      }
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), cVar2 != cVar1)) {
        _OUTLINED_FUNCTION_83();
        if (!(bool)uVar3) {
          _OUTLINED_FUNCTION_8();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_15();
      }
      iVar4 = _OUTLINED_FUNCTION_38();
      if (iVar4 != 0) {
        _OUTLINED_FUNCTION_28(*(undefined8 *)(param_1 + 8),DAT_1001b30f0);
        local_74 = 0x840;
        local_72 = pcVar8;
        _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_10();
        __os_log_impl();
      }
      uVar7 = _OUTLINED_FUNCTION_17(param_1 + 0x80,0xd02,*(undefined8 *)(param_1 + 200));
      if (pcVar8 != (char *)0x0) {
        lVar5 = _CFArrayGetCount(pcVar6);
        cVar1 = SBORROW8(lVar5,1);
        cVar2 = lVar5 + -1 < 0;
        uVar3 = lVar5 == 1;
        if (0 < lVar5) {
          lVar9 = 0;
          do {
            _CFArrayGetValueAtIndex(pcVar6,lVar9);
            auVar10 = _OUTLINED_FUNCTION_13();
            ___addI16NumberParameterToMsg(auVar10._0_8_,auVar10._8_8_,0);
            lVar9 = lVar9 + 1;
            cVar1 = SBORROW8(lVar5,lVar9);
            cVar2 = lVar5 - lVar9 < 0;
            uVar3 = lVar5 == lVar9;
          } while (!(bool)uVar3);
        }
      }
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), cVar2 != cVar1)) {
        _OUTLINED_FUNCTION_83();
        if (!(bool)uVar3) {
          _OUTLINED_FUNCTION_8();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      _OUTLINED_FUNCTION_15();
      iVar4 = _os_log_type_enabled();
      if (iVar4 != 0) {
        _iAP2MsgGetMsgID(uVar7);
        _OUTLINED_FUNCTION_68(DAT_1001b30f0);
        _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_4();
        __os_log_impl();
      }
      _iap2_sessionControl_sendOutgoingMessage(param_1,uVar7);
      uVar7 = 1;
    }
  }
  return uVar7;
}


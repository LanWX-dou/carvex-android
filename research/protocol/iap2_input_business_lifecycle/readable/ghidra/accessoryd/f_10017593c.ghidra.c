/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10017593c
 * original code SHA256: 128b66dfcff893fa4f99d3d39bbbb7ea0c06979ab054954297e1539be511b321
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_navigation_stopRouteGuidanceHandler(void)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  undefined8 uVar7;
  undefined8 *extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long lVar8;
  undefined8 unaff_x30;
  undefined1 auVar9 [16];
  undefined8 in_stack_00000038;
  
  auVar9 = _OUTLINED_FUNCTION_90();
  lVar8 = auVar9._8_8_;
  lVar3 = auVar9._0_8_;
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_89(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_9();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_27();
  }
  _OUTLINED_FUNCTION_15();
  iVar1 = _os_log_type_enabled();
  if (iVar1 != 0) {
    if (lVar3 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = *(undefined8 *)(lVar3 + 8);
    }
    _OUTLINED_FUNCTION_11(uVar7,DAT_1001b3088);
    _OUTLINED_FUNCTION_44();
    __os_log_impl();
  }
  uVar7 = 0;
  if ((lVar3 != 0) && (lVar8 != 0)) {
    _OUTLINED_FUNCTION_17();
    lVar4 = _iAP2MsgGetFirstParam();
    in_stack_00000038._4_4_ = 0;
    _OUTLINED_FUNCTION_39();
    uVar7 = *extraout_x8;
    lVar5 = _CFArrayCreateMutable(uVar7,1,PTR__kCFTypeArrayCallBacks_10022bd38);
    if (lVar4 == 0) {
      lVar8 = 0;
    }
    else {
      iVar1 = 0;
      _OUTLINED_FUNCTION_18();
      do {
        iVar2 = _iAP2MsgGetParamID(lVar4);
        if (iVar2 == 0) {
          in_stack_00000038._2_2_ = _iAP2MsgGetDataAsU16(lVar4,(long)&stack0x00000038 + 4);
          if (in_stack_00000038._4_4_ != 0) {
            _logObjectForModule();
            iVar1 = _OUTLINED_FUNCTION_63();
            if (iVar1 != 0) {
              _iAP2MsgGetMsgID(lVar8);
              uVar7 = _OUTLINED_FUNCTION_7();
              _OUTLINED_FUNCTION_96(uVar7,lVar3);
            }
            goto LAB_100175c10;
          }
          lVar6 = _CFNumberCreate(uVar7,2,(long)&stack0x00000038 + 2);
          _OUTLINED_FUNCTION_30();
          _CFArrayAppendValue();
          if (lVar6 != 0) {
            _CFRelease(lVar6);
          }
          iVar1 = iVar1 + 1;
        }
        else {
          if (((_gLogObjects == 0) || (_OUTLINED_FUNCTION_89(), in_NG != in_OV)) &&
             (_OUTLINED_FUNCTION_9(), !(bool)in_ZR)) {
            _OUTLINED_FUNCTION_8();
            _dispatch_once();
          }
          iVar2 = _OUTLINED_FUNCTION_73();
          if (iVar2 != 0) {
            _iAP2MsgGetMsgID(lVar8);
            _OUTLINED_FUNCTION_12();
            __os_log_debug_impl();
          }
        }
        auVar9 = _OUTLINED_FUNCTION_17();
        lVar4 = _iAP2MsgGetNextParam(auVar9._0_8_,auVar9._8_8_,lVar4);
      } while (lVar4 != 0);
      in_NG = iVar1 < 0;
      in_ZR = iVar1 == 0;
      in_OV = '\0';
      lVar8 = lVar5;
      if (iVar1 < 1) {
        lVar8 = 0;
      }
    }
    uVar7 = 0;
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_89(), in_NG != in_OV)) {
      _OUTLINED_FUNCTION_9();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_8();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_26();
    }
    else {
      uVar7 = *(undefined8 *)(extraout_x8_00 + 0x188);
    }
    iVar1 = _OUTLINED_FUNCTION_36();
    if (iVar1 != 0) {
      _OUTLINED_FUNCTION_11(*(undefined8 *)(lVar3 + 8),DAT_1001b3088);
      _OUTLINED_FUNCTION_27();
      __os_log_impl();
    }
    lVar4 = _OUTLINED_FUNCTION_94();
    if ((lVar4 == 0) || (iVar1 = _OUTLINED_FUNCTION_66(), iVar1 == 0)) {
LAB_100175c10:
      uVar7 = 0;
    }
    else {
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_89(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_9();
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_8();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_26();
      }
      else {
        uVar7 = *(undefined8 *)(extraout_x8_01 + 0x188);
      }
      iVar1 = _os_log_type_enabled(uVar7,2);
      if (iVar1 != 0) {
        _OUTLINED_FUNCTION_6();
        auVar9 = _OUTLINED_FUNCTION_45();
        __os_log_debug_impl(auVar9._0_8_,auVar9._8_8_,2);
      }
      _platform_navigation_stopRouteGuidance(*(undefined8 *)(lVar3 + 8),lVar8);
      uVar7 = 1;
    }
    if (lVar5 != 0) {
      _CFRelease(lVar5);
    }
  }
  _OUTLINED_FUNCTION_91(uVar7,unaff_x30);
  return;
}


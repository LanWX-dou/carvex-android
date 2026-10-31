/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100131fbc
 * original code SHA256: 855069f65bf862dc1d3fe8bec2eab116f6969bcf0bb37fec707fc46993e2d166
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

undefined8 _mfi4Auth_protocol_decryptIncomingData(long param_1,undefined8 param_2,long param_3)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  int extraout_w1;
  ulong uVar6;
  undefined1 auVar7 [16];
  undefined4 local_60;
  int local_5c;
  
  if (param_1 == 0) {
    uVar4 = _logObjectForModule();
    iVar2 = _OUTLINED_FUNCTION_7(uVar4);
    if (iVar2 != 0) {
      _OUTLINED_FUNCTION_4();
LAB_100132290:
      _OUTLINED_FUNCTION_2();
      __os_log_error_impl();
    }
  }
  else {
    _OUTLINED_FUNCTION_34();
    if ((bool)in_ZR) {
      uVar4 = _logObjectForModule();
      iVar2 = _OUTLINED_FUNCTION_7(uVar4);
      if (iVar2 != 0) {
        _OUTLINED_FUNCTION_4();
        goto LAB_100132290;
      }
    }
    else if (param_3 == 0) {
      uVar4 = _logObjectForModule();
      iVar2 = _OUTLINED_FUNCTION_7(uVar4);
      if (iVar2 != 0) {
        _OUTLINED_FUNCTION_4();
        goto LAB_100132290;
      }
    }
    else {
      if (*(int *)(param_1 + 0xe0) == 0) {
        return 1;
      }
      if ((_gLogObjects == 0) || (uVar4 = _OUTLINED_FUNCTION_23(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_30();
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_3();
          _dispatch_once();
        }
        uVar4 = _OUTLINED_FUNCTION_19();
      }
      iVar2 = _os_log_type_enabled(uVar4,0);
      if (iVar2 != 0) {
        uVar5 = _OUTLINED_FUNCTION_4();
        __os_log_impl(uVar5,uVar4,0,"decryptIncomingData",&local_60,2);
      }
      iVar2 = _iAP2MsgGetMsgID(param_3);
      if (iVar2 != 0) {
        if ((_gLogObjects == 0) || (uVar4 = _OUTLINED_FUNCTION_23(), in_NG != in_OV)) {
          _OUTLINED_FUNCTION_30();
          if (!(bool)in_ZR) {
            _OUTLINED_FUNCTION_3();
            _dispatch_once();
          }
          uVar4 = _OUTLINED_FUNCTION_19();
        }
        iVar3 = _os_log_type_enabled(uVar4,0);
        if (iVar3 != 0) {
          local_60 = (undefined4)DAT_1001b30b0;
          local_5c = iVar2;
          uVar5 = _OUTLINED_FUNCTION_6();
          _OUTLINED_FUNCTION_13(uVar5,uVar4);
        }
        uVar4 = 0;
        uVar6 = (ulong)(iVar2 - 0x5213U);
        if (iVar2 - 0x5213U < 0x38) {
          in_ZR = (1L << (uVar6 & 0x3f) & 0x8428a480000000U) == 0;
          in_NG = false;
          in_OV = false;
          if (!(bool)in_ZR) goto LAB_100132140;
          if (uVar6 == 0) {
            if (extraout_w1 == 0) goto LAB_10013229c;
            auVar7 = _OUTLINED_FUNCTION_26(0);
            uVar4 = 10;
            uVar5 = 0xb;
          }
          else {
            in_OV = SBORROW8(uVar6,1);
            in_NG = (long)(uVar6 - 1) < 0;
            in_ZR = uVar6 == 1;
            if (!(bool)in_ZR) goto LAB_100132128;
            if (extraout_w1 == 0) goto LAB_10013229c;
            auVar7 = _OUTLINED_FUNCTION_26(0);
            uVar4 = 7;
            uVar5 = 8;
          }
        }
        else {
LAB_100132128:
          bVar1 = iVar2 - 0x5264U < 3;
          in_OV = !bVar1 && SBORROW4(iVar2,0x52ff);
          in_ZR = bVar1 || iVar2 == 0x52ff;
          in_NG = !bVar1 && iVar2 + -0x52ff < 0;
          if (bVar1 || iVar2 == 0x52ff) {
LAB_100132140:
            if (extraout_w1 == 0) goto LAB_10013229c;
            auVar7 = _OUTLINED_FUNCTION_26(0);
            uVar4 = 0xc;
            uVar5 = 0xd;
          }
          else {
            in_OV = SBORROW4(iVar2,0x5212);
            in_NG = iVar2 + -0x5212 < 0;
            in_ZR = iVar2 == 0x5212;
            if (!(bool)in_ZR) {
              if ((_gLogObjects == 0) || (uVar4 = _OUTLINED_FUNCTION_23(), in_NG != in_OV)) {
                _OUTLINED_FUNCTION_30();
                if (!(bool)in_ZR) {
                  _OUTLINED_FUNCTION_3();
                  _dispatch_once();
                }
                uVar4 = _OUTLINED_FUNCTION_19();
              }
              iVar2 = _os_log_type_enabled(uVar4,2);
              if (iVar2 != 0) {
                uVar5 = _OUTLINED_FUNCTION_4();
                __os_log_debug_impl(uVar5,uVar4,2,"Received plain text message",&local_60,2);
              }
              return 1;
            }
            if (extraout_w1 == 0) goto LAB_10013229c;
            auVar7 = _OUTLINED_FUNCTION_26(0);
            uVar4 = 3;
            uVar5 = 4;
          }
        }
        uVar4 = _mfi4Auth_protocol_decryptPayload(auVar7._0_8_,auVar7._8_8_,uVar4,uVar5);
        if ((int)uVar4 == 0) {
          return 1;
        }
        goto LAB_10013229c;
      }
      uVar4 = _logObjectForModule();
      iVar2 = _OUTLINED_FUNCTION_7(uVar4);
      if (iVar2 != 0) {
        _OUTLINED_FUNCTION_4();
        goto LAB_100132290;
      }
    }
  }
  uVar4 = 0;
LAB_10013229c:
  if ((_gLogObjects == 0) || (uVar4 = _OUTLINED_FUNCTION_23(uVar4), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_30();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_3();
      _dispatch_once();
    }
    uVar4 = _OUTLINED_FUNCTION_19();
  }
  iVar2 = _OUTLINED_FUNCTION_7(uVar4);
  if (iVar2 != 0) {
    _OUTLINED_FUNCTION_4();
    _OUTLINED_FUNCTION_2();
    __os_log_error_impl();
  }
  return 0;
}


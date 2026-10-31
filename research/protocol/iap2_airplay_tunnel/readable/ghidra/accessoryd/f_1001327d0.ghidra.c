/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001327d0
 * original code SHA256: f8c7096434f26b53a7ad928eb7a21262d189068f166036d4629ec7ca26da9ad6
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

undefined8 _mfi4Auth_protocol_encryptOutgoingData(long param_1)

{
  char in_NG;
  char cVar1;
  undefined1 in_ZR;
  undefined1 uVar2;
  char in_OV;
  char cVar3;
  bool bVar4;
  int iVar5;
  undefined8 uVar6;
  ulong uVar7;
  undefined8 uVar8;
  long extraout_x1;
  
  if (param_1 == 0) {
    uVar6 = _logObjectForModule();
    iVar5 = _OUTLINED_FUNCTION_7(uVar6);
    if (iVar5 == 0) {
      return 0;
    }
    _OUTLINED_FUNCTION_4();
  }
  else {
    _OUTLINED_FUNCTION_34();
    if ((bool)in_ZR) {
      uVar6 = _logObjectForModule();
      iVar5 = _OUTLINED_FUNCTION_7(uVar6);
      if (iVar5 == 0) {
        return 0;
      }
      _OUTLINED_FUNCTION_4();
    }
    else if (extraout_x1 == 0) {
      uVar6 = _logObjectForModule();
      iVar5 = _OUTLINED_FUNCTION_7(uVar6);
      if (iVar5 == 0) {
        return 0;
      }
      _OUTLINED_FUNCTION_4();
    }
    else {
      if (*(int *)(param_1 + 0xe0) == 0) {
        return 1;
      }
      iVar5 = _iAP2MsgGetMsgID(extraout_x1);
      if (iVar5 != 0) {
        if ((_gLogObjects == 0) || (uVar6 = _OUTLINED_FUNCTION_23(), in_NG != in_OV)) {
          _OUTLINED_FUNCTION_30();
          if (!(bool)in_ZR) {
            _OUTLINED_FUNCTION_3();
            _dispatch_once();
          }
          uVar6 = _OUTLINED_FUNCTION_19();
        }
        uVar7 = _os_log_type_enabled(uVar6,0);
        if ((uVar7 & 1) != 0) {
          uVar8 = _OUTLINED_FUNCTION_9(DAT_1001b30b0);
          _OUTLINED_FUNCTION_13(uVar8,uVar6);
        }
        uVar7 = (ulong)(iVar5 - 0x5112U);
        if (iVar5 - 0x5112U < 0x38) {
          if ((1L << (uVar7 & 0x3f) & 0x812e92c0000000U) != 0) goto LAB_1001328f0;
          if (uVar7 == 0) {
            iVar5 = _mfi4Auth_protocol_encryptPayload(param_1,extraout_x1,10,0xb);
            if (iVar5 == 0) {
              return 1;
            }
            uVar6 = _logObjectForModule();
            iVar5 = _OUTLINED_FUNCTION_7(uVar6);
            if (iVar5 == 0) {
              return 0;
            }
            _OUTLINED_FUNCTION_9(DAT_1001b30b0);
          }
          else {
            if (uVar7 != 1) goto LAB_1001328c0;
            iVar5 = _mfi4Auth_protocol_encryptPayload(param_1,extraout_x1,3,4);
            if (iVar5 == 0) {
              return 1;
            }
            uVar6 = _logObjectForModule();
            iVar5 = _OUTLINED_FUNCTION_7(uVar6);
            if (iVar5 == 0) {
              return 0;
            }
            _OUTLINED_FUNCTION_9(DAT_1001b30b0);
          }
        }
        else {
LAB_1001328c0:
          bVar4 = iVar5 - 0x5163U < 2;
          cVar3 = !bVar4 && SBORROW4(iVar5,0x51ff);
          uVar2 = bVar4 || iVar5 == 0x51ff;
          cVar1 = !bVar4 && iVar5 + -0x51ff < 0;
          if (!bVar4 && iVar5 != 0x51ff) {
            if ((_gLogObjects == 0) || (uVar6 = _OUTLINED_FUNCTION_23(0), cVar1 != cVar3)) {
              _OUTLINED_FUNCTION_30();
              if (!(bool)uVar2) {
                _OUTLINED_FUNCTION_3();
                _dispatch_once();
              }
              uVar6 = _OUTLINED_FUNCTION_19();
            }
            iVar5 = _os_log_type_enabled(uVar6,0);
            if (iVar5 != 0) {
              uVar8 = _OUTLINED_FUNCTION_9(DAT_1001b30b0);
              _OUTLINED_FUNCTION_13(uVar8,uVar6);
            }
            return 1;
          }
LAB_1001328f0:
          iVar5 = _mfi4Auth_protocol_encryptPayload(param_1,extraout_x1,5,6);
          if (iVar5 == 0) {
            return 1;
          }
          uVar6 = _logObjectForModule();
          iVar5 = _OUTLINED_FUNCTION_7(uVar6);
          if (iVar5 == 0) {
            return 0;
          }
          _OUTLINED_FUNCTION_9(DAT_1001b30b0);
        }
        _OUTLINED_FUNCTION_7();
        goto LAB_100132a74;
      }
      uVar6 = _logObjectForModule();
      iVar5 = _OUTLINED_FUNCTION_7(uVar6);
      if (iVar5 == 0) {
        return 0;
      }
      _OUTLINED_FUNCTION_4();
    }
  }
  _OUTLINED_FUNCTION_2();
LAB_100132a74:
  __os_log_error_impl();
  return 0;
}


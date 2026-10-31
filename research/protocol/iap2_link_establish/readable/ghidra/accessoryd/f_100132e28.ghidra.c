/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100132e28
 * original code SHA256: d703fc3597762742039b32d292d1ddcb50b467876ab4e3b01385c3e68fee805f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_protocol_initMessage_RequestAuthSetup(long param_1)

{
  undefined1 in_ZR;
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  long *extraout_x1;
  long unaff_x19;
  ulong uVar4;
  
  if (param_1 == 0) {
    uVar3 = _logObjectForModule();
    iVar1 = _OUTLINED_FUNCTION_7(uVar3);
    if (iVar1 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_13();
  }
  else {
    _OUTLINED_FUNCTION_19();
    if ((bool)in_ZR) {
      uVar3 = _logObjectForModule();
      iVar1 = _OUTLINED_FUNCTION_7(uVar3);
      if (iVar1 == 0) {
        return 1;
      }
      _OUTLINED_FUNCTION_2();
    }
    else {
      if (extraout_x1 != (long *)0x0) {
        lVar2 = _OUTLINED_FUNCTION_13();
        *extraout_x1 = lVar2;
        if (lVar2 == 0) {
          return 0xffffffff;
        }
        uVar3 = _OUTLINED_FUNCTION_37();
        _OUTLINED_FUNCTION_24(uVar3,0,0x5100);
        _iAP2MsgInitWithSom();
        _iAP2MsgAddU8Param(*extraout_x1,0,0,*(undefined1 *)(unaff_x19 + 0xac));
        _iAP2MsgAddU8Param(*extraout_x1,0,1,*(undefined1 *)(unaff_x19 + 0xad));
        _iAP2MsgAddU8Param(*extraout_x1,0,2,*(undefined1 *)(unaff_x19 + 0x24));
        if (*(long *)(unaff_x19 + 0xb8) != 0) {
          uVar4 = 0;
          do {
            _iAP2MsgAddU8Param(*extraout_x1,0,3,*(undefined1 *)(unaff_x19 + 0xae + uVar4));
            uVar4 = uVar4 + 1;
          } while (uVar4 < *(ulong *)(unaff_x19 + 0xb8));
        }
        if (*(long *)(unaff_x19 + 200) != 0) {
          uVar4 = 0;
          do {
            _iAP2MsgAddU8Param(*extraout_x1,0,4,*(undefined1 *)(unaff_x19 + 0xc0 + uVar4));
            uVar4 = uVar4 + 1;
          } while (uVar4 < *(ulong *)(unaff_x19 + 200));
        }
        *(undefined2 *)(unaff_x19 + 0x1c) = 0x5100;
        return 0;
      }
      uVar3 = _logObjectForModule();
      iVar1 = _OUTLINED_FUNCTION_7(uVar3);
      if (iVar1 == 0) {
        return 1;
      }
      _OUTLINED_FUNCTION_4();
    }
  }
  _OUTLINED_FUNCTION_21();
  __os_log_error_impl();
  return 1;
}


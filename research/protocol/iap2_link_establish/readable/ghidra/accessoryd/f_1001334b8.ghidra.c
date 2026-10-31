/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001334b8
 * original code SHA256: 149a84243e6da566beb587a9180fba63e3624582e5607880260bcabd22b7e011
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_protocol_initMessage_AuthenticationSucceeded(void)

{
  undefined2 uVar1;
  undefined1 in_ZR;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  undefined1 auVar5 [16];
  
  auVar5 = _OUTLINED_FUNCTION_34();
  if ((bool)in_ZR) {
    uVar4 = _logObjectForModule();
    iVar2 = _OUTLINED_FUNCTION_7(uVar4);
    if (iVar2 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_2();
  }
  else {
    if (auVar5._8_8_ != (long *)0x0) {
      uVar1 = *(undefined2 *)(auVar5._0_8_ + 0x150);
      lVar3 = _OUTLINED_FUNCTION_13();
      *auVar5._8_8_ = lVar3;
      if (lVar3 == 0) {
        return 0xffffffff;
      }
      uVar4 = _OUTLINED_FUNCTION_37();
      _OUTLINED_FUNCTION_24(uVar4,uVar1,0x51ff);
      _iAP2MsgInitWithSom();
      *(undefined2 *)(auVar5._0_8_ + 0x1c) = 0x51ff;
      return 0;
    }
    uVar4 = _logObjectForModule();
    iVar2 = _OUTLINED_FUNCTION_7(uVar4);
    if (iVar2 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_4();
  }
  _OUTLINED_FUNCTION_21();
  __os_log_error_impl();
  return 1;
}


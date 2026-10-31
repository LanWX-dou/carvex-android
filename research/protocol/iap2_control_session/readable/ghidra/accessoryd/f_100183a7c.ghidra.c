/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100183a7c
 * original code SHA256: ca47dc2d9fb27a80bdcc9785f4d467355c0bfb726a758f463eadf806a45117de
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_sessionFileTransfer_start(long param_1)

{
  int iVar1;
  long extraout_x8;
  int extraout_w9;
  undefined8 unaff_x20;
  undefined1 auVar2 [16];
  
  if (param_1 != 0) {
    _iap2_sessionFileTransfer_getVersion();
    _OUTLINED_FUNCTION_6();
    if (extraout_x8 == 0 || extraout_w9 < 0x1b) {
      if (_logObjectForModule_onceToken != -1) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    else {
      unaff_x20 = *(undefined8 *)(extraout_x8 + 0xd0);
    }
    iVar1 = _os_log_type_enabled(unaff_x20,1);
    if (iVar1 != 0) {
      _OUTLINED_FUNCTION_6();
      auVar2 = _OUTLINED_FUNCTION_44();
      __os_log_impl(auVar2._0_8_,auVar2._8_8_,1);
    }
  }
  return 0;
}


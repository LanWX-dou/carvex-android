/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011d7e4
 * original code SHA256: a5b954975103279a18f5237ba2c6ec62e102b5b223db6864cd3955271efa764b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_sessionControl_accAuthenticationStateChanged(long *param_1,int param_2)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  undefined8 unaff_x20;
  ulong unaff_x30;
  
  if (((param_1 != (long *)0x0) && (param_2 == 2)) && (*param_1 != 0)) {
    iVar3 = _iap2_identification_getState(param_1);
    if (iVar3 == 0) {
      _OUTLINED_FUNCTION_44();
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10011d85c);
        (*pcVar1)();
      }
      _iap2_features_startFeatureFromDevice();
      return;
    }
    iVar3 = _iap2_identification_getState(param_1);
    if (iVar3 == 6) {
      bVar2 = true;
      if ((_gLogObjects == 0) || (bVar2 = _gNumLogObjects == 0x1a, _gNumLogObjects < 0x1a)) {
        _OUTLINED_FUNCTION_9();
        if (!bVar2) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      else {
        unaff_x20 = *(undefined8 *)(_gLogObjects + 200);
      }
      iVar3 = _os_log_type_enabled(unaff_x20,1);
      if (iVar3 != 0) {
        _OUTLINED_FUNCTION_2(param_1[1],DAT_1001b3088);
        _OUTLINED_FUNCTION_4();
        __os_log_impl();
      }
      __authAndIDComplete(param_1);
    }
  }
  return;
}


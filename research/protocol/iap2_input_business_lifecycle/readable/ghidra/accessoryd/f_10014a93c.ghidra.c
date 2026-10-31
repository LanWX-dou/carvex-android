/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10014a93c
 * original code SHA256: c52ec0a16e8f4adc774c28b758fc4aa9e07db273fb9fb7fc05cd5ca13459a3ea
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 __stopNowPlayingUpdatesHandler(long param_1,long param_2)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  int iVar1;
  undefined8 uVar2;
  undefined1 *puVar3;
  long extraout_x8;
  
  uVar2 = 0;
  if ((param_1 != 0) && (param_2 != 0)) {
    puVar3 = (undefined1 *)_iap2_feature_getFeature(param_1,0xe);
    uVar2 = 0;
    if (puVar3 != (undefined1 *)0x0) {
      _OUTLINED_FUNCTION_18();
      if ((extraout_x8 == 0) || (_OUTLINED_FUNCTION_5(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_2();
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      _OUTLINED_FUNCTION_20();
      iVar1 = _os_log_type_enabled();
      if (iVar1 != 0) {
        _OUTLINED_FUNCTION_4();
        _OUTLINED_FUNCTION_44();
        _OUTLINED_FUNCTION_42();
        __os_log_debug_impl();
      }
      __pauseElapsedTimeTimer(puVar3);
      __removeSubscribersForSubFeatures(puVar3);
      *puVar3 = 0;
      puVar3[0x28] = 0;
      puVar3[0x88] = 0;
      *(undefined8 *)(puVar3 + 0x50) = 0;
      *(undefined8 *)(puVar3 + 0x58) = 0;
      if (*(long *)(puVar3 + 8) != 0) {
        _CFRelease();
        *(undefined8 *)(puVar3 + 8) = 0;
      }
      if (*(long *)(puVar3 + 0x10) != 0) {
        _CFRelease();
        *(undefined8 *)(puVar3 + 0x10) = 0;
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}


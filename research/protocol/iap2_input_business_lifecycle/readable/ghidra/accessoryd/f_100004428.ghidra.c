/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100004428
 * original code SHA256: 38f67bf829b980f89ed6062e648b023b2417b5224bcbe546e146fd0ece58c391
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



uint __convertRouteGuidanceStateTypeForFunc(undefined8 param_1)

{
  int iVar1;
  undefined *puVar2;
  
  if (6 < (uint)param_1) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x32)) {
      puVar2 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        __parseRoadSignParameter_cold_1();
        puVar2 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar2 = *(undefined **)(_gLogObjects + 0x188);
    }
    iVar1 = _os_log_type_enabled(puVar2,0x10);
    if (iVar1 != 0) {
      __convertRouteGuidanceStateTypeForFunc_cold_2(param_1,puVar2);
    }
    param_1 = 0xff;
  }
  return (uint)param_1 & 0xff;
}


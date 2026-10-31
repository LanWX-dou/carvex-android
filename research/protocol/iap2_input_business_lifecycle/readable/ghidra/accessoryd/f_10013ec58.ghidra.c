/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013ec58
 * original code SHA256: 247fd98daf54c7bc2b72ed08c00732f846ab60ae33c3011125435337411463f3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_features_startFeatureFromDevice(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined1 uVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  long extraout_x8;
  long extraout_x9;
  long extraout_x11;
  long lVar6;
  int extraout_w12;
  long *plVar7;
  code *pcVar8;
  
  _OUTLINED_FUNCTION_13();
  while( true ) {
    _OUTLINED_FUNCTION_6();
    plVar7 = *(long **)(extraout_x11 + 8);
    bVar4 = extraout_w12 != (int)param_2;
    cVar3 = '\0';
    uVar2 = bVar4 || plVar7 == (long *)0x0;
    cVar1 = !bVar4 && (long)plVar7 < 0;
    if ((!bVar4 && plVar7 != (long *)0x0) && (lVar6 = *plVar7, lVar6 != 0)) break;
    if (extraout_x9 == 1) {
      return 0;
    }
  }
  if ((*(byte *)((long)plVar7 + 0x22) & 1) == 0) {
    iVar5 = _iap2_identification_isIdentifiedForFeature(param_1,param_2);
    if (iVar5 == 0) {
      return 0;
    }
    lVar6 = *plVar7;
  }
  pcVar8 = *(code **)(lVar6 + 0x10);
  if (pcVar8 == (code *)0x0) {
    return 0;
  }
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_4(), cVar1 != cVar3)) {
    _OUTLINED_FUNCTION_1();
    if (!(bool)uVar2) {
      _OUTLINED_FUNCTION_2();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  else {
    plVar7 = *(long **)(extraout_x8 + 0xa8);
  }
  iVar5 = _os_log_type_enabled(plVar7,1);
  if (iVar5 != 0) {
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_10();
    __os_log_impl();
  }
  (*pcVar8)(param_1);
  return 0;
}


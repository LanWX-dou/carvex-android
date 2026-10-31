/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10014be18
 * original code SHA256: bfb566d75dee4df728699916e7b82703b92e74c8cb205f002f247309610cdde2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_assistiveTouch_stopAssistiveTouchUpdateHandler(long param_1,long param_2)

{
  char cVar1;
  undefined1 in_ZR;
  undefined1 uVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  long extraout_x8;
  long extraout_x8_00;
  int extraout_w9;
  long unaff_x20;
  
  uVar5 = 0;
  if ((param_1 != 0) && (param_2 != 0)) {
    _OUTLINED_FUNCTION_4(0);
    cVar3 = !(bool)in_ZR && SBORROW4(extraout_w9,0x18);
    uVar2 = !(bool)in_ZR && extraout_w9 == 0x18;
    cVar1 = (bool)in_ZR || extraout_w9 + -0x18 < 0;
    if ((bool)in_ZR || extraout_w9 < 0x18) {
      _OUTLINED_FUNCTION_9();
      if (!(bool)uVar2) {
        _OUTLINED_FUNCTION_3();
      }
      _OUTLINED_FUNCTION_27();
    }
    else {
      unaff_x20 = *(long *)(extraout_x8 + 0xb8);
    }
    iVar4 = _OUTLINED_FUNCTION_31();
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_2(*(undefined8 *)(param_1 + 8),DAT_1001b3088);
      _OUTLINED_FUNCTION_4();
      __os_log_impl();
    }
    lVar6 = _OUTLINED_FUNCTION_14();
    uVar5 = 0;
    if (lVar6 != 0) {
      _OUTLINED_FUNCTION_17();
      if ((extraout_x8_00 == 0) || (_OUTLINED_FUNCTION_16(), cVar1 != cVar3)) {
        _OUTLINED_FUNCTION_9();
        if (!(bool)uVar2) {
          _OUTLINED_FUNCTION_3();
        }
        _OUTLINED_FUNCTION_15();
      }
      iVar4 = _OUTLINED_FUNCTION_15();
      if (iVar4 != 0) {
        _OUTLINED_FUNCTION_1(*(undefined8 *)(param_1 + 8),DAT_1001b3130);
        _OUTLINED_FUNCTION_0();
        _OUTLINED_FUNCTION_7();
      }
      *(undefined1 *)(unaff_x20 + 1) = 0;
      uVar5 = 1;
    }
  }
  return uVar5;
}


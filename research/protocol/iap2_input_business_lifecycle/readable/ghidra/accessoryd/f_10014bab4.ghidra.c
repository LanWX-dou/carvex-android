/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10014bab4
 * original code SHA256: 0dbe7bb7ca05bf315c394c3bb21900736d2d3722ca327d96303364a14f9525d1
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_assistiveTouch_startAssistiveTouchHandler(long param_1,long param_2)

{
  char cVar1;
  undefined1 in_ZR;
  undefined1 uVar2;
  char cVar3;
  int iVar4;
  long lVar5;
  long extraout_x8;
  long extraout_x8_00;
  int extraout_w9;
  undefined1 *unaff_x20;
  undefined8 uVar6;
  
  uVar6 = 0;
  if ((param_1 != 0) && (param_2 != 0)) {
    _OUTLINED_FUNCTION_4();
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
      unaff_x20 = *(undefined1 **)(extraout_x8 + 0xb8);
    }
    iVar4 = _OUTLINED_FUNCTION_31();
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_2(*(undefined8 *)(param_1 + 8),DAT_1001b3088);
      _OUTLINED_FUNCTION_4();
      __os_log_impl();
    }
    lVar5 = _OUTLINED_FUNCTION_14();
    if (lVar5 == 0) {
      uVar6 = 0;
    }
    else {
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
      uVar6 = 1;
      *unaff_x20 = 1;
      _platform_assistiveTouch_setState(*(undefined8 *)(param_1 + 8),1);
    }
  }
  return uVar6;
}


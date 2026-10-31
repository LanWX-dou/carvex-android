/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10014569c
 * original code SHA256: 422349516e98a5096fbd954d64c58060343746c23a04deddb62c1f5dcea9b04d
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_nowPlaying_mediaItemAttributesUpdateHandler(long *param_1,long param_2)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  byte *pbVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  uint uVar8;
  long extraout_x8;
  undefined1 auVar9 [16];
  
  if (param_1 != (long *)0x0) {
    if (param_2 == 0) {
      return 0;
    }
    if (*param_1 == 0) {
      return 0;
    }
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
      _OUTLINED_FUNCTION_64();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    _OUTLINED_FUNCTION_13();
    iVar4 = _os_log_type_enabled();
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_6();
      auVar9 = _OUTLINED_FUNCTION_23();
      __os_log_impl(auVar9._0_8_,auVar9._8_8_,1);
    }
    _OUTLINED_FUNCTION_54();
    pbVar5 = (byte *)_iap2_feature_getFeature();
    if (pbVar5 == (byte *)0x0) {
      return 0;
    }
    uVar8 = (uint)*pbVar5;
    cVar1 = SBORROW4(uVar8,1);
    cVar2 = (int)(uVar8 - 1) < 0;
    uVar3 = uVar8 == 1;
    if ((bool)uVar3) {
      uVar6 = _OUTLINED_FUNCTION_13();
      auVar9 = _malloc_type_malloc(0xffff,0x393031c3);
      _OUTLINED_FUNCTION_48(auVar9._0_8_,auVar9._8_8_,auVar9._0_8_);
      _iAP2MsgInit();
      _OUTLINED_FUNCTION_88();
      uVar7 = _iAP2MsgAddGroupParam();
      iVar4 = __addMediaItemAttributesToMessage(uVar6,uVar7,pbVar5,param_2);
      if (iVar4 != 0) {
        _iap2_sessionControl_sendOutgoingMessage(param_1,uVar6);
        return 1;
      }
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), cVar2 != cVar1)) {
        _OUTLINED_FUNCTION_64();
        if (!(bool)uVar3) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_18();
      }
      else {
        param_1 = *(long **)(extraout_x8 + 0x110);
      }
      iVar4 = _OUTLINED_FUNCTION_90();
      if (iVar4 != 0) {
        uVar6 = _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_78(uVar6,param_1);
      }
      _OUTLINED_FUNCTION_13();
      _iAP2MsgCleanup();
      return 1;
    }
  }
  return 0;
}


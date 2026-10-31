/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100131864
 * original code SHA256: e10960c2b7986ba4d6481db7389e823ec40ce66014e9c1c6954c02df1644bf3a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_hid_sendGetReport(void)

{
  bool bVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  undefined8 uVar7;
  long unaff_x19;
  undefined1 auVar8 [16];
  undefined1 local_60 [30];
  undefined2 local_42;
  
  auVar8 = _OUTLINED_FUNCTION_33();
  lVar6 = auVar8._8_8_;
  uVar7 = auVar8._0_8_;
  if ((unaff_x19 != 0) && (lVar6 != 0)) {
    lVar3 = _OUTLINED_FUNCTION_25();
    uVar7 = 0;
    if (lVar3 != 0) {
      _OUTLINED_FUNCTION_19();
      lVar4 = _CFDictionaryGetValue(lVar6);
      lVar5 = _CFDictionaryGetValue(lVar6,_kCFAccessoryHID_ReportType);
      lVar6 = _CFDictionaryGetValue(lVar6,_kCFAccessoryHID_ReportID);
      local_42 = 0;
      if (lVar4 != 0) {
        _CFNumberGetValue(lVar4,8,&local_42);
      }
      if ((*(long *)(lVar3 + 8) == 0) ||
         (lVar3 = _CFDictionaryGetValue(*(long *)(lVar3 + 8),lVar4), lVar3 == 0)) {
        _logObjectForModule();
        uVar7 = _OUTLINED_FUNCTION_8();
        if ((int)uVar7 == 0) {
          return uVar7;
        }
        _OUTLINED_FUNCTION_2();
        _OUTLINED_FUNCTION_1(DAT_1001b30f8);
        _OUTLINED_FUNCTION_8();
        __os_log_error_impl();
      }
      else if ((*(byte *)(lVar3 + 0x18) & 1) == 0) {
        uVar7 = _logObjectForModule();
        uVar7 = _os_log_type_enabled(uVar7,0);
        if ((int)uVar7 == 0) {
          return uVar7;
        }
        _OUTLINED_FUNCTION_2();
        _OUTLINED_FUNCTION_1(DAT_1001b30f8);
        _OUTLINED_FUNCTION_23();
      }
      else {
        uVar7 = _OUTLINED_FUNCTION_31();
        _OUTLINED_FUNCTION_17(uVar7,0x6804);
        bVar1 = false;
        if (lVar4 != 0) {
          lVar3 = _OUTLINED_FUNCTION_14();
          bVar1 = lVar3 != 0;
        }
        bVar2 = false;
        if (lVar5 != 0) {
          local_60[0] = 0;
          _CFNumberGetValue(lVar5,7,local_60);
          auVar8 = _OUTLINED_FUNCTION_20();
          lVar3 = _iAP2MsgAddU8Param(auVar8._0_8_,auVar8._8_8_,1);
          bVar2 = lVar3 != 0;
        }
        if (lVar6 != 0) {
          _OUTLINED_FUNCTION_35();
          auVar8 = _OUTLINED_FUNCTION_20();
          lVar6 = _iAP2MsgAddU8Param(auVar8._0_8_,auVar8._8_8_,2);
          if (!(bool)(bVar1 & bVar2)) {
            return 0;
          }
          if (lVar6 == 0) {
            return 0;
          }
          _OUTLINED_FUNCTION_4(0);
          uVar7 = _iap2_sessionControl_sendOutgoingMessage();
          return uVar7;
        }
      }
      uVar7 = 0;
    }
  }
  return uVar7;
}


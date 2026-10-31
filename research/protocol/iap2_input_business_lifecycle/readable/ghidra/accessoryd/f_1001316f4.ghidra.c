/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001316f4
 * original code SHA256: 10f1d69410b9aba080c7c89222963542baa9494a0bdfa94c1235ebe8c6affd65
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_hid_sendOutReport(void)

{
  undefined2 uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  long unaff_x19;
  undefined1 auVar6 [16];
  undefined2 local_32;
  
  auVar6 = _OUTLINED_FUNCTION_33();
  lVar4 = auVar6._8_8_;
  if (unaff_x19 == 0) {
    return auVar6._0_8_;
  }
  if (lVar4 == 0) {
    return auVar6._0_8_;
  }
  lVar2 = _OUTLINED_FUNCTION_25();
  if (lVar2 == 0) {
    return 0;
  }
  lVar3 = _CFDictionaryGetValue(lVar4,_kCFAccessoryHID_Report);
  _OUTLINED_FUNCTION_19();
  lVar4 = _CFDictionaryGetValue(lVar4);
  local_32 = 0;
  if (lVar4 != 0) {
    _CFNumberGetValue(lVar4,8,&local_32);
    if ((*(long *)(lVar2 + 8) != 0) &&
       (lVar4 = _CFDictionaryGetValue(*(long *)(lVar2 + 8),lVar4), lVar4 != 0)) {
      if ((*(byte *)(lVar4 + 0x18) & 1) == 0) {
        uVar5 = _logObjectForModule();
        uVar5 = _os_log_type_enabled(uVar5,0);
        if ((int)uVar5 != 0) {
          _OUTLINED_FUNCTION_2();
          _OUTLINED_FUNCTION_1(DAT_1001b30f8);
          _OUTLINED_FUNCTION_23();
          return 0;
        }
        return uVar5;
      }
      uVar5 = _OUTLINED_FUNCTION_31();
      _OUTLINED_FUNCTION_17(uVar5,0x6801);
      lVar4 = _OUTLINED_FUNCTION_14();
      if (lVar3 == 0) {
        return 0;
      }
      uVar5 = _CFDataGetBytePtr(lVar3);
      uVar1 = _CFDataGetLength(lVar3);
      lVar2 = _iAP2MsgAddDataParam(unaff_x19 + 0x80,0,1,uVar5,uVar1);
      if (lVar4 == 0) {
        return 0;
      }
      if (lVar2 != 0) {
        _OUTLINED_FUNCTION_4(0);
        uVar5 = _iap2_sessionControl_sendOutgoingMessage();
        return uVar5;
      }
      return 0;
    }
  }
  _logObjectForModule();
  uVar5 = _OUTLINED_FUNCTION_8();
  if ((int)uVar5 != 0) {
    _OUTLINED_FUNCTION_2();
    _OUTLINED_FUNCTION_1(DAT_1001b30f8);
    _OUTLINED_FUNCTION_8();
    __os_log_error_impl();
    return 0;
  }
  return uVar5;
}


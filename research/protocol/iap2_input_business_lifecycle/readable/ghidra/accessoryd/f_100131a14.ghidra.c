/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100131a14
 * original code SHA256: 9a2d212996b761602459920798051956c4dd1341df8f05ae422fa7284e83c83f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_hid_sendComponentUpdate(void)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  bool bVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long unaff_x19;
  undefined *puVar7;
  undefined1 auVar8 [16];
  undefined1 auStack_60 [29];
  char local_43;
  undefined2 local_42;
  
  auVar8 = _OUTLINED_FUNCTION_33();
  lVar4 = auVar8._8_8_;
  uVar6 = auVar8._0_8_;
  if ((unaff_x19 != 0) && (lVar4 != 0)) {
    _OUTLINED_FUNCTION_19();
    lVar3 = _CFDictionaryGetValue(lVar4);
    lVar4 = _CFDictionaryGetValue(lVar4,_kCFAccessoryHID_ComponentEnabled);
    local_42 = 0;
    if (lVar3 != 0) {
      _CFNumberGetValue(lVar3,8,&local_42);
    }
    local_43 = '\0';
    if (lVar4 != 0) {
      _CFNumberGetValue(lVar4,7,&local_43);
    }
    lVar5 = _OUTLINED_FUNCTION_25();
    if (lVar5 != 0) {
      if ((*(long *)(lVar5 + 8) == 0) ||
         (lVar5 = _CFDictionaryGetValue(*(long *)(lVar5 + 8),lVar3), lVar5 == 0)) {
        _OUTLINED_FUNCTION_18();
        if ((extraout_x8_01 == 0) || (_OUTLINED_FUNCTION_11(), in_NG != in_OV)) {
          _OUTLINED_FUNCTION_7();
          puVar7 = PTR___os_log_default_10022bbb0;
          if (!(bool)in_ZR) {
            _OUTLINED_FUNCTION_5();
            _dispatch_once();
            puVar7 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar7 = *(undefined **)(extraout_x8_02 + 0x118);
        }
        iVar2 = _os_log_type_enabled(puVar7,0x10);
        if (iVar2 != 0) {
          _OUTLINED_FUNCTION_2();
          uVar6 = _OUTLINED_FUNCTION_1(DAT_1001b30f8);
          __os_log_error_impl(uVar6,puVar7,0x10,
                              "Could not find HID component! (connectionUUID: %@, endpointUUID: %@, componentID: %d)"
                              ,auStack_60,0x1c);
        }
      }
      else {
        _OUTLINED_FUNCTION_18();
        if ((extraout_x8 == 0) || (_OUTLINED_FUNCTION_11(), in_NG != in_OV)) {
          _OUTLINED_FUNCTION_7();
          puVar7 = PTR___os_log_default_10022bbb0;
          if (!(bool)in_ZR) {
            _OUTLINED_FUNCTION_5();
            _dispatch_once();
            puVar7 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar7 = *(undefined **)(extraout_x8_00 + 0x118);
        }
        iVar2 = _os_log_type_enabled(puVar7,0);
        if (iVar2 != 0) {
          _OUTLINED_FUNCTION_2();
          uVar6 = _OUTLINED_FUNCTION_1(DAT_1001b30f8);
          __os_log_impl(uVar6,puVar7,0,
                        "Marking HID component as enabled... (connectionUUID: %@, endpointUUID: %@, componentID: %d)"
                        ,auStack_60,0x1c);
        }
        *(bool *)(lVar5 + 0x1a) = local_43 != '\0';
      }
    }
    uVar6 = _OUTLINED_FUNCTION_31();
    _OUTLINED_FUNCTION_17(uVar6,0x6807);
    bVar1 = false;
    if (lVar3 != 0) {
      lVar3 = _OUTLINED_FUNCTION_14();
      bVar1 = lVar3 != 0;
    }
    if (lVar4 != 0) {
      _OUTLINED_FUNCTION_35();
      auVar8 = _OUTLINED_FUNCTION_20();
      lVar4 = _iAP2MsgAddU8Param(auVar8._0_8_,auVar8._8_8_,1);
      bVar1 = (bool)(bVar1 ^ 1);
      if (lVar4 == 0) {
        bVar1 = true;
      }
      if (!bVar1) {
        _OUTLINED_FUNCTION_4();
        uVar6 = _iap2_sessionControl_sendOutgoingMessage();
        return uVar6;
      }
    }
    uVar6 = 0;
  }
  return uVar6;
}


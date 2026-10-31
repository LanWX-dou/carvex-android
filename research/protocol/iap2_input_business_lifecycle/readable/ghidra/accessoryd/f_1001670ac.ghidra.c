/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001670ac
 * original code SHA256: 8611fcb76ee6060c8e7ddcc1448edec2282aaee64beb1888d6adc3bb67947101
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_vehicle_startStatusUpdatesHandler(long *param_1)

{
  undefined1 in_ZR;
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  undefined8 uVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  undefined *puVar12;
  undefined1 auVar13 [16];
  uint local_70;
  long local_6c;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if (*param_1 != 0) {
    if ((_gLogObjects == 0) || (in_ZR = _gNumLogObjects == 0x2c, _gNumLogObjects < 0x2c)) {
      _OUTLINED_FUNCTION_6();
      puVar12 = PTR___os_log_default_10022bbb0;
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_3();
        _dispatch_once();
        puVar12 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar12 = *(undefined **)(_gLogObjects + 0x158);
    }
    iVar5 = _os_log_type_enabled(puVar12,0);
    if (iVar5 != 0) {
      local_6c = param_1[1];
      local_70 = (uint)DAT_1001b3088;
      uVar6 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar6,puVar12,0,"Starting vehicle status updates for endpoint %@!",&local_70,0xc
                   );
    }
    _OUTLINED_FUNCTION_14();
    lVar7 = _iap2_feature_getFeature();
    if (lVar7 == 0) {
      return 0;
    }
    if ((*(byte *)(lVar7 + 0x89) & 1) == 0) {
      _logObjectForModule();
      uVar6 = _OUTLINED_FUNCTION_7();
      if ((int)uVar6 == 0) {
        return uVar6;
      }
      local_70 = local_70 & 0xffff0000;
      _OUTLINED_FUNCTION_6();
    }
    else {
      if (*(char *)(lVar7 + 0x8a) != '\x01') {
        *(undefined1 *)(lVar7 + 0x8a) = 1;
        _iAP2MsgInit(param_1 + 0x10,0xa100,param_1[0x19],0xffff,0,0);
        if (*(long *)(lVar7 + 0x10) == 0) {
          bVar4 = false;
          bVar3 = false;
          bVar2 = false;
          bVar1 = false;
        }
        else {
          _CFArrayGetCount();
          local_70 = local_70 & 0xffffff00;
          lVar8 = _OUTLINED_FUNCTION_15();
          local_70._0_1_ = 1;
          lVar9 = _OUTLINED_FUNCTION_15();
          local_70._0_1_ = 2;
          lVar10 = _OUTLINED_FUNCTION_15();
          local_70 = CONCAT31(local_70._1_3_,3);
          lVar11 = _OUTLINED_FUNCTION_15();
          _OUTLINED_FUNCTION_11();
          iVar5 = _CFArrayContainsValue();
          bVar1 = iVar5 != 0;
          _OUTLINED_FUNCTION_11();
          iVar5 = _CFArrayContainsValue();
          bVar2 = iVar5 != 0;
          _OUTLINED_FUNCTION_11();
          iVar5 = _CFArrayContainsValue();
          bVar3 = iVar5 != 0;
          _OUTLINED_FUNCTION_11();
          iVar5 = _CFArrayContainsValue();
          bVar4 = iVar5 != 0;
          if (lVar8 != 0) {
            _CFRelease(lVar8);
          }
          if (lVar9 != 0) {
            _CFRelease(lVar9);
          }
          if (lVar10 != 0) {
            _CFRelease(lVar10);
          }
          if (lVar11 != 0) {
            _CFRelease(lVar11);
          }
        }
        if (*(char *)(lVar7 + 0x78) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,3);
        }
        if (*(char *)(lVar7 + 0x79) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,4);
        }
        if (*(char *)(lVar7 + 0x7a) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,6);
        }
        if ((*(byte *)(lVar7 + 0x7b) & bVar1) != 0) {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,9);
        }
        if ((*(byte *)(lVar7 + 0x7c) & bVar2) != 0) {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,10);
        }
        if ((*(byte *)(lVar7 + 0x7d) & bVar3) != 0) {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0xb);
        }
        if ((*(byte *)(lVar7 + 0x7e) & bVar4) != 0) {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0xc);
        }
        if (*(char *)(lVar7 + 0x83) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0x11);
        }
        if ((*(byte *)(lVar7 + 0x7f) & bVar1) != 0) {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0xd);
        }
        if ((*(byte *)(lVar7 + 0x80) & bVar2) != 0) {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0xe);
        }
        if ((*(byte *)(lVar7 + 0x81) & bVar3) != 0) {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0xf);
        }
        if ((*(byte *)(lVar7 + 0x82) & bVar4) != 0) {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0x10);
        }
        if (*(char *)(lVar7 + 0x84) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0x12);
        }
        if (*(char *)(lVar7 + 0x85) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0x13);
        }
        if (*(char *)(lVar7 + 0x86) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0x14);
        }
        if (*(char *)(lVar7 + 0x87) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0x15);
        }
        if (*(char *)(lVar7 + 0x88) == '\x01') {
          auVar13 = _OUTLINED_FUNCTION_33();
          _iAP2MsgAddVoidParam(auVar13._0_8_,auVar13._8_8_,0x1e);
        }
        uVar6 = _iap2_sessionControl_sendOutgoingMessage(param_1,param_1 + 0x10);
        return uVar6;
      }
      _logObjectForModule();
      uVar6 = _OUTLINED_FUNCTION_7();
      if ((int)uVar6 == 0) {
        return uVar6;
      }
      local_70 = local_70 & 0xffff0000;
      _OUTLINED_FUNCTION_6();
    }
    _OUTLINED_FUNCTION_7();
    __os_log_error_impl();
  }
  return 0;
}


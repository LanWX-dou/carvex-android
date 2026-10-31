/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000d3094
 * original code SHA256: 7fcc1f16b3f62b80106e6222a309aad3aafd919c50a4ae32a306c8936a34e19e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

long _mfi4Auth_protocol_parse(long param_1,long param_2,long param_3,undefined8 param_4)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  
  if (param_1 == 0) {
    uVar4 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar4,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_parse_cold_4(uVar4);
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    uVar4 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar4,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_parse_cold_3(uVar4);
    }
  }
  else if (param_2 == 0) {
    uVar4 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar4,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_parse_cold_2(uVar4);
    }
  }
  else if (param_3 == 0) {
    uVar4 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar4,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_parse_cold_1(uVar4);
    }
  }
  else {
    uVar2 = _CFDataGetLength(param_3);
    lVar3 = _CFDataGetBytePtr(param_3);
    _iAP2MsgInitWithSom(param_2,param_4,0,0,0,0,0);
    uVar4 = _iAP2MsgParserInit(0xffff,*(undefined8 *)(param_1 + 8),0,param_4);
    uVar2 = uVar2 & 0xffffffff;
    if (uVar2 != 0) {
      lVar6 = 0;
      do {
        lVar5 = _iAP2MsgParserConsumeByte(uVar4,*(undefined1 *)(lVar3 + lVar6),param_2);
        if (lVar5 != 0) {
          return lVar5;
        }
        lVar6 = lVar6 + 1;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
  }
  return 0;
}


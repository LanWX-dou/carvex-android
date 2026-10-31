/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100048a1c
 * original code SHA256: 2f929fab803d302787f4f710cb532bfcefc47bfd214772274645a69aa85e881f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */

ulong _mfi4Auth_protocol_handle_AuthFinish(long param_1,long param_2,undefined8 param_3)

{
  int iVar1;
  long lVar2;
  ulong uVar3;
  undefined8 uVar4;
  byte local_35;
  uint local_34;
  
  local_34 = 1;
  if (param_1 == 0) {
    uVar4 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar4,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_handle_AuthFinish_cold_4(uVar4);
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    uVar4 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar4,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_handle_AuthFinish_cold_3(uVar4);
    }
  }
  else if (param_2 == 0) {
    uVar4 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar4,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_handle_AuthFinish_cold_2(uVar4);
    }
  }
  else {
    local_35 = 0;
    lVar2 = _iAP2MsgGetFirstParam(param_2,0);
    do {
      if (lVar2 == 0) {
        uVar3 = _mfi4Auth_protocol_initMessage_RequestAuthCert(param_1,param_3,0);
        local_34 = (uint)uVar3;
        if (local_34 == 0) {
          return uVar3;
        }
        uVar4 = _logObjectForModule();
        iVar1 = _os_log_type_enabled(uVar4,0x10);
        if (iVar1 != 0) {
          _mfi4Auth_protocol_handle_AuthFinish_cold_1(uVar4);
        }
        break;
      }
      iVar1 = _iAP2MsgGetParamID(lVar2);
      if (iVar1 == 1) {
        iVar1 = _iAP2MsgGetDataAsArrayU8(lVar2,&local_34,param_1 + 0x270,0x40);
        if (local_34 != 0) goto LAB_100048afc;
        if (iVar1 != 0x40) goto LAB_100048b4c;
      }
      else if (iVar1 == 0) {
        iVar1 = _iAP2MsgGetDataAsArrayU8(lVar2,&local_34,param_1 + 0x21c,0x20);
        if (local_34 != 0) goto LAB_100048afc;
        if (iVar1 != 0x20) goto LAB_100048b4c;
      }
      lVar2 = _iAP2MsgGetNextParamWithError(param_2,0,lVar2,&local_35);
    } while ((local_35 & 1) == 0);
  }
  if (local_34 == 0) {
LAB_100048b4c:
    uVar3 = 0;
  }
  else {
LAB_100048afc:
    _mfi4Auth_protocol_handle_AuthState(param_1,1);
    uVar3 = (ulong)local_34;
  }
  return uVar3;
}


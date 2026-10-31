/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100048bd8
 * original code SHA256: f7dc5c3cf3b7fee8f1abed95e6b9b4feb93523fd1f337c152920af1934f02a9c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _mfi4Auth_protocol_handle_AuthChallengeResponse(long param_1,long param_2,undefined8 param_3)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  byte local_45;
  int local_44;
  
  local_44 = 1;
  if (param_1 == 0) {
    _mfi4Auth_protocol_handle_AuthChallengeResponse_cold_3();
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    _mfi4Auth_protocol_handle_AuthChallengeResponse_cold_2();
  }
  else if (param_2 == 0) {
    _mfi4Auth_protocol_handle_AuthChallengeResponse_cold_1();
  }
  else {
    lVar2 = _iAP2MsgGetFirstParam(param_2,0);
    uVar3 = 0;
    local_45 = 0;
    do {
      if (lVar2 == 0) {
        if (uVar3 == 7) {
          _mfi4Auth_protocol_initMessage_RequestAuthCert(param_1,param_3,0);
          return 0;
        }
        local_44 = -1;
        goto LAB_100048d04;
      }
      iVar1 = _iAP2MsgGetParamID(lVar2);
      if (iVar1 == 2) {
        *(undefined8 *)(param_1 + 0x338) = 0x20;
        iVar1 = _iAP2MsgGetDataAsArrayU8(lVar2,&local_44,param_1 + 0x318,0x20);
        if ((local_44 != 0) || (iVar1 != 0x20)) break;
        uVar3 = uVar3 | 4;
      }
      else if (iVar1 == 1) {
        iVar1 = _iAP2MsgGetDataAsArrayU8(lVar2,&local_44,param_1 + 0x2b0,0x10);
        if ((local_44 != 0) || (iVar1 != 0x10)) break;
        uVar3 = uVar3 | 2;
      }
      else if (iVar1 == 0) {
        iVar1 = _iAP2MsgGetDataAsArrayU8(lVar2,&local_44,param_1 + 0x2d0,0x40);
        if ((local_44 != 0) || (iVar1 != 0x40)) break;
        uVar3 = uVar3 | 1;
      }
      lVar2 = _iAP2MsgGetNextParamWithError(param_2,0,lVar2,&local_45);
    } while ((local_45 & 1) == 0);
    if (local_44 == 0) {
      return 0;
    }
  }
LAB_100048d04:
  _mfi4Auth_protocol_handle_AuthState(param_1,1);
  return local_44;
}


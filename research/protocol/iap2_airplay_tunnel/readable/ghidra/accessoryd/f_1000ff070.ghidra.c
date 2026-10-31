/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000ff070
 * original code SHA256: d7bfd184be4f05fff316c1275b8c7286eeb8f13ea584b30957d0dbb7141ff97c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _mfi4Auth_protocol_messageHandler_sendOutgoingData(undefined8 *param_1,long param_2)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  
  if (param_1 == (undefined8 *)0x0) {
    uVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if ((int)uVar2 == 0) {
      return uVar2;
    }
    _mfi4Auth_protocol_messageHandler_sendOutgoingData_cold_3();
  }
  else if (*(char *)((long)param_1 + 0x1e) == '\x01') {
    uVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if ((int)uVar2 == 0) {
      return uVar2;
    }
    _mfi4Auth_protocol_messageHandler_sendOutgoingData_cold_2();
  }
  else {
    if (param_2 != 0) {
      lVar3 = param_1[0x25];
      if (lVar3 != 0) {
        uVar4 = *param_1;
        uVar2 = _iAP2MsgGetSom(param_2);
        (**(code **)(lVar3 + 0x10))(lVar3,uVar4,uVar2,param_2,0,0,0,0,0,0);
      }
      uVar2 = _mfi4Auth_protocol_encryptOutgoingData(param_1,param_2);
      if ((int)uVar2 == 0) {
        return uVar2;
      }
      iVar1 = _mfi4Auth_util_packetLoggingEncryptedData();
      if ((iVar1 != 0) && (lVar3 = param_1[0x25], lVar3 != 0)) {
        uVar4 = *param_1;
        uVar2 = _iAP2MsgGetSom(param_2);
        (**(code **)(lVar3 + 0x10))(lVar3,uVar4,uVar2,param_2,0,1,0,0,0,0);
      }
      lVar3 = param_1[0x20];
      if (lVar3 != 0) {
        (**(code **)(lVar3 + 0x10))(lVar3,*param_1,param_2);
      }
      return 1;
    }
    uVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if ((int)uVar2 == 0) {
      return uVar2;
    }
    _mfi4Auth_protocol_messageHandler_sendOutgoingData_cold_1();
  }
  return 0;
}


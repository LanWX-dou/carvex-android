/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100084da8
 * original code SHA256: 1b841211c3009d102650b57059d9fe91bbd4e8d988a6fe44fd6fc93c09dafdfd
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient(long param_1,ulong param_2,long param_3)

{
  void *pvVar1;
  int iVar2;
  void *local_38;
  
  local_38 = (void *)0x0;
  if (param_1 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient_cold_6();
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient_cold_5();
    }
  }
  else if (param_3 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient_cold_4();
    }
  }
  else if ((uint)param_2 < 3) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,2);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient_cold_2(param_1,param_3,param_2);
    }
    if (*(long *)(param_1 + 0xe8 + (param_2 & 0xffffffff) * 8) == 0) {
      iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
      if (iVar2 != 0) {
        _mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient_cold_3();
      }
    }
    else {
      _mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote_TypeData(param_1,&local_38,param_2,param_3);
      pvVar1 = local_38;
      _mfi4Auth_protocol_messageHandler_sendOutgoingData(param_1,local_38);
      if (pvVar1 != (void *)0x0) {
        _free(pvVar1);
      }
    }
  }
  else {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient_cold_1(param_2);
    }
  }
  return 0;
}


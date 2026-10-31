/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000ff27c
 * original code SHA256: acb6e2d30a5f1b0c42e132bf6f70a6040e006556b2790308366dff8fe43d9e5a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _mfi4Auth_protocol_messageHandler_handleOutgoingSecureTunnelDataForClient
               (long param_1,undefined8 param_2,long param_3)

{
  code *pcVar1;
  int iVar2;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_handleOutgoingSecureTunnelDataForClient_cold_5();
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_handleOutgoingSecureTunnelDataForClient_cold_4();
    }
  }
  else if (param_3 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_handleOutgoingSecureTunnelDataForClient_cold_3();
    }
  }
  else if ((uint)param_2 < 3) {
    if (((uint)param_2 - 1 & 0xff) < 2) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000ff310);
        (*pcVar1)();
      }
      _mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient(param_1,param_2);
      return;
    }
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_handleOutgoingSecureTunnelDataForClient_cold_2();
    }
  }
  else {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_setEndpointSecureTunnelDataReceiveTypeHandler_cold_1
                (param_2);
    }
  }
  return;
}


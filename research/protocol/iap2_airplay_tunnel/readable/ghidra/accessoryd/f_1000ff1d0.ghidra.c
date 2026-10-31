/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000ff1d0
 * original code SHA256: 64a23cfb3c6688e95b06560a86e20a03cbafeb0e432d467058cdd8c8f60e6df7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_mfi4Auth_protocol_messageHandler_setEndpointSecureTunnelDataReceiveTypeHandler
          (long param_1,undefined8 param_2,long param_3)

{
  code *pcVar1;
  int iVar2;
  undefined8 uVar3;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_setEndpointSecureTunnelDataReceiveTypeHandler_cold_3();
    }
  }
  else if (param_3 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_handleOutgoingSecureTunnelDataForClient_cold_3();
    }
  }
  else {
    if ((uint)param_2 < 3) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000ff210);
        (*pcVar1)();
      }
      uVar3 = _mfi4Auth_protocol_setSecureTunnelDataReceiveTypeHandler(param_1,param_2);
      return uVar3;
    }
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_setEndpointSecureTunnelDataReceiveTypeHandler_cold_1
                (param_2);
    }
  }
  return 0;
}


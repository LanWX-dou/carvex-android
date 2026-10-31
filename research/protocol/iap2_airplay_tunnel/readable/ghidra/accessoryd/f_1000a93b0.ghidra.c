/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000a93b0
 * original code SHA256: 4880fc22b486bc0e0b157fd59d63d576375e3f2b0070b0ec936603215565ae45
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _mfi4Auth_endpoint_setEndpointSecureTunnelDataReceiveTypeHandler
                (long param_1,undefined8 param_2,long param_3)

{
  code *pcVar1;
  ulong uVar2;
  ulong unaff_x30;
  byte local_12;
  byte local_11;
  
  if (param_1 == 0) {
    _mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_cold_4(&local_11);
    local_12 = local_11;
  }
  else {
    if (param_3 != 0) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000a93e8);
        (*pcVar1)();
      }
      uVar2 = _mfi4Auth_protocol_messageHandler_setEndpointSecureTunnelDataReceiveTypeHandler
                        (*(undefined8 *)(*(long *)(param_1 + 0x38) + 8));
      return uVar2;
    }
    _mfi4Auth_endpoint_setEndpointSecureTunnelDataReceiveTypeHandler_cold_1(&local_12);
  }
  return (ulong)local_12;
}


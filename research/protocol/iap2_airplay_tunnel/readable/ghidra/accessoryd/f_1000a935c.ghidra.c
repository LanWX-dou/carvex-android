/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000a935c
 * original code SHA256: 161e580361fa99ff09d1999a4df23f2c5e5939ff9c79b9301c6f93b0edab1607
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void ___mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_block_invoke(long param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  
  _mfi4Auth_protocol_messageHandler_handleOutgoingSecureTunnelDataForClient
            (*(undefined8 *)(*(long *)(param_1 + 0x20) + 8),*(undefined1 *)(param_1 + 0x30),
             *(undefined8 *)(param_1 + 0x28));
  if (*(long *)(param_1 + 0x28) == 0) {
    return;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000a93a0);
    (*pcVar1)();
  }
  _CFRelease();
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000cb158
 * original code SHA256: 12beb2a8570d7de5037702a7191c559cca0e9c5e779f044bf1279c307a0a3cd9
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkRunLoopAttached(long param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    return;
  }
  _iAP2LinkRunLoopSetEventMaskBit(param_1,1);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000cb19c);
    (*pcVar1)();
  }
  _iAP2LinkRunLoopSignal(param_1,0,0);
  return;
}


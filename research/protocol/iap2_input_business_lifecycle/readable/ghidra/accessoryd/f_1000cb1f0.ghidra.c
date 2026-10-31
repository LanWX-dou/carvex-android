/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000cb1f0
 * original code SHA256: 929c0c99ad062b723bf1b08c5b596709e879749352da2ad9f4c5e22482797412
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkRunLoopHandleSuspend(long param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    return;
  }
  _iAP2LinkRunLoopSetEventMaskBit(param_1,4);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000cb234);
    (*pcVar1)();
  }
  _iAP2LinkRunLoopRunOnce(param_1,0,0);
  return;
}


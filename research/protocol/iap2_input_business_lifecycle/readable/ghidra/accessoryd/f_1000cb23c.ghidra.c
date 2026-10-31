/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000cb23c
 * original code SHA256: 29849bed407e67b887913059cb6b3a0675f358686c9d850e63db2997fde6c8c7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkRunLoopHandleResume(long param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    return;
  }
  _iAP2LinkRunLoopSetEventMaskBit(param_1,8);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000cb280);
    (*pcVar1)();
  }
  _iAP2LinkRunLoopRunOnce(param_1,0,0);
  return;
}


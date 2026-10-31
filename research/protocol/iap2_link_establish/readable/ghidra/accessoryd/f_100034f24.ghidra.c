/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034f24
 * original code SHA256: 76e01055ece1b46c01411ef55f0adde7cabb509e55f4efa2593634de89555080
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkHandleTimeout(long param_1,undefined8 param_2,undefined8 param_3)

{
  code *pcVar1;
  ulong unaff_x30;
  
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    _iAP2LinkHandleTimeout_cold_1();
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100034f3c);
    (*pcVar1)();
  }
  _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),param_3);
  return;
}


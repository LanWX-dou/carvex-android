/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10003286c
 * original code SHA256: c6b5631b0e9b58a6e7b7f7975b27b0d32323bd6d42ffa898eb71c5bc36fed379
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkActionNotifyConnectionFail(long param_1,undefined1 *param_2)

{
  code *pcVar1;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    _iAP2LinkActionNotifyConnectionFail_cold_2();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000328a4);
      (*pcVar1)();
    }
    _iAP2LinkConnectedCB(*(undefined8 *)(param_1 + 0x10),0);
    return;
  }
                    /* WARNING: Subroutine does not return */
  _iAP2LinkActionNotifyConnectionFail_cold_1();
}


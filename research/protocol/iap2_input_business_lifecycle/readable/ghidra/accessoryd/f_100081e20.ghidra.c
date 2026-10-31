/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100081e20
 * original code SHA256: 087aa38942ad9cd47ebc16960af4e98ab6a40db518762e8702ffe11c69c1b477
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _OUTLINED_FUNCTION_77(void)

{
  code *pcVar1;
  undefined4 unaff_w19;
  long unaff_x29;
  ulong unaff_x30;
  
  *(undefined4 *)(unaff_x29 + -0x54) = unaff_w19;
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100081e38);
    (*pcVar1)();
  }
  _iAP2MsgGetDataAsU32();
  return;
}


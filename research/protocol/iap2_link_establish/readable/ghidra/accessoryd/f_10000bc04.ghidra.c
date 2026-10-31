/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000bc04
 * original code SHA256: a5b8225dab2f354879bb38bc6fc6896bea1ed30ba4d945208c37c9b0c72edf3e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkActionHandleACK(long param_1,undefined1 *param_2)

{
  if (param_1 == 0) {
    _iAP2LinkActionHandleACK_cold_2();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    return;
  }
                    /* WARNING: Subroutine does not return */
  _iAP2LinkActionHandleACK_cold_1();
}


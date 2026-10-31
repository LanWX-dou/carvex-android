/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000328b0
 * original code SHA256: a6925aa53bbd56bb700989dbb84c345e8c379540e0f7841e390e309fbf53daf7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkSetDefaultSYNParam(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    param_1[1] = 0x3e8ffff;
    *(undefined2 *)(param_1 + 2) = 10;
    *param_1 = (int)DAT_1001b3348;
    *(undefined4 *)((long)param_1 + 10) = 0xffff0100;
  }
  return;
}


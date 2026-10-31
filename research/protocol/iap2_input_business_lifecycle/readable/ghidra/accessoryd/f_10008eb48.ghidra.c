/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008eb48
 * original code SHA256: b49f90c3af43944eaa0cec4ee54bec1da3b0ae56fd0e957b8d6a4f0e5a5c8e77
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined2 *
_iAP2MsgParserInit(undefined2 param_1,undefined2 *param_2,undefined8 param_3,undefined2 param_4)

{
  *param_2 = 0;
  param_2[1] = param_1;
  *(undefined2 **)(param_2 + 4) = param_2 + 0x10;
  *(undefined8 *)(param_2 + 8) = param_3;
  param_2[0xc] = param_4;
  return param_2;
}


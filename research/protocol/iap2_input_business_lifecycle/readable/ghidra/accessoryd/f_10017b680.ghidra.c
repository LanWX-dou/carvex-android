/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10017b680
 * original code SHA256: 29334272fd35650937f353d888573fd74d3099ba59e96e871e68734dd718e288
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _acc_protocolParser_iAP2_reset(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = 0;
    *(undefined2 *)(param_1 + 1) = 0;
    *(undefined1 *)((long)param_1 + 6) = 0;
    *(undefined8 *)(param_1 + 2) = 0;
    *(undefined2 *)(param_1 + 4) = 0;
    *(undefined1 *)((long)param_1 + 0x12) = 0;
  }
  return param_1 != (undefined4 *)0x0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be4c03c
 * original code SHA256: 850ae24298f6f23589fb59b0fe9065edee6319daeea9e86d59eef4d2494cb947
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _HTTPMessageGetHeaderField
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6)

{
  _HTTPGetHeaderField(param_1 + 0x18,*(undefined8 *)(param_1 + 0x2018),param_2,param_3,param_4,
                      param_5,param_6,0);
  return;
}


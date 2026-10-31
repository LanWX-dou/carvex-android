/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005fcaf8
 * original code SHA256: 2cd2ac3b45716899b77b2798482fd2a5e247cc2b3b99f332887e9b3e13e2a86d
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined1 FUN_1005fcaf8(long param_1)

{
  undefined1 uVar1;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  uStack_30 = 0;
  uStack_28 = 0;
  FUN_100006ef8(&uStack_30,param_1);
  uVar1 = *(undefined1 *)(param_1 + 0x647);
  FUN_100006ec0(&uStack_30);
  return uVar1;
}


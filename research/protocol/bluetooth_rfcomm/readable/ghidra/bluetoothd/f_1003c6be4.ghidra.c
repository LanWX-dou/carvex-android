/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c6be4
 * original code SHA256: 47eb60244d6e3989d412d8f570fa8f708ad68aa77f8d1155feab8b344fd989e2
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined4 FUN_1003c6be4(byte param_1,byte param_2,uint param_3)

{
  undefined4 uVar1;
  
  uVar1 = 0xff;
  if (((byte)(&UNK_1009349a0)[(&UNK_1009349a0)[(byte)~param_1] ^ param_2] ^ param_3) == 0xff) {
    uVar1 = 0;
  }
  return uVar1;
}


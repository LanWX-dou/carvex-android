/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c6b60
 * original code SHA256: d7bef474797645439fb1863f093dc1ffea11d0e857552b935d7e88ac75bdeaaf
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


byte FUN_1003c6b60(byte *param_1,char param_2)

{
  byte bVar1;
  
  if (param_2 == '\0') {
    bVar1 = 0;
  }
  else {
    bVar1 = 0xff;
    do {
      param_2 = param_2 + -1;
      bVar1 = (&UNK_1009349a0)[*param_1 ^ bVar1];
      param_1 = param_1 + 1;
    } while (param_2 != '\0');
    bVar1 = ~bVar1;
  }
  return bVar1;
}


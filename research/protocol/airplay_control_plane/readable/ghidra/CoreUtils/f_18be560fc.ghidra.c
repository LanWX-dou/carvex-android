/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be560fc
 * original code SHA256: 03b3fef5f54d4f3a87fcb91d3ab357ca0bca1525f37cda3c75c05df4e99bddc5
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 __ChaCha20Poly1305EncryptMessage(long param_1,undefined8 param_2,long param_3)

{
  undefined8 uVar1;
  long in_stack_00000008;
  
  uVar1 = 0xffffe5cf;
  if ((param_3 == 0xc) && (in_stack_00000008 == 0x10)) {
    __chacha20_poly1305_encrypt_all(param_1 + 0x18,param_2,0xc);
    uVar1 = 0;
  }
  return uVar1;
}


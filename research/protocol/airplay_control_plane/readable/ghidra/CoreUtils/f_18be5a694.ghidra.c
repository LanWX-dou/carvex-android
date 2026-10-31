/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be5a694
 * original code SHA256: f118467a9a914a2b76bf6b77d93d44735bad847cec9d015064793b91284e489c
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 __ChaCha20Poly1305DecryptMessage(long param_1,undefined8 param_2,long param_3)

{
  undefined8 uVar1;
  long in_stack_00000008;
  
  if ((param_3 == 0xc) && (in_stack_00000008 == 0x10)) {
    uVar1 = __chacha20_poly1305_decrypt_all(param_1 + 0x18,param_2,0xc);
    return uVar1;
  }
  return 0xffffe5cf;
}


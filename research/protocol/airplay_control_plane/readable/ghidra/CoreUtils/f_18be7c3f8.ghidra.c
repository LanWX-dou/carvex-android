/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be7c3f8
 * original code SHA256: 5765d8c2fdd600a6acfa9832f0f2e3ed672ab3077a20e9f62833002f239c3e85
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
__ChaCha20Poly1305Initialize(long param_1,undefined8 param_2,undefined8 *param_3,long param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (param_4 == 0x20) {
    uVar2 = param_3[1];
    uVar1 = *param_3;
    uVar3 = param_3[2];
    *(undefined8 *)(param_1 + 0x30) = param_3[3];
    *(undefined8 *)(param_1 + 0x28) = uVar3;
    *(undefined8 *)(param_1 + 0x20) = uVar2;
    *(undefined8 *)(param_1 + 0x18) = uVar1;
    return 0;
  }
  return 0xffffe5cf;
}


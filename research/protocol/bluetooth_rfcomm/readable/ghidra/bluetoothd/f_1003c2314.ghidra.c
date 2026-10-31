/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c2314
 * original code SHA256: d952eee6ecea7dc677a6bcfebd04c2bcd8a4fabf76abff8bd6cb61b6202669b9
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 FUN_1003c2314(undefined8 param_1,uint param_2)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  
  if (param_2 == 0) {
    return 0x79;
  }
  uVar1 = (ulong)*(byte *)(lRam0000000100cadd68 + 1);
  if (uVar1 != 0) {
    lVar2 = 0;
    lVar3 = lRam0000000100c38318 + 0x1a;
    do {
      if (*(byte *)(lRam0000000100c38318 + lVar2 * 0x38 + 0x1a) == param_2) {
        (**(code **)(lVar3 + -0x12))();
        return 0;
      }
      lVar2 = lVar2 + 1;
      lVar3 = lVar3 + 0x38;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  return 0x79;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be5021c
 * original code SHA256: c6b9124475a556626737ced1dd0581d3d9d79e13cff4d2556f8b07c0d6a0afec
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_PairingSessionDeriveKey
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6,undefined8 param_7)

{
  uint uVar1;
  uint uVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  
  uVar1 = *(uint *)(param_1 + 0x60);
  if (6 < uVar1) {
    return 0xffffe5b1;
  }
  uVar2 = 1 << (ulong)(uVar1 & 0x1f);
  if ((uVar2 & 6) == 0) {
    if ((uVar2 & 0x18) == 0) {
      if ((1 << (ulong)(uVar1 & 0x1f) & 0x60U) == 0) {
        return 0xffffe5b1;
      }
      if (*(char *)(param_1 + 0x80) != '\x03') {
        return 0xffffe5cb;
      }
    }
    else if (*(char *)(param_1 + 0x80) != '\x05') {
      return 0xffffe5cb;
    }
    uVar3 = func_0x0001900cf870(0xffffe5b1);
    lVar5 = param_1 + 0x28e;
    lVar4 = 0x20;
  }
  else {
    if (*(char *)(param_1 + 0x80) != '\a') {
      return 0xffffe5cb;
    }
    lVar5 = *(long *)(param_1 + 0x300);
    if (lVar5 == 0) {
      return 0xffffe5cb;
    }
    lVar4 = *(long *)(param_1 + 0x308);
    if (lVar4 == 0) {
      return 0xffffe5cb;
    }
    uVar3 = func_0x0001900cf870(0xffffe5b1);
  }
  func_0x0001900cf190(uVar3,lVar4,lVar5,param_3,param_2,param_5,param_4,param_6,param_7);
  return 0;
}


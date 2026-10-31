/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be7bb64
 * original code SHA256: dfc4a584ba3cce573281601dd1497d879d241bfc5541b3ea082e2189952e255f
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long _CryptoAEADCreate(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                      int *param_5)

{
  int iVar1;
  long lVar2;
  
  if (_gCryptoAEADInitOnce != -1) {
    func_0x0001900cc2c0(&_gCryptoAEADInitOnce,0,__CryptoAEADGetTypeID);
  }
  lVar2 = func_0x0001900ce6a0(0,_gCryptoAEADTypeID,0x128,0);
  if (lVar2 == 0) {
    iVar1 = -0x1a48;
  }
  else {
    *(undefined8 *)(lVar2 + 0x100) = 0;
    *(undefined8 *)(lVar2 + 0xf8) = 0;
    *(undefined8 *)(lVar2 + 0xf0) = 0;
    *(undefined8 *)(lVar2 + 0xe8) = 0;
    *(undefined8 *)(lVar2 + 0xe0) = 0;
    *(undefined8 *)(lVar2 + 0xd8) = 0;
    *(undefined8 *)(lVar2 + 0xd0) = 0;
    *(undefined8 *)(lVar2 + 200) = 0;
    *(undefined8 *)(lVar2 + 0xc0) = 0;
    *(undefined8 *)(lVar2 + 0xb8) = 0;
    *(undefined8 *)(lVar2 + 0xb0) = 0;
    *(undefined8 *)(lVar2 + 0xa8) = 0;
    *(undefined8 *)(lVar2 + 0xa0) = 0;
    *(undefined8 *)(lVar2 + 0x98) = 0;
    *(undefined8 *)(lVar2 + 0x90) = 0;
    *(undefined8 *)(lVar2 + 0x88) = 0;
    *(undefined8 *)(lVar2 + 0x80) = 0;
    *(undefined8 *)(lVar2 + 0x78) = 0;
    *(undefined8 *)(lVar2 + 0x70) = 0;
    *(undefined8 *)(lVar2 + 0x68) = 0;
    *(undefined8 *)(lVar2 + 0x60) = 0;
    *(undefined8 *)(lVar2 + 0x58) = 0;
    *(undefined8 *)(lVar2 + 0x50) = 0;
    *(undefined8 *)(lVar2 + 0x48) = 0;
    *(undefined8 *)(lVar2 + 0x40) = 0;
    *(undefined8 *)(lVar2 + 0x38) = 0;
    *(undefined8 *)(lVar2 + 0x20) = 0;
    *(undefined8 *)(lVar2 + 0x18) = 0;
    *(undefined8 *)(lVar2 + 0x30) = 0;
    *(undefined8 *)(lVar2 + 0x28) = 0;
    *(undefined8 *)(lVar2 + 0x120) = 0;
    *(undefined8 *)(lVar2 + 0x118) = 0;
    *(undefined8 *)(lVar2 + 0x130) = 0;
    *(undefined8 *)(lVar2 + 0x128) = 0;
    *(undefined8 *)(lVar2 + 0x110) = 0;
    *(undefined8 *)(lVar2 + 0x108) = 0;
    *(undefined8 **)(lVar2 + 0x10) = param_1;
    iVar1 = (*(code *)*param_1)(lVar2,param_2,param_3,param_4);
    if (iVar1 != 0) {
      func_0x0001900caac0(lVar2);
      lVar2 = 0;
    }
  }
  if (param_5 != (int *)0x0) {
    *param_5 = iVar1;
  }
  return lVar2;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf220cc
 * original code SHA256: d862167be09191a25fb824775da89d30ccb0b2acc3460f188ebb9713fa81239d
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _PairingSessionCreate(long *param_1,undefined8 *param_2,undefined4 param_3)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  if (_gPairingSessionInitOnce != -1) {
    func_0x0001900cc2c0(&_gPairingSessionInitOnce,0,__PairingSessionGetTypeID);
  }
  lVar1 = func_0x0001900ce6a0(0,_gPairingSessionTypeID,0x3f0,0);
  if (lVar1 == 0) {
    uVar2 = 0xffffe5b8;
  }
  else {
    func_0x0001900cc250(lVar1 + 0x18,1000);
    *(undefined **)(lVar1 + 0x10) = &_gLogCategory_CUPairing;
    *(undefined4 *)(lVar1 + 0x60) = param_3;
    uVar2 = _DAT_18bf721d0;
    *(undefined8 *)(lVar1 + 0x78) = _UNK_18bf721d8;
    *(undefined8 *)(lVar1 + 0x70) = uVar2;
    if (_SecondsToUpTicks_sOnce != -1) {
      func_0x0001900cc2c0(&_SecondsToUpTicks_sOnce,&_SecondsToUpTicks_sMultiplier,
                          __SecondsToUpTicksInit);
    }
    *(long *)(lVar1 + 0x180) = _SecondsToUpTicks_sMultiplier * 0x2a300;
    if (param_2 == (undefined8 *)0x0) {
      *(undefined8 *)(lVar1 + 0x58) = 0;
      *(undefined8 *)(lVar1 + 0x50) = 0;
      *(undefined8 *)(lVar1 + 0x48) = 0;
      *(undefined8 *)(lVar1 + 0x40) = 0;
      *(undefined8 *)(lVar1 + 0x38) = 0;
      *(undefined8 *)(lVar1 + 0x30) = 0;
      *(undefined8 *)(lVar1 + 0x28) = 0;
      *(undefined8 *)(lVar1 + 0x20) = 0;
      *(undefined8 *)(lVar1 + 0x18) = 0;
    }
    else {
      uVar2 = *param_2;
      *(undefined8 *)(lVar1 + 0x20) = param_2[1];
      *(undefined8 *)(lVar1 + 0x18) = uVar2;
      uVar3 = param_2[3];
      uVar2 = param_2[2];
      uVar5 = param_2[5];
      uVar4 = param_2[4];
      uVar7 = param_2[7];
      uVar6 = param_2[6];
      *(undefined8 *)(lVar1 + 0x58) = param_2[8];
      *(undefined8 *)(lVar1 + 0x50) = uVar7;
      *(undefined8 *)(lVar1 + 0x48) = uVar6;
      *(undefined8 *)(lVar1 + 0x40) = uVar5;
      *(undefined8 *)(lVar1 + 0x38) = uVar4;
      *(undefined8 *)(lVar1 + 0x30) = uVar3;
      *(undefined8 *)(lVar1 + 0x28) = uVar2;
    }
    _PairingSessionSetKeychainInfo
              (lVar1,&cfstringStruct_1e9b93de0,0x70724964,&cfstringStruct_1e9b968e0,
               &cfstringStruct_1e9b968e0,0x70725065,&cfstringStruct_1e9b96900,
               &cfstringStruct_1e9b96900,0);
    uVar2 = 0;
    *param_1 = lVar1;
  }
  return uVar2;
}


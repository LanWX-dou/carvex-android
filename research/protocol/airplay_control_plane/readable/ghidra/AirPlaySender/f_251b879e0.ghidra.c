/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b879e0
 * original code SHA256: 570e84c762afc9e5fcc654ffd81a266ffc2076131df905d65fcd937e43941a23
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _coreUtilsPairing_IsPeerKnown(undefined8 param_1)

{
  undefined1 in_ZR;
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 extraout_x8;
  ulong uVar4;
  long local_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 local_28;
  
  _OUTLINED_FUNCTION_13();
  local_28 = extraout_x8;
  lVar2 = func_0x00025810ac50();
  uStack_48 = 0;
  local_50 = 0;
  uStack_38 = 0;
  uStack_40 = 0;
  uStack_68 = 0;
  local_70 = 0;
  uStack_58 = 0;
  uStack_60 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_78 = 0;
  uStack_80 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  local_d8 = 0;
  if (*(long *)(lVar2 + 0x18) == 0) {
    uVar4 = 0;
  }
  else {
    _OUTLINED_FUNCTION_23(*(long *)(lVar2 + 0x18),&local_d0);
    uVar3 = _coreUtilsPairing_createAirPlayPairingSession(param_1,0,0,0,&local_d8);
    lVar2 = local_d8;
    if ((int)uVar3 == 0) {
      iVar1 = func_0x00025810fd30(local_d8,&local_d0,0xffffffffffffffff,&local_50);
      in_ZR = iVar1 == 0;
      uVar4 = (ulong)(byte)in_ZR;
    }
    else {
      func_0x000258109a30(uVar3,"coreUtilsPairing_IsPeerKnown",0x19f,0);
      uVar4 = 0;
      lVar2 = local_d8;
    }
    if (lVar2 != 0) {
      func_0x0002580f5830(lVar2);
    }
  }
  _OUTLINED_FUNCTION_10(local_28);
  if ((bool)in_ZR) {
    return uVar4;
  }
  uVar4 = func_0x0002580f4380();
  return uVar4;
}


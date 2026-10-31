/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100035440
 * original code SHA256: aa9674f4eff432972a1c7d9f15a570ce33b779bbb50112d3fa95db5c1d4280b3
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_100035440(undefined4 *param_1,SEL param_2)

{
  uint uVar1;
  ulong uVar2;
  undefined4 *puVar3;
  unsigned_long_long uVar4;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar5;
  
  puVar3 = (undefined4 *)0x100c26408;
  puVar5 = param_1;
  if (uRam0000000100c2640c == 0) {
    _mach_timebase_info();
    uVar7 = uRam0000000100c26408;
    uVar6 = uRam0000000100c2640c;
    do {
      if (uVar7 == 0) goto LAB_1000354b4;
      uVar8 = uVar7;
      if (uVar6 < uVar7) {
        uVar1 = 0;
        if (uVar6 != 0) {
          uVar1 = uVar7 / uVar6;
        }
        uVar8 = uVar6;
        uVar6 = uVar7 - uVar1 * uVar6;
      }
      uVar7 = uVar6;
      uVar6 = uVar8;
    } while (uVar7 != uVar8);
    uVar6 = 1;
LAB_1000354b4:
    uVar7 = 0;
    if (uVar6 != 0) {
      uVar7 = uRam0000000100c26408 / uVar6;
    }
    uVar8 = 0;
    if (uVar6 != 0) {
      uVar8 = uRam0000000100c2640c / uVar6;
    }
    uRam0000000100c2640c = uVar8;
    uRam0000000100c26408 = uVar7;
    if (0x862 < uVar8 >> 1) {
      FUN_1000f9438();
    }
    uRam0000000100c2640c = uRam0000000100c2640c * 1000000;
    puVar5 = puVar3;
  }
  uVar4 = _mach_absolute_time((ID)puVar5,param_2);
  uVar2 = 0;
  if ((ulong)uRam0000000100c2640c != 0) {
    uVar2 = (uVar4 * uRam0000000100c26408) / (ulong)uRam0000000100c2640c;
  }
  *(short *)(param_1 + 1) = (short)uVar2 + (short)(uVar2 / 1000) * -1000;
  *param_1 = (int)(uVar2 / 1000);
  return;
}


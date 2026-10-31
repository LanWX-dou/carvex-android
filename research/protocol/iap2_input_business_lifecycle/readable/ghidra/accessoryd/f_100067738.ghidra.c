/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100067738
 * original code SHA256: 43a362fa26a6839135a91dcfe847b6db96828168b0384ad6d788663f23a721d2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort * _iAP2MsgGetFirstParam(long param_1,ushort *param_2)

{
  ushort *puVar1;
  ushort *puVar2;
  uint uVar3;
  ushort *puVar4;
  ushort uVar5;
  uint uVar6;
  ushort *puVar7;
  ulong uVar8;
  long lVar9;
  
  if (param_2 == (ushort *)0x0) {
    puVar4 = *(ushort **)(param_1 + 0x20);
    puVar1 = (ushort *)(*(long *)(param_1 + 0x18) + 6);
    puVar2 = (ushort *)0x0;
    if (puVar1 < puVar4) {
      puVar2 = puVar1;
    }
    puVar7 = (ushort *)0x0;
    if (puVar4 != (ushort *)0x0 && puVar1 < puVar4) {
      if ((long)puVar4 - (long)puVar1 < 4) {
        return (ushort *)0x0;
      }
      uVar5 = *(ushort *)(*(long *)(param_1 + 0x18) + 6);
      puVar7 = puVar2;
      if ((ulong)((long)puVar4 - (long)puVar1) <
          (ulong)((uint)(uVar5 >> 8) | (uVar5 & 0xff00ff) << 8)) {
        return (ushort *)0x0;
      }
    }
  }
  else {
    uVar6 = (uint)(*param_2 >> 8) | (*param_2 & 0xff00ff) << 8;
    uVar3 = 0;
    if (3 < uVar6) {
      uVar3 = uVar6 - 4;
    }
    if (param_1 == 0) {
      uVar8 = 0;
      lVar9 = _DAT_00000018;
    }
    else {
      lVar9 = *(long *)(param_1 + 0x18);
      if ((lVar9 == 0) || (*(uint *)(param_1 + 0x10) < 6)) {
        uVar8 = 0;
      }
      else {
        uVar8 = (ulong)((uint)(*(ushort *)(lVar9 + 2) >> 8) |
                       (*(ushort *)(lVar9 + 2) & 0xff00ff) << 8);
      }
    }
    puVar2 = (ushort *)(lVar9 + uVar8);
    puVar1 = param_2 + 2;
    puVar4 = (ushort *)0x0;
    if (puVar1 <= puVar2 && (ushort *)((long)param_2 + (ulong)uVar6) <= puVar2) {
      puVar4 = puVar1;
    }
    puVar7 = (ushort *)0x0;
    if (((4 < uVar6) && (puVar1 <= puVar2 && (ushort *)((long)param_2 + (ulong)uVar6) <= puVar2)) &&
       ((uVar3 < 4 ||
        ((uVar6 = (uint)(param_2[2] >> 8) | (param_2[2] & 0xff00ff) << 8, uVar6 < 4 ||
         (puVar7 = puVar4, uVar3 < uVar6)))))) {
      return (ushort *)0x0;
    }
  }
  return puVar7;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c1404
 * original code SHA256: 6ae0b7f481c9c7b33bf2ae33eb7f2f87cd399421e65cde606905dea107dc9b3b
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


long FUN_1003c1404(long param_1,uint param_2,long *param_3)

{
  ushort uVar1;
  ulong uVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  
  if (param_2 < 2) {
    return 0x79;
  }
  uVar2 = (ulong)*(byte *)(lRam0000000100cadd68 + 1);
  if (uVar2 != 0) {
    lVar4 = 0;
    puVar7 = (undefined8 *)(lRam0000000100c38318 + 0x30);
    do {
      if ((uint)*(byte *)(lRam0000000100c38318 + lVar4 * 0x38 + 0x1a) == param_2 >> 1) {
        lVar4 = param_1;
        FUN_1003c14dc(param_1,param_2,param_3);
        if ((int)lVar4 != 0) {
          return lVar4;
        }
        lVar3 = *param_3;
        *(undefined1 *)(lVar3 + 0x14) = 1;
        uVar5 = puVar7[-4];
        *(undefined2 *)(lVar3 + 0xa0) = *(undefined2 *)(puVar7 + -1);
        uVar1 = *(ushort *)(puVar7 + -3);
        if (*(ushort *)(param_1 + 4) <= *(ushort *)(puVar7 + -3)) {
          uVar1 = *(ushort *)(param_1 + 4);
        }
        *(ushort *)(lVar3 + 0x10) = uVar1;
        uVar6 = *puVar7;
        *(undefined8 *)(lVar3 + 0x28) = uVar5;
        *(undefined8 *)(lVar3 + 0x30) = uVar6;
        return lVar4;
      }
      lVar4 = lVar4 + 1;
      puVar7 = puVar7 + 7;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return 0x79;
}


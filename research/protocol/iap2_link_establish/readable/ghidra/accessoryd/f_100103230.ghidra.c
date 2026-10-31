/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100103230
 * original code SHA256: d244b47ebb3982ff87b8a8a23224be3f2fc99d641efed1786d8de31c46fb05df
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


bool _iAP2PacketParseSYNData(char *param_1,uint param_2,char *param_3)

{
  char *pcVar1;
  uint uVar2;
  char cVar3;
  byte bVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  ulong uVar10;
  
  if (9 < param_2) {
    cVar3 = *param_1;
    *param_3 = cVar3;
    param_3[1] = param_1[1];
    bVar4 = param_1[2];
    *(ushort *)(param_3 + 4) = (ushort)bVar4 << 8;
    *(ushort *)(param_3 + 4) = CONCAT11(bVar4,param_1[3]);
    bVar4 = param_1[4];
    *(ushort *)(param_3 + 6) = (ushort)bVar4 << 8;
    *(ushort *)(param_3 + 6) = CONCAT11(bVar4,param_1[5]);
    bVar4 = param_1[6];
    *(ushort *)(param_3 + 8) = (ushort)bVar4 << 8;
    *(ushort *)(param_3 + 8) = CONCAT11(bVar4,param_1[7]);
    param_3[2] = param_1[8];
    param_3[3] = param_1[9];
    if (cVar3 == '\0') {
      uVar5 = 0;
      uVar7 = 0;
    }
    else if (cVar3 == '\x01') {
      uVar7 = (param_2 - 10) / 3;
      param_3[0x18] = '\0';
      uVar5 = 10;
    }
    else {
      bVar4 = param_1[10];
      uVar5 = (uint)bVar4;
      if (4 < uVar5) {
        uVar5 = 5;
      }
      param_3[0x18] = (char)uVar5;
      if (bVar4 != 0) {
        lVar9 = 0;
        uVar10 = (ulong)uVar5;
        do {
          param_3[lVar9 + 0x19] = param_1[lVar9 + 0xb];
          lVar9 = lVar9 + 1;
          uVar10 = uVar10 - 1;
        } while (uVar10 != 0);
      }
      uVar7 = (uint)(byte)param_1[(ulong)uVar5 + 0xb];
      uVar5 = uVar5 + 0xc;
    }
    pcVar6 = param_3 + 0x1e;
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6[4] = '\0';
    pcVar6[5] = '\0';
    pcVar6[6] = '\0';
    pcVar6[7] = '\0';
    param_3[0x25] = '\0';
    param_3[0x26] = '\0';
    param_3[0x27] = '\0';
    param_3[0x28] = '\0';
    param_3[0x29] = '\0';
    param_3[0x2a] = '\0';
    param_3[0x2b] = '\0';
    param_3[0x2c] = '\0';
    uVar7 = uVar7 & 0xff;
    uVar2 = uVar7;
    if (4 < uVar7) {
      uVar2 = 5;
    }
    if (uVar7 != 0) {
      uVar7 = uVar5 & 0xff;
      if (uVar7 + 3 <= param_2) {
        lVar9 = 0;
        uVar10 = 1;
        uVar8 = uVar7 + 3;
        do {
          bVar4 = param_1[(ulong)uVar7 + 1];
          pcVar1 = pcVar6 + lVar9 * 4;
          *pcVar1 = param_1[(byte)uVar5];
          pcVar1[2] = param_1[(ulong)uVar7 + 2];
          pcVar1[1] = bVar4 & 0x7f;
          pcVar1[3] = bVar4 >> 7;
          if (uVar2 <= uVar10) break;
          lVar9 = lVar9 + 1;
          uVar7 = uVar8 & 0xff;
          uVar10 = uVar10 + 1;
          uVar5 = uVar8;
          uVar8 = uVar7 + 3;
        } while (uVar7 + 3 <= param_2);
      }
    }
    param_3[10] = (char)uVar2;
  }
  return 9 < param_2;
}


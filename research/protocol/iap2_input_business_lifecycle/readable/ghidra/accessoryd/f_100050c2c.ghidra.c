/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100050c2c
 * original code SHA256: dafd1505f61252ea994f0698bfdc399d45aef7533d89fe09ba264ac7643333ab
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



byte _iap2_identification_checkRequiredMsgIDs
               (undefined8 param_1,long param_2,uint param_3,byte *param_4)

{
  undefined2 *puVar1;
  long lVar2;
  bool bVar3;
  int iVar4;
  long lVar5;
  ulong uVar7;
  byte bVar8;
  byte bVar9;
  long lVar10;
  long lVar6;
  
  lVar5 = _iap2_identification_getIdentificationInfo();
  if (param_3 == 0) {
    bVar8 = 0;
    bVar9 = 1;
  }
  else {
    lVar10 = 0;
    bVar8 = 0;
    lVar2 = *(long *)(lVar5 + 0x60);
    lVar5 = *(long *)(lVar5 + 0x68);
    bVar9 = 1;
    uVar7 = (ulong)param_3;
    do {
      puVar1 = (undefined2 *)(param_2 + lVar10 * 0xc);
      if (*(int *)(puVar1 + 2) == 1) {
        lVar6 = lVar5;
        if (lVar5 != 0) goto LAB_100050ca4;
LAB_100050c94:
        bVar3 = false;
      }
      else {
        lVar6 = lVar2;
        if (lVar2 == 0) goto LAB_100050c94;
LAB_100050ca4:
        iVar4 = _CFSetContainsValue(lVar6,*puVar1);
        bVar3 = iVar4 != 0;
      }
      bVar8 = bVar8 | bVar3;
      bVar9 = bVar9 & (*(byte *)(puVar1 + 4) ^ 1 | bVar3);
      lVar10 = lVar10 + 1;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
  *param_4 = bVar8;
  return bVar9;
}


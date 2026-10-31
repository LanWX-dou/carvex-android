/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf414a4
 * original code SHA256: 03ec4e08e67687c798c2a963c5567b1ed944da5c1cdd21e791f5810c297868a7
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_TLV8GetBytes(byte *param_1,byte *param_2,uint param_3,ulong param_4,ulong param_5,long param_6,
             ulong *param_7,undefined8 *param_8)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte bVar4;
  undefined8 uVar5;
  byte *pbVar6;
  long lVar7;
  ulong uVar8;
  
  do {
    if (param_1 == param_2) {
      return 0xffffe5b9;
    }
    if (param_2 <= param_1) {
      return 0xffffe5cf;
    }
    if ((ulong)((long)param_2 - (long)param_1) < 2) {
      return 0xffffe5b9;
    }
    pbVar1 = param_1 + 2;
    uVar8 = (ulong)param_1[1];
    pbVar6 = pbVar1 + uVar8;
    if (param_2 < pbVar6) goto LAB_18bf415d8;
    bVar4 = *param_1;
    param_1 = pbVar6;
  } while (bVar4 != param_3);
  if (param_5 < uVar8) {
LAB_18bf415e8:
    uVar5 = 0xffffe5a1;
  }
  else {
    func_0x0001900cc480(param_6,pbVar1,uVar8);
    lVar7 = param_6 + uVar8;
    while ((pbVar6 < param_2 && (1 < (ulong)((long)param_2 - (long)pbVar6)))) {
      pbVar2 = pbVar6 + 2;
      pbVar1 = pbVar6 + 1;
      uVar8 = (ulong)*pbVar1;
      pbVar3 = pbVar2 + uVar8;
      if ((param_2 < pbVar3) || (*pbVar6 != param_3)) break;
      pbVar6 = pbVar3;
      if (*pbVar1 != 0) {
        if ((param_6 + param_5) - lVar7 < uVar8) goto LAB_18bf415e8;
        func_0x0001900cc480(lVar7,pbVar2,uVar8);
        lVar7 = lVar7 + uVar8;
      }
    }
    if ((ulong)(lVar7 - param_6) < param_4) {
LAB_18bf415d8:
      uVar5 = 0xffffe5a2;
    }
    else {
      if (param_7 != (ulong *)0x0) {
        *param_7 = lVar7 - param_6;
      }
      uVar5 = 0;
      if (param_8 != (undefined8 *)0x0) {
        *param_8 = pbVar6;
      }
    }
  }
  return uVar5;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519c1b94
 * original code SHA256: 39dec1e48153cd60dc1a9772ee4060fba9971eb97a23ea80581e188d12614010
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _APAudioZeroTimeStampProviderGetZeroTimeStamp(long param_1,undefined8 *param_2)

{
  uint *puVar1;
  undefined8 *puVar2;
  uint uVar3;
  uint in_wzr;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  
  puVar1 = (uint *)(param_1 + 0x98);
  LOAcquire();
  uVar3 = *puVar1;
  *puVar1 = uVar3 | in_wzr;
  LORelease();
  puVar2 = (undefined8 *)(param_1 + 0x18 + CONCAT44((int)((ulong)puVar1 >> 0x20),uVar3) * 0x40);
  uVar5 = puVar2[1];
  uVar4 = *puVar2;
  uVar7 = puVar2[3];
  uVar6 = puVar2[2];
  uVar8 = puVar2[4];
  uVar10 = puVar2[7];
  uVar9 = puVar2[6];
  param_2[5] = puVar2[5];
  param_2[4] = uVar8;
  param_2[7] = uVar10;
  param_2[6] = uVar9;
  param_2[1] = uVar5;
  *param_2 = uVar4;
  param_2[3] = uVar7;
  param_2[2] = uVar6;
  return;
}


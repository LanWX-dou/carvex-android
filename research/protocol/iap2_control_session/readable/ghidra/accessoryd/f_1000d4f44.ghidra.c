/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000d4f44
 * original code SHA256: 1ba21b4cd680e64f4bbc6224b942306ecfba0e864d291324c139f4da261d5dd2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkCommandValidateFeatureSets(long param_1,long param_2)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  ulong uVar4;
  long lVar5;
  uint uVar6;
  
  bVar3 = *(byte *)(param_2 + 0x18);
  uVar4 = (ulong)bVar3;
  if (uVar4 == 0) {
    uVar2 = 0;
  }
  else {
    lVar5 = 0;
    uVar2 = 0;
    do {
      cVar1 = *(char *)(param_2 + 0x19 + lVar5);
      uVar6 = 2;
      if (cVar1 != 'U') {
        uVar6 = 0x80000000;
      }
      if (cVar1 == 'T') {
        uVar6 = 1;
      }
      uVar2 = uVar6 | uVar2;
      lVar5 = lVar5 + 1;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
    if ((uVar2 & 3) == 0) {
      bVar3 = 0;
    }
    else {
      *(undefined2 *)(param_2 + 0x19) = 0x5554;
      uVar2 = uVar2 | 3;
      bVar3 = 2;
    }
  }
  *(byte *)(param_2 + 0x18) = bVar3;
  *(uint *)(param_1 + 0x110) = uVar2;
  return;
}


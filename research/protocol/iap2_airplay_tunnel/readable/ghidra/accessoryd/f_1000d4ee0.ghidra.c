/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000d4ee0
 * original code SHA256: 4a3ccf0061c756fa983b7ba7c7bb3fbda808e1befbba2f8b61ac4cd33931e4e6
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iAP2LinkCommandIsFeatureSetValid(long param_1)

{
  char cVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  uint uVar5;
  
  uVar3 = (ulong)*(byte *)(param_1 + 0x18);
  if (uVar3 == 0) {
    uVar2 = 0;
  }
  else {
    lVar4 = 0;
    uVar2 = 0;
    do {
      cVar1 = *(char *)(param_1 + 0x19 + lVar4);
      uVar5 = 2;
      if (cVar1 != 'U') {
        uVar5 = 0x80000000;
      }
      if (cVar1 == 'T') {
        uVar5 = 1;
      }
      uVar2 = uVar5 | uVar2;
      lVar4 = lVar4 + 1;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
    if ((int)uVar2 < 0) {
      return false;
    }
  }
  return (uVar2 & 3) == 3 || (uVar2 & 3) == 0;
}


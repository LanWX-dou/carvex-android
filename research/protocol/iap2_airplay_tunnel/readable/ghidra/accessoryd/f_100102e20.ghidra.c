/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100102e20
 * original code SHA256: 7e1798b2ab7de0f5d6553f65171d3589831c331cae2c232415c5b59c9bc2f294
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iAP2PacketCheckDetect(long param_1)

{
  long lVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  ulong uVar5;
  
  pbVar4 = *(byte **)(param_1 + 0x40);
  uVar3 = *pbVar4 - 0xff;
  uVar5 = (ulong)(uVar3 < 0xffffff02);
  pbVar2 = pbVar4;
  if (uVar3 < 0xffffff02) {
    pbVar2 = pbVar4 + 1;
  }
  if (*pbVar2 == 0x55) {
    lVar1 = 1;
    if (uVar3 < 0xffffff02) {
      lVar1 = 2;
    }
    if ((pbVar4[lVar1] == 2) && (pbVar4[uVar5 | 2] == 0)) {
      lVar1 = 3;
      if (uVar3 < 0xffffff02) {
        lVar1 = 4;
      }
      if (pbVar4[lVar1] == 0xee) {
        return pbVar4[uVar5 | 4] == 0x10;
      }
    }
  }
  return false;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100032828
 * original code SHA256: 6399553e7068fb0daaf8d09696e7476233dd1b9c48f3105058520d4a20de49c6
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



byte * _iAP2LinkGetSessionInfo(long param_1,uint param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  ulong uVar3;
  long lVar4;
  
  pbVar2 = (byte *)0x0;
  if (param_1 != 0) {
    uVar3 = (ulong)*(byte *)(param_1 + 0x1a4);
    if (uVar3 == 0) {
      return (byte *)0x0;
    }
    lVar4 = 0;
    pbVar1 = (byte *)0x0;
    do {
      pbVar2 = (byte *)(param_1 + 0x1b8 + lVar4 * 4);
      if (*pbVar2 != param_2) {
        pbVar2 = pbVar1;
      }
      lVar4 = lVar4 + 1;
      uVar3 = uVar3 - 1;
      pbVar1 = pbVar2;
    } while (uVar3 != 0);
  }
  return pbVar2;
}


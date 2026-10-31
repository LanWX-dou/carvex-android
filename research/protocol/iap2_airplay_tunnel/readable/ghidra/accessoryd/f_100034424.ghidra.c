/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034424
 * original code SHA256: 28b4e15022ffee1ec111deac5d6bb64e81f21178f673f95db98770b45fce2060
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



byte _iAP2LinkGetNewSeqNum(long param_1)

{
  char cVar1;
  byte bVar2;
  
  if ((*(byte *)(param_1 + 0xd4) >> 2 & 1) == 0) {
    bVar2 = _iAP2TimeGetCurTimeMs();
  }
  else {
    cVar1 = *(char *)(param_1 + 0xbe);
    bVar2 = _iAP2TimeGetCurTimeMs();
    bVar2 = cVar1 + 0x47U & bVar2;
  }
  return bVar2;
}


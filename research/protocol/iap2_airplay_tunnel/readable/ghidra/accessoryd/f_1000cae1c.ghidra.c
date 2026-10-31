/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000cae1c
 * original code SHA256: 59946aaaead63f43da2d0bdc07be61c5654eb9d4213f2e8ac7c2f2527c19290e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _iAP2LinkRunLoopGetBuffSize(void)

{
  int iVar1;
  
  iVar1 = _iAP2LinkGetBuffSize();
  return iVar1 + 0x60;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10012961c
 * original code SHA256: c86f49e6ab97b8861b24be95bfb5a164abf3b7519754fa024cb41b6f8a3f9033
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



byte _iap2_endpoint_isInitialized(long param_1)

{
  byte bVar1;
  
  if (param_1 == 0) {
    bVar1 = 0;
  }
  else {
    bVar1 = *(byte *)(param_1 + 0x1c0);
  }
  return bVar1 & 1;
}


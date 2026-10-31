/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011d148
 * original code SHA256: 8a8c893aab5106b104cc87cc1b943330bd92b0843101c2d1a619ab653af033a5
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



byte _iap2_sessionControl_init(long param_1)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  long lVar5;
  
  bVar2 = 0;
  if (param_1 != 0) {
    if (*(long *)(param_1 + 200) == 0) {
      lVar5 = _malloc_type_malloc(0xffff,0x4c7b7cb3);
      *(long *)(param_1 + 200) = lVar5;
      bVar1 = lVar5 != 0;
    }
    else {
      bVar1 = true;
    }
    bVar2 = _iap2_features_registerMessageHandlers();
    bVar3 = _iap2_features_registerIdentificationParamHandlers();
    _OUTLINED_FUNCTION_44();
    bVar4 = _iap2_features_createFeatures();
    bVar2 = bVar1 & bVar2 & bVar3 & bVar4;
  }
  return bVar2;
}


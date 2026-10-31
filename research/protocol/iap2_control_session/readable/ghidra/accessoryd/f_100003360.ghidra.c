/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100003360
 * original code SHA256: f81e302bdba6408d32f7976ba932a2cc5af0b54e93a59e40ee60baa7ca48d7b3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_feature_getFeature(long param_1,uint param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined8 *)(param_1 + 0xd0 + (ulong)param_2 * 8);
  }
  return uVar1;
}


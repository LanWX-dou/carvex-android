/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013ed5c
 * original code SHA256: 6448dd98272d11613bb72b2f581ee1bfb6d33a6bbecd25ce128e69d14237b633
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined4 * _iap2_feature_getFeatureInfoEntries(undefined1 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)0x0;
  if (param_1 != (undefined1 *)0x0) {
    *param_1 = 0x1d;
    puVar1 = &__kiAP2FeatureInfoEntries;
  }
  return puVar1;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013c148
 * original code SHA256: b10ec8d6c3ce2330268dd74cc99b0eeca9e8c956dd560d2e285ede6589713c9a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



byte _iap2_identification_isIdentifiedForCarPlay(long param_1)

{
  undefined1 in_ZR;
  long lVar1;
  byte bVar2;
  
  if (param_1 == 0) {
    bVar2 = 0;
    goto LAB_10013c188;
  }
  lVar1 = _iap2_feature_getFeature(param_1,1);
  if ((lVar1 != 0) && (lVar1 = _OUTLINED_FUNCTION_24(), (bool)in_ZR)) {
    lVar1 = *(long *)(lVar1 + 8);
    bVar2 = 0;
    if (lVar1 == 0) goto LAB_10013c188;
    if (*(long *)(lVar1 + 0x70) != 0) {
      bVar2 = *(byte *)(lVar1 + 0x80);
      goto LAB_10013c188;
    }
  }
  bVar2 = 0;
LAB_10013c188:
  return bVar2 & 1;
}


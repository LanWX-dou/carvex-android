/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013c0ec
 * original code SHA256: 093503be44baf7dfc24038e45be5fa93c452931e63c04168bf870bbdbf0e9f69
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iap2_identification_isIdentifiedForFeature(long param_1)

{
  undefined1 in_ZR;
  bool bVar1;
  int iVar2;
  long lVar3;
  undefined4 unaff_w19;
  
  bVar1 = false;
  if (param_1 != 0) {
    lVar3 = _OUTLINED_FUNCTION_33();
    bVar1 = false;
    if (lVar3 != 0) {
      lVar3 = _OUTLINED_FUNCTION_24();
      if (((bool)in_ZR) && (*(long *)(lVar3 + 8) != 0)) {
        lVar3 = *(long *)(*(long *)(lVar3 + 8) + 0x70);
        bVar1 = false;
        if (lVar3 != 0) {
          iVar2 = _CFSetContainsValue(lVar3,unaff_w19);
          bVar1 = iVar2 != 0;
        }
      }
      else {
        bVar1 = false;
      }
    }
  }
  return bVar1;
}


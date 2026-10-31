/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011d4b8
 * original code SHA256: 4150302e26bbe6238a211c0765baf7b555a3d80330a9d92cdea813dbcf3e01f8
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1 _iap2_sessionControl_getVersion(long param_1)

{
  undefined1 uVar1;
  undefined8 uVar2;
  long lVar3;
  
  if ((param_1 != 0) && (*(long *)(param_1 + 0x28) != 0)) {
    lVar3 = *(long *)(*(long *)(param_1 + 0x28) + 0x18);
    if (lVar3 == 0) {
      uVar1 = 0;
    }
    else {
      _OUTLINED_FUNCTION_8();
      uVar2 = _iAP2LinkGetSessionForService();
      lVar3 = _iAP2LinkGetSessionInfo(lVar3,uVar2);
      uVar1 = 0;
      if (lVar3 != 0) {
        uVar1 = *(undefined1 *)(lVar3 + 2);
      }
    }
    return uVar1;
  }
  return 0;
}


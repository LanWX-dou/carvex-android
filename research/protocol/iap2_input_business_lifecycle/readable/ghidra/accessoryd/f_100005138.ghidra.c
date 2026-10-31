/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100005138
 * original code SHA256: 94aafd25c58232b89f16037ef27e2d71736a87f176bd3baf47a86a744333343b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_identification_isIdentifiedForOutgoingMessageID(long param_1,uint param_2)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  
  uVar2 = 0;
  if (param_1 != 0) {
    uVar2 = 1;
    if ((((5 < param_2 - 0xaa00) || ((1 << (ulong)(param_2 - 0xaa00 & 0x1f) & 0x35U) == 0)) &&
        ((5 < param_2 || ((1 << (ulong)(param_2 & 0x1f) & 0x31U) == 0)))) &&
       ((3 < param_2 - 0x1d00 || (param_2 - 0x1d00 == 1)))) {
      lVar3 = _iap2_identification_getIdentificationInfo(param_1);
      uVar2 = 0;
      if (lVar3 != 0) {
        iVar1 = _iap2_accAuthentication_getState(param_1);
        if ((iVar1 == 2) && (iVar1 = _iap2_identification_getState(param_1), iVar1 == 6)) {
          uVar2 = 0;
          if ((*(long *)(lVar3 + 0x68) != 0) &&
             (uVar2 = _CFSetContainsValue(*(long *)(lVar3 + 0x68),param_2), (int)uVar2 != 0)) {
            _kdebug_trace(0x2b94115c,0,0,0,0);
            uVar2 = 1;
          }
        }
        else {
          uVar2 = 0;
        }
      }
    }
  }
  return uVar2;
}


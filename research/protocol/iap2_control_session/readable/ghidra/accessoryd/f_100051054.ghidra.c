/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100051054
 * original code SHA256: b3a26412fba38ef3918ef4848bcccfc1a390510d592580879ea25695b639b21d
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iap2_identification_isIdentifiedForIncomingMessageID(long param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  
  if (param_1 == 0) {
    return false;
  }
  uVar1 = param_2;
  if ((int)param_2 < 0x1d01) {
joined_r0x0001000510b0:
    if ((uVar1 < 6) && ((1 << (ulong)(uVar1 & 0x1f) & 0x31U) != 0)) {
      return true;
    }
  }
  else {
    if ((int)param_2 < 0xaa01) {
      uVar1 = param_2 - 0x1d01;
      goto joined_r0x0001000510b0;
    }
    if (param_2 == 0xaa01) {
      return true;
    }
    if (param_2 == 0xaa03) {
      return true;
    }
    if (param_2 == 0xaa06) {
      lVar3 = _iap2_identification_getIdentificationInfo(param_1);
      if (lVar3 == 0) {
        return false;
      }
      if (*(long *)(lVar3 + 0x60) == 0) {
        return false;
      }
      iVar2 = _iap2_identification_getState(param_1);
      if (iVar2 != 6) {
        return false;
      }
      lVar3 = *(long *)(lVar3 + 0x60);
      param_2 = 0xaa06;
      goto LAB_100051170;
    }
  }
  lVar3 = _iap2_identification_getIdentificationInfo(param_1);
  if (lVar3 == 0) {
    return false;
  }
  iVar2 = _iap2_accAuthentication_getState(param_1);
  if ((iVar2 != 2) || (iVar2 = _iap2_identification_getState(param_1), iVar2 != 6)) {
    return false;
  }
  lVar3 = *(long *)(lVar3 + 0x60);
  if (lVar3 == 0) {
    return false;
  }
LAB_100051170:
  iVar2 = _CFSetContainsValue(lVar3,param_2);
  return iVar2 != 0;
}


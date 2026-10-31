/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa9060
 * original code SHA256: 60142bfcf16b673fc3b51bca3e6eafc9af0977f768648e1047a8a1151bf645aa
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _APKeyHolderLegacyCreate(undefined8 param_1,long param_2,long param_3,long *param_4)

{
  int iVar1;
  undefined8 uVar2;
  long *plVar3;
  long lVar4;
  long local_48;
  
  local_48 = 0;
  uVar2 = func_0x00025810d720();
  uVar2 = func_0x00025810acc0(param_1,&_kAPSKeyHolderLegacyVTable,uVar2,&local_48);
  if ((int)uVar2 == 0) {
    plVar3 = (long *)func_0x00025810ac50(local_48);
    plVar3[1] = param_3;
    if (param_3 != 0) {
      func_0x0002580f6a60(param_3);
    }
    *plVar3 = param_2;
    if (param_2 != 0) {
      func_0x0002580f6a60(param_2);
    }
    uVar2 = func_0x000258101e80(plVar3 + 2,0x10);
    if ((int)uVar2 == 0) {
      uVar2 = func_0x000258101e80(plVar3 + 4,0x10);
      if ((int)uVar2 == 0) {
        lVar4 = func_0x00025810d150();
        plVar3[6] = lVar4;
        if (lVar4 != 0) {
          if ((_gLogCategory_APKeyHolderLegacy < 0x1f) &&
             ((_gLogCategory_APKeyHolderLegacy != -1 ||
              (iVar1 = func_0x000258101e40(&_gLogCategory_APKeyHolderLegacy,0x200001e), iVar1 != 0))
             )) {
            _APKeyHolderLegacyCreate_cold_4(&local_48);
          }
          *param_4 = local_48;
          return 0;
        }
        _APKeyHolderLegacyCreate_cold_5();
        uVar2 = 0xfffee7d8;
      }
      else {
        _APKeyHolderLegacyCreate_cold_3();
      }
    }
    else {
      _APKeyHolderLegacyCreate_cold_2();
    }
  }
  else {
    _APKeyHolderLegacyCreate_cold_1();
  }
  if (local_48 != 0) {
    func_0x0002580f5830();
  }
  return uVar2;
}


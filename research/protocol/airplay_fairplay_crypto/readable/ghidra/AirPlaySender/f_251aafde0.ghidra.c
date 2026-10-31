/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aafde0
 * original code SHA256: f9345ba4d0f65a374bbebab7b6898abb51964b6420bdbce863ac67603902b455
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_APKeyHolderSharedKeyCreate(undefined8 param_1,long param_2,long param_3,long param_4,long *param_5)

{
  int iVar1;
  undefined8 uVar2;
  long *plVar3;
  long lVar4;
  long local_48;
  
  local_48 = 0;
  uVar2 = func_0x00025810d720();
  uVar2 = func_0x00025810acc0(param_1,&_kAPSKeyHolderSharedKeyVTable,uVar2,&local_48);
  if ((int)uVar2 == 0) {
    plVar3 = (long *)func_0x00025810ac50(local_48);
    *plVar3 = param_2;
    if (param_2 != 0) {
      func_0x0002580f6a60(param_2);
    }
    if (param_3 == 0) {
      uVar2 = func_0x000258101e80(plVar3 + 1,0x10);
      if ((int)uVar2 != 0) {
        _APKeyHolderSharedKeyCreate_cold_2();
        goto LAB_251aaff58;
      }
    }
    else {
      uVar2 = func_0x0002580f6a40(param_3);
      func_0x000258101800(param_3,0,uVar2,plVar3 + 1);
    }
    if (param_4 == 0) {
      uVar2 = func_0x000258101e80(plVar3 + 3,0x10);
      if ((int)uVar2 != 0) {
        _APKeyHolderSharedKeyCreate_cold_3();
        goto LAB_251aaff58;
      }
    }
    else {
      uVar2 = func_0x0002580f6a40(param_4);
      func_0x000258101800(param_4,0,uVar2,plVar3 + 3);
    }
    lVar4 = func_0x00025810d150();
    plVar3[5] = lVar4;
    if (lVar4 != 0) {
      if ((_gLogCategory_APKeyHolderSharedKey < 0x1f) &&
         ((_gLogCategory_APKeyHolderSharedKey != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APKeyHolderSharedKey,0x200001e), iVar1 != 0)))
         ) {
        _APKeyHolderSharedKeyCreate_cold_4(&local_48);
      }
      *param_5 = local_48;
      return 0;
    }
    _APKeyHolderSharedKeyCreate_cold_5();
    uVar2 = 0xfffee7d8;
  }
  else {
    _APKeyHolderSharedKeyCreate_cold_1();
  }
LAB_251aaff58:
  if (local_48 != 0) {
    func_0x0002580f5830();
  }
  return uVar2;
}


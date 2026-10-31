/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a355d0
 * original code SHA256: 1e4a141e32092d1da5bef910a21db865eaab6e2c2f332cbb16974cb848381266
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _APKeyHolderCoreUtilsCreate(undefined8 param_1,long param_2,long *param_3)

{
  int iVar1;
  undefined8 uVar2;
  long *plVar3;
  long lVar4;
  long local_38;
  
  local_38 = 0;
  uVar2 = func_0x00025810d720();
  uVar2 = func_0x00025810acc0(param_1,&_kAPSKeyHolderCoreUtilsVTable,uVar2,&local_38);
  if ((int)uVar2 == 0) {
    plVar3 = (long *)func_0x00025810ac50(local_38);
    *plVar3 = param_2;
    if (param_2 != 0) {
      func_0x0002580f6a60(param_2);
    }
    lVar4 = func_0x00025810d150();
    plVar3[1] = lVar4;
    if (lVar4 != 0) {
      if ((_gLogCategory_APKeyHolderCoreUtils < 0x1f) &&
         ((_gLogCategory_APKeyHolderCoreUtils != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APKeyHolderCoreUtils,0x200001e), iVar1 != 0)))
         ) {
        _APKeyHolderCoreUtilsCreate_cold_2(&local_38);
      }
      *param_3 = local_38;
      return 0;
    }
    _APKeyHolderCoreUtilsCreate_cold_3();
    uVar2 = 0xfffee7d8;
  }
  else {
    _APKeyHolderCoreUtilsCreate_cold_1();
  }
  if (local_38 != 0) {
    func_0x0002580f5830();
  }
  return uVar2;
}


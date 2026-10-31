/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa97a0
 * original code SHA256: 89035c4563a2f5d77b4451d5bf21eddc29a14363daabf17a604e81e8ae5c4c95
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_legacyKeyHolder_CreateDerivedAESKeyAndIVForLegacyStream
          (undefined8 param_1,undefined8 param_2,long *param_3,long *param_4)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  undefined1 *puVar4;
  long lVar5;
  long lVar6;
  long local_60;
  long local_58;
  undefined1 *local_50;
  undefined1 *local_48;
  
  local_50 = (undefined1 *)0x0;
  local_48 = (undefined1 *)0x0;
  local_60 = 0;
  local_58 = 0;
  iVar1 = func_0x00025810a1a0(&local_48,"%s%llu");
  lVar6 = (long)iVar1;
  iVar2 = func_0x00025810a1a0(&local_50,"%s%llu");
  lVar5 = (long)iVar2;
  uVar3 = _legacyKeyHolder_createDerivedKeyLegacy(param_1,local_48,lVar6,&local_58);
  if ((int)uVar3 == 0) {
    uVar3 = _legacyKeyHolder_createDerivedKeyLegacy(param_1,local_50,lVar5,&local_60);
    if ((int)uVar3 == 0) {
      if (param_3 != (long *)0x0) {
        *param_3 = local_58;
        local_58 = 0;
      }
      uVar3 = 0;
      if (param_4 != (long *)0x0) {
        *param_4 = local_60;
        local_60 = 0;
      }
    }
    else {
      _legacyKeyHolder_CreateDerivedAESKeyAndIVForLegacyStream_cold_2();
    }
  }
  else {
    _legacyKeyHolder_CreateDerivedAESKeyAndIVForLegacyStream_cold_1();
  }
  puVar4 = local_48;
  if (iVar1 != 0) {
    do {
      *puVar4 = 0;
      lVar6 = lVar6 + -1;
      puVar4 = puVar4 + 1;
    } while (lVar6 != 0);
  }
  puVar4 = local_50;
  if (iVar2 != 0) {
    do {
      *puVar4 = 0;
      lVar5 = lVar5 + -1;
      puVar4 = puVar4 + 1;
    } while (lVar5 != 0);
  }
  if (local_48 != (undefined1 *)0x0) {
    func_0x0002580f4d30();
    local_48 = (undefined1 *)0x0;
  }
  if (local_50 != (undefined1 *)0x0) {
    func_0x0002580f4d30();
    local_50 = (undefined1 *)0x0;
  }
  if (local_58 != 0) {
    func_0x0002580f5830();
  }
  if (local_60 != 0) {
    func_0x0002580f5830();
  }
  return uVar3;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519bfecc
 * original code SHA256: cebfd84d456170ad006012b9c86fc3dcdd83df80e25dcb99399b0e02bbba8d31
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_coreUtilsKeyHolder_CreateEncryptionKeysForStream
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined8 uVar2;
  undefined1 *puVar3;
  long lVar4;
  char *pcVar5;
  undefined1 *local_48;
  
  local_48 = (undefined1 *)0x0;
  pcVar5 = "DataStream-Salt";
  iVar1 = func_0x00025810a1a0(&local_48,"%s%llu");
  lVar4 = (long)iVar1;
  uVar2 = _coreUtilsKeyHolder_CreateDerivedKey
                    (param_1,local_48,lVar4,"DataStream-Input-Encryption-Key",0x1f,param_3,param_4,
                     param_8,pcVar5,param_2);
  if ((int)uVar2 == 0) {
    uVar2 = _coreUtilsKeyHolder_CreateDerivedKey
                      (param_1,local_48,lVar4,"DataStream-Output-Encryption-Key",0x20,param_5,
                       param_6,param_8,pcVar5,param_2);
    if ((int)uVar2 != 0) {
      _coreUtilsKeyHolder_CreateEncryptionKeysForStream_cold_2(uVar2);
    }
  }
  else {
    _coreUtilsKeyHolder_CreateEncryptionKeysForStream_cold_1();
  }
  puVar3 = local_48;
  if (iVar1 != 0) {
    do {
      *puVar3 = 0;
      lVar4 = lVar4 + -1;
      puVar3 = puVar3 + 1;
    } while (lVar4 != 0);
  }
  if (local_48 != (undefined1 *)0x0) {
    func_0x0002580f4d30();
  }
  return uVar2;
}


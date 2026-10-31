/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ace54c
 * original code SHA256: 45a756d91ba5c9afb075b678d17e5fea003296663cd0c014d3674354deba795b
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _APAuthenticationClientFairPlayCreate(undefined8 param_1,long param_2,long *param_3)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  long local_38;
  
  local_38 = 0;
  if (param_2 == 0) {
    _APAuthenticationClientFairPlayCreate_cold_2();
    uVar2 = 0xfffee787;
  }
  else {
    uVar2 = _APAuthenticationClientGetClassID();
    uVar2 = func_0x00025810acc0(param_1,&_kAPAuthenticationClientFairPlayVTable,uVar2,&local_38);
    if ((int)uVar2 == 0) {
      lVar3 = func_0x00025810ac50(local_38);
      *(long *)(lVar3 + 8) = param_2;
      func_0x0002580f6a60(param_2);
      if ((_gLogCategory_APAuthenticationClientFairPlay < 0x1f) &&
         ((_gLogCategory_APAuthenticationClientFairPlay != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APAuthenticationClientFairPlay,0x200001e),
          iVar1 != 0)))) {
        _APAuthenticationClientFairPlayCreate_cold_1(&local_38);
      }
      uVar2 = 0;
      *param_3 = local_38;
    }
    else {
      func_0x000258109a30(uVar2,"APAuthenticationClientFairPlayCreate",0x7c,0);
      if (local_38 != 0) {
        func_0x0002580f5830();
      }
    }
  }
  return uVar2;
}


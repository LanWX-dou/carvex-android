/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aaf934
 * original code SHA256: ec34bb75c18cb7e672ef8685c78c112ccece450a133559a066dab275db852474
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_coreUtilsPairing_createAirPlayPairingSession
          (undefined8 param_1,undefined8 param_2,int param_3,int param_4,long *param_5)

{
  int iVar1;
  undefined4 uVar4;
  long lVar2;
  undefined8 uVar3;
  undefined8 in_stack_ffffffffffffff40;
  undefined4 uVar5;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  long local_60;
  undefined8 local_58;
  cfstringStruct *local_50;
  long local_48;
  
  uVar5 = (undefined4)((ulong)in_stack_ffffffffffffff40 >> 0x20);
  uVar4 = (undefined4)((ulong)param_1 >> 0x20);
  local_48 = *_DAT_2681b4ee0;
  lVar2 = func_0x00025810ac50();
  local_60 = 0;
  local_70 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_78 = 0;
  uStack_80 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  uVar3 = func_0x00025810b9f0(&local_60,&local_b0,param_2);
  if ((int)uVar3 == 0) {
    if (param_3 == 0) {
      iVar1 = 0;
      if (*(char *)(lVar2 + 0x39) != '\0') {
        iVar1 = 0xc;
      }
    }
    else {
      iVar1 = 0x10;
    }
    if (param_4 != 0) {
      iVar1 = iVar1 + 1;
    }
    if (((iVar1 != 0) &&
        (func_0x00025810ba40(local_60,iVar1), _gLogCategory_APPairingClientCoreUtils < 0x33)) &&
       ((_gLogCategory_APPairingClientCoreUtils != -1 ||
        (iVar1 = func_0x000258101e40(&_gLogCategory_APPairingClientCoreUtils,0x32), iVar1 != 0)))) {
      uVar5 = uVar4;
      func_0x000258101eb0(&_gLogCategory_APPairingClientCoreUtils,
                          "OSStatus coreUtilsPairing_createAirPlayPairingSession(APPairingClientRef, PairingSessionType, Boolean, Boolean, PairingSessionRef *)"
                          ,0x32,"[%{ptr}] PairingFlags %d\n");
    }
    if (*(char *)(lVar2 + 0x3b) != '\0') {
      local_50 = &cfstringStruct_2761363d0;
      local_58 = *_DAT_2680d3198;
      uVar3 = func_0x000258102640(0,&local_50,&local_58,1,_DAT_2680d3340,_DAT_2680d3358);
      func_0x00025810ba30(local_60,uVar3);
      if ((_gLogCategory_APPairingClientCoreUtils < 0x33) &&
         ((_gLogCategory_APPairingClientCoreUtils != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APPairingClientCoreUtils,0x32), iVar1 != 0))))
      {
        uVar5 = uVar4;
        func_0x000258101eb0(&_gLogCategory_APPairingClientCoreUtils,
                            "OSStatus coreUtilsPairing_createAirPlayPairingSession(APPairingClientRef, PairingSessionType, Boolean, Boolean, PairingSessionRef *)"
                            ,0x32,"[%{ptr}] ACL %@\n");
      }
      func_0x0002580f5830(uVar3);
    }
    func_0x00025810ba50(local_60,&cfstringStruct_2761363f0,0x41504964,&cfstringStruct_276136410,
                        &cfstringStruct_276136410,0x41505072,&cfstringStruct_276136430,
                        &cfstringStruct_276136430,CONCAT44(uVar5,3));
    func_0x00025810ba60(local_60,&_gLogCategory_APPairingClientCoreUtils);
    uVar3 = func_0x00025810fd80(local_60,*(char *)(lVar2 + 0x41) != '\0');
    if ((int)uVar3 == 0) {
      *param_5 = local_60;
      goto LAB_251aafb54;
    }
    _coreUtilsPairing_createAirPlayPairingSession_cold_2(uVar3);
  }
  else {
    _coreUtilsPairing_createAirPlayPairingSession_cold_1();
  }
  if (local_60 != 0) {
    func_0x0002580f5830();
  }
LAB_251aafb54:
  if (*_DAT_2681b4ee0 != local_48) {
    uVar3 = func_0x0002580f4380();
    return uVar3;
  }
  return uVar3;
}


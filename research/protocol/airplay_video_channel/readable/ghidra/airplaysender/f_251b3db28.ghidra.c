/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b3db28
 * original code SHA256: 5ddefbe7058ae44de4fce9d503e9cd32a01f7961d70caf2aec846a0bfac43982
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _endpoint_setupScreenStream(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  long local_58;
  
  lVar2 = func_0x00025810ac50();
  local_58 = 0;
  uVar5 = param_1;
  lVar3 = func_0x00025810aa80(0,"[%{ptr}]");
  lVar4 = _endpoint_createBasicOptionsForStreamScreen(param_1,param_2,lVar3);
  if (lVar4 == 0) {
    _endpoint_setupScreenStream_cold_5();
    uVar5 = 0xffffbe87;
  }
  else {
    if (*(char *)(lVar2 + 0x141) == '\0') {
      uVar6 = func_0x0002581064f0(param_1);
      uVar5 = _APEndpointStreamScreenCreate
                        (uVar6,lVar4,*(undefined8 *)(lVar2 + 0x208),*(undefined8 *)(lVar2 + 0xe0),
                         *(undefined8 *)(lVar2 + 0x28),0,*(undefined8 *)(lVar2 + 0xd8),&local_58,
                         uVar5);
      if ((int)uVar5 != 0) {
        _endpoint_setupScreenStream_cold_3();
        goto LAB_251b3dcbc;
      }
    }
    else {
      if ((_gLogCategory_APEndpoint < 0x33) &&
         ((_gLogCategory_APEndpoint != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APEndpoint,0x2000032), iVar1 != 0)))) {
        _endpoint_setupScreenStream_cold_1(param_1);
      }
      uVar5 = func_0x0002581064f0(param_1);
      uVar5 = _APEndpointStreamScreenUDPCreate
                        (uVar5,lVar4,*(undefined8 *)(lVar2 + 0x208),*(undefined8 *)(lVar2 + 0xe0),
                         *(undefined8 *)(lVar2 + 0x28),0,*(undefined8 *)(lVar2 + 0xd8),0,&local_58);
      if ((int)uVar5 != 0) {
        _endpoint_setupScreenStream_cold_2();
        goto LAB_251b3dcbc;
      }
    }
    uVar6 = *_DAT_2680d5800;
    uVar5 = _endpoint_addEndpointStreamNotificationListeners(param_1,uVar6,local_58);
    if ((int)uVar5 == 0) {
      func_0x0002580f7000(*(undefined8 *)(lVar2 + 0xa8),uVar6,local_58);
      if ((_gLogCategory_APEndpoint < 0x33) &&
         ((_gLogCategory_APEndpoint != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APEndpoint,0x2000032), iVar1 != 0)))) {
        func_0x000258101eb0(&_gLogCategory_APEndpoint,
                            "OSStatus endpoint_setupScreenStream(FigEndpointRef, CFDictionaryRef)",
                            0x2000032,"[%{ptr}] Set up %@ stream [%{ptr}]\n");
      }
      uVar5 = 0;
    }
    else {
      _endpoint_setupScreenStream_cold_4();
    }
  }
LAB_251b3dcbc:
  if (lVar3 != 0) {
    func_0x0002580f5830(lVar3);
  }
  if (lVar4 != 0) {
    func_0x0002580f5830(lVar4);
  }
  if (local_58 != 0) {
    func_0x0002580f5830();
  }
  return uVar5;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aafbb0
 * original code SHA256: 6fffb4d5ea0ac13a862f3a0ab5eff87e8ed471f3af1ed1c7976e18b51c547ac6
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _coreUtilsPairing_validateMFiCertificate
              (undefined8 param_1,undefined8 param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  undefined8 uVar6;
  undefined8 extraout_x1;
  undefined8 extraout_x1_00;
  undefined1 auVar7 [16];
  int local_44;
  
  local_44 = 0;
  lVar3 = func_0x00025810ac50();
  auVar7 = func_0x00025810fd20(param_2,&cfstringStruct_276136490,&local_44);
  uVar6 = auVar7._8_8_;
  lVar4 = auVar7._0_8_;
  if (local_44 == 0) {
    uVar1 = 5;
    if (*(long *)(lVar3 + 0x20) == 0) {
      uVar1 = 1;
    }
    if ((_gLogCategory_APPairingClientCoreUtils < 0x1f) &&
       ((_gLogCategory_APPairingClientCoreUtils != -1 ||
        (iVar2 = func_0x000258101e40(&_gLogCategory_APPairingClientCoreUtils,0x200001e),
        uVar6 = extraout_x1_00, iVar2 != 0)))) {
      func_0x000258101eb0(&_gLogCategory_APPairingClientCoreUtils,
                          "OSStatus coreUtilsPairing_validateMFiCertificate(APPairingClientRef, PairingSessionRef, CFDataRef *)"
                          ,0x200001e,
                          "[%{ptr}] Validating MFA cert for pairing session [%{ptr}] with features 0x%llx\n"
                         );
      uVar6 = extraout_x1;
    }
    uVar5 = func_0x000258030bf0(_DAT_26815bf68,uVar6,uVar1,lVar4);
    if ((uVar5 & 1) == 0) {
      _coreUtilsPairing_validateMFiCertificate_cold_2(&local_44,param_1,param_2,uVar1);
    }
    else {
      if ((_gLogCategory_APPairingClientCoreUtils < 0x1f) &&
         ((_gLogCategory_APPairingClientCoreUtils != -1 ||
          (iVar2 = func_0x000258101e40(&_gLogCategory_APPairingClientCoreUtils,0x200001e),
          iVar2 != 0)))) {
        func_0x000258101eb0(&_gLogCategory_APPairingClientCoreUtils,
                            "OSStatus coreUtilsPairing_validateMFiCertificate(APPairingClientRef, PairingSessionRef, CFDataRef *)"
                            ,0x200001e,
                            "[%{ptr}] Validated MFA cert for pairing session [%{ptr}] with features 0x%llx\n"
                           );
      }
      if (param_3 != (undefined8 *)0x0) {
        uVar6 = func_0x0002580f6a60(lVar4);
        *param_3 = uVar6;
      }
    }
  }
  else {
    _coreUtilsPairing_validateMFiCertificate_cold_1();
  }
  if (lVar4 != 0) {
    func_0x0002580f5830(lVar4);
  }
  return local_44;
}


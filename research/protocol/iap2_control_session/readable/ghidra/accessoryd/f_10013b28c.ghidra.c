/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013b28c
 * original code SHA256: f7e5131f6b17a6f724b52955ad188ca74fb4eb8efd487714abb47c2e1c2ee0f1
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iap2_identification_cancelIdentificationHandler(long param_1)

{
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  undefined8 unaff_x20;
  undefined1 auVar6 [16];
  undefined2 local_50 [8];
  
  if (param_1 != 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x1d) {
      if (DAT_10023e660 != -1) {
        _OUTLINED_FUNCTION_1();
      }
      _OUTLINED_FUNCTION_27();
    }
    else {
      unaff_x20 = *(undefined8 *)(_gLogObjects + 0xe0);
    }
    iVar1 = _os_log_type_enabled(unaff_x20,0);
    if (iVar1 != 0) {
      local_50[0] = 0;
      uVar3 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar3,unaff_x20,0,"Identification cancelled by accessory!",local_50,2);
    }
    uVar2 = _iap2_identification_getState(param_1);
    if ((uVar2 & 0xfffffffd) == 1) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1d)) {
        if (DAT_10023e660 != -1) {
          _OUTLINED_FUNCTION_1();
        }
        _OUTLINED_FUNCTION_27();
      }
      _OUTLINED_FUNCTION_15();
      iVar1 = _os_log_type_enabled();
      if (iVar1 != 0) {
        _OUTLINED_FUNCTION_4();
        auVar6 = _OUTLINED_FUNCTION_44();
        __os_log_impl(auVar6._0_8_,auVar6._8_8_,1);
      }
      _iap2_identification_setIdentificationState(param_1,4);
      lVar4 = _acc_userNotifications_createAccessoryNotSupportedCF();
      lVar5 = _acc_userNotifications_createIdentifier
                        (&cf_identification,*(undefined8 *)(param_1 + 8));
      _ACCUNSetIdentifier(lVar4,lVar5);
      if (lVar5 != 0) {
        _CFRelease(lVar5);
      }
      _ACCUNSetGroupIdentifier(lVar4,*(undefined8 *)(param_1 + 0x10));
      _OUTLINED_FUNCTION_12();
      _ACCUNManagerPresentNotification();
      if (lVar4 != 0) {
        _CFRelease(lVar4);
      }
    }
  }
  return param_1 != 0;
}


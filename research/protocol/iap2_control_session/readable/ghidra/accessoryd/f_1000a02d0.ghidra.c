/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000a02d0
 * original code SHA256: f61afb2a8aa840427c9fc446c4e2db720b022445b62541cc6b2bb25025bc97b2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool __parseIdentificationPreferredBundleSeedID
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  long lVar2;
  long *plVar3;
  undefined *puVar4;
  undefined8 uVar5;
  undefined4 local_40;
  long local_3c;
  int local_34;
  
  local_34 = 0;
  iVar1 = _iAP2MsgGetParamID(param_3);
  if (iVar1 == 0xb) {
    lVar2 = _iAP2MsgCopyDataAsCFString(param_3,&local_34);
    if ((lVar2 == 0) || (local_34 != 0)) {
      uVar5 = 10;
      iVar1 = local_34;
      if (lVar2 == 0) goto LAB_1000a0460;
    }
    else {
      _iap2_features_createFeature(param_1,10);
      plVar3 = (long *)_iap2_feature_getFeature(param_1,10);
      if (plVar3 != (long *)0x0) {
        if (*plVar3 != 0) {
          _CFRelease();
        }
        *plVar3 = lVar2;
        _CFRetain(lVar2);
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x21)) {
          puVar4 = PTR___os_log_default_10022bbb0;
          if (DAT_10023e9d8 != -1) {
            _iap2_externalAccessory_openEASession_cold_3();
            puVar4 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar4 = *(undefined **)(_gLogObjects + 0x100);
        }
        iVar1 = _os_log_type_enabled(puVar4,0);
        if (iVar1 != 0) {
          local_3c = *plVar3;
          local_40 = (undefined4)DAT_1001b3088;
          __os_log_impl(0x100000000,puVar4,0,"preferredAppBundleSeedID %@",&local_40,0xc);
        }
        _CFRelease(lVar2);
        iVar1 = local_34;
        goto LAB_1000a0470;
      }
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x21)) {
        puVar4 = PTR___os_log_default_10022bbb0;
        if (DAT_10023e9d8 != -1) {
          _iap2_externalAccessory_openEASession_cold_3();
          puVar4 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0x100);
      }
      iVar1 = _os_log_type_enabled(puVar4,0x10);
      if (iVar1 != 0) {
        __parseIdentificationPreferredBundleSeedID_cold_3(puVar4);
      }
      uVar5 = 0x11;
    }
    _CFRelease(lVar2);
    iVar1 = local_34;
  }
  else {
    uVar5 = 0x11;
    iVar1 = 0;
  }
LAB_1000a0460:
  _iap2_identification_addRejectParam(param_1,0xb,uVar5);
LAB_1000a0470:
  return iVar1 == 0;
}


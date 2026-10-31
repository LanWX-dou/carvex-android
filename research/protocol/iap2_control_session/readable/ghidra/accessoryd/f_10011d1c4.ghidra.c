/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011d1c4
 * original code SHA256: e2d2e23f75e98b1534687d0e8b1ce17ca32790b6d19141cc880851138c0074cd
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



uint _iap2_sessionControl_cleanup(long *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined *local_70;
  undefined8 local_68;
  code *local_60;
  undefined *puStack_58;
  undefined8 local_50;
  undefined *local_48;
  undefined8 local_40;
  code *local_38;
  undefined *puStack_30;
  undefined8 local_28;
  
  if (((param_1 == (long *)0x0) || ((long *)*param_1 == (long *)0x0)) || (*(long *)*param_1 == 0)) {
    uVar2 = 0;
  }
  else {
    iVar1 = _acc_endpoint2_getTransportType();
    if (iVar1 == 8) {
      local_28 = 0;
      if (param_1[2] != 0) {
        local_28 = _CFRetain();
      }
      local_48 = PTR___NSConcreteStackBlock_10022bb78;
      local_40 = DAT_1001b3118;
      local_38 = ___iap2_sessionControl_cleanup_block_invoke;
      puStack_30 = &___block_descriptor_tmp;
      _acc_manager2_performPlatformWorkAsync(&local_48);
    }
    _acc_endpoint2_externalAccessory_removeEAAccessoryForPrimaryEndpoint(param_1[1]);
    _OUTLINED_FUNCTION_8();
    _iap2_endpoint_setInitialized();
    iVar1 = _iap2_identification_isIdentifiedForWirelessCarPlay(param_1);
    if ((iVar1 != 0) && (param_1[1] != 0)) {
      local_50 = _CFRetain();
      local_70 = PTR___NSConcreteStackBlock_10022bb78;
      local_68 = DAT_1001b3118;
      local_60 = ___iap2_sessionControl_cleanup_block_invoke_2;
      puStack_58 = &___block_descriptor_tmp_1;
      _acc_manager2_performPlatformWorkAsync(&local_70);
    }
    _OUTLINED_FUNCTION_8();
    uVar2 = _iap2_features_destroyFeatures();
    _OUTLINED_FUNCTION_44();
    uVar3 = _iap2_features_destroyFeatures();
    uVar2 = uVar2 & uVar3;
    if ((void *)param_1[0x19] != (void *)0x0) {
      _free((void *)param_1[0x19]);
      param_1[0x19] = 0;
    }
  }
  return uVar2;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100123108
 * original code SHA256: bd7d94e34bc6d01fc104b6eac2c1b288e8e23a2f50c39acc8685e7d0603d340a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_deviceAuthentication_RequestDeviceCertificate(undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined *local_58;
  undefined8 local_50;
  code *local_48;
  undefined *puStack_40;
  undefined8 *local_38;
  undefined4 local_30;
  char *local_2c;
  
  uVar1 = 0;
  if (((param_1 != (undefined8 *)0x0) && (param_2 != 0)) &&
     (lVar2 = _iap2_feature_getFeature(param_1,7), uVar1 = 0, lVar2 != 0)) {
    if (param_1[3] == 0) {
      uVar3 = _logObjectForModule();
      uVar1 = _os_log_type_enabled(uVar3,0x10);
      if ((int)uVar1 != 0) {
        local_30 = (undefined4)DAT_1001b3090;
        local_2c = "iap2_deviceAuthentication_RequestDeviceCertificate";
        uVar1 = _OUTLINED_FUNCTION_6();
        __os_log_error_impl(uVar1,uVar3,0x10,"%s No processing queue!",&local_30,0xc);
        uVar1 = 0;
      }
    }
    else {
      local_58 = PTR___NSConcreteStackBlock_10022bb78;
      local_50 = DAT_1001b3118;
      local_48 = ___iap2_deviceAuthentication_RequestDeviceCertificate_block_invoke;
      puStack_40 = &___block_descriptor_tmp;
      local_38 = param_1;
      _acc_protocolEndpoint_performAsync(*param_1,*(undefined1 *)(param_1 + 4),param_1[3],&local_58)
      ;
      uVar1 = 1;
    }
  }
  return uVar1;
}


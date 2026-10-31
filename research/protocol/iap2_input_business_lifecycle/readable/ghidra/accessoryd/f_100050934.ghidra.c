/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100050934
 * original code SHA256: 6ca108c1bcc2c736ed804028af9c97470d44dd4157f25b6b964e925b4d91df21
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iap2_identification_identificationInfoUpdateHandler(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  undefined8 *puVar5;
  undefined *puVar6;
  char *pcVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  undefined2 local_50 [8];
  undefined4 local_40;
  int local_3c;
  
  puVar8 = (undefined4 *)local_50;
  iVar1 = _iap2_identification_getState();
  if (iVar1 != 6) goto LAB_100050ac8;
  pvVar4 = (void *)_iap2_identification_createIdentificationInfo();
  if (pvVar4 == (void *)0x0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x1d) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (DAT_10023e660 != -1) {
        __addRejectParam_cold_1();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0xe0);
    }
    iVar2 = _os_log_type_enabled(puVar6,0);
    if (iVar2 != 0) {
      local_50[0] = 0;
      pcVar7 = "iAP2MsgIdentificationInfoUpdate: IdentificationInfo invalid\n";
      uVar9 = 2;
LAB_100050a98:
      __os_log_impl(0x100000000,puVar6,0,pcVar7,puVar8,uVar9);
    }
  }
  else {
    iVar2 = _iAP2MsgForEachParamDo
                      (param_2,0,_iap2_identification_cbIdentificationInfoUpdateParams,pvVar4);
    if (iVar2 == 0) {
      _iap2_identification_updateIdentificationInfo(param_1,pvVar4);
    }
    else {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1d)) {
        puVar6 = PTR___os_log_default_10022bbb0;
        if (DAT_10023e660 != -1) {
          __addRejectParam_cold_1();
          puVar6 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar6 = *(undefined **)(_gLogObjects + 0xe0);
      }
      iVar3 = _os_log_type_enabled(puVar6,0);
      if (iVar3 != 0) {
        local_40 = (undefined4)DAT_1001b30b0;
        pcVar7 = "IdentificationInfoUpdate message processing error: %d\n";
        puVar8 = &local_40;
        uVar9 = 8;
        local_3c = iVar2;
        goto LAB_100050a98;
      }
    }
  }
  puVar5 = *(undefined8 **)((long)pvVar4 + 0xe8);
  if (puVar5 != (undefined8 *)0x0) {
    if ((void *)*puVar5 != (void *)0x0) {
      _free((void *)*puVar5);
      puVar5 = *(undefined8 **)((long)pvVar4 + 0xe8);
      if (puVar5 == (undefined8 *)0x0) goto LAB_100050ac0;
    }
    _free(puVar5);
  }
LAB_100050ac0:
  _free(pvVar4);
LAB_100050ac8:
  return iVar1 != 6;
}


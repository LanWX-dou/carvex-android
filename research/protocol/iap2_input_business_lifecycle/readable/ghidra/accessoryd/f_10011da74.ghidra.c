/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011da74
 * original code SHA256: c037402e1e6222cfe5440261fdaf0046105c8ec45dee49a742c1dcd1f65d9b2f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_sessionControl_identificationStateChanged(long *param_1,long param_2)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  long lVar8;
  undefined8 uVar9;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  undefined *puVar10;
  undefined *local_80;
  undefined8 local_78;
  code *local_70;
  undefined *puStack_68;
  undefined8 local_60;
  undefined4 local_58;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  if (*param_1 == 0) {
    return;
  }
  iVar6 = _acc_endpoint2_getTransportType();
  lVar8 = _acc_endpoint2_getParentConnection(*param_1);
  if (lVar8 == 0) {
    bVar3 = false;
  }
  else {
    iVar7 = _acc_connection2_getType_internal();
    bVar3 = iVar7 == 6;
  }
  if ((int)param_2 != 6) {
    return;
  }
  cVar1 = SBORROW4(iVar6,8);
  cVar2 = iVar6 + -8 < 0;
  uVar4 = iVar6 == 8;
  if ((((!(bool)uVar4) && (!(bool)(iVar6 != 0 & bVar3))) || ((long *)*param_1 == (long *)0x0)) ||
     (*(long *)*param_1 == 0)) goto LAB_10011dd08;
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_7(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_6();
    if (!(bool)uVar4) {
      _OUTLINED_FUNCTION_1();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_27();
  }
  else {
    param_2 = *(long *)(extraout_x8 + 200);
  }
  iVar6 = _os_log_type_enabled(param_2,0);
  if (iVar6 != 0) {
    local_80 = (undefined *)((ulong)local_80 & 0xffffffffffff0000);
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_11();
  }
  lVar8 = _acc_endpoint2_getParentConnection(*param_1);
  if (lVar8 != 0) {
    _acc_connection2_isAuthenticated_internal(lVar8,6);
  }
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_7(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_6();
    if (!(bool)uVar4) {
      _OUTLINED_FUNCTION_1();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_27();
  }
  else {
    param_2 = *(long *)(extraout_x8_00 + 200);
  }
  iVar6 = _os_log_type_enabled(param_2,1);
  if (iVar6 != 0) {
    local_80 = (undefined *)CONCAT44(*(undefined4 *)(*param_1 + 0x18),(int)DAT_1001b30b0);
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_4();
    __os_log_impl();
  }
  param_2 = _iap2_identification_getTransportComponent(param_1,2);
  if (param_2 != 0) {
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_7(), cVar2 != cVar1)) {
      _OUTLINED_FUNCTION_6();
      puVar10 = PTR___os_log_default_10022bbb0;
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_1();
        _dispatch_once();
        puVar10 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar10 = *(undefined **)(extraout_x8_01 + 200);
    }
    iVar6 = _os_log_type_enabled(puVar10,1);
    if (iVar6 != 0) {
      local_80 = (undefined *)((ulong)local_80 & 0xffffffffffff0000);
      uVar9 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar9,puVar10,1,"Found USB Host identification component!",&local_80,2);
    }
  }
  if (param_1[2] == 0) {
    local_60 = 0;
    if (param_2 != 0) goto LAB_10011dc60;
LAB_10011dc90:
    local_58 = 0;
    uVar4 = 0;
    local_54 = 0;
    local_51 = 0;
    local_52 = 0;
  }
  else {
    local_60 = _CFRetain();
    if (param_2 == 0) goto LAB_10011dc90;
LAB_10011dc60:
    if (*(char *)(param_2 + 0x35) != '\x01') goto LAB_10011dc90;
    uVar4 = *(undefined1 *)(param_2 + 0x37);
    uVar5 = _iap2_identification_isIdentifiedForCarPlay(param_1);
    local_58 = _iAP2_carPlayConnectionType(param_1);
    local_51 = *(undefined1 *)(param_2 + 0x36);
    local_54 = 1;
    local_52 = uVar5;
  }
  local_80 = PTR___NSConcreteStackBlock_10022bb78;
  local_78 = DAT_1001b3118;
  local_70 = ____configureAndUnlockUSBHostInterfaces_block_invoke;
  puStack_68 = &___block_descriptor_tmp_6;
  local_53 = uVar4;
  _acc_manager2_performPlatformWorkAsync(&local_80);
LAB_10011dd08:
  iVar6 = _iap2_accAuthentication_getState(param_1);
  if (iVar6 == 0) {
    _OUTLINED_FUNCTION_8();
    _iap2_features_startFeatureFromDevice();
  }
  else {
    iVar6 = _iap2_accAuthentication_getState(param_1);
    cVar1 = SBORROW4(iVar6,2);
    cVar2 = iVar6 + -2 < 0;
    uVar4 = iVar6 == 2;
    if ((bool)uVar4) {
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_7(), cVar2 != cVar1)) {
        _OUTLINED_FUNCTION_6();
        if (!(bool)uVar4) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      else {
        param_2 = *(long *)(extraout_x8_02 + 200);
      }
      iVar6 = _os_log_type_enabled(param_2,1);
      if (iVar6 != 0) {
        _OUTLINED_FUNCTION_2(param_1[1],DAT_1001b3088);
        _OUTLINED_FUNCTION_4();
        __os_log_impl();
      }
      __authAndIDComplete(param_1);
    }
  }
  return;
}


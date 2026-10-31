/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10017a0f0
 * original code SHA256: 10adb307555cfa1fe1c7f98b26558bf4a74995f0bfec1539ee632b1a2822abb5
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _acc_protocolRouter_initProtocolLayer(long *param_1)

{
  undefined1 uVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  long extraout_x8;
  int extraout_w9;
  long lVar5;
  undefined *local_90;
  undefined8 local_88;
  code *local_80;
  undefined *puStack_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 local_60;
  undefined4 local_58;
  undefined1 local_54;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if ((param_1[7] != 0) &&
     (uVar2 = _acc_protocolRouter_destroyProtocolLayer(param_1), (int)uVar2 == 0)) {
    return uVar2;
  }
  if (0x11 < *(int *)((long)param_1 + 0x1c) - 1U) {
switchD_10017a160_caseD_9:
    _OUTLINED_FUNCTION_6();
    if (extraout_x8 == 0 || extraout_w9 < 0x14) {
      if (_logObjectForModule_onceToken != -1) {
        _OUTLINED_FUNCTION_1();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    uVar2 = _OUTLINED_FUNCTION_71();
    if ((int)uVar2 == 0) {
      return uVar2;
    }
    _OUTLINED_FUNCTION_11(*(undefined4 *)((long)param_1 + 0x1c),DAT_1001b30b0);
    _OUTLINED_FUNCTION_5();
    return 0;
  }
  uVar2 = 1;
  switch(*(int *)((long)param_1 + 0x1c)) {
  default:
    goto switchD_10017a160_caseD_1;
  case 3:
    lVar3 = *param_1;
    if (lVar3 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = _acc_connection2_isAuthenticated_internal(lVar3,0);
    }
    if (param_1[1] == 0) {
      return 0;
    }
    lVar5 = param_1[2];
    if (lVar5 == 0) {
      return 0;
    }
    uVar4 = _CFRetain(param_1[1]);
    uStack_68 = _CFRetain(lVar5);
    lVar5 = param_1[3];
    if (lVar3 == 0) {
      local_58 = 0xb;
    }
    else {
      local_58 = _acc_connection2_getType_internal(lVar3);
    }
    local_90 = PTR___NSConcreteStackBlock_10022bb78;
    local_88 = DAT_1001b3118;
    local_80 = ___acc_protocolRouter_initProtocolLayer_block_invoke;
    puStack_78 = &___block_descriptor_tmp;
    local_60 = NEON_rev64(lVar5,4);
    local_70 = uVar4;
    local_54 = uVar1;
    _acc_manager2_performPlatformWorkAsync(&local_90);
    return 1;
  case 4:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _iap2_endpoint_create();
    break;
  case 5:
  case 6:
  case 7:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _ea_endpoint_create();
    break;
  case 8:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _oobPairing_endpoint_create();
    break;
  case 9:
  case 0xc:
    goto switchD_10017a160_caseD_9;
  case 10:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _accAuthProtocol_endpoint_create();
    break;
  case 0xb:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _configStream_endpoint_create();
    break;
  case 0xd:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _audioProductCerts_endpoint_create();
    break;
  case 0xe:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _mfi4Auth_endpoint_create();
    break;
  case 0xf:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _accSNTPTimeSync_endpoint_create();
    break;
  case 0x10:
    uVar2 = _platform_systemInfo_supportsQiAuth();
    if ((int)uVar2 == 0) {
      return uVar2;
    }
    _OUTLINED_FUNCTION_6();
    lVar3 = _qiAuth_endpoint_create();
    break;
  case 0x11:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _t56_endpoint_create();
    break;
  case 0x12:
    _OUTLINED_FUNCTION_6(1);
    lVar3 = _genericMFi_endpoint_create();
  }
  param_1[7] = lVar3;
  uVar2 = (ulong)(lVar3 != 0);
switchD_10017a160_caseD_1:
  return uVar2;
}


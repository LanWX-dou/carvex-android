/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000995c
 * original code SHA256: 394d4c2bca476b33939a0823a36884bc4b31c18a622340100ea9fc62d0854e35
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Type propagation algorithm not settling */

undefined8 _acc_protocolRouter_routeIncomingData(long param_1,long param_2)

{
  uint uVar1;
  bool bVar2;
  undefined1 uVar3;
  int iVar4;
  ulong uVar5;
  undefined8 uVar6;
  long extraout_x8;
  int extraout_w9;
  undefined8 uVar7;
  undefined *local_88;
  undefined8 local_80;
  code *local_78;
  undefined *puStack_70;
  undefined8 local_68;
  long lStack_60;
  undefined8 local_58;
  
  if (param_1 == 0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  uVar1 = *(int *)(param_1 + 0x1c) - 3;
  if (0xf < uVar1) {
switchD_1000099c8_caseD_3:
    bVar2 = uVar1 == 0xf;
    _OUTLINED_FUNCTION_12();
    uVar3 = !bVar2 && extraout_w9 == 0x14;
    if (bVar2 || extraout_w9 < 0x14) {
      _OUTLINED_FUNCTION_11();
      if (!(bool)uVar3) {
        _OUTLINED_FUNCTION_1();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    else {
      param_2 = *(long *)(extraout_x8 + 0x98);
    }
    iVar4 = _OUTLINED_FUNCTION_71();
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_11(*(undefined4 *)(param_1 + 0x1c),DAT_1001b30b0);
      _OUTLINED_FUNCTION_5();
    }
    goto LAB_100009b60;
  }
  uVar3 = uVar1 == 0xf;
  switch(uVar1) {
  default:
    uVar6 = _CFRetain(*(undefined8 *)(param_1 + 0x10));
    uVar7 = *(undefined8 *)(param_1 + 0x18);
    _CFRetain(param_2);
    local_88 = PTR___NSConcreteStackBlock_10022bb78;
    local_80 = DAT_1001b3118;
    local_78 = ___acc_protocolRouter_routeIncomingData_block_invoke;
    puStack_70 = &___block_descriptor_tmp_2;
    local_58 = NEON_rev64(uVar7,4);
    local_68 = uVar6;
    lStack_60 = param_2;
    _acc_manager2_performPlatformWorkAsync(&local_88);
    goto LAB_100009b30;
  case 1:
    _kdebug_trace(0x2b940008,0,0,0,0);
    _OUTLINED_FUNCTION_7();
    uVar5 = _iap2_endpoint_processIncomingData();
    goto joined_r0x000100009a20;
  case 2:
  case 4:
    _acc_endpoint2_externalAccessory_handleIncomingEADataFromAccessoryForEndpointUUID
              (*(undefined8 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x18),param_2);
    goto LAB_100009b30;
  case 3:
  case 6:
  case 9:
    goto switchD_1000099c8_caseD_3;
  case 5:
    _OUTLINED_FUNCTION_7(0);
    uVar5 = _oobPairing_endpoint_processIncomingData();
    goto joined_r0x000100009a20;
  case 7:
    _OUTLINED_FUNCTION_7(0);
    uVar5 = _accAuthProtocol_endpoint_processIncomingData();
joined_r0x000100009a20:
    if ((uVar5 & 1) == 0) goto LAB_100009b60;
    goto LAB_100009b30;
  case 8:
    _OUTLINED_FUNCTION_7(0);
    uVar5 = _configStream_endpoint_processIncomingData();
    break;
  case 10:
    _OUTLINED_FUNCTION_7(0);
    uVar5 = _audioProductCerts_endpoint_processIncomingData();
    break;
  case 0xb:
    _OUTLINED_FUNCTION_7(0);
    uVar5 = _mfi4Auth_endpoint_processIncomingData();
    break;
  case 0xc:
    _OUTLINED_FUNCTION_7(0);
    uVar5 = _accSNTPTimeSync_endpoint_processIncomingData();
    break;
  case 0xd:
    iVar4 = _platform_systemInfo_supportsQiAuth();
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_7();
      uVar5 = _qiAuth_endpoint_processIncomingData();
      break;
    }
    goto LAB_100009b60;
  case 0xe:
    _OUTLINED_FUNCTION_7(0);
    uVar5 = _t56_endpoint_processIncomingData();
    break;
  case 0xf:
    _OUTLINED_FUNCTION_7(0);
    uVar5 = _genericMFi_endpoint_processIncomingData();
  }
  if ((uVar5 & 1) == 0) {
LAB_100009b60:
    if ((_gLogObjects == 0) || (uVar3 = _gNumLogObjects == 0x14, _gNumLogObjects < 0x14)) {
      _OUTLINED_FUNCTION_11();
      if (!(bool)uVar3) {
        _OUTLINED_FUNCTION_1();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    else {
      param_2 = *(long *)(_gLogObjects + 0x98);
    }
    uVar6 = _os_log_type_enabled(param_2,0x10);
    if ((int)uVar6 != 0) {
      _OUTLINED_FUNCTION_4(*(undefined8 *)(param_1 + 0x10),DAT_1001b30f0);
      _OUTLINED_FUNCTION_8();
      __os_log_error_impl();
      uVar6 = 0;
    }
  }
  else {
LAB_100009b30:
    uVar6 = 1;
  }
  return uVar6;
}


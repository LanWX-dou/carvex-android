/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100030d4c
 * original code SHA256: 6e91c117c545f9c40a3a72f2ad6987ebb9cf3b1e07166ab731d4e17d3312771e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1 _iap2_endpoint_destroy(undefined8 *param_1)

{
  int iVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined *puVar4;
  long *plVar5;
  undefined8 uVar6;
  dispatch_object_t object;
  undefined *local_c8;
  undefined8 local_c0;
  code *local_b8;
  undefined *puStack_b0;
  long *local_a8;
  undefined4 local_a0;
  char *local_9c;
  undefined *local_90;
  undefined8 local_88;
  code *local_80;
  undefined *puStack_78;
  long *local_70;
  undefined *local_68;
  undefined8 local_60;
  code *local_58;
  undefined *puStack_50;
  long *local_48;
  
  if (param_1 == (undefined8 *)0x0) {
    _iap2_endpoint_destroy_cold_3(&local_a0);
  }
  else {
    plVar5 = (long *)*param_1;
    if (plVar5 == (long *)0x0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        puVar4 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          __iap2_endpoint_dispatchQueueFinalizer_cold_1();
          puVar4 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar1 = _os_log_type_enabled(puVar4,0);
      local_a0._0_1_ = 0;
      if (iVar1 != 0) {
        local_a0 = (uint)local_a0._2_2_ << 0x10;
        __os_log_impl(0x100000000,puVar4,0,"iAP2 Endpoint Destroy. *ppProtocolEndpoint is null!",
                      &local_a0,2);
        local_a0._0_1_ = 0;
      }
    }
    else {
      uVar2 = _acc_endpoint2_isWireless(*plVar5);
      if ((uVar2 & 1) == 0) {
        _iap2_power_unregisterForSleepNotification(plVar5);
      }
      uVar6 = *(undefined8 *)(*plVar5 + 0x10);
      uVar3 = _acc_endpoint2_getTransportTypeString();
      _acc_platform_packetLogging_logEventForEndpoint
                (uVar6,uVar3,"DETACH","iAP2 accessory detached!");
      uVar3 = DAT_1001b3118;
      local_68 = PTR___NSConcreteStackBlock_10022bb78;
      local_60 = DAT_1001b3118;
      local_58 = ___iap2_endpoint_destroy_block_invoke;
      puStack_50 = &___block_descriptor_tmp;
      local_48 = plVar5;
      _acc_protocolEndpoint_performSync(*plVar5,(char)plVar5[4],plVar5[3],&local_68);
      if ((char)plVar5[4] == '\x01') {
        object = *(dispatch_object_t *)(plVar5 + 3);
        plVar5[3] = 0;
        local_90 = PTR___NSConcreteStackBlock_10022bb78;
        local_88 = uVar3;
        local_80 = ___iap2_endpoint_destroy_block_invoke_4;
        puStack_78 = &___block_descriptor_tmp_5;
        local_70 = plVar5;
        _dispatch_sync(object._os_obj,&local_90);
        _dispatch_sync(object._os_obj,&___block_literal_global);
        _dispatch_release(object);
      }
      else {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
          puVar4 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            _iap2_endpoint_destroy_cold_1();
            puVar4 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar4 = *(undefined **)(_gLogObjects + 0xb0);
        }
        iVar1 = _os_log_type_enabled(puVar4,0);
        if (iVar1 != 0) {
          local_9c = _dispatch_queue_get_label((dispatch_queue_t)0x0);
          local_a0 = (int)DAT_1001b3090;
          __os_log_impl(0x100000000,puVar4,0,"iAP2 Endpoint Destroy. currentDispatchQueue: %s",
                        &local_a0,0xc);
        }
        _iAP2LinkRunLoopShuttingDown(plVar5[5]);
        _iap2_sessionControl_cleanup(plVar5);
        _iap2_sessionFileTransfer_cleanup(plVar5);
        _iap2_sessionLog_cleanup(plVar5);
        local_c8 = PTR___NSConcreteStackBlock_10022bb78;
        local_c0 = uVar3;
        local_b8 = ___iap2_endpoint_destroy_block_invoke_8;
        puStack_b0 = &___block_descriptor_tmp_9;
        local_a8 = plVar5;
        _dispatch_async(plVar5[3],&local_c8);
        plVar5[3] = 0;
      }
      *param_1 = 0;
      local_a0._0_1_ = 1;
    }
  }
  return (undefined1)local_a0;
}


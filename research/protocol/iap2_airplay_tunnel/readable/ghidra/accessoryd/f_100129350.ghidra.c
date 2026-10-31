/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100129350
 * original code SHA256: f342cee149c7c85316a54178f872178ad5dce549db7904e449b3de4a439b86b9
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long * _iap2_endpoint_create(long param_1,long param_2)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  long *context;
  long lVar4;
  dispatch_object_t object;
  undefined8 uVar5;
  ulong uVar6;
  undefined1 uVar7;
  undefined8 uVar8;
  undefined2 local_40 [8];
  
  if (param_1 == 0) {
    uVar5 = _logObjectForModule(0x15);
    iVar3 = _os_log_type_enabled(uVar5,0x10);
    if (iVar3 != 0) {
      local_40[0] = 0;
      uVar8 = _OUTLINED_FUNCTION_6();
      __os_log_error_impl(uVar8,uVar5,0x10,"pProtocolEndpoint = NULL",local_40,2);
    }
LAB_1001295d8:
    context = (long *)0x0;
  }
  else {
    context = (long *)_malloc_type_calloc(1,0x1d8,0x10f00404a663fe2);
    if (context == (long *)0x0) {
      return (long *)0x0;
    }
    *context = param_1;
    puVar1 = PTR__kCFAllocatorDefault_10022bce0;
    if (*(long *)(param_1 + 0x10) == 0) {
      lVar4 = 0;
    }
    else {
      lVar4 = _CFStringCreateCopy(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0);
    }
    context[1] = lVar4;
    if (*(long *)(param_1 + 8) == 0) {
      lVar4 = 0;
    }
    else {
      lVar4 = _CFStringCreateCopy(*(undefined8 *)puVar1);
    }
    context[2] = lVar4;
    if (param_2 == 0) {
      object._os_obj =
           (_os_object_s *)_dispatch_queue_create("iAP2Endpoint",(dispatch_queue_attr_t)0x0);
      ((dispatch_object_t *)(context + 3))->_os_obj = (_os_object_s *)object;
      if (object._os_obj == (_os_object_s *)0x0) {
        _free(context);
        goto LAB_1001295d8;
      }
      _dispatch_set_context(object,context);
      _dispatch_set_finalizer_f
                (*(dispatch_object_t *)(context + 3),__iap2_endpoint_dispatchQueueFinalizer);
      uVar7 = 1;
    }
    else {
      uVar7 = 0;
      context[3] = param_2;
    }
    *(undefined1 *)(context + 4) = uVar7;
    context[5] = 0;
    *(undefined4 *)((long)context + 100) = 0;
    *(undefined1 *)(context + 0xd) = 0;
    context[0x19] = 0;
    context[0x37] = 0;
    context[0xe] = 0;
    context[0xf] = 0;
    lVar4 = _CFAbsoluteTimeGetCurrent();
    context[0x3a] = lVar4;
    if (context[5] == 0) {
      *(int *)(context + 6) = (int)DAT_1001b32c0;
      *(undefined2 *)(context + 7) = 0x7fff;
      *(undefined1 *)((long)context + 0x3a) = 0;
      *(undefined1 *)((long)context + 0x42) = 1;
      *(int *)((long)context + 0x3e) = (int)DAT_1001b32c8;
      *(undefined8 *)((long)context + 0x43) = 0x5554030000000000;
      *(undefined4 *)((long)context + 0x34) = 0xffffffff;
      *(undefined2 *)((long)context + 0x3c) = 0xffff;
      uVar2 = _iAP2LinkRunLoopGetBuffSize(0x7f,0xffff);
      lVar4 = _malloc_type_malloc(uVar2,0x55b95949);
      context[5] = lVar4;
      lVar4 = _iAP2LinkRunLoopCreateDevice(context + 6,context,1,0,0x7f,0xffff,lVar4);
      context[5] = lVar4;
      uVar5 = _malloc_type_calloc(1,0x1001f,0x1090040daa7631a);
      lVar4 = _iAP2MsgParserInit(0xffff,uVar5,context[5],0x4040);
      context[0xf] = lVar4;
      uVar8 = *(undefined8 *)(*context + 0x10);
      uVar5 = _acc_endpoint2_getTransportTypeString();
      _acc_platform_packetLogging_logEventForEndpoint
                (uVar8,uVar5,"ATTACH","iAP2 accessory attached!");
      _iAP2LinkRunLoopAttached(context[5]);
    }
    uVar6 = _acc_endpoint2_isWireless(param_1);
    iVar3 = _acc_endpoint2_getTransportType(param_1);
    if (((uVar6 & 1) == 0) && (iVar3 != 8)) {
      _iap2_power_registerForSleepNotification(context);
    }
  }
  return context;
}


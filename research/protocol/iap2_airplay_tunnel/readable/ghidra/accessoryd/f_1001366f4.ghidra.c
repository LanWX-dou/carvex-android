/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001366f4
 * original code SHA256: 7422f03b490c54d3f5897dec2e8ff3cb0cdcb2cb03e7ea6ca4b2def60ea0f3df
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iap2_sessionLog_cleanup(long param_1)

{
  void *pvVar1;
  long lVar2;
  
  if (param_1 != 0) {
    if (*(long *)(param_1 + 0x1c8) != 0) {
      lVar2 = *(long *)(*(long *)(param_1 + 0x1c8) + 0x20);
      if (*(dispatch_source_t *)(lVar2 + 0x48) != (dispatch_source_t)0x0) {
        _dispatch_source_cancel(*(dispatch_source_t *)(lVar2 + 0x48));
        _dispatch_release(*(dispatch_object_t *)(lVar2 + 0x48));
        *(undefined8 *)(lVar2 + 0x48) = 0;
      }
      if (*(dispatch_source_t *)(lVar2 + 0x30) != (dispatch_source_t)0x0) {
        _dispatch_source_cancel(*(dispatch_source_t *)(lVar2 + 0x30));
        _dispatch_release(*(dispatch_object_t *)(lVar2 + 0x30));
        *(undefined8 *)(lVar2 + 0x30) = 0;
      }
      if (*(dispatch_source_t *)(lVar2 + 0x38) != (dispatch_source_t)0x0) {
        _dispatch_source_cancel(*(dispatch_source_t *)(lVar2 + 0x38));
        _dispatch_release(*(dispatch_object_t *)(lVar2 + 0x38));
        *(undefined8 *)(lVar2 + 0x38) = 0;
      }
      if (*(long *)(lVar2 + 0x40) != 0) {
        _dispatch_sync(*(long *)(lVar2 + 0x40),&___block_literal_global);
        _dispatch_release(*(dispatch_object_t *)(lVar2 + 0x40));
        *(undefined8 *)(lVar2 + 0x40) = 0;
      }
    }
    _acc_platform_loggingProtocol_removeNotificationObserver(*(undefined8 *)(param_1 + 8));
    pvVar1 = *(void **)(param_1 + 0x1c8);
    if (pvVar1 != (void *)0x0) {
      if (*(void **)((long)pvVar1 + 0x20) != (void *)0x0) {
        _free(*(void **)((long)pvVar1 + 0x20));
        pvVar1 = *(void **)(param_1 + 0x1c8);
        *(undefined8 *)((long)pvVar1 + 0x20) = 0;
      }
      if (*(void **)((long)pvVar1 + 0x10) != (void *)0x0) {
        _free(*(void **)((long)pvVar1 + 0x10));
        pvVar1 = *(void **)(param_1 + 0x1c8);
        *(undefined8 *)((long)pvVar1 + 0x10) = 0;
      }
      if (*(void **)((long)pvVar1 + 0x50) != (void *)0x0) {
        _free(*(void **)((long)pvVar1 + 0x50));
        pvVar1 = *(void **)(param_1 + 0x1c8);
        *(undefined8 *)((long)pvVar1 + 0x50) = 0;
      }
      if (*(void **)((long)pvVar1 + 0x58) != (void *)0x0) {
        _free(*(void **)((long)pvVar1 + 0x58));
        pvVar1 = *(void **)(param_1 + 0x1c8);
        *(undefined8 *)((long)pvVar1 + 0x58) = 0;
      }
      if (*(void **)((long)pvVar1 + 0x60) != (void *)0x0) {
        _free(*(void **)((long)pvVar1 + 0x60));
        pvVar1 = *(void **)(param_1 + 0x1c8);
        *(undefined8 *)((long)pvVar1 + 0x60) = 0;
      }
      _free(pvVar1);
      *(undefined8 *)(param_1 + 0x1c8) = 0;
    }
    _acc_platform_loggingProtocol_postLoggingCleanup();
  }
  return param_1 != 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000caf0c
 * original code SHA256: a42e47c86bc1d81eb0625105595e8992e114f2b295015547280fc499b4489940
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkRunLoopDelete(long param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  undefined4 local_42;
  
  if ((__iAP2LogEnableMask >> 1 & 1) != 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar2 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkRunLoopRunOnce_cold_1();
        puVar2 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar2 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar1 = _os_log_type_enabled(puVar2,1);
    if (iVar1 != 0) {
      local_50 = (undefined4)DAT_1001b3098;
      local_4c = "iAP2LinkRunLoopDelete";
      local_44 = 0x400;
      local_42 = 0x125;
      __os_log_impl(0x100000000,puVar2,1,"entering %s:%d",&local_50,0x12);
    }
  }
  if (param_1 == 0) {
    if ((__iAP2LogEnableMask & 1) != 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        puVar2 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkRunLoopDelete_cold_2();
          puVar2 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar2 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar1 = _os_log_type_enabled(puVar2,0);
      if (iVar1 != 0) {
        local_50 = (undefined4)DAT_1001b3098;
        local_4c = "iAP2LinkRunLoopDelete";
        local_44 = 0x400;
        local_42 = 0x12f;
        __os_log_impl(0x100000000,puVar2,0,"ERROR: %s:%d NULL linkRunLoop!",&local_50,0x12);
      }
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x2c) = 1;
    _iAP2LinkRunLoopCleanupImplementation(param_1);
    _iAP2LinkDelete(*(undefined8 *)(param_1 + 0x18));
    *(undefined8 *)(param_1 + 0x18) = 0;
  }
  return;
}


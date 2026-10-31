/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000347b0
 * original code SHA256: f5cd92772f9a1dc58bc443d6df4f6ce5e93bbff058c135fa4f3cde599ecb6cad
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkDelete(long param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  undefined4 local_42;
  undefined2 local_3e;
  char *local_3c;
  
  if ((__iAP2LogEnableMask >> 1 & 1) != 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar2 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_1();
        puVar2 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar2 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar1 = _os_log_type_enabled(puVar2,1);
    if (iVar1 != 0) {
      local_4c = "iAP2LinkDelete";
      local_50 = (undefined4)DAT_1001b3080;
      local_3c = "Yes";
      if (param_1 != 0) {
        local_3c = "No";
      }
      local_44 = 0x400;
      local_42 = 0xd2d;
      local_3e = 0x820;
      __os_log_impl(0x100000000,puVar2,1,"%s:%d link null?: %s",&local_50,0x1c);
    }
  }
  if (param_1 == 0) {
    if ((__iAP2LogEnableMask & 1) != 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        puVar2 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_2();
          puVar2 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar2 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar1 = _os_log_type_enabled(puVar2,0);
      if (iVar1 != 0) {
        local_50 = (undefined4)DAT_1001b3098;
        local_4c = "iAP2LinkDelete";
        local_44 = 0x400;
        local_42 = 0xd5b;
        __os_log_impl(0x100000000,puVar2,0,"ERROR: %s:%d NULL link!",&local_50,0x12);
      }
    }
  }
  else {
    if (*(long *)(param_1 + 8) != 0) {
      _iAP2FSMDelete();
      *(undefined8 *)(param_1 + 8) = 0;
    }
    if (*(long *)(param_1 + 0x118) != 0) {
      _iAP2PacketRelease();
      *(undefined8 *)(param_1 + 0x118) = 0;
    }
    _iAP2ListArrayCleanup(*(undefined8 *)(param_1 + 0x120),__DeletePckCB);
    _iAP2LinkResetSend(param_1);
    if (*(long *)(param_1 + 200) != 0) {
      _iAP2TimeDelete();
      *(undefined8 *)(param_1 + 200) = 0;
    }
    _iAP2BuffPoolCleanup(*(undefined8 *)(param_1 + 0xf0));
    *(undefined8 *)(param_1 + 0xf0) = 0;
    _iAP2BuffPoolCleanup(*(undefined8 *)(param_1 + 0xf8));
    *(undefined8 *)(param_1 + 0xf8) = 0;
    _iAP2BuffPoolCleanup(*(undefined8 *)(param_1 + 0x100));
    *(undefined8 *)(param_1 + 0x100) = 0;
    if (*(long *)(param_1 + 0x108) != 0) {
      _iAP2TimeSyncCleanup();
      *(undefined8 *)(param_1 + 0x108) = 0;
    }
  }
  return;
}


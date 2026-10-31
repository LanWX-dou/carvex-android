/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10012e4c4
 * original code SHA256: d3fadf42fb23da9dc87128aca8b5760f9a4151c1af06e2ff3aa3982683cffd24
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_messageHandlers_setHandler(undefined4 param_1,undefined8 param_2)

{
  int iVar1;
  undefined *puVar2;
  undefined4 local_70;
  undefined4 local_6c;
  undefined2 local_60 [8];
  
  if (__MergedGlobals == 0) {
    __MergedGlobals =
         _CFDictionaryCreateMutable(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,0,0,0);
    if (_gLogObjects == 0 || _gNumLogObjects < 0x1a) {
      puVar2 = PTR___os_log_default_10022bbb0;
      if (DAT_10023e5d0 != -1) {
        _OUTLINED_FUNCTION_0();
        puVar2 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar2 = *(undefined **)(_gLogObjects + 200);
    }
    iVar1 = _os_log_type_enabled(puVar2,2);
    if (iVar1 != 0) {
      local_60[0] = 0;
      __os_log_debug_impl(0x100000000,puVar2,2,"Initialized message handler dictionary!",local_60,2)
      ;
    }
    if (__MergedGlobals == 0) {
      return 0;
    }
  }
  _CFDictionarySetValue(__MergedGlobals,param_1,param_2);
  if (_gLogObjects == 0 || _gNumLogObjects < 0x1a) {
    puVar2 = PTR___os_log_default_10022bbb0;
    if (DAT_10023e5d0 != -1) {
      _OUTLINED_FUNCTION_0();
      puVar2 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar2 = *(undefined **)(_gLogObjects + 200);
  }
  iVar1 = _os_log_type_enabled(puVar2,2);
  if (iVar1 != 0) {
    local_70 = (undefined4)DAT_1001b30b0;
    local_6c = param_1;
    __os_log_debug_impl(0x100000000,puVar2,2,"Added message handler for ID: 0x%04X",&local_70,8);
  }
  return 1;
}


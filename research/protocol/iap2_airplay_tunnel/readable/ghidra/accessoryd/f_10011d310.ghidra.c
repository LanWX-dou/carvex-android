/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011d310
 * original code SHA256: 43770827bd7af367fb6babc1cada0787dcae3466cafa475060787e08d0e88fb7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_sessionControl_start(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined *puVar4;
  undefined4 local_50;
  int local_4c;
  
  if (param_1 != 0) {
    uVar2 = _iap2_sessionControl_getVersion();
    if (_gLogObjects == 0 || _gNumLogObjects < 0x1a) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _OUTLINED_FUNCTION_1();
        _dispatch_once();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 200);
    }
    iVar1 = _os_log_type_enabled(puVar4,1);
    if (iVar1 != 0) {
      local_50 = (undefined4)DAT_1001b30b0;
      local_4c = (int)uVar2;
      uVar3 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar3,puVar4,1,"Starting control session (version = %d)...",&local_50,8);
    }
    if ((int)uVar2 == 2) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x1a) {
        if (_logObjectForModule_onceToken != -1) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      else {
        uVar2 = *(undefined8 *)(_gLogObjects + 200);
      }
      iVar1 = _os_log_type_enabled(uVar2,0);
      if (iVar1 != 0) {
        _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_11();
      }
      uVar3 = 1;
    }
    else {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x1a) {
        if (_logObjectForModule_onceToken != -1) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      else {
        uVar2 = *(undefined8 *)(_gLogObjects + 200);
      }
      uVar2 = _os_log_type_enabled(uVar2,0);
      uVar3 = 0;
      if ((int)uVar2 != 0) {
        _OUTLINED_FUNCTION_6(uVar2,0);
        _OUTLINED_FUNCTION_11();
        uVar3 = 0;
      }
    }
    _iap2_features_startFeatureFromDevice(param_1,uVar3);
  }
  return 0;
}


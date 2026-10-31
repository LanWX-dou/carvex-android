/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011e1f0
 * original code SHA256: eb9eac7ab29bc131e3816b8f9fd48f76644f3d2a698c3cf5ac41cb408a764d79
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_sessionControl_authorizationHook_identification
               (long *param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined8 extraout_x8;
  undefined8 extraout_x9;
  code *extraout_x9_00;
  undefined *puVar6;
  undefined4 local_60;
  undefined4 local_5c;
  undefined2 local_58;
  undefined4 local_56;
  
  if (param_1 != (long *)0x0) {
    if (((long *)*param_1 != (long *)0x0) && (*(long *)*param_1 != 0)) {
      iVar1 = _iap2_accAuthentication_getState(param_1);
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1a)) {
        puVar6 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
          puVar6 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar6 = *(undefined **)(_gLogObjects + 200);
      }
      iVar2 = _os_log_type_enabled(puVar6,1);
      if (iVar2 != 0) {
        _OUTLINED_FUNCTION_68();
        uVar4 = extraout_x9;
        if (iVar1 != 0) {
          uVar4 = extraout_x8;
        }
        uVar4 = _OUTLINED_FUNCTION_2(uVar4,DAT_1001b3090);
        __os_log_impl(uVar4,puVar6,1,
                      "authorizationHook from Identification triggered... (startedAuthentication: %s)"
                      ,&local_60,0xc);
      }
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1a)) {
        puVar6 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
          puVar6 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar6 = *(undefined **)(_gLogObjects + 200);
      }
      iVar2 = _os_log_type_enabled(puVar6,2);
      if (iVar2 != 0) {
        uVar3 = _iap2_accAuthentication_getState(param_1);
        local_56 = _iap2_identification_getState(param_1);
        local_60 = (undefined4)DAT_1001b3108;
        local_58 = 0x400;
        local_5c = uVar3;
        uVar4 = _OUTLINED_FUNCTION_6();
        __os_log_debug_impl(uVar4,puVar6,2,
                            "authState: %{coreacc:iAP2Feature_AccAuthentication_State_t}d, idState: %{coreacc:iAP2Feature_Identification_State_t}d"
                            ,&local_60,0xe);
      }
      if (iVar1 == 0) {
        _OUTLINED_FUNCTION_44();
        (*extraout_x9_00)();
      }
      else {
        lVar5 = _iap2_accAuthentication_copyCertificateSerialString(param_1);
        __requestAuthorization(param_1,lVar5,param_2,param_3);
        if (lVar5 != 0) {
          _CFRelease(lVar5);
        }
      }
    }
  }
  return;
}


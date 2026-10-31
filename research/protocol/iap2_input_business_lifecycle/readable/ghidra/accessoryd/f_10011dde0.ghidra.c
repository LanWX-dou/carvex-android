/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011dde0
 * original code SHA256: b7e4219ee002e26030c30ec3655378905317ecf45f0c47e8f2ce58eb3ed0d162
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_sessionControl_authorizationHook_authentication(long *param_1,undefined8 param_2)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  long extraout_x8;
  undefined8 extraout_x8_00;
  long extraout_x8_01;
  undefined8 extraout_x9;
  code *extraout_x9_00;
  undefined *puVar7;
  undefined4 local_60;
  undefined4 local_5c;
  undefined2 local_58;
  undefined4 local_56;
  
  if (param_1 != (long *)0x0) {
    if (((long *)*param_1 != (long *)0x0) && (*(long *)*param_1 != 0)) {
      iVar1 = _iap2_identification_getState(param_1);
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_7(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_6();
        puVar7 = PTR___os_log_default_10022bbb0;
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
          puVar7 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar7 = *(undefined **)(extraout_x8 + 200);
      }
      iVar2 = _os_log_type_enabled(puVar7,1);
      if (iVar2 != 0) {
        _OUTLINED_FUNCTION_68();
        in_NG = iVar1 < 0;
        in_ZR = iVar1 == 0;
        in_OV = '\0';
        uVar4 = extraout_x9;
        if (!(bool)in_ZR) {
          uVar4 = extraout_x8_00;
        }
        uVar4 = _OUTLINED_FUNCTION_2(uVar4,DAT_1001b3090);
        __os_log_impl(uVar4,puVar7,1,
                      "authorizationHook from Authentication triggered... (startedIdentification: %s)"
                      ,&local_60,0xc);
      }
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_7(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_6();
        puVar7 = PTR___os_log_default_10022bbb0;
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
          puVar7 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar7 = *(undefined **)(extraout_x8_01 + 200);
      }
      iVar2 = _os_log_type_enabled(puVar7,2);
      if (iVar2 != 0) {
        uVar3 = _iap2_accAuthentication_getState(param_1);
        local_56 = _iap2_identification_getState(param_1);
        local_60 = (undefined4)DAT_1001b3108;
        local_58 = 0x400;
        local_5c = uVar3;
        uVar4 = _OUTLINED_FUNCTION_6();
        __os_log_debug_impl(uVar4,puVar7,2,
                            "authState: %{coreacc:iAP2Feature_AccAuthentication_State_t}d, idState: %{coreacc:iAP2Feature_Identification_State_t}d"
                            ,&local_60,0xe);
      }
      if (iVar1 == 0) {
        _OUTLINED_FUNCTION_44();
        (*extraout_x9_00)();
      }
      else {
        lVar5 = _iap2_accAuthentication_copyCertificateSerialString(param_1);
        uVar4 = _acc_endpoint2_getAccessoryInfo(*param_1);
        lVar6 = _acc_accInfo_retainedProperty(uVar4,0,0);
        if (lVar6 == 0) {
          lVar6 = _acc_strings_copyPlaceholder_Unknown();
        }
        __requestAuthorization(param_1,lVar5,lVar6,param_2);
        if (lVar5 != 0) {
          _CFRelease(lVar5);
        }
        if (lVar6 != 0) {
          _CFRelease(lVar6);
        }
      }
    }
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10019bfac
 * original code SHA256: e23236fca393cc47750126f2ef5539de359e2b3b051e07738f575ea9d00968e7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */

undefined8
_iAP2LinkDataReadyCB
          (long param_1,undefined8 param_2,undefined2 param_3,undefined8 param_4,undefined8 param_5)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined *puVar6;
  undefined8 uVar7;
  undefined2 local_70 [8];
  undefined2 local_60 [8];
  
  uVar7 = *(undefined8 *)(*(long *)(param_1 + 0xb0) + 0x10);
  lVar2 = _iAP2LinkGetSessionInfo(param_1,param_5);
  if (lVar2 == 0) {
    uVar7 = 0;
  }
  else {
    lVar5 = lVar2;
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        lVar5 = _OUTLINED_FUNCTION_0();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar1 = _os_log_type_enabled(puVar6,lVar5,1);
    if (iVar1 != 0) {
      local_60[0] = 0;
      uVar3 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar3,lVar5,1,"Processing session data...",local_60,2);
    }
    uVar7 = _iap2_sessionRouter_processSessionData(uVar7,lVar2,param_2,param_3);
    uVar3 = uVar7;
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        uVar3 = _OUTLINED_FUNCTION_0();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar1 = _os_log_type_enabled(puVar6,uVar3,1);
    if (iVar1 != 0) {
      local_70[0] = 0;
      uVar4 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar4,uVar3,1,"Finished processing session data!",local_70,2);
    }
  }
  return uVar7;
}


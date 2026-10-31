/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100036c08
 * original code SHA256: 1c97d4674d9ab68d8e6ed673c9a44e970a12cd444e0247a6c1b345bc42bf2a1b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

undefined8 _platform_assistiveTouch_accessoryDetached(ID param_1)

{
  int iVar1;
  ID IVar2;
  undefined *puVar3;
  undefined4 local_30;
  ID local_2c;
  
  IVar2 = param_1;
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x26)) {
    puVar3 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      IVar2 = _platform_assistiveTouch_accessoryDetached_cold_1();
      puVar3 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar3 = *(undefined **)(_gLogObjects + 0x128);
  }
  iVar1 = _os_log_type_enabled(puVar3,IVar2,1);
  if (iVar1 != 0) {
    local_30 = (undefined4)DAT_1001b3088;
    local_2c = param_1;
    __os_log_impl(0x100000000,IVar2,1,"assistiveTouch accessoryDetached: %@",&local_30,0xc);
  }
  IVar2 = ACCAssistiveTouchServer::sharedServer((ID)PTR_ACCAssistiveTouchServer_10022aea0);
  ACCAssistiveTouchServer::accessoryAssistiveTouchDetached_(IVar2,param_1);
  return 0;
}


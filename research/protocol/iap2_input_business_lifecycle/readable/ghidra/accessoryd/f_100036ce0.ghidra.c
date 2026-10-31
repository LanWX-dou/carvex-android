/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100036ce0
 * original code SHA256: 2e0c6e60d43b719193a8f855d8cfb5b1700bb101712f27a150048269c1115f03
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

undefined8 _platform_assistiveTouch_setState(ID param_1,bool param_2)

{
  int iVar1;
  ID IVar2;
  undefined *puVar3;
  undefined4 local_50;
  ID local_4c;
  undefined2 local_44;
  bool local_42;
  
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
    local_50 = (undefined4)DAT_1001b30f0;
    local_44 = 0x400;
    local_4c = param_1;
    local_42 = param_2;
    __os_log_impl(0x100000000,IVar2,1,"assistiveTouch setState: %@ enabled=%d",&local_50,0x12);
  }
  IVar2 = ACCAssistiveTouchServer::sharedServer((ID)PTR_ACCAssistiveTouchServer_10022aea0);
  ACCAssistiveTouchServer::setEnabled_flag_(IVar2,param_1,param_2);
  return 0;
}


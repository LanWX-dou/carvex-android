/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000dc974
 * original code SHA256: fa989cae0cf97263197b8a7e89f36f331c39c52fc61b058da507c6d3d3891174
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

undefined8 _platform_navigation_objectDetectionUpdateInfo(ID param_1,ID param_2,ID param_3)

{
  int iVar1;
  ID IVar2;
  undefined *puVar3;
  undefined4 local_50;
  ID local_4c;
  undefined2 local_44;
  ID local_42;
  undefined2 local_3a;
  ID local_38;
  
  IVar2 = param_1;
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x32)) {
    puVar3 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      IVar2 = _platform_navigation_accessoryDetached_cold_1();
      puVar3 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar3 = *(undefined **)(_gLogObjects + 0x188);
  }
  iVar1 = _os_log_type_enabled(puVar3,IVar2,1);
  if (iVar1 != 0) {
    local_50 = (undefined4)DAT_1001b30f8;
    local_44 = 0x840;
    local_3a = 0x840;
    local_4c = param_1;
    local_42 = param_2;
    local_38 = param_3;
    __os_log_impl(0x100000000,IVar2,1,
                  "navigation objectDetectionUpdateInfo: %@, componentIdList=%@, updateInfo=%@",
                  &local_50,0x20);
  }
  IVar2 = ACCNavigationServer::sharedServer((ID)PTR_ACCNavigationServer_10022aef8);
  ACCNavigationServer::accessoryNavigationObjectDetectionUpdateInfo_componentIdList_updateInfo_
            (IVar2,param_1,param_2,param_3);
  return 0;
}


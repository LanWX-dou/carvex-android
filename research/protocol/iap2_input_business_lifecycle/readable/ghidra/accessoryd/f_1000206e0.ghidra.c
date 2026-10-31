/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000206e0
 * original code SHA256: 3a101d70418d9f1f58065866f3e15ee12e42c087ec82c27aeb3676f072f4015c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */

undefined8 _platform_btConnectionStatus_accessoryDetached(undefined8 param_1)

{
  int iVar1;
  ID IVar2;
  ID self;
  ulong uVar3;
  ID IVar4;
  undefined8 uVar5;
  undefined *puVar6;
  undefined4 local_60;
  undefined8 local_5c;
  undefined2 local_54;
  ID local_52;
  
  uVar5 = param_1;
  if (_gLogObjects == 0 || _gNumLogObjects < 8) {
    puVar6 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      uVar5 = _platform_btConnectionStatus_updateHandler_cold_1();
      puVar6 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar6 = *(undefined **)(_gLogObjects + 0x38);
  }
  iVar1 = _os_log_type_enabled(puVar6,uVar5,1);
  if (iVar1 != 0) {
    local_60 = (undefined4)DAT_1001b3088;
    local_5c = param_1;
    __os_log_impl(0x100000000,uVar5,1,
                  "[#BT Connection Status] btConnectionStatus accessoryDetached: %@",&local_60,0xc);
  }
  IVar2 = _ACCBTConnectionStatusAccessory::accessoryList
                    ((ID)PTR__ACCBTConnectionStatusAccessory_10022af70);
  IVar2 = objc_stub::objectForKey_(IVar2,param_1);
  uVar5 = 0;
  if (IVar2 == 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 8)) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        uVar5 = _platform_btConnectionStatus_accessoryDetached_cold_2();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0x38);
    }
    iVar1 = _os_log_type_enabled(puVar6,uVar5,1);
    if (iVar1 != 0) {
      local_52 = _ACCBTConnectionStatusAccessory::accessoryList
                           ((ID)PTR__ACCBTConnectionStatusAccessory_10022af70);
      local_60 = (undefined4)DAT_1001b30f0;
      local_54 = 0x840;
      local_5c = param_1;
      __os_log_impl(0x100000000,uVar5,1,
                    "[#BT Connection Status] btConnectionStatus accessoryDetached: Unable to find accessory for accessoryUID %@ ! accessoryList=%@"
                    ,&local_60,0x16);
    }
  }
  else {
    self = __getBTStatusPluginInstance();
    uVar3 = _objc_opt_respondsToSelector(self,PTR_s_accessoryDetached__100237608);
    if ((uVar3 & 1) != 0) {
      IVar4 = _ACCBTConnectionStatusAccessory::pluginAccessory(IVar2);
      objc_stub::accessoryDetached_(self,IVar4);
      _ACCBTConnectionStatusAccessory::setPluginAccessory_(IVar2,0);
    }
    IVar2 = _ACCBTConnectionStatusAccessory::accessoryList
                      ((ID)PTR__ACCBTConnectionStatusAccessory_10022af70);
    objc_stub::removeObjectForKey_(IVar2,param_1);
  }
  return 0;
}


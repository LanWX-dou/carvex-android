/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100028278
 * original code SHA256: 26de37886e6c31f868bc03ce8fa9b9e679c2e3eb34523fe22e558fe3bb151e8a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_power_unregisterForSleepWakeUpdate(ID param_1)

{
  code *pcVar1;
  ID IVar2;
  ID IVar3;
  ulong unaff_x30;
  
  IVar2 = ACCPlatformPowerManager::sharedManager((ID)PTR_ACCPlatformPowerManager_10022af18);
  IVar2 = ACCPlatformPowerManager::powerAccessories(IVar2);
  IVar2 = objc_stub::objectForKey_(IVar2,param_1);
  if (IVar2 != 0) {
    IVar3 = objc_stub::requestSleepUpdate(IVar2);
    if ((int)IVar3 != 0) {
      objc_stub::stopPowerUpdates(IVar2);
      objc_stub::setRequestSleepUpdate_(IVar2,0);
      objc_stub::startPowerUpdates(IVar2);
    }
    IVar2 = objc_stub::updateTypesBitmask(IVar2);
    if (IVar2 == 0) {
      IVar2 = ACCPlatformPowerManager::sharedManager((ID)PTR_ACCPlatformPowerManager_10022af18);
      ACCPlatformPowerManager::removeAccessoryForEndpointUID_(IVar2,param_1);
    }
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10002834c);
    (*pcVar1)();
  }
  return 0;
}


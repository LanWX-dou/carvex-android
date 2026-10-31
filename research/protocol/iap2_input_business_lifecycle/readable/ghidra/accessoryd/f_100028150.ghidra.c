/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100028150
 * original code SHA256: 42949afb4e80474183c8ae322b7d286dfd48373a011393145e37cfd5c8152d67
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x19 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_power_registerForSleepWakeUpdate(ID param_1)

{
  code *pcVar1;
  ID IVar2;
  ID IVar3;
  ulong unaff_x30;
  
  IVar2 = ACCPlatformPowerManager::sharedManager((ID)PTR_ACCPlatformPowerManager_10022af18);
  IVar2 = ACCPlatformPowerManager::powerAccessories(IVar2);
  IVar2 = objc_stub::objectForKey_(IVar2,param_1);
  if (IVar2 == 0) {
    IVar2 = _objc_alloc(&objc::class_t::ACCPlatformPowerInfo);
    IVar2 = ACCPlatformPowerInfo::initWithEndpointUID_andModelNumber_andBitmask_andOldBitmask_
                      (IVar2,param_1,param_1,0,0);
    ACCPlatformPowerInfo::setRequestSleepUpdate_(IVar2,1);
    IVar3 = ACCPlatformPowerManager::sharedManager((ID)PTR_ACCPlatformPowerManager_10022af18);
    IVar3 = ACCPlatformPowerManager::powerAccessories(IVar3);
    objc_stub::setObject_forKey_(IVar3,IVar2,param_1);
  }
  else {
    IVar3 = objc_stub::requestSleepUpdate(IVar2);
    if ((IVar3 & 1) != 0) goto LAB_100028244;
    objc_stub::stopPowerUpdates(IVar2);
    objc_stub::setRequestSleepUpdate_(IVar2,1);
  }
  ACCPlatformPowerInfo::startPowerUpdates(IVar2);
LAB_100028244:
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100028274);
    (*pcVar1)();
  }
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000dd9e8
 * original code SHA256: efad61d4f2bc676412b4ecef079db2546fce05fd56926c20f715bdccaa1c04e3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_navigation_incrementUserCount(void)

{
  code *pcVar1;
  ID IVar2;
  unsigned_long_long uVar3;
  ulong unaff_x30;
  
  IVar2 = ACCNavigationServer::sharedServer((ID)PTR_ACCNavigationServer_10022aef8);
  ACCXPCFeatureServer::incrementUserCount(IVar2);
  IVar2 = ACCNavigationServer::sharedServer((ID)PTR_ACCNavigationServer_10022aef8);
  uVar3 = ACCXPCFeatureServer::featureUserCount(IVar2);
  if (uVar3 != 1) {
    return 0;
  }
  IVar2 = ACCFeaturePluginManager::sharedManager((ID)PTR_ACCFeaturePluginManager_10022aed0);
  ACCPluginManager::startPlugInsWithClasses_(IVar2,0x10022a0d8);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000dda7c);
    (*pcVar1)();
  }
  return 0;
}


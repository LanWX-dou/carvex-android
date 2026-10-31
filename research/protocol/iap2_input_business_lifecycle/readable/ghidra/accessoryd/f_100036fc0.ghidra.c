/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100036fc0
 * original code SHA256: 51224f1420caa81e53aaba970998967734fc0de7c00725339317be9e7769269a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_assistiveTouch_incrementUserCount(void)

{
  code *pcVar1;
  int iVar2;
  ID IVar3;
  ulong unaff_x30;
  
  IVar3 = ACCAssistiveTouchServer::sharedServer((ID)PTR_ACCAssistiveTouchServer_10022aea0);
  ACCFeatureServer::incrementUserCount(IVar3);
  IVar3 = ACCAssistiveTouchServer::sharedServer((ID)PTR_ACCAssistiveTouchServer_10022aea0);
  iVar2 = ACCFeatureServer::featureUserCount(IVar3);
  if (iVar2 != 1) {
    return 0;
  }
  IVar3 = ACCFeaturePluginManager::sharedManager((ID)PTR_ACCFeaturePluginManager_10022aed0);
  ACCPluginManager::startPlugInsWithClasses_(IVar3,0x10022a078);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100037054);
    (*pcVar1)();
  }
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100037068
 * original code SHA256: b61701a50289e181c7712d7f476d01eada45a1c525d88811233438405061a25c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_assistiveTouch_decrementUserCount(void)

{
  code *pcVar1;
  ID IVar2;
  ulong unaff_x30;
  
  IVar2 = ACCAssistiveTouchServer::sharedServer((ID)PTR_ACCAssistiveTouchServer_10022aea0);
  ACCFeatureServer::decrementUserCount(IVar2);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000370ac);
    (*pcVar1)();
  }
  return 0;
}


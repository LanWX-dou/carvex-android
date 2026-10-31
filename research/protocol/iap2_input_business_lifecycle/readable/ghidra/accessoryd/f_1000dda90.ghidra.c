/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000dda90
 * original code SHA256: d2830d87344aab1c49992d38d4948517e77d3bea8644d095f029cdf159a89928
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_navigation_decrementUserCount(void)

{
  code *pcVar1;
  ID IVar2;
  ulong unaff_x30;
  
  IVar2 = ACCNavigationServer::sharedServer((ID)PTR_ACCNavigationServer_10022aef8);
  ACCXPCFeatureServer::decrementUserCount(IVar2);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000ddad4);
    (*pcVar1)();
  }
  return 0;
}


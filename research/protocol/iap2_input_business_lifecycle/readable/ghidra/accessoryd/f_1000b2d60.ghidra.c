/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000b2d60
 * original code SHA256: ec4b15d36ec19b8a6218c2b1e05d51b913abf38c8afbcc4cb8ac04c663134347
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */

undefined8 _platform_hid_in_report(ID param_1,unsigned_short param_2,ID param_3)

{
  ID IVar1;
  
  IVar1 = ACCHIDServer::sharedServer((ID)PTR_ACCHIDServer_10022aed8);
  ACCHIDServer::inReport_componentID_report_(IVar1,param_1,param_2,param_3);
  return 1;
}


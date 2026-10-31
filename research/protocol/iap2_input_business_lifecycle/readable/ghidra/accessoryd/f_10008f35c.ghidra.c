/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008f35c
 * original code SHA256: 0dbb64aeb52baef702f25290e2f89aaf799aed99884d98b3fcf7d521230e0d03
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */

undefined8 _platform_nowPlaying_setPlaybackElapsedTime(ulong param_1)

{
  ID self;
  ID IVar1;
  
  self = __sharedClient();
  IVar1 = NSNumber::numberWithLong_((ID)PTR__OBJC_CLASS___NSNumber_10022bb28,param_1 & 0xffffffff);
  objc_stub::setPlaybackElapsedTime_(self,IVar1);
  return 1;
}


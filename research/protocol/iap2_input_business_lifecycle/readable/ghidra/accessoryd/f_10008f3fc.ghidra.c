/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008f3fc
 * original code SHA256: 19977a4968c9775951fb4d686d7c5e6ed5958b7e65928cd634b0265e0e02a8ea
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */

undefined8 _platform_nowPlaying_setPlaybackQueueIndex(ulong param_1)

{
  ID self;
  ID IVar1;
  
  self = __sharedClient();
  IVar1 = NSNumber::numberWithLong_((ID)PTR__OBJC_CLASS___NSNumber_10022bb28,param_1 & 0xffffffff);
  objc_stub::setPlaybackQueueIndex_(self,IVar1);
  return 1;
}


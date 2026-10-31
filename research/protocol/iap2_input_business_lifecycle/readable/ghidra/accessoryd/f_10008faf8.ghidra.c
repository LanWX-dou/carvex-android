/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008faf8
 * original code SHA256: bcff6d1aa77c896d1deaa1bbc92fff80a264e91c5ae46dc5e14e11ac64c6e3bf
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8
_platform_nowPlaying_requestPlaybackQueueListInfo
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5)

{
  code *pcVar1;
  ID self;
  ulong unaff_x30;
  
  self = __sharedClient();
  objc_stub::requestPlaybackQueueListInfo_requestID_startIndex_upToCount_infoMask_
            (self,param_1,param_2,param_3,param_4,param_5);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10008fb74);
    (*pcVar1)();
  }
  return 0;
}


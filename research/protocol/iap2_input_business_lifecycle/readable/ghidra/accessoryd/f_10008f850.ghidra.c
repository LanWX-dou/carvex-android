/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008f850
 * original code SHA256: 47bb8e7239ffb2f19b220700f4c7b626bb3234fa81fd16f5ea670970fa397ea2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_nowPlaying_triggerPlaybackAttributesUpdate(void)

{
  code *pcVar1;
  ID self;
  ulong unaff_x30;
  
  __gShouldSendMediaLibraryUID = 1;
  self = __sharedClient();
  objc_stub::requestCurrentPlaybackAttributes_(self,&___block_literal_global_61);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10008f8a0);
    (*pcVar1)();
  }
  return 0;
}


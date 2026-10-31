/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008f70c
 * original code SHA256: 2d13aa3934ad49fe5c2074f271b2b34b9f68c2a839e2eba222fa6e0fd46c64ac
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_nowPlaying_triggerMediaItemArtworkUpdate(void)

{
  code *pcVar1;
  ID self;
  ulong unaff_x30;
  
  self = __sharedClient();
  objc_stub::requestCurrentMediaItemArtwork_(self,&___block_literal_global_59);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10008f750);
    (*pcVar1)();
  }
  return 0;
}


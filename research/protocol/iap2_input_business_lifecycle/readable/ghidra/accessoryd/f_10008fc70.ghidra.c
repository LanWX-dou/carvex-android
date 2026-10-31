/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008fc70
 * original code SHA256: fcae26edaa388a2e945f01a61b6a4af5f3fba866ba0e049b946d6150f66cfecc
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */

undefined8 _platform_nowPlaying_incrementUserCount(void)

{
  code *pcVar1;
  ID self;
  ulong unaff_x30;
  
  self = __sharedClient();
  objc_stub::incrementUserCount(self);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10008fcac);
    (*pcVar1)();
  }
  return 0;
}


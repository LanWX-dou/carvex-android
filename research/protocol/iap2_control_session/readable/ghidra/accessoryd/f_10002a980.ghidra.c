/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002a980
 * original code SHA256: 59b98054559e437a1e2cf19be8d8a6feb8cee9e01ab30579641b46a40fba1a34
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void ___iap2_sessionControl_cleanup_block_invoke_2(long param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  
  _platform_iapd_bridge_accessory_disconnected(*(undefined8 *)(param_1 + 0x20));
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10002a9b8);
    (*pcVar1)();
  }
  _CFRelease(*(undefined8 *)(param_1 + 0x20));
  return;
}


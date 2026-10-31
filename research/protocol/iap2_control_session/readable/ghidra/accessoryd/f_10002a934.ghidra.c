/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002a934
 * original code SHA256: 0bd3d85594e2de3e3b1e1544c65f7b89ba85f0c0debae82c806424d02f79a83e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void ___iap2_sessionControl_cleanup_block_invoke(long param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  
  _platform_usb_lockUSBHostInterfaces(*(undefined8 *)(param_1 + 0x20));
  if (*(long *)(param_1 + 0x20) == 0) {
    return;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x10002a970);
    (*pcVar1)();
  }
  _CFRelease();
  return;
}


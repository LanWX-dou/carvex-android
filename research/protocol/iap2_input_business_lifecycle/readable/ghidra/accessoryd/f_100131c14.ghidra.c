/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100131c14
 * original code SHA256: 9c82e3abf3b091e0e2a7e419d227e39b9a6c7f9148665af77a76dc046f35c111
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void __CFDictionaryApplierFunction_releaseHIDComponents(undefined8 param_1,void *param_2)

{
  code *pcVar1;
  ulong unaff_x30;
  
  if (param_2 == (void *)0x0) {
    return;
  }
  if (*(long *)((long)param_2 + 8) != 0) {
    _CFRelease();
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100131c54);
    (*pcVar1)();
  }
  _free(param_2);
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c6db8
 * original code SHA256: ff5cabb3f15a0f683f7f8f32349e412135a05c772688dcef47cd64a8cc8317e5
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003c6db8(long param_1)

{
  code *pcVar1;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1003c6df0);
    (*pcVar1)();
  }
  FUN_1000609fc(*(undefined4 *)(param_1 + 0x24));
  return;
}


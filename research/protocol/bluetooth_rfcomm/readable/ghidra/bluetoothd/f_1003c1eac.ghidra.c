/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c1eac
 * original code SHA256: 9c3c9486e45d5d56baebcc53e9127ca74c165c9ae8086897a1723eda5b3eaf20
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003c1eac(void)

{
  int iVar1;
  code *pcVar2;
  ulong unaff_x30;
  
  if ((piRam0000000100c38320 == (int *)0x0) &&
     (FUN_1000f9438(), piRam0000000100c38320 == (int *)0x0)) {
    return;
  }
  iVar1 = *piRam0000000100c38320;
  *piRam0000000100c38320 = iVar1 + -1;
  if (iVar1 + -1 != 0) {
    return;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
    FUN_1003c2d6c();
    return;
  }
                    /* WARNING: Does not return */
  pcVar2 = (code *)SoftwareBreakpoint(0xc471,0x1003c1f08);
  (*pcVar2)();
}


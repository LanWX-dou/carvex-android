/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c16dc
 * original code SHA256: 798eb849a90f4fcf24469f42ff26b6ffb7c64d551c4d543c4a3a541371939740
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003c16dc(long param_1,int param_2)

{
  code *pcVar1;
  long lVar2;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  lVar2 = *(long *)(param_1 + 0x80);
  if (lVar2 == 0) {
    FUN_1000f9438();
    lVar2 = *(long *)(param_1 + 0x80);
  }
  FUN_1003d94a8(*(undefined4 *)(param_1 + 0x38));
  FUN_1003d84bc(param_1 + 0x90);
  if (*(int *)(param_1 + 0x88) != 0) {
    FUN_1000609fc();
    *(undefined4 *)(param_1 + 0x88) = 0;
  }
  FUN_1003c15f0(param_1);
  FUN_1003c4d8c(param_1);
  if ((param_2 != 0) && (*(long **)(lVar2 + 0x10) == (long *)(lVar2 + 0x10))) {
    FUN_1003c1788(lVar2,0,*(undefined4 *)(param_1 + 0xa4));
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1003c1784);
    (*pcVar1)();
  }
  FUN_1000110b8(param_1);
  return;
}


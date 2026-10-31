/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c2d6c
 * original code SHA256: c477c7bfc0262cc71a156962f056a788784f8017d4e423a9171542a4a01a58bd
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003c2d6c(void)

{
  int iVar1;
  
  if (iRam0000000100cade68 != 1) {
    FUN_1000f9438();
  }
  iVar1 = 3;
  FUN_10036efcc();
  if (iVar1 == 0) {
    if (lRam0000000100c38320 != 0) {
      FUN_1000110b8();
      lRam0000000100c38320 = 0;
    }
    if (lRam0000000100c38318 != 0) {
      FUN_1000110b8();
      lRam0000000100c38318 = 0;
    }
    if (lRam0000000100c38308 != 0) {
      FUN_1000110b8();
      lRam0000000100c38308 = 0;
    }
    iRam0000000100cade68 = 0;
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_1000e3dcc();
}


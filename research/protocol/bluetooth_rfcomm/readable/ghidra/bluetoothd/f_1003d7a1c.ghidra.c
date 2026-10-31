/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003d7a1c
 * original code SHA256: fdc808ee9dd0f3717db089f702ada9e707698474461a96b05f500f130f5fb89a
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


long FUN_1003d7a1c(uint param_1)

{
  long lVar1;
  
  if (0x46 < param_1) {
    FUN_1000f9438();
  }
  lVar1 = *(long *)((ulong)param_1 * 8 + 0x100c38540);
  if (lVar1 == 0) {
    FUN_1000f9438();
    lVar1 = *(long *)((ulong)param_1 * 8 + 0x100c38540);
  }
  return lVar1;
}


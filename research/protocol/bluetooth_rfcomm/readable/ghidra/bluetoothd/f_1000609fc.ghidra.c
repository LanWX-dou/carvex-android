/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000609fc
 * original code SHA256: 0ecb5315c514a4e8f8e4d70736a8d02735ffd6d8693c799b1b27b1323422a8a9
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 FUN_1000609fc(ulong param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1;
  FUN_100060a70();
  if ((int)uVar1 == 0) {
    uVar2 = 0x3e9;
  }
  else {
    if (*(undefined **)(lRam0000000100c39fb0 + (param_1 >> 0x10 & 0xffff) * 0x18 + 8) ==
        &DAT_1003d8088) {
                    /* WARNING: Subroutine does not return */
      FUN_1000e3dcc(param_1);
    }
    FUN_100060b80((int)param_1 >> 0x10);
    uVar2 = 0;
  }
  return uVar2;
}


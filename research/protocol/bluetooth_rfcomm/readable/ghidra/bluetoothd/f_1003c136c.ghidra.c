/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c136c
 * original code SHA256: 49afb425851e1a3d25ff11dd2e6a1b56860436d26e7a181f72a6dbc1626f1455
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 FUN_1003c136c(long param_1,uint param_2,long *param_3)

{
  undefined8 uVar1;
  long *plVar2;
  
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  if (param_3 == (long *)0x0) {
    FUN_1000f9438();
  }
  if (iRam0000000100cade68 == 0) {
    uVar1 = 0x198;
  }
  else {
    plVar2 = (long *)(param_1 + 0x10);
    do {
      plVar2 = (long *)*plVar2;
      if (plVar2 == (long *)0x0 || plVar2 == (long *)(param_1 + 0x10)) {
        return 0x390;
      }
    } while (param_2 != *(byte *)((long)plVar2 + -0x86));
    uVar1 = 0;
    *param_3 = (long)(plVar2 + -0x12);
  }
  return uVar1;
}


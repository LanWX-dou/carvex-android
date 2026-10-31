/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c14dc
 * original code SHA256: b87bf9df4e59ccabb8a317003f8f6e59ad14c0d873553706ebf00641576cdd49
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 FUN_1003c14dc(long param_1,undefined8 param_2,long *param_3)

{
  long *plVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  if (iRam0000000100cade68 == 0) {
    uVar2 = 0x198;
  }
  else {
    plVar1 = (long *)(param_1 + 0x10);
    plVar5 = plVar1;
    do {
      plVar5 = (long *)*plVar5;
      if (plVar5 == (long *)0x0 || plVar5 == plVar1) {
        lVar3 = 0xa8;
        FUN_1001aad2c(0xa8,0x10e0040432f2197);
        if (lVar3 != 0) {
          *(undefined1 *)(lVar3 + 0x14) = 0;
          lVar4 = param_1;
          FUN_1003c12dc(param_1,param_2);
          *(short *)(lVar3 + 8) = (short)lVar4;
          *(long *)(lVar3 + 0x80) = param_1;
          *(char *)(lVar3 + 10) = (char)param_2;
          *(undefined8 *)(lVar3 + 0x58) = 0;
          *(undefined2 *)(lVar3 + 0x10) = 0x7f;
          *(undefined2 *)(lVar3 + 0xc) = 0x8c;
          *(undefined8 *)(lVar3 + 0x68) = 0;
          *(undefined2 *)(lVar3 + 0xa2) = 0;
          *(undefined8 *)(lVar3 + 0x16) = 0x3033f7f;
          *(undefined4 *)(lVar3 + 0x1e) = 0x1011311;
          *(undefined4 *)(lVar3 + 0x38) = 0;
          FUN_1003d84a8(lVar3 + 0x90,plVar1);
          *param_3 = lVar3;
          return 0;
        }
        return 0x6a;
      }
    } while ((uint)*(byte *)((long)plVar5 + -0x86) != (uint)param_2);
    uVar2 = 0x38f;
  }
  return uVar2;
}


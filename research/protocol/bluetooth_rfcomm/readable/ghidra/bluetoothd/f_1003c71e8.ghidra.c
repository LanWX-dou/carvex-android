/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c71e8
 * original code SHA256: 99d8b2cd7d552a666078593c25fb19f15889d5038acdd8b952939c2e958f308c
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003c71e8(undefined8 param_1,int param_2,char param_3,byte param_4,int param_5)

{
  undefined8 uVar1;
  undefined1 uStack_25;
  undefined1 uStack_24;
  byte bStack_23;
  byte bStack_22;
  byte bStack_21;
  
  bStack_21 = 0;
  uStack_25 = 0xe3;
  if (param_2 == 0) {
    uStack_25 = 0xe1;
  }
  if (param_5 == 0) {
    bStack_22 = param_4 | 1;
    uVar1 = 4;
    uStack_24 = 5;
  }
  else {
    bStack_21 = (byte)(param_5 << 4) | 3;
    uVar1 = 5;
    uStack_24 = 7;
    bStack_22 = param_4;
  }
  bStack_23 = param_3 << 2 | 3;
  if (param_2 != 0) {
    FUN_1003c6d00(param_1);
  }
  FUN_1003c5884(param_1,0,&uStack_25,uVar1,0);
  return;
}


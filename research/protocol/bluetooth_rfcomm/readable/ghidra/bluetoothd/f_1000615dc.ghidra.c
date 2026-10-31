/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000615dc
 * original code SHA256: 9a00b12b80d89d26129718d52bc9a87567bf8b0590833548cdadf05945c6047d
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1000615dc(long param_1,int param_2)

{
  short sVar1;
  short sVar2;
  undefined8 uStack_38;
  
  uStack_38 = 0;
  FUN_100035440(&uStack_38);
  sVar2 = (short)((uStack_38._4_2_ + 99) / 100) + (short)uStack_38 * 10;
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  sVar1 = (short)param_2 + sVar2;
  *(short *)(param_1 + 2) = sVar1;
  if ((sRam0000000100c39faa == 0) || (param_2 <= (short)(sRam0000000100c39fae - sVar2))) {
    sRam0000000100c39fae = sVar1;
    if (pcRam0000000100c39fb8 != (code *)0x0) {
      (*pcRam0000000100c39fb8)(param_2 * 100);
    }
  }
  return;
}


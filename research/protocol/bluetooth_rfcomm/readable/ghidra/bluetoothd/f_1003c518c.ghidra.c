/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c518c
 * original code SHA256: 2049278bc4d8c6c96c63cbbb98c49d4d9ad0210a51bf3acee722dd79ad63f85f
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined1 * FUN_1003c518c(long param_1,undefined8 param_2)

{
  int iVar1;
  undefined1 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uStack_38;
  long *plStack_30;
  long lStack_28;
  
  uStack_38 = 0;
  lStack_28 = param_1;
  FUN_1000609fc(*(undefined4 *)(param_1 + 0x28));
  plStack_30 = &lStack_28;
  uStack_38 = CONCAT62(uStack_38._2_6_,8);
  puVar2 = &LAB_1003c5248;
  FUN_10006135c(&LAB_1003c5248,&uStack_38,param_2,(undefined4 *)(param_1 + 0x28));
  if ((int)puVar2 != 0) {
    iVar1 = 2;
    FUN_10000d938(2,0x32);
    if (iVar1 != 0) {
      FUN_10000d120("Error registering session shutdown dispatch - %!");
      uVar3 = 0x32;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_100105b50(uVar3);
      }
    }
  }
  return puVar2;
}


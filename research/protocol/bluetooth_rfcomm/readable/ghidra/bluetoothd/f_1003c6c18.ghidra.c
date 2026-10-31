/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c6c18
 * original code SHA256: 4bdca17f3ff94fd54fada8a0768a9e56c37d8b2e14b79ce6ea335c24e347d6df
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003c6c18(long param_1)

{
  undefined8 uStack_38;
  long *plStack_30;
  long lStack_28;
  
  uStack_38 = 0;
  lStack_28 = param_1;
  FUN_1000609fc(*(undefined4 *)(param_1 + 0x20));
  plStack_30 = &lStack_28;
  uStack_38 = CONCAT62(uStack_38._2_6_,8);
  FUN_10006135c(&LAB_1003c6c8c,&uStack_38,*(undefined2 *)(lRam0000000100cadd68 + 4),
                (undefined4 *)(param_1 + 0x20));
  return;
}


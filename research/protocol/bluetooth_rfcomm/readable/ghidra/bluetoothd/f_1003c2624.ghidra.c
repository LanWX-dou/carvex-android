/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c2624
 * original code SHA256: 3d865ebc3fca5d4ce2d4f54fdc3553ce527ca89631e9f6c20803b819d686142c
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 FUN_1003c2624(void)

{
  byte *pbVar1;
  long lVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  
  if (iRam0000000100cade68 != 0) {
    FUN_1000f9438();
  }
  pbVar1 = (byte *)0x32;
  FUN_1003d7a1c();
  pbRam0000000100cadd68 = pbVar1;
  if ((pbVar1 == (byte *)0x0) && (FUN_1000f9438(), pbRam0000000100cadd68 == (byte *)0x0)) {
    return 0x7f;
  }
  uRam0000000100c38310 = 0;
  lRam0000000100c38308 = 0;
  lRam0000000100c38318 = 0;
  puRam0000000100c38320 = (undefined4 *)0x0;
  lVar2 = (ulong)*pbRam0000000100cadd68 * 0x58;
  FUN_1001aad2c(lVar2,0x10a004017a26594);
  lRam0000000100c38308 = lVar2;
  if (lVar2 == 0) {
LAB_1003c2734:
    uVar4 = 0x6a;
  }
  else {
    lVar2 = (ulong)pbRam0000000100cadd68[1] * 0x38;
    FUN_1001aad2c(lVar2,0x10f0040a30ad163);
    lRam0000000100c38318 = lVar2;
    if (lVar2 == 0) goto LAB_1003c2734;
    puVar3 = (undefined4 *)0x4;
    FUN_1001aad2c(4,0x100004052888210);
    puRam0000000100c38320 = puVar3;
    if (puVar3 == (undefined4 *)0x0) {
      uVar4 = 0x6a;
      goto LAB_1003c2758;
    }
    *puVar3 = 0;
    uVar4 = 3;
    FUN_10036edc8(3,&LAB_1003c3fac);
    if ((int)uVar4 == 0) {
      iRam0000000100cade68 = 1;
      return uVar4;
    }
  }
  if (puRam0000000100c38320 != (undefined4 *)0x0) {
    FUN_1000110b8();
    puRam0000000100c38320 = (undefined4 *)0x0;
  }
LAB_1003c2758:
  if (lRam0000000100c38318 != 0) {
    FUN_1000110b8();
    lRam0000000100c38318 = 0;
  }
  if (lRam0000000100c38308 != 0) {
    FUN_1000110b8();
    lRam0000000100c38308 = 0;
  }
  return uVar4;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003d7f28
 * original code SHA256: 954560587790d06a818bd3f7c3777adae52ca427c595a0b1dde1280fd73ab758
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003d7f28(long param_1,undefined8 param_2)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  long lVar4;
  ushort *puVar5;
  
  if (iRam0000000100cade48 != 0) {
    iVar1 = 2;
    FUN_10000d938(2,0x2a);
    if (iVar1 != 0) {
      FUN_10000d120("OI_Dispatch_Init: %!");
      uVar2 = 0x2a;
      FUN_10000e9d4();
      uVar3 = uVar2;
      _os_log_type_enabled();
      if ((int)uVar3 != 0) {
        FUN_10018f150(uVar2);
      }
    }
    FUN_1000f9438();
  }
  if (param_1 != 0) {
    iVar1 = 2;
    FUN_10000d938(2,0x2a);
    if (iVar1 != 0) {
      FUN_10000d120("OI_Dispatch_Init: configuration parameter is deprecated");
      uVar2 = 0x2a;
      FUN_10000e9d4();
      uVar3 = uVar2;
      _os_log_type_enabled();
      if ((int)uVar3 != 0) {
        FUN_10018f150(uVar2);
      }
    }
    FUN_1003d7a60(param_1,0x2a);
  }
  lVar4 = 0x2a;
  FUN_1003d7a1c();
  if (lVar4 == 0) {
    FUN_1000f9438();
  }
  uRam0000000100c39fa8 = 0;
  uRam0000000100c39fa9 = 0;
  puVar5 = (ushort *)0x2a;
  FUN_1003d7a1c();
  uRam0000000100c39fac = *puVar5;
  lVar4 = (ulong)uRam0000000100c39fac * 0x18;
  FUN_1001aad2c(lVar4,0x1092040c7b4450d);
  lRam0000000100c39fb0 = lVar4;
  uRam0000000100c39faa = 0xffff;
  uRam0000000100c39fb8 = param_2;
  uRam0000000100c39fc0 = 0xffffffff;
  iRam0000000100cade48 = 1;
  return;
}


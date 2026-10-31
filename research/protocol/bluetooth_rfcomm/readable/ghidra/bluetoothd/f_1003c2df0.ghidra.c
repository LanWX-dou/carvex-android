/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c2df0
 * original code SHA256: ab36001783e4b468ab5a2faa15dc6f19e309bfaac8c25d849a463f8086a91a10
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined1 * FUN_1003c2df0(long param_1,undefined1 *param_2,int param_3)

{
  long lVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined1 *puVar5;
  long lStack_38;
  
  lStack_38 = 0;
  if (iRam0000000100cade68 != 0) {
    if ((param_1 == 0) && (param_3 != 0)) {
      FUN_1000f9438();
      return (undefined1 *)0x65;
    }
    FUN_1003c2394(param_2,&lStack_38);
    lVar1 = lStack_38;
    if ((int)param_2 != 0) {
      iVar2 = 2;
      FUN_10000d938(2,0x32);
      if (iVar2 == 0) {
        return param_2;
      }
      FUN_10000d120("OI_RFCOMM_Accept - linkhandle %d not found");
      uVar3 = 0x32;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 == 0) {
        return param_2;
      }
      FUN_1008b8180(param_2,uVar3);
      return param_2;
    }
    if (*(char *)(lStack_38 + 0xd) == '\x03') {
      *(long *)(lStack_38 + 0x48) = param_1;
      if (param_3 != 0) {
        puVar5 = &LAB_1003c2f74;
        FUN_1003d8e5c(&LAB_1003c2f74,*(long *)(lStack_38 + 0x80) + 6,
                      *(undefined8 *)(lStack_38 + 0x30),lStack_38 + 0x38,1);
        return puVar5;
      }
      puVar5 = (undefined1 *)0xf;
      FUN_1003c5334(0xf,*(long *)(lStack_38 + 0x80),*(undefined1 *)(lStack_38 + 10));
      if ((int)puVar5 != 0) {
        *(int *)(lVar1 + 0xa4) = (int)puVar5;
        FUN_1003c16dc(lVar1,1);
        return puVar5;
      }
      *(undefined1 *)(lVar1 + 0xd) = 9;
      return puVar5;
    }
    iVar2 = 2;
    FUN_10000d938(2,0x32);
    if (iVar2 != 0) {
      FUN_10000d120("Invalid state");
      uVar3 = 0x32;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_1008b4ec0(uVar3);
      }
    }
  }
  return (undefined1 *)0x198;
}


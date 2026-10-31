/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c5334
 * original code SHA256: e005ce73b34b7b91f4b5aa1bff31b3f461e2b8939a672d34ae14de250abe13fb
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


long FUN_1003c5334(int param_1,long param_2,undefined8 param_3)

{
  bool bVar1;
  undefined4 *puVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  byte bVar6;
  int iVar7;
  undefined1 uVar8;
  int iVar9;
  long lStack_50;
  undefined4 uStack_44;
  
  if (((0x34 < param_1 - 0x2fU) ||
      ((1L << ((ulong)(param_1 - 0x2fU) & 0x3f) & 0x10000000100001U) == 0)) && (param_1 != 0xf)) {
    FUN_1000f9438();
  }
  bVar1 = *(char *)(param_2 + 0xc) == '\0';
  iVar7 = 0x43;
  if (bVar1) {
    iVar7 = 99;
  }
  iVar9 = 0x2f;
  if (bVar1) {
    iVar9 = 0xf;
  }
  bVar6 = 3;
  if (param_1 != iVar9 && param_1 != iVar7) {
    bVar6 = 1;
  }
  uStack_44 = CONCAT22(1,CONCAT11((char)param_1,bVar6 | (byte)((int)param_3 << 2))) | 0x1000;
  puVar2 = &uStack_44;
  FUN_1003c6b60(puVar2,3);
  uStack_44 = CONCAT13((char)puVar2,(undefined3)uStack_44);
  puVar2 = &uStack_44;
  FUN_1003d8668(puVar2,4,0);
  if (puVar2 != (undefined4 *)0x0) {
    lVar3 = param_2;
    FUN_1003c54f8(param_2,param_3,puVar2,0);
    if ((int)lVar3 != 0) {
      iVar7 = 2;
      FUN_10000d938(2,0x32);
      if (iVar7 != 0) {
        FUN_10000d120("%! (%d)");
        uVar4 = 0x32;
        FUN_10000e9d4();
        uVar5 = uVar4;
        _os_log_type_enabled();
        if ((int)uVar5 != 0) {
          FUN_100105b50(uVar4);
        }
      }
      FUN_1000c3bf8(puVar2);
      return lVar3;
    }
    lStack_50 = 0;
    if ((int)param_3 == 0) {
      if ((param_1 != 0x2f) && (param_1 != 0x43)) {
        return 0;
      }
    }
    else {
      lVar3 = param_2;
      FUN_1003c136c(param_2,param_3,&lStack_50);
      if ((int)lVar3 != 0) {
        return lVar3;
      }
      *(char *)(lStack_50 + 0xb) = (char)param_1;
      if (param_1 == 0x2f) {
        uVar8 = 2;
      }
      else {
        if (param_1 != 0x43) {
          return 0;
        }
        uVar8 = 6;
      }
      *(undefined1 *)(lStack_50 + 0xd) = uVar8;
    }
    FUN_1003c6c18(param_2);
    return 0;
  }
  return 0x6a;
}


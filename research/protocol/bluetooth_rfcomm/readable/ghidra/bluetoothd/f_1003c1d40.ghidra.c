/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c1d40
 * original code SHA256: 39ac1c915195ca2b4b9cf2ca6930708af40b9a683e133ed8b53f22ed78c9303f
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined1 * FUN_1003c1d40(undefined1 *param_1,uint param_2)

{
  long lVar1;
  undefined1 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int iVar5;
  undefined2 uStack_50;
  undefined4 uStack_4e;
  undefined2 uStack_4a;
  uint6 uStack_48;
  undefined2 uStack_42;
  undefined8 uStack_40;
  ulong uStack_38;
  
  _uStack_48 = 0;
  uStack_40 = 0;
  uStack_38 = 0;
  FUN_1003d7a1c(0x28);
  uStack_4e = 0x1388ffff;
  uStack_4a = 0x308;
  uStack_48 = (uint6)(uint)uStack_48;
  uStack_38 = uStack_38 & 0xffffffffffffff00;
  iVar5 = 5;
  if (0x7f < param_2) {
    iVar5 = 6;
  }
  param_2 = iVar5 + param_2;
  uStack_50 = (undefined2)param_2;
  if ((param_2 & 0xffff) < 0x81) {
    uStack_50 = 0x80;
  }
  else {
    lVar1 = 0x28;
    FUN_1003d7a1c();
    if ((uint)*(ushort *)(lVar1 + 8) < (param_2 & 0xffff)) {
      lVar1 = 0x28;
      FUN_1003d7a1c();
      uStack_50 = *(undefined2 *)(lVar1 + 8);
    }
  }
  param_1[0xc] = 1;
  *(undefined8 *)(param_1 + 0x20) = 0;
  puVar2 = &LAB_1003c3a94;
  FUN_1003699e0(&LAB_1003c3a94,&LAB_1003c4180,&DAT_1003c3a08,3,param_1 + 6,&uStack_50,param_1 + 2,
                &UNK_100934970);
  if ((int)puVar2 == 0) {
    *param_1 = 2;
  }
  else {
    iVar5 = 2;
    FUN_10000d938(2,0x32);
    if (iVar5 != 0) {
      FUN_10000d120("L2CAP_CreateConnection failed with result %!");
      uVar3 = 0x32;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_1008b4ec0(uVar3);
      }
    }
    FUN_1003c1a34(param_1,puVar2,1);
  }
  return puVar2;
}


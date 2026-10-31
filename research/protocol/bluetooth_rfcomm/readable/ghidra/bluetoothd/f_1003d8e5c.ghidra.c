/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003d8e5c
 * original code SHA256: 9eed6f4179cb06c23731cf9fb118a6da77be314dcfacbe6778e1aba7b38fc2b0
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void FUN_1003d8e5c(undefined8 param_1,undefined4 *param_2,undefined8 *param_3,undefined4 *param_4,
                  undefined1 param_5)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  int iVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  
  if (((param_3 == (undefined8 *)0x0) || (param_2 == (undefined4 *)0x0)) ||
     (param_4 == (undefined4 *)0x0)) {
    FUN_1000f9438();
  }
  else if (iRam0000000100cade64 != 0) {
    uStack_50 = 0;
    uStack_68 = 0;
    uStack_60 = 0;
    puVar4 = param_2;
    FUN_100318f0c(param_2,&uStack_68);
    lVar9 = lRam0000000100c39fc8;
    if ((int)puVar4 == 0) {
      uVar1 = *(short *)(lRam0000000100c39fc8 + 0x20) + 1;
      uVar2 = uVar1;
      if (uVar1 < 0x1a5) {
        uVar2 = 0x1a4;
      }
      *(ushort *)(lRam0000000100c39fc8 + 0x20) = uVar2;
      uVar7 = (ulong)*(ushort *)(lVar9 + 0x14);
      if (uVar7 != 0) {
        uVar8 = 0;
        lVar9 = *(long *)(lVar9 + 0x18);
        if (uVar1 < 0x1a5) {
          uVar1 = 0x1a4;
        }
        iVar10 = (uint)uVar1 << 0x10;
        lVar6 = lVar9 + 0x38;
        do {
          if (*(int *)(lVar9 + uVar8 * 0x40 + 0x38) == 0) {
            lVar9 = lVar9 + (uVar8 & 0xffff) * 0x40;
            *(int *)(lVar9 + 0x38) = iVar10;
            uVar3 = *param_2;
            *(undefined2 *)(lVar6 + -0x34) = *(undefined2 *)(param_2 + 1);
            *(undefined4 *)(lVar6 + -0x38) = uVar3;
            *(undefined1 *)(lVar6 + 4) = param_5;
            uVar12 = param_3[2];
            uVar5 = param_3[5];
            uVar11 = param_3[4];
            uVar14 = param_3[1];
            uVar13 = *param_3;
            *(undefined8 *)(lVar6 + -0x18) = param_3[3];
            *(undefined8 *)(lVar6 + -0x20) = uVar12;
            *(undefined8 *)(lVar6 + -8) = uVar5;
            *(undefined8 *)(lVar6 + -0x10) = uVar11;
            *(undefined8 *)(lVar6 + -0x28) = uVar14;
            *(undefined8 *)(lVar6 + -0x30) = uVar13;
            uVar3 = *(undefined4 *)(lVar9 + 0x38);
            uStack_60 = CONCAT44(uStack_60._4_4_,uVar3);
            *param_4 = uVar3;
            puStack_48 = &uStack_60;
            uStack_50 = CONCAT62(uStack_50._2_6_,0x10);
            uStack_58 = param_1;
            FUN_100060de4(&LAB_1003d9004,&uStack_50,0);
            return;
          }
          uVar8 = uVar8 + 1;
          iVar10 = iVar10 + 1;
          lVar6 = lVar6 + 0x40;
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
      }
      iVar10 = 2;
      FUN_10000d938(2,0x31);
      if (iVar10 != 0) {
        FUN_10000d120("OI_POLICYMGR_NewConnection: connection list full!");
        uVar5 = 0x31;
        FUN_10000e9d4();
        uVar11 = uVar5;
        _os_log_type_enabled();
        if ((int)uVar11 != 0) {
          FUN_100105b50(uVar5);
        }
      }
    }
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1002f1300
 * original code SHA256: 95e07d8b14c0a055c11ac48a7c864c11357771839ffb82a74e2e4f87eaa8b30a
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined **
FUN_1002f1300(undefined8 *param_1,undefined4 *param_2,uint param_3,long param_4,undefined8 param_5,
             undefined8 param_6)

{
  undefined2 uVar1;
  int iVar2;
  long lVar3;
  undefined1 *puVar4;
  undefined **ppuVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  long lVar8;
  long lVar9;
  undefined **ppuVar10;
  undefined *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined *puStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  ppuVar10 = &puStack_b0;
  if ((param_1 == (undefined8 *)0x0) || (param_4 == 0)) {
    FUN_1000f9438();
    return (undefined **)0x65;
  }
  if (iRam0000000100cadde0 != 0) {
    return (undefined **)0x8c;
  }
  lVar3 = 0x198;
  FUN_1001aad2c(0x198,0x10a0040d48d3414);
  if (lVar3 == 0) {
    lRam0000000100c29f50 = lVar3;
    return (undefined **)0x6a;
  }
  lVar8 = 0;
  uStack_68 = 0;
  puStack_70 = (undefined *)0x0;
  uStack_58 = 0;
  uStack_60 = 0;
  uStack_88 = 0;
  puStack_90 = (undefined *)0x0;
  uStack_78 = 0;
  uStack_80 = 0;
  uStack_a8 = 0;
  puStack_b0 = (undefined *)0x0;
  uStack_98 = 0;
  uStack_a0 = 0;
  lVar9 = 8;
  lRam0000000100c29f50 = lVar3;
  do {
    *(undefined2 *)(lVar3 + lVar8 * 0x30) = 0xffff;
    lVar8 = lVar8 + 1;
    lVar9 = lVar9 + -1;
  } while (lVar9 != 0);
  puVar4 = (undefined1 *)0x10;
  FUN_1003d7a1c();
  lVar3 = lRam0000000100c29f50;
  *(undefined1 *)(lRam0000000100c29f50 + 400) = *puVar4;
  *(short *)(lVar3 + 0x192) = (short)param_5;
  *(short *)(lVar3 + 0x194) = (short)param_6;
  ppuVar5 = (undefined **)&LAB_1002f15e0;
  FUN_1003c2434(&LAB_1002f15e0,&PTR_LAB_100ba52a8,param_5,param_6,lVar3 + 400,&UNK_100ba52e8);
  if ((int)ppuVar5 == 0) {
    DAT_100c29f58 = 1;
    uRam0000000100c29f5a = 1;
    uRam0000000100c29f60 = (uint)*(byte *)(lRam0000000100c29f50 + 400);
    DAT_100c29f68 = 1;
    uRam0000000100c29f6a = 1;
    uRam0000000100c29f70 = param_3 >> 5 & 1;
    uRam0000000100c29f80 = param_3 & 0x1f | (param_3 >> 9 & 1) << 5;
    DAT_100c29f78 = 1;
    uRam0000000100c29f7a = 2;
    puStack_70 = &UNK_100ba5318;
    uStack_68 = CONCAT62(uStack_68._2_6_,5);
    uStack_a0 = *param_1;
    uVar1 = *(undefined2 *)(param_1 + 1);
    uStack_58 = CONCAT62(uStack_58._2_6_,uVar1);
    puStack_90 = &UNK_100ba53e0;
    uStack_88 = CONCAT62(uStack_88._2_6_,5);
    uStack_78 = CONCAT62(uStack_78._2_6_,uVar1);
    puStack_b0 = &UNK_100ba5468;
    uStack_a8 = CONCAT62(uStack_a8._2_6_,5);
    uStack_98 = CONCAT62(uStack_98._2_6_,uVar1);
    uStack_80 = uStack_a0;
    uStack_60 = uStack_a0;
    if (sRam0000000100c1cc48 == 0x106) {
      FUN_1003cb22c(&puStack_b0,lRam0000000100c29f50 + 0x184);
      if ((int)ppuVar10 != 0) goto LAB_1002f1574;
    }
    else {
      if (sRam0000000100c1cc48 == 0x107) {
        ppuVar10 = &puStack_90;
        FUN_1003cb22c(ppuVar10,lRam0000000100c29f50 + 0x184);
        if ((int)ppuVar10 != 0) {
LAB_1002f1574:
          FUN_1003c2790(*(undefined1 *)(lRam0000000100c29f50 + 400));
          goto LAB_1002f1584;
        }
      }
      else {
        ppuVar10 = &puStack_70;
        FUN_1003cb22c(ppuVar10,lRam0000000100c29f50 + 0x184);
        if ((int)ppuVar10 != 0) goto LAB_1002f1574;
        FUN_1003cb554(*(undefined4 *)(lRam0000000100c29f50 + 0x184),&puStack_90);
      }
      FUN_1003cb554(*(undefined4 *)(lRam0000000100c29f50 + 0x184),&puStack_b0);
    }
    lVar3 = lRam0000000100c29f50;
    *(long *)(lRam0000000100c29f50 + 0x188) = param_4;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = *(undefined4 *)(lVar3 + 0x184);
    }
    FUN_10031ed88(0x600000);
    ppuVar10 = (undefined **)0x0;
    iRam0000000100cadde0 = 1;
  }
  else {
    iVar2 = 2;
    FUN_10000d938(2,0x10);
    ppuVar10 = ppuVar5;
    if (iVar2 != 0) {
      FUN_10000d120("RFCOMM registration failed!\n");
      uVar6 = 0x10;
      FUN_10000e9d4();
      uVar7 = uVar6;
      _os_log_type_enabled();
      if ((int)uVar7 != 0) {
        FUN_1008b4ec0(uVar6);
      }
    }
LAB_1002f1584:
    FUN_1000110b8(lRam0000000100c29f50);
    lRam0000000100c29f50 = 0;
  }
  return ppuVar10;
}


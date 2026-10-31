/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100634b7c
 * original code SHA256: 6a11c2c3da546a5260036484fabeda733ebce035db6f82c2b59027d7231fbb8f
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100634b7c(void)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined *puVar17;
  undefined8 uVar18;
  undefined *puVar19;
  ushort uVar20;
  int iVar21;
  undefined8 *puVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  byte bVar25;
  long lVar26;
  long lVar27;
  undefined4 uStack_180;
  undefined8 uStack_17c;
  undefined8 uStack_170;
  undefined8 *puStack_168;
  undefined8 uStack_160;
  undefined1 *puStack_158;
  undefined8 uStack_150;
  undefined8 *puStack_148;
  undefined8 uStack_140;
  undefined *puStack_138;
  undefined8 uStack_130;
  undefined *puStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  ulong uStack_70;
  undefined8 *puStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_48;
  undefined8 uStack_40;
  long lStack_38;
  
  uVar1 = uRam0000000100cae4a0;
  puVar19 = PTR_DAT_100bbdcb8;
  uVar18 = _UNK_100bbdcb0;
  puVar17 = PTR_DAT_100bbdca8;
  uVar16 = _UNK_100bbdca0;
  uVar15 = _UNK_10093a268;
  uVar14 = _UNK_10093a260;
  uVar13 = _UNK_10093a258;
  uVar12 = _UNK_10093a250;
  uVar11 = _UNK_10093a248;
  uVar10 = _UNK_10093a240;
  uVar9 = _UNK_10093a238;
  uVar8 = _UNK_10093a230;
  uVar7 = _UNK_10093a228;
  uVar6 = _UNK_10093a220;
  uVar5 = _UNK_10093a218;
  uVar4 = _UNK_10093a210;
  uVar3 = _UNK_10093a208;
  uVar2 = _UNK_10093a200;
  uVar24 = _UNK_10093a1f8;
  uVar23 = _UNK_10093a1f0;
  lStack_38 = *(long *)PTR____stack_chk_guard_100bfc980;
  iVar21 = *(int *)(lRam0000000100cae158 + 0x84);
  if (iVar21 == 9) {
    lVar26 = *(long *)(lRam0000000100cae158 + 0x28);
    lVar27 = lRam0000000100cae158;
    while (lRam0000000100cae158 = lVar27, uRam0000000100cae4a0 = uVar1, lVar26 != 0) {
      uStack_b8 = uVar3;
      uStack_c0 = uVar2;
      uStack_a8 = uVar24;
      uStack_b0 = uVar23;
      uStack_d8 = uVar7;
      uStack_e0 = uVar6;
      uStack_c8 = uVar5;
      uStack_d0 = uVar4;
      uStack_f8 = uVar11;
      uStack_100 = uVar10;
      uStack_e8 = uVar9;
      uStack_f0 = uVar8;
      uStack_108 = uVar13;
      uStack_110 = uVar12;
      puStack_128 = puVar17;
      uStack_130 = uVar16;
      uStack_118 = uVar15;
      uStack_120 = uVar14;
      puStack_138 = puVar19;
      uStack_140 = uVar18;
      puVar22 = (undefined8 *)
                (*(long *)(*(long *)(lVar27 + 8) +
                          (*(ulong *)(lVar27 + 0x20) >> 5 & 0x7fffffffffffff8)) +
                (*(ulong *)(lVar27 + 0x20) & 0xff) * 0x10);
      puStack_148 = (undefined8 *)puVar22[1];
      uStack_150 = *puVar22;
      puVar22 = &uStack_150;
      FUN_10019da5c(puVar22,&uStack_b0);
      if (((ulong)puVar22 & 1) == 0) {
        puVar22 = &uStack_150;
        FUN_10019da5c(puVar22,&uStack_c0);
        if (((ulong)puVar22 & 1) == 0) {
          puVar22 = &uStack_150;
          FUN_10019da5c(puVar22,&uStack_d0);
          if (((ulong)puVar22 & 1) == 0) {
            puVar22 = &uStack_150;
            FUN_10019da5c(puVar22,&uStack_e0);
            if (((ulong)puVar22 & 1) == 0) {
              puVar22 = &uStack_150;
              FUN_10019da5c(puVar22,&uStack_f0);
              if (((ulong)puVar22 & 1) == 0) {
                puVar22 = &uStack_150;
                FUN_10019da5c(puVar22,&uStack_110);
                if (((ulong)puVar22 & 1) == 0) {
                  puVar22 = &uStack_150;
                  FUN_10019da5c(puVar22,&uStack_120);
                  if (((ulong)puVar22 & 1) == 0) {
                    puVar22 = &uStack_150;
                    FUN_10019da5c(puVar22,&uStack_100);
                    if (((ulong)puVar22 & 1) == 0) {
                      if (bRam0000000100c1f619 == 1) {
                        puVar22 = &uStack_150;
                        FUN_10019da5c(puVar22,&uStack_130);
                        if (((ulong)puVar22 & 1) != 0) goto LAB_100634d58;
                        if (bRam0000000100c1f619 != 1) goto LAB_100634e24;
                        puVar22 = &uStack_150;
                        FUN_10019da5c(puVar22,&uStack_140);
                        bVar25 = bRam0000000100c1f619;
                        if (((ulong)puVar22 & 1) != 0) goto LAB_100634d58;
                      }
                      else {
LAB_100634e24:
                        bVar25 = 0;
                      }
                      uStack_48 = 0;
                      uStack_40 = 0;
                      puStack_68 = &uStack_48;
                      uStack_58 = 3;
                      uStack_70 = 0x100003;
                      uStack_60 = 0x20003;
                      uStack_88 = _UNK_10093a1c0;
                      uStack_90 = _UNK_10093a1b8;
                      uStack_78 = _UNK_10093a1d0;
                      uStack_80 = _UNK_10093a1c8;
                      uStack_98 = _UNK_10093a278;
                      uStack_a0 = _UNK_10093a270;
                      uStack_160 = 0;
                      puStack_158 = (undefined1 *)0x0;
                      uStack_170 = 0;
                      if ((bVar25 & 1) == 0) {
                        puVar22 = &uStack_150;
                        FUN_10019da5c(puVar22,&uStack_130);
                        if (((ulong)puVar22 & 1) != 0) goto LAB_100634ea8;
                        puVar22 = &uStack_150;
                        FUN_10019da5c(puVar22,&uStack_140);
                        if ((int)puVar22 != 0) goto LAB_100634ea8;
                      }
                      else {
LAB_100634ea8:
                        bRam0000000100c1f619 = 1;
                      }
                      if ((char)uStack_150 == '\x03') {
                        uVar20 = uStack_150._2_2_;
                        iVar21 = 0;
                        FUN_10000d938(0,0x5c);
                        if (uVar20 < 5) {
                          if (iVar21 != 0) {
                            FUN_1003d59f8();
                            FUN_10000d120("Querying RFCOMM Service : %s");
                            uVar24 = 0x5c;
                            FUN_10000e9d4();
                            uVar23 = uVar24;
                            _os_log_type_enabled();
                            if ((int)uVar23 != 0) {
                              FUN_10000ea80();
                              uStack_180 = (undefined4)_UNK_100930b20;
                              uStack_17c = uVar23;
LAB_100634f88:
                              __os_log_impl(0x100000000,uVar24,0," %{public}s",&uStack_180,0xc);
                            }
                          }
                        }
                        else if (iVar21 != 0) {
                          FUN_1003d56fc();
                          FUN_10000d120("Querying RFCOMM Service : %s");
                          uVar24 = 0x5c;
                          FUN_10000e9d4();
                          uVar23 = uVar24;
                          _os_log_type_enabled();
                          if ((int)uVar23 != 0) {
                            FUN_10000ea80();
                            uStack_180 = (undefined4)_UNK_100930b20;
                            uStack_17c = uVar23;
                            goto LAB_100634f88;
                          }
                        }
                        uVar23 = uStack_160;
                        if ((char)uStack_150 == '\x03') {
                          if (uStack_150._2_2_ == 0x10) {
                            uVar24 = *puStack_148;
                            puStack_68[1] = puStack_148[1];
                            *puStack_68 = uVar24;
                            lVar27 = -0x60;
                          }
                          else {
                            uStack_88 = CONCAT44(uStack_88._4_4_,puStack_148._0_4_);
                            lVar27 = -0x80;
                          }
                          puStack_158 = &stack0xfffffffffffffff0 + lVar27;
                          uStack_160 = CONCAT71(uStack_160._1_7_,6);
                          uVar24 = uStack_160;
                          uStack_160._4_4_ = SUB84(uVar23,4);
                          uStack_160._0_4_ = CONCAT22(2,(short)uVar24);
                        }
                      }
                      uVar23 = uStack_170;
                      uStack_170 = CONCAT71(uStack_170._1_7_,6);
                      uVar24 = uStack_170;
                      uStack_170._4_4_ = SUB84(uVar23,4);
                      uStack_170._0_4_ = CONCAT22(1,(short)uVar24);
                      puStack_168 = &uStack_a0;
                      iVar21 = 0x6350b0;
                      FUN_1003c9dd8(&LAB_1006350b0,&uStack_160,&uStack_170);
                      uVar23 = uRam0000000100cae4a0;
                      if (iVar21 == 0) goto LAB_100634de8;
                      uVar24 = uRam0000000100cae4a0;
                      _os_log_type_enabled(uRam0000000100cae4a0,0x10);
                      if ((int)uVar24 != 0) {
                        uStack_180 = (undefined4)_UNK_100930510;
                        uStack_17c = CONCAT44(uStack_17c._4_4_,iVar21);
                        __os_log_error_impl(0x100000000,uVar23,0x10,
                                            "Service+RFCOMM search failed with %{bluetooth:OI_STATUS}u"
                                            ,&uStack_180,8);
                      }
                      *(undefined4 *)(lRam0000000100cae158 + 0x80) = 0;
                      goto LAB_100634dc4;
                    }
                  }
                }
              }
            }
          }
        }
      }
LAB_100634d58:
      FUN_10063508c(lRam0000000100cae158);
      lVar27 = lRam0000000100cae158;
      uVar1 = uRam0000000100cae4a0;
      lVar26 = *(long *)(lRam0000000100cae158 + 0x28);
    }
    if (*(int *)(lVar27 + 0x84) == 9) {
      uVar23 = uVar1;
      _os_log_type_enabled(uVar1,0);
      if ((int)uVar23 != 0) {
        uStack_70 = uStack_70 & 0xffffffffffff0000;
        __os_log_impl(0x100000000,uVar1,0,"RFCOMM channel update complete",&uStack_70,2);
        lVar27 = lRam0000000100cae158;
      }
      *(undefined4 *)(lVar27 + 0x80) = 0;
LAB_100634dc4:
      FUN_1006332cc();
    }
  }
  else {
    uVar23 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0x10);
    if ((int)uVar23 != 0) {
      FUN_1008de940(iVar21,uVar1);
    }
  }
LAB_100634de8:
  if (*(long *)PTR____stack_chk_guard_100bfc980 == lStack_38) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}


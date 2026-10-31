/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c73f0
 * original code SHA256: cc129683eb1fee6d5963bb1ce5e404806d4be7fc1cf4657493e675e61e8a8229
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0001003c7084) */
/* WARNING: Removing unreachable block (ram,0x0001003c7094) */
/* WARNING: Removing unreachable block (ram,0x0001003c70f0) */
/* WARNING: Removing unreachable block (ram,0x0001003c70bc) */
/* WARNING: Removing unreachable block (ram,0x0001003c705c) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1003c73f0(long param_1,byte *param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  code *pcVar8;
  int iVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined1 uVar12;
  char cVar13;
  ushort uVar14;
  long lVar15;
  ushort uVar16;
  uint uVar17;
  uint uVar18;
  ulong unaff_x30;
  ulong uVar19;
  undefined1 uStack_148;
  byte bStack_147;
  undefined8 uStack_146;
  undefined8 uStack_13e;
  undefined8 uStack_136;
  undefined8 uStack_12e;
  undefined8 uStack_126;
  undefined8 uStack_11e;
  undefined8 uStack_116;
  undefined8 uStack_10e;
  undefined8 uStack_106;
  undefined8 uStack_fe;
  undefined8 uStack_f6;
  undefined8 uStack_ee;
  undefined8 uStack_e6;
  undefined8 uStack_de;
  undefined8 uStack_d6;
  undefined8 uStack_ce;
  undefined8 uStack_c6;
  undefined8 uStack_be;
  undefined8 uStack_b6;
  undefined8 uStack_ae;
  undefined8 uStack_a6;
  undefined8 uStack_9e;
  undefined6 uStack_96;
  ushort uStack_90;
  undefined6 uStack_8e;
  ushort uStack_88;
  undefined6 uStack_86;
  undefined2 uStack_80;
  undefined8 uStack_7e;
  undefined2 uStack_76;
  undefined2 uStack_74;
  byte bStack_72;
  byte bStack_71;
  undefined2 uStack_70;
  undefined2 uStack_6e;
  undefined2 uStack_6c;
  undefined2 uStack_6a;
  undefined2 uStack_68;
  undefined6 uStack_66;
  ushort uStack_60;
  byte bStack_5e;
  undefined1 uStack_5d;
  undefined1 uStack_5c;
  undefined1 uStack_5b;
  undefined1 uStack_5a;
  byte bStack_59;
  undefined1 uStack_58;
  undefined1 uStack_57;
  undefined6 uStack_56;
  
  bVar1 = *param_2;
  uVar18 = (uint)bVar1;
  uVar17 = bVar1 & 0xfc;
  bVar2 = param_2[1];
  bVar4 = bVar2 >> 1;
  uVar6 = (uint)bVar4;
  if (param_3 != uVar6 + 2) {
    iVar9 = 2;
    FUN_10000d938(2,0x32);
    if (iVar9 != 0) {
      uStack_90 = (ushort)uVar17;
      uStack_8e = 0;
      FUN_10000d120("Invalid RFCOMM packet received, command (%d), force disconnect the link");
      uVar11 = 0x32;
      FUN_10000e9d4();
      uVar10 = uVar11;
      _os_log_type_enabled();
      if ((int)uVar10 != 0) {
        FUN_10018f150(uVar11);
      }
    }
    FUN_100316bbc(param_1 + 6);
    return;
  }
  uVar7 = uVar17 - 0x10 >> 4 | uVar17 << 0x1c;
  if ((int)uVar7 < 7) {
    if ((int)uVar7 < 4) {
      if (uVar7 == 0) {
        if (uVar6 == 1) {
          if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
            pcVar8 = (code *)SoftwareBreakpoint(0xc471,0x1003c7634);
            (*pcVar8)();
          }
          if (param_1 == 0) {
            FUN_1000f9438();
          }
          if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
            pcVar8 = (code *)SoftwareBreakpoint(0xc471,0x1003c6e2c);
            (*pcVar8)();
          }
          FUN_1003d8200(*(undefined4 *)(param_1 + 0x24));
          return;
        }
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 == 0) {
          return;
        }
        uStack_90 = 0x395;
        uStack_8e = 0;
        uStack_88 = 0;
        uStack_86 = 0;
        FUN_10000d120("%! (%d)");
        uVar11 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_10018f150(uVar11);
        return;
      }
      if (uVar7 == 1) {
        if (uVar17 != 0x20) {
          FUN_1000f9438();
          uVar18 = (uint)*param_2;
        }
        if ((uVar18 >> 1 & 1) != 0) {
          if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
            pcVar8 = (code *)SoftwareBreakpoint(0xc471,0x1003c78d8);
            (*pcVar8)();
          }
          lVar15 = *(long *)PTR____stack_chk_guard_100bfc980;
          if (param_1 == 0) {
            FUN_1000f9438();
          }
          uStack_56 = 0;
          bStack_5e = 0;
          uStack_5d = 0;
          uStack_5c = 0;
          uStack_5b = 0;
          uStack_5a = 0;
          bStack_59 = 0;
          uStack_58 = 0;
          uStack_57 = 0;
          uStack_66 = 0;
          uStack_60 = 0;
          uStack_6e = 0;
          uStack_6c = 0;
          uStack_6a = 0;
          uStack_68 = 0;
          uStack_76 = 0;
          uStack_74 = 0;
          bStack_72 = 0;
          bStack_71 = 0;
          uStack_70 = 0;
          uStack_7e = 0;
          uStack_86 = 0;
          uStack_80 = 0;
          uStack_8e = 0;
          uStack_88 = 0;
          uStack_96 = 0;
          uStack_90 = 0;
          uStack_9e = 0;
          uStack_a6 = 0;
          uStack_ae = 0;
          uStack_b6 = 0;
          uStack_be = 0;
          uStack_c6 = 0;
          uStack_ce = 0;
          uStack_d6 = 0;
          uStack_de = 0;
          uStack_e6 = 0;
          uStack_ee = 0;
          uStack_f6 = 0;
          uStack_fe = 0;
          uStack_106 = 0;
          uStack_10e = 0;
          uStack_116 = 0;
          uStack_11e = 0;
          uStack_126 = 0;
          uStack_12e = 0;
          uStack_136 = 0;
          uStack_13e = 0;
          uStack_146 = 0;
          uStack_148 = 0x21;
          bStack_147 = bVar4 << 1 | 1;
          ___memmove_chk(&uStack_146,param_2 + 2,uVar6,0xfe);
          FUN_1003c5884(param_1,0,&uStack_148,uVar6 + 2,0);
          if (*(long *)PTR____stack_chk_guard_100bfc980 == lVar15) {
            return;
          }
                    /* WARNING: Subroutine does not return */
          ___stack_chk_fail();
        }
        FUN_1003c6db8(param_1);
        if (*(code **)(param_1 + 0x30) != (code *)0x0) {
          (**(code **)(param_1 + 0x30))(param_1 + 6,param_2 + 2,uVar6);
          *(undefined8 *)(param_1 + 0x30) = 0;
          return;
        }
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 == 0) {
          return;
        }
        FUN_10000d120("Mux_ReceiveTEST, receive response but no outstanding command, ignoring");
        uVar11 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_10018f150(uVar11);
        return;
      }
    }
    else {
      if (uVar7 == 4) {
        uStack_60 = 0;
        bStack_5e = 0;
        uStack_5d = 0;
        uStack_5c = 0;
        uStack_5b = 0;
        uStack_5a = 0;
        bStack_59 = 0;
        if (uVar6 != 2) {
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 == 0) {
            return;
          }
          uStack_90 = 0x395;
          uStack_8e = 0;
          uStack_88 = 0;
          uStack_86 = 0;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_10018f150(uVar11);
          return;
        }
        bVar2 = param_2[2];
        bVar4 = bVar2 >> 2;
        uVar16 = (ushort)bVar4;
        if ((0xf7 < bVar2) || (bVar4 == 1)) {
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 == 0) {
            return;
          }
          uStack_90 = 0x395;
          uStack_8e = 0;
          uStack_88 = (ushort)bVar4;
          uStack_86 = 0;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_10018f150(uVar11);
          return;
        }
        if ((bVar1 >> 1 & 1) == 0) {
          FUN_1003c6db8(param_1);
          return;
        }
        bVar1 = param_2[3];
        lVar15 = param_1;
        FUN_1003c136c(param_1,uVar16,&uStack_60);
        if ((int)lVar15 == 0) {
          uStack_74 = 0x551;
          bStack_72 = bVar2 | 3;
          bStack_71 = bVar1;
          FUN_1003c5884(param_1,0,&uStack_74,4,0);
          lVar15 = CONCAT17(bStack_59,
                            CONCAT16(uStack_5a,
                                     CONCAT15(uStack_5b,
                                              CONCAT14(uStack_5c,
                                                       CONCAT13(uStack_5d,
                                                                CONCAT12(bStack_5e,uStack_60))))));
          pcVar8 = *(code **)(*(long *)(lVar15 + 0x28) + 0x10);
          if (pcVar8 == (code *)0x0) {
            return;
          }
          (*pcVar8)(*(undefined2 *)(lVar15 + 8),bVar1 & 0xf);
          return;
        }
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 != 0) {
          uStack_90 = (ushort)lVar15;
          uStack_8e = (undefined6)((ulong)lVar15 >> 0x10);
          uStack_88 = (ushort)bVar4;
          uStack_86 = 0;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 != 0) {
            FUN_10018f150(uVar11);
          }
        }
        goto LAB_1003c80b8;
      }
      if (uVar7 == 5) {
        if (param_1 == 0) {
          FUN_1000f9438();
          uVar18 = (uint)*param_2;
        }
        if ((uVar18 >> 1 & 1) != 0) {
          FUN_1003c7174(param_1,0);
          if ((*(byte *)(param_1 + 0x2c) & 1) != 0) {
            return;
          }
          *(undefined1 *)(param_1 + 0x2d) = 0;
          return;
        }
        goto LAB_1003c7720;
      }
    }
LAB_1003c7750:
    uStack_60 = 0x311;
    bStack_5e = bVar1 & 0xfe;
    FUN_1003c5884(param_1,0,&uStack_60,3,0);
    return;
  }
  if (8 < (int)uVar7) {
    if (uVar7 == 9) {
      if (param_1 == 0) {
        FUN_1000f9438();
        uVar18 = (uint)*param_2;
      }
      if ((uVar18 >> 1 & 1) != 0) {
        FUN_1003c7100(param_1,0);
        if ((*(byte *)(param_1 + 0x2c) & 1) != 0) {
          return;
        }
        *(undefined1 *)(param_1 + 0x2d) = 1;
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
          pcVar8 = (code *)SoftwareBreakpoint(0xc471,0x1003c789c);
          (*pcVar8)();
        }
        FUN_1003c5108(param_1);
        return;
      }
LAB_1003c7720:
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar8 = (code *)SoftwareBreakpoint(0xc471,0x1003c774c);
        (*pcVar8)();
      }
      FUN_1003c6db8(param_1);
      return;
    }
    if (uVar7 != 0xd) goto LAB_1003c7750;
    if (param_1 == 0) {
      FUN_1000f9438();
    }
    uStack_60 = 0;
    bStack_5e = 0;
    uStack_5d = 0;
    uStack_5c = 0;
    uStack_5b = 0;
    uStack_5a = 0;
    bStack_59 = 0;
    if (bVar2 < 4) {
      iVar9 = 2;
      FUN_10000d938(2,0x32);
      if (iVar9 == 0) {
        return;
      }
      uStack_90 = (ushort)bVar4;
      uStack_8e = 0;
      FUN_10000d120("Invalid MSC command length %d, minimum 2 required");
      uVar11 = 0x32;
      FUN_10000e9d4();
      uVar10 = uVar11;
      _os_log_type_enabled();
      if ((int)uVar10 == 0) {
        return;
      }
      FUN_10018f150(uVar11);
      return;
    }
    bVar2 = param_2[2] >> 2;
    uVar16 = (ushort)bVar2;
    bVar1 = param_2[3];
    if (uVar6 == 2) {
      uVar17 = 0;
    }
    else {
      if (uVar6 != 3) {
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 == 0) {
          return;
        }
        uStack_90 = 0x395;
        uStack_8e = 0;
        uStack_88 = (ushort)bVar2;
        uStack_86 = 0;
        FUN_10000d120("%! (%d)");
        uVar11 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_10018f150(uVar11);
        return;
      }
      uVar17 = (uint)(int)(char)(param_2[4] << 6) >> 7 & (uint)(param_2[4] >> 4);
    }
    lVar15 = param_1;
    FUN_1003c136c(param_1,uVar16,&uStack_60);
    if ((int)lVar15 != 0) {
      iVar9 = 2;
      FUN_10000d938(2,0x32);
      if (iVar9 != 0) {
        uStack_90 = (ushort)lVar15;
        uStack_8e = (undefined6)((ulong)lVar15 >> 0x10);
        uStack_88 = (ushort)bVar2;
        uStack_86 = 0;
        FUN_10000d120("%! (%d)");
        uVar11 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar10 != 0) {
          FUN_10018f150(uVar11);
        }
      }
      if ((*param_2 >> 1 & 1) == 0) {
        return;
      }
      goto LAB_1003c80b8;
    }
    if ((*param_2 >> 1 & 1) != 0) {
      FUN_1003c71e8(param_1,0,uVar16,bVar1,uVar17);
      lVar15 = CONCAT17(bStack_59,
                        CONCAT16(uStack_5a,
                                 CONCAT15(uStack_5b,
                                          CONCAT14(uStack_5c,
                                                   CONCAT13(uStack_5d,CONCAT12(bStack_5e,uStack_60))
                                                  ))));
      if ((*(byte *)(param_1 + 0x2c) & 1) == 0) {
        if ((bVar1 >> 1 & 1) == 0) {
          *(undefined1 *)(lVar15 + 0x20) = 1;
          FUN_1003c50a8();
          lVar15 = CONCAT17(bStack_59,
                            CONCAT16(uStack_5a,
                                     CONCAT15(uStack_5b,
                                              CONCAT14(uStack_5c,
                                                       CONCAT13(uStack_5d,
                                                                CONCAT12(bStack_5e,uStack_60))))));
        }
        else {
          *(undefined1 *)(lVar15 + 0x20) = 0;
        }
      }
      pcVar8 = *(code **)(*(long *)(lVar15 + 0x28) + 0x18);
      if (pcVar8 == (code *)0x0) {
        return;
      }
      (*pcVar8)(*(undefined2 *)(lVar15 + 8),bVar1 & 0xce,uVar17);
      return;
    }
    FUN_1003c6db8(param_1);
    lVar15 = CONCAT17(bStack_59,
                      CONCAT16(uStack_5a,
                               CONCAT15(uStack_5b,
                                        CONCAT14(uStack_5c,
                                                 CONCAT13(uStack_5d,CONCAT12(bStack_5e,uStack_60))))
                              ));
    if (*(char *)(lVar15 + 0xd) != '\x04') {
      return;
    }
    *(undefined1 *)(lVar15 + 0xd) = 5;
    if (*(char *)(param_1 + 0x2c) == '\x01') {
      bVar1 = *(byte *)(lVar15 + 0xa2);
      if (bVar1 == 0) {
        cVar13 = -1;
      }
      else {
        bVar2 = *(byte *)(lVar15 + 0xe);
        if (bVar1 < bVar2) {
          FUN_1000f9438();
          lVar15 = CONCAT17(bStack_59,
                            CONCAT16(uStack_5a,
                                     CONCAT15(uStack_5b,
                                              CONCAT14(uStack_5c,
                                                       CONCAT13(uStack_5d,
                                                                CONCAT12(bStack_5e,uStack_60))))));
          bVar1 = *(byte *)(lVar15 + 0xa2);
          bVar2 = *(byte *)(lVar15 + 0xe);
        }
        cVar13 = bVar1 - (bVar2 + *(char *)(lVar15 + 0xa3));
        if (cVar13 == '\0') goto LAB_1003c83a4;
      }
      FUN_1003c5030(lVar15,cVar13);
      if ((int)lVar15 != 0) {
        return;
      }
      lVar15 = CONCAT17(bStack_59,
                        CONCAT16(uStack_5a,
                                 CONCAT15(uStack_5b,
                                          CONCAT14(uStack_5c,
                                                   CONCAT13(uStack_5d,CONCAT12(bStack_5e,uStack_60))
                                                  ))));
    }
LAB_1003c83a4:
    if (*(code **)(lVar15 + 0x48) == (code *)0x0) {
      return;
    }
    (**(code **)(lVar15 + 0x48))(*(undefined2 *)(lVar15 + 8),*(undefined2 *)(lVar15 + 0x10),0);
    *(undefined8 *)
     (CONCAT17(bStack_59,
               CONCAT16(uStack_5a,
                        CONCAT15(uStack_5b,
                                 CONCAT14(uStack_5c,
                                          CONCAT13(uStack_5d,CONCAT12(bStack_5e,uStack_60)))))) +
     0x48) = 0;
    return;
  }
  if (uVar7 != 7) {
    if (uVar7 == 8) {
      uStack_58 = 0;
      uStack_57 = 0;
      uStack_68 = 0;
      uStack_66 = 0;
      uStack_60 = 0;
      bStack_5e = 0;
      uStack_5d = 0;
      uStack_5c = 0;
      uStack_5b = 0;
      uStack_5a = 0;
      bStack_59 = 0;
      if (bVar2 < 2) {
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 == 0) {
          return;
        }
        uStack_90 = 0;
        uStack_8e = 0;
        FUN_10000d120("Invalid RPN command length %d, minimum 1 required");
        uVar11 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_10018f150(uVar11);
        return;
      }
      bVar2 = param_2[2] >> 2;
      uVar16 = (ushort)bVar2;
      if ((0xf7 < param_2[2]) || (bVar2 == 1)) {
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 == 0) {
          return;
        }
        uStack_90 = 0x395;
        uStack_8e = 0;
        uStack_88 = (ushort)bVar2;
        uStack_86 = 0;
        FUN_10000d120("%! (%d)");
        uVar11 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_10018f150(uVar11);
        return;
      }
      if (uVar6 != 8) {
        if (uVar6 != 1) {
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 == 0) {
            return;
          }
          uStack_90 = 0x395;
          uStack_8e = 0;
          uStack_88 = (ushort)bVar2;
          uStack_86 = 0;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_10018f150(uVar11);
          return;
        }
        lVar15 = param_1;
        FUN_1003c136c(param_1,uVar16,&uStack_68);
        if ((int)lVar15 != 0) {
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 != 0) {
            uStack_90 = (ushort)lVar15;
            uStack_8e = (undefined6)((ulong)lVar15 >> 0x10);
            uStack_88 = (ushort)bVar2;
            uStack_86 = 0;
            FUN_10000d120("Receive RPN with result %! on DLCI %d");
            uVar11 = 0x32;
            FUN_10000e9d4();
            uVar10 = uVar11;
            _os_log_type_enabled();
            if ((int)uVar10 != 0) {
              FUN_10018f150(uVar11);
            }
          }
          uStack_74 = 0x3f7f;
          bStack_72 = 7;
          bStack_71 = 3;
          uStack_70 = 0;
          uStack_6e = 0;
          uStack_6c = 0x1311;
          if ((bVar1 >> 1 & 1) == 0) {
            return;
          }
          FUN_1003c7288(param_1,0,uVar16,&uStack_74);
          if ((int)param_1 == 0) {
            return;
          }
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 == 0) {
            return;
          }
          uStack_90 = (ushort)param_1;
          uStack_8e = (undefined6)((ulong)param_1 >> 0x10);
          uStack_88 = (ushort)bVar2;
          uStack_86 = 0;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_10018f150(uVar11);
          return;
        }
        if ((bVar1 >> 1 & 1) != 0) {
          FUN_1003c7288(param_1,0,uVar16,CONCAT62(uStack_66,uStack_68) + 0x16);
          if ((int)param_1 == 0) {
            return;
          }
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 == 0) {
            return;
          }
          uStack_90 = (ushort)param_1;
          uStack_8e = (undefined6)((ulong)param_1 >> 0x10);
          uStack_88 = (ushort)bVar2;
          uStack_86 = 0;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_10018f150(uVar11);
          return;
        }
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 == 0) {
          return;
        }
        FUN_10000d120("Mux_ReceiveRPN, command is parameter report but C/R bit is not set, ignoring"
                     );
        uVar11 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_10018f150(uVar11);
        return;
      }
      bStack_5e = param_2[3];
      bVar4 = param_2[4];
      uVar19 = CONCAT16(bVar4,(uint6)CONCAT14(bVar4,(uint)CONCAT12(bVar4,(ushort)bVar4))) &
               _UNK_100934aa0;
      uStack_5d = (undefined1)uVar19;
      uStack_5c = (undefined1)(uVar19 >> 0x10);
      uStack_5b = (undefined1)(uVar19 >> 0x20);
      uStack_5a = (undefined1)(uVar19 >> 0x30);
      bStack_59 = param_2[5] & 0x3f;
      uStack_58 = (undefined1)*(undefined2 *)(param_2 + 6);
      uStack_57 = (undefined1)((ushort)*(undefined2 *)(param_2 + 6) >> 8);
      uStack_60 = *(ushort *)(param_2 + 8);
      lVar15 = param_1;
      FUN_1003c136c(param_1,uVar16,&uStack_68);
      if ((int)lVar15 == 0) {
        if ((bVar1 >> 1 & 1) == 0) {
          if (*(long *)(CONCAT62(uStack_66,uStack_68) + 0x40) != 0) {
            FUN_1003c6db8(param_1);
            lVar15 = CONCAT62(uStack_66,uStack_68);
            *(ulong *)(lVar15 + 0x16) =
                 CONCAT17(bStack_59,
                          CONCAT16(uStack_5a,
                                   CONCAT15(uStack_5b,
                                            CONCAT14(uStack_5c,
                                                     CONCAT13(uStack_5d,
                                                              CONCAT12(bStack_5e,uStack_60))))));
            *(ushort *)(lVar15 + 0x1e) = CONCAT11(uStack_57,uStack_58);
            (**(code **)(lVar15 + 0x40))(*(undefined2 *)(lVar15 + 8),&uStack_60);
            return;
          }
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 == 0) {
            return;
          }
          FUN_10000d120("Mux_ReceiveRPN, unsolicited response, ignoring");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_10018f150(uVar11);
          return;
        }
      }
      else {
        if ((bVar1 >> 1 & 1) == 0) {
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 == 0) {
            return;
          }
          uStack_90 = (ushort)lVar15;
          uStack_8e = (undefined6)((ulong)lVar15 >> 0x10);
          uStack_88 = (ushort)bVar2;
          uStack_86 = 0;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_10018f150(uVar11);
          return;
        }
        lVar15 = param_1;
        FUN_1003c1404(param_1,uVar16,&uStack_68);
        if ((int)lVar15 != 0) {
          iVar9 = 2;
          FUN_10000d938(2,0x32);
          if (iVar9 != 0) {
            uStack_90 = (ushort)lVar15;
            uStack_8e = (undefined6)((ulong)lVar15 >> 0x10);
            uStack_88 = (ushort)bVar2;
            uStack_86 = 0;
            FUN_10000d120("%! (%d)");
            uVar11 = 0x32;
            FUN_10000e9d4();
            uVar10 = uVar11;
            _os_log_type_enabled();
            if ((int)uVar10 != 0) {
              FUN_10018f150(uVar11);
            }
          }
          goto LAB_1003c80b8;
        }
      }
      pcVar8 = *(code **)(*(long *)(CONCAT62(uStack_66,uStack_68) + 0x28) + 0x20);
      if (pcVar8 != (code *)0x0) {
        (*pcVar8)(*(undefined2 *)(CONCAT62(uStack_66,uStack_68) + 8),&uStack_60);
      }
      if ((uStack_60 & 1) != 0) {
        *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x18) = bStack_5e;
      }
      if ((uStack_60 >> 1 & 1) != 0) {
        *(undefined1 *)(CONCAT62(uStack_66,uStack_68) + 0x19) = uStack_5d;
      }
      if ((uStack_60 >> 2 & 1) != 0) {
        *(undefined1 *)(CONCAT62(uStack_66,uStack_68) + 0x1a) = uStack_5c;
      }
      if ((uStack_60 >> 3 & 1) != 0) {
        *(undefined1 *)(CONCAT62(uStack_66,uStack_68) + 0x1b) = uStack_5b;
      }
      if ((uStack_60 >> 4 & 1) != 0) {
        *(undefined1 *)(CONCAT62(uStack_66,uStack_68) + 0x1c) = uStack_5a;
      }
      if ((uStack_60 >> 5 & 1) != 0) {
        *(undefined1 *)(CONCAT62(uStack_66,uStack_68) + 0x1e) = uStack_58;
      }
      if ((uStack_60 >> 6 & 1) != 0) {
        *(undefined1 *)(CONCAT62(uStack_66,uStack_68) + 0x1f) = uStack_57;
      }
      if ((uStack_60 >> 8 & 1) != 0) {
        *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) =
             *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) & 0xfe | bStack_59 & 1;
      }
      if ((uStack_60 >> 9 & 1) != 0) {
        *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) =
             *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) & 0xfd | bStack_59 & 2;
      }
      if ((uStack_60 >> 10 & 1) != 0) {
        *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) =
             *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) & 0xfb | bStack_59 & 4;
      }
      if ((uStack_60 >> 0xb & 1) != 0) {
        *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) =
             *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) & 0xf7 | bStack_59 & 8;
      }
      if ((uStack_60 >> 0xc & 1) != 0) {
        *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) =
             *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) & 0xef | bStack_59 & 0x10;
      }
      if ((uStack_60 >> 0xd & 1) != 0) {
        *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) =
             *(byte *)(CONCAT62(uStack_66,uStack_68) + 0x1d) & 0xdf | bStack_59 & 0x20;
      }
      FUN_1003c7288(param_1,0,uVar16,&uStack_60);
      if ((int)param_1 == 0) {
        return;
      }
      iVar9 = 2;
      FUN_10000d938(2,0x32);
      if (iVar9 == 0) {
        return;
      }
      uStack_90 = (ushort)param_1;
      uStack_8e = (undefined6)((ulong)param_1 >> 0x10);
      uStack_88 = 0;
      uStack_86 = 0;
      FUN_10000d120("%! (%d)");
      uVar11 = 0x32;
      FUN_10000e9d4();
      uVar10 = uVar11;
      _os_log_type_enabled();
      if ((int)uVar10 == 0) {
        return;
      }
      FUN_10018f150(uVar11);
      return;
    }
    goto LAB_1003c7750;
  }
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  uStack_60 = 0;
  bStack_5e = 0;
  uStack_5d = 0;
  uStack_5c = 0;
  uStack_5b = 0;
  uStack_5a = 0;
  bStack_59 = 0;
  if (uVar6 != 8) {
    iVar9 = 2;
    FUN_10000d938(2,0x32);
    if (iVar9 == 0) {
      return;
    }
    uStack_90 = (ushort)bVar4;
    uStack_8e = 0;
    uStack_88 = 8;
    uStack_86 = 0;
    FUN_10000d120("Mux_ReceivePN invalid cmdLen=%d, shall be=%d");
    uVar11 = 0x32;
    FUN_10000e9d4();
    uVar10 = uVar11;
    _os_log_type_enabled();
    if ((int)uVar10 == 0) {
      return;
    }
    FUN_10018f150(uVar11);
    return;
  }
  uVar16 = param_2[2] & 0x3f;
  if ((uVar16 == 1) || (0x3d < uVar16)) {
    iVar9 = 2;
    FUN_10000d938(2,0x32);
    if (iVar9 == 0) {
      return;
    }
    uStack_90 = 0x395;
    uStack_8e = 0;
    uStack_86 = 0;
    uStack_88 = uVar16;
    FUN_10000d120("%! (%d)");
    uVar11 = 0x32;
    FUN_10000e9d4();
    uVar10 = uVar11;
    _os_log_type_enabled();
    if ((int)uVar10 == 0) {
      return;
    }
    FUN_10018f150(uVar11);
    return;
  }
  bVar2 = *param_2;
  bVar1 = param_2[3];
  bVar4 = param_2[4];
  uVar5 = *(ushort *)(param_2 + 6);
  bVar3 = param_2[9];
  lVar15 = param_1;
  FUN_1003c136c(param_1,uVar16,&uStack_60);
  if ((int)lVar15 == 0) {
    if ((bVar2 >> 1 & 1) == 0) {
      if (*(char *)(CONCAT17(bStack_59,
                             CONCAT16(uStack_5a,
                                      CONCAT15(uStack_5b,
                                               CONCAT14(uStack_5c,
                                                        CONCAT13(uStack_5d,
                                                                 CONCAT12(bStack_5e,uStack_60))))))
                   + 0xd) != '\x01') {
        return;
      }
      bVar1 = bVar1 & 0xf0;
      FUN_1003c6db8(param_1);
      *(bool *)(param_1 + 0x2c) = bVar1 == 0xe0;
      lVar15 = CONCAT17(bStack_59,
                        CONCAT16(uStack_5a,
                                 CONCAT15(uStack_5b,
                                          CONCAT14(uStack_5c,
                                                   CONCAT13(uStack_5d,CONCAT12(bStack_5e,uStack_60))
                                                  ))));
      if (*(ushort *)(lVar15 + 0x10) < uVar5) {
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 != 0) {
          uStack_90 = 0x395;
          uStack_8e = 0;
          uStack_86 = 0;
          uStack_88 = uVar16;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 != 0) {
            FUN_10018f150(uVar11);
          }
        }
        iVar9 = 0x43;
        FUN_1003c5334(0x43,param_1,uVar16);
        if (iVar9 != 0) {
          return;
        }
        lVar15 = CONCAT17(bStack_59,
                          CONCAT16(uStack_5a,
                                   CONCAT15(uStack_5b,
                                            CONCAT14(uStack_5c,
                                                     CONCAT13(uStack_5d,
                                                              CONCAT12(bStack_5e,uStack_60))))));
        *(undefined4 *)(lVar15 + 0xa4) = 0x396;
        if (*(code **)(lVar15 + 0x48) != (code *)0x0) {
          (**(code **)(lVar15 + 0x48))(0,0,0x396);
          lVar15 = CONCAT17(bStack_59,
                            CONCAT16(uStack_5a,
                                     CONCAT15(uStack_5b,
                                              CONCAT14(uStack_5c,
                                                       CONCAT13(uStack_5d,
                                                                CONCAT12(bStack_5e,uStack_60))))));
        }
        FUN_1003c16dc(lVar15,1);
        if (*(char *)(param_1 + 0x2c) != '\x01') goto LAB_1003c8354;
        lVar15 = CONCAT17(bStack_59,
                          CONCAT16(uStack_5a,
                                   CONCAT15(uStack_5b,
                                            CONCAT14(uStack_5c,
                                                     CONCAT13(uStack_5d,
                                                              CONCAT12(bStack_5e,uStack_60))))));
      }
      else {
        *(ushort *)(lVar15 + 0x10) = uVar5;
        if (bVar1 != 0xe0) goto LAB_1003c8354;
      }
      *(ushort *)(lVar15 + 0x12) = bVar3 & 7;
LAB_1003c8354:
      iVar9 = 0x2f;
      FUN_1003c5334(0x2f,param_1,uVar16);
      if (iVar9 != 0) {
        return;
      }
      lVar15 = CONCAT17(bStack_59,
                        CONCAT16(uStack_5a,
                                 CONCAT15(uStack_5b,
                                          CONCAT14(uStack_5c,
                                                   CONCAT13(uStack_5d,CONCAT12(bStack_5e,uStack_60))
                                                  ))));
      if (lVar15 == 0) {
        FUN_1000f9438();
        lVar15 = CONCAT17(bStack_59,
                          CONCAT16(uStack_5a,
                                   CONCAT15(uStack_5b,
                                            CONCAT14(uStack_5c,
                                                     CONCAT13(uStack_5d,
                                                              CONCAT12(bStack_5e,uStack_60))))));
      }
      *(undefined1 *)(lVar15 + 0xd) = 2;
      return;
    }
  }
  else {
    if ((bVar2 >> 1 & 1) == 0) {
      iVar9 = 2;
      FUN_10000d938(2,0x32);
      if (iVar9 == 0) {
        return;
      }
      uStack_90 = (ushort)lVar15;
      uStack_8e = (undefined6)((ulong)lVar15 >> 0x10);
      uStack_86 = 0;
      uStack_88 = uVar16;
      FUN_10000d120("%! (%d)");
      uVar11 = 0x32;
      FUN_10000e9d4();
      uVar10 = uVar11;
      _os_log_type_enabled();
      if ((int)uVar10 == 0) {
        return;
      }
      FUN_10018f150(uVar11);
      return;
    }
    lVar15 = param_1;
    FUN_1003c1404(param_1,uVar16,&uStack_60);
    if ((int)lVar15 != 0) {
      iVar9 = 2;
      FUN_10000d938(2,0x32);
      if (iVar9 != 0) {
        uStack_90 = (ushort)lVar15;
        uStack_8e = (undefined6)((ulong)lVar15 >> 0x10);
        uStack_86 = 0;
        uStack_88 = uVar16;
        FUN_10000d120("%! (%d)");
        uVar11 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar11;
        _os_log_type_enabled();
        if ((int)uVar10 != 0) {
          FUN_10018f150(uVar11);
        }
      }
      goto LAB_1003c80b8;
    }
  }
  lVar15 = CONCAT17(bStack_59,
                    CONCAT16(uStack_5a,
                             CONCAT15(uStack_5b,
                                      CONCAT14(uStack_5c,
                                               CONCAT13(uStack_5d,CONCAT12(bStack_5e,uStack_60))))))
  ;
  if (*(char *)(lVar15 + 0xd) == '\0') {
    uVar14 = *(ushort *)(lVar15 + 0x10);
    if (uVar5 <= *(ushort *)(lVar15 + 0x10)) {
      *(ushort *)(lVar15 + 0x10) = uVar5;
      uVar14 = uVar5;
    }
    if (bVar1 < 0xf0) {
      uVar12 = 0;
      *(undefined1 *)(param_1 + 0x2c) = 0;
      *(undefined1 *)(lVar15 + 0xe) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x2c) = 1;
      *(ushort *)(lVar15 + 0x12) = bVar3 & 7;
      FUN_1003c4c88();
      if ((int)lVar15 != 0) {
        iVar9 = 2;
        FUN_10000d938(2,0x32);
        if (iVar9 != 0) {
          uStack_90 = (ushort)lVar15;
          uStack_8e = (undefined6)((ulong)lVar15 >> 0x10);
          uStack_86 = 0;
          uStack_88 = uVar16;
          FUN_10000d120("%! (%d)");
          uVar11 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar11;
          _os_log_type_enabled();
          if ((int)uVar10 != 0) {
            FUN_10018f150(uVar11);
          }
        }
        lVar15 = CONCAT17(bStack_59,
                          CONCAT16(uStack_5a,
                                   CONCAT15(uStack_5b,
                                            CONCAT14(uStack_5c,
                                                     CONCAT13(uStack_5d,
                                                              CONCAT12(bStack_5e,uStack_60))))));
        if (lVar15 == 0) {
          FUN_1000f9438();
          lVar15 = CONCAT17(bStack_59,
                            CONCAT16(uStack_5a,
                                     CONCAT15(uStack_5b,
                                              CONCAT14(uStack_5c,
                                                       CONCAT13(uStack_5d,
                                                                CONCAT12(bStack_5e,uStack_60))))));
        }
        *(undefined1 *)(lVar15 + 0xd) = 9;
LAB_1003c80b8:
        FUN_1003c5334(0xf,param_1,uVar16);
        return;
      }
      lVar15 = CONCAT17(bStack_59,
                        CONCAT16(uStack_5a,
                                 CONCAT15(uStack_5b,
                                          CONCAT14(uStack_5c,
                                                   CONCAT13(uStack_5d,CONCAT12(bStack_5e,uStack_60))
                                                  ))));
      uVar14 = *(ushort *)(lVar15 + 0x10);
      uVar12 = *(undefined1 *)(lVar15 + 0xe);
    }
  }
  else {
    uVar12 = 0;
    uVar14 = uVar5;
  }
  FUN_1003c6e30(param_1,0,uVar16,bVar4 & 0x3f,uVar14,uVar12);
  return;
}


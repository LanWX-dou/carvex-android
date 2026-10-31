/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003c59a0
 * original code SHA256: c43f625016a371b2ac6e22822acf3b6d0f6b99fc4ade9d27a8c836547d40c689
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_1003c59a0(char *param_1,byte *param_2,uint param_3)

{
  ushort uVar1;
  short sVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;
  undefined2 uVar6;
  code *pcVar7;
  int iVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  char *pcVar11;
  long lVar12;
  uint uVar13;
  uint uVar14;
  ulong uVar15;
  char *pcVar16;
  char *pcVar17;
  ushort uVar18;
  ulong unaff_x30;
  ulong uStack_58;
  
  FUN_1003c18a4();
  if (param_1 == (char *)0x0) {
    iVar8 = 2;
    FUN_10000d938(2,0x32);
    if (iVar8 == 0) {
      return;
    }
    FUN_10000d120("No session found with CID %d");
    uVar9 = 0x32;
    FUN_10000e9d4();
    uVar10 = uVar9;
    _os_log_type_enabled();
    if ((int)uVar10 == 0) {
      return;
    }
    FUN_100105b50(uVar9);
    return;
  }
  if (param_3 < 4) {
    iVar8 = 2;
    FUN_10000d938(2,0x32);
    if (iVar8 == 0) {
      return;
    }
    FUN_10000d120("OI_Rfcomm_ReceiveFrame invalid frame length=%d");
    uVar9 = 0x32;
    FUN_10000e9d4();
    uVar10 = uVar9;
    _os_log_type_enabled();
    if ((int)uVar10 == 0) {
      return;
    }
    FUN_100105b50(uVar9);
    return;
  }
  bVar3 = param_2[1];
  uVar14 = bVar3 & 0xffffffef;
  if (0x34 < uVar14 - 0x2f || (1L << ((ulong)(uVar14 - 0x2f) & 0x3f) & 0x10000000100001U) == 0) {
    if (uVar14 == 0xef) {
      uVar14 = (uint)*param_2;
      FUN_1003c6be4(*param_2,bVar3,param_2[param_3 - 1]);
      if (uVar14 != 0) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("UIH FCS Error: %@");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003c5c14);
        (*pcVar7)();
      }
      uStack_58 = 0;
      bVar3 = *param_2;
      if ((bVar3 & 1) == 0) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("%! (%d)");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
      if (param_1[0xc] == '\x01') {
        if ((bVar3 >> 1 & 1) != 0) {
          iVar8 = 2;
          FUN_10000d938(2,0x32);
          if (iVar8 == 0) {
            return;
          }
          FUN_10000d120("%! (%d)");
          uVar9 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar9;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_100105b50(uVar9);
          return;
        }
      }
      else if ((bVar3 >> 1 & 1) == 0) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("%! (%d)");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
      bVar5 = param_2[2];
      if ((bVar5 & 1) == 0) {
        uVar14 = (uint)(ushort)(CONCAT11(param_2[3],bVar5) >> 1);
        lVar12 = 4;
      }
      else {
        uVar14 = (uint)(bVar5 >> 1);
        lVar12 = 3;
      }
      uVar13 = (uint)lVar12;
      bVar5 = param_2[1];
      if ((bVar5 >> 4 & 1) == 0) {
        uVar18 = 0;
      }
      else {
        if (param_1[0x2c] != '\x01') {
          iVar8 = 2;
          FUN_10000d938(2,0x32);
          if (iVar8 == 0) {
            return;
          }
          FUN_10000d120("%! (%d)");
          uVar9 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar9;
          _os_log_type_enabled();
          if ((int)uVar10 == 0) {
            return;
          }
          FUN_100105b50(uVar9);
          return;
        }
        uVar18 = (ushort)param_2[lVar12];
        uVar13 = uVar13 + 1;
      }
      if (uVar14 + uVar13 + 1 != param_3) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("%! (%d)");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
      if (*param_1 != '\a') {
        return;
      }
      if ((0xf7 < bVar3) || (bVar3 >> 2 == 1)) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("%! (%d)");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
      param_2 = param_2 + uVar13;
      if (bVar3 < 4) {
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003c681c);
          (*pcVar7)();
        }
        FUN_1003c73f0(param_1,param_2,uVar14);
        return;
      }
      pcVar16 = param_1;
      FUN_1003c136c(param_1,bVar3 >> 2,&uStack_58);
      if ((int)pcVar16 != 0) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("%! (%d)");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
      if (param_1[0x2c] == '\x01') {
        if (((bVar5 >> 4 & 1) != 0) && (uVar18 != 0)) {
          if ((*(ushort *)(uStack_58 + 0x12) ^ 0xffff) <= uVar18) {
            iVar8 = 2;
            FUN_10000d938(2,0x32);
            if (iVar8 != 0) {
              FUN_10000d120("%! (%d)");
              uVar9 = 0x32;
              FUN_10000e9d4();
              uVar10 = uVar9;
              _os_log_type_enabled();
              if ((int)uVar10 != 0) {
                FUN_100105b50(uVar9);
              }
            }
            FUN_1003c31b4(*(undefined2 *)(uStack_58 + 8),0x39a);
            return;
          }
          uVar1 = *(ushort *)(uStack_58 + 0x12) + uVar18;
          *(ushort *)(uStack_58 + 0x12) = uVar1;
          if (uVar18 == uVar1) {
            FUN_1003c50a8();
          }
        }
        if (uVar14 != 0) {
          if (*(char *)(uStack_58 + 0xe) == '\0') {
            iVar8 = 2;
            FUN_10000d938(2,0x32);
            if (iVar8 != 0) {
              FUN_10000d120("Received data when remote credits = 0!");
              uVar9 = 0x32;
              FUN_10000e9d4();
              uVar10 = uVar9;
              _os_log_type_enabled();
              if ((int)uVar10 != 0) {
                FUN_100105b50(uVar9);
              }
            }
          }
          else {
            *(char *)(uStack_58 + 0xe) = *(char *)(uStack_58 + 0xe) + -1;
          }
          goto LAB_1003c6a48;
        }
        if ((*(byte *)(uStack_58 + 0x21) & 1) != 0) {
          return;
        }
        if (param_1[0x2c] != '\x01') {
          return;
        }
LAB_1003c6aa0:
        uVar15 = uStack_58;
        FUN_1003c4edc(uStack_58,param_2,uVar14);
        if ((int)uVar15 != 0) {
          iVar8 = 2;
          FUN_10000d938(2,0x32);
          if (iVar8 != 0) {
            FUN_10000d120("Save received packet failed in Receive_UIH %! (%d)");
            uVar9 = 0x32;
            FUN_10000e9d4();
            uVar10 = uVar9;
            _os_log_type_enabled();
            if ((int)uVar10 != 0) {
              FUN_100105b50(uVar9);
            }
          }
        }
      }
      else {
LAB_1003c6a48:
        if ((*(byte *)(uStack_58 + 0x21) & 1) == 0) {
          if ((param_1[0x2c] & 1U) != 0) goto LAB_1003c6aa0;
          if (uVar14 == 0) {
            return;
          }
        }
        else {
          if (uVar14 == 0) {
            return;
          }
          if ((param_1[0x2c] == '\x01') &&
             (bVar3 = *(byte *)(uStack_58 + 0xe), bVar3 <= *(byte *)(lRam0000000100cadd68 + 2))) {
            if (*(char *)(uStack_58 + 0xa2) == '\0') {
              bVar3 = ~bVar3;
            }
            else {
              bVar3 = *(char *)(uStack_58 + 0xa2) - (bVar3 + *(char *)(uStack_58 + 0xa3));
            }
            uVar15 = uStack_58;
            FUN_1003c5030(uStack_58,bVar3);
            if ((int)uVar15 != 0) {
              return;
            }
          }
        }
        (**(code **)(*(long *)(uStack_58 + 0x28) + 8))
                  (*(undefined2 *)(uStack_58 + 8),param_2,uVar14);
      }
      return;
    }
    if (uVar14 != 0xf) {
      return;
    }
  }
  uVar13 = (uint)*param_2;
  FUN_1003c6ba4(*param_2,bVar3,param_2[2],param_2[param_3 - 1]);
  if (uVar13 != 0) {
    iVar8 = 2;
    FUN_10000d938(2,0x32);
    if (iVar8 != 0) {
      FUN_10000d120("FCS Error: %@");
      uVar9 = 0x32;
      FUN_10000e9d4();
      uVar10 = uVar9;
      _os_log_type_enabled();
      if ((int)uVar10 != 0) {
        FUN_100105b50(uVar9);
      }
    }
    return;
  }
  if (0x42 < uVar14) {
    if (uVar14 == 0x43) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003c5c6c);
        (*pcVar7)();
      }
      bVar3 = *param_2;
      if (((bVar3 & 1) != 0) && ((param_2[1] >> 4 & 1) != 0)) {
        if (((bVar3 & 2) == 0) == (bool)param_1[0xc]) {
          bVar5 = bVar3 >> 2;
          if (bVar3 < 0xf8 && bVar5 != 1) {
            if (*param_1 == '\a') {
              if (3 < bVar3) {
                pcVar16 = param_1;
                FUN_1003c136c(param_1,bVar5,&stack0xffffffffffffffd8);
                if ((int)pcVar16 != 0) {
                  iVar8 = 2;
                  FUN_10000d938(2,0x32);
                  if (iVar8 == 0) {
                    return;
                  }
                  FUN_10000d120("DLCI %d not found");
                  uVar9 = 0x32;
                  FUN_10000e9d4();
                  uVar10 = uVar9;
                  _os_log_type_enabled();
                  if ((int)uVar10 == 0) {
                    return;
                  }
                  FUN_100105b50(uVar9);
                  return;
                }
                iVar8 = 99;
                FUN_1003c5334(99,param_1,bVar5);
                pcVar7 = pcRam0000000000000048;
                uVar6 = uRam0000000000000008;
                if (bRam000000000000000d == 6) {
                  return;
                }
                if (bRam000000000000000d == 5) {
                  bRam000000000000000d = 7;
                  if (iVar8 == 0) {
                    bRam000000000000000d = 7;
                    return;
                  }
                  iVar8 = 2;
                  FUN_10000d938(2,0x32);
                  if (iVar8 != 0) {
                    FUN_10000d120("RFCOMM send command failed with result : %!");
                    uVar9 = 0x32;
                    FUN_10000e9d4();
                    uVar10 = uVar9;
                    _os_log_type_enabled();
                    if ((int)uVar10 != 0) {
                      FUN_100105b50(uVar9);
                    }
                  }
                  uRam00000000000000a4 = 0x3a5;
                  FUN_1003c52cc(0,0);
                  return;
                }
                if (pcRam0000000000000048 == (code *)0x0) {
                  return;
                }
                bRam000000000000000d = 8;
                if (iVar8 == 0) {
                  bRam000000000000000d = 8;
                  return;
                }
                FUN_1003c16dc(0,0);
                (*pcVar7)(uVar6,0,0x39f);
                return;
              }
              lVar12 = 0x32;
              FUN_1003d7a1c();
              sVar2 = 0x1e;
              if (*(short *)(lVar12 + 10) != 0) {
                sVar2 = *(short *)(lVar12 + 10);
              }
              *param_1 = '\b';
              FUN_1003c518c(param_1,sVar2);
            }
            if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
              pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003c62d4);
              (*pcVar7)();
            }
            FUN_1003c5334(99,param_1,bVar5);
            return;
          }
          iVar8 = 2;
          FUN_10000d938(2,0x32);
          if (iVar8 != 0) {
            FUN_10000d120("%! (%d)");
            uVar9 = 0x32;
            FUN_10000e9d4();
            uVar10 = uVar9;
            _os_log_type_enabled();
            if ((int)uVar10 != 0) {
              FUN_100105b50(uVar9);
            }
          }
        }
        else {
          iVar8 = 2;
          FUN_10000d938(2,0x32);
          if (iVar8 != 0) {
            FUN_10000d120("%! (%d)");
            uVar9 = 0x32;
            FUN_10000e9d4();
            uVar10 = uVar9;
            _os_log_type_enabled();
            if ((int)uVar10 != 0) {
              FUN_100105b50(uVar9);
            }
          }
        }
      }
      return;
    }
    if (uVar14 != 99) {
      return;
    }
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003c5bd0);
      (*pcVar7)();
    }
    FUN_1003c6d7c();
    bVar3 = *param_2;
    if ((bVar3 & 1) == 0) {
      return;
    }
    if ((param_2[1] >> 4 & 1) == 0) {
      return;
    }
    if (((bVar3 & 2) == 0) == (bool)param_1[0xc]) {
      return;
    }
    uVar15 = (ulong)(uint)(bVar3 >> 2);
    cVar4 = *param_1;
    uStack_58 = uVar15;
    if (cVar4 == '\t') {
      if (bVar3 < 4) {
        uVar15 = (ulong)*(ushort *)(param_1 + 2);
        FUN_10036b5bc(uVar15,0x230);
        if ((int)uVar15 == 0) {
          *param_1 = '\n';
          return;
        }
        if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003c601c);
          (*pcVar7)();
        }
        FUN_1003c1a34(param_1,uVar15,1);
        return;
      }
      FUN_1003c136c(param_1,uVar15,&stack0xffffffffffffffb8);
      if ((int)param_1 != 0) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("%! (%d)");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
    }
    else {
      if (cVar4 != '\a') {
        if (cVar4 != '\x05') {
          return;
        }
        if (3 < bVar3) {
          return;
        }
        *param_1 = '\a';
        param_1 = param_1 + 0x10;
        pcVar16 = *(char **)param_1;
        if (pcVar16 == (char *)0x0) {
          return;
        }
        if (pcVar16 == param_1) {
          return;
        }
        do {
          pcVar11 = pcVar16 + -0x90;
          FUN_1003c20b8();
          pcVar17 = pcVar16;
          if ((int)pcVar11 != 0) {
            pcVar17 = *(char **)(pcVar16 + 8);
            (**(code **)(pcVar16 + -0x48))(*(undefined2 *)(pcVar16 + -0x88),0,pcVar11);
            *(int *)(pcVar16 + 0x14) = (int)pcVar11;
            FUN_1003c16dc(pcVar16 + -0x90,1);
          }
          pcVar16 = *(char **)pcVar17;
        } while (pcVar16 != (char *)0x0 && pcVar16 != param_1);
        return;
      }
      if ((bVar3 >> 2 == 1) || ((byte)(bVar3 + 8) < 0xc)) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("%! (%d)");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
      pcVar16 = param_1;
      FUN_1003c136c(param_1,uVar15,&stack0xffffffffffffffb8);
      if ((int)pcVar16 != 0) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        FUN_10000d120("Link %d does not exist");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_1008b4ec0(uVar9);
        return;
      }
      if (bRam000000000000000d != 6) {
        if (bRam000000000000000d == 2) {
          bRam000000000000000d = 4;
          FUN_1003c71e8(param_1,1,uVar15,uRam000000000000000c,0);
          return;
        }
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 == 0) {
          return;
        }
        uStack_58 = (ulong)bRam000000000000000d;
        FUN_10000d120("%! (%d)");
        uVar9 = 0x32;
        FUN_10000e9d4();
        uVar10 = uVar9;
        _os_log_type_enabled();
        if ((int)uVar10 == 0) {
          return;
        }
        FUN_100105b50(uVar9);
        return;
      }
    }
    FUN_1003c52cc(0,1);
    return;
  }
  if (uVar14 != 0xf) {
    if (uVar14 != 0x2f) {
      return;
    }
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003c5b3c);
      (*pcVar7)();
    }
    bVar3 = *param_2;
    if ((bVar3 & 1) == 0) {
      return;
    }
    if ((param_2[1] >> 4 & 1) == 0) {
      return;
    }
    if ((((bVar3 & 2) == 0 ^ param_1[0xc]) & 1U) != 0) {
      return;
    }
    bVar5 = bVar3 >> 2;
    if (*param_1 == '\a') {
      if ((bVar3 < 0xf8) && (bVar5 != 1)) {
        pcVar16 = param_1;
        FUN_1003c136c(param_1,bVar5,&stack0xffffffffffffffc8);
        if ((int)pcVar16 == 0) {
          if (bRam000000000000000d == 6) goto LAB_1003c5e50;
        }
        else {
          pcVar16 = param_1;
          FUN_1003c1404(param_1,bVar5,&stack0xffffffffffffffc8);
          if ((int)pcVar16 != 0) {
            iVar8 = 2;
            FUN_10000d938(2,0x32);
            if (iVar8 != 0) {
              FUN_10000d120("%! (%d)");
              uVar9 = 0x32;
              FUN_10000e9d4();
              uVar10 = uVar9;
              _os_log_type_enabled();
              if ((int)uVar10 != 0) {
                FUN_100105b50(uVar9);
              }
            }
            goto LAB_1003c5e50;
          }
          FUN_1000f9438();
        }
        bRam000000000000000d = 3;
        pcVar16 = param_1 + 6;
        bRam000000000000000a = bVar5;
        FUN_1003c2314(pcVar16,bVar3 >> 3,uRam0000000000000010,uRam0000000000000008);
        if ((int)pcVar16 == 0) {
          return;
        }
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 != 0) {
          FUN_10000d120("No registered server on DLCI %d, rejecting incoming link");
          uVar9 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar9;
          _os_log_type_enabled();
          if ((int)uVar10 != 0) {
            FUN_1008b4ec0(uVar9);
          }
        }
        uRam00000000000000a4 = 0x399;
        FUN_1003c16dc(0,0);
      }
      else {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 != 0) {
          FUN_10000d120("%! (%d)");
          uVar9 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar9;
          _os_log_type_enabled();
          if ((int)uVar10 != 0) {
            FUN_100105b50(uVar9);
          }
        }
      }
    }
    else if ((*param_1 == '\x04') && (bVar3 < 4)) {
      iVar8 = 99;
      FUN_1003c5334(99,param_1,bVar5);
      if (iVar8 != 0) {
        return;
      }
      *param_1 = '\a';
      return;
    }
LAB_1003c5e50:
    FUN_1003c5334(0xf,param_1,bVar5);
    return;
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar7 = (code *)SoftwareBreakpoint(0xc471,0x1003c5c40);
    (*pcVar7)();
  }
  bVar3 = *param_2;
  if ((bVar3 & 1) == 0) {
    return;
  }
  if (((bVar3 & 2) == 0) == (bool)param_1[0xc]) {
    return;
  }
  uVar14 = (uint)(bVar3 >> 2);
  pcVar16 = param_1;
  FUN_1003c136c(param_1,(ulong)uVar14,&stack0xffffffffffffffb8);
  if ((int)pcVar16 != 0) {
    iVar8 = 2;
    FUN_10000d938(2,0x32);
    if (iVar8 == 0) {
      return;
    }
    uStack_58 = (ulong)uVar14;
    FUN_10000d120("%! (%d)");
    uVar9 = 0x32;
    FUN_10000e9d4();
    uVar10 = uVar9;
    _os_log_type_enabled();
    if ((int)uVar10 == 0) {
      return;
    }
    FUN_100105b50(uVar9);
    return;
  }
  if (((param_2[1] >> 4 & 1) == 0) && ((bRam000000000000000d | 4) == 6)) {
    return;
  }
  if (*param_1 != '\a') {
    if (*param_1 == '\x05') {
      FUN_1003c6d7c(param_1);
      FUN_1003c1788(param_1,0,0x3a1);
      return;
    }
    iVar8 = 2;
    FUN_10000d938(2,0x32);
    if (iVar8 == 0) {
      return;
    }
    FUN_10000d120("Unexpected DM received");
    uVar9 = 0x32;
    FUN_10000e9d4();
    uVar10 = uVar9;
    _os_log_type_enabled();
    if ((int)uVar10 == 0) {
      return;
    }
    FUN_100105b50(uVar9);
    return;
  }
  if (uVar14 == 1) {
    return;
  }
  if ((byte)(bVar3 + 8) < 0xc) {
    return;
  }
  if ((bRam000000000000000d | 4) == 6) {
    FUN_1003c6d7c();
  }
  else {
    FUN_1003c6db8(param_1);
  }
  uVar14 = (uint)bRam000000000000000d;
  if (bRam000000000000000d < 10) {
    uVar13 = 1 << (ulong)(uVar14 & 0x1f);
    if ((uVar13 & 0x38) == 0) {
      if ((uVar13 & 0x180) == 0) {
        if ((1 << (ulong)(uVar14 & 0x1f) & 0x240U) == 0) goto LAB_1003c65a0;
      }
      else {
        uRam00000000000000a4 = 0x39f;
      }
    }
    else {
      uRam00000000000000a4 = 0x3a6;
    }
    FUN_1003c52cc(0,1);
  }
  else {
LAB_1003c65a0:
    if (uVar14 < 3) {
      if (pcRam0000000000000048 == (code *)0x0) {
        iVar8 = 2;
        FUN_10000d938(2,0x32);
        if (iVar8 != 0) {
          FUN_10000d120("Received unsolicited remote reject, ignore");
          uVar9 = 0x32;
          FUN_10000e9d4();
          uVar10 = uVar9;
          _os_log_type_enabled();
          if ((int)uVar10 != 0) {
            FUN_100105b50(uVar9);
          }
        }
      }
      else {
        uRam00000000000000a4 = 0x3a6;
        (*pcRam0000000000000048)(uRam0000000000000008,0,0x391);
        FUN_1003c16dc(0,1);
      }
    }
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be49060
 * original code SHA256: 67c1337427d5463e64978ebba462e58f5c54825e27d9803de04f74de4422f3e6
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _HTTPMessageReadMessageEx(long param_1,code *param_2,undefined8 param_3)

{
  long lVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  ulong uVar7;
  long lVar8;
  uint *puVar9;
  int *piVar10;
  char *pcVar11;
  char *pcVar12;
  undefined4 uVar13;
  ulong uVar14;
  ulong uVar15;
  byte *pbVar16;
  byte bVar17;
  byte *pbVar18;
  ulong local_88;
  ulong local_80;
  ulong local_78;
  long local_70;
  byte *local_68;
  
  local_88 = 0;
  if (*(char *)(param_1 + 0x2138) == '\0') {
    uVar7 = _HTTPReadHeader(param_1 + 0x18,param_2,param_3);
    if ((int)uVar7 != 0) {
      return uVar7;
    }
    *(char *)(param_1 + 0x2138) = '\x01';
    if (*(long *)(param_1 + 0x2610) != 0) {
      if (-1 < *(int *)(param_1 + 0x2618)) {
        iVar6 = func_0x0001900cf930();
        if ((iVar6 != 0) && (piVar10 = (int *)func_0x0001900ce930(), *piVar10 != 0)) {
          func_0x0001900ce930();
        }
        *(undefined4 *)(param_1 + 0x2618) = 0xffffffff;
      }
      do {
        iVar6 = func_0x0001900cfef0(*(undefined8 *)(param_1 + 0x2610),0x602);
        *(int *)(param_1 + 0x2618) = iVar6;
        if (-1 < iVar6) goto LAB_18be49438;
        piVar10 = (int *)func_0x0001900ce930();
        if (*piVar10 == 0) {
          return 0xffffe5d4;
        }
        puVar9 = (uint *)func_0x0001900ce930();
        uVar5 = *puVar9;
      } while (uVar5 == 4);
      if (uVar5 != 0) {
        return (ulong)uVar5;
      }
    }
LAB_18be49438:
    lVar8 = *(long *)(param_1 + 0x2018);
    if (lVar8 == -1) {
      lVar8 = func_0x0001900d0320(param_1 + 0x18);
    }
    local_70 = 0;
    local_68 = (byte *)0x0;
    iVar6 = _HTTPGetHeaderField(param_1 + 0x18,lVar8,"Transfer-Encoding",0,0,&local_68,&local_70,0);
    lVar8 = _DAT_1e016af20;
    if ((iVar6 == 0) && (pbVar2 = local_68 + local_70, local_70 != 0)) {
      bVar17 = 0;
      local_78 = local_78 & 0xffffffffffffff00;
      pbVar3 = local_68 + local_70;
      lVar1 = _DAT_1e016af20 + 0x3c;
LAB_18be494ac:
      pbVar16 = local_68;
      if (local_68 < pbVar2) {
        do {
          bVar4 = *pbVar16;
          if ((long)(char)bVar4 < 0) {
            uVar5 = func_0x0001900ce950(bVar4,0x4000);
          }
          else {
            uVar5 = *(uint *)(lVar1 + (long)(char)bVar4 * 4) & 0x4000;
          }
        } while ((uVar5 != 0) && (pbVar16 = pbVar16 + 1, pbVar16 != pbVar3));
      }
      pbVar18 = pbVar16;
      local_68 = pbVar16;
      if (pbVar16 < pbVar2) {
        while ((bVar17 = *pbVar18, bVar17 != 0x2c && (bVar17 != 0x3b))) {
          if ((char)bVar17 < '\0') {
            uVar5 = func_0x0001900ce950(bVar17,0x4000);
          }
          else {
            uVar5 = *(uint *)(lVar8 + 0x3c + (ulong)bVar17 * 4) & 0x4000;
          }
          if ((uVar5 != 0) || (pbVar18 = pbVar18 + 1, pbVar18 == pbVar3)) break;
        }
      }
      local_78 = CONCAT71(local_78._1_7_,bVar17);
      local_68 = pbVar18;
      iVar6 = _strnicmpx(pbVar16,(long)pbVar18 - (long)pbVar16,"chunked");
      if (iVar6 != 0) {
        pbVar16 = pbVar18;
        if (pbVar18 < pbVar2) {
          do {
            bVar4 = *pbVar18;
            if ((long)(char)bVar4 < 0) {
              uVar5 = func_0x0001900ce950(bVar4,0x4000);
            }
            else {
              uVar5 = *(uint *)(lVar8 + 0x3c + (long)(char)bVar4 * 4) & 0x4000;
            }
            if (uVar5 == 0) {
              pbVar16 = pbVar18;
              if (*pbVar18 == 0x3b) {
                local_68 = pbVar18 + 1;
                goto LAB_18be49604;
              }
              break;
            }
            pbVar18 = pbVar18 + 1;
            pbVar16 = pbVar3;
          } while (pbVar18 != pbVar3);
        }
        goto LAB_18be495bc;
      }
      *(undefined4 *)(param_1 + 0x213c) = 1;
      goto LAB_18be490a4;
    }
LAB_18be49728:
    *(undefined4 *)(param_1 + 0x213c) = 0;
    uVar7 = *(ulong *)(param_1 + 0x2128);
    if (*(int *)(param_1 + 0x2618) < 0) {
      if (*(ulong *)(param_1 + 0x2158) < uVar7) {
        if ((_gLogCategory_HTTPMessage < 0x5b) &&
           ((_gLogCategory_HTTPMessage != -1 ||
            (iVar6 = __LogCategory_Initialize(&_gLogCategory_HTTPMessage,0x5a), iVar6 != 0)))) {
          pcVar11 = "OSStatus HTTPMessageReadMessageEx(HTTPMessageRef, NetTransportRead_f, void *)";
          pcVar12 = "### Bad content length: %llu vs %zu";
LAB_18be498bc:
          _LogPrintF_safe(&_gLogCategory_HTTPMessage,pcVar11,0x5a,pcVar12);
        }
        return 0xffffe5a9;
      }
    }
    else {
      *(ulong *)(param_1 + 0x2620) = uVar7;
      if (0xfffff < uVar7) {
        uVar7 = 0x100000;
      }
      *(ulong *)(param_1 + 0x2158) = uVar7;
    }
    local_88 = uVar7;
    uVar7 = _HTTPMessageSetBodyLength(param_1);
    if ((int)uVar7 != 0) {
      return uVar7;
    }
  }
LAB_18be490a4:
  iVar6 = *(int *)(param_1 + 0x213c);
  if (iVar6 != 0) {
    local_70 = 0;
    local_68 = (byte *)0x0;
    local_78 = 0;
    do {
      if (iVar6 < 3) {
        if (iVar6 == 1) {
          local_80 = 0;
          uVar7 = _HTTPReadLine(param_1 + 0x18,param_2,param_3,&local_68,&local_70);
          if ((int)uVar7 != 0) {
            return uVar7;
          }
          iVar6 = _SNScanF(local_68,local_70,"%llx");
          uVar7 = local_80;
          if (iVar6 != 1) {
            return 0xffffe5aa;
          }
          if (local_80 == 0) {
            uVar13 = 4;
          }
          else if (*(int *)(param_1 + 0x2618) < 0) {
            uVar7 = *(ulong *)(param_1 + 0x2150) + local_80;
            if (uVar7 <= *(ulong *)(param_1 + 0x2150)) {
              if (0x5a < _gLogCategory_HTTPMessage) {
                return 0xffffe5a9;
              }
              if ((_gLogCategory_HTTPMessage == -1) &&
                 (iVar6 = __LogCategory_Initialize(&_gLogCategory_HTTPMessage,0x5a), iVar6 == 0)) {
                return 0xffffe5a9;
              }
              pcVar11 = "OSStatus _HTTPMessageProcessChunkHeader(HTTPMessageRef, uint64_t)";
              pcVar12 = "### Bad chunk wrap: %zu vs %zu";
              goto LAB_18be498bc;
            }
            if (*(ulong *)(param_1 + 0x2158) < uVar7) {
              if (0x5a < _gLogCategory_HTTPMessage) {
                return 0xffffe5a9;
              }
              if ((_gLogCategory_HTTPMessage == -1) &&
                 (iVar6 = __LogCategory_Initialize(&_gLogCategory_HTTPMessage,0x5a), iVar6 == 0)) {
                return 0xffffe5a9;
              }
              pcVar11 = "OSStatus _HTTPMessageProcessChunkHeader(HTTPMessageRef, uint64_t)";
              pcVar12 = "### Chunked body too large: %zu vs %zu";
              goto LAB_18be498bc;
            }
            lVar8 = param_1 + 0x2168;
            if (1000 < uVar7) {
              lVar8 = func_0x0001900cfd80(*(undefined8 *)(param_1 + 0x2550),uVar7,0x100004077774924)
              ;
              if (lVar8 == 0) {
                return 0xffffe5b8;
              }
              if ((*(long *)(param_1 + 0x2550) == 0) && (*(long *)(param_1 + 0x2160) != 0)) {
                func_0x0001900cc490(lVar8,*(undefined8 *)(param_1 + 0x2148));
              }
              *(long *)(param_1 + 0x2550) = lVar8;
            }
            *(long *)(param_1 + 0x2148) = lVar8;
            *(ulong *)(param_1 + 0x2150) = uVar7;
            uVar13 = 2;
          }
          else {
            uVar14 = local_80;
            if (0xfffff < local_80) {
              uVar14 = 0x100000;
            }
            if (*(ulong *)(param_1 + 0x2158) < uVar14) {
              uVar15 = _HTTPMessageSetBodyLength(param_1,uVar14);
              if ((int)uVar15 != 0) {
                return uVar15;
              }
              *(ulong *)(param_1 + 0x2158) = uVar14;
            }
            *(ulong *)(param_1 + 0x2620) = uVar7;
            uVar13 = 2;
          }
LAB_18be493a4:
          *(undefined4 *)(param_1 + 0x213c) = uVar13;
        }
        else {
          if (iVar6 != 2) {
            return 0xffffe5cb;
          }
          uVar7 = *(ulong *)(param_1 + 0x2028);
          if (*(int *)(param_1 + 0x2618) < 0) {
            uVar14 = *(ulong *)(param_1 + 0x2160);
            uVar15 = *(ulong *)(param_1 + 0x2150);
            if (uVar7 != 0) {
              local_78 = uVar15 - uVar14;
              if (uVar7 <= uVar15 - uVar14) {
                local_78 = uVar7;
              }
              func_0x0001900cc490(*(long *)(param_1 + 0x2148) + uVar14,
                                  *(undefined8 *)(param_1 + 0x2020));
              *(ulong *)(param_1 + 0x2020) = *(long *)(param_1 + 0x2020) + local_78;
              *(ulong *)(param_1 + 0x2028) = *(long *)(param_1 + 0x2028) - local_78;
              uVar14 = *(long *)(param_1 + 0x2160) + local_78;
              *(ulong *)(param_1 + 0x2160) = uVar14;
              uVar15 = *(ulong *)(param_1 + 0x2150);
            }
            local_78 = uVar14;
            if (uVar14 <= uVar15 && uVar15 - uVar14 != 0) {
              uVar7 = (*param_2)(*(long *)(param_1 + 0x2148) + uVar14,uVar15 - uVar14,&local_78,
                                 param_3);
              if ((int)uVar7 != 0) {
                return uVar7;
              }
              uVar14 = *(long *)(param_1 + 0x2160) + local_78;
              *(ulong *)(param_1 + 0x2160) = uVar14;
              uVar15 = *(ulong *)(param_1 + 0x2150);
            }
            if (uVar14 != uVar15) goto LAB_18be493a8;
          }
          else {
            uVar14 = *(ulong *)(param_1 + 0x2620);
            if (uVar7 != 0) {
              if (uVar14 == 0) goto LAB_18be49318;
              local_78 = uVar7;
              if (uVar14 <= uVar7) {
                local_78 = uVar14;
              }
              uVar7 = _FDWriteAll(*(int *)(param_1 + 0x2618),*(undefined8 *)(param_1 + 0x2020));
              if ((int)uVar7 != 0) {
                return uVar7;
              }
              *(ulong *)(param_1 + 0x2020) = *(long *)(param_1 + 0x2020) + local_78;
              *(ulong *)(param_1 + 0x2028) = *(long *)(param_1 + 0x2028) - local_78;
              uVar14 = *(long *)(param_1 + 0x2620) - local_78;
              *(ulong *)(param_1 + 0x2620) = uVar14;
            }
            if (uVar14 != 0) {
              local_78 = *(ulong *)(param_1 + 0x2158);
              if (uVar14 <= *(ulong *)(param_1 + 0x2158)) {
                local_78 = uVar14;
              }
              uVar7 = (*param_2)(*(undefined8 *)(param_1 + 0x2148),local_78,&local_78,param_3);
              if ((int)uVar7 != 0) {
                return uVar7;
              }
              uVar7 = _FDWriteAll(*(undefined4 *)(param_1 + 0x2618),
                                  *(undefined8 *)(param_1 + 0x2148),local_78);
              if ((int)uVar7 != 0) {
                return uVar7;
              }
              lVar8 = *(long *)(param_1 + 0x2620) - local_78;
              *(long *)(param_1 + 0x2620) = lVar8;
              if (lVar8 != 0) goto LAB_18be493a8;
            }
          }
LAB_18be49318:
          *(undefined4 *)(param_1 + 0x213c) = 3;
        }
      }
      else if (iVar6 == 3) {
        uVar7 = _HTTPReadLine(param_1 + 0x18,param_2,param_3,&local_68,&local_70);
        if ((int)uVar7 != 0) {
          return uVar7;
        }
        if (local_70 != 0) {
          return 0xffffe5aa;
        }
        *(undefined4 *)(param_1 + 0x213c) = 1;
      }
      else {
        if (iVar6 != 4) {
          if (iVar6 != 5) {
            return 0xffffe5cb;
          }
          goto LAB_18be49648;
        }
        uVar7 = _HTTPReadLine(param_1 + 0x18,param_2,param_3,&local_68,&local_70);
        if ((int)uVar7 != 0) {
          return uVar7;
        }
        if (local_70 == 0) {
          uVar13 = 5;
          goto LAB_18be493a4;
        }
      }
LAB_18be493a8:
      iVar6 = *(int *)(param_1 + 0x213c);
    } while( true );
  }
  uVar7 = *(ulong *)(param_1 + 0x2028);
  if (*(int *)(param_1 + 0x2618) < 0) {
    if (uVar7 == 0) {
      local_88 = *(ulong *)(param_1 + 0x2160);
    }
    else {
      if (*(ulong *)(param_1 + 0x2150) <= uVar7) {
        uVar7 = *(ulong *)(param_1 + 0x2150);
      }
      func_0x0001900cc490(*(undefined8 *)(param_1 + 0x2148),*(undefined8 *)(param_1 + 0x2020),uVar7)
      ;
      *(ulong *)(param_1 + 0x2020) = *(long *)(param_1 + 0x2020) + uVar7;
      *(ulong *)(param_1 + 0x2028) = *(long *)(param_1 + 0x2028) - uVar7;
      local_88 = *(long *)(param_1 + 0x2160) + uVar7;
      *(ulong *)(param_1 + 0x2160) = local_88;
    }
    uVar7 = *(ulong *)(param_1 + 0x2150);
    if (local_88 <= uVar7 && uVar7 - local_88 != 0) {
      uVar7 = (*param_2)(*(long *)(param_1 + 0x2148) + local_88,uVar7 - local_88,&local_88,param_3);
      if ((int)uVar7 != 0) {
        return uVar7;
      }
      local_88 = *(long *)(param_1 + 0x2160) + local_88;
      *(ulong *)(param_1 + 0x2160) = local_88;
      uVar7 = *(ulong *)(param_1 + 0x2150);
    }
    uVar5 = 0;
    if (local_88 != uVar7) {
      uVar5 = 0x23;
    }
    return (ulong)uVar5;
  }
  uVar14 = *(ulong *)(param_1 + 0x2620);
  if (uVar7 != 0) {
    if (uVar14 == 0) goto LAB_18be49648;
    if (uVar14 <= uVar7) {
      uVar7 = uVar14;
    }
    local_88 = uVar7;
    uVar14 = _FDWriteAll(*(int *)(param_1 + 0x2618),*(undefined8 *)(param_1 + 0x2020),uVar7);
    if ((int)uVar14 != 0) {
      return uVar14;
    }
    *(ulong *)(param_1 + 0x2020) = *(long *)(param_1 + 0x2020) + uVar7;
    *(ulong *)(param_1 + 0x2028) = *(long *)(param_1 + 0x2028) - uVar7;
    uVar14 = *(long *)(param_1 + 0x2620) - uVar7;
    *(ulong *)(param_1 + 0x2620) = uVar14;
  }
  if (uVar14 != 0) {
    local_88 = *(ulong *)(param_1 + 0x2158);
    if (uVar14 <= *(ulong *)(param_1 + 0x2158)) {
      local_88 = uVar14;
    }
    uVar7 = (*param_2)(*(undefined8 *)(param_1 + 0x2148),local_88,&local_88,param_3);
    if ((int)uVar7 != 0) {
      return uVar7;
    }
    uVar7 = _FDWriteAll(*(undefined4 *)(param_1 + 0x2618),*(undefined8 *)(param_1 + 0x2148),local_88
                       );
    if ((int)uVar7 != 0) {
      return uVar7;
    }
    lVar8 = *(long *)(param_1 + 0x2620) - local_88;
    *(long *)(param_1 + 0x2620) = lVar8;
    if (lVar8 != 0) {
      return 0x23;
    }
  }
LAB_18be49648:
  if (-1 < *(int *)(param_1 + 0x2618)) {
    iVar6 = func_0x0001900cf930();
    if ((iVar6 != 0) && (piVar10 = (int *)func_0x0001900ce930(), *piVar10 != 0)) {
      func_0x0001900ce930();
    }
    *(undefined4 *)(param_1 + 0x2618) = 0xffffffff;
  }
  return 0;
  while ((byte)local_78 == 0x3b) {
LAB_18be49604:
    iVar6 = _HTTPParseParameter(local_68,pbVar2,0,0,0,0,&local_78,&local_68);
    pbVar16 = local_68;
    bVar17 = (byte)local_78;
    if (iVar6 != 0) break;
  }
LAB_18be495bc:
  local_68 = pbVar16;
  if ((local_68 < pbVar2) && (*local_68 == 0x2c)) {
    local_68 = local_68 + 1;
  }
  if (pbVar2 <= local_68) goto LAB_18be49728;
  goto LAB_18be494ac;
}


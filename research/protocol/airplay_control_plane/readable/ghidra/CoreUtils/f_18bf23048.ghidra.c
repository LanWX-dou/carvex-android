/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf23048
 * original code SHA256: f942ab31266282781e28acd3ce77fb98b29e71ac35d0cc1189a2eedd2d845e5d
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _PairingSessionExchange
                (long param_1,byte *param_2,ulong param_3,long *param_4,ulong *param_5,
                undefined1 *param_6)

{
  byte *pbVar1;
  byte *pbVar2;
  ulong *puVar3;
  byte *pbVar4;
  ulong uVar5;
  byte bVar6;
  ulong uVar7;
  undefined8 uVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  int *piVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  undefined8 uVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  undefined8 uVar20;
  byte bVar21;
  byte *pbVar22;
  code *pcVar23;
  long lVar24;
  byte *pbVar25;
  undefined1 uVar26;
  byte *pbVar27;
  long lVar28;
  ulong uVar29;
  ulong local_240;
  byte *local_238;
  byte *local_220;
  ulong local_210;
  long local_208;
  long local_200;
  undefined8 local_1f8;
  ulong local_1f0;
  char local_1e5;
  uint local_1e4;
  ulong local_1e0;
  long local_1d8;
  uint local_1cc;
  undefined8 *local_1c8;
  ulong local_1c0;
  undefined8 uStack_1b8;
  long local_1b0;
  undefined8 local_1a8;
  undefined8 uStack_1a0;
  undefined8 local_198;
  undefined8 uStack_190;
  undefined8 local_188;
  undefined8 uStack_180;
  undefined8 local_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 local_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 local_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 local_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  ulong local_78;
  long local_70;
  
  local_70 = *_DAT_1e016af28;
  if (param_1 == 0) {
    uVar13 = 0xffffe5ac;
    goto LAB_18bf23400;
  }
  pbVar25 = (byte *)(param_1 + 0x80);
  if (*pbVar25 == 0) {
    piVar12 = *(int **)(param_1 + 0x10);
    if (*piVar12 < 0x1f) {
      if (*piVar12 == -1) {
        iVar9 = __LogCategory_Initialize(piVar12,0x1e);
        if (iVar9 == 0) goto LAB_18bf2312c;
        piVar12 = *(int **)(param_1 + 0x10);
      }
      _LogPrintF(piVar12,
                 "OSStatus PairingSessionExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                 ,0x1e,"PairStart, %s, %#{flags}\n");
    }
  }
LAB_18bf2312c:
  uVar8 = _UNK_18bf721e8;
  uVar7 = _DAT_18bf721e0;
  local_78 = 0;
  local_1e0 = 0;
  local_1d8 = 0;
  uStack_90 = 0;
  local_98 = 0;
  uStack_80 = 0;
  uStack_88 = 0;
  uStack_b0 = 0;
  local_b8 = 0;
  uStack_a0 = 0;
  uStack_a8 = 0;
  uStack_d0 = 0;
  local_d8 = 0;
  uStack_c0 = 0;
  uStack_c8 = 0;
  uStack_f0 = 0;
  local_f8 = 0;
  uStack_e0 = 0;
  uStack_e8 = 0;
  uStack_110 = 0;
  local_118 = 0;
  uStack_100 = 0;
  uStack_108 = 0;
  uStack_130 = 0;
  local_138 = 0;
  uStack_120 = 0;
  uStack_128 = 0;
  uStack_150 = 0;
  local_158 = 0;
  uStack_140 = 0;
  uStack_148 = 0;
  uStack_170 = 0;
  local_178 = 0;
  uStack_160 = 0;
  uStack_168 = 0;
  uStack_180 = 0;
  local_188 = 0;
  uStack_190 = 0;
  local_198 = 0;
  uStack_1a0 = 0;
  local_1a8 = 0;
  uStack_1b8 = _UNK_18bf721e8;
  local_1c0 = _DAT_18bf721e0;
  local_1b0 = 0;
  local_1c8 = &local_1a8;
  uVar13 = _TLV8GetOrCopyCoalesced(param_2,param_2 + param_3,0xc,&local_1d8,&local_1e0,&local_78,0);
  iVar9 = (int)uVar13;
  if (iVar9 == -0x1a47) {
    uVar13 = _TLV8GetOrCopyCoalesced
                       (param_2,param_2 + param_3,0xd,&local_1d8,&local_1e0,&local_78,0);
  }
  uVar29 = local_1e0;
  local_238 = param_2;
  local_240 = param_3;
  if ((int)uVar13 == 0) {
    if (local_1e0 == 0) {
      lVar28 = *(long *)(param_1 + 0xa0);
      lVar17 = *(long *)(param_1 + 0xa8);
      uVar5 = lVar28 - lVar17;
      if (*(ulong *)(param_1 + 0x70) <= (ulong)(lVar28 - lVar17)) {
        uVar5 = *(ulong *)(param_1 + 0x70);
      }
      if (uVar5 == 0) {
        lVar24 = 0;
        uVar29 = 0;
        uVar26 = 0;
        local_220 = (byte *)0x0;
        uVar13 = 0xffffe596;
      }
      else {
        uVar10 = 0xc;
        if (uVar5 + lVar17 == lVar28) {
          uVar10 = 0xd;
        }
        uVar13 = _TLV8BufferAppend(&local_1c8,uVar10,*(long *)(param_1 + 0x98) + lVar17,uVar5);
        uVar29 = local_1c0;
        if ((int)uVar13 == 0) {
          lVar24 = local_1b0;
          if (local_1b0 == 0) {
            uVar13 = local_1c0;
            if (local_1c0 < 2) {
              uVar13 = 1;
            }
            lVar24 = func_0x0001900cfd70(uVar13,0x100004077774924);
            if (lVar24 == 0) goto LAB_18bf24a0c;
            if (uVar29 != 0) {
              func_0x0001900cc480(lVar24,local_1c8,uVar29);
            }
          }
          local_1c0 = 0;
          local_1b0 = 0;
          if (uVar5 + lVar17 == lVar28) {
            uVar26 = *(undefined1 *)(param_1 + 0xb0);
            local_1c8 = &local_1a8;
            func_0x0001900cc3a0(*(undefined8 *)(param_1 + 0x98));
            uVar13 = 0;
            local_220 = (byte *)0x0;
            *(long *)(param_1 + 0x98) = 0;
            *(undefined8 *)(param_1 + 0xa0) = 0;
            *(undefined1 *)(param_1 + 0xb0) = 0;
            *(undefined8 *)(param_1 + 0xa8) = 0;
          }
          else {
            uVar13 = 0;
            uVar26 = 0;
            local_220 = (byte *)0x0;
            *(ulong *)(param_1 + 0xa8) = *(long *)(param_1 + 0xa8) + uVar5;
            local_1c8 = &local_1a8;
          }
        }
        else {
LAB_18bf23378:
          lVar24 = 0;
          uVar29 = 0;
          uVar26 = 0;
          local_220 = (byte *)0x0;
          local_240 = param_3;
          local_238 = param_2;
        }
      }
    }
    else {
      local_240 = *(ulong *)(param_1 + 0x90) + local_1e0;
      if (*(ulong *)(param_1 + 0x90) < local_240) {
        if (local_240 < 0x3e81) {
          local_238 = (byte *)func_0x0001900cfd80(*(undefined8 *)(param_1 + 0x88),local_240,
                                                  0x100004077774924);
          if (local_238 == (byte *)0x0) {
            lVar24 = 0;
LAB_18bf24a0c:
            uVar29 = 0;
            uVar26 = 0;
            local_220 = (byte *)0x0;
            uVar13 = 0xffffe5b8;
            local_240 = param_3;
            local_238 = param_2;
          }
          else {
            func_0x0001900cc480(local_238 + *(long *)(param_1 + 0x90),local_1d8,uVar29);
            if (local_78 != 0) {
              func_0x0001900cc3a0();
              local_78 = 0;
            }
            if (iVar9 == -0x1a47) {
              lVar24 = 0;
              uVar29 = 0;
              uVar13 = 0;
              uVar26 = 0;
              *(undefined8 *)(param_1 + 0x88) = 0;
              *(undefined8 *)(param_1 + 0x90) = 0;
              local_220 = local_238;
            }
            else {
              *(byte **)(param_1 + 0x88) = local_238;
              *(ulong *)(param_1 + 0x90) = local_240;
              uVar13 = _TLV8BufferAppend(&local_1c8,0xc,0,0);
              uVar29 = local_1c0;
              if ((int)uVar13 != 0) goto LAB_18bf23378;
              lVar24 = local_1b0;
              if (local_1b0 == 0) {
                uVar13 = local_1c0;
                if (local_1c0 < 2) {
                  uVar13 = 1;
                }
                lVar24 = func_0x0001900cfd70(uVar13,0x100004077774924);
                if (lVar24 == 0) {
                  uVar29 = 0;
                  uVar26 = 0;
                  local_220 = (byte *)0x0;
                  uVar13 = 0xffffe5b8;
                  local_240 = param_3;
                  local_238 = param_2;
                  goto LAB_18bf23390;
                }
                if (uVar29 != 0) {
                  func_0x0001900cc480(lVar24,local_1c8,uVar29);
                }
              }
              uVar13 = 0;
              uVar26 = 0;
              local_220 = (byte *)0x0;
              local_1c0 = 0;
              local_1b0 = 0;
              local_240 = param_3;
              local_238 = param_2;
              local_1c8 = &local_1a8;
            }
          }
        }
        else {
          lVar24 = 0;
          uVar29 = 0;
          uVar26 = 0;
          local_220 = (byte *)0x0;
          uVar13 = 0xffffe5a9;
          local_240 = param_3;
        }
      }
      else {
        lVar24 = 0;
        uVar29 = 0;
        uVar26 = 0;
        local_220 = (byte *)0x0;
        uVar13 = 0xffffe5a1;
        local_240 = param_3;
      }
    }
  }
  else {
    if ((int)uVar13 == -0x1a47) {
      uVar13 = 0;
    }
    uVar29 = 0;
    lVar24 = 0;
    uVar26 = 0;
    local_220 = (byte *)0x0;
  }
LAB_18bf23390:
  if (local_1b0 != 0) {
    func_0x0001900cc3a0();
    local_1b0 = 0;
  }
  if (local_78 != 0) {
    func_0x0001900cc3a0();
  }
  *param_6 = uVar26;
  local_210 = uVar29;
  local_208 = lVar24;
  if ((int)uVar13 != 0) goto LAB_18bf233d0;
  if (lVar24 == 0) {
    if (*(int *)(param_1 + 0x60) - 1U < 0xe) {
      switch(*(int *)(param_1 + 0x60)) {
      default:
        uVar13 = __SetupClientExchange(param_1,local_238,local_240,&local_208,&local_210,param_6);
        break;
      case 2:
        uVar13 = __SetupServerExchange(param_1,local_238,local_240,&local_208,&local_210,param_6);
        break;
      case 3:
        uVar13 = __VerifyClientExchange(param_1,local_238,local_240,&local_208,&local_210,param_6);
        break;
      case 4:
        uVar13 = __VerifyServerExchange(param_1,local_238,local_240,&local_208,&local_210,param_6);
        break;
      case 5:
        uVar13 = __ResumePairingClientExchange
                           (param_1,local_238,local_240,&local_208,&local_210,param_6);
        break;
      case 6:
        uVar13 = __ResumePairingServerExchange
                           (param_1,local_238,local_240,&local_208,&local_210,param_6);
        break;
      case 7:
      case 8:
        goto switchD_18bf23468_caseD_7;
      case 9:
      case 0xb:
      case 0xd:
        pbVar4 = local_238 + local_240;
        bVar21 = *pbVar25;
        if (bVar21 == 0) {
          bVar21 = 1;
          *pbVar25 = 1;
        }
        pbVar22 = local_238;
        if (local_240 != 0) {
          do {
            if (pbVar22 == pbVar4) {
LAB_18bf24334:
              uVar13 = 0xffffe5b9;
              goto LAB_18bf2442c;
            }
            if (pbVar4 <= pbVar22) {
              uVar13 = 0xffffe5cf;
              goto LAB_18bf2442c;
            }
            if ((ulong)((long)pbVar4 - (long)pbVar22) < 2) goto LAB_18bf24334;
            pbVar2 = pbVar22 + 2;
            pbVar1 = pbVar22 + 1;
            pbVar27 = pbVar2 + *pbVar1;
            if (pbVar4 < pbVar27) {
              uVar13 = 0xffffe5a2;
              goto LAB_18bf2442c;
            }
            bVar6 = *pbVar22;
            pbVar22 = pbVar27;
          } while (bVar6 != 6);
          if (*pbVar1 != 1) goto LAB_18bf24adc;
          if (*pbVar2 == bVar21) goto LAB_18bf23614;
LAB_18bf23b7c:
          uVar13 = 0xffffe5cb;
          goto LAB_18bf2442c;
        }
        pbVar27 = (byte *)0x0;
LAB_18bf23614:
        if (bVar21 != 2) {
          if (bVar21 != 1) {
            piVar12 = *(int **)(param_1 + 0x10);
            if (0x3c < *piVar12) goto LAB_18bf23b7c;
            if (*piVar12 == -1) {
              iVar9 = __LogCategory_Initialize(piVar12,0x3c);
              if (iVar9 != 0) {
                piVar12 = *(int **)(param_1 + 0x10);
                goto LAB_18bf239e8;
              }
            }
            else {
LAB_18bf239e8:
              _LogPrintF(piVar12,
                         "OSStatus _AdminPairingClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                         ,0x3c,"### AdminPairing client bad state: %d\n");
            }
            uVar13 = 0xffffe5cb;
            goto LAB_18bf2442c;
          }
          uStack_90 = 0;
          local_98 = 0;
          uStack_80 = 0;
          uStack_88 = 0;
          uStack_b0 = 0;
          local_b8 = 0;
          uStack_a0 = 0;
          uStack_a8 = 0;
          uStack_d0 = 0;
          local_d8 = 0;
          uStack_c0 = 0;
          uStack_c8 = 0;
          uStack_f0 = 0;
          local_f8 = 0;
          uStack_e0 = 0;
          uStack_e8 = 0;
          uStack_110 = 0;
          local_118 = 0;
          uStack_100 = 0;
          uStack_108 = 0;
          uStack_130 = 0;
          local_138 = 0;
          uStack_120 = 0;
          uStack_128 = 0;
          uStack_150 = 0;
          local_158 = 0;
          uStack_140 = 0;
          uStack_148 = 0;
          uStack_170 = 0;
          local_178 = 0;
          uStack_160 = 0;
          uStack_168 = 0;
          uStack_180 = 0;
          local_188 = 0;
          uStack_190 = 0;
          local_198 = 0;
          uStack_1a0 = 0;
          local_1a8 = 0;
          local_1e0 = 0;
          local_1d8 = 0;
          uStack_1b8 = uVar8;
          local_1c0 = uVar7;
          local_1b0 = 0;
          local_1c8 = &local_1a8;
          if (local_240 != 0) goto LAB_18bf248a0;
          iVar9 = _TLV8BufferAppend(&local_1c8,6,pbVar25,1);
          local_1f0 = CONCAT44(local_1f0._4_4_,iVar9);
          if (iVar9 == 0) {
            iVar9 = *(int *)(param_1 + 0x60);
            if (iVar9 == 0xd) {
              local_78 = CONCAT71(local_78._1_7_,5);
              iVar9 = _TLV8BufferAppend(&local_1c8,0,&local_78,1);
LAB_18bf23fbc:
              local_1f0 = CONCAT44(local_1f0._4_4_,iVar9);
              if (iVar9 == 0) {
LAB_18bf23fc4:
                uVar13 = local_1c0;
                lVar24 = local_1b0;
                if (local_1b0 == 0) {
                  uVar29 = local_1c0;
                  if (local_1c0 < 2) {
                    uVar29 = 1;
                  }
                  lVar24 = func_0x0001900cfd70(uVar29,0x100004077774924);
                  if (lVar24 == 0) {
                    uVar10 = 0xffffe5b8;
                    goto LAB_18bf248a4;
                  }
                  if (uVar13 != 0) {
                    func_0x0001900cc480(lVar24,local_1c8,uVar13);
                  }
                }
                local_1c0 = 0;
                local_1b0 = 0;
                local_210 = uVar13;
                local_1f0 = local_1f0 & 0xffffffff00000000;
                *(undefined1 *)(param_1 + 0x80) = 2;
                piVar12 = *(int **)(param_1 + 0x10);
                iVar9 = *piVar12;
                local_208 = lVar24;
                local_1c8 = &local_1a8;
                if (iVar9 < 0x1f) {
                  if (iVar9 == -1) {
                    iVar9 = __LogCategory_Initialize(piVar12,0x1e);
                    if (iVar9 == 0) goto LAB_18bf23690;
                    piVar12 = *(int **)(param_1 + 0x10);
                    iVar9 = *piVar12;
                  }
                  if ((iVar9 < 0xb) && (iVar9 == -1)) {
                    __LogCategory_Initialize(piVar12,10);
                  }
                  _LogPrintF(piVar12,
                             "OSStatus _AdminPairingClientM1(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                             ,0x1e,"AdminPairing client M1 -- request\n%?{end}%1{tlv8}\n");
                }
              }
            }
            else if (iVar9 == 0xb) {
              local_78 = CONCAT71(local_78._1_7_,4);
              iVar9 = _TLV8BufferAppend(&local_1c8,0,&local_78,1);
              local_1f0 = CONCAT44(local_1f0._4_4_,iVar9);
              if ((iVar9 == 0) &&
                 (lVar24 = _CFDictionaryGetOrCopyBytes
                                     (*(undefined8 *)(param_1 + 0x168),&cfstringStruct_1e9b96a40,
                                      &local_1d8,&local_1e0,&local_1f0), lVar24 != 0)) {
                iVar9 = _TLV8BufferAppend(&local_1c8,1,lVar24,local_1d8);
                local_1f0 = CONCAT44(local_1f0._4_4_,iVar9);
                if (iVar9 == 0) {
                  if (local_1e0 != 0) {
                    func_0x0001900cc3a0();
                    local_1e0 = 0;
                  }
                  goto LAB_18bf23fc4;
                }
              }
            }
            else if (iVar9 == 9) {
              local_78 = CONCAT71(local_78._1_7_,3);
              iVar9 = _TLV8BufferAppend(&local_1c8,0,&local_78,1);
              local_1f0 = CONCAT44(local_1f0._4_4_,iVar9);
              if ((iVar9 == 0) &&
                 (lVar24 = _CFDictionaryGetOrCopyBytes
                                     (*(undefined8 *)(param_1 + 0x168),&cfstringStruct_1e9b96a40,
                                      &local_1d8,&local_1e0,&local_1f0), lVar24 != 0)) {
                iVar9 = _TLV8BufferAppend(&local_1c8,1,lVar24,local_1d8);
                local_1f0 = CONCAT44(local_1f0._4_4_,iVar9);
                if (iVar9 == 0) {
                  if (local_1e0 != 0) {
                    func_0x0001900cc3a0();
                    local_1e0 = 0;
                  }
                  uVar16 = *(undefined8 *)(param_1 + 0x168);
                  uVar20 = func_0x0001900cddf0();
                  lVar24 = _CFDictionaryGetTypedValue
                                     (uVar16,&cfstringStruct_1e9b96a60,uVar20,&local_1f0);
                  if (lVar24 != 0) {
                    uVar20 = func_0x0001900caa40();
                    uVar16 = func_0x0001900caa50(lVar24);
                    iVar9 = _TLV8BufferAppend(&local_1c8,3,uVar20,uVar16);
                    local_1f0 = CONCAT44(local_1f0._4_4_,iVar9);
                    if (iVar9 == 0) {
                      uVar10 = _CFDictionaryGetInt64Ranged
                                         (*(undefined8 *)(param_1 + 0x168),&cfstringStruct_1e9b96a80
                                          ,0,0xffffffff,&local_1f0);
                      if ((int)local_1f0 == 0) {
                        iVar9 = _TLV8BufferAppendUInt64(&local_1c8,0xb,uVar10);
                        goto LAB_18bf23fbc;
                      }
                    }
                  }
                }
              }
            }
            else {
              piVar12 = *(int **)(param_1 + 0x10);
              if (*piVar12 < 0x3d) {
                if (*piVar12 == -1) {
                  iVar9 = __LogCategory_Initialize(piVar12,0x3c);
                  if (iVar9 == 0) goto LAB_18bf248a0;
                  piVar12 = *(int **)(param_1 + 0x10);
                }
                _LogPrintF(piVar12,
                           "OSStatus _AdminPairingClientM1(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                           ,0x3c,"### AdminPairing client bad session type %d\n");
              }
LAB_18bf248a0:
              uVar10 = 0xffffe5cf;
LAB_18bf248a4:
              local_1f0 = CONCAT44(local_1f0._4_4_,uVar10);
            }
          }
LAB_18bf23690:
          if (local_1e0 != 0) {
            func_0x0001900cc3a0();
          }
          if (local_1b0 != 0) {
            func_0x0001900cc3a0();
          }
          uVar13 = local_1f0 & 0xffffffff;
          *param_6 = 0;
          if ((int)local_1f0 == 0) goto LAB_18bf23838;
          goto LAB_18bf24430;
        }
        piVar12 = *(int **)(param_1 + 0x10);
        iVar9 = *piVar12;
        if (iVar9 < 0x1f) {
          if (iVar9 == -1) {
            iVar9 = __LogCategory_Initialize(piVar12,0x1e);
            if (iVar9 == 0) goto LAB_18bf2437c;
            piVar12 = *(int **)(param_1 + 0x10);
            iVar9 = *piVar12;
          }
          if ((iVar9 < 0xb) && (iVar9 == -1)) {
            __LogCategory_Initialize(piVar12,10);
          }
          _LogPrintF(piVar12,
                     "OSStatus _AdminPairingClientM2(PairingSessionRef, const uint8_t *const, const uint8_t *const, const uint8_t *const)"
                     ,0x1e,"AdminPairing client M2 -- response\n%?{end}%1{tlv8}\n");
        }
LAB_18bf2437c:
        while ((local_238 < pbVar4 && (1 < (ulong)((long)pbVar4 - (long)local_238)))) {
          pbVar22 = local_238 + 2;
          pbVar25 = local_238 + 1;
          if (pbVar4 < pbVar22 + *pbVar25) break;
          bVar21 = *local_238;
          local_238 = pbVar22 + *pbVar25;
          if (bVar21 == 7) goto code_r0x00018bf243b0;
        }
        if (*(int *)(param_1 + 0x60) == 0xd) {
          lVar24 = func_0x0001900caa10(0,0,_DAT_1e00e6a20);
          if (lVar24 != 0) {
            do {
              lVar28 = 0;
LAB_18bf24500:
              pbVar25 = pbVar27;
              if ((pbVar4 <= pbVar25) || ((ulong)((long)pbVar4 - (long)pbVar25) < 2)) {
LAB_18bf24948:
                if (lVar28 != 0) {
                  lVar17 = func_0x0001900cdf10(lVar28);
                  if (0 < lVar17) {
                    func_0x0001900caa00(lVar24,lVar28);
                  }
                  func_0x0001900caac0(lVar28);
                }
                uVar13 = _PairingSessionSetProperty(param_1,&cfstringStruct_1e9b96ac0,lVar24);
                func_0x0001900caac0(lVar24);
                if ((int)uVar13 != 0) goto LAB_18bf2442c;
                goto LAB_18bf24998;
              }
              puVar3 = (ulong *)(pbVar25 + 2);
              bVar21 = pbVar25[1];
              uVar13 = (ulong)bVar21;
              pbVar27 = (byte *)((long)puVar3 + uVar13);
              if (pbVar4 < pbVar27) goto LAB_18bf24948;
              bVar6 = *pbVar25;
              if ((lVar28 == 0) &&
                 (lVar28 = func_0x0001900cdef0(0,0,_DAT_1e00e6a30,_DAT_1e00e6a38), lVar28 == 0)) {
                func_0x0001900caac0(lVar24);
                break;
              }
              uVar11 = bVar6 + 1 >> 1 & 0x7f | (bVar6 + 1) * 0x80 & 0xff;
              if (1 < uVar11) {
                if (uVar11 != 2) goto code_r0x00018bf245a0;
                uVar13 = _CFDictionarySetData(lVar28,&cfstringStruct_1e9b93e00,puVar3,uVar13);
                iVar9 = (int)uVar13;
                goto joined_r0x00018bf245e4;
              }
              if (uVar11 != 0) {
                if ((uVar11 == 1) &&
                   (uVar13 = _CFDictionarySetCString(lVar28,&cfstringStruct_1e9b96aa0,puVar3,uVar13)
                   , (int)uVar13 != 0)) goto LAB_18bf24ac0;
                goto LAB_18bf24500;
              }
              lVar17 = func_0x0001900cdf10(lVar28);
              if (0 < lVar17) {
                func_0x0001900caa00(lVar24,lVar28);
              }
              func_0x0001900caac0(lVar28);
            } while( true );
          }
          uVar13 = 0xffffe5b8;
          goto LAB_18bf2442c;
        }
LAB_18bf24998:
        *(undefined1 *)(param_1 + 0x80) = 3;
        piVar12 = *(int **)(param_1 + 0x10);
        if (*piVar12 < 0x1f) {
          if (*piVar12 == -1) {
            iVar9 = __LogCategory_Initialize(piVar12,0x1e);
            if (iVar9 == 0) goto LAB_18bf24a44;
            piVar12 = *(int **)(param_1 + 0x10);
          }
          _LogPrintF(piVar12,
                     "OSStatus _AdminPairingClientM2(PairingSessionRef, const uint8_t *const, const uint8_t *const, const uint8_t *const)"
                     ,0x1e,"AdminPairing client done\n");
        }
LAB_18bf24a44:
        local_210 = 0;
        local_208 = 0;
        *param_6 = 1;
        goto LAB_18bf23838;
      case 10:
      case 0xc:
      case 0xe:
        pbVar4 = local_238 + local_240;
        pbVar22 = local_238;
        do {
          if (pbVar22 == pbVar4) {
LAB_18bf23f24:
            uVar13 = 0xffffe5b9;
            goto LAB_18bf23e70;
          }
          if (pbVar4 <= pbVar22) {
            uVar13 = 0xffffe5cf;
            goto LAB_18bf23e70;
          }
          if ((ulong)((long)pbVar4 - (long)pbVar22) < 2) goto LAB_18bf23f24;
          pbVar2 = pbVar22 + 2;
          pbVar1 = pbVar22 + 1;
          if (pbVar4 < pbVar2 + *pbVar1) {
            uVar13 = 0xffffe5a2;
            goto LAB_18bf23e70;
          }
          bVar21 = *pbVar22;
          pbVar22 = pbVar2 + *pbVar1;
        } while (bVar21 != 6);
        if (*pbVar1 == 1) {
          if (*pbVar2 == 1) {
            __PairingSessionReset(param_1);
          }
          bVar21 = *pbVar25;
          if (bVar21 != 0) {
            if (*pbVar2 == bVar21) {
              if (bVar21 == 1) goto LAB_18bf236d0;
              piVar12 = *(int **)(param_1 + 0x10);
              if (*piVar12 < 0x3d) {
                if (*piVar12 == -1) {
                  iVar9 = __LogCategory_Initialize(piVar12,0x3c);
                  if (iVar9 == 0) goto LAB_18bf23e6c;
                  piVar12 = *(int **)(param_1 + 0x10);
                }
                _LogPrintF(piVar12,
                           "OSStatus _AdminPairingServerExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                           ,0x3c,"### AdminPairing server bad state: %d\n");
              }
            }
LAB_18bf23e6c:
            uVar13 = 0xffffe5cb;
            goto LAB_18bf23e70;
          }
          *pbVar25 = 1;
          if (*pbVar2 != 1) goto LAB_18bf23e6c;
LAB_18bf236d0:
          uStack_90 = 0;
          local_98 = 0;
          uStack_80 = 0;
          uStack_88 = 0;
          uStack_b0 = 0;
          local_b8 = 0;
          uStack_a0 = 0;
          uStack_a8 = 0;
          uStack_d0 = 0;
          local_d8 = 0;
          uStack_c0 = 0;
          uStack_c8 = 0;
          uStack_f0 = 0;
          local_f8 = 0;
          uStack_e0 = 0;
          uStack_e8 = 0;
          uStack_110 = 0;
          local_118 = 0;
          uStack_100 = 0;
          uStack_108 = 0;
          uStack_130 = 0;
          local_138 = 0;
          uStack_120 = 0;
          uStack_128 = 0;
          uStack_150 = 0;
          local_158 = 0;
          uStack_140 = 0;
          uStack_148 = 0;
          uStack_170 = 0;
          local_178 = 0;
          uStack_160 = 0;
          uStack_168 = 0;
          uStack_180 = 0;
          local_188 = 0;
          uStack_190 = 0;
          local_198 = 0;
          uStack_1a0 = 0;
          local_1a8 = 0;
          local_1e5 = '\0';
          local_1f8 = 0;
          local_1f0 = 0;
          local_200 = 0;
          uStack_1b8 = uVar8;
          local_1c0 = uVar7;
          local_1b0 = 0;
          *pbVar25 = 2;
          local_1c8 = &local_1a8;
          local_1e4 = _TLV8BufferAppend(&local_1c8,6,pbVar25,1);
          if (local_1e4 == 0) {
            iVar9 = *(int *)(param_1 + 0x60);
            if (iVar9 == 0xe) {
              local_1e4 = _TLV8GetBytes(local_238,pbVar4,0,1,1,&local_1e5,0,0);
              if (local_1e4 != 0) goto LAB_18bf2374c;
              if (local_1e5 != '\x05') goto LAB_18bf24754;
              lVar24 = func_0x0001900cdef0(0,0,_DAT_1e00e6a30,_DAT_1e00e6a38);
              if (lVar24 == 0) goto LAB_18bf24b2c;
              if (*(code **)(param_1 + 0x3b0) == (code *)0x0) {
                local_78 = local_78 & 0xffffffff00000000;
                lVar28 = func_0x0001900caa10(0,0,_DAT_1e00e6a20);
                if (lVar28 == 0) {
                  local_78 = CONCAT44(local_78._4_4_,0xffffe5b8);
                }
                else {
                  lVar17 = __PairingSessionCopyPeers(param_1,0,0,&local_78);
                  if (lVar17 != 0) {
                    lVar15 = func_0x0001900cdb00();
                    if (0 < lVar15) {
                      lVar18 = 0;
                      do {
                        uVar20 = func_0x0001900cdf30();
                        uVar20 = _CFArrayGetTypedValueAtIndex(lVar17,lVar18,uVar20,&local_78);
                        if ((uint)local_78 != 0) {
LAB_18bf24b48:
                          func_0x0001900caac0(lVar17);
                          func_0x0001900caac0(lVar28);
                          lVar28 = 0;
                          goto LAB_18bf24b60;
                        }
                        lVar19 = func_0x0001900cdef0(0,0,_DAT_1e00e6a30,_DAT_1e00e6a38);
                        if (lVar19 == 0) {
                          local_78 = CONCAT44(local_78._4_4_,0xffffe5b8);
                          goto LAB_18bf24b48;
                        }
                        uVar16 = func_0x0001900ce370();
                        lVar14 = _CFDictionaryGetTypedValue
                                           (uVar20,&cfstringStruct_1e9b96aa0,uVar16,&local_78);
                        if (lVar14 == 0) {
LAB_18bf24b10:
                          func_0x0001900caac0(lVar19);
                          goto LAB_18bf24b48;
                        }
                        func_0x0001900cdf80(lVar19,&cfstringStruct_1e9b96aa0,lVar14);
                        uVar16 = func_0x0001900cddf0();
                        lVar14 = _CFDictionaryGetTypedValue
                                           (uVar20,&cfstringStruct_1e9b93e00,uVar16,&local_78);
                        if (lVar14 == 0) goto LAB_18bf24b10;
                        func_0x0001900cdf80(lVar19,&cfstringStruct_1e9b93e00,lVar14);
                        uVar10 = _CFDictionaryGetInt64Ranged
                                           (uVar20,&cfstringStruct_1e9b96a80,0,0xffffffff,0);
                        _CFDictionarySetInt64(lVar19,&cfstringStruct_1e9b96a80,uVar10);
                        func_0x0001900caa00(lVar28,lVar19);
                        func_0x0001900caac0(lVar19);
                        lVar18 = lVar18 + 1;
                      } while (lVar15 != lVar18);
                    }
                    func_0x0001900caac0(lVar17);
                  }
                }
LAB_18bf24b60:
                local_1e4 = (uint)local_78;
              }
              else {
                lVar28 = (**(code **)(param_1 + 0x3b0))(&local_1e4,*(undefined8 *)(param_1 + 0x3b8))
                ;
              }
              uVar11 = local_1e4;
              if ((lVar28 != 0) && (local_1e4 == 0)) {
                lVar17 = func_0x0001900cdb00(lVar28);
                if (0 < lVar17) {
                  lVar15 = 0;
                  local_1cc = 0;
                  do {
                    local_78 = 0;
                    local_1e0 = 0;
                    local_1d8 = 0;
                    if ((lVar15 != 0) &&
                       (local_1cc = _TLV8BufferAppend(&local_1c8,0xff,0,0), uVar11 = local_1cc,
                       local_1cc != 0)) goto joined_r0x00018bf24ce0;
                    uVar20 = func_0x0001900cdf30();
                    lVar18 = _CFArrayGetTypedValueAtIndex(lVar28,lVar15,uVar20,&local_1cc);
                    if (lVar18 == 0) {
LAB_18bf24cf0:
                      local_1e4 = local_1cc;
                      uVar11 = local_1e4;
                      if (local_1cc != 0) goto LAB_18bf24ce4;
                      goto LAB_18bf247c4;
                    }
                    uVar20 = func_0x0001900ce370();
                    lVar19 = _CFDictionaryGetTypedValue
                                       (lVar18,&cfstringStruct_1e9b96aa0,uVar20,&local_1cc);
                    if (lVar19 == 0) goto LAB_18bf24cf0;
                    uVar11 = _CFStringGetOrCopyCStringUTF8(lVar19,&local_78,&local_1d8,&local_1e0);
                    if (uVar11 != 0) goto joined_r0x00018bf24ce0;
                    uVar11 = _TLV8BufferAppend(&local_1c8,1,local_78,local_1e0);
                    local_1cc = uVar11;
                    if (local_1d8 != 0) {
                      func_0x0001900cc3a0();
                    }
                    if (uVar11 != 0) goto joined_r0x00018bf24ce0;
                    uVar20 = func_0x0001900cddf0();
                    lVar19 = _CFDictionaryGetTypedValue
                                       (lVar18,&cfstringStruct_1e9b93e00,uVar20,&local_1cc);
                    if (lVar19 == 0) goto LAB_18bf24cf0;
                    uVar20 = func_0x0001900caa40();
                    uVar16 = func_0x0001900caa50(lVar19);
                    uVar11 = _TLV8BufferAppend(&local_1c8,3,uVar20,uVar16);
                    if (uVar11 != 0) goto joined_r0x00018bf24ce0;
                    uVar10 = _CFDictionaryGetInt64Ranged
                                       (lVar18,&cfstringStruct_1e9b96a80,0,0xffffffff,0);
                    local_1cc = _TLV8BufferAppendUInt64(&local_1c8,0xb,uVar10);
                    uVar11 = local_1cc;
                    if (local_1cc != 0) goto LAB_18bf24ce4;
                    lVar15 = lVar15 + 1;
                  } while (lVar17 != lVar15);
                }
                local_1e4 = 0;
LAB_18bf247c4:
                uVar13 = local_1c0;
                lVar17 = local_1b0;
                if (local_1b0 == 0) {
                  uVar29 = local_1c0;
                  if (local_1c0 < 2) {
                    uVar29 = 1;
                  }
                  lVar17 = func_0x0001900cfd70(uVar29,0x100004077774924);
                  if (lVar17 == 0) {
                    local_1e4 = 0xffffe5b8;
                    uVar11 = local_1e4;
                    goto joined_r0x00018bf24ce0;
                  }
                  if (uVar13 != 0) {
                    func_0x0001900cc480(lVar17,local_1c8,uVar13);
                  }
                }
                local_1c0 = 0;
                local_1b0 = 0;
                local_210 = uVar13;
                local_1e4 = 0;
                piVar12 = *(int **)(param_1 + 0x10);
                iVar9 = *piVar12;
                local_208 = lVar17;
                if (iVar9 < 0x1f) {
                  local_1c8 = &local_1a8;
                  if (iVar9 == -1) {
                    iVar9 = __LogCategory_Initialize(piVar12,0x1e);
                    piVar12 = *(int **)(param_1 + 0x10);
                    if (iVar9 != 0) {
                      iVar9 = *piVar12;
                      goto LAB_18bf24830;
                    }
                  }
                  else {
LAB_18bf24830:
                    if ((iVar9 < 0xb) && (iVar9 == -1)) {
                      __LogCategory_Initialize(piVar12,10);
                    }
                    _LogPrintF(piVar12,
                               "OSStatus _AdminPairingServerM1(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                               ,0x1e,"AdminPairing server M4 -- response\n%?{end}%1{tlv8}\n");
                    piVar12 = *(int **)(param_1 + 0x10);
                  }
                  iVar9 = *piVar12;
                  *pbVar25 = 3;
                  uVar11 = local_1e4;
                  if (iVar9 < 0x1f) {
                    if (iVar9 == -1) {
                      iVar9 = __LogCategory_Initialize(piVar12,0x1e);
                      uVar11 = local_1e4;
                      if (iVar9 == 0) goto joined_r0x00018bf24ce0;
                      piVar12 = *(int **)(param_1 + 0x10);
                    }
                    _LogPrintF(piVar12,
                               "OSStatus _AdminPairingServerM1(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                               ,0x1e,"AdminPairing server done\n");
                    uVar11 = local_1e4;
                  }
                }
                else {
                  *pbVar25 = 3;
                  uVar11 = local_1e4;
                  local_1c8 = &local_1a8;
                }
              }
joined_r0x00018bf24ce0:
              local_1e4 = uVar11;
              uVar11 = local_1e4;
              if (lVar28 != 0) {
LAB_18bf24ce4:
                local_1e4 = uVar11;
                func_0x0001900caac0(lVar28);
              }
            }
            else if (iVar9 == 0xc) {
              local_1e4 = _TLV8GetBytes(local_238,pbVar4,0,1,1,&local_1e5,0,0);
              if (local_1e4 != 0) goto LAB_18bf2374c;
              if (local_1e5 != '\x04') goto LAB_18bf24754;
              lVar24 = func_0x0001900cdef0(0,0,_DAT_1e00e6a30,_DAT_1e00e6a38);
              if (lVar24 == 0) {
LAB_18bf24b2c:
                local_1e4 = 0xffffe5b8;
              }
              else {
                local_1e4 = _TLV8GetOrCopyCoalesced
                                      (local_238,pbVar4,1,&local_1f0,&local_1f8,&local_200,0);
                if ((local_1e4 == 0) &&
                   (local_1e4 = _CFDictionarySetCString
                                          (lVar24,&cfstringStruct_1e9b96aa0,local_1f0,local_1f8),
                   local_1e4 == 0)) {
                  if (local_200 != 0) {
                    func_0x0001900cc3a0();
                    local_200 = 0;
                  }
                  pcVar23 = *(code **)(param_1 + 0x3a0);
                  if (pcVar23 == (code *)0x0) {
                    lVar28 = _CFDictionaryGetOrCopyBytes
                                       (lVar24,&cfstringStruct_1e9b96aa0,&local_78,&local_1d8,
                                        &local_1e0);
                    if (lVar28 != 0) {
                      __PairingSessionDeletePeer(param_1,lVar28,local_78);
                      local_1e0 = local_1e0 & 0xffffffff00000000;
                    }
LAB_18bf242dc:
                    if (local_1d8 != 0) {
                      func_0x0001900cc3a0();
                    }
                    local_1e4 = (uint)local_1e0;
                  }
                  else {
                    uVar20 = *(undefined8 *)(param_1 + 0x3a8);
LAB_18bf23d70:
                    local_1e4 = (*pcVar23)(lVar24,uVar20);
                  }
                  if (local_1e4 != 0) {
                    piVar12 = *(int **)(param_1 + 0x10);
                    if (*piVar12 < 0x33) {
                      if (*piVar12 == -1) {
                        iVar9 = __LogCategory_Initialize(piVar12,0x32);
                        if (iVar9 == 0) goto LAB_18bf24678;
                        piVar12 = *(int **)(param_1 + 0x10);
                      }
                      _LogPrintF(piVar12,
                                 "OSStatus _AdminPairingServerM1(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                                 ,0x32,"### AdminPairing server failed for %##@: %#m\n");
                    }
LAB_18bf24678:
                    if ((int)local_1e4 < -0x1a6b) {
                      if ((int)local_1e4 < -0x1a75) {
                        if (local_1e4 == 0xfffeea18) {
                          uVar20 = 8;
                        }
                        else if (local_1e4 == 0xffffe588) {
                          uVar20 = 9;
                        }
                        else {
LAB_18bf2479c:
                          uVar20 = 10;
                          if (local_1e4 != 0xffffe5b1) {
                            uVar20 = 1;
                          }
                        }
                      }
                      else if (local_1e4 == 0xffffe58b) {
                        uVar20 = 7;
                      }
                      else {
                        if (local_1e4 != 0xffffe594) goto LAB_18bf2479c;
                        uVar20 = 6;
                      }
                    }
                    else if ((int)local_1e4 < -0x1a62) {
                      if (local_1e4 == 0xffffe595) {
                        uVar20 = 5;
                      }
                      else {
                        if (local_1e4 != 0xffffe598) goto LAB_18bf2479c;
                        uVar20 = 3;
                      }
                    }
                    else if (local_1e4 == 0xffffe59e) {
                      uVar20 = 2;
                    }
                    else if (local_1e4 == 0xffffe5b9) {
                      uVar20 = 4;
                    }
                    else {
                      if (local_1e4 != 0xffffe5d4) goto LAB_18bf2479c;
                      uVar20 = 1;
                    }
                    local_1e4 = _TLV8BufferAppendUInt64(&local_1c8,7,uVar20);
                    if (local_1e4 != 0) goto LAB_18bf23750;
                  }
                  lVar28 = 0;
                  goto LAB_18bf247c4;
                }
              }
            }
            else {
              if (iVar9 == 10) {
                local_1e4 = _TLV8GetBytes(local_238,pbVar4,0,1,1,&local_1e5,0,0);
                if (local_1e4 != 0) goto LAB_18bf2374c;
                if (local_1e5 == '\x03') {
                  lVar24 = func_0x0001900cdef0(0,0,_DAT_1e00e6a30,_DAT_1e00e6a38);
                  if (lVar24 != 0) {
                    local_1e4 = _TLV8GetOrCopyCoalesced
                                          (local_238,pbVar4,1,&local_1f0,&local_1f8,&local_200,0);
                    if ((local_1e4 == 0) &&
                       (local_1e4 = _CFDictionarySetCString
                                              (lVar24,&cfstringStruct_1e9b96aa0,local_1f0,local_1f8)
                       , local_1e4 == 0)) {
                      if (local_200 != 0) {
                        func_0x0001900cc3a0();
                        local_200 = 0;
                      }
                      local_1e4 = _TLV8GetOrCopyCoalesced
                                            (local_238,pbVar4,3,&local_1f0,&local_1f8,&local_200,0);
                      if ((local_1e4 == 0) &&
                         (local_1e4 = _CFDictionarySetData
                                                (lVar24,&cfstringStruct_1e9b93e00,local_1f0,
                                                 local_1f8), local_1e4 == 0)) {
                        if (local_200 != 0) {
                          func_0x0001900cc3a0();
                          local_200 = 0;
                        }
                        uVar13 = _TLV8GetUInt64(local_238,pbVar4,0xb,&local_1e4,0);
                        if (local_1e4 == 0) {
                          if (uVar13 >> 0x20 == 0) {
                            local_1e4 = _CFDictionarySetInt64
                                                  (lVar24,&cfstringStruct_1e9b96a80,uVar13);
                            if (local_1e4 == 0) {
                              pcVar23 = *(code **)(param_1 + 0x390);
                              if (pcVar23 == (code *)0x0) {
                                lVar28 = _CFDictionaryGetOrCopyBytes
                                                   (lVar24,&cfstringStruct_1e9b96aa0,&local_78,
                                                    &local_1d8,&local_1e0);
                                if (lVar28 != 0) {
                                  uVar20 = func_0x0001900cddf0();
                                  lVar17 = _CFDictionaryGetTypedValue
                                                     (lVar24,&cfstringStruct_1e9b93e00,uVar20,
                                                      &local_1e0);
                                  if (lVar17 != 0) {
                                    lVar15 = func_0x0001900caa50();
                                    if (lVar15 == 0x20) {
                                      uVar20 = _CFDictionaryGetInt64Ranged
                                                         (lVar24,&cfstringStruct_1e9b96a80,0,
                                                          0xffffffff,0);
                                      uVar13 = local_78;
                                      uVar16 = func_0x0001900caa40(lVar17);
                                      uVar10 = __PairingSessionSavePeerKeychain
                                                         (param_1,lVar28,uVar13,uVar16,uVar20);
                                    }
                                    else {
                                      uVar10 = 0xffffe5a9;
                                    }
                                    local_1e0 = CONCAT44(local_1e0._4_4_,uVar10);
                                  }
                                }
                                goto LAB_18bf242dc;
                              }
                              uVar20 = *(undefined8 *)(param_1 + 0x398);
                              local_1e4 = 0;
                              goto LAB_18bf23d70;
                            }
                          }
                          else {
                            local_1e4 = 0xffffe5ca;
                          }
                        }
                      }
                    }
                    goto LAB_18bf23750;
                  }
                  goto LAB_18bf24b2c;
                }
              }
              else {
                piVar12 = *(int **)(param_1 + 0x10);
                if (*piVar12 < 0x3d) {
                  if (*piVar12 == -1) {
                    iVar9 = __LogCategory_Initialize(piVar12,0x3c);
                    if (iVar9 == 0) goto LAB_18bf24754;
                    piVar12 = *(int **)(param_1 + 0x10);
                  }
                  _LogPrintF(piVar12,
                             "OSStatus _AdminPairingServerM1(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                             ,0x3c,"### AdminPairing server bad session type %d\n");
                }
              }
LAB_18bf24754:
              lVar24 = 0;
              local_1e4 = 0xffffe5cf;
            }
          }
          else {
LAB_18bf2374c:
            lVar24 = 0;
          }
LAB_18bf23750:
          if (local_200 != 0) {
            func_0x0001900cc3a0();
          }
          if (lVar24 != 0) {
            func_0x0001900caac0(lVar24);
          }
          if (local_1b0 != 0) {
            func_0x0001900cc3a0();
          }
          uVar13 = (ulong)local_1e4;
          *param_6 = local_1e4 == 0;
          if (local_1e4 == 0) goto LAB_18bf23838;
        }
        else {
          uVar13 = 0xffffe5a9;
LAB_18bf23e70:
          *param_6 = 0;
        }
        piVar12 = *(int **)(param_1 + 0x10);
        iVar9 = *piVar12;
        if (iVar9 < 0x33) {
          if (iVar9 == -1) {
            iVar9 = __LogCategory_Initialize(piVar12,0x32);
            if (iVar9 == 0) goto LAB_18bf233d0;
            piVar12 = *(int **)(param_1 + 0x10);
            iVar9 = *piVar12;
          }
          if ((iVar9 < 0x29) && (iVar9 == -1)) {
            __LogCategory_Initialize(piVar12,0x28);
          }
          _LogPrintF(piVar12,
                     "OSStatus _AdminPairingServerExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                     ,0x32,"### AdminPairing server state %d failed: %#m\n%?{end}%1{tlv8}\n");
        }
        goto LAB_18bf233d0;
      }
LAB_18bf23834:
      if ((int)uVar13 == 0) {
LAB_18bf23838:
        uStack_90 = 0;
        local_98 = 0;
        uStack_80 = 0;
        uStack_88 = 0;
        uStack_b0 = 0;
        local_b8 = 0;
        uStack_a0 = 0;
        uStack_a8 = 0;
        uStack_d0 = 0;
        local_d8 = 0;
        uStack_c0 = 0;
        uStack_c8 = 0;
        uStack_f0 = 0;
        local_f8 = 0;
        uStack_e0 = 0;
        uStack_e8 = 0;
        uStack_110 = 0;
        local_118 = 0;
        uStack_100 = 0;
        uStack_108 = 0;
        uStack_130 = 0;
        local_138 = 0;
        uStack_120 = 0;
        uStack_128 = 0;
        uStack_150 = 0;
        local_158 = 0;
        uStack_140 = 0;
        uStack_148 = 0;
        uStack_170 = 0;
        local_178 = 0;
        uStack_160 = 0;
        uStack_168 = 0;
        uStack_180 = 0;
        local_188 = 0;
        uStack_190 = 0;
        local_198 = 0;
        uStack_1a0 = 0;
        local_1a8 = 0;
        uStack_1b8 = uVar8;
        local_1c0 = uVar7;
        local_1b0 = 0;
        local_1c8 = &local_1a8;
        if (local_210 <= *(ulong *)(param_1 + 0x78)) {
          *param_4 = local_208;
          *param_5 = local_210;
          goto LAB_18bf233cc;
        }
        if ((*(long *)(param_1 + 0x98) == 0) && (*(long *)(param_1 + 0xa0) == 0)) {
          *(long *)(param_1 + 0x98) = local_208;
          *(ulong *)(param_1 + 0xa0) = local_210;
          *(undefined8 *)(param_1 + 0xa8) = *(undefined8 *)(param_1 + 0x70);
          *(undefined1 *)(param_1 + 0xb0) = *param_6;
          uVar13 = _TLV8BufferAppend(&local_1c8,0xc);
          uVar7 = local_1c0;
          local_208 = 0;
          if ((int)uVar13 == 0) {
            lVar24 = local_1b0;
            if (local_1b0 == 0) {
              uVar13 = local_1c0;
              if (local_1c0 < 2) {
                uVar13 = 1;
              }
              lVar24 = func_0x0001900cfd70(uVar13,0x100004077774924);
              if (lVar24 == 0) {
                uVar13 = 0xffffe5b8;
                goto joined_r0x00018bf24b24;
              }
              if (uVar7 != 0) {
                func_0x0001900cc480(lVar24,local_1c8,uVar7);
              }
            }
            uVar13 = 0;
            local_1c0 = 0;
            local_1b0 = 0;
            *param_4 = lVar24;
            *param_5 = uVar7;
            *param_6 = 0;
            local_1c8 = &local_1a8;
          }
          else {
joined_r0x00018bf24b24:
            if (local_1b0 != 0) {
              func_0x0001900cc3a0(local_1b0);
            }
          }
        }
        else {
          uVar13 = 0xffffe5d1;
        }
      }
    }
    else {
switchD_18bf23468_caseD_7:
      piVar12 = *(int **)(param_1 + 0x10);
      if (*piVar12 < 0x3d) {
        if (*piVar12 == -1) {
          iVar9 = __LogCategory_Initialize(piVar12,0x3c);
          if (iVar9 == 0) goto LAB_18bf23cac;
          piVar12 = *(int **)(param_1 + 0x10);
        }
        _LogPrintF(piVar12,
                   "OSStatus PairingSessionExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                   ,0x3c,"### Bad pair type: %d\n");
      }
LAB_18bf23cac:
      uVar13 = 0xffffe5cb;
    }
  }
  else {
    *param_4 = lVar24;
    *param_5 = uVar29;
LAB_18bf233cc:
    uVar13 = 0;
    local_208 = 0;
  }
LAB_18bf233d0:
  if (local_220 != (byte *)0x0) {
    func_0x0001900cc3a0();
  }
  if (local_208 != 0) {
    func_0x0001900cc3a0();
  }
  if (((int)uVar13 != -0x1a73) && ((int)uVar13 != 0)) {
    __PairingSessionReset(param_1);
  }
LAB_18bf23400:
  if (*_DAT_1e016af28 != local_70) {
    uVar13 = func_0x0001900cc180();
    return uVar13;
  }
  return uVar13;
code_r0x00018bf243b0:
  if (*pbVar25 == 1) {
    bVar21 = *pbVar22;
    if (bVar21 < 10) {
      uVar11 = *(uint *)(&DAT_18bf7326c + (ulong)bVar21 * 4);
    }
    else {
      uVar11 = 0xffffe5b1;
      if (bVar21 != 10) {
        uVar11 = 0xffffe5d4;
      }
    }
    uVar13 = (ulong)uVar11;
    piVar12 = *(int **)(param_1 + 0x10);
    if (*piVar12 < 0x33) {
      if (*piVar12 == -1) {
        iVar9 = __LogCategory_Initialize(piVar12,0x32);
        if (iVar9 == 0) goto LAB_18bf2442c;
        piVar12 = *(int **)(param_1 + 0x10);
      }
      _LogPrintF(piVar12,
                 "OSStatus _AdminPairingClientM2(PairingSessionRef, const uint8_t *const, const uint8_t *const, const uint8_t *const)"
                 ,0x32,"### AdminPairing client M2 bad status: 0x%X, %#m\n");
    }
  }
  else {
LAB_18bf24adc:
    uVar13 = 0xffffe5a9;
  }
LAB_18bf2442c:
  *param_6 = 0;
LAB_18bf24430:
  piVar12 = *(int **)(param_1 + 0x10);
  iVar9 = *piVar12;
  if (iVar9 < 0x33) {
    if (iVar9 == -1) {
      iVar9 = __LogCategory_Initialize(piVar12,0x32);
      if (iVar9 == 0) goto LAB_18bf23834;
      piVar12 = *(int **)(param_1 + 0x10);
      iVar9 = *piVar12;
    }
    if ((iVar9 < 0x29) && (iVar9 == -1)) {
      __LogCategory_Initialize(piVar12,0x28);
    }
    _LogPrintF(piVar12,
               "OSStatus _AdminPairingClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
               ,0x32,"### AdminPairing client state %d failed: %#m\n%?{end}%1{tlv8}\n");
  }
  goto LAB_18bf23834;
code_r0x00018bf245a0:
  if (uVar11 != 6) goto LAB_18bf24500;
  uVar13 = 0xffffe5a9;
  if (bVar21 < 4) {
    if (bVar21 == 1) {
      uVar13 = (ulong)(byte)*puVar3;
    }
    else {
      if (bVar21 != 2) goto LAB_18bf24ac0;
      uVar13 = (ulong)*(ushort *)(pbVar25 + 2);
    }
  }
  else if (bVar21 == 4) {
    uVar13 = (ulong)(uint)*puVar3;
  }
  else {
    if (bVar21 != 8) goto LAB_18bf24ac0;
    uVar13 = *puVar3;
  }
  uVar13 = _CFDictionarySetInt64(lVar28,&cfstringStruct_1e9b96a80,uVar13);
  iVar9 = (int)uVar13;
joined_r0x00018bf245e4:
  if (iVar9 == 0) goto LAB_18bf24500;
LAB_18bf24ac0:
  func_0x0001900caac0(lVar28);
  func_0x0001900caac0(lVar24);
  goto LAB_18bf2442c;
}


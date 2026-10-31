/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf29408
 * original code SHA256: 8cb46b6f7f26b98c638156048389b644f81f3772d06cecbf602de7b1960626d8
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong __VerifyClientExchange
                (long param_1,byte *param_2,long param_3,undefined8 *param_4,undefined8 *param_5,
                undefined1 *param_6)

{
  byte *pbVar1;
  undefined8 *puVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte bVar5;
  undefined1 auVar6 [16];
  int iVar7;
  uint uVar8;
  undefined8 uVar9;
  ulong uVar10;
  long lVar11;
  char *pcVar12;
  byte *pbVar13;
  byte bVar14;
  uint uVar15;
  int *piVar16;
  undefined1 uVar17;
  byte *pbVar18;
  undefined8 *puVar19;
  long lVar20;
  long lVar21;
  char cVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 *local_268;
  ulong local_260;
  uint local_254;
  undefined8 local_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 local_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  ulong local_208 [8];
  undefined8 *local_1c8;
  undefined8 local_1c0;
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
  undefined8 local_168;
  undefined8 uStack_160;
  undefined8 local_158;
  undefined8 uStack_150;
  undefined8 local_148;
  undefined8 uStack_140;
  undefined8 local_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 uStack_120;
  undefined8 local_118;
  undefined8 uStack_110;
  undefined8 local_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined8 uStack_80;
  long local_78;
  
  local_78 = *_DAT_1e016af28;
  pbVar18 = (byte *)(param_1 + 0x80);
  bVar14 = *pbVar18;
  pbVar4 = param_2 + param_3;
  pbVar13 = param_2;
  if (bVar14 == 0) {
    bVar14 = 1;
    *pbVar18 = 1;
    if (param_3 != 0) goto LAB_18bf2947c;
LAB_18bf294cc:
    if (bVar14 != 4) {
      if (bVar14 == 2) {
        uStack_80 = 0;
        local_88 = 0;
        uStack_90 = 0;
        local_98 = 0;
        uStack_a0 = 0;
        local_a8 = 0;
        uStack_b0 = 0;
        local_b8 = 0;
        uStack_c0 = 0;
        local_c8 = 0;
        uStack_d0 = 0;
        local_d8 = 0;
        uStack_e0 = 0;
        local_e8 = 0;
        uStack_f0 = 0;
        local_f8 = 0;
        uStack_100 = 0;
        local_108 = 0;
        uStack_110 = 0;
        local_118 = 0;
        uStack_120 = 0;
        local_128 = 0;
        uStack_130 = 0;
        local_138 = 0;
        uStack_140 = 0;
        local_148 = 0;
        uStack_150 = 0;
        local_158 = 0;
        uStack_160 = 0;
        local_168 = 0;
        uStack_170 = 0;
        local_178 = 0;
        uStack_180 = 0;
        local_188 = 0;
        uStack_190 = 0;
        local_198 = 0;
        uStack_1a0 = 0;
        local_1a8 = 0;
        local_1c8 = &local_1a8;
        local_268 = (undefined8 *)0x0;
        local_260 = 0;
        uStack_1b8 = _UNK_18bf721e8;
        local_1c0 = _DAT_18bf721e0;
        local_1b0 = 0;
        piVar16 = *(int **)(param_1 + 0x10);
        iVar7 = *piVar16;
        if (iVar7 < 0x1f) {
          if (iVar7 == -1) {
            iVar7 = __LogCategory_Initialize(piVar16,0x1e);
            if (iVar7 == 0) goto LAB_18bf29960;
            piVar16 = *(int **)(param_1 + 0x10);
            iVar7 = *piVar16;
          }
          if ((iVar7 < 0xb) && (iVar7 == -1)) {
            __LogCategory_Initialize(piVar16,10);
          }
          _LogPrintF(piVar16,
                     "OSStatus _VerifyClientM2(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                     ,0x1e,"PairVerify client M2 -- start response\n%?{end}%1{tlv8}\n");
        }
LAB_18bf29960:
        puVar2 = (undefined8 *)(param_1 + 0x24e);
        local_254 = _TLV8GetBytes(param_2,pbVar4,3,0x20,0x20,puVar2,0,0);
        if (local_254 == 0) {
          puVar19 = (undefined8 *)(param_1 + 0x28e);
          local_254 = func_0x0001900ec2a0(puVar19,param_1 + 0x1ee,puVar2);
          if (local_254 != 0) goto LAB_18bf299b0;
          uVar24 = *(undefined8 *)(param_1 + 0x296);
          uVar9 = *puVar19;
          uVar25 = *(undefined8 *)(param_1 + 0x2a6);
          uVar23 = *(undefined8 *)(param_1 + 0x29e);
          auVar6[1] = (byte)((ulong)uVar23 >> 8) | (byte)((ulong)uVar9 >> 8);
          auVar6[0] = (byte)uVar23 | (byte)uVar9;
          auVar6[2] = (byte)((ulong)uVar23 >> 0x10) | (byte)((ulong)uVar9 >> 0x10);
          auVar6[3] = (byte)((ulong)uVar23 >> 0x18) | (byte)((ulong)uVar9 >> 0x18);
          auVar6[4] = (byte)((ulong)uVar23 >> 0x20) | (byte)((ulong)uVar9 >> 0x20);
          auVar6[5] = (byte)((ulong)uVar23 >> 0x28) | (byte)((ulong)uVar9 >> 0x28);
          auVar6[6] = (byte)((ulong)uVar23 >> 0x30) | (byte)((ulong)uVar9 >> 0x30);
          auVar6[7] = (byte)((ulong)uVar23 >> 0x38) | (byte)((ulong)uVar9 >> 0x38);
          auVar6[8] = (byte)uVar25 | (byte)uVar24;
          auVar6[9] = (byte)((ulong)uVar25 >> 8) | (byte)((ulong)uVar24 >> 8);
          auVar6[10] = (byte)((ulong)uVar25 >> 0x10) | (byte)((ulong)uVar24 >> 0x10);
          auVar6[0xb] = (byte)((ulong)uVar25 >> 0x18) | (byte)((ulong)uVar24 >> 0x18);
          auVar6[0xc] = (byte)((ulong)uVar25 >> 0x20) | (byte)((ulong)uVar24 >> 0x20);
          auVar6[0xd] = (byte)((ulong)uVar25 >> 0x28) | (byte)((ulong)uVar24 >> 0x28);
          auVar6[0xe] = (byte)((ulong)uVar25 >> 0x30) | (byte)((ulong)uVar24 >> 0x30);
          auVar6[0xf] = (byte)((ulong)uVar25 >> 0x38) | (byte)((ulong)uVar24 >> 0x38);
          cVar22 = NEON_umaxv(auVar6,1);
          if (cVar22 == '\0') {
            puVar19 = (undefined8 *)0x0;
            lVar20 = 0;
            local_254 = 0xffffe5aa;
            goto LAB_18bf29a7c;
          }
          uVar9 = func_0x0001900cf870();
          func_0x0001900cf190(uVar9,0x20,puVar19,0x18,"Pair-Verify-Encrypt-Salt",0x18,
                              "Pair-Verify-Encrypt-Info",0x20,param_1 + 0x1ae);
          lVar20 = _TLV8CopyCoalesced(param_2,pbVar4,5,&local_260,&local_254);
          if (local_254 != 0) {
            piVar16 = *(int **)(param_1 + 0x10);
            if (*piVar16 < 0x5b) {
              if (*piVar16 == -1) {
                iVar7 = __LogCategory_Initialize(piVar16,0x5a);
                if (iVar7 == 0) goto LAB_18bf29a74;
                piVar16 = *(int **)(param_1 + 0x10);
              }
              pcVar12 = "### PairVerify client M2 failed: get encrypted data, %#m\n";
LAB_18bf2a364:
              _LogPrintF(piVar16,
                         "OSStatus _VerifyClientM2(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                         ,0x5a,pcVar12);
            }
LAB_18bf29a74:
            puVar19 = (undefined8 *)0x0;
            goto LAB_18bf29a7c;
          }
          if (local_260 < 0x10) goto LAB_18bf2a318;
          local_260 = local_260 - 0x10;
          lVar21 = lVar20 + local_260;
          local_254 = __chacha20_poly1305_decrypt_all
                                (param_1 + 0x1ae,"PV-Msg02",8,0,0,lVar20,local_260,lVar20,lVar21,
                                 0x10);
          if (local_254 != 0) goto LAB_18bf29a74;
          uVar9 = _TLV8GetUInt64(lVar20,lVar21,0x19,0,0);
          *(undefined8 *)(param_1 + 0xd0) = uVar9;
          if ((*(uint *)(param_1 + 100) >> 0xc & 1) == 0) {
            if (*(long *)(param_1 + 0x3d8) != 0) {
              lVar11 = func_0x0001900cfe90();
              local_254 = _TLV8GetBytes(lVar20,lVar21,10,0x40,0x40,local_208,0,0);
              if (local_254 != 0) {
                func_0x0001900cc6c0();
                goto LAB_18bf29a74;
              }
              uStack_248 = *(undefined8 *)(param_1 + 0x256);
              local_250 = *puVar2;
              uStack_238 = *(undefined8 *)(param_1 + 0x266);
              uStack_240 = *(undefined8 *)(param_1 + 0x25e);
              uStack_228 = *(undefined8 *)(param_1 + 0x1d6);
              local_230 = *(undefined8 *)(param_1 + 0x1ce);
              uStack_218 = *(undefined8 *)(param_1 + 0x1e6);
              uStack_220 = *(undefined8 *)(param_1 + 0x1de);
              local_254 = (**(code **)(lVar11 + 0x10))
                                    (lVar11,*(undefined4 *)(param_1 + 100),&local_250,0x40,local_208
                                    );
              if (local_254 == 0xffffe5c6) {
                func_0x0001900cc720(lVar11);
                goto LAB_18bf29fd4;
              }
              if (local_254 == 0) {
                func_0x0001900cc720(lVar11);
                goto LAB_18bf29b50;
              }
              piVar16 = *(int **)(param_1 + 0x10);
              if (*piVar16 < 0x5b) {
                if (*piVar16 == -1) {
                  iVar7 = __LogCategory_Initialize(piVar16,0x5a);
                  if (iVar7 == 0) goto LAB_18bf2a2c4;
                  piVar16 = *(int **)(param_1 + 0x10);
                }
                _LogPrintF(piVar16,
                           "OSStatus _VerifyClientM2(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                           ,0x5a,"### PairVerify client M2 verify signature failed: %#m\n");
              }
LAB_18bf2a2c4:
              func_0x0001900cc720(lVar11);
              goto LAB_18bf2a2cc;
            }
LAB_18bf29fd4:
            if (*(long *)(param_1 + 0x138) != 0) {
              func_0x0001900cc3a0();
              *(undefined8 *)(param_1 + 0x138) = 0;
            }
            *(undefined8 *)(param_1 + 0x140) = 0;
            uVar9 = _TLV8CopyCoalesced(lVar20,lVar21,1,param_1 + 0x140,&local_254);
            *(undefined8 *)(param_1 + 0x138) = uVar9;
            if (local_254 == 0) {
              if (*(long *)(param_1 + 0x140) == 0) {
LAB_18bf2a318:
                puVar19 = (undefined8 *)0x0;
                local_254 = 0xffffe5a9;
                goto LAB_18bf29a7c;
              }
              local_254 = _PairingSessionFindPeerEx
                                    (param_1,uVar9,*(long *)(param_1 + 0x140),param_1 + 0x26e,
                                     &local_268);
              if (local_254 == 0) {
                local_254 = _TLV8GetBytes(lVar20,lVar21,10,0x40,0x40,local_208,0,0);
                if (local_254 == 0) {
                  uVar10 = *(ulong *)(param_1 + 0x140);
                  if (uVar10 < 0xffffffffffffffc0) {
                    puVar19 = (undefined8 *)func_0x0001900cfd70(uVar10 + 0x40,0x100004077774924);
                    if (puVar19 == (undefined8 *)0x0) {
                      local_254 = 0xffffe5b8;
                    }
                    else {
                      uVar9 = *puVar2;
                      uVar23 = *(undefined8 *)(param_1 + 0x266);
                      uVar24 = *(undefined8 *)(param_1 + 0x25e);
                      puVar19[1] = *(undefined8 *)(param_1 + 0x256);
                      *puVar19 = uVar9;
                      puVar19[3] = uVar23;
                      puVar19[2] = uVar24;
                      func_0x0001900cc480(puVar19 + 4,*(undefined8 *)(param_1 + 0x138),
                                          *(undefined8 *)(param_1 + 0x140));
                      puVar2 = (undefined8 *)((long)puVar19 + *(long *)(param_1 + 0x140) + 0x20);
                      uVar23 = *(undefined8 *)(param_1 + 0x1ce);
                      uVar24 = *(undefined8 *)(param_1 + 0x1e6);
                      uVar9 = *(undefined8 *)(param_1 + 0x1de);
                      puVar2[1] = *(undefined8 *)(param_1 + 0x1d6);
                      *puVar2 = uVar23;
                      puVar2[3] = uVar24;
                      puVar2[2] = uVar9;
                      uVar9 = func_0x0001900cf870();
                      iVar7 = func_0x0001900cf130(uVar9,uVar10 + 0x40,puVar19,local_208,
                                                  param_1 + 0x26e);
                      if (iVar7 == 0) {
                        func_0x0001900cc3a0(puVar19);
                        puVar19 = local_268;
                        goto LAB_18bf2a0e8;
                      }
                      local_254 = 0xffffe59e;
                    }
                    goto LAB_18bf29a7c;
                  }
                  goto LAB_18bf2a318;
                }
                piVar16 = *(int **)(param_1 + 0x10);
                if (0x5a < *piVar16) goto LAB_18bf29a74;
                if (*piVar16 == -1) {
                  iVar7 = __LogCategory_Initialize(piVar16,0x5a);
                  if (iVar7 == 0) goto LAB_18bf29a74;
                  piVar16 = *(int **)(param_1 + 0x10);
                }
                pcVar12 = "### PairVerify client M2 failed: get signature failed, %#m\n";
              }
              else {
                piVar16 = *(int **)(param_1 + 0x10);
                if (0x5a < *piVar16) goto LAB_18bf29a74;
                if (*piVar16 == -1) {
                  iVar7 = __LogCategory_Initialize(piVar16,0x5a);
                  if (iVar7 == 0) goto LAB_18bf29a74;
                  piVar16 = *(int **)(param_1 + 0x10);
                }
                pcVar12 = "### PairVerify client M2 failed: find peer failed, id=%.*s, error=%#m\n";
              }
            }
            else {
              piVar16 = *(int **)(param_1 + 0x10);
              if (0x5a < *piVar16) goto LAB_18bf29a74;
              if (*piVar16 == -1) {
                iVar7 = __LogCategory_Initialize(piVar16,0x5a);
                if (iVar7 == 0) goto LAB_18bf29a74;
                piVar16 = *(int **)(param_1 + 0x10);
              }
              pcVar12 = "### PairVerify client M2 failed: get identifier failed, %#m\n";
            }
            goto LAB_18bf2a364;
          }
          if ((*(uint *)(param_1 + 100) & 0x20200000) == 0) {
            local_254 = __PairingSessionAppleIDVerifyPeer(param_1,lVar20,lVar21);
            puVar19 = (undefined8 *)0x0;
            if (local_254 != 0) goto LAB_18bf29a7c;
          }
          else {
LAB_18bf29b50:
            puVar19 = (undefined8 *)0x0;
          }
LAB_18bf2a0e8:
          iVar7 = __PairingSessionVerifyACL(param_1,puVar19);
          if (iVar7 != 0) {
            piVar16 = *(int **)(param_1 + 0x10);
            if (*piVar16 < 0x33) {
              if (*piVar16 == -1) {
                iVar7 = __LogCategory_Initialize(piVar16,0x32);
                if (iVar7 == 0) goto LAB_18bf2a190;
                piVar16 = *(int **)(param_1 + 0x10);
              }
              _LogPrintF(piVar16,
                         "OSStatus _VerifyClientM2(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                         ,0x32,"### PairVerify client -- server lacks ACL: %@\n");
            }
LAB_18bf2a190:
            local_250 = CONCAT71(local_250._1_7_,7);
            local_254 = _TLV8BufferAppend(&local_1c8,7,&local_250,1);
            if (local_254 == 0) {
              local_250 = CONCAT71(local_250._1_7_,3);
              local_254 = _TLV8BufferAppend(&local_1c8,6,&local_250,1);
              if ((local_254 == 0) &&
                 (local_254 = _TLV8BufferDetach(&local_1c8,param_4,param_5), local_254 == 0)) {
                __PairingSessionReset(param_1);
              }
            }
LAB_18bf2a2cc:
            puVar19 = (undefined8 *)0x0;
            goto LAB_18bf29a7c;
          }
          if (*(long *)(param_1 + 0x118) != 0) {
            func_0x0001900caac0();
          }
          *(undefined8 **)(param_1 + 0x118) = puVar19;
          local_268 = (undefined8 *)0x0;
          local_254 = __ExtractAppInfoTLV(param_1,lVar20,lVar21);
          if (local_254 == 0) {
            *(undefined1 *)(param_1 + 0x80) = 3;
            local_254 = __VerifyClientM3(param_1,param_4,param_5);
            puVar19 = (undefined8 *)0x0;
            goto LAB_18bf29a7c;
          }
        }
        else {
          piVar16 = *(int **)(param_1 + 0x10);
          if (*piVar16 < 0x5b) {
            if (*piVar16 == -1) {
              iVar7 = __LogCategory_Initialize(piVar16,0x5a);
              if (iVar7 == 0) goto LAB_18bf299b0;
              piVar16 = *(int **)(param_1 + 0x10);
            }
            _LogPrintF(piVar16,
                       "OSStatus _VerifyClientM2(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                       ,0x5a,"### PairVerify client M2 failed: get PK, %#m\n");
          }
LAB_18bf299b0:
          puVar19 = (undefined8 *)0x0;
          lVar20 = 0;
LAB_18bf29a7c:
          if (local_268 != (undefined8 *)0x0) {
            func_0x0001900caac0();
          }
          if (puVar19 != (undefined8 *)0x0) {
            func_0x0001900cc3a0(puVar19);
          }
        }
        if (lVar20 != 0) {
          func_0x0001900cc3a0(lVar20);
        }
        if (local_1b0 != 0) {
          func_0x0001900cc3a0();
        }
        uVar10 = (ulong)local_254;
        if (local_254 != 0) goto LAB_18bf29c50;
      }
      else {
        if (bVar14 != 1) {
          piVar16 = *(int **)(param_1 + 0x10);
          if (*piVar16 < 0x3d) {
            if (*piVar16 == -1) {
              iVar7 = __LogCategory_Initialize(piVar16,0x3c);
              if (iVar7 == 0) goto LAB_18bf298a0;
              piVar16 = *(int **)(param_1 + 0x10);
            }
            _LogPrintF(piVar16,
                       "OSStatus _VerifyClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                       ,0x3c,"### PairVerify client bad state: %d\n");
          }
LAB_18bf298a0:
          uVar10 = 0xffffe5cb;
          goto LAB_18bf29c50;
        }
        uStack_80 = 0;
        local_88 = 0;
        uStack_90 = 0;
        local_98 = 0;
        uStack_a0 = 0;
        local_a8 = 0;
        uStack_b0 = 0;
        local_b8 = 0;
        uStack_c0 = 0;
        local_c8 = 0;
        uStack_d0 = 0;
        local_d8 = 0;
        uStack_e0 = 0;
        local_e8 = 0;
        uStack_f0 = 0;
        local_f8 = 0;
        uStack_100 = 0;
        local_108 = 0;
        uStack_110 = 0;
        local_118 = 0;
        uStack_120 = 0;
        local_128 = 0;
        uStack_130 = 0;
        local_138 = 0;
        uStack_140 = 0;
        local_148 = 0;
        uStack_150 = 0;
        local_158 = 0;
        uStack_160 = 0;
        local_168 = 0;
        uStack_170 = 0;
        local_178 = 0;
        uStack_180 = 0;
        local_188 = 0;
        uStack_190 = 0;
        local_198 = 0;
        uStack_1a0 = 0;
        local_1a8 = 0;
        local_1c8 = &local_1a8;
        uStack_1b8 = _UNK_18bf721e8;
        local_1c0 = _DAT_18bf721e0;
        local_1b0 = 0;
        if (param_3 != 0) {
LAB_18bf29df0:
          uVar10 = 0xffffe5cf;
          goto LAB_18bf29c50;
        }
        lVar20 = param_1 + 0x1ee;
        _RandomBytes(lVar20,0x20);
        uVar9 = func_0x0001900cf870();
        func_0x0001900cf190(uVar9,0x20,lVar20,0x15,"Pair-Verify-ECDH-Salt",0x15,
                            "Pair-Verify-ECDH-Info",0x20,lVar20);
        func_0x0001900ec2b0(param_1 + 0x1ce,lVar20);
        if ((*(byte *)(param_1 + 100) & 1) != 0) {
          local_208[0] = CONCAT71(local_208[0]._1_7_,7);
          uVar10 = _TLV8BufferAppend(&local_1c8,0,local_208,1);
          if ((int)uVar10 != 0) goto LAB_18bf29c44;
        }
        uVar10 = _TLV8BufferAppend(&local_1c8,6,pbVar18,1);
        if (((((int)uVar10 != 0) ||
             (uVar10 = _TLV8BufferAppend(&local_1c8,3,param_1 + 0x1ce,0x20), (int)uVar10 != 0)) ||
            ((*(long *)(param_1 + 0xd8) != 0 &&
             (uVar10 = _TLV8BufferAppendUInt64(&local_1c8,0x19), (int)uVar10 != 0)))) ||
           (uVar10 = _TLV8BufferDetach(&local_1c8,param_4,param_5), (int)uVar10 != 0))
        goto LAB_18bf29c44;
        *(undefined1 *)(param_1 + 0x80) = 2;
        piVar16 = *(int **)(param_1 + 0x10);
        iVar7 = *piVar16;
        if (iVar7 < 0x1f) {
          if (iVar7 == -1) {
            iVar7 = __LogCategory_Initialize(piVar16,0x1e);
            if (iVar7 == 0) goto LAB_18bf2a2a0;
            piVar16 = *(int **)(param_1 + 0x10);
            iVar7 = *piVar16;
          }
          if ((iVar7 < 0xb) && (iVar7 == -1)) {
            __LogCategory_Initialize(piVar16,10);
          }
          _LogPrintF(piVar16,
                     "OSStatus _VerifyClientM1(PairingSessionRef, const uint8_t *const, const uint8_t *const, uint8_t **, size_t *)"
                     ,0x1e,"PairVerify client M1 -- start request\n%?{end}%1{tlv8}\n");
        }
LAB_18bf2a2a0:
        if (local_1b0 != 0) {
          func_0x0001900cc3a0();
        }
      }
      uVar17 = 0;
LAB_18bf29ab8:
      __PairingSessionUpdateTranscript(param_1,param_2,param_3,*param_4,*param_5);
      uVar10 = 0;
      *param_6 = uVar17;
      goto LAB_18bf29cec;
    }
    uStack_80 = 0;
    local_88 = 0;
    uStack_90 = 0;
    local_98 = 0;
    uStack_a0 = 0;
    local_a8 = 0;
    uStack_b0 = 0;
    local_b8 = 0;
    uStack_c0 = 0;
    local_c8 = 0;
    uStack_d0 = 0;
    local_d8 = 0;
    uStack_e0 = 0;
    local_e8 = 0;
    uStack_f0 = 0;
    local_f8 = 0;
    uStack_100 = 0;
    local_108 = 0;
    uStack_110 = 0;
    local_118 = 0;
    uStack_120 = 0;
    local_128 = 0;
    uStack_130 = 0;
    local_138 = 0;
    uStack_140 = 0;
    local_148 = 0;
    uStack_150 = 0;
    local_158 = 0;
    uStack_160 = 0;
    local_168 = 0;
    uStack_170 = 0;
    local_178 = 0;
    uStack_180 = 0;
    local_188 = 0;
    uStack_190 = 0;
    local_198 = 0;
    uStack_1a0 = 0;
    local_1a8 = 0;
    local_1c8 = &local_1a8;
    uStack_1b8 = _UNK_18bf721e8;
    local_1c0 = _DAT_18bf721e0;
    local_1b0 = 0;
    piVar16 = *(int **)(param_1 + 0x10);
    iVar7 = *piVar16;
    pbVar13 = param_2;
    if (iVar7 < 0x1f) {
      if (iVar7 == -1) {
        iVar7 = __LogCategory_Initialize(piVar16,0x1e);
        if (iVar7 == 0) goto LAB_18bf29b98;
        piVar16 = *(int **)(param_1 + 0x10);
        iVar7 = *piVar16;
      }
      if ((iVar7 < 0xb) && (iVar7 == -1)) {
        __LogCategory_Initialize(piVar16,10);
      }
      _LogPrintF(piVar16,
                 "OSStatus _VerifyClientM4(PairingSessionRef, const uint8_t *const, const uint8_t *const)"
                 ,0x1e,"PairVerify client M4 -- finish response\n%?{end}%1{tlv8}\n");
    }
LAB_18bf29b98:
    do {
      if ((pbVar4 <= pbVar13) || ((ulong)((long)pbVar4 - (long)pbVar13) < 2)) {
LAB_18bf29d28:
        pcVar12 = "PV-Msg04";
        if ((*(uint *)(param_1 + 100) & 0x20000000) != 0) {
          pcVar12 = "PV-Msg4s";
        }
        if ((*(uint *)(param_1 + 100) & 1) == 0) {
          local_208[0] = 0;
          lVar20 = _TLV8CopyCoalesced(param_2,pbVar4,5,local_208,0);
          lVar21 = 0;
          if ((lVar20 == 0) || (local_208[0] == 0)) {
LAB_18bf29db4:
            if ((((*(byte *)(param_1 + 0x67) >> 5 & 1) == 0) ||
                (uVar10 = __PairingSessionAppleIDVerifyPeer(param_1,lVar20,lVar21), (int)uVar10 == 0
                )) && (uVar10 = __ExtractGroupInfoTLV(param_1,lVar20,lVar21), (int)uVar10 == 0)) {
              __UpdatePeerIRKFromTLV(param_1,lVar20,lVar21);
              goto LAB_18bf29efc;
            }
          }
          else if (local_208[0] < 0x10) {
            uVar10 = 0xffffe5a9;
          }
          else {
            lVar21 = lVar20 + (local_208[0] - 0x10);
            uVar10 = __chacha20_poly1305_decrypt_all
                               (param_1 + 0x1ae,pcVar12,8,0,0,lVar20,local_208[0] - 0x10,lVar20,
                                lVar21,0x10);
            if ((int)uVar10 == 0) goto LAB_18bf29db4;
          }
        }
        else {
          uVar8 = __MFiClientVerify(param_1,param_2,param_3,pcVar12,param_1 + 0x28e,0x20,
                                    "MFi-Pair-Verify-Salt",0x14,"MFi-Pair-Verify-Info",0x14,1);
          uVar15 = 0xfffeea17;
          if (uVar8 == 0xfffeea04 || uVar8 == 0) {
            uVar15 = uVar8;
          }
          uVar10 = (ulong)uVar15;
          if (uVar15 != 0) goto LAB_18bf29c44;
          lVar20 = 0;
LAB_18bf29efc:
          if ((*(byte *)(param_1 + 100) >> 1 & 1) != 0) {
            uVar9 = func_0x0001900cf870();
            func_0x0001900cf190(uVar9,0x20,param_1 + 0x28e,0x20,"Pair-Verify-ResumeSessionID-Salt",
                                0x20,"Pair-Verify-ResumeSessionID-Info",8,local_208);
            *(ulong *)(param_1 + 0x188) = local_208[0];
            __PairingSaveResumeState
                      (param_1,*(undefined8 *)(param_1 + 0x138),*(undefined8 *)(param_1 + 0x140),
                       *(undefined8 *)(param_1 + 0x100),*(undefined8 *)(param_1 + 0x108),
                       local_208[0],param_1 + 0x28e);
          }
          *(undefined1 *)(param_1 + 0x80) = 5;
          piVar16 = *(int **)(param_1 + 0x10);
          if (*piVar16 < 0x1f) {
            if (*piVar16 == -1) {
              iVar7 = __LogCategory_Initialize(piVar16,0x1e);
              if (iVar7 == 0) goto LAB_18bf29f9c;
              piVar16 = *(int **)(param_1 + 0x10);
            }
            _LogPrintF(piVar16,
                       "OSStatus _VerifyClientM4(PairingSessionRef, const uint8_t *const, const uint8_t *const)"
                       ,0x1e,"PairVerify client done\n");
          }
LAB_18bf29f9c:
          uVar10 = 0;
        }
        if (lVar20 != 0) {
          func_0x0001900cc3a0(lVar20);
        }
        if (local_1b0 != 0) {
          func_0x0001900cc3a0();
        }
        if ((int)uVar10 != 0) goto LAB_18bf29c50;
        *param_4 = 0;
        *param_5 = 0;
        uVar17 = 1;
        goto LAB_18bf29ab8;
      }
      pbVar3 = pbVar13 + 2;
      pbVar18 = pbVar13 + 1;
      if (pbVar4 < pbVar3 + *pbVar18) goto LAB_18bf29d28;
      bVar14 = *pbVar13;
      pbVar13 = pbVar3 + *pbVar18;
    } while (bVar14 != 7);
    if (*pbVar18 == 1) {
      bVar14 = *pbVar3;
      if (bVar14 < 10) {
        uVar15 = *(uint *)(&DAT_18bf7326c + (ulong)bVar14 * 4);
      }
      else {
        uVar15 = 0xffffe5b1;
        if (bVar14 != 10) {
          uVar15 = 0xffffe5d4;
        }
      }
      uVar10 = (ulong)uVar15;
      piVar16 = *(int **)(param_1 + 0x10);
      if (*piVar16 < 0x33) {
        if (*piVar16 == -1) {
          iVar7 = __LogCategory_Initialize(piVar16,0x32);
          if (iVar7 == 0) goto LAB_18bf29c44;
          piVar16 = *(int **)(param_1 + 0x10);
        }
        _LogPrintF(piVar16,
                   "OSStatus _VerifyClientM4(PairingSessionRef, const uint8_t *const, const uint8_t *const)"
                   ,0x32,"### PairVerify client M4 bad status: 0x%X, %#m\n");
      }
    }
    else {
      uVar10 = 0xffffe5a9;
    }
LAB_18bf29c44:
    if (local_1b0 != 0) {
      func_0x0001900cc3a0();
    }
  }
  else {
    if (param_3 == 0) goto LAB_18bf294cc;
LAB_18bf2947c:
    do {
      if (pbVar13 == pbVar4) {
LAB_18bf2991c:
        uVar10 = 0xffffe5b9;
        goto LAB_18bf29c50;
      }
      if (pbVar4 <= pbVar13) goto LAB_18bf29df0;
      if ((ulong)((long)pbVar4 - (long)pbVar13) < 2) goto LAB_18bf2991c;
      pbVar1 = pbVar13 + 2;
      pbVar3 = pbVar13 + 1;
      if (pbVar4 < pbVar1 + *pbVar3) {
        uVar10 = 0xffffe5a2;
        goto LAB_18bf29c50;
      }
      bVar5 = *pbVar13;
      pbVar13 = pbVar1 + *pbVar3;
    } while (bVar5 != 6);
    if (*pbVar3 == 1) {
      if (*pbVar1 == bVar14) goto LAB_18bf294cc;
      goto LAB_18bf298a0;
    }
    uVar10 = 0xffffe5a9;
  }
LAB_18bf29c50:
  *param_6 = 0;
  piVar16 = *(int **)(param_1 + 0x10);
  iVar7 = *piVar16;
  if (iVar7 < 0x33) {
    if (iVar7 == -1) {
      iVar7 = __LogCategory_Initialize(piVar16,0x32);
      if (iVar7 == 0) goto LAB_18bf29cec;
      piVar16 = *(int **)(param_1 + 0x10);
      iVar7 = *piVar16;
    }
    if ((iVar7 < 0x29) && (iVar7 == -1)) {
      __LogCategory_Initialize(piVar16,0x28);
    }
    _LogPrintF(piVar16,
               "OSStatus _VerifyClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
               ,0x32,"### PairVerify client state %d failed: %#m\n%?{end}%1{tlv8}\n");
  }
LAB_18bf29cec:
  if (*_DAT_1e016af28 == local_78) {
    return uVar10;
  }
  uVar10 = func_0x0001900cc180();
  return uVar10;
}


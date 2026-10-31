/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf24d98
 * original code SHA256: e1cc97639f56abb18621aef2ff3b6b6ada3c88861d78c6ae41598875ac9117b6
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong __SetupClientExchange
                (long param_1,byte *param_2,long param_3,undefined8 *param_4,undefined8 *param_5,
                undefined1 *param_6)

{
  byte *pbVar1;
  byte *pbVar2;
  undefined8 *puVar3;
  byte *pbVar4;
  undefined8 *puVar5;
  byte bVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  char *pcVar15;
  long lVar16;
  byte bVar17;
  byte *pbVar18;
  ulong uVar19;
  byte *pbVar20;
  undefined1 uVar21;
  undefined8 uVar22;
  long lVar23;
  long *plVar24;
  int *piVar25;
  undefined1 auVar26 [16];
  byte *in_stack_fffffffffffffbe0;
  undefined8 local_3e8;
  undefined8 local_3b8;
  long local_3b0;
  undefined8 local_3a8;
  long local_3a0;
  ulong local_398;
  long local_390;
  ulong local_388;
  byte *pbStack_380;
  uint local_374;
  undefined8 local_370;
  undefined8 local_368;
  long local_360;
  undefined8 local_358;
  undefined8 local_350 [8];
  undefined8 *local_310;
  long local_308;
  undefined8 uStack_300;
  long local_2f8;
  undefined8 local_2f0;
  undefined8 uStack_2e8;
  undefined8 local_2e0;
  undefined8 uStack_2d8;
  undefined8 uStack_2d0;
  undefined8 uStack_2c8;
  undefined8 local_2c0;
  undefined8 uStack_2b8;
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined8 local_2a0;
  undefined8 uStack_298;
  undefined8 uStack_290;
  undefined8 uStack_288;
  undefined8 local_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 local_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 local_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 local_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 local_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 local_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 *local_1c0;
  long local_1b8;
  undefined8 uStack_1b0;
  long local_1a8;
  undefined8 local_1a0;
  undefined8 uStack_198;
  undefined8 local_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 local_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  long local_70;
  
  local_70 = *_DAT_1e016af28;
  pbVar4 = param_2 + param_3;
  uStack_88 = 0;
  local_90 = 0;
  uStack_78 = 0;
  uStack_80 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  local_1c0 = &local_1a0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_108 = 0;
  local_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  uStack_128 = 0;
  local_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_148 = 0;
  local_150 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_168 = 0;
  local_170 = 0;
  uStack_158 = 0;
  uStack_160 = 0;
  uStack_188 = 0;
  local_190 = 0;
  uStack_178 = 0;
  uStack_180 = 0;
  uStack_198 = 0;
  local_1a0 = 0;
  local_310 = &local_2f0;
  uStack_1d8 = 0;
  local_1e0 = 0;
  uStack_1c8 = 0;
  uStack_1d0 = 0;
  uStack_1f8 = 0;
  local_200 = 0;
  uStack_1e8 = 0;
  uStack_1f0 = 0;
  uStack_218 = 0;
  local_220 = 0;
  uStack_208 = 0;
  uStack_210 = 0;
  uStack_238 = 0;
  local_240 = 0;
  uStack_228 = 0;
  uStack_230 = 0;
  uStack_258 = 0;
  local_260 = 0;
  uStack_248 = 0;
  uStack_250 = 0;
  uStack_278 = 0;
  local_280 = 0;
  uStack_268 = 0;
  uStack_270 = 0;
  uStack_298 = 0;
  local_2a0 = 0;
  uStack_288 = 0;
  uStack_290 = 0;
  uStack_2b8 = 0;
  local_2c0 = 0;
  uStack_2a8 = 0;
  uStack_2b0 = 0;
  uStack_2d8 = 0;
  local_2e0 = 0;
  uStack_2c8 = 0;
  uStack_2d0 = 0;
  uStack_2e8 = 0;
  local_2f0 = 0;
  local_388 = 0;
  pbStack_380 = (byte *)0x0;
  local_398 = 0;
  local_390 = 0;
  local_3a8 = 0;
  local_3a0 = 0;
  local_3b8 = 0;
  local_3b0 = 0;
  uStack_1b0 = _UNK_18bf721e8;
  local_1b8 = _DAT_18bf721e0;
  local_1a8 = 0;
  uStack_300 = _UNK_18bf721e8;
  local_308 = _DAT_18bf721e0;
  local_2f8 = 0;
  pbVar20 = (byte *)(param_1 + 0x80);
  bVar17 = *pbVar20;
  if (bVar17 == 0) {
    bVar17 = 1;
    *pbVar20 = 1;
  }
  pbVar18 = param_2;
  if (param_3 != 0) {
    do {
      if (pbVar18 == pbVar4) {
LAB_18bf252f4:
        local_374 = 0xffffe5b9;
LAB_18bf25308:
        lVar23 = 0;
        goto LAB_18bf251a8;
      }
      if (pbVar4 <= pbVar18) {
        local_374 = 0xffffe5cf;
        goto LAB_18bf25308;
      }
      if ((ulong)((long)pbVar4 - (long)pbVar18) < 2) goto LAB_18bf252f4;
      pbVar2 = pbVar18 + 2;
      pbVar1 = pbVar18 + 1;
      uVar19 = (ulong)*pbVar1;
      if (pbVar4 < pbVar2 + uVar19) {
        local_374 = 0xffffe5a2;
        goto LAB_18bf25308;
      }
      bVar6 = *pbVar18;
      pbVar18 = pbVar2 + uVar19;
    } while (bVar6 != 6);
    local_388 = uVar19;
    pbStack_380 = pbVar2;
    if (*pbVar1 != 1) goto LAB_18bf263e0;
    if (*pbVar2 == bVar17) goto LAB_18bf24ef8;
    goto LAB_18bf2519c;
  }
LAB_18bf24ef8:
  local_374 = 0;
  if (bVar17 < 3) {
    if (bVar17 != 1) {
      if (bVar17 == 2) {
        piVar25 = *(int **)(param_1 + 0x10);
        iVar9 = *piVar25;
        pbVar18 = param_2;
        if (iVar9 < 0x1f) {
          if (iVar9 == -1) {
            iVar9 = __LogCategory_Initialize(piVar25,0x1e);
            if (iVar9 == 0) goto LAB_18bf254bc;
            piVar25 = *(int **)(param_1 + 0x10);
            iVar9 = *piVar25;
          }
          if ((iVar9 < 0xb) && (iVar9 == -1)) {
            __LogCategory_Initialize(piVar25,10);
          }
          _LogPrintF(piVar25,
                     "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                     ,0x1e,"PairSetup client M2 -- start response\n%?{end}%1{tlv8}\n");
        }
LAB_18bf254bc:
        do {
          if (pbVar18 == pbVar4) {
LAB_18bf25928:
            local_374 = 0xffffe5b9;
LAB_18bf25ab8:
            uVar8 = _TLV8GetUInt64(param_2,pbVar4,0x13,0,0);
            *(undefined4 *)(param_1 + 0x128) = uVar8;
            uVar19 = _TLV8GetUInt64(param_2,pbVar4,0x1f,0,0);
            *(ulong *)(param_1 + 0x130) = uVar19;
            uVar19 = uVar19 & 3;
            if ((((uint)*(ulong *)(param_1 + 0x68) >> 1 & 1) != 0) && (uVar19 == 0)) {
              piVar25 = *(int **)(param_1 + 0x10);
              if (*piVar25 < 0x33) {
                if (*piVar25 == -1) {
                  iVar9 = __LogCategory_Initialize(piVar25,0x32);
                  if (iVar9 == 0) goto LAB_18bf25fa4;
                  piVar25 = *(int **)(param_1 + 0x10);
                }
                _LogPrintF(piVar25,
                           "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                           ,0x32,"### PairSetup client SPAKE2+ not supported by server");
              }
LAB_18bf25fa4:
              lVar23 = 0;
              local_374 = 0xffffe5b1;
              goto LAB_18bf251a8;
            }
            if ((*(ulong *)(param_1 + 0x68) & 3) == 0) {
              *(undefined1 *)(param_1 + 0x2c1) = 0;
LAB_18bf25e08:
              if (*(long *)(param_1 + 0x2d8) != 0) {
                _SRPDelete_libsrp();
                *(undefined8 *)(param_1 + 0x2d8) = 0;
              }
              lVar23 = func_0x0001900cc460(1,0x38,0x103004063a0f53d);
              if (lVar23 == 0) goto LAB_18bf26d54;
              *(long *)(param_1 + 0x2d8) = lVar23;
              local_374 = 0;
              if (*(long *)(param_1 + 0x2f0) != 0) {
                func_0x0001900cc3a0();
                *(undefined8 *)(param_1 + 0x2f0) = 0;
              }
              *(undefined8 *)(param_1 + 0x2f8) = 0;
              uVar11 = _TLV8CopyCoalesced(param_2,pbVar4,2,(ulong *)(param_1 + 0x2f8),&local_374);
              *(undefined8 *)(param_1 + 0x2f0) = uVar11;
              if (local_374 != 0) goto LAB_18bf2668c;
              if (*(ulong *)(param_1 + 0x2f8) < 0x10) goto LAB_18bf263e0;
              if (*(long *)(param_1 + 0x2e0) != 0) {
                func_0x0001900cc3a0();
                *(undefined8 *)(param_1 + 0x2e0) = 0;
              }
              *(undefined8 *)(param_1 + 0x2e8) = 0;
              uVar11 = _TLV8CopyCoalesced(param_2,pbVar4,3,(long *)(param_1 + 0x2e8),&local_374);
              *(undefined8 *)(param_1 + 0x2e0) = uVar11;
              if (local_374 != 0) goto LAB_18bf2668c;
              if (*(long *)(param_1 + 0x2e8) == 0) goto LAB_18bf263e0;
            }
            else {
              *(bool *)(param_1 + 0x2c1) = uVar19 != 0;
              if (uVar19 == 0) goto LAB_18bf25e08;
            }
            lVar23 = _TLV8GetUInt64(param_2,pbVar4,0x1b,0,0);
            if (lVar23 != 0) {
              lVar14 = _CFNumberCreateInt64();
              lVar23 = 0;
              if (lVar14 == 0) goto LAB_18bf26d8c;
              _PairingSessionSetProperty(param_1,&cfstringStruct_1e9b942c0,lVar14);
              func_0x0001900caac0(lVar14);
            }
            *(undefined1 *)(param_1 + 0x80) = 3;
            if ((*(long *)(param_1 + 400) == 0) || (*(long *)(param_1 + 0x198) == 0)) {
              if (*(code **)(param_1 + 0x30) == (code *)0x0) goto LAB_18bf26600;
              uVar7 = *(uint *)(param_1 + 100);
              if (*(char *)(param_1 + 0x1a0) != '\0') {
                uVar7 = *(uint *)(param_1 + 100) | 0x10000;
              }
              local_374 = (**(code **)(param_1 + 0x30))
                                    (uVar7,0xffffffff,*(undefined8 *)(param_1 + 0x18));
              if (local_374 != 0) goto LAB_18bf2668c;
              if ((*(long *)(param_1 + 400) == 0) ||
                 (local_374 = 0, *(long *)(param_1 + 0x198) == 0)) {
                lVar23 = 0;
                local_374 = 0xffffe58d;
                goto LAB_18bf251a8;
              }
            }
            lVar23 = 0;
            goto LAB_18bf24fac;
          }
          if (pbVar4 <= pbVar18) {
            local_374 = 0xffffe5cf;
            goto LAB_18bf25ab8;
          }
          if ((ulong)((long)pbVar4 - (long)pbVar18) < 2) goto LAB_18bf25928;
          pbVar2 = pbVar18 + 2;
          pbVar1 = pbVar18 + 1;
          uVar19 = (ulong)*pbVar1;
          if (pbVar4 < pbVar2 + uVar19) {
            local_374 = 0xffffe5a2;
            goto LAB_18bf25ab8;
          }
          bVar17 = *pbVar18;
          pbVar18 = pbVar2 + uVar19;
        } while (bVar17 != 7);
        local_374 = 0;
        local_388 = uVar19;
        pbStack_380 = pbVar2;
        if (*pbVar1 != 1) goto LAB_18bf263e0;
        bVar17 = *pbVar2;
        if (bVar17 < 10) {
          uVar7 = 0xffffe5af;
          switch(bVar17) {
          case 1:
            uVar7 = 0xffffe5d4;
            break;
          case 2:
            uVar7 = 0xffffe59e;
            break;
          case 3:
            uVar19 = _TLV8GetUInt64(param_2,pbVar4,8,&local_374,0);
            if (local_374 == 0) {
              if (uVar19 >> 0x1f == 0) {
                __PairingSessionReset(param_1);
                if (*(code **)(param_1 + 0x30) == (code *)0x0) goto LAB_18bf26600;
                uVar7 = (**(code **)(param_1 + 0x30))
                                  (*(uint *)(param_1 + 100) | 0x20000,uVar19,
                                   *(undefined8 *)(param_1 + 0x18));
                lVar23 = 0;
                local_374 = 0xffffe58d;
                if (uVar7 != 0) {
                  local_374 = uVar7;
                }
              }
              else {
                lVar23 = 0;
                local_374 = 0xffffe5ca;
              }
              goto LAB_18bf251a8;
            }
            goto LAB_18bf2668c;
          case 4:
            uVar7 = 0xffffe5b9;
            break;
          case 5:
            uVar7 = 0xffffe595;
            break;
          case 6:
            uVar7 = 0xffffe594;
            break;
          case 7:
            uVar7 = 0xffffe58b;
            break;
          case 8:
            uVar7 = 0xfffeea18;
            break;
          case 9:
            uVar7 = 0xffffe588;
          }
        }
        else {
          uVar7 = 0xffffe5b1;
          if (bVar17 != 10) {
            uVar7 = 0xffffe5d4;
          }
        }
        local_374 = uVar7;
        piVar25 = *(int **)(param_1 + 0x10);
        if (0x32 < *piVar25) goto LAB_18bf2668c;
        if (*piVar25 == -1) {
          iVar9 = __LogCategory_Initialize(piVar25,0x32);
          if (iVar9 == 0) goto LAB_18bf25738;
          piVar25 = *(int **)(param_1 + 0x10);
        }
        pcVar15 = "### PairSetup client M2 bad status: 0x%X, %#m\n";
        goto LAB_18bf25730;
      }
LAB_18bf250e4:
      piVar25 = *(int **)(param_1 + 0x10);
      if (*piVar25 < 0x3d) {
        if (*piVar25 == -1) {
          iVar9 = __LogCategory_Initialize(piVar25,0x3c);
          if (iVar9 == 0) goto LAB_18bf2519c;
          piVar25 = *(int **)(param_1 + 0x10);
        }
        _LogPrintF(piVar25,
                   "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                   ,0x3c,"### PairSetup client bad state: %d\n");
      }
LAB_18bf2519c:
      lVar23 = 0;
      local_374 = 0xffffe5cb;
      goto LAB_18bf251a8;
    }
    if (param_3 != 0) {
      lVar23 = 0;
      local_374 = 0xffffe5cf;
      goto LAB_18bf251a8;
    }
    local_374 = _TLV8BufferAppendUInt64(&local_1c0,0,*(uint *)(param_1 + 100) & 1);
    if ((local_374 != 0) || (local_374 = _TLV8BufferAppend(&local_1c0,6,pbVar20,1), local_374 != 0))
    {
LAB_18bf2668c:
      uVar21 = 0;
      lVar23 = 0;
      goto LAB_18bf26694;
    }
    uVar7 = 0;
    if (((((*(uint *)(param_1 + 100) & 0x5770ff34) != 0) &&
         (((*(uint *)(param_1 + 100) & 0x7770ff10) != 0 &&
          (local_374 = _TLV8BufferAppendUInt64(&local_1c0,0x13), uVar7 = local_374, local_374 != 0))
         )) || ((local_374 = uVar7, *(long *)(param_1 + 0x68) != 0 &&
                (local_374 = _TLV8BufferAppendUInt64(&local_1c0,0x1f), local_374 != 0)))) ||
       (local_374 = _TLV8BufferDetach(&local_1c0,param_4,param_5), local_374 != 0))
    goto LAB_18bf2668c;
    *(undefined1 *)(param_1 + 0x80) = 2;
    piVar25 = *(int **)(param_1 + 0x10);
    iVar9 = *piVar25;
    if (iVar9 < 0x1f) {
      if (iVar9 == -1) {
        iVar9 = __LogCategory_Initialize(piVar25,0x1e);
        if (iVar9 == 0) goto LAB_18bf26574;
        piVar25 = *(int **)(param_1 + 0x10);
        iVar9 = *piVar25;
      }
      if ((iVar9 < 0xb) && (iVar9 == -1)) {
        __LogCategory_Initialize(piVar25,10);
      }
      _LogPrintF(piVar25,
                 "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                 ,0x1e,"PairSetup client M1 -- start request\n%?{end}%1{tlv8}\n");
    }
LAB_18bf26574:
    uVar21 = 0;
LAB_18bf26594:
    lVar23 = 0;
    local_374 = 0;
    goto LAB_18bf2574c;
  }
  if (bVar17 != 3) {
    if (bVar17 == 4) {
      piVar25 = *(int **)(param_1 + 0x10);
      iVar9 = *piVar25;
      pbVar18 = param_2;
      if (iVar9 < 0x1f) {
        if (iVar9 == -1) {
          iVar9 = __LogCategory_Initialize(piVar25,0x1e);
          if (iVar9 == 0) goto LAB_18bf25354;
          piVar25 = *(int **)(param_1 + 0x10);
          iVar9 = *piVar25;
        }
        if ((iVar9 < 0xb) && (iVar9 == -1)) {
          __LogCategory_Initialize(piVar25,10);
        }
        in_stack_fffffffffffffbe0 = param_2;
        _LogPrintF(piVar25,
                   "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                   ,0x1e,"PairSetup client M4 -- verify response\n%?{end}%1{tlv8}\n");
      }
LAB_18bf25354:
      do {
        if (pbVar18 == pbVar4) {
LAB_18bf25920:
          local_374 = 0xffffe5b9;
LAB_18bf25974:
          if (*(char *)(param_1 + 0x2c1) == '\0') {
            if (*(long *)(param_1 + 0x2d8) == 0) goto LAB_18bf268b4;
            local_374 = _TLV8GetOrCopyCoalesced
                                  (param_2,pbVar4,4,&pbStack_380,&local_388,&local_390,0);
            if (local_374 != 0) goto LAB_18bf2668c;
            local_374 = _SRPClientVerify_libsrp
                                  (*(undefined8 *)(param_1 + 0x2d8),pbStack_380,local_388);
            if (local_390 != 0) {
              func_0x0001900cc3a0(local_390);
              local_390 = 0;
            }
            if (local_374 != 0) {
              lVar23 = 0;
              goto LAB_18bf26d9c;
            }
            if (*(long *)(param_1 + 0x2d8) != 0) {
              _SRPDelete_libsrp();
              *(undefined8 *)(param_1 + 0x2d8) = 0;
            }
          }
          else {
            local_358 = 0;
            local_350[0] = 0;
            local_360 = 0;
            uVar7 = _TLV8GetOrCopyCoalesced(param_2,pbVar4,0x23,local_350,&local_358,&local_360,0);
            if (uVar7 != 0) {
              piVar25 = *(int **)(param_1 + 0x10);
              if (0x5a < *piVar25) goto switchD_18bf253d0_caseD_2;
              if (*piVar25 == -1) {
                iVar9 = __LogCategory_Initialize(piVar25,0x5a);
                if (iVar9 == 0) goto switchD_18bf253d0_caseD_2;
                piVar25 = *(int **)(param_1 + 0x10);
              }
              _LogPrintF_safe(piVar25,
                              "OSStatus _SetupClientSPAKE2Verify(PairingSessionRef, const uint8_t *, const uint8_t *const, TLV8Buffer *)"
                              ,0x5a,"### PairSetup SPAKE2 get M2 ShareVData failed: %d");
              goto switchD_18bf253d0_caseD_2;
            }
            uVar11 = func_0x0001900cc540(DAT_1e0928768);
            auVar26 = func_0x0001900cc520(_DAT_1e00e6008);
            auVar26 = func_0x00019000c8e0(auVar26._0_8_,auVar26._8_8_,local_350[0],local_358);
            func_0x000190039270(uVar11,auVar26._8_8_,auVar26._0_8_);
            func_0x0001900cc6c0();
            if (local_360 != 0) {
              func_0x0001900cc3a0();
              local_360 = 0;
            }
            uVar7 = _TLV8GetOrCopyCoalesced(param_2,pbVar4,0x21,local_350,&local_358,&local_360,0);
            if (uVar7 != 0) {
              piVar25 = *(int **)(param_1 + 0x10);
              if (*piVar25 < 0x5b) {
                if (*piVar25 == -1) {
                  iVar9 = __LogCategory_Initialize(piVar25,0x5a);
                  if (iVar9 == 0) goto LAB_18bf26500;
                  piVar25 = *(int **)(param_1 + 0x10);
                }
                _LogPrintF_safe(piVar25,
                                "OSStatus _SetupClientSPAKE2Verify(PairingSessionRef, const uint8_t *, const uint8_t *const, TLV8Buffer *)"
                                ,0x5a,"### PairSetup SPAKE2 get M2 ConfirmVData failed: %d");
              }
LAB_18bf26500:
              func_0x0001900cc6a0();
              goto switchD_18bf253d0_caseD_2;
            }
            auVar26 = func_0x0001900cc520(_DAT_1e00e6008);
            auVar26 = func_0x00019000c8e0(auVar26._0_8_,auVar26._8_8_,local_350[0],local_358);
            func_0x000190038b30(uVar11,auVar26._8_8_,auVar26._0_8_);
            func_0x0001900cc6c0();
            if (local_360 != 0) {
              func_0x0001900cc3a0();
              local_360 = 0;
            }
            auVar26 = func_0x0001900cc8c0(*(undefined8 *)(param_1 + 0x2c8));
            lVar23 = auVar26._0_8_;
            if (lVar23 == 0) {
              piVar25 = *(int **)(param_1 + 0x10);
              if (*piVar25 < 0x5b) {
                if (*piVar25 == -1) {
                  iVar9 = __LogCategory_Initialize(piVar25,0x5a);
                  if (iVar9 == 0) goto LAB_18bf268a4;
                  piVar25 = *(int **)(param_1 + 0x10);
                }
                _LogPrintF_safe(piVar25,
                                "OSStatus _SetupClientSPAKE2Verify(PairingSessionRef, const uint8_t *, const uint8_t *const, TLV8Buffer *)"
                                ,0x5a,"### PairSetup client SPAKE2 verify failed: no prover");
              }
LAB_18bf268a4:
              func_0x0001900cc6a0();
              uVar7 = 0xffffe5a7;
              goto switchD_18bf253d0_caseD_2;
            }
            local_368 = 0;
            func_0x000190037ae0(lVar23,auVar26._8_8_,uVar11,&local_368);
            lVar14 = func_0x0001900cc570();
            auVar26 = func_0x0001900cc8c0(local_368);
            local_3e8 = auVar26._0_8_;
            if (lVar14 == 0) {
              piVar25 = *(int **)(param_1 + 0x10);
              if (*piVar25 < 0x5b) {
                if (*piVar25 == -1) {
                  iVar9 = __LogCategory_Initialize(piVar25,0x5a);
                  if (iVar9 == 0) {
                    uVar7 = 0xffffe59e;
                    goto LAB_18bf26cd4;
                  }
                  piVar25 = *(int **)(param_1 + 0x10);
                }
                _NSPrintF("%{error}");
                func_0x0001900cc570();
                _LogPrintF_safe(piVar25,
                                "OSStatus _SetupClientSPAKE2Verify(PairingSessionRef, const uint8_t *, const uint8_t *const, TLV8Buffer *)"
                                ,0x5a,"### PairSetup client SPAKE2 generate M3 failed: %@");
                uVar7 = 0xffffe59e;
                goto LAB_18bf26cd0;
              }
              uVar7 = 0xffffe59e;
            }
            else {
              local_370 = local_3e8;
              func_0x000190037a60(lVar23,auVar26._8_8_,&local_370);
              uVar11 = func_0x0001900cc570();
              local_3e8 = func_0x0001900cc8c0(local_370);
              func_0x0001900cc6f0();
              if (*(long *)(param_1 + 0x2c8) != 0) {
                func_0x0001900caac0();
                *(undefined8 *)(param_1 + 0x2c8) = 0;
              }
              lVar12 = func_0x0001900026d0(uVar11);
              if (lVar12 == 0) {
                piVar25 = *(int **)(param_1 + 0x10);
                if (0x5a < *piVar25) {
                  uVar7 = 0xffffe5d4;
                  goto LAB_18bf26cd0;
                }
                if (*piVar25 == -1) {
                  iVar9 = __LogCategory_Initialize(piVar25,0x5a);
                  if (iVar9 != 0) {
                    piVar25 = *(int **)(param_1 + 0x10);
                    goto LAB_18bf267f8;
                  }
                }
                else {
LAB_18bf267f8:
                  _NSPrintF("%{error}");
                  func_0x0001900cc570();
                  _LogPrintF_safe(piVar25,
                                  "OSStatus _SetupClientSPAKE2Verify(PairingSessionRef, const uint8_t *, const uint8_t *const, TLV8Buffer *)"
                                  ,0x5a,"### PairSetup client SPAKE2 finish failed: %@");
                  func_0x0001900cc6c0();
                }
                uVar7 = 0xffffe5d4;
              }
              else {
                lVar13 = func_0x0001900cfd70(lVar12,0x100004077774924);
                if (lVar13 == 0) {
                  piVar25 = *(int **)(param_1 + 0x10);
                  if (*piVar25 < 0x5b) {
                    if (*piVar25 == -1) {
                      iVar9 = __LogCategory_Initialize(piVar25,0x5a);
                      if (iVar9 == 0) goto LAB_18bf26cc8;
                      piVar25 = *(int **)(param_1 + 0x10);
                    }
                    _LogPrintF_safe(piVar25,
                                    "OSStatus _SetupClientSPAKE2Verify(PairingSessionRef, const uint8_t *, const uint8_t *const, TLV8Buffer *)"
                                    ,0x5a,"### PairSetup client SPAKE2 malloc secret failed");
                  }
LAB_18bf26cc8:
                  uVar7 = 0xffffe5b8;
                }
                else {
                  func_0x0001900cc750(uVar11);
                  uVar11 = func_0x0001900018a0();
                  func_0x0001900cc480(lVar13,uVar11,lVar12);
                  if ((*(long *)(param_1 + 0x300) != 0) &&
                     (func_0x0001900cfdb0(*(long *)(param_1 + 0x300),
                                          *(undefined8 *)(param_1 + 0x308),0,
                                          *(undefined8 *)(param_1 + 0x308)),
                     *(long *)(param_1 + 0x300) != 0)) {
                    func_0x0001900cc3a0();
                  }
                  *(long *)(param_1 + 0x300) = lVar13;
                  *(long *)(param_1 + 0x308) = lVar12;
                  func_0x000190037510(lVar14);
                  func_0x0001900cc570();
                  func_0x0001900cc750();
                  uVar11 = func_0x0001900018a0();
                  func_0x000190037510(lVar14);
                  func_0x0001900cc570();
                  uVar22 = func_0x0001900026d0();
                  uVar7 = _TLV8BufferAppend(&local_1c0,0x20,uVar11,uVar22);
                  func_0x0001900cc700();
                  func_0x0001900cc6c0();
                  if (uVar7 == 0) {
                    uVar7 = 0;
                  }
                  else {
                    piVar25 = *(int **)(param_1 + 0x10);
                    if (*piVar25 < 0x5b) {
                      if (*piVar25 == -1) {
                        iVar9 = __LogCategory_Initialize(piVar25,0x5a);
                        if (iVar9 == 0) goto LAB_18bf26cd0;
                        piVar25 = *(int **)(param_1 + 0x10);
                      }
                      _LogPrintF_safe(piVar25,
                                      "OSStatus _SetupClientSPAKE2Verify(PairingSessionRef, const uint8_t *, const uint8_t *const, TLV8Buffer *)"
                                      ,0x5a,
                                      "### PairSetup client SPAKE2 add M3 ConfirmPData TLV failed: %d"
                                     );
                    }
                  }
                }
              }
LAB_18bf26cd0:
              func_0x0001900cc6a0();
            }
LAB_18bf26cd4:
            func_0x0001900cc720(lVar14);
            func_0x0001900cc720(local_3e8);
            func_0x0001900cc720(lVar23);
            func_0x0001900cc6a0();
            local_374 = uVar7;
            if (uVar7 != 0) goto switchD_18bf253d0_caseD_2;
          }
          if ((*(long *)(param_1 + 0x300) == 0) || (*(long *)(param_1 + 0x308) == 0))
          goto LAB_18bf268b4;
          _CryptoHKDF(&__kCryptoHashDescriptor_SHA512,*(long *)(param_1 + 0x300),
                      *(long *)(param_1 + 0x308),"Pair-Setup-Encrypt-Salt",0x17,
                      "Pair-Setup-Encrypt-Info",0x17,0x20,param_1 + 0x1ae);
          if ((*(byte *)(param_1 + 100) & 1) == 0) {
            __ClientDecryptExtra(param_1,param_2,param_3);
          }
          else {
            uVar7 = __MFiClientVerify(param_1,param_2,param_3,"PS-Msg04",
                                      *(undefined8 *)(param_1 + 0x300),
                                      *(undefined8 *)(param_1 + 0x308),"MFi-Pair-Setup-Salt",0x13,
                                      "MFi-Pair-Setup-Info",0x13,
                                      (ulong)in_stack_fffffffffffffbe0 & 0xffffffffffffff00);
            local_374 = 0xfffeea17;
            if (uVar7 == 0xfffeea04 || uVar7 == 0) {
              local_374 = uVar7;
            }
            if (local_374 != 0) goto LAB_18bf2668c;
          }
          if (((*(uint *)(param_1 + 100) >> 4 & 1) != 0) ||
             (((*(uint *)(param_1 + 0x128) ^ *(uint *)(param_1 + 100)) >> 9 & 1) != 0)) {
            *(undefined1 *)(param_1 + 0x80) = 7;
            *param_4 = 0;
            *param_5 = 0;
            piVar25 = *(int **)(param_1 + 0x10);
            if (*piVar25 < 0x1f) {
              if (*piVar25 == -1) {
                iVar9 = __LogCategory_Initialize(piVar25,0x1e);
                if (iVar9 == 0) goto LAB_18bf2658c;
                piVar25 = *(int **)(param_1 + 0x10);
              }
              _LogPrintF(piVar25,
                         "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                         ,0x1e,"PairSetup transient client done -- server authenticated\n");
            }
LAB_18bf2658c:
            uVar21 = 1;
            goto LAB_18bf26594;
          }
          if (*(code **)(param_1 + 0x380) != (code *)0x0) {
            (**(code **)(param_1 + 0x380))(3,0,*(undefined8 *)(param_1 + 0x388));
          }
          plVar24 = (long *)(param_1 + 0xc0);
          *(undefined1 *)(param_1 + 0x80) = 5;
          if (*plVar24 != 0) {
            func_0x0001900cc3a0();
            *plVar24 = 0;
          }
          *(undefined8 *)(param_1 + 200) = 0;
          puVar3 = (undefined8 *)(param_1 + 0x20e);
          local_374 = _PairingSessionCopyIdentity(param_1,1,plVar24,puVar3,param_1 + 0x22e);
          if (local_374 != 0) goto LAB_18bf2668c;
          uVar19 = func_0x0001900d0320(*(undefined8 *)(param_1 + 0xc0));
          *(ulong *)(param_1 + 200) = uVar19;
          if (uVar19 == 0) {
            lVar23 = 0;
            local_374 = 0xffffe5cc;
            goto LAB_18bf251a8;
          }
          if (0xffffffffffffffbf < uVar19) goto LAB_18bf263e0;
          uVar19 = uVar19 + 0x40;
          local_388 = uVar19;
          lVar23 = func_0x0001900cfd70(uVar19,0x100004077774924);
          local_390 = lVar23;
          if (lVar23 == 0) goto LAB_18bf26d54;
          _CryptoHKDF(&__kCryptoHashDescriptor_SHA512,*(undefined8 *)(param_1 + 0x300),
                      *(undefined8 *)(param_1 + 0x308),"Pair-Setup-Controller-Sign-Salt",0x1f,
                      "Pair-Setup-Controller-Sign-Info",0x1f,0x20,lVar23);
          func_0x0001900cc480(lVar23 + 0x20,*(undefined8 *)(param_1 + 0xc0),
                              *(undefined8 *)(param_1 + 200));
          puVar5 = (undefined8 *)(lVar23 + *(long *)(param_1 + 200) + 0x20);
          uVar11 = *puVar3;
          uVar10 = *(undefined8 *)(param_1 + 0x226);
          uVar22 = *(undefined8 *)(param_1 + 0x21e);
          puVar5[1] = *(undefined8 *)(param_1 + 0x216);
          *puVar5 = uVar11;
          puVar5[3] = uVar10;
          puVar5[2] = uVar22;
          if (*(code **)(param_1 + 0x3c0) == (code *)0x0) {
            uVar11 = func_0x0001900cf870();
            func_0x0001900ec2c0(uVar11,local_350,uVar19,lVar23,puVar3,param_1 + 0x22e);
          }
          else {
            (**(code **)(param_1 + 0x3c0))
                      (*(undefined4 *)(param_1 + 100),lVar23,uVar19,local_350,
                       *(undefined8 *)(param_1 + 0x3c8));
          }
          func_0x0001900cc3a0(lVar23);
          local_390 = 0;
          local_374 = _TLV8BufferAppend(&local_310,1,*(undefined8 *)(param_1 + 0xc0),
                                        *(undefined8 *)(param_1 + 200));
          if (((local_374 != 0) ||
              (local_374 = _TLV8BufferAppend(&local_310,3,puVar3,0x20), local_374 != 0)) ||
             (local_374 = _TLV8BufferAppend(&local_310,10,local_350,0x40), local_374 != 0))
          goto LAB_18bf2668c;
          if (*(long *)(param_1 + 0xb8) != 0) {
            lVar14 = _OPACKEncoderCreateDataMutable(*(long *)(param_1 + 0xb8),0,&local_374);
            lVar23 = 0;
            if (lVar14 == 0) goto LAB_18bf25740;
            uVar11 = func_0x0001900caa40(lVar14);
            uVar22 = func_0x0001900caa50(lVar14);
            local_374 = _TLV8BufferAppend(&local_310,0x12,uVar11,uVar22);
            func_0x0001900caac0(lVar14);
            if (local_374 != 0) goto LAB_18bf26ed4;
          }
          if ((*(long *)(param_1 + 0xe0) != 0) &&
             (local_374 = _TLV8BufferAppend(&local_310,0x10,*(long *)(param_1 + 0xe0),
                                            *(undefined8 *)(param_1 + 0xe8)), local_374 != 0))
          goto LAB_18bf2668c;
          if (((*(uint *)(param_1 + 100) & 0x5770ff34) != 0) &&
             (((*(uint *)(param_1 + 100) & 0x1000e001) == 0 &&
              (lVar23 = __PairingSessionGetSelfInfo(param_1), lVar23 != 0)))) {
            lVar14 = _OPACKEncoderCreateDataMutable(lVar23,0,&local_374);
            lVar23 = 0;
            if (lVar14 == 0) goto LAB_18bf25740;
            uVar11 = func_0x0001900caa40(lVar14);
            uVar22 = func_0x0001900caa50(lVar14);
            local_374 = _TLV8BufferAppend(&local_310,0x11,uVar11,uVar22);
            func_0x0001900caac0(lVar14);
            if (local_374 != 0) goto LAB_18bf2668c;
          }
          uVar22 = *(undefined8 *)(param_1 + 0x168);
          uVar11 = func_0x0001900cddf0();
          lVar23 = _CFDictionaryGetTypedValue(uVar22,&cfstringStruct_1e9b96920,uVar11,0);
          if (lVar23 != 0) {
            uVar11 = func_0x0001900caa40();
            uVar22 = func_0x0001900caa50(lVar23);
            local_374 = _TLV8BufferAppend(&local_310,0x1a,uVar11,uVar22);
            if (local_374 != 0) goto LAB_18bf2668c;
          }
          local_374 = __AddAppInfoTLV(*(undefined8 *)(param_1 + 0x168),&local_310);
          if (local_374 != 0) goto LAB_18bf2668c;
          lVar14 = func_0x0001900cfd70(local_308 + 0x10,0x100004077774924);
          lVar23 = 0;
          local_390 = lVar14;
          if (lVar14 == 0) goto LAB_18bf26d8c;
          __chacha20_poly1305_encrypt_all
                    (param_1 + 0x1ae,"PS-Msg05",8,0,0,local_310,local_308,lVar14,lVar14 + local_308)
          ;
          local_374 = _TLV8BufferAppend(&local_1c0,5,lVar14,local_308 + 0x10);
          if (local_374 != 0) goto LAB_18bf2668c;
          func_0x0001900cc3a0(lVar14);
          local_390 = 0;
          local_374 = _TLV8BufferAppend(&local_1c0,6,pbVar20,1);
          if ((local_374 != 0) ||
             (local_374 = _TLV8BufferDetach(&local_1c0,param_4,param_5), local_374 != 0))
          goto LAB_18bf2668c;
          *(undefined1 *)(param_1 + 0x80) = 6;
          piVar25 = *(int **)(param_1 + 0x10);
          iVar9 = *piVar25;
          if (iVar9 < 0x1f) {
            if (iVar9 == -1) {
              iVar9 = __LogCategory_Initialize(piVar25,0x1e);
              if (iVar9 == 0) goto LAB_18bf26e04;
              piVar25 = *(int **)(param_1 + 0x10);
              iVar9 = *piVar25;
            }
            if ((iVar9 < 0xb) && (iVar9 == -1)) {
              __LogCategory_Initialize(piVar25,10);
            }
            _LogPrintF(piVar25,
                       "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                       ,0x1e,"PairSetup client M5 -- exchange request\n%?{end}%1{tlv8}\n");
            uVar21 = 0;
          }
          else {
LAB_18bf26e04:
            uVar21 = 0;
          }
          goto LAB_18bf26594;
        }
        if (pbVar4 <= pbVar18) {
          local_374 = 0xffffe5cf;
          goto LAB_18bf25974;
        }
        if ((ulong)((long)pbVar4 - (long)pbVar18) < 2) goto LAB_18bf25920;
        pbVar2 = pbVar18 + 2;
        pbVar1 = pbVar18 + 1;
        uVar19 = (ulong)*pbVar1;
        if (pbVar4 < pbVar2 + uVar19) {
          local_374 = 0xffffe5a2;
          goto LAB_18bf25974;
        }
        bVar17 = *pbVar18;
        pbVar18 = pbVar2 + uVar19;
      } while (bVar17 != 7);
      local_374 = 0;
      local_388 = uVar19;
      pbStack_380 = pbVar2;
      if (*pbVar1 != 1) goto LAB_18bf263e0;
      bVar17 = *pbVar2;
      if (bVar17 < 10) {
        uVar7 = local_374;
        local_374 = 0xffffe5af;
        switch(bVar17) {
        case 1:
          local_374 = 0xffffe5d4;
          break;
        case 2:
switchD_18bf253d0_caseD_2:
          local_374 = uVar7;
          local_374 = __SetupClientAuthenticationFailed(param_1,param_2,pbVar4);
          lVar23 = 0;
          goto LAB_18bf25740;
        case 3:
          local_374 = 0xffffe598;
          break;
        case 4:
          local_374 = 0xffffe5b9;
          break;
        case 5:
          local_374 = 0xffffe595;
          break;
        case 6:
          local_374 = 0xffffe594;
          break;
        case 7:
          local_374 = 0xffffe58b;
          break;
        case 8:
          local_374 = 0xfffeea18;
          break;
        case 9:
          local_374 = 0xffffe588;
        }
      }
      else {
        local_374 = 0xffffe5b1;
        if (bVar17 != 10) {
          local_374 = 0xffffe5d4;
        }
      }
      piVar25 = *(int **)(param_1 + 0x10);
      if (0x32 < *piVar25) goto LAB_18bf2668c;
      if (*piVar25 == -1) {
        iVar9 = __LogCategory_Initialize(piVar25,0x32);
        if (iVar9 == 0) goto LAB_18bf25738;
        piVar25 = *(int **)(param_1 + 0x10);
      }
      pcVar15 = "### PairSetup client M4 bad status: 0x%X, %#m\n";
      goto LAB_18bf25730;
    }
    if (bVar17 != 6) goto LAB_18bf250e4;
    if ((*(long *)(param_1 + 0x300) == 0) || (*(long *)(param_1 + 0x308) == 0)) {
LAB_18bf268b4:
      lVar23 = 0;
      local_374 = 0xffffe5d1;
      goto LAB_18bf251a8;
    }
    piVar25 = *(int **)(param_1 + 0x10);
    iVar9 = *piVar25;
    pbVar20 = param_2;
    if (iVar9 < 0x1f) {
      if (iVar9 == -1) {
        iVar9 = __LogCategory_Initialize(piVar25,0x1e);
        if (iVar9 == 0) goto LAB_18bf2568c;
        piVar25 = *(int **)(param_1 + 0x10);
        iVar9 = *piVar25;
      }
      if ((iVar9 < 0xb) && (iVar9 == -1)) {
        __LogCategory_Initialize(piVar25,10);
      }
      _LogPrintF(piVar25,
                 "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                 ,0x1e,"PairSetup client M6 -- exchange response\n%?{end}%1{tlv8}\n");
    }
LAB_18bf2568c:
    while (pbVar20 != pbVar4) {
      if (pbVar4 <= pbVar20) {
        local_374 = 0xffffe5cf;
        goto LAB_18bf25bf8;
      }
      if ((ulong)((long)pbVar4 - (long)pbVar20) < 2) break;
      pbVar1 = pbVar20 + 2;
      pbVar18 = pbVar20 + 1;
      uVar19 = (ulong)*pbVar18;
      if (pbVar4 < pbVar1 + uVar19) {
        local_374 = 0xffffe5a2;
        goto LAB_18bf25bf8;
      }
      bVar17 = *pbVar20;
      pbVar20 = pbVar1 + uVar19;
      if (bVar17 == 7) goto code_r0x00018bf256c8;
    }
    local_374 = 0xffffe5b9;
LAB_18bf25bf8:
    lVar23 = _TLV8CopyCoalesced(param_2,pbVar4,5,&local_398,&local_374);
    if (local_374 != 0) {
LAB_18bf264b8:
      uVar21 = 0;
      goto LAB_18bf26694;
    }
    if (local_398 < 0x10) goto LAB_18bf263e8;
    local_398 = local_398 - 0x10;
    lVar14 = lVar23 + local_398;
    local_374 = __chacha20_poly1305_decrypt_all
                          (param_1 + 0x1ae,"PS-Msg06",8,0,0,lVar23,local_398,lVar23,lVar14,0x10);
    if (local_374 != 0) goto LAB_18bf264b8;
    if (*(long *)(param_1 + 0xf0) != 0) {
      func_0x0001900cc3a0();
    }
    *(undefined8 *)(param_1 + 0xf8) = 0;
    uVar11 = _TLV8CopyCoalesced(lVar23,lVar14,0x10,(undefined8 *)(param_1 + 0xf8),0);
    *(undefined8 *)(param_1 + 0xf0) = uVar11;
    if (*(long *)(param_1 + 0x148) != 0) {
      func_0x0001900caac0();
      *(undefined8 *)(param_1 + 0x148) = 0;
    }
    lVar12 = _TLV8CopyCoalesced(lVar23,lVar14,0x11,&local_388,0);
    if (lVar12 == 0) {
      uVar11 = 0;
    }
    else {
      uVar11 = __OPACKDecodeBytes(0,lVar12,local_388,0,0,&local_374);
      *(undefined8 *)(param_1 + 0x148) = uVar11;
      func_0x0001900cc3a0(lVar12);
      if (*(long *)(param_1 + 0x148) == 0) goto LAB_18bf25740;
      lVar12 = func_0x0001900caaa0();
      lVar13 = func_0x0001900cdf30();
      if (lVar12 != lVar13) {
        local_374 = 0xffffe59c;
        if (*(long *)(param_1 + 0x148) == 0) goto LAB_18bf264b8;
        func_0x0001900caac0();
        *(undefined8 *)(param_1 + 0x148) = 0;
        goto LAB_18bf25740;
      }
      uVar22 = *(undefined8 *)(param_1 + 0x148);
      uVar11 = func_0x0001900cdf30();
      uVar11 = _CFDictionaryGetTypedValue(uVar22,&cfstringStruct_1e9b94160,uVar11,0);
    }
    _PairingSessionSetProperty(param_1,&cfstringStruct_1e9b94240,uVar11);
    local_374 = __ExtractAppInfoTLV(param_1,lVar23,lVar14);
    if (local_374 != 0) goto LAB_18bf264b8;
    if (*(long *)(param_1 + 0x138) != 0) {
      func_0x0001900cc3a0();
      *(undefined8 *)(param_1 + 0x138) = 0;
    }
    *(undefined8 *)(param_1 + 0x140) = 0;
    uVar11 = _TLV8CopyCoalesced(lVar23,lVar14,1,param_1 + 0x140,&local_374);
    *(undefined8 *)(param_1 + 0x138) = uVar11;
    if (local_374 != 0) goto LAB_18bf264b8;
    if (*(long *)(param_1 + 0x140) == 0) goto LAB_18bf263e8;
    puVar3 = (undefined8 *)(param_1 + 0x26e);
    local_374 = _TLV8GetBytes(lVar23,lVar14,3,0x20,0x20,puVar3,0,0);
    if ((local_374 != 0) ||
       (local_374 = _TLV8GetBytes(lVar23,lVar14,10,0x40,0x40,local_350,0,0), local_374 != 0))
    goto LAB_18bf264b8;
    if (0xffffffffffffffbf < *(ulong *)(param_1 + 0x140)) goto LAB_18bf263e8;
    uVar19 = *(ulong *)(param_1 + 0x140) + 0x40;
    local_388 = uVar19;
    lVar14 = func_0x0001900cfd70(uVar19,0x100004077774924);
    local_390 = lVar14;
    if (lVar14 == 0) goto LAB_18bf26d8c;
    _CryptoHKDF(&__kCryptoHashDescriptor_SHA512,*(undefined8 *)(param_1 + 0x300),
                *(undefined8 *)(param_1 + 0x308),"Pair-Setup-Accessory-Sign-Salt",0x1e,
                "Pair-Setup-Accessory-Sign-Info",0x1e,0x20,lVar14);
    func_0x0001900cc480(lVar14 + 0x20,*(undefined8 *)(param_1 + 0x138),
                        *(undefined8 *)(param_1 + 0x140));
    puVar5 = (undefined8 *)(lVar14 + *(long *)(param_1 + 0x140) + 0x20);
    uVar10 = *puVar3;
    uVar22 = *(undefined8 *)(param_1 + 0x286);
    uVar11 = *(undefined8 *)(param_1 + 0x27e);
    puVar5[1] = *(undefined8 *)(param_1 + 0x276);
    *puVar5 = uVar10;
    puVar5[3] = uVar22;
    puVar5[2] = uVar11;
    uVar11 = func_0x0001900cf870();
    local_374 = func_0x0001900cf130(uVar11,uVar19,lVar14,local_350,puVar3);
    if (local_374 != 0) goto LAB_18bf26d9c;
    func_0x0001900cc3a0(lVar14);
    local_390 = 0;
    if (lVar23 != 0) {
      func_0x0001900cc3a0(lVar23);
    }
    local_374 = __PairingSessionVerifyAllowed(param_1);
    if (local_374 == 0) {
      local_374 = _PairingSessionSavePeer
                            (param_1,*(undefined8 *)(param_1 + 0x138),
                             *(undefined8 *)(param_1 + 0x140),puVar3);
      if (local_374 != 0) goto LAB_18bf2668c;
      if (*(long *)(param_1 + 400) != 0) {
        func_0x0001900cc3a0();
        *(undefined8 *)(param_1 + 400) = 0;
      }
      *(undefined8 *)(param_1 + 0x198) = 0;
      *(undefined1 *)(param_1 + 0x1a0) = 0;
      *(undefined1 *)(param_1 + 0x80) = 7;
      *param_4 = 0;
      *param_5 = 0;
      piVar25 = *(int **)(param_1 + 0x10);
      if (*piVar25 < 0x1f) {
        if (*piVar25 == -1) {
          iVar9 = __LogCategory_Initialize(piVar25,0x1e);
          if (iVar9 == 0) goto LAB_18bf26d24;
          piVar25 = *(int **)(param_1 + 0x10);
        }
        _LogPrintF(piVar25,
                   "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                   ,0x1e,"PairSetup client done -- server authenticated\n");
      }
LAB_18bf26d24:
      uVar21 = 1;
      goto LAB_18bf26594;
    }
    piVar25 = *(int **)(param_1 + 0x10);
    if (0x32 < *piVar25) goto LAB_18bf26ed4;
    if (*piVar25 == -1) {
      iVar9 = __LogCategory_Initialize(piVar25,0x32);
      if (iVar9 == 0) goto LAB_18bf26ed4;
      piVar25 = *(int **)(param_1 + 0x10);
    }
    _LogPrintF(piVar25,
               "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
               ,0x32,"### PairSetup client: server not allowed: %#m\n");
LAB_18bf26ed4:
    lVar23 = 0;
    goto LAB_18bf25740;
  }
  if ((*(long *)(param_1 + 400) == 0) || (lVar23 = param_3, *(long *)(param_1 + 0x198) == 0)) {
LAB_18bf26600:
    lVar23 = 0;
    local_374 = 0xffffe5a7;
    goto LAB_18bf251a8;
  }
LAB_18bf24fac:
  local_374 = _TLV8BufferAppend(&local_1c0,6,pbVar20,1);
  if (local_374 != 0) goto LAB_18bf24fc8;
  if (*(char *)(param_1 + 0x2c1) == '\0') {
    if (lVar23 == 0) {
      lVar23 = *(long *)(param_1 + 0x2d8);
      if ((((lVar23 == 0) || (lVar14 = *(long *)(param_1 + 0x2e0), lVar14 == 0)) ||
          (lVar12 = *(long *)(param_1 + 0x2e8), lVar12 == 0)) ||
         ((lVar13 = *(long *)(param_1 + 0x2f0), lVar13 == 0 ||
          (lVar16 = *(long *)(param_1 + 0x2f8), lVar16 == 0)))) goto LAB_18bf268b4;
      if (*(long *)(param_1 + 0x300) != 0) {
        func_0x0001900cc3a0(*(long *)(param_1 + 0x300));
        *(undefined8 *)(param_1 + 0x300) = 0;
        lVar23 = *(long *)(param_1 + 0x2d8);
        lVar13 = *(long *)(param_1 + 0x2f0);
        lVar16 = *(long *)(param_1 + 0x2f8);
        lVar14 = *(long *)(param_1 + 0x2e0);
        lVar12 = *(long *)(param_1 + 0x2e8);
      }
      *(undefined8 *)(param_1 + 0x308) = 0;
      local_374 = _SRPClientStart_libsrp
                            (lVar23,&__kSRPParameters_3072_SHA512,"Pair-Setup",10,
                             *(undefined8 *)(param_1 + 400),*(undefined8 *)(param_1 + 0x198),lVar13,
                             lVar16,lVar14,lVar12,&local_3a0,&local_3a8,param_1 + 0x300,
                             param_1 + 0x308,&local_3b0,&local_3b8);
      if (local_374 == 0) {
        if (*(long *)(param_1 + 0x2e0) != 0) {
          func_0x0001900cc3a0();
          *(undefined8 *)(param_1 + 0x2e0) = 0;
        }
        *(undefined8 *)(param_1 + 0x2e8) = 0;
        if (*(long *)(param_1 + 0x2f0) != 0) {
          func_0x0001900cc3a0();
          *(undefined8 *)(param_1 + 0x2f0) = 0;
        }
        *(undefined8 *)(param_1 + 0x2f8) = 0;
        local_374 = _TLV8BufferAppend(&local_1c0,3,local_3a0,local_3a8);
        if ((local_374 == 0) &&
           (local_374 = _TLV8BufferAppend(&local_1c0,4,local_3b0,local_3b8), local_374 == 0))
        goto LAB_18bf25f10;
      }
      goto LAB_18bf2668c;
    }
    local_374 = 0xffffe5cf;
LAB_18bf25950:
    lVar23 = 0;
    uVar21 = 0;
  }
  else {
    piVar25 = *(int **)(param_1 + 0x10);
    if (*piVar25 < 0x1f) {
      if (*piVar25 == -1) {
        iVar9 = __LogCategory_Initialize(piVar25,0x1e);
        if (iVar9 == 0) goto LAB_18bf25794;
        piVar25 = *(int **)(param_1 + 0x10);
      }
      _LogPrintF_safe(piVar25,"OSStatus _SetupClientSPAKE2Start(PairingSessionRef, TLV8Buffer *)",
                      0x1e,"PairSetup client SPAKE2 start");
    }
LAB_18bf25794:
    if (*(long *)(param_1 + 0x198) == 0) {
      piVar25 = *(int **)(param_1 + 0x10);
      if (*piVar25 < 0x5b) {
        if (*piVar25 == -1) {
          iVar9 = __LogCategory_Initialize(piVar25,0x5a);
          if (iVar9 == 0) goto LAB_18bf25944;
          piVar25 = *(int **)(param_1 + 0x10);
        }
        _LogPrintF_safe(piVar25,"OSStatus _SetupClientSPAKE2Start(PairingSessionRef, TLV8Buffer *)",
                        0x5a,"### PairSetup client SPAKE2 start failed: no password");
      }
LAB_18bf25944:
      local_374 = 0xffffe5a7;
      goto LAB_18bf25950;
    }
    auVar26 = func_0x0001900cc520(DAT_1e0928778);
    func_0x000190037e60(auVar26._0_8_,auVar26._8_8_,*(undefined8 *)(param_1 + 400),
                        *(undefined8 *)(param_1 + 0x198));
    if (*(long *)(param_1 + 0x2c8) != 0) {
      func_0x0001900caac0();
    }
    auVar26 = func_0x0001900cc860();
    *(long *)(param_1 + 0x2c8) = auVar26._0_8_;
    local_350[0] = 0;
    func_0x000190037ac0(auVar26._0_8_,auVar26._8_8_,local_350);
    lVar23 = func_0x0001900cc570();
    uVar11 = func_0x0001900cc8c0(local_350[0]);
    if (lVar23 == 0) {
      piVar25 = *(int **)(param_1 + 0x10);
      if (*piVar25 < 0x5b) {
        if (*piVar25 == -1) {
          iVar9 = __LogCategory_Initialize(piVar25,0x5a);
          if (iVar9 == 0) goto LAB_18bf25ef4;
          piVar25 = *(int **)(param_1 + 0x10);
        }
        _NSPrintF("%{error}");
        uVar22 = func_0x0001900cc570();
        _LogPrintF_safe(piVar25,"OSStatus _SetupClientSPAKE2Start(PairingSessionRef, TLV8Buffer *)",
                        0x5a,"### PairSetup client SPAKE2 generate M1 failed: %@");
        func_0x0001900cc720(uVar22);
      }
LAB_18bf25ef4:
      uVar7 = 0xffffe5d4;
    }
    else {
      func_0x000190039570(lVar23);
      func_0x0001900cc570();
      func_0x0001900cc750();
      uVar22 = func_0x0001900018a0();
      func_0x000190039570(lVar23);
      func_0x0001900cc570();
      uVar10 = func_0x0001900026d0();
      uVar7 = _TLV8BufferAppend(&local_1c0,0x22,uVar22,uVar10);
      func_0x0001900cc6d0();
      func_0x0001900cc6c0();
      if (uVar7 != 0) {
        piVar25 = *(int **)(param_1 + 0x10);
        if (*piVar25 < 0x5b) {
          if (*piVar25 == -1) {
            iVar9 = __LogCategory_Initialize(piVar25,0x5a);
            if (iVar9 == 0) goto LAB_18bf25ef8;
            piVar25 = *(int **)(param_1 + 0x10);
          }
          _LogPrintF_safe(piVar25,
                          "OSStatus _SetupClientSPAKE2Start(PairingSessionRef, TLV8Buffer *)",0x5a,
                          "### PairSetup client SPAKE2 add M1 SharePData TLV failed: %d");
        }
      }
    }
LAB_18bf25ef8:
    func_0x0001900cc6f0();
    func_0x0001900cc720(uVar11);
    func_0x0001900cc6e0();
    local_374 = uVar7;
    if (uVar7 == 0) {
LAB_18bf25f10:
      local_374 = _TLV8BufferDetach(&local_1c0,param_4,param_5);
      if (local_374 == 0) {
        *(undefined1 *)(param_1 + 0x80) = 4;
        piVar25 = *(int **)(param_1 + 0x10);
        iVar9 = *piVar25;
        if (iVar9 < 0x1f) {
          if (iVar9 == -1) {
            iVar9 = __LogCategory_Initialize(piVar25,0x1e);
            if (iVar9 == 0) goto LAB_18bf263d8;
            piVar25 = *(int **)(param_1 + 0x10);
            iVar9 = *piVar25;
          }
          if ((iVar9 < 0xb) && (iVar9 == -1)) {
            __LogCategory_Initialize(piVar25,10);
          }
          _LogPrintF(piVar25,
                     "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                     ,0x1e,"PairSetup  client M3 -- verify request\n%?{end}%1{tlv8}\n");
        }
LAB_18bf263d8:
        uVar21 = 0;
        goto LAB_18bf26594;
      }
    }
LAB_18bf24fc8:
    uVar21 = 0;
    lVar23 = 0;
  }
  goto LAB_18bf26694;
code_r0x00018bf256c8:
  local_388 = uVar19;
  pbStack_380 = pbVar1;
  if (*pbVar18 != 1) {
LAB_18bf263e0:
    lVar23 = 0;
LAB_18bf263e8:
    local_374 = 0xffffe5a9;
    goto LAB_18bf251a8;
  }
  bVar17 = *pbVar1;
  if (bVar17 < 10) {
    local_374 = *(uint *)(&DAT_18bf7326c + (ulong)bVar17 * 4);
  }
  else {
    local_374 = 0xffffe5b1;
    if (bVar17 != 10) {
      local_374 = 0xffffe5d4;
    }
  }
  piVar25 = *(int **)(param_1 + 0x10);
  if (0x32 < *piVar25) goto LAB_18bf2668c;
  if (*piVar25 == -1) {
    iVar9 = __LogCategory_Initialize(piVar25,0x32);
    if (iVar9 != 0) {
      piVar25 = *(int **)(param_1 + 0x10);
      goto LAB_18bf2571c;
    }
  }
  else {
LAB_18bf2571c:
    pcVar15 = "### PairSetup client M6 bad status: 0x%X, %#m\n";
LAB_18bf25730:
    _LogPrintF(piVar25,
               "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
               ,0x32,pcVar15);
  }
LAB_18bf25738:
  lVar23 = 0;
LAB_18bf25740:
  uVar21 = 0;
  if (local_374 == 0) {
LAB_18bf2574c:
    __PairingSessionUpdateTranscript(param_1,param_2,param_3,*param_4,*param_5);
  }
  goto LAB_18bf26694;
LAB_18bf26d9c:
  local_374 = 0xffffe59e;
  goto LAB_18bf251a8;
LAB_18bf26d54:
  lVar23 = 0;
LAB_18bf26d8c:
  local_374 = 0xffffe5b8;
LAB_18bf251a8:
  uVar21 = 0;
LAB_18bf26694:
  *param_6 = uVar21;
  if (local_1a8 != 0) {
    func_0x0001900cc3a0();
    local_1a8 = 0;
  }
  if (local_2f8 != 0) {
    func_0x0001900cc3a0();
    local_2f8 = 0;
  }
  if (local_390 != 0) {
    func_0x0001900cc3a0();
    local_390 = 0;
  }
  if (lVar23 != 0) {
    func_0x0001900cc3a0(lVar23);
  }
  if (local_3a0 != 0) {
    func_0x0001900cc3a0();
  }
  if (local_3b0 != 0) {
    func_0x0001900cc3a0();
  }
  uVar19 = (ulong)local_374;
  if ((local_374 != 0xffffe58d) && (local_374 != 0)) {
    piVar25 = *(int **)(param_1 + 0x10);
    iVar9 = *piVar25;
    if (iVar9 < 0x33) {
      if (iVar9 == -1) {
        iVar9 = __LogCategory_Initialize(piVar25,0x32);
        uVar19 = (ulong)local_374;
        if (iVar9 == 0) goto LAB_18bf267a0;
        piVar25 = *(int **)(param_1 + 0x10);
        iVar9 = *piVar25;
      }
      if ((iVar9 < 0x29) && (iVar9 == -1)) {
        __LogCategory_Initialize(piVar25,0x28);
      }
      _LogPrintF(piVar25,
                 "OSStatus _SetupClientExchange(PairingSessionRef, const void *, size_t, uint8_t **, size_t *, Boolean *)"
                 ,0x32,"### PairSetup client state %d failed: %#m\n%?{end}%1{tlv8}\n");
      uVar19 = (ulong)local_374;
    }
  }
LAB_18bf267a0:
  if (*_DAT_1e016af28 == local_70) {
    return uVar19;
  }
  uVar19 = func_0x0001900cc180();
  return uVar19;
}


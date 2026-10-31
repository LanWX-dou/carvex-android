/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10014778c
 * original code SHA256: a84c7b99af764f6b09cfecf688c9c4ef88e33012686f3c4777b1f156fe4963cc
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_nowPlaying_playbackQueueListInfoResponseHandler(long *param_1,long param_2)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  char in_NG;
  undefined1 in_ZR;
  bool bVar16;
  char in_OV;
  char cVar17;
  char cVar18;
  undefined1 uVar19;
  bool bVar20;
  int iVar21;
  int iVar22;
  cfstringStruct *pcVar23;
  byte *pbVar24;
  long lVar25;
  long lVar26;
  long lVar27;
  undefined8 uVar28;
  undefined1 *puVar29;
  undefined8 uVar30;
  undefined *puVar31;
  ulong uVar32;
  undefined4 extraout_w1;
  byte bVar33;
  undefined2 extraout_w8;
  undefined2 extraout_w8_00;
  undefined2 extraout_w8_01;
  undefined2 extraout_w8_02;
  uint uVar34;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  ulong extraout_x8_03;
  ulong extraout_x8_04;
  long extraout_x8_05;
  long extraout_x8_06;
  undefined4 extraout_w9;
  undefined4 extraout_w11;
  undefined4 extraout_w11_00;
  undefined4 extraout_w11_01;
  undefined4 extraout_w12;
  long lVar35;
  undefined *puVar36;
  ushort uVar37;
  undefined8 *puVar38;
  undefined8 *puVar39;
  byte bVar40;
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  uint local_11c;
  undefined8 *local_100;
  undefined4 local_d0;
  uint uStack_cc;
  undefined2 uStack_c8;
  ushort uStack_c6;
  undefined2 uStack_c4;
  undefined2 uStack_c2;
  ushort uStack_c0;
  undefined2 uStack_be;
  undefined2 uStack_bc;
  undefined2 local_ba;
  undefined2 uStack_b8;
  undefined2 local_b6;
  undefined2 uStack_b4;
  undefined2 uStack_b2;
  undefined1 *local_b0;
  undefined1 *puStack_a8;
  undefined1 *puStack_a0;
  undefined1 *puStack_98;
  undefined1 *local_90;
  undefined2 local_7a;
  undefined8 local_78;
  undefined8 local_70;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if (*param_1 == 0) {
    return 0;
  }
  _OUTLINED_FUNCTION_18();
  if ((extraout_x8 == 0) || (_OUTLINED_FUNCTION_27(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_22();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_18();
  }
  iVar21 = _OUTLINED_FUNCTION_90();
  if (iVar21 != 0) {
    lVar35 = param_1[1];
    if (param_2 == 0) {
      pcVar23 = &cf__nil_;
    }
    else {
      pcVar23 = (cfstringStruct *)
                _CFDictionaryGetValue(param_2,_kCFACCNowPlaying_PlaybackQueueContentInfo_RequestID);
    }
    local_d0 = (undefined4)DAT_1001b30f0;
    uStack_cc = (uint)lVar35;
    uStack_c8 = (undefined2)((ulong)lVar35 >> 0x20);
    uStack_c6 = (ushort)((ulong)lVar35 >> 0x30);
    uStack_c4 = 0x840;
    uStack_c2 = SUB82(pcVar23,0);
    uStack_c0 = (ushort)((ulong)pcVar23 >> 0x10);
    uStack_be = (undefined2)((ulong)pcVar23 >> 0x20);
    uStack_bc = (undefined2)((ulong)pcVar23 >> 0x30);
    _OUTLINED_FUNCTION_6();
    auVar41 = _OUTLINED_FUNCTION_26();
    __os_log_impl(auVar41._0_8_,auVar41._8_8_,0);
  }
  pbVar24 = (byte *)_iap2_feature_getFeature(param_1,0xe);
  if (pbVar24 == (byte *)0x0) {
    return 0;
  }
  uVar34 = (uint)*pbVar24;
  cVar17 = SBORROW4(uVar34,1);
  cVar18 = (int)(uVar34 - 1) < 0;
  uVar19 = uVar34 == 1;
  if (!(bool)uVar19) {
    return 0;
  }
  if (param_1[5] == 0) {
    return 0;
  }
  if (*(long *)(param_1[5] + 0x18) == 0) {
    return 0;
  }
  lVar35 = _OUTLINED_FUNCTION_74(&_kCFACCNowPlaying_PlaybackQueueContentInfo_StartIndex);
  lVar25 = _OUTLINED_FUNCTION_74(&_kCFACCNowPlaying_PlaybackQueueContentInfo_Count);
  lVar26 = _OUTLINED_FUNCTION_74(&_kCFACCNowPlaying_PlaybackQueueContentInfo_NonLibrary);
  lVar27 = _OUTLINED_FUNCTION_74(&_kCFACCNowPlaying_PlaybackQueueContentInfo_Available);
  local_78 = 0;
  local_7a = 0;
  if (lVar27 == 0) {
    _logObjectForModule();
    iVar21 = _OUTLINED_FUNCTION_7();
    if (iVar21 == 0) {
      return 0;
    }
    _OUTLINED_FUNCTION_7();
  }
  else {
    if (param_2 == 0) {
      _OUTLINED_FUNCTION_18();
      if ((extraout_x8_01 == 0) || (_OUTLINED_FUNCTION_27(), cVar18 != cVar17)) {
        _OUTLINED_FUNCTION_22();
        if (!(bool)uVar19) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_18();
      }
      iVar21 = _OUTLINED_FUNCTION_75();
      if (iVar21 != 0) {
        _OUTLINED_FUNCTION_8(local_78._4_4_,0x400040004000400);
        local_ba = (undefined2)extraout_w11_00;
        uStack_b8 = (undefined2)((uint)extraout_w11_00 >> 0x10);
        uStack_bc = extraout_w8_00;
        _OUTLINED_FUNCTION_6();
        goto LAB_1001479e0;
      }
    }
    else {
      if (lVar35 != 0) {
        _CFNumberGetValue(lVar35,9,(long)&local_78 + 4);
      }
      if (lVar25 != 0) {
        _CFNumberGetValue(lVar25,9,&local_78);
      }
      if (lVar26 != 0) {
        _CFNumberGetValue(lVar26,1,(long)&local_7a + 1);
      }
      _CFNumberGetValue(lVar27,1,&local_7a);
      _OUTLINED_FUNCTION_18();
      if ((extraout_x8_00 == 0) || (_OUTLINED_FUNCTION_27(), cVar18 != cVar17)) {
        _OUTLINED_FUNCTION_22();
        if (!(bool)uVar19) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_18();
      }
      iVar21 = _OUTLINED_FUNCTION_75();
      if (iVar21 != 0) {
        _OUTLINED_FUNCTION_8(local_78._4_4_,0x400040004000400);
        local_ba = (undefined2)extraout_w11;
        uStack_b8 = (undefined2)((uint)extraout_w11 >> 0x10);
        uStack_bc = extraout_w8;
        _OUTLINED_FUNCTION_6();
LAB_1001479e0:
        _OUTLINED_FUNCTION_17();
        __os_log_impl();
      }
    }
    lVar35 = _CFDictionaryGetValue(param_2,_kCFACCNowPlaying_PlaybackQueueContentInfo_RequestID);
    if (lVar35 == 0) {
      _logObjectForModule();
      iVar21 = _OUTLINED_FUNCTION_7();
      if (iVar21 == 0) {
        return 0;
      }
      _OUTLINED_FUNCTION_7();
    }
    else if (*(long *)(pbVar24 + 0x60) == 0) {
      _logObjectForModule(0,lVar35);
      iVar21 = _OUTLINED_FUNCTION_7();
      if (iVar21 == 0) {
        return 0;
      }
      _OUTLINED_FUNCTION_7();
    }
    else {
      iVar21 = _CFEqual();
      if (iVar21 == 0) {
        _logObjectForModule();
        iVar21 = _OUTLINED_FUNCTION_7();
        if (iVar21 == 0) {
          return 0;
        }
        _OUTLINED_FUNCTION_7();
      }
      else if (((pbVar24[0x50] & 1) == 0) && ((pbVar24[0x51] & 1) == 0)) {
        _logObjectForModule();
        iVar21 = _OUTLINED_FUNCTION_7();
        if (iVar21 == 0) {
          return 0;
        }
        _OUTLINED_FUNCTION_7();
      }
      else {
        uVar28 = _OUTLINED_FUNCTION_83();
        uVar28 = _iAP2LinkGetSessionForService(uVar28,1);
        _OUTLINED_FUNCTION_83(uVar28,uVar28);
        lVar35 = _iAP2LinkGetSessionInfo();
        if (lVar35 != 0) {
          bVar2 = *(byte *)(lVar35 + 2);
          bVar3 = pbVar24[0x50];
          puVar36 = (undefined *)(ulong)bVar3;
          if (bVar2 < 2) {
            bVar4 = pbVar24[0x52];
            lVar35 = _OUTLINED_FUNCTION_74(&_kCFACCNowPlaying_PlaybackQueueContentInfo_List);
            bVar33 = 0;
            uVar37 = 0;
          }
          else {
            bVar40 = pbVar24[0x51];
            uVar37 = (ushort)bVar40;
            bVar4 = pbVar24[0x52];
            lVar35 = _OUTLINED_FUNCTION_74(&_kCFACCNowPlaying_PlaybackQueueContentInfo_List);
            bVar33 = 6;
            if (bVar40 == 0) {
              bVar33 = 0;
            }
          }
          bVar40 = 3;
          if (bVar3 == 0) {
            bVar40 = bVar33;
          }
          lVar26 = (long)(int)(uint)local_78;
          lVar25 = 0;
          if (lVar35 != 0) {
            lVar25 = _CFArrayGetCount();
          }
          cVar17 = SBORROW8(lVar25,lVar26);
          cVar18 = lVar25 - lVar26 < 0;
          uVar19 = lVar25 == lVar26;
          if (!(bool)uVar19) {
            _logObjectForModule();
            iVar21 = _OUTLINED_FUNCTION_7();
            if (iVar21 == 0) {
              return 0;
            }
            uVar34 = (uint)local_78;
            if (lVar35 == 0) {
              uVar28 = 0;
            }
            else {
              uVar28 = _CFArrayGetCount(lVar35);
            }
            local_d0 = (undefined4)DAT_1001b3108;
            uStack_cc = uVar34;
            uStack_c8 = 0x800;
            uStack_c6 = (ushort)uVar28;
            uStack_c4 = (undefined2)((ulong)uVar28 >> 0x10);
            uStack_c2 = (undefined2)((ulong)uVar28 >> 0x20);
            uStack_c0 = (ushort)((ulong)uVar28 >> 0x30);
            _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_16();
            goto LAB_100148404;
          }
          _OUTLINED_FUNCTION_18();
          if ((extraout_x8_02 == 0) || (_OUTLINED_FUNCTION_27(), cVar18 != cVar17)) {
            _OUTLINED_FUNCTION_22();
            if (!(bool)uVar19) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_18();
          }
          iVar21 = _OUTLINED_FUNCTION_75();
          if (iVar21 != 0) {
            local_d0 = 0x4000400;
            uStack_cc = (uint)local_7a._1_1_;
            _OUTLINED_FUNCTION_35();
            uStack_c6 = (ushort)bVar3;
            uStack_c4 = 0;
            uStack_be = 0;
            local_ba = (undefined2)extraout_w9;
            uStack_b8 = (undefined2)((uint)extraout_w9 >> 0x10);
            uStack_c2 = extraout_w8_01;
            uStack_c0 = uVar37;
            uStack_bc = extraout_w8_01;
            _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_17();
            __os_log_impl();
          }
          puVar14 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_Composer;
          puVar13 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_Genre;
          puVar12 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_AlbumArtist;
          puVar11 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_AlbumTitle;
          puVar10 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_Title;
          puVar9 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_PersistentID;
          uVar34 = (uint)(local_7a._1_1_ == '\0' & bVar3);
          cVar17 = SBORROW4(uVar34,1);
          cVar18 = (int)(uVar34 - 1) < 0;
          uVar19 = uVar34 == 1;
          if ((bool)uVar19) {
            puVar36 = (undefined *)(ulong)((uint)local_78 << 3);
            bVar40 = 3;
            uVar19 = true;
            cVar18 = false;
            cVar17 = false;
LAB_100147d24:
            _OUTLINED_FUNCTION_91();
            if ((extraout_x8_03 & 1) != 0) {
LAB_1001483c8:
              __sendPBQTransferTypeAndAvailability(param_1,bVar40,1 < bVar2,1,0);
              return 1;
            }
            if ((int)puVar36 != 0) goto LAB_100147d38;
LAB_100148204:
            bVar3 = 0;
            local_11c = 0;
            local_100 = (undefined8 *)0x0;
          }
          else {
            if (uVar37 == 0) {
              if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_27(), cVar18 != cVar17)) {
                _OUTLINED_FUNCTION_22();
                if (!(bool)uVar19) {
                  _OUTLINED_FUNCTION_0();
                  _dispatch_once();
                }
                _OUTLINED_FUNCTION_18();
              }
              iVar21 = _OUTLINED_FUNCTION_75();
              if (iVar21 != 0) {
                _OUTLINED_FUNCTION_7();
                _OUTLINED_FUNCTION_17();
                __os_log_impl();
              }
              local_7a = local_7a & 0xff00;
              if ((bVar4 & 1) != 0) goto LAB_1001483c8;
              goto LAB_100148204;
            }
            cVar18 = SBORROW4((uint)local_78,1);
            cVar17 = (int)((uint)local_78 + -1) < 0;
            uVar19 = (uint)local_78 == 1;
            if (0 < (int)(uint)local_78) {
              lVar25 = 0;
              puVar36 = (undefined *)0x16;
              do {
                lVar26 = _CFArrayGetValueAtIndex(lVar35,lVar25);
                auVar8._8_8_ = puVar10;
                auVar8._0_8_ = lVar26;
                auVar7._8_8_ = puVar11;
                auVar7._0_8_ = lVar26;
                auVar6._8_8_ = puVar12;
                auVar6._0_8_ = lVar26;
                auVar5._8_8_ = puVar13;
                auVar5._0_8_ = lVar26;
                auVar41._8_8_ = puVar14;
                auVar41._0_8_ = lVar26;
                if ((lVar26 == 0) || (*pbVar24 != 1)) {
                  iVar21 = 0;
                }
                else {
                  uVar32 = 0;
                  uVar1 = *(uint *)(pbVar24 + 0x5c);
                  iVar21 = 4;
                  do {
                    if ((uVar1 >> (uVar32 & 0x3f) & 1) != 0) {
                      iVar22 = (int)uVar32;
                      if (iVar22 - 0xcU < 7) {
                        switch(iVar22) {
                        default:
                          auVar42 = _OUTLINED_FUNCTION_40();
                          break;
                        case 0xd:
                        case 0xf:
                        case 0x11:
                          goto switchD_100147c40_caseD_d;
                        case 0xe:
                          auVar42 = auVar6;
                          break;
                        case 0x10:
                          auVar42 = auVar5;
                          break;
                        case 0x12:
                          auVar42 = auVar41;
                        }
LAB_100147cb4:
                        _CFDictionaryGetValue(auVar42._0_8_,auVar42._8_8_);
                        iVar22 = __calculateStrParamSize();
                        iVar21 = iVar22 + iVar21;
                      }
                      else {
                        auVar42 = auVar7;
                        if ((iVar22 == 6) || (auVar42 = auVar8, iVar22 == 1)) goto LAB_100147cb4;
                        if (iVar22 == 0) {
                          lVar27 = _CFDictionaryGetValue(lVar26,puVar9);
                          if (lVar27 != 0) {
                            iVar21 = iVar21 + 0xc;
                          }
                        }
                      }
                    }
switchD_100147c40_caseD_d:
                    uVar32 = uVar32 + 1;
                  } while (uVar32 != 0x13);
                }
                puVar36 = (undefined *)(ulong)(uint)(iVar21 + (int)puVar36);
                lVar25 = lVar25 + 1;
                lVar26 = (long)(int)(uint)local_78;
                cVar18 = SBORROW8(lVar25,lVar26);
                cVar17 = lVar25 - lVar26 < 0;
                uVar19 = lVar25 == lVar26;
              } while (lVar25 < lVar26);
              bVar40 = 6;
              goto LAB_100147d24;
            }
            _OUTLINED_FUNCTION_91();
            bVar40 = 6;
            if ((extraout_x8_04 & 1) != 0) goto LAB_1001483c8;
            puVar36 = (undefined *)0x16;
LAB_100147d38:
            local_100 = (undefined8 *)_malloc_type_malloc(puVar36,0x5af76c7f);
            if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_27(), cVar17 != cVar18)) {
              _OUTLINED_FUNCTION_22();
              if (!(bool)uVar19) {
                _OUTLINED_FUNCTION_0();
                _dispatch_once();
              }
              _OUTLINED_FUNCTION_18();
            }
            iVar21 = _OUTLINED_FUNCTION_75();
            local_11c = (uint)puVar36;
            if (iVar21 != 0) {
              uVar28 = _obfuscatedPointer(local_100);
              local_d0 = (undefined4)DAT_1001b3108;
              uStack_c8 = 0x800;
              uStack_c6 = (ushort)uVar28;
              uStack_c4 = (undefined2)((ulong)uVar28 >> 0x10);
              uStack_c2 = (undefined2)((ulong)uVar28 >> 0x20);
              uStack_c0 = (ushort)((ulong)uVar28 >> 0x30);
              uStack_cc = local_11c;
              _OUTLINED_FUNCTION_6();
              _OUTLINED_FUNCTION_17();
              __os_log_impl();
            }
            puVar9 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_PersistentID;
            uVar28 = DAT_1001b3480;
            if (uVar34 == 0) {
              local_90 = &DAT_aaaaaaaaaaaaaaaa;
              puStack_a8 = &DAT_aaaaaaaaaaaaaaaa;
              local_b0 = &DAT_aaaaaaaaaaaaaaaa;
              puStack_98 = &DAT_aaaaaaaaaaaaaaaa;
              puStack_a0 = &DAT_aaaaaaaaaaaaaaaa;
              uStack_c8 = 0xaaaa;
              uStack_c6 = 0xaaaa;
              uStack_c4 = 0xaaaa;
              uStack_c2 = 0xaaaa;
              local_d0 = 0xaaaaaaaa;
              uStack_cc = 0xaaaaaaaa;
              uStack_b8 = 0xaaaa;
              local_b6 = 0xaaaa;
              uStack_b4 = 0xaaaa;
              uStack_b2 = 0xaaaa;
              uStack_c0 = 0xaaaa;
              uStack_be = 0xaaaa;
              uStack_bc = 0xaaaa;
              local_ba = 0xaaaa;
              _iAP2MsgInit(&local_d0,0,local_100,puVar36,0,0);
              _iAP2MsgAddU32Param(&local_d0,0,0,local_78 & 0xffffffff);
              _iAP2MsgAddU32Param(&local_d0,0,1,local_78._4_4_);
              puVar15 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_Composer;
              puVar14 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_Genre;
              puVar13 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_AlbumArtist;
              puVar12 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_Artist;
              puVar11 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_AlbumTitle;
              puVar10 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_Title;
              puVar9 = _kCFACCNowPlaying_PlaybackQueueContentItemAttributes_PersistentID;
              if (0 < (int)(uint)local_78) {
                lVar25 = 0;
                do {
                  puVar31 = (undefined *)_CFArrayGetValueAtIndex(lVar35,lVar25);
                  if (((puVar31 != (undefined *)0x0) &&
                      (uVar34 = *(uint *)(pbVar24 + 0x5c), uVar34 != 0)) && (*pbVar24 == 1)) {
                    uVar28 = _iAP2MsgAddGroupParam(&local_d0,2);
                    uVar32 = 0;
                    do {
                      if ((uVar34 >> (uVar32 & 0x3f) & 1) != 0) {
                        iVar21 = (int)uVar32;
                        if (iVar21 - 0xcU < 7) {
                          switch(iVar21) {
                          default:
                            lVar26 = _CFDictionaryGetValue(puVar31,puVar12);
                            if (lVar26 != 0) {
                              auVar41 = _OUTLINED_FUNCTION_21();
                              uVar30 = 0xc;
LAB_100148188:
                              _iAP2MsgAddCFStringParam(auVar41._0_8_,auVar41._8_8_,uVar30);
                            }
                            break;
                          case 0xd:
                          case 0xf:
                          case 0x11:
                            break;
                          case 0xe:
                            lVar26 = _CFDictionaryGetValue(puVar31,puVar13);
                            if (lVar26 != 0) {
                              auVar41 = _OUTLINED_FUNCTION_21();
                              uVar30 = 0xe;
                              goto LAB_100148188;
                            }
                            break;
                          case 0x10:
                            lVar26 = _CFDictionaryGetValue(puVar31,puVar14);
                            if (lVar26 != 0) {
                              auVar41 = _OUTLINED_FUNCTION_21();
                              uVar30 = 0x10;
                              goto LAB_100148188;
                            }
                            break;
                          case 0x12:
                            lVar26 = _CFDictionaryGetValue(puVar31,puVar15);
                            if (lVar26 != 0) {
                              auVar41 = _OUTLINED_FUNCTION_21();
                              uVar30 = 0x12;
                              goto LAB_100148188;
                            }
                          }
                        }
                        else if (iVar21 == 6) {
                          lVar26 = _CFDictionaryGetValue(puVar31,puVar11);
                          if (lVar26 != 0) {
                            auVar41 = _OUTLINED_FUNCTION_21();
                            uVar30 = 6;
                            goto LAB_100148188;
                          }
                        }
                        else if (iVar21 == 1) {
                          lVar26 = _CFDictionaryGetValue(puVar31,puVar10);
                          if (lVar26 != 0) {
                            auVar41 = _OUTLINED_FUNCTION_21();
                            uVar30 = 1;
                            goto LAB_100148188;
                          }
                        }
                        else if (iVar21 == 0) {
                          lVar26 = _CFDictionaryGetValue(puVar31,puVar9);
                          local_70 = 0;
                          if ((lVar26 != 0) &&
                             (iVar21 = _CFNumberGetValue(lVar26,4,&local_70), iVar21 != 0)) {
                            _iAP2MsgAddU64Param(&local_d0,uVar28,0,local_70);
                          }
                        }
                      }
                      uVar32 = uVar32 + 1;
                      puVar36 = puVar31;
                    } while (uVar32 != 0x13);
                  }
                  lVar25 = lVar25 + 1;
                } while (lVar25 < (int)(uint)local_78);
              }
            }
            else {
              uVar19 = (uint)local_78 == 1;
              if (0 < (int)(uint)local_78) {
                lVar25 = 0;
                _OUTLINED_FUNCTION_26();
                puVar38 = local_100;
                do {
                  puVar29 = (undefined1 *)_CFArrayGetValueAtIndex(lVar35,lVar25);
                  lVar26 = _CFDictionaryGetValue(puVar29,puVar9);
                  local_70 = 0;
                  if ((lVar26 == 0) || (iVar21 = _CFNumberGetValue(lVar26,4,&local_70), iVar21 == 0)
                     ) {
                    if ((_gLogObjects == 0) ||
                       (uVar19 = _gNumLogObjects == 0x23, _gNumLogObjects < 0x23)) {
                      _OUTLINED_FUNCTION_22();
                      puVar39 = local_100;
                      if (!(bool)uVar19) {
                        _OUTLINED_FUNCTION_0();
                        _dispatch_once();
                      }
                    }
                    else {
                      puVar39 = *(undefined8 **)(_gLogObjects + 0x110);
                    }
                    iVar21 = _os_log_type_enabled(puVar39,0x10);
                    uVar32 = local_78;
                    if (iVar21 != 0) {
                      uVar30 = _obfuscatedPointer(puVar38);
                      local_d0 = (undefined4)uVar28;
                      uStack_cc = (uint)lVar25;
                      uStack_c8 = 0x400;
                      uStack_c6 = (ushort)uVar32;
                      uStack_c4 = (undefined2)(uVar32 >> 0x10);
                      uStack_c2 = 0x800;
                      uStack_c0 = (ushort)uVar30;
                      uStack_be = (undefined2)((ulong)uVar30 >> 0x10);
                      uStack_bc = (undefined2)((ulong)uVar30 >> 0x20);
                      local_ba = (undefined2)((ulong)uVar30 >> 0x30);
                      uStack_b8 = 0x400;
                      local_b6 = (undefined2)*(undefined4 *)(pbVar24 + 0x5c);
                      uStack_b4 = (undefined2)((uint)*(undefined4 *)(pbVar24 + 0x5c) >> 0x10);
                      uStack_b2 = 0x840;
                      local_b0 = puVar29;
                      uVar30 = _OUTLINED_FUNCTION_6();
                      __os_log_error_impl(uVar30,puVar39,0x10,
                                          "#PlaybackQueueList fill in pid list, failed to retrieve pid from item: i=%d / %d, p=%p infoMask=0x%x item=%@"
                                         );
                    }
                    *puVar38 = 0;
                  }
                  else {
                    *(undefined1 *)puVar38 = local_70._7_1_;
                    *(char *)((long)puVar38 + 1) = (char)((ulong)local_70 >> 0x30);
                    *(char *)((long)puVar38 + 2) = (char)((ulong)local_70 >> 0x28);
                    *(char *)((long)puVar38 + 3) = (char)((ulong)local_70 >> 0x20);
                    *(char *)((long)puVar38 + 4) = (char)((ulong)local_70 >> 0x18);
                    *(char *)((long)puVar38 + 5) = (char)((ulong)local_70 >> 0x10);
                    *(char *)((long)puVar38 + 6) = (char)((ulong)local_70 >> 8);
                    *(char *)((long)puVar38 + 7) = (char)local_70;
                  }
                  lVar25 = lVar25 + 1;
                  puVar38 = puVar38 + 1;
                  uVar19 = lVar25 == (int)(uint)local_78;
                  puVar36 = puVar9;
                } while (lVar25 < (int)(uint)local_78);
              }
            }
            bVar3 = 1;
          }
          uVar34 = (uint)pbVar24[0x78];
          cVar17 = SBORROW4(uVar34,1);
          cVar18 = (int)(uVar34 - 1) < 0;
          uVar19 = uVar34 == 1;
          if ((bool)uVar19) {
            puVar29 = (undefined1 *)
                      _iap2_sessionFileTransfer_findTransferEntry(param_1,pbVar24[0x79]);
            if ((puVar29 != (undefined1 *)0x0) && (lVar35 = *(long *)(puVar29 + 8), lVar35 != 0)) {
              _OUTLINED_FUNCTION_18();
              if ((extraout_x8_05 == 0) || (_OUTLINED_FUNCTION_27(), cVar18 != cVar17)) {
                _OUTLINED_FUNCTION_22();
                if (!(bool)uVar19) {
                  _OUTLINED_FUNCTION_0();
                  _dispatch_once();
                }
                lVar35 = *(long *)(puVar29 + 8);
                _OUTLINED_FUNCTION_27();
              }
              else {
                puVar36 = *(undefined **)(extraout_x8_06 + 0x110);
              }
              iVar21 = _OUTLINED_FUNCTION_31();
              if (iVar21 != 0) {
                _OUTLINED_FUNCTION_8(*puVar29,DAT_1001b3358);
                local_ba = (undefined2)extraout_w11_01;
                uStack_b8 = (undefined2)((uint)extraout_w11_01 >> 0x10);
                uStack_b4 = (undefined2)extraout_w12;
                uStack_b2 = (undefined2)((uint)extraout_w12 >> 0x10);
                uStack_bc = extraout_w8_02;
                local_b6 = extraout_w8_02;
                uVar28 = _OUTLINED_FUNCTION_6();
                __os_log_impl(uVar28,puVar36,1,
                              "#PlaybackQueueList cancel previous transfer: id=%d(%d) type=%d(%d) state=%d"
                              ,&local_d0,0x20);
                lVar35 = *(long *)(puVar29 + 8);
              }
              __cancelPendingTransfer(lVar35);
            }
            pbVar24[0x78] = 0;
            pbVar24[0x79] = 0;
          }
          uVar28 = _OUTLINED_FUNCTION_83();
          iVar21 = _iAP2FileTransferAllocateBufferID(uVar28,extraout_w1,pbVar24 + 0x79);
          if (iVar21 == 0) {
            if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_27(), cVar18 != cVar17)) {
              _OUTLINED_FUNCTION_22();
              if (!(bool)uVar19) {
                _OUTLINED_FUNCTION_0();
                _dispatch_once();
              }
              _OUTLINED_FUNCTION_18();
            }
            iVar21 = _OUTLINED_FUNCTION_11();
            if (iVar21 != 0) {
              _OUTLINED_FUNCTION_7();
              _OUTLINED_FUNCTION_16();
              __os_log_error_impl();
            }
          }
          else {
            pbVar24[0x78] = 1;
            lVar35 = _OUTLINED_FUNCTION_47();
            if (lVar35 == 0) {
              uVar28 = 0;
              goto joined_r0x000100148398;
            }
            auVar41 = _OUTLINED_FUNCTION_83();
            uVar28 = _OUTLINED_FUNCTION_38(auVar41._0_8_,auVar41._8_8_,pbVar24[0x79]);
            _OUTLINED_FUNCTION_67(uVar28,extraout_w1);
            _iAP2FileTransferCreate();
            _iAP2FileTransferTypeData(lVar35,bVar40,0);
            iVar21 = _iap2_sessionFileTransfer_addTransferForFeature(param_1,0xe,lVar35,0);
            bVar20 = _gLogObjects == 0;
            bVar16 = bVar20 || _gNumLogObjects == 0x22;
            if (iVar21 != 0) {
              if (bVar20 || _gNumLogObjects < 0x23) {
                _OUTLINED_FUNCTION_84();
                if (!bVar16) {
                  _OUTLINED_FUNCTION_0();
                  _dispatch_once();
                }
                _OUTLINED_FUNCTION_18();
              }
              iVar21 = _OUTLINED_FUNCTION_75();
              if (iVar21 != 0) {
                _OUTLINED_FUNCTION_8(*(undefined1 *)(lVar35 + 0x6d),DAT_1001b3100);
                _OUTLINED_FUNCTION_6();
                _OUTLINED_FUNCTION_17();
                __os_log_impl();
              }
              if (*(long *)(pbVar24 + 0x80) != 0) {
                _CFRelease();
                pbVar24[0x80] = 0;
                pbVar24[0x81] = 0;
                pbVar24[0x82] = 0;
                pbVar24[0x83] = 0;
                pbVar24[0x84] = 0;
                pbVar24[0x85] = 0;
                pbVar24[0x86] = 0;
                pbVar24[0x87] = 0;
              }
              bVar16 = (bool)(bVar3 ^ 1);
              if (local_100 == (undefined8 *)0x0) {
                bVar16 = true;
              }
              if (bVar16) {
                uVar28 = 0;
              }
              else {
                uVar28 = _CFDataCreateWithBytesNoCopy
                                   (*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,local_100,
                                    local_11c,*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0);
              }
              *(undefined8 *)(pbVar24 + 0x80) = uVar28;
              pbVar24[0x7a] = bVar40;
              cVar18 = '\0';
              uVar19 = (char)local_7a == '\0';
              cVar17 = '\0';
              uVar32 = __sendPBQTransferTypeAndAvailability
                                 (param_1,bVar40,1 < bVar2,bVar4 & 1,!(bool)uVar19);
              if ((uVar32 & 1) == 0) {
                if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_27(), cVar18 != cVar17)) {
                  _OUTLINED_FUNCTION_84();
                  if (!(bool)uVar19) {
                    _OUTLINED_FUNCTION_0();
                    _dispatch_once();
                  }
                  _OUTLINED_FUNCTION_18();
                }
                iVar21 = _OUTLINED_FUNCTION_11();
                if (iVar21 != 0) {
                  _OUTLINED_FUNCTION_7();
                  _OUTLINED_FUNCTION_16();
                  __os_log_error_impl();
                }
                _iAP2FileTransferCancel(lVar35);
              }
              return 1;
            }
            if (bVar20 || _gNumLogObjects < 0x23) {
              _OUTLINED_FUNCTION_84();
              if (!bVar16) {
                _OUTLINED_FUNCTION_0();
                _dispatch_once();
              }
              _OUTLINED_FUNCTION_18();
            }
            iVar21 = _OUTLINED_FUNCTION_11();
            if (iVar21 != 0) {
              _OUTLINED_FUNCTION_7();
              _OUTLINED_FUNCTION_16();
              __os_log_error_impl();
            }
            _iAP2FileTransferRelease(lVar35);
          }
          uVar28 = 1;
joined_r0x000100148398:
          if (local_100 != (undefined8 *)0x0) {
            _free(local_100);
            return uVar28;
          }
          return uVar28;
        }
        _OUTLINED_FUNCTION_74(&_kCFACCNowPlaying_PlaybackQueueContentInfo_List);
        _logObjectForModule();
        iVar21 = _OUTLINED_FUNCTION_7();
        if (iVar21 == 0) {
          return 0;
        }
        _OUTLINED_FUNCTION_7();
      }
    }
  }
  _OUTLINED_FUNCTION_16();
LAB_100148404:
  __os_log_error_impl();
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001499f0
 * original code SHA256: 2f269c679f98bfc091cc7987151dd74bbd2dd3c337e660304e0922088a4f3465
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 __startNowPlayingUpdatesHandler(long *param_1,long param_2)

{
  char in_NG;
  char cVar1;
  undefined1 in_ZR;
  char in_OV;
  char cVar2;
  undefined1 uVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  undefined1 *puVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  ulong uVar14;
  undefined8 uVar15;
  long lVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  long lVar19;
  byte *pbVar20;
  long *plVar21;
  uint uVar22;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long extraout_x8_04;
  undefined8 uVar23;
  ushort uVar24;
  undefined8 unaff_x24;
  undefined *puVar25;
  undefined1 auVar26 [16];
  undefined8 local_a8;
  undefined8 local_a0;
  undefined4 local_98;
  int local_94;
  undefined4 local_90;
  int local_8c;
  undefined2 uStack_88;
  ushort uStack_86;
  undefined2 uStack_84;
  undefined2 local_82;
  ushort uStack_80;
  undefined2 local_7e;
  undefined8 local_7c;
  uint local_74;
  undefined2 local_70;
  undefined4 local_6e;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  puVar10 = (undefined1 *)_iap2_feature_getFeature(param_1,0xe);
  if (puVar10 == (undefined1 *)0x0) {
    return 0;
  }
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_24(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_2();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_18();
  }
  iVar6 = _OUTLINED_FUNCTION_75();
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_7();
    _OUTLINED_FUNCTION_26();
    _OUTLINED_FUNCTION_42();
    __os_log_debug_impl();
  }
  uVar23 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
  lVar11 = _CFArrayCreateMutable(uVar23,0x1c,0);
  lVar12 = _CFArrayCreateMutable(uVar23,0x12,0);
  lVar13 = _iAP2MsgGetFirstParam(param_2,0);
  uVar23 = DAT_1001b30b0;
  if (lVar13 == 0) {
    uVar22 = 0;
    local_98 = 0;
    local_a8 = 0;
    local_a0 = 0;
  }
  else {
    local_a8 = 0;
    local_a0 = 0;
    local_98 = 0;
    uVar22 = 0;
    _OUTLINED_FUNCTION_11();
    uVar17 = DAT_1001b3108;
    do {
      iVar6 = _iAP2MsgGetParamID(lVar13);
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_2();
        uVar18 = unaff_x24;
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
      }
      else {
        uVar18 = *(undefined8 *)(extraout_x8 + 0x110);
      }
      uVar14 = _os_log_type_enabled(uVar18,2);
      if ((uVar14 & 1) != 0) {
        _OUTLINED_FUNCTION_62(uVar23);
        uVar15 = _OUTLINED_FUNCTION_6();
        __os_log_debug_impl(uVar15,uVar18,2,"msgParamID: %d");
      }
      in_OV = SBORROW4(iVar6,2);
      in_NG = iVar6 + -2 < 0;
      in_ZR = iVar6 == 2;
      if ((bool)in_ZR) {
        _OUTLINED_FUNCTION_40();
        for (lVar16 = _iAP2MsgGetFirstParam(); lVar16 != 0;
            lVar16 = _iAP2MsgGetNextParam(auVar26._0_8_,auVar26._8_8_,lVar16)) {
          uVar9 = _iAP2MsgGetParamID(lVar16);
          if (((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), in_NG != in_OV)) &&
             (_OUTLINED_FUNCTION_2(), !(bool)in_ZR)) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
          }
          _OUTLINED_FUNCTION_20();
          iVar6 = _os_log_type_enabled();
          if (iVar6 != 0) {
            _OUTLINED_FUNCTION_62(uVar23);
            _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_71();
            __os_log_debug_impl();
          }
          uVar14 = _iAP2MsgIsDataVoid(lVar16);
          if ((uVar14 & 1) == 0) {
            if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), in_NG != in_OV)) {
              _OUTLINED_FUNCTION_2();
              if (!(bool)in_ZR) {
                _OUTLINED_FUNCTION_0();
                _dispatch_once();
              }
              _OUTLINED_FUNCTION_18();
            }
            iVar6 = _OUTLINED_FUNCTION_11();
            if (iVar6 == 0) goto LAB_100149f30;
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_62(DAT_1001b3100);
            _OUTLINED_FUNCTION_35();
            uStack_86 = 2;
            uStack_84 = 0;
            _OUTLINED_FUNCTION_11();
            goto LAB_10014a6d0;
          }
          uVar22 = 1 << (ulong)(uVar9 & 0x1f) | uVar22;
          auVar26 = _OUTLINED_FUNCTION_40();
        }
      }
      else {
        in_OV = SBORROW4(iVar6,1);
        in_NG = iVar6 + -1 < 0;
        in_ZR = iVar6 == 1;
        if ((bool)in_ZR) {
          _OUTLINED_FUNCTION_40();
          for (lVar16 = _iAP2MsgGetFirstParam(); lVar16 != 0;
              lVar16 = _iAP2MsgGetNextParam(auVar26._0_8_,auVar26._8_8_,lVar16)) {
            iVar6 = _iAP2MsgGetParamID(lVar16);
            if (((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), in_NG != in_OV)) &&
               (_OUTLINED_FUNCTION_2(), !(bool)in_ZR)) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_20();
            iVar8 = _os_log_type_enabled();
            if (iVar8 != 0) {
              local_90 = (undefined4)uVar23;
              local_8c = iVar6;
              _OUTLINED_FUNCTION_6();
              _OUTLINED_FUNCTION_71();
              __os_log_debug_impl();
            }
            in_OV = SBORROW4(iVar6,0x11);
            in_NG = iVar6 + -0x11 < 0;
            in_ZR = iVar6 == 0x11;
            if ((bool)in_ZR) {
              local_94 = 0;
              local_98 = _iAP2MsgGetDataAsU32(lVar16,&local_94);
              if (local_94 != 0) {
                _logObjectForModule();
                iVar6 = _OUTLINED_FUNCTION_7();
                if (iVar6 == 0) goto LAB_100149f30;
                _iAP2MsgGetMsgID(param_2);
                local_90 = (undefined4)DAT_1001b3100;
                local_8c = 0x11;
                _OUTLINED_FUNCTION_3();
                goto LAB_10014a6d0;
              }
              uVar14 = (ulong)local_a8 >> 0x20;
              local_a8 = CONCAT44((int)uVar14,1);
            }
            else {
              in_OV = SBORROW4(iVar6,0xe);
              in_NG = iVar6 + -0xe < 0;
              in_ZR = iVar6 == 0xe;
              if ((bool)in_ZR) {
                uVar14 = _iAP2MsgIsDataVoid(lVar16);
                if ((uVar14 & 1) == 0) {
                  _logObjectForModule();
                  iVar6 = _OUTLINED_FUNCTION_7();
                  if (iVar6 == 0) goto LAB_100149f30;
                  _iAP2MsgGetMsgID(param_2);
                  local_90 = (undefined4)DAT_1001b3100;
                  local_8c = 0xe;
                  _OUTLINED_FUNCTION_3();
                  goto LAB_10014a6d0;
                }
                local_a0 = CONCAT44(1,(uint)local_a0);
              }
              else {
                in_OV = SBORROW4(iVar6,0xf);
                in_NG = iVar6 + -0xf < 0;
                in_ZR = iVar6 == 0xf;
                if ((bool)in_ZR) {
                  uVar14 = _iAP2MsgIsDataVoid(lVar16);
                  if ((uVar14 & 1) == 0) {
                    _logObjectForModule();
                    iVar6 = _OUTLINED_FUNCTION_7();
                    if (iVar6 == 0) goto LAB_100149f30;
                    _iAP2MsgGetMsgID(param_2);
                    local_90 = (undefined4)DAT_1001b3100;
                    local_8c = 0xf;
                    _OUTLINED_FUNCTION_3();
                    goto LAB_10014a6d0;
                  }
                  uVar14 = (ulong)local_a0 >> 0x20;
                  local_a0 = CONCAT44((int)uVar14,1);
                }
                else {
                  in_OV = SBORROW4(iVar6,1);
                  in_NG = iVar6 + -1 < 0;
                  in_ZR = iVar6 == 1;
                  if ((bool)in_ZR) {
                    uVar14 = _iAP2MsgIsDataVoid(lVar16);
                    if ((uVar14 & 1) == 0) {
                      _logObjectForModule();
                      iVar6 = _OUTLINED_FUNCTION_7();
                      if (iVar6 == 0) goto LAB_100149f30;
                      uVar7 = _iAP2MsgGetMsgID(param_2);
                      local_90 = (undefined4)DAT_1001b3100;
                      local_8c = 1;
                      uStack_88 = 0x400;
                      uStack_86 = 1;
                      uStack_84 = 0;
                      local_82 = 0x400;
                      uStack_80 = (ushort)uVar7;
                      local_7e = (undefined2)((uint)uVar7 >> 0x10);
                      _OUTLINED_FUNCTION_6();
                      goto LAB_10014a6d0;
                    }
                    local_a8 = CONCAT44(1,(undefined4)local_a8);
                  }
                  else {
                    uVar14 = _iAP2MsgIsDataVoid(lVar16);
                    if ((uVar14 & 1) == 0) {
                      _logObjectForModule();
                      iVar8 = _OUTLINED_FUNCTION_7();
                      if (iVar8 == 0) goto LAB_100149f30;
                      _iAP2MsgGetMsgID(param_2);
                      local_90 = (undefined4)DAT_1001b3100;
                      local_8c = iVar6;
                      _OUTLINED_FUNCTION_3();
                      goto LAB_10014a6d0;
                    }
                  }
                }
              }
            }
            _CFArrayAppendValue(lVar12,iVar6);
            auVar26 = _OUTLINED_FUNCTION_40();
          }
        }
        else if (iVar6 == 0) {
          _OUTLINED_FUNCTION_40();
          for (lVar16 = _iAP2MsgGetFirstParam(); lVar16 != 0;
              lVar16 = _iAP2MsgGetNextParam(auVar26._0_8_,auVar26._8_8_,lVar16)) {
            uVar7 = _iAP2MsgGetParamID(lVar16);
            if (((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), in_NG != in_OV)) &&
               (_OUTLINED_FUNCTION_2(), !(bool)in_ZR)) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_20();
            iVar6 = _os_log_type_enabled();
            if (iVar6 != 0) {
              _OUTLINED_FUNCTION_62(uVar23);
              _OUTLINED_FUNCTION_6();
              _OUTLINED_FUNCTION_71();
              __os_log_debug_impl();
            }
            uVar14 = _iAP2MsgIsDataVoid(lVar16);
            if ((uVar14 & 1) == 0) {
              if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), in_NG != in_OV)) {
                _OUTLINED_FUNCTION_2();
                if (!(bool)in_ZR) {
                  _OUTLINED_FUNCTION_0();
                  _dispatch_once();
                }
                _OUTLINED_FUNCTION_18();
              }
              iVar6 = _OUTLINED_FUNCTION_11();
              if (iVar6 != 0) {
                _iAP2MsgGetMsgID(param_2);
                _OUTLINED_FUNCTION_62(DAT_1001b3100);
                _OUTLINED_FUNCTION_35();
                uStack_86 = 0;
                uStack_84 = 0;
                _OUTLINED_FUNCTION_11();
LAB_10014a6d0:
                _OUTLINED_FUNCTION_16();
                __os_log_error_impl();
              }
LAB_100149f30:
              if (lVar11 != 0) {
                _CFRelease(lVar11);
              }
              if (lVar12 != 0) {
                _CFRelease(lVar12);
              }
              return 0;
            }
            _CFArrayAppendValue(lVar11,uVar7);
            auVar26 = _OUTLINED_FUNCTION_40();
          }
        }
        else {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_2();
            uVar18 = unaff_x24;
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
            }
          }
          else {
            uVar18 = *(undefined8 *)(extraout_x8_00 + 0x110);
          }
          iVar6 = _os_log_type_enabled(uVar18,1);
          if (iVar6 != 0) {
            _iAP2MsgGetMsgID(param_2);
            _OUTLINED_FUNCTION_62(uVar17);
            uVar7 = _OUTLINED_FUNCTION_35();
            uStack_86 = (ushort)uVar7;
            uStack_84 = (undefined2)((uint)uVar7 >> 0x10);
            uVar15 = _OUTLINED_FUNCTION_6();
            __os_log_impl(uVar15,uVar18,1,"Unknown Param ID: %d for Msg ID: 0x%04X - ignoring param"
                         );
          }
        }
      }
      lVar13 = _iAP2MsgGetNextParam(param_2,0,lVar13);
    } while (lVar13 != 0);
  }
  __removeSubscribersForSubFeatures(puVar10);
  if (*(long *)(puVar10 + 8) != 0) {
    _CFRelease();
  }
  *(long *)(puVar10 + 8) = lVar11;
  if (*(long *)(puVar10 + 0x10) != 0) {
    _CFRelease();
  }
  *(long *)(puVar10 + 0x10) = lVar12;
  puVar10[0x28] = (char)((ulong)local_a8 >> 0x20);
  puVar10[0x50] = (char)local_a0;
  puVar10[0x51] = (char)local_a8;
  puVar10[0x52] = (char)((ulong)local_a0 >> 0x20);
  puVar10[0x53] = 0;
  *(undefined4 *)(puVar10 + 0x54) = 0;
  *(undefined4 *)(puVar10 + 0x58) = local_98;
  *(uint *)(puVar10 + 0x5c) = uVar22 | (uint)local_a0;
  *puVar10 = 1;
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_2();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_18();
  }
  iVar6 = _OUTLINED_FUNCTION_75();
  uVar23 = 0x1001b3000;
  if (iVar6 != 0) {
    uVar17 = _CFArrayGetCount(*(undefined8 *)(puVar10 + 8));
    local_90 = (undefined4)DAT_1001b30a8;
    local_8c = (int)uVar17;
    uStack_88 = (undefined2)((ulong)uVar17 >> 0x20);
    uStack_86 = (ushort)((ulong)uVar17 >> 0x30);
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_26();
    _OUTLINED_FUNCTION_43();
    __os_log_debug_impl();
  }
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_2();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_18();
  }
  iVar6 = _OUTLINED_FUNCTION_75();
  if (iVar6 != 0) {
    uVar17 = _CFArrayGetCount(*(undefined8 *)(puVar10 + 0x10));
    local_90 = (undefined4)DAT_1001b30a8;
    local_8c = (int)uVar17;
    uStack_88 = (undefined2)((ulong)uVar17 >> 0x20);
    uStack_86 = (ushort)((ulong)uVar17 >> 0x30);
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_26();
    _OUTLINED_FUNCTION_43();
    __os_log_debug_impl();
  }
  if ((*param_1 != 0) && (*(long *)(puVar10 + 8) != 0)) {
    if (*(long *)(puVar10 + 0x10) == 0) goto LAB_10014a4e8;
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
      _OUTLINED_FUNCTION_2();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_18();
    }
    iVar6 = _OUTLINED_FUNCTION_90();
    if (iVar6 != 0) {
      lVar11 = param_1[1];
      local_90 = (undefined4)DAT_1001b3088;
      local_8c = (int)lVar11;
      uStack_88 = (undefined2)((ulong)lVar11 >> 0x20);
      uStack_86 = (ushort)((ulong)lVar11 >> 0x30);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_26();
      _OUTLINED_FUNCTION_78();
    }
    lVar11 = _platform_nowPlaying_copyDefaultMediaItemAttributes();
    lVar12 = _platform_nowPlaying_copyDefaultPlaybackAttributes();
    lVar13 = _OUTLINED_FUNCTION_13();
    uVar17 = _malloc_type_malloc(0xffff,0xf3803b9c);
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
      _OUTLINED_FUNCTION_2();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    else {
      uVar23 = *(undefined8 *)(extraout_x8_01 + 0x110);
    }
    iVar6 = _os_log_type_enabled(uVar23,0);
    if (iVar6 != 0) {
      local_7c = param_1[1];
      local_90 = (undefined4)DAT_1001b3080;
      local_8c = 0x1d162e;
      uStack_88 = 1;
      uStack_86 = 0;
      uStack_84 = 0x400;
      local_82 = 0x5c9;
      uStack_80 = 0;
      local_7e = 0x840;
      uVar18 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar18,uVar23,0,
                    "%s:%d - iAP2MsgInit with cleanupCB - _artworkFileTransferIDSent endpointUUID: %@"
                    ,&local_90,0x1c);
    }
    auVar26 = _OUTLINED_FUNCTION_33();
    _iAP2MsgInit(auVar26._0_8_,auVar26._8_8_,uVar17,0xffff);
    lVar16 = _CFArrayGetCount(*(undefined8 *)(puVar10 + 8));
    if (lVar16 < 1) {
      lVar16 = 0;
      sVar5 = 0;
    }
    else {
      uVar23 = _iAP2MsgAddGroupParam(lVar13,0);
      sVar5 = __addMediaItemAttributesToMessage(lVar13,uVar23,puVar10,lVar11);
      if (((lVar13 == 0) || (*(long *)(puVar10 + 8) == 0)) ||
         (iVar6 = __isSubscribingForMediaItemAttribute(puVar10), iVar6 == 0)) {
LAB_10014a720:
        lVar16 = 0;
LAB_10014a724:
        uVar24 = 0;
      }
      else {
        uVar22 = (uint)(byte)puVar10[0x40];
        cVar2 = SBORROW4(uVar22,1);
        cVar1 = (int)(uVar22 - 1) < 0;
        uVar3 = uVar22 == 1;
        if ((bool)uVar3) {
          pbVar20 = (byte *)_iap2_sessionFileTransfer_findTransferEntry(param_1,puVar10[0x41]);
          if ((pbVar20 != (byte *)0x0) && (lVar16 = *(long *)(pbVar20 + 8), lVar16 != 0)) {
            if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), cVar1 != cVar2)) {
              _OUTLINED_FUNCTION_2();
              puVar25 = PTR___os_log_default_10022bbb0;
              if (!(bool)uVar3) {
                _OUTLINED_FUNCTION_0();
                _dispatch_once();
                puVar25 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar25 = *(undefined **)(extraout_x8_04 + 0x110);
            }
            iVar6 = _os_log_type_enabled(puVar25,1);
            if (iVar6 != 0) {
              lVar19 = *(long *)(pbVar20 + 8);
              local_6e = *(undefined4 *)(lVar19 + 0x68);
              local_90 = (undefined4)DAT_1001b3360;
              local_8c = 0x6b2;
              uStack_88 = 0x400;
              uStack_86 = (ushort)*pbVar20;
              uStack_84 = 0;
              local_82 = 0x400;
              uStack_80 = (ushort)*(byte *)(lVar19 + 0x6d);
              local_7e = 0;
              local_7c = CONCAT26(0x400,CONCAT42(*(undefined4 *)(pbVar20 + 4),0x400));
              local_74 = (uint)*(ushort *)(lVar19 + 0x70);
              local_70 = 0x400;
              uVar17 = _OUTLINED_FUNCTION_6();
              __os_log_impl(uVar17,puVar25,1,
                            "#Artwork %d: cancel previous transfer: id=%d(%d) type=%d(%d) state=%d",
                            &local_90,0x26);
            }
            __cancelPendingTransfer(lVar16);
          }
          *(undefined2 *)(puVar10 + 0x40) = 0;
        }
        if (param_1[5] == 0) goto LAB_10014a720;
        lVar16 = *(long *)(param_1[5] + 0x18);
        if (lVar16 == 0) {
          lVar16 = 0;
          uVar24 = 0;
          goto LAB_10014a728;
        }
        uVar18 = 1;
        uVar17 = _iAP2LinkGetSessionForService(lVar16,1);
        iVar6 = _iAP2FileTransferAllocateBufferID
                          (*(undefined8 *)(param_1[5] + 0x18),uVar17,puVar10 + 0x41);
        if (iVar6 == 0) {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_24(), cVar1 != cVar2)) {
            _OUTLINED_FUNCTION_2();
            if (!(bool)uVar3) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_27();
          }
          else {
            uVar18 = *(undefined8 *)(extraout_x8_02 + 0x110);
          }
          iVar6 = _os_log_type_enabled(uVar18,0x10);
          if (iVar6 != 0) {
            uVar23 = _OUTLINED_FUNCTION_7();
            __os_log_error_impl(uVar23,uVar18,0x10,
                                "#Artwork Failed to allocate file transfer buffer ID!",&local_90,2);
          }
          goto LAB_10014a720;
        }
        puVar10[0x40] = 1;
        auVar26 = _OUTLINED_FUNCTION_47();
        lVar16 = auVar26._0_8_;
        if (lVar16 != 0) {
          uVar18 = _OUTLINED_FUNCTION_38
                             (*(undefined8 *)(param_1[5] + 0x18),auVar26._8_8_,puVar10[0x41]);
          _OUTLINED_FUNCTION_67(uVar18,uVar17);
          _iAP2FileTransferCreate();
          auVar26 = _OUTLINED_FUNCTION_20();
          _iAP2FileTransferTypeData(auVar26._0_8_,auVar26._8_8_,0);
          auVar26 = _OUTLINED_FUNCTION_54();
          iVar6 = _iap2_sessionFileTransfer_addTransferForFeature
                            (auVar26._0_8_,auVar26._8_8_,lVar16,0);
          if (iVar6 != 0) {
            _iAP2MsgSetCleanupCB(lVar13,__artworkFileTransferIDSent);
            plVar21 = (long *)_OUTLINED_FUNCTION_46();
            *plVar21 = (long)param_1;
            *(undefined1 *)(plVar21 + 1) = puVar10[0x41];
            *(undefined4 *)((long)plVar21 + 0xc) = 2;
            *(long **)(lVar13 + 0x30) = plVar21;
            lVar19 = _iAP2MsgAddU8Param(lVar13,uVar23,0x1a);
            uVar24 = (ushort)(lVar19 != 0);
            if (*(long *)(puVar10 + 0x48) != 0) {
              _CFRelease();
              *(undefined8 *)(puVar10 + 0x48) = 0;
            }
            goto LAB_10014a728;
          }
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_5(), cVar1 != cVar2)) {
            _OUTLINED_FUNCTION_2();
            if (!(bool)uVar3) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_11();
          }
          else {
            uVar23 = *(undefined8 *)(extraout_x8_03 + 0x110);
          }
          iVar6 = _os_log_type_enabled(uVar23,0x10);
          if (iVar6 != 0) {
            uVar17 = _OUTLINED_FUNCTION_7();
            __os_log_error_impl(uVar17,uVar23,0x10,"#Artwork Failed to add file transfer!",&local_90
                                ,2);
          }
          _iAP2FileTransferRelease(lVar16);
          goto LAB_10014a724;
        }
        uVar24 = 0;
      }
LAB_10014a728:
      sVar5 = uVar24 + sVar5;
    }
    lVar19 = _CFArrayGetCount(*(undefined8 *)(puVar10 + 0x10));
    if (0 < lVar19) {
      _OUTLINED_FUNCTION_60();
      uVar23 = _iAP2MsgAddGroupParam();
      sVar4 = __addplaybackAttributesToMessage(lVar13,uVar23,puVar10,lVar12,0,1);
      sVar5 = sVar4 + sVar5;
    }
    uVar3 = sVar5 == 0;
    cVar1 = '\0';
    cVar2 = '\0';
    if ((bool)uVar3) {
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), cVar1 != cVar2)) {
        _OUTLINED_FUNCTION_2();
        if (!(bool)uVar3) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_18();
      }
      iVar6 = _OUTLINED_FUNCTION_90();
      if (iVar6 != 0) {
        local_90 = (undefined4)DAT_1001b3090;
        local_8c = 0x1d162e;
        uStack_88 = 1;
        uStack_86 = 0;
        _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_26();
        _OUTLINED_FUNCTION_78();
      }
LAB_10014a3d8:
      _OUTLINED_FUNCTION_60();
      _iAP2MsgCleanup();
    }
    else {
      uVar14 = _iap2_sessionControl_sendOutgoingMessageAndCallbackOnACK(param_1,lVar13);
      if ((lVar16 != 0) && ((uVar14 & 1) == 0)) {
        _iAP2FileTransferCancel(lVar16);
        _iap2_sessionFileTransfer_removeTransferForFeature(param_1,0xe,lVar16);
        if (*(void **)(lVar16 + 0x40) != (void *)0x0) {
          _free(*(void **)(lVar16 + 0x40));
          *(undefined8 *)(lVar16 + 0x40) = 0;
        }
        goto LAB_10014a3d8;
      }
    }
    if (lVar11 != 0) {
      _CFRelease(lVar11);
    }
    if (lVar12 != 0) {
      _CFRelease(lVar12);
    }
  }
  if (*(long *)(puVar10 + 0x10) != 0) {
    lVar11 = _CFArrayGetCount();
    cVar2 = SBORROW8(lVar11,1);
    cVar1 = lVar11 + -1 < 0;
    uVar3 = lVar11 == 1;
    if (0 < lVar11) {
      _acc_manager2_performPlatformWorkAsync(&___block_literal_global_24);
      uVar14 = __isSubscribingForPlaybackAttribute(puVar10,0xf);
      if (((uVar14 & 1) != 0) ||
         (iVar6 = __isSubscribingForPlaybackAttribute(puVar10,0x11), iVar6 != 0)) {
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), cVar1 != cVar2)) {
          _OUTLINED_FUNCTION_2();
          if (!(bool)uVar3) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
          }
          _OUTLINED_FUNCTION_18();
        }
        iVar6 = _OUTLINED_FUNCTION_75();
        if (iVar6 != 0) {
          _OUTLINED_FUNCTION_7();
          _OUTLINED_FUNCTION_17();
          __os_log_impl();
        }
        _acc_manager2_performPlatformWorkAsync(&___block_literal_global_28);
      }
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), cVar1 != cVar2)) {
        _OUTLINED_FUNCTION_2();
        if (!(bool)uVar3) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_18();
      }
      iVar6 = _OUTLINED_FUNCTION_75();
      if (iVar6 != 0) {
        _OUTLINED_FUNCTION_7();
        _OUTLINED_FUNCTION_26();
        _OUTLINED_FUNCTION_42();
        __os_log_debug_impl();
      }
      __checkMoveWindowAndRequestPBQList(1,*(undefined4 *)(puVar10 + 0x54),param_1,puVar10);
    }
  }
  if (*(long *)(puVar10 + 8) == 0) {
    return 1;
  }
LAB_10014a4e8:
  lVar11 = _CFArrayGetCount();
  if (0 < lVar11) {
    _acc_manager2_performPlatformWorkAsync(&___block_literal_global_32);
  }
  iVar6 = __isSubscribingForMediaItemAttribute(puVar10);
  if (iVar6 != 0) {
    _acc_manager2_performPlatformWorkAsync(&___block_literal_global_35);
  }
  return 1;
}


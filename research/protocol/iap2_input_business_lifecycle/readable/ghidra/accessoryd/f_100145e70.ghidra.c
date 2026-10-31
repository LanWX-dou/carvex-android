/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100145e70
 * original code SHA256: 6a2fec254b2fb1e336933230ca5684343541ed600badc55d3b6097396fd7a53a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_nowPlaying_mediaItemArtworkUpdateHandler(long *param_1,long param_2)

{
  char in_NG;
  undefined1 in_ZR;
  bool bVar1;
  char in_OV;
  char cVar2;
  char cVar3;
  bool bVar4;
  undefined1 uVar5;
  int iVar6;
  char *pcVar7;
  undefined8 uVar8;
  undefined1 *puVar9;
  undefined8 uVar10;
  long *plVar11;
  undefined8 uVar12;
  ulong uVar13;
  undefined2 extraout_w8;
  uint uVar14;
  long extraout_x8;
  undefined4 extraout_w11;
  long lVar15;
  undefined *puVar16;
  undefined1 auVar17 [16];
  undefined4 local_80;
  char *local_7c;
  undefined2 local_74;
  undefined4 local_72;
  undefined2 local_6e;
  undefined8 local_6c;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if (*param_1 == 0) {
    return 0;
  }
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_39(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_22();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  _OUTLINED_FUNCTION_13();
  iVar6 = _os_log_type_enabled();
  if (iVar6 != 0) {
    local_7c = (char *)param_1[1];
    local_80 = (undefined4)DAT_1001b3088;
    _OUTLINED_FUNCTION_6();
    auVar17 = _OUTLINED_FUNCTION_23();
    __os_log_impl(auVar17._0_8_,auVar17._8_8_,1);
  }
  bVar4 = _gLogObjects == 0;
  bVar1 = bVar4 || _gNumLogObjects == 0x22;
  if (param_2 == 0) {
    if (bVar4 || _gNumLogObjects < 0x23) {
      _OUTLINED_FUNCTION_22();
      if (!bVar1) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    iVar6 = _OUTLINED_FUNCTION_15();
    if (iVar6 == 0) goto LAB_100145fa0;
    _OUTLINED_FUNCTION_4();
    _OUTLINED_FUNCTION_14();
  }
  else {
    if (bVar4 || _gNumLogObjects < 0x23) {
      _OUTLINED_FUNCTION_22();
      if (!bVar1) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    iVar6 = _OUTLINED_FUNCTION_15();
    if (iVar6 == 0) goto LAB_100145fa0;
    local_7c = (char *)_CFDataGetLength(param_2);
    local_80 = (undefined4)DAT_1001b30a8;
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_14();
  }
  __os_log_debug_impl();
LAB_100145fa0:
  _OUTLINED_FUNCTION_54();
  pcVar7 = (char *)_iap2_feature_getFeature();
  if (pcVar7 == (char *)0x0) {
    return 0;
  }
  if (*pcVar7 == '\x01') {
    uVar8 = __isSubscribingForMediaItemAttribute(pcVar7);
    if ((int)uVar8 == 0) {
      return uVar8;
    }
    uVar14 = (uint)(byte)pcVar7[0x40];
    cVar2 = SBORROW4(uVar14,1);
    cVar3 = (int)(uVar14 - 1) < 0;
    uVar5 = uVar14 == 1;
    if ((bool)uVar5) {
      puVar9 = (undefined1 *)_iap2_sessionFileTransfer_findTransferEntry(param_1,pcVar7[0x41]);
      if ((puVar9 != (undefined1 *)0x0) && (lVar15 = *(long *)(puVar9 + 8), lVar15 != 0)) {
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_39(), cVar3 != cVar2)) {
          _OUTLINED_FUNCTION_22();
          if (!(bool)uVar5) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
          }
          lVar15 = *(long *)(puVar9 + 8);
          _OUTLINED_FUNCTION_41();
        }
        _OUTLINED_FUNCTION_60();
        iVar6 = _os_log_type_enabled();
        if (iVar6 != 0) {
          _OUTLINED_FUNCTION_12(*puVar9,DAT_1001b3358);
          _OUTLINED_FUNCTION_57();
          local_6c = CONCAT26(extraout_w8,CONCAT42(extraout_w11,extraout_w8));
          _OUTLINED_FUNCTION_6();
          auVar17 = _OUTLINED_FUNCTION_27();
          __os_log_impl(auVar17._0_8_,auVar17._8_8_,1);
          lVar15 = *(long *)(puVar9 + 8);
        }
        __cancelPendingTransfer(lVar15);
      }
      pcVar7[0x40] = '\0';
      pcVar7[0x41] = '\0';
    }
    if (param_1[5] != 0) {
      lVar15 = *(long *)(param_1[5] + 0x18);
      if (lVar15 == 0) {
        return 0;
      }
      uVar8 = _iAP2LinkGetSessionForService(lVar15,1);
      iVar6 = _iAP2FileTransferAllocateBufferID
                        (*(undefined8 *)(param_1[5] + 0x18),uVar8,pcVar7 + 0x41);
      if (iVar6 == 0) {
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_39(), cVar3 != cVar2)) {
          _OUTLINED_FUNCTION_22();
          if (!(bool)uVar5) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
          }
          _OUTLINED_FUNCTION_18();
        }
        iVar6 = _OUTLINED_FUNCTION_11();
        if (iVar6 != 0) {
          _OUTLINED_FUNCTION_4();
          _OUTLINED_FUNCTION_41();
          __os_log_error_impl();
        }
      }
      else {
        pcVar7[0x40] = '\x01';
        auVar17 = _OUTLINED_FUNCTION_47();
        lVar15 = auVar17._0_8_;
        if (lVar15 == 0) {
          return 0;
        }
        uVar10 = _OUTLINED_FUNCTION_38
                           (*(undefined8 *)(param_1[5] + 0x18),auVar17._8_8_,pcVar7[0x41]);
        _OUTLINED_FUNCTION_67(uVar10,uVar8);
        _iAP2FileTransferCreate();
        auVar17 = _OUTLINED_FUNCTION_53();
        _iAP2FileTransferTypeData(auVar17._0_8_,auVar17._8_8_,0);
        auVar17 = _OUTLINED_FUNCTION_54();
        iVar6 = _iap2_sessionFileTransfer_addTransferForFeature
                          (auVar17._0_8_,auVar17._8_8_,lVar15,0);
        if (iVar6 == 0) {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_39(), cVar3 != cVar2)) {
            _OUTLINED_FUNCTION_22();
            if (!(bool)uVar5) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_18();
          }
          iVar6 = _OUTLINED_FUNCTION_11();
          if (iVar6 != 0) {
            _OUTLINED_FUNCTION_4();
            _OUTLINED_FUNCTION_41();
            __os_log_error_impl();
          }
          _iAP2FileTransferRelease(lVar15);
        }
        else {
          uVar8 = _OUTLINED_FUNCTION_13();
          uVar10 = _malloc_type_malloc(0xffff,0xb3dff8c7);
          plVar11 = (long *)_OUTLINED_FUNCTION_46();
          *plVar11 = (long)param_1;
          *(char *)(plVar11 + 1) = pcVar7[0x41];
          *(undefined4 *)((long)plVar11 + 0xc) = 2;
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_39(), cVar3 != cVar2)) {
            _OUTLINED_FUNCTION_2();
            puVar16 = PTR___os_log_default_10022bbb0;
            if (!(bool)uVar5) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(extraout_x8 + 0x110);
          }
          iVar6 = _os_log_type_enabled(puVar16,0);
          if (iVar6 != 0) {
            local_6c = param_1[1];
            local_80 = (undefined4)DAT_1001b3080;
            local_7c = "iap2_nowPlaying_mediaItemArtworkUpdateHandler";
            local_74 = 0x400;
            local_72 = 0x2a0;
            local_6e = 0x840;
            uVar12 = _OUTLINED_FUNCTION_6();
            __os_log_impl(uVar12,puVar16,0,
                          "%s:%d - iAP2MsgInit with cleanupCB - _artworkFileTransferIDSent endpointUUID: %@"
                          ,&local_80,0x1c);
          }
          auVar17 = _OUTLINED_FUNCTION_33();
          _iAP2MsgInit(auVar17._0_8_,auVar17._8_8_,uVar10,0xffff);
          uVar10 = _iAP2MsgAddGroupParam(uVar8,0);
          _iAP2MsgAddU8Param(uVar8,uVar10,0x1a,pcVar7[0x41]);
          if (param_2 == 0) {
            if (*(long *)(pcVar7 + 0x48) == 0) {
              cVar3 = '\0';
            }
            else {
              _CFRelease();
              cVar3 = '\0';
              pcVar7[0x48] = '\0';
              pcVar7[0x49] = '\0';
              pcVar7[0x4a] = '\0';
              pcVar7[0x4b] = '\0';
              pcVar7[0x4c] = '\0';
              pcVar7[0x4d] = '\0';
              pcVar7[0x4e] = '\0';
              pcVar7[0x4f] = '\0';
            }
          }
          else {
            uVar10 = _CFRetain(param_2);
            *(undefined8 *)(pcVar7 + 0x48) = uVar10;
            cVar3 = '\x02';
          }
          pcVar7[0x42] = cVar3;
          uVar13 = _iap2_sessionControl_sendOutgoingMessageAndCallbackOnACK(param_1,uVar8);
          if ((uVar13 & 1) == 0) {
            _iAP2FileTransferCancel(lVar15);
          }
        }
      }
      return 1;
    }
  }
  return 0;
}


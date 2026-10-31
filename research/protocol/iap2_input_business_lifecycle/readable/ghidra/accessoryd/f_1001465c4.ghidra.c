/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001465c4
 * original code SHA256: 0e29a54a1b8d5852c6d164834c33eb01ffe99b1a787fd913a8f6ab108aab800e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_nowPlaying_playbackAttributesUpdateHandler(long *param_1,long param_2)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  bool bVar5;
  int iVar6;
  char *pcVar7;
  long lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  uint uVar11;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  undefined8 unaff_x23;
  long unaff_x25;
  long unaff_x26;
  undefined1 auVar12 [16];
  int local_68;
  uint local_64;
  
  if (param_1 == (long *)0x0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  if (*param_1 == 0) {
    return 0;
  }
  _OUTLINED_FUNCTION_89(0);
  if ((extraout_x8 == 0) || (_OUTLINED_FUNCTION_31(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_28();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_27();
  }
  iVar6 = _OUTLINED_FUNCTION_31();
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_6();
    auVar12 = _OUTLINED_FUNCTION_44();
    __os_log_impl(auVar12._0_8_,auVar12._8_8_,1);
  }
  _OUTLINED_FUNCTION_54();
  pcVar7 = (char *)_iap2_feature_getFeature();
  if (pcVar7 == (char *)0x0) {
    return 0;
  }
  if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_28();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_26();
  }
  _OUTLINED_FUNCTION_61();
  iVar6 = _os_log_type_enabled();
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_1(param_1[1]);
    _OUTLINED_FUNCTION_6();
    auVar12 = _OUTLINED_FUNCTION_14();
    __os_log_impl(auVar12._0_8_,auVar12._8_8_,1);
  }
  if (*pcVar7 != '\x01') {
    return 0;
  }
  uVar11 = (uint)(byte)pcVar7[0x28];
  cVar1 = SBORROW4(uVar11,1);
  cVar2 = (int)(uVar11 - 1) < 0;
  uVar3 = uVar11 == 1;
  uVar4 = 0;
  if (!(bool)uVar3) goto LAB_100146a98;
  if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_28();
    if (!(bool)uVar3) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_26();
  }
  _OUTLINED_FUNCTION_61();
  iVar6 = _os_log_type_enabled();
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_4();
    auVar12 = _OUTLINED_FUNCTION_14();
    __os_log_impl(auVar12._0_8_,auVar12._8_8_,1);
  }
  local_64 = *(uint *)(pcVar7 + 0x18);
  local_68 = *(int *)(pcVar7 + 0x24);
  lVar8 = _CFDictionaryGetValue
                    (param_2,_kCFACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_Status);
  if (lVar8 != 0) {
    _CFNumberGetValue(lVar8,9,&local_64);
  }
  if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_28();
    if (!(bool)uVar3) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_41();
  }
  else {
    unaff_x23 = *(undefined8 *)(extraout_x8_00 + 0x110);
  }
  iVar6 = _os_log_type_enabled(unaff_x23,2);
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_27();
    _OUTLINED_FUNCTION_43();
    __os_log_debug_impl();
  }
  if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_28();
    if (!(bool)uVar3) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_26();
  }
  _OUTLINED_FUNCTION_53();
  iVar6 = _os_log_type_enabled();
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_11(local_64,DAT_1001b30b0);
    _OUTLINED_FUNCTION_21();
    __os_log_debug_impl();
  }
  lVar8 = _CFDictionaryGetValue
                    (param_2,_kCFACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_ElapsedTimeMS);
  if (lVar8 != 0) {
    _CFNumberGetValue(lVar8,9,&local_68);
  }
  if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_28();
    if (!(bool)uVar3) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_41();
  }
  else {
    unaff_x23 = *(undefined8 *)(extraout_x8_01 + 0x110);
  }
  iVar6 = _os_log_type_enabled(unaff_x23,2);
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_27();
    _OUTLINED_FUNCTION_43();
    __os_log_debug_impl();
  }
  if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_28();
    if (!(bool)uVar3) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_26();
  }
  _OUTLINED_FUNCTION_53();
  iVar6 = _os_log_type_enabled();
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_11(local_68,DAT_1001b30b0);
    _OUTLINED_FUNCTION_21();
    __os_log_debug_impl();
  }
  if (local_64 == *(uint *)(pcVar7 + 0x18)) {
    iVar6 = *(int *)(pcVar7 + 0x24);
    cVar1 = SBORROW4(local_68,iVar6);
    cVar2 = local_68 - iVar6 < 0;
    uVar4 = 1;
    if (local_68 == iVar6) goto LAB_100146a98;
  }
  cVar2 = (int)(local_64 & 0xfffffffd) < 0;
  uVar4 = (local_64 & 0xfffffffd) == 0;
  cVar1 = '\0';
  if ((bool)uVar4) {
    if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
      _OUTLINED_FUNCTION_28();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_26();
    }
    _OUTLINED_FUNCTION_53();
    iVar6 = _os_log_type_enabled();
    if (iVar6 != 0) {
      _OUTLINED_FUNCTION_4();
LAB_1001469bc:
      _OUTLINED_FUNCTION_14();
      _OUTLINED_FUNCTION_42();
      __os_log_debug_impl();
    }
LAB_1001469c8:
    __pauseElapsedTimeTimer(pcVar7);
  }
  else {
    uVar11 = local_64 - 3;
    bVar5 = *(long *)(unaff_x26 + 0xa28) == 0;
    cVar1 = SBORROW4(uVar11,1);
    cVar2 = (int)(local_64 - 4) < 0;
    uVar4 = uVar11 == 1;
    if (uVar11 < 2) {
      if (bVar5 || *(int *)(unaff_x25 + 0xa30) < 0x23) {
        _OUTLINED_FUNCTION_28();
        if (!(bool)uVar4) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_26();
      }
      _OUTLINED_FUNCTION_53();
      iVar6 = _os_log_type_enabled();
      if (iVar6 != 0) {
        _OUTLINED_FUNCTION_4();
        goto LAB_1001469bc;
      }
      goto LAB_1001469c8;
    }
    if (bVar5 || *(int *)(unaff_x25 + 0xa30) < 0x23) {
      _OUTLINED_FUNCTION_28();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_26();
    }
    _OUTLINED_FUNCTION_53();
    iVar6 = _os_log_type_enabled();
    if (iVar6 != 0) {
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_21();
      __os_log_debug_impl();
    }
    uVar11 = (uint)(byte)pcVar7[0x28];
    cVar1 = SBORROW4(uVar11,1);
    cVar2 = (int)(uVar11 - 1) < 0;
    uVar4 = uVar11 == 1;
    if ((bool)uVar4) {
      pcVar7[0x88] = pcVar7[0x28];
      if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
        _OUTLINED_FUNCTION_28();
        if (!(bool)uVar4) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_26();
      }
      _OUTLINED_FUNCTION_61();
      iVar6 = _os_log_type_enabled();
      if (iVar6 != 0) {
        _OUTLINED_FUNCTION_12(pcVar7[0x88],DAT_1001b3108);
        _OUTLINED_FUNCTION_6();
        auVar12 = _OUTLINED_FUNCTION_14();
        __os_log_impl(auVar12._0_8_,auVar12._8_8_,1);
      }
      __continueElapsedTimeTimer(pcVar7);
    }
  }
  *(uint *)(pcVar7 + 0x18) = local_64;
  *(int *)(pcVar7 + 0x24) = local_68;
LAB_100146a98:
  uVar9 = _OUTLINED_FUNCTION_13();
  uVar10 = _malloc_type_malloc(0xffff,0x2951793c);
  _iAP2MsgInit(uVar9,0x5001,uVar10,0xffff,__playbackAttributesUpdateSentCB,0);
  _OUTLINED_FUNCTION_61();
  uVar10 = _iAP2MsgAddGroupParam();
  local_64 = local_64 & 0xffffff00;
  iVar6 = __addplaybackAttributesToMessage(uVar9,uVar10,pcVar7,param_2,&local_64,0);
  if (iVar6 == 0) {
    if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
      _OUTLINED_FUNCTION_28();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    _OUTLINED_FUNCTION_88();
    iVar6 = _os_log_type_enabled();
    if (iVar6 != 0) {
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_6();
      __os_log_impl();
    }
    _OUTLINED_FUNCTION_61();
    _iAP2MsgCleanup();
  }
  else {
    iVar6 = _iap2_sessionControl_sendOutgoingMessage(param_1,uVar9);
    if ((iVar6 != 0) && ((local_64 & 1) != 0)) {
      uVar9 = _systemInfo_getCurrentUnixTimeMS();
      *(undefined8 *)(pcVar7 + 0x30) = uVar9;
    }
  }
  uVar11 = (uint)(byte)pcVar7[0x53];
  cVar1 = SBORROW4(uVar11,1);
  cVar2 = (int)(uVar11 - 1) < 0;
  uVar4 = uVar11 == 1;
  if ((bool)uVar4) {
    if ((*(long *)(unaff_x26 + 0xa28) == 0) || (_OUTLINED_FUNCTION_31(), cVar2 != cVar1)) {
      _OUTLINED_FUNCTION_28();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    iVar6 = _OUTLINED_FUNCTION_15();
    if (iVar6 != 0) {
      _OUTLINED_FUNCTION_4();
      _OUTLINED_FUNCTION_14();
      __os_log_debug_impl();
    }
    __checkMoveWindowAndRequestPBQList(0,*(undefined4 *)(pcVar7 + 0x54),param_1,pcVar7);
  }
  return 1;
}


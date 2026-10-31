/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100145934
 * original code SHA256: 5a307c633118bf6d0e2975298d0d010b41a46481c8a29913f91abc61f8f77c7c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



short __addMediaItemAttributesToMessage(long param_1,undefined8 param_2,long param_3,long param_4)

{
  ushort uVar1;
  undefined *puVar2;
  undefined *puVar3;
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  int iVar4;
  long lVar5;
  long lVar6;
  undefined *puVar7;
  long lVar8;
  undefined8 uVar9;
  size_t sVar10;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  void *pvVar11;
  short sVar12;
  undefined1 auVar13 [16];
  undefined *local_f0;
  undefined *local_e8;
  undefined *local_e0;
  undefined *local_d8;
  undefined *local_d0;
  undefined *local_c8;
  undefined *local_c0;
  undefined *local_b8;
  undefined *local_b0;
  undefined *local_a8;
  undefined *local_a0;
  undefined *local_98;
  undefined *local_90;
  undefined1 *local_88;
  undefined4 local_80;
  long local_7c;
  undefined8 local_68;
  
  sVar12 = 0;
  local_68 = *(undefined8 *)PTR____stack_chk_guard_10022bb80;
  if (((param_1 != 0) && (param_3 != 0)) && (param_4 != 0)) {
    if (*(long *)(param_3 + 8) == 0) {
      sVar12 = 0;
    }
    else {
      lVar5 = _CFArrayGetCount();
      sVar10 = lVar5 << 3;
      local_88 = (undefined1 *)&local_f0;
      lVar6 = (*(code *)PTR____chkstk_darwin_10022bdd0)();
      pvVar11 = (void *)((long)&local_f0 - (sVar10 + 0xf & 0xfffffffffffffff0));
      if (lVar6 != 0) {
        _memset(pvVar11,0xaa,sVar10);
      }
      _CFArrayGetValues(*(undefined8 *)(param_3 + 8),0,lVar5,pvVar11);
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_39(), in_NG != in_OV)) {
        in_OV = SCARRY8(_logObjectForModule_onceToken,1);
        in_NG = _logObjectForModule_onceToken + 1 < 0;
        puVar7 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
          puVar7 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar7 = *(undefined **)(extraout_x8 + 0x110);
      }
      iVar4 = _os_log_type_enabled(puVar7,2);
      if (iVar4 != 0) {
        lVar6 = _CFArrayCreateRawValuesString(*(undefined8 *)(param_3 + 8),0);
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_39(), in_NG != in_OV)) {
          in_OV = SCARRY8(_logObjectForModule_onceToken,1);
          in_NG = _logObjectForModule_onceToken + 1 < 0;
          puVar7 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
            puVar7 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar7 = *(undefined **)(extraout_x8_00 + 0x110);
        }
        iVar4 = _os_log_type_enabled(puVar7,2);
        if (iVar4 != 0) {
          local_80 = (undefined4)DAT_1001b3088;
          local_7c = lVar6;
          uVar9 = _OUTLINED_FUNCTION_6();
          _OUTLINED_FUNCTION_43(uVar9,puVar7);
          __os_log_debug_impl();
        }
        if (lVar6 != 0) {
          _CFRelease(lVar6);
        }
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_39(), in_NG != in_OV)) {
          if (_logObjectForModule_onceToken != -1) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
          }
          _OUTLINED_FUNCTION_11();
        }
        else {
          lVar6 = *(long *)(extraout_x8_01 + 0x110);
        }
        iVar4 = _os_log_type_enabled(lVar6,2);
        if (iVar4 != 0) {
          local_80 = (undefined4)DAT_1001b3088;
          local_7c = param_4;
          uVar9 = _OUTLINED_FUNCTION_6();
          _OUTLINED_FUNCTION_43(uVar9,lVar6);
          __os_log_debug_impl();
        }
      }
      puVar3 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_PlaybackDurationMS;
      puVar2 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_Title;
      puVar7 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_PersistentID;
      in_ZR = lVar5 == 1;
      if (lVar5 < 1) {
        sVar12 = 0;
      }
      else {
        lVar6 = 0;
        sVar12 = 0;
        local_90 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_ChapterCount;
        local_98 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_IsBanned;
        local_a0 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_IsLiked;
        local_a8 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_IsBanSupported;
        local_b0 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_IsLikeSupported;
        local_b8 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_Composer;
        local_c0 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_Genre;
        local_c8 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_Artist;
        local_d0 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumDiscCount;
        local_d8 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumDiscNum;
        local_e0 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumTrackCount;
        local_e8 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumTrackNum;
        local_f0 = _kCFACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumTitle;
        do {
          uVar1 = *(ushort *)((long)pvVar11 + lVar6 * 8);
          if (0x1b < uVar1) goto switchD_100145bf4_caseD_2;
          switch(uVar1) {
          default:
            _CFDictionaryGetValue(param_4,puVar7);
            auVar13 = _OUTLINED_FUNCTION_6();
            lVar8 = _iAP2MsgAddCFU64Param(auVar13._0_8_,auVar13._8_8_,0);
            goto LAB_100145d88;
          case 1:
            _CFDictionaryGetValue(param_4,puVar2);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 1;
            break;
          case 2:
          case 3:
          case 5:
          case 0xb:
          case 0xd:
          case 0xe:
          case 0xf:
          case 0x11:
          case 0x13:
          case 0x14:
          case 0x19:
          case 0x1a:
            goto switchD_100145bf4_caseD_2;
          case 4:
            _CFDictionaryGetValue(param_4,puVar3);
            auVar13 = _OUTLINED_FUNCTION_6();
            lVar8 = _iAP2MsgAddCFU32Param(auVar13._0_8_,auVar13._8_8_,4);
            goto LAB_100145d88;
          case 6:
            _CFDictionaryGetValue(param_4,local_f0);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 6;
            break;
          case 7:
            _CFDictionaryGetValue(param_4,local_e8);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 7;
            goto LAB_100145d50;
          case 8:
            _CFDictionaryGetValue(param_4,local_e0);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 8;
            goto LAB_100145d50;
          case 9:
            _CFDictionaryGetValue(param_4,local_d8);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 9;
            goto LAB_100145d50;
          case 10:
            _CFDictionaryGetValue(param_4,local_d0);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 10;
            goto LAB_100145d50;
          case 0xc:
            _CFDictionaryGetValue(param_4,local_c8);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 0xc;
            break;
          case 0x10:
            _CFDictionaryGetValue(param_4,local_c0);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 0x10;
            break;
          case 0x12:
            _CFDictionaryGetValue(param_4,local_b8);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 0x12;
            break;
          case 0x15:
            _CFDictionaryGetValue(param_4,local_b0);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 0x15;
            goto LAB_100145d04;
          case 0x16:
            _CFDictionaryGetValue(param_4,local_a8);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 0x16;
            goto LAB_100145d04;
          case 0x17:
            _CFDictionaryGetValue(param_4,local_a0);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 0x17;
            goto LAB_100145d04;
          case 0x18:
            _CFDictionaryGetValue(param_4,local_98);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 0x18;
LAB_100145d04:
            lVar8 = _iAP2MsgAddCFBooleanParam(auVar13._0_8_,auVar13._8_8_,uVar9);
            goto LAB_100145d88;
          case 0x1b:
            _CFDictionaryGetValue(param_4,local_90);
            auVar13 = _OUTLINED_FUNCTION_6();
            uVar9 = 0x1b;
LAB_100145d50:
            lVar8 = _iAP2MsgAddCFU16Param(auVar13._0_8_,auVar13._8_8_,uVar9);
            goto LAB_100145d88;
          }
          lVar8 = _iAP2MsgAddCFStringParam(auVar13._0_8_,auVar13._8_8_,uVar9);
LAB_100145d88:
          if (lVar8 != 0) {
            sVar12 = sVar12 + 1;
          }
switchD_100145bf4_caseD_2:
          lVar6 = lVar6 + 1;
          lVar5 = lVar5 + -1;
        } while (lVar5 != 0);
        in_ZR = 1;
      }
    }
  }
  _OUTLINED_FUNCTION_34(local_68);
  if ((bool)in_ZR) {
    return sVar12;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008ef30
 * original code SHA256: 67102e1d2413fa3e6e1765f1d8e6a593a66c24ec4a9859b2ce81a1f369791214
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_storeStrong replaced with injection: _objc_store_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x27 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */

undefined8 _platform_nowPlaying_playbackAttributesUpdate(ID param_1)

{
  bool bVar1;
  int iVar2;
  ID IVar3;
  ID IVar4;
  undefined *puVar5;
  undefined **ppuVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  byte bVar9;
  uint local_80;
  undefined8 local_7c;
  undefined2 local_74;
  char *local_72;
  undefined2 local_6a;
  char *local_68;
  
  bVar9 = __gShouldSendMediaLibraryUID;
  IVar3 = objc_stub::objectForKeyedSubscript_
                    (param_1,_kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_AppBundleID);
  if ((IVar3 != 0) &&
     ((_platform_nowPlaying_playbackAttributesUpdate_appBundleID == 0 ||
      (IVar4 = objc_stub::isEqualToString_
                         (_platform_nowPlaying_playbackAttributesUpdate_appBundleID,IVar3),
      (IVar4 & 1) == 0)))) {
    bVar9 = 1;
    _platform_nowPlaying_playbackAttributesUpdate_appBundleID = IVar3;
  }
  IVar3 = objc_stub::objectForKeyedSubscript_
                    (param_1,_kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_IsMusicApp);
  if ((IVar3 != 0) &&
     ((_platform_nowPlaying_playbackAttributesUpdate_isMusicAppNS == 0 ||
      (IVar4 = objc_stub::isEqualToNumber_
                         (_platform_nowPlaying_playbackAttributesUpdate_isMusicAppNS,IVar3),
      (IVar4 & 1) == 0)))) {
    bVar9 = 1;
    _platform_nowPlaying_playbackAttributesUpdate_isMusicAppNS = IVar3;
  }
  puVar5 = (undefined *)
           objc_stub::objectForKeyedSubscript_
                     (param_1,
                      _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_iTunesRadioStationIdentifier
                     );
  ppuVar6 = (undefined **)0x0;
  if ((puVar5 == (undefined *)0x0) ||
     ((_platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier !=
       (undefined *)0x0 &&
      (ppuVar6 = (undefined **)
                 objc_stub::isEqualToString_
                           ((ID)
                            _platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier
                            ,puVar5), ((ulong)ppuVar6 & 1) != 0)))) {
joined_r0x00010008f030:
    if (bVar9 == 0) goto LAB_10008f284;
  }
  else {
    IVar3 = objc_stub::isEqualToString_
                      ((ID)
                       _platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier,
                       &cf___);
    if ((((int)IVar3 == 0) ||
        (IVar3 = objc_stub::isEqualToString_((ID)puVar5,&cf___), (int)IVar3 != 0)) &&
       ((IVar3 = objc_stub::isEqualToString_
                           ((ID)
                            _platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier
                            ,&cf___), (IVar3 & 1) != 0 ||
        (IVar3 = objc_stub::isEqualToString_((ID)puVar5,&cf___), (int)IVar3 == 0)))) {
      ppuVar6 = &_platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier;
      bVar9 = bVar9 & 1;
      _platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier = puVar5;
      goto joined_r0x00010008f030;
    }
    ppuVar6 = &_platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier;
    _platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier = puVar5;
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 8)) {
    puVar5 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      ppuVar6 = (undefined **)
                ___platform_nowPlaying_triggerMediaItemAttributesUpdate_block_invoke_cold_1();
      puVar5 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar5 = *(undefined **)(_gLogObjects + 0x38);
  }
  iVar2 = _os_log_type_enabled(puVar5,ppuVar6,1);
  if (iVar2 != 0) {
    local_80 = local_80 & 0xffff0000;
    __os_log_impl(0x100000000,ppuVar6,1,"[#Now Playing] Injecting MediaLibraryUID...",&local_80,2);
  }
  if (_platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier == (undefined *)0x0
     ) {
    bVar1 = false;
  }
  else {
    IVar3 = objc_stub::length((ID)
                              _platform_nowPlaying_playbackAttributesUpdate_iTunesRadioStationIdentifier
                             );
    bVar1 = IVar3 != 0;
  }
  if (_platform_nowPlaying_playbackAttributesUpdate_isMusicAppNS == 0) {
    IVar3 = 0;
  }
  else {
    IVar3 = objc_stub::boolValue(_platform_nowPlaying_playbackAttributesUpdate_isMusicAppNS);
  }
  IVar4 = NSMutableDictionary::dictionaryWithDictionary_
                    ((ID)PTR__OBJC_CLASS___NSMutableDictionary_10022bc70,param_1);
  uVar7 = _platform_system_copyMediaLibraryUIDString(IVar3,bVar1);
  uVar8 = uVar7;
  if ((_gLogObjects == 0) || (_gNumLogObjects < 8)) {
    puVar5 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      uVar8 = _platform_nowPlaying_playbackAttributesUpdate_cold_2();
      puVar5 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar5 = *(undefined **)(_gLogObjects + 0x38);
  }
  iVar2 = _os_log_type_enabled(puVar5,uVar8,1);
  if (iVar2 != 0) {
    local_72 = "YES";
    if ((int)IVar3 == 0) {
      local_72 = "NO";
    }
    local_80 = (uint)DAT_1001b30f8;
    local_74 = 0x820;
    local_68 = "YES";
    if (bVar1 == false) {
      local_68 = "NO";
    }
    local_6a = 0x820;
    local_7c = uVar7;
    __os_log_impl(0x100000000,uVar8,1,
                  "[#Now Playing] mediaLibraryUID: \'%@\'; isMusicApp: %s; isiTunesRadio: %s",
                  &local_80,0x20);
  }
  NSMutableDictionary::setObject_forKey_
            (IVar4,uVar7,_kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_MediaLibraryUID);
  param_1 = NSMutableDictionary::copy(IVar4);
  __gShouldSendMediaLibraryUID = 0;
LAB_10008f284:
  uVar8 = _accFeatureHandlers_invokeHandler(0,0xca,param_1);
  return uVar8;
}


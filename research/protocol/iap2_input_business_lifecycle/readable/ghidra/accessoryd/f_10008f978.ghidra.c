/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008f978
 * original code SHA256: bd1b36b898f72f91806c1150bb255f953af83fe855582e61a1ec2110adc2c547
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

void _platform_nowPlaying_copyDefaultPlaybackAttributes(void)

{
  ID IVar1;
  undefined *local_118;
  undefined *puStack_110;
  undefined *local_108;
  undefined *puStack_100;
  undefined *local_f8;
  undefined *puStack_f0;
  undefined *local_e8;
  undefined *puStack_e0;
  undefined *local_d8;
  undefined *puStack_d0;
  undefined *local_c8;
  undefined *puStack_c0;
  undefined *local_b8;
  undefined *puStack_b0;
  undefined *local_a8;
  undefined **local_a0;
  undefined **ppuStack_98;
  undefined **local_90;
  undefined **ppuStack_88;
  undefined **local_80;
  undefined **ppuStack_78;
  undefined **local_70;
  cfstringStruct *pcStack_68;
  cfstringStruct *local_60;
  undefined *puStack_58;
  cfstringStruct *local_50;
  undefined **ppuStack_48;
  undefined **local_40;
  undefined *puStack_38;
  cfstringStruct *local_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_10022bb80;
  local_118 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_Status;
  puStack_110 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_ElapsedTimeMS;
  local_a0 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a180;
  ppuStack_98 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  local_108 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_QueueIndex;
  puStack_100 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_QueueCount;
  local_90 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  ppuStack_88 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  local_f8 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_QueueChapterIndex;
  puStack_f0 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_ShuffleMode;
  local_80 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  ppuStack_78 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a180;
  local_e8 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_RepeatMode;
  puStack_e0 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_AppName;
  local_70 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a180;
  pcStack_68 = &cf___;
  local_d8 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_MediaLibraryUID;
  puStack_d0 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_iTunesRadioAd;
  local_60 = &cf___;
  puStack_58 = PTR____kCFBooleanFalse_10022bcd0;
  local_c8 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_iTunesRadioStation;
  puStack_c0 = 
  _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_iTunesRadioStationMediaPlaylistPersistentID;
  local_50 = &cf___;
  ppuStack_48 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  local_b8 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_PlaybackSpeed;
  puStack_b0 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_SetTimeElapsedAvailable;
  local_40 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  puStack_38 = PTR____kCFBooleanFalse_10022bcd0;
  local_a8 = _kACCNowPlaying_NowPlayingUpdate_PlaybackAttributes_AppBundleID;
  local_30 = &cf___;
  IVar1 = NSDictionary::dictionaryWithObjects_forKeys_count_
                    ((ID)PTR__OBJC_CLASS___NSDictionary_10022bc48,&local_a0,&local_118,0xf);
  if (*(long *)PTR____stack_chk_guard_10022bb80 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(IVar1);
}


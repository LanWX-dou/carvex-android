/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008f588
 * original code SHA256: a8fab2e63be3a56c63c3a843848fc4c934f27c66386a1f91b261fa238678a0ee
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */

void _platform_nowPlaying_copyDefaultMediaItemAttributes(void)

{
  ID IVar1;
  undefined *local_128;
  undefined *puStack_120;
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
  undefined **local_a8;
  cfstringStruct *pcStack_a0;
  undefined **local_98;
  cfstringStruct *pcStack_90;
  undefined **local_88;
  undefined **ppuStack_80;
  undefined **local_78;
  undefined **ppuStack_70;
  cfstringStruct *local_68;
  cfstringStruct *pcStack_60;
  cfstringStruct *local_58;
  undefined *puStack_50;
  undefined *local_48;
  undefined *puStack_40;
  undefined *local_38;
  undefined **ppuStack_30;
  long local_28;
  
  local_28 = *(long *)PTR____stack_chk_guard_10022bb80;
  local_128 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_PersistentID;
  puStack_120 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_Title;
  local_a8 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  pcStack_a0 = &cf___;
  local_118 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_PlaybackDurationMS;
  puStack_110 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumTitle;
  local_98 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  pcStack_90 = &cf___;
  local_108 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumTrackNum;
  puStack_100 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumTrackCount;
  local_88 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  ppuStack_80 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  local_f8 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumDiscNum;
  puStack_f0 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_AlbumDiscCount;
  local_78 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  ppuStack_70 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  local_e8 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_Artist;
  puStack_e0 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_Genre;
  local_68 = &cf___;
  pcStack_60 = &cf___;
  local_d8 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_Composer;
  puStack_d0 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_IsLikeSupported;
  local_58 = &cf___;
  puStack_50 = PTR____kCFBooleanFalse_10022bcd0;
  local_c8 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_IsBanSupported;
  puStack_c0 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_IsLiked;
  local_48 = PTR____kCFBooleanFalse_10022bcd0;
  puStack_40 = PTR____kCFBooleanFalse_10022bcd0;
  local_b8 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_IsBanned;
  puStack_b0 = _kACCNowPlaying_NowPlayingUpdate_MediaItemAttributes_ChapterCount;
  local_38 = PTR____kCFBooleanFalse_10022bcd0;
  ppuStack_30 = &PTR__OBJC_CLASS___NSConstantIntegerNumber_10022a168;
  IVar1 = NSDictionary::dictionaryWithObjects_forKeys_count_
                    ((ID)PTR__OBJC_CLASS___NSDictionary_10022bc48,&local_a8,&local_128,0x10);
  if (*(long *)PTR____stack_chk_guard_10022bb80 == local_28) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(IVar1);
}


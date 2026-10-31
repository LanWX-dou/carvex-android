/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001474b4
 * original code SHA256: 353f4a104c3feefb5bbcd4b45e9d6756bd157deea95e5590f43160dfb69816d7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_nowPlaying_playbackQueueListChangedHandler(long *param_1,undefined8 param_2)

{
  char in_NG;
  char cVar1;
  undefined1 in_ZR;
  undefined1 uVar2;
  char in_OV;
  char cVar3;
  int iVar4;
  char *pcVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  long extraout_x8;
  long extraout_x8_00;
  undefined8 unaff_x20;
  long unaff_x23;
  undefined1 auVar8 [16];
  undefined1 local_41;
  
  if (param_1 != (long *)0x0) {
    local_41 = 0xaa;
    _CFNumberGetValue(param_2,7,&local_41);
    if (*param_1 != 0) {
      _OUTLINED_FUNCTION_87();
      if ((extraout_x8 == 0) || (_OUTLINED_FUNCTION_70(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_51();
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      else {
        unaff_x20 = *(undefined8 *)(extraout_x8_00 + 0x110);
      }
      iVar4 = _os_log_type_enabled(unaff_x20,0);
      if (iVar4 != 0) {
        _OUTLINED_FUNCTION_1(param_1[1]);
        _OUTLINED_FUNCTION_6();
        auVar8 = _OUTLINED_FUNCTION_44();
        __os_log_impl(auVar8._0_8_,auVar8._8_8_,0);
      }
      _OUTLINED_FUNCTION_54();
      pcVar5 = (char *)_iap2_feature_getFeature();
      if (pcVar5 == (char *)0x0) {
        return 0;
      }
      if (*pcVar5 == '\x01') {
        if (((pcVar5[0x50] & 1U) == 0) && (pcVar5[0x51] != '\x01')) {
          return 1;
        }
        uVar2 = 1;
        cVar3 = '\0';
        cVar1 = '\0';
        if ((*(long *)(unaff_x23 + 0xa28) == 0) || (_OUTLINED_FUNCTION_70(), cVar1 != cVar3)) {
          _OUTLINED_FUNCTION_51();
          if (!(bool)uVar2) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
          }
          _OUTLINED_FUNCTION_15();
        }
        iVar4 = _OUTLINED_FUNCTION_15();
        if (iVar4 != 0) {
          _OUTLINED_FUNCTION_11(local_41,DAT_1001b30b0);
          _OUTLINED_FUNCTION_14();
          __os_log_debug_impl();
        }
        __checkMoveWindowAndRequestPBQList(local_41,*(undefined4 *)(pcVar5 + 0x54),param_1,pcVar5);
        uVar6 = _OUTLINED_FUNCTION_13();
        auVar8 = _malloc_type_malloc(0xffff,0xe4f5d8b8);
        _OUTLINED_FUNCTION_48(auVar8._0_8_,auVar8._8_8_,auVar8._0_8_);
        _iAP2MsgInit();
        _OUTLINED_FUNCTION_13();
        uVar7 = _iAP2MsgAddGroupParam();
        _iAP2MsgAddU8Param(uVar6,uVar7,0xe,0);
        _iap2_sessionControl_sendOutgoingMessageAndCallbackOnACK(param_1,uVar6);
        return 1;
      }
    }
  }
  return 0;
}


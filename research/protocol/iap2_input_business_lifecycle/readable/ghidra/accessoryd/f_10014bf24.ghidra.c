/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10014bf24
 * original code SHA256: 36b3d40d53804237e7eebba4721e45318f5a2b1f9f8f87040d03962fc12eb0b2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_assistiveTouch_notifyStatusUpdateHandler(long param_1,undefined8 param_2)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 unaff_x21;
  undefined8 uVar4;
  undefined4 local_80;
  undefined8 local_7c;
  undefined2 local_74;
  undefined4 local_72;
  undefined1 local_51;
  
  uVar4 = 0;
  if (param_1 != 0) {
    local_51 = 0xaa;
    _CFNumberGetValue(param_2,7,&local_51);
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x26)) {
      if (_logObjectForModule_onceToken != -1) {
        _OUTLINED_FUNCTION_3();
      }
      _OUTLINED_FUNCTION_27();
    }
    iVar1 = _OUTLINED_FUNCTION_31();
    if (iVar1 != 0) {
      _OUTLINED_FUNCTION_1(*(undefined8 *)(param_1 + 8),DAT_1001b30f0);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_4();
      __os_log_impl();
    }
    lVar2 = _OUTLINED_FUNCTION_14();
    uVar4 = 0;
    if (lVar2 != 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x26)) {
        if (_logObjectForModule_onceToken != -1) {
          _OUTLINED_FUNCTION_3();
        }
        _OUTLINED_FUNCTION_15();
      }
      else {
        unaff_x21 = *(undefined8 *)(_gLogObjects + 0x128);
      }
      iVar1 = _OUTLINED_FUNCTION_15();
      if (iVar1 != 0) {
        _OUTLINED_FUNCTION_1(*(undefined8 *)(param_1 + 8),DAT_1001b3130);
        _OUTLINED_FUNCTION_0();
        _OUTLINED_FUNCTION_7();
      }
      if (*(char *)(lVar2 + 1) == '\x01') {
        uVar3 = _iAP2MsgInit(param_1 + 0x80,0x5403,*(undefined8 *)(param_1 + 200),0xffff,0,0);
        lVar2 = _iAP2MsgAddU8Param(uVar3,0,0,local_51);
        uVar4 = 0;
        if (lVar2 != 0) {
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x26)) {
            if (_logObjectForModule_onceToken != -1) {
              _OUTLINED_FUNCTION_3();
            }
            _OUTLINED_FUNCTION_15();
          }
          else {
            unaff_x21 = *(undefined8 *)(_gLogObjects + 0x128);
          }
          iVar1 = _os_log_type_enabled(unaff_x21,1);
          if (iVar1 != 0) {
            uVar4 = *(undefined8 *)(param_1 + 8);
            local_72 = _iAP2MsgGetMsgID(uVar3);
            local_80 = (undefined4)DAT_1001b30f0;
            local_74 = 0x400;
            local_7c = uVar4;
            uVar4 = _OUTLINED_FUNCTION_6();
            __os_log_impl(uVar4,unaff_x21,1,
                          "iAP2AssistiveTouch notifyStatusUpdate: %@ send message %xh",&local_80,
                          0x12);
          }
          _iap2_sessionControl_sendOutgoingMessage(param_1,uVar3);
          uVar4 = 1;
        }
      }
      else {
        uVar4 = 0;
      }
    }
  }
  return uVar4;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001313dc
 * original code SHA256: 2c282e46f206c10519f6f7ca333080dcccf89319a83b326b97a4719ad3e177de
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_hid_StopHIDMsgHandler(long param_1,long param_2)

{
  undefined *puVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 *extraout_x8;
  uint uVar9;
  ushort uVar10;
  undefined *puVar11;
  undefined1 auVar12 [16];
  undefined4 local_90;
  int local_8c;
  undefined2 local_88;
  undefined4 local_86;
  uint local_78;
  ushort local_66;
  int local_64;
  
  local_64 = 0;
  local_66 = 0;
  if ((param_1 != 0) && (param_2 != 0)) {
    iVar3 = _iAP2MsgGetMsgID(param_2);
    uVar2 = iVar3 == 0x6803;
    if ((bool)uVar2) {
      _OUTLINED_FUNCTION_12();
      lVar5 = _iAP2MsgGetFirstParam();
      puVar1 = PTR___os_log_default_10022bbb0;
      uVar7 = DAT_1001b30b0;
      uVar9 = 0;
      if (lVar5 != 0) {
        uVar10 = 0;
        do {
          iVar3 = _iAP2MsgGetParamID(lVar5);
          if (iVar3 == 0) {
            local_66 = _iAP2MsgGetDataAsU16(lVar5,&local_64);
            uVar10 = local_66;
            if (local_64 != 0) {
              uVar7 = _logObjectForModule();
              iVar3 = _os_log_type_enabled(uVar7,0x10);
              if (iVar3 == 0) {
                return 0;
              }
              local_86 = _iAP2MsgGetMsgID(param_2);
              local_90 = (undefined4)DAT_1001b3108;
              local_8c = 0;
              local_88 = 0x400;
              uVar8 = _OUTLINED_FUNCTION_6();
              auVar12 = _OUTLINED_FUNCTION_26(uVar8,uVar7);
              goto LAB_100131680;
            }
          }
          else {
            if ((_gLogObjects == 0) || (uVar2 = _gNumLogObjects == 0x24, _gNumLogObjects < 0x24)) {
              _OUTLINED_FUNCTION_7();
              puVar11 = puVar1;
              if (!(bool)uVar2) {
                _OUTLINED_FUNCTION_5();
                _dispatch_once();
              }
            }
            else {
              puVar11 = *(undefined **)(_gLogObjects + 0x118);
            }
            iVar4 = _os_log_type_enabled(puVar11,1);
            if (iVar4 != 0) {
              local_90 = (undefined4)uVar7;
              local_8c = iVar3;
              __os_log_impl(0x100000000,puVar11,1,"Unrecognized paramID:0x%04X",&local_90,8);
            }
          }
          auVar12 = _OUTLINED_FUNCTION_12();
          lVar5 = _iAP2MsgGetNextParam(auVar12._0_8_,auVar12._8_8_,lVar5);
        } while (lVar5 != 0);
        uVar9 = (uint)uVar10;
      }
      if ((_gLogObjects == 0) || (uVar2 = _gNumLogObjects == 0x24, _gNumLogObjects < 0x24)) {
        _OUTLINED_FUNCTION_7();
        if (!(bool)uVar2) {
          _OUTLINED_FUNCTION_5();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      else {
        param_2 = *(long *)(_gLogObjects + 0x118);
      }
      iVar3 = _os_log_type_enabled(param_2,0);
      if (iVar3 != 0) {
        _OUTLINED_FUNCTION_27();
        _OUTLINED_FUNCTION_13(DAT_1001b30f8);
        local_78 = uVar9;
        _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_23();
      }
      lVar5 = _iap2_feature_getFeature(param_1,0xb);
      if (lVar5 != 0) {
        _OUTLINED_FUNCTION_39();
        lVar6 = _CFNumberCreate(*extraout_x8,2,&local_66);
        if (*(long *)(lVar5 + 8) == 0) {
          lVar5 = 0;
        }
        else {
          lVar5 = _CFDictionaryGetValue(*(long *)(lVar5 + 8),lVar6);
        }
        if (lVar6 != 0) {
          _CFRelease(lVar6);
        }
        if (lVar5 == 0) {
          if ((_gLogObjects == 0) || (uVar2 = _gNumLogObjects == 0x24, _gNumLogObjects < 0x24)) {
            _OUTLINED_FUNCTION_7();
            if (!(bool)uVar2) {
              _OUTLINED_FUNCTION_5();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_27();
          }
          else {
            lVar6 = *(long *)(_gLogObjects + 0x118);
          }
          iVar3 = _os_log_type_enabled(lVar6,0x10);
          if (iVar3 != 0) {
            _OUTLINED_FUNCTION_27();
            _OUTLINED_FUNCTION_13(DAT_1001b30f8);
            uVar7 = _OUTLINED_FUNCTION_6();
            auVar12._8_8_ = lVar6;
            auVar12._0_8_ = uVar7;
LAB_100131680:
            __os_log_error_impl(auVar12._0_8_,auVar12._8_8_);
          }
        }
        else {
          *(undefined1 *)(lVar5 + 0x18) = 0;
          *(undefined1 *)(lVar5 + 0x1a) = 0;
        }
      }
    }
  }
  return 0;
}


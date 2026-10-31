/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100175c70
 * original code SHA256: 0f535a06d3ad642f64dc7ab02b6733be6d4c6f3510bd1af627380d692645b6c2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined4 _iap2_navigation_roadObjectDetectionUpdateHandler(long param_1,long param_2)

{
  int iVar1;
  undefined4 uVar2;
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  int iVar3;
  uint uVar4;
  long lVar5;
  ulong uVar6;
  undefined8 uVar7;
  long lVar8;
  undefined8 uVar9;
  long extraout_x8;
  long lVar10;
  undefined4 uVar11;
  undefined1 auVar12 [16];
  undefined1 auStack_c0 [4];
  uint local_bc;
  undefined2 local_b8;
  undefined4 local_b6;
  undefined8 local_b2;
  long local_a8;
  int local_94;
  undefined8 local_90;
  undefined8 local_88;
  
  local_88 = *(undefined8 *)PTR____stack_chk_guard_10022bb80;
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
    _OUTLINED_FUNCTION_34();
    if (!(bool)in_ZR) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_27();
  }
  _OUTLINED_FUNCTION_15();
  iVar3 = _os_log_type_enabled();
  if (iVar3 != 0) {
    if (param_1 == 0) {
      uVar9 = 0;
    }
    else {
      uVar9 = *(undefined8 *)(param_1 + 8);
    }
    _OUTLINED_FUNCTION_11(uVar9,DAT_1001b3088);
    _OUTLINED_FUNCTION_44();
    __os_log_impl();
  }
  uVar11 = 0;
  if ((param_1 == 0) || (param_2 == 0)) {
LAB_100176128:
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
      _OUTLINED_FUNCTION_34();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_8();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    _OUTLINED_FUNCTION_15();
    iVar3 = _os_log_type_enabled();
    if (iVar3 != 0) {
      if (param_1 == 0) {
        uVar9 = 0;
      }
      else {
        uVar9 = *(undefined8 *)(param_1 + 8);
      }
      _OUTLINED_FUNCTION_26(uVar9,DAT_1001b30f0);
      _OUTLINED_FUNCTION_77();
      local_b2 = CONCAT44(local_b2._4_4_,uVar11);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_44();
      __os_log_impl();
    }
    _OUTLINED_FUNCTION_34(local_88);
    if (!(bool)in_ZR) {
                    /* WARNING: Subroutine does not return */
      ___stack_chk_fail();
    }
    return uVar11;
  }
  _OUTLINED_FUNCTION_17();
  lVar5 = _iAP2MsgGetFirstParam();
  uVar9 = DAT_1001b30f0;
  local_94 = 0;
  if (lVar5 == 0) {
    lVar10 = 0;
LAB_100176020:
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
      _OUTLINED_FUNCTION_34();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_8();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    else {
      param_2 = *(long *)(extraout_x8 + 0x188);
    }
    iVar3 = _os_log_type_enabled(param_2,2);
    if (iVar3 != 0) {
      uVar9 = _OUTLINED_FUNCTION_11(*(undefined8 *)(param_1 + 8),DAT_1001b3088);
      __os_log_debug_impl(uVar9,param_2,2,"iAP2Navigation RoadObjectDetectionUpdate: %@",auStack_c0,
                          0xc);
    }
    lVar5 = _OUTLINED_FUNCTION_94();
    if (((lVar5 == 0) || (iVar3 = _OUTLINED_FUNCTION_66(), iVar3 == 0)) || (lVar10 == 0)) {
LAB_100176308:
      uVar11 = 0;
      uVar2 = 0;
      if (lVar10 == 0) goto LAB_100176128;
    }
    else {
      _OUTLINED_FUNCTION_71();
      uVar9 = _platform_navigation_objectDetectionInfoGetItem();
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) {
        _OUTLINED_FUNCTION_34();
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_8();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_26();
      }
      iVar3 = _OUTLINED_FUNCTION_36();
      if (iVar3 != 0) {
        _OUTLINED_FUNCTION_18(*(undefined8 *)(param_1 + 8),DAT_1001b30f8);
        local_b2 = uVar9;
        local_a8 = lVar10;
        _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_27();
        __os_log_impl();
      }
      _platform_navigation_objectDetectionUpdateInfo(*(undefined8 *)(param_1 + 8),0,lVar10);
      uVar2 = 1;
    }
    uVar11 = uVar2;
    _CFRelease(lVar10);
    goto LAB_100176128;
  }
  lVar10 = 0;
LAB_100175d68:
  uVar4 = _iAP2MsgGetParamID(lVar5);
  if (((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) &&
     (_OUTLINED_FUNCTION_34(), !(bool)in_ZR)) {
    _OUTLINED_FUNCTION_8();
    _dispatch_once();
  }
  uVar6 = _OUTLINED_FUNCTION_73();
  if ((uVar6 & 1) != 0) {
    _OUTLINED_FUNCTION_26(*(undefined8 *)(param_1 + 8),uVar9);
    _OUTLINED_FUNCTION_77();
    local_b2 = CONCAT44(local_b2._4_4_,uVar4);
    _OUTLINED_FUNCTION_12();
    __os_log_debug_impl();
  }
  in_OV = SBORROW4(uVar4,6);
  in_NG = (int)(uVar4 - 6) < 0;
  in_ZR = uVar4 == 6;
  if (6 < uVar4) {
    if (((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), in_NG != in_OV)) &&
       (_OUTLINED_FUNCTION_34(), !(bool)in_ZR)) {
      _OUTLINED_FUNCTION_8();
      _dispatch_once();
    }
    iVar3 = _OUTLINED_FUNCTION_73();
    if (iVar3 != 0) {
      _iAP2MsgGetMsgID(param_2);
      local_b6 = _OUTLINED_FUNCTION_32();
      local_b8 = 0x400;
      local_bc = uVar4;
      _OUTLINED_FUNCTION_12();
      __os_log_debug_impl();
    }
    goto LAB_100175f5c;
  }
  uVar6 = (ulong)uVar4;
  in_OV = SBORROW8(uVar6,6);
  in_NG = (long)(uVar6 - 6) < 0;
  in_ZR = uVar6 == 6;
  switch(uVar6) {
  default:
    _OUTLINED_FUNCTION_80();
    uVar7 = _iAP2MsgGetDataAsU16();
    if (local_94 != 0) {
      _logObjectForModule();
      iVar3 = _OUTLINED_FUNCTION_20();
      if (iVar3 != 0) {
        _iAP2MsgGetMsgID(param_2);
        _OUTLINED_FUNCTION_32();
        local_bc = 0;
        _OUTLINED_FUNCTION_7();
        goto LAB_1001762fc;
      }
      goto LAB_100176308;
    }
    if (lVar10 == 0) {
      lVar10 = _platform_navigation_createObjectDetectionInfoDict();
    }
    _platform_navigation_objectDetectionInfoAddComponentID(lVar10,uVar7);
    break;
  case 1:
    _OUTLINED_FUNCTION_80();
    _iAP2MsgGetDataAsU64();
    if (local_94 != 0) {
      _logObjectForModule();
      iVar3 = _OUTLINED_FUNCTION_20();
      if (iVar3 != 0) {
        _iAP2MsgGetMsgID(param_2);
        _OUTLINED_FUNCTION_32();
        local_bc = 1;
        _OUTLINED_FUNCTION_7();
        _OUTLINED_FUNCTION_45();
        _OUTLINED_FUNCTION_96();
      }
      goto LAB_100176308;
    }
    _OUTLINED_FUNCTION_15();
    lVar8 = _platform_navigation_objectDetectionInfoGetItem();
    if (lVar8 != 0) goto LAB_100176308;
    if (lVar10 == 0) {
      lVar10 = _platform_navigation_createObjectDetectionInfoDict();
    }
    _OUTLINED_FUNCTION_30();
    _platform_navigation_objectDetectionInfoSetTimestamp();
    break;
  case 2:
    _OUTLINED_FUNCTION_80();
    uVar7 = _iAP2MsgGetDataAsI32();
    if (local_94 != 0) {
      uVar9 = _logObjectForModule();
      iVar3 = _os_log_type_enabled(uVar9,2);
      if (iVar3 != 0) {
        _iAP2MsgGetMsgID(param_2);
        _OUTLINED_FUNCTION_32();
        local_bc = 2;
        _OUTLINED_FUNCTION_7();
        goto LAB_1001762fc;
      }
      goto LAB_100176308;
    }
    _OUTLINED_FUNCTION_20();
    lVar8 = _platform_navigation_objectDetectionInfoGetItem();
    if (lVar8 != 0) goto LAB_100176308;
    if (lVar10 == 0) {
      lVar10 = _platform_navigation_createObjectDetectionInfoDict();
    }
    _platform_navigation_objectDetectionInfoSetEgoSpeed(lVar10,uVar7);
    break;
  case 3:
    local_90 = &DAT_aaaaaaaaaaaaaaaa;
    iVar3 = _iAP2MsgGetDataAsArrayI32(lVar5,&local_94,&local_90,2);
    if (local_94 == 0) {
      in_OV = SBORROW4(iVar3,2);
      in_NG = iVar3 + -2 < 0;
      in_ZR = iVar3 == 2;
      if ((bool)in_ZR) {
        lVar8 = _platform_navigation_objectDetectionInfoGetItem(lVar10,3);
        if (lVar8 == 0) {
          iVar3 = (int)local_90;
          iVar1 = local_90._4_4_;
          if (lVar10 == 0) {
            lVar10 = _platform_navigation_createObjectDetectionInfoDict();
          }
          _platform_navigation_objectDetectionInfoSetEgoYawRate((float)iVar3 / (float)iVar1,lVar10);
          break;
        }
      }
      else {
        _logObjectForModule();
        iVar3 = _OUTLINED_FUNCTION_20();
        if (iVar3 != 0) {
          _iAP2MsgGetMsgID(param_2);
          _OUTLINED_FUNCTION_32();
          local_bc = 3;
          _OUTLINED_FUNCTION_7();
          goto LAB_1001762fc;
        }
      }
      goto LAB_100176308;
    }
    _logObjectForModule();
    iVar3 = _OUTLINED_FUNCTION_20();
    if (iVar3 == 0) goto LAB_100176308;
    _iAP2MsgGetMsgID(param_2);
    _OUTLINED_FUNCTION_32();
    local_bc = 3;
    _OUTLINED_FUNCTION_7();
    goto LAB_1001762fc;
  case 4:
    _OUTLINED_FUNCTION_43();
    uVar7 = __parseRoadSignParameter();
    if (local_94 != 0) {
      _CFRelease(uVar7);
      _logObjectForModule();
      iVar3 = _OUTLINED_FUNCTION_20();
      if (iVar3 != 0) {
        _iAP2MsgGetMsgID(param_2);
        _OUTLINED_FUNCTION_32();
        local_bc = 4;
        _OUTLINED_FUNCTION_7();
        goto LAB_1001762fc;
      }
      goto LAB_100176308;
    }
    if (lVar10 == 0) {
      lVar10 = _platform_navigation_createObjectDetectionInfoDict();
    }
    _OUTLINED_FUNCTION_30();
    _platform_navigation_objectDetectionInfoAddRoadSign();
LAB_100175e50:
    _CFRelease(uVar7);
    break;
  case 5:
    _OUTLINED_FUNCTION_43();
    uVar7 = __parseRoadLaneParameter();
    if (local_94 == 0) {
      if (lVar10 == 0) {
        lVar10 = _platform_navigation_createObjectDetectionInfoDict();
      }
      _OUTLINED_FUNCTION_30();
      _platform_navigation_objectDetectionInfoAddRoadLane();
      goto LAB_100175e50;
    }
    _CFRelease(uVar7);
    _logObjectForModule();
    iVar3 = _OUTLINED_FUNCTION_20();
    if (iVar3 != 0) {
      _iAP2MsgGetMsgID(param_2);
      _OUTLINED_FUNCTION_32();
      local_bc = 5;
      _OUTLINED_FUNCTION_7();
      goto LAB_1001762fc;
    }
    goto LAB_100176308;
  case 6:
    _OUTLINED_FUNCTION_43();
    uVar7 = __parseRoadObjectParameter();
    if (local_94 == 0) {
      if (lVar10 == 0) {
        lVar10 = _platform_navigation_createObjectDetectionInfoDict();
      }
      _OUTLINED_FUNCTION_30();
      _platform_navigation_objectDetectionInfoAddRoadObject();
      goto LAB_100175e50;
    }
    _CFRelease(uVar7);
    _logObjectForModule();
    iVar3 = _OUTLINED_FUNCTION_20();
    if (iVar3 == 0) goto LAB_100176308;
    _iAP2MsgGetMsgID(param_2);
    _OUTLINED_FUNCTION_32();
    local_bc = 6;
    _OUTLINED_FUNCTION_7();
LAB_1001762fc:
    _OUTLINED_FUNCTION_45();
    _OUTLINED_FUNCTION_96();
    goto LAB_100176308;
  }
LAB_100175f5c:
  auVar12 = _OUTLINED_FUNCTION_17();
  lVar5 = _iAP2MsgGetNextParam(auVar12._0_8_,auVar12._8_8_,lVar5);
  if (lVar5 == 0) goto LAB_100176020;
  goto LAB_100175d68;
}


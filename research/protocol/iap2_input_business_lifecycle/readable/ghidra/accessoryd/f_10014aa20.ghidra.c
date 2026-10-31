/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10014aa20
 * original code SHA256: 8c933d2247f465ef2cce6a055aa7ef249bbb97a193c90c1d4399b9add9d0db02
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool __setNowPlayingInfoHandler(long param_1,long param_2)

{
  char in_NG;
  char in_OV;
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  long lVar8;
  undefined8 uVar9;
  uint uVar10;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long lVar11;
  long extraout_x10;
  undefined8 unaff_x20;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  undefined *local_d0;
  undefined8 local_c8;
  code *local_c0;
  undefined *puStack_b8;
  undefined4 local_b0;
  undefined *local_a8;
  undefined8 local_a0;
  code *local_98;
  undefined *puStack_90;
  undefined4 local_88;
  uint local_80;
  uint local_7c;
  undefined2 local_78;
  undefined4 local_76;
  int local_64;
  
  _OUTLINED_FUNCTION_18();
  lVar11 = 0x10023e000;
  if ((extraout_x8 == 0) || (_OUTLINED_FUNCTION_24(), lVar11 = extraout_x10, in_NG != in_OV)) {
    if (*(long *)(lVar11 + 0x850) != -1) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_27();
  }
  else {
    unaff_x20 = *(undefined8 *)(extraout_x8_00 + 0x110);
  }
  _OUTLINED_FUNCTION_20();
  iVar4 = _os_log_type_enabled();
  if (iVar4 != 0) {
    local_80 = local_80 & 0xffff0000;
    uVar7 = _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_42(uVar7,unaff_x20);
    __os_log_debug_impl();
  }
  bVar12 = false;
  if ((param_1 != 0) && (param_2 != 0)) {
    _OUTLINED_FUNCTION_54();
    lVar11 = _iap2_feature_getFeature();
    if ((lVar11 == 0) || (lVar8 = _iAP2MsgGetFirstParam(param_2,0), lVar8 == 0)) {
LAB_10014ada4:
      bVar12 = false;
    }
    else {
      uVar5 = 0;
      bVar12 = false;
      uVar6 = 0;
      bVar14 = false;
      uVar7 = 0;
      bVar13 = false;
      do {
        iVar4 = _iAP2MsgGetParamID(lVar8);
        if (iVar4 == 2) {
          uVar7 = _OUTLINED_FUNCTION_77();
          if (local_64 != 0) {
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_7();
            if (iVar4 != 0) {
              local_76 = _iAP2MsgGetMsgID(param_2);
              local_80 = (uint)DAT_1001b3108;
              local_7c = 2;
              local_78 = 0x400;
              _OUTLINED_FUNCTION_6();
LAB_10014ae0c:
              _OUTLINED_FUNCTION_41();
              __os_log_error_impl();
            }
            goto LAB_10014ada4;
          }
          bVar13 = true;
        }
        else if (iVar4 == 1) {
          uVar6 = _OUTLINED_FUNCTION_77();
          if (local_64 != 0) {
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_7();
            if (iVar4 != 0) {
              local_76 = _iAP2MsgGetMsgID(param_2);
              local_80 = (uint)DAT_1001b3108;
              local_7c = 1;
              local_78 = 0x400;
              _OUTLINED_FUNCTION_6();
              goto LAB_10014ae0c;
            }
            goto LAB_10014ada4;
          }
          bVar14 = true;
        }
        else if (iVar4 == 0) {
          uVar5 = _OUTLINED_FUNCTION_77();
          if (local_64 != 0) {
            _logObjectForModule();
            iVar4 = _OUTLINED_FUNCTION_7();
            if (iVar4 != 0) {
              local_76 = _iAP2MsgGetMsgID(param_2);
              local_80 = (uint)DAT_1001b3108;
              local_7c = 0;
              local_78 = 0x400;
              _OUTLINED_FUNCTION_6();
              goto LAB_10014ae0c;
            }
            goto LAB_10014ada4;
          }
          bVar12 = true;
        }
        lVar8 = _iAP2MsgGetNextParam(param_2,0,lVar8);
      } while (lVar8 != 0);
      if (bVar12) {
        local_a8 = PTR___NSConcreteStackBlock_10022bb78;
        local_a0 = DAT_1001b3118;
        local_98 = ____setNowPlayingInfoHandler_block_invoke;
        puStack_90 = &___block_descriptor_tmp_36;
        local_88 = uVar5;
        _acc_manager2_performPlatformWorkAsync(&local_a8);
      }
      if (bVar14) {
        local_d0 = PTR___NSConcreteStackBlock_10022bb78;
        local_c8 = DAT_1001b3118;
        local_c0 = ____setNowPlayingInfoHandler_block_invoke_2;
        puStack_b8 = &___block_descriptor_tmp_37;
        local_b0 = uVar6;
        _acc_manager2_performPlatformWorkAsync(&local_d0);
        bVar12 = true;
      }
      if (bVar13) {
        iVar4 = (int)uVar7;
        cVar1 = SCARRY4(iVar4,1);
        cVar2 = iVar4 + 1 < 0;
        uVar3 = iVar4 == -1;
        *(undefined1 *)(lVar11 + 0x53) = uVar3;
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), cVar2 != cVar1)) {
          _OUTLINED_FUNCTION_64();
          if (!(bool)uVar3) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
          }
          _OUTLINED_FUNCTION_26();
        }
        else {
          param_2 = *(long *)(extraout_x8_01 + 0x110);
        }
        _OUTLINED_FUNCTION_53();
        iVar4 = _os_log_type_enabled();
        if (iVar4 != 0) {
          local_80 = (uint)DAT_1001b30b0;
          local_7c = (uint)*(byte *)(lVar11 + 0x53);
          uVar9 = _OUTLINED_FUNCTION_6();
          __os_log_debug_impl(uVar9,param_2,2,
                              "_setNowPlayingInfoHandler: autoChoosePBQListStartIndex=%d",&local_80,
                              8);
        }
        uVar10 = (uint)*(byte *)(lVar11 + 0x51);
        cVar1 = SBORROW4(uVar10,1);
        cVar2 = (int)(uVar10 - 1) < 0;
        uVar3 = uVar10 == 1;
        if ((bool)uVar3) {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_38(), cVar2 != cVar1)) {
            _OUTLINED_FUNCTION_64();
            if (!(bool)uVar3) {
              _OUTLINED_FUNCTION_0();
              _dispatch_once();
            }
            _OUTLINED_FUNCTION_26();
          }
          else {
            param_2 = *(long *)(extraout_x8_02 + 0x110);
          }
          _OUTLINED_FUNCTION_53();
          iVar4 = _os_log_type_enabled();
          if (iVar4 != 0) {
            local_80 = local_80 & 0xffff0000;
            uVar9 = _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_42(uVar9,param_2);
            __os_log_debug_impl();
          }
          __checkMoveWindowAndRequestPBQList(0,uVar7,param_1,lVar11);
          bVar12 = true;
        }
      }
    }
  }
  return bVar12;
}


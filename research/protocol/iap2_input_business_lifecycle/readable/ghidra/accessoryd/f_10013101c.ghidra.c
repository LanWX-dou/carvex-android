/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013101c
 * original code SHA256: 9bea16c9e2fea17a76be6a873f4bd5f6d40b5b586164f34116182f37a48e44a4
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_hid_AccessoryHIDGetReportResponseHandler(long param_1,long param_2)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  long lVar10;
  undefined8 uVar11;
  undefined8 *extraout_x8;
  undefined8 uVar12;
  long extraout_x8_00;
  long extraout_x8_01;
  long lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined *puVar16;
  undefined1 auVar17 [16];
  uint local_c0;
  uint uStack_bc;
  undefined *local_b8;
  undefined8 local_b0;
  code *local_a8;
  undefined *puStack_a0;
  undefined8 local_98;
  long lStack_90;
  undefined2 local_88;
  undefined1 local_86;
  undefined1 local_85;
  undefined4 local_80;
  uint local_7c;
  int local_64;
  
  uVar9 = 0;
  local_64 = 0;
  if ((param_1 != 0) && (param_2 != 0)) {
    iVar5 = _iAP2MsgGetMsgID(param_2);
    if (iVar5 == 0x6805) {
      _OUTLINED_FUNCTION_12();
      lVar10 = _iAP2MsgGetFirstParam();
      uVar9 = 0;
      if (lVar10 != 0) {
        uVar15 = 0;
        uVar4 = 0;
        uVar14 = 0;
        lVar13 = 0;
        uVar7 = 0;
        local_c0 = 0;
        uStack_bc = 0;
        _OUTLINED_FUNCTION_39();
        uVar9 = DAT_1001b30b0;
        uVar12 = *extraout_x8;
        do {
          uVar6 = _iAP2MsgGetParamID(lVar10);
          cVar1 = SBORROW4(uVar6,3);
          cVar2 = (int)(uVar6 - 3) < 0;
          uVar3 = uVar6 == 3;
          if (uVar6 < 4) {
            switch(uVar6) {
            default:
              _OUTLINED_FUNCTION_32();
              uVar15 = _iAP2MsgGetDataAsU16();
              if (local_64 != 0) {
                _logObjectForModule();
                iVar5 = _OUTLINED_FUNCTION_24();
                if (iVar5 != 0) {
                  _iAP2MsgGetMsgID(param_2);
                  local_80 = (undefined4)DAT_1001b3108;
                  local_7c = 0;
                  uVar9 = _OUTLINED_FUNCTION_1();
LAB_1001313c8:
                  _OUTLINED_FUNCTION_26(uVar9,uVar14);
                  __os_log_error_impl();
                }
                goto LAB_100131364;
              }
              uVar7 = __validateHIDComponent(param_1,uVar15);
              break;
            case 1:
              _OUTLINED_FUNCTION_32();
              uVar4 = _iAP2MsgGetDataAsU8();
              if (local_64 != 0) {
                _logObjectForModule();
                iVar5 = _OUTLINED_FUNCTION_24();
                if (iVar5 != 0) {
                  _iAP2MsgGetMsgID(param_2);
                  local_80 = (undefined4)DAT_1001b3108;
                  local_7c = 1;
                  uVar9 = _OUTLINED_FUNCTION_1();
                  goto LAB_1001313c8;
                }
                goto LAB_100131364;
              }
              local_c0 = 1;
              break;
            case 2:
              _OUTLINED_FUNCTION_32();
              uVar11 = _iAP2MsgGetDataAsU8();
              if (local_64 != 0) {
                _logObjectForModule();
                iVar5 = _OUTLINED_FUNCTION_24();
                if (iVar5 != 0) {
                  _iAP2MsgGetMsgID(param_2);
                  local_80 = (undefined4)DAT_1001b3108;
                  local_7c = 2;
                  uVar9 = _OUTLINED_FUNCTION_1();
                  goto LAB_1001313c8;
                }
                goto LAB_100131364;
              }
              uStack_bc = 1;
              uVar14 = uVar11;
              break;
            case 3:
              uVar8 = _iAP2MsgGetParamValueLen(lVar10);
              _OUTLINED_FUNCTION_32();
              uVar11 = _iAP2MsgGetDataAsData();
              if (local_64 != 0) {
                _logObjectForModule();
                iVar5 = _OUTLINED_FUNCTION_24();
                if (iVar5 != 0) {
                  _iAP2MsgGetMsgID(param_2);
                  local_80 = (undefined4)DAT_1001b3108;
                  local_7c = 3;
                  uVar9 = _OUTLINED_FUNCTION_1();
                  goto LAB_1001313c8;
                }
                goto LAB_100131364;
              }
              if (lVar13 != 0) {
                _CFRelease(lVar13);
              }
              lVar13 = _CFDataCreate(uVar12,uVar11,uVar8);
            }
          }
          else {
            _OUTLINED_FUNCTION_18();
            if ((extraout_x8_00 == 0) || (_OUTLINED_FUNCTION_11(), cVar2 != cVar1)) {
              _OUTLINED_FUNCTION_7();
              puVar16 = PTR___os_log_default_10022bbb0;
              if (!(bool)uVar3) {
                _OUTLINED_FUNCTION_5();
                _dispatch_once();
                puVar16 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar16 = *(undefined **)(extraout_x8_01 + 0x118);
            }
            iVar5 = _os_log_type_enabled(puVar16,1);
            if (iVar5 != 0) {
              local_80 = (undefined4)uVar9;
              local_7c = uVar6;
              uVar11 = _OUTLINED_FUNCTION_6();
              __os_log_impl(uVar11,puVar16,1,"Unrecognized paramID:0x%04X");
            }
          }
          auVar17 = _OUTLINED_FUNCTION_12();
          lVar10 = _iAP2MsgGetNextParam(auVar17._0_8_,auVar17._8_8_,lVar10);
        } while (lVar10 != 0);
        if (((uVar7 & local_c0 & uStack_bc) == 0) || (lVar13 == 0)) {
LAB_100131364:
          uVar9 = 0;
          if (lVar13 == 0) {
            return 0;
          }
        }
        else {
          if (*(long *)(param_1 + 8) == 0) {
            local_98 = 0;
          }
          else {
            local_98 = _CFRetain();
          }
          _CFRetain(lVar13);
          local_b8 = PTR___NSConcreteStackBlock_10022bb78;
          local_b0 = DAT_1001b3118;
          local_a8 = ___iap2_hid_AccessoryHIDGetReportResponseHandler_block_invoke;
          puStack_a0 = &___block_descriptor_tmp_5;
          local_88 = (undefined2)uVar15;
          local_85 = (undefined1)uVar14;
          lStack_90 = lVar13;
          local_86 = uVar4;
          _acc_manager2_performPlatformWorkAsync(&local_b8);
          uVar9 = 1;
        }
        _CFRelease(lVar13);
      }
    }
    else {
      uVar9 = 0;
    }
  }
  return uVar9;
}


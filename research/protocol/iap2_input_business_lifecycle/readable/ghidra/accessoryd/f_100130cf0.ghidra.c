/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100130cf0
 * original code SHA256: f6a9f5c7b12f6f23f825abbe0fcfebac2f0521dc0d65690f8867c2274f8d970f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_hid_AccessoryHIDReportHandler(long param_1,long param_2)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  long lVar8;
  undefined8 uVar9;
  undefined8 *extraout_x8;
  long extraout_x8_00;
  long lVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined *puVar14;
  undefined1 auVar15 [16];
  undefined *local_b8;
  undefined8 local_b0;
  code *local_a8;
  undefined *puStack_a0;
  undefined8 local_98;
  long lStack_90;
  undefined2 local_88;
  undefined4 local_80;
  int local_7c;
  undefined2 local_78;
  undefined4 local_76;
  int local_64;
  
  local_64 = 0;
  uVar12 = 0;
  if ((param_1 != 0) && (param_2 != 0)) {
    _OUTLINED_FUNCTION_12(0x2b9411a8);
    iVar5 = _iAP2MsgGetMsgID(param_2);
    if (iVar5 == 0x6802) {
      _OUTLINED_FUNCTION_12();
      lVar8 = _iAP2MsgGetFirstParam();
      if (lVar8 != 0) {
        uVar11 = 0;
        lVar10 = 0;
        bVar4 = 0;
        _OUTLINED_FUNCTION_39();
        uVar12 = DAT_1001b30b0;
        uVar13 = *extraout_x8;
        do {
          iVar5 = _iAP2MsgGetParamID(lVar8);
          cVar1 = SBORROW4(iVar5,1);
          cVar2 = iVar5 + -1 < 0;
          uVar3 = iVar5 == 1;
          if ((bool)uVar3) {
            uVar6 = _iAP2MsgGetParamValueLen(lVar8);
            uVar9 = _iAP2MsgGetDataAsData(lVar8,&local_64);
            if (local_64 != 0) {
              _logObjectForModule();
              iVar5 = _OUTLINED_FUNCTION_24();
              if (iVar5 != 0) {
                local_76 = _iAP2MsgGetMsgID(param_2);
                local_80 = (undefined4)DAT_1001b3108;
                local_7c = 1;
                local_78 = 0x400;
                uVar12 = _OUTLINED_FUNCTION_6();
LAB_100131008:
                _OUTLINED_FUNCTION_26(uVar12,param_1);
                __os_log_error_impl();
              }
              goto LAB_100130f88;
            }
            if (lVar10 != 0) {
              _CFRelease(lVar10);
            }
            lVar10 = _CFDataCreate(uVar13,uVar9,uVar6);
          }
          else if (iVar5 == 0) {
            uVar11 = _iAP2MsgGetDataAsU16(lVar8,&local_64);
            if (local_64 != 0) {
              _logObjectForModule();
              iVar5 = _OUTLINED_FUNCTION_24();
              if (iVar5 != 0) {
                local_76 = _iAP2MsgGetMsgID(param_2);
                local_80 = (undefined4)DAT_1001b3108;
                local_7c = 0;
                local_78 = 0x400;
                uVar12 = _OUTLINED_FUNCTION_6();
                goto LAB_100131008;
              }
              goto LAB_100130f88;
            }
            bVar4 = __validateHIDComponent(param_1,uVar11);
          }
          else {
            if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_11(), cVar2 != cVar1)) {
              _OUTLINED_FUNCTION_7();
              puVar14 = PTR___os_log_default_10022bbb0;
              if (!(bool)uVar3) {
                _OUTLINED_FUNCTION_5();
                _dispatch_once();
                puVar14 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar14 = *(undefined **)(extraout_x8_00 + 0x118);
            }
            iVar7 = _os_log_type_enabled(puVar14,1);
            if (iVar7 != 0) {
              local_80 = (undefined4)uVar12;
              local_7c = iVar5;
              uVar9 = _OUTLINED_FUNCTION_6();
              __os_log_impl(uVar9,puVar14,1,"Unrecognized paramID:0x%04X");
            }
          }
          auVar15 = _OUTLINED_FUNCTION_12();
          lVar8 = _iAP2MsgGetNextParam(auVar15._0_8_,auVar15._8_8_,lVar8);
        } while (lVar8 != 0);
        if ((bVar4 & lVar10 != 0) == 1) {
          if (*(long *)(param_1 + 8) == 0) {
            local_98 = 0;
          }
          else {
            local_98 = _CFRetain();
          }
          _CFRetain(lVar10);
          local_b8 = PTR___NSConcreteStackBlock_10022bb78;
          local_b0 = DAT_1001b3118;
          local_a8 = ___iap2_hid_AccessoryHIDReportHandler_block_invoke;
          puStack_a0 = &___block_descriptor_tmp_4;
          local_88 = (undefined2)uVar11;
          lStack_90 = lVar10;
          _acc_manager2_performPlatformWorkAsync(&local_b8);
          uVar11 = 1;
        }
        else {
LAB_100130f88:
          uVar11 = 0;
          uVar12 = 0;
          if (lVar10 == 0) goto LAB_100130fa8;
        }
        _CFRelease(lVar10);
        uVar12 = uVar11;
        goto LAB_100130fa8;
      }
    }
    uVar12 = 0;
  }
LAB_100130fa8:
  _OUTLINED_FUNCTION_12(0x2b9411ac);
  return uVar12;
}


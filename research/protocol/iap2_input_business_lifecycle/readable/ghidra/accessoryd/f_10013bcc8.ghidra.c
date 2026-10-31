/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013bcc8
 * original code SHA256: 5265716a10600e7b85d22168a5ecca684497351484144f14d1069ce73deaad01
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _iap2_identification_identificationInfoHandler(long *param_1,undefined8 param_2)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  uint uVar4;
  int iVar5;
  void *pvVar6;
  ulong uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long extraout_x8_04;
  long extraout_x8_05;
  long extraout_x8_06;
  long extraout_x8_07;
  long extraout_x8_08;
  long extraout_x8_09;
  long extraout_x8_10;
  undefined8 unaff_x19;
  undefined1 auVar10 [16];
  undefined *local_b8;
  undefined8 local_b0;
  code *local_a8;
  undefined *puStack_a0;
  long *local_98;
  void *pvStack_90;
  int local_88;
  undefined *local_80;
  undefined8 local_78;
  code *local_70;
  undefined *puStack_68;
  long *local_60;
  void *pvStack_58;
  undefined4 local_50;
  int local_4c;
  
  if ((param_1 != (long *)0x0) && (*param_1 != 0)) {
    uVar4 = _iap2_identification_getState(param_1);
    uVar4 = uVar4 & 0xfffffffd;
    cVar1 = SBORROW4(uVar4,1);
    cVar2 = (int)(uVar4 - 1) < 0;
    uVar3 = uVar4 == 1;
    if ((bool)uVar3) {
      pvVar6 = (void *)_iap2_identification_createIdentificationInfo();
      if (pvVar6 == (void *)0x0) {
        _OUTLINED_FUNCTION_18();
        if ((extraout_x8 == 0) || (_OUTLINED_FUNCTION_6(), cVar2 != cVar1)) {
          _OUTLINED_FUNCTION_3();
          if (!(bool)uVar3) {
            _OUTLINED_FUNCTION_1();
          }
          _OUTLINED_FUNCTION_18();
        }
        else {
          unaff_x19 = *(undefined8 *)(extraout_x8_00 + 0xe0);
        }
        uVar7 = _os_log_type_enabled(unaff_x19,0x10);
        if ((int)uVar7 == 0) {
          return uVar7;
        }
        local_50 = (uint)local_50._2_2_ << 0x10;
        uVar8 = _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_18(uVar8,unaff_x19);
      }
      else {
        _OUTLINED_FUNCTION_26();
        iVar5 = _iap2_identification_setIdentificationInfo();
        if (iVar5 == 0) {
          _OUTLINED_FUNCTION_18();
          if ((extraout_x8_03 == 0) || (_OUTLINED_FUNCTION_6(), cVar2 != cVar1)) {
            _OUTLINED_FUNCTION_3();
            if (!(bool)uVar3) {
              _OUTLINED_FUNCTION_1();
            }
            _OUTLINED_FUNCTION_27();
          }
          else {
            param_1 = *(long **)(extraout_x8_04 + 0xe0);
          }
          iVar5 = _OUTLINED_FUNCTION_35();
          if (iVar5 != 0) {
            local_50 = local_50 & 0xffff0000;
            uVar8 = _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_18(uVar8,param_1);
          }
          _free(pvVar6);
        }
        else {
          auVar10 = _iap2_identification_createRejectMessage(pvVar6);
          uVar8 = auVar10._0_8_;
          if (auVar10._0_4_ == 0) {
            _OUTLINED_FUNCTION_14
                      (uVar8,auVar10._8_8_,_iap2_identification_cbIdentificationInfoParams);
            uVar8 = _iAP2MsgForEachParamDo();
            uVar9 = __MergedGlobals;
            if ((int)uVar8 == 0) {
              uVar8 = _CFArrayGetCount(__MergedGlobals);
              _CFArrayApplyFunction
                        (uVar9,0,uVar8,__CFSetValidateRequiredIdentificationParamsApplierFunction,
                         pvVar6);
              _OUTLINED_FUNCTION_26();
              iVar5 = _iap2_identification_checkIdentificationInfoForRequiredTransportParam();
              if ((*(byte *)((long)pvVar6 + 0x90) & 1) == 0) {
                if (iVar5 == 0) {
                  _OUTLINED_FUNCTION_18();
                  if ((extraout_x8_09 == 0) || (_OUTLINED_FUNCTION_6(), cVar2 != cVar1)) {
                    _OUTLINED_FUNCTION_3();
                    if (!(bool)uVar3) {
                      _OUTLINED_FUNCTION_1();
                    }
                    _OUTLINED_FUNCTION_15();
                  }
                  else {
                    uVar9 = *(undefined8 *)(extraout_x8_10 + 0xe0);
                  }
                  iVar5 = _os_log_type_enabled(uVar9,1);
                  if (iVar5 != 0) {
                    local_50 = local_50 & 0xffff0000;
                    uVar8 = _OUTLINED_FUNCTION_6();
                    __os_log_impl(uVar8,uVar9,1,
                                  "IdentificationInfo params processed, checking identification info..."
                                  ,&local_50,2);
                  }
                  _OUTLINED_FUNCTION_26();
                  iVar5 = _iap2_identification_checkIdentificationInfoAll();
                  local_b8 = PTR___NSConcreteStackBlock_10022bb78;
                  local_b0 = DAT_1001b3118;
                  local_a8 = ___iap2_identification_identificationInfoHandler_block_invoke_76;
                  puStack_a0 = &___block_descriptor_tmp_77;
                  local_98 = param_1;
                  pvStack_90 = pvVar6;
                  local_88 = iVar5;
                  _iap2_sessionControl_authorizationHook_identification
                            (param_1,*(undefined8 *)((long)pvVar6 + 8),&local_b8);
                  return (ulong)(iVar5 == 0);
                }
                uVar8 = 1;
              }
              else {
                uVar8 = 0xffffffff;
              }
            }
            else {
              _OUTLINED_FUNCTION_18();
              if ((extraout_x8_05 == 0) || (_OUTLINED_FUNCTION_6(), cVar2 != cVar1)) {
                _OUTLINED_FUNCTION_3();
                if (!(bool)uVar3) {
                  _OUTLINED_FUNCTION_1();
                }
                _OUTLINED_FUNCTION_26();
              }
              else {
                param_2 = *(undefined8 *)(extraout_x8_06 + 0xe0);
              }
              iVar5 = _os_log_type_enabled(param_2,0x10);
              if (iVar5 != 0) {
                local_50 = (uint)DAT_1001b30b0;
                local_4c = (int)uVar8;
                uVar9 = _OUTLINED_FUNCTION_6();
                _OUTLINED_FUNCTION_32(uVar9,param_2);
              }
            }
          }
          _OUTLINED_FUNCTION_18();
          if ((extraout_x8_07 == 0) || (_OUTLINED_FUNCTION_6(), cVar2 != cVar1)) {
            _OUTLINED_FUNCTION_3();
            if (!(bool)uVar3) {
              _OUTLINED_FUNCTION_1();
            }
            _OUTLINED_FUNCTION_26();
          }
          else {
            param_2 = *(undefined8 *)(extraout_x8_08 + 0xe0);
          }
          iVar5 = _os_log_type_enabled(param_2,0);
          if (iVar5 != 0) {
            local_50 = (uint)DAT_1001b30b0;
            local_4c = (int)uVar8;
            uVar8 = _OUTLINED_FUNCTION_6();
            __os_log_impl(uVar8,param_2,0,"IdentificationInfo rejected. Error: %d",&local_50,8);
          }
          local_80 = PTR___NSConcreteStackBlock_10022bb78;
          local_78 = DAT_1001b3118;
          local_70 = ___iap2_identification_identificationInfoHandler_block_invoke;
          puStack_68 = &___block_descriptor_tmp;
          local_60 = param_1;
          pvStack_58 = pvVar6;
          _iap2_sessionControl_authorizationHook_identification
                    (&local_70,param_1,*(undefined8 *)((long)pvVar6 + 8),&local_80);
        }
      }
    }
    else {
      _OUTLINED_FUNCTION_18();
      if ((extraout_x8_01 == 0) || (_OUTLINED_FUNCTION_6(), cVar2 != cVar1)) {
        _OUTLINED_FUNCTION_3();
        if (!(bool)uVar3) {
          _OUTLINED_FUNCTION_1();
        }
        _OUTLINED_FUNCTION_18();
      }
      else {
        unaff_x19 = *(undefined8 *)(extraout_x8_02 + 0xe0);
      }
      uVar7 = _os_log_type_enabled(unaff_x19,0);
      if ((int)uVar7 == 0) {
        return uVar7;
      }
      local_50 = (uint)local_50._2_2_ << 0x10;
      uVar8 = _OUTLINED_FUNCTION_6();
      __os_log_impl(uVar8,unaff_x19,0,
                    "After accessory has already completed Identify process once, any subsequent IdentificationInfo is ignored."
                    ,&local_50,2);
    }
  }
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100130444
 * original code SHA256: 008673991e86aac61988f5204d95f98eedafa0705a2281eb5bbfcd13e44a51db
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_hid_StartHIDMsgHandler(undefined8 *param_1,long param_2)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  long lVar9;
  long lVar10;
  undefined8 uVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  long lVar21;
  long lVar22;
  long lVar23;
  long lVar24;
  long lVar25;
  long lVar26;
  long lVar27;
  long lVar28;
  long lVar29;
  long lVar30;
  long lVar31;
  long lVar32;
  long lVar33;
  long lVar34;
  undefined8 *extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long lVar35;
  undefined *puVar36;
  undefined8 uVar37;
  uint uVar38;
  undefined8 uVar39;
  uint uVar40;
  undefined1 auVar41 [16];
  undefined *local_128;
  undefined8 local_120;
  code *local_118;
  undefined *puStack_110;
  undefined8 local_108;
  long lStack_100;
  undefined2 local_f8;
  undefined *local_f0;
  undefined8 local_e8;
  code *local_e0;
  undefined *puStack_d8;
  undefined8 local_d0;
  undefined2 local_c8;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 local_98;
  uint local_94;
  undefined4 local_90;
  uint local_8c;
  undefined2 local_88;
  undefined4 local_86;
  undefined4 local_7c;
  undefined1 local_77;
  undefined2 local_76;
  int local_74;
  
  local_74 = 0;
  local_76 = 0;
  local_77 = 0;
  local_7c = 0;
  uVar37 = 0;
  if ((param_1 != (undefined8 *)0x0) && (param_2 != 0)) {
    lVar9 = _iap2_feature_getFeature(param_1,0xb);
    if (lVar9 != 0) {
      _OUTLINED_FUNCTION_12(0x2b941180);
      iVar5 = _iAP2MsgGetMsgID(param_2);
      if ((iVar5 == 0x6800) && (lVar10 = _iAP2MsgGetFirstParam(param_2,0), lVar10 != 0)) {
        lVar35 = 0;
        uVar7 = 0;
        uVar38 = 0;
        uVar40 = 0;
        _OUTLINED_FUNCTION_39();
        uVar37 = DAT_1001b30b0;
        uVar39 = *extraout_x8;
        do {
          uVar6 = _iAP2MsgGetParamID(lVar10);
          cVar1 = SBORROW4(uVar6,4);
          cVar2 = (int)(uVar6 - 4) < 0;
          uVar3 = uVar6 == 4;
          if (uVar6 < 5) {
            switch(uVar6) {
            default:
              _OUTLINED_FUNCTION_21();
              uVar11 = _iAP2MsgGetDataAsU16();
              local_76 = (undefined2)uVar11;
              if (local_74 != 0) {
                _logObjectForModule();
                iVar5 = _OUTLINED_FUNCTION_8();
                if (iVar5 != 0) {
                  local_86 = _iAP2MsgGetMsgID(param_2);
                  local_90 = (undefined4)DAT_1001b3108;
                  local_8c = 0;
                  local_88 = 0x400;
                  uVar37 = _OUTLINED_FUNCTION_6();
LAB_100130cdc:
                  _OUTLINED_FUNCTION_26(uVar37,param_1);
                  __os_log_error_impl();
                }
                goto LAB_100130c5c;
              }
              uVar7 = __validateHIDComponent(param_1,uVar11);
              break;
            case 1:
              _OUTLINED_FUNCTION_21();
              uVar4 = _iAP2MsgGetDataAsU16();
              local_7c = CONCAT22(uVar4,(undefined2)local_7c);
              uVar38 = 1;
              break;
            case 2:
              _OUTLINED_FUNCTION_21();
              uVar4 = _iAP2MsgGetDataAsU16();
              local_7c = CONCAT22(local_7c._2_2_,uVar4);
              uVar40 = 1;
              break;
            case 3:
              _OUTLINED_FUNCTION_21();
              local_77 = _iAP2MsgGetDataAsU8();
              break;
            case 4:
              uVar8 = _iAP2MsgGetParamValueLen(lVar10);
              _OUTLINED_FUNCTION_21();
              uVar11 = _iAP2MsgGetDataAsData();
              if (local_74 != 0) {
                _logObjectForModule();
                iVar5 = _OUTLINED_FUNCTION_8();
                if (iVar5 != 0) {
                  local_86 = _iAP2MsgGetMsgID(param_2);
                  local_90 = (undefined4)DAT_1001b3108;
                  local_8c = 4;
                  local_88 = 0x400;
                  uVar37 = _OUTLINED_FUNCTION_6();
                  goto LAB_100130cdc;
                }
                goto LAB_100130c5c;
              }
              if (lVar35 != 0) {
                _CFRelease(lVar35);
              }
              lVar35 = _CFDataCreate(uVar39,uVar11,uVar8);
            }
          }
          else {
            _OUTLINED_FUNCTION_18();
            if ((extraout_x8_00 == 0) || (_OUTLINED_FUNCTION_11(), cVar2 != cVar1)) {
              _OUTLINED_FUNCTION_7();
              puVar36 = PTR___os_log_default_10022bbb0;
              if (!(bool)uVar3) {
                _OUTLINED_FUNCTION_5();
                _dispatch_once();
                puVar36 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar36 = *(undefined **)(extraout_x8_01 + 0x118);
            }
            iVar5 = _os_log_type_enabled(puVar36,1);
            if (iVar5 != 0) {
              local_90 = (undefined4)uVar37;
              local_8c = uVar6;
              uVar11 = _OUTLINED_FUNCTION_6();
              __os_log_impl(uVar11,puVar36,1,"Unrecognized paramID:0x%04X");
            }
          }
          auVar41 = _iAP2MsgGetNextParam(param_2,0,lVar10);
          lVar10 = auVar41._0_8_;
        } while (lVar10 != 0);
        uVar7 = (uint)(lVar35 != 0) & uVar38 & uVar40 & uVar7;
        if (uVar7 == 1) {
          local_90 = 0;
          local_98 = 2;
          local_a0 = 4;
          uStack_9c = 3;
          local_a8 = 6;
          uStack_a4 = 5;
          local_ac = 7;
          local_b0 = 9;
          local_b8 = 0xb;
          uStack_b4 = 10;
          local_bc = 0xc;
          local_94 = uVar7;
          auVar41 = _OUTLINED_FUNCTION_16(0,auVar41._8_8_,&local_90);
          lVar10 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar10,auVar41._8_8_,&local_94);
          lVar12 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar12,auVar41._8_8_,&local_98);
          lVar13 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar13,auVar41._8_8_,&uStack_9c);
          lVar14 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar14,auVar41._8_8_,&local_a0);
          lVar15 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar15,auVar41._8_8_,&uStack_a4);
          lVar16 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar16,auVar41._8_8_,&local_a8);
          lVar17 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar17,auVar41._8_8_,&local_ac);
          lVar18 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar18,auVar41._8_8_,&local_b0);
          lVar19 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar19,auVar41._8_8_,&uStack_b4);
          lVar20 = auVar41._0_8_;
          auVar41 = _OUTLINED_FUNCTION_16(lVar20,auVar41._8_8_,&local_b8);
          lVar21 = auVar41._0_8_;
          lVar22 = _OUTLINED_FUNCTION_16(lVar21,auVar41._8_8_,&local_bc);
          lVar23 = _CFNumberCreate(uVar39,8,(long)&local_7c + 2);
          lVar24 = _CFNumberCreate(uVar39,8,&local_7c);
          lVar25 = _CFNumberCreate(uVar39,7,&local_77);
          lVar26 = _CFNumberCreate(uVar39,2,&local_76);
          lVar27 = _acc_endpoint2_getAccessoryInfo(*param_1);
          if (lVar27 == 0) {
            _iap2_identification_paramName();
            lVar28 = _OUTLINED_FUNCTION_10();
            _iap2_identification_paramName(2);
            lVar29 = _OUTLINED_FUNCTION_10();
            _iap2_identification_paramName(1);
            lVar30 = _OUTLINED_FUNCTION_10();
            _iap2_identification_paramName(3);
            lVar31 = _OUTLINED_FUNCTION_10();
            _iap2_identification_paramName(4);
            lVar27 = _OUTLINED_FUNCTION_10();
          }
          else {
            lVar28 = _acc_accInfo_retainedProperty(lVar27,0,0);
            lVar29 = _acc_accInfo_retainedProperty(lVar27,1,0);
            lVar30 = _acc_accInfo_retainedProperty(lVar27,2,0);
            lVar31 = _acc_accInfo_retainedProperty(lVar27,3,0);
            lVar27 = _acc_accInfo_retainedProperty(lVar27,5,0);
          }
          auVar41 = __hidComponentFunctionType(param_1,local_76);
          local_c0 = auVar41._0_4_;
          lVar32 = _OUTLINED_FUNCTION_16(auVar41._0_8_,auVar41._8_8_,&local_c0);
          lVar33 = _CFDictionaryCreateMutable
                             (0,0,PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,
                              PTR__kCFTypeDictionaryValueCallBacks_10022bd48);
          _CFDictionaryAddValue(lVar33,lVar10,&cf_iAP);
          _CFDictionaryAddValue(lVar33,lVar12,lVar23);
          _CFDictionaryAddValue(lVar33,lVar13,lVar24);
          _CFDictionaryAddValue(lVar33,lVar22,lVar28);
          _CFDictionaryAddValue(lVar33,lVar15,lVar29);
          _CFDictionaryAddValue(lVar33,lVar16,lVar30);
          _CFDictionaryAddValue(lVar33,lVar17,lVar31);
          _CFDictionaryAddValue(lVar33,lVar14,lVar27);
          _CFDictionaryAddValue(lVar33,lVar18,lVar25);
          _CFDictionaryAddValue(lVar33,lVar19,lVar35);
          _CFDictionaryAddValue(lVar33,lVar20,lVar32);
          _CFDictionaryAddValue(lVar33,lVar21,*(undefined8 *)PTR__kCFBooleanTrue_10022bd00);
          lVar34 = _acc_endpoint2_copyProperty
                             (*param_1,*(undefined8 *)
                                        PTR__kCFACCProperties_Endpoint_RegistryEntryID_10022b970);
          if (lVar34 != 0) {
            _CFDictionaryAddValue(lVar33,_kCFAccessoryHID_HIDServiceRegistryEntryIDKey,lVar34);
            _CFRelease(lVar34);
          }
          if ((*(long *)(lVar9 + 8) != 0) &&
             (lVar9 = _CFDictionaryGetValue(*(long *)(lVar9 + 8),lVar26), lVar9 != 0)) {
            if (*(char *)(lVar9 + 0x19) == '\x01') {
              *(undefined2 *)(lVar9 + 0x18) = 0;
              *(undefined1 *)(lVar9 + 0x1a) = 0;
              local_d0 = 0;
              if (param_1[1] != 0) {
                local_d0 = _CFRetain();
              }
              local_f0 = PTR___NSConcreteStackBlock_10022bb78;
              local_e8 = DAT_1001b3118;
              local_e0 = ___iap2_hid_StartHIDMsgHandler_block_invoke;
              puStack_d8 = &___block_descriptor_tmp;
              local_c8 = local_76;
              _acc_manager2_performPlatformWorkAsync(&local_f0);
            }
            *(undefined2 *)(lVar9 + 0x18) = 0x101;
          }
          if (param_1[1] == 0) {
            local_108 = 0;
          }
          else {
            local_108 = _CFRetain();
          }
          _CFRetain(lVar33);
          local_128 = PTR___NSConcreteStackBlock_10022bb78;
          local_120 = DAT_1001b3118;
          local_118 = ___iap2_hid_StartHIDMsgHandler_block_invoke_2;
          puStack_110 = &___block_descriptor_tmp_3;
          local_f8 = local_76;
          lStack_100 = lVar33;
          _acc_manager2_performPlatformWorkAsync(&local_128);
          if (lVar26 != 0) {
            _CFRelease();
          }
          if (lVar23 != 0) {
            _CFRelease();
          }
          if (lVar24 != 0) {
            _CFRelease();
          }
          if (lVar25 != 0) {
            _CFRelease();
          }
          if (lVar28 != 0) {
            _CFRelease();
          }
          if (lVar29 != 0) {
            _CFRelease();
          }
          if (lVar30 != 0) {
            _CFRelease(lVar30);
          }
          if (lVar31 != 0) {
            _CFRelease();
          }
          if (lVar27 != 0) {
            _CFRelease(lVar27);
          }
          if (lVar32 != 0) {
            _CFRelease(lVar32);
          }
          if (lVar10 != 0) {
            _CFRelease(lVar10);
          }
          if (lVar12 != 0) {
            _CFRelease();
          }
          if (lVar13 != 0) {
            _CFRelease(lVar13);
          }
          if (lVar14 != 0) {
            _CFRelease(lVar14);
          }
          if (lVar15 != 0) {
            _CFRelease(lVar15);
          }
          if (lVar16 != 0) {
            _CFRelease();
          }
          if (lVar17 != 0) {
            _CFRelease();
          }
          if (lVar18 != 0) {
            _CFRelease();
          }
          if (lVar19 != 0) {
            _CFRelease();
          }
          if (lVar20 != 0) {
            _CFRelease();
          }
          if (lVar21 != 0) {
            _CFRelease();
          }
          if (lVar22 != 0) {
            _CFRelease();
          }
          if (lVar33 != 0) {
            _CFRelease(lVar33);
          }
          uVar39 = 1;
        }
        else {
LAB_100130c5c:
          uVar39 = 0;
          uVar37 = 0;
          if (lVar35 == 0) goto LAB_100130c7c;
        }
        _CFRelease(lVar35);
        uVar37 = uVar39;
        goto LAB_100130c7c;
      }
    }
    uVar37 = 0;
  }
LAB_100130c7c:
  _OUTLINED_FUNCTION_12(0x2b941184);
  return uVar37;
}


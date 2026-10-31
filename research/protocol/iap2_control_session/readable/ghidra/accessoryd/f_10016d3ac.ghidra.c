/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10016d3ac
 * original code SHA256: 7d5db2d7d7b9c2cebd668e773346c3fbba78a4ec697eb1ca6d877fe1eaa98b04
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_CarPlayStartSession(long *param_1,long param_2)

{
  uint uVar1;
  undefined8 *puVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  char *pcVar13;
  undefined2 extraout_w8;
  int extraout_w8_00;
  int extraout_w8_01;
  int extraout_w8_02;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long extraout_x8_04;
  ulong uVar14;
  undefined8 uVar15;
  undefined *puVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  long lVar20;
  undefined8 uVar21;
  long lVar22;
  undefined1 auVar23 [16];
  undefined8 local_198;
  undefined8 local_190;
  long *local_188;
  long local_180;
  undefined8 local_178;
  long *local_170;
  long local_168;
  long local_160;
  long local_158;
  long local_150;
  long local_148;
  long local_140;
  long local_138;
  long local_130;
  long local_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined4 local_110;
  uint local_10c;
  undefined2 uStack_108;
  undefined2 uStack_106;
  undefined2 uStack_104;
  undefined8 local_102;
  undefined2 local_fa;
  long local_f8;
  undefined2 local_f0;
  long local_ee;
  undefined2 local_e6;
  long local_e4;
  undefined2 local_dc;
  long local_da;
  undefined2 local_d2;
  long local_d0;
  undefined2 local_c8;
  long local_c6;
  undefined2 local_be;
  long local_bc;
  undefined2 local_b4;
  long *local_b2;
  undefined2 local_aa;
  long local_a8;
  undefined2 local_a0;
  long local_9e;
  undefined2 local_96;
  long local_94;
  undefined2 local_8c;
  undefined8 local_8a;
  undefined2 local_78 [6];
  int local_6c;
  
  puVar16 = PTR__kCFTypeArrayCallBacks_10022bd38;
  uVar21 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
  lVar9 = _CFArrayCreateMutable(uVar21,0,PTR__kCFTypeArrayCallBacks_10022bd38);
  lVar10 = _CFArrayCreateMutable(uVar21,0,puVar16);
  uVar15 = 0;
  lVar17 = 0;
  lVar18 = 0;
  lVar19 = 0;
  local_188 = param_1;
  if (param_1 == (long *)0x0) {
    lVar11 = _OUTLINED_FUNCTION_15();
  }
  else {
    lVar11 = _OUTLINED_FUNCTION_15();
    if (param_2 != 0) {
      uVar6 = _iAP2MsgGetMsgID(param_2);
      if (uVar6 == 0x4301) {
        _OUTLINED_FUNCTION_2(0x6d64);
        uVar1 = *(uint *)(*local_188 + 0x18);
        cVar3 = SBORROW4(uVar1,8);
        cVar4 = (int)(uVar1 - 8) < 0;
        uVar5 = uVar1 == 8;
        if (uVar1 < 9) {
          uVar8 = *(undefined4 *)(&DAT_1001b3fe0 + (ulong)uVar1 * 4);
        }
        else {
          uVar8 = 0;
        }
        local_158 = lVar10;
        local_140 = lVar9;
        _CFAbsoluteTimeGetCurrent();
        _platform_CarPlay_sendConnectionEvent(4,uVar8);
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar4 != cVar3)) {
          _OUTLINED_FUNCTION_6();
          puVar16 = PTR___os_log_default_10022bbb0;
          if (!(bool)uVar5) {
            _OUTLINED_FUNCTION_2();
            _dispatch_once();
            puVar16 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar16 = *(undefined **)(extraout_x8 + 0x1b0);
        }
        iVar7 = _os_log_type_enabled(puVar16,0);
        lVar19 = 0x1001b3000;
        if (iVar7 != 0) {
          local_110 = (undefined4)DAT_1001b30b0;
          local_10c = uVar6;
          uVar15 = _OUTLINED_FUNCTION_6();
          __os_log_impl(uVar15,puVar16,0,"iap2_CarPlayStartSession: Received message 0x%x",
                        &local_110,8);
        }
        lVar10 = _iAP2MsgGetFirstParam(param_2,0);
        local_6c = -0x55555556;
        if (lVar10 == 0) {
          local_180 = 0;
          local_178 = 0;
          lVar17 = 0;
          lVar18 = 0;
          local_170 = (long *)0x0;
          local_168 = 0;
          local_160 = 0;
          local_150 = 0;
          local_148 = 0;
          local_130 = 0;
          local_128 = 0;
          local_138 = 0;
        }
        else {
          local_150 = 0;
          local_148 = 0;
          local_138 = 0;
          local_130 = 0;
          local_128 = 0;
          local_168 = 0;
          local_160 = 0;
          local_178 = 0;
          local_170 = (long *)0x0;
          local_180 = 0;
          lVar18 = 0;
          lVar17 = 0;
          local_190 = *(undefined8 *)PTR__kCFBooleanTrue_10022bd00;
          local_198 = *(undefined8 *)PTR__kCFBooleanFalse_10022bcf8;
          uStack_118 = 0;
          local_120 = DAT_1001b30b0;
          do {
            uVar12 = _iAP2MsgGetParamID(lVar10);
            uVar6 = (uint)uVar12;
            cVar3 = SBORROW4(uVar6,8);
            cVar4 = (int)(uVar6 - 8) < 0;
            uVar5 = uVar6 == 8;
            if (uVar6 < 9) {
              uVar14 = uVar12 & 0xffffffff;
              cVar3 = SBORROW8(uVar14,8);
              cVar4 = (long)(uVar14 - 8) < 0;
              uVar5 = uVar14 == 8;
              switch(uVar14) {
              default:
                _OUTLINED_FUNCTION_11();
                for (uVar12 = _iAP2MsgGetFirstParam(); uVar12 != 0;
                    uVar12 = _iAP2MsgGetNextParam(auVar23._0_8_,auVar23._8_8_,uVar12)) {
                  iVar7 = _iAP2MsgGetParamID(uVar12);
                  if (iVar7 == 0) {
                    _OUTLINED_FUNCTION_9();
                    _iAP2MsgGetDataAsString();
                    if (local_6c == 0) {
                      lVar9 = _OUTLINED_FUNCTION_5();
                      if (lVar9 != 0) {
                        _CFArrayAppendValue(local_140,lVar9);
                        _CFRelease(lVar9);
                        lVar19 = lVar9;
                      }
                      goto LAB_10016d634;
                    }
                    _logObjectForModule();
                    iVar7 = _OUTLINED_FUNCTION_7();
                    if (iVar7 != 0) {
                      _iAP2MsgGetMsgID(param_2);
                      uVar8 = _OUTLINED_FUNCTION_8(DAT_1001b3100);
                      uStack_106 = 0;
                      uStack_104 = 0;
                      local_102._0_6_ = CONCAT42(uVar8,extraout_w8);
                      uVar15 = _OUTLINED_FUNCTION_6();
LAB_10016de44:
                      pcVar13 = 
                      "Subparam ID: %d parse error in Param ID: %d for Msg ID: 0x%04X - ignoring message"
                      ;
                      uVar21 = 0x14;
                      goto LAB_10016de54;
                    }
                    goto LAB_10016df6c;
                  }
                  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar4 != cVar3)) {
                    _OUTLINED_FUNCTION_6();
                    if (!(bool)uVar5) {
                      _OUTLINED_FUNCTION_2();
                      _dispatch_once();
                    }
                    _OUTLINED_FUNCTION_41();
                  }
                  else {
                    lVar19 = *(long *)(extraout_x8_00 + 0x1b0);
                  }
                  iVar7 = _OUTLINED_FUNCTION_21();
                  if (iVar7 != 0) {
                    _OUTLINED_FUNCTION_4();
                    __os_log_impl();
                  }
LAB_10016d634:
                  auVar23 = _OUTLINED_FUNCTION_11();
                }
                break;
              case 1:
                _OUTLINED_FUNCTION_11();
                for (uVar12 = _iAP2MsgGetFirstParam(); uVar12 != 0;
                    uVar12 = _iAP2MsgGetNextParam(auVar23._0_8_,auVar23._8_8_,uVar12)) {
                  uVar6 = _iAP2MsgGetParamID(uVar12);
                  cVar3 = SBORROW4(uVar6,4);
                  cVar4 = (int)(uVar6 - 4) < 0;
                  uVar5 = uVar6 == 4;
                  if (uVar6 < 5) {
                    uVar14 = (ulong)uVar6;
                    cVar3 = SBORROW8(uVar14,4);
                    cVar4 = (long)(uVar14 - 4) < 0;
                    uVar5 = uVar14 == 4;
                    switch(uVar14) {
                    default:
                      _OUTLINED_FUNCTION_9();
                      _iAP2MsgGetDataAsString();
                      if (local_6c != 0) {
                        _logObjectForModule();
                        iVar7 = _OUTLINED_FUNCTION_7();
                        if (iVar7 == 0) goto LAB_10016df6c;
                        _iAP2MsgGetMsgID(param_2);
                        _OUTLINED_FUNCTION_8(DAT_1001b3100);
                        uVar15 = _OUTLINED_FUNCTION_1();
                        goto LAB_10016de44;
                      }
                      local_148 = _OUTLINED_FUNCTION_5();
                      break;
                    case 1:
                      _OUTLINED_FUNCTION_9();
                      lVar19 = _iAP2MsgGetDataAsString();
                      if (local_6c != 0) {
                        _logObjectForModule();
                        iVar7 = _OUTLINED_FUNCTION_7();
                        if (iVar7 == 0) goto LAB_10016df6c;
                        uVar8 = _iAP2MsgGetMsgID(param_2);
                        local_110 = (undefined4)DAT_1001b3100;
                        local_10c = 1;
                        uStack_108 = 0x400;
                        uStack_106 = 1;
                        uStack_104 = 0;
                        local_102._0_6_ = CONCAT42(uVar8,0x400);
                        uVar15 = _OUTLINED_FUNCTION_6();
                        goto LAB_10016de44;
                      }
                      if (local_130 != 0) {
                        _CFRelease();
                      }
                      local_130 = _OUTLINED_FUNCTION_20();
                      break;
                    case 2:
                      _OUTLINED_FUNCTION_9();
                      _iAP2MsgGetDataAsU8();
                      _OUTLINED_FUNCTION_14();
                      if (extraout_w8_02 != 0) {
                        _logObjectForModule();
                        iVar7 = _OUTLINED_FUNCTION_7();
                        if (iVar7 == 0) goto LAB_10016df6c;
                        _iAP2MsgGetMsgID(param_2);
                        local_110 = (undefined4)DAT_1001b3100;
                        _OUTLINED_FUNCTION_3(2);
                        uVar15 = _OUTLINED_FUNCTION_1();
                        goto LAB_10016de44;
                      }
                      if (local_128 != 0) {
                        _CFRelease();
                      }
                      local_128 = _OUTLINED_FUNCTION_17();
                      break;
                    case 3:
                      _OUTLINED_FUNCTION_9();
                      _iAP2MsgGetDataAsString();
                      if (local_6c != 0) {
                        _logObjectForModule();
                        iVar7 = _OUTLINED_FUNCTION_7();
                        if (iVar7 == 0) goto LAB_10016df6c;
                        _iAP2MsgGetMsgID(param_2);
                        local_110 = (undefined4)DAT_1001b3100;
                        _OUTLINED_FUNCTION_3(3);
                        uVar15 = _OUTLINED_FUNCTION_1();
                        goto LAB_10016de44;
                      }
                      lVar9 = _OUTLINED_FUNCTION_5();
                      if (lVar9 != 0) {
                        _CFArrayAppendValue(local_158,lVar9);
                        _CFRelease(lVar9);
                        lVar19 = lVar9;
                      }
                      break;
                    case 4:
                      _OUTLINED_FUNCTION_9();
                      local_78[0] = _iAP2MsgGetDataAsU8();
                      if (local_6c != 0) {
                        _logObjectForModule();
                        iVar7 = _OUTLINED_FUNCTION_7();
                        if (iVar7 == 0) goto LAB_10016df6c;
                        _iAP2MsgGetMsgID(param_2);
                        local_110 = (undefined4)DAT_1001b3100;
                        _OUTLINED_FUNCTION_3(4);
                        uVar15 = _OUTLINED_FUNCTION_1();
                        goto LAB_10016de44;
                      }
                      if (local_138 != 0) {
                        _CFRelease();
                      }
                      local_138 = _CFNumberCreate(uVar21,2,local_78);
                    }
                  }
                  else {
                    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar4 != cVar3)) {
                      _OUTLINED_FUNCTION_6();
                      if (!(bool)uVar5) {
                        _OUTLINED_FUNCTION_2();
                        _dispatch_once();
                      }
                      _OUTLINED_FUNCTION_41();
                    }
                    else {
                      lVar19 = *(long *)(extraout_x8_02 + 0x1b0);
                    }
                    iVar7 = _OUTLINED_FUNCTION_21();
                    if (iVar7 != 0) {
                      _OUTLINED_FUNCTION_4();
                      __os_log_impl();
                    }
                  }
                  auVar23 = _OUTLINED_FUNCTION_11();
                }
                break;
              case 2:
                _OUTLINED_FUNCTION_13();
                _iAP2MsgGetDataAsU32();
                _OUTLINED_FUNCTION_14();
                if (extraout_w8_00 != 0) {
                  _logObjectForModule();
                  iVar7 = _OUTLINED_FUNCTION_7();
                  if (iVar7 != 0) {
                    _iAP2MsgGetMsgID(param_2);
                    local_110 = (undefined4)DAT_1001b3108;
                    uVar15 = _OUTLINED_FUNCTION_0(2);
LAB_10016dff0:
                    pcVar13 = "Param ID: %d parse error for Msg ID: 0x%04X - ignoring message";
                    uVar21 = 0xe;
LAB_10016de54:
                    __os_log_error_impl(uVar15,uVar12,0x10,pcVar13,&local_110,uVar21);
                  }
LAB_10016df6c:
                  uVar15 = 0;
                  lVar11 = local_138;
                  param_1 = local_170;
                  lVar9 = local_140;
                  lVar10 = local_158;
                  lVar19 = local_180;
                  goto LAB_10016db80;
                }
                local_150 = _OUTLINED_FUNCTION_17();
                break;
              case 3:
                _OUTLINED_FUNCTION_13();
                _iAP2MsgGetDataAsString();
                if (local_6c != 0) {
                  _logObjectForModule();
                  iVar7 = _OUTLINED_FUNCTION_7();
                  if (iVar7 != 0) {
                    _iAP2MsgGetMsgID(param_2);
                    local_110 = (undefined4)DAT_1001b3108;
                    uVar15 = _OUTLINED_FUNCTION_0(3);
                    goto LAB_10016dff0;
                  }
                  goto LAB_10016df6c;
                }
                local_168 = _OUTLINED_FUNCTION_5();
                break;
              case 4:
                _OUTLINED_FUNCTION_13();
                _iAP2MsgGetDataAsString();
                if (local_6c != 0) {
                  _logObjectForModule();
                  iVar7 = _OUTLINED_FUNCTION_7();
                  if (iVar7 != 0) {
                    _iAP2MsgGetMsgID(param_2);
                    local_110 = (undefined4)DAT_1001b3108;
                    uVar15 = _OUTLINED_FUNCTION_0(4);
                    goto LAB_10016dff0;
                  }
                  goto LAB_10016df6c;
                }
                local_160 = _OUTLINED_FUNCTION_5();
                break;
              case 5:
                _OUTLINED_FUNCTION_13();
                _iAP2MsgGetDataAsString();
                if (local_6c != 0) {
                  _logObjectForModule();
                  iVar7 = _OUTLINED_FUNCTION_7();
                  if (iVar7 != 0) {
                    _iAP2MsgGetMsgID(param_2);
                    local_110 = (undefined4)DAT_1001b3108;
                    uVar15 = _OUTLINED_FUNCTION_0(5);
                    goto LAB_10016dff0;
                  }
                  goto LAB_10016df6c;
                }
                local_170 = (long *)_OUTLINED_FUNCTION_5();
                break;
              case 6:
                _OUTLINED_FUNCTION_13();
                _iAP2MsgGetDataAsString();
                if (local_6c != 0) {
                  _logObjectForModule();
                  iVar7 = _OUTLINED_FUNCTION_7();
                  if (iVar7 != 0) {
                    _iAP2MsgGetMsgID(param_2);
                    local_110 = (undefined4)DAT_1001b3108;
                    uVar15 = _OUTLINED_FUNCTION_0(6);
                    goto LAB_10016dff0;
                  }
                  goto LAB_10016df6c;
                }
                local_180 = _OUTLINED_FUNCTION_5();
                break;
              case 7:
                _OUTLINED_FUNCTION_11();
                for (uVar12 = _iAP2MsgGetFirstParam(); uVar12 != 0;
                    uVar12 = _iAP2MsgGetNextParam(auVar23._0_8_,auVar23._8_8_,uVar12)) {
                  iVar7 = _iAP2MsgGetParamID(uVar12);
                  cVar3 = SBORROW4(iVar7,1);
                  cVar4 = iVar7 + -1 < 0;
                  uVar5 = iVar7 == 1;
                  if ((bool)uVar5) {
                    _OUTLINED_FUNCTION_9();
                    _iAP2MsgGetDataAsU32();
                    _OUTLINED_FUNCTION_14();
                    if (extraout_w8_01 != 0) {
                      _logObjectForModule();
                      iVar7 = _OUTLINED_FUNCTION_7();
                      if (iVar7 == 0) goto LAB_10016df6c;
                      _iAP2MsgGetMsgID(param_2);
                      local_110 = (undefined4)DAT_1001b3100;
                      _OUTLINED_FUNCTION_3(1);
                      uVar15 = _OUTLINED_FUNCTION_1();
                      goto LAB_10016de44;
                    }
                    if (lVar17 != 0) {
                      _CFRelease(lVar17);
                    }
                    lVar17 = _OUTLINED_FUNCTION_17();
                  }
                  else if (iVar7 == 0) {
                    _OUTLINED_FUNCTION_9();
                    lVar19 = _iAP2MsgGetDataAsString();
                    if (local_6c != 0) {
                      _logObjectForModule();
                      iVar7 = _OUTLINED_FUNCTION_7();
                      if (iVar7 == 0) goto LAB_10016df6c;
                      _iAP2MsgGetMsgID(param_2);
                      _OUTLINED_FUNCTION_8(DAT_1001b3100);
                      uVar15 = _OUTLINED_FUNCTION_1();
                      goto LAB_10016de44;
                    }
                    if (lVar18 != 0) {
                      _CFRelease(lVar18);
                    }
                    lVar18 = _OUTLINED_FUNCTION_20();
                  }
                  else {
                    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar4 != cVar3)) {
                      _OUTLINED_FUNCTION_6();
                      if (!(bool)uVar5) {
                        _OUTLINED_FUNCTION_2();
                        _dispatch_once();
                      }
                      _OUTLINED_FUNCTION_41();
                    }
                    else {
                      lVar19 = *(long *)(extraout_x8_01 + 0x1b0);
                    }
                    iVar7 = _OUTLINED_FUNCTION_21();
                    if (iVar7 != 0) {
                      _OUTLINED_FUNCTION_4();
                      __os_log_impl();
                    }
                  }
                  auVar23 = _OUTLINED_FUNCTION_11();
                }
                break;
              case 8:
                _OUTLINED_FUNCTION_13();
                iVar7 = _iAP2MsgGetDataAsBool();
                if (local_6c != 0) {
                  _logObjectForModule();
                  iVar7 = _OUTLINED_FUNCTION_7();
                  if (iVar7 != 0) {
                    _iAP2MsgGetMsgID(param_2);
                    local_110 = (undefined4)DAT_1001b3108;
                    uVar15 = _OUTLINED_FUNCTION_0(8);
                    goto LAB_10016dff0;
                  }
                  goto LAB_10016df6c;
                }
                cVar4 = iVar7 < 0;
                uVar5 = iVar7 == 0;
                cVar3 = '\0';
                puVar2 = &local_190;
                if ((bool)uVar5) {
                  puVar2 = &local_198;
                }
                local_178 = *puVar2;
              }
            }
            else {
              if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar4 != cVar3)) {
                _OUTLINED_FUNCTION_6();
                if (!(bool)uVar5) {
                  _OUTLINED_FUNCTION_2();
                  _dispatch_once();
                }
                _OUTLINED_FUNCTION_41();
              }
              else {
                lVar19 = *(long *)(extraout_x8_03 + 0x1b0);
              }
              iVar7 = _OUTLINED_FUNCTION_21();
              if (iVar7 != 0) {
                local_110 = (undefined4)local_120;
                local_10c = uVar6;
                uVar15 = _OUTLINED_FUNCTION_6();
                __os_log_impl(uVar15,lVar19,1,"Unrecognized paramID:0x%04X");
              }
            }
            lVar10 = _iAP2MsgGetNextParam(param_2,0,lVar10);
          } while (lVar10 != 0);
        }
        uVar15 = _platform_externalAccesory_legacyConnectionUUIDForPrimaryEndpointUUID(local_188[1])
        ;
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar4 != cVar3)) {
          _OUTLINED_FUNCTION_6();
          lVar20 = local_160;
          lVar22 = local_168;
          lVar19 = local_180;
          puVar16 = PTR___os_log_default_10022bbb0;
          if (!(bool)uVar5) {
            _OUTLINED_FUNCTION_2();
            _dispatch_once();
            puVar16 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar16 = *(undefined **)(extraout_x8_04 + 0x1b0);
          lVar19 = local_180;
          lVar20 = local_160;
          lVar22 = local_168;
        }
        lVar9 = local_140;
        lVar10 = local_158;
        iVar7 = _os_log_type_enabled(puVar16,0);
        if (iVar7 != 0) {
          local_110 = (undefined4)DAT_1001b3ab0;
          local_10c = (uint)lVar9;
          uStack_108 = (undefined2)((ulong)lVar9 >> 0x20);
          uStack_106 = (undefined2)((ulong)lVar9 >> 0x30);
          uStack_104 = 0x840;
          local_102 = lVar10;
          local_fa = 0x840;
          local_f8 = local_148;
          local_f0 = 0x840;
          local_ee = local_130;
          local_e6 = 0x840;
          local_e4 = local_138;
          local_dc = 0x840;
          local_da = local_128;
          local_d2 = 0x840;
          local_d0 = local_150;
          local_c8 = 0x840;
          local_be = 0x840;
          local_b4 = 0x840;
          local_b2 = local_170;
          local_aa = 0x840;
          local_a0 = 0x840;
          local_96 = 0x840;
          local_8c = 0x840;
          local_8a = local_178;
          local_c6 = lVar22;
          local_bc = lVar20;
          local_a8 = lVar19;
          local_9e = lVar18;
          local_94 = lVar17;
          uVar21 = _OUTLINED_FUNCTION_6();
          __os_log_impl(uVar21,puVar16,0,
                        "iap2_CarPlayStartSession: call platform_CarPlay_startSession, usbIP %@, wifiIP %@, ssid %@, pass %@, securityType %@, channel %@, port %@, deviceID %@, pubKey %@, srcVer %@, sdkVer %@, assetID %@, assetVer %@, mutualAuth %@"
                        ,&local_110,0x8e);
        }
        lVar11 = local_138;
        param_1 = local_170;
        _platform_CarPlay_startSession
                  (uVar15,lVar9,lVar10,local_148,local_130,local_138,local_128,local_150,lVar22,
                   lVar20,local_170,lVar19,lVar18,lVar17,local_178);
        uVar15 = 1;
      }
      else {
        lVar17 = 0;
        lVar18 = 0;
        param_1 = (long *)0x0;
        local_168 = 0;
        local_160 = 0;
        local_150 = 0;
        local_148 = 0;
        local_130 = 0;
        local_128 = 0;
        uVar15 = 0;
        lVar11 = 0;
        lVar19 = 0;
      }
    }
  }
LAB_10016db80:
  if (lVar9 != 0) {
    _CFRelease(lVar9);
  }
  lVar22 = local_160;
  lVar9 = local_168;
  if (lVar10 != 0) {
    _CFRelease(lVar10);
  }
  if (local_148 != 0) {
    _CFRelease(local_148);
  }
  lVar10 = local_150;
  if (local_130 != 0) {
    _CFRelease(local_130);
  }
  if (local_128 != 0) {
    _CFRelease(local_128);
  }
  if (lVar11 != 0) {
    _CFRelease();
  }
  if (lVar10 != 0) {
    _CFRelease(lVar10);
  }
  if (lVar9 != 0) {
    _CFRelease(lVar9);
  }
  if (lVar22 != 0) {
    _CFRelease(lVar22);
  }
  if (param_1 != (long *)0x0) {
    _CFRelease(param_1);
  }
  if (lVar19 != 0) {
    _CFRelease(lVar19);
  }
  if (lVar18 != 0) {
    _CFRelease(lVar18);
  }
  if (lVar17 != 0) {
    _CFRelease(lVar17);
  }
  return uVar15;
}


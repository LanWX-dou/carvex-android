/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001850bc
 * original code SHA256: ad5f8c9a290acc985f3e69a1b737fc8bcdccdc1e8c88f1ad3baa7cdceb79deb2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_accAuthentication_certificate(undefined8 *param_1,long param_2)

{
  undefined1 uVar1;
  undefined8 uVar2;
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  long lVar7;
  int *piVar8;
  ulong uVar9;
  long lVar10;
  long lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long extraout_x8_04;
  long extraout_x8_05;
  undefined4 extraout_w9;
  undefined4 extraout_w9_00;
  undefined8 extraout_x9;
  undefined8 extraout_x10;
  undefined1 unaff_w19;
  undefined1 uVar14;
  undefined8 uVar15;
  int *unaff_x22;
  undefined *puVar16;
  undefined8 *puVar17;
  int *piVar18;
  uint uVar19;
  undefined1 auVar20 [16];
  uint local_104;
  long local_f0;
  long local_e8;
  undefined *local_e0;
  undefined8 local_d8;
  code *local_d0;
  undefined *puStack_c8;
  undefined8 *local_c0;
  undefined8 *puStack_b8;
  int *local_b0;
  undefined1 local_a8;
  uint local_a0;
  uint local_9c;
  undefined2 uStack_98;
  undefined2 uStack_96;
  undefined2 uStack_94;
  int local_92;
  undefined2 uStack_8e;
  undefined2 uStack_8c;
  undefined2 uStack_8a;
  undefined8 local_88;
  undefined2 local_80;
  long local_7e;
  int local_6c [3];
  
  if (param_1 == (undefined8 *)0x0) {
    return 0;
  }
  if (param_2 == 0) {
    return 0;
  }
  local_6c[0] = 0;
  lVar7 = _iAP2MsgGetFirstParam(param_2,0);
  piVar8 = (int *)_iap2_feature_getFeature(param_1,0);
  uVar15 = DAT_1001b3c10;
  if (piVar8 == (int *)0x0) {
    return 0;
  }
  if (*piVar8 != 0) {
    uVar15 = _logObjectForModule(0x1b);
    iVar4 = _os_log_type_enabled(uVar15,0);
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_7(*piVar8);
      uVar15 = extraout_x10;
      if (!(bool)in_ZR) {
        uVar15 = extraout_x9;
      }
      _OUTLINED_FUNCTION_16(uVar15,DAT_1001b3090);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_13();
    }
    return 1;
  }
  puVar17 = &DAT_10023f000;
  if (lVar7 == 0) {
    iVar4 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ForceAuthTimeout);
    local_f0 = 0;
    local_e8 = 0;
    if (iVar4 != 0) goto LAB_1001854a8;
LAB_1001854f0:
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_9(), in_NG != in_OV)) {
      _OUTLINED_FUNCTION_2();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_1();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    else {
      piVar8 = *(int **)(extraout_x8_03 + 0xd8);
    }
    iVar4 = _os_log_type_enabled(piVar8,0x10);
    if (iVar4 != 0) {
      uVar15 = _OUTLINED_FUNCTION_4(DAT_1001b3090);
      _OUTLINED_FUNCTION_19(uVar15,piVar8);
    }
    _OUTLINED_FUNCTION_3();
LAB_100185844:
    if (param_1[3] == 0) {
      uVar15 = _logObjectForModule(0x1b);
      iVar4 = _os_log_type_enabled(uVar15,0x10);
      if (iVar4 != 0) {
        uVar12 = _OUTLINED_FUNCTION_4(DAT_1001b3090);
        _OUTLINED_FUNCTION_19(uVar12,uVar15);
      }
      uVar15 = 0;
      goto LAB_1001858b0;
    }
    local_e0 = PTR___NSConcreteStackBlock_10022bb78;
    local_d8 = DAT_1001b3118;
    local_d0 = ___iap2_accAuthentication_certificate_block_invoke;
    puStack_c8 = &___block_descriptor_tmp_4;
    local_c0 = param_1;
    puStack_b8 = puVar17;
    local_b0 = unaff_x22;
    local_a8 = unaff_w19;
    _acc_protocolEndpoint_performAsync(*param_1,*(undefined1 *)(param_1 + 4),param_1[3],&local_e0);
  }
  else {
    local_f0 = 0;
    local_e8 = 0;
    local_104 = 0;
    uVar13 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
    unaff_w19 = 0;
    uVar14 = 0;
    uVar1 = 0;
    _OUTLINED_FUNCTION_15();
    uVar2 = DAT_1001b3108;
    uVar12 = DAT_1001b30b0;
    do {
      uVar3 = _iAP2MsgGetParamID(lVar7);
      in_OV = SBORROW4(uVar3,2);
      in_NG = (int)(uVar3 - 2) < 0;
      in_ZR = uVar3 == 2;
      uVar19 = (uint)uVar12;
      if ((bool)in_ZR) {
        uVar9 = _iAP2MsgGetParamValueData(lVar7);
        iVar4 = _iAP2MsgGetParamValueLen(lVar7);
        if (((uVar9 == 0) || (iVar4 == 0)) || (local_6c[0] != 0)) {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_9(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_2();
            unaff_x22 = piVar8;
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_1();
              _dispatch_once();
            }
          }
          else {
            unaff_x22 = *(int **)(extraout_x8_00 + 0xd8);
          }
          iVar6 = _OUTLINED_FUNCTION_12();
          if (iVar6 != 0) {
            _OUTLINED_FUNCTION_16(uVar9 & 0xffff,uVar15);
            uStack_94 = 0x400;
            uStack_8e = 0x400;
            uStack_8c = (undefined2)extraout_w9;
            uStack_8a = (undefined2)((uint)extraout_w9 >> 0x10);
            local_92 = iVar4;
            auVar20 = _OUTLINED_FUNCTION_5();
            goto LAB_10018542c;
          }
        }
        else {
          if (local_e8 != 0) {
            _CFRelease();
          }
          local_e8 = _CFDataCreate(uVar13,uVar9,iVar4);
        }
      }
      else {
        in_OV = SBORROW4(uVar3,1);
        in_NG = (int)(uVar3 - 1) < 0;
        in_ZR = uVar3 == 1;
        if ((bool)in_ZR) {
          uVar3 = _iAP2MsgGetDataAsU8(lVar7,local_6c);
          in_OV = SBORROW4(uVar3,1);
          in_NG = (int)(uVar3 - 1) < 0;
          in_ZR = uVar3 == 1;
          if ((uVar3 < 2) && (local_6c[0] == 0)) {
            if (_gLogObjects == 0 || _gNumLogObjects < 0x1c) {
              _OUTLINED_FUNCTION_2();
              unaff_x22 = piVar8;
              if (!(bool)in_ZR) {
                _OUTLINED_FUNCTION_1();
                _dispatch_once();
              }
            }
            else {
              unaff_x22 = *(int **)(_gLogObjects + 0xd8);
            }
            iVar4 = _OUTLINED_FUNCTION_12();
            local_104 = uVar3;
            if (iVar4 != 0) {
              local_a0 = uVar19;
              local_9c = uVar3;
              _OUTLINED_FUNCTION_5();
              __os_log_impl();
            }
          }
          else {
            if (_gLogObjects == 0 || _gNumLogObjects < 0x1c) {
              _OUTLINED_FUNCTION_2();
              unaff_x22 = piVar8;
              if (!(bool)in_ZR) {
                _OUTLINED_FUNCTION_1();
                _dispatch_once();
              }
            }
            else {
              unaff_x22 = *(int **)(_gLogObjects + 0xd8);
            }
            iVar4 = _OUTLINED_FUNCTION_12();
            if (iVar4 != 0) {
              uStack_98 = 0x400;
              uStack_96 = (undefined2)local_6c[0];
              uStack_94 = (undefined2)((uint)local_6c[0] >> 0x10);
              local_a0 = (uint)uVar2;
              local_9c = uVar3;
              auVar20 = _OUTLINED_FUNCTION_5();
              goto LAB_10018542c;
            }
          }
        }
        else if (uVar3 == 0) {
          uVar9 = _iAP2MsgGetParamValueData(lVar7);
          iVar4 = _iAP2MsgGetParamValueLen(lVar7);
          if (((uVar9 == 0) || (iVar4 == 0)) || (local_6c[0] != 0)) {
            if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_9(), in_NG != in_OV)) {
              _OUTLINED_FUNCTION_2();
              unaff_x22 = piVar8;
              if (!(bool)in_ZR) {
                _OUTLINED_FUNCTION_1();
                _dispatch_once();
              }
            }
            else {
              unaff_x22 = *(int **)(extraout_x8_01 + 0xd8);
            }
            iVar6 = _OUTLINED_FUNCTION_12();
            if (iVar6 != 0) {
              _OUTLINED_FUNCTION_16(uVar9 & 0xffff,uVar15);
              uStack_94 = 0x400;
              uStack_8e = 0x400;
              uStack_8c = (undefined2)extraout_w9_00;
              uStack_8a = (undefined2)((uint)extraout_w9_00 >> 0x10);
              local_92 = iVar4;
              auVar20 = _OUTLINED_FUNCTION_5();
              goto LAB_10018542c;
            }
          }
          else {
            if (local_f0 != 0) {
              _CFRelease();
            }
            local_f0 = _CFDataCreate(0,uVar9,iVar4);
          }
        }
        else {
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_9(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_2();
            piVar18 = piVar8;
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_1();
              _dispatch_once();
            }
          }
          else {
            piVar18 = *(int **)(extraout_x8 + 0xd8);
          }
          auVar20._8_8_ = piVar18;
          auVar20._0_8_ = 0x100000000;
          iVar4 = _os_log_type_enabled(piVar18,0);
          if (iVar4 != 0) {
            uVar5 = _iAP2MsgGetMsgID(param_2);
            uStack_98 = 0x400;
            uStack_96 = (undefined2)uVar5;
            uStack_94 = (undefined2)((uint)uVar5 >> 0x10);
            local_a0 = (uint)uVar2;
            local_9c = uVar3;
LAB_10018542c:
            __os_log_impl(auVar20._0_8_,auVar20._8_8_);
          }
        }
      }
      lVar7 = _iAP2MsgGetNextParam(param_2,0,lVar7);
    } while (lVar7 != 0);
    uVar9 = _OUTLINED_FUNCTION_14();
    if ((uVar9 & 1) == 0) {
      if (local_f0 == 0) goto LAB_1001854f0;
      unaff_w19 = uVar1;
      if (local_104 == 0) {
        uVar9 = _platform_auth_verifyPublicCertificate();
        if ((uVar9 & 1) == 0) {
          _OUTLINED_FUNCTION_3();
          unaff_w19 = 0;
        }
        else {
          iVar4 = _platform_auth_verifyCertificateSerialNumber(local_f0);
          if (iVar4 != 0) goto LAB_100185708;
          _OUTLINED_FUNCTION_3();
        }
      }
      else {
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_9(), in_NG != in_OV)) {
          _OUTLINED_FUNCTION_2();
          unaff_x22 = (int *)PTR___os_log_default_10022bbb0;
          if (!(bool)in_ZR) {
            _OUTLINED_FUNCTION_1();
            _dispatch_once();
            unaff_x22 = (int *)PTR___os_log_default_10022bbb0;
          }
        }
        else {
          unaff_x22 = *(int **)(extraout_x8_02 + 0xd8);
        }
        iVar4 = _OUTLINED_FUNCTION_12();
        if (iVar4 != 0) {
          local_a0 = local_a0 & 0xffff0000;
          _OUTLINED_FUNCTION_6();
          _OUTLINED_FUNCTION_15();
          __os_log_impl();
        }
        if (local_e8 == 0) {
          _OUTLINED_FUNCTION_3();
          local_e8 = 0;
        }
        else {
          uVar3 = _platform_auth_verifyBAACertificateChain(local_f0);
          if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_9(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_2();
            puVar16 = PTR___os_log_default_10022bbb0;
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_1();
              _dispatch_once();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(extraout_x8_04 + 0xd8);
          }
          iVar4 = _os_log_type_enabled(puVar16,0);
          if (iVar4 != 0) {
            local_a0 = uVar19;
            local_9c = uVar3;
            uVar15 = _OUTLINED_FUNCTION_6();
            __os_log_impl(uVar15,puVar16,0,"After verifying BAA cert chain, bCertValid = %d",
                          &local_a0,8);
            uVar3 = uVar3 & 1;
          }
          if (uVar3 == 0) {
            _OUTLINED_FUNCTION_3();
          }
          else {
            if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_9(), in_NG != in_OV)) {
              _OUTLINED_FUNCTION_2();
              puVar16 = PTR___os_log_default_10022bbb0;
              if (!(bool)in_ZR) {
                _OUTLINED_FUNCTION_1();
                _dispatch_once();
                puVar16 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar16 = *(undefined **)(extraout_x8_05 + 0xd8);
            }
            iVar4 = _os_log_type_enabled(puVar16,0);
            if (iVar4 != 0) {
              local_9c = 1;
              local_a0 = uVar19;
              uVar15 = _OUTLINED_FUNCTION_6();
              __os_log_impl(uVar15,puVar16,0,
                            "Not checking serial number revocation list for authType %d",&local_a0,8
                           );
            }
LAB_100185708:
            lVar7 = _platform_auth_createCertificateSerialNumber(local_f0);
            lVar10 = _platform_auth_createSerialNumberStringFromData();
            if (*(long *)(piVar8 + 0xc) == 0) {
LAB_100185738:
              lVar11 = _platform_auth_createRandomNonce(local_f0);
              if (lVar11 == 0) {
                unaff_x22 = (int *)0x0;
                puVar17 = (undefined8 *)0x0;
              }
              else {
                uVar15 = _CFRetain(local_f0);
                *(undefined8 *)(piVar8 + 4) = uVar15;
                if (*(long *)(piVar8 + 6) != 0) {
                  _CFRelease();
                  piVar8[6] = 0;
                  piVar8[7] = 0;
                }
                uVar15 = _CFRetain(lVar7);
                *(undefined8 *)(piVar8 + 6) = uVar15;
                if (*(long *)(piVar8 + 0xc) != 0) {
                  _CFRelease();
                  piVar8[0xc] = 0;
                  piVar8[0xd] = 0;
                }
                uVar15 = _CFRetain(lVar10);
                *(undefined8 *)(piVar8 + 0xc) = uVar15;
                *(long *)(piVar8 + 0xe) = lVar11;
                piVar8[8] = local_104;
                if (local_e8 != 0) {
                  uVar15 = _CFRetain(local_e8);
                  *(undefined8 *)(piVar8 + 10) = uVar15;
                  _CFRelease(local_e8);
                }
                puVar17 = (undefined8 *)_CFDataGetBytePtr(lVar11);
                unaff_x22 = (int *)_CFDataGetLength(lVar11);
                local_e8 = 0;
              }
              uVar14 = 1;
            }
            else {
              if (lVar10 != 0) {
                lVar11 = _CFStringCompare(*(long *)(piVar8 + 0xc),lVar10,1);
                if (lVar11 != 0) {
                  uVar15 = _logObjectForModule(0x1b);
                  iVar4 = _os_log_type_enabled(uVar15,0);
                  if (iVar4 != 0) {
                    uVar12 = _CFStringGetCStringPtr(*(undefined8 *)(piVar8 + 0xc),0x8000100);
                    local_88 = _CFStringGetCStringPtr(lVar10,0x8000100);
                    local_a0 = (uint)DAT_1001b30e0;
                    local_9c = 0x1d7808;
                    uStack_98 = 1;
                    uStack_96 = 0;
                    uStack_94 = 0x820;
                    local_92 = (int)uVar12;
                    uStack_8e = (undefined2)((ulong)uVar12 >> 0x20);
                    uStack_8c = (undefined2)((ulong)uVar12 >> 0x30);
                    uStack_8a = 0x820;
                    local_80 = 0x800;
                    local_7e = lVar11;
                    uVar12 = _OUTLINED_FUNCTION_6();
                    __os_log_impl(uVar12,uVar15,0,
                                  "%s Auth cert serial number data string mismatch: AuthSerNum:[%s] != CertSerNum:[%s], serNumCompareStatus:%02lX"
                                  ,&local_a0,0x2a);
                  }
                  uVar15 = _logObjectForModule(0x1b);
                  iVar4 = _os_log_type_enabled(uVar15,0);
                  if (iVar4 != 0) {
                    local_a0 = local_a0 & 0xffff0000;
                    _OUTLINED_FUNCTION_6();
                    _OUTLINED_FUNCTION_15();
                    __os_log_impl();
                  }
                  __cleariAP2AuthState(param_1);
                }
                goto LAB_100185738;
              }
              unaff_x22 = (int *)_logObjectForModule(0x1b);
              iVar4 = _os_log_type_enabled(unaff_x22,0x10);
              if (iVar4 != 0) {
                uVar15 = _OUTLINED_FUNCTION_4(DAT_1001b3090);
                _OUTLINED_FUNCTION_19(uVar15,unaff_x22);
              }
              _OUTLINED_FUNCTION_3();
            }
            if (lVar7 != 0) {
              _CFRelease(lVar7);
            }
            unaff_w19 = uVar14;
            if (lVar10 != 0) {
              _CFRelease(lVar10);
            }
          }
        }
      }
      _CFRelease(local_f0);
      goto LAB_100185844;
    }
LAB_1001854a8:
    if (((_gLogObjects == 0) || (_OUTLINED_FUNCTION_9(), in_NG != in_OV)) &&
       (_OUTLINED_FUNCTION_2(), !(bool)in_ZR)) {
      _OUTLINED_FUNCTION_1();
      _dispatch_once();
    }
    iVar4 = _OUTLINED_FUNCTION_12();
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_16(param_1[1],DAT_1001b3088);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_15();
      __os_log_impl();
    }
    if (local_f0 != 0) {
      _CFRelease();
    }
  }
  uVar15 = 1;
LAB_1001858b0:
  if (local_e8 != 0) {
    _CFRelease();
  }
  return uVar15;
}


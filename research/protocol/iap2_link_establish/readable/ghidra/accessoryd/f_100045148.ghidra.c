/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100045148
 * original code SHA256: 745df27edd4deae10cb40ced27bd941d3e896420ef4d20f07baabce1422a855b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x26 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x8 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */

ulong _mfi4Auth_protocol_handle_AuthSetup(long param_1,long param_2,undefined8 param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  int iVar4;
  uint uVar5;
  u_int32_t uVar6;
  uint uVar7;
  long lVar8;
  ulong uVar9;
  undefined8 uVar10;
  undefined8 extraout_x0;
  undefined1 *puVar11;
  long lVar12;
  ID IVar13;
  undefined8 *data;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined *puVar16;
  undefined2 *puVar17;
  undefined8 uVar18;
  char local_85;
  uint local_84;
  uint local_80;
  uint local_7c;
  undefined2 uStack_78;
  ushort uStack_76;
  undefined2 uStack_74;
  long local_68;
  
  local_84 = 1;
  if (param_1 == 0) {
    uVar10 = _logObjectForModule();
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_54(uVar10);
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    uVar10 = _logObjectForModule();
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_53(uVar10);
    }
  }
  else if (param_2 == 0) {
    uVar10 = _logObjectForModule();
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_52(uVar10);
    }
  }
  else {
    local_85 = '\0';
    puVar17 = (undefined2 *)(param_1 + 0xd1);
    *puVar17 = 0;
    *(undefined1 *)(param_1 + 0xd3) = 0;
    *(undefined8 *)(param_1 + 0xd8) = 0;
    lVar8 = _iAP2MsgGetFirstParam(param_2,0);
    uVar7 = 0;
    do {
      if (lVar8 == 0) {
        if (((uVar7 ^ 0xffffffff) & 7) != 0) {
          local_84 = 0xffffffff;
          uVar10 = _logObjectForModule();
          iVar4 = _os_log_type_enabled(uVar10,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_14(uVar7,uVar10);
          }
          goto LAB_10004586c;
        }
        uVar10 = 0;
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar16 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
            puVar16 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar4 = _os_log_type_enabled(puVar16,uVar10,0);
        if (iVar4 != 0) {
          local_7c = *(uint *)(param_1 + 0xe0);
          local_80 = (uint)DAT_1001b30b0;
          __os_log_impl(0x100000000,uVar10,0,"handle_AuthSetup: authType:%x",&local_80,8);
        }
        iVar4 = *(int *)(param_1 + 0xe0);
        if (iVar4 == 0) {
          *(undefined8 *)(param_1 + 0x2c8) = 0;
          *(undefined8 *)(param_1 + 0x2c0) = 0;
          _arc4random_buf((void *)(param_1 + 0x2c0),0x10);
          uVar10 = extraout_x0;
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar16 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar4 = _os_log_type_enabled(puVar16);
          if (iVar4 != 0) {
            local_80 = local_80 & 0xffff0000;
            __os_log_impl(0x100000000,uVar10,0,
                          "handle_AuthSetup: initMessage_RequestAuthChallengeResponse",&local_80,2);
          }
          uVar9 = _mfi4Auth_protocol_initMessage_RequestAuthChallengeResponse(param_1,param_3);
          local_84 = (uint)uVar9;
          if (local_84 == 0) {
            return uVar9;
          }
          uVar10 = _logObjectForModule();
          iVar4 = _os_log_type_enabled(uVar10,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_51(uVar10);
          }
        }
        else {
          if (iVar4 != 2) {
            if (iVar4 == 1) {
              *(undefined1 *)(param_1 + 0x176) = 0;
              *(undefined8 *)(param_1 + 0x16e) = 0;
              *(undefined8 *)(param_1 + 0x166) = 0;
              *(undefined8 *)(param_1 + 0x15e) = 0;
              *(undefined8 *)(param_1 + 0x156) = 0;
              uVar7 = 0;
              while (*(short *)(param_1 + 0x152) = (short)uVar7,
                    (uVar7 & 0xffff) == 0xffff || (uVar7 & 0xffff) == 0) {
                uVar7 = _arc4random();
              }
              uVar9 = _mfi4Auth_protocol_initMessage_RequestAuthStart(param_1,param_3);
              local_84 = (uint)uVar9;
              if (local_84 == 0) {
                return uVar9;
              }
              uVar10 = _logObjectForModule();
              iVar4 = _os_log_type_enabled(uVar10,0x10);
              if (iVar4 != 0) {
                _mfi4Auth_protocol_handle_AuthSetup_cold_49(uVar10);
              }
              goto LAB_10004586c;
            }
            goto LAB_10004540c;
          }
          if (((uVar7 ^ 0xffffffff) & 0x18) == 0) goto LAB_100045454;
          local_84 = 0xffffffff;
          uVar10 = _logObjectForModule(0);
          iVar4 = _os_log_type_enabled(uVar10,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_16(uVar10);
          }
        }
        goto LAB_10004586c;
      }
      iVar4 = _iAP2MsgGetParamID(lVar8);
      if (iVar4 < 3) {
        if (iVar4 == 0) {
          uVar10 = _iAP2MsgGetDataAsU8(lVar8,&local_84);
          *(undefined1 *)(param_1 + 0xd0) = (char)uVar10;
          if (local_84 != 0) {
            uVar10 = _logObjectForModule();
            iVar4 = _os_log_type_enabled(uVar10,0x10);
            if (iVar4 != 0) {
              _mfi4Auth_protocol_handle_AuthSetup_cold_10(uVar10);
            }
            goto LAB_10004586c;
          }
          if (((uint)uVar10 < (uint)*(byte *)(param_1 + 0xac)) ||
             ((uint)*(byte *)(param_1 + 0xad) < (uint)uVar10)) {
            local_84 = 0xffffffff;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar16 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar16 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar4 = _os_log_type_enabled(puVar16,uVar10,0x10);
            if (iVar4 != 0) {
              _mfi4Auth_protocol_handle_AuthSetup_cold_12((undefined1 *)(param_1 + 0xd0),uVar10);
            }
            goto LAB_10004586c;
          }
          uVar7 = uVar7 | 1;
        }
        else if (iVar4 == 1) {
          uVar5 = _iAP2MsgGetDataAsU8(lVar8,&local_84);
          *(uint *)(param_1 + 0xe0) = uVar5;
          if (local_84 != 0) {
            uVar10 = _logObjectForModule();
            iVar4 = _os_log_type_enabled(uVar10,0x10);
            if (iVar4 != 0) {
              _mfi4Auth_protocol_handle_AuthSetup_cold_8(uVar10);
            }
            goto LAB_10004586c;
          }
          if (3 < uVar5) {
            local_84 = 0xffffffff;
            uVar10 = _logObjectForModule();
            iVar4 = _os_log_type_enabled(uVar10,0x10);
            if (iVar4 != 0) {
              _mfi4Auth_protocol_handle_AuthSetup_cold_9(param_1 + 0xe0,uVar10);
            }
            goto LAB_10004586c;
          }
          uVar7 = uVar7 | 2;
        }
        else {
          if (iVar4 != 2) goto LAB_100045308;
          uVar9 = _iAP2MsgGetDataAsU8(lVar8,&local_84);
          if (local_84 != 0) {
            uVar10 = _logObjectForModule();
            iVar4 = _os_log_type_enabled(uVar10,0x10);
            if (iVar4 != 0) {
              _mfi4Auth_protocol_handle_AuthSetup_cold_6(uVar10);
            }
            goto LAB_10004586c;
          }
          if ((uVar9 & 0xfffffffd) != 0) {
            local_84 = 0xffffffff;
            uVar10 = _logObjectForModule();
            iVar4 = _os_log_type_enabled(uVar10,0x10);
            if (iVar4 != 0) {
              _mfi4Auth_protocol_handle_AuthSetup_cold_7(uVar10);
            }
            goto LAB_10004586c;
          }
          uVar7 = uVar7 | 4;
        }
      }
      else if (iVar4 == 3) {
        uVar3 = _iAP2MsgGetDataAsU16(lVar8,&local_84);
        *(undefined2 *)(param_1 + 0x152) = uVar3;
        if (local_84 != 0) {
          uVar10 = _logObjectForModule();
          iVar4 = _os_log_type_enabled(uVar10,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_5(uVar10);
          }
          goto LAB_10004586c;
        }
        uVar7 = uVar7 | 8;
      }
      else if (iVar4 == 4) {
        uVar10 = _iAP2MsgGetDataAsArrayU8(lVar8,&local_84,param_1 + 0x156,0x21);
        if (local_84 != 0) {
          uVar10 = _logObjectForModule();
          iVar4 = _os_log_type_enabled(uVar10,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_3(uVar10);
          }
          goto LAB_10004586c;
        }
        if ((int)uVar10 != 0x21) {
          local_84 = 0xffffffff;
          uVar14 = _logObjectForModule();
          iVar4 = _os_log_type_enabled(uVar14,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_4(uVar10,uVar14);
          }
          goto LAB_10004586c;
        }
        uVar7 = uVar7 | 0x10;
      }
      else if (iVar4 == 5) {
        uVar2 = _iAP2MsgGetDataAsU8(lVar8,&local_84);
        if (local_84 != 0) {
          uVar10 = _logObjectForModule();
          iVar4 = _os_log_type_enabled(uVar10,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_1(uVar10);
          }
          goto LAB_10004586c;
        }
        if (2 < *(ulong *)(param_1 + 0xd8)) {
          local_84 = 0xffffffff;
          uVar10 = _logObjectForModule();
          iVar4 = _os_log_type_enabled(uVar10,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_2(uVar10);
          }
          goto LAB_10004586c;
        }
        *(undefined1 *)((long)puVar17 + *(ulong *)(param_1 + 0xd8)) = uVar2;
        *(long *)(param_1 + 0xd8) = *(long *)(param_1 + 0xd8) + 1;
        uVar7 = uVar7 | 0x20;
      }
LAB_100045308:
      lVar8 = _iAP2MsgGetNextParamWithError(param_2,0,lVar8,&local_85);
    } while (local_85 != '\x01');
    local_84 = 0xffffffff;
    uVar10 = _logObjectForModule();
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_13(uVar10);
    }
  }
  goto LAB_10004586c;
LAB_100045454:
  do {
    uVar6 = _arc4random();
    *(short *)(param_1 + 0x154) = (short)uVar6;
    uVar7 = (uint)*(ushort *)(param_1 + 0x152) ^ uVar6 & 0xffff;
    *(short *)(param_1 + 0x150) = (short)uVar7;
  } while ((uint)*(ushort *)(param_1 + 0x152) == (uVar6 & 0xffff) || uVar7 == 0xffff);
  lVar8 = *(long *)(param_1 + 0xb8) + *(long *)(param_1 + 0xd8) + *(long *)(param_1 + 200);
  puVar11 = (undefined1 *)_malloc_type_malloc(lVar8 + 3,0xb995e67c);
  if (puVar11 == (undefined1 *)0x0) {
    local_84 = 0xffffffff;
    uVar10 = _logObjectForModule();
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_48(uVar10);
    }
    goto LAB_10004586c;
  }
  *puVar11 = *(undefined1 *)(param_1 + 0xad);
  _memcpy(puVar11 + 1,(void *)(param_1 + 0xae),*(size_t *)(param_1 + 0xb8));
  _memcpy(puVar11 + *(long *)(param_1 + 0xb8) + 1,(void *)(param_1 + 0xc0),
          *(size_t *)(param_1 + 200));
  puVar11[*(long *)(param_1 + 0xb8) + *(long *)(param_1 + 200) + 1] =
       *(undefined1 *)(param_1 + 0xd0);
  puVar11[*(long *)(param_1 + 0xb8) + *(long *)(param_1 + 200) + 2] =
       (char)*(undefined4 *)(param_1 + 0xe0);
  _memcpy(puVar11 + *(long *)(param_1 + 0xb8) + *(long *)(param_1 + 200) + 3,puVar17,
          *(size_t *)(param_1 + 0xd8));
  uVar14 = _ccsigma_mfi_info();
  local_68 = 0x21;
  uVar10 = uVar14;
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
    puVar16 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
      puVar16 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
  }
  iVar4 = _os_log_type_enabled(puVar16,uVar10,0);
  if (iVar4 != 0) {
    local_80 = local_80 & 0xffff0000;
    __os_log_impl(0x100000000,uVar10,0,"mfi4Auth_protocol_initSigmaContext",&local_80,2);
  }
  if (*(char *)(param_1 + 0x1e) == '\x01') {
    uVar10 = _logObjectForModule(0);
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_45(uVar10);
    }
    goto LAB_1000463c0;
  }
  if ((*(byte *)(param_1 + 0x2d) & 1) == 0) {
    IVar13 = ACCUserDefaults::sharedDefaults((ID)PTR_ACCUserDefaults_10022af48);
    IVar13 = objc_stub::boolForKey_(IVar13,_ACCUserDefaultsKey_AllowMFi4DevCertsOnProdDevice);
    uVar10 = _MFAAIsDevelopmentHW(0);
    uVar7 = (uint)uVar10 | (uint)IVar13;
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
      puVar16 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
        puVar16 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
    }
    iVar4 = _os_log_type_enabled(puVar16,uVar10,0);
    if (iVar4 != 0) {
      uStack_76 = (ushort)uVar7 & 1;
      local_80 = (uint)DAT_1001b3108;
      local_7c = (uint)*(byte *)(param_1 + 0x90);
      uStack_78 = 0x400;
      uStack_74 = 0;
      __os_log_impl(0x100000000,uVar10,0,
                    "mfi4Auth_protocol_initSigmaContext: authSession->authStatus:%x devIdentityAllowed:%d"
                    ,&local_80,0xe);
    }
    uVar10 = 0;
    bVar1 = *(byte *)(param_1 + 0x90);
    if ((bVar1 & 1) == 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
        puVar16 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
          puVar16 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
      }
      iVar4 = _os_log_type_enabled(puVar16,uVar10,0);
      if (iVar4 != 0) {
        local_80 = local_80 & 0xffff0000;
        __os_log_impl(0x100000000,uVar10,0,"mfi4Auth_protocol_initSigmaContext: try prod identity",
                      &local_80,2);
      }
      *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xfc | 1;
      uVar10 = _mfi4Auth_protocol_initIdentity(param_1,1);
      if ((int)uVar10 == 0) goto LAB_10004564c;
      uVar18 = uVar10;
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
        puVar16 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          uVar18 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
          puVar16 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
      }
      iVar4 = _os_log_type_enabled(puVar16,uVar18,0x10);
      if (iVar4 != 0) {
        _mfi4Auth_protocol_handle_AuthSetup_cold_21(uVar10,uVar18);
      }
      *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xfc;
    }
    uVar10 = 0;
    if ((uVar7 & 1) != 0 && (bVar1 & 4) == 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x3b) {
        puVar16 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
          puVar16 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
      }
      iVar4 = _os_log_type_enabled(puVar16,uVar10,0);
      if (iVar4 != 0) {
        local_80 = local_80 & 0xffff0000;
        __os_log_impl(0x100000000,uVar10,0,"mfi4Auth_protocol_initSigmaContext: try dev identity",
                      &local_80,2);
      }
      *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xf7 | 4;
      iVar4 = _mfi4Auth_protocol_initIdentity(param_1,0);
      if (iVar4 != 0) {
        uVar10 = _logObjectForModule();
        iVar4 = _os_log_type_enabled(uVar10,0x10);
        if (iVar4 != 0) {
          _mfi4Auth_protocol_handle_AuthSetup_cold_25(uVar10);
        }
        goto LAB_1000463c0;
      }
      goto LAB_10004564c;
    }
    if (_gLogObjects == 0 || _gNumLogObjects < 0x3b) {
      puVar16 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
        puVar16 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
    }
    iVar4 = _os_log_type_enabled(puVar16,uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_23(uVar10);
    }
    uVar10 = 0xfffffffe;
    goto LAB_100045f38;
  }
LAB_10004564c:
  lVar12 = _malloc_type_malloc(0x2f0,0x10e0040123a03ea);
  *(long *)(param_1 + 0x98) = lVar12;
  if (lVar12 == 0) {
    uVar10 = _logObjectForModule();
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_44(uVar10);
    }
LAB_1000463c0:
    uVar10 = 0xffffffff;
LAB_100045f38:
    local_84 = (uint)uVar10;
  }
  else {
    lVar12 = _ccrng(0);
    *(long *)(param_1 + 0xa0) = lVar12;
    if (lVar12 == 0) {
      uVar10 = _logObjectForModule();
      iVar4 = _os_log_type_enabled(uVar10,0x10);
      if (iVar4 != 0) {
        _mfi4Auth_protocol_handle_AuthSetup_cold_43(uVar10);
      }
      goto LAB_1000463c0;
    }
    uVar18 = *(undefined8 *)(param_1 + 0x98);
    uVar10 = _ccsigma_init(uVar14,uVar18,1,lVar12);
    if ((int)uVar10 != 0) {
      uVar14 = _logObjectForModule();
      iVar4 = _os_log_type_enabled(uVar14,0x10);
      if (iVar4 != 0) {
        _mfi4Auth_protocol_handle_AuthSetup_cold_26(uVar14);
      }
      goto LAB_100045f38;
    }
    if ((*(char *)(param_1 + 0x2d) != '\x01') || (*(long *)(param_1 + 0x210) == 0)) {
      if (*(long *)(param_1 + 0x200) == 0) {
        if (*(long *)(param_1 + 0x210) == 0) {
          if (_gLogObjects == 0 || _gNumLogObjects < 0x3b) {
            puVar16 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar4 = _os_log_type_enabled(puVar16,uVar10,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_32(uVar10);
          }
        }
        else {
          if (_gLogObjects == 0 || _gNumLogObjects < 0x3b) {
            puVar16 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar4 = _os_log_type_enabled(puVar16,uVar10,0);
          if (iVar4 != 0) {
            local_80 = local_80 & 0xffff0000;
            __os_log_impl(0x100000000,uVar10,0,"initSigmaContext: ccsigma_set_signing_function",
                          &local_80,2);
          }
          iVar4 = _ccsigma_set_signing_function
                            (uVar18,_seckey_sign,*(undefined8 *)(param_1 + 0x210));
          if (iVar4 != 0) {
            uVar10 = _logObjectForModule();
            iVar4 = _os_log_type_enabled(uVar10,0x10);
            if (iVar4 != 0) {
              _mfi4Auth_protocol_handle_AuthSetup_cold_30(uVar10);
            }
            uVar10 = 0;
            goto LAB_100045f38;
          }
        }
      }
      else {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar16 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
            puVar16 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar4 = _os_log_type_enabled(puVar16,uVar10,0);
        if (iVar4 != 0) {
          local_80 = local_80 & 0xffff0000;
          __os_log_impl(0x100000000,uVar10,0,"initSigmaContext: ccsigma_import_signing_key",
                        &local_80,2);
        }
        uVar10 = _ccsigma_import_signing_key
                           (uVar18,*(undefined8 *)(param_1 + 0x208),*(undefined8 *)(param_1 + 0x200)
                           );
        if ((int)uVar10 != 0) {
          uVar14 = _logObjectForModule();
          iVar4 = _os_log_type_enabled(uVar14,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_28(uVar14);
          }
          goto LAB_100045f38;
        }
      }
    }
    uVar10 = _ccsigma_import_peer_key_share(uVar18,0x21,param_1 + 0x156);
    if ((int)uVar10 != 0) {
      uVar14 = _logObjectForModule();
      iVar4 = _os_log_type_enabled(uVar14,0x10);
      if (iVar4 != 0) {
        _mfi4Auth_protocol_handle_AuthSetup_cold_33(uVar14);
      }
      goto LAB_100045f38;
    }
    uVar10 = _ccsigma_derive_session_keys(uVar18,lVar8 + 3,puVar11,*(undefined8 *)(param_1 + 0xa0));
    if ((int)uVar10 != 0) {
      uVar14 = _logObjectForModule();
      iVar4 = _os_log_type_enabled(uVar14,0x10);
      if (iVar4 != 0) {
        _mfi4Auth_protocol_handle_AuthSetup_cold_34(uVar14);
      }
      goto LAB_100045f38;
    }
    data = (undefined8 *)_malloc_type_malloc(*(long *)(param_1 + 0x1e8) + 0x10,0x1000040451b5be8);
    if (data != (undefined8 *)0x0) {
      _arc4random_buf((undefined8 *)(param_1 + 0x198),0x10);
      uVar10 = *(undefined8 *)(param_1 + 0x198);
      data[1] = *(undefined8 *)(param_1 + 0x1a0);
      *data = uVar10;
      _memcpy(data + 2,*(void **)(param_1 + 0x1e0),*(size_t *)(param_1 + 0x1e8));
      _CC_SHA256(data,*(int *)(param_1 + 0x1e8) + 0x10,(uchar *)(param_1 + 0x1bc));
      NSData::dataWithBytes_length_((ID)PTR__OBJC_CLASS___NSData_10022bc38,param_1 + 0x1bc,0x20);
      uVar14 = __dumpSimpleHex();
      uVar10 = uVar14;
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
        puVar16 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          uVar10 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
          puVar16 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
      }
      iVar4 = _os_log_type_enabled(puVar16,uVar10,0);
      if (iVar4 != 0) {
        local_80 = (uint)DAT_1001b3088;
        local_7c = (uint)uVar14;
        uStack_78 = (undefined2)((ulong)uVar14 >> 0x20);
        uStack_76 = (ushort)((ulong)uVar14 >> 0x30);
        __os_log_impl(0x100000000,uVar10,0,"initSigmaContext: cert_hash_resp: %@",&local_80,0xc);
      }
      uVar10 = _ccsigma_export_key_share(uVar18,&local_68,param_1 + 0x177);
      if ((int)uVar10 == 0) {
        if (local_68 == 0x21) {
          NSData::dataWithBytes_length_((ID)PTR__OBJC_CLASS___NSData_10022bc38,puVar11,lVar8 + 3);
          uVar14 = __dumpSimpleHex();
          uVar15 = 0;
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar16 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              uVar15 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar4 = _os_log_type_enabled(puVar16,uVar15,0);
          if (iVar4 != 0) {
            local_80 = (uint)DAT_1001b3088;
            local_7c = (uint)uVar14;
            uStack_78 = (undefined2)((ulong)uVar14 >> 0x20);
            uStack_76 = (ushort)((ulong)uVar14 >> 0x30);
            __os_log_impl(0x100000000,uVar15,0,"negoTrans %@",&local_80,0xc);
          }
          NSData::dataWithBytes_length_((ID)PTR__OBJC_CLASS___NSData_10022bc38,param_1 + 0x156,0x21)
          ;
          uVar14 = __dumpSimpleHex();
          uVar15 = 0;
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar16 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              uVar15 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar4 = _os_log_type_enabled(puVar16,uVar15,0);
          if (iVar4 != 0) {
            local_80 = (uint)DAT_1001b3088;
            local_7c = (uint)uVar14;
            uStack_78 = (undefined2)((ulong)uVar14 >> 0x20);
            uStack_76 = (ushort)((ulong)uVar14 >> 0x30);
            __os_log_impl(0x100000000,uVar15,0,"dhPublicKeyInitiator %@",&local_80,0xc);
          }
          NSData::dataWithBytes_length_((ID)PTR__OBJC_CLASS___NSData_10022bc38,param_1 + 0x177,0x21)
          ;
          uVar14 = __dumpSimpleHex();
          uVar15 = 0;
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar16 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              uVar15 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar4 = _os_log_type_enabled(puVar16,uVar15,0);
          if (iVar4 != 0) {
            local_80 = (uint)DAT_1001b3088;
            local_7c = (uint)uVar14;
            uStack_78 = (undefined2)((ulong)uVar14 >> 0x20);
            uStack_76 = (ushort)((ulong)uVar14 >> 0x30);
            __os_log_impl(0x100000000,uVar15,0,"dhPublicKeyResponder %@",&local_80,0xc);
          }
          _printSessionKeys(uVar18,0);
        }
        else {
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar16 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar16 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar4 = _os_log_type_enabled(puVar16,0x10);
          if (iVar4 != 0) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_39(puVar16);
          }
        }
      }
      else {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar16 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            _mfi4Auth_protocol_handle_AuthSetup_cold_15();
            puVar16 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar16 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar4 = _os_log_type_enabled(puVar16,0x10);
        if (iVar4 != 0) {
          _mfi4Auth_protocol_handle_AuthSetup_cold_37(puVar16);
        }
      }
      _free(data);
      goto LAB_100045f38;
    }
    local_84 = 0xffffffff;
  }
  _free(puVar11);
  if (local_84 == 0) {
    uVar9 = _mfi4Auth_protocol_initMessage_AuthStart(param_1);
    local_84 = (uint)uVar9;
    if (local_84 == 0) {
      return uVar9;
    }
    uVar10 = _logObjectForModule();
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_47(uVar10);
    }
  }
  else {
    uVar10 = _logObjectForModule();
    iVar4 = _os_log_type_enabled(uVar10,0x10);
    if (iVar4 != 0) {
      _mfi4Auth_protocol_handle_AuthSetup_cold_46(uVar10);
    }
  }
LAB_10004586c:
  if (local_84 == 0) {
LAB_10004540c:
    uVar9 = 0;
  }
  else {
    _mfi4Auth_protocol_handle_AuthState(param_1,1);
    uVar9 = (ulong)local_84;
  }
  return uVar9;
}


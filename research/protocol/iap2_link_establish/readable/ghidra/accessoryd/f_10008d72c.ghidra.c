/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008d72c
 * original code SHA256: d1cc8c6c051fa5240c8cfacead92cad745fb00133ff5d46a95df0255715479fd
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x28 replaced with injection: _objc_release_fixup */

ushort __acc_auth_protocol_validateCertificateChain(ulong param_1,long param_2)

{
  uint *puVar1;
  long *plVar2;
  undefined8 uVar3;
  int iVar4;
  ulong uVar5;
  ID IVar6;
  ID IVar7;
  undefined8 uVar8;
  ID IVar9;
  ID IVar10;
  ID IVar11;
  undefined8 uVar12;
  cfstringStruct *pcVar13;
  undefined *puVar14;
  ushort uVar15;
  undefined8 uVar16;
  long lVar17;
  undefined8 local_98;
  undefined4 local_90;
  undefined4 local_8c;
  undefined2 uStack_88;
  ushort uStack_86;
  undefined2 uStack_84;
  undefined2 local_82;
  undefined2 uStack_80;
  undefined2 uStack_7e;
  undefined4 uStack_7c;
  undefined2 local_78;
  uint local_76;
  undefined2 local_72;
  undefined4 local_70;
  undefined2 local_6c;
  undefined4 local_6a;
  undefined2 local_66;
  uint local_64;
  
  uVar15 = 1;
  uVar5 = param_1;
  if ((param_1 != 0) && (param_2 != 0)) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
      puVar14 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        uVar5 = _logObjectForModule_cold_1();
        puVar14 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar14 = *(undefined **)(_gLogObjects + 0x1c8);
    }
    iVar4 = _os_log_type_enabled(puVar14,uVar5,2);
    if (iVar4 != 0) {
      __acc_auth_protocol_validateCertificateChain_cold_2(param_2,uVar5);
    }
    iVar4 = _platform_systemInfo_isInternalBuild(0);
    if ((iVar4 == 0) ||
       (uVar5 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ACCAuthProtocolPretendAuth),
       (uVar5 & 1) == 0)) {
      IVar6 = _objc_alloc(PTR__OBJC_CLASS___NSMutableArray_10022bc60);
      puVar1 = (uint *)(param_2 + 0x160);
      IVar6 = NSMutableArray::initWithCapacity_(IVar6,(ulong)*(uint *)(param_2 + 0x160));
      if (IVar6 == 0) {
        uVar12 = 0;
        if (_gLogObjects == 0 || _gNumLogObjects < 0x3a) {
          puVar14 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar12 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
            puVar14 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar14 = *(undefined **)(_gLogObjects + 0x1c8);
        }
        iVar4 = _os_log_type_enabled(puVar14,uVar12,0x10);
        if (iVar4 != 0) {
          __acc_auth_protocol_validateCertificateChain_cold_10(puVar1,uVar12);
        }
LAB_10008dd6c:
        uVar5 = 0;
        uVar15 = 0xc;
      }
      else {
        IVar7 = IVar6;
        if (_gLogObjects == 0 || _gNumLogObjects < 0x3a) {
          puVar14 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            IVar7 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
            puVar14 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar14 = *(undefined **)(_gLogObjects + 0x1c8);
        }
        iVar4 = _os_log_type_enabled(puVar14,IVar7,2);
        if (iVar4 != 0) {
          __acc_auth_protocol_validateCertificateChain_cold_4(puVar1,IVar7);
        }
        uVar3 = DAT_1001b3150;
        uVar12 = DAT_1001b3128;
        if (*puVar1 != 0) {
          uVar5 = 0;
          do {
            uVar8 = 0;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
              puVar14 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar8 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
                puVar14 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar14 = *(undefined **)(_gLogObjects + 0x1c8);
            }
            iVar4 = _os_log_type_enabled(puVar14,uVar8,2);
            if (iVar4 != 0) {
              lVar17 = param_2 + uVar5 * 0x58;
              local_70 = *(undefined4 *)(lVar17 + 0x38);
              local_6a = *(undefined4 *)(lVar17 + 8);
              local_90 = (undefined4)uVar12;
              local_8c = 0x1d1ffb;
              uStack_88 = 1;
              uStack_86 = 0;
              uStack_84 = 0x400;
              local_82 = 0x7f1;
              uStack_80 = 0;
              uStack_7e = 0x400;
              local_78 = 0x400;
              local_76 = (uint)*(byte *)(lVar17 + 0x28);
              local_72 = 0x400;
              local_6c = 0x400;
              local_66 = 0x400;
              local_64 = (uint)*(byte *)(lVar17 + 0x18);
              uStack_7c = (int)uVar5;
              __os_log_debug_impl(0x100000000,uVar8,2,
                                  "[AccAuth] %s:%d [%d] privacyPrefixLen %u, compressedCertLen %u, certificateDataLen %u, certificateHashLen %u \n"
                                  ,&local_90,0x30);
            }
            plVar2 = (long *)(param_2 + uVar5 * 0x58);
            if (*(uint *)(plVar2 + 1) == 0) goto LAB_10008dd5c;
            lVar17 = **(long **)(param_1 + 0x578);
            if (lVar17 != 0) {
              if ((plVar2[6] == 0) || ((int)plVar2[7] == 0)) {
                if (*(uint *)(plVar2 + 1) < 0x191 && *plVar2 != 0) {
                  if (uVar5 == 0) {
                    pcVar13 = &cf_MFi40Accessory_Compressed_Certificate;
                  }
                  else {
                    pcVar13 = &cf_MFi40Accessory_Compressed_Intermediate__d;
                  }
                }
                else if (uVar5 == 0) {
                  pcVar13 = &cf_Accessory_Certificate;
                }
                else {
                  pcVar13 = &cf_Accessory_Intermediate__d;
                }
                IVar7 = NSString::stringWithFormat_
                                  ((ID)PTR__OBJC_CLASS___NSString_10022bb48,pcVar13);
                uVar16 = *(undefined8 *)(lVar17 + 0x10);
                uVar8 = _acc_endpoint2_getTransportTypeString(lVar17);
                IVar9 = NSData::dataWithBytes_length_
                                  ((ID)PTR__OBJC_CLASS___NSData_10022bc38,*plVar2,
                                   (ulong)*(uint *)(plVar2 + 1));
                _acc_platform_packetLogging_logDataForEndpoint
                          (uVar16,uVar8,IVar7,&cf_AccAuth,IVar9,1);
              }
              else {
                if (uVar5 == 0) {
                  pcVar13 = &cf_MFi40Accessory_Compressed_Certificate;
                }
                else {
                  pcVar13 = &cf_MFi40Accessory_Compressed_Intermediate__d;
                }
                IVar7 = NSString::stringWithFormat_
                                  ((ID)PTR__OBJC_CLASS___NSString_10022bb48,pcVar13);
                uVar16 = *(undefined8 *)(lVar17 + 0x10);
                uVar8 = _acc_endpoint2_getTransportTypeString(lVar17);
                IVar9 = NSData::dataWithBytes_length_
                                  ((ID)PTR__OBJC_CLASS___NSData_10022bc38,plVar2[6],
                                   (ulong)*(uint *)(plVar2 + 7));
                _acc_platform_packetLogging_logDataForEndpoint
                          (uVar16,uVar8,IVar7,&cf_AccAuth,IVar9,1);
                if ((*plVar2 != 0) && (400 < *(uint *)(plVar2 + 1))) {
                  if (uVar5 == 0) {
                    pcVar13 = &cf_MFi40Accessory_Certificate;
                  }
                  else {
                    pcVar13 = &cf_MFi40Accessory_Intermediate__d;
                  }
                  IVar7 = NSString::stringWithFormat_
                                    ((ID)PTR__OBJC_CLASS___NSString_10022bb48,pcVar13);
                  uVar16 = *(undefined8 *)(lVar17 + 0x10);
                  uVar8 = _acc_endpoint2_getTransportTypeString(lVar17);
                  IVar9 = NSData::dataWithBytes_length_
                                    ((ID)PTR__OBJC_CLASS___NSData_10022bc38,*plVar2,
                                     (ulong)*(uint *)(plVar2 + 1));
                  _acc_platform_packetLogging_logDataForEndpoint
                            (uVar16,uVar8,IVar7,&cf_AccAuth,IVar9,1);
                }
              }
            }
            IVar7 = NSData::dataWithBytes_length_
                              ((ID)PTR__OBJC_CLASS___NSData_10022bc38,*plVar2,
                               (ulong)*(uint *)(plVar2 + 1));
            if (IVar7 == 0) goto LAB_10008dd6c;
            IVar9 = IVar7;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
              puVar14 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                IVar9 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
                puVar14 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar14 = *(undefined **)(_gLogObjects + 0x1c8);
            }
            iVar4 = _os_log_type_enabled(puVar14,IVar9,1);
            if (iVar4 != 0) {
              IVar10 = NSData::length(IVar7);
              IVar11 = _objc_retainAutorelease(IVar7);
              IVar11 = objc_stub::bytes(IVar11);
              local_90 = (undefined4)uVar3;
              uStack_88 = 0x410;
              uStack_86 = (ushort)IVar10;
              uStack_84 = (undefined2)(IVar10 >> 0x10);
              local_82 = 0x832;
              uStack_80 = (undefined2)IVar11;
              uStack_7e = (undefined2)(IVar11 >> 0x10);
              uStack_7c = (undefined4)(IVar11 >> 0x20);
              local_8c = (int)uVar5;
              __os_log_impl(0x100000000,IVar9,1,
                            "[AccAuth] _validateCertificateChain: [%d] certificateData: \n<%{public,coreacc:bytes}.*P>"
                            ,&local_90,0x18);
            }
            NSMutableArray::addObject_(IVar6,IVar7);
            uVar5 = uVar5 + 1;
          } while (uVar5 < *puVar1);
        }
        uVar12 = 0;
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
          puVar14 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar12 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
            puVar14 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar14 = *(undefined **)(_gLogObjects + 0x1c8);
        }
        iVar4 = _os_log_type_enabled(puVar14,uVar12,2);
        if (iVar4 != 0) {
          __acc_auth_protocol_validateCertificateChain_cold_8(IVar6,uVar12);
        }
        IVar7 = NSMutableArray::count(IVar6);
        if (IVar7 == 0) {
LAB_10008dd5c:
          uVar5 = 0;
          uVar15 = 2;
        }
        else {
          IVar7 = MFAACertificateManager::sharedManager
                            ((ID)PTR__OBJC_CLASS___MFAACertificateManager_10022b1c8);
          local_98 = 0;
          IVar6 = MFAACertificateManager::validateCertificateChain_realtime_error_
                            (IVar7,IVar6,0,&local_98);
          uVar5 = 0;
          uVar15 = (ushort)((int)IVar6 != 1);
        }
      }
    }
    else {
      uVar15 = 0;
    }
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
    puVar14 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      uVar5 = __acc_auth_protocol_handleSessionAuthenticationState_cold_2();
      puVar14 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar14 = *(undefined **)(_gLogObjects + 0x1c8);
  }
  iVar4 = _os_log_type_enabled(puVar14,uVar5,1);
  if (iVar4 != 0) {
    if (param_2 == 0) {
      local_8c = 0xffffffff;
    }
    else {
      local_8c = *(undefined4 *)(param_2 + 0x160);
    }
    local_90 = (undefined4)DAT_1001b3108;
    uStack_88 = 0x400;
    uStack_84 = 0;
    uStack_86 = uVar15;
    __os_log_impl(0x100000000,uVar5,1,
                  "[AccAuth] _validateCertificateChain: certificateDataCount %d, errorNo %d \n",
                  &local_90,0xe);
  }
  return uVar15;
}


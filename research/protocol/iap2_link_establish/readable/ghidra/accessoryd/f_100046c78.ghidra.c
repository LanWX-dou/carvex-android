/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100046c78
 * original code SHA256: 6199a26826c1910fccb86e1b088a2dc78935c6151a603be843c7a5053315f208
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x26 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x28 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x27 replaced with injection: _objc_release_fixup */

void _mfi4Auth_protocol_handle_AuthCert(undefined8 *param_1,long param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  long *plVar2;
  char *pcVar3;
  uint uVar4;
  long lVar5;
  size_t sVar6;
  uchar uVar7;
  uchar uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  bool bVar13;
  int iVar14;
  int iVar15;
  long lVar16;
  undefined8 uVar17;
  ulong uVar18;
  undefined8 uVar19;
  undefined8 *puVar20;
  long lVar21;
  long lVar22;
  long lVar23;
  ID IVar24;
  ID IVar25;
  undefined *puVar26;
  undefined *puVar27;
  long lVar28;
  uint uVar29;
  void *pvVar30;
  long lVar31;
  long lVar32;
  ushort uVar33;
  uint uVar34;
  undefined8 uVar35;
  ulong uVar36;
  void *pvVar37;
  undefined8 uVar38;
  undefined8 uVar39;
  size_t local_e8;
  byte local_dd;
  int local_dc;
  long local_d8;
  uchar local_d0;
  undefined1 uStack_cf;
  undefined2 uStack_ce;
  uint uStack_cc;
  undefined1 uStack_c8;
  undefined1 uStack_c7;
  ushort uStack_c6;
  undefined2 uStack_c4;
  undefined2 uStack_c2;
  undefined1 uStack_c0;
  undefined1 uStack_bf;
  undefined2 uStack_be;
  undefined4 uStack_bc;
  undefined1 uStack_b8;
  undefined1 uStack_b7;
  undefined6 uStack_b6;
  undefined1 uStack_b0;
  undefined1 uStack_af;
  undefined2 local_ae;
  undefined4 local_ac;
  undefined2 local_a8;
  undefined8 local_a6;
  undefined1 *local_90;
  undefined1 *puStack_88;
  undefined1 *puStack_80;
  undefined1 *puStack_78;
  long local_70;
  
  local_70 = *(long *)PTR____stack_chk_guard_10022bb80;
  local_dc = 1;
  local_dd = 0;
  local_e8 = 0;
  if (param_1 == (undefined8 *)0x0) {
    _mfi4Auth_protocol_handle_AuthCert_cold_60();
LAB_1000482a4:
    pvVar30 = (void *)0x0;
LAB_1000482bc:
    lVar32 = 0;
LAB_1000482c0:
    lVar28 = 0;
LAB_1000482c4:
    lVar16 = 0;
LAB_1000482c8:
    if (local_dc != 0) goto LAB_100048174;
  }
  else {
    if (*(char *)((long)param_1 + 0x1e) == '\x01') {
      _mfi4Auth_protocol_handle_AuthCert_cold_59();
      goto LAB_1000482a4;
    }
    if (param_2 == 0) {
      _mfi4Auth_protocol_handle_AuthCert_cold_58();
      pvVar30 = (void *)0x0;
      goto LAB_1000482bc;
    }
    lVar16 = _iAP2MsgGetFirstParam(param_2,0);
    puVar27 = PTR___os_log_default_10022bbb0;
    uVar19 = DAT_1001b30b0;
    uVar29 = 0;
    uVar36 = 0;
    pvVar37 = (void *)0x0;
    puVar1 = param_1 + 0x35;
    uVar35 = 0xd;
    do {
      if (lVar16 == 0) {
        lVar16 = 0;
        uVar34 = (uint)uVar35;
        if (9 < uVar34) {
          lVar28 = 0;
          lVar32 = 0;
          pvVar30 = (void *)0x0;
          goto LAB_100048164;
        }
        uVar4 = 1 << (ulong)(uVar34 & 0x1f);
        if ((uVar4 & 0x381) == 0) {
          lVar28 = 0;
          lVar32 = 0;
          pvVar30 = (void *)0x0;
          if ((uVar4 & 0xe) == 0) goto LAB_100048164;
          local_dc = _CTDecompressComputeBufferSize(pvVar37,uVar36 & 0xffff,&local_e8);
          if (local_dc == 0) {
            pvVar30 = (void *)_malloc_type_malloc(local_e8,0x3bbda037);
            if (pvVar30 != (void *)0x0) {
              local_dc = _CTDecompress(pvVar37,uVar36 & 0xffff,pvVar30,local_e8);
              if (local_dc == 0) {
                lVar16 = param_1[0x25];
                uVar19 = 0;
                if (lVar16 != 0) {
                  pcVar3 = "MFi40Accessory-Certificate";
                  if (uVar34 != 3) {
                    pcVar3 = "MFi40Accessory-Intermediate";
                  }
                  uVar19 = (**(code **)(lVar16 + 0x10))
                                     (lVar16,*param_1,0,0,1,0,pvVar30,local_e8,pcVar3,"MFi4Auth");
                }
                goto LAB_100047044;
              }
              _mfi4Auth_protocol_handle_AuthCert_cold_7(pvVar30);
              goto LAB_100048260;
            }
            _mfi4Auth_protocol_handle_AuthCert_cold_8(&local_dc,&local_e8);
          }
          else {
            _mfi4Auth_protocol_handle_AuthCert_cold_6(&local_dc);
LAB_100048260:
            pvVar30 = (void *)0x0;
          }
          lVar32 = 0;
          lVar28 = 0;
          lVar16 = 0;
          goto LAB_1000482c8;
        }
        local_e8 = uVar36 & 0xffff;
        pvVar30 = (void *)_malloc_type_malloc(local_e8,0x7997a451);
        if (pvVar30 == (void *)0x0) goto LAB_100048288;
        _memcpy(pvVar30,pvVar37,local_e8);
        lVar16 = param_1[0x25];
        uVar19 = 0;
        if (lVar16 != 0) {
          uVar19 = (**(code **)(lVar16 + 0x10))
                             (lVar16,*param_1,0,0,1,0,pvVar30,local_e8,"MFi30Accessory-Certificate",
                              "MFi4Auth");
        }
LAB_100047044:
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar27 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
            puVar27 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar14 = _os_log_type_enabled(puVar27,uVar19,0);
        if (iVar14 != 0) {
          uStack_cc = (uint)uVar36 & 0xffff;
          local_d0 = (uchar)DAT_1001b3108;
          uStack_cf = (undefined1)((ulong)DAT_1001b3108 >> 8);
          uStack_ce = (undefined2)((ulong)DAT_1001b3108 >> 0x10);
          uStack_c8 = 0;
          uStack_c7 = 8;
          uStack_c6 = (ushort)local_e8;
          uStack_c4 = (undefined2)(local_e8 >> 0x10);
          uStack_c2 = (undefined2)(local_e8 >> 0x20);
          uStack_c0 = (undefined1)(local_e8 >> 0x30);
          uStack_bf = (undefined1)(local_e8 >> 0x38);
          __os_log_impl(0x100000000,uVar19,0,
                        "mfi4Auth_protocol_handle_AuthCert: compressedLength %d, decompressedLength %zu"
                        ,&local_d0,0x12);
        }
        uVar19 = 0;
        if (0x1000 < local_e8) {
          _mfi4Auth_protocol_handle_AuthCert_cold_57(&local_e8);
          goto LAB_1000482bc;
        }
        if (9 < uVar34) {
LAB_100047160:
          if (uVar34 != 0) goto LAB_1000472b8;
          if (((uVar29 ^ 0xffffffff) & 3) != 0) goto LAB_100048288;
          if (*(int *)(param_1 + 0x1c) == 0) {
            param_1[0x68] = pvVar30;
            param_1[0x69] = local_e8;
            *(undefined4 *)((long)param_1 + 0x314) = 0;
          }
          else {
            param_1[0x48] = pvVar30;
            param_1[0x49] = local_e8;
            *(undefined4 *)(param_1 + 0x43) = 0;
          }
          uStack_c8 = 0xaa;
          uStack_c7 = 0xaa;
          uStack_c6 = 0xaaaa;
          uStack_c4 = 0xaaaa;
          uStack_c2 = 0xaaaa;
          local_d0 = 0xaa;
          uStack_cf = 0xaa;
          uStack_ce = 0xaaaa;
          uStack_cc = 0xaaaaaaaa;
          uStack_b8 = 0xaa;
          uStack_b7 = 0xaa;
          uStack_b6 = 0xaaaaaaaaaaaa;
          uStack_c0 = 0xaa;
          uStack_bf = 0xaa;
          uStack_be = 0xaaaa;
          uStack_bc = 0xaaaaaaaa;
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar27 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar27 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar14 = _os_log_type_enabled(puVar27,uVar19,0);
          if (iVar14 != 0) {
            local_90 = (undefined1 *)((ulong)local_90 & 0xffffffffffff0000);
            __os_log_impl(0x100000000,uVar19,0,
                          "mfi4Auth_protocol_handle_AuthCert: Accessory DID provide PrivacyPrefix!",
                          &local_90,2);
          }
          puVar20 = (undefined8 *)_malloc_type_malloc(local_e8 + 0x10,0x33b916e2);
          sVar6 = local_e8;
          uVar19 = *puVar1;
          puVar20[1] = param_1[0x36];
          *puVar20 = uVar19;
          _memcpy(puVar20 + 2,pvVar30,local_e8);
          _CC_SHA256(puVar20,(int)sVar6 + 0x10,&local_d0);
          lVar16 = 0x318;
          if (*(int *)(param_1 + 0x1c) != 0) {
            lVar16 = 0x21c;
          }
          plVar2 = (long *)((long)param_1 + lVar16);
          lVar22 = CONCAT44(uStack_cc,CONCAT22(uStack_ce,CONCAT11(uStack_cf,local_d0)));
          lVar23 = CONCAT26(uStack_c2,
                            CONCAT24(uStack_c4,CONCAT22(uStack_c6,CONCAT11(uStack_c7,uStack_c8))));
          lVar16 = *plVar2;
          lVar28 = plVar2[1];
          lVar31 = CONCAT44(uStack_bc,CONCAT22(uStack_be,CONCAT11(uStack_bf,uStack_c0)));
          lVar5 = CONCAT62(uStack_b6,CONCAT11(uStack_b7,uStack_b8));
          lVar32 = plVar2[2];
          lVar21 = plVar2[3];
          _free(puVar20);
          if (((lVar22 != lVar16 || lVar23 != lVar28) || lVar31 != lVar32) || lVar5 != lVar21) {
            _mfi4Auth_protocol_handle_AuthCert_cold_13(&local_dc,&local_d0);
            goto LAB_1000482bc;
          }
          lVar16 = 0;
          lVar28 = 0;
          lVar32 = 0;
LAB_100047768:
          IVar24 = NSMutableArray::arrayWithCapacity_
                             ((ID)PTR__OBJC_CLASS___NSMutableArray_10022bc60,3);
          if (*(char *)((long)param_1 + 0x1e) == '\x01') {
            uVar19 = _logObjectForModule();
            iVar14 = _os_log_type_enabled(uVar19,0x10);
            if (iVar14 != 0) {
              _mfi4Auth_protocol_handle_AuthCert_cold_35(uVar19);
            }
            goto LAB_10004851c;
          }
          if (IVar24 == 0) {
            uVar19 = _logObjectForModule();
            iVar14 = _os_log_type_enabled(uVar19,0x10);
            if (iVar14 != 0) {
              _mfi4Auth_protocol_handle_AuthCert_cold_34(uVar19);
            }
LAB_10004853c:
            iVar14 = 2;
LAB_100048544:
            uVar19 = 0;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar27 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar27 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar15 = _os_log_type_enabled(puVar27,uVar19,0x10);
            if (iVar15 != 0) {
              _mfi4Auth_protocol_handle_AuthCert_cold_37(iVar14,uVar19);
            }
LAB_100047cd4:
            local_dc = iVar14;
            if (local_dc != 0) {
              _mfi4Auth_protocol_handle_AuthCert_cold_38(&local_dc);
              goto LAB_1000482c8;
            }
          }
          else {
            if (*(int *)(param_1 + 0x1c) == 0) {
              IVar25 = IVar24;
              if (_gLogObjects == 0 || _gNumLogObjects < 0x3b) {
                puVar27 = PTR___os_log_default_10022bbb0;
                if (_logObjectForModule_onceToken != -1) {
                  IVar25 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                  puVar27 = PTR___os_log_default_10022bbb0;
                }
              }
              else {
                puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
              }
              iVar14 = _os_log_type_enabled(puVar27,IVar25,1);
              if (iVar14 != 0) {
                uStack_bc = *(undefined4 *)(param_1 + 0x1c);
                uVar19 = param_1[0x69];
                local_ac = *(undefined4 *)((long)param_1 + 0x314);
                local_a6 = param_1[0x4b];
                local_d0 = (uchar)DAT_1001b30e8;
                uStack_cf = (undefined1)((ulong)DAT_1001b30e8 >> 8);
                uStack_ce = (undefined2)((ulong)DAT_1001b30e8 >> 0x10);
                uStack_cc = 0x1cd966;
                uStack_c8 = 1;
                uStack_c7 = 0;
                uStack_c6 = 0;
                uStack_c4 = 0x400;
                uStack_c2 = 0xa9d;
                uStack_c0 = 0;
                uStack_bf = 0;
                uStack_be = 0x400;
                uStack_b8 = 0;
                uStack_b7 = 8;
                uStack_b6 = (undefined6)uVar19;
                uStack_b0 = (undefined1)((ulong)uVar19 >> 0x30);
                uStack_af = (undefined1)((ulong)uVar19 >> 0x38);
                local_ae = 0x400;
                local_a8 = 0x800;
                __os_log_impl(0x100000000,IVar25,1,
                              "%s:%d negotiatedAuthType %d, leafCertLen %zu, leafCertType %d, intermediate1_cert_init_len %zu"
                              ,&local_d0,0x32);
              }
              if ((param_1[0x69] != 0) &&
                 ((uVar29 = *(uint *)((long)param_1 + 0x314), uVar29 == 0 || (param_1[0x4b] != 0))))
              {
                lVar21 = 0x340;
                goto LAB_100047974;
              }
              uVar19 = _logObjectForModule(0);
              iVar14 = _os_log_type_enabled(uVar19,0x10);
              if (iVar14 != 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_32(uVar19);
              }
              goto LAB_10004853c;
            }
            IVar25 = IVar24;
            if (_gLogObjects == 0 || _gNumLogObjects < 0x3b) {
              puVar27 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                IVar25 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar27 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar14 = _os_log_type_enabled(puVar27,IVar25,1);
            if (iVar14 != 0) {
              uStack_bc = *(undefined4 *)(param_1 + 0x1c);
              uVar19 = param_1[0x49];
              local_ac = *(undefined4 *)(param_1 + 0x43);
              local_a6 = param_1[0x4b];
              local_d0 = (uchar)DAT_1001b30e8;
              uStack_cf = (undefined1)((ulong)DAT_1001b30e8 >> 8);
              uStack_ce = (undefined2)((ulong)DAT_1001b30e8 >> 0x10);
              uStack_cc = 0x1cd966;
              uStack_c8 = 1;
              uStack_c7 = 0;
              uStack_c6 = 0;
              uStack_c4 = 0x400;
              uStack_c2 = 0xaad;
              uStack_c0 = 0;
              uStack_bf = 0;
              uStack_be = 0x400;
              uStack_b8 = 0;
              uStack_b7 = 8;
              uStack_b6 = (undefined6)uVar19;
              uStack_b0 = (undefined1)((ulong)uVar19 >> 0x30);
              uStack_af = (undefined1)((ulong)uVar19 >> 0x38);
              local_ae = 0x400;
              local_a8 = 0x800;
              __os_log_impl(0x100000000,IVar25,1,
                            "%s:%d negotiatedAuthType %d, cert_init_len %zu, cert_init_type %d, intermediate1_cert_init_len %zu"
                            ,&local_d0,0x32);
            }
            if ((param_1[0x49] == 0) ||
               ((uVar29 = *(uint *)(param_1 + 0x43), uVar29 != 0 && (param_1[0x4b] == 0)))) {
              uVar19 = _logObjectForModule(0);
              iVar14 = _os_log_type_enabled(uVar19,0x10);
              if (iVar14 != 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_32(uVar19);
              }
              goto LAB_10004853c;
            }
            lVar21 = 0x240;
LAB_100047974:
            if (*(long *)((long)param_1 + lVar21) == 0) {
              uVar19 = _logObjectForModule(0);
              iVar14 = _os_log_type_enabled(uVar19,0x10);
              if (iVar14 != 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_32(uVar19);
              }
              goto LAB_10004853c;
            }
            IVar25 = NSData::dataWithBytes_length_((ID)PTR__OBJC_CLASS___NSData_10022bc38);
            NSMutableArray::addObject_(IVar24,IVar25);
            if (param_1[0x4b] != 0) {
              IVar25 = NSData::dataWithBytes_length_
                                 ((ID)PTR__OBJC_CLASS___NSData_10022bc38,param_1[0x4a]);
              NSMutableArray::addObject_(IVar24,IVar25);
            }
            if (param_1[0x4d] != 0) {
              IVar25 = NSData::dataWithBytes_length_
                                 ((ID)PTR__OBJC_CLASS___NSData_10022bc38,param_1[0x4c]);
              NSMutableArray::addObject_(IVar24,IVar25);
            }
            IVar25 = NSMutableArray::count(IVar24);
            if (IVar25 == 0) {
              uVar19 = _logObjectForModule();
              iVar14 = _os_log_type_enabled(uVar19,0x10);
              if (iVar14 != 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_31(uVar19);
              }
              goto LAB_10004853c;
            }
            if (uVar29 < 10) {
              uVar36 = (ulong)*(uint *)(&DAT_1001b39e8 + (ulong)uVar29 * 4);
            }
            else {
              uVar36 = 0xffffffff;
            }
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar27 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                IVar25 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar27 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar14 = _os_log_type_enabled(puVar27,IVar25,0);
            if (iVar14 != 0) {
              local_d0 = (uchar)DAT_1001b3088;
              uStack_cf = (undefined1)((ulong)DAT_1001b3088 >> 8);
              uStack_ce = (undefined2)((ulong)DAT_1001b3088 >> 0x10);
              uStack_cc = (uint)IVar24;
              uStack_c8 = (undefined1)(IVar24 >> 0x20);
              uStack_c7 = (undefined1)(IVar24 >> 0x28);
              uStack_c6 = (ushort)(IVar24 >> 0x30);
              __os_log_impl(0x100000000,IVar25,0,"mfi4Auth_protocol_validateCertChain: certList %@",
                            &local_d0,0xc);
            }
            IVar25 = MFAACertificateManager::sharedManager
                               ((ID)PTR__OBJC_CLASS___MFAACertificateManager_10022b1c8);
            IVar24 = MFAACertificateManager::copyParsedCertificateChainInfoFromCerts_assumeType_
                               (IVar25,IVar24,uVar36);
            uVar19 = 0;
            if (IVar24 == 0) {
              uVar19 = _logObjectForModule();
              iVar14 = _os_log_type_enabled(uVar19,0x10);
              if (iVar14 != 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_30(uVar19);
              }
              goto LAB_10004853c;
            }
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar27 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar27 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar14 = _os_log_type_enabled(puVar27,uVar19,0);
            if (iVar14 != 0) {
              local_d0 = (uchar)DAT_1001b3088;
              uStack_cf = (undefined1)((ulong)DAT_1001b3088 >> 8);
              uStack_ce = (undefined2)((ulong)DAT_1001b3088 >> 0x10);
              uStack_cc = (uint)IVar24;
              uStack_c8 = (undefined1)(IVar24 >> 0x20);
              uStack_c7 = (undefined1)(IVar24 >> 0x28);
              uStack_c6 = (ushort)(IVar24 >> 0x30);
              __os_log_impl(0x100000000,uVar19,0,
                            "mfi4Auth_protocol_validateCertChain: certListDict %@",&local_d0,0xc);
            }
            IVar25 = MFAACertificateManager::sharedManager
                               ((ID)PTR__OBJC_CLASS___MFAACertificateManager_10022b1c8);
            IVar24 = MFAACertificateManager::copyEvaluatedCertificateChainInfo_(IVar25,IVar24);
            uVar19 = 0;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar27 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar27 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar14 = _os_log_type_enabled(puVar27,uVar19,0);
            if (iVar14 != 0) {
              local_d0 = (uchar)DAT_1001b3088;
              uStack_cf = (undefined1)((ulong)DAT_1001b3088 >> 8);
              uStack_ce = (undefined2)((ulong)DAT_1001b3088 >> 0x10);
              uStack_cc = (uint)IVar24;
              uStack_c8 = (undefined1)(IVar24 >> 0x20);
              uStack_c7 = (undefined1)(IVar24 >> 0x28);
              uStack_c6 = (ushort)(IVar24 >> 0x30);
              __os_log_impl(0x100000000,uVar19,0,
                            "mfi4Auth_protocol_validateCertChain: certListDict %@",&local_d0,0xc);
            }
            if (IVar24 == 0) {
              uVar19 = _logObjectForModule(0);
              iVar14 = _os_log_type_enabled(uVar19,0x10);
              if (iVar14 != 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_29(uVar19);
              }
LAB_10004851c:
              iVar14 = -1;
              goto LAB_100048544;
            }
            if (*(int *)(param_1 + 5) != -1) {
              IVar25 = MFAACertificateManager::sharedManager
                                 ((ID)PTR__OBJC_CLASS___MFAACertificateManager_10022b1c8);
              IVar24 = MFAACertificateManager::verifyModuleCertificate_forModule_forAuthFlags_
                                 (IVar25,IVar24,(ulong)*(uint *)(param_1 + 5),0);
              uVar19 = 0;
              if ((int)IVar24 != 0) {
                uVar19 = _logObjectForModule();
                iVar14 = _os_log_type_enabled(uVar19,0x10);
                if (iVar14 != 0) {
                  _mfi4Auth_protocol_handle_AuthCert_cold_27(uVar19);
                }
                goto LAB_10004851c;
              }
              if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
                puVar27 = PTR___os_log_default_10022bbb0;
                if (_logObjectForModule_onceToken != -1) {
                  uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                  puVar27 = PTR___os_log_default_10022bbb0;
                }
              }
              else {
                puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
              }
              iVar14 = _os_log_type_enabled(puVar27,uVar19,0);
              if (iVar14 != 0) {
                local_d0 = '\0';
                uStack_cf = 0;
                __os_log_impl(0x100000000,uVar19,0,"verifyModuleCertificate succeeded",&local_d0,2);
              }
              iVar14 = 0;
              goto LAB_100047cd4;
            }
            local_dc = 0;
          }
          local_d8 = 0;
          if (*(char *)((long)param_1 + 0x1e) == '\x01') {
            _mfi4Auth_protocol_handle_AuthCert_cold_53(0);
LAB_100048658:
            local_dc = -1;
          }
          else {
            if (*(int *)(param_1 + 0x1c) == 0) {
              lVar21 = param_1[0x68];
              if (lVar21 == 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_52();
                goto LAB_100048658;
              }
              uVar19 = param_1[0x69];
              local_d0 = '\0';
              uVar39 = param_1[0x57];
              uVar38 = param_1[0x56];
              uVar17 = param_1[0x59];
              uVar35 = param_1[0x58];
              uStack_c7 = (undefined1)uVar17;
              uStack_c6 = (ushort)((ulong)uVar17 >> 8);
              uStack_c4 = (undefined2)((ulong)uVar17 >> 0x18);
              uStack_c2 = (undefined2)((ulong)uVar17 >> 0x28);
              uStack_c0 = (undefined1)((ulong)uVar17 >> 0x38);
              uStack_cf = (undefined1)uVar35;
              uStack_ce = (undefined2)((ulong)uVar35 >> 8);
              uStack_cc = (uint)((ulong)uVar35 >> 0x18);
              uStack_c8 = (undefined1)((ulong)uVar35 >> 0x38);
              uStack_b7 = (undefined1)uVar39;
              uStack_b6 = (undefined6)((ulong)uVar39 >> 8);
              uStack_b0 = (undefined1)((ulong)uVar39 >> 0x38);
              uStack_bf = (undefined1)uVar38;
              uStack_be = (undefined2)((ulong)uVar38 >> 8);
              uStack_bc = (undefined4)((ulong)uVar38 >> 0x18);
              uStack_b8 = (undefined1)((ulong)uVar38 >> 0x38);
              puStack_88 = &DAT_aaaaaaaaaaaaaaaa;
              local_90 = &DAT_aaaaaaaaaaaaaaaa;
              puStack_78 = &DAT_aaaaaaaaaaaaaaaa;
              puStack_80 = &DAT_aaaaaaaaaaaaaaaa;
              _CC_SHA256(&local_d0,0x21,(uchar *)&local_90);
              uVar35 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
              lVar22 = _CFDataCreate(uVar35,lVar21,uVar19);
              lVar23 = _CFDataCreate(uVar35,&local_90,0x20);
              lVar21 = _CFDataCreate(uVar35,param_1 + 0x5a,0x40);
              if (lVar22 == 0) {
                uVar36 = _mfi4Auth_protocol_handle_AuthCert_cold_51(lVar23,lVar21);
                if ((uVar36 & 1) != 0) goto LAB_100048658;
LAB_100048650:
                _CFRelease(lVar21);
                goto LAB_100048658;
              }
              if (lVar23 == 0) {
                uVar36 = _mfi4Auth_protocol_handle_AuthCert_cold_50(lVar22,lVar21);
                if ((uVar36 & 1) == 0) goto LAB_100048650;
                goto LAB_100048658;
              }
              if (lVar21 == 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_49();
                lVar21 = lVar23;
LAB_100048648:
                _CFRelease(lVar22);
                goto LAB_100048650;
              }
              uVar36 = _MFAAVerifyNonceSignature(lVar22,lVar23,lVar21);
              if ((uVar36 & 1) == 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_46(lVar22);
                lVar22 = lVar23;
                goto LAB_100048648;
              }
              _CFRelease(lVar22);
              _CFRelease(lVar23);
              uVar19 = _CFRelease(lVar21);
              lVar23 = 0;
              lVar22 = 0;
              lVar21 = 0;
LAB_100047f14:
              if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
                puVar27 = PTR___os_log_default_10022bbb0;
                if (_logObjectForModule_onceToken != -1) {
                  uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                  puVar27 = PTR___os_log_default_10022bbb0;
                }
              }
              else {
                puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
              }
              iVar14 = _os_log_type_enabled(puVar27,uVar19,0);
              if (iVar14 != 0) {
                local_d0 = '\0';
                uStack_cf = 0;
                __os_log_impl(0x100000000,uVar19,0,
                              "mfi4Auth_protocol_validateSignature: verification passed",&local_d0,2
                             );
              }
              iVar15 = 0;
              iVar14 = 0;
              if (lVar21 != 0) goto LAB_100047f9c;
            }
            else {
              lVar21 = ___createCertificateRefWithBytes
                                 (param_1[0x48],param_1[0x49],*(undefined4 *)(param_1 + 0x43));
              if (lVar21 == 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_45();
                goto LAB_100048658;
              }
              lVar22 = _SecCertificateCopyKey();
              if (lVar22 == 0) {
                uVar19 = _logObjectForModule();
                iVar14 = _os_log_type_enabled(uVar19,0x10);
                if (iVar14 != 0) {
                  _mfi4Auth_protocol_handle_AuthCert_cold_44(uVar19);
                }
LAB_1000484ac:
                lVar23 = 0;
LAB_1000485e8:
                iVar14 = -1;
              }
              else {
                lVar23 = _SecKeyCopyExternalRepresentation(lVar22,&local_d8);
                if ((local_d8 != 0) && (uVar19 = _CFErrorCopyDescription(), local_d8 != 0)) {
                  _mfi4Auth_protocol_handle_AuthCert_cold_39(uVar19);
                  goto LAB_1000485e8;
                }
                if (lVar23 == 0) {
                  uVar19 = _logObjectForModule(0);
                  iVar14 = _os_log_type_enabled(uVar19,0x10);
                  if (iVar14 != 0) {
                    _mfi4Auth_protocol_handle_AuthCert_cold_43(uVar19);
                  }
                  goto LAB_1000484ac;
                }
                uVar35 = __dumpSimpleHex(lVar23);
                uVar19 = uVar35;
                if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
                  puVar27 = PTR___os_log_default_10022bbb0;
                  if (_logObjectForModule_onceToken != -1) {
                    uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                    puVar27 = PTR___os_log_default_10022bbb0;
                  }
                }
                else {
                  puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
                }
                iVar14 = _os_log_type_enabled(puVar27,uVar19,0);
                if (iVar14 != 0) {
                  local_d0 = (uchar)DAT_1001b3088;
                  uStack_cf = (undefined1)((ulong)DAT_1001b3088 >> 8);
                  uStack_ce = (undefined2)((ulong)DAT_1001b3088 >> 0x10);
                  uStack_cc = (uint)uVar35;
                  uStack_c8 = (undefined1)((ulong)uVar35 >> 0x20);
                  uStack_c7 = (undefined1)((ulong)uVar35 >> 0x28);
                  uStack_c6 = (ushort)((ulong)uVar35 >> 0x30);
                  __os_log_impl(0x100000000,uVar19,0,"validateSignature: keyRepresentation: %@\n",
                                &local_d0,0xc);
                }
                uVar17 = param_1[0x13];
                uVar19 = _CFDataGetLength(lVar23);
                uVar35 = _CFDataGetBytePtr(lVar23);
                uVar19 = _ccsigma_import_peer_verification_key(uVar17,uVar19,uVar35);
                if ((int)uVar19 == 0) {
                  uVar19 = _ccsigma_verify(uVar17,param_1 + 0x4e,0x20,(long)param_1 + 0x21c);
                  if ((int)uVar19 == 0) goto LAB_100047f14;
                  uVar35 = _logObjectForModule();
                  iVar14 = _os_log_type_enabled(uVar35,0x10);
                  if (iVar14 != 0) {
                    _mfi4Auth_protocol_handle_AuthCert_cold_42(uVar35);
                  }
                }
                else {
                  uVar35 = _logObjectForModule();
                  iVar14 = _os_log_type_enabled(uVar35,0x10);
                  if (iVar14 != 0) {
                    _mfi4Auth_protocol_handle_AuthCert_cold_41(uVar35);
                  }
                }
                iVar14 = (int)uVar19;
              }
LAB_100047f9c:
              iVar15 = iVar14;
              _CFRelease(lVar21);
            }
            if (lVar22 != 0) {
              _CFRelease(lVar22);
            }
            if (lVar23 != 0) {
              _CFRelease(lVar23);
            }
            local_dc = iVar15;
            if (iVar15 == 0) {
              uVar36 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ForceAuthFail);
              if (((uVar36 & 1) == 0) &&
                 (uVar36 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_PretendNFCAuthFailed)
                 , (int)uVar36 == 0)) {
                uVar36 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ForceAuthTimeout);
                if (((uVar36 & 1) != 0) ||
                   (iVar14 = _acc_userDefaults_boolForKey
                                       (_kCFACCUserDefaultsKey_PretendNFCAuthTimeout), iVar14 != 0))
                {
                  uVar19 = _logObjectForModule();
                  iVar14 = _os_log_type_enabled(uVar19,0);
                  if (iVar14 != 0) {
                    local_d0 = (uchar)DAT_1001b3098;
                    uStack_cf = (undefined1)((ulong)DAT_1001b3098 >> 8);
                    uStack_ce = (undefined2)((ulong)DAT_1001b3098 >> 0x10);
                    uStack_cc = 0x1cd909;
                    uStack_c8 = 1;
                    uStack_c7 = 0;
                    uStack_c6 = 0;
                    uStack_c4 = 0x400;
                    uStack_c2 = 2;
                    uStack_c0 = 0;
                    uStack_bf = 0;
                    __os_log_impl(0x100000000,uVar19,0,
                                  "%s: ForceAuthTimeout/PretendNFCAuthTimeout!!!, ignore status(%d)"
                                  ,&local_d0,0x12);
                  }
                  goto LAB_1000480a4;
                }
                if (*(int *)(param_1 + 0x1c) != 0) {
                  local_dc = _mfi4Auth_protocol_initMessage_AuthenticationSucceeded(param_1,param_3)
                  ;
                  goto LAB_10004751c;
                }
                uVar19 = 2;
              }
              else {
                if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
                  puVar27 = PTR___os_log_default_10022bbb0;
                  if (_logObjectForModule_onceToken != -1) {
                    uVar36 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                    puVar27 = PTR___os_log_default_10022bbb0;
                  }
                }
                else {
                  puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
                }
                iVar14 = _os_log_type_enabled(puVar27,uVar36,0);
                if (iVar14 != 0) {
                  local_d0 = (uchar)DAT_1001b3098;
                  uStack_cf = (undefined1)((ulong)DAT_1001b3098 >> 8);
                  uStack_ce = (undefined2)((ulong)DAT_1001b3098 >> 0x10);
                  uStack_cc = 0x1cd909;
                  uStack_c8 = 1;
                  uStack_c7 = 0;
                  uStack_c6 = 0;
                  uStack_c4 = 0x400;
                  uStack_c2 = 1;
                  uStack_c0 = 0;
                  uStack_bf = 0;
                  __os_log_impl(0x100000000,uVar36,0,
                                "%s: ForceAuthFail/PretendNFCAuthFailed!!!, set status(%d)",
                                &local_d0,0x12);
                }
                uVar19 = 1;
              }
              _mfi4Auth_protocol_handle_AuthState(param_1,uVar19);
              goto LAB_1000480a4;
            }
          }
          _mfi4Auth_protocol_handle_AuthCert_cold_54(&local_dc);
          goto LAB_1000482c8;
        }
        uVar4 = 1 << (ulong)(uVar34 & 0x1f);
        if ((uVar4 & 0x82) == 0) {
          if ((uVar4 & 0x104) == 0) {
            if ((1 << (ulong)(uVar34 & 0x1f) & 0x208U) == 0) goto LAB_100047160;
            if (((uVar29 ^ 0xffffffff) & 3) != 0) goto LAB_100048288;
            if (*(int *)(param_1 + 0x1c) == 0) {
              param_1[0x68] = pvVar30;
              param_1[0x69] = local_e8;
              *(uint *)((long)param_1 + 0x314) = uVar34;
            }
            else {
              param_1[0x48] = pvVar30;
              param_1[0x49] = local_e8;
              *(uint *)(param_1 + 0x43) = uVar34;
            }
            uStack_c8 = 0xaa;
            uStack_c7 = 0xaa;
            uStack_c6 = 0xaaaa;
            uStack_c4 = 0xaaaa;
            uStack_c2 = 0xaaaa;
            local_d0 = 0xaa;
            uStack_cf = 0xaa;
            uStack_ce = 0xaaaa;
            uStack_cc = 0xaaaaaaaa;
            uStack_b8 = 0xaa;
            uStack_b7 = 0xaa;
            uStack_b6 = 0xaaaaaaaaaaaa;
            uStack_c0 = 0xaa;
            uStack_bf = 0xaa;
            uStack_be = 0xaaaa;
            uStack_bc = 0xaaaaaaaa;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar27 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar19 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar27 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar14 = _os_log_type_enabled(puVar27,uVar19,0);
            if (iVar14 != 0) {
              local_90 = (undefined1 *)((ulong)local_90 & 0xffffffffffff0000);
              __os_log_impl(0x100000000,uVar19,0,
                            "mfi4Auth_protocol_handle_AuthCert: Accessory DID provide PrivacyPrefix!"
                            ,&local_90,2);
            }
            puVar20 = (undefined8 *)_malloc_type_malloc(local_e8 + 0x10,0x9189c146);
            sVar6 = local_e8;
            uVar19 = *puVar1;
            puVar20[1] = param_1[0x36];
            *puVar20 = uVar19;
            _memcpy(puVar20 + 2,pvVar30,local_e8);
            _CC_SHA256(puVar20,(int)sVar6 + 0x10,&local_d0);
            lVar16 = 0x318;
            if (*(int *)(param_1 + 0x1c) != 0) {
              lVar16 = 0x21c;
            }
            plVar2 = (long *)((long)param_1 + lVar16);
            lVar22 = CONCAT44(uStack_cc,CONCAT22(uStack_ce,CONCAT11(uStack_cf,local_d0)));
            lVar23 = CONCAT26(uStack_c2,
                              CONCAT24(uStack_c4,CONCAT22(uStack_c6,CONCAT11(uStack_c7,uStack_c8))))
            ;
            lVar16 = *plVar2;
            lVar28 = plVar2[1];
            lVar31 = CONCAT44(uStack_bc,CONCAT22(uStack_be,CONCAT11(uStack_bf,uStack_c0)));
            lVar5 = CONCAT62(uStack_b6,CONCAT11(uStack_b7,uStack_b8));
            lVar32 = plVar2[2];
            lVar21 = plVar2[3];
            _free(puVar20);
            if (((lVar22 != lVar16 || lVar23 != lVar28) || lVar31 != lVar32) || lVar5 != lVar21) {
              _mfi4Auth_protocol_handle_AuthCert_cold_13(&local_dc,&local_d0);
              goto LAB_1000482bc;
            }
          }
          else {
            if (uVar29 != 3) goto LAB_100048288;
            param_1[0x4c] = pvVar30;
            param_1[0x4d] = local_e8;
          }
        }
        else {
          if (uVar29 != 3) {
LAB_100048288:
            lVar16 = 0;
            lVar28 = 0;
            lVar32 = 0;
            goto LAB_100048164;
          }
          param_1[0x4a] = pvVar30;
          param_1[0x4b] = local_e8;
        }
LAB_1000472b8:
        lVar32 = ___createCertificateRefWithBytes(pvVar30,local_e8,uVar35);
        if (lVar32 == 0) {
          _mfi4Auth_protocol_handle_AuthCert_cold_17(&local_dc);
          goto LAB_1000482c0;
        }
        lVar21 = _SecCertificateGetAuthorityKeyID(lVar32);
        if (lVar21 == 0) {
          _mfi4Auth_protocol_handle_AuthCert_cold_55(&local_dc);
          goto LAB_1000482c0;
        }
        if (uVar34 - 7 < 3) {
          lVar28 = _SecCertificateCreateWithBytes
                             (*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,
                              PTR__kCertDER_ComponentAuth_ComponentRoot_Area51_10022b1d0,
                              *(undefined8 *)
                               PTR__kCertDER_ComponentAuth_ComponentRoot_Area51_Length_10022b1d8);
          if (lVar28 == 0) {
            _mfi4Auth_protocol_handle_AuthCert_cold_17(&local_dc);
            goto LAB_1000482c4;
          }
          lVar22 = 0;
          lVar16 = 0;
LAB_100047390:
          lVar23 = _SecCertificateGetSubjectKeyID(lVar28);
          lVar31 = lVar23;
          if (lVar23 == 0) {
            _mfi4Auth_protocol_handle_AuthCert_cold_15(&local_dc);
            goto LAB_1000482c8;
          }
        }
        else {
          if (uVar34 - 1 < 3) {
            uVar19 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
            lVar16 = _SecCertificateCreateWithBytes
                               (uVar19,PTR__kCertDER_Mfi4_Root_Test_10022b1f0,
                                *(undefined8 *)PTR__kCertDER_Mfi4_Root_Test_Length_10022b1f8);
            if (lVar16 == 0) {
              _mfi4Auth_protocol_handle_AuthCert_cold_17(&local_dc);
              lVar28 = 0;
            }
            else {
              lVar28 = _SecCertificateCreateWithBytes
                                 (uVar19,PTR__kCertDER_Mfi4_Root_10022b1e0,
                                  *(undefined8 *)PTR__kCertDER_Mfi4_Root_Length_10022b1e8);
              if (lVar28 == 0) {
                _mfi4Auth_protocol_handle_AuthCert_cold_17(&local_dc);
              }
              else {
                lVar22 = _SecCertificateGetSubjectKeyID(lVar16);
                if (lVar22 != 0) goto LAB_100047390;
                _mfi4Auth_protocol_handle_AuthCert_cold_16(&local_dc);
              }
            }
            goto LAB_1000482c8;
          }
          lVar22 = 0;
          lVar28 = 0;
          lVar16 = 0;
          lVar23 = lVar21;
          lVar31 = 0;
        }
        if (6 < (int)uVar34) {
          if (uVar34 != 8) {
            if (uVar34 != 7) goto LAB_10004750c;
            goto LAB_1000473cc;
          }
LAB_100047400:
          if (lVar22 == 0) {
            uVar29 = 0;
            if (lVar31 == 0) goto LAB_100047530;
LAB_10004741c:
            lVar23 = _CFEqual(lVar21,lVar31);
            uVar33 = (ushort)((int)lVar23 != 0);
          }
          else {
            lVar23 = _CFEqual(lVar21,lVar22);
            uVar29 = (uint)((int)lVar23 != 0);
            if (lVar31 != 0) goto LAB_10004741c;
LAB_100047530:
            uVar33 = 0;
          }
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar27 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              lVar23 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar27 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar14 = _os_log_type_enabled(puVar27,lVar23,0);
          if (iVar14 != 0) {
            local_d0 = (uchar)DAT_1001b3108;
            uStack_cf = (undefined1)((ulong)DAT_1001b3108 >> 8);
            uStack_ce = (undefined2)((ulong)DAT_1001b3108 >> 0x10);
            uStack_c8 = 0;
            uStack_c7 = 4;
            uStack_c4 = 0;
            uStack_cc = uVar29;
            uStack_c6 = uVar33;
            __os_log_impl(0x100000000,lVar23,0,
                          "mfi4Auth_protocol_handle_AuthCert: authorityIsRoot: dev:%d, prod:%d",
                          &local_d0,0xe);
          }
          if (uVar29 != 0 || uVar33 != 0) {
            uVar19 = _logObjectForModule(0);
            iVar14 = _os_log_type_enabled(uVar19,0);
            if (iVar14 != 0) {
LAB_1000475fc:
              uStack_cf = 0;
              local_d0 = '\0';
              __os_log_impl(0x100000000,uVar19,0,"mfi4Auth_protocol_handle_AuthCert: known skid",
                            &local_d0,2);
            }
            goto LAB_100047768;
          }
          goto LAB_100048164;
        }
        if (uVar34 == 1) {
LAB_1000473cc:
          if (lVar22 == 0) {
            uVar29 = 0;
            if (lVar31 == 0) goto LAB_10004743c;
LAB_1000473e8:
            lVar23 = _CFEqual(lVar21,lVar31);
            uVar33 = (ushort)((int)lVar23 != 0);
          }
          else {
            lVar23 = _CFEqual(lVar21,lVar22);
            uVar29 = (uint)((int)lVar23 != 0);
            if (lVar31 != 0) goto LAB_1000473e8;
LAB_10004743c:
            uVar33 = 0;
          }
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar27 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              lVar23 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
              puVar27 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar27 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          iVar14 = _os_log_type_enabled(puVar27,lVar23,0);
          if (iVar14 != 0) {
            local_d0 = (uchar)DAT_1001b3108;
            uStack_cf = (undefined1)((ulong)DAT_1001b3108 >> 8);
            uStack_ce = (undefined2)((ulong)DAT_1001b3108 >> 0x10);
            uStack_c8 = 0;
            uStack_c7 = 4;
            uStack_c4 = 0;
            uStack_cc = uVar29;
            uStack_c6 = uVar33;
            __os_log_impl(0x100000000,lVar23,0,
                          "mfi4Auth_protocol_handle_AuthCert: authorityIsRoot: dev:%d, prod:%d",
                          &local_d0,0xe);
          }
          if (uVar29 != 0 || uVar33 != 0) {
            uVar19 = _logObjectForModule(0);
            iVar14 = _os_log_type_enabled(uVar19,0);
            if (iVar14 == 0) goto LAB_100047768;
            goto LAB_1000475fc;
          }
        }
        else if (uVar34 == 2) goto LAB_100047400;
LAB_10004750c:
        local_dc = _mfi4Auth_protocol_initMessage_RequestAuthCert(param_1,param_3,lVar21);
LAB_10004751c:
        if (local_dc != 0) goto LAB_100048174;
LAB_1000480a4:
        local_dc = 0;
        goto LAB_100048180;
      }
      iVar14 = _iAP2MsgGetParamID(lVar16);
      uVar11 = uStack_ce;
      uVar9 = uStack_cf;
      uVar7 = local_d0;
      if (iVar14 == 2) {
        uVar17 = _iAP2MsgGetDataAsArrayU8(lVar16,&local_dc,puVar1,0x10);
        if (local_dc == 0) {
          if ((int)uVar17 == 0x10) {
            uVar29 = uVar29 | 4;
            goto LAB_100046ebc;
          }
          _mfi4Auth_protocol_handle_AuthCert_cold_2(&local_dc,uVar17);
        }
        else {
          _mfi4Auth_protocol_handle_AuthCert_cold_3();
        }
        goto LAB_100048260;
      }
      uStack_ce = (undefined2)((ulong)uVar19 >> 0x10);
      uVar12 = uStack_ce;
      local_d0 = (uchar)uVar19;
      uVar8 = local_d0;
      uStack_cf = (undefined1)((ulong)uVar19 >> 8);
      uVar10 = uStack_cf;
      local_d0 = uVar7;
      uStack_cf = uVar9;
      uStack_ce = uVar11;
      if (iVar14 == 1) {
        pvVar37 = (void *)_iAP2MsgGetDataAsData(lVar16,&local_dc);
        uVar36 = _iAP2MsgGetParamValueLen(lVar16);
        if (local_dc != 0) {
          _mfi4Auth_protocol_handle_AuthCert_cold_3();
          goto LAB_100048260;
        }
        uVar18 = uVar36;
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar26 = puVar27;
          if (_logObjectForModule_onceToken != -1) {
            uVar18 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
          }
        }
        else {
          puVar26 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar14 = _os_log_type_enabled(puVar26,uVar18,0);
        if (iVar14 != 0) {
          uStack_cc = (uint)uVar36;
          local_d0 = uVar8;
          uStack_cf = uVar10;
          uStack_ce = uVar12;
          __os_log_impl(0x100000000,uVar18,0,
                        "mfi4Auth_protocol_handle_AuthCert: compressedLength:%d",&local_d0,8);
        }
        uVar29 = uVar29 | 2;
      }
      else if (iVar14 == 0) {
        uVar35 = _iAP2MsgGetDataAsU8(lVar16,&local_dc);
        uVar17 = uVar35;
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar26 = puVar27;
          if (_logObjectForModule_onceToken != -1) {
            uVar17 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
          }
        }
        else {
          puVar26 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar14 = _os_log_type_enabled(puVar26,uVar17,0);
        if (iVar14 != 0) {
          local_d0 = uVar8;
          uStack_cf = uVar10;
          uStack_ce = uVar12;
          uStack_cc = (uint)uVar35;
          __os_log_impl(0x100000000,uVar17,0,"mfi4Auth_protocol_handle_AuthCert: certType:%d",
                        &local_d0,8);
        }
        if (local_dc != 0) {
          lVar16 = 0;
          lVar28 = 0;
          lVar32 = 0;
          pvVar30 = (void *)0x0;
          goto LAB_100048174;
        }
        if (0xc < (uint)uVar35) break;
        uVar29 = uVar29 | 1;
      }
LAB_100046ebc:
      lVar16 = _iAP2MsgGetNextParamWithError(param_2,0,lVar16,&local_dd);
    } while ((local_dd & 1) == 0);
    lVar16 = 0;
    lVar28 = 0;
    lVar32 = 0;
    pvVar30 = (void *)0x0;
LAB_100048164:
    local_dc = -1;
LAB_100048174:
    _mfi4Auth_protocol_handle_AuthState(param_1,1);
  }
LAB_100048180:
  if (param_1 == (undefined8 *)0x0) {
    bVar13 = true;
  }
  else {
    if ((((void *)param_1[0x48] == pvVar30) || ((void *)param_1[0x68] == pvVar30)) ||
       ((void *)param_1[0x4a] == pvVar30)) goto LAB_1000481d0;
    bVar13 = (void *)param_1[0x4c] != pvVar30;
  }
  if ((pvVar30 != (void *)0x0) && (bVar13)) {
    _free(pvVar30);
  }
LAB_1000481d0:
  if (lVar16 != 0) {
    _CFRelease(lVar16);
  }
  if (lVar28 != 0) {
    _CFRelease(lVar28);
  }
  if (lVar32 != 0) {
    _CFRelease(lVar32);
  }
  if (*(long *)PTR____stack_chk_guard_10022bb80 == local_70) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(local_dc);
}


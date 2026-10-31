/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10088c824
 * original code SHA256: 6e03de627e81310b48e04802e1224ecff9ab4a7c1531e640dddaa866b0de2893
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x25 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */
/* WARNING: Removing unreachable block (ram,0x00010088d414) */
/* WARNING: Removing unreachable block (ram,0x00010088f5a8) */
/* WARNING: Removing unreachable block (ram,0x00010088f9f4) */
/* WARNING: Removing unreachable block (ram,0x00010089014c) */
/* WARNING: Removing unreachable block (ram,0x00010088ff68) */
/* WARNING: Removing unreachable block (ram,0x00010088fd88) */
/* WARNING: Removing unreachable block (ram,0x00010088fe38) */
/* WARNING: Removing unreachable block (ram,0x00010088dea0) */
/* WARNING: Removing unreachable block (ram,0x00010088f700) */
/* WARNING: Removing unreachable block (ram,0x00010088df00) */
/* WARNING: Removing unreachable block (ram,0x00010088ef9c) */
/* WARNING: Removing unreachable block (ram,0x00010088dd0c) */
/* WARNING: Removing unreachable block (ram,0x00010088d4f0) */
/* WARNING: Removing unreachable block (ram,0x00010088dfdc) */
/* WARNING: Removing unreachable block (ram,0x00010088e2dc) */
/* WARNING: Removing unreachable block (ram,0x00010088fe64) */
/* WARNING: Removing unreachable block (ram,0x00010088f840) */
/* WARNING: Removing unreachable block (ram,0x00010088fea0) */
/* WARNING: Removing unreachable block (ram,0x000100890120) */
/* WARNING: Removing unreachable block (ram,0x00010088d20c) */
/* WARNING: Removing unreachable block (ram,0x00010088d528) */
/* WARNING: Removing unreachable block (ram,0x00010089021c) */
/* WARNING: Removing unreachable block (ram,0x00010088d52c) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void phone_fn_10088c824(double param_1,long param_2,undefined8 param_3,ulong *param_4)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  undefined8 uVar7;
  ulong *puVar8;
  ulong *puVar9;
  ulong *puVar10;
  ulong *puVar11;
  undefined8 *puVar12;
  undefined2 *puVar13;
  char *pcVar14;
  byte *pbVar15;
  long *plVar16;
  undefined *puVar17;
  long *plVar18;
  ID IVar19;
  undefined4 *puVar20;
  undefined8 *puVar21;
  ID IVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  long lVar25;
  long lVar26;
  ulong uVar27;
  ulong *puVar28;
  ulong uVar29;
  ulong uVar30;
  ulong uVar31;
  ulong uVar32;
  ulong uVar33;
  double dVar34;
  double dVar35;
  int iStack_400;
  int iStack_3fc;
  int iStack_3f8;
  int iStack_3f4;
  undefined8 uStack_3e0;
  undefined8 uStack_3d8;
  long lStack_3d0;
  ulong uStack_3c0;
  undefined8 uStack_3b8;
  long lStack_3b0;
  undefined8 auStack_3a8 [2];
  char cStack_391;
  undefined4 uStack_390;
  undefined2 uStack_38c;
  undefined1 uStack_38a;
  undefined1 uStack_383;
  undefined2 uStack_382;
  undefined8 uStack_380;
  undefined8 *puStack_378;
  undefined8 uStack_370;
  undefined8 uStack_368;
  long lStack_360;
  long lStack_358;
  undefined8 uStack_350;
  undefined8 uStack_348;
  long lStack_340;
  long lStack_338;
  undefined8 uStack_330;
  undefined8 uStack_328;
  long lStack_320;
  long lStack_318;
  undefined8 uStack_310;
  undefined8 uStack_308;
  long lStack_300;
  undefined4 uStack_2f8;
  undefined2 uStack_2f4;
  undefined8 uStack_2f0;
  undefined8 uStack_2e8;
  long lStack_2e0;
  undefined8 uStack_2d0;
  undefined8 uStack_2c8;
  long lStack_2c0;
  undefined8 auStack_2b8 [2];
  char cStack_2a1;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  long lStack_290;
  undefined8 uStack_280;
  undefined8 uStack_278;
  long lStack_270;
  undefined8 uStack_260;
  undefined8 uStack_258;
  long lStack_250;
  undefined8 uStack_240;
  undefined8 uStack_238;
  long lStack_230;
  undefined8 uStack_220;
  undefined8 uStack_218;
  long lStack_210;
  undefined8 uStack_200;
  undefined8 uStack_1f8;
  long lStack_1f0;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  long lStack_1d0;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  long lStack_1b0;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  long lStack_190;
  undefined8 auStack_188 [2];
  char cStack_171;
  undefined8 auStack_170 [2];
  char cStack_159;
  undefined8 uStack_158;
  cfstringStruct *pcStack_150;
  ID IStack_148;
  byte bStack_140;
  byte bStack_13f;
  byte bStack_13e;
  byte bStack_13d;
  byte bStack_13c;
  byte bStack_13b;
  undefined2 uStack_13a;
  undefined4 uStack_138;
  undefined2 uStack_134;
  undefined2 uStack_132;
  undefined4 uStack_130;
  undefined2 uStack_12c;
  char cStack_129;
  undefined8 uStack_120;
  short sStack_118;
  short sStack_116;
  short sStack_114;
  short sStack_112;
  undefined2 uStack_110;
  undefined4 uStack_10e;
  char cStack_109;
  undefined8 uStack_100;
  ulong uStack_f8;
  undefined8 uStack_f0;
  ulong uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  long lStack_d0;
  undefined2 uStack_c0;
  undefined2 uStack_be;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined2 uStack_b4;
  char cStack_b2;
  uint uStack_b1;
  undefined4 uStack_ad;
  undefined1 uStack_a9;
  byte *pbStack_a8;
  long lStack_98;
  
  uVar7 = uRam0000000100cae468;
  lStack_98 = *(long *)PTR____stack_chk_guard_100bfc980;
  uVar24 = uRam0000000100cae468;
  _os_log_type_enabled(uRam0000000100cae468,0);
  if ((int)uVar24 != 0) {
    uStack_c0 = SUB82(_UNK_100930b20,0);
    uStack_be = (undefined2)((ulong)_UNK_100930b20 >> 0x10);
    uStack_bc = (undefined4)param_3;
    uStack_b8 = (undefined4)((ulong)param_3 >> 0x20);
    param_1 = _UNK_100930b20;
    __os_log_impl(0x100000000,uVar7,0,"Received XPC message \"%{public}s\"",&uStack_c0,0xc);
  }
  uVar7 = param_3;
  _strcmp(param_3,"SetConnectionParameters");
  if ((int)uVar7 == 0) {
    uStack_c0 = 0;
    uStack_be = 0;
    uStack_bc = 0;
    uStack_b8 = 0;
    uStack_b4 = 0;
    cStack_b2 = '\0';
    uStack_b1 = uStack_b1 & 0xffffff00;
    puVar8 = param_4;
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    _uuid_copy(&uStack_c0,puVar8);
    _xpc_dictionary_get_double(param_4,"kMinInterval");
    dVar34 = param_1;
    _xpc_dictionary_get_double(param_4,"kPreferredInterval");
    dVar35 = dVar34;
    _xpc_dictionary_get_double(param_4,"kMaxInterval");
    puVar8 = param_4;
    _xpc_dictionary_get_int64(param_4,"kMinCELength");
    puVar28 = param_4;
    _xpc_dictionary_get_int64(param_4,"kMaxCELength");
    puVar9 = param_4;
    _xpc_dictionary_get_int64(param_4,"kPreferredPeripheralLatency");
    puVar10 = param_4;
    _xpc_dictionary_get_int64(param_4,"kMaxPeripheralLatency");
    puVar11 = param_4;
    _xpc_dictionary_get_int64(param_4,"kTimeout");
    _xpc_dictionary_get_int64(param_4,"kMaxDeferment");
    if (lRam0000000100c1b1f8 != -1) {
      FUN_1009066bc();
    }
    FUN_100810000((float)param_1,(float)dVar34,(float)dVar35,uRam0000000100c1b1f0,&uStack_c0,
                  (uint)puVar8 & 0xffff,(uint)puVar28 & 0xffff,(uint)puVar9 & 0xffff,
                  (uint)puVar10 & 0xffff,(uint)puVar11 & 0xffff,(uint)param_4 & 0xff,1);
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"AuthenticationDidSucceed");
  if ((int)uVar7 == 0) {
    uStack_e0 = 0;
    uStack_d8 = 0;
    puVar8 = param_4;
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    _uuid_copy(&uStack_e0,puVar8);
    _xpc_dictionary_get_int64(param_4,"kCertClass");
    uStack_b8 = 0;
    uStack_b4 = 0;
    cStack_b2 = '\0';
    uStack_c0 = 0;
    uStack_be = 0;
    uStack_bc = 0;
    pbStack_a8 = (byte *)0x0;
    uStack_b1 = 0;
    uStack_ad = 0;
    uStack_a9 = 0;
    if (param_4 == (ulong *)0x7fffffff) {
      uStack_b8 = (undefined4)s_IsMFiAuthenticated_100a713ef._8_8_;
      uStack_b4 = SUB82(s_IsMFiAuthenticated_100a713ef._8_8_,4);
      cStack_b2 = SUB81(s_IsMFiAuthenticated_100a713ef._8_8_,6);
      uStack_b1._0_1_ = SUB81(s_IsMFiAuthenticated_100a713ef._8_8_,7);
      uStack_b1 = CONCAT31(0x6465,(char)uStack_b1);
      uStack_c0 = (undefined2)s_IsMFiAuthenticated_100a713ef._0_8_;
      uStack_be = SUB82(s_IsMFiAuthenticated_100a713ef._0_8_,2);
      uStack_bc = SUB84(s_IsMFiAuthenticated_100a713ef._0_8_,4);
    }
    else {
      _snprintf(&uStack_c0,0x20,"IsMFiAuthenticated_CertClass%02X");
    }
    if (lRam0000000100c1b218 != -1) {
      FUN_1009060a0();
    }
    uVar7 = uRam0000000100c1b210;
    puVar12 = &uStack_e0;
    FUN_100011444(puVar12);
    puVar13 = &uStack_c0;
    _strlen();
    puVar21 = auStack_170;
    FUN_1001ec44c(puVar21,puVar13);
    _memcpy();
    *(undefined1 *)((long)puVar21 + (long)puVar13) = 0;
    FUN_100830608(uVar7,puVar12,auStack_170);
    if (cStack_159 < '\0') {
      __ZdlPv(auStack_170[0]);
    }
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"AuthenticationDidFail");
  if ((int)uVar7 == 0) {
    uStack_c0 = 0;
    uStack_be = 0;
    uStack_bc = 0;
    uStack_b8 = 0;
    uStack_b4 = 0;
    cStack_b2 = '\0';
    uStack_b1 = uStack_b1 & 0xffffff00;
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    _uuid_copy(&uStack_c0,param_4);
    if (lRam0000000100c1b218 != -1) {
      FUN_1009060a0();
    }
    uVar7 = uRam0000000100c1b210;
    puVar13 = &uStack_c0;
    FUN_100011444(puVar13);
    FUN_10082c3fc(uVar7,puVar13,&cf_IsMFiAuthenticated);
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"PeerIsUsingBuiltinService");
  if ((int)uVar7 == 0) {
    uStack_c0 = 0;
    uStack_be = 0;
    uStack_bc = 0;
    uStack_b8 = 0;
    uStack_b4 = 0;
    cStack_b2 = '\0';
    uStack_b1 = uStack_b1 & 0xffffff00;
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    _uuid_copy(&uStack_c0,param_4);
    if (lRam0000000100c1b218 != -1) {
      FUN_1009060a0();
    }
    uVar24 = uRam0000000100c1b210;
    puVar13 = &uStack_c0;
    FUN_100011444(puVar13);
    pcVar14 = (char *)auStack_188;
    FUN_1001ec44c(pcVar14,0x12);
    pcVar14[0x10] = 'e';
    uVar7 = s_HasBuiltinServices_100a8664d._0_8_;
    pcVar14[0x11] = 's';
    *(undefined8 *)(pcVar14 + 8) = s_HasBuiltinServices_100a8664d._8_8_;
    *(undefined8 *)pcVar14 = uVar7;
    pcVar14[0x12] = '\0';
    FUN_100830608(uVar24,puVar13,auStack_188);
    if (cStack_171 < '\0') {
      __ZdlPv(auStack_188[0]);
    }
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"PeerIsNotUsingBuiltinService");
  if ((int)uVar7 == 0) {
    uStack_c0 = 0;
    uStack_be = 0;
    uStack_bc = 0;
    uStack_b8 = 0;
    uStack_b4 = 0;
    cStack_b2 = '\0';
    uStack_b1 = uStack_b1 & 0xffffff00;
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    _uuid_copy(&uStack_c0,param_4);
    if (lRam0000000100c1b218 != -1) {
      FUN_1009060a0();
    }
    uVar7 = uRam0000000100c1b210;
    puVar13 = &uStack_c0;
    FUN_100011444(puVar13);
    FUN_10082c3fc(uVar7,puVar13,&cf_HasBuiltinServices);
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"DisconnectClassicDevice");
  if ((int)uVar7 == 0) {
    uStack_c0 = 0;
    uStack_be = 0;
    uStack_bc = 0;
    uStack_b8 = 0;
    uStack_b4 = 0;
    cStack_b2 = '\0';
    uStack_b1 = 0;
    uStack_ad = 0;
    uStack_a9 = 0;
    _xpc_dictionary_get_string(param_4,"kDeviceAddress");
    _strlen();
    puVar13 = &uStack_c0;
    FUN_1001ec44c(puVar13,param_4);
    _memmove();
    *(undefined1 *)((long)puVar13 + (long)param_4) = 0;
    bStack_13c = 0;
    bStack_13b = 0;
    bStack_140 = 0;
    bStack_13f = 0;
    bStack_13e = 0;
    bStack_13d = 0;
    pbVar15 = &bStack_140;
    FUN_100118ae4(pbVar15,&uStack_c0);
    uVar7 = uRam0000000100cae468;
    if (((ulong)pbVar15 & 1) == 0) {
      uVar24 = uRam0000000100cae468;
      _os_log_type_enabled(uRam0000000100cae468,0x10);
      if ((int)uVar24 != 0) {
        FUN_1009065f4(uVar7);
      }
      goto LAB_10088d530;
    }
    if (lRam0000000100c1b238 != -1) {
      FUN_100906084();
    }
    plVar16 = plRam0000000100c1b230;
    FUN_10010bebc(plRam0000000100c1b230,&bStack_140,1);
    uVar7 = uRam0000000100cae468;
    if (plVar16 == (long *)0x0) {
      uVar24 = uRam0000000100cae468;
      _os_log_type_enabled(uRam0000000100cae468,0x10);
      if ((int)uVar24 != 0) {
        FUN_1000c6c24(&uStack_e0,&bStack_140);
        FUN_100906648(&uStack_e0,&uStack_120,uVar7);
      }
      goto LAB_10088d530;
    }
    if (lRam0000000100c1b990 != -1) {
      FUN_100906620();
    }
    uVar27 = uRam0000000100c1b988;
    FUN_1000cbb48(uRam0000000100c1b988,plVar16);
    uVar7 = uRam0000000100cae468;
    if ((uVar27 & 1) != 0) {
      if (lRam0000000100c1b4d8 != -1) {
        FUN_10090630c();
      }
      FUN_100645c70(uRam0000000100c1b4d0,plVar16,0xffffffff);
      goto LAB_10088d530;
    }
    uVar24 = uRam0000000100cae468;
    _os_log_type_enabled(uRam0000000100cae468,0);
    if ((int)uVar24 == 0) goto LAB_10088d530;
    FUN_10010aa84(&uStack_e0,plVar16);
    uStack_120._0_2_ = SUB82(_UNK_100930b20,0);
    uStack_120._2_2_ = (undefined2)((ulong)_UNK_100930b20 >> 0x10);
    uStack_120._4_2_ = (short)&uStack_e0;
    uStack_120._6_2_ = (short)((ulong)&uStack_e0 >> 0x10);
    sStack_118 = (short)((ulong)&uStack_e0 >> 0x20);
    sStack_116 = (short)((ulong)&uStack_e0 >> 0x30);
    pcVar14 = "Ignoring disconnection request as device \"%{public}s\" is not connected";
    puVar21 = &uStack_120;
    uVar24 = 0xc;
LAB_10088d200:
    __os_log_impl(0x100000000,uVar7,0,pcVar14,puVar21,uVar24);
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"EnableBTSync");
  if ((int)uVar7 == 0) {
    puVar17 = PTR__OBJC_CLASS___NSUUID_100bfc8e0;
    _objc_alloc();
    puVar8 = param_4;
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    objc_stub::FUN_100918d60((ID)puVar17,puVar8);
    _xpc_dictionary_get_int64(param_4,"kPeriod");
    FUN_1000071f0();
    (**(code **)(*param_4 + 0x408))();
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"EnableBTSyncInMs");
  if ((int)uVar7 == 0) {
    puVar17 = PTR__OBJC_CLASS___NSUUID_100bfc8e0;
    _objc_alloc();
    puVar8 = param_4;
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    objc_stub::FUN_100918d60((ID)puVar17,puVar8);
    _xpc_dictionary_get_int64(param_4,"kPeriod");
    FUN_1000071f0();
    (**(code **)(*param_4 + 0x408))();
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"DevMgmtPipeConnected");
  if ((int)uVar7 == 0) {
    puVar17 = PTR__OBJC_CLASS___NSUUID_100bfc8e0;
    _objc_alloc();
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    IVar22 = objc_stub::FUN_100918d60((ID)puVar17,param_4);
    if (lRam0000000100c1b258 != -1) {
      FUN_1009065dc();
    }
    FUN_10066c538(uRam0000000100c1b250,1);
    objc_stub::FUN_1009117c0(*(ID *)(param_2 + 0x10),IVar22);
    if (lRam0000000100c1b298 != -1) {
      FUN_1009060bc();
    }
    FUN_10041b298(lRam0000000100c1b290,IVar22);
    if (lRam0000000100c1b268 != -1) {
      FUN_1009061ac();
    }
    FUN_1006eb9f4(uRam0000000100c1b260,IVar22);
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"DevMgmtPipeDisconnected");
  if ((int)uVar7 == 0) {
    puVar17 = PTR__OBJC_CLASS___NSUUID_100bfc8e0;
    _objc_alloc();
    _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
    IVar22 = objc_stub::FUN_100918d60((ID)puVar17,param_4);
    if (lRam0000000100c1b258 != -1) {
      FUN_1009065dc();
    }
    FUN_10066c538(uRam0000000100c1b250,0);
    objc_stub::FUN_10091ce20(*(ID *)(param_2 + 0x10),IVar22);
    if (lRam0000000100c1b298 != -1) {
      FUN_1009060bc();
    }
    FUN_10041b724(lRam0000000100c1b290,IVar22);
    if (lRam0000000100c1b268 != -1) {
      FUN_1009061ac();
    }
    FUN_1006ebb30(uRam0000000100c1b260,IVar22);
    goto LAB_10088d530;
  }
  uVar7 = param_3;
  _strcmp(param_3,"VersionInfoRequest");
  if ((int)uVar7 == 0) {
    puVar8 = param_4;
    _xpc_dictionary_get_int64(param_4,"kEasyPairingVersion");
    uStack_c0 = 0;
    uStack_be = 0;
    uStack_bc = 0;
    uStack_b8 = 0;
    uStack_b4 = 0;
    cStack_b2 = '\0';
    uStack_b1 = 0;
    uStack_ad = 0;
    uStack_a9 = 0;
    _xpc_dictionary_get_string(param_4,"kCloudAccount");
    FUN_1002274a0(&uStack_c0,param_4);
    if (lRam0000000100c1ec38 != -1) {
      FUN_1009065c4();
    }
    uStack_198 = CONCAT17((char)uStack_b1,CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
    uStack_1a0 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
    lStack_190 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
    FUN_1003f7938(uRam0000000100c1ec30,(uint)puVar8 & 0xff,&uStack_1a0);
    uVar7 = uStack_1a0;
    lVar25 = lStack_190;
  }
  else {
    uVar7 = param_3;
    _strcmp(param_3,"VersionInfoResponse");
    if ((int)uVar7 != 0) {
      uVar7 = param_3;
      _strcmp(param_3,"ClassicPairStateRequest");
      if ((int)uVar7 == 0) {
        uStack_c0 = 0;
        uStack_be = 0;
        uStack_bc = 0;
        uStack_b8 = 0;
        uStack_b4 = 0;
        cStack_b2 = '\0';
        uStack_b1 = 0;
        uStack_ad = 0;
        uStack_a9 = 0;
        _xpc_dictionary_get_string(param_4,"kDeviceAddress");
        FUN_1002274a0(&uStack_c0,param_4);
        uStack_e0 = (ulong)uStack_e0._6_2_ << 0x30;
        puVar21 = &uStack_e0;
        FUN_100118ae4(puVar21,&uStack_c0);
        uVar7 = uRam0000000100cae4c8;
        if (((ulong)puVar21 & 1) == 0) {
          uVar24 = uRam0000000100cae4c8;
          _os_log_type_enabled(uRam0000000100cae4c8,0x10);
          if ((int)uVar24 != 0) {
            FUN_100906598(uVar7);
          }
        }
        else {
          if (lRam0000000100c1ec38 != -1) {
            FUN_1009065c4();
          }
          FUN_1003f7e50(uRam0000000100c1ec30,&uStack_e0);
        }
        goto LAB_10088d530;
      }
      uVar7 = param_3;
      _strcmp(param_3,"ClassicPairStateResponse");
      if ((int)uVar7 == 0) {
        uStack_c0 = 0;
        uStack_be = 0;
        uStack_bc = 0;
        uStack_b8 = 0;
        uStack_b4 = 0;
        cStack_b2 = '\0';
        uStack_b1 = 0;
        uStack_ad = 0;
        uStack_a9 = 0;
        puVar8 = param_4;
        _xpc_dictionary_get_string(param_4,"kDeviceAddress");
        FUN_1002274a0(&uStack_c0,puVar8);
        _xpc_dictionary_get_int64(param_4,"kDevicePairState");
        uStack_e0 = (ulong)uStack_e0._6_2_ << 0x30;
        puVar21 = &uStack_e0;
        FUN_100118ae4(puVar21,&uStack_c0);
        uVar7 = uRam0000000100cae4c8;
        if (((ulong)puVar21 & 1) == 0) {
          uVar24 = uRam0000000100cae4c8;
          _os_log_type_enabled(uRam0000000100cae4c8,0x10);
          if ((int)uVar24 != 0) {
            FUN_10090656c(uVar7);
          }
        }
        else {
          if (lRam0000000100c1b238 != -1) {
            FUN_100906084();
          }
          plVar16 = plRam0000000100c1b230;
          FUN_10010bebc(plRam0000000100c1b230,&uStack_e0,1);
          if (lRam0000000100c1b298 != -1) {
            FUN_1009060bc();
          }
          FUN_10041b9f0(lRam0000000100c1b290,plVar16,(uint)param_4 & 0xff);
        }
        goto LAB_10088d530;
      }
      uVar7 = param_3;
      _strcmp(param_3,"StoreClassicLinkKeyRequest");
      if ((int)uVar7 == 0) {
        uStack_c0 = 0;
        uStack_be = 0;
        uStack_bc = 0;
        uStack_b8 = 0;
        uStack_b4 = 0;
        cStack_b2 = '\0';
        uStack_b1 = 0;
        uStack_ad = 0;
        uStack_a9 = 0;
        puVar8 = param_4;
        _xpc_dictionary_get_string(param_4,"kDeviceAddress");
        FUN_1002274a0(&uStack_c0,puVar8);
        uStack_e0 = 0;
        uStack_d8 = 0;
        lStack_d0 = 0;
        puVar8 = param_4;
        _xpc_dictionary_get_string(param_4,"kDeviceName");
        FUN_1002274a0(&uStack_e0,puVar8);
        _xpc_dictionary_get_value(param_4,"kDeviceLinkKey");
        uStack_158 = (ulong)uStack_158._6_2_ << 0x30;
        puVar21 = &uStack_158;
        FUN_100118ae4(puVar21,&uStack_c0);
        uVar7 = uRam0000000100cae4c8;
        if (((ulong)puVar21 & 1) == 0) {
          uVar24 = uRam0000000100cae4c8;
          _os_log_type_enabled(uRam0000000100cae4c8,0x10);
          if ((int)uVar24 != 0) {
            FUN_100906448(uVar7);
          }
          uStack_1d8 = CONCAT17((char)uStack_b1,CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
          uStack_1e0 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
          lStack_1d0 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
          FUN_10088c604(param_2,&uStack_1e0,1);
          uVar7 = uStack_1e0;
          lVar25 = lStack_1d0;
        }
        else {
          puVar8 = param_4;
          _xpc_array_get_count();
          uVar7 = uRam0000000100cae4c8;
          if ((param_4 != (ulong *)0x0) && (puVar8 == (ulong *)0x10)) {
            lVar25 = 0;
            uStack_f0 = 0;
            uStack_e8 = 0;
            uStack_100 = 0;
            uStack_f8 = 0;
            do {
              puVar8 = param_4;
              _xpc_array_get_int64(param_4,lVar25);
              *(char *)((long)&uStack_f0 + lVar25) = (char)puVar8;
              lVar25 = lVar25 + 1;
            } while (lVar25 != 0x10);
            if (lRam0000000100c1b238 != -1) {
              FUN_100906084();
            }
            plVar16 = plRam0000000100c1b230;
            FUN_10010bebc(plRam0000000100c1b230,&uStack_158,1);
            if (uStack_f0 == uStack_100 && uStack_e8 == uStack_f8) {
              if ((plVar16 == (long *)0x0) ||
                 (plVar18 = plVar16, FUN_1000cbaf4(), (int)plVar18 == 0)) {
                uVar7 = uRam0000000100cae4c8;
                uVar24 = uRam0000000100cae4c8;
                _os_log_type_enabled(uRam0000000100cae4c8,0x10);
                if ((int)uVar24 != 0) {
                  FUN_100906514(uVar7);
                }
              }
              else {
                if (lRam0000000100c1b298 != -1) {
                  FUN_1009060bc();
                }
                *(undefined1 *)(lRam0000000100c1b290 + 0x1af) = 2;
                if (lRam0000000100c1b4c8 != -1) {
                  FUN_10090648c();
                }
                uVar27 = uRam0000000100c1b4c0;
                FUN_10010751c(uRam0000000100c1b4c0,plVar16);
                uVar7 = uRam0000000100cae4c8;
                uVar24 = uRam0000000100cae4c8;
                _os_log_type_enabled(uRam0000000100cae4c8,0x10);
                if ((int)uVar27 == 0) {
                  if ((int)uVar24 != 0) {
                    FUN_1009064a4(uVar7);
                  }
                  if (lRam0000000100c1b9b0 != -1) {
                    FUN_1009064d0();
                  }
                  FUN_1007859a0(uRam0000000100c1b9a8,plVar16);
                }
                else {
                  if ((int)uVar24 != 0) {
                    FUN_1009064e8(uVar7);
                  }
                  if (lRam0000000100c1b4c8 != -1) {
                    FUN_10090648c();
                  }
                  FUN_1006078d8(uRam0000000100c1b4c0,plVar16,0);
                }
              }
              goto LAB_10088d530;
            }
            uStack_138 = 0;
            uStack_134 = 0;
            uStack_132 = 0;
            bStack_140 = 0;
            bStack_13f = 0;
            bStack_13e = 0;
            bStack_13d = 0;
            bStack_13c = 0;
            bStack_13b = 0;
            uStack_13a = 0;
            uStack_130 = 0;
            FUN_10014cb48(&bStack_140);
            if (lRam0000000100c1bd10 != -1) {
              FUN_100906474();
            }
            uVar7 = uRam0000000100c1bd08;
            FUN_10017aa9c(uRam0000000100c1bd08,plVar16,&bStack_140);
            if ((int)uVar7 == 0x96) {
              if (lRam0000000100c1b4c8 != -1) {
                FUN_10090648c();
              }
              uVar27 = uRam0000000100c1b4c0;
              FUN_10010751c(uRam0000000100c1b4c0,plVar16);
              if ((uVar27 & 1) != 0) goto LAB_10088d6fc;
              thunk_FUN_1007771f0(&uStack_120,&uStack_f0,5);
              FUN_10017ac4c(&bStack_140,&uStack_120);
              FUN_100043ed4(&uStack_120);
              if (lRam0000000100c1bd10 != -1) {
                FUN_100906474();
              }
              uVar7 = uRam0000000100c1bd08;
              FUN_10078d798(uRam0000000100c1bd08,plVar16,&bStack_140,0);
              iVar6 = (int)uVar7;
              if (iVar6 == 0) {
                uStack_380 = (undefined **)0x0;
                FUN_100035440(&uStack_380);
                uStack_120._0_2_ = SUB82(uStack_380,0);
                uStack_120._2_2_ = (undefined2)((ulong)uStack_380 >> 0x10);
                uStack_120._4_2_ = (short)((int)uStack_380 >> 0x1f);
                sStack_118 = uStack_380._4_2_;
                sStack_116 = uStack_380._4_2_ >> 0xf;
                uStack_120._6_2_ = uStack_120._4_2_;
                sStack_114 = sStack_116;
                sStack_112 = sStack_116;
                FUN_1005e868c(plVar16,&uStack_e0,&uStack_120);
              }
              uVar7 = uRam0000000100cae4c8;
              bVar4 = iVar6 != 0;
              uVar24 = uRam0000000100cae4c8;
              _os_log_type_enabled(uRam0000000100cae4c8,0);
              if ((int)uVar24 != 0) {
                pcVar14 = "Successfully stored";
                if (iVar6 != 0) {
                  pcVar14 = "Failed to store";
                }
                uStack_120._0_2_ = (undefined2)_UNK_100930b18;
                uStack_120._2_2_ = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
                uStack_120._4_2_ = (short)pcVar14;
                uStack_120._6_2_ = (short)((ulong)pcVar14 >> 0x10);
                sStack_118 = (short)((ulong)pcVar14 >> 0x20);
                sStack_116 = 0;
                sStack_114 = 0x820;
                sStack_112 = (short)&uStack_c0;
                uStack_110 = (undefined2)((ulong)&uStack_c0 >> 0x10);
                uStack_10e = (undefined4)((ulong)&uStack_c0 >> 0x20);
                __os_log_impl(0x100000000,uVar7,0,"%s classic link key for address %s",&uStack_120,
                              0x16);
              }
            }
            else {
LAB_10088d6fc:
              uVar7 = uRam0000000100cae4c8;
              uVar24 = uRam0000000100cae4c8;
              _os_log_type_enabled(uRam0000000100cae4c8,0);
              bVar4 = false;
              if ((int)uVar24 != 0) {
                if (lRam0000000100c1b4c8 != -1) {
                  FUN_10090648c();
                }
                uVar27 = uRam0000000100c1b4c0;
                FUN_10010751c(uRam0000000100c1b4c0,plVar16);
                uStack_120._0_2_ = (undefined2)_UNK_1009304f0;
                uStack_120._2_2_ = (undefined2)((ulong)_UNK_1009304f0 >> 0x10);
                uStack_120._4_2_ = (short)uVar27;
                uStack_120._6_2_ = (short)(uVar27 >> 0x10);
                sStack_118 = 0x820;
                sStack_116 = (short)&uStack_c0;
                sStack_114 = (short)((ulong)&uStack_c0 >> 0x10);
                sStack_112 = (short)((ulong)&uStack_c0 >> 0x20);
                uStack_110 = (undefined2)((ulong)&uStack_c0 >> 0x30);
                __os_log_impl(0x100000000,uVar7,0,
                              "Already stored classic link key (Magic Paired: %d) for address: %s",
                              &uStack_120,0x12);
                bVar4 = false;
              }
            }
            uStack_218 = CONCAT17((char)uStack_b1,CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)))
            ;
            uStack_220 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
            lStack_210 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
            FUN_10088c604(param_2,&uStack_220,bVar4);
            uVar7 = uStack_220;
            lVar25 = lStack_210;
joined_r0x00010088efbc:
            if (lVar25 < 0) {
              __ZdlPv(uVar7);
            }
            FUN_100043ed4(&bStack_140);
            goto LAB_10088d530;
          }
          uVar24 = uRam0000000100cae4c8;
          _os_log_type_enabled(uRam0000000100cae4c8,0x10);
          if ((int)uVar24 != 0) {
            FUN_100906540(uVar7);
          }
          uStack_1f8 = CONCAT17((char)uStack_b1,CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
          uStack_200 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
          lStack_1f0 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
          FUN_10088c604(param_2,&uStack_200,1);
          uVar7 = uStack_200;
          lVar25 = lStack_1f0;
        }
      }
      else {
        uVar7 = param_3;
        _strcmp(param_3,"StoreClassicLinkKeyRequestExtended");
        if ((int)uVar7 == 0) {
          uStack_c0 = 0;
          uStack_be = 0;
          uStack_bc = 0;
          uStack_b8 = 0;
          uStack_b4 = 0;
          cStack_b2 = '\0';
          uStack_b1 = 0;
          uStack_ad = 0;
          uStack_a9 = 0;
          puVar8 = param_4;
          _xpc_dictionary_get_string(param_4,"kDeviceAddress");
          FUN_1002274a0(&uStack_c0,puVar8);
          uStack_e0 = 0;
          uStack_d8 = 0;
          lStack_d0 = 0;
          puVar8 = param_4;
          _xpc_dictionary_get_string(param_4,"kDeviceName");
          FUN_1002274a0(&uStack_e0,puVar8);
          puVar8 = param_4;
          _xpc_dictionary_get_value(param_4,"kDeviceLinkKey");
          puVar28 = param_4;
          _xpc_dictionary_get_int64(param_4,"kDeviceServiceMask");
          _xpc_dictionary_get_int64(param_4,"kClassOfDeviceMask");
          uStack_158 = (ulong)uStack_158._6_2_ << 0x30;
          puVar21 = &uStack_158;
          FUN_100118ae4(puVar21,&uStack_c0);
          uVar7 = uRam0000000100cae4c8;
          if (((ulong)puVar21 & 1) == 0) {
            uVar24 = uRam0000000100cae4c8;
            _os_log_type_enabled(uRam0000000100cae4c8,0x10);
            if ((int)uVar24 != 0) {
              FUN_100906448(uVar7);
            }
            uStack_238 = CONCAT17((char)uStack_b1,CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)))
            ;
            uStack_240 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
            lStack_230 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
            FUN_10088c604(param_2,&uStack_240,1);
            uVar7 = uStack_240;
            lVar25 = lStack_230;
          }
          else {
            puVar9 = puVar8;
            _xpc_array_get_count();
            uVar7 = uRam0000000100cae4c8;
            if ((puVar8 != (ulong *)0x0) && (puVar9 == (ulong *)0x10)) {
              lVar25 = 0;
              uStack_f0 = 0;
              uStack_e8 = 0;
              uStack_100 = 0;
              uStack_f8 = 0;
              do {
                puVar9 = puVar8;
                _xpc_array_get_int64(puVar8,lVar25);
                *(char *)((long)&uStack_f0 + lVar25) = (char)puVar9;
                lVar25 = lVar25 + 1;
              } while (lVar25 != 0x10);
              if (lRam0000000100c1b238 != -1) {
                FUN_100906084();
              }
              plVar16 = plRam0000000100c1b230;
              FUN_10010bebc(plRam0000000100c1b230,&uStack_158,1);
              if (uStack_f0 == uStack_100 && uStack_e8 == uStack_f8) {
                if ((plVar16 == (long *)0x0) ||
                   (plVar18 = plVar16, FUN_1000cbaf4(), (int)plVar18 == 0)) {
                  uVar7 = uRam0000000100cae4c8;
                  uVar24 = uRam0000000100cae4c8;
                  _os_log_type_enabled(uRam0000000100cae4c8,0x10);
                  if ((int)uVar24 != 0) {
                    FUN_100906514(uVar7);
                  }
                }
                else {
                  if (lRam0000000100c1b298 != -1) {
                    FUN_1009060bc();
                  }
                  *(undefined1 *)(lRam0000000100c1b290 + 0x1af) = 2;
                  if (lRam0000000100c1b4c8 != -1) {
                    FUN_10090648c();
                  }
                  uVar27 = uRam0000000100c1b4c0;
                  FUN_10010751c(uRam0000000100c1b4c0,plVar16);
                  uVar7 = uRam0000000100cae4c8;
                  uVar24 = uRam0000000100cae4c8;
                  _os_log_type_enabled(uRam0000000100cae4c8,0x10);
                  if ((int)uVar27 == 0) {
                    if ((int)uVar24 != 0) {
                      FUN_1009064a4(uVar7);
                    }
                    if (lRam0000000100c1b9b0 != -1) {
                      FUN_1009064d0();
                    }
                    FUN_1007859a0(uRam0000000100c1b9a8,plVar16);
                  }
                  else {
                    if ((int)uVar24 != 0) {
                      FUN_1009064e8(uVar7);
                    }
                    if (lRam0000000100c1b4c8 != -1) {
                      FUN_10090648c();
                    }
                    FUN_1006078d8(uRam0000000100c1b4c0,plVar16,0);
                  }
                }
                goto LAB_10088d530;
              }
              if ((int)param_4 != 0) {
                if (lRam0000000100c1b238 != -1) {
                  FUN_100906084();
                }
                FUN_100619428(plRam0000000100c1b230,plVar16,param_4);
              }
              if ((int)puVar28 != 0) {
                uVar5 = 0;
                do {
                  uVar2 = 1 << (ulong)(uVar5 & 0x1f);
                  uVar1 = (uint)puVar28 & uVar2;
                  if (uVar1 != 0) {
                    bStack_140 = 0;
                    bStack_13f = 0;
                    bStack_13e = 0;
                    bStack_13d = '\0';
                    bStack_13c = 0;
                    bStack_13b = '\0';
                    uStack_13a = 0;
                    FUN_100035440(&bStack_140);
                    uStack_120._0_2_ = CONCAT11(bStack_13f,bStack_140);
                    sStack_118 = CONCAT11(bStack_13b,bStack_13c);
                    uStack_120._2_2_ =
                         (undefined2)
                         (CONCAT13(bStack_13d,CONCAT12(bStack_13e,(undefined2)uStack_120)) >> 0x10);
                    uStack_120._4_2_ = (short)((int)(char)bStack_13d >> 7);
                    uStack_120._6_2_ = (short)((int)(char)bStack_13d >> 7);
                    sStack_116 = (short)(char)bStack_13b >> 7;
                    sStack_114 = (short)(char)bStack_13b >> 7;
                    sStack_112 = (short)(char)bStack_13b >> 7;
                    FUN_1005e96cc(plVar16,uVar1,4,&uStack_120,0);
                  }
                  if (0x1e < uVar5) break;
                  uVar1 = (uint)puVar28 & (uVar2 ^ 0xffffffff);
                  puVar28 = (ulong *)(ulong)uVar1;
                  uVar5 = uVar5 + 1;
                } while (uVar1 != 0);
              }
              uStack_138 = 0;
              uStack_134 = 0;
              uStack_132 = 0;
              bStack_140 = 0;
              bStack_13f = 0;
              bStack_13e = 0;
              bStack_13d = 0;
              bStack_13c = 0;
              bStack_13b = 0;
              uStack_13a = 0;
              uStack_130 = 0;
              FUN_10014cb48(&bStack_140);
              if (lRam0000000100c1bd10 != -1) {
                FUN_100906474();
              }
              uVar7 = uRam0000000100c1bd08;
              FUN_10017aa9c(uRam0000000100c1bd08,plVar16,&bStack_140);
              if ((int)uVar7 == 0x96) {
                if (lRam0000000100c1b4c8 != -1) {
                  FUN_10090648c();
                }
                uVar27 = uRam0000000100c1b4c0;
                FUN_10010751c(uRam0000000100c1b4c0,plVar16);
                if ((uVar27 & 1) != 0) goto LAB_10088d9cc;
                thunk_FUN_1007771f0(&uStack_120,&uStack_f0,5);
                FUN_10017ac4c(&bStack_140,&uStack_120);
                FUN_100043ed4(&uStack_120);
                if (lRam0000000100c1bd10 != -1) {
                  FUN_100906474();
                }
                uVar7 = uRam0000000100c1bd08;
                FUN_10078d798(uRam0000000100c1bd08,plVar16,&bStack_140,0);
                iVar6 = (int)uVar7;
                if (iVar6 == 0) {
                  uStack_380 = (undefined **)0x0;
                  FUN_100035440(&uStack_380);
                  uStack_120._0_2_ = SUB82(uStack_380,0);
                  uStack_120._2_2_ = (undefined2)((ulong)uStack_380 >> 0x10);
                  uStack_120._4_2_ = (short)((int)uStack_380 >> 0x1f);
                  sStack_118 = uStack_380._4_2_;
                  sStack_116 = uStack_380._4_2_ >> 0xf;
                  uStack_120._6_2_ = uStack_120._4_2_;
                  sStack_114 = sStack_116;
                  sStack_112 = sStack_116;
                  FUN_1005e868c(plVar16,&uStack_e0,&uStack_120);
                }
                uVar7 = uRam0000000100cae4c8;
                bVar4 = iVar6 != 0;
                uVar24 = uRam0000000100cae4c8;
                _os_log_type_enabled(uRam0000000100cae4c8,0);
                if ((int)uVar24 != 0) {
                  pcVar14 = "Successfully stored";
                  if (iVar6 != 0) {
                    pcVar14 = "Failed to store";
                  }
                  uStack_120._0_2_ = (undefined2)_UNK_100930b18;
                  uStack_120._2_2_ = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
                  uStack_120._4_2_ = (short)pcVar14;
                  uStack_120._6_2_ = (short)((ulong)pcVar14 >> 0x10);
                  sStack_118 = (short)((ulong)pcVar14 >> 0x20);
                  sStack_116 = 0;
                  sStack_114 = 0x820;
                  sStack_112 = (short)&uStack_c0;
                  uStack_110 = (undefined2)((ulong)&uStack_c0 >> 0x10);
                  uStack_10e = (undefined4)((ulong)&uStack_c0 >> 0x20);
                  __os_log_impl(0x100000000,uVar7,0,"%s classic link key for address %s",&uStack_120
                                ,0x16);
                }
              }
              else {
LAB_10088d9cc:
                uVar7 = uRam0000000100cae4c8;
                uVar24 = uRam0000000100cae4c8;
                _os_log_type_enabled(uRam0000000100cae4c8,0);
                bVar4 = false;
                if ((int)uVar24 != 0) {
                  if (lRam0000000100c1b4c8 != -1) {
                    FUN_10090648c();
                  }
                  uVar27 = uRam0000000100c1b4c0;
                  FUN_10010751c(uRam0000000100c1b4c0,plVar16);
                  uStack_120._0_2_ = (undefined2)_UNK_1009304f0;
                  uStack_120._2_2_ = (undefined2)((ulong)_UNK_1009304f0 >> 0x10);
                  uStack_120._4_2_ = (short)uVar27;
                  uStack_120._6_2_ = (short)(uVar27 >> 0x10);
                  sStack_118 = 0x820;
                  sStack_116 = (short)&uStack_c0;
                  sStack_114 = (short)((ulong)&uStack_c0 >> 0x10);
                  sStack_112 = (short)((ulong)&uStack_c0 >> 0x20);
                  uStack_110 = (undefined2)((ulong)&uStack_c0 >> 0x30);
                  __os_log_impl(0x100000000,uVar7,0,
                                "Already stored classic link key (Magic Paired: %d) for address: %s"
                                ,&uStack_120,0x12);
                  bVar4 = false;
                }
              }
              uStack_278 = CONCAT17((char)uStack_b1,
                                    CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
              uStack_280 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
              lStack_270 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
              FUN_10088c604(param_2,&uStack_280,bVar4);
              uVar7 = uStack_280;
              lVar25 = lStack_270;
              goto joined_r0x00010088efbc;
            }
            uVar24 = uRam0000000100cae4c8;
            _os_log_type_enabled(uRam0000000100cae4c8,0x10);
            if ((int)uVar24 != 0) {
              FUN_100906540(uVar7);
            }
            uStack_258 = CONCAT17((char)uStack_b1,CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)))
            ;
            uStack_260 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
            lStack_250 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
            FUN_10088c604(param_2,&uStack_260,1);
            uVar7 = uStack_260;
            lVar25 = lStack_250;
          }
        }
        else {
          uVar7 = param_3;
          _strcmp(param_3,"StoreClassicLinkKeyResponse");
          if ((int)uVar7 == 0) {
            uStack_c0 = 0;
            uStack_be = 0;
            uStack_bc = 0;
            uStack_b8 = 0;
            uStack_b4 = 0;
            cStack_b2 = '\0';
            uStack_b1 = 0;
            uStack_ad = 0;
            uStack_a9 = 0;
            puVar8 = param_4;
            _xpc_dictionary_get_string(param_4,"kDeviceAddress");
            FUN_1002274a0(&uStack_c0,puVar8);
            _xpc_dictionary_get_int64(param_4,"kStoreClassicLinkKeyResult");
            uStack_e0 = (ulong)uStack_e0._6_2_ << 0x30;
            puVar21 = &uStack_e0;
            FUN_100118ae4(puVar21,&uStack_c0);
            uVar7 = uRam0000000100cae4c8;
            if (((ulong)puVar21 & 1) == 0) {
              uVar24 = uRam0000000100cae4c8;
              _os_log_type_enabled(uRam0000000100cae4c8,0x10);
              if ((int)uVar24 != 0) {
                FUN_10090641c(uVar7);
              }
            }
            else {
              if (lRam0000000100c1b238 != -1) {
                FUN_100906084();
              }
              plVar16 = plRam0000000100c1b230;
              FUN_10010bebc(plRam0000000100c1b230,&uStack_e0,1);
              if (lRam0000000100c1b298 != -1) {
                FUN_1009060bc();
              }
              FUN_10041baa8(lRam0000000100c1b290,plVar16,(uint)param_4 & 0xff);
            }
            goto LAB_10088d530;
          }
          uVar7 = param_3;
          _strcmp(param_3,"StoreClassicDeviceSettings");
          if ((int)uVar7 == 0) {
            uStack_c0 = 0;
            uStack_be = 0;
            uStack_bc = 0;
            uStack_b8 = 0;
            uStack_b4 = 0;
            cStack_b2 = '\0';
            uStack_b1 = 0;
            uStack_ad = 0;
            uStack_a9 = 0;
            puVar8 = param_4;
            _xpc_dictionary_get_string(param_4,"kDeviceAddress");
            FUN_1002274a0(&uStack_c0,puVar8);
            uStack_f0 = (ulong)uStack_f0._6_2_ << 0x30;
            puVar21 = &uStack_f0;
            FUN_100118ae4(puVar21,&uStack_c0);
            uVar7 = uRam0000000100cae468;
            if (((ulong)puVar21 & 1) == 0) {
              uVar24 = uRam0000000100cae468;
              _os_log_type_enabled(uRam0000000100cae468,0x10);
              if ((int)uVar24 != 0) {
                FUN_10090637c(uVar7);
              }
            }
            else {
              puVar8 = param_4;
              _xpc_dictionary_get_int64(param_4,"kClassicDeviceMicMode");
              puVar28 = param_4;
              _xpc_dictionary_get_int64(param_4,"kClassicDeviceInEarEnable");
              puVar9 = param_4;
              _xpc_dictionary_get_int64(param_4,"kClassicDeviceDoubleTapMode");
              puVar10 = param_4;
              _xpc_dictionary_get_value(param_4,"kClassicDeviceSettings");
              if (puVar10 == (ulong *)0x0) {
                IVar19 = 0xffffffff;
                iStack_400 = -1;
                iStack_3fc = -1;
                IVar22 = 0xffffffff;
                iStack_3f8 = -1;
                iStack_3f4 = -1;
              }
              else {
                puVar11 = puVar10;
                thunk_FUN_100029f7c();
                IVar22 = objc_stub::FUN_100911f40((ID)puVar11);
                IVar22 = objc_stub::FUN_100914380(IVar22,&cf_kCfgDoubleClickInt);
                if ((int)IVar22 == 0) {
                  iStack_3f8 = -1;
                }
                else {
                  IVar22 = objc_stub::FUN_10091b3a0((ID)puVar11,&cf_kCfgDoubleClickInt);
                  IVar22 = objc_stub::FUN_100918ee0(IVar22);
                  iStack_3f8 = (int)IVar22;
                }
                IVar22 = objc_stub::FUN_100911f40((ID)puVar11);
                IVar22 = objc_stub::FUN_100914380(IVar22,&cf_kCfgClickHold);
                if ((int)IVar22 == 0) {
                  iStack_3f4 = -1;
                }
                else {
                  IVar22 = objc_stub::FUN_10091b3a0((ID)puVar11,&cf_kCfgClickHold);
                  IVar22 = objc_stub::FUN_100918ee0(IVar22);
                  iStack_3f4 = (int)IVar22;
                }
                IVar22 = objc_stub::FUN_100911f40((ID)puVar11);
                IVar22 = objc_stub::FUN_100914380(IVar22,&cf_kCfgClickHoldInt);
                if ((int)IVar22 == 0) {
                  iStack_3fc = -1;
                }
                else {
                  IVar22 = objc_stub::FUN_10091b3a0((ID)puVar11,&cf_kCfgClickHoldInt);
                  IVar22 = objc_stub::FUN_100918ee0(IVar22);
                  iStack_3fc = (int)IVar22;
                }
                IVar22 = objc_stub::FUN_100911f40((ID)puVar11);
                IVar22 = objc_stub::FUN_100914380(IVar22,&cf_kCfgListenModeCfgs);
                if ((int)IVar22 == 0) {
                  IVar22 = 0xffffffff;
                }
                else {
                  IVar22 = objc_stub::FUN_10091b3a0((ID)puVar11,&cf_kCfgListenModeCfgs);
                  IVar22 = objc_stub::FUN_100918ee0(IVar22);
                }
                IVar19 = objc_stub::FUN_100911f40((ID)puVar11);
                IVar19 = objc_stub::FUN_100914380(IVar19,&cf_kCfgOneBudANCMode);
                if ((int)IVar19 == 0) {
                  iStack_400 = -1;
                }
                else {
                  IVar19 = objc_stub::FUN_10091b3a0((ID)puVar11,&cf_kCfgOneBudANCMode);
                  IVar19 = objc_stub::FUN_100918ee0(IVar19);
                  iStack_400 = (int)IVar19;
                }
                IVar19 = objc_stub::FUN_100911f40((ID)puVar11);
                IVar19 = objc_stub::FUN_100914380(IVar19,&cf_kCfgListenMode);
                if ((int)IVar19 == 0) {
                  IVar19 = 0xffffffff;
                }
                else {
                  IVar19 = objc_stub::FUN_10091b3a0((ID)puVar11,&cf_kCfgListenMode);
                  IVar19 = objc_stub::FUN_100918ee0(IVar19);
                }
              }
              uStack_e0 = 0;
              uStack_d8 = 0;
              lStack_d0 = 0;
              _xpc_dictionary_get_string(param_4,"kDeviceName");
              FUN_1002274a0(&uStack_e0,param_4);
              if (lRam0000000100c1b238 != -1) {
                FUN_100906084();
              }
              plVar16 = plRam0000000100c1b230;
              FUN_10010bebc(plRam0000000100c1b230,&uStack_f0,1);
              if ((plVar16 == (long *)0x0) ||
                 (plVar18 = plVar16, FUN_1000cbaf4(), (int)plVar18 == 0)) {
                uVar7 = uRam0000000100cae468;
                uVar24 = uRam0000000100cae468;
                _os_log_type_enabled(uRam0000000100cae468,0x10);
                if ((int)uVar24 != 0) {
                  FUN_1009063a8(&uStack_a9,&uStack_c0,uVar7);
                }
              }
              else {
                plVar18 = plVar16;
                FUN_1001084f4();
                if (((uint)(puVar28 != (ulong *)0x0) != (uint)plVar18) &&
                   (plVar18 = plVar16, FUN_1001070b4(plVar16,1), (int)plVar18 != 0)) {
                  if (lRam0000000100c1b298 != -1) {
                    FUN_1009060bc();
                  }
                  FUN_10041cabc(lRam0000000100c1b290,plVar16,puVar28 != (ulong *)0x0,3);
                }
                plVar18 = plVar16;
                FUN_1001082b0();
                if ((int)plVar18 != (int)puVar8) {
                  if (lRam0000000100c1b298 != -1) {
                    FUN_1009060bc();
                  }
                  FUN_10041c5f4(lRam0000000100c1b290,plVar16,puVar8,3);
                }
                plVar18 = plVar16;
                FUN_100108124();
                uVar5 = (uint)puVar9;
                if (((uint)plVar18 != uVar5) &&
                   (plVar18 = plVar16, FUN_1001070b4(plVar16,0xe), (int)plVar18 != 0)) {
                  if (lRam0000000100c1b298 != -1) {
                    FUN_1009060bc();
                  }
                  FUN_10041c8a4(lRam0000000100c1b290,plVar16,uVar5 >> 8 & 0xff,uVar5 & 0xff,3);
                }
                FUN_1000de164(&uStack_120,plVar16);
                puVar13 = (undefined2 *)&uStack_120;
                FUN_100794220(puVar13,&uStack_e0);
                if (cStack_109 < '\0') {
                  __ZdlPv(CONCAT26(uStack_120._6_2_,
                                   CONCAT24(uStack_120._4_2_,
                                            CONCAT22(uStack_120._2_2_,(undefined2)uStack_120))));
                }
                uVar7 = uRam0000000100cae468;
                if (((ulong)puVar13 & 1) == 0) {
                  uVar24 = uRam0000000100cae468;
                  _os_log_type_enabled(uRam0000000100cae468,0);
                  if ((int)uVar24 != 0) {
                    FUN_1000de164(&uStack_120,plVar16);
                    puVar13 = (undefined2 *)
                              CONCAT26(uStack_120._6_2_,
                                       CONCAT24(uStack_120._4_2_,
                                                CONCAT22(uStack_120._2_2_,(undefined2)uStack_120)));
                    if (-1 < cStack_109) {
                      puVar13 = (undefined2 *)&uStack_120;
                    }
                    bStack_140 = (byte)_UNK_100930b18;
                    bStack_13f = (byte)((ulong)_UNK_100930b18 >> 8);
                    bStack_13e = (byte)((ulong)_UNK_100930b18 >> 0x10);
                    bStack_13d = (byte)((ulong)_UNK_100930b18 >> 0x18);
                    bStack_13c = (byte)puVar13;
                    bStack_13b = (byte)((ulong)puVar13 >> 8);
                    uStack_13a = (undefined2)((ulong)puVar13 >> 0x10);
                    uStack_138 = (undefined4)((ulong)puVar13 >> 0x20);
                    uStack_134 = 0x820;
                    uStack_132 = SUB82(&uStack_e0,0);
                    uStack_130 = (undefined4)((ulong)&uStack_e0 >> 0x10);
                    uStack_12c = (undefined2)((ulong)&uStack_e0 >> 0x30);
                    __os_log_impl(0x100000000,uVar7,0,
                                  "StoreClassicDeviceSettings update Device name on Watch side only, oldName = %s, newName = %s"
                                  ,&bStack_140,0x16);
                    if (cStack_109 < '\0') {
                      __ZdlPv(CONCAT26(uStack_120._6_2_,
                                       CONCAT24(uStack_120._4_2_,
                                                CONCAT22(uStack_120._2_2_,(undefined2)uStack_120))))
                      ;
                    }
                  }
                  FUN_1005e8f20(plVar16,&uStack_e0,0);
                  FUN_1005e98dc(plVar16,&uStack_e0);
                }
                if (puVar10 != (ulong *)0x0) {
                  if (((iStack_3f4 != -1) &&
                      (plVar18 = plVar16, FUN_100105890(), (int)plVar18 != iStack_3f4)) &&
                     (plVar18 = plVar16, FUN_1001070b4(plVar16,0x1e), (int)plVar18 != 0)) {
                    if (lRam0000000100c1b298 != -1) {
                      FUN_1009060bc();
                    }
                    FUN_100410e08(lRam0000000100c1b290,plVar16,0x16,iStack_3f4,3);
                  }
                  plVar18 = plVar16;
                  FUN_1001070b4(plVar16,0x2b);
                  uVar5 = (uint)plVar18;
                  if (iStack_3f8 == -1) {
                    uVar5 = 1;
                  }
                  if ((((uVar5 & 1) == 0) &&
                      (plVar18 = plVar16, FUN_1005f8d64(), (int)plVar18 != iStack_3f8)) &&
                     ((plVar18 = plVar16, FUN_1001070b4(plVar16,0x1d), ((ulong)plVar18 & 1) != 0 ||
                      (plVar18 = plVar16, FUN_10010531c(plVar16,0x80), (int)plVar18 != 0)))) {
                    if (lRam0000000100c1b298 != -1) {
                      FUN_1009060bc();
                    }
                    FUN_100410e08(lRam0000000100c1b290,plVar16,0x17,iStack_3f8,3);
                  }
                  plVar18 = plVar16;
                  FUN_1001070b4(plVar16,0x2b);
                  uVar5 = (uint)plVar18;
                  if (iStack_3fc == -1) {
                    uVar5 = 1;
                  }
                  if ((((uVar5 & 1) == 0) &&
                      (plVar18 = plVar16, FUN_1005f8dac(), (int)plVar18 != iStack_3fc)) &&
                     ((plVar18 = plVar16, FUN_1001070b4(plVar16,0x1e), ((ulong)plVar18 & 1) != 0 ||
                      (plVar18 = plVar16, FUN_10010531c(plVar16,0x80), (int)plVar18 != 0)))) {
                    if (lRam0000000100c1b298 != -1) {
                      FUN_1009060bc();
                    }
                    FUN_100410e08(lRam0000000100c1b290,plVar16,0x18,iStack_3fc,3);
                  }
                  if ((((int)IVar22 != -1) &&
                      (plVar18 = plVar16, FUN_100108268(), (int)plVar18 != (int)IVar22)) &&
                     (plVar18 = plVar16, FUN_1001070b4(plVar16,0x1c), (int)plVar18 != 0)) {
                    if (lRam0000000100c1b298 != -1) {
                      FUN_1009060bc();
                    }
                    FUN_100410e08(lRam0000000100c1b290,plVar16,0x1a,IVar22,3);
                  }
                  plVar18 = plVar16;
                  FUN_1001070b4(plVar16,0x2b);
                  uVar5 = (uint)plVar18;
                  if (iStack_400 == -1) {
                    uVar5 = 1;
                  }
                  if ((((uVar5 & 1) == 0) &&
                      (plVar18 = plVar16, FUN_1005f8df4(), iStack_400 != (int)plVar18)) &&
                     ((plVar18 = plVar16, FUN_1001070b4(plVar16,0x10), (int)plVar18 != 0 &&
                      (plVar18 = plVar16, FUN_1001070b4(plVar16,1), (int)plVar18 != 0)))) {
                    if (lRam0000000100c1b298 != -1) {
                      FUN_1009060bc();
                    }
                    FUN_100410e08(lRam0000000100c1b290,plVar16,0x1b,iStack_400,3);
                  }
                  if ((((int)IVar19 != -1) &&
                      (plVar18 = plVar16, FUN_100108220(), (int)plVar18 != (int)IVar19)) &&
                     ((plVar18 = plVar16, FUN_1001070b4(plVar16,0x10), (int)plVar18 != 0 &&
                      (plVar18 = plVar16, FUN_1001070b4(plVar16,0x11), (int)plVar18 != 0)))) {
                    if (lRam0000000100c1b298 != -1) {
                      FUN_1009060bc();
                    }
                    FUN_100410e08(lRam0000000100c1b290,plVar16,0xd,IVar19,3);
                  }
                }
              }
            }
            goto LAB_10088d530;
          }
          uVar7 = param_3;
          _strcmp(param_3,"ClassicDeviceUnexpectedDisconnection");
          if ((int)uVar7 == 0) {
            uStack_c0 = 0;
            uStack_be = 0;
            uStack_bc = 0;
            uStack_b8 = 0;
            uStack_b4 = 0;
            cStack_b2 = '\0';
            uStack_b1 = 0;
            uStack_ad = 0;
            uStack_a9 = 0;
            _xpc_dictionary_get_string(param_4,"kDeviceAddress");
            FUN_1002274a0(&uStack_c0,param_4);
            bStack_13c = 0;
            bStack_13b = 0;
            bStack_140 = 0;
            bStack_13f = 0;
            bStack_13e = 0;
            bStack_13d = 0;
            pbVar15 = &bStack_140;
            FUN_100118ae4(pbVar15,&uStack_c0);
            uVar7 = uRam0000000100cae4c8;
            if (((ulong)pbVar15 & 1) == 0) {
              uVar24 = uRam0000000100cae4c8;
              _os_log_type_enabled(uRam0000000100cae4c8,0x10);
              if ((int)uVar24 != 0) {
                FUN_100906350(uVar7);
              }
            }
            else {
              if (lRam0000000100c1b238 != -1) {
                FUN_100906084();
              }
              plVar16 = plRam0000000100c1b230;
              FUN_10010bebc(plRam0000000100c1b230,&bStack_140,1);
              if ((plVar16 == (long *)0x0) ||
                 (plVar18 = plVar16, FUN_1000cbaf4(), uVar7 = uRam0000000100cae4c8,
                 (int)plVar18 == 0)) {
                uVar7 = uRam0000000100cae4c8;
                uVar24 = uRam0000000100cae4c8;
                _os_log_type_enabled(uRam0000000100cae4c8,0x10);
                if ((int)uVar24 != 0) {
                  FUN_100906324(uVar7);
                }
              }
              else {
                uVar24 = uRam0000000100cae4c8;
                _os_log_type_enabled(uRam0000000100cae4c8,0);
                if ((int)uVar24 != 0) {
                  FUN_10010aa84(&uStack_e0,plVar16);
                  plVar18 = plVar16;
                  FUN_1000cb9c8();
                  pcVar14 = "is";
                  if ((int)plVar18 == 0) {
                    pcVar14 = "not";
                  }
                  uStack_120._0_2_ = (undefined2)_UNK_1009316b0;
                  uStack_120._2_2_ = (undefined2)((ulong)_UNK_1009316b0 >> 0x10);
                  uStack_120._4_2_ = (short)&uStack_e0;
                  uStack_120._6_2_ = (short)((ulong)&uStack_e0 >> 0x10);
                  sStack_118 = (short)((ulong)&uStack_e0 >> 0x20);
                  sStack_116 = (short)((ulong)&uStack_e0 >> 0x30);
                  sStack_114 = 0x820;
                  sStack_112 = (short)pcVar14;
                  uStack_110 = (undefined2)((ulong)pcVar14 >> 0x10);
                  uStack_10e = (undefined4)((ulong)pcVar14 >> 0x20);
                  __os_log_impl(0x100000000,uVar7,0,
                                "ClassicDeviceUnexpectedDisconnection: device %{public}s %s connected"
                                ,&uStack_120,0x16);
                }
                plVar18 = plVar16;
                FUN_1000cb9c8();
                if ((int)plVar18 != 0) {
                  if (lRam0000000100c1b298 != -1) {
                    FUN_1009060bc();
                  }
                  FUN_10041c570(lRam0000000100c1b290,plVar16);
                }
              }
            }
            goto LAB_10088d530;
          }
          uVar7 = param_3;
          _strcmp(param_3,"ConnectClassicDevice");
          if ((int)uVar7 == 0) {
            uStack_e0 = 0;
            uStack_d8 = 0;
            lStack_d0 = 0;
            puVar8 = param_4;
            _xpc_dictionary_get_string(param_4,"kDeviceAddress");
            FUN_1002274a0(&uStack_e0,puVar8);
            _xpc_dictionary_get_int64(param_4,"kQuickDisconnectEnabled");
            uStack_f0 = (ulong)uStack_f0._6_2_ << 0x30;
            puVar21 = &uStack_f0;
            FUN_100118ae4(puVar21,&uStack_e0);
            uVar7 = uRam0000000100cae4c8;
            if (((ulong)puVar21 & 1) == 0) {
              lVar25 = 0;
              lVar26 = 5;
              do {
                pcVar14 = (char *)((long)&uStack_f0 + lVar25);
                bVar4 = lVar26 != 0;
                lVar26 = lVar26 + -1;
                if (*pcVar14 != '\0') break;
                lVar25 = lVar25 + 1;
              } while (bVar4);
              if (*pcVar14 != '\0') {
                uVar24 = uRam0000000100cae4c8;
                _os_log_type_enabled(uRam0000000100cae4c8,0x10);
                if ((int)uVar24 != 0) {
                  FUN_10090628c(uVar7);
                }
                goto LAB_10088d530;
              }
            }
            if (lRam0000000100c1b238 != -1) {
              FUN_100906084();
            }
            plVar16 = plRam0000000100c1b230;
            FUN_10010bebc(plRam0000000100c1b230,&uStack_f0,0);
            if ((plVar16 == (long *)0x0) ||
               (plVar18 = plVar16, FUN_1000cbaf4(), uVar7 = uRam0000000100cae4c8, (int)plVar18 == 0)
               ) {
              uVar7 = uRam0000000100cae4c8;
              uVar24 = uRam0000000100cae4c8;
              _os_log_type_enabled(uRam0000000100cae4c8,0x10);
              if ((int)uVar24 != 0) {
                FUN_100906324(uVar7);
              }
            }
            else {
              uVar24 = uRam0000000100cae4c8;
              _os_log_type_enabled(uRam0000000100cae4c8,0);
              if ((int)uVar24 != 0) {
                FUN_10010aa84(&uStack_120,plVar16);
                cVar3 = cStack_109;
                puVar13 = (undefined2 *)
                          CONCAT26(uStack_120._6_2_,
                                   CONCAT24(uStack_120._4_2_,
                                            CONCAT22(uStack_120._2_2_,(undefined2)uStack_120)));
                plVar18 = plVar16;
                FUN_1000cb9c8();
                if (-1 < cVar3) {
                  puVar13 = (undefined2 *)&uStack_120;
                }
                uStack_c0 = (undefined2)_UNK_100930fa8;
                uStack_be = (undefined2)((ulong)_UNK_100930fa8 >> 0x10);
                uStack_bc = SUB84(puVar13,0);
                uStack_b8 = (undefined4)((ulong)puVar13 >> 0x20);
                pcVar14 = "is";
                if ((int)plVar18 == 0) {
                  pcVar14 = "not";
                }
                uStack_b4 = 0x820;
                cStack_b2 = (char)pcVar14;
                uStack_b1 = (uint)((ulong)pcVar14 >> 8);
                uStack_ad = 0;
                uStack_a9 = 4;
                pbStack_a8 = (byte *)CONCAT44(pbStack_a8._4_4_,(uint)(param_4 != (ulong *)0x0));
                __os_log_impl(0x100000000,uVar7,0,
                              "ConnectClassicDevice: device %{public}s %s connected with QuickDisconnectEnabled %d"
                              ,&uStack_c0,0x1c);
                if (cStack_109 < '\0') {
                  __ZdlPv(CONCAT26(uStack_120._6_2_,
                                   CONCAT24(uStack_120._4_2_,
                                            CONCAT22(uStack_120._2_2_,(undefined2)uStack_120))));
                }
              }
              plVar18 = plVar16;
              FUN_1000cb9c8();
              if ((int)plVar18 == 0) {
                if (lRam0000000100c1b1e8 != -1) {
                  FUN_1009062b8();
                }
                uVar27 = uRam0000000100c1b1e0;
                FUN_10009e680();
                uVar7 = uRam0000000100cae4c8;
                puVar17 = PTR__OBJC_CLASS___NSNumber_100bfc888;
                if ((uVar27 & 1) == 0) {
                  pcStack_150 = &cf_wxAddress;
                  plVar18 = plVar16 + 0x10;
                  FUN_1003e0968(plVar18);
                  IStack_148 = objc_stub::FUN_10091b2e0((ID)puVar17,plVar18);
                  IVar22 = objc_stub::FUN_100915980
                                     ((ID)PTR__OBJC_CLASS___NSDictionary_100bfcaf0,&IStack_148,
                                      &pcStack_150,1);
                  uVar7 = uRam0000000100cae4c8;
                  uVar24 = uRam0000000100cae4c8;
                  _os_log_type_enabled(uRam0000000100cae4c8,0);
                  if ((int)uVar24 != 0) {
                    FUN_10010aa84(&uStack_c0,plVar16);
                    uStack_120._0_2_ = SUB82(_UNK_100930b20,0);
                    uStack_120._2_2_ = (undefined2)((ulong)_UNK_100930b20 >> 0x10);
                    uStack_120._4_2_ = (short)&uStack_c0;
                    uStack_120._6_2_ = (short)((ulong)&uStack_c0 >> 0x10);
                    sStack_118 = (short)((ulong)&uStack_c0 >> 0x20);
                    sStack_116 = (short)((ulong)&uStack_c0 >> 0x30);
                    __os_log_impl(0x100000000,uVar7,0,
                                  "ConnectClassicDevice: Sending notification to ask SR to connect for device %{public}s,"
                                  ,&uStack_120,0xc);
                  }
                  IVar19 = objc_stub::FUN_100914f20
                                     ((ID)
                                      PTR__OBJC_CLASS___NSDistributedNotificationCenter_100bfc820);
                  objc_stub::FUN_10091bc80
                            (IVar19,&cf_com_apple_BTServer_TriangleRecoveryInitiated,0,IVar22);
                }
                else {
                  uVar24 = uRam0000000100cae4c8;
                  _os_log_type_enabled(uRam0000000100cae4c8,0);
                  if ((int)uVar24 != 0) {
                    FUN_10010aa84(&uStack_c0,plVar16);
                    uStack_120._0_2_ = (undefined2)_UNK_1009316b0;
                    uStack_120._2_2_ = (undefined2)((ulong)_UNK_1009316b0 >> 0x10);
                    uStack_120._4_2_ = (short)&uStack_c0;
                    uStack_120._6_2_ = (short)((ulong)&uStack_c0 >> 0x10);
                    sStack_118 = (short)((ulong)&uStack_c0 >> 0x20);
                    sStack_116 = (short)((ulong)&uStack_c0 >> 0x30);
                    sStack_114 = 0x820;
                    sStack_112 = 0x3139;
                    uStack_110 = 0x9d;
                    uStack_10e = 1;
                    __os_log_impl(0x100000000,uVar7,0,
                                  "Ignoring ConnectClassicDevice msg for %{public}s, Denylist is %s"
                                  ,&uStack_120,0x16);
                  }
                }
              }
              else if (param_4 == (ulong *)0x0) {
                FUN_1000071b8();
                (**(code **)(*plVar18 + 400))();
                uVar7 = uRam0000000100cae4c8;
                if ((int)plVar18 == 0) {
                  uVar24 = uRam0000000100cae4c8;
                  _os_log_type_enabled(uRam0000000100cae4c8,0);
                  if ((int)uVar24 != 0) {
                    uStack_c0 = 0;
                    __os_log_impl(0x100000000,uVar7,0,
                                  "Device already connected ignoring connect classic request",
                                  &uStack_c0,2);
                  }
                }
                else {
                  IVar22 = objc_stub::FUN_100916d00(*(ID *)(param_2 + 0x10));
                  uVar7 = uRam0000000100cae4c8;
                  if (IVar22 == 0) {
                    uVar24 = uRam0000000100cae4c8;
                    _os_log_type_enabled(uRam0000000100cae4c8,0x10);
                    if ((int)uVar24 != 0) {
                      FUN_1009062e0(uVar7);
                    }
                  }
                  else {
                    if (lRam0000000100c1b218 != -1) {
                      FUN_1009060a0();
                    }
                    uVar24 = uRam0000000100c1b210;
                    FUN_10002d028(uRam0000000100c1b210,IVar22,0);
                    uVar7 = uRam0000000100cae4c8;
                    uStack_100._0_6_ =
                         CONCAT15((char)uVar24,
                                  CONCAT14((char)((ulong)uVar24 >> 8),
                                           CONCAT13((char)((ulong)uVar24 >> 0x10),
                                                    CONCAT12((char)((ulong)uVar24 >> 0x18),
                                                             CONCAT11((char)((ulong)uVar24 >> 0x20),
                                                                      (char)((ulong)uVar24 >> 0x28))
                                                            ))));
                    uVar24 = uRam0000000100cae4c8;
                    _os_log_type_enabled(uRam0000000100cae4c8,0);
                    if ((int)uVar24 != 0) {
                      FUN_10010aa84(&uStack_120,plVar16);
                      cVar3 = cStack_109;
                      puVar13 = (undefined2 *)
                                CONCAT26(uStack_120._6_2_,
                                         CONCAT24(uStack_120._4_2_,
                                                  CONCAT22(uStack_120._2_2_,(undefined2)uStack_120))
                                        );
                      FUN_1000c6c24(&bStack_140,&uStack_100);
                      if (-1 < cVar3) {
                        puVar13 = (undefined2 *)&uStack_120;
                      }
                      pbStack_a8 = (byte *)CONCAT26(uStack_13a,
                                                    CONCAT15(bStack_13b,
                                                             CONCAT14(bStack_13c,
                                                                      CONCAT13(bStack_13d,
                                                                               CONCAT12(bStack_13e,
                                                                                        CONCAT11(
                                                  bStack_13f,bStack_140))))));
                      if (-1 < cStack_129) {
                        pbStack_a8 = &bStack_140;
                      }
                      uStack_c0 = (undefined2)_UNK_1009330d8;
                      uStack_be = (undefined2)((ulong)_UNK_1009330d8 >> 0x10);
                      uStack_bc = SUB84(puVar13,0);
                      uStack_b8 = (undefined4)((ulong)puVar13 >> 0x20);
                      uStack_b4 = 0x870;
                      cStack_b2 = 'h';
                      uStack_b1 = 0x687361;
                      uStack_ad = 0x21000000;
                      uStack_a9 = 8;
                      __os_log_impl(0x100000000,uVar7,0,
                                    "ConnectClassicDevice: already in triangle, device %{public}s, peerSource %{private, mask.hash}s"
                                    ,&uStack_c0,0x20);
                      if (cStack_129 < '\0') {
                        __ZdlPv(CONCAT26(uStack_13a,
                                         CONCAT15(bStack_13b,
                                                  CONCAT14(bStack_13c,
                                                           CONCAT13(bStack_13d,
                                                                    CONCAT12(bStack_13e,
                                                                             CONCAT11(bStack_13f,
                                                                                      bStack_140))))
                                                 )));
                      }
                      if (cStack_109 < '\0') {
                        __ZdlPv(CONCAT26(uStack_120._6_2_,
                                         CONCAT24(uStack_120._4_2_,
                                                  CONCAT22(uStack_120._2_2_,(undefined2)uStack_120))
                                        ));
                      }
                    }
                    if (lRam0000000100c1b298 != -1) {
                      FUN_1009060bc();
                    }
                    FUN_1004177b4(lRam0000000100c1b290,plVar16,0);
                  }
                }
              }
              else {
                if (lRam0000000100c1b4d8 != -1) {
                  FUN_10090630c();
                }
                FUN_1006448c4(uRam0000000100c1b4d0,&uStack_f0);
              }
            }
            goto LAB_10088d530;
          }
          uVar7 = param_3;
          _strcmp(param_3,"NotifyPrimaryBudSide");
          if ((int)uVar7 == 0) {
            uStack_c0 = 0;
            uStack_be = 0;
            uStack_bc = 0;
            uStack_b8 = 0;
            uStack_b4 = 0;
            cStack_b2 = '\0';
            uStack_b1 = 0;
            uStack_ad = 0;
            uStack_a9 = 0;
            puVar8 = param_4;
            _xpc_dictionary_get_string(param_4,"kDeviceAddress");
            FUN_1002274a0(&uStack_c0,puVar8);
            _xpc_dictionary_get_int64(param_4,"kPrimaryBudSide");
            uStack_e0 = (ulong)uStack_e0._6_2_ << 0x30;
            puVar21 = &uStack_e0;
            FUN_100118ae4(puVar21,&uStack_c0);
            uVar7 = uRam0000000100cae468;
            if (((ulong)puVar21 & 1) == 0) {
              uVar24 = uRam0000000100cae468;
              _os_log_type_enabled(uRam0000000100cae468,0x10);
              if ((int)uVar24 != 0) {
                FUN_10090628c(uVar7);
              }
            }
            else {
              if (lRam0000000100c1b238 != -1) {
                FUN_100906084();
              }
              plVar16 = plRam0000000100c1b230;
              FUN_10010bebc(plRam0000000100c1b230,&uStack_e0,1);
              if (plVar16 != (long *)0x0) {
                if (lRam0000000100c1b298 != -1) {
                  FUN_1009060bc();
                }
                FUN_10041cef0(lRam0000000100c1b290,plVar16,(uint)param_4 & 0xff);
              }
            }
            goto LAB_10088d530;
          }
          uVar7 = param_3;
          _strcmp(param_3,"LeaEasyPairRequest");
          if ((int)uVar7 != 0) {
            uVar7 = param_3;
            _strcmp(param_3,"LeaEasyPairResponse");
            if ((int)uVar7 == 0) {
              uStack_c0 = 0;
              uStack_be = 0;
              uStack_bc = 0;
              uStack_b8 = 0;
              uStack_b4 = 0;
              cStack_b2 = '\0';
              uStack_b1 = 0;
              uStack_ad = 0;
              uStack_a9 = 0;
              puVar8 = param_4;
              _xpc_dictionary_get_string(param_4,"kLeaDeviceAddress");
              FUN_1002274a0(&uStack_c0,puVar8);
              _xpc_dictionary_get_int64(param_4,"kLeaDevicePairState");
              uVar7 = uRam0000000100cae468;
              uVar24 = uRam0000000100cae468;
              _os_log_type_enabled(uRam0000000100cae468,0);
              if ((int)uVar24 != 0) {
                uStack_e0 = uStack_e0 & 0xffffffffffff0000;
                __os_log_impl(0x100000000,uVar7,0,"Received LeaEasyPairResponse",&uStack_e0,2);
              }
              uStack_e0 = uStack_e0 & 0xffff000000000000;
              puVar21 = &uStack_e0;
              FUN_100118ae4(puVar21,&uStack_c0);
              uVar7 = uRam0000000100cae468;
              if (((ulong)puVar21 & 1) != 0) {
                if (lRam0000000100c1b268 != -1) {
                  FUN_1009061ac();
                }
                uStack_120._0_2_ = (undefined2)uStack_e0;
                uStack_120._2_2_ = (undefined2)(uStack_e0 >> 0x10);
                uStack_120._4_2_ = uStack_e0._4_2_;
                FUN_1006ebccc(uRam0000000100c1b260,&uStack_120,(uint)param_4 & 0xff);
                goto LAB_10088d530;
              }
              uVar24 = uRam0000000100cae468;
              _os_log_type_enabled(uRam0000000100cae468,0);
              if ((int)uVar24 == 0) goto LAB_10088d530;
              pcVar14 = "Received invalid device address on LeaEasyPairResponse";
            }
            else {
              uVar7 = param_3;
              _strcmp(param_3,"LeaStoreBondingInfoRequest");
              if ((int)uVar7 == 0) {
                uStack_c0 = 0;
                uStack_be = 0;
                uStack_bc = 0;
                uStack_b8 = 0;
                uStack_b4 = 0;
                cStack_b2 = '\0';
                uStack_b1 = 0;
                uStack_ad = 0;
                uStack_a9 = 0;
                puVar8 = param_4;
                _xpc_dictionary_get_string(param_4,"kLeaDeviceAddress");
                FUN_1002274a0(&uStack_c0,puVar8);
                uStack_e0 = 0;
                uStack_d8 = 0;
                lStack_d0 = 0;
                puVar8 = param_4;
                _xpc_dictionary_get_string(param_4,"kLeaDeviceName");
                FUN_1002274a0(&uStack_e0,puVar8);
                puVar8 = param_4;
                _xpc_dictionary_get_int64(param_4,"kLeaDeviceEdiv");
                uStack_2f4 = 0;
                uStack_2f8 = 0;
                puVar20 = &uStack_2f8;
                FUN_100118ae4(puVar20,&uStack_c0);
                uVar7 = uRam0000000100cae468;
                if (((ulong)puVar20 & 1) == 0) {
                  uVar24 = uRam0000000100cae468;
                  _os_log_type_enabled(uRam0000000100cae468,0);
                  if ((int)uVar24 != 0) {
                    uStack_120._0_2_ = 0;
                    __os_log_impl(0x100000000,uVar7,0,
                                  "Received invalid device address on LeaStoreBondingInfoRequest",
                                  &uStack_120,2);
                  }
                  uStack_308 = CONCAT17((char)uStack_b1,
                                        CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
                  uStack_310 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
                  lStack_300 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
                  FUN_10088c788(param_2,&uStack_310,1);
                  uVar7 = uStack_310;
                  lVar25 = lStack_300;
                }
                else {
                  uStack_158 = 0;
                  uStack_138 = 0;
                  uStack_134 = 0;
                  uStack_132 = 0;
                  bStack_140 = 0;
                  bStack_13f = 0;
                  bStack_13e = 0;
                  bStack_13d = 0;
                  bStack_13c = 0;
                  bStack_13b = 0;
                  uStack_13a = 0;
                  uStack_f0 = 0;
                  uStack_e8 = 0;
                  lStack_318 = 0;
                  puVar28 = param_4;
                  _xpc_dictionary_get_data(param_4,"kLeaDeviceRand",&lStack_318);
                  uVar7 = uRam0000000100cae468;
                  if ((puVar28 == (ulong *)0x0) || (lStack_318 != 8)) {
                    uVar24 = uRam0000000100cae468;
                    _os_log_type_enabled(uRam0000000100cae468,0x10);
                    if ((int)uVar24 != 0) {
                      FUN_100906234(uVar7);
                    }
                    uStack_328 = CONCAT17((char)uStack_b1,
                                          CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
                    uStack_330 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
                    lStack_320 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
                    FUN_10088c788(param_2,&uStack_330,1);
                    uVar7 = uStack_330;
                    lVar25 = lStack_320;
                  }
                  else {
                    uStack_158 = *puVar28;
                    lStack_338 = 0;
                    puVar28 = param_4;
                    _xpc_dictionary_get_data(param_4,"kLeaDeviceLtk",&lStack_338);
                    uVar7 = uRam0000000100cae468;
                    if ((puVar28 == (ulong *)0x0) || (lStack_338 != 0x10)) {
                      uVar24 = uRam0000000100cae468;
                      _os_log_type_enabled(uRam0000000100cae468,0x10);
                      if ((int)uVar24 != 0) {
                        FUN_100906208(uVar7);
                      }
                      uStack_348 = CONCAT17((char)uStack_b1,
                                            CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
                      uStack_350 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
                      lStack_340 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
                      FUN_10088c788(param_2,&uStack_350,1);
                      uVar7 = uStack_350;
                      lVar25 = lStack_340;
                    }
                    else {
                      uVar29 = puVar28[1];
                      uVar27 = *puVar28;
                      uStack_138 = (undefined4)uVar29;
                      uStack_134 = (undefined2)(uVar29 >> 0x20);
                      uStack_132 = (undefined2)(uVar29 >> 0x30);
                      bStack_140 = (byte)uVar27;
                      bStack_13f = (byte)(uVar27 >> 8);
                      bStack_13e = (byte)(uVar27 >> 0x10);
                      bStack_13d = (byte)(uVar27 >> 0x18);
                      bStack_13c = (byte)(uVar27 >> 0x20);
                      bStack_13b = (byte)(uVar27 >> 0x28);
                      uStack_13a = (undefined2)(uVar27 >> 0x30);
                      lStack_358 = 0;
                      _xpc_dictionary_get_data(param_4,"kLeaDeviceIrk",&lStack_358);
                      uVar7 = uRam0000000100cae468;
                      if ((param_4 != (ulong *)0x0) && (lStack_358 == 0x10)) {
                        uStack_e8 = param_4[1];
                        uStack_f0 = *param_4;
                        if (((ulong)puVar8 & 0xffff) != 0) {
                          uVar31 = (ulong)(byte)uStack_2f8;
                          uVar33 = (ulong)uStack_2f8._1_1_;
                          uVar32 = (ulong)uStack_2f8._2_1_;
                          uVar30 = (ulong)uStack_2f8._3_1_;
                          uVar27 = (ulong)(byte)uStack_2f4;
                          uVar29 = (ulong)uStack_2f4._1_1_;
                          uStack_100 = 0;
                          uStack_f8 = 0;
                          if (lRam0000000100c1b218 != -1) {
                            FUN_1009060a0();
                          }
                          uVar27 = uVar31 << 0x28 | uVar33 << 0x20 | uVar32 << 0x18 | uVar30 << 0x10
                                   | uVar27 << 8;
                          FUN_10082adf0(&uStack_100,uRam0000000100c1b210,uVar27 | uVar29,0,0,0,0,1);
                          uStack_380 = (undefined **)0x0;
                          puStack_378 = (undefined8 *)0x0;
                          puVar21 = (undefined8 *)0x28;
                          __ZnwmSt19__type_descriptor_t(0x28,0x10a1c40c3d8c859);
                          *(undefined4 *)(puVar21 + 1) = 1;
                          *puVar21 = &PTR_LAB_100bc1688;
                          puVar21[3] = 0;
                          puVar21[4] = 0;
                          puVar21[2] = puVar21 + 3;
                          uStack_380 = &PTR_LAB_100bc1768;
                          uStack_382 = SUB82(puVar8,0);
                          uStack_383 = 0x10;
                          uStack_38c = 0;
                          uStack_38a = 0;
                          uStack_390 = 0;
                          uVar27 = uVar27 | uVar29;
                          puStack_378 = puVar21;
                          FUN_10009ad50();
                          puVar21 = puStack_378;
                          uStack_390 = (undefined4)uVar27;
                          uStack_38a = (undefined1)(uVar27 >> 0x30);
                          uStack_38c = (undefined2)(uVar27 >> 0x20);
                          FUN_1000072d0(&uStack_120,&uStack_390,7);
                          FUN_100890a78(puVar21,0xb,&uStack_120);
                          uStack_120._0_2_ = 0xd988;
                          uStack_120._2_2_ = 0xb9;
                          uStack_120._4_2_ = 1;
                          uStack_120._6_2_ = 0;
                          if (CONCAT26(sStack_112,
                                       CONCAT24(sStack_114,CONCAT22(sStack_116,sStack_118))) != 0) {
                            FUN_100007228();
                          }
                          puVar21 = puStack_378;
                          FUN_1000072d0(&uStack_120,&uStack_382,2);
                          FUN_100890a78(puVar21,3,&uStack_120);
                          uStack_120._0_2_ = 0xd988;
                          uStack_120._2_2_ = 0xb9;
                          uStack_120._4_2_ = 1;
                          uStack_120._6_2_ = 0;
                          if (CONCAT26(sStack_112,
                                       CONCAT24(sStack_114,CONCAT22(sStack_116,sStack_118))) != 0) {
                            FUN_100007228();
                          }
                          puVar21 = puStack_378;
                          FUN_1000072d0(&uStack_120,&uStack_158,8);
                          FUN_100890a78(puVar21,4,&uStack_120);
                          uStack_120._0_2_ = 0xd988;
                          uStack_120._2_2_ = 0xb9;
                          uStack_120._4_2_ = 1;
                          uStack_120._6_2_ = 0;
                          if (CONCAT26(sStack_112,
                                       CONCAT24(sStack_114,CONCAT22(sStack_116,sStack_118))) != 0) {
                            FUN_100007228();
                          }
                          puVar21 = puStack_378;
                          FUN_1000072d0(&uStack_120,&bStack_140,0x10);
                          FUN_100890a78(puVar21,0,&uStack_120);
                          uStack_120._0_2_ = 0xd988;
                          uStack_120._2_2_ = 0xb9;
                          uStack_120._4_2_ = 1;
                          uStack_120._6_2_ = 0;
                          if (CONCAT26(sStack_112,
                                       CONCAT24(sStack_114,CONCAT22(sStack_116,sStack_118))) != 0) {
                            FUN_100007228();
                          }
                          puVar21 = puStack_378;
                          FUN_1000072d0(&uStack_120,&uStack_383,1);
                          FUN_100890a78(puVar21,1,&uStack_120);
                          uStack_120._0_2_ = 0xd988;
                          uStack_120._2_2_ = 0xb9;
                          uStack_120._4_2_ = 1;
                          uStack_120._6_2_ = 0;
                          if (CONCAT26(sStack_112,
                                       CONCAT24(sStack_114,CONCAT22(sStack_116,sStack_118))) != 0) {
                            FUN_100007228();
                          }
                          puVar21 = puStack_378;
                          FUN_1000072d0(&uStack_120,&uStack_f0,0x10);
                          FUN_100890a78(puVar21,10,&uStack_120);
                          uStack_120._0_2_ = 0xd988;
                          uStack_120._2_2_ = 0xb9;
                          uStack_120._4_2_ = 1;
                          uStack_120._6_2_ = 0;
                          if (CONCAT26(sStack_112,
                                       CONCAT24(sStack_114,CONCAT22(sStack_116,sStack_118))) != 0) {
                            FUN_100007228();
                          }
                          if (lRam0000000100c1b268 != -1) {
                            FUN_1009061ac();
                          }
                          uStack_120._0_2_ = (undefined2)uStack_2f8;
                          uStack_120._2_2_ = (undefined2)((uint)uStack_2f8 >> 0x10);
                          uStack_120._4_2_ = uStack_2f4;
                          FUN_1006ebf24(uRam0000000100c1b260,&uStack_120);
                          if (lRam0000000100c1b208 != -1) {
                            FUN_1009061c4();
                          }
                          uVar7 = uRam0000000100c1b200;
                          puVar21 = &uStack_100;
                          FUN_100011444(puVar21);
                          FUN_1002274a0(auStack_3a8,"");
                          FUN_10086c98c(uVar7,puVar21,&uStack_380,auStack_3a8,0,0);
                          if (cStack_391 < '\0') {
                            __ZdlPv(auStack_3a8[0]);
                          }
                          if (lRam0000000100c1b218 != -1) {
                            FUN_1009060a0(0);
                          }
                          uVar24 = uRam0000000100c1b210;
                          puVar21 = &uStack_100;
                          FUN_100011444(puVar21);
                          thunk_FUN_10002141c(&uStack_120,puVar21);
                          uStack_3b8 = uStack_d8;
                          uStack_3c0 = uStack_e0;
                          lStack_3b0 = lStack_d0;
                          FUN_10011cf5c(uVar24,&uStack_120,&uStack_3c0,2);
                          if (lStack_3b0 < 0) {
                            __ZdlPv(uStack_3c0);
                          }
                          uVar24 = uRam0000000100cae468;
                          uVar23 = uRam0000000100cae468;
                          _os_log_type_enabled(uRam0000000100cae468,0);
                          if ((int)uVar23 != 0) {
                            pcVar14 = "Failed to store";
                            if ((int)uVar7 == 0) {
                              pcVar14 = "Successfully stored";
                            }
                            uStack_120._0_2_ = (undefined2)_UNK_100930b18;
                            uStack_120._2_2_ = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
                            uStack_120._4_2_ = (short)pcVar14;
                            uStack_120._6_2_ = (short)((ulong)pcVar14 >> 0x10);
                            sStack_118 = (short)((ulong)pcVar14 >> 0x20);
                            sStack_116 = 0;
                            sStack_114 = 0x820;
                            sStack_112 = (short)&uStack_c0;
                            uStack_110 = (undefined2)((ulong)&uStack_c0 >> 0x10);
                            uStack_10e = (undefined4)((ulong)&uStack_c0 >> 0x20);
                            __os_log_impl(0x100000000,uVar24,0,"%s bonding info for address %s",
                                          &uStack_120,0x16);
                          }
                          uStack_3d8 = CONCAT17((char)uStack_b1,
                                                CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
                          uStack_3e0 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
                          lStack_3d0 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
                          FUN_10088c788(param_2,&uStack_3e0,(int)uVar7 != 0);
                          if (lStack_3d0 < 0) {
                            __ZdlPv(uStack_3e0);
                          }
                          uStack_380 = &PTR_LAB_100bc1768;
                          if (puStack_378 != (undefined8 *)0x0) {
                            FUN_100007228();
                          }
                          goto LAB_10088d530;
                        }
                        uVar24 = uRam0000000100cae468;
                        _os_log_type_enabled(uRam0000000100cae468,0);
                        if ((int)uVar24 != 0) {
                          uStack_120._0_2_ = 0;
                          __os_log_impl(0x100000000,uVar7,0,
                                        "Received LeaStoreBondingInfoRequest to trigger unpairing",
                                        &uStack_120,2);
                        }
                        sStack_118 = 0;
                        sStack_116 = 0;
                        sStack_114 = 0;
                        sStack_112 = 0;
                        uStack_120._0_2_ = 0;
                        uStack_120._2_2_ = 0;
                        uStack_120._4_2_ = 0;
                        uStack_120._6_2_ = 0;
                        if (lRam0000000100c1b218 != -1) {
                          FUN_1009060a0();
                        }
                        FUN_10082adf0(&uStack_120,uRam0000000100c1b210,
                                      (ulong)(byte)uStack_2f8 << 0x28 |
                                      (ulong)uStack_2f8._1_1_ << 0x20 |
                                      (ulong)uStack_2f8._2_1_ << 0x18 |
                                      (ulong)uStack_2f8._3_1_ << 0x10 | (ulong)(byte)uStack_2f4 << 8
                                      | (ulong)uStack_2f4._1_1_,0,0,0,0,1);
                        if (lRam0000000100c1b208 != -1) {
                          FUN_1009061c4();
                        }
                        uVar24 = uRam0000000100c1b200;
                        puVar13 = (undefined2 *)&uStack_120;
                        FUN_100011444(puVar13);
                        FUN_100024d14(uVar24,puVar13);
                        uVar7 = uRam0000000100cae468;
                        if ((int)uVar24 != 0) {
                          if (lRam0000000100c1b268 != -1) {
                            FUN_1009061ac(0);
                          }
                          uStack_100._0_6_ = CONCAT24(uStack_2f4,uStack_2f8);
                          FUN_1006ec02c(uRam0000000100c1b260,&uStack_100);
                          if (lRam0000000100c1b208 != -1) {
                            FUN_1009061c4();
                          }
                          uVar7 = uRam0000000100c1b200;
                          puVar13 = (undefined2 *)&uStack_120;
                          FUN_100011444(puVar13);
                          FUN_10018f9b8(uVar7,puVar13);
                          goto LAB_10088d530;
                        }
                        uVar24 = uRam0000000100cae468;
                        _os_log_type_enabled(uRam0000000100cae468,0);
                        if ((int)uVar24 == 0) goto LAB_10088d530;
                        uStack_100 = uStack_100 & 0xffffffffffff0000;
                        pcVar14 = "Device is already unpaired";
                        puVar21 = &uStack_100;
                        uVar24 = 2;
                        goto LAB_10088d200;
                      }
                      uVar24 = uRam0000000100cae468;
                      _os_log_type_enabled(uRam0000000100cae468,0x10);
                      if ((int)uVar24 != 0) {
                        FUN_1009061dc(uVar7);
                      }
                      uStack_368 = CONCAT17((char)uStack_b1,
                                            CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
                      uStack_370 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
                      lStack_360 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
                      FUN_10088c788(param_2,&uStack_370,1);
                      uVar7 = uStack_370;
                      lVar25 = lStack_360;
                    }
                  }
                }
                goto joined_r0x00010088dd2c;
              }
              uVar7 = param_3;
              _strcmp(param_3,"LeaStoreBondingInfoResponse");
              if ((int)uVar7 != 0) {
                uVar7 = param_3;
                _strcmp(param_3,"ANCSNotificationSourceRegistered");
                if ((int)uVar7 == 0) {
                  puVar17 = PTR__OBJC_CLASS___NSUUID_100bfc8e0;
                  _objc_alloc();
                  _xpc_dictionary_get_uuid(param_4,"kPeerIdentifier");
                  IVar22 = objc_stub::FUN_100918d60((ID)puVar17,param_4);
                  uVar7 = uRam0000000100cae468;
                  uVar24 = uRam0000000100cae468;
                  _os_log_type_enabled(uRam0000000100cae468,0);
                  if ((int)uVar24 != 0) {
                    uStack_c0 = (undefined2)_UNK_1009304d0;
                    uStack_be = (undefined2)((ulong)_UNK_1009304d0 >> 0x10);
                    uStack_bc = (undefined4)IVar22;
                    uStack_b8 = (undefined4)(IVar22 >> 0x20);
                    __os_log_impl(0x100000000,uVar7,0,
                                  "Device %@ has subscribed to ANCSNotificationSource",&uStack_c0,
                                  0xc);
                  }
                  if (lRam0000000100c1f9c0 != -1) {
                    FUN_100906184();
                  }
                  FUN_100778fe0(uRam0000000100c1f9b8,IVar22);
                }
                else {
                  uVar7 = param_3;
                  _strcmp(param_3,"UARPDataOverAACP");
                  if ((int)uVar7 == 0) {
                    puVar8 = param_4;
                    _xpc_dictionary_get_string(param_4,"kUARPDeviceUUID");
                    puVar17 = PTR__OBJC_CLASS___NSString_100bfc8c8;
                    _objc_alloc();
                    IVar22 = objc_stub::FUN_100918d40((ID)puVar17,puVar8);
                    puVar17 = PTR__OBJC_CLASS___NSUUID_100bfc8e0;
                    _objc_alloc();
                    IVar22 = objc_stub::FUN_100918d80((ID)puVar17,IVar22);
                    if (lRam0000000100c1b218 != -1) {
                      FUN_1009060a0();
                    }
                    uVar7 = uRam0000000100c1b210;
                    FUN_10002d028(uRam0000000100c1b210,IVar22,0);
                    if (lRam0000000100c1b238 != -1) {
                      FUN_100906084();
                    }
                    plVar16 = plRam0000000100c1b230;
                    FUN_10002d680(plRam0000000100c1b230,uVar7,1);
                    uVar7 = uRam0000000100cae468;
                    if (plVar16 == (long *)0x0) {
                      uVar24 = uRam0000000100cae468;
                      _os_log_type_enabled(uRam0000000100cae468,0x10);
                      if ((int)uVar24 != 0) {
                        FUN_100906158(uVar7);
                      }
                    }
                    else {
                      uStack_c0 = 0;
                      uStack_be = 0;
                      uStack_bc = 0;
                      _xpc_dictionary_get_data(param_4,"kUARPData",&uStack_c0);
                      uVar7 = uRam0000000100cae468;
                      if ((param_4 == (ulong *)0x0) ||
                         (lVar25 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0)), lVar25 == 0))
                      {
                        uVar24 = uRam0000000100cae468;
                        _os_log_type_enabled(uRam0000000100cae468,0x10);
                        if ((int)uVar24 != 0) {
                          FUN_10090612c(uVar7);
                        }
                      }
                      else {
                        _malloc_type_malloc(lVar25,0x100004077774924);
                        uVar7 = uRam0000000100cae468;
                        if (lVar25 == 0) {
                          uVar24 = uRam0000000100cae468;
                          _os_log_type_enabled(uRam0000000100cae468,0x10);
                          if ((int)uVar24 != 0) {
                            FUN_100906100(uVar7);
                          }
                        }
                        else {
                          _memcpy(lVar25,param_4,CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0)));
                          if (lRam0000000100c1b298 != -1) {
                            FUN_1009060bc();
                          }
                          lVar26 = lRam0000000100c1b290;
                          FUN_10041e81c(lRam0000000100c1b290,plVar16,uStack_c0,lVar25);
                          uVar7 = uRam0000000100cae468;
                          if (((int)lVar26 != 0) &&
                             (uVar24 = uRam0000000100cae468,
                             _os_log_type_enabled(uRam0000000100cae468,0x10), (int)uVar24 != 0)) {
                            FUN_1009060d4(uVar7);
                          }
                          _free(lVar25);
                        }
                      }
                    }
                  }
                  else {
                    _strcmp(param_3,"BatteryServiceNotification");
                    if ((int)param_3 == 0) {
                      iVar6 = 0x9c8510;
                      __os_feature_enabled_impl("BluetoothFeatures","BAS");
                      if (iVar6 != 0) {
                        thunk_FUN_100029f7c(param_4);
                        if (lRam0000000100c1b238 != -1) {
                          FUN_100906084();
                        }
                        FUN_10061a804(plRam0000000100c1b230,param_4);
                      }
                    }
                  }
                }
                goto LAB_10088d530;
              }
              uStack_c0 = 0;
              uStack_be = 0;
              uStack_bc = 0;
              uStack_b8 = 0;
              uStack_b4 = 0;
              cStack_b2 = '\0';
              uStack_b1 = 0;
              uStack_ad = 0;
              uStack_a9 = 0;
              puVar8 = param_4;
              _xpc_dictionary_get_string(param_4,"kLeaDeviceAddress");
              FUN_1002274a0(&uStack_c0,puVar8);
              _xpc_dictionary_get_int64(param_4,"kLeaStoreBondingInfoResult");
              uStack_e0 = (ulong)uStack_e0._6_2_ << 0x30;
              puVar21 = &uStack_e0;
              FUN_100118ae4(puVar21,&uStack_c0);
              uVar7 = uRam0000000100cae468;
              if (((ulong)puVar21 & 1) != 0) {
                if (lRam0000000100c1b268 != -1) {
                  FUN_1009061ac();
                }
                uStack_120._0_2_ = (undefined2)uStack_e0;
                uStack_120._2_2_ = (undefined2)(uStack_e0 >> 0x10);
                uStack_120._4_2_ = uStack_e0._4_2_;
                FUN_1006ebdf8(uRam0000000100c1b260,&uStack_120,(uint)param_4 & 0xff);
                goto LAB_10088d530;
              }
              uVar24 = uRam0000000100cae468;
              _os_log_type_enabled(uRam0000000100cae468,0);
              if ((int)uVar24 == 0) goto LAB_10088d530;
              pcVar14 = "Received invalid device address on LeaStoreBondingInfoResponse";
            }
            uStack_120._0_2_ = 0;
            __os_log_impl(0x100000000,uVar7,0,pcVar14,&uStack_120,2);
            goto LAB_10088d530;
          }
          uStack_c0 = 0;
          uStack_be = 0;
          uStack_bc = 0;
          uStack_b8 = 0;
          uStack_b4 = 0;
          cStack_b2 = '\0';
          uStack_b1 = 0;
          uStack_ad = 0;
          uStack_a9 = 0;
          puVar8 = param_4;
          _xpc_dictionary_get_string(param_4,"kLeaDeviceAddress");
          FUN_1002274a0(&uStack_c0,puVar8);
          uStack_e0 = 0;
          uStack_d8 = 0;
          lStack_d0 = 0;
          puVar8 = param_4;
          _xpc_dictionary_get_string(param_4,"kLeaDeviceIdentifier");
          FUN_1002274a0(&uStack_e0,puVar8);
          _xpc_dictionary_get_value(param_4,"kLeaDeviceTags");
          puVar8 = param_4;
          FUN_1000071f0();
          uVar5 = (uint)puVar8;
          FUN_1000aa450();
          if (1 < uVar5) {
            bStack_13c = 0;
            bStack_13b = 0;
            bStack_140 = 0;
            bStack_13f = 0;
            bStack_13e = 0;
            bStack_13d = 0;
            pbVar15 = &bStack_140;
            FUN_100118ae4(pbVar15,&uStack_c0);
            uVar7 = uRam0000000100cae4c8;
            if (((ulong)pbVar15 & 1) == 0) {
              uVar24 = uRam0000000100cae4c8;
              _os_log_type_enabled(uRam0000000100cae4c8,0x10);
              if ((int)uVar24 != 0) {
                FUN_100906260(uVar7);
              }
            }
            else {
              uVar33 = (ulong)bStack_140;
              uVar32 = (ulong)bStack_13f;
              uVar31 = (ulong)bStack_13e;
              uVar30 = (ulong)bStack_13d;
              uVar29 = (ulong)bStack_13c;
              uVar27 = (ulong)bStack_13b;
              sStack_118 = 0;
              sStack_116 = 0;
              sStack_114 = 0;
              sStack_112 = 0;
              uStack_120._0_2_ = 0;
              uStack_120._2_2_ = 0;
              uStack_120._4_2_ = 0;
              uStack_120._6_2_ = 0;
              if (lRam0000000100c1b218 != -1) {
                FUN_1009060a0();
              }
              FUN_10082adf0(&uStack_120,uRam0000000100c1b210,
                            uVar33 << 0x28 | uVar32 << 0x20 | uVar31 << 0x18 | uVar30 << 0x10 |
                            uVar29 << 8 | uVar27,1,0,0,0,1);
              if (lRam0000000100c1b208 != -1) {
                FUN_1009061c4();
              }
              uVar7 = uRam0000000100c1b200;
              puVar13 = (undefined2 *)&uStack_120;
              FUN_100011444(puVar13);
              FUN_100024d14(uVar7,puVar13);
              if (param_4 != (ulong *)0x0) {
                thunk_FUN_100097f24();
              }
              IVar22 = objc_stub::FUN_10091b380((ID)param_4);
              if (IVar22 != 0) {
                while (IVar19 = objc_stub::FUN_10091ae60(IVar22), IVar19 != 0) {
                  if (lRam0000000100c1b218 != -1) {
                    FUN_1009060a0(0);
                  }
                  uVar24 = uRam0000000100c1b210;
                  puVar13 = (undefined2 *)&uStack_120;
                  FUN_100011444(puVar13);
                  _objc_retainAutorelease(IVar19);
                  IVar19 = objc_stub::FUN_10090cba0(IVar19);
                  FUN_1002274a0(auStack_2b8,IVar19);
                  FUN_100830608(uVar24,puVar13,auStack_2b8);
                  if (cStack_2a1 < '\0') {
                    __ZdlPv(auStack_2b8[0]);
                  }
                }
              }
              if ((int)uVar7 == 0) {
                uStack_2e8 = CONCAT17((char)uStack_b1,
                                      CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
                uStack_2f0 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
                lStack_2e0 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
                FUN_10088c6a0(param_2,&uStack_2f0,1);
                if (-1 < lStack_2e0) goto LAB_10088d530;
                puVar21 = &uStack_2f0;
              }
              else {
                uStack_2c8 = CONCAT17((char)uStack_b1,
                                      CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
                uStack_2d0 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
                lStack_2c0 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
                FUN_10088c6a0(param_2,&uStack_2d0,2);
                if (-1 < lStack_2c0) goto LAB_10088d530;
                puVar21 = &uStack_2d0;
              }
              __ZdlPv(*puVar21);
            }
            goto LAB_10088d530;
          }
          uStack_298 = CONCAT17((char)uStack_b1,CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
          uStack_2a0 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
          lStack_290 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
          FUN_10088c6a0(param_2,&uStack_2a0,3);
          uVar7 = uStack_2a0;
          lVar25 = lStack_290;
        }
      }
joined_r0x00010088dd2c:
      if (lVar25 < 0) {
        __ZdlPv(uVar7);
      }
      goto LAB_10088d530;
    }
    puVar8 = param_4;
    _xpc_dictionary_get_int64(param_4,"kEasyPairingVersion");
    uStack_c0 = 0;
    uStack_be = 0;
    uStack_bc = 0;
    uStack_b8 = 0;
    uStack_b4 = 0;
    cStack_b2 = '\0';
    uStack_b1 = 0;
    uStack_ad = 0;
    uStack_a9 = 0;
    puVar28 = param_4;
    _xpc_dictionary_get_string(param_4,"kCloudAccount");
    FUN_1002274a0(&uStack_c0,puVar28);
    _xpc_dictionary_get_int64(param_4,"kEasyPairingStatus");
    if (lRam0000000100c1ec38 != -1) {
      FUN_1009065c4();
    }
    uStack_1b8 = CONCAT17((char)uStack_b1,CONCAT16(cStack_b2,CONCAT24(uStack_b4,uStack_b8)));
    uStack_1c0 = CONCAT44(uStack_bc,CONCAT22(uStack_be,uStack_c0));
    lStack_1b0 = CONCAT17(uStack_a9,CONCAT43(uStack_ad,uStack_b1._1_3_));
    FUN_1003f7d64(uRam0000000100c1ec30,(uint)puVar8 & 0xff,&uStack_1c0,(uint)param_4 & 0xff);
    uVar7 = uStack_1c0;
    lVar25 = lStack_1b0;
  }
  if (lVar25 < 0) {
    __ZdlPv(uVar7);
  }
LAB_10088d530:
  if (*(long *)PTR____stack_chk_guard_100bfc980 == lStack_98) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}


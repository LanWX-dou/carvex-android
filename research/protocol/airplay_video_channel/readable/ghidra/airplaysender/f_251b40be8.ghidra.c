/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b40be8
 * original code SHA256: 6024da51820542c430e80e109c2632aa429be7d64fb9dad4700b7357a37d513b
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000251b414bc) */
/* WARNING: Removing unreachable block (ram,0x000251b4257c) */
/* WARNING: Removing unreachable block (ram,0x000251b40e90) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_APEndpointStreamScreenCreate
          (undefined8 param_1,long param_2,long param_3,long param_4,long param_5,long param_6,
          long param_7,long *param_8)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  undefined8 uVar11;
  undefined8 *puVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  long lVar16;
  int iVar17;
  code *pcVar18;
  undefined8 *puVar19;
  undefined8 *puVar20;
  undefined8 uVar21;
  double dVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 local_118;
  undefined8 local_110;
  code *local_108;
  undefined *puStack_100;
  long local_f8;
  undefined4 local_ec;
  undefined8 local_e8;
  long local_e0;
  long local_d8;
  long local_d0;
  long local_c8;
  char local_b9;
  undefined8 local_b8;
  undefined1 auStack_b0 [64];
  long local_70;
  
  local_70 = *_DAT_2681b4ee0;
  local_d0 = 0;
  local_c8 = 0;
  local_e0 = 0;
  local_d8 = 0;
  local_e8 = 0x3ff0000000000000;
  local_ec = 0;
  if (param_3 == 0) {
LAB_251b426e8:
    _APEndpointStreamScreenCreate_cold_28();
LAB_251b42714:
    puVar12 = (undefined8 *)0x0;
LAB_251b422c0:
    uVar11 = 0xffffbe88;
  }
  else {
    lVar8 = func_0x0002580f6a50(param_3);
    lVar9 = func_0x0002581018a0();
    if (lVar8 != lVar9) goto LAB_251b426e8;
    if (param_5 == 0) {
LAB_251b426f0:
      _APEndpointStreamScreenCreate_cold_27();
      goto LAB_251b42714;
    }
    lVar8 = func_0x0002580f6a50(param_5);
    lVar9 = _APEndpointDescriptionGetTypeID();
    if (lVar8 != lVar9) goto LAB_251b426f0;
    if (param_8 == (long *)0x0) {
      _APEndpointStreamScreenCreate_cold_26();
      goto LAB_251b42714;
    }
    if (param_7 == 0) {
      _APEndpointStreamScreenCreate_cold_25();
      goto LAB_251b42714;
    }
    if (param_2 == 0) {
      lVar8 = 0;
    }
    else {
      lVar8 = func_0x000258102680(param_2,&cfstringStruct_27612ce10);
      if (lVar8 == 0) {
        lVar8 = 0;
      }
      else {
        lVar9 = func_0x0002580f6a50();
        lVar10 = func_0x00025810e430();
        if (lVar9 != lVar10) {
          lVar8 = 0;
        }
      }
      func_0x00025810b080(param_2,*_DAT_2680eb6c0,&local_e8);
      func_0x00025810b090(param_2,*_DAT_2680eb6a0,&local_ec);
      func_0x000258102680(param_2,_kAPEndpointStreamCreationOptionKey_LogPrefix);
    }
    if (param_4 == 0 && lVar8 == 0) {
      _APEndpointStreamScreenCreate_cold_24();
      goto LAB_251b42714;
    }
    if ((param_4 != 0) && (lVar8 != 0)) {
      _APEndpointStreamScreenCreate_cold_1();
      goto LAB_251b42714;
    }
    uVar11 = func_0x00025810f560();
    uVar11 = func_0x00025810acc0(param_1,&_kAPEndpointStreamScreenVTable,uVar11,&local_c8);
    if ((int)uVar11 == 0) {
      puVar12 = (undefined8 *)func_0x00025810ac50(local_c8);
      func_0x00025810bb20(auStack_b0,0x40,"APEndpointStreamScreen.%{ptr}");
      uVar11 = func_0x0002580f54e0(auStack_b0,0);
      *puVar12 = uVar11;
      uVar11 = func_0x0002580f6d10(auStack_b0);
      puVar12[2] = uVar11;
      uVar11 = func_0x0002580f54e0("APEndpointStreamScreen.properties",0);
      puVar12[0x3e] = uVar11;
      func_0x00025810bb20(auStack_b0,0x40,"APEndpointStreamScreen.%{ptr}.notification");
      uVar11 = func_0x0002580f54e0(auStack_b0,0);
      puVar12[0xc] = uVar11;
      puVar12[0x23] = local_e8;
      *(undefined4 *)(puVar12 + 0x24) = local_ec;
      uVar11 = func_0x0002580f6a60(param_3);
      puVar12[1] = uVar11;
      uVar11 = func_0x0002580f6a60(param_5);
      puVar12[7] = uVar11;
      uVar11 = func_0x00025810aa80(0,"%@%s[%{ptr}]");
      puVar12[5] = uVar11;
      uVar11 = _APEndpointDescriptionGetCMBaseObject(puVar12[7]);
      lVar9 = func_0x000258109150();
      puVar19 = (undefined8 *)(*(long *)(lVar9 + 8) + 0x30);
      pcVar18 = (code *)*puVar19;
      if ((pcVar18 == (code *)0x0) || (pcVar18 == (code *)0x0)) {
        uVar11 = 0xffffce12;
LAB_251b40f58:
        uVar21 = 0xe04;
LAB_251b40f68:
        func_0x000258109a30(uVar11,"APEndpointStreamScreenCreate",uVar21,0);
        goto LAB_251b40f70;
      }
      uVar21 = *_DAT_2680d3150;
      uVar11 = (*pcVar18)((ulong)puVar19 & 0xffffffffffff | 0x9725000000000000,uVar11,
                          _kAPEndpointDescriptionProperty_DisplayDescriptionArray,uVar21,&local_d0);
      if ((int)uVar11 != 0) goto LAB_251b40f58;
      if ((local_d0 != 0) && (lVar9 = func_0x0002581017d0(), 0 < lVar9)) {
        lVar9 = func_0x0002581017e0(local_d0,0);
        if (lVar9 == 0) {
          _APEndpointStreamScreenCreate_cold_22();
          goto LAB_251b422c0;
        }
        if (param_6 == 0) {
          uVar11 = func_0x0002580f6a60(lVar9);
          puVar12[9] = uVar11;
          uVar6 = 0x6e;
        }
        else {
          uVar11 = func_0x0002580f6a60(param_6);
          puVar12[9] = uVar11;
          uVar11 = _kAPEndpointDisplayDescriptionProperty_UUID;
          _APEndpointDisplayDescriptionCopyProperty
                    (lVar9,_kAPEndpointDisplayDescriptionProperty_UUID,uVar21,&local_d8);
          if (local_d8 == 0) {
            _APEndpointStreamScreenCreate_cold_3();
            goto LAB_251b422c0;
          }
          _APEndpointDisplayDescriptionCopyProperty(puVar12[9],uVar11,uVar21,&local_e0);
          iVar5 = func_0x00025810b1a0(local_e0,local_d8);
          uVar6 = 0x6e;
          if (iVar5 == 0) {
            uVar6 = 0x6f;
          }
        }
        *(undefined4 *)(puVar12 + 0xb) = uVar6;
        if (param_4 == 0) {
          uVar11 = 0;
        }
        else {
          uVar11 = func_0x0002580f6a60(param_4);
        }
        puVar12[6] = uVar11;
        if (lVar8 == 0) {
          uVar11 = 0;
        }
        else {
          uVar11 = func_0x0002580f6a60(lVar8);
        }
        puVar12[0x10] = uVar11;
        uVar11 = func_0x0002580f6ca0(_DAT_2681b4e38,0,0,*puVar12);
        puVar12[0x19] = uVar11;
        local_118 = _DAT_2681b4ed0;
        local_110 = DAT_251c6aff8;
        local_108 = ___APEndpointStreamScreenCreate_block_invoke;
        puStack_100 = &___block_descriptor_tmp;
        local_f8 = local_c8;
        func_0x0002580f6cb0(uVar11,&local_118);
        func_0x0002580f6cc0(puVar12[0x19],0xffffffffffffffff,0,0);
        func_0x000258102360(puVar12[0x19]);
        uVar11 = func_0x0002580f6a60(param_7);
        puVar12[8] = uVar11;
        lVar8 = func_0x00025810ac50(local_c8);
        if (param_2 == 0) {
          uVar11 = 0;
        }
        else {
          uVar11 = func_0x000258102680(param_2,&cfstringStruct_27612e5f0);
        }
        puVar19 = (undefined8 *)(lVar8 + 0x478);
        if (*(long *)(lVar8 + 0x478) != 0) {
          func_0x0002580f5830();
          *puVar19 = 0;
        }
        uVar11 = func_0x00025810d330(0xff00000,*(undefined8 *)(lVar8 + 8),4,0,uVar11,puVar19);
        if ((int)uVar11 != 0) {
          _APEndpointStreamScreenCreate_cold_4();
          goto LAB_251b40f70;
        }
        func_0x00025810d320(*puVar19,0xff00000,0x2b160258);
        func_0x00025810d320(*puVar19,0xff00002,0x2b16025c);
        uVar11 = func_0x0002580f54e0("APEndpointStreamScreen.%{ptr}.RTC",0);
        puVar12[0x90] = uVar11;
        uVar11 = func_0x0002581017c0(param_1,0,_DAT_2680d3338);
        lVar8 = local_c8;
        puVar12[0x91] = uVar11;
        lVar9 = func_0x00025810ac50(local_c8);
        local_b9 = '\0';
        if (*(char *)(lVar9 + 0x18) != '\0') {
          _APEndpointStreamScreenCreate_cold_5();
          uVar11 = 0xffffbe86;
          goto LAB_251b427e4;
        }
        if (*(char *)(lVar9 + 0x19) != '\0') {
LAB_251b426a4:
          _APEndpointStreamScreenCreate_cold_21(&local_b9,puVar12 + 5,&local_c8,puVar12 + 0x10);
LAB_251b425f0:
          uVar11 = 0;
          *param_8 = local_c8;
          local_c8 = 0;
          goto LAB_251b42604;
        }
        local_b8 = local_b8 & 0xffffffff00000000;
        lVar10 = func_0x000258109860(*(undefined8 *)(lVar9 + 0x38),
                                     _kAPEndpointDescriptionProperty_IsConnectedOverUSB,&local_b8);
        *(bool *)(lVar9 + 0x185) = lVar10 != 0;
        uVar6 = 0;
        if (*(long *)(lVar9 + 0x30) != 0) {
          uVar6 = func_0x000258109860(*(long *)(lVar9 + 0x30),
                                      _kAPSenderSessionProperty_ControlConnectionInterfaceLatencyHint
                                      ,&local_b8);
        }
        *(undefined4 *)(lVar9 + 0x4a4) = uVar6;
        lVar10 = func_0x000258109860(*(undefined8 *)(lVar9 + 0x38),
                                     _kAPEndpointDescriptionProperty_IsCarPlay,&local_b8);
        *(bool *)(lVar9 + 0x183) = lVar10 != 0;
        lVar10 = func_0x000258109860(*(undefined8 *)(lVar9 + 0x38),
                                     _kAPEndpointDescriptionProperty_IsScreenDemoMode,0);
        *(bool *)(lVar9 + 400) = lVar10 != 0;
        uVar4 = _APDemoManagerIsDemoSession
                          (*(undefined8 *)(lVar9 + 0x38),*(undefined8 *)(lVar9 + 0x30));
        *(undefined1 *)(lVar9 + 0x191) = uVar4;
        *(undefined1 *)(lVar9 + 0x192) = 0;
        if (*(char *)(lVar9 + 0x183) == '\0') {
          uVar6 = func_0x000258109db0(*(undefined4 *)(lVar9 + 0x4a4));
        }
        else {
          uVar6 = func_0x00025810d090(*(undefined1 *)(lVar9 + 0x185));
        }
        *(undefined4 *)(lVar9 + 0x49c) = uVar6;
        iVar5 = func_0x00025810dc80();
        iVar17 = *(int *)(lVar9 + 0x49c);
        if (iVar5 <= iVar17) {
          iVar5 = iVar17;
        }
        *(int *)(lVar9 + 0x4a0) = iVar5;
        if (_gLogCategory_APEndpointStreamScreen < 0x29) {
          if (_gLogCategory_APEndpointStreamScreen == -1) {
            iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028);
            iVar17 = *(int *)(lVar9 + 0x49c);
            if (iVar5 == 0) goto LAB_251b412b8;
          }
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_init(StreamScreenStorage *)",0x2000028,
                              "%@ initial latency settings are screen latency: %d, media presentation mode latency: %d\n"
                             );
          iVar17 = *(int *)(lVar9 + 0x49c);
        }
LAB_251b412b8:
        uVar11 = func_0x00025810b890((long)iVar17);
        *(undefined8 *)(lVar9 + 0x3b8) = uVar11;
        *(undefined4 *)(lVar9 + 0x3c0) = 0;
        *(undefined1 *)(lVar9 + 0x3c4) = 0;
        lVar10 = func_0x000258109860(*(undefined8 *)(lVar9 + 0x38),
                                     _kAPEndpointDescriptionProperty_SupportsStatsAsBody,0);
        *(bool *)(lVar9 + 0x3c5) = lVar10 != 0;
        lVar10 = func_0x000258109860(*(undefined8 *)(lVar9 + 0x38),
                                     _kAPEndpointDescriptionProperty_SupportsScreenMultiCodec,0);
        *(bool *)(lVar9 + 0x3c7) = lVar10 != 0;
        lVar10 = func_0x000258109860(*(undefined8 *)(lVar9 + 0x38),
                                     _kAPEndpointDescriptionProperty_ForwardFrameUserData,0);
        *(bool *)(lVar9 + 0x3ca) = lVar10 != 0;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_init(StreamScreenStorage *)",0x2000028,
                              "%@ forward frame user data: %s\n");
        }
        lVar10 = func_0x000258109860(*(undefined8 *)(lVar9 + 0x38),
                                     _kAPEndpointDescriptionProperty_ForwardCryptorSubsampleAuxData,
                                     0);
        *(bool *)(lVar9 + 0x3cb) = lVar10 != 0;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_init(StreamScreenStorage *)",0x2000028,
                              "%@ forward cryptor aux data: %s\n");
        }
        puVar20 = (undefined8 *)(lVar9 + 0x28);
        *(undefined1 *)(lVar9 + 0x3c8) = 0;
        *(undefined8 *)(lVar9 + 0x3b0) = *puVar20;
        uVar2 = _UNK_251c6bae8;
        uVar11 = _DAT_251c6bae0;
        uVar24 = _DAT_2680d3700[1];
        uVar23 = *_DAT_2680d3700;
        *(undefined8 *)(lVar9 + 0x100) = uVar24;
        *(undefined8 *)(lVar9 + 0xf8) = uVar23;
        *(undefined8 *)(lVar9 + 0x110) = uVar24;
        *(undefined8 *)(lVar9 + 0x108) = uVar23;
        *(undefined8 *)(lVar9 + 0xe0) = uVar2;
        *(undefined8 *)(lVar9 + 0xd8) = uVar11;
        *(undefined8 *)(lVar9 + 0xf0) = uVar24;
        *(undefined8 *)(lVar9 + 0xe8) = uVar23;
        uVar11 = _APEndpointDescriptionGetCMBaseObject(*(undefined8 *)(lVar9 + 0x38));
        lVar10 = func_0x000258109150();
        puVar19 = (undefined8 *)(*(long *)(lVar10 + 8) + 0x30);
        pcVar18 = (code *)*puVar19;
        if ((pcVar18 == (code *)0x0) || (pcVar18 == (code *)0x0)) {
          uVar6 = 0xffffce12;
        }
        else {
          uVar6 = (*pcVar18)((ulong)puVar19 & 0xffffffffffff | 0x9725000000000000,uVar11,
                             _kAPEndpointDescriptionProperty_ReceiverHDRCapability,uVar21,
                             lVar9 + 0x128);
        }
        *(undefined1 *)(lVar9 + 0x172) = 0;
        *(undefined2 *)(lVar9 + 0x170) = 0;
        *(undefined1 *)(lVar9 + 0x175) = 1;
        local_b8._0_4_ = uVar6;
        lVar10 = func_0x000258109e00(&cfstringStruct_276131490,0);
        *(bool *)(lVar9 + 0x176) = lVar10 == 0;
        *(undefined1 *)(lVar9 + 0x150) = 0;
        *(undefined1 *)(lVar9 + 0x174) = 1;
        puVar1 = (undefined4 *)(lVar9 + 0x177);
        *puVar1 = 0x100;
        *(undefined4 *)(lVar9 + 0x17c) = *(undefined4 *)(lVar9 + 0x4a0);
        lVar10 = func_0x000258109860(*(undefined8 *)(lVar9 + 0x38),
                                     _kAPEndpointDescriptionProperty_CanRecordScreenStream,0);
        *(bool *)(lVar9 + 0x173) = lVar10 != 0;
        *(undefined8 *)(lVar9 + 0x168) = 0;
        *(undefined1 *)(lVar9 + 0x184) = 0;
        *(bool *)(lVar9 + 0x3c6) = *(char *)(lVar9 + 0x183) == '\0';
        *(undefined8 *)(lVar9 + 0x188) = DAT_251c6ba98;
        uVar6 = func_0x000258109e00(&cfstringStruct_2761376b0,0);
        *(undefined4 *)(lVar9 + 0x498) = uVar6;
        *(undefined1 *)(lVar9 + 0x182) = 0;
        uVar11 = _DAT_251c6baf0;
        *(undefined8 *)(lVar9 + 0x1a8) = _UNK_251c6baf8;
        *(undefined8 *)(lVar9 + 0x1a0) = uVar11;
        *(undefined8 *)(lVar9 + 0x1b0) = 0x418312d000000000;
        uVar23 = _UNK_251c6bb18;
        uVar2 = _DAT_251c6bb10;
        uVar11 = _DAT_251c6bb00;
        *(undefined8 *)(lVar9 + 0x1c8) = _UNK_251c6bb08;
        *(undefined8 *)(lVar9 + 0x1c0) = uVar11;
        *(undefined8 *)(lVar9 + 0x1d8) = uVar23;
        *(undefined8 *)(lVar9 + 0x1d0) = uVar2;
        *(undefined8 *)(lVar9 + 0x1e0) = 0;
        lVar10 = func_0x00025810bd80();
        *(long *)(lVar9 + 0x1e8) = lVar10 * 5;
        local_b8 = (ulong)local_b8._4_4_ << 0x20;
        uVar6 = *(undefined4 *)(lVar9 + 0x4a4);
        uVar7 = func_0x00025810b2f0(&cfstringStruct_276131530,&cfstringStruct_27612dcf0,
                                    *(undefined4 *)(lVar9 + 0x3c0));
        *(undefined4 *)(lVar9 + 0x3c0) = uVar7;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ remote log level: %d\n");
        }
        uVar4 = func_0x00025810b2f0(&cfstringStruct_276131550,&cfstringStruct_27612dcf0,
                                    *(undefined1 *)(lVar9 + 0x3c4));
        *(undefined1 *)(lVar9 + 0x3c4) = uVar4;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ show HUD: %s\n");
        }
        uVar4 = func_0x00025810b2f0(&cfstringStruct_276140210,&cfstringStruct_27612dcf0,
                                    *(undefined1 *)(lVar9 + 0x3c8));
        *(undefined1 *)(lVar9 + 0x3c8) = uVar4;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ force multi codec: %s\n");
        }
        uVar11 = func_0x00025810b820();
        uVar4 = func_0x00025810b2f0(&cfstringStruct_276140230,&cfstringStruct_27612dcf0,uVar11);
        *(undefined1 *)(lVar9 + 0x3c9) = uVar4;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ log histograms: %s\n");
        }
        uVar4 = func_0x00025810b2f0(&cfstringStruct_276140250,&cfstringStruct_27612dcf0,
                                    *(undefined1 *)(lVar9 + 0x174));
        *(undefined1 *)(lVar9 + 0x174) = uVar4;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ max display size enabled: %s\n");
        }
        uVar4 = func_0x00025810b2f0(&cfstringStruct_2761314f0,&cfstringStruct_27612dcf0,
                                    *(undefined1 *)(lVar9 + 0x175));
        *(undefined1 *)(lVar9 + 0x175) = uVar4;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ HDR enabled: %s\n");
        }
        uVar4 = func_0x00025810b2f0(&cfstringStruct_276131510,&cfstringStruct_27612dcf0,
                                    *(undefined1 *)(lVar9 + 0x176));
        *(undefined1 *)(lVar9 + 0x176) = uVar4;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ DoVi enabled: %s\n");
        }
        dVar22 = (double)func_0x00025810b2e0(*(undefined8 *)(lVar9 + 0x1c0),
                                             &cfstringStruct_276140270,&cfstringStruct_27612dcf0);
        *(double *)(lVar9 + 0x1c0) = dVar22;
        if (((0.0 < dVar22) && (_gLogCategory_APEndpointStreamScreen < 0x29)) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ fixed encoder bandwidth: %f bps\n");
        }
        iVar5 = func_0x00025810b2f0(&cfstringStruct_276140290,&cfstringStruct_27612dcf0,
                                    *(undefined4 *)(lVar9 + 0x1d4));
        *(int *)(lVar9 + 0x1d4) = iVar5;
        if (((0 < iVar5) && (_gLogCategory_APEndpointStreamScreen < 0x29)) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ fixed encoder FPS: %d\n");
        }
        uVar7 = func_0x00025810b2f0(&cfstringStruct_276133ed0,&cfstringStruct_27612dcf0,
                                    *(undefined4 *)(lVar9 + 0x1d0));
        *(undefined4 *)(lVar9 + 0x1d0) = uVar7;
        if (_gLogCategory_APEndpointStreamScreen < 0x29) {
          if (_gLogCategory_APEndpointStreamScreen == -1) {
            iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028);
            uVar7 = *(undefined4 *)(lVar9 + 0x1d0);
            if (iVar5 == 0) goto LAB_251b41b58;
          }
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ max FPS: %d\n");
          uVar7 = *(undefined4 *)(lVar9 + 0x1d0);
        }
LAB_251b41b58:
        *(undefined4 *)(lVar9 + 0x1d8) = uVar7;
        *(undefined4 *)(lVar9 + 0x1dc) = uVar7;
        uVar11 = func_0x00025810b2e0(*(undefined8 *)(lVar9 + 0x1a8),&cfstringStruct_2761402b0,
                                     &cfstringStruct_27612dcf0);
        *(undefined8 *)(lVar9 + 0x1a8) = uVar11;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ bandwidth min: %f bps\n");
        }
        uVar11 = func_0x00025810b2e0(*(undefined8 *)(lVar9 + 0x1b0),&cfstringStruct_2761402d0,
                                     &cfstringStruct_27612dcf0);
        *(undefined8 *)(lVar9 + 0x1b0) = uVar11;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ bandwidth max: %f bps\n");
        }
        uVar4 = func_0x00025810b2f0(&cfstringStruct_2761402f0,&cfstringStruct_27612dcf0,
                                    *(undefined1 *)(lVar9 + 0x178));
        *(undefined1 *)(lVar9 + 0x178) = uVar4;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ enable mirroring restrictions: %s\n");
        }
        iVar5 = func_0x00025810b2f0(&cfstringStruct_276140310,&cfstringStruct_27612dcf0,
                                    *(undefined4 *)(lVar9 + 0x17c));
        *(int *)(lVar9 + 0x17c) = iVar5;
        if (((0 < iVar5) && (_gLogCategory_APEndpointStreamScreen < 0x29)) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                              "%@ requested max encoder latency: %d\n");
        }
        if (*(char *)(lVar9 + 0x183) != '\0') {
          iVar5 = func_0x00025810b2f0(&cfstringStruct_276140330,&cfstringStruct_27612dcf0,0);
          *(int *)(lVar9 + 0x188) = iVar5;
          if (((0 < iVar5) && (_gLogCategory_APEndpointStreamScreen < 0x29)) &&
             ((_gLogCategory_APEndpointStreamScreen != -1 ||
              (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
              iVar5 != 0)))) {
            func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                                "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                                "%@ will use APVirtualDisplayTestSink in mode %d\n");
          }
          uVar7 = func_0x00025810b2f0(&cfstringStruct_276140350,&cfstringStruct_276132350,
                                      *(undefined4 *)(lVar9 + 0x18c));
          *(undefined4 *)(lVar9 + 0x18c) = uVar7;
          if ((_gLogCategory_APEndpointStreamScreen < 0x33) &&
             ((_gLogCategory_APEndpointStreamScreen != -1 ||
              (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000032),
              iVar5 != 0)))) {
            func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                                "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000032,
                                "%@ max times to reencode idle frame: %d\n");
          }
        }
        lVar10 = func_0x000258109dd0(&cfstringStruct_276131870,&local_b8);
        if (((int)local_b8 == 0) && (lVar10 != 0)) {
          lVar13 = func_0x0002580f6a50(lVar10);
          lVar14 = func_0x0002581018a0();
          if (lVar13 == lVar14) {
            lVar13 = *(long *)(lVar9 + 0x128);
            *(long *)(lVar9 + 0x128) = lVar10;
            func_0x0002580f6a60(lVar10);
            if (lVar13 != 0) {
              func_0x0002580f5830(lVar13);
            }
            if ((_gLogCategory_APEndpointStreamScreen < 0x33) &&
               ((_gLogCategory_APEndpointStreamScreen != -1 ||
                (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000032),
                iVar5 != 0)))) {
              _APEndpointStreamScreenCreate_cold_6(puVar20,lVar9 + 0x128);
            }
          }
LAB_251b41f1c:
          func_0x0002580f5830(lVar10);
        }
        else if (lVar10 != 0) goto LAB_251b41f1c;
        local_b8 = local_b8 & 0xffffffff00000000;
        iVar5 = func_0x00025810b2f0(&cfstringStruct_276140370,&cfstringStruct_27612dcf0,uVar6);
        if (iVar5 != *(int *)(lVar9 + 0x4a4)) {
          *(int *)(lVar9 + 0x4a4) = iVar5;
          if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
             ((_gLogCategory_APEndpointStreamScreen != -1 ||
              (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
              iVar5 != 0)))) {
            func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                                "void screenstream_initFromPrefs(StreamScreenStorage *)",0x2000028,
                                "%@ connection latency hint: %d\n");
          }
          if (*(char *)(lVar9 + 0x183) == '\0') {
            uVar6 = func_0x000258109db0(*(undefined4 *)(lVar9 + 0x4a4));
            *(undefined4 *)(lVar9 + 0x49c) = uVar6;
          }
        }
        iVar5 = func_0x00025810b820();
        if ((iVar5 != 0) && (lVar10 = func_0x000258109dd0(&cfstringStruct_276140390,0), lVar10 != 0)
           ) {
          lVar13 = func_0x0002580f6a50();
          lVar14 = func_0x0002581018a0();
          if (lVar13 == lVar14) {
            lVar13 = *(long *)(lVar9 + 0x198);
            *(long *)(lVar9 + 0x198) = lVar10;
            func_0x0002580f6a60(lVar10);
            if (lVar13 != 0) {
              func_0x0002580f5830(lVar13);
            }
            if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
               ((_gLogCategory_APEndpointStreamScreen != -1 ||
                (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
                iVar5 != 0)))) {
              _APEndpointStreamScreenCreate_cold_7(puVar20,lVar9 + 0x198);
            }
          }
          func_0x0002580f5830(lVar10);
        }
        uVar11 = func_0x00025810eb50();
        uVar11 = func_0x00025810eb10(uVar21,0,uVar11,lVar9 + 0x68);
        if ((int)uVar11 == 0) {
          uVar11 = func_0x00025810eb70(*(undefined8 *)(lVar9 + 0x68),
                                       _screenstream_signalDataAvailable,lVar9,0xb,0,lVar9 + 0x70);
          if ((int)uVar11 == 0) {
            if (param_2 != 0) {
              lVar10 = func_0x000258102680(param_2,_kAPEndpointStreamCreationOptionKey_ClientPID);
              if (lVar10 != 0) {
                lVar13 = func_0x0002580f6a50();
                lVar14 = func_0x000258101850();
                if (lVar13 == lVar14) {
                  lVar13 = *(long *)(lVar9 + 0xc0);
                  *(long *)(lVar9 + 0xc0) = lVar10;
                  func_0x0002580f6a60(lVar10);
                  goto joined_r0x000251b420d4;
                }
                _APEndpointStreamScreenCreate_cold_10();
LAB_251b427e0:
                uVar11 = 0xffffbe88;
                goto LAB_251b427e4;
              }
              lVar13 = *(long *)(lVar9 + 0xc0);
              *(undefined8 *)(lVar9 + 0xc0) = 0;
joined_r0x000251b420d4:
              if (lVar13 != 0) {
                func_0x0002580f5830(lVar13);
              }
              lVar10 = func_0x000258102680(param_2,_kAPEndpointStreamCreationOptionKey_ScreenSource)
              ;
              if (lVar10 == 0) {
                lVar13 = *(long *)(lVar9 + 0x90);
                *(undefined8 *)(lVar9 + 0x90) = 0;
              }
              else {
                lVar13 = func_0x0002580f6a50(lVar10);
                lVar14 = func_0x00025810f820();
                if (lVar13 != lVar14) {
                  _APEndpointStreamScreenCreate_cold_11();
                  goto LAB_251b427e0;
                }
                lVar13 = *(long *)(lVar9 + 0x90);
                *(long *)(lVar9 + 0x90) = lVar10;
                func_0x0002580f6a60(lVar10);
              }
              if (lVar13 != 0) {
                func_0x0002580f5830(lVar13);
              }
              lVar13 = func_0x000258102680(param_2,
                                           _kAPEndpointStreamCreationOptionKey_ScreenProcessor);
              if (lVar13 == 0) {
                lVar14 = *(long *)(lVar9 + 0x98);
                *(undefined8 *)(lVar9 + 0x98) = 0;
              }
              else {
                lVar14 = func_0x0002580f6a50(lVar13);
                lVar15 = func_0x00025810f7d0();
                if (lVar14 != lVar15) {
                  _APEndpointStreamScreenCreate_cold_12();
                  goto LAB_251b427e0;
                }
                lVar14 = *(long *)(lVar9 + 0x98);
                *(long *)(lVar9 + 0x98) = lVar13;
                func_0x0002580f6a60(lVar13);
              }
              if (lVar14 != 0) {
                func_0x0002580f5830(lVar14);
              }
              lVar14 = func_0x000258102680(param_2,
                                           _kAPEndpointStreamCreationOptionKey_ScreenUsageMode);
              if (lVar14 == 0) {
                lVar15 = *(long *)(lVar9 + 0xa8);
                *(undefined8 *)(lVar9 + 0xa8) = 0;
              }
              else {
                lVar15 = func_0x0002580f6a50();
                lVar16 = func_0x0002581018a0();
                if (lVar15 != lVar16) {
                  _APEndpointStreamScreenCreate_cold_13();
                  goto LAB_251b427e0;
                }
                lVar15 = *(long *)(lVar9 + 0xa8);
                *(long *)(lVar9 + 0xa8) = lVar14;
                func_0x0002580f6a60(lVar14);
              }
              if (lVar15 != 0) {
                func_0x0002580f5830(lVar15);
              }
              if (lVar10 == 0 && lVar13 == 0) {
                lVar10 = func_0x000258102680(param_2,
                                             _kAPEndpointStreamCreationOptionKey_ProtectionOptions);
                if (lVar10 == 0) {
                  lVar13 = *(long *)(lVar9 + 0x148);
                  *(undefined8 *)(lVar9 + 0x148) = 0;
                }
                else {
                  lVar13 = func_0x0002580f6a50(lVar10);
                  lVar14 = func_0x000258102670();
                  if (lVar13 != lVar14) {
                    _APEndpointStreamScreenCreate_cold_14();
                    goto LAB_251b427e0;
                  }
                  lVar13 = *(long *)(lVar9 + 0x148);
                  *(long *)(lVar9 + 0x148) = lVar10;
                  func_0x0002580f6a60(lVar10);
                }
                if (lVar13 != 0) {
                  func_0x0002580f5830(lVar13);
                }
                if (((lVar10 != 0) && (_gLogCategory_APEndpointStreamScreen < 0x29)) &&
                   ((_gLogCategory_APEndpointStreamScreen != -1 ||
                    (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
                    iVar5 != 0)))) {
                  func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                                      "OSStatus screenstream_activate(FigEndpointStreamRef, CFDictionaryRef)"
                                      ,0x2000028,"%@ PWD activation options: %@\n");
                }
              }
              lVar10 = func_0x000258102680(param_2,
                                           _kAPEndpointStreamCreationOptionKey_ScreenOverrides);
              if (lVar10 == 0) {
LAB_251b4232c:
                lVar13 = *(long *)(lVar9 + 0xb0);
                *(undefined8 *)(lVar9 + 0xb0) = 0;
              }
              else {
                lVar13 = func_0x0002580f6a50();
                lVar14 = func_0x000258102670();
                if ((lVar13 != lVar14) || (iVar5 = func_0x00025810b820(), iVar5 == 0))
                goto LAB_251b4232c;
                lVar13 = *(long *)(lVar9 + 0xb0);
                *(long *)(lVar9 + 0xb0) = lVar10;
                func_0x0002580f6a60(lVar10);
              }
              if (lVar13 != 0) {
                func_0x0002580f5830(lVar13);
              }
              func_0x00025810b040(param_2,_kAPEndpointStreamCreationOptionKey_IsMediaPresentation,
                                  &local_b9);
              func_0x00025810b040(param_2,
                                  _kAPEndpointStreamCreationOptionKey_IsMediaPresentationModeAvailable
                                  ,puVar1);
              if ((_gLogCategory_APEndpointStreamScreen < 0x33) &&
                 ((_gLogCategory_APEndpointStreamScreen != -1 ||
                  (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000032),
                  iVar5 != 0)))) {
                _APEndpointStreamScreenCreate_cold_15(puVar20,puVar1);
              }
              func_0x00025810b040(param_2,_kAPEndpointStreamCreationOptionKey_UseCarPlayHEVC,
                                  lVar9 + 0x184);
              func_0x00025810b040(param_2,_kAPEndpointStreamCreationOptionKey_IsAuxScreenStream,
                                  lVar9 + 0x182);
              iVar5 = func_0x00025810b060(param_2,
                                          _kAPEndpointStreamCreationOptionKey_OverrideCanvasSize,
                                          lVar9 + 0xe8);
              if (((iVar5 != 0) && (_gLogCategory_APEndpointStreamScreen < 0x33)) &&
                 ((_gLogCategory_APEndpointStreamScreen != -1 ||
                  (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000032),
                  iVar5 != 0)))) {
                _APEndpointStreamScreenCreate_cold_16(puVar20);
              }
            }
            cVar3 = local_b9;
            lVar10 = func_0x00025810ac50(lVar8);
            local_b8 = 0;
            uVar11 = _screenstream_initDisplayInfo();
            if ((int)uVar11 == 0) {
              if (*(int *)(lVar10 + 0x188) < 1) {
                uVar11 = _APVirtualDisplaySinkCreate(lVar8,*(undefined8 *)(lVar10 + 0x68),&local_b8)
                ;
              }
              else {
                uVar11 = _APVirtualDisplayTestSinkCreate
                                   (*(int *)(lVar10 + 0x188),lVar8,*(undefined8 *)(lVar10 + 0x68),
                                    &local_b8);
              }
              if ((int)uVar11 == 0) {
                lVar13 = *(long *)(lVar10 + 0x90);
                if (lVar13 == 0) {
                  lVar13 = func_0x00025810f830();
                }
                if ((cVar3 != '\0') && (*(char *)(lVar10 + 0x177) != '\0')) {
                  if ((_gLogCategory_APEndpointStreamScreen < 0x33) &&
                     ((_gLogCategory_APEndpointStreamScreen != -1 ||
                      (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000032),
                      iVar5 != 0)))) {
                    _APEndpointStreamScreenCreate_cold_18(lVar10);
                  }
                  *(undefined8 *)(lVar10 + 0x168) = 1;
                }
                lVar14 = _screenstream_createVirtualDisplayActivationOptions(lVar8);
                lVar13 = func_0x00025810f7e0(lVar13,local_b8,lVar14);
                *(long *)(lVar10 + 0xa0) = lVar13;
                if (lVar13 == 0) {
                  _APEndpointStreamScreenCreate_cold_19();
                  uVar11 = 0xffffbe87;
                }
                else {
                  func_0x0002580f6a60();
                  uVar11 = func_0x00025810ad10();
                  func_0x00025810ad00(uVar11,lVar8,_screenstream_virtualDisplaySourceTerminated,
                                      *_DAT_2680eb648,*(undefined8 *)(lVar10 + 0xa0),0);
                  uVar11 = *(undefined8 *)(lVar10 + 0xa0);
                  lVar10 = func_0x000258109150(uVar11);
                  puVar19 = (undefined8 *)(*(long *)(lVar10 + 0x10) + 0x28);
                  pcVar18 = (code *)*puVar19;
                  if ((pcVar18 == (code *)0x0) || (pcVar18 == (code *)0x0)) {
                    uVar11 = 0xffffce12;
                  }
                  else {
                    uVar11 = (*pcVar18)((ulong)puVar19 & 0xffffffffffff | 0xfdb3000000000000,uVar11)
                    ;
                    if ((int)uVar11 == 0) goto joined_r0x000251b42598;
                  }
                  func_0x000258109a30(uVar11,"screenstream_activateVirtualDisplaySession",0xc02,0);
                }
joined_r0x000251b42598:
                if (lVar14 != 0) {
                  func_0x0002580f5830(lVar14);
                }
              }
              else {
                _APEndpointStreamScreenCreate_cold_17(uVar11);
              }
              if (local_b8 != 0) {
                func_0x0002580f5830();
              }
              if ((int)uVar11 == 0) {
                *(undefined1 *)(lVar9 + 0x19) = 1;
                if (_gLogCategory_APEndpointStreamScreen < 0x33) {
                  if ((_gLogCategory_APEndpointStreamScreen != -1) ||
                     (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000032),
                     iVar5 != 0)) {
                    _APEndpointStreamScreenCreate_cold_20(puVar20,lVar9,lVar8);
                  }
                  goto LAB_251b426a4;
                }
                goto LAB_251b425f0;
              }
            }
            else {
              func_0x000258109a30(uVar11,"screenstream_activateVirtualDisplaySession",0xbe3,0);
            }
            func_0x000258109a30(uVar11,"screenstream_activate",0xc53,0);
          }
          else {
            _APEndpointStreamScreenCreate_cold_9();
          }
        }
        else {
          _APEndpointStreamScreenCreate_cold_8();
        }
LAB_251b427e4:
        if ((_gLogCategory_APEndpointStreamScreen < 0x5b) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x200005a),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "OSStatus screenstream_activate(FigEndpointStreamRef, CFDictionaryRef)"
                              ,0x200005a,"%@ ### activation failed: %#m\n");
        }
        _screenstream_cleanup(lVar8);
        uVar21 = 0xe2f;
        goto LAB_251b40f68;
      }
      _APEndpointStreamScreenCreate_cold_23();
      goto LAB_251b422c0;
    }
    _APEndpointStreamScreenCreate_cold_2();
    puVar12 = (undefined8 *)0x0;
  }
LAB_251b40f70:
  if ((_gLogCategory_APEndpointStreamScreen < 0x5b) &&
     ((_gLogCategory_APEndpointStreamScreen != -1 ||
      (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x200005a), iVar5 != 0))))
  {
    _APEndpointStreamScreenCreate_cold_29(puVar12,uVar11);
  }
LAB_251b42604:
  if (local_d0 != 0) {
    func_0x0002580f5830();
  }
  if (local_e0 != 0) {
    func_0x0002580f5830();
  }
  if (local_d8 != 0) {
    func_0x0002580f5830();
  }
  if (local_c8 != 0) {
    func_0x0002580f5830();
  }
  if (*_DAT_2681b4ee0 == local_70) {
    return uVar11;
  }
  uVar11 = func_0x0002580f4380();
  return uVar11;
}


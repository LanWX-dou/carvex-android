/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2518d4338
 * original code SHA256: c43c031ddc688773e405df85a301fce318c91719ad5624adf37fe112b9750117
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x0002518d6ba8) */
/* WARNING: Removing unreachable block (ram,0x0002518d60a8) */
/* WARNING: Removing unreachable block (ram,0x0002518d658c) */
/* WARNING: Removing unreachable block (ram,0x0002518d633c) */
/* WARNING: Removing unreachable block (ram,0x0002518d5bdc) */
/* WARNING: Removing unreachable block (ram,0x0002518d5b5c) */
/* WARNING: Removing unreachable block (ram,0x0002518d594c) */
/* WARNING: Removing unreachable block (ram,0x0002518d5ac8) */
/* WARNING: Removing unreachable block (ram,0x0002518d5c80) */
/* WARNING: Removing unreachable block (ram,0x0002518d5d20) */
/* WARNING: Removing unreachable block (ram,0x0002518d63bc) */
/* WARNING: Removing unreachable block (ram,0x0002518d705c) */
/* WARNING: Removing unreachable block (ram,0x0002518d74ac) */
/* WARNING: Removing unreachable block (ram,0x0002518d6c40) */
/* WARNING: Removing unreachable block (ram,0x0002518d47b8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _AirPlayReceiverSessionSetup(ulong *param_1,long param_2,long *param_3)

{
  char cVar1;
  ulong *puVar2;
  bool bVar3;
  bool bVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  bool bVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  uint uVar12;
  undefined4 uVar13;
  long lVar14;
  ulong uVar15;
  long lVar16;
  undefined8 uVar17;
  long lVar18;
  undefined8 uVar19;
  long lVar20;
  long lVar21;
  long lVar22;
  long lVar23;
  long lVar24;
  undefined8 uVar25;
  long lVar26;
  undefined8 extraout_x1;
  char *pcVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  ulong **ppuVar30;
  long *plVar31;
  code *pcVar32;
  undefined8 uVar33;
  undefined8 *puVar34;
  ulong uVar35;
  long lVar36;
  long lVar37;
  long lVar38;
  undefined8 uVar39;
  ulong uVar40;
  long local_1d0;
  uint local_1c4;
  undefined8 local_1c0;
  long local_1b8;
  ulong local_1b0;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined4 local_1a0;
  undefined4 uStack_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  ulong *local_190;
  long local_180;
  undefined1 auStack_178 [32];
  long local_158;
  code *pcStack_150;
  code *local_148;
  long local_138 [2];
  ulong *local_128;
  code *pcStack_120;
  code *local_118;
  ulong local_110;
  undefined8 uStack_108;
  undefined4 local_100;
  undefined4 uStack_fc;
  undefined4 local_f8;
  undefined4 uStack_f4;
  ulong *local_f0;
  undefined8 uStack_e8;
  undefined4 local_e0;
  uint uStack_dc;
  undefined4 uStack_d8;
  undefined2 uStack_d4;
  undefined2 uStack_d2;
  undefined4 uStack_d0;
  undefined2 uStack_cc;
  undefined2 uStack_ca;
  uint local_c8;
  undefined4 uStack_c4;
  ulong *local_c0;
  long lStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  long local_98;
  
  local_98 = *_DAT_2681b4ee0;
  local_1c4 = 0;
  cVar1 = (char)param_1[0x37];
  local_1d0 = 0;
  if ((_gLogCategory_AirPlayReceiverCore < 0x33) &&
     ((_gLogCategory_AirPlayReceiverCore != -1 ||
      (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032), iVar9 != 0)))) {
    if ((_gLogCategory_AirPlayReceiverCore < 0x1f) && (_gLogCategory_AirPlayReceiverCore == -1)) {
      func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x1e);
    }
    func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                        "OSStatus AirPlayReceiverSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFDictionaryRef *)"
                        ,0x2000032,"Setting up session [%{ptr}]: %llu with %##a %?@\n");
  }
  lVar14 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
  if (lVar14 == 0) {
    func_0x000258109a30(0,"AirPlayReceiverSessionSetup",0x6d7,0);
    local_1c4 = 0xffffe5b8;
  }
  else if (cVar1 == '\0') {
    iVar9 = func_0x00025810b820();
    if (iVar9 == 0) {
      lVar38 = 0;
    }
    else {
      func_0x000258109330();
      lVar38 = func_0x0002580f5640();
      uVar17 = func_0x000258109330();
      if ((lVar38 - 1U < 0xfffffffffffffffe) && (iVar9 = func_0x0002580f5630(), iVar9 != 0)) {
        uVar15 = param_1[0x1d];
        local_e0 = (undefined4)DAT_251913250;
        uStack_dc = (uint)param_1[0x1c];
        uStack_d8 = (undefined4)(param_1[0x1c] >> 0x20);
        uStack_d4 = 0x800;
        uStack_d2 = (undefined2)uVar15;
        uStack_d0 = (undefined4)(uVar15 >> 0x10);
        uStack_cc = (undefined2)(uVar15 >> 0x30);
        uStack_ca = 0x400;
        local_c8 = (uint)((int)param_1[0x58] == 1);
        func_0x0002580f5490(&MACH_HEADER,uVar17,1,lVar38,"Receiver Control Setup",
                            "SenderDeviceID: %llu ReceiverDeviceID: %llu isRC: %d",&local_e0,0x1c);
      }
    }
    if ((char)param_1[0x37] == '\0') {
      if (*(char *)((long)param_1 + 0x1b9) != '\0') {
        uVar17 = func_0x00025810bb60(*(undefined1 *)((long)param_1 + 0xb1),1,6,0,param_1 + 0x39,
                                     0xffffffff,(undefined4 *)((long)param_1 + 0x1c4));
        if ((int)uVar17 == 0) {
          if ((char)param_1[0x30] != '\0') {
            func_0x00025810bc20(*(undefined4 *)((long)param_1 + 0x1c4),1);
          }
          if ((_gLogCategory_AirPlayReceiverCore < 0x33) &&
             ((_gLogCategory_AirPlayReceiverCore != -1 ||
              (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032), iVar9 != 0
              )))) {
            func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                "OSStatus _ControlSetup(AirPlayReceiverSessionRef, CFMutableDictionaryRef)"
                                ,0x2000032,"[%{ptr}] Listening to port %d for event connection");
          }
          uVar15 = func_0x0002580f6ca0(_DAT_2681b4e28,(long)*(int *)((long)param_1 + 0x1c4),0,
                                       param_1[2]);
          param_1[3] = uVar15;
          if (uVar15 != 0) {
            func_0x0002580f6a60(param_1);
            uVar17 = DAT_251913160;
            local_e0 = (undefined4)_DAT_2681b4ed0;
            uStack_dc = (uint)(_DAT_2681b4ed0 >> 0x20);
            uStack_d8 = (undefined4)DAT_251913160;
            uVar10 = uStack_d8;
            uStack_d4 = (undefined2)((ulong)DAT_251913160 >> 0x20);
            uStack_d2 = (undefined2)((ulong)DAT_251913160 >> 0x30);
            uStack_d0 = 0x518deb74;
            uStack_cc = 2;
            uStack_ca = 0;
            local_c8 = 0x693dd998;
            uStack_c4 = 2;
            local_c0 = param_1;
            func_0x0002580f6cb0(&uStack_d0,param_1[3],&local_e0);
            local_110 = _DAT_2681b4ed0;
            uStack_108._4_4_ = (undefined4)((ulong)uVar17 >> 0x20);
            local_100 = 0x518df478;
            uStack_fc = 2;
            local_f8 = 0x693dd998;
            uStack_f4 = 2;
            uStack_108._0_4_ = uVar10;
            local_f0 = param_1;
            func_0x00025810bf20(&local_100,param_1[3],&local_110);
            func_0x000258102360(param_1[3]);
            func_0x00025810a790(lVar14,&cfstringStruct_276117fb0,(long)(int)param_1[0x39]);
            if ((_gLogCategory_AirPlayReceiverCore < 0x1f) &&
               ((_gLogCategory_AirPlayReceiverCore != -1 ||
                (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200001e),
                iVar9 != 0)))) {
              func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                  "OSStatus _ControlSetup(AirPlayReceiverSessionRef, CFMutableDictionaryRef)"
                                  ,0x200001e,"[%{ptr}] Events set up on port %d");
            }
            goto LAB_2518d46f4;
          }
          func_0x000258109a30(0,"_ControlSetup",0xa5f,0);
          uVar17 = 0xffffe5b8;
        }
        else {
          func_0x000258109a30(uVar17,"_ControlSetup",0xa57,0);
        }
        uVar12 = (uint)uVar17;
        __ControlTearDown(param_1);
        goto LAB_2518d7984;
      }
LAB_2518d46f4:
      *(undefined1 *)(param_1 + 0x37) = 1;
      uVar15 = _APReceiverStatsCollectorCreate();
      param_1[0x10] = uVar15;
      if (uVar15 == 0) {
LAB_2518d47d8:
        uVar12 = 0;
      }
      else {
        if ((_gLogCategory_AirPlayReceiverCore < 0x1f) &&
           ((_gLogCategory_AirPlayReceiverCore != -1 ||
            (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200001e), iVar9 != 0))
           )) {
          func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                              "OSStatus _ControlSetup(AirPlayReceiverSessionRef, CFMutableDictionaryRef)"
                              ,0x200001e,"[%{ptr}] created stats collector [%{ptr}]\n");
        }
        uVar15 = param_1[0x4c];
        uVar12 = 0;
        if (uVar15 != 0) {
          uVar35 = param_1[0x10];
          lVar16 = func_0x000258109150(uVar15);
          puVar34 = (undefined8 *)(*(long *)(lVar16 + 8) + 0x38);
          pcVar32 = (code *)*puVar34;
          if ((pcVar32 != (code *)0x0) && (pcVar32 != (code *)0x0)) {
            (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x2724000000000000,uVar15,
                       &cfstringStruct_276111f10,uVar35);
          }
          goto LAB_2518d47d8;
        }
      }
    }
    else {
      func_0x000258109a30(0,"_ControlSetup",0xa51,0);
      uVar12 = 0xffffe5c1;
LAB_2518d7984:
      if ((_gLogCategory_AirPlayReceiverCore < 0x3d) &&
         ((_gLogCategory_AirPlayReceiverCore != -1 ||
          (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200003c), iVar9 != 0))))
      {
        func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                            "OSStatus _ControlSetup(AirPlayReceiverSessionRef, CFMutableDictionaryRef)"
                            ,0x200003c,"[%{ptr}] Control setup failed: %#m\n");
      }
    }
    local_1c4 = uVar12;
    iVar9 = func_0x00025810b820();
    if (((iVar9 != 0) && (uVar17 = func_0x000258109330(), lVar38 - 1U < 0xfffffffffffffffe)) &&
       (iVar9 = func_0x0002580f5630(), iVar9 != 0)) {
      local_e0 = (undefined4)DAT_251913210;
      uStack_dc = local_1c4;
      func_0x0002580f5490(&MACH_HEADER,uVar17,2,lVar38,"Receiver Control Setup","Error: %d",
                          &local_e0,8);
    }
    uVar15 = (ulong)local_1c4;
    if (local_1c4 == 0) {
      lVar16 = func_0x00025810a6f0(param_2,&cfstringStruct_276119a50,0);
      if (lVar16 != 0) {
        *(undefined1 *)((long)param_1 + 0x2ec) = 1;
        uVar15 = func_0x00025810a6c0(param_2,&cfstringStruct_276119a70,0);
        param_1[0x5e] = uVar15;
      }
      lVar16 = func_0x00025810a6f0(param_2,&cfstringStruct_276117bd0,0);
      if (lVar16 != 0) {
        *(undefined1 *)(param_1 + 0x55) = 1;
        if (param_1[5] == 0) {
          uVar17 = 0;
        }
        else {
          uVar17 = *(undefined8 *)(param_1[5] + 0xd8);
        }
        local_e0 = 0;
        uStack_dc = 0;
        if ((param_1[0x52] == 0) || ((char)param_1[0x53] == '\0')) {
          if (param_1[0x1c] == 0) {
            func_0x000258109a30(0,"_AdoptPWDProtectionContextFromPrimaryScreenSession",0x133b,0);
            if ((_gLogCategory_AirPlayReceiverCore < 0x5b) &&
               ((_gLogCategory_AirPlayReceiverCore != -1 ||
                (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200005a),
                iVar9 != 0)))) {
              func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                  "void _AdoptPWDProtectionContextFromPrimaryScreenSession(AirPlayReceiverSessionRef)"
                                  ,0x200005a,
                                  "[%{ptr}] Auxiliary screen session: clientDeviceID is 0\n");
            }
          }
          else {
            _APReceiverSessionManagerCopyAirPlaySessionWithAttribute(uVar17,2,0,&local_e0);
            puVar2 = (ulong *)CONCAT44(uStack_dc,local_e0);
            if ((puVar2 == (ulong *)0x0) || (puVar2 == param_1)) {
              if ((_gLogCategory_AirPlayReceiverCore < 0x3d) &&
                 ((_gLogCategory_AirPlayReceiverCore != -1 ||
                  (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200003c),
                  iVar9 != 0)))) {
                func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                    "void _AdoptPWDProtectionContextFromPrimaryScreenSession(AirPlayReceiverSessionRef)"
                                    ,0x200003c,
                                    "[%{ptr}] Auxiliary screen session: no primary mirroring session (clientDeviceID=%llu)\n"
                                   );
              }
              if (puVar2 == (ulong *)0x0) goto LAB_2518d4a1c;
            }
            else if (puVar2[0x1c] == param_1[0x1c]) {
              if ((puVar2[0x52] == 0) || ((char)puVar2[0x53] == '\0')) {
                if ((_gLogCategory_AirPlayReceiverCore < 0x3d) &&
                   ((_gLogCategory_AirPlayReceiverCore != -1 ||
                    (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200003c),
                    iVar9 != 0)))) {
                  pcVar27 = 
                  "[%{ptr}] Auxiliary screen session: primary [%{ptr}] has not completed PWD key exchange\n"
                  ;
                  uVar10 = 0x200003c;
                  goto LAB_2518d49c4;
                }
              }
              else {
                uVar15 = func_0x0002580f6a60();
                param_1[0x52] = uVar15;
                *(undefined1 *)(param_1 + 0x53) = 1;
                *(int *)(param_1 + 0x51) = (int)puVar2[0x51];
                if ((_gLogCategory_AirPlayReceiverCore < 0x33) &&
                   ((_gLogCategory_AirPlayReceiverCore != -1 ||
                    (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032),
                    iVar9 != 0)))) {
                  pcVar27 = 
                  "[%{ptr}] Auxiliary screen session reusing PWD context [%{ptr}] from primary session [%{ptr}] (clientDeviceID=%llu, protectionBits=0x%x)\n"
                  ;
                  uVar10 = 0x2000032;
LAB_2518d49c4:
                  func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                      "void _AdoptPWDProtectionContextFromPrimaryScreenSession(AirPlayReceiverSessionRef)"
                                      ,uVar10,pcVar27);
                }
              }
            }
            else if ((_gLogCategory_AirPlayReceiverCore < 0x3d) &&
                    ((_gLogCategory_AirPlayReceiverCore != -1 ||
                     (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200003c),
                     iVar9 != 0)))) {
              func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                  "void _AdoptPWDProtectionContextFromPrimaryScreenSession(AirPlayReceiverSessionRef)"
                                  ,0x200003c,
                                  "[%{ptr}] Auxiliary screen session: primary [%{ptr}] clientDeviceID=%llu mismatch (ours=%llu)\n"
                                 );
            }
            func_0x0002580f5830(puVar2);
          }
        }
      }
      goto LAB_2518d4a1c;
    }
    uVar17 = 0x6de;
LAB_2518d7770:
    func_0x000258109a30(uVar15,"AirPlayReceiverSessionSetup",uVar17,0);
  }
  else {
    lVar38 = 0;
LAB_2518d4a1c:
    if ((*(char *)((long)param_1 + 0x192) == '\0') &&
       (iVar9 = func_0x000258101830(param_1[0x56],&cfstringStruct_276117d50), iVar9 == 0)) {
      local_110 = local_110 & 0xffffffff00000000;
      *(undefined1 *)((long)param_1 + 0x192) = 1;
      if (param_1[0x33] == 0) {
        iVar9 = func_0x000258101830(param_1[0x56],&cfstringStruct_2761132f0);
        if (iVar9 != 0) {
          uVar15 = _AirPlayReceiverServerPlatformCopyProperty
                             (param_1[5],extraout_x1,&cfstringStruct_2761136d0);
          param_1[0x33] = uVar15;
          uVar15 = local_110 & 0xffffffff;
          if ((int)local_110 == 0) goto LAB_2518d4a80;
          uVar35 = uVar15;
          if ((int)local_110 == -0x1a3e) {
            if (_gLogCategory_AirPlayReceiverCore < 0x5b) {
              if ((_gLogCategory_AirPlayReceiverCore != -1) ||
                 (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200005a),
                 iVar9 != 0)) {
                func_0x00025810a8d0(*(undefined8 *)(param_1[5] + 0xa0),0,
                                    _APReceiverSystemInfoCopyProperty,1,&cfstringStruct_276114610,0,
                                    0);
                func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                    "OSStatus _TimingInit(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                    ,0x200005a,
                                    "[%{ptr}] PTP clock was not enabled per receiver setting (enablePTPClock: %s)"
                                   );
              }
            }
            else {
              uVar35 = 0xffffe5c2;
            }
          }
          uVar17 = 0xb37;
LAB_2518d4f44:
          func_0x000258109a30(uVar35,"_TimingInit",uVar17,0);
          local_1c4 = (uint)uVar15;
          uVar17 = 0x6f5;
          goto LAB_2518d7770;
        }
LAB_2518d4a80:
        if ((_gLogCategory_AirPlayReceiverCore < 0x33) &&
           ((_gLogCategory_AirPlayReceiverCore != -1 ||
            (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032), iVar9 != 0))
           )) {
          func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                              "OSStatus _TimingInit(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                              ,0x2000032,
                              "[%{ptr}] timingProtocol = %@ | shouldRunTimingSetupAsync = %s");
        }
        if ((char)param_1[99] == '\0') {
          uVar35 = __TimingSetup(param_1,param_2,lVar14);
          if ((int)uVar35 != 0) {
            uVar17 = 0xb49;
            uVar15 = uVar35;
            goto LAB_2518d4f44;
          }
        }
        else {
          if (param_1[0x34] != 0) {
            func_0x00025802e5e0();
          }
          func_0x0002580f6a60(param_1);
          if (param_2 != 0) {
            func_0x0002580f6a60(param_2);
          }
          local_e0 = (undefined4)_DAT_2681b4ed0;
          uStack_dc = (uint)(_DAT_2681b4ed0 >> 0x20);
          uStack_d8 = (undefined4)DAT_251913160;
          uStack_d4 = (undefined2)((ulong)DAT_251913160 >> 0x20);
          uStack_d2 = (undefined2)((ulong)DAT_251913160 >> 0x30);
          uStack_d0 = 0x518dff3c;
          uStack_cc = 2;
          uStack_ca = 0;
          local_c8 = 0x693ddc08;
          uStack_c4 = 2;
          local_c0 = param_1;
          lStack_b8 = param_2;
          func_0x0002580f4bb0(&uStack_d0,param_1[4],&local_e0);
          iVar9 = func_0x000258101830(param_1[0x56],&cfstringStruct_2761132f0);
          if (iVar9 != 0) {
            func_0x00025810b100(lVar14,&cfstringStruct_276117cd0,1);
          }
        }
      }
      local_1c4 = 0;
    }
    func_0x00025810a6a0(param_2,&cfstringStruct_276112e70,auStack_178,0x20,&local_1c4);
    if (local_1c4 == 0) {
      func_0x00025810be60(param_1 + 9,auStack_178,0x20,0x20);
      local_1c4 = 0xffffe5b9;
    }
    iVar9 = func_0x00025810a660(param_2,&cfstringStruct_276112e70);
    if (iVar9 != 0) {
      uVar35 = param_1[0x23];
      uVar15 = func_0x000258102680(param_2,&cfstringStruct_276112e70);
      if (uVar15 != 0) {
        func_0x0002580f6a60(uVar15);
      }
      param_1[0x23] = uVar15;
      if (uVar35 != 0) {
        func_0x0002580f5830(uVar35);
      }
    }
    iVar9 = func_0x00025810a660(param_2,&cfstringStruct_276112e30);
    if (iVar9 != 0) {
      uVar35 = param_1[0x22];
      uVar15 = func_0x000258102680(param_2,&cfstringStruct_276112e30);
      if (uVar15 != 0) {
        func_0x0002580f6a60(uVar15);
      }
      param_1[0x22] = uVar15;
      if (uVar35 != 0) {
        func_0x0002580f5830(uVar35);
      }
    }
    iVar9 = func_0x00025810a660(param_2,&cfstringStruct_276112e50);
    if (iVar9 != 0) {
      uVar35 = param_1[0x21];
      uVar15 = func_0x000258102680(param_2,&cfstringStruct_276112e50);
      if (uVar15 != 0) {
        func_0x0002580f6a60(uVar15);
      }
      param_1[0x21] = uVar15;
      if (uVar35 != 0) {
        func_0x0002580f5830(uVar35);
      }
    }
    iVar9 = func_0x00025810a660(param_2,&cfstringStruct_2761111b0);
    if (iVar9 != 0) {
      uVar35 = param_1[0x1f];
      uVar15 = func_0x000258102680(param_2,&cfstringStruct_2761111b0);
      if (uVar15 != 0) {
        func_0x0002580f6a60(uVar15);
      }
      param_1[0x1f] = uVar15;
      if (uVar35 != 0) {
        func_0x0002580f5830(uVar35);
      }
    }
    iVar9 = func_0x00025810a660(param_2,&cfstringStruct_276119a90);
    if (iVar9 != 0) {
      uVar35 = param_1[0x20];
      uVar15 = func_0x000258102680(param_2,&cfstringStruct_276119a90);
      if (uVar15 != 0) {
        func_0x0002580f6a60(uVar15);
      }
      param_1[0x20] = uVar15;
      if (uVar35 != 0) {
        func_0x0002580f5830(uVar35);
      }
    }
    if ((cVar1 == '\0') && ((int)param_1[0x58] == 2)) {
      lVar16 = func_0x00025810a6f0(param_2,&cfstringStruct_276117cf0,0);
      *(bool *)(param_1 + 0x57) = lVar16 != 0;
      uVar10 = func_0x00025810a6f0(param_2,&cfstringStruct_276110b70,0);
      *(undefined4 *)(param_1 + 0x3f) = uVar10;
      if ((_gLogCategory_AirPlayReceiverCore < 0x33) &&
         ((_gLogCategory_AirPlayReceiverCore != -1 ||
          (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032), iVar9 != 0))))
      {
        func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                            "OSStatus AirPlayReceiverSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFDictionaryRef *)"
                            ,0x2000032,
                            "[%{ptr}] Multi-select: %d, sender perceived cluster type: %d\n");
      }
      if ((((((char)param_1[0x57] != '\0') && (iVar9 = func_0x000258109970(), iVar9 != 0)) &&
           ((int)param_1[0x3f] != 2)) && (_gLogCategory_AirPlayReceiverCore < 0x33)) &&
         ((_gLogCategory_AirPlayReceiverCore != -1 ||
          (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032), iVar9 != 0))))
      {
        func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                            "OSStatus AirPlayReceiverSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFDictionaryRef *)"
                            ,0x2000032,
                            "[%{ptr}] Group change: Sender does not perceive me in a HT cluster.\n")
        ;
      }
    }
    iVar9 = func_0x00025810a660(param_2,&cfstringStruct_276119ab0);
    if (iVar9 != 0) {
      uVar10 = func_0x00025810a700(param_2,&cfstringStruct_276119ab0,0,0xffffffff,0);
      *(undefined4 *)(param_1 + 0x5d) = uVar10;
      if ((_gLogCategory_AirPlayReceiverCore < 0x33) &&
         ((_gLogCategory_AirPlayReceiverCore != -1 ||
          (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032), iVar9 != 0))))
      {
        func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                            "OSStatus AirPlayReceiverSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFDictionaryRef *)"
                            ,0x2000032,"[%{ptr}] Sender display latency: %ums\n");
      }
    }
    uVar17 = func_0x000258106470();
    lVar16 = func_0x00025810a710(param_2,&cfstringStruct_276117df0,uVar17,&local_1c4);
    if (lVar16 != 0) {
      lVar18 = func_0x0002581017d0();
      uVar7 = DAT_251913248;
      uVar6 = DAT_251913220;
      uVar5 = DAT_251913210;
      uVar17 = DAT_251913160;
      if (0 < lVar18) {
        bVar4 = false;
        bVar3 = false;
        lVar37 = 0;
        puVar2 = param_1 + 0x4e;
        uVar28 = *_DAT_2680d3150;
        uVar33 = *_DAT_2680d3198;
        uVar29 = *_DAT_2680d3188;
        do {
          uVar19 = func_0x000258102670();
          lVar20 = func_0x00025810a5c0(lVar16,lVar37,uVar19,&local_1c4);
          uVar15 = (ulong)local_1c4;
          if (local_1c4 != 0) {
            uVar17 = 0x73f;
            goto LAB_2518d78d8;
          }
          iVar9 = func_0x00025810a6f0(lVar20,&cfstringStruct_276112330,0);
          if (_gLogCategory_AirPlayReceiverCore < 0x33) {
            if (_gLogCategory_AirPlayReceiverCore == -1) {
              iVar11 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032);
              if (iVar11 == 0) goto LAB_2518d51e0;
            }
            if ((_gLogCategory_AirPlayReceiverCore < 0x1f) &&
               (_gLogCategory_AirPlayReceiverCore == -1)) {
              func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x1e);
            }
            func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                "OSStatus AirPlayReceiverSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFDictionaryRef *)"
                                ,0x2000032,"[%{ptr}] Setting up stream (type %s/%u)%?@\n");
          }
LAB_2518d51e0:
          if (((int)param_1[0x58] == 1) && (iVar9 != 0x82)) {
            uVar17 = 0x749;
LAB_2518d779c:
            func_0x000258109a30(0,"AirPlayReceiverSessionSetup",uVar17,0);
            local_1c4 = 0xffffe5b1;
            goto LAB_2518d7608;
          }
          if (iVar9 < 0x6e) {
            if (iVar9 == 0x60) {
              iVar9 = func_0x00025810b820();
              if (iVar9 != 0) {
                func_0x000258109330();
                lVar38 = func_0x0002580f5640();
                uVar19 = func_0x000258109330();
                if (lVar38 - 1U < 0xfffffffffffffffe) {
                  iVar9 = func_0x0002580f5630();
                  if (iVar9 != 0) {
                    uVar15 = param_1[0x1d];
                    uStack_dc = (uint)param_1[0x1c];
                    uStack_d8 = (undefined4)(param_1[0x1c] >> 0x20);
                    uStack_d4 = 0x800;
                    uStack_d2 = (undefined2)uVar15;
                    uStack_d0 = (undefined4)(uVar15 >> 0x10);
                    uStack_cc = (undefined2)(uVar15 >> 0x30);
                    local_e0 = (int)uVar7;
                    func_0x0002580f5490(&MACH_HEADER,uVar19,1,lVar38,"Receiver Setup RTAS",
                                        "SenderDeviceID: %llu ReceiverDeviceID: %llu",&local_e0,0x16
                                       );
                  }
                }
              }
              local_1c4 = __GeneralAudioSetup(param_1,0x60,lVar20,lVar14);
              iVar9 = func_0x00025810b820();
              if (iVar9 != 0) {
                uVar19 = func_0x000258109330();
                if (lVar38 - 1U < 0xfffffffffffffffe) {
                  iVar9 = func_0x0002580f5630();
                  if (iVar9 != 0) {
                    uStack_dc = local_1c4;
                    local_e0 = (int)uVar5;
                    func_0x0002580f5490(&MACH_HEADER,uVar19,2,lVar38,"Receiver Setup RTAS",
                                        "Error: %d",&local_e0,8);
                  }
                }
              }
              uVar15 = (ulong)local_1c4;
              if (local_1c4 != 0) {
                uVar17 = 0x753;
                goto LAB_2518d78d8;
              }
              bVar3 = true;
            }
            else if (iVar9 == 0x67) {
              iVar9 = func_0x00025810b820();
              if (iVar9 != 0) {
                func_0x000258109330();
                lVar38 = func_0x0002580f5640();
                uVar19 = func_0x000258109330();
                if (lVar38 - 1U < 0xfffffffffffffffe) {
                  iVar9 = func_0x0002580f5630();
                  if (iVar9 != 0) {
                    uVar15 = param_1[0x1d];
                    uStack_dc = (uint)param_1[0x1c];
                    uStack_d8 = (undefined4)(param_1[0x1c] >> 0x20);
                    uStack_d4 = 0x800;
                    uStack_d2 = (undefined2)uVar15;
                    uStack_d0 = (undefined4)(uVar15 >> 0x10);
                    uStack_cc = (undefined2)(uVar15 >> 0x30);
                    local_e0 = (int)uVar7;
                    func_0x0002580f5490(&MACH_HEADER,uVar19,1,lVar38,"Receiver Setup BuffAS",
                                        "SenderDeviceID: %llu ReceiverDeviceID: %llu",&local_e0,0x16
                                       );
                  }
                }
              }
              local_1c4 = __GeneralAudioSetup(param_1,0x67,lVar20,lVar14);
              iVar9 = func_0x00025810b820();
              if (iVar9 != 0) {
                uVar19 = func_0x000258109330();
                if (lVar38 - 1U < 0xfffffffffffffffe) {
                  iVar9 = func_0x0002580f5630();
                  if (iVar9 != 0) {
                    uStack_dc = local_1c4;
                    local_e0 = (int)uVar5;
                    func_0x0002580f5490(&MACH_HEADER,uVar19,2,lVar38,"Receiver Setup BuffAS",
                                        "Error: %d",&local_e0,8);
                  }
                }
              }
              uVar15 = (ulong)local_1c4;
              if (local_1c4 != 0) {
                uVar17 = 0x75d;
                goto LAB_2518d78d8;
              }
              bVar4 = true;
            }
            else {
LAB_2518d5688:
              if (_gLogCategory_AirPlayReceiverCore < 0x33) {
                if (_gLogCategory_AirPlayReceiverCore == -1) {
                  iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032);
                  if (iVar9 == 0) goto LAB_2518d7298;
                }
                func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                    "OSStatus AirPlayReceiverSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFDictionaryRef *)"
                                    ,0x2000032,"### Unsupported stream type: %d\n");
              }
            }
          }
          else {
            if (iVar9 == 0x6e) {
              local_1c0 = 0;
              local_1b8 = 0;
              if (*puVar2 == 0) {
                uVar15 = __EnsureTimingSetupCompleted(param_1);
                if ((int)uVar15 == 0) {
                  lVar21 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
                  if (lVar21 == 0) {
                    func_0x000258109a30(0,"_ScreenSetup",0x11d8,0);
                    uVar15 = 0xffffe5b8;
                  }
                  else {
                    uVar35 = param_1[0x4b];
                    if (uVar35 == 0) {
                      uVar15 = _APReceiverScreenSinkCreateAirPlay(uVar28,&local_1b8);
                      if ((int)uVar15 != 0) {
                        func_0x000258109a30(uVar15,"_ScreenSetup",0x11e3,0);
                        goto LAB_2518d6e88;
                      }
LAB_2518d596c:
                      lVar23 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
                      if (lVar23 == 0) {
                        func_0x000258109a30(0,"_ScreenSetup",0x11e8,0);
                        uVar15 = 0xffffe5b8;
                        goto LAB_2518d6e88;
                      }
                      func_0x00025810b140(lVar23,&cfstringStruct_276111e30,0);
                      func_0x00025810b140(lVar23,&cfstringStruct_276111e50,
                                          *(undefined1 *)((long)param_1 + 0xb1));
                      func_0x00025810b140(lVar23,&cfstringStruct_276111ed0,
                                          *(undefined4 *)((long)param_1 + 0x234));
                      func_0x0002580f7000(lVar23,&cfstringStruct_276111ef0,param_1[0x33]);
                      uVar19 = uVar33;
                      if ((char)param_1[0x47] != '\0') {
                        uVar19 = uVar29;
                      }
                      func_0x0002580f7000(lVar23,&cfstringStruct_276111e90,uVar19);
                      uVar19 = uVar29;
                      if ((char)param_1[0x30] != '\0') {
                        uVar19 = uVar33;
                      }
                      func_0x0002580f7000(lVar23,&cfstringStruct_276111e70,uVar19);
                      func_0x0002580f7000(lVar23,&cfstringStruct_276111f70,param_1);
                      if (param_1[0x10] != 0) {
                        _APReceiverStatsCollectorSetScreenOptions(param_1[0x10],lVar20);
                        _APReceiverStatsCollectorSetIfName(param_1[0x10],param_1 + 0xd);
                        func_0x0002580f7000(lVar23,&cfstringStruct_276111f10,param_1[0x10]);
                      }
                      lVar24 = local_1b8;
                      uVar15 = _APReceiverScreenSessionCreate(uVar28,local_1b8,lVar23,puVar2);
                      if ((int)uVar15 == 0) {
                        *(undefined1 *)(param_1 + 0x32) = 1;
                        *(undefined2 *)(param_1 + 0x50) = 0;
                        uVar15 = param_1[0x4e];
                        lVar36 = func_0x000258109150(uVar15);
                        puVar34 = (undefined8 *)(*(long *)(lVar36 + 0x10) + 0x18);
                        pcVar32 = (code *)*puVar34;
                        if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                          uVar15 = 0xffffce12;
LAB_2518d5c08:
                          uVar19 = 0x1220;
                          goto LAB_2518d7238;
                        }
                        uVar15 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x94e8000000000000,
                                            uVar15,__ScreenHandleEvent,param_1);
                        if ((int)uVar15 != 0) goto LAB_2518d5c08;
                        lVar36 = func_0x00025810a6f0(lVar20,&cfstringStruct_276119dd0,0);
                        if (lVar36 != 0) {
                          uVar15 = param_1[0x3e];
                          if (uVar15 == 0) {
LAB_2518d5c1c:
                            func_0x0002581096f0(param_1 + 0x2c,0x10,lVar36,&local_128,local_138);
                            uVar15 = *puVar2;
                            lVar36 = func_0x000258109150(uVar15);
                            puVar34 = (undefined8 *)(*(long *)(lVar36 + 0x10) + 0x28);
                            pcVar32 = (code *)*puVar34;
                            if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                              uVar15 = 0xffffce12;
                            }
                            else {
                              uVar15 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff |
                                                  0x36b4000000000000,uVar15,&local_128,local_138);
                            }
                            lVar36 = -0x10;
                            ppuVar30 = &local_128;
                            do {
                              *(undefined1 *)ppuVar30 = 0;
                              bVar8 = lVar36 != -1;
                              lVar36 = lVar36 + 1;
                              ppuVar30 = (ulong **)((long)ppuVar30 + 1);
                            } while (bVar8);
                            lVar36 = -0x10;
                            plVar31 = local_138;
                            do {
                              *(undefined1 *)plVar31 = 0;
                              bVar8 = lVar36 != -1;
                              lVar36 = lVar36 + 1;
                              plVar31 = (long *)((long)plVar31 + 1);
                            } while (bVar8);
                            if ((int)uVar15 != 0) {
                              uVar19 = 0x1234;
                              goto LAB_2518d7238;
                            }
                          }
                          else {
                            lVar22 = func_0x000258109150(uVar15);
                            puVar34 = (undefined8 *)(*(long *)(lVar22 + 0x10) + 0x20);
                            pcVar32 = (code *)*puVar34;
                            if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0))
                            goto LAB_2518d5c1c;
                            iVar9 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0xb441000000000000,
                                               uVar15);
                            if (iVar9 == 0) goto LAB_2518d5c1c;
                            uVar15 = __GetDataStreamSecurityKeys(param_1,lVar36,0,0,&local_158);
                            if ((int)uVar15 != 0) {
                              uVar19 = 0x1229;
                              goto LAB_2518d7238;
                            }
                            uVar15 = *puVar2;
                            lVar36 = func_0x000258109150(uVar15);
                            puVar34 = (undefined8 *)(*(long *)(lVar36 + 0x10) + 0x20);
                            pcVar32 = (code *)*puVar34;
                            if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                              uVar15 = 0xffffce12;
LAB_2518d6284:
                              uVar19 = 0x122b;
                              goto LAB_2518d7238;
                            }
                            uVar15 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x4a0000000000000,
                                                uVar15,&local_158,0x20);
                            if ((int)uVar15 != 0) goto LAB_2518d6284;
                          }
                          uVar15 = *puVar2;
                          lVar36 = func_0x000258109150(uVar15);
                          puVar34 = (undefined8 *)(*(long *)(lVar36 + 8) + 0x30);
                          pcVar32 = (code *)*puVar34;
                          if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                            uVar15 = 0xffffce12;
                          }
                          else {
                            uVar15 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x9725000000000000
                                                ,uVar15,&cfstringStruct_276111e30,0,&local_1c0);
                            if ((int)uVar15 == 0) {
                              func_0x00025810a790(lVar21,&cfstringStruct_276112330,0x6e);
                              func_0x0002580f7000(lVar21,&cfstringStruct_276117f90,local_1c0);
                              uVar15 = __AddResponseStream(lVar14,lVar21);
                              if ((int)uVar15 != 0) {
                                uVar19 = 0x123e;
                                goto LAB_2518d7238;
                              }
                              if (_gLogCategory_AirPlayReceiverCore < 0x33) {
                                if (_gLogCategory_AirPlayReceiverCore == -1) {
                                  iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,
                                                              0x2000032);
                                  if (iVar9 == 0) goto LAB_2518d62c0;
                                }
                                func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                                                                                        
                                                  "OSStatus _ScreenSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                                  ,0x2000032,
                                                  "[%{ptr}] screen session [%{ptr}] set up on port %@\n"
                                                  );
                              }
LAB_2518d62c0:
                              __UpdateActiveSessionRegistration(param_1,0,2);
                              if ((lVar20 != 0) && (param_1[0x4c] != 0)) {
                                lVar36 = func_0x000258102680(lVar20,&cfstringStruct_27611a190);
                                if (lVar36 != 0) {
                                  uVar15 = param_1[0x4c];
                                  lVar22 = func_0x000258109150(uVar15);
                                  puVar34 = (undefined8 *)(*(long *)(lVar22 + 8) + 0x38);
                                  pcVar32 = (code *)*puVar34;
                                  if ((pcVar32 != (code *)0x0) && (pcVar32 != (code *)0x0)) {
                                    (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x2724000000000000,
                                               uVar15,&cfstringStruct_276116db0,lVar36);
                                  }
                                }
                                lVar20 = func_0x000258102680(lVar20,&cfstringStruct_276116dd0);
                                if (lVar20 != 0) {
                                  uVar15 = param_1[0x4c];
                                  lVar36 = func_0x000258109150(uVar15);
                                  puVar34 = (undefined8 *)(*(long *)(lVar36 + 8) + 0x38);
                                  pcVar32 = (code *)*puVar34;
                                  if ((pcVar32 != (code *)0x0) && (pcVar32 != (code *)0x0)) {
                                    (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x2724000000000000,
                                               uVar15,&cfstringStruct_276116dd0,lVar20);
                                  }
                                }
                              }
                              if ((*(char *)((long)param_1 + 0x1ba) != '\0') &&
                                 (local_180 = 0, (char)param_1[0x50] == '\0')) {
                                lStack_b8 = *(long *)(param_1[5] + 0xa0);
                                local_c0 = &local_110;
                                local_110 = 0;
                                local_100 = (undefined4)uVar6;
                                uStack_fc = (undefined4)((ulong)uVar6 >> 0x20);
                                local_f8 = 0x51914ae1;
                                uStack_f4 = 2;
                                local_f0 = (ulong *)0x0;
                                uStack_e8 = 0;
                                local_e0 = (undefined4)_DAT_2681b4ed0;
                                uStack_dc = (uint)(_DAT_2681b4ed0 >> 0x20);
                                uStack_d8 = (undefined4)uVar17;
                                uVar10 = uStack_d8;
                                uStack_d4 = (undefined2)((ulong)uVar17 >> 0x20);
                                uStack_d2 = (undefined2)((ulong)uVar17 >> 0x30);
                                uStack_d0 = 0x5187734c;
                                uStack_cc = 2;
                                uStack_ca = 0;
                                local_c8 = 0x693dd9c0;
                                uStack_c4 = 2;
                                local_b0 = CONCAT44(local_b0._4_4_,(int)param_1[0x4d]);
                                uStack_108 = local_c0;
                                func_0x0002580f54f0(*(undefined8 *)(lStack_b8 + 600),&local_e0);
                                uVar35 = uStack_108[4];
                                uVar40 = uStack_108[5];
                                func_0x0002580f4ba0(&local_110,8);
                                if (_gLogCategory_AirPlayReceiverCore < 0x33) {
                                  if (_gLogCategory_AirPlayReceiverCore == -1) {
                                    iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,
                                                                0x2000032);
                                    if (iVar9 == 0) goto LAB_2518d64dc;
                                  }
                                  func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                                                                                            
                                                  "OSStatus _ScreenStart(AirPlayReceiverSessionRef)"
                                                  ,0x2000032,
                                                  "[%{ptr}] screen session [%{ptr}] using display size %f x %f\n"
                                                  );
                                }
LAB_2518d64dc:
                                if (param_1[0x4c] == 0) {
                                  local_180 = 0;
LAB_2518d6f80:
                                  lVar20 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
                                  if (lVar20 == 0) {
                                    func_0x000258109a30(0,"_ScreenStart",0x129e,0);
                                    uVar15 = 0xffffe5b8;
                                  }
                                  else {
                                    if (local_180 != 0) {
                                      lVar36 = func_0x000258102680(local_180,
                                                                   &cfstringStruct_276116810);
                                      if (lVar36 != 0) {
                                        func_0x0002580f7000(lVar20,&cfstringStruct_276111010,lVar36)
                                        ;
                                      }
                                      lVar36 = func_0x000258102680(local_180,
                                                                   &cfstringStruct_276116310);
                                      if (lVar36 != 0) {
                                        func_0x0002580f7000(lVar20,&cfstringStruct_276111fd0,lVar36)
                                        ;
                                      }
                                    }
                                    func_0x00025810b110(uVar35,uVar40,lVar20,
                                                        &cfstringStruct_276111f90);
                                    uVar15 = *puVar2;
                                    lVar36 = func_0x000258109150(uVar15);
                                    puVar34 = (undefined8 *)(*(long *)(lVar36 + 0x10) + 8);
                                    pcVar32 = (code *)*puVar34;
                                    if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                                      uVar15 = 0xffffce12;
                                    }
                                    else {
                                      uVar15 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff |
                                                          0x603d000000000000,uVar15,lVar20);
                                      if ((int)uVar15 == 0) {
                                        *(undefined1 *)(param_1 + 0x50) = 1;
                                        uVar15 = param_1[0x67];
                                        param_1[0x67] = (ulong)&cfstringStruct_27611a070;
                                        func_0x0002580f6a60();
                                        if (uVar15 != 0) {
                                          func_0x0002580f5830(uVar15);
                                        }
                                        if ((param_1[0x52] != 0) && ((char)param_1[0x53] != '\0')) {
                                          uVar15 = param_1[0x54];
                                          if (uVar15 == 0) {
                                            uVar15 = func_0x0002580f6ca0(_DAT_2681b4e38,0,0,
                                                                         param_1[2]);
                                            param_1[0x54] = uVar15;
                                            local_1b0 = _DAT_2681b4ed0;
                                            uStack_1a4 = (undefined4)((ulong)uVar17 >> 0x20);
                                            local_1a0 = 0x518e0820;
                                            uStack_19c = 2;
                                            uStack_198 = 0x693dd998;
                                            uStack_194 = 2;
                                            uStack_1a8 = uVar10;
                                            local_190 = param_1;
                                            func_0x0002580f6cb0(uVar15,&local_1b0);
                                            func_0x0002580f6cc0(param_1[0x54],0xffffffffffffffff,0,0
                                                               );
                                            func_0x000258102360(param_1[0x54]);
                                            uVar15 = param_1[0x54];
                                          }
                                          uVar19 = func_0x0002580f5500(0,10000000000);
                                          func_0x0002580f6cc0(uVar15,uVar19,10000000000,1000000000);
                                        }
                                        uVar15 = 0;
                                        goto LAB_2518d7190;
                                      }
                                    }
                                    func_0x000258109a30(uVar15,"_ScreenStart",0x12a9,0);
                                  }
                                }
                                else {
                                  if (*(char *)((long)param_1 + 0x281) != '\0') goto LAB_2518d6f80;
                                  lVar20 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
                                  func_0x00025810a7a0(lVar20,&cfstringStruct_2761122f0,4,
                                                      param_1 + 0x1c);
                                  if ((param_1[0x52] != 0) && ((char)param_1[0x53] != '\0')) {
                                    func_0x0002580f7000(lVar20,&cfstringStruct_276116890,uVar33);
                                  }
                                  uVar15 = param_1[0x4c];
                                  lVar36 = func_0x000258109150(uVar15);
                                  puVar34 = (undefined8 *)(*(long *)(lVar36 + 0x10) + 0x20);
                                  pcVar32 = (code *)*puVar34;
                                  if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                                    uVar15 = 0xffffce12;
LAB_2518d65dc:
                                    func_0x000258109a30(uVar15,"_ScreenStartPresentation",0x119a,0);
                                  }
                                  else {
                                    uVar15 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff |
                                                        0x2bcd000000000000,uVar15,lVar20,&local_180)
                                    ;
                                    if ((int)uVar15 != 0) goto LAB_2518d65dc;
                                    *(undefined1 *)((long)param_1 + 0x281) = 1;
                                    uVar13 = func_0x00025810a6f0(local_180,&cfstringStruct_276112310
                                                                 ,0);
                                    *(undefined4 *)((long)param_1 + 0x284) = uVar13;
                                  }
                                  if (lVar20 != 0) {
                                    func_0x0002580f5830(lVar20);
                                  }
                                  if ((int)uVar15 == 0) goto LAB_2518d6f80;
                                  if (_gLogCategory_AirPlayReceiverCore < 0x3d) {
                                    if (_gLogCategory_AirPlayReceiverCore == -1) {
                                      iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore
                                                                  ,0x200003c);
                                      if (iVar9 == 0) goto LAB_2518d69e4;
                                    }
                                    func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                                                                                                
                                                  "OSStatus _ScreenStartPresentation(AirPlayReceiverSessionRef, CFDictionaryRef *)"
                                                  ,0x200003c,
                                                  "[%{ptr}] start UI presentation failed: %#m\n");
                                  }
LAB_2518d69e4:
                                  func_0x000258109a30(uVar15,"_ScreenStart",0x129b,0);
                                  lVar20 = 0;
                                }
LAB_2518d7190:
                                if (local_180 != 0) {
                                  func_0x0002580f5830();
                                }
                                if (lVar20 != 0) {
                                  func_0x0002580f5830(lVar20);
                                }
                                if ((int)uVar15 != 0) {
                                  if (_gLogCategory_AirPlayReceiverCore < 0x3d) {
                                    if (_gLogCategory_AirPlayReceiverCore == -1) {
                                      iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore
                                                                  ,0x200003c);
                                      if (iVar9 == 0) goto LAB_2518d7220;
                                    }
                                    func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                                                                                                
                                                  "OSStatus _ScreenStart(AirPlayReceiverSessionRef)"
                                                  ,0x200003c,
                                                  "[%{ptr}] screen session [%{ptr}] screen start failed: %#m\n"
                                                  );
                                  }
LAB_2518d7220:
                                  __ScreenTearDown(param_1);
                                  uVar19 = 0x1254;
                                  goto LAB_2518d7238;
                                }
                              }
                              uVar15 = 0;
                              goto LAB_2518d7240;
                            }
                          }
                          uVar19 = 0x1238;
                          goto LAB_2518d7238;
                        }
                        func_0x000258109a30(0,"_ScreenSetup",0x1224,0);
                        uVar15 = 0xffffe5c5;
                      }
                      else {
                        uVar19 = 0x1219;
LAB_2518d7238:
                        func_0x000258109a30(uVar15,"_ScreenSetup",uVar19,0);
                      }
LAB_2518d7240:
                      func_0x0002580f5830(lVar21);
                      func_0x0002580f5830(lVar23);
                    }
                    else {
                      local_e0 = 0;
                      uStack_dc = 0;
                      lVar23 = func_0x0002580f6a50(uVar35);
                      lVar24 = func_0x00025810b4b0();
                      if (lVar23 == lVar24) {
                        if (_gLogCategory_APReceiverScreenSinkSBufConsumer < 0x1f) {
                          if (_gLogCategory_APReceiverScreenSinkSBufConsumer == -1) {
                            iVar9 = func_0x000258101e40(&
                                                  _gLogCategory_APReceiverScreenSinkSBufConsumer,
                                                  0x200001e);
                            if (iVar9 == 0) goto LAB_2518d5840;
                          }
                          func_0x000258101eb0(&_gLogCategory_APReceiverScreenSinkSBufConsumer,
                                              "OSStatus APReceiverScreenSinkCreateSBufConsumer(CFAllocatorRef, APReceiverSBufConsumerRef, APReceiverScreenSinkRef *)"
                                              ,0x200001e,"Creating SBufConsumer screen sink\n");
                        }
LAB_2518d5840:
                        if (_APReceiverScreenSinkGetClassID_once != -1) {
                          func_0x0002580f48c0(&_APReceiverScreenSinkGetClassID_once,
                                              &___block_literal_global_6248);
                        }
                        uVar15 = func_0x00025810acc0(uVar28,&_kAPRScreenSinkSBufConsumerVTable,
                                                     _APReceiverScreenSinkGetClassID_classID,
                                                     &local_e0);
                        if ((int)uVar15 == 0) {
                          lVar23 = func_0x00025810ac50(CONCAT44(uStack_dc,local_e0));
                          uVar19 = func_0x0002580f6a60(uVar35);
                          *(undefined8 *)(lVar23 + 8) = uVar19;
                          if (_gLogCategory_APReceiverScreenSinkSBufConsumer < 0x1f) {
                            if (_gLogCategory_APReceiverScreenSinkSBufConsumer == -1) {
                              iVar9 = func_0x000258101e40(&
                                                  _gLogCategory_APReceiverScreenSinkSBufConsumer,
                                                  0x200001e);
                              if (iVar9 == 0) goto LAB_2518d58f0;
                            }
                            func_0x000258101eb0(&_gLogCategory_APReceiverScreenSinkSBufConsumer,
                                                "OSStatus APReceiverScreenSinkCreateSBufConsumer(CFAllocatorRef, APReceiverSBufConsumerRef, APReceiverScreenSinkRef *)"
                                                ,0x200001e,
                                                "Created SBufConsumer screen sink %{ptr}\n");
                          }
LAB_2518d58f0:
                          lVar23 = CONCAT44(uStack_dc,local_e0);
                          uVar15 = param_1[0x52];
                          local_1b8 = lVar23;
                          if ((uVar15 != 0) && ((char)param_1[0x53] != '\0')) {
                            lVar24 = func_0x000258109150(lVar23);
                            puVar34 = (undefined8 *)(*(long *)(lVar24 + 8) + 0x38);
                            pcVar32 = (code *)*puVar34;
                            if ((pcVar32 != (code *)0x0) && (pcVar32 != (code *)0x0)) {
                              (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x2724000000000000,lVar23
                                         ,&cfstringStruct_276119830,uVar15);
                            }
                          }
                          goto LAB_2518d596c;
                        }
                        func_0x000258109a30(uVar15,"APReceiverScreenSinkCreateSBufConsumer",0x1d9,0)
                        ;
                        if (CONCAT44(uStack_dc,local_e0) != 0) {
                          func_0x0002580f5830();
                        }
                      }
                      else {
                        func_0x000258109a30(0,"APReceiverScreenSinkCreateSBufConsumer",0x1d3,0);
                        uVar15 = 0xfffee63d;
                      }
                      func_0x000258109a30(uVar15,"_ScreenSetup",0x11dc,0);
LAB_2518d6e88:
                      func_0x0002580f5830(lVar21);
                      lVar24 = local_1b8;
                    }
                    if (lVar24 != 0) {
                      func_0x0002580f5830(lVar24);
                    }
                  }
                  if (local_1c0 != 0) {
                    func_0x0002580f5830();
                  }
                  if ((int)uVar15 != 0) {
                    __ScreenTearDown(param_1);
                  }
                }
                else if (_gLogCategory_AirPlayReceiverCore < 0x5b) {
                  if (_gLogCategory_AirPlayReceiverCore == -1) {
                    iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200005a);
                    if (iVar9 == 0) goto LAB_2518d727c;
                  }
                  func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                      "OSStatus _ScreenSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                      ,0x200005a,
                                      "[%{ptr}] Screen setup failed due to async %@ clock err: %#m\n"
                                     );
                }
              }
              else {
                func_0x000258109a30(0,"_ScreenSetup",0x11d1,0);
                uVar15 = 0xffffe5c1;
              }
LAB_2518d727c:
              lVar20 = -0x20;
              plVar31 = &local_158;
              do {
                *(undefined1 *)plVar31 = 0;
                bVar8 = lVar20 != -1;
                lVar20 = lVar20 + 1;
                plVar31 = (long *)((long)plVar31 + 1);
              } while (bVar8);
              if ((uint)uVar15 == 0) {
                local_1c4 = 0;
                goto LAB_2518d7298;
              }
              if (_gLogCategory_AirPlayReceiverCore < 0x3d) {
                if (_gLogCategory_AirPlayReceiverCore == -1) {
                  iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200003c);
                  if (iVar9 == 0) goto LAB_2518d775c;
                }
                func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                    "OSStatus _ScreenSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                    ,0x200003c,"[%{ptr}] screen session setup failed: %#m\n");
              }
LAB_2518d775c:
              uVar17 = 0x765;
              local_1c4 = (uint)uVar15;
              goto LAB_2518d7770;
            }
            if (iVar9 != 0x78) {
              if (iVar9 != 0x82) goto LAB_2518d5688;
              lVar21 = func_0x000258102680(lVar20,&cfstringStruct_276119ad0);
              if (lVar21 != 0) {
                iVar9 = func_0x000258101830(lVar21,&cfstringStruct_276119af0);
                if (iVar9 != 0) {
                  if ((int)param_1[0x58] != 2) {
                    uVar17 = 0x777;
                    goto LAB_2518d779c;
                  }
                  if (lVar20 == 0) {
                    func_0x000258109a30(0,"_PlaybackV2Setup",0x1764,0);
                    uVar15 = 0xffffe5cf;
LAB_2518d78c4:
                    local_1c4 = (uint)uVar15;
                  }
                  else {
                    uVar15 = param_1[0x59];
                    param_1[0x59] = uVar15 + 1;
                    lVar21 = func_0x00025810a800(uVar15 + 1);
                    if (lVar21 == 0) {
                      func_0x000258109a30(0,"_PlaybackV2Setup",0x1769,0);
                      uVar15 = 0xffffe5b8;
                      goto LAB_2518d78c4;
                    }
                    lVar20 = func_0x000258102680(lVar20,&cfstringStruct_276116a70);
                    if (lVar20 == 0) {
                      func_0x000258109a30(0,"_PlaybackV2Setup",0x176c,0);
                      uVar15 = 0xffffe5cf;
LAB_2518d78bc:
                      func_0x0002580f5830(lVar21);
                      goto LAB_2518d78c4;
                    }
                    if (_gLogCategory_AirPlayReceiverCore < 0x33) {
                      if (_gLogCategory_AirPlayReceiverCore == -1) {
                        iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032);
                        if (iVar9 != 0) goto LAB_2518d5290;
                      }
                      else {
LAB_2518d5290:
                        func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                            "OSStatus _PlaybackV2Setup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                            ,0x2000032,
                                            "[%{ptr}] Set up RCS-%@ for Playback V2, streamID = %llu\n"
                                           );
                      }
                      if (_gLogCategory_AirPlayReceiverCore < 0x33) {
                        if (_gLogCategory_AirPlayReceiverCore == -1) {
                          iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032);
                          if (iVar9 == 0) goto LAB_2518d5ff8;
                        }
                        func_0x00025810a7d0(lVar21,0);
                        func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                            "OSStatus _PlaybackV2Start(AirPlayReceiverSessionRef, CFNumberRef)"
                                            ,0x2000032,
                                            "[%{ptr}] Starting video playback, streamID %llu\n");
                      }
                    }
LAB_2518d5ff8:
                    if (param_1[0x4c] == 0) {
                      func_0x000258109a30(0,"_PlaybackV2Start",0x1749,0);
                      uVar15 = 0xffffe5b1;
LAB_2518d7888:
                      func_0x000258109a30(uVar15,"_PlaybackV2Setup",0x1771,0);
                      goto LAB_2518d78bc;
                    }
                    lVar23 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
                    func_0x00025810a7a0(lVar23,&cfstringStruct_2761122f0,4,param_1 + 0x1c);
                    func_0x0002580f7000(lVar23,&cfstringStruct_276112310,lVar21);
                    if (param_1[0x33] != 0) {
                      func_0x0002580f7000(lVar23,&cfstringStruct_276116870);
                    }
                    uVar15 = param_1[0x4c];
                    lVar24 = func_0x000258109150(uVar15);
                    puVar34 = (undefined8 *)(*(long *)(lVar24 + 0x10) + 0x30);
                    pcVar32 = (code *)*puVar34;
                    if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                      uVar15 = 0xffffce12;
LAB_2518d61b4:
                      func_0x000258109a30(uVar15,"_PlaybackV2Start",0x1752,0);
                    }
                    else {
                      uVar15 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x3b04000000000000,
                                          uVar15,__PlaybackV2EventCallback,
                                          __PlaybackV2TLSInfoRequestCallback,param_1,lVar23);
                      if ((int)uVar15 != 0) goto LAB_2518d61b4;
                    }
                    if (lVar23 != 0) {
                      func_0x0002580f5830(lVar23);
                    }
                    if ((int)uVar15 != 0) goto LAB_2518d7888;
                    lVar23 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
                    if (lVar23 == 0) {
                      func_0x000258109a30(0,"_PlaybackV2Setup",0x1774,0);
                      uVar15 = 0xffffe5b8;
                      goto LAB_2518d78bc;
                    }
                    func_0x00025810a790(lVar23,&cfstringStruct_276112330,0x82);
                    func_0x0002580f7000(lVar23,&cfstringStruct_276119b10,lVar21);
                    uVar15 = __AddResponseStream(lVar14,lVar23);
                    uVar12 = (uint)uVar15;
                    if (uVar12 == 0) {
                      func_0x0002580f7000(param_1[0x5f],lVar21,lVar20);
                      func_0x00025810aa20(param_1[0x60],lVar21);
                      lVar20 = func_0x00025810aa00(param_1[0x60]);
                      if (lVar20 == 1) {
                        __UpdateActiveSessionRegistration(param_1,0,1);
                      }
                    }
                    else {
                      func_0x000258109a30(uVar15,"_PlaybackV2Setup",0x177a,0);
                    }
                    func_0x0002580f5830(lVar21);
                    func_0x0002580f5830(lVar23);
                    local_1c4 = uVar12;
                    if (uVar12 == 0) goto LAB_2518d7298;
                  }
                  uVar17 = 0x77c;
                  goto LAB_2518d78d8;
                }
                local_1c0 = local_1c0 & 0xffffffff00000000;
                local_180 = 0;
                local_1b8 = 0;
                local_128 = (ulong *)0x0;
                pcStack_120 = (code *)0x0;
                local_118 = (code *)0x0;
                if (lVar20 == 0) {
                  lVar21 = 0;
                  lVar23 = 0;
                  uVar10 = 0xffffe5cf;
                  uVar19 = 0x17e2;
LAB_2518d6f10:
                  func_0x000258109a30(0,"_RemoteControlSessionSetup",uVar19,0);
                  lVar36 = 0;
                  lVar20 = 0;
                  local_1c0 = CONCAT44(local_1c0._4_4_,uVar10);
LAB_2518d6c9c:
                  __RemoteControlTearDownSession(param_1,lVar21);
                }
                else {
                  uVar15 = param_1[0x59];
                  param_1[0x59] = uVar15 + 1;
                  lVar21 = func_0x00025810a800(uVar15 + 1);
                  if (lVar21 == 0) {
                    lVar23 = 0;
                    uVar10 = 0xffffe5b8;
                    uVar19 = 0x17e9;
                    goto LAB_2518d6f10;
                  }
                  lVar23 = func_0x000258101820(uVar28,0,_DAT_2680d3340,_DAT_2680d3358);
                  if (lVar23 == 0) {
                    lVar23 = 0;
                    uVar10 = 0xffffe5b8;
                    uVar19 = 0x17ec;
                    goto LAB_2518d6f10;
                  }
                  func_0x00025810a790(lVar23,&cfstringStruct_276112330,0x82);
                  func_0x0002580f7000(lVar23,&cfstringStruct_276119b10,lVar21);
                  lVar24 = func_0x000258102680(lVar20,&cfstringStruct_276119ad0);
                  if (_gLogCategory_AirPlayReceiverCore < 0x33) {
                    if (_gLogCategory_AirPlayReceiverCore == -1) {
                      iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032);
                      if (iVar9 == 0) goto LAB_2518d5e60;
                    }
                    func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                        "OSStatus _RemoteControlSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                        ,0x2000032,
                                        "clientTypeUUID in remote control sesssion setup: %@\n");
                  }
LAB_2518d5e60:
                  if (lVar24 == 0) {
                    uVar10 = 0xffffe5cf;
                    uVar19 = 0x17f4;
                    goto LAB_2518d6f10;
                  }
                  iVar9 = func_0x000258101830(lVar24,&cfstringStruct_276115790);
                  if (iVar9 == 0) {
                    iVar9 = func_0x000258101830(lVar24,&cfstringStruct_2761168d0);
                    if (iVar9 != 0) goto LAB_2518d5e8c;
                    local_1c0 = CONCAT44(local_1c0._4_4_,0xffffe5b1);
                    if (0x5a < _gLogCategory_AirPlayReceiverCore) {
                      lVar36 = 0;
                      lVar20 = 0;
                      goto LAB_2518d6c9c;
                    }
                    if (_gLogCategory_AirPlayReceiverCore == -1) {
                      iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200005a);
                      if (iVar9 != 0) goto LAB_2518d61f0;
                    }
                    else {
LAB_2518d61f0:
                      func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                          "OSStatus _RemoteControlSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                          ,0x200005a,"[%{ptr}] Unsupported client type: %@\n");
                    }
                    lVar20 = 0;
                    lVar36 = 0;
LAB_2518d6c94:
                    if ((uint)local_1c0 == 0) goto LAB_2518d6ca8;
                    goto LAB_2518d6c9c;
                  }
LAB_2518d5e8c:
                  uVar19 = func_0x000258102680(lVar20,&cfstringStruct_276116a70);
                  func_0x000258102680(lVar20,&cfstringStruct_27611a230);
                  uVar15 = func_0x00025810a6f0(lVar20,&cfstringStruct_27611a250,0);
                  if ((uVar15 & 0xfffffffd) != 0) {
                    local_1c0 = CONCAT44(local_1c0._4_4_,0xffffe5b1);
                    if (_gLogCategory_AirPlayReceiverCore < 0x5b) {
                      if (_gLogCategory_AirPlayReceiverCore == -1) {
                        iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200005a);
                        if (iVar9 != 0) goto LAB_2518d5f04;
                      }
                      else {
LAB_2518d5f04:
                        func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                            "OSStatus _RemoteControlSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                            ,0x200005a,"[%{ptr}] Unsupported control type: %d\n");
                      }
                      lVar20 = 0;
                      lVar36 = 0;
                      goto LAB_2518d6c94;
                    }
                    lVar36 = 0;
                    lVar20 = 0;
                    goto LAB_2518d6c9c;
                  }
                  local_118 = __HandleRemoteControlSessionFailed;
                  local_128 = param_1;
                  lVar22 = func_0x00025810a6f0(lVar20,&cfstringStruct_27611a270,0);
                  if (lVar22 != 0) {
                    uStack_d8 = 0;
                    uStack_d4 = 0;
                    uStack_d2 = 0;
                    local_e0 = 0;
                    uStack_dc = 0;
                    local_c8 = 0;
                    uStack_c4 = 0;
                    uStack_d0 = 0;
                    uStack_cc = 0;
                    uStack_ca = 0;
                    uStack_108._0_4_ = 0;
                    uStack_108._4_4_ = 0;
                    local_110 = 0;
                    local_f8 = 0;
                    uStack_f4 = 0;
                    local_100 = 0;
                    uStack_fc = 0;
                    if ((_gLogCategory_AirPlayReceiverCore < 0x33) &&
                       ((_gLogCategory_AirPlayReceiverCore != -1 ||
                        (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032),
                        iVar9 != 0)))) {
                      func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                          "OSStatus _RemoteControlSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                          ,0x2000032,
                                          "[%{ptr}] Sender wants a dedicated socket for RCS-%@\n");
                    }
                    uVar25 = func_0x00025810a6f0(lVar20,&cfstringStruct_27611a290,&local_1c0);
                    uVar15 = local_1c0 & 0xffffffff;
                    if ((uint)local_1c0 == 0) {
                      uVar15 = __GetDataStreamSecurityKeys(param_1,uVar25,0x20,&local_110,&local_e0)
                      ;
                      local_1c0 = CONCAT44(local_1c0._4_4_,(int)uVar15);
                      if ((int)uVar15 != 0) {
                        uVar19 = 0x1819;
                        goto LAB_2518d72c8;
                      }
                      lVar20 = func_0x0002580f6ff0(uVar28,&local_e0,0x20);
                      if (lVar20 == 0) {
                        func_0x000258109a30(0,"_RemoteControlSessionSetup",0x181c,0);
                        lVar20 = 0;
                      }
                      else {
                        lVar36 = func_0x0002580f6ff0(uVar28,&local_110,0x20);
                        if (lVar36 != 0) goto LAB_2518d66ec;
                        func_0x000258109a30(0,"_RemoteControlSessionSetup",0x181f,0);
                      }
                      local_1c0 = CONCAT44(local_1c0._4_4_,0xffffe5b8);
                    }
                    else {
                      uVar19 = 0x1816;
LAB_2518d72c8:
                      func_0x000258109a30(uVar15,"_RemoteControlSessionSetup",uVar19,0);
                      lVar20 = 0;
                    }
                    lVar36 = 0;
                    goto LAB_2518d6c94;
                  }
                  lVar20 = 0;
                  lVar36 = 0;
                  pcStack_120 = __SendRemoteControlSessionOutgoingMessage;
LAB_2518d66ec:
                  iVar9 = func_0x000258101830(lVar24,&cfstringStruct_276115790);
                  if (iVar9 == 0) {
                    uVar15 = param_1[0x4c];
                    local_1b0 = param_1[0x16];
                    uStack_1a8 = (undefined4)param_1[0x17];
                    uStack_19c = (undefined4)*(undefined8 *)((long)param_1 + 0xc4);
                    uStack_198 = (undefined4)((ulong)*(undefined8 *)((long)param_1 + 0xc4) >> 0x20);
                    uStack_1a4 = (undefined4)*(undefined8 *)((long)param_1 + 0xbc);
                    local_1a0 = (undefined4)((ulong)*(undefined8 *)((long)param_1 + 0xbc) >> 0x20);
                    local_138[0] = 0;
                    lStack_b8 = 0;
                    local_c0 = (ulong *)0x0;
                    uStack_a8 = 0;
                    local_b0 = 0;
                    uStack_d8 = 0;
                    uStack_d4 = 0;
                    uStack_d2 = 0;
                    local_e0 = 0;
                    uStack_dc = 0;
                    local_c8 = 0;
                    uStack_c4 = 0;
                    uStack_d0 = 0;
                    uStack_cc = 0;
                    uStack_ca = 0;
                    if (uVar15 == 0) {
                      func_0x000258109a30(0,
                                          "APReceiverRemoteControlSessionSenderUIEventsChannelCreate"
                                          ,0xae,0);
LAB_2518d73ac:
                      lVar24 = 0;
                      uVar19 = 0xffffe5cf;
                    }
                    else {
                      if (lVar22 == 0) {
                        func_0x000258109a30(0,
                                            "APReceiverRemoteControlSessionSenderUIEventsChannelCreate"
                                            ,0xb0,0);
                        goto LAB_2518d73ac;
                      }
                      if (_APReceiverRemoteControlSessionGetClassID_sRegisterOnce != -1) {
                        func_0x0002580fd0c0(&_APReceiverRemoteControlSessionGetClassID_sRegisterOnce
                                            ,&_APReceiverRemoteControlSessionGetClassID_sClassID,
                                            _rcs_getClassID);
                      }
                      uVar19 = func_0x00025810acc0(uVar28,&
                                                  _kAPRRemoteControlSessionMediaRemoteVTable_3388,
                                                  _APReceiverRemoteControlSessionGetClassID_sClassID
                                                  ,local_138);
                      if ((int)uVar19 == 0) {
                        lVar26 = func_0x00025810ac50(local_138[0]);
                        uVar19 = func_0x0002580f6a60(lVar21);
                        *(undefined8 *)(lVar26 + 0x10) = uVar19;
                        *(ulong *)(lVar26 + 0x50) = uVar15;
                        func_0x0002580f6a60(uVar15);
                        lVar24 = func_0x00025810b410();
                        *(long *)(lVar26 + 0x70) = lVar24;
                        if (lVar24 == 0) {
                          uVar19 = 0xbb;
LAB_2518d744c:
                          func_0x000258109a30(0,
                                              "APReceiverRemoteControlSessionSenderUIEventsChannelCreate"
                                              ,uVar19,0);
                          lVar24 = 0;
                        }
                        else {
                          func_0x00025810bb20(&local_e0,0x40,
                                              "APReceiverRemoteControlSessionSenderUIEventsChannel.%{ptr}.incoming"
                                             );
                          lVar24 = func_0x0002580f54e0(&local_e0,0);
                          *(long *)(lVar26 + 0x38) = lVar24;
                          if (lVar24 == 0) {
                            uVar19 = 0xbf;
                            goto LAB_2518d744c;
                          }
                          func_0x00025810bb20(&local_e0,0x40,
                                              "APReceiverRemoteControlSessionSenderUIEventsChannel.%{ptr}.outgoing"
                                             );
                          lVar24 = func_0x0002580f54e0(&local_e0,0);
                          *(long *)(lVar26 + 0x40) = lVar24;
                          if (lVar24 == 0) {
                            uVar19 = 0xc3;
                            goto LAB_2518d744c;
                          }
                          *(code **)(lVar26 + 0x20) = pcStack_120;
                          *(ulong **)(lVar26 + 0x18) = local_128;
                          *(code **)(lVar26 + 0x28) = local_118;
                          lVar24 = func_0x00025810b250(param_1);
                          *(long *)(lVar26 + 0x30) = lVar24;
                          if (lVar24 == 0) {
                            uVar19 = 200;
                            goto LAB_2518d744c;
                          }
                          lVar24 = func_0x000258101820(uVar28,0,_DAT_2680d3340,_DAT_2680d3358);
                          if (lVar24 != 0) {
                            func_0x00025810b180(lVar24,&cfstringStruct_27610f1b0,lVar20);
                            func_0x00025810b180(lVar24,&cfstringStruct_27610f1d0,lVar36);
                            func_0x0002580f7000(lVar24,&cfstringStruct_27610f1f0,
                                                &cfstringStruct_2761168f0);
                            func_0x00025810b140(lVar24,&cfstringStruct_27610f230,3);
                            local_158 = local_138[0];
                            pcStack_150 = _rcsSenderUIEventsChannel_handleMediaDataControlRequest;
                            local_148 = _rcsSenderUIEventsChannel_handleMediaDataControlFailure;
                            uStack_108._0_4_ = uStack_1a8;
                            local_110 = local_1b0;
                            uStack_fc = uStack_19c;
                            local_f8 = uStack_198;
                            uStack_108._4_4_ = uStack_1a4;
                            local_100 = local_1a0;
                            uVar19 = _APMediaDataControlServerCreate
                                               (&local_110,lVar24,&local_158,lVar26 + 0x48);
                            if ((int)uVar19 != 0) {
                              func_0x000258109a30(uVar19,
                                                  "APReceiverRemoteControlSessionSenderUIEventsChannelCreate"
                                                  ,0xd8,0);
                              goto LAB_2518d745c;
                            }
                            if (_gLogCategory_APReceiverRemoteControlSessionSenderUIEventsChannel <
                                0x33) {
                              if ((_gLogCategory_APReceiverRemoteControlSessionSenderUIEventsChannel
                                   != -1) ||
                                 (iVar9 = func_0x000258101e40(&
                                                  _gLogCategory_APReceiverRemoteControlSessionSenderUIEventsChannel
                                                  ,0x2000032), iVar9 != 0)) {
                                func_0x000258101eb0(&
                                                  _gLogCategory_APReceiverRemoteControlSessionSenderUIEventsChannel
                                                  ,
                                                  "OSStatus APReceiverRemoteControlSessionSenderUIEventsChannelCreate(CFAllocatorRef, CFNumberRef, sockaddr_ip, CFDataRef, CFDataRef, const APReceiverRemoteControlSessionTransportDelegate *, APReceiverUIControllerRef, APReceiverRemoteControlSessionRef *)"
                                                  ,0x2000032,
                                                  "[%{ptr}] Listening for connection on port %d\n");
                              }
                              if ((_gLogCategory_APReceiverRemoteControlSessionSenderUIEventsChannel
                                   < 0x33) &&
                                 ((_gLogCategory_APReceiverRemoteControlSessionSenderUIEventsChannel
                                   != -1 || (iVar9 = func_0x000258101e40(&
                                                  _gLogCategory_APReceiverRemoteControlSessionSenderUIEventsChannel
                                                  ,0x2000032), iVar9 != 0)))) {
                                func_0x000258101eb0(&
                                                  _gLogCategory_APReceiverRemoteControlSessionSenderUIEventsChannel
                                                  ,
                                                  "OSStatus APReceiverRemoteControlSessionSenderUIEventsChannelCreate(CFAllocatorRef, CFNumberRef, sockaddr_ip, CFDataRef, CFDataRef, const APReceiverRemoteControlSessionTransportDelegate *, APReceiverUIControllerRef, APReceiverRemoteControlSessionRef *)"
                                                  ,0x2000032,"[%{ptr}] RCS-%@ created\n");
                              }
                            }
                            local_180 = local_138[0];
                            local_138[0] = 0;
                            func_0x0002580f5830(lVar24);
                            local_1c0 = local_1c0 & 0xffffffff00000000;
                            if ((_gLogCategory_AirPlayReceiverCore < 0x33) &&
                               ((_gLogCategory_AirPlayReceiverCore != -1 ||
                                (iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,
                                                             0x2000032), iVar9 != 0)))) {
                              pcVar27 = 
                              "[%{ptr}] Created RCS-%@ [%{ptr}] for SenderUIEvents with channel name: %@, streamID: %llu\n"
                              ;
                              goto LAB_2518d6ae8;
                            }
                            lVar24 = local_180;
                            func_0x0002580f7000(param_1[0x5a],lVar21,local_180);
                            goto LAB_2518d6b64;
                          }
                          func_0x000258109a30(0,
                                              "APReceiverRemoteControlSessionSenderUIEventsChannelCreate"
                                              ,0xcc,0);
                        }
                        uVar19 = 0xffffe5b8;
                      }
                      else {
                        func_0x000258109a30(uVar19,
                                            "APReceiverRemoteControlSessionSenderUIEventsChannelCreate"
                                            ,0xb3,0);
                        lVar24 = 0;
                      }
                    }
LAB_2518d745c:
                    lVar22 = local_138[0];
                    if (local_138[0] != 0) {
                      lVar26 = func_0x000258109150(local_138[0]);
                      puVar34 = (undefined8 *)(*(long *)(lVar26 + 8) + 0x18);
                      pcVar32 = (code *)*puVar34;
                      if ((pcVar32 != (code *)0x0) && (pcVar32 != (code *)0x0)) {
                        (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x3af8000000000000,lVar22);
                      }
                      if (local_138[0] != 0) {
                        func_0x0002580f5830();
                      }
                    }
                    if (lVar24 != 0) {
                      func_0x0002580f5830(lVar24);
                    }
                    local_1c0 = CONCAT44(local_1c0._4_4_,(int)uVar19);
                    func_0x000258109a30(uVar19,"_RemoteControlSessionSetup",0x183f,0);
                    goto LAB_2518d6c94;
                  }
                  uStack_d8 = (undefined4)param_1[0x17];
                  local_e0 = (undefined4)param_1[0x16];
                  uStack_dc = (uint)(param_1[0x16] >> 0x20);
                  uVar39 = *(undefined8 *)((long)param_1 + 0xc4);
                  uVar25 = *(undefined8 *)((long)param_1 + 0xbc);
                  uStack_cc = (undefined2)uVar39;
                  uStack_ca = (undefined2)((ulong)uVar39 >> 0x10);
                  local_c8 = (uint)((ulong)uVar39 >> 0x20);
                  uStack_d4 = (undefined2)uVar25;
                  uStack_d2 = (undefined2)((ulong)uVar25 >> 0x10);
                  uStack_d0 = (undefined4)((ulong)uVar25 >> 0x20);
                  uVar19 = _APReceiverRemoteControlSessionMediaRemoteCreate
                                     (uVar28,lVar21,&local_e0,uVar19,lVar20,lVar36,&local_128,0,
                                      &local_180);
                  local_1c0 = CONCAT44(local_1c0._4_4_,(int)uVar19);
                  if ((int)uVar19 != 0) {
                    uVar25 = 0x183a;
LAB_2518d6c8c:
                    func_0x000258109a30(uVar19,"_RemoteControlSessionSetup",uVar25,0);
                    goto LAB_2518d6c94;
                  }
                  if (_gLogCategory_AirPlayReceiverCore < 0x33) {
                    if (_gLogCategory_AirPlayReceiverCore == -1) {
                      iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032);
                      if (iVar9 == 0) goto LAB_2518d6b18;
                    }
                    pcVar27 = 
                    "[%{ptr}] Created RCS-%@ [%{ptr}] for MediaRemote with channel name: %@, streamID: %llu\n"
                    ;
LAB_2518d6ae8:
                    func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                        "OSStatus _RemoteControlSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFMutableDictionaryRef)"
                                        ,0x2000032,pcVar27);
                  }
LAB_2518d6b18:
                  lVar24 = local_180;
                  func_0x0002580f7000(param_1[0x5a],lVar21,local_180);
                  if (lVar22 != 0) {
LAB_2518d6b64:
                    lVar22 = func_0x000258109150(lVar24);
                    puVar34 = (undefined8 *)(*(long *)(lVar22 + 8) + 0x30);
                    pcVar32 = (code *)*puVar34;
                    if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                      uVar19 = 0xffffce12;
                      local_1c0 = CONCAT44(local_1c0._4_4_,0xffffce12);
                    }
                    else {
                      uVar19 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x9725000000000000,
                                          lVar24,&cfstringStruct_27610f810,uVar28,&local_1b8);
                      local_1c0 = CONCAT44(local_1c0._4_4_,(int)uVar19);
                      if ((int)uVar19 == 0) {
                        func_0x0002580f7000(lVar23,&cfstringStruct_276117f90,local_1b8);
                        goto LAB_2518d6be8;
                      }
                    }
                    uVar25 = 0x1847;
                    goto LAB_2518d6c8c;
                  }
LAB_2518d6be8:
                  uVar19 = __AddResponseStream(lVar14,lVar23);
                  local_1c0 = CONCAT44(local_1c0._4_4_,(int)uVar19);
                  if ((int)uVar19 != 0) {
                    uVar25 = 0x184c;
                    goto LAB_2518d6c8c;
                  }
                  lVar22 = func_0x000258109150(lVar24);
                  puVar34 = (undefined8 *)(*(long *)(lVar22 + 0x10) + 8);
                  pcVar32 = (code *)*puVar34;
                  if ((pcVar32 == (code *)0x0) || (pcVar32 == (code *)0x0)) {
                    uVar19 = 0xffffce12;
                    local_1c0 = CONCAT44(local_1c0._4_4_,0xffffce12);
LAB_2518d6c80:
                    uVar25 = 0x184f;
                    goto LAB_2518d6c8c;
                  }
                  uVar19 = (*pcVar32)((ulong)puVar34 & 0xffffffffffff | 0x4a51000000000000,lVar24);
                  local_1c0 = CONCAT44(local_1c0._4_4_,(int)uVar19);
                  if ((int)uVar19 != 0) goto LAB_2518d6c80;
                }
LAB_2518d6ca8:
                if (local_180 != 0) {
                  func_0x0002580f5830();
                }
                if (lVar21 != 0) {
                  func_0x0002580f5830(lVar21);
                }
                if (lVar23 != 0) {
                  func_0x0002580f5830(lVar23);
                }
                if (lVar20 != 0) {
                  func_0x0002580f5830(lVar20);
                }
                if (lVar36 != 0) {
                  func_0x0002580f5830(lVar36);
                }
                uVar15 = local_1c0 & 0xffffffff;
                local_1c4 = (uint)local_1c0;
                if ((uint)local_1c0 != 0) {
                  uVar17 = 0x781;
                  goto LAB_2518d78d8;
                }
                goto LAB_2518d7298;
              }
              func_0x000258109a30(0,"AirPlayReceiverSessionSetup",0x773,0);
              local_1c4 = 0xffffe5cf;
              goto LAB_2518d7608;
            }
            uVar15 = param_1[0x59] + 1;
            param_1[0x59] = uVar15;
            lVar20 = func_0x00025810a800(uVar15);
            if (lVar20 == 0) {
              func_0x000258109a30(0,"_PlaybackSetup",0x16b6,0);
              lVar21 = 0;
LAB_2518d6d98:
              uVar15 = 0xffffe5b8;
            }
            else {
              lVar21 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
              if (lVar21 == 0) {
                func_0x000258109a30(0,"_PlaybackSetup",0x16b9,0);
                goto LAB_2518d6d98;
              }
              func_0x00025810a790(lVar21,&cfstringStruct_276112330,0x78);
              func_0x00025810a790(lVar21,&cfstringStruct_276119b10,uVar15);
              uVar15 = __AddResponseStream(lVar14,lVar21);
              if ((int)uVar15 == 0) {
                func_0x00025810aa20(param_1[0x60],lVar20);
                lVar23 = func_0x00025810aa00(param_1[0x60]);
                if (lVar23 == 1) {
                  __UpdateActiveSessionRegistration(param_1,0,1);
                }
                uVar15 = 0;
              }
              else {
                func_0x000258109a30(uVar15,"_PlaybackSetup",0x16bf,0);
              }
            }
            if (_gLogCategory_AirPlayReceiverCore < 0x33) {
              if (_gLogCategory_AirPlayReceiverCore == -1) {
                iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032);
                if (iVar9 == 0) goto LAB_2518d57e4;
              }
              func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                                  "OSStatus _PlaybackSetup(AirPlayReceiverSessionRef, CFMutableDictionaryRef)"
                                  ,0x2000032,"[%{ptr}] Playback set up, streamID = %llu, err = %d\n"
                                 );
            }
LAB_2518d57e4:
            if (lVar21 != 0) {
              func_0x0002580f5830(lVar21);
            }
            if (lVar20 != 0) {
              func_0x0002580f5830(lVar20);
            }
            local_1c4 = (uint)uVar15;
            if (local_1c4 != 0) {
              uVar17 = 0x76c;
LAB_2518d78d8:
              func_0x000258109a30(uVar15,"AirPlayReceiverSessionSetup",uVar17,0);
              goto LAB_2518d7608;
            }
          }
LAB_2518d7298:
          lVar37 = lVar37 + 1;
        } while (lVar37 != lVar18);
        if (((int)param_1[0x58] == 2) && (bVar3 || bVar4)) {
          lVar16 = func_0x000258102660(param_1[0x48]);
          uVar15 = __cfDictionaryCopyKeysAndValues(param_1[0x48],0,&local_1d0);
          lVar38 = local_1d0;
          if ((uint)uVar15 != 0) {
            uVar17 = 0x794;
            local_1c4 = (uint)uVar15;
            goto LAB_2518d7770;
          }
          if (0 < lVar16) {
            lVar18 = 0;
            local_1c4 = 0;
            do {
              func_0x0002581017e0(lVar38,lVar18);
              _APReceiverAudioSessionUpdateLatency();
              lVar18 = lVar18 + 1;
            } while (lVar16 != lVar18);
          }
        }
      }
    }
    *param_3 = lVar14;
    local_1c4 = 0;
    if (cVar1 == '\0') {
      __LogSessionStateChange(param_1,1,0);
    }
    lVar14 = 0;
  }
LAB_2518d7608:
  if (local_1d0 != 0) {
    func_0x0002580f5830();
  }
  if (lVar14 != 0) {
    func_0x0002580f5830(lVar14);
  }
  if (local_1c4 == 0) {
    uVar12 = 0;
    goto LAB_2518d76b4;
  }
  if (_gLogCategory_AirPlayReceiverCore < 0x33) {
    if (_gLogCategory_AirPlayReceiverCore == -1) {
      iVar9 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x2000032);
      if (iVar9 == 0) goto LAB_2518d76a0;
    }
    func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                        "OSStatus AirPlayReceiverSessionSetup(AirPlayReceiverSessionRef, CFDictionaryRef, CFDictionaryRef *)"
                        ,0x2000032,"### [%{ptr}] Set up session %llu with %##a failed: %#m %@\n");
  }
LAB_2518d76a0:
  _AirPlayReceiverSessionTearDown(param_1,param_2,local_1c4,0);
  uVar12 = local_1c4;
LAB_2518d76b4:
  if (*_DAT_2681b4ee0 == local_98) {
    return;
  }
  func_0x0002580f4380(uVar12);
  return;
}


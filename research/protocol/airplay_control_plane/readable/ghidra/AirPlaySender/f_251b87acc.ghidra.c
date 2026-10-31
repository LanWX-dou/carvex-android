/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b87acc
 * original code SHA256: c702321d6e49b5069ec60ee5f962647119e04ae28a8f85bf7992688506216238
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_coreUtilsPairing_PerformVerification(undefined8 param_1,undefined8 *param_2,undefined8 param_3)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  undefined8 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 in_ZR;
  char cVar7;
  char cVar8;
  undefined1 uVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 *puVar16;
  long lVar17;
  undefined8 extraout_x1;
  undefined8 extraout_x1_00;
  undefined8 extraout_x1_01;
  uint uVar18;
  int extraout_w8;
  int extraout_w8_00;
  int extraout_w8_01;
  undefined4 uVar19;
  int extraout_w8_02;
  int extraout_w8_03;
  int extraout_w8_04;
  int extraout_w8_05;
  int extraout_w8_06;
  int extraout_w8_07;
  int extraout_w8_08;
  int extraout_w8_09;
  int extraout_w8_10;
  int extraout_w8_11;
  int extraout_w8_12;
  int extraout_w8_13;
  int extraout_w8_14;
  int extraout_w8_15;
  int extraout_w8_16;
  undefined8 extraout_x8;
  char *pcVar20;
  long *plVar21;
  long lVar22;
  uint uVar23;
  cfstringStruct *pcVar24;
  undefined8 unaff_x27;
  undefined1 auVar25 [16];
  long local_108;
  long local_100;
  char local_f1;
  undefined8 local_f0;
  long local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined4 local_b0;
  int iStack_ac;
  undefined4 local_a8;
  undefined4 uStack_a4;
  code *local_a0;
  undefined *puStack_98;
  undefined8 local_90;
  undefined8 *puStack_88;
  cfstringStruct *local_78;
  undefined8 local_70;
  
  _OUTLINED_FUNCTION_13();
  local_70 = extraout_x8;
  lVar12 = func_0x00025810ac50();
  if (*(char *)(lVar12 + 0x40) == '\0') {
    uVar23 = 0;
  }
  else {
    in_ZR = *(char *)(lVar12 + 0x42) == '\0';
    uVar23 = (uint)(byte)in_ZR;
  }
  if (*(char *)(lVar12 + 0x3a) != '\0') {
    unaff_x27 = 0;
    goto LAB_251b88450;
  }
  if (*(char *)(lVar12 + 0x3c) == '\0') {
    if (*(char *)(lVar12 + 0x3d) == '\0') {
      if (*(char *)(lVar12 + 0x39) == '\0') {
        uVar18 = 2;
      }
      else {
        uVar18 = 3;
        if (*(char *)(lVar12 + 0x3b) != '\0') {
          uVar18 = 5;
        }
      }
    }
    else {
      uVar18 = 6;
      if (*(char *)(lVar12 + 0x3e) != '\0') {
        uVar18 = 7;
      }
    }
  }
  else {
    uVar18 = 8;
  }
  lVar12 = func_0x00025810ac50(param_1);
  local_e8 = 0;
  local_e0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  local_f0 = 0;
  local_f1 = '\0';
  uVar3 = uVar18 - 6;
  local_108 = 0;
  local_100 = 0;
  cVar7 = SBORROW4(uVar3,2);
  cVar8 = (int)(uVar18 - 8) < 0;
  uVar9 = uVar3 == 2;
  if (uVar3 < 3) {
    pcVar20 = *(char **)(&UNK_2693e7868 + (ulong)uVar3 * 8);
  }
  else {
    pcVar20 = "AP";
  }
  plVar21 = (long *)(lVar12 + 8);
  if (*plVar21 != 0) {
    func_0x0002580f5830();
    *plVar21 = 0;
  }
  _OUTLINED_FUNCTION_9();
  if ((bool)uVar9 || cVar8 != cVar7) {
    if (extraout_w8 == -1) {
      uVar13 = _OUTLINED_FUNCTION_2();
      iVar10 = func_0x000258101e40(uVar13,extraout_w8_00 + 0x14);
      if (iVar10 == 0) goto LAB_251b87c24;
    }
    _OUTLINED_FUNCTION_1();
    auVar25 = _OUTLINED_FUNCTION_11();
    func_0x000258101eb0(auVar25._0_8_,auVar25._8_8_,extraout_w8_01 + 0x14);
  }
LAB_251b87c24:
  cVar7 = SBORROW4(uVar18,8);
  cVar8 = (int)(uVar18 - 8) < 0;
  in_ZR = uVar18 == 8;
  if ((bool)in_ZR) {
    unaff_x27 = _OUTLINED_FUNCTION_26();
    if ((int)unaff_x27 != 0) {
      func_0x000258109a30(unaff_x27,"coreUtilsPairing_createAccountOwnerPairVerifySession",0x43d,0);
      if (CONCAT44(iStack_ac,local_b0) != 0) {
        func_0x0002580f5830();
      }
      auVar25._8_8_ = "coreUtilsPairing_performVerificationInternal";
      auVar25._0_8_ = unaff_x27;
      uVar13 = 0x35c;
      goto LAB_251b885dc;
    }
    uVar19 = 0xc;
    if (uVar23 != 0) {
      uVar19 = 0xd;
    }
    func_0x00025810ba40(CONCAT44(iStack_ac,local_b0),uVar19);
    func_0x00025810ba60(CONCAT44(iStack_ac,local_b0),&_gLogCategory_APPairingClientCoreUtils);
    func_0x00025810ba80(CONCAT44(iStack_ac,local_b0),&___block_literal_global);
    func_0x00025810ba90(CONCAT44(iStack_ac,local_b0),&___block_literal_global_121);
LAB_251b87cc8:
    *plVar21 = CONCAT44(iStack_ac,local_b0);
LAB_251b87d28:
    cVar7 = SBORROW4(_gLogCategory_APPairingClientCoreUtils,0x32);
    cVar8 = _gLogCategory_APPairingClientCoreUtils + -0x32 < 0;
    in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x32;
    if (_gLogCategory_APPairingClientCoreUtils < 0x33) {
      cVar7 = SCARRY4(_gLogCategory_APPairingClientCoreUtils,1);
      cVar8 = _gLogCategory_APPairingClientCoreUtils + 1 < 0;
      in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
      if ((bool)in_ZR) {
        uVar13 = _OUTLINED_FUNCTION_2();
        iVar10 = func_0x000258101e40(uVar13,extraout_w8_02 + 0x14);
        if (iVar10 == 0) goto LAB_251b87d78;
      }
      _OUTLINED_FUNCTION_1();
      auVar25 = _OUTLINED_FUNCTION_11();
      func_0x000258101eb0(auVar25._0_8_,auVar25._8_8_,extraout_w8_03 + 0x14);
    }
LAB_251b87d78:
    lVar22 = local_108;
    if (local_108 == 0) {
LAB_251b87e94:
      uVar4 = DAT_251c6b1b8;
      uVar13 = DAT_251c6b118;
      local_e0 = 0;
      local_f0 = 0;
      local_f1 = '\0';
      do {
        do {
          iVar11 = func_0x00025810b820();
          uVar19 = local_a8;
          iVar10 = iStack_ac;
          iStack_ac = (int)pcVar20;
          iVar5 = iStack_ac;
          local_a8 = (undefined4)((ulong)pcVar20 >> 0x20);
          uVar6 = local_a8;
          iStack_ac = iVar10;
          local_a8 = uVar19;
          if (iVar11 != 0) {
            uVar14 = func_0x000258109330();
            iVar10 = func_0x00025810ae00(*(undefined8 *)(lVar12 + 0x30));
            if ((iVar10 != 0) && (iVar10 = func_0x0002580f5630(uVar14), iVar10 != 0)) {
              local_b0 = (int)uVar13;
              iStack_ac = iVar5;
              local_a8 = uVar6;
              uVar15 = _OUTLINED_FUNCTION_12();
              func_0x0002580f5490(uVar15,uVar14,1);
            }
          }
          unaff_x27 = func_0x00025810ba20(*plVar21,local_e0,local_f0,&local_e8,&local_f0,&local_f1);
          iVar10 = func_0x00025810b820();
          if (iVar10 != 0) {
            uVar14 = func_0x000258109330();
            iVar10 = func_0x00025810ae00(*(undefined8 *)(lVar12 + 0x30));
            if ((iVar10 != 0) && (iVar10 = func_0x0002580f5630(uVar14), iVar10 != 0)) {
              local_b0 = (int)uVar4;
              iStack_ac = (int)unaff_x27;
              uVar15 = _OUTLINED_FUNCTION_12();
              func_0x0002580f5490(uVar15,uVar14,2);
            }
          }
          if ((int)unaff_x27 != 0) goto LAB_251b88394;
          if (local_f1 != '\0') {
            if ((uVar23 == 0) ||
               (unaff_x27 = _coreUtilsPairing_validateMFiCertificate(param_1,*plVar21,0),
               (int)unaff_x27 == 0)) {
              cVar7 = SBORROW4(_gLogCategory_APPairingClientCoreUtils,0x32);
              cVar8 = _gLogCategory_APPairingClientCoreUtils + -0x32 < 0;
              in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x32;
              if (_gLogCategory_APPairingClientCoreUtils < 0x33) {
                cVar7 = SCARRY4(_gLogCategory_APPairingClientCoreUtils,1);
                cVar8 = _gLogCategory_APPairingClientCoreUtils + 1 < 0;
                in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
                if ((bool)in_ZR) {
                  uVar13 = _OUTLINED_FUNCTION_2();
                  iVar10 = func_0x000258101e40(uVar13,extraout_w8_09 + 0x14);
                  if (iVar10 == 0) goto LAB_251b88168;
                }
                _OUTLINED_FUNCTION_1();
                auVar25 = _OUTLINED_FUNCTION_11();
                func_0x000258101eb0(auVar25._0_8_,auVar25._8_8_,extraout_w8_10 + 0x14);
              }
LAB_251b88168:
              *(char *)(lVar12 + 0x42) = (char)uVar23;
              local_d8 = (ulong)local_d8._4_4_ << 0x20;
              lVar12 = func_0x00025810ac50(param_1);
              if (*(long *)(lVar12 + 8) == 0) {
                func_0x000258109a30(0,"coreUtilsPairing_getPairedPeerFromVerificationPairingSession"
                                    ,0x300,0);
                lVar12 = 0;
              }
              else {
                auVar25 = func_0x00025810fd50(*(long *)(lVar12 + 8),&local_d8);
                lVar12 = auVar25._0_8_;
                if ((int)local_d8 == 0) {
                  if (lVar22 != 0) {
                    local_78 = &cfstringStruct_2761364d0;
                    local_b0 = (undefined4)lVar22;
                    iStack_ac = (int)((ulong)lVar22 >> 0x20);
                    auVar25 = func_0x000258001740(_DAT_2680d2e90,auVar25._8_8_,&local_b0,&local_78,1
                                                 );
                    lVar12 = func_0x000258030d00(lVar12,auVar25._8_8_,auVar25._0_8_);
                  }
                }
                else {
                  cVar7 = SBORROW4((int)local_d8,-0x1a47);
                  cVar8 = (int)local_d8 + 0x1a47 < 0;
                  in_ZR = (int)local_d8 == -0x1a47;
                  if (!(bool)in_ZR) {
                    func_0x000258109a30(local_d8 & 0xffffffff,
                                        "coreUtilsPairing_getPairedPeerFromVerificationPairingSession"
                                        ,0x304,0);
                  }
                }
              }
              auVar25 = func_0x00025810ac50(param_1);
              puVar16 = auVar25._0_8_;
              local_78 = (cfstringStruct *)0x0;
              local_d8 = 0;
              if ((lVar22 != 0) && (lVar12 != 0)) {
                uVar13 = func_0x000258030e50(*puVar16,auVar25._8_8_,lVar12);
                if ((int)uVar13 == 0) {
                  lVar17 = func_0x00025810fd20(puVar16[1],&cfstringStruct_2761364f0,0);
                  if (lVar17 != 0) {
                    cVar7 = SBORROW4(_gLogCategory_APPairingClientCoreUtils,0x1e);
                    cVar8 = _gLogCategory_APPairingClientCoreUtils + -0x1e < 0;
                    in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x1e;
                    if (_gLogCategory_APPairingClientCoreUtils < 0x1f) {
                      cVar7 = SCARRY4(_gLogCategory_APPairingClientCoreUtils,1);
                      cVar8 = _gLogCategory_APPairingClientCoreUtils + 1 < 0;
                      in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
                      if ((bool)in_ZR) {
                        uVar13 = _OUTLINED_FUNCTION_8();
                        iVar10 = func_0x000258101e40(uVar13,0x200001e);
                        if (iVar10 == 0) goto LAB_251b88268;
                      }
                      uVar13 = _OUTLINED_FUNCTION_4();
                      func_0x000258101eb0(uVar13,
                                          "void coreUtilsPairing_updatePairingGroupInfoIfNeeded(APPairingClientRef, CFDictionaryRef, CUPairedPeer *)"
                                          ,0x200001e,
                                          "[%{ptr}] Copied peer group info from pair-verify session [%{ptr}]: %1.64@\n"
                                         );
                    }
LAB_251b88268:
                    auVar25 = _APPairingClientCoreUtilsCreateCombinedPairingGroupInfo
                                        (lVar22,lVar17,puVar16[3],puVar16[5],&local_78);
                    uVar13 = auVar25._8_8_;
                    if (auVar25._0_4_ == 0) {
                      cVar7 = SBORROW4(_gLogCategory_APPairingClientCoreUtils,0x1e);
                      cVar8 = _gLogCategory_APPairingClientCoreUtils + -0x1e < 0;
                      in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x1e;
                      if (_gLogCategory_APPairingClientCoreUtils < 0x1f) {
                        cVar7 = SCARRY4(_gLogCategory_APPairingClientCoreUtils,1);
                        cVar8 = _gLogCategory_APPairingClientCoreUtils + 1 < 0;
                        in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
                        if ((bool)in_ZR) {
                          uVar13 = _OUTLINED_FUNCTION_8();
                          iVar10 = func_0x000258101e40(uVar13,0x200001e);
                          uVar13 = extraout_x1;
                          if (iVar10 == 0) goto LAB_251b882d0;
                        }
                        uVar13 = _OUTLINED_FUNCTION_6(local_78);
                        func_0x000258101eb0(uVar13,
                                            "void coreUtilsPairing_updatePairingGroupInfoIfNeeded(APPairingClientRef, CFDictionaryRef, CUPairedPeer *)"
                                            ,0x200001e,"[%{ptr}] Combined group info: %1.64@\n");
                        uVar13 = extraout_x1_00;
                      }
LAB_251b882d0:
                      uVar13 = func_0x000258030d10(*puVar16,uVar13,puVar16[4]);
                      pcVar24 = local_78;
                      _APPairingClientCoreUtilsCreateUnpairedPeersFromGroupInfo
                                (local_78,uVar13,&local_d8);
                      local_b0 = (undefined4)_DAT_2681b4ed0;
                      iStack_ac = (int)((ulong)_DAT_2681b4ed0 >> 0x20);
                      local_a8 = (undefined4)DAT_251c6b008;
                      uStack_a4 = (undefined4)((ulong)DAT_251c6b008 >> 0x20);
                      local_a0 = ___coreUtilsPairing_updatePairingGroupInfoIfNeeded_block_invoke;
                      puStack_98 = &___block_descriptor_48_e29_v32__0__CUPairedPeer_8Q16_B24l;
                      local_90 = param_1;
                      puStack_88 = puVar16;
                      func_0x000258003d80(&local_a0,local_d8,extraout_x1_01,&local_b0);
                      uVar13 = _APPairingClientCoreUtilsUpdateGroupInfo(param_1,pcVar24);
                      if ((int)uVar13 != 0) {
                        func_0x000258109a30(uVar13,"coreUtilsPairing_updatePairingGroupInfoIfNeeded"
                                            ,0x337,0);
                      }
                    }
                    else {
                      func_0x000258109a30(auVar25._0_8_,
                                          "coreUtilsPairing_updatePairingGroupInfoIfNeeded",0x327,0)
                      ;
                      pcVar24 = local_78;
                    }
                    if (pcVar24 != (cfstringStruct *)0x0) {
                      func_0x0002580f5830(pcVar24);
                    }
                    func_0x0002580f5830(lVar17);
                  }
                }
                else {
                  func_0x000258109a30(uVar13,"coreUtilsPairing_updatePairingGroupInfoIfNeeded",799,0
                                     );
                }
              }
              if (param_2 == (undefined8 *)0x0) {
                unaff_x27 = 0;
              }
              else {
                if (lVar12 == 0) {
                  uVar13 = 0;
                }
                else {
                  uVar13 = func_0x0002580f6a60(lVar12);
                }
                unaff_x27 = 0;
                *param_2 = uVar13;
              }
            }
            else {
              _OUTLINED_FUNCTION_3();
              if (!(bool)in_ZR && cVar8 == cVar7) goto LAB_251b88394;
              cVar7 = SCARRY4(extraout_w8_14,1);
              cVar8 = extraout_w8_14 + 1 < 0;
              in_ZR = extraout_w8_14 == -1;
              if ((bool)in_ZR) {
                uVar13 = _OUTLINED_FUNCTION_2();
                iVar10 = func_0x000258101e40(uVar13,extraout_w8_15 + 0x3c);
                if (iVar10 == 0) goto LAB_251b88394;
              }
              _OUTLINED_FUNCTION_1();
              auVar25 = _OUTLINED_FUNCTION_11();
              func_0x000258101eb0(auVar25._0_8_,auVar25._8_8_,extraout_w8_16 + 0x3c);
            }
            goto LAB_251b88394;
          }
          if (local_100 != 0) {
            func_0x0002580f5830();
            local_100 = 0;
          }
          iVar10 = func_0x00025810b820();
          if (iVar10 != 0) {
            uVar14 = func_0x000258109330();
            iVar10 = func_0x00025810ae00(*(undefined8 *)(lVar12 + 0x30));
            if ((iVar10 != 0) && (iVar10 = func_0x0002580f5630(uVar14), iVar10 != 0)) {
              local_b0 = (int)uVar13;
              iStack_ac = iVar5;
              local_a8 = uVar6;
              uVar15 = _OUTLINED_FUNCTION_12();
              func_0x0002580f5490(uVar15,uVar14,1);
            }
          }
          unaff_x27 = _coreUtilsPairing_sendPairingRequest
                                (param_1,uVar18,0x70617665,local_e8,local_f0,1,0,0,0,0,&local_100,
                                 param_3);
          iVar10 = func_0x00025810b820();
          if (iVar10 != 0) {
            uVar14 = func_0x000258109330();
            iVar10 = func_0x00025810ae00(*(undefined8 *)(lVar12 + 0x30));
            if ((iVar10 != 0) && (iVar10 = func_0x0002580f5630(uVar14), iVar10 != 0)) {
              local_b0 = (int)uVar4;
              iStack_ac = (int)unaff_x27;
              uVar15 = _OUTLINED_FUNCTION_12();
              func_0x0002580f5490(uVar15,uVar14,2);
            }
          }
          if ((int)unaff_x27 != 0) goto LAB_251b88394;
          if (local_e8 != 0) {
            func_0x0002580f4d30();
            local_e8 = 0;
          }
          param_3 = 0;
          local_f0 = 0;
          local_e0 = 0;
        } while (local_100 == 0);
        iVar10 = func_0x00025810eae0(local_100,0,&local_f0,0,&local_e0);
        param_3 = 0;
      } while (iVar10 == 0);
      auVar25 = _OUTLINED_FUNCTION_18();
      func_0x000258109a30(auVar25._0_8_,auVar25._8_8_,0x3a3,0);
LAB_251b88394:
      if (lVar22 != 0) goto LAB_251b88398;
    }
    else {
      iVar10 = _APPairingClientCoreUtilsIsValidPairingGroupInfo
                         (local_108,*(undefined8 *)(lVar12 + 0x18),*(undefined8 *)(lVar12 + 0x28));
      if (iVar10 == 0) {
        cVar7 = SBORROW4(_gLogCategory_APPairingClientCoreUtils,0x3c);
        cVar8 = _gLogCategory_APPairingClientCoreUtils + -0x3c < 0;
        in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x3c;
        if (_gLogCategory_APPairingClientCoreUtils < 0x3d) {
          cVar7 = SCARRY4(_gLogCategory_APPairingClientCoreUtils,1);
          cVar8 = _gLogCategory_APPairingClientCoreUtils + 1 < 0;
          in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
          if ((bool)in_ZR) {
            uVar13 = _OUTLINED_FUNCTION_2();
            iVar10 = func_0x000258101e40(uVar13,extraout_w8_07 + 0x1e);
            if (iVar10 == 0) goto LAB_251b87e84;
          }
          _OUTLINED_FUNCTION_1();
          auVar25 = _OUTLINED_FUNCTION_11();
          func_0x000258101eb0(auVar25._0_8_,auVar25._8_8_,extraout_w8_08 + 0x1e);
        }
LAB_251b87e84:
        func_0x0002580f5830(lVar22);
        lVar22 = 0;
        local_108 = 0;
        goto LAB_251b87e94;
      }
      cVar7 = SBORROW4(_gLogCategory_APPairingClientCoreUtils,0x1e);
      cVar8 = _gLogCategory_APPairingClientCoreUtils + -0x1e < 0;
      in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x1e;
      if (_gLogCategory_APPairingClientCoreUtils < 0x1f) {
        cVar7 = SCARRY4(_gLogCategory_APPairingClientCoreUtils,1);
        cVar8 = _gLogCategory_APPairingClientCoreUtils + 1 < 0;
        in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
        if ((bool)in_ZR) {
          uVar13 = _OUTLINED_FUNCTION_8();
          iVar10 = func_0x000258101e40(uVar13,0x200001e);
          if (iVar10 == 0) goto LAB_251b87de0;
        }
        auVar25 = _OUTLINED_FUNCTION_1();
        func_0x000258101eb0(auVar25._0_8_,auVar25._8_8_,0x200001e,
                            "[%{ptr}] Setting self group info on pair-verify session [%{ptr}]: %1.64@\n"
                           );
      }
LAB_251b87de0:
      unaff_x27 = func_0x00025810fd70(*plVar21,&cfstringStruct_2761364b0,lVar22);
      if ((int)unaff_x27 == 0) goto LAB_251b87e94;
      _OUTLINED_FUNCTION_3();
      if ((bool)in_ZR || cVar8 != cVar7) {
        cVar7 = SCARRY4(extraout_w8_04,1);
        cVar8 = extraout_w8_04 + 1 < 0;
        in_ZR = extraout_w8_04 == -1;
        if ((bool)in_ZR) {
          uVar13 = _OUTLINED_FUNCTION_2();
          iVar10 = func_0x000258101e40(uVar13,extraout_w8_05 + 0x3c);
          if (iVar10 == 0) goto LAB_251b88398;
        }
        _OUTLINED_FUNCTION_1();
        auVar25 = _OUTLINED_FUNCTION_11();
        func_0x000258101eb0(auVar25._0_8_,auVar25._8_8_,extraout_w8_06 + 0x3c);
      }
LAB_251b88398:
      func_0x0002580f5830(lVar22);
    }
  }
  else {
    uVar1 = uVar18 & 0xe;
    cVar7 = SBORROW4(uVar1,6);
    cVar8 = (int)(uVar1 - 6) < 0;
    in_ZR = uVar1 == 6;
    if ((bool)in_ZR) {
      cVar2 = *(char *)(lVar12 + 0x3f);
      unaff_x27 = _OUTLINED_FUNCTION_26();
      if ((int)unaff_x27 == 0) {
        uVar1 = 0x4000004;
        if (cVar2 != '\0') {
          uVar1 = 0x84000004;
        }
        func_0x00025810ba40(CONCAT44(iStack_ac,local_b0),uVar1 | uVar23);
        func_0x00025810ba60(CONCAT44(iStack_ac,local_b0),&_gLogCategory_APPairingClientCoreUtils);
        goto LAB_251b87cc8;
      }
      func_0x000258109a30(unaff_x27,"coreUtilsPairing_createHKPairVerifySession",0x471,0);
      if (CONCAT44(iStack_ac,local_b0) != 0) {
        func_0x0002580f5830();
      }
      auVar25._8_8_ = "coreUtilsPairing_performVerificationInternal";
      auVar25._0_8_ = unaff_x27;
      uVar13 = 0x360;
    }
    else {
      iVar10 = _coreUtilsPairing_createAirPlayPairingSession(param_1,3,0,uVar23,plVar21);
      if (iVar10 == 0) {
        func_0x000258101880(*(undefined8 *)(lVar12 + 0x10),&local_d0,0x20,0x8000100);
        iVar10 = func_0x00025810fd60(*(undefined8 *)(lVar12 + 8),&local_d0,0xffffffffffffffff);
        if (iVar10 == 0) {
          _APPairingClientCoreUtilsCopyGroupInfo(param_1,&local_108);
          goto LAB_251b87d28;
        }
        auVar25 = _OUTLINED_FUNCTION_18();
        uVar13 = 0x369;
      }
      else {
        auVar25 = _OUTLINED_FUNCTION_18();
        uVar13 = 0x364;
      }
    }
LAB_251b885dc:
    func_0x000258109a30(auVar25._0_8_,auVar25._8_8_,uVar13,0);
  }
  if (local_100 != 0) {
    func_0x0002580f5830();
  }
  if (local_e8 != 0) {
    func_0x0002580f4d30();
    local_e8 = 0;
  }
  if ((int)unaff_x27 == 0) goto LAB_251b88450;
  _OUTLINED_FUNCTION_3();
  if ((bool)in_ZR || cVar8 != cVar7) {
    in_ZR = extraout_w8_11 == -1;
    if ((bool)in_ZR) {
      uVar13 = _OUTLINED_FUNCTION_2();
      iVar10 = func_0x000258101e40(uVar13,extraout_w8_12 + 0x3c);
      if (iVar10 == 0) goto LAB_251b88428;
    }
    in_ZR = uVar3 == 2;
    _OUTLINED_FUNCTION_1();
    auVar25 = _OUTLINED_FUNCTION_11();
    func_0x000258101eb0(auVar25._0_8_,auVar25._8_8_,extraout_w8_13 + 0x3c);
  }
LAB_251b88428:
  if (*plVar21 != 0) {
    func_0x0002580f5830();
    *plVar21 = 0;
  }
  func_0x000258109a30(unaff_x27,"coreUtilsPairing_PerformVerification",0x3e9,0);
LAB_251b88450:
  _OUTLINED_FUNCTION_10(local_70);
  if ((bool)in_ZR) {
    return unaff_x27;
  }
  uVar13 = func_0x0002580f4380();
  return uVar13;
}


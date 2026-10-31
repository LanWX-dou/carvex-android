/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519b0014
 * original code SHA256: 3294e357f7d3416ee6f60ad4285a9a8e85e4af770c0655cb4a90e27da2c0de9d
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0002519b0ff8) */
/* WARNING: Removing unreachable block (ram,0x0002519b0ee8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _screenstream_dequeueAndProcessSampleBuffer
                (undefined8 param_1,int param_2,undefined4 *param_3)

{
  long *plVar1;
  long *plVar2;
  char in_NG;
  undefined1 in_ZR;
  bool bVar3;
  char in_OV;
  char cVar4;
  char cVar5;
  undefined1 uVar6;
  bool bVar7;
  int iVar8;
  uint uVar10;
  int iVar11;
  int iVar9;
  long lVar12;
  long lVar13;
  long lVar14;
  undefined8 *puVar15;
  ulong uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  long lVar19;
  long lVar20;
  undefined8 uVar21;
  long lVar22;
  char *pcVar23;
  int *piVar24;
  int extraout_w8;
  int extraout_w8_00;
  int extraout_w8_01;
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
  uint uVar25;
  int extraout_w8_13;
  int extraout_w8_14;
  int extraout_w8_15;
  int extraout_w8_16;
  int extraout_w8_17;
  int extraout_w8_18;
  undefined8 uVar26;
  undefined8 *extraout_x8;
  ulong extraout_x8_00;
  undefined8 *extraout_x8_01;
  undefined8 *extraout_x8_02;
  undefined8 *puVar27;
  byte bVar28;
  long extraout_x9;
  code *pcVar29;
  undefined8 *puVar30;
  undefined8 *puVar31;
  int *piVar32;
  ulong uVar33;
  char *unaff_x26;
  ulong unaff_x28;
  float fVar34;
  double dVar35;
  double dVar36;
  undefined *puVar37;
  double dVar38;
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  ulong local_e8;
  int local_dc;
  long local_d8;
  ulong local_d0;
  ulong uStack_c8;
  ulong local_c0;
  ulong local_b0;
  ulong local_a8;
  undefined8 local_a0;
  undefined8 uStack_98;
  code *local_90;
  undefined *puStack_88;
  undefined8 local_80;
  
  local_e8 = 0;
  lVar12 = func_0x00025810ac50();
  if (*(char *)(lVar12 + 0x474) != '\0') {
    return local_e8;
  }
  if (param_2 == 0) {
    lVar13 = func_0x00025810eb20(*(undefined8 *)(lVar12 + 0x68));
    if (lVar13 == 0) {
      return local_e8;
    }
    plVar1 = (long *)(lVar12 + 0x208);
    _OUTLINED_FUNCTION_27();
    lVar14 = func_0x00025810ec10();
    plVar2 = _DAT_2680d3198;
    puVar31 = (undefined8 *)&UNK_2693e7000;
    param_2 = (int)puVar31;
    if (lVar14 == 0) {
      _OUTLINED_FUNCTION_54(0,&cfstringStruct_27613fdd0);
      uVar16 = func_0x00025810acf0();
      if (uVar16 != 0) {
        local_d0 = 0;
        local_b0 = 0;
        local_a8 = 0;
        func_0x0002580f7510();
        puVar15 = (undefined8 *)func_0x00025810bda0();
        lVar14 = func_0x0002580f6a50(uVar16);
        lVar19 = func_0x000258102670();
        in_OV = SBORROW8(lVar14,lVar19);
        in_NG = lVar14 - lVar19 < 0;
        in_ZR = lVar14 == lVar19;
        if ((bool)in_ZR) {
          iVar8 = (int)puVar15;
          if (*(char *)(lVar12 + 0x3c5) == '\0') {
            lVar14 = 0;
            iVar9 = 0;
LAB_2519b066c:
            _OUTLINED_FUNCTION_27(*(undefined8 *)(lVar12 + 0x290));
            if ((extraout_x8_00 < uVar16 + extraout_x9 + 1) && (*(char *)(lVar12 + 0x3c6) != '\0'))
            {
              _OUTLINED_FUNCTION_19();
              bVar7 = extraout_w8_06 == 0x1e;
              if (extraout_w8_06 < 0x1f) {
                auVar39 = _OUTLINED_FUNCTION_32();
                if (bVar7) {
                  _OUTLINED_FUNCTION_11(auVar39._0_8_,iVar8 + -10);
                  auVar39 = func_0x000258101e40();
                  if (auVar39._0_4_ == 0) goto LAB_2519b06dc;
                }
                uVar26 = _OUTLINED_FUNCTION_6
                                   (*(undefined8 *)(lVar12 + 0x3b0),auVar39._0_8_,auVar39._8_8_,
                                    iVar8 + -10);
                func_0x000258101eb0(uVar26,
                                    "OSStatus sbpd_createStatsBBuf(SBufProcessingData *, CFTypeRef, CMBlockBufferRef *)"
                                   );
              }
LAB_2519b06dc:
              _OUTLINED_FUNCTION_20();
              uVar26 = *extraout_x8_01;
              local_a0 = _DAT_2681b4ed0;
              uStack_98 = DAT_251c6aff8;
              local_90 = ___getRandomDataBlob_block_invoke;
              puStack_88 = &___block_descriptor_tmp_201;
              local_80 = 25000;
              in_OV = SCARRY8(DAT_27097be58,1);
              in_NG = DAT_27097be58 + 1 < 0;
              in_ZR = DAT_27097be58 == -1;
              if (!(bool)in_ZR) {
                func_0x0002580f48c0(&DAT_27097be58,&local_a0);
              }
              iVar8 = func_0x00025810ac90(uVar26,DAT_27097be60,25000,*_DAT_2680d3170,0,0,25000,0,
                                          &local_b0);
              if (iVar8 == 0) {
                iVar8 = func_0x00025810aca0(local_b0);
                iVar9 = iVar8 + iVar9;
                goto LAB_2519b078c;
              }
              auVar39 = _OUTLINED_FUNCTION_17();
              uVar26 = 0x2e4;
LAB_2519b158c:
              func_0x000258109a30(auVar39._0_8_,auVar39._8_8_,uVar26,0);
            }
            else {
LAB_2519b078c:
              piVar24 = (int *)func_0x0002580f6280(1,0x80,0x79074dee);
              *piVar24 = iVar9;
              in_NG = '\0';
              in_ZR = *(char *)(lVar12 + 0x3c5) == '\0';
              in_OV = '\0';
              uVar6 = 2;
              if (!(bool)in_ZR) {
                uVar6 = 5;
              }
              *(undefined1 *)(piVar24 + 1) = uVar6;
              *(char *)((long)piVar24 + 5) = (char)*(undefined4 *)(lVar12 + 0x3c0);
              if (local_a8 == 0) {
                fVar34 = 0.0;
              }
              else {
                uVar33 = func_0x00025810aca0();
                fVar34 = (float)uVar33;
              }
              piVar24[0x1f] = (int)fVar34;
              uVar26 = _OUTLINED_FUNCTION_13();
              iVar8 = _OUTLINED_FUNCTION_42(uVar26,piVar24);
              if (iVar8 == 0) {
                if (local_a8 != 0) {
                  _OUTLINED_FUNCTION_100(local_d0);
                  iVar8 = func_0x00025810eab0();
                  if (iVar8 != 0) {
                    auVar39 = _OUTLINED_FUNCTION_17();
                    uVar26 = 0x2f8;
                    goto LAB_2519b158c;
                  }
                }
                if (local_b0 != 0) {
                  _OUTLINED_FUNCTION_100(local_d0);
                  iVar8 = func_0x00025810eab0();
                  if (iVar8 != 0) {
                    auVar39 = _OUTLINED_FUNCTION_17();
                    uVar26 = 0x2fd;
                    goto LAB_2519b158c;
                  }
                }
                unaff_x26 = (char *)0x0;
                *(undefined8 **)(lVar12 + 0x288) = puVar15;
                *(undefined8 *)(lVar12 + 0x468) = 0;
                *(undefined4 *)(lVar12 + 0x470) = 0;
                local_e8 = local_d0;
                local_d0 = 0;
              }
              else {
                auVar39 = _OUTLINED_FUNCTION_17();
                func_0x000258109a30(auVar39._0_8_,auVar39._8_8_,0x2f3,0);
                func_0x0002580f4d30(piVar24);
              }
            }
            if (lVar14 == 0) goto LAB_2519b0860;
          }
          else {
            dVar35 = DAT_251c6b120 / (double)(ulong)((long)puVar15 - *(long *)(lVar12 + 0x288));
            dVar36 = dVar35 * (double)(ulong)(*(long *)(lVar12 + 0x468) << 3);
            dVar38 = (double)NEON_ucvtf((ulong)*(uint *)(lVar12 + 0x470));
            iVar11 = (int)(dVar35 * dVar38 + 0.5);
            func_0x00025810b120(dVar36,uVar16,&cfstringStruct_27613fe70);
            func_0x00025810b140(uVar16,&cfstringStruct_27613fe90,iVar11);
            func_0x00025810b140(uVar16,&cfstringStruct_27613feb0,iVar11);
            _OUTLINED_FUNCTION_19();
            in_OV = SBORROW4(extraout_w8,0x1e);
            in_NG = extraout_w8 + -0x1e < 0;
            in_ZR = extraout_w8 == 0x1e;
            if (extraout_w8 < 0x1f) {
              auVar39 = _OUTLINED_FUNCTION_32();
              if ((bool)in_ZR) {
                _OUTLINED_FUNCTION_11(auVar39._0_8_,iVar8 + -10);
                auVar39 = func_0x000258101e40();
                if (auVar39._0_4_ == 0) goto LAB_2519b0234;
              }
              uVar26 = _OUTLINED_FUNCTION_11(auVar39._0_8_,auVar39._8_8_,iVar8 + -10);
              func_0x000258101eb0(uVar26,
                                  "OSStatus sbpd_createStatsBBuf(SBufProcessingData *, CFTypeRef, CMBlockBufferRef *)"
                                 );
            }
LAB_2519b0234:
            _OUTLINED_FUNCTION_20();
            unaff_x26 = (char *)*extraout_x8;
            lVar14 = func_0x00025810a970(unaff_x26,uVar16,200,0,0);
            if (lVar14 == 0) {
              uVar26 = 0x2ce;
              goto LAB_2519b1524;
            }
            _OUTLINED_FUNCTION_100(unaff_x26,lVar14);
            iVar9 = func_0x00025810f290();
            if (iVar9 == 0) {
              iVar9 = func_0x00025810aca0(local_a8);
              lVar19 = func_0x00025810a6f0(uVar16,&cfstringStruct_27613fed0,0);
              _sbpd_addHistogramValue((double)lVar19,plVar1,&cfstringStruct_27613fd10);
              _sbpd_addHistogramValue((double)iVar11,plVar1,&cfstringStruct_27613fd30);
              lVar19 = func_0x00025810a6f0(uVar16,&cfstringStruct_27613fef0,0);
              _sbpd_addHistogramValue((double)lVar19,plVar1,&cfstringStruct_27613fd50);
              dVar35 = DAT_251c6b4c0;
              _sbpd_addHistogramValue(dVar36 / DAT_251c6b4c0,plVar1,&cfstringStruct_27613fd90);
              dVar38 = (double)func_0x00025810a6c0(uVar16,&cfstringStruct_27613ff10,0);
              _sbpd_addHistogramValue(dVar38 / dVar35,plVar1,&cfstringStruct_27613fdb0);
              goto LAB_2519b066c;
            }
            auVar39 = _OUTLINED_FUNCTION_17();
            func_0x000258109a30(auVar39._0_8_,auVar39._8_8_,0x2d0,0);
            _OUTLINED_FUNCTION_27();
          }
          func_0x0002580f5830(lVar14);
        }
        else {
          uVar26 = 0x2c0;
LAB_2519b1524:
          func_0x000258109a30(0,"sbpd_createStatsBBuf",uVar26,0);
          unaff_x26 = (char *)0xffffbe88;
          _OUTLINED_FUNCTION_27();
        }
LAB_2519b0860:
        if (local_a8 != 0) {
          func_0x0002580f5830();
        }
        unaff_x28 = uVar16;
        uVar16 = local_d0;
        if (local_b0 != 0) {
          func_0x0002580f5830();
          uVar16 = local_d0;
        }
        goto joined_r0x0002519b0880;
      }
      _OUTLINED_FUNCTION_54(0,_kAPSampleBufferAttachmentKey_ClearScreen);
      lVar14 = func_0x00025810acf0();
      lVar19 = *plVar2;
      in_OV = SBORROW8(lVar14,lVar19);
      in_NG = lVar14 - lVar19 < 0;
      in_ZR = lVar14 == lVar19;
      *(undefined1 *)(lVar12 + 0x26c) = in_ZR;
      uVar26 = func_0x0002580f7510();
      *(undefined8 *)(lVar12 + 0x3d8) = uVar26;
      unaff_x26 = (char *)_sbpd_createConfigBBuf(plVar1,&local_e8);
      _OUTLINED_FUNCTION_27();
    }
    else {
      local_b0 = 0;
      local_a8 = 0;
      local_d8 = 0;
      puVar15 = (undefined8 *)func_0x00025810ec10(lVar13);
      iVar8 = func_0x00025810aca0();
      uVar26 = *(undefined8 *)(lVar12 + 0x3a8);
      uVar21 = _DAT_2680d36f8[1];
      uVar18 = *_DAT_2680d36f8;
      puVar37 = (undefined *)_DAT_2680d36f8[3];
      pcVar29 = (code *)_DAT_2680d36f8[2];
      local_dc = 0;
      local_a0 = uVar18;
      uStack_98 = uVar21;
      local_90 = pcVar29;
      puStack_88 = puVar37;
      iVar9 = _sbufGetAttachmentCGRect(lVar13,*_DAT_2680d5968,&local_a0);
      if (iVar9 != 0) {
        auVar39 = _OUTLINED_FUNCTION_12();
        uVar26 = 0x456;
        goto LAB_2519b14b0;
      }
      uVar16 = func_0x0002580f70c0(local_a0,uStack_98,local_90,puStack_88,
                                   *(undefined8 *)(lVar12 + 0x228),*(undefined8 *)(lVar12 + 0x230),
                                   *(undefined8 *)(lVar12 + 0x238),*(undefined8 *)(lVar12 + 0x240));
      if ((uVar16 & 1) == 0) {
        puVar31 = (undefined8 *)(lVar12 + 0x228);
        _OUTLINED_FUNCTION_13();
        if ((bool)in_ZR || in_NG != in_OV) {
          in_OV = SCARRY4(extraout_w8_00,1);
          in_NG = extraout_w8_00 + 1 < 0;
          in_ZR = extraout_w8_00 == -1;
          if ((!(bool)in_ZR) || (iVar9 = _OUTLINED_FUNCTION_10(), iVar9 != 0)) {
            uVar17 = _OUTLINED_FUNCTION_11();
            _OUTLINED_FUNCTION_12
                      (uVar17,
                       "OSStatus sbpd_createFrameBBuf(SBufProcessingData *, CMSampleBufferRef, CMBlockBufferRef *)"
                      );
          }
        }
        *(undefined8 *)(lVar12 + 0x230) = uStack_98;
        *puVar31 = local_a0;
        *(undefined **)(lVar12 + 0x240) = puStack_88;
        *(code **)(lVar12 + 0x238) = local_90;
        unaff_x28 = 1;
      }
      else {
        unaff_x28 = 0;
      }
      local_a0 = uVar18;
      uStack_98 = uVar21;
      local_90 = pcVar29;
      puStack_88 = puVar37;
      iVar9 = _sbufGetAttachmentCGRect(lVar13,*_DAT_2680d5948,&local_a0);
      if (iVar9 == 0) {
        uVar16 = func_0x0002580f70c0(local_a0,uStack_98,local_90,puStack_88,
                                     *(undefined8 *)(lVar12 + 0x248),*(undefined8 *)(lVar12 + 0x250)
                                     ,*(undefined8 *)(lVar12 + 600),*(undefined8 *)(lVar12 + 0x260))
        ;
        if ((uVar16 & 1) == 0) {
          uVar16 = _OUTLINED_FUNCTION_13();
          if (((bool)in_ZR || in_NG != in_OV) &&
             ((extraout_w8_01 != -1 || (uVar16 = _OUTLINED_FUNCTION_10(), (int)uVar16 != 0)))) {
            uVar18 = _OUTLINED_FUNCTION_11();
            uVar16 = _OUTLINED_FUNCTION_12
                               (uVar18,
                                "OSStatus sbpd_createFrameBBuf(SBufProcessingData *, CMSampleBufferRef, CMBlockBufferRef *)"
                               );
          }
          *(undefined8 *)(lVar12 + 0x250) = uStack_98;
          *(undefined8 *)(lVar12 + 0x248) = local_a0;
          *(undefined **)(lVar12 + 0x260) = puStack_88;
          *(code **)(lVar12 + 600) = local_90;
          unaff_x28 = 1;
        }
        _OUTLINED_FUNCTION_54(uVar16,*_DAT_2680d5970);
        lVar14 = func_0x00025810acf0();
        if (lVar14 == 0) {
LAB_2519b1324:
          func_0x000258109a30(0,"sbufGetAttachmentInt32",0x1d8,0);
        }
        else {
          lVar19 = func_0x0002580f6a50();
          lVar20 = func_0x000258101850();
          if (lVar19 != lVar20) goto LAB_2519b1324;
          func_0x0002580f59b0(lVar14,3,&local_dc);
        }
        if (local_dc != *(int *)(lVar12 + 0x268)) {
          if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
             ((_gLogCategory_APEndpointStreamScreen != -1 ||
              (iVar9 = _OUTLINED_FUNCTION_10(), iVar9 != 0)))) {
            uVar18 = _OUTLINED_FUNCTION_11();
            _OUTLINED_FUNCTION_12
                      (uVar18,
                       "OSStatus sbpd_createFrameBBuf(SBufProcessingData *, CMSampleBufferRef, CMBlockBufferRef *)"
                      );
          }
          *(int *)(lVar12 + 0x268) = local_dc;
          unaff_x28 = 1;
        }
        lVar14 = func_0x00025810c480(lVar13);
        iVar9 = func_0x00025810ace0();
        if (lVar14 != 0) {
          cVar4 = SBORROW4(iVar9,0x61766331);
          cVar5 = iVar9 + -0x61766331 < 0;
          uVar6 = iVar9 == 0x61766331;
          if (((bool)uVar6) && (*(char *)(lVar12 + 0x3c8) == '\0')) {
            lVar19 = func_0x00025810acd0(lVar14,*_DAT_2680d44d0);
            if (lVar19 == 0) {
LAB_2519b0938:
              bVar7 = true;
            }
            else {
              lVar20 = func_0x0002580f6a50();
              lVar22 = func_0x000258102670();
              if (lVar20 == lVar22) {
                lVar19 = func_0x000258102680(lVar19,&cfstringStruct_27613fe10);
LAB_2519b08ac:
                if (lVar19 != 0) {
                  lVar20 = func_0x0002580f6a50(lVar19);
                  lVar22 = func_0x0002581064c0();
                  cVar4 = SBORROW8(lVar20,lVar22);
                  cVar5 = lVar20 - lVar22 < 0;
                  uVar6 = lVar20 == lVar22;
                  if ((bool)uVar6) {
                    iVar9 = func_0x00025810b1a0(lVar19,*plVar1);
                    if (iVar9 == 0) {
                      _OUTLINED_FUNCTION_13();
                      if (((bool)uVar6 || cVar5 != cVar4) &&
                         ((extraout_w8_10 != -1 || (iVar9 = _OUTLINED_FUNCTION_10(), iVar9 != 0))))
                      {
                        func_0x0002580f6a40(lVar19);
                        _OUTLINED_FUNCTION_8();
                        _OUTLINED_FUNCTION_12();
                      }
                      lVar20 = *plVar1;
                      *plVar1 = lVar19;
                      func_0x0002580f6a60(lVar19);
                      if (lVar20 != 0) {
                        func_0x0002580f5830(lVar20);
                      }
                      bVar7 = false;
                      goto LAB_2519b099c;
                    }
                  }
                  else {
                    _OUTLINED_FUNCTION_14();
                    if ((bool)uVar6 || cVar5 != cVar4) {
                      if (extraout_w8_07 == -1) {
                        _OUTLINED_FUNCTION_11();
                        uVar18 = _OUTLINED_FUNCTION_24();
                        iVar9 = func_0x000258101e40(uVar18,extraout_w8_08 + 0x32);
                        if (iVar9 == 0) goto LAB_2519b0938;
                      }
                      _OUTLINED_FUNCTION_8();
                      auVar39 = _OUTLINED_FUNCTION_24();
                      func_0x000258101eb0(auVar39._0_8_,auVar39._8_8_,extraout_w8_09 + 0x32);
                    }
                  }
                }
                goto LAB_2519b0938;
              }
              lVar20 = func_0x0002580f6a50(lVar19);
              lVar22 = func_0x000258106470();
              if (lVar20 == lVar22) {
                lVar19 = func_0x0002581017e0(lVar19,0);
                goto LAB_2519b08ac;
              }
              bVar7 = true;
            }
LAB_2519b099c:
            uVar18 = func_0x00025810c520(lVar14);
            dVar38 = (double)(int)uVar18;
            dVar35 = *(double *)(lVar12 + 0x218);
            cVar5 = NAN(dVar35) || NAN(dVar38);
            bVar3 = dVar35 == dVar38;
            cVar4 = dVar35 < dVar38;
            iVar9 = (int)((ulong)uVar18 >> 0x20);
            if (bVar3) {
              dVar35 = (double)iVar9;
              dVar36 = *(double *)(lVar12 + 0x220);
              cVar5 = NAN(dVar36) || NAN(dVar35);
              bVar3 = dVar36 == dVar35;
              cVar4 = dVar36 < dVar35;
              if (!bVar3) goto LAB_2519b09cc;
              if (bVar7) goto LAB_2519b0a10;
            }
            else {
LAB_2519b09cc:
              _OUTLINED_FUNCTION_13();
              if ((bVar3 || cVar4 != cVar5) &&
                 ((extraout_w8_11 != -1 || (iVar11 = _OUTLINED_FUNCTION_10(), iVar11 != 0)))) {
                _OUTLINED_FUNCTION_8();
                _OUTLINED_FUNCTION_12();
              }
              *(double *)(lVar12 + 0x218) = dVar38;
              *(double *)(lVar12 + 0x220) = (double)iVar9;
            }
            unaff_x28 = 1;
          }
          else if (*(char *)(lVar12 + 0x3c7) == '\0') {
            _OUTLINED_FUNCTION_14();
            if ((bool)uVar6 || cVar5 != cVar4) {
              if (extraout_w8_03 == -1) {
                _OUTLINED_FUNCTION_11();
                uVar18 = _OUTLINED_FUNCTION_24();
                iVar9 = func_0x000258101e40(uVar18,extraout_w8_04 + 0x32);
                if (iVar9 == 0) goto LAB_2519b0a10;
              }
              _OUTLINED_FUNCTION_8();
              auVar39 = _OUTLINED_FUNCTION_24();
              func_0x000258101eb0(auVar39._0_8_,auVar39._8_8_,extraout_w8_05 + 0x32);
            }
          }
          else {
            iVar9 = func_0x00025810ebb0(lVar14,*(undefined8 *)(lVar12 + 0x210));
            if (iVar9 == 0) {
              uVar18 = func_0x00025810c520(lVar14);
              _OUTLINED_FUNCTION_13();
              if (((bool)uVar6 || cVar5 != cVar4) &&
                 ((extraout_w8_02 != -1 || (iVar9 = _OUTLINED_FUNCTION_10(), iVar9 != 0)))) {
                _OUTLINED_FUNCTION_8();
                _OUTLINED_FUNCTION_12();
              }
              lVar19 = *(long *)(lVar12 + 0x210);
              *(long *)(lVar12 + 0x210) = lVar14;
              func_0x0002580f6a60(lVar14);
              if (lVar19 != 0) {
                func_0x0002580f5830(lVar19);
              }
              *(double *)(lVar12 + 0x218) = (double)(int)uVar18;
              *(double *)(lVar12 + 0x220) = (double)(int)((ulong)uVar18 >> 0x20);
              unaff_x28 = 1;
            }
          }
        }
LAB_2519b0a10:
        auVar39 = func_0x00025810ad50(lVar13,0);
        if (auVar39._0_8_ == 0) {
          local_d0 = local_d0 & 0xffffffffffffff00;
          auVar40._8_8_ = 0;
          auVar40._0_8_ = auVar39._8_8_;
          auVar40 = auVar40 << 0x40;
LAB_2519b0a88:
          bVar7 = true;
        }
        else {
          auVar40 = func_0x0002581017d0();
          lVar14 = auVar40._0_8_;
          local_d0 = local_d0 & 0xffffffffffffff00;
          if (lVar14 < 1) goto LAB_2519b0a88;
          lVar19 = 0;
          uVar18 = *_DAT_2680d4600;
          do {
            uVar21 = func_0x0002581017e0(auVar39._0_8_,lVar19);
            auVar40 = func_0x00025810b040(uVar21,uVar18,&local_d0);
            if (auVar40._0_4_ != 0) break;
            bVar7 = lVar14 + -1 != lVar19;
            lVar19 = lVar19 + 1;
          } while (bVar7);
          bVar7 = (char)local_d0 == '\0';
        }
        uVar18 = auVar40._0_8_;
        *(bool *)(lVar12 + 0x45d) = bVar7;
        if (_gLogCategory_APEndpointStreamScreen < 0x15) {
          if (_gLogCategory_APEndpointStreamScreen == -1) {
            uVar18 = _OUTLINED_FUNCTION_24();
            _OUTLINED_FUNCTION_11(uVar18,extraout_w8_12 + -0x14);
            auVar40 = func_0x000258101e40();
            uVar18 = auVar40._0_8_;
            if (auVar40._0_4_ == 0) goto LAB_2519b0b08;
          }
          uVar18 = _OUTLINED_FUNCTION_11(auVar40._0_8_,auVar40._8_8_,0x2000014);
          uVar18 = func_0x000258101eb0(uVar18,
                                       "void sbpd_updateKeyFrameStatus(SBufProcessingData *, CMSampleBufferRef)"
                                      );
        }
LAB_2519b0b08:
        lVar14 = _OUTLINED_FUNCTION_47(uVar18,_kAPSampleBufferAttachmentKey_ClearScreen);
        lVar19 = *plVar2;
        if ((bool)*(char *)(lVar12 + 0x26c) != (lVar14 == lVar19)) {
          *(bool *)(lVar12 + 0x26c) = lVar14 == lVar19;
          unaff_x28 = 1;
        }
        lVar14 = _OUTLINED_FUNCTION_47(lVar14,_kAPSampleBufferAttachmentKey_InterestingFrame);
        *(bool *)(lVar12 + 0x45c) = lVar14 == lVar19;
        lVar14 = _OUTLINED_FUNCTION_47(lVar14,_kAPSampleBufferAttachmentKey_SubmitSurfaceTimestamp);
        lVar19 = _OUTLINED_FUNCTION_47(lVar14,_kAPSampleBufferAttachmentKey_Timestamps);
        *(undefined4 *)(lVar12 + 0x458) = 0;
        *(undefined8 *)(lVar12 + 0x3e0) = 0;
        if (lVar14 != 0) {
          lVar20 = func_0x0002580f6a50(lVar14);
          lVar22 = func_0x000258101850();
          if (lVar20 == lVar22) {
            func_0x0002580f59b0(lVar14,4,lVar12 + 0x3e0);
          }
        }
        if (lVar19 != 0) {
          lVar14 = func_0x0002580f6a50(lVar19);
          lVar20 = func_0x000258106470();
          if (lVar14 == lVar20) {
            uVar10 = func_0x0002581017d0(lVar19);
            puVar31 = (undefined8 *)(lVar12 + 1000);
            if ((int)uVar10 < 1) {
              uVar18 = func_0x0002580f7510();
              *puVar31 = uVar18;
              uVar10 = 1;
LAB_2519b0c7c:
              uVar25 = uVar10 + 1;
              puVar31[uVar10] = uVar18;
            }
            else {
              uVar16 = 0;
              uVar25 = uVar10;
              if (0xd < uVar10) {
                uVar25 = 0xe;
              }
              uVar33 = (ulong)uVar25;
              do {
                uVar18 = func_0x0002581017e0(lVar19,uVar16);
                uVar18 = func_0x00025810a7d0(uVar18,0);
                puVar31[uVar16] = uVar18;
                uVar16 = uVar16 + 1;
              } while (uVar33 != uVar16);
              lVar14 = 0;
              uVar16 = uVar33;
              do {
                uVar16 = uVar16 - 1;
                lVar19 = puVar31[lVar14];
                if (lVar19 != 0) break;
                lVar14 = lVar14 + 1;
              } while (uVar16 != 0);
              lVar14 = 0;
              uVar16 = uVar33;
              do {
                if (puVar31[lVar14] != 0) {
                  lVar19 = puVar31[lVar14];
                }
                puVar31[lVar14] = lVar19;
                lVar14 = lVar14 + 1;
                uVar16 = uVar16 - 1;
              } while (uVar16 != 0);
              uVar18 = func_0x0002580f7510();
              if (uVar10 < 0xe) {
                puVar31[uVar33] = uVar18;
                if (uVar10 != 0xd) {
                  uVar10 = uVar25 + 1;
                  goto LAB_2519b0c7c;
                }
                uVar25 = 0xe;
              }
            }
            *(uint *)(lVar12 + 0x458) = uVar25;
          }
        }
        func_0x00025810c490(&local_d0,lVar13);
        uVar18 = func_0x00025810eba0(&local_d0);
        *(undefined8 *)(lVar12 + 0x3d8) = uVar18;
        if (*(char *)(lVar12 + 0x3ca) == '\0') {
          pcVar23 = (char *)0x0;
        }
        else {
          pcVar23 = (char *)_OUTLINED_FUNCTION_47(uVar18,&cfstringStruct_27613fe30);
        }
        puVar30 = _DAT_2680d45d0;
        iVar8 = (int)uVar26 + iVar8;
        puVar31 = (undefined8 *)0x27097b000;
        if (*(char *)(lVar12 + 0x3cb) == '\0') {
          in_OV = SCARRY8(DAT_27097be50,1);
          in_NG = DAT_27097be50 + 1 < 0;
          in_ZR = DAT_27097be50 == -1;
          if (!(bool)in_ZR) {
            _OUTLINED_FUNCTION_56();
          }
          if (__MergedGlobals != '\0') goto LAB_2519b0cf4;
          lVar19 = 0;
        }
        else {
LAB_2519b0cf4:
          lVar19 = func_0x00025810ad50(lVar13,0);
          lVar14 = 0;
          if (lVar19 != 0) {
            lVar14 = func_0x0002581017d0(lVar19);
            if (lVar14 < 1) {
              lVar14 = 0;
            }
            else {
              uVar26 = func_0x0002581017e0(lVar19,0);
              lVar14 = func_0x00025810b0c0(uVar26,*puVar30);
            }
          }
          cVar4 = SCARRY8(DAT_27097be50,1);
          cVar5 = DAT_27097be50 + 1 < 0;
          uVar6 = DAT_27097be50 == -1;
          if (!(bool)uVar6) {
            _OUTLINED_FUNCTION_56();
          }
          if (((__MergedGlobals != '\0') && (_OUTLINED_FUNCTION_13(), (bool)uVar6 || cVar5 != cVar4)
              ) && ((extraout_w8_13 != -1 || (iVar9 = _OUTLINED_FUNCTION_10(), iVar9 != 0)))) {
            uVar26 = _OUTLINED_FUNCTION_6(*(undefined8 *)(lVar12 + 0x3b0));
            _OUTLINED_FUNCTION_12
                      (uVar26,
                       "OSStatus sbpd_createUserDataBBuf(SBufProcessingData *, CMSampleBufferRef, CMBlockBufferRef *)"
                      );
          }
          in_NG = '\0';
          in_ZR = *(char *)(lVar12 + 0x3cb) == '\0';
          in_OV = '\0';
          lVar19 = 0;
          if (!(bool)in_ZR) {
            lVar19 = lVar14;
          }
        }
        if (pcVar23 != (char *)0x0 || lVar19 != 0) {
          _OUTLINED_FUNCTION_20();
          uVar26 = *extraout_x8_02;
          _OUTLINED_FUNCTION_1();
          lVar14 = func_0x000258101820(uVar26,0);
          func_0x00025810b180(lVar14,&cfstringStruct_27613fe30,pcVar23);
          func_0x00025810b180(lVar14,*puVar30,lVar19);
          lVar19 = func_0x00025810a970(uVar26,lVar14,200,0,0);
          if (lVar19 == 0) {
            func_0x000258109a30(0,"sbpd_createUserDataBBuf",0x43b,0);
            pcVar23 = (char *)0x0;
            local_d8 = 0;
          }
          else {
            _OUTLINED_FUNCTION_100(uVar26,lVar19);
            pcVar23 = (char *)func_0x00025810f290();
            if ((int)pcVar23 != 0) {
              func_0x000258109a30(pcVar23,"sbpd_createUserDataBBuf",0x43e,0);
            }
          }
          if (lVar14 != 0) {
            func_0x0002580f5830(lVar14);
          }
          if (lVar19 != 0) {
            func_0x0002580f5830(lVar19);
          }
          if ((int)pcVar23 == 0) {
            if (local_d8 == 0) {
              iVar9 = 0;
            }
            else {
              iVar9 = func_0x00025810aca0();
              iVar9 = (int)*(undefined8 *)(lVar12 + 0x3a8) + iVar9;
              iVar8 = iVar9 + iVar8;
            }
            goto joined_r0x0002519b0e5c;
          }
          auVar39 = _OUTLINED_FUNCTION_34();
          uVar26 = 0x483;
LAB_2519b14cc:
          func_0x000258109a30(auVar39._0_8_,auVar39._8_8_,uVar26,0);
          puVar15 = puVar31;
          unaff_x26 = pcVar23;
          goto LAB_2519b14d8;
        }
        iVar9 = 0;
        local_d8 = 0;
joined_r0x0002519b0e5c:
        if (((int)unaff_x28 != 0) &&
           (iVar11 = _sbpd_createConfigBBuf(plVar1,&local_a8), iVar11 != 0)) {
          auVar39 = _OUTLINED_FUNCTION_12();
          uVar26 = 0x48d;
          goto LAB_2519b14cc;
        }
        piVar24 = (int *)func_0x0002580f6280(1,0x80,0x73cf7482);
        *piVar24 = iVar8;
        *(undefined1 *)(piVar24 + 1) = 0;
        puVar31 = *(undefined8 **)(lVar12 + 0x3d8);
        lVar19 = *(long *)(lVar12 + 0x3b8);
        uStack_c8 = 0;
        local_c0 = 0;
        local_d0 = 0;
        uVar26 = *(undefined8 *)(lVar12 + 0x3d0);
        lVar14 = func_0x000258109150(uVar26);
        puVar30 = (undefined8 *)(*(long *)(lVar14 + 0x10) + 0x10);
        pcVar29 = (code *)*puVar30;
        if (pcVar29 == (code *)0x0) {
LAB_2519b0f24:
          _OUTLINED_FUNCTION_14();
          if ((bool)in_ZR || in_NG != in_OV) {
            if (extraout_w8_14 == -1) {
              _OUTLINED_FUNCTION_11();
              uVar26 = _OUTLINED_FUNCTION_24();
              iVar8 = func_0x000258101e40(uVar26,extraout_w8_15 + 0x32);
              if (iVar8 == 0) goto LAB_2519b0f70;
            }
            uVar26 = _OUTLINED_FUNCTION_11();
            auVar39 = _OUTLINED_FUNCTION_24
                                (uVar26,
                                 "APSNetworkTime sbpd_convertFrameTimestampToNetworkTime(SBufProcessingData *, uint64_t)"
                                );
            func_0x000258101eb0(auVar39._0_8_,auVar39._8_8_,extraout_w8_16 + 0x32);
          }
LAB_2519b0f70:
          uStack_c8 = *(ulong *)(lVar12 + 0x278);
          local_d0 = *(ulong *)(lVar12 + 0x270);
          local_c0 = *(long *)(lVar12 + 0x280);
        }
        else {
          in_OV = SBORROW8((long)pcVar29,(long)pcVar29);
          in_NG = '\0';
          in_ZR = 1;
          if ((pcVar29 == (code *)0x0) ||
             (iVar8 = (*pcVar29)((ulong)puVar30 & 0xffffffffffff | 0xea2e000000000000,uVar26,
                                 (undefined *)(lVar19 + (long)puVar31),&local_d0), iVar8 != 0))
          goto LAB_2519b0f24;
          *(ulong *)(lVar12 + 0x278) = uStack_c8;
          *(ulong *)(lVar12 + 0x270) = local_d0;
          *(ulong *)(lVar12 + 0x280) = local_c0;
        }
        *(ulong *)(piVar24 + 2) = uStack_c8 >> 0x20 | local_c0 << 0x20;
        *(ulong *)(piVar24 + 10) = local_d0;
        *(undefined8 *)(piVar24 + 4) = *(undefined8 *)(lVar12 + 0x3e0);
        piVar24[6] = 0;
        piVar24[7] = iVar9;
        lVar14 = *(long *)(lVar12 + 1000);
        uStack_c8 = 0;
        local_c0 = 0;
        local_d0 = 0;
        unaff_x26 = pcVar23;
        if (lVar14 == 0) {
LAB_2519b1028:
          uVar33 = 0;
          uVar16 = 0;
        }
        else {
          unaff_x26 = *(char **)(lVar12 + 0x3d0);
          lVar19 = func_0x000258109150(unaff_x26);
          puVar30 = (undefined8 *)(*(long *)(lVar19 + 0x10) + 0x10);
          pcVar29 = (code *)*puVar30;
          if (pcVar29 == (code *)0x0) {
            uVar33 = 0;
            uVar16 = 0;
          }
          else {
            if (pcVar29 == (code *)0x0) goto LAB_2519b1028;
            (*pcVar29)((ulong)puVar30 & 0xffffffffffff | 0xea2e000000000000,unaff_x26,lVar14,
                       &local_d0);
            uVar33 = local_c0 & 0xffffffff;
            uVar16 = uStack_c8;
          }
        }
        uVar16 = uVar16 >> 0x20 | uVar33 << 0x20;
        *(ulong *)(piVar24 + 8) = uVar16;
        in_NG = false;
        in_ZR = *(char *)(lVar12 + 0x45c) == '\0';
        in_OV = false;
        bVar28 = 0;
        if (!(bool)in_ZR) {
          bVar28 = 0x80;
        }
        *(byte *)((long)piVar24 + 5) = bVar28;
        if (*(char *)(lVar12 + 0x45d) != '\0') {
          *(byte *)((long)piVar24 + 5) = bVar28 | 0x10;
        }
        *(ulong *)(piVar24 + 0x16) = uVar16;
        if (*(int *)(lVar12 + 0x458) != 0) {
          piVar32 = piVar24 + 0x18;
          lVar14 = 0x60;
          unaff_x26 = 
          "void sbpd_setFrameHeaderTimestamps(const SBufProcessingData *, APScreenProtocolHeader *)"
          ;
          puVar30 = (undefined8 *)0x1;
          do {
            puVar27 = (undefined8 *)(ulong)*(uint *)(lVar12 + 0x458);
            in_OV = SBORROW8((long)puVar30,(long)puVar27);
            in_NG = (long)puVar30 - (long)puVar27 < 0;
            in_ZR = puVar30 == puVar27;
            puVar31 = puVar30;
            if (puVar27 <= puVar30) break;
            unaff_x28 = func_0x00025810bd90(*(long *)(lVar12 + 1000 + (long)puVar30 * 8) -
                                            *(long *)(lVar12 + 1000 + (long)puVar30 * 8 + -8));
            if (0xffff < unaff_x28) {
              _OUTLINED_FUNCTION_19();
              if (extraout_w8_17 < 0x3d) {
                if (extraout_w8_17 == -1) {
                  _OUTLINED_FUNCTION_24();
                  iVar8 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,
                                              extraout_w8_18 + 0x14);
                  if (iVar8 == 0) goto LAB_2519b1110;
                }
                func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                                    "void sbpd_setFrameHeaderTimestamps(const SBufProcessingData *, APScreenProtocolHeader *)"
                                    ,0x200003c,"%@ ### bad timestamp[%d] (> 65 seconds): %llu ms\n")
                ;
              }
LAB_2519b1110:
              unaff_x28 = 0xffff;
            }
            lVar14 = lVar14 + 2;
            *(short *)piVar32 = (short)unaff_x28;
            puVar31 = (undefined8 *)((long)puVar30 + 1);
            piVar32 = (int *)((long)piVar24 + lVar14);
            in_OV = SBORROW8((long)puVar31,0x11);
            in_NG = (long)(puVar30 + -2) < 0;
            in_ZR = puVar31 == (undefined8 *)0x11;
            puVar30 = puVar31;
          } while (!(bool)in_ZR);
        }
        uVar26 = _OUTLINED_FUNCTION_13();
        pcVar23 = (char *)_OUTLINED_FUNCTION_42(uVar26,piVar24);
        if ((int)pcVar23 != 0) {
          func_0x000258109a30(pcVar23,"sbpd_createFrameHeaderBBuf",0x399,0);
          func_0x0002580f4d30(piVar24);
          auVar39 = _OUTLINED_FUNCTION_34();
          uVar26 = 0x491;
          goto LAB_2519b14cc;
        }
        _sbpd_encryptBBuf(plVar1,local_b0,puVar15);
        iVar8 = _OUTLINED_FUNCTION_27();
        if (iVar8 == 0) {
          puVar31 = puVar15;
          if (local_d8 == 0) {
LAB_2519b1178:
            uVar33 = local_a8;
            uVar16 = local_b0;
            if (local_a8 == 0) {
              local_b0 = 0;
              local_a8 = uVar16;
            }
            else {
              _OUTLINED_FUNCTION_100(local_a8,local_b0);
              iVar8 = func_0x00025810eab0();
              uVar16 = uVar33;
              if (iVar8 != 0) {
                auVar39 = _OUTLINED_FUNCTION_12();
                uVar26 = 0x4a3;
                goto LAB_2519b14b0;
              }
            }
            _OUTLINED_FUNCTION_100(uVar16,puVar15);
            unaff_x26 = (char *)func_0x00025810eab0();
            if ((int)unaff_x26 == 0) {
              *(int *)(lVar12 + 0x470) = *(int *)(lVar12 + 0x470) + 1;
              uVar26 = func_0x00025810aca0(uVar16);
              _OUTLINED_FUNCTION_100(0x2b1604b0,uVar26);
              func_0x0002580f5a40();
              local_a8 = 0;
              local_e8 = uVar16;
              goto LAB_2519b11fc;
            }
            auVar39 = _OUTLINED_FUNCTION_34();
            uVar26 = 0x4ab;
          }
          else {
            iVar8 = _sbpd_encryptBBuf(plVar1,local_b0);
            if (iVar8 == 0) {
              _OUTLINED_FUNCTION_100(puVar15,local_d8);
              iVar8 = func_0x00025810eab0();
              if (iVar8 == 0) goto LAB_2519b1178;
              auVar39 = _OUTLINED_FUNCTION_12();
              uVar26 = 0x49e;
            }
            else {
              auVar39 = _OUTLINED_FUNCTION_12();
              uVar26 = 0x49c;
            }
          }
LAB_2519b14b0:
          func_0x000258109a30(auVar39._0_8_,auVar39._8_8_,uVar26,0);
          puVar15 = puVar31;
        }
        else {
          auVar39 = _OUTLINED_FUNCTION_12();
          func_0x000258109a30(auVar39._0_8_,auVar39._8_8_,0x496,0);
        }
      }
      else {
        auVar39 = _OUTLINED_FUNCTION_12();
        func_0x000258109a30(auVar39._0_8_,auVar39._8_8_,0x460,0);
        puVar15 = puVar31;
LAB_2519b14d8:
        _OUTLINED_FUNCTION_27();
      }
LAB_2519b11fc:
      if (local_d8 != 0) {
        func_0x0002580f5830();
      }
      uVar16 = local_a8;
      if (local_b0 != 0) {
        func_0x0002580f5830();
        uVar16 = local_a8;
      }
joined_r0x0002519b0880:
      param_2 = (int)puVar15;
      if (uVar16 != 0) {
        func_0x0002580f5830();
      }
    }
    if ((int)unaff_x26 == 0) {
      lVar14 = func_0x00025810aca0(local_e8);
      func_0x0002580f7510();
      lVar19 = func_0x00025810bda0();
      uVar16 = 0;
      uVar10 = *(uint *)(lVar12 + 0x398);
      uVar33 = (ulong)uVar10;
      *(long *)(lVar12 + 0x468) = *(long *)(lVar12 + 0x468) + lVar14;
      plVar1 = (long *)(lVar12 + 0x298 + (uVar33 & 0xf) * 0x10);
      *plVar1 = lVar19;
      plVar1[1] = lVar14;
      iVar8 = -0x10;
      do {
        plVar1 = (long *)(lVar12 + 0x298 + (ulong)((uint)uVar33 & 0xf) * 0x10);
        if (unaff_x28 < (ulong)(lVar19 - *plVar1)) break;
        uVar16 = plVar1[1] + uVar16;
        uVar33 = (ulong)((uint)uVar33 - 1);
        bVar7 = iVar8 != -1;
        iVar8 = iVar8 + 1;
      } while (bVar7);
      if (0xc34 < uVar16 >> 3) {
        *(long *)(lVar12 + 0x290) = lVar19;
      }
      *(uint *)(lVar12 + 0x398) = uVar10 + 1;
      *param_3 = 0;
      goto joined_r0x0002519b13e4;
    }
    func_0x000258109a30(unaff_x26,"screenstream_dequeueAndProcessSampleBuffer",0x4f6,0);
  }
  else {
    unaff_x26 = (char *)func_0x000258109e90(0xfffee4a1,"send data failed, stream disconnected",
                                            "screenstream_dequeueAndProcessSampleBuffer");
    if ((int)unaff_x26 == 0) {
      return local_e8;
    }
    lVar13 = 0;
  }
  *(undefined1 *)(lVar12 + 0x474) = 1;
  _OUTLINED_FUNCTION_14();
  if ((bool)in_ZR || in_NG != in_OV) {
    _OUTLINED_FUNCTION_32();
    if ((bool)in_ZR) {
      uVar26 = _OUTLINED_FUNCTION_11();
      iVar8 = func_0x000258101e40(uVar26,param_2 + 0x32);
      if (iVar8 == 0) goto LAB_2519b13d0;
    }
    uVar26 = _OUTLINED_FUNCTION_11();
    func_0x000258101eb0(uVar26,
                        "CMBlockBufferRef screenstream_dequeueAndProcessSampleBuffer(void *, OSStatus, OSType *)"
                        ,param_2 + 0x32,"%@ ### sample buffer processing failed, error: %d\n");
  }
LAB_2519b13d0:
  _screenstream_handleFatalError(param_1,unaff_x26,&cfstringStruct_27613fdf0);
joined_r0x0002519b13e4:
  if (lVar13 != 0) {
    func_0x0002580f5830(lVar13);
  }
  return local_e8;
}


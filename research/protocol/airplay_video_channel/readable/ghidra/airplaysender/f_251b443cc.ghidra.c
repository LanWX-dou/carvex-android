/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b443cc
 * original code SHA256: 8bffbec0c33fa30cb8200298f469c32633a8b099aad6631607ab1aad256faa81
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000251b44478) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _screenstream_initDisplayInfo(undefined1 param_1 [16],undefined8 param_2,long param_3)

{
  undefined1 auVar1 [16];
  undefined1 (*pauVar2) [16];
  bool bVar3;
  char cVar4;
  int iVar5;
  undefined8 uVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  byte bVar10;
  char cVar11;
  code *pcVar12;
  undefined8 *puVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  long *plVar16;
  undefined8 uVar17;
  double dVar18;
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  double dVar21;
  double dVar22;
  undefined8 local_f8;
  undefined8 local_f0;
  code *local_e8;
  undefined *puStack_e0;
  long local_d8;
  long lStack_d0;
  long local_c8;
  ulong local_c0;
  long local_b8;
  long local_b0;
  long local_a8;
  long local_a0;
  long local_98;
  long local_90;
  long local_88;
  long local_80;
  long local_78;
  
  uVar14 = *(undefined8 *)(param_3 + 0x48);
  local_80 = 0;
  local_78 = 0;
  local_90 = 0;
  local_88 = 0;
  local_a0 = 0;
  local_98 = 0;
  local_b0 = 0;
  local_a8 = 0;
  local_b8 = 0;
  auVar19 = func_0x00025810d280();
  if (*(long *)(param_3 + 0x130) != 0) {
    func_0x0002580f5830();
    *(undefined8 *)(param_3 + 0x130) = 0;
  }
  uVar6 = _APEndpointDescriptionGetCMBaseObject(*(undefined8 *)(param_3 + 0x38));
  lVar7 = func_0x000258109150();
  puVar13 = (undefined8 *)(*(long *)(lVar7 + 8) + 0x30);
  pcVar12 = (code *)*puVar13;
  if ((pcVar12 == (code *)0x0) || (pcVar12 == (code *)0x0)) {
    uVar8 = 0xffffce12;
  }
  else {
    uVar15 = *_DAT_2680d3150;
    uVar8 = (*pcVar12)((ulong)puVar13 & 0xffffffffffff | 0x9725000000000000,uVar6,
                       _kAPEndpointDescriptionProperty_Name,uVar15,param_3 + 0x130);
    if ((int)uVar8 == 0) {
      plVar16 = (long *)(param_3 + 0xd0);
      if (*plVar16 != 0) {
        func_0x0002580f5830();
        *plVar16 = 0;
      }
      uVar8 = _APEndpointDisplayDescriptionCopyProperty
                        (uVar14,_kAPEndpointDisplayDescriptionProperty_EDID,uVar15,plVar16);
      if ((int)uVar8 != 0) {
        _screenstream_initDisplayInfo_cold_1();
        goto LAB_251b44d98;
      }
      uVar8 = _APEndpointDisplayDescriptionCopyProperty
                        (uVar14,_kAPEndpointDisplayDescriptionProperty_PixelSize,uVar15,&local_78);
      if ((int)uVar8 != 0) {
        _screenstream_initDisplayInfo_cold_2();
        goto LAB_251b44d98;
      }
      func_0x00025810ac10(local_78,param_3 + 0xd8);
      if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
         ((_gLogCategory_APEndpointStreamScreen != -1 ||
          (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028), iVar5 != 0)
          ))) {
        _screenstream_initDisplayInfo_cold_3(param_3,param_3 + 0xd8);
      }
      pauVar2 = _DAT_2680d3700;
      dVar18 = *(double *)(param_3 + 0xd8);
      if (*(char *)(param_3 + 0x183) == '\0') {
        dVar21 = *(double *)(param_3 + 0xe0);
        dVar22 = dVar18;
        if (dVar21 <= dVar18) {
          dVar22 = dVar21;
        }
        if (dVar22 < DAT_251c6bac8) {
          if (dVar22 <= 0.0) {
            dVar18 = 1280.0;
            dVar21 = DAT_251c6bac8;
          }
          else {
            dVar18 = dVar18 * (DAT_251c6bac8 / dVar22);
            dVar21 = dVar21 * (DAT_251c6bac8 / dVar22);
          }
        }
        *(double *)(param_3 + 0xd8) = dVar18;
        *(double *)(param_3 + 0xe0) = dVar21;
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "OSStatus screenstream_initDisplayInfo(StreamScreenStorage *)",
                              0x2000028,"%@ sanitized display size: %.1f x %.1f\n");
        }
LAB_251b4467c:
        auVar1 = *pauVar2;
        *(long *)(param_3 + 0x100) = auVar1._8_8_;
        *(long *)(param_3 + 0xf8) = auVar1._0_8_;
        if (*(char *)(param_3 + 0x174) != '\0') {
          uVar8 = _APEndpointDisplayDescriptionCopyProperty
                            (uVar14,_kAPEndpointDisplayDescriptionProperty_PixelSizeMax,uVar15,
                             &local_80);
          if ((int)uVar8 != 0) {
            _screenstream_initDisplayInfo_cold_6();
            goto LAB_251b44d98;
          }
          func_0x00025810ac10(local_80,param_3 + 0xf8);
        }
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          _screenstream_initDisplayInfo_cold_7(param_3,param_3 + 0xf8);
        }
        auVar20 = *(undefined1 (*) [16])(param_3 + 0xf8);
        auVar1._8_8_ = -(ulong)(*(double *)(param_3 + 0xe0) < auVar20._8_8_);
        auVar1._0_8_ = -(ulong)(*(double *)*(undefined1 (*) [16])(param_3 + 0xd8) < auVar20._0_8_);
        auVar20 = auVar20 ^ (auVar20 ^ *(undefined1 (*) [16])(param_3 + 0xd8)) & ~auVar1;
        dVar21 = auVar20._8_8_;
        *(double *)(param_3 + 0x100) = dVar21;
        dVar18 = auVar20._0_8_;
        *(double *)(param_3 + 0xf8) = dVar18;
        if ((1920.0 < dVar18) || (DAT_251c6bad0 < dVar21)) {
          iVar5 = func_0x00025810efd0();
          if ((iVar5 == 0) || (iVar5 = func_0x00025810d570(), iVar5 == 0)) {
            *(long *)(param_3 + 0x100) = SUB168(*(undefined1 (*) [16])(param_3 + 0xd8),8);
            *(long *)(param_3 + 0xf8) = SUB168(*(undefined1 (*) [16])(param_3 + 0xd8),0);
          }
          else {
            *(undefined1 *)(param_3 + 0x17a) = 1;
            if (*(char *)(param_3 + 0x183) == '\0') {
              auVar20._0_8_ = *(ulong *)(param_3 + 0xf8);
              auVar20._8_8_ = 0;
              uVar6 = *(undefined8 *)(param_3 + 0x100);
              auVar19 = func_0x00025810c320(auVar20,uVar6,auVar19._0_8_,param_2);
              *(long *)(param_3 + 0xf8) = auVar19._0_8_;
              *(undefined8 *)(param_3 + 0x100) = uVar6;
            }
          }
        }
        if ((_gLogCategory_APEndpointStreamScreen < 0x29) &&
           ((_gLogCategory_APEndpointStreamScreen != -1 ||
            (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
            iVar5 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                              "OSStatus screenstream_initDisplayInfo(StreamScreenStorage *)",
                              0x2000028,"%@ sanitized display size max: %.1f x %.1f\n");
        }
        uVar8 = _APEndpointDisplayDescriptionCopyProperty
                          (uVar14,_kAPEndpointDisplayDescriptionProperty_PhysicalSize,uVar15,
                           &local_88);
        if ((int)uVar8 == 0) {
          func_0x00025810ac10(local_88,param_3 + 0x108);
          if (*(long *)(param_3 + 0x138) != 0) {
            func_0x0002580f5830();
            *(undefined8 *)(param_3 + 0x138) = 0;
          }
          if (*(char *)(param_3 + 0x182) == '\0') {
            uVar8 = _APEndpointDisplayDescriptionCopyProperty
                              (uVar14,_kAPEndpointDisplayDescriptionProperty_UUID,uVar15,
                               param_3 + 0x138);
            if ((int)uVar8 != 0) {
              _screenstream_initDisplayInfo_cold_9();
              goto LAB_251b44d98;
            }
          }
          else {
            uVar6 = func_0x00025810ef90(0);
            *(undefined8 *)(param_3 + 0x138) = uVar6;
          }
          if (*(long *)(param_3 + 0x140) != 0) {
            func_0x0002580f5830();
            *(undefined8 *)(param_3 + 0x140) = 0;
          }
          if ((*(char *)(param_3 + 0x175) == '\0') ||
             (uVar8 = _APEndpointDisplayDescriptionCopyProperty
                                (uVar14,_kAPEndpointDisplayDescriptionProperty_HDRInfo,uVar15,
                                 param_3 + 0x140), (int)uVar8 == 0)) {
            _screenstream_setIsHDR(param_3);
            if (*(long *)(param_3 + 0x90) == 0) {
              bVar3 = true;
            }
            else {
              local_c0 = 0;
              uVar17 = *_DAT_2680eb788;
              uVar6 = func_0x00025810f810();
              _CMBaseObjectCopyProperty(uVar6,uVar17,uVar15,&local_c0);
              iVar5 = func_0x00025810b1a0(local_c0,&cfstringStruct_2761400f0);
              if (local_c0 != 0) {
                func_0x0002580f5830();
              }
              bVar3 = iVar5 != 0;
            }
            iVar5 = func_0x00025810d570();
            if (iVar5 == 0) {
              bVar10 = 0;
            }
            else {
              bVar10 = *(char *)(param_3 + 0x170) != '\0' & bVar3;
            }
            *(byte *)(param_3 + 0x179) = bVar10;
            _APEndpointDisplayDescriptionCopyProperty
                      (uVar14,_kAPEndpointDisplayDescriptionProperty_ReceiverSupports444,uVar15,
                       &local_a8);
            lVar7 = *_DAT_2680d3198;
            cVar4 = func_0x00025810b2f0(&cfstringStruct_276133c90,&cfstringStruct_27612dcf0,
                                        local_a8 == lVar7);
            bVar3 = false;
            *(char *)(param_3 + 0x150) = cVar4;
            cVar11 = *(char *)(param_3 + 0x191);
            if ((cVar11 != '\0') && (cVar4 != '\0')) {
              iVar5 = func_0x00025810efd0();
              if (iVar5 == 0) {
                iVar5 = func_0x00025810efb0();
                bVar3 = iVar5 != 0;
              }
              else {
                bVar3 = true;
              }
              cVar11 = *(char *)(param_3 + 0x191);
            }
            *(bool *)(param_3 + 0x192) = bVar3;
            if (((cVar11 != '\0') && (_gLogCategory_APEndpointStreamScreen < 0x29)) &&
               ((_gLogCategory_APEndpointStreamScreen != -1 ||
                (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028),
                iVar5 != 0)))) {
              func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                                  "OSStatus screenstream_initDisplayInfo(StreamScreenStorage *)",
                                  0x2000028,"%@ %s session\n");
            }
            func_0x00025810f5f0();
            uVar6 = func_0x0002581026d0(uVar15,0,&cfstringStruct_276131890);
            *(undefined8 *)(param_3 + 0x50) = uVar6;
            _APEndpointDisplayDescriptionCopyProperty
                      (uVar14,_kAPEndpointDisplayDescriptionProperty_MaxFPS,uVar15,&local_90);
            if (((local_90 != 0) && (iVar5 = func_0x00025810a7d0(local_90,0), 0 < iVar5)) &&
               (iVar5 < *(int *)(param_3 + 0x1d0))) {
              *(int *)(param_3 + 0x1d0) = iVar5;
            }
            _APEndpointDisplayDescriptionCopyProperty
                      (uVar14,_kAPEndpointDisplayDescriptionProperty_IsOverscanned,uVar15,&local_98)
            ;
            *(bool *)(param_3 + 0x171) = local_98 == lVar7;
            _APEndpointDisplayDescriptionCopyProperty
                      (uVar14,_kAPEndpointDisplayDescriptionProperty_SupportsRotation,uVar15,
                       &local_a0);
            *(bool *)(param_3 + 0x172) = local_a0 == lVar7;
            *(double *)(param_3 + 0x160) =
                 *(double *)(param_3 + 0xd8) * *(double *)(param_3 + 0xe0) *
                 (double)*(int *)(param_3 + 0x1d0);
            if (*(char *)(param_3 + 0x183) != '\0') {
              local_c8 = 0;
              local_c0 = 0;
              lVar9 = func_0x000258101820(uVar15,0,_DAT_2680d3340,_DAT_2680d3358);
              if (*(long *)(param_3 + 0x138) != 0) {
                func_0x0002580f7000(lVar9,&cfstringStruct_276131cf0);
              }
              _APEndpointDisplayDescriptionCopyProperty
                        (uVar14,_kAPEndpointDisplayDescriptionProperty_InitialViewArea,uVar15,
                         &local_c0);
              if (local_c0 != 0) {
                func_0x0002580f7000(lVar9,&cfstringStruct_2761372b0);
              }
              _APEndpointDisplayDescriptionCopyProperty
                        (uVar14,_kAPEndpointDisplayDescriptionProperty_AdjacentViewAreas,uVar15,
                         &local_c8);
              if (local_c8 != 0) {
                func_0x0002580f7000(lVar9,&cfstringStruct_276133e90);
              }
              local_f8 = _DAT_2681b4ed0;
              local_f0 = DAT_251c6aff8;
              local_e8 = ___screenstream_initDisplayInfo_block_invoke;
              puStack_e0 = &___block_descriptor_tmp_303;
              local_d8 = param_3;
              lStack_d0 = lVar9;
              func_0x0002580f54f0(&local_e8,*(undefined8 *)(param_3 + 0x1f0),&local_f8);
              if (local_c0 != 0) {
                func_0x0002580f5830();
              }
              if (local_c8 != 0) {
                func_0x0002580f5830();
              }
              if (lVar9 != 0) {
                func_0x0002580f5830(lVar9);
              }
            }
            uVar6 = _kAPEndpointDescriptionProperty_IsThirdPartyTVFamily;
            uVar17 = _APEndpointDescriptionGetCMBaseObject(*(undefined8 *)(param_3 + 0x38));
            _CMBaseObjectCopyProperty(uVar17,uVar6,uVar15,&local_b8);
            *(bool *)(param_3 + 0x180) = local_b8 == lVar7;
            _APEndpointDisplayDescriptionCopyProperty
                      (uVar14,_kAPEndpointDisplayDescriptionProperty_ReceiverSupportsHDRMirroring,
                       uVar15,&local_b0);
            *(bool *)(param_3 + 0x181) = local_b0 == lVar7;
            if ((_gLogCategory_APEndpointStreamScreen < 0x33) &&
               ((_gLogCategory_APEndpointStreamScreen != -1 ||
                (iVar5 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000032),
                iVar5 != 0)))) {
              func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                                  "OSStatus screenstream_initDisplayInfo(StreamScreenStorage *)",
                                  0x2000032,
                                  "%@ endpoint display info: name: %@ (%@), size in pixels: %.1f x %.1f, max size in pixels: %.1f x %.1f, physical size: %.1f x %.1f, UUID: %@, EDID: %s, HDR: %s, max FPS: %d, overscanned: %s, supports rotation: %s, receiver supports 444: %s, is third party TV receiver: %s, receiver supports HDR mirroring: %s, preferredUIScale: %d\n"
                                 );
            }
            if (*(long *)(param_3 + 0x138) == 0) {
              _screenstream_initDisplayInfo_cold_11(param_3,&local_c0);
              uVar8 = local_c0 & 0xffffffff;
            }
            else {
              uVar8 = 0;
            }
          }
          else {
            _screenstream_initDisplayInfo_cold_10();
          }
        }
        else {
          _screenstream_initDisplayInfo_cold_8();
        }
      }
      else {
        if ((dVar18 <= 0.0) || (*(double *)(param_3 + 0xe0) <= 0.0)) {
          _screenstream_initDisplayInfo_cold_5();
        }
        else {
          if (((*(double *)(param_3 + 0x108) == *(double *)*_DAT_2680d3700) &&
              (*(double *)(param_3 + 0x110) == *(double *)(*_DAT_2680d3700 + 8))) ||
             ((0.0 < *(double *)(param_3 + 0x108) && (0.0 < *(double *)(param_3 + 0x110)))))
          goto LAB_251b4467c;
          _screenstream_initDisplayInfo_cold_4();
        }
        uVar8 = 0xffffbe88;
      }
      goto LAB_251b44d98;
    }
  }
  func_0x000258109a30(uVar8,"screenstream_initDisplayInfo",0x680,0);
LAB_251b44d98:
  if (local_78 != 0) {
    func_0x0002580f5830();
  }
  if (local_80 != 0) {
    func_0x0002580f5830();
  }
  if (local_88 != 0) {
    func_0x0002580f5830();
  }
  if (local_90 != 0) {
    func_0x0002580f5830();
  }
  if (local_98 != 0) {
    func_0x0002580f5830();
  }
  if (local_a0 != 0) {
    func_0x0002580f5830();
  }
  if (local_b8 != 0) {
    func_0x0002580f5830();
  }
  if (local_b0 != 0) {
    func_0x0002580f5830();
  }
  if (local_a8 != 0) {
    func_0x0002580f5830();
  }
  return uVar8;
}


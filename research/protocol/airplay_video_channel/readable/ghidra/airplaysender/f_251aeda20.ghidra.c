/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aeda20
 * original code SHA256: 0cc7e507acd3b022841daaaa668307b103a55bbe1784378d7705ee6b0662eabd
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000251aef628) */
/* WARNING: Removing unreachable block (ram,0x000251aef488) */
/* WARNING: Removing unreachable block (ram,0x000251aeea2c) */
/* WARNING: Removing unreachable block (ram,0x000251aef0a4) */
/* WARNING: Removing unreachable block (ram,0x000251aef534) */
/* WARNING: Removing unreachable block (ram,0x000251aef738) */
/* WARNING: Removing unreachable block (ram,0x000251aedb14) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _carEndpoint_setupScreenStreams(undefined8 param_1,undefined8 param_2)

{
  bool bVar1;
  cfstringStruct *pcVar2;
  bool bVar3;
  bool bVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  int iVar14;
  long lVar15;
  long lVar16;
  undefined8 uVar17;
  long lVar18;
  long lVar19;
  undefined8 uVar20;
  long lVar21;
  ulong uVar22;
  undefined8 uVar23;
  long lVar24;
  undefined8 uVar25;
  long lVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  long lVar30;
  undefined8 uVar31;
  undefined8 uVar32;
  undefined8 uVar33;
  undefined8 uVar34;
  undefined8 uVar35;
  undefined8 uVar36;
  undefined8 uVar37;
  undefined8 uVar38;
  undefined8 uVar39;
  undefined8 uVar40;
  undefined8 uVar41;
  undefined8 uVar42;
  undefined8 uVar43;
  undefined8 uVar44;
  undefined8 uVar45;
  undefined8 uVar46;
  undefined8 uVar47;
  undefined8 uVar48;
  undefined8 uVar49;
  undefined8 uVar50;
  undefined8 uVar51;
  undefined8 uVar52;
  undefined8 uVar53;
  undefined8 uVar54;
  undefined8 uVar55;
  undefined8 uVar56;
  undefined8 uVar57;
  undefined8 uVar58;
  undefined8 uVar59;
  code *pcVar60;
  undefined8 uVar61;
  undefined8 *puVar62;
  long lVar63;
  ulong uVar64;
  undefined8 uVar65;
  undefined8 uVar66;
  undefined8 uVar67;
  undefined8 uVar68;
  undefined8 uVar69;
  ulong uVar70;
  undefined8 uVar71;
  undefined8 uVar72;
  undefined1 auVar73 [16];
  long local_4a0;
  long local_320;
  long local_318;
  long local_310;
  long local_308;
  long local_2e8;
  long local_2e0;
  long local_2d8;
  undefined8 local_2d0;
  long local_2c8;
  long local_2c0;
  long local_2b8;
  long local_2b0;
  long local_2a8;
  undefined8 local_2a0;
  code *local_298;
  undefined *local_290;
  undefined8 *local_288;
  undefined8 local_280;
  undefined8 uStack_278;
  undefined8 local_270;
  undefined8 uStack_268;
  undefined8 local_260;
  undefined8 local_258;
  undefined8 uStack_250;
  ulong uStack_248;
  undefined8 uStack_240;
  undefined8 local_238;
  double dStack_230;
  long local_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  double dStack_210;
  long local_208;
  undefined8 local_200;
  undefined8 *local_1f8;
  undefined8 local_1f0;
  undefined4 local_1e8;
  undefined8 local_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 local_1c0;
  undefined8 uStack_1b8;
  undefined8 local_1b0;
  undefined8 local_1a8;
  ulong local_1a0;
  undefined8 uStack_198;
  undefined8 local_190;
  undefined8 local_188;
  ulong local_178;
  long local_170;
  ulong local_168;
  ulong local_160;
  long local_158;
  long local_150;
  long local_148;
  undefined8 local_140;
  undefined8 uStack_138;
  long local_128;
  long local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 local_108;
  ulong local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  double local_e8;
  long local_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  double local_c8;
  long local_b8;
  long local_b0;
  long local_a8;
  ulong local_a0;
  ulong local_98;
  ulong local_90;
  ulong local_88;
  uint local_7c [3];
  
  lVar15 = func_0x00025810ac50();
  local_2c0 = 0;
  local_2c8 = 0;
  local_2d8 = 0;
  local_2d0 = 0;
  local_2e0 = 0;
  lVar16 = func_0x00025810aa80(0,"[%{ptr}]");
  uVar17 = func_0x0002581064f0(param_1);
  lVar18 = func_0x00025810ac50(param_1);
  local_2b0 = 0;
  local_2b8 = 0;
  lVar19 = func_0x0002581017c0(0,0,_DAT_2680d3338);
  if (lVar19 == 0) {
    _carEndpoint_setupScreenStreams_cold_32();
LAB_251aef900:
    local_320 = 0;
LAB_251aef908:
    local_4a0 = 0;
    uVar22 = 0xffffbeaf;
  }
  else {
    uVar20 = _APEndpointDescriptionGetCMBaseObject(*(undefined8 *)(lVar18 + 8));
    lVar21 = func_0x000258109150();
    puVar62 = (undefined8 *)(*(long *)(lVar21 + 8) + 0x30);
    pcVar60 = (code *)*puVar62;
    if ((pcVar60 == (code *)0x0) || (pcVar60 == (code *)0x0)) {
      uVar22 = 0xffffce12;
    }
    else {
      uVar22 = (*pcVar60)((ulong)puVar62 & 0xffffffffffff | 0x9725000000000000,uVar20,
                          _kAPEndpointDescriptionProperty_DisplayDescriptionArray,uVar17,&local_2b0)
      ;
      if ((int)uVar22 == 0) {
        if (local_2b0 == 0) {
          local_320 = func_0x0002581017c0(0,0,_DAT_2680d3338);
          if (local_320 == 0) goto LAB_251aef8fc;
          bVar4 = false;
          local_308 = 0;
        }
        else {
          local_308 = func_0x0002581017d0();
          local_320 = func_0x0002581017c0(0,0,_DAT_2680d3338);
          uVar57 = _kAPEndpointDisplayDescriptionProperty_ZoomFactor;
          uVar25 = _kAPEndpointDisplayDescriptionProperty_PixelSize;
          uVar5 = _kAPEndpointDisplayDescriptionProperty_PhysicalSize;
          uVar20 = _kAPEndpointDisplayDescriptionProperty_ViewAreas;
          if (local_320 == 0) {
LAB_251aef8fc:
            _carEndpoint_setupScreenStreams_cold_31();
            goto LAB_251aef900;
          }
          if (local_308 < 1) {
            bVar4 = false;
          }
          else {
            lVar21 = 0;
            uVar33 = *_DAT_2680d5538;
            uVar65 = *_DAT_2680d5540;
            do {
              uVar23 = func_0x0002581017e0(local_2b0,lVar21);
              local_2a8 = 0;
              local_e0 = 0;
              local_100 = 0;
              local_120 = 0;
              lVar24 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
              lVar63 = lVar24;
              if (lVar24 == 0) {
                _carEndpoint_setupScreenStreams_cold_4();
                lVar24 = 0;
                uVar22 = 0xfffee7ba;
              }
              else {
                uVar22 = _APEndpointDisplayDescriptionCopyProperty(uVar23,uVar5,uVar17,&local_e0);
                if ((int)uVar22 == 0) {
                  if (local_e0 != 0) {
                    func_0x0002580f7000(lVar24,uVar33);
                  }
                  uVar22 = _APEndpointDisplayDescriptionCopyProperty
                                     (uVar23,uVar25,uVar17,&local_2a8);
                  if ((int)uVar22 == 0) {
                    if (local_2a8 != 0) {
                      func_0x0002580f7000(lVar24,uVar65);
                    }
                    uVar22 = _APEndpointDisplayDescriptionCopyProperty
                                       (uVar23,uVar20,uVar17,&local_100);
                    if ((int)uVar22 == 0) {
                      if (local_100 != 0) {
                        func_0x0002580f7000(lVar24,uVar20);
                      }
                      uVar22 = _APEndpointDisplayDescriptionCopyProperty
                                         (uVar23,uVar57,uVar17,&local_120);
                      if (local_120 != 0) {
                        func_0x0002580f7000(lVar24,uVar57);
                      }
                      lVar63 = 0;
                      goto LAB_251aedcc8;
                    }
                    _carEndpoint_setupScreenStreams_cold_3();
                  }
                  else {
                    _carEndpoint_setupScreenStreams_cold_2();
                  }
                }
                else {
                  _carEndpoint_setupScreenStreams_cold_1();
                }
                lVar24 = 0;
              }
LAB_251aedcc8:
              if (local_100 != 0) {
                func_0x0002580f5830();
              }
              if (local_2a8 != 0) {
                func_0x0002580f5830();
              }
              if (local_e0 != 0) {
                func_0x0002580f5830();
              }
              if (lVar63 != 0) {
                func_0x0002580f5830(lVar63);
              }
              if (local_120 != 0) {
                func_0x0002580f5830();
              }
              if ((int)uVar22 != 0) {
                _carEndpoint_setupScreenStreams_cold_5(uVar22);
                local_4a0 = 0;
                goto LAB_251aef020;
              }
              func_0x0002581017b0(local_320,lVar24);
              if (lVar24 != 0) {
                func_0x0002580f5830(lVar24);
              }
              lVar21 = lVar21 + 1;
            } while (local_308 != lVar21);
            bVar4 = true;
          }
        }
        if ((_gLogCategory_APEndpointCarPlay < 0x33) &&
           ((_gLogCategory_APEndpointCarPlay != -1 ||
            (iVar14 = func_0x000258101e40(&_gLogCategory_APEndpointCarPlay,0x2000032), iVar14 != 0))
           )) {
          _carEndpoint_setupScreenStreams_cold_6(local_320);
        }
        iVar14 = _APCarPlay_CRFetchScaledDisplaysForCarDisplayConfiguration
                           (*(undefined8 *)(lVar18 + 0x38),local_320,&local_2b8);
        if ((iVar14 != 0) || (local_2b8 == 0)) {
          lVar21 = func_0x0002581017c0(0,0,_DAT_2680d3338);
          if (lVar21 == 0) {
            _carEndpoint_setupScreenStreams_cold_30();
            goto LAB_251aef908;
          }
          if (bVar4) {
            lVar63 = 0;
            do {
              uVar20 = func_0x0002581017e0(local_320,lVar63);
              func_0x0002581017b0(lVar21,uVar20);
              lVar63 = lVar63 + 1;
            } while (local_308 != lVar63);
          }
          local_2b8 = lVar21;
          if ((_gLogCategory_APEndpointCarPlay < 0x33) &&
             ((_gLogCategory_APEndpointCarPlay != -1 ||
              (iVar14 = func_0x000258101e40(&_gLogCategory_APEndpointCarPlay,0x2000032), iVar14 != 0
              )))) {
            func_0x000258101eb0(&_gLogCategory_APEndpointCarPlay,
                                "OSStatus carEndpoint_copyScreenInfo(FigEndpointRef, CFAllocatorRef, CFArrayRef *, CFMutableDictionaryRef *)"
                                ,0x2000032,
                                "[%{ptr}] Non-scaled Display Characteristics created. err: %#m\n");
          }
        }
        if (*(char *)(lVar18 + 0x48) == '\0') {
LAB_251aee15c:
          local_4a0 = 0;
          uVar20 = DAT_251c6aff0;
          uVar5 = DAT_251c6aff8;
          uVar25 = _kAPEndpointStreamCreationOptionKey_OverrideCanvasSize;
          uVar57 = _kAPEndpointDisplayDescriptionProperty_ApplicationURL;
          uVar33 = _kAPEndpointDisplayDescriptionProperty_InitialApplicationURL;
          uVar65 = _kAPEndpointDisplayDescriptionProperty_UUID;
          uVar23 = _kAPEndpointDisplayDescriptionProperty_ViewAreas;
          uVar58 = _kAPEndpointDisplayDescriptionProperty_MaxFPS;
          uVar59 = _kAPEndpointDisplayDescriptionProperty_IsNightMode;
          uVar66 = _kAPEndpointDisplayDescriptionProperty_IsLimitedUI;
          uVar67 = _kAPEndpointDisplayDescriptionProperty_LimitedUIElements;
          uVar68 = _kAPEndpointDisplayDescriptionProperty_PhysicalSize;
          uVar31 = _kAPEndpointDisplayDescriptionProperty_PixelSize;
          uVar32 = _kAPEndpointDisplayDescriptionProperty_PrimaryInputDevice;
          uVar6 = _kAPEndpointDisplayDescriptionProperty_SupportsKnobInput;
          uVar7 = _kAPEndpointDisplayDescriptionProperty_SupportsLowFidelityTouch;
          uVar8 = _kAPEndpointDisplayDescriptionProperty_SupportsHighFidelityTouch;
          uVar9 = _kAPEndpointDisplayDescriptionProperty_SupportsTouchpadInput;
          uVar10 = _kAPEndpointDisplayDescriptionProperty_SupportsCornerMasks;
          uVar11 = _kAPEndpointDescriptionProperty_IsLimitedUI;
          uVar12 = _kAPEndpointDescriptionProperty_LimitedUIElements;
          uVar13 = _kAPEndpointDescriptionProperty_IsNightMode;
        }
        else {
          local_2a8 = 0;
          iVar14 = _APCarPlay_CRFetchDisplayCornerMasks
                             (*(undefined8 *)(lVar18 + 0x38),local_320,&local_2a8);
          if ((iVar14 != 0) || (local_2a8 == 0)) {
            if ((_gLogCategory_APEndpointCarPlay < 0x5b) &&
               ((_gLogCategory_APEndpointCarPlay != -1 ||
                (iVar14 = func_0x000258101e40(&_gLogCategory_APEndpointCarPlay,0x200005a),
                iVar14 != 0)))) {
              func_0x000258101eb0(&_gLogCategory_APEndpointCarPlay,
                                  "OSStatus carEndpoint_copyScreenInfo(FigEndpointRef, CFAllocatorRef, CFArrayRef *, CFMutableDictionaryRef *)"
                                  ,0x200005a,"[%{ptr}] Failed to fetch DisplayCornerMasks, err = %d"
                                 );
            }
            goto LAB_251aee15c;
          }
          local_4a0 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
          if (local_4a0 != 0) {
            lVar21 = func_0x0002581017d0(local_2a8);
            uVar5 = _kAPEndpointDisplayDescriptionProperty_SupportsCornerMasks;
            uVar20 = _kAPEndpointDisplayDescriptionProperty_UUID;
            bVar1 = (bool)(bVar4 ^ 1);
            if (lVar21 < 1) {
              bVar1 = true;
            }
            if (!bVar1) {
              uVar70 = *_DAT_2680d3188;
              uVar22 = *_DAT_2680d3198;
              lVar63 = *_DAT_2680d3270;
              lVar21 = 1;
              do {
                uVar25 = func_0x0002581017e0(local_2b0,lVar21 + -1);
                local_e0 = 0;
                local_100 = uVar70;
                _APEndpointDisplayDescriptionCopyProperty(uVar25,uVar20,0,&local_e0);
                _APEndpointDisplayDescriptionCopyProperty(uVar25,uVar5,0,&local_100);
                if (local_e0 != 0) {
                  auVar73 = func_0x0002581017e0(local_2a8,lVar21 + -1);
                  lVar30 = auVar73._0_8_;
                  lVar24 = lVar63;
                  if ((local_100 == uVar22 && lVar30 != 0) &&
                     (lVar26 = func_0x0002580f6a40(lVar30,auVar73._8_8_,lVar63), 0 < lVar26)) {
                    lVar24 = lVar30;
                  }
                  func_0x0002580f7000(local_4a0,local_e0,lVar24);
                  if ((_gLogCategory_APEndpointCarPlay < 0x33) &&
                     ((_gLogCategory_APEndpointCarPlay != -1 ||
                      (iVar14 = func_0x000258101e40(&_gLogCategory_APEndpointCarPlay,0x2000032),
                      iVar14 != 0)))) {
                    func_0x000258101eb0(&_gLogCategory_APEndpointCarPlay,
                                        "OSStatus carEndpoint_copyScreenInfo(FigEndpointRef, CFAllocatorRef, CFArrayRef *, CFMutableDictionaryRef *)"
                                        ,0x2000032,
                                        "[%{ptr}] Stored DisplayCornerMask for DisplayUUID: %@");
                  }
                  if (local_e0 != 0) {
                    func_0x0002580f5830();
                  }
                }
                if (local_100 != 0) {
                  func_0x0002580f5830();
                }
                lVar24 = func_0x0002581017d0(local_2a8);
                bVar1 = lVar21 < lVar24;
                bVar3 = lVar21 < local_308;
                lVar21 = lVar21 + 1;
              } while (bVar1 && bVar3);
            }
            if ((_gLogCategory_APEndpointCarPlay < 0x33) &&
               ((_gLogCategory_APEndpointCarPlay != -1 ||
                (iVar14 = func_0x000258101e40(&_gLogCategory_APEndpointCarPlay,0x2000032),
                iVar14 != 0)))) {
              _carEndpoint_setupScreenStreams_cold_7(local_4a0,param_1);
            }
          }
          uVar20 = DAT_251c6aff0;
          uVar5 = DAT_251c6aff8;
          uVar25 = _kAPEndpointStreamCreationOptionKey_OverrideCanvasSize;
          uVar57 = _kAPEndpointDisplayDescriptionProperty_ApplicationURL;
          uVar33 = _kAPEndpointDisplayDescriptionProperty_InitialApplicationURL;
          uVar65 = _kAPEndpointDisplayDescriptionProperty_UUID;
          uVar23 = _kAPEndpointDisplayDescriptionProperty_ViewAreas;
          uVar58 = _kAPEndpointDisplayDescriptionProperty_MaxFPS;
          uVar59 = _kAPEndpointDisplayDescriptionProperty_IsNightMode;
          uVar66 = _kAPEndpointDisplayDescriptionProperty_IsLimitedUI;
          uVar67 = _kAPEndpointDisplayDescriptionProperty_LimitedUIElements;
          uVar68 = _kAPEndpointDisplayDescriptionProperty_PhysicalSize;
          uVar31 = _kAPEndpointDisplayDescriptionProperty_PixelSize;
          uVar32 = _kAPEndpointDisplayDescriptionProperty_PrimaryInputDevice;
          uVar6 = _kAPEndpointDisplayDescriptionProperty_SupportsKnobInput;
          uVar7 = _kAPEndpointDisplayDescriptionProperty_SupportsLowFidelityTouch;
          uVar8 = _kAPEndpointDisplayDescriptionProperty_SupportsHighFidelityTouch;
          uVar9 = _kAPEndpointDisplayDescriptionProperty_SupportsTouchpadInput;
          uVar10 = _kAPEndpointDisplayDescriptionProperty_SupportsCornerMasks;
          uVar11 = _kAPEndpointDescriptionProperty_IsLimitedUI;
          uVar12 = _kAPEndpointDescriptionProperty_LimitedUIElements;
          uVar13 = _kAPEndpointDescriptionProperty_IsNightMode;
          if (local_2a8 != 0) {
            func_0x0002580f5830();
            uVar20 = DAT_251c6aff0;
            uVar5 = DAT_251c6aff8;
            uVar25 = _kAPEndpointStreamCreationOptionKey_OverrideCanvasSize;
            uVar57 = _kAPEndpointDisplayDescriptionProperty_ApplicationURL;
            uVar33 = _kAPEndpointDisplayDescriptionProperty_InitialApplicationURL;
            uVar65 = _kAPEndpointDisplayDescriptionProperty_UUID;
            uVar23 = _kAPEndpointDisplayDescriptionProperty_ViewAreas;
            uVar58 = _kAPEndpointDisplayDescriptionProperty_MaxFPS;
            uVar59 = _kAPEndpointDisplayDescriptionProperty_IsNightMode;
            uVar66 = _kAPEndpointDisplayDescriptionProperty_IsLimitedUI;
            uVar67 = _kAPEndpointDisplayDescriptionProperty_LimitedUIElements;
            uVar68 = _kAPEndpointDisplayDescriptionProperty_PhysicalSize;
            uVar31 = _kAPEndpointDisplayDescriptionProperty_PixelSize;
            uVar32 = _kAPEndpointDisplayDescriptionProperty_PrimaryInputDevice;
            uVar6 = _kAPEndpointDisplayDescriptionProperty_SupportsKnobInput;
            uVar7 = _kAPEndpointDisplayDescriptionProperty_SupportsLowFidelityTouch;
            uVar8 = _kAPEndpointDisplayDescriptionProperty_SupportsHighFidelityTouch;
            uVar9 = _kAPEndpointDisplayDescriptionProperty_SupportsTouchpadInput;
            uVar10 = _kAPEndpointDisplayDescriptionProperty_SupportsCornerMasks;
            uVar11 = _kAPEndpointDescriptionProperty_IsLimitedUI;
            uVar12 = _kAPEndpointDescriptionProperty_LimitedUIElements;
            uVar13 = _kAPEndpointDescriptionProperty_IsNightMode;
          }
        }
        DAT_251c6aff0 = uVar20;
        DAT_251c6aff8 = uVar5;
        _kAPEndpointStreamCreationOptionKey_OverrideCanvasSize = uVar25;
        _kAPEndpointDisplayDescriptionProperty_ApplicationURL = uVar57;
        _kAPEndpointDisplayDescriptionProperty_InitialApplicationURL = uVar33;
        _kAPEndpointDisplayDescriptionProperty_UUID = uVar65;
        _kAPEndpointDisplayDescriptionProperty_ViewAreas = uVar23;
        _kAPEndpointDisplayDescriptionProperty_MaxFPS = uVar58;
        _kAPEndpointDisplayDescriptionProperty_IsNightMode = uVar59;
        _kAPEndpointDisplayDescriptionProperty_IsLimitedUI = uVar66;
        _kAPEndpointDisplayDescriptionProperty_LimitedUIElements = uVar67;
        _kAPEndpointDisplayDescriptionProperty_PhysicalSize = uVar68;
        _kAPEndpointDisplayDescriptionProperty_PixelSize = uVar31;
        _kAPEndpointDisplayDescriptionProperty_PrimaryInputDevice = uVar32;
        _kAPEndpointDisplayDescriptionProperty_SupportsKnobInput = uVar6;
        _kAPEndpointDisplayDescriptionProperty_SupportsLowFidelityTouch = uVar7;
        _kAPEndpointDisplayDescriptionProperty_SupportsHighFidelityTouch = uVar8;
        _kAPEndpointDisplayDescriptionProperty_SupportsTouchpadInput = uVar9;
        _kAPEndpointDisplayDescriptionProperty_SupportsCornerMasks = uVar10;
        _kAPEndpointDescriptionProperty_IsLimitedUI = uVar11;
        _kAPEndpointDescriptionProperty_LimitedUIElements = uVar12;
        _kAPEndpointDescriptionProperty_IsNightMode = uVar13;
        if (bVar4) {
          local_2e8 = 0;
          uVar64 = *_DAT_2680d3188;
          uVar70 = *_DAT_2680d3198;
          uVar34 = *_DAT_2680d5598;
          uVar35 = *_DAT_2680d55a0;
          uVar36 = *_DAT_2680d5590;
          uVar37 = *_DAT_2680d55a8;
          uVar38 = *_DAT_2680d5510;
          uVar39 = *_DAT_2680d5548;
          uVar40 = *_DAT_2680d5500;
          uVar41 = *_DAT_2680d5530;
          uVar42 = *_DAT_2680d5538;
          uVar43 = *_DAT_2680d5540;
          uVar61 = *_DAT_2680d5550;
          uVar44 = *_DAT_2680d5560;
          uVar45 = *_DAT_2680eb6a0;
          uVar46 = *_DAT_2680d5520;
          uVar47 = *_DAT_2680d5518;
          uVar72 = _DAT_2680d3700[1];
          uVar71 = *_DAT_2680d3700;
          uVar48 = *_DAT_2680d5508;
          uVar49 = *_DAT_2680d5578;
          uVar50 = *_DAT_2680d5568;
          uVar51 = *_DAT_2680d5588;
          uVar52 = *_DAT_2680d5580;
          uVar53 = *_DAT_2680d5570;
          uVar54 = *_DAT_2680d5558;
          uVar55 = *_DAT_2680d54f8;
          uVar56 = *_DAT_2680d5528;
          do {
            uVar27 = func_0x0002581017e0(local_2b0,local_2e8);
            uVar28 = func_0x0002581017e0(local_2b8,local_2e8);
            uVar69 = *(undefined8 *)(lVar18 + 8);
            local_7c[0] = 0;
            local_b0 = 0;
            local_a8 = 0;
            local_b8 = 0;
            uStack_d8 = 0;
            local_e0 = 0;
            local_c8 = 0.0;
            local_d0 = 0;
            uStack_f8 = 0;
            local_100 = 0;
            local_e8 = 0.0;
            uStack_f0 = 0;
            uStack_118 = 0;
            local_120 = 0;
            local_108 = 0;
            local_110 = 0;
            local_128 = 0;
            local_148 = 0;
            local_150 = 0;
            local_158 = 0;
            local_170 = 0;
            local_178 = uVar64;
            local_168 = uVar64;
            local_160 = uVar64;
            local_140 = uVar71;
            uStack_138 = uVar72;
            local_a0 = uVar64;
            local_98 = uVar64;
            local_90 = uVar64;
            local_88 = uVar64;
            lVar21 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
            if (lVar21 == 0) {
              _carEndpoint_setupScreenStreams_cold_28(local_7c);
LAB_251aeef28:
              lVar30 = 0;
              lVar63 = 0;
              lVar24 = 0;
              local_318 = 0;
              local_310 = 0;
            }
            else {
              local_310 = func_0x0002581017c0(0,0,_DAT_2680d3338);
              if (local_310 == 0) {
                _carEndpoint_setupScreenStreams_cold_27(local_7c);
                goto LAB_251aeef28;
              }
              local_7c[0] = _APEndpointDisplayDescriptionCopyProperty(uVar27,uVar6,uVar17,&local_88)
              ;
              if (local_7c[0] == 0) {
                if (local_88 == uVar70) {
                  func_0x0002581017b0(local_310,uVar34);
                }
                local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                        (uVar27,uVar7,uVar17,&local_90);
                if (local_7c[0] != 0) {
                  _carEndpoint_setupScreenStreams_cold_9();
                  goto LAB_251aeef78;
                }
                if (local_90 == uVar70) {
                  func_0x0002581017b0(local_310,uVar35);
                }
                local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                        (uVar27,uVar8,uVar17,&local_98);
                if (local_7c[0] != 0) {
                  _carEndpoint_setupScreenStreams_cold_10();
                  goto LAB_251aeef78;
                }
                if (local_98 == uVar70) {
                  func_0x0002581017b0(local_310,uVar36);
                }
                local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                        (uVar27,uVar9,uVar17,&local_a0);
                if (local_7c[0] != 0) {
                  _carEndpoint_setupScreenStreams_cold_11();
                  goto LAB_251aeef78;
                }
                if (local_a0 == uVar70) {
                  func_0x0002581017b0(local_310,uVar37);
                }
                func_0x0002580f7000(lVar21,uVar38,local_310);
                local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                        (uVar27,uVar32,uVar17,&local_148);
                if (local_7c[0] != 0) {
                  _carEndpoint_setupScreenStreams_cold_12();
                  goto LAB_251aeef78;
                }
                iVar14 = func_0x00025810a7d0(local_148,local_7c);
                if (local_7c[0] == 0) {
                  if (iVar14 == 1) {
                    uVar29 = uVar36;
                    if ((local_98 == uVar70) || (uVar29 = uVar35, local_90 == uVar70))
                    goto LAB_251aeeef4;
                  }
                  else {
                    uVar29 = uVar37;
                    uVar22 = local_a0;
                    if (((iVar14 == 2) || (uVar29 = uVar34, uVar22 = local_88, iVar14 == 3)) &&
                       (uVar22 == uVar70)) {
LAB_251aeeef4:
                      func_0x0002580f7000(lVar21,uVar39,uVar29);
                    }
                    else if ((_gLogCategory_APEndpointCarPlay < 0x3d) &&
                            ((_gLogCategory_APEndpointCarPlay != -1 ||
                             (iVar14 = func_0x000258101e40(&_gLogCategory_APEndpointCarPlay,
                                                           0x200003c), iVar14 != 0)))) {
                      func_0x000258101eb0(&_gLogCategory_APEndpointCarPlay,
                                          "OSStatus carEndpoint_copyScreenInfoFromDisplayDescription(FigEndpointRef, Boolean, APEndpointDisplayDescriptionRef, CFDictionaryRef, APEndpointDescriptionRef, CFAllocatorRef, CFDictionaryRef *)"
                                          ,0x200003c,
                                          "[%{ptr}] Primary input device is not a supported input method: %u\n"
                                         );
                    }
                  }
                }
                local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                        (uVar27,uVar65,uVar17,&local_a8);
                if (local_7c[0] != 0) {
                  _carEndpoint_setupScreenStreams_cold_13();
                  goto LAB_251aeef78;
                }
                if (local_a8 != 0) {
                  func_0x0002580f7000(lVar21,uVar40);
                }
                local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                        (uVar27,uVar58,uVar17,&local_b0);
                if (local_7c[0] != 0) {
                  _carEndpoint_setupScreenStreams_cold_14();
                  goto LAB_251aeef78;
                }
                if (local_b0 != 0) {
                  func_0x0002580f7000(lVar21,uVar41);
                }
                local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                        (uVar27,uVar68,uVar17,&local_128);
                if (local_7c[0] != 0) {
                  _carEndpoint_setupScreenStreams_cold_15();
                  goto LAB_251aeef78;
                }
                if (local_128 != 0) {
                  func_0x0002580f7000(lVar21,uVar42);
                  func_0x00025810ac10(local_128,&local_140);
                }
                local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                        (uVar27,uVar31,uVar17,&local_b8);
                if (local_7c[0] != 0) {
                  _carEndpoint_setupScreenStreams_cold_16();
                  goto LAB_251aeef78;
                }
                if (local_b8 == 0) {
                  local_318 = 0;
                }
                else {
                  local_1a0 = CONCAT44(local_1a0._4_4_,2);
                  func_0x0002580f7000(lVar21,uVar43);
                  func_0x00025810ac10(local_b8,&local_d0);
                  uVar29 = func_0x000258102680(uVar28,uVar43);
                  func_0x00025810ac10(uVar29,&uStack_f0);
                  func_0x00025810f310(local_d0,local_c8,local_140,uStack_138,local_d0,local_c8,
                                      local_e8 / local_c8,&local_110);
                  local_318 = func_0x00025810c450(local_110,local_108);
                  func_0x0002580f7000(lVar21,uVar61);
                  func_0x00025810a780(local_e8 / local_c8,lVar21,uVar44);
                  func_0x00025810b090(uVar28,uVar45,&local_1a0);
                  func_0x00025810b140(lVar21,uVar45,local_1a0 & 0xffffffff);
                }
                lVar63 = func_0x00025810b0c0(uVar28,uVar25);
                if (lVar63 != 0) {
                  func_0x00025810b180(lVar21,uVar25,lVar63);
                }
                if (local_2e8 == 0) {
                  lVar63 = func_0x000258109860(uVar69,uVar13,0);
                  uVar22 = uVar64;
                  if (lVar63 != 0) {
                    uVar22 = uVar70;
                  }
                  func_0x0002580f7000(lVar21,uVar46,uVar22);
                  lVar63 = func_0x000258109860(uVar69,uVar11,0);
                  uVar22 = uVar64;
                  if (lVar63 != 0) {
                    uVar22 = uVar70;
                  }
                  func_0x0002580f7000(lVar21,uVar47,uVar22);
                  uVar28 = _APEndpointDescriptionGetCMBaseObject(uVar69);
                  lVar63 = func_0x000258109150();
                  puVar62 = (undefined8 *)(*(long *)(lVar63 + 8) + 0x30);
                  pcVar60 = (code *)*puVar62;
                  if ((pcVar60 == (code *)0x0) || (pcVar60 == (code *)0x0)) {
                    local_7c[0] = 0xffffce12;
LAB_251aeeea4:
                    _carEndpoint_setupScreenStreams_cold_26();
                    goto LAB_251aeeea8;
                  }
                  local_7c[0] = (*pcVar60)((ulong)puVar62 & 0xffffffffffff | 0x9725000000000000,
                                           uVar28,uVar12,0,&local_158);
                  if (local_7c[0] != 0) goto LAB_251aeeea4;
                  lVar24 = 0;
                  puVar62 = _DAT_2680d5528;
                  lVar63 = local_158;
                  if (local_158 != 0) {
LAB_251aeea68:
                    func_0x0002580f7000(lVar21,*puVar62,lVar63);
                  }
LAB_251aeea78:
                  uVar28 = func_0x0002581064f0(param_1);
                  lVar30 = func_0x0002581017c0(uVar28,0,_DAT_2680d3338);
                  if (lVar30 == 0) {
                    _carEndpoint_setupScreenStreams_cold_25(local_7c);
LAB_251aeeff8:
                    lVar63 = 0;
                  }
                  else {
                    _APEndpointDisplayDescriptionCopyProperty(uVar27,uVar23,uVar17,&local_150);
                    if ((local_150 != 0) && (lVar63 = func_0x0002581017d0(), lVar63 != 0)) {
                      uStack_1d8 = 0;
                      local_1e0 = 0;
                      uStack_1c8 = 0;
                      uStack_1d0 = 0;
                      local_200 = 0;
                      local_1e8 = 0;
                      local_1f8 = &local_200;
                      local_1f0 = uVar20;
                      func_0x00025810ac10(local_b8,&uStack_1d0);
                      lVar63 = local_150;
                      uVar28 = func_0x0002581017d0(local_150);
                      local_2a8 = _DAT_2681b4ed0;
                      uStack_278 = uStack_1d8;
                      local_280 = local_1e0;
                      uStack_268 = uStack_1c8;
                      local_270 = uStack_1d0;
                      uStack_250 = uStack_138;
                      local_258 = local_140;
                      uStack_240 = uStack_f8;
                      uStack_248 = local_100;
                      uStack_220 = uStack_d8;
                      local_228 = local_e0;
                      dStack_210 = local_c8;
                      uStack_218 = local_d0;
                      local_298 = ___carEndpoint_copyScreenInfoFromDisplayDescription_block_invoke;
                      local_290 = &DAT_2693e9830;
                      dStack_230 = local_e8;
                      local_238 = uStack_f0;
                      local_2a0 = uVar5;
                      local_288 = &local_200;
                      local_260 = param_1;
                      local_208 = lVar30;
                      func_0x00025810a550(lVar63,0,uVar28,&local_2a8);
                      if (*(int *)(local_1f8 + 3) == 0) {
                        func_0x0002580f4ba0(&local_200,8);
                        goto LAB_251aeec8c;
                      }
                      _carEndpoint_setupScreenStreams_cold_23(local_7c,&local_200,&local_1e0);
                      goto LAB_251aeeff8;
                    }
                    uStack_198 = 0;
                    local_1a0 = 0;
                    local_188 = 0;
                    local_190 = 0;
                    uStack_1b8 = 0;
                    local_1c0 = 0;
                    local_1a8 = 0;
                    local_1b0 = 0;
                    func_0x00025810ac10(local_b8,&local_190);
                    func_0x00025810f310(local_190,local_188,local_140,uStack_138,local_190,local_188
                                        ,local_e8 / local_c8,&local_1b0);
                    uVar28 = func_0x00025810ac00(local_1c0,uStack_1b8,local_1b0,local_1a8);
                    uVar69 = func_0x0002581064f0(param_1);
                    lVar63 = func_0x000258101820(uVar69,0,_DAT_2680d3340,_DAT_2680d3358);
                    if (lVar63 == 0) {
                      func_0x000258109a30(0,"carEndpoint_copyScreenInfoFromDisplayDescription",
                                          0x1a4d,0);
                      lVar63 = 0;
                      local_7c[0] = 0xffffbeaf;
                    }
                    else {
                      func_0x0002580f7000(lVar63,uVar49,uVar28);
                      func_0x0002580f7000(lVar63,uVar50,uVar28);
                      func_0x0002580f7000(lVar63,uVar51,uVar64);
                      func_0x0002580f7000(lVar63,uVar52,uVar64);
                      func_0x00025810a790(lVar63,uVar53,0);
                      func_0x0002581017b0(lVar30,lVar63);
                      func_0x0002580f5830(uVar28);
                      func_0x0002580f5830(lVar63);
LAB_251aeec8c:
                      func_0x0002580f7000(lVar21,uVar54,lVar30);
                      local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                              (uVar27,uVar10,uVar17,&local_178);
                      if (local_7c[0] != 0) {
                        _carEndpoint_setupScreenStreams_cold_24();
                        goto LAB_251aeeff8;
                      }
                      iVar14 = func_0x0002580f6a20(local_178);
                      uVar22 = uVar64;
                      if (iVar14 != 0) {
                        uVar22 = uVar70;
                      }
                      func_0x0002580f7000(lVar21,uVar55,uVar22);
                      lVar63 = lVar21;
                      lVar21 = 0;
                    }
                  }
                }
                else {
                  local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                          (uVar27,uVar59,uVar17,&local_160);
                  if (local_7c[0] == 0) {
                    iVar14 = func_0x0002580f6a20(local_160);
                    uVar22 = uVar64;
                    if (iVar14 != 0) {
                      uVar22 = uVar70;
                    }
                    func_0x0002580f7000(lVar21,uVar46,uVar22);
                    local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                            (uVar27,uVar66,uVar17,&local_168);
                    if (local_7c[0] == 0) {
                      iVar14 = func_0x0002580f6a20(local_168);
                      uVar22 = uVar64;
                      if (iVar14 != 0) {
                        uVar22 = uVar70;
                      }
                      func_0x0002580f7000(lVar21,uVar47,uVar22);
                      local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                              (uVar27,uVar67,uVar17,&local_158);
                      if (local_7c[0] == 0) {
                        if (local_158 != 0) {
                          func_0x0002580f7000(lVar21,uVar56);
                        }
                        local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                                (uVar27,uVar33,uVar17,&local_170);
                        if (local_7c[0] == 0) {
                          if (local_170 == 0) {
                            if ((_gLogCategory_APEndpointCarPlay < 0x33) &&
                               ((_gLogCategory_APEndpointCarPlay != -1 ||
                                (iVar14 = func_0x000258101e40(&_gLogCategory_APEndpointCarPlay,
                                                              0x2000032), iVar14 != 0)))) {
                              _carEndpoint_setupScreenStreams_cold_21(param_1);
                            }
                            local_7c[0] = _APEndpointDisplayDescriptionCopyProperty
                                                    (uVar27,uVar57,uVar17,&local_170);
                            if (local_7c[0] != 0) {
                              _carEndpoint_setupScreenStreams_cold_22();
                              goto LAB_251aeeea8;
                            }
                            if (local_170 != 0) goto LAB_251aee94c;
                          }
                          else {
LAB_251aee94c:
                            lVar63 = func_0x000258101890();
                            if ((0 < lVar63) &&
                               (lVar24 = func_0x00025810c420(0,local_170,0), lVar24 != 0)) {
                              func_0x0002580f7000(lVar21,uVar48,lVar24);
                              puVar62 = _DAT_2680d54f0;
                              lVar63 = lVar24;
                              goto LAB_251aeea68;
                            }
                          }
                          lVar24 = 0;
                          goto LAB_251aeea78;
                        }
                        _carEndpoint_setupScreenStreams_cold_20();
                      }
                      else {
                        _carEndpoint_setupScreenStreams_cold_19();
                      }
                    }
                    else {
                      _carEndpoint_setupScreenStreams_cold_18();
                    }
                  }
                  else {
                    _carEndpoint_setupScreenStreams_cold_17();
                  }
LAB_251aeeea8:
                  lVar63 = 0;
                  lVar30 = 0;
                  lVar24 = 0;
                }
              }
              else {
                _carEndpoint_setupScreenStreams_cold_8();
LAB_251aeef78:
                lVar63 = 0;
                lVar30 = 0;
                lVar24 = 0;
                local_318 = 0;
              }
            }
            if (local_170 != 0) {
              func_0x0002580f5830();
            }
            if (lVar24 != 0) {
              func_0x0002580f5830(lVar24);
            }
            if (local_168 != 0) {
              func_0x0002580f5830();
            }
            if (local_160 != 0) {
              func_0x0002580f5830();
            }
            if (local_158 != 0) {
              func_0x0002580f5830();
            }
            if (local_b0 != 0) {
              func_0x0002580f5830();
            }
            if (local_b8 != 0) {
              func_0x0002580f5830();
            }
            if (local_318 != 0) {
              func_0x0002580f5830();
            }
            if (local_128 != 0) {
              func_0x0002580f5830();
            }
            if (local_a8 != 0) {
              func_0x0002580f5830();
            }
            if (local_148 != 0) {
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
            if (local_310 != 0) {
              func_0x0002580f5830();
            }
            if (lVar21 != 0) {
              func_0x0002580f5830(lVar21);
            }
            if (local_150 != 0) {
              func_0x0002580f5830();
            }
            if (local_178 != 0) {
              func_0x0002580f5830();
            }
            if (lVar30 != 0) {
              func_0x0002580f5830(lVar30);
            }
            uVar22 = (ulong)local_7c[0];
            if (local_7c[0] != 0) {
              _carEndpoint_setupScreenStreams_cold_29(uVar22);
              goto LAB_251aef020;
            }
            func_0x0002581017b0(lVar19,lVar63);
            if (lVar63 != 0) {
              func_0x0002580f5830(lVar63);
            }
            local_2e8 = local_2e8 + 1;
          } while (local_308 != local_2e8);
        }
        uVar22 = 0;
        *(long *)(lVar15 + 0x158) = lVar19;
        lVar19 = 0;
        goto LAB_251aef020;
      }
    }
    func_0x000258109a30(uVar22,"carEndpoint_copyScreenInfo",0x1afd,0);
    local_4a0 = 0;
    local_320 = 0;
  }
LAB_251aef020:
  if (local_2b0 != 0) {
    func_0x0002580f5830();
  }
  if (lVar19 != 0) {
    func_0x0002580f5830(lVar19);
  }
  if (local_320 != 0) {
    func_0x0002580f5830();
  }
  if (local_2b8 != 0) {
    func_0x0002580f5830();
  }
  if ((int)uVar22 != 0) {
    _carEndpoint_setupScreenStreams_cold_33(uVar22);
    goto joined_r0x000251aef870;
  }
  uVar17 = _APEndpointDescriptionGetCMBaseObject(*(undefined8 *)(lVar15 + 8));
  lVar18 = func_0x000258109150();
  puVar62 = (undefined8 *)(*(long *)(lVar18 + 8) + 0x30);
  pcVar60 = (code *)*puVar62;
  if ((pcVar60 == (code *)0x0) || (pcVar60 == (code *)0x0)) {
    uVar22 = 0xffffce12;
  }
  else {
    uVar22 = (*pcVar60)((ulong)puVar62 & 0xffffffffffff | 0x9725000000000000,uVar17,
                        _kAPEndpointDescriptionProperty_DisplayDescriptionArray,*_DAT_2680d3150,
                        &local_2c0);
    if ((int)uVar22 == 0) {
      if (local_2c0 == 0) {
LAB_251aef860:
        _carEndpoint_setupScreenStreams_cold_41();
        uVar22 = 0xffffbe88;
      }
      else {
        lVar18 = func_0x0002581017d0();
        uVar5 = _kAPEndpointShowInfoKey_StreamInfo_Screen;
        uVar20 = _kAPEndpointStreamCreationOptionKey_LogPrefix;
        uVar17 = _kAPEndpointStreamCreationOptionKey_OverrideCanvasSize;
        if (lVar18 < 2) {
          if (lVar18 != 1) goto LAB_251aef860;
          lVar18 = 1;
        }
        else if (*(char *)(lVar15 + 0x46) == '\0') {
          lVar18 = 1;
        }
        lVar19 = 0;
        uVar66 = *_DAT_2680d5560;
        uVar25 = *_DAT_2680eb6a0;
        uVar68 = *_DAT_2680d52f0;
        uVar57 = *_DAT_2680d5730;
        uVar33 = *_DAT_2680d5788;
        uVar65 = *_DAT_2680d4be0;
        uVar23 = *_DAT_2680d57d0;
        uVar58 = *_DAT_2680d57c8;
        uVar59 = *_DAT_2680eb730;
        uVar67 = *_DAT_2680eb688;
        do {
          local_100 = local_100 & 0xffffffff00000000;
          local_e0 = 0;
          lVar21 = func_0x000258102650(0,0,param_2);
          if (lVar21 == 0) {
            _carEndpoint_setupScreenStreams_cold_40();
            lVar63 = 0;
LAB_251aef8d4:
            uVar22 = 0xffffbeaf;
            goto joined_r0x000251aef7bc;
          }
          if (lVar19 != 0) {
            func_0x00025810a750(lVar21,&cfstringStruct_27612e5f0);
          }
          func_0x0002580f7000(lVar21,uVar20,lVar16);
          lVar24 = func_0x00025810ac50(param_1);
          local_2a8 = 0x3ff0000000000000;
          lVar30 = func_0x0002581017d0(*(undefined8 *)(lVar24 + 0x158));
          lVar63 = 0x3ff0000000000000;
          if (0 < lVar30) {
            lVar26 = 0;
            do {
              uVar31 = func_0x0002581017e0(*(undefined8 *)(lVar24 + 0x158),lVar26);
              if (lVar19 == lVar26) {
                func_0x00025810b080(uVar31,uVar66,&local_2a8);
                lVar63 = local_2a8;
                break;
              }
              lVar26 = lVar26 + 1;
            } while (lVar30 != lVar26);
          }
          func_0x00025810a780(lVar63,lVar21,uVar66);
          lVar63 = func_0x00025810ac50(param_1);
          lVar24 = func_0x0002581017d0(*(undefined8 *)(lVar63 + 0x158));
          if (0 < lVar24) {
            lVar30 = 0;
            do {
              uVar31 = func_0x0002581017e0(*(undefined8 *)(lVar63 + 0x158),lVar30);
              if (lVar19 == lVar30) {
                iVar14 = func_0x00025810b090(uVar31,uVar25,&local_100);
                if (iVar14 != 0) {
                  func_0x00025810b140(lVar21,uVar25,local_100 & 0xffffffff);
                }
                break;
              }
              lVar30 = lVar30 + 1;
            } while (lVar24 != lVar30);
          }
          lVar63 = func_0x00025810ac50(param_1);
          if (*(long *)(lVar63 + 0x158) == 0) {
            _carEndpoint_setupScreenStreams_cold_35();
          }
          else {
            lVar24 = func_0x0002581017d0();
            if (lVar19 < lVar24) {
              uVar31 = func_0x0002581017e0(*(undefined8 *)(lVar63 + 0x158),lVar19);
              iVar14 = func_0x00025810b0d0(uVar31,uVar68,&local_2d0);
              if (iVar14 != 0) {
                func_0x00025810b180(lVar21,uVar17,local_2d0);
              }
            }
            else {
              _carEndpoint_setupScreenStreams_cold_34();
            }
          }
          uVar31 = func_0x0002581017e0(local_2c0,lVar19);
          uVar32 = func_0x0002581064f0(param_1);
          uVar22 = _APEndpointStreamScreenCreate
                             (uVar32,lVar21,*(undefined8 *)(lVar15 + 0x10),
                              *(undefined8 *)(lVar15 + 0x128),*(undefined8 *)(lVar15 + 8),uVar31,
                              *(undefined8 *)(lVar15 + 0x140),&local_2e0);
          if ((int)uVar22 != 0) {
            _carEndpoint_setupScreenStreams_cold_36();
LAB_251aef7b0:
            lVar63 = 0;
            goto joined_r0x000251aef7bc;
          }
          _carEndpoint_addEndpointStreamNotificationListeners(param_1,local_2e0);
          uVar31 = func_0x00025810f550(local_2e0);
          lVar63 = func_0x000258109150();
          puVar62 = (undefined8 *)(*(long *)(lVar63 + 8) + 0x30);
          pcVar60 = (code *)*puVar62;
          if ((pcVar60 == (code *)0x0) || (pcVar60 == (code *)0x0)) {
            uVar22 = 0xffffce12;
LAB_251aef780:
            uVar17 = 0x218c;
LAB_251aef7a8:
            func_0x000258109a30(uVar22,"carEndpoint_setupScreenStreams",uVar17,0);
            goto LAB_251aef7b0;
          }
          uVar22 = (*pcVar60)((ulong)puVar62 & 0xffffffffffff | 0x9725000000000000,uVar31,uVar57,0,
                              &local_2d8);
          if ((int)uVar22 != 0) goto LAB_251aef780;
          if ((_gLogCategory_APEndpointCarPlay < 0x33) &&
             ((_gLogCategory_APEndpointCarPlay != -1 ||
              (iVar14 = func_0x000258101e40(&_gLogCategory_APEndpointCarPlay,0x2000032), iVar14 != 0
              )))) {
            _carEndpoint_setupScreenStreams_cold_37(lVar15 + 0x45);
          }
          if (*(char *)(lVar15 + 0x45) != '\0') {
            uVar31 = func_0x00025810f550(local_2e0);
            lVar63 = func_0x000258109150();
            puVar62 = (undefined8 *)(*(long *)(lVar63 + 8) + 0x30);
            pcVar60 = (code *)*puVar62;
            if ((pcVar60 == (code *)0x0) || (pcVar60 == (code *)0x0)) {
              uVar22 = 0xffffce12;
            }
            else {
              uVar22 = (*pcVar60)((ulong)puVar62 & 0xffffffffffff | 0x9725000000000000,uVar31,uVar33
                                  ,0,&local_2c8);
              if ((int)uVar22 == 0) {
                _carEndpoint_postNotification
                          (param_1,uVar65,*(undefined4 *)(lVar15 + 0x118),local_2c8);
                goto LAB_251aef56c;
              }
            }
            uVar17 = 0x2194;
            goto LAB_251aef7a8;
          }
LAB_251aef56c:
          iVar14 = func_0x00025810b1a0(local_2d8,uVar23);
          if (iVar14 == 0) {
            iVar14 = func_0x00025810b1a0(local_2d8,uVar58);
            if (iVar14 == 0) {
              lVar63 = 0;
              uVar22 = 0xffffe5b1;
              goto joined_r0x000251aef7bc;
            }
            uVar31 = 0;
            uVar32 = 0;
          }
          else {
            uVar32 = 0xff00001;
            uVar31 = 0xff00000;
          }
          pcVar2 = &cfstringStruct_27613b4f0;
          if (*(char *)(lVar15 + 0x28) != '\0') {
            pcVar2 = &cfstringStruct_27613b4d0;
          }
          lVar63 = _APEndpointCarPlayStreamInfoCreate(local_2e0,uVar5,uVar31,uVar32,pcVar2);
          if (lVar63 == 0) {
            _carEndpoint_setupScreenStreams_cold_39();
            goto LAB_251aef8d4;
          }
          *(long *)(lVar63 + 0x20) = lVar19;
          uVar31 = func_0x00025810f550(local_2e0);
          lVar24 = func_0x000258109150();
          puVar62 = (undefined8 *)(*(long *)(lVar24 + 8) + 0x30);
          pcVar60 = (code *)*puVar62;
          if ((pcVar60 != (code *)0x0) && (pcVar60 != (code *)0x0)) {
            (*pcVar60)((ulong)puVar62 & 0xffffffffffff | 0x9725000000000000,uVar31,uVar59,0,
                       &local_e0);
          }
          if (local_e0 == 0) {
            _carEndpoint_setupScreenStreams_cold_38();
            uVar22 = 0xffffbb3a;
            goto joined_r0x000251aef7bc;
          }
          lVar24 = func_0x000258102680(local_e0,uVar67);
          uVar31 = 0;
          if (lVar24 != 0) {
            uVar31 = func_0x0002580f6a60();
          }
          *(undefined8 *)(lVar63 + 0x28) = uVar31;
          func_0x0002581017b0(*(undefined8 *)(lVar15 + 0x148),lVar63);
          if ((lVar19 != 0) && (*(char *)(lVar15 + 0x48) == '\0')) {
            _carEndpoint_raiseAltScreenPowerAssertionIfNeeded(param_1);
            lVar24 = local_2e0;
            lVar30 = func_0x000258109150(local_2e0);
            puVar62 = (undefined8 *)(*(long *)(lVar30 + 0x10) + 0x10);
            pcVar60 = (code *)*puVar62;
            if ((pcVar60 != (code *)0x0) && (pcVar60 != (code *)0x0)) {
              (*pcVar60)((ulong)puVar62 & 0xffffffffffff | 0x7e61000000000000,lVar24,0,0,0);
            }
          }
          func_0x0002580f5830(lVar21);
          if (local_2e0 != 0) {
            func_0x0002580f5830();
            local_2e0 = 0;
          }
          func_0x0002580f5830(lVar63);
          if (local_2d8 != 0) {
            func_0x0002580f5830();
            local_2d8 = 0;
          }
          if (local_e0 != 0) {
            func_0x0002580f5830();
            local_e0 = 0;
          }
          if (local_2c8 != 0) {
            func_0x0002580f5830();
            local_2c8 = 0;
          }
          lVar19 = lVar19 + 1;
        } while (lVar19 != lVar18);
        lVar15 = func_0x00025810ac50(param_1);
        if ((local_4a0 != 0) && (*(char *)(lVar15 + 0x48) != '\0')) {
          local_2a8 = _DAT_2681b4ed0;
          local_2a0 = DAT_251c6aff8;
          local_298 = ___carEndpoint_updateDisplayCornerMasks_block_invoke;
          local_290 = &___block_descriptor_tmp_878;
          local_288 = (undefined8 *)0x0;
          local_280 = param_1;
          func_0x00025810a640(&local_298,local_4a0,&local_2a8);
        }
        uVar22 = 0;
      }
      goto joined_r0x000251aef870;
    }
  }
  func_0x000258109a30(uVar22,"carEndpoint_setupScreenStreams",0x215c,0);
joined_r0x000251aef870:
  lVar21 = 0;
  lVar63 = 0;
joined_r0x000251aef7bc:
  if (lVar16 != 0) {
    func_0x0002580f5830(lVar16);
  }
  if (lVar21 != 0) {
    func_0x0002580f5830(lVar21);
  }
  if (local_2e0 != 0) {
    func_0x0002580f5830();
  }
  if (lVar63 != 0) {
    func_0x0002580f5830(lVar63);
  }
  if (local_2d8 != 0) {
    func_0x0002580f5830();
  }
  if (local_2c8 != 0) {
    func_0x0002580f5830();
  }
  if (local_2c0 != 0) {
    func_0x0002580f5830();
  }
  if (local_4a0 != 0) {
    func_0x0002580f5830(local_4a0);
  }
  return uVar22;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b371ac
 * original code SHA256: 86e170091c249079f4fc010a8020efdc7be8cce87ad494cef89e694f35790e9f
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251b375d4) */
/* WARNING: Removing unreachable block (ram,0x000251b374e4) */
/* WARNING: Removing unreachable block (ram,0x000251b37398) */
/* WARNING: Removing unreachable block (ram,0x000251b3755c) */
/* WARNING: Removing unreachable block (ram,0x000251b3771c) */
/* WARNING: Removing unreachable block (ram,0x000251b372c0) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_endpoint_setupStreams(long param_1,ulong param_2,ulong param_3,undefined8 param_4,ulong *param_5)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  undefined8 uVar14;
  ulong uVar15;
  uint uVar16;
  code *pcVar17;
  undefined8 *puVar18;
  ulong uVar19;
  undefined8 uVar20;
  uint uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  long local_140;
  undefined8 local_138;
  code *local_130;
  undefined *puStack_128;
  long local_120;
  undefined8 uStack_118;
  long local_110;
  long local_108;
  undefined8 local_100;
  code *local_f8;
  undefined *puStack_f0;
  long local_e8;
  undefined8 *puStack_e0;
  long local_d8;
  long local_d0;
  long local_c8;
  long local_c0;
  ulong local_b8;
  long local_b0;
  long local_a8;
  long local_a0;
  undefined8 local_98;
  code *local_90;
  undefined *puStack_88;
  long local_80;
  
  local_c0 = 0;
  local_b8 = 0;
  local_c8 = 0;
  puVar8 = (undefined8 *)func_0x00025810ac50();
  local_d8 = 0;
  local_d0 = 0;
  if ((_gLogCategory_APEndpoint < 0x33) &&
     ((_gLogCategory_APEndpoint != -1 ||
      (iVar7 = func_0x000258101e40(&_gLogCategory_APEndpoint,0x2000032), iVar7 != 0)))) {
    func_0x000258101eb0(&_gLogCategory_APEndpoint,
                        "OSStatus endpoint_setupStreams(FigEndpointRef, FigEndpointFeatures, FigEndpointFeatures, CFDictionaryRef, FigEndpointFeatures *)"
                        ,0x2000032,"[%{ptr}] setupStreams, features %#ll{flags} -> %#ll{flags}\n");
  }
  uVar23 = *_DAT_2680d3150;
  uVar9 = _APEndpointDescriptionGetCMBaseObject(puVar8[5]);
  lVar10 = func_0x000258109150();
  puVar18 = (undefined8 *)(*(long *)(lVar10 + 8) + 0x30);
  pcVar17 = (code *)*puVar18;
  if ((pcVar17 != (code *)0x0) && (pcVar17 != (code *)0x0)) {
    (*pcVar17)((ulong)puVar18 & 0xffffffffffff | 0x9725000000000000,uVar9,
               _kAPEndpointDescriptionProperty_DeviceID,uVar23,&local_d8);
  }
  if (param_3 == 0) {
    if ((puVar8[0x15] != 0) &&
       (func_0x00025810a650(puVar8[0x15],_endpoint_dissociateStreamsDictionaryEntry,0),
       puVar8[0x15] != 0)) {
      func_0x0002580f5830();
      puVar8[0x15] = 0;
    }
    lVar10 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
    puVar8[0x15] = lVar10;
    if (lVar10 == 0) {
      _endpoint_setupStreams_cold_17();
      uVar9 = 0xffffbeaf;
      goto LAB_251b37b54;
    }
  }
  uVar9 = _endpoint_getSupportedFeatures(param_1,&local_b8);
  if ((int)uVar9 != 0) {
    _endpoint_setupStreams_cold_1();
    goto LAB_251b37b54;
  }
  uVar9 = puVar8[5];
  lVar10 = func_0x000258109150(uVar9);
  puVar18 = (undefined8 *)(*(long *)(lVar10 + 0x10) + 8);
  pcVar17 = (code *)*puVar18;
  if ((pcVar17 == (code *)0x0) || (pcVar17 == (code *)0x0)) {
    uVar9 = 0xffffce12;
  }
  else {
    uVar9 = (*pcVar17)((ulong)puVar18 & 0xffffffffffff | 0xdf60000000000000,uVar9,&local_c0);
    if ((int)uVar9 == 0) {
      if (puVar8[0x1b] == 0) {
        _endpoint_setupStreams_cold_16();
LAB_251b37d74:
        uVar9 = 0xffffbb3a;
      }
      else {
        if (((uint)param_2 >> 1 & 1) == 0) {
          bVar3 = true;
        }
        else {
          iVar7 = func_0x0002581097c0(local_c0,9);
          bVar3 = iVar7 == 0;
        }
        bVar4 = (param_2 & 8) != 0;
        bVar5 = (local_b8 & 8) != 0;
        uVar21 = (uint)param_3;
        uVar1 = uVar21 & 0xff;
        uVar16 = (uint)local_b8;
        uVar2 = 0;
        if ((param_2 & 0x20) != 0) {
          uVar2 = uVar16 >> 5 & 1;
        }
        lVar10 = func_0x00025810a6f0(param_4,_kAPEndpointActivationOptionKey_ForceEnableLLStream,0);
        if (lVar10 != 0) {
          uVar2 = 1;
        }
        bVar6 = false;
        if ((param_3 & 2) == 0) {
          bVar6 = (bool)(bVar3 ^ 1);
        }
        if (((bVar6) || ((bVar5 && bVar4) && (uVar21 >> 3 & 1) == 0)) ||
           (((uVar1 >> 5 & 1) == 0 && (uVar2 != 0)))) {
          lVar11 = func_0x00025810ac50(param_1);
          local_a8 = 0;
          local_a0 = 0;
          local_b0 = 0;
          uVar9 = _APEndpointDescriptionGetCMBaseObject(*(undefined8 *)(lVar11 + 0x28));
          lVar12 = func_0x000258109150();
          puVar18 = (undefined8 *)(*(long *)(lVar12 + 8) + 0x30);
          pcVar17 = (code *)*puVar18;
          if ((pcVar17 == (code *)0x0) || (pcVar17 == (code *)0x0)) {
            uVar9 = 0xffffce12;
LAB_251b377dc:
            uVar22 = 0x14f4;
LAB_251b3781c:
            func_0x000258109a30(uVar9,"endpoint_createAudioOptions",uVar22,0);
            lVar12 = 0;
            lVar13 = 0;
          }
          else {
            uVar9 = (*pcVar17)((ulong)puVar18 & 0xffffffffffff | 0x9725000000000000,uVar9,
                               _kAPEndpointDescriptionProperty_SupportedAudioFormats,uVar23,
                               &local_a0);
            if ((int)uVar9 != 0) goto LAB_251b377dc;
            uVar9 = _APEndpointDescriptionGetCMBaseObject(*(undefined8 *)(lVar11 + 0x28));
            lVar12 = func_0x000258109150();
            puVar18 = (undefined8 *)(*(long *)(lVar12 + 8) + 0x30);
            pcVar17 = (code *)*puVar18;
            if ((pcVar17 == (code *)0x0) || (pcVar17 == (code *)0x0)) {
              uVar9 = 0xffffce12;
LAB_251b377f4:
              uVar22 = 0x14f7;
              goto LAB_251b3781c;
            }
            uVar9 = (*pcVar17)((ulong)puVar18 & 0xffffffffffff | 0x9725000000000000,uVar9,
                               _kAPEndpointDescriptionProperty_IsConnectedOverUSB,uVar23,&local_a8);
            if ((int)uVar9 != 0) goto LAB_251b377f4;
            uVar9 = _APSenderSessionGetCMBaseObject(*(undefined8 *)(lVar11 + 0xe0));
            lVar12 = func_0x000258109150();
            puVar18 = (undefined8 *)(*(long *)(lVar12 + 8) + 0x30);
            pcVar17 = (code *)*puVar18;
            if ((pcVar17 == (code *)0x0) || (pcVar17 == (code *)0x0)) {
              uVar9 = 0xffffce12;
LAB_251b3780c:
              uVar22 = 0x14fa;
              goto LAB_251b3781c;
            }
            uVar9 = (*pcVar17)((ulong)puVar18 & 0xffffffffffff | 0x9725000000000000,uVar9,
                               _kAPSenderSessionProperty_ControlConnectionInterfaceLatencyHint,
                               uVar23,&local_b0);
            if ((int)uVar9 != 0) goto LAB_251b3780c;
            lVar12 = func_0x000258101820(uVar23,0,_DAT_2680d3340,_DAT_2680d3358);
            if (lVar12 == 0) {
              _endpoint_setupStreams_cold_5();
              lVar13 = 0;
LAB_251b37dc0:
              uVar9 = 0xffffbeaf;
            }
            else {
              func_0x0002580f7000(lVar12,
                                  _kAPEndpointSharedContextParsingAudioEngineOption_SupportedAudioFormats
                                  ,local_a0);
              func_0x0002580f7000(lVar12,
                                  _kAPEndpointSharedContextParsingAudioEngineOption_IsConnectedOverUSB
                                  ,local_a8);
              uVar22 = _kAPEndpointSharedContextParsingAudioEngineOption_IsCarPlay;
              lVar13 = func_0x000258109860(*(undefined8 *)(lVar11 + 0x28),
                                           _kAPEndpointDescriptionProperty_IsCarPlay,0);
              uVar20 = *_DAT_2680d3198;
              uVar14 = *_DAT_2680d3188;
              uVar9 = uVar14;
              if (lVar13 != 0) {
                uVar9 = uVar20;
              }
              func_0x0002580f7000(lVar12,uVar22,uVar9);
              func_0x0002580f7000(lVar12,
                                  _kAPEndpointSharedContextParsingAudioEngineOption_ConnectionLatencyHint
                                  ,local_b0);
              uVar9 = _kAPEndpointSharedContextParsingAudioEngineOption_SupportRedundantAudio;
              uVar22 = *(undefined8 *)(lVar11 + 0x28);
              lVar13 = func_0x000258109150(uVar22);
              puVar18 = (undefined8 *)(*(long *)(lVar13 + 0x10) + 0x10);
              pcVar17 = (code *)*puVar18;
              if (((pcVar17 == (code *)0x0) || (pcVar17 == (code *)0x0)) ||
                 (iVar7 = (*pcVar17)((ulong)puVar18 & 0xffffffffffff | 0xdcf2000000000000,uVar22,0xb
                                    ), iVar7 == 0)) {
                uVar20 = uVar14;
              }
              func_0x0002580f7000(lVar12,uVar9,uVar20);
              lVar13 = func_0x000258101820(uVar23,0,_DAT_2680d3340,_DAT_2680d3358);
              if (lVar13 == 0) {
                _endpoint_setupStreams_cold_4();
                goto LAB_251b37dc0;
              }
              if (*(long *)(lVar11 + 0xd8) == 0) {
                _endpoint_setupStreams_cold_3();
                uVar9 = 0xffffbb3a;
              }
              else {
                func_0x0002580f7000(lVar13,_kAPEndpointSharedContextParsingOption_NetworkClock);
                func_0x0002580f7000(lVar13,_kAPEndpointSharedContextParsingOption_AudioEngineOptions
                                    ,lVar12);
                uVar9 = _APEndpointCopyFromActivationOptionsOrCreateSharedContext
                                  (param_4,param_2,lVar13,0,0,&local_c8);
                if ((int)uVar9 != 0) {
                  _endpoint_setupStreams_cold_2(uVar9);
                }
              }
            }
          }
          if (local_a0 != 0) {
            func_0x0002580f5830();
          }
          if (local_a8 != 0) {
            func_0x0002580f5830();
          }
          if (local_b0 != 0) {
            func_0x0002580f5830();
          }
          if (lVar12 != 0) {
            func_0x0002580f5830(lVar12);
          }
          if (lVar13 != 0) {
            func_0x0002580f5830(lVar13);
          }
          if ((int)uVar9 != 0) {
            _endpoint_setupStreams_cold_6(uVar9);
            goto LAB_251b37b54;
          }
        }
        if (!bVar3 && (bVar5 && bVar4)) {
          bVar6 = *(char *)((long)puVar8 + 0x119) == '\0';
          if (!bVar3) goto LAB_251b37880;
LAB_251b37964:
          if ((uVar21 >> 1 & 1) != 0) {
            _markStreamForRemoval(&local_d0,*_DAT_2680d57e0,puVar8[0x15]);
          }
          uVar19 = 0;
          if (bVar5 && bVar4) goto LAB_251b378dc;
LAB_251b37988:
          if ((uVar1 >> 3 & 1) != 0) {
            _markStreamForRemoval(&local_d0,*_DAT_2680d57e8,puVar8[0x15]);
          }
        }
        else {
          bVar6 = false;
          if (bVar3) goto LAB_251b37964;
LAB_251b37880:
          if ((uVar21 >> 1 & 1) == 0) {
            uVar9 = *_DAT_2680d57e0;
            lVar11 = func_0x000258102680(local_c8,uVar9);
            if (lVar11 == 0) {
              _endpoint_setupStreams_cold_8();
              goto LAB_251b37d74;
            }
            uVar22 = func_0x000258102680(lVar11,_kAPEndpointStreamOptions_AudioEngineVendor);
            uVar9 = _endpoint_setupAudioStream(param_1,bVar6,0,0,uVar22,0,uVar9);
            if ((int)uVar9 != 0) {
              _endpoint_setupStreams_cold_7();
              goto LAB_251b37b54;
            }
          }
          uVar19 = 2;
          if (!bVar5 || !bVar4) goto LAB_251b37988;
LAB_251b378dc:
          if ((uVar1 >> 3 & 1) == 0) {
            uVar9 = *_DAT_2680d57e8;
            lVar11 = func_0x000258102680(local_c8,uVar9);
            if (lVar11 == 0) {
              _endpoint_setupStreams_cold_11();
              uVar9 = 0xffffbb3a;
              goto LAB_251b37b54;
            }
            uVar22 = func_0x000258102680(lVar11,_kAPEndpointStreamOptions_AudioEngineVendor);
            uVar20 = func_0x000258102680(lVar11,_kAPEndpointStreamOptions_AudioEngineVendorOptions);
            if (bVar6 == false) {
              uVar14 = 0;
            }
            else {
              uVar14 = func_0x000258102680(puVar8[0x15],*_DAT_2680d57e0);
            }
            uVar9 = _endpoint_setupAudioStream(param_1,bVar6,uVar14,0,uVar22,uVar20,uVar9);
            if ((int)uVar9 != 0) {
              _endpoint_setupStreams_cold_9();
              goto LAB_251b37b54;
            }
            if ((_gLogCategory_APEndpoint < 0x33) &&
               ((_gLogCategory_APEndpoint != -1 ||
                (iVar7 = func_0x000258101e40(&_gLogCategory_APEndpoint,0x2000032), iVar7 != 0)))) {
              _endpoint_setupStreams_cold_10(param_1);
            }
            uVar22 = *puVar8;
            uVar9 = func_0x00025810ad10();
            func_0x00025810f2d0(uVar22,uVar9,*_DAT_2680d4b48,param_1,0,0);
          }
          uVar19 = uVar19 | 8;
        }
        if (uVar2 == 0) {
          if ((uVar1 >> 5 & 1) != 0) {
            _markStreamForRemoval(&local_d0,*_DAT_2680d57f0,puVar8[0x15]);
          }
        }
        else {
          if ((uVar1 >> 5 & 1) == 0) {
            uVar9 = *_DAT_2680d57f0;
            lVar11 = func_0x000258102680(local_c8,uVar9);
            if (lVar11 == 0) {
              _endpoint_setupStreams_cold_13();
              goto LAB_251b37d74;
            }
            uVar22 = func_0x000258102680(lVar11,_kAPEndpointStreamOptions_AudioEngineVendor);
            uVar20 = func_0x000258102680(lVar11,_kAPEndpointStreamOptions_AudioEngineVendorOptions);
            uVar9 = _endpoint_setupAudioStream(param_1,0,0,lVar10 != 0,uVar22,uVar20,uVar9);
            if ((int)uVar9 != 0) {
              _endpoint_setupStreams_cold_12();
              goto LAB_251b37b54;
            }
          }
          uVar19 = uVar19 | 0x20;
        }
        if (((param_2 & 1) == 0) || (iVar7 = func_0x0002581097c0(local_c0,7), iVar7 == 0)) {
          if ((param_3 & 1) != 0) {
            _markStreamForRemoval(&local_d0,*_DAT_2680d5800,puVar8[0x15]);
          }
        }
        else {
          if ((param_3 & 1) == 0) {
            uVar9 = _endpoint_setupScreenStream(param_1,param_4);
            if ((int)uVar9 != 0) {
              _endpoint_setupStreams_cold_14();
              goto LAB_251b37b54;
            }
            if ((((*(char *)((long)puVar8 + 0x143) != '\0') &&
                 (iVar7 = _endpoint_setupAuxiliaryScreenStream(param_1,param_4), iVar7 != 0)) &&
                (_gLogCategory_APEndpoint < 0x5b)) &&
               ((_gLogCategory_APEndpoint != -1 ||
                (iVar7 = func_0x000258101e40(&_gLogCategory_APEndpoint,0x200005a), iVar7 != 0)))) {
              _endpoint_setupStreams_cold_15();
            }
          }
          uVar19 = uVar19 | 1;
        }
        uVar9 = 0;
        uVar15 = (ulong)(uVar16 & (uint)param_2);
        *param_5 = uVar19 | uVar15 & 4 | uVar15 & 0x10;
      }
      goto LAB_251b37b54;
    }
  }
  func_0x000258109a30(uVar9,"endpoint_setupStreams",0x1296,0);
LAB_251b37b54:
  lVar10 = local_d0;
  if (local_d0 != 0) {
    uVar22 = puVar8[0x1c];
    lVar11 = func_0x0002581017c0(uVar23,0,_DAT_2680d3338);
    if (lVar11 != 0) {
      local_a0 = _DAT_2681b4ed0;
      local_98 = DAT_251c6b008;
      local_90 = ___endpoint_addStreamDescriptors_block_invoke;
      puStack_88 = &___block_descriptor_40_e15_v24__0r_v8r_v16l;
      local_80 = lVar11;
      func_0x00025810b000(lVar10,&local_a0);
    }
    uVar23 = DAT_251c6b008;
    local_108 = _DAT_2681b4ed0;
    local_100 = DAT_251c6b008;
    local_f8 = ___endpoint_setupStreams_block_invoke;
    puStack_f0 = &___block_descriptor_48_e15_v24__0r_v8r_v16l;
    local_e8 = param_1;
    puStack_e0 = puVar8;
    func_0x00025810b000(&local_f8,lVar10,&local_108);
    func_0x0002580f6a60(uVar22);
    if (param_1 != 0) {
      func_0x0002580f6a60(param_1);
    }
    local_140 = _DAT_2681b4ed0;
    local_138 = uVar23;
    local_130 = ___endpoint_setupStreams_block_invoke_2;
    puStack_128 = &___block_descriptor_56_e5_v8__0l;
    local_120 = lVar11;
    uStack_118 = uVar22;
    local_110 = param_1;
    func_0x0002580f4bb0(puVar8[1],&local_140);
  }
  if (local_c0 != 0) {
    func_0x0002580f5830();
  }
  if (local_c8 != 0) {
    func_0x0002580f5830();
  }
  if (lVar10 != 0) {
    func_0x0002580f5830(lVar10);
  }
  if (local_d8 != 0) {
    func_0x0002580f5830();
  }
  return uVar9;
}


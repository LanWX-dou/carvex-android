/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10006a610
 * original code SHA256: 93f7e6b9ce8d3fe6e736b2e3c779c4d9e2043475bdf248b8c54f0a58c4c29304
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_features_destroyFeatures(long param_1,uint param_2)

{
  uint uVar1;
  undefined8 uVar2;
  int iVar3;
  char *pcVar4;
  ulong uVar5;
  long *plVar6;
  long lVar7;
  undefined *puVar8;
  long lVar9;
  long lVar10;
  code *pcVar11;
  undefined4 uVar12;
  undefined4 local_80;
  uint local_7c;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  
  puVar8 = PTR___os_log_default_10022bbb0;
  if (param_2 == 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x16) {
      if (_logObjectForModule_onceToken != -1) {
        _iap2_features_registerMessageHandlers_cold_6();
        puVar8 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar8 = *(undefined **)(_gLogObjects + 0xa8);
    }
    iVar3 = _os_log_type_enabled(puVar8,0);
    if (iVar3 == 0) goto LAB_10006a72c;
    pcVar4 = _dispatch_queue_get_label((dispatch_queue_t)0x0);
    local_70 = (undefined4)DAT_1001b3090;
    uStack_6c = SUB84(pcVar4,0);
    uStack_68 = (undefined4)((ulong)pcVar4 >> 0x20);
    pcVar4 = "Destroying optional features... currentDispatchQueue: %s";
  }
  else {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x16) {
      if (_logObjectForModule_onceToken != -1) {
        _iap2_features_registerMessageHandlers_cold_6();
        puVar8 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar8 = *(undefined **)(_gLogObjects + 0xa8);
    }
    iVar3 = _os_log_type_enabled(puVar8,0);
    if (iVar3 == 0) goto LAB_10006a72c;
    pcVar4 = _dispatch_queue_get_label((dispatch_queue_t)0x0);
    local_70 = (undefined4)DAT_1001b3090;
    uStack_6c = SUB84(pcVar4,0);
    uStack_68 = (undefined4)((ulong)pcVar4 >> 0x20);
    pcVar4 = "Destroying required features... currentDispatchQueue: %s";
  }
  __os_log_impl(0x100000000,puVar8,0,pcVar4,&local_70,0xc);
LAB_10006a72c:
  uVar2 = DAT_1001b30b0;
  lVar10 = 0;
  lVar9 = 0x1d;
  do {
    uVar1 = (&__kiAP2FeatureInfoEntries)[lVar10 * 4];
    plVar6 = (long *)(&PTR__kiAP2FeatureInfo_AccAuthentication_10021b558)[lVar10 * 2];
    if ((((plVar6 != (long *)0x0) && (*plVar6 != 0)) && (*(byte *)((long)plVar6 + 0x22) == param_2))
       && (param_1 != 0)) {
      lVar7 = *(long *)(param_1 + 0xd0 + (ulong)uVar1 * 8);
      local_70 = (undefined4)lVar7;
      uStack_6c = (undefined4)((ulong)lVar7 >> 0x20);
      if (lVar7 != 0) {
        pcVar11 = *(code **)(*plVar6 + 8);
        uVar12 = (undefined4)uVar2;
        if (pcVar11 == (code *)0x0) {
          if (_gLogObjects == 0 || _gNumLogObjects < 0x16) {
            puVar8 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              _iap2_features_registerIdentificationParamHandlers_cold_2();
              puVar8 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar8 = *(undefined **)(_gLogObjects + 0xa8);
          }
          iVar3 = _os_log_type_enabled(puVar8,1);
          if (iVar3 != 0) {
            local_80 = uVar12;
            local_7c = uVar1;
            __os_log_impl(0x100000000,puVar8,1,
                          "No destroy function for feature: %{coreacc:iAP2Feature_t}d!",&local_80,8)
            ;
          }
        }
        else {
          if (_gLogObjects == 0 || _gNumLogObjects < 0x16) {
            puVar8 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              _iap2_features_registerIdentificationParamHandlers_cold_2();
              puVar8 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar8 = *(undefined **)(_gLogObjects + 0xa8);
          }
          iVar3 = _os_log_type_enabled(puVar8,0);
          if (iVar3 != 0) {
            local_80 = uVar12;
            local_7c = uVar1;
            __os_log_impl(0x100000000,puVar8,0,"Destroying feature: %{coreacc:iAP2Feature_t}d...",
                          &local_80,8);
          }
          uVar5 = (*pcVar11)(&local_70,param_1);
          if ((uVar5 & 1) == 0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x16)) {
              puVar8 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                _iap2_features_registerIdentificationParamHandlers_cold_2();
                puVar8 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar8 = *(undefined **)(_gLogObjects + 0xa8);
            }
            iVar3 = _os_log_type_enabled(puVar8,0x10);
            if (iVar3 != 0) {
              local_80 = uVar12;
              local_7c = uVar1;
              __os_log_error_impl(0x100000000,puVar8,0x10,
                                  "Error destroying feature: %{coreacc:iAP2Feature_t}d!",&local_80,8
                                 );
            }
          }
        }
        *(undefined8 *)(param_1 + 0xd0 + (ulong)uVar1 * 8) = 0;
      }
    }
    lVar10 = lVar10 + 1;
    lVar9 = lVar9 + -1;
  } while (lVar9 != 0);
  return 0;
}


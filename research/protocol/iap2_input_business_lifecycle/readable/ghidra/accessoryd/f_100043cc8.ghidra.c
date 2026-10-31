/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100043cc8
 * original code SHA256: 23517266e3d3aebd6f44a567be48e55bd10767eb2eb227e603c0019ee67ae6cf
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool __parseiAPHIDComponentIdentificationParams(long param_1,undefined8 param_2,undefined8 param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined1 *puVar7;
  long lVar8;
  long lVar9;
  int *piVar10;
  undefined *puVar11;
  undefined8 uVar12;
  undefined8 local_98;
  undefined4 local_90;
  int local_8c;
  undefined2 local_88;
  uint local_86;
  undefined2 local_82;
  undefined8 local_80;
  undefined2 local_78;
  int local_76;
  undefined2 local_66;
  int local_64;
  
  local_64 = -1;
  if (param_1 == 0) {
    __parseUSBHostHIDComponentIdentificationParams_cold_4(&local_90);
    return (bool)(undefined1)local_90;
  }
  puVar7 = (undefined1 *)_iap2_feature_getFeature(param_1,0xb);
  if (puVar7 == (undefined1 *)0x0) {
    _iap2_features_createFeature(param_1,0xb);
    puVar7 = (undefined1 *)_iap2_feature_getFeature(param_1,0xb);
    if (puVar7 == (undefined1 *)0x0) {
      __parseUSBHostHIDComponentIdentificationParams_cold_3(&local_90);
      return (bool)(undefined1)local_90;
    }
  }
  iVar4 = _iAP2MsgGetParamID(param_3);
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x24)) {
    puVar11 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      ___iap2_hid_StartHIDMsgHandler_block_invoke_cold_1();
      puVar11 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar11 = *(undefined **)(_gLogObjects + 0x118);
  }
  iVar5 = _os_log_type_enabled(puVar11,1);
  if (iVar5 != 0) {
    local_90 = (undefined4)DAT_1001b30b0;
    local_8c = iVar4;
    __os_log_impl(0x100000000,puVar11,1,"parsing identification paramID 0x%X",&local_90,8);
  }
  if (iVar4 != 0x12) {
    bVar3 = false;
    iVar4 = 10;
    goto LAB_1000440c4;
  }
  local_66 = 0;
  lVar8 = _iAP2MsgGetFirstParam(param_2,param_3);
  if (lVar8 == 0) {
LAB_100043f84:
    bVar3 = false;
    iVar4 = 2;
  }
  else {
    bVar2 = false;
    local_98 = 0;
    bVar1 = false;
    bVar3 = false;
    uVar6 = 9;
    iVar4 = 10;
    do {
      iVar5 = _iAP2MsgGetParamID(lVar8);
      if (iVar5 == 2) {
        if (bVar1) {
          iVar4 = 5;
          bVar1 = true;
        }
        else {
          uVar6 = _iAP2MsgGetDataAsU8(lVar8,&local_64);
          if (local_64 == 0) {
            bVar1 = uVar6 < 0xb;
            if (!bVar1) {
              iVar4 = 6;
            }
          }
          else {
            bVar1 = false;
          }
        }
      }
      else if (iVar5 == 1) {
        if (bVar3) {
          iVar4 = 5;
          bVar3 = true;
        }
        else {
          local_98 = _iAP2MsgGetDataAsString(lVar8,&local_64);
          bVar3 = local_64 == 0;
        }
      }
      else if (iVar5 == 0) {
        if (bVar2) {
          iVar4 = 5;
          bVar2 = true;
        }
        else {
          local_66 = _iAP2MsgGetDataAsU16(lVar8,&local_64);
          bVar2 = local_64 == 0;
        }
      }
      lVar8 = _iAP2MsgGetNextParam(param_2,param_3,lVar8);
    } while (lVar8 != 0);
    if (((bool)(bVar2 & bVar3 & bVar1)) && (iVar4 != 5)) {
      uVar12 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
      lVar8 = _CFNumberCreate(uVar12,8,&local_66);
      if (lVar8 != 0) {
        lVar9 = *(long *)(puVar7 + 8);
        if (lVar9 == 0) {
          lVar9 = _CFDictionaryCreateMutable
                            (uVar12,1,PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,0);
          *(long *)(puVar7 + 8) = lVar9;
        }
        iVar4 = _CFDictionaryContainsKey(lVar9,lVar8);
        if (iVar4 == 0) {
          piVar10 = (int *)_malloc_type_calloc(1,0x20,0x106004075560eeb);
          if (piVar10 != (int *)0x0) {
            *piVar10 = 0;
            *(undefined2 *)(piVar10 + 1) = local_66;
            uVar12 = _CFStringCreateWithCString(uVar12,local_98,0x8000100);
            *(undefined8 *)(piVar10 + 2) = uVar12;
            piVar10[4] = uVar6;
            *(undefined2 *)(piVar10 + 6) = 0;
            *(undefined1 *)((long)piVar10 + 0x1a) = 0;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x24)) {
              puVar11 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                __validateHIDComponent_cold_1();
                puVar11 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar11 = *(undefined **)(_gLogObjects + 0x118);
            }
            iVar4 = _os_log_type_enabled(puVar11,1);
            if (iVar4 != 0) {
              local_8c = *piVar10;
              local_80 = *(undefined8 *)(piVar10 + 2);
              local_76 = piVar10[4];
              local_90 = (undefined4)DAT_1001b3470;
              local_88 = 0x400;
              local_86 = (uint)*(ushort *)(piVar10 + 1);
              local_82 = 0x840;
              local_78 = 0x400;
              __os_log_impl(0x100000000,puVar11,1,
                            "Adding iAP HID componentType: %d componentID: %d: \'%@\' %{coreacc:iAP2ParamID_IdentificationInfo_HIDComponent_Function_t}d"
                            ,&local_90,0x1e);
            }
          }
          _CFDictionaryAddValue(*(undefined8 *)(puVar7 + 8),lVar8,piVar10);
          iVar4 = 0;
          *puVar7 = 1;
        }
        else {
          if ((*(long *)(puVar7 + 8) != 0) &&
             (_CFDictionaryApplyFunction
                        (*(long *)(puVar7 + 8),__CFDictionaryApplierFunction_releaseHIDComponents,0)
             , *(long *)(puVar7 + 8) != 0)) {
            _CFRelease();
            *(undefined8 *)(puVar7 + 8) = 0;
          }
          iVar4 = 3;
        }
        _CFRelease(lVar8);
      }
    }
    else if (iVar4 == 10) goto LAB_100043f84;
    bVar3 = local_64 == 0 && iVar4 == 0;
    if (iVar4 == 0) {
      return bVar3;
    }
  }
LAB_1000440c4:
  _iap2_identification_addRejectParam(param_1,0x12,iVar4);
  return bVar3;
}


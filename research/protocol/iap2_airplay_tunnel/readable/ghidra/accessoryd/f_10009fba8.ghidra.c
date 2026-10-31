/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10009fba8
 * original code SHA256: 2108995c432507bd05dc5e153e8957aee8aff6fa1644f4faa188466e8bb0eddc
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool __parseIdentificationSupportedEAProtocol
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  ushort uVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  long lVar10;
  ushort *puVar11;
  undefined8 uVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  void *pvVar16;
  undefined8 uVar17;
  bool bVar18;
  int iVar19;
  undefined *puVar20;
  long lVar21;
  long local_98;
  uint local_90;
  undefined8 local_88;
  uint local_80;
  long local_7c;
  undefined2 local_74;
  uint local_72;
  undefined1 local_65;
  int local_64;
  
  local_64 = 0;
  iVar7 = _iAP2MsgGetParamID(param_3);
  if (iVar7 == 10) {
    local_65 = 0;
    _iap2_features_createFeature(param_1,10);
    lVar10 = _iAP2MsgGetFirstParam(param_2,param_3);
    if (lVar10 == 0) {
      iVar7 = 0x11;
      local_98 = 0;
    }
    else {
      local_88 = 0;
      bVar2 = false;
      bVar5 = false;
      bVar1 = false;
      bVar18 = false;
      bVar4 = false;
      local_98 = 0;
      uVar6 = 0;
      uVar17 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
      local_90 = 5;
      do {
        iVar8 = _iAP2MsgGetParamID(lVar10);
        iVar19 = 0x11;
        iVar7 = iVar19;
        bVar3 = bVar4;
        if (iVar8 < 2) {
          if (iVar8 == 0) {
            if (bVar2) {
              bVar2 = true;
              iVar7 = 5;
            }
            else {
              uVar9 = _iAP2MsgGetDataAsU8(lVar10,&local_64);
              local_88 = CONCAT44(local_88._4_4_,uVar9);
              local_65 = (undefined1)uVar9;
              bVar4 = local_64 == 0;
              bVar2 = bVar4;
LAB_10009fd70:
              if (!bVar4) {
                iVar7 = 0xf;
              }
            }
          }
          else {
            iVar7 = 0x11;
            if (iVar8 == 1) {
              if (bVar5) {
                bVar5 = true;
                iVar7 = 5;
              }
              else {
                uVar12 = _iAP2MsgGetDataAsString(lVar10,&local_64);
                if (local_64 == 0) {
                  local_98 = _CFStringCreateWithCString(uVar17,uVar12,0x8000100);
                  bVar5 = local_98 != 0;
                }
                else {
                  bVar5 = false;
                  iVar7 = 0xf;
                }
              }
            }
          }
        }
        else if (iVar8 == 2) {
          if (bVar1) {
            bVar1 = true;
            iVar7 = 5;
          }
          else {
            local_90 = _iAP2MsgGetDataAsU8(lVar10,&local_64);
            bVar4 = (local_90 & 0xff) < 5;
            bVar1 = local_64 == 0 && bVar4;
            if (local_64 != 0 || !bVar4) {
              iVar7 = 0xf;
            }
          }
        }
        else if (iVar8 == 3) {
          if (bVar18 == false) {
            uVar6 = _iAP2MsgGetDataAsU16(lVar10,&local_64);
            bVar4 = local_64 == 0;
            uVar9 = 2;
            if (!bVar4) {
              uVar9 = local_88._4_4_;
            }
            local_88 = CONCAT44(uVar9,(uint)local_88);
            bVar18 = bVar4;
            goto LAB_10009fd70;
          }
          bVar18 = true;
          iVar7 = 5;
        }
        else {
          iVar7 = 5;
          if (!bVar4) {
            iVar7 = iVar19;
          }
          bVar3 = true;
          if (iVar8 != 4) {
            iVar7 = 0x11;
            bVar3 = bVar4;
          }
        }
        bVar4 = bVar3;
        lVar10 = _iAP2MsgGetNextParam(param_2,param_3,lVar10);
      } while ((lVar10 != 0) && (iVar7 == 0x11));
      if (((bool)(bVar2 & bVar5)) && (iVar7 == 0x11)) {
        if ((_gLogObjects == (undefined8 *)0x0) || (_gNumLogObjects < 0x21)) {
          puVar20 = PTR___os_log_default_10022bbb0;
          if (DAT_10023e9d8 != -1) {
            _iap2_externalAccessory_openEASession_cold_3();
            puVar20 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar20 = (undefined *)_gLogObjects[0x20];
        }
        iVar7 = _os_log_type_enabled(puVar20,1);
        if (iVar7 != 0) {
          local_72 = (uint)local_88 & 0xff;
          local_80 = (uint)DAT_1001b30f0;
          local_7c = local_98;
          local_74 = 0x400;
          __os_log_impl(0x100000000,puVar20,1,"Adding EA protocol %@, protocolID %d",&local_80,0x12)
          ;
        }
        puVar11 = (ushort *)_malloc_type_calloc(1,0x20,0x106004016586fa1);
        if (puVar11 == (ushort *)0x0) {
          local_64 = -1;
          if ((_gLogObjects == (undefined8 *)0x0) || (_gNumLogObjects < 0x21)) {
            puVar20 = PTR___os_log_default_10022bbb0;
            if (DAT_10023e9d8 != -1) {
              _iap2_externalAccessory_openEASession_cold_3();
              puVar20 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar20 = (undefined *)_gLogObjects[0x20];
          }
          iVar7 = _os_log_type_enabled(puVar20,0x10);
          if (iVar7 != 0) {
            __parseIdentificationSupportedEAProtocol_cold_7(puVar20);
          }
          if (local_98 != 0) {
            _CFRelease(local_98);
          }
        }
        else {
          *puVar11 = (ushort)local_88 & 0xff;
          *(long *)(puVar11 + 4) = local_98;
          *(bool *)((long)puVar11 + 0x17) = bVar4;
          puVar11[10] = uVar6;
          *(bool *)(puVar11 + 0xb) = bVar18;
          *(undefined4 *)(puVar11 + 0xc) = local_88._4_4_;
          if (!bVar1) {
            local_90 = 1;
          }
          *(uint *)(puVar11 + 8) = local_90;
          lVar10 = _iap2_feature_getFeature(param_1,10);
          if (lVar10 != 0) {
            if (*(long *)(lVar10 + 8) == 0) {
              uVar12 = _CFArrayCreateMutable(uVar17,1,0);
              *(undefined8 *)(lVar10 + 8) = uVar12;
            }
            if (*(long *)(lVar10 + 0x18) == 0) {
              uVar12 = _CFDictionaryCreateMutable
                                 (uVar17,1,PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,
                                  PTR__kCFTypeDictionaryValueCallBacks_10022bd48);
              *(undefined8 *)(lVar10 + 0x18) = uVar12;
            }
            if (*(long *)(lVar10 + 0x10) == 0) {
              uVar12 = _CFDictionaryCreateMutable
                                 (uVar17,1,PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,0);
              *(undefined8 *)(lVar10 + 0x10) = uVar12;
            }
            if (*(long *)(lVar10 + 0x20) == 0) {
              uVar12 = _CFDictionaryCreateMutable
                                 (uVar17,1,PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,0);
              *(undefined8 *)(lVar10 + 0x20) = uVar12;
            }
            lVar13 = _CFNumberCreate(uVar17,1,&local_65);
            lVar14 = _CFDictionaryGetCountOfKey(*(undefined8 *)(lVar10 + 0x10),lVar13);
            if (lVar14 == 0) {
              _CFDictionaryAddValue(*(undefined8 *)(lVar10 + 0x10),lVar13,puVar11);
              _CFArrayAppendValue(*(undefined8 *)(lVar10 + 8),puVar11);
              iVar7 = 0;
            }
            else {
              if ((_gLogObjects == (undefined8 *)0x0) || (_gNumLogObjects < 1)) {
                puVar20 = PTR___os_log_default_10022bbb0;
                if (DAT_10023e9d8 != -1) {
                  _iap2_externalAccessory_openEASession_cold_3();
                  puVar20 = PTR___os_log_default_10022bbb0;
                }
              }
              else {
                puVar20 = (undefined *)*_gLogObjects;
              }
              iVar7 = _os_log_type_enabled(puVar20,0x10);
              if (iVar7 != 0) {
                __parseIdentificationSupportedEAProtocol_cold_3(&local_65,local_98,puVar20);
              }
              local_64 = -1;
              _CFDictionaryRemoveAllValues(*(undefined8 *)(lVar10 + 0x10));
              if (*(long *)(lVar10 + 8) != 0) {
                lVar15 = _CFArrayGetCount();
                if (0 < lVar15) {
                  lVar21 = 0;
                  do {
                    pvVar16 = (void *)_CFArrayGetValueAtIndex(*(undefined8 *)(lVar10 + 8),lVar21);
                    if (*(long *)((long)pvVar16 + 8) != 0) {
                      _CFRelease();
                    }
                    _free(pvVar16);
                    lVar21 = lVar21 + 1;
                  } while (lVar15 != lVar21);
                }
                if (*(long *)(lVar10 + 8) != 0) {
                  _CFRelease();
                  *(undefined8 *)(lVar10 + 8) = 0;
                }
              }
              if (local_98 != 0) {
                _CFRelease(local_98);
              }
              _free(puVar11);
              iVar7 = 0x11;
            }
            if (lVar13 != 0) {
              _CFRelease(lVar13);
            }
            iVar8 = local_64;
            if (lVar14 == 0) goto LAB_1000a024c;
            goto LAB_1000a023c;
          }
          local_64 = -1;
          if ((_gLogObjects == (undefined8 *)0x0) || (_gNumLogObjects < 0x21)) {
            puVar20 = PTR___os_log_default_10022bbb0;
            if (DAT_10023e9d8 != -1) {
              _iap2_externalAccessory_openEASession_cold_3();
              puVar20 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar20 = (undefined *)_gLogObjects[0x20];
          }
          iVar7 = _os_log_type_enabled(puVar20,0x10);
          if (iVar7 != 0) {
            __parseIdentificationSupportedEAProtocol_cold_5(puVar20);
          }
          if (local_98 != 0) {
            _CFRelease(local_98);
          }
          _free(puVar11);
        }
        iVar7 = 0x11;
        iVar8 = local_64;
        goto LAB_1000a023c;
      }
    }
    local_64 = -1;
    if ((_gLogObjects == (undefined8 *)0x0) || (_gNumLogObjects < 0x21)) {
      puVar20 = PTR___os_log_default_10022bbb0;
      if (DAT_10023e9d8 != -1) {
        _iap2_externalAccessory_openEASession_cold_3();
        puVar20 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar20 = (undefined *)_gLogObjects[0x20];
    }
    iVar8 = _os_log_type_enabled(puVar20,0);
    if (iVar8 != 0) {
      local_80 = local_80 & 0xffff0000;
      __os_log_impl(0x100000000,puVar20,0,
                    "Invalid EA Protocol param! (need to log more details later)",&local_80,2);
    }
    iVar8 = local_64;
    if (local_98 != 0) {
      _CFRelease(local_98);
      iVar8 = local_64;
    }
  }
  else {
    iVar7 = 0x11;
    iVar8 = 0;
  }
LAB_1000a023c:
  _iap2_identification_addRejectParam(param_1,10,iVar7);
  local_64 = iVar8;
LAB_1000a024c:
  return local_64 == 0;
}


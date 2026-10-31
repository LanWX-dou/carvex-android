/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a9e5d0
 * original code SHA256: bff9ae8b42f19596986d6abf4a18e09b2bb82cc37c71ce4c1e84c2c06a39bc5d
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251a9e868) */
/* WARNING: Removing unreachable block (ram,0x000251a9e9f4) */
/* WARNING: Removing unreachable block (ram,0x000251a9e790) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _sdpsession_setupStreamCreatingResponseInternal(undefined8 *param_1)

{
  char cVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  code *pcVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ulong local_80;
  long local_78;
  long local_70;
  long local_68;
  
  lVar3 = func_0x00025810ac50(*param_1);
  if ((_gLogCategory_APSenderSessionSDP < 0x1f) &&
     ((_gLogCategory_APSenderSessionSDP != -1 ||
      (iVar2 = func_0x000258101e40(&_gLogCategory_APSenderSessionSDP,0x200001e), iVar2 != 0)))) {
    _sdpsession_setupStreamCreatingResponseInternal_cold_1(param_1,lVar3);
  }
  if (*(int *)(param_1 + 1) != 0x60) {
    uVar4 = 0xfffee76f;
    _sdpsession_setupStreamCreatingResponseInternal_cold_2();
    goto LAB_251a9eb90;
  }
  func_0x00025810b430(*(undefined8 *)(lVar3 + 0x48));
  cVar1 = *(char *)(lVar3 + 0x85);
  func_0x00025810b440(*(undefined8 *)(lVar3 + 0x48));
  if (cVar1 != '\0') {
    return 0;
  }
  uVar4 = _sdpsession_ensureTransportControlStreamResumedSync(*param_1);
  if ((int)uVar4 != 0) {
    _sdpsession_setupStreamCreatingResponseInternal_cold_3();
    goto LAB_251a9eb90;
  }
  uVar12 = *param_1;
  local_80 = local_80 & 0xffffffff00000000;
  lVar5 = func_0x00025810ac50(uVar12);
  local_70 = 0;
  local_68 = 0;
  func_0x00025810b430(*(undefined8 *)(lVar5 + 0x48));
  if (*(long *)(lVar5 + 0x60) == 0) {
    lVar6 = 0;
  }
  else {
    lVar6 = func_0x0002580f6a60();
  }
  local_78 = lVar6;
  func_0x00025810b440(*(undefined8 *)(lVar5 + 0x48));
  puVar11 = _DAT_2680d3150;
  if (lVar6 == 0) {
    _sdpsession_copyTransportControlStream(uVar12,&local_70);
    lVar6 = local_70;
    local_80 = local_80 & 0xffffffff00000000;
    if (local_70 == 0) {
      _sdpsession_setupStreamCreatingResponseInternal_cold_11(&local_80);
    }
    else {
      uVar12 = func_0x000258109860(*(undefined8 *)(lVar5 + 0x18),
                                   _kAPEndpointDescriptionProperty_AuthenticationType,&local_80);
      if ((int)local_80 == 0) {
        iVar2 = (int)uVar12;
        if (iVar2 == 8) {
          iVar2 = _APAuthenticationClientMFiCreate(*puVar11,lVar6,&local_78);
          local_80 = CONCAT44(local_80._4_4_,iVar2);
          if (iVar2 == 0) {
LAB_251a9e820:
            lVar6 = local_78;
            lVar7 = func_0x000258109150(local_78);
            puVar10 = (undefined8 *)(*(long *)(lVar7 + 0x10) + 0x10);
            pcVar9 = (code *)*puVar10;
            if ((pcVar9 == (code *)0x0) || (pcVar9 == (code *)0x0)) {
              local_80 = CONCAT44(local_80._4_4_,0xffffce12);
            }
            else {
              iVar2 = (*pcVar9)((ulong)puVar10 & 0xffffffffffff | 0xd045000000000000,lVar6);
              local_80 = CONCAT44(local_80._4_4_,iVar2);
              if (iVar2 == 0) {
                func_0x00025810b430(*(undefined8 *)(lVar5 + 0x48));
                lVar6 = *(long *)(lVar5 + 0x60);
                *(long *)(lVar5 + 0x60) = local_78;
                if (local_78 != 0) {
                  func_0x0002580f6a60();
                }
                if (lVar6 != 0) {
                  func_0x0002580f5830(lVar6);
                }
                func_0x00025810b440(*(undefined8 *)(lVar5 + 0x48));
                goto LAB_251a9e918;
              }
            }
            _sdpsession_setupStreamCreatingResponseInternal_cold_8();
          }
          else {
            _sdpsession_setupStreamCreatingResponseInternal_cold_6();
          }
        }
        else if (iVar2 == 4) {
          iVar2 = _APAuthenticationClientFairPlayCreate(*puVar11,lVar6,&local_78);
          local_80 = CONCAT44(local_80._4_4_,iVar2);
          if (iVar2 == 0) goto LAB_251a9e820;
          _sdpsession_setupStreamCreatingResponseInternal_cold_5();
        }
        else if (iVar2 == 1) {
          uVar12 = _APEndpointDescriptionGetCMBaseObject(*(undefined8 *)(lVar5 + 0x18));
          lVar7 = func_0x000258109150();
          puVar10 = (undefined8 *)(*(long *)(lVar7 + 8) + 0x30);
          pcVar9 = (code *)*puVar10;
          if ((pcVar9 == (code *)0x0) || (pcVar9 == (code *)0x0)) {
            local_80 = CONCAT44(local_80._4_4_,0xffffce12);
          }
          else {
            uVar13 = *puVar11;
            iVar2 = (*pcVar9)((ulong)puVar10 & 0xffffffffffff | 0x9725000000000000,uVar12,
                              _kAPEndpointDescriptionProperty_MACAddress,uVar13,&local_68);
            local_80 = CONCAT44(local_80._4_4_,iVar2);
            if (iVar2 == 0) {
              iVar2 = _APAuthenticationClientRSACreate(uVar13,lVar6,local_68,&local_78);
              local_80 = CONCAT44(local_80._4_4_,iVar2);
              if (iVar2 == 0) goto LAB_251a9e820;
              _sdpsession_setupStreamCreatingResponseInternal_cold_7();
              goto LAB_251a9e918;
            }
          }
          _sdpsession_setupStreamCreatingResponseInternal_cold_9();
        }
        else {
          if ((_gLogCategory_APSenderSessionSDP < 0x5b) &&
             ((_gLogCategory_APSenderSessionSDP != -1 ||
              (iVar2 = func_0x000258101e40(&_gLogCategory_APSenderSessionSDP,0x200005a), iVar2 != 0)
              ))) {
            _sdpsession_setupStreamCreatingResponseInternal_cold_10(uVar12);
          }
          local_80 = CONCAT44(local_80._4_4_,0xfffee770);
        }
      }
      else {
        _sdpsession_setupStreamCreatingResponseInternal_cold_4();
      }
    }
LAB_251a9e918:
    lVar6 = local_78;
    if (local_78 != 0) goto LAB_251a9e920;
  }
  else {
LAB_251a9e920:
    func_0x0002580f5830(lVar6);
  }
  if (local_68 != 0) {
    func_0x0002580f5830();
  }
  if (local_70 != 0) {
    func_0x0002580f5830();
  }
  uVar4 = local_80 & 0xffffffff;
  if ((int)local_80 != 0) {
    _sdpsession_setupStreamCreatingResponseInternal_cold_12(uVar4);
    goto LAB_251a9eb90;
  }
  lVar5 = func_0x00025810ac50(*param_1);
  local_70 = 0;
  local_68 = 0;
  local_80 = 0;
  local_78 = 0;
  if (*(long *)(lVar5 + 0x38) == 0) {
    func_0x00025810b430(*(undefined8 *)(lVar5 + 0x48));
    if (*(long *)(lVar5 + 0x60) == 0) {
      lVar6 = 0;
    }
    else {
      lVar6 = func_0x0002580f6a60();
    }
    func_0x00025810b440(*(undefined8 *)(lVar5 + 0x48));
    uVar12 = *puVar11;
    uVar4 = _APKeyHolderSharedKeyCreate(uVar12,0,0,0,&local_70);
    lVar7 = local_70;
    if ((int)uVar4 == 0) {
      lVar8 = func_0x000258109150(local_70);
      puVar11 = (undefined8 *)(*(long *)(lVar8 + 0x10) + 0x10);
      pcVar9 = (code *)*puVar11;
      if ((pcVar9 == (code *)0x0) || (pcVar9 == (code *)0x0)) {
        uVar4 = 0xffffce12;
      }
      else {
        uVar4 = (*pcVar9)((ulong)puVar11 & 0xffffffffffff | 0x7362000000000000,lVar7,&local_78,
                          &local_80);
        if ((int)uVar4 == 0) {
          uVar4 = _APKeyHolderSharedKeyCreate(uVar12,lVar6,local_78,local_80,&local_68);
          if ((int)uVar4 == 0) {
            lVar7 = *(long *)(lVar5 + 0x38);
            *(long *)(lVar5 + 0x38) = local_68;
            if (local_68 != 0) {
              func_0x0002580f6a60();
            }
            uVar4 = 0;
            if (lVar7 != 0) {
              func_0x0002580f5830(lVar7);
              uVar4 = 0;
            }
          }
          else {
            _sdpsession_setupStreamCreatingResponseInternal_cold_14();
          }
          goto LAB_251a9ea70;
        }
      }
      func_0x000258109a30(uVar4,"sdpsession_ensureKeyHolderSetUp",0x46b,0);
    }
    else {
      _sdpsession_setupStreamCreatingResponseInternal_cold_13();
    }
LAB_251a9ea70:
    if (lVar6 != 0) {
      func_0x0002580f5830(lVar6);
    }
  }
  else {
    uVar4 = 0;
  }
  if (local_68 != 0) {
    func_0x0002580f5830();
  }
  if (local_70 != 0) {
    func_0x0002580f5830();
  }
  if (local_78 != 0) {
    func_0x0002580f5830();
  }
  if (local_80 != 0) {
    func_0x0002580f5830();
  }
  if ((int)uVar4 == 0) {
    uVar4 = _sdpsession_sendAnnounce(*param_1,param_1[2]);
    if ((int)uVar4 == 0) {
      uVar4 = _sdpsession_sendSetup(*param_1,param_1[2],param_1[3]);
      if ((int)uVar4 == 0) {
        uVar4 = _sdpsession_ensureInitialVolumeFetched(*param_1);
        if ((int)uVar4 == 0) {
          uVar4 = _sdpsession_startSession(*param_1);
          if ((int)uVar4 == 0) {
            uVar4 = _sdpsession_sendPendingSetVolumeCommand(*param_1);
            if ((int)uVar4 == 0) {
              uVar4 = _sdpsession_copyCryptor(*param_1,param_1[4]);
              if ((int)uVar4 == 0) {
                uVar4 = _sdpsession_ensureKeepAliveResumed(*param_1);
                if ((int)uVar4 == 0) {
                  if ((_gLogCategory_APSenderSessionSDP < 0x29) &&
                     ((_gLogCategory_APSenderSessionSDP != -1 ||
                      (iVar2 = func_0x000258101e40(&_gLogCategory_APSenderSessionSDP,0x2000028),
                      iVar2 != 0)))) {
                    _sdpsession_setupStreamCreatingResponseInternal_cold_22
                              (param_1,lVar3,param_1 + 1);
                  }
                  uVar13 = *(undefined8 *)(lVar3 + 8);
                  uVar12 = func_0x00025810ad10();
                  func_0x00025810f2d0(uVar13,uVar12,_kAPSenderSessionNotification_Started,*param_1,0
                                      ,0);
                  return 0;
                }
                _sdpsession_setupStreamCreatingResponseInternal_cold_21();
              }
              else {
                _sdpsession_setupStreamCreatingResponseInternal_cold_20();
              }
            }
            else {
              _sdpsession_setupStreamCreatingResponseInternal_cold_19();
            }
          }
          else {
            _sdpsession_setupStreamCreatingResponseInternal_cold_18();
          }
        }
        else {
          _sdpsession_setupStreamCreatingResponseInternal_cold_17();
        }
      }
      else {
        _sdpsession_setupStreamCreatingResponseInternal_cold_16();
      }
    }
    else {
      _sdpsession_setupStreamCreatingResponseInternal_cold_15();
    }
  }
  else {
    func_0x000258109a30(uVar4,"sdpsession_setupStreamCreatingResponseInternal",0x31c,0);
  }
LAB_251a9eb90:
  _sdpsession_postFailedNotificationAsync(*param_1,uVar4,_kAPSenderSessionState_Starting);
  _sdpsession_teardownTransportControlStream(*param_1);
  return uVar4;
}


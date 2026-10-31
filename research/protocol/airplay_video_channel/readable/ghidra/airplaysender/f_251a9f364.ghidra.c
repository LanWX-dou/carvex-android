/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a9f364
 * original code SHA256: 7bbd385cd064940885f094526c7ae6750b794ce7c11ab83ba39245aca94537ac
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _sdpsession_sendSetup(undefined8 param_1,undefined8 param_2,long *param_3)

{
  undefined8 uVar1;
  int iVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  undefined8 uVar8;
  long local_b8;
  long local_b0;
  int local_a4;
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  long local_80;
  long local_78;
  long local_70;
  undefined8 local_68;
  
  local_a4 = 0;
  func_0x00025810ac50();
  local_b0 = 0;
  if ((_gLogCategory_APSenderSessionSDP < 0x1f) &&
     ((_gLogCategory_APSenderSessionSDP != -1 ||
      (iVar2 = func_0x000258101e40(&_gLogCategory_APSenderSessionSDP,0x200001e), iVar2 != 0)))) {
    _sdpsession_sendSetup_cold_1();
  }
  _sdpsession_copyTransportControlStream(param_1,&local_b8);
  local_a4 = 0;
  if (local_b8 == 0) {
    _sdpsession_sendSetup_cold_17(&local_a4);
    goto LAB_251a9f780;
  }
  uVar8 = *_DAT_2680d3150;
  lVar3 = func_0x00025810aa90(uVar8,0);
  if (lVar3 == 0) {
    _sdpsession_sendSetup_cold_16(&local_a4);
    goto LAB_251a9f780;
  }
  func_0x00025810aa50(lVar3,0,&cfstringStruct_2761341d0);
  uVar1 = _kAPSenderSessionStreamKey_NetworkPortControl;
  puVar4 = (undefined8 *)
           func_0x00025810a6f0(param_2,_kAPSenderSessionStreamKey_NetworkPortControl,&local_a4);
  if (local_a4 == 0) {
    func_0x00025810aa50(lVar3,0,&cfstringStruct_2761341f0);
    local_a4 = _sdpsession_sendMessageCreatingReply(local_b8,0x73736470,lVar3,&local_b0);
    if (local_a4 == 0) {
      local_70 = 0;
      local_68 = 0;
      local_80 = 0;
      local_78 = 0;
      local_90 = 0;
      uStack_88 = 0;
      local_a0 = 0;
      uStack_98 = 0;
      uVar5 = func_0x00025810eae0(local_b0,0,&local_78,&local_70,&local_80);
      if ((int)uVar5 == 0) {
        if (local_70 == local_78) {
          lVar6 = local_80 + local_70;
          uVar5 = func_0x00025810b770(local_80,lVar6,&uStack_88,&local_90,0,0,0,&local_80,puVar4);
          if ((int)uVar5 == 0) {
            iVar2 = func_0x00025810c260(uStack_88,local_90,"RTP/AVP/UDP");
            if (iVar2 == 0) {
              uVar5 = func_0x00025810b770(local_80,lVar6,&uStack_88,&local_90,&uStack_98,&local_a0,0
                                          ,&local_80);
              if ((int)uVar5 == 0) {
                do {
                  iVar2 = func_0x00025810c260(uStack_88,local_90,"control_port");
                  if (iVar2 == 0) {
                    puVar4 = (undefined8 *)((long)&local_68 + 4);
                    iVar2 = func_0x00025810bb30(uStack_98,local_a0,"%u");
                    if (iVar2 != 1) {
                      _sdpsession_sendSetup_cold_11();
LAB_251a9f7fc:
                      uVar5 = 0xfffee76d;
                      goto LAB_251a9f53c;
                    }
                    if (local_68._4_4_ < 1) {
                      _sdpsession_sendSetup_cold_15();
LAB_251a9f810:
                      uVar5 = 0xfffee76c;
                      goto LAB_251a9f53c;
                    }
                  }
                  else {
                    iVar2 = func_0x00025810c260(uStack_88,local_90,"server_port");
                    if (iVar2 == 0) {
                      puVar4 = &local_68;
                      iVar2 = func_0x00025810bb30(uStack_98,local_a0,"%u");
                      if (iVar2 != 1) {
                        _sdpsession_sendSetup_cold_9();
                        goto LAB_251a9f7fc;
                      }
                      if ((int)local_68 < 1) {
                        _sdpsession_sendSetup_cold_10();
                        goto LAB_251a9f810;
                      }
                    }
                    else {
                      iVar2 = func_0x00025810c260(uStack_88,local_90,"event_port");
                      if ((((((iVar2 != 0) &&
                             (iVar2 = func_0x00025810c260(uStack_88,local_90,"interleaved"),
                             iVar2 != 0)) &&
                            (iVar2 = func_0x00025810c260(uStack_88,local_90,"mode"), iVar2 != 0)) &&
                           ((iVar2 = func_0x00025810c260(uStack_88,local_90,"timing_port"),
                            iVar2 != 0 &&
                            (iVar2 = func_0x00025810c260(uStack_88,local_90,"unicast"), iVar2 != 0))
                           )) && ((iVar2 = func_0x00025810c260(uStack_88,local_90,"x-events"),
                                  iVar2 != 0 && (_gLogCategory_APSenderSessionSDP < 0x29)))) &&
                         ((_gLogCategory_APSenderSessionSDP != -1 ||
                          (iVar2 = func_0x000258101e40(&_gLogCategory_APSenderSessionSDP,0x2000028),
                          iVar2 != 0)))) {
                        _sdpsession_sendSetup_cold_8(&local_90,&uStack_88,&uStack_98,&local_a0);
                      }
                    }
                  }
                  iVar2 = func_0x00025810b770(local_80,lVar6,&uStack_88,&local_90,&uStack_98,
                                              &local_a0,0,&local_80,puVar4);
                } while (iVar2 == 0);
                iVar2 = local_68._4_4_;
                uVar5 = uVar8;
                if (0 < local_68._4_4_) {
                  uVar7 = local_68 & 0xffffffff;
                  if (0 < (int)local_68) {
                    local_a4 = 0;
                    lVar6 = func_0x000258101820(uVar8,0,_DAT_2680d3340,_DAT_2680d3358);
                    if (lVar6 == 0) {
                      _sdpsession_sendSetup_cold_12(&local_a4);
                    }
                    else {
                      func_0x00025810a790(lVar6,uVar1,iVar2);
                      func_0x00025810a790(lVar6,_kAPSenderSessionStreamKey_NetworkPortData,uVar7);
                      *param_3 = lVar6;
                    }
                    goto LAB_251a9f778;
                  }
                  _sdpsession_sendSetup_cold_13();
                  goto LAB_251a9f7c8;
                }
              }
              _sdpsession_sendSetup_cold_14(uVar5);
              goto LAB_251a9f7c8;
            }
            uVar5 = 0xfffee76e;
            if ((_gLogCategory_APSenderSessionSDP < 0x5b) &&
               ((_gLogCategory_APSenderSessionSDP != -1 ||
                (iVar2 = func_0x000258101e40(&_gLogCategory_APSenderSessionSDP,0x200005a),
                iVar2 != 0)))) {
              _sdpsession_sendSetup_cold_7(&local_70,&local_80);
            }
          }
          else {
            _sdpsession_sendSetup_cold_6();
          }
        }
        else {
          _sdpsession_sendSetup_cold_5();
LAB_251a9f7c8:
          uVar5 = 0xfffee773;
        }
      }
      else {
        _sdpsession_sendSetup_cold_4();
      }
LAB_251a9f53c:
      local_a4 = (int)uVar5;
      func_0x000258109a30(uVar5,"sdpsession_sendSetup",0x587,0);
    }
    else {
      _sdpsession_sendSetup_cold_3();
    }
  }
  else {
    _sdpsession_sendSetup_cold_2(local_a4);
  }
LAB_251a9f778:
  func_0x0002580f5830(lVar3);
LAB_251a9f780:
  if (local_b0 != 0) {
    func_0x0002580f5830();
  }
  if (local_b8 != 0) {
    func_0x0002580f5830(local_b8);
  }
  return local_a4;
}


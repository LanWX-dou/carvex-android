/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fdc7034
 * original code SHA256: 70120697cde770c45184617ee49cc3cab8e957456ca905b7e783711bcce34d58
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _APTransportConnectionHTTPCreate
               (undefined8 param_1,long param_2,undefined4 param_3,undefined8 param_4,
               undefined8 param_5,long *param_6)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  undefined8 local_118;
  undefined8 uStack_110;
  undefined8 local_108;
  long local_100;
  int local_f4;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 local_e0;
  long local_70;
  
  local_70 = *_DAT_2681b4ee0;
  local_f4 = 0;
  local_100 = 0;
  if (param_6 == (long *)0x0) {
    _APTransportConnectionHTTPCreate_cold_13(&local_f4);
    goto LAB_24fdc75c0;
  }
  uVar5 = _APTransportConnectionGetClassID();
  local_f4 = func_0x0002500e5ab0(param_1,&_kAPTransportConnectionHTTPVTable,uVar5,&local_100);
  if (local_f4 != 0) {
    _APTransportConnectionHTTPCreate_cold_1();
    goto LAB_24fdc75c0;
  }
  lVar6 = func_0x0002500e5a60(local_100);
  lVar7 = func_0x0002500a4550(param_5,_kAPTransportConnectionOption_IsListener,&local_f4);
  *(bool *)(lVar6 + 0xe0) = lVar7 != 0;
  if (local_f4 == 0) {
    if (lVar7 != 0) {
      *(undefined8 *)(lVar6 + 0xf0) = 0;
      *(undefined4 *)(lVar6 + 0xf8) = 0xffffffff;
    }
  }
  else {
    *(undefined1 *)(lVar6 + 0xe0) = 0;
    local_f4 = 0;
  }
  lVar7 = func_0x0002500e5a60(local_100);
  lVar8 = func_0x000250090220(param_5,_kAPTransportConnectionOption_TransportTrafficCapture);
  if (lVar8 == 0) {
    uVar5 = 0;
    lVar8 = 0x208;
LAB_24fdc7160:
    *(undefined8 *)(lVar7 + lVar8) = uVar5;
  }
  else {
    lVar8 = func_0x0002500903e0();
    *(long *)(lVar7 + 0x208) = lVar8;
    if (lVar8 != 0) {
      *(undefined8 *)(lVar7 + 0x240) = _DAT_268123928;
      lVar8 = 0x238;
      uVar5 = _DAT_268123920;
      goto LAB_24fdc7160;
    }
  }
  lVar7 = func_0x0002500a4550(param_5,&cfstringStruct_275fa45e0,&local_f4);
  *(bool *)(lVar6 + 0x100) = lVar7 != 0;
  if (local_f4 != 0) {
    *(undefined1 *)(lVar6 + 0x100) = 0;
    local_f4 = 0;
  }
  uVar5 = _kAPTransportConnectionOption_TrafficRegistrationOptions;
  uVar9 = func_0x000250090210();
  lVar7 = func_0x0002500a4560(param_5,uVar5,uVar9,0);
  if (lVar7 != 0) {
    lVar8 = func_0x0002500a4550(lVar7,
                                _kAPTransportConnectionOptionTrafficRegistrationOption_PerformInitialTrafficRegistration
                                ,0);
    *(bool *)(lVar6 + 0x38) = lVar8 != 0;
    lVar8 = func_0x0002500a4550(lVar7,
                                _kAPTransportConnectionOptionTrafficRegistrationOption_AllowMultiplePeers
                                ,0);
    *(bool *)(lVar6 + 0x39) = lVar8 != 0;
    uVar5 = _kAPTransportConnectionOptionTrafficRegistrationOption_PeerGroupIdentifier;
    if (lVar8 != 0) {
      uVar9 = func_0x000250090580();
      lVar7 = func_0x0002500a4560(lVar7,uVar5,uVar9,0);
      if (lVar7 == 0) {
        *(undefined8 *)(lVar6 + 0x40) = 0;
      }
      else {
        lVar7 = func_0x0002500903e0();
        *(long *)(lVar6 + 0x40) = lVar7;
        if (lVar7 != 0) goto LAB_24fdc723c;
      }
      _APTransportConnectionHTTPCreate_cold_2(&local_f4,&local_100);
      goto LAB_24fdc75c0;
    }
  }
LAB_24fdc723c:
  iVar3 = func_0x0002500a7510();
  if ((iVar3 != 0) &&
     (iVar3 = func_0x0002500ee5b0(&cfstringStruct_275fa4620,lVar6 + 0x38), iVar3 != 0)) {
    if ((_gLogCategory_APTransportConnectionHTTP < 0x33) &&
       ((_gLogCategory_APTransportConnectionHTTP != -1 ||
        (iVar3 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x2000032), iVar3 != 0
        )))) {
      _APTransportConnectionHTTPCreate_cold_3(&local_100,lVar6 + 0x38);
    }
  }
  puVar2 = _DAT_2680d3150;
  if ((*(char *)(lVar6 + 0x100) == '\0') ||
     (lVar7 = func_0x0002500a4550(param_5,&cfstringStruct_275fa3900,0), lVar7 == 0)) {
    lVar7 = 0;
LAB_24fdc7308:
    uVar4 = func_0x0002500a4550(param_5,_kAPTransportConnectionOption_QualityOfService,&local_f4);
    *(undefined4 *)(lVar6 + 200) = uVar4;
    if (local_f4 != 0) {
      *(undefined4 *)(lVar6 + 200) = 0;
      local_f4 = 0;
    }
    uVar5 = _kAPTransportConnectionOption_DelegatedID;
    uVar9 = func_0x0002500932b0();
    lVar8 = func_0x0002500a4560(param_5,uVar5,uVar9,0);
    *(long *)(lVar6 + 0xd0) = lVar8;
    if (lVar8 != 0) {
      func_0x0002500903e0();
    }
    puVar1 = (undefined8 *)(lVar6 + 0x1b8);
    func_0x0002500a09f0(&local_f0,0x403e000000000000,1000);
    *(undefined8 *)(lVar6 + 0x1c0) = uStack_e8;
    *puVar1 = local_f0;
    *(undefined8 *)(lVar6 + 0x1c8) = local_e0;
    iVar3 = func_0x0002500eecf0(param_5,_kAPTransportConnectionOption_ConnectTimeout,puVar1);
    if (((iVar3 != 0) && (_gLogCategory_APTransportConnectionHTTP < 0x29)) &&
       ((_gLogCategory_APTransportConnectionHTTP != -1 ||
        (iVar3 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x2000028), iVar3 != 0
        )))) {
      _APTransportConnectionHTTPCreate_cold_5(&local_100,puVar1);
    }
    *(long *)(lVar6 + 0x18) = param_2;
    if (param_2 != 0) {
      func_0x0002500903e0(param_2);
    }
    *(undefined4 *)(lVar6 + 0x30) = param_3;
    func_0x0002500ef390(&local_f0,0x80,"APTransportConnectionHTTP.%{ptr}");
    if ((int)param_4 == 0) {
      lVar8 = func_0x000250091070(&local_f0,0);
    }
    else {
      lVar8 = func_0x0002500eeeb0(&local_f0,0,param_4);
    }
    *(long *)(lVar6 + 8) = lVar8;
    if (lVar8 == 0) {
      _APTransportConnectionHTTPCreate_cold_12(&local_f4);
    }
    else {
      func_0x0002500ef390(&local_f0,0x80,"APTransportConnectionHTTP.event.%{ptr}");
      if ((int)param_4 == 0) {
        lVar8 = func_0x000250091070(&local_f0,0);
      }
      else {
        lVar8 = func_0x0002500eeeb0(&local_f0,0,param_4);
      }
      *(long *)(lVar6 + 0x10) = lVar8;
      if (lVar8 == 0) {
        _APTransportConnectionHTTPCreate_cold_11(&local_f4);
      }
      else {
        func_0x0002500ef390(&local_f0,0x80,"APTransportConnectionHTTP.callbackState.%{ptr}");
        lVar8 = func_0x000250091070(&local_f0,0);
        *(long *)(lVar6 + 0x50) = lVar8;
        if (lVar8 == 0) {
          _APTransportConnectionHTTPCreate_cold_10(&local_f4);
        }
        else {
          func_0x0002500ef390(&local_f0,0x80,"APTransportConnectionHTTP.notification.%{ptr}");
          lVar8 = func_0x000250091070(&local_f0,0);
          *(long *)(lVar6 + 0x28) = lVar8;
          if (lVar8 == 0) {
            _APTransportConnectionHTTPCreate_cold_9(&local_f4);
          }
          else {
            if (*(char *)(lVar6 + 0x100) != '\0') {
              lVar8 = func_0x0002500eae50();
              *(long *)(lVar6 + 0x110) = lVar8;
              if (lVar8 == 0) {
                _APTransportConnectionHTTPCreate_cold_6(&local_f4);
                goto LAB_24fdc75b4;
              }
            }
            lVar8 = func_0x0002500eedf0(local_100);
            *(long *)(lVar6 + 0xd8) = lVar8;
            if (lVar8 == 0) {
              _APTransportConnectionHTTPCreate_cold_8(&local_f4);
            }
            else {
              lVar8 = func_0x0002500901d0(*puVar2,0,0,_DAT_2680d3358);
              *(long *)(lVar6 + 0x60) = lVar8;
              if (lVar8 == 0) {
                _APTransportConnectionHTTPCreate_cold_7(&local_f4);
              }
              else {
                *(undefined4 *)(lVar6 + 0x6c) = 0;
                func_0x0002500b8200(&local_118,2000,1000);
                *(undefined8 *)(lVar6 + 0x198) = uStack_110;
                *(undefined8 *)(lVar6 + 400) = local_118;
                *(undefined8 *)(lVar6 + 0x1a0) = local_108;
                if ((_gLogCategory_APTransportConnectionHTTP < 0x33) &&
                   ((_gLogCategory_APTransportConnectionHTTP != -1 ||
                    (iVar3 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x2000032)
                    , iVar3 != 0)))) {
                  func_0x0002500ef250(&_gLogCategory_APTransportConnectionHTTP,
                                      "OSStatus APTransportConnectionHTTPCreate(CFAllocatorRef, CFStringRef, APTransportConnectionFlags, FigThreadPriority, CFDictionaryRef, APTransportConnectionRef *)"
                                      ,0x2000032,
                                      "[%{ptr}] APTransportConnectionHTTP with name %\'@ created. QoS: %d Priority: %u"
                                     );
                }
                _APTTrafficMetricsCreate
                          (&_gLogCategory_APTransportConnectionHTTP,local_100,lVar6 + 0x200,4);
                *param_6 = local_100;
                local_100 = 0;
              }
            }
          }
        }
      }
    }
  }
  else {
    uVar5 = *puVar2;
    lVar7 = func_0x000250090520(uVar5,0,&cfstringStruct_275fa4640);
    lVar8 = func_0x0002500ee370(0x4024000000000000,uVar5,lVar7);
    *(long *)(lVar6 + 0xe8) = lVar8;
    if (lVar8 != 0) goto LAB_24fdc7308;
    _APTransportConnectionHTTPCreate_cold_4(&local_f4);
  }
LAB_24fdc75b4:
  if (lVar7 != 0) {
    func_0x0002500903d0(lVar7);
  }
LAB_24fdc75c0:
  if (local_100 != 0) {
    func_0x0002500903d0();
  }
  if (*_DAT_2681b4ee0 == local_70) {
    return;
  }
  func_0x000250090ec0(local_f4);
  return;
}


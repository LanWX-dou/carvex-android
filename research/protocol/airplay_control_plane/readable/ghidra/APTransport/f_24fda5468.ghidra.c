/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda5468
 * original code SHA256: 1c8273c1e14d43085939e0269ba6be2eeb9de2e4895175d5d12f1517f48b6c3c
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x00024fda54e4) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _httpconnection_sendPackageInternal(undefined8 *param_1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  long lVar6;
  undefined8 uVar7;
  code *pcVar8;
  undefined8 *puVar9;
  long *plVar10;
  long lVar11;
  undefined2 local_70;
  undefined6 uStack_6e;
  undefined8 uStack_68;
  undefined8 local_60;
  
  lVar3 = func_0x0002500e5a60(*param_1);
  plVar10 = param_1 + 1;
  lVar11 = *plVar10;
  lVar4 = func_0x0002500b5820(lVar11);
  puVar9 = (undefined8 *)(*(long *)(lVar4 + 0x10) + 0x18);
  pcVar8 = (code *)*puVar9;
  if ((pcVar8 == (code *)0x0) || (pcVar8 == (code *)0x0)) {
    iVar1 = 0;
  }
  else {
    iVar1 = (*pcVar8)((ulong)puVar9 & 0xffffffffffff | 0x2a67000000000000,lVar11);
  }
  if (*(int *)(lVar3 + 0x6c) == 5) {
    if (*(long *)(lVar3 + 0x108) == 0) {
      _httpconnection_sendPackageInternal_cold_6();
      goto LAB_24fda58b4;
    }
    if (*(long *)(lVar3 + 0x168) != 0) {
      func_0x0002500eea90(*(long *)(lVar3 + 0x108),_DAT_268123930,&cfstringStruct_275fa4700);
    }
    _APTransportPackageHTTPSetURL(*plVar10,*(undefined8 *)(lVar3 + 0x118));
    lVar4 = _APTransportPackageHTTPGetHTTPMessage(*plVar10);
    if (lVar4 == 0) {
      _httpconnection_sendPackageInternal_cold_5();
      goto LAB_24fda58b4;
    }
    lVar11 = lVar4 + 0x18;
    *(int *)(lVar3 + 0x110) = *(int *)(lVar3 + 0x110) + 1;
    func_0x0002500ef110(lVar11,"CSeq","%u");
    if (*(int *)(lVar3 + 0x150) != 0) {
      func_0x0002500ef110(lVar11,"DACP-ID","%llX");
      func_0x0002500ef110(lVar11,"Active-Remote","%u");
    }
    if (*(long *)(lVar3 + 0x20) != 0) {
      func_0x0002500ef110(lVar11,"User-Agent","%s");
    }
    uVar5 = func_0x0002500903e0(*(undefined8 *)(lVar3 + 0xd8));
    *(undefined8 *)(lVar4 + 0x25c8) = uVar5;
    lVar6 = *plVar10;
    *(long *)(lVar4 + 0x25e0) = lVar6;
    if (lVar6 != 0) {
      func_0x0002500903e0();
    }
    *(code **)(lVar4 + 0x25f0) = _httpconnection_httpResponseReceived;
    if (_gLogCategory_APTransportConnectionHTTP < 0x1f) {
      if ((_gLogCategory_APTransportConnectionHTTP != -1) ||
         (iVar2 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x200001e),
         iVar2 != 0)) {
        _httpconnection_sendPackageInternal_cold_1(param_1,plVar10,lVar4);
      }
      if ((_gLogCategory_APTransportConnectionHTTP < 0xb) &&
         ((_gLogCategory_APTransportConnectionHTTP != -1 ||
          (iVar2 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,10), iVar2 != 0))))
      {
        _httpconnection_sendPackageInternal_cold_2(lVar4,lVar11);
      }
    }
    if (((iVar1 == 0x7464776e) || (iVar1 == 0x73747570)) &&
       (func_0x0002500ef180(lVar4,100), *(char *)(lVar3 + 0x270) != '\0')) {
      iVar1 = func_0x0002500a7510();
      if (iVar1 != 0) {
        uVar5 = func_0x0002500eddc0();
        iVar1 = func_0x0002500eec00(*param_1);
        if ((iVar1 != 0) && (iVar2 = func_0x000250093ac0(uVar5), iVar2 != 0)) {
          local_70 = 0;
          func_0x000250093960(&MACH_HEADER,uVar5,1,iVar1,"AP Setup Msg Send Delay","",&local_70,2);
        }
      }
      uVar5 = 0;
      *(long *)(lVar3 + 0x268) = lVar11;
    }
    else {
      uVar5 = 1;
    }
    _APTTrafficMetricsSendStarted
              (*(undefined8 *)(lVar3 + 0x200),*(long *)(lVar4 + 0x2150) + *(long *)(lVar4 + 0x2018))
    ;
    uVar7 = func_0x000250091250();
    *(undefined8 *)(lVar3 + 0x1e8) = uVar7;
    uVar7 = func_0x0002500eefd0(*(undefined8 *)(lVar3 + 0x108),lVar4);
    _APTTrafficMetricsSendFinished
              (*(undefined8 *)(lVar3 + 0x200),uVar7,
               *(long *)(lVar4 + 0x2150) + *(long *)(lVar4 + 0x2018));
    if ((int)uVar7 == 0) {
      uVar5 = *param_1;
      lVar3 = func_0x0002500e5a60(uVar5);
      if (*(int *)(lVar3 + 0x174) == 0) {
        func_0x0002500b5840();
        func_0x0002500b5850(&local_70);
        *(undefined8 *)(lVar3 + 0x180) = uStack_68;
        *(ulong *)(lVar3 + 0x178) = CONCAT62(uStack_6e,local_70);
        *(undefined8 *)(lVar3 + 0x188) = local_60;
        lVar4 = func_0x0002500e5a60(uVar5);
        lVar11 = func_0x0002500eedf0(uVar5);
        if (*(long *)(lVar4 + 0x1a8) == 0) {
          lVar6 = func_0x0002500910d0(_DAT_2681b4e38,0,0,*(undefined8 *)(lVar4 + 8));
          *(long *)(lVar4 + 0x1a8) = lVar6;
          if (lVar6 != 0) {
            func_0x0002500dfc40(lVar6,lVar11);
            func_0x0002500dfc50(*(undefined8 *)(lVar4 + 0x1a8),_httpconnection_checkIfNetworkStalled
                               );
            func_0x0002500ef600(*(undefined8 *)(lVar4 + 0x1a8),
                                _httpconnection_stallMonitorCancelledCallback);
            uVar7 = *(undefined8 *)(lVar4 + 0x1a8);
            uVar5 = func_0x000250091110(0,2000000000);
            func_0x0002500910f0(uVar7,uVar5,2000000000,100000000000);
            func_0x0002500910a0(*(undefined8 *)(lVar4 + 0x1a8));
            goto LAB_24fda584c;
          }
          _httpconnection_sendPackageInternal_cold_4();
        }
        if (lVar11 != 0) {
          func_0x0002500903d0(lVar11);
        }
      }
LAB_24fda584c:
      *(int *)(lVar3 + 0x174) = *(int *)(lVar3 + 0x174) + 1;
      goto LAB_24fda5858;
    }
    _httpconnection_sendPackageInternal_cold_3(uVar7);
  }
  else {
LAB_24fda58b4:
    uVar5 = 1;
  }
  _httpconnection_sendPackageInternal_cold_7(uVar5,param_1,plVar10);
LAB_24fda5858:
  func_0x0002500903d0(param_1[1]);
  func_0x0002500903d0(*param_1);
  return;
}


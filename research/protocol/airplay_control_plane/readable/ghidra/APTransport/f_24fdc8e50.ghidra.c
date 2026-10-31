/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fdc8e50
 * original code SHA256: b445d78444ef8853492a13e2e8aa79cd3ee01a97aaefc9d1b6d7c1be950652e2
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _httpconnection_handleConnectionEstablished(undefined8 param_1,undefined8 param_2)

{
  uint uVar1;
  undefined1 auVar2 [16];
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined8 uVar6;
  int *piVar7;
  long lVar8;
  undefined8 uVar9;
  undefined4 local_c0;
  int iStack_bc;
  undefined8 local_b8;
  undefined8 local_b0;
  undefined *local_a8;
  undefined *puStack_a0;
  char *local_98;
  undefined1 local_90 [16];
  char *local_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  code *local_68;
  undefined8 local_60;
  code *pcStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  pcVar5 = (char *)func_0x0002500e5a60();
  local_c0 = 0;
  iStack_bc = 0;
  if (*pcVar5 != '\0') {
    uVar6 = 0;
    goto LAB_24fdc9060;
  }
  if ((_gLogCategory_APTransportConnectionHTTP < 0x1f) &&
     ((_gLogCategory_APTransportConnectionHTTP != -1 ||
      (iVar3 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x200001e), iVar3 != 0))
     )) {
    _httpconnection_handleConnectionEstablished_cold_1(pcVar5,param_1);
  }
  uVar6 = func_0x0002500bb4b0(param_2,0,pcVar5 + 0x136,0,pcVar5 + 0x130,0,0,0,0,&iStack_bc);
  auVar2._8_8_ = local_90._8_8_;
  auVar2._0_8_ = local_90._0_8_;
  if ((int)uVar6 != 0) {
    _httpconnection_handleConnectionEstablished_cold_2();
    goto LAB_24fdc9060;
  }
  uVar1 = *(uint *)(pcVar5 + 0x30);
  if ((uVar1 & 1) != 0) {
    if (iStack_bc != 4) goto LAB_24fdc8f1c;
    if ((uVar1 >> 3 & 1) == 0) {
      iVar3 = 4;
      goto LAB_24fdc8f28;
    }
LAB_24fdc8f34:
    uVar6 = 0xfffee580;
    local_90 = auVar2;
    if (_gLogCategory_APTransportConnectionHTTP < 0x5b) {
      if (_gLogCategory_APTransportConnectionHTTP == -1) {
        iVar3 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x200005a);
        if (iVar3 == 0) goto LAB_24fdc9060;
      }
      _httpconnection_handleConnectionEstablished_cold_12(param_1);
    }
LAB_24fdc9060:
    if (-1 < (int)param_2) {
      iVar3 = func_0x000250090fd0(param_2);
      if (iVar3 != 0) {
        piVar7 = (int *)func_0x000250090e90();
        if (*piVar7 != 0) {
          func_0x000250090e90();
        }
      }
    }
    return uVar6;
  }
  if (((uVar1 >> 1 & 1) != 0) && (iStack_bc != 4)) {
LAB_24fdc8f1c:
    if (iStack_bc != 0x80) {
      uVar6 = 0xfffee580;
      if (_gLogCategory_APTransportConnectionHTTP < 0x5b) {
        if (_gLogCategory_APTransportConnectionHTTP == -1) {
          iVar3 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x200005a);
          if (iVar3 == 0) goto LAB_24fdc9060;
        }
        _httpconnection_handleConnectionEstablished_cold_3(param_1);
      }
      goto LAB_24fdc9060;
    }
  }
  iVar3 = iStack_bc;
  if ((uVar1 >> 3 & 1) == 0) {
LAB_24fdc8f28:
    if ((uVar1 >> 4 & 1) != 0) goto LAB_24fdc8f2c;
  }
  else {
LAB_24fdc8f2c:
    if (iVar3 != 0x80) goto LAB_24fdc8f34;
  }
  *(int *)(pcVar5 + 0x1b4) = iVar3;
  func_0x0002500ef4e0(param_2,*(undefined4 *)(pcVar5 + 200));
  if (*(long *)(pcVar5 + 0xd0) != 0) {
    local_90._0_8_ = 0;
    local_90._8_8_ = 0;
    local_90 = func_0x0002500905e0();
    func_0x0002500b5f90(param_2,0xffff,0x1108,local_90,0x10);
  }
  local_c0 = 0x1c;
  uVar6 = func_0x0002500b5dd0(param_2,pcVar5 + 0x88,&local_c0);
  if ((int)uVar6 != 0) {
    _httpconnection_handleConnectionEstablished_cold_4();
    goto LAB_24fdc9060;
  }
  local_c0 = 0x1c;
  uVar6 = func_0x0002500b7b10(param_2,pcVar5 + 0xa4,&local_c0);
  if ((int)uVar6 != 0) {
    _httpconnection_handleConnectionEstablished_cold_5();
    goto LAB_24fdc9060;
  }
  uVar4 = func_0x0002500ef440(pcVar5 + 0xa4);
  *(undefined4 *)(pcVar5 + 0xc0) = uVar4;
  if (pcVar5[0xa5] == '\x1e') {
    uVar6 = 0x29;
    uVar9 = 0x7d;
LAB_24fdc90a0:
    local_c0 = 4;
    iVar3 = func_0x0002500b7b20(param_2,uVar6,uVar9,pcVar5 + 0xc4,&local_c0);
    if (iVar3 != 0) goto LAB_24fdc90a8;
  }
  else {
    if (pcVar5[0xa5] == '\x02') {
      uVar6 = 0;
      uVar9 = 0x19;
      goto LAB_24fdc90a0;
    }
LAB_24fdc90a8:
    pcVar5[0xc4] = '\0';
    pcVar5[0xc5] = '\0';
    pcVar5[0xc6] = '\0';
    pcVar5[199] = '\0';
  }
  uVar6 = *(undefined8 *)(pcVar5 + 0x208);
  lVar8 = func_0x0002500e5a60(param_1);
  if (*(long *)(lVar8 + 0x208) != 0) {
    _APTransportTrafficCaptureOpenTCPStream(uVar6,pcVar5 + 0x88,pcVar5 + 0xa4,pcVar5 + 0x210);
  }
  if (pcVar5[0x100] == '\0') {
    uVar6 = _httpConnection_setupHTTPClient(param_1,param_2);
    if ((int)uVar6 == 0) {
      return uVar6;
    }
    _httpconnection_handleConnectionEstablished_cold_11(uVar6);
    return uVar6;
  }
  pcVar5 = (char *)func_0x0002500e5a60(param_1);
  pcStack_58 = (code *)0x0;
  local_60 = 0;
  uStack_48 = 0;
  uStack_50 = 0;
  uStack_78 = 0;
  local_80 = (char *)0x0;
  local_68 = (code *)0x0;
  uStack_70 = 0;
  local_90._8_8_ = 0;
  local_90._0_8_ = 0;
  if (*pcVar5 == '\0') {
    local_80 = "RTSP/1.0";
    pcStack_58 = _httpconnection_handleEvent;
    local_68 = _httpconnection_handleConnectionClosed;
    uVar6 = func_0x0002500ef070(pcVar5 + 0x108,local_90,param_2,0);
    if ((int)uVar6 == 0) {
      uVar6 = 0;
      if (*(long *)(pcVar5 + 0xd8) != 0) {
        uVar6 = func_0x0002500903e0();
      }
      *(undefined8 *)(*(long *)(pcVar5 + 0x108) + 0x180) = uVar6;
      if (*(long *)(*(long *)(pcVar5 + 0x108) + 0x180) == 0) {
        _httpconnection_handleConnectionEstablished_cold_10();
        uVar6 = 0xfffee57d;
      }
      else {
        func_0x0002500ef0a0(*(long *)(pcVar5 + 0x108),*(undefined8 *)(pcVar5 + 0x10));
        local_b8 = _DAT_2681b4ed0;
        local_b0 = DAT_24fe44b40;
        local_a8 = &___httpConnection_setupHTTPServer_block_invoke;
        puStack_a0 = &___block_descriptor_tmp_106;
        local_98 = pcVar5;
        _httpConnectionCapture_setCapturingDelegateIfNeeded(param_1,&local_b8);
        if ((*(long *)(pcVar5 + 0x70) != 0) && (*(long *)(pcVar5 + 0x78) != 0)) {
          if ((_gLogCategory_APTransportConnectionHTTP < 0x1f) &&
             ((_gLogCategory_APTransportConnectionHTTP != -1 ||
              (iVar3 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x200001e),
              iVar3 != 0)))) {
            _httpconnection_handleConnectionEstablished_cold_7(param_1);
          }
          uVar6 = _httpconnection_configureEncryptionInternal
                            (param_1,*(undefined8 *)(pcVar5 + 0x70),*(undefined8 *)(pcVar5 + 0x78));
          if (*(long *)(pcVar5 + 0x70) != 0) {
            func_0x0002500903d0();
            pcVar5[0x70] = '\0';
            pcVar5[0x71] = '\0';
            pcVar5[0x72] = '\0';
            pcVar5[0x73] = '\0';
            pcVar5[0x74] = '\0';
            pcVar5[0x75] = '\0';
            pcVar5[0x76] = '\0';
            pcVar5[0x77] = '\0';
          }
          if (*(long *)(pcVar5 + 0x78) != 0) {
            func_0x0002500903d0();
            pcVar5[0x78] = '\0';
            pcVar5[0x79] = '\0';
            pcVar5[0x7a] = '\0';
            pcVar5[0x7b] = '\0';
            pcVar5[0x7c] = '\0';
            pcVar5[0x7d] = '\0';
            pcVar5[0x7e] = '\0';
            pcVar5[0x7f] = '\0';
          }
          if ((int)uVar6 != 0) {
            _httpconnection_handleConnectionEstablished_cold_8(uVar6);
            goto LAB_24fdc93a4;
          }
        }
        if (*(int *)(pcVar5 + 0x158) != 0) {
          func_0x0002500ef0b0(*(undefined8 *)(pcVar5 + 0x108));
        }
        uVar6 = func_0x0002500ef0d0(*(undefined8 *)(pcVar5 + 0x108));
        if ((int)uVar6 == 0) {
          if ((_gLogCategory_APTransportConnectionHTTP < 0x33) &&
             ((_gLogCategory_APTransportConnectionHTTP != -1 ||
              (iVar3 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x2000032),
              iVar3 != 0)))) {
            func_0x0002500ef250(&_gLogCategory_APTransportConnectionHTTP,
                                "OSStatus httpConnection_setupHTTPServer(APTransportConnectionRef, SocketRef)"
                                ,0x2000032,"[%{ptr}] HTTPServer connected to %##a (from %##a)");
          }
          return 0;
        }
        _httpconnection_handleConnectionEstablished_cold_9();
      }
      goto LAB_24fdc93a4;
    }
    _httpconnection_handleConnectionEstablished_cold_6();
  }
  else {
    uVar6 = 0;
  }
  if (((-1 < (int)param_2) && (iVar3 = func_0x000250090fd0(param_2), iVar3 != 0)) &&
     (piVar7 = (int *)func_0x000250090e90(), *piVar7 != 0)) {
    func_0x000250090e90();
  }
  if ((int)uVar6 == 0) {
    return uVar6;
  }
LAB_24fdc93a4:
  func_0x0002500ee220(uVar6,"httpconnection_handleConnectionEstablished",0x50d,0);
  return uVar6;
}


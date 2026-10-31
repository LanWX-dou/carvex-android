/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda58ec
 * original code SHA256: 6a4552591408d3fc25dabbd8cefce2cffffd6c0c8a308e338672b2df9d62ab5e
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _APTransportPackageHTTPGetHTTPMessage(undefined8 param_1)

{
  int iVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  bool bVar7;
  undefined8 uVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  char *pcVar12;
  undefined8 uVar13;
  undefined8 local_118;
  ulong local_110;
  ulong uStack_108;
  long local_100;
  char *local_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  long local_68;
  
  local_68 = *_DAT_2681b4ee0;
  plVar3 = (long *)func_0x0002500e5a60();
  pcVar9 = (char *)0x0;
  local_100 = 0;
  local_f8 = (char *)0x0;
  iVar1 = (int)plVar3[1];
  uStack_88 = 0;
  local_90 = 0;
  uStack_78 = 0;
  uStack_80 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  pcVar10 = "application/x-apple-binary-plist";
  if (0x70617573 < iVar1) {
    if (iVar1 < 0x7365656b) {
      if (0x7073706b < iVar1) {
        if (iVar1 < 0x72616174) {
          if (iVar1 != 0x7073706c) {
            if (iVar1 == 0x7073756c) {
              pcVar12 = "/pair-setup";
              goto LAB_24fda62d8;
            }
            iVar2 = 0x70766f6c;
LAB_24fda5dc8:
            if (iVar1 == iVar2) {
              pcVar9 = (char *)0x0;
              pcVar12 = (char *)0x0;
              bVar7 = true;
              goto LAB_24fda61c8;
            }
            goto LAB_24fda679c;
          }
          pcVar12 = "/pair-setup-pin";
        }
        else {
          if (0x72637263 < iVar1) {
            if (iVar1 == 0x72637264) {
              lVar4 = 0;
              pcVar9 = "application/x-apple-binary-plist";
              pcVar11 = "RECORD";
              goto LAB_24fda6300;
            }
            if (iVar1 == 0x72736120) goto LAB_24fda5f70;
            goto LAB_24fda679c;
          }
          if (iVar1 != 0x72616174) {
            iVar2 = 0x72617465;
            goto LAB_24fda5dc8;
          }
          pcVar12 = "/rateandanchortime";
        }
        goto LAB_24fda62c0;
      }
      if (iVar1 < 0x706e666f) {
        if (iVar1 == 0x70617574) {
          bVar7 = false;
          pcVar12 = "/authorize";
          pcVar9 = "text/parameters";
        }
        else {
          if (iVar1 != 0x70617665) {
            if (iVar1 == 0x706c6179) {
              pcVar12 = "/play";
              goto LAB_24fda62c0;
            }
            goto LAB_24fda679c;
          }
          pcVar12 = "/pair-verify";
LAB_24fda6184:
          bVar7 = false;
          pcVar9 = "application/octet-stream";
        }
      }
      else {
        if (iVar1 < 0x70707374) {
          if (iVar1 == 0x706e666f) {
            pcVar10 = (char *)0x0;
            pcVar12 = "/playback-info";
            goto LAB_24fda6298;
          }
          if (iVar1 == 0x706e6720) {
            pcVar9 = "image/png";
            goto LAB_24fda6130;
          }
          goto LAB_24fda679c;
        }
        if (iVar1 != 0x70707374) {
          iVar2 = 0x70726f67;
          goto LAB_24fda5e94;
        }
        pcVar9 = (char *)0x0;
        bVar7 = false;
        pcVar12 = "/pair-pin-start";
      }
LAB_24fda61c8:
      pcVar11 = "POST";
LAB_24fda61d0:
      if (plVar3[2] == 0) {
        lVar4 = 0;
joined_r0x00024fda6280:
        if (!bVar7) goto LAB_24fda6314;
        goto LAB_24fda6300;
      }
      uVar8 = *_DAT_2680d3150;
      iVar1 = func_0x0002500eee80(uVar8,plVar3[2],0,0,&local_100);
      if (iVar1 != 0) {
        _APTransportPackageHTTPGetHTTPMessage_cold_1();
        goto LAB_24fda67e4;
      }
      lVar4 = func_0x0002500903c0(uVar8,local_100,0,0,0);
      if (lVar4 != 0) {
        lVar5 = func_0x000250090270(lVar4);
        lVar6 = func_0x000250090210();
        if (lVar5 == lVar6) {
          uVar13 = *_DAT_2681041d8;
          uVar8 = func_0x000250090580();
          lVar5 = func_0x0002500a4560(lVar4,uVar13,uVar8,0);
          if (lVar5 != 0) {
            lVar6 = *plVar3;
            *plVar3 = lVar5;
            func_0x0002500903e0();
            if (lVar6 != 0) {
              func_0x0002500903d0(lVar6);
            }
          }
          goto joined_r0x00024fda6280;
        }
      }
      _APTransportPackageHTTPGetHTTPMessage_cold_2();
    }
    else {
      if (iVar1 < 0x73747274) {
        if (iVar1 < 0x73707072) {
          if (iVar1 == 0x7365656b) {
LAB_24fda5fec:
            pcVar12 = (char *)0x0;
            bVar7 = true;
            goto LAB_24fda60e4;
          }
          if (iVar1 == 0x73657065) {
            lVar4 = 0;
            pcVar9 = "/peer-list-changed";
            pcVar11 = "SETPEERS";
          }
          else {
            if (iVar1 != 0x73657078) goto LAB_24fda679c;
            lVar4 = 0;
            pcVar9 = "/peer-list-changed-x";
            pcVar11 = "SETPEERSX";
          }
        }
        else if (iVar1 < 0x73736470) {
          if (iVar1 == 0x73707072) {
            pcVar12 = (char *)0x0;
            bVar7 = true;
            pcVar9 = "application/x-apple-binary-plist";
            pcVar11 = "PUT";
            goto LAB_24fda61d0;
          }
          if (iVar1 != 0x73726174) goto LAB_24fda679c;
          lVar4 = 0;
          pcVar9 = "application/x-apple-binary-plist";
          pcVar11 = "SETRATEANCHORTIME";
        }
        else {
          if (iVar1 != 0x73736470) {
            if (iVar1 == 0x73746f70) {
              pcVar9 = (char *)0x0;
              pcVar12 = "/stop";
              goto LAB_24fda62e0;
            }
            goto LAB_24fda679c;
          }
          lVar4 = 0;
          pcVar9 = (char *)0x0;
          pcVar11 = "SETUP";
        }
      }
      else if (iVar1 < 0x7464776e) {
        if (iVar1 == 0x73747274) {
          lVar4 = 0;
          pcVar9 = "application/x-apple-binary-plist";
          pcVar11 = "SETRATE";
        }
        else {
          if (iVar1 != 0x73747570) {
            iVar2 = 0x73766f6c;
LAB_24fda5e94:
            if (iVar1 == iVar2) {
              pcVar9 = "text/parameters";
              goto LAB_24fda6130;
            }
            goto LAB_24fda679c;
          }
          pcVar11 = "SETUP";
          lVar4 = 0;
          pcVar9 = "application/x-apple-binary-plist";
        }
      }
      else {
        if (iVar1 < 0x74736470) {
          if (iVar1 != 0x7464776e) {
            if (iVar1 != 0x74657874) goto LAB_24fda679c;
            pcVar9 = "application/x-dmap-tagged";
LAB_24fda6130:
            lVar4 = 0;
            pcVar11 = "SET_PARAMETER";
            goto LAB_24fda6300;
          }
          pcVar9 = "application/x-apple-binary-plist";
        }
        else {
          if (iVar1 != 0x74736470) {
            if (iVar1 == 0x7a6c6c20) {
              pcVar9 = "application/x-apple-binary-plist";
              goto LAB_24fda6130;
            }
            goto LAB_24fda679c;
          }
          pcVar9 = (char *)0x0;
        }
        lVar4 = 0;
        pcVar11 = "TEARDOWN";
      }
LAB_24fda6300:
      iVar1 = func_0x0002500eeae0(*plVar3,&local_f8);
      pcVar12 = local_f8;
      if (iVar1 == 0) goto LAB_24fda6314;
      _APTransportPackageHTTPGetHTTPMessage_cold_3();
    }
    goto LAB_24fda67e8;
  }
  if (iVar1 < 0x696e666f) {
    if (iVar1 < 0x636f6e66) {
      if (iVar1 < 0x616e6e63) {
        if (iVar1 == 0x6163746e) {
          pcVar12 = "/action";
        }
        else {
          if (iVar1 != 0x616d736d) {
            if (iVar1 != 0x616e6368) goto LAB_24fda679c;
            lVar4 = 0;
            pcVar9 = "application/x-apple-binary-plist";
            pcVar11 = "GETANCHOR";
            goto LAB_24fda6300;
          }
          pcVar12 = "/audioMode";
        }
LAB_24fda62c0:
        pcVar9 = "application/x-apple-binary-plist";
        goto LAB_24fda62e0;
      }
      if (iVar1 < 0x61757468) {
        if (iVar1 == 0x616e6e63) {
          lVar4 = 0;
          pcVar9 = "application/sdp";
          pcVar11 = "ANNOUNCE";
          goto LAB_24fda6300;
        }
        if (iVar1 == 0x61737570) {
          bVar7 = false;
          pcVar12 = "/auth-setup";
          goto LAB_24fda60e4;
        }
      }
      else {
        if (iVar1 == 0x61757468) goto LAB_24fda5f70;
        if (iVar1 == 0x636f6d6d) {
          pcVar12 = "/command";
          goto LAB_24fda62c0;
        }
      }
    }
    else {
      if (0x66703234 < iVar1) {
        if (iVar1 < 0x67707072) {
          if (iVar1 == 0x66703235) {
            pcVar12 = "/fp-setup";
            goto LAB_24fda62d8;
          }
          if (iVar1 != 0x66736862) goto LAB_24fda679c;
          lVar4 = 0;
          pcVar9 = "application/x-apple-binary-plist";
          pcVar11 = "FLUSHBUFFERED";
        }
        else {
          if (iVar1 == 0x67707072) goto LAB_24fda5fec;
          if (iVar1 != 0x67766f6c) goto LAB_24fda679c;
          lVar4 = 0;
          pcVar9 = "text/parameters";
          pcVar11 = "GET_PARAMETER";
        }
        goto LAB_24fda6300;
      }
      if (iVar1 == 0x636f6e66) {
        pcVar12 = "/configure";
        goto LAB_24fda62c0;
      }
      if (iVar1 == 0x65737070) {
        pcVar9 = (char *)0x0;
        pcVar12 = "/ensure-pair-pin";
        goto LAB_24fda62e0;
      }
      if (iVar1 == 0x666c7368) {
        bVar7 = true;
        pcVar11 = "FLUSH";
        pcVar12 = (char *)0x0;
        goto LAB_24fda61d0;
      }
    }
LAB_24fda679c:
    if ((_gLogCategory_APTransportPackageHTTP < 0x33) &&
       ((_gLogCategory_APTransportPackageHTTP != -1 ||
        (iVar2 = func_0x0002500a8720(&_gLogCategory_APTransportPackageHTTP,0x2000032), iVar2 != 0)))
       ) {
      _APTransportPackageHTTPGetHTTPMessage_cold_21(iVar1);
    }
    func_0x0002500ee220(0xffffbefd,"APTransportPackageHTTPGetHTTPMessage",0x3b7,0);
    goto LAB_24fda67e4;
  }
  if (iVar1 < 0x6d666920) {
    if (iVar1 < 0x6c6b6565) {
      if (iVar1 != 0x696e666f) {
        if (iVar1 == 0x6a706567) {
          pcVar9 = "image/jpeg";
          goto LAB_24fda6130;
        }
        if (iVar1 == 0x6b656570) {
          pcVar12 = "/feedback";
          goto LAB_24fda62c0;
        }
        goto LAB_24fda679c;
      }
      pcVar12 = "/info";
LAB_24fda6298:
      lVar4 = 0;
      pcVar11 = "GET";
      pcVar9 = pcVar10;
    }
    else {
      if (0x6c6f7563 < iVar1) {
        if (iVar1 == 0x6c6f7564) {
          lVar4 = 0;
          pcVar9 = "application/x-apple-binary-plist";
          pcVar11 = "LOUDNESSNORMALIZATION";
        }
        else {
          if (iVar1 != 0x6d616763) goto LAB_24fda679c;
          lVar4 = 0;
          pcVar9 = "application/x-apple-binary-plist";
          pcVar11 = "SETMAGICCOOKIE";
        }
        goto LAB_24fda6300;
      }
      if (iVar1 != 0x6c6b6565) {
        if (iVar1 == 0x6c6f6773) {
          pcVar12 = "/logs";
          pcVar10 = "application/x-apple-binary-plist";
          goto LAB_24fda6298;
        }
        goto LAB_24fda679c;
      }
LAB_24fda5f70:
      lVar4 = 0;
      pcVar11 = "OPTIONS";
      pcVar9 = (char *)0x0;
      pcVar12 = "*";
    }
  }
  else {
    if (0x7061616f < iVar1) {
      if (iVar1 < 0x70617270) {
        if (iVar1 == 0x70616170) {
          bVar7 = false;
          pcVar12 = "/pair-add";
        }
        else {
          if (iVar1 != 0x70616c70) goto LAB_24fda679c;
          bVar7 = false;
          pcVar12 = "/pair-list";
        }
      }
      else if (iVar1 == 0x70617270) {
        bVar7 = false;
        pcVar12 = "/pair-remove";
      }
      else {
        if (iVar1 != 0x70617365) goto LAB_24fda679c;
        bVar7 = false;
        pcVar12 = "/pair-setup";
      }
LAB_24fda60e4:
      pcVar9 = "application/x-apple-binary-plist";
      goto LAB_24fda61c8;
    }
    if (iVar1 != 0x6d666920) {
      if (iVar1 == 0x6d66696d) {
        pcVar12 = "/auth-setup";
        goto LAB_24fda6184;
      }
      if (iVar1 == 0x6e6f6e65) {
        pcVar9 = "image/none";
        goto LAB_24fda6130;
      }
      goto LAB_24fda679c;
    }
    pcVar12 = "/auth-setup";
LAB_24fda62d8:
    pcVar9 = "application/octet-stream";
LAB_24fda62e0:
    lVar4 = 0;
    pcVar11 = "POST";
  }
LAB_24fda6314:
  iVar1 = func_0x0002500ef100(plVar3[3] + 0x18,pcVar11,pcVar12,"RTSP/1.0");
  if (iVar1 == 0) {
    lVar5 = func_0x0002500e5a60(param_1);
    if ((*(int *)(lVar5 + 8) == 0x73747570) || (*(int *)(lVar5 + 8) == 0x696e666f)) {
      lVar5 = *(long *)(lVar5 + 0x18);
      func_0x0002500ee660();
      iVar1 = func_0x0002500ef110(lVar5 + 0x18,"X-Apple-ProtocolVersion","%u");
      if (iVar1 != 0) {
        _APTransportPackageHTTPGetHTTPMessage_cold_5();
        goto LAB_24fda67e8;
      }
    }
    if ((int)plVar3[1] == 0x706c6179) {
      lVar5 = plVar3[3];
      func_0x0002500ef270(0,&local_f0,0x40);
      func_0x0002500ef110(lVar5 + 0x18,"X-Transmit-Date","%s");
    }
    else if (((int)plVar3[1] == 0x66703235) &&
            (iVar1 = func_0x0002500ef110(plVar3[3] + 0x18,"X-Apple-ET","%u"), iVar1 != 0)) {
      _APTransportPackageHTTPGetHTTPMessage_cold_6();
      goto LAB_24fda67e8;
    }
    if ((plVar3[4] == 0) ||
       (iVar1 = func_0x0002500ef110(plVar3[3] + 0x18,"X-Apple-StreamID","%llu"), iVar1 == 0)) {
      if (lVar4 == 0) {
        if (plVar3[2] == 0) goto LAB_24fda655c;
        local_110 = 0;
        uStack_108 = 0;
        local_118 = 0;
        iVar1 = func_0x0002500b5830(plVar3[2],0,&uStack_108,&local_110,&local_118);
        if (iVar1 != 0) {
          _APTransportPackageHTTPGetHTTPMessage_cold_9();
          goto LAB_24fda67e4;
        }
        iVar1 = (int)plVar3[1];
        if (iVar1 < 0x70726f67) {
          if (((iVar1 == 0x6a706567) || (iVar1 == 0x6e6f6e65)) || (iVar1 == 0x706e6720))
          goto LAB_24fda65f4;
LAB_24fda6760:
          if (uStack_108 != local_110) {
            _APTransportPackageHTTPGetHTTPMessage_cold_19();
            goto LAB_24fda67e4;
          }
          uVar8 = func_0x0002500ef150(plVar3[3],pcVar9,local_118);
          iVar1 = func_0x0002500a7510();
          bVar7 = iVar1 != 0;
          if (bVar7) {
            _httpPackage_computeMessageTypeString(param_1,local_118,local_110,&local_b0);
          }
          if ((int)uVar8 != 0) {
            _APTransportPackageHTTPGetHTTPMessage_cold_20(uVar8);
            goto LAB_24fda67e4;
          }
        }
        else {
          if (iVar1 < 0x73736470) {
            if (iVar1 != 0x70726f67) {
              if (iVar1 != 0x72736120) goto LAB_24fda6760;
              if (uStack_108 == local_110) {
                iVar1 = func_0x0002500ef110(plVar3[3] + 0x18,"Apple-Challenge","%.*s");
                if (iVar1 == 0) goto LAB_24fda668c;
                _APTransportPackageHTTPGetHTTPMessage_cold_16();
              }
              else {
                _APTransportPackageHTTPGetHTTPMessage_cold_15();
              }
              goto LAB_24fda67e4;
            }
LAB_24fda65f4:
            iVar1 = func_0x0002500ef110(plVar3[3] + 0x18,"RTP-Info","rtptime=%u");
            if (iVar1 == 0) {
              if (local_110 < 5) {
                iVar1 = func_0x0002500ef150(plVar3[3],pcVar9,0,0);
                if (iVar1 == 0) goto LAB_24fda668c;
                _APTransportPackageHTTPGetHTTPMessage_cold_11();
              }
              else {
                iVar1 = func_0x0002500b5830(plVar3[2],4,&uStack_108,&local_110,&local_118);
                if (iVar1 == 0) {
                  if (uStack_108 + 4 == local_110) {
                    iVar1 = func_0x0002500ef150(plVar3[3],pcVar9,local_118);
                    if (iVar1 == 0) goto LAB_24fda668c;
                    _APTransportPackageHTTPGetHTTPMessage_cold_14();
                  }
                  else {
                    _APTransportPackageHTTPGetHTTPMessage_cold_13();
                  }
                }
                else {
                  _APTransportPackageHTTPGetHTTPMessage_cold_12();
                }
              }
            }
            else {
              _APTransportPackageHTTPGetHTTPMessage_cold_10();
            }
LAB_24fda67e4:
            lVar4 = 0;
            goto LAB_24fda67e8;
          }
          if (iVar1 == 0x74657874) goto LAB_24fda65f4;
          if (iVar1 != 0x73736470) goto LAB_24fda6760;
          if (uStack_108 != local_110) {
            _APTransportPackageHTTPGetHTTPMessage_cold_17();
            goto LAB_24fda67e4;
          }
          iVar1 = func_0x0002500ef110(plVar3[3] + 0x18,"Transport","%.*s");
          if (iVar1 != 0) {
            _APTransportPackageHTTPGetHTTPMessage_cold_18();
            goto LAB_24fda67e4;
          }
LAB_24fda668c:
          bVar7 = false;
        }
        bVar7 = !bVar7;
      }
      else {
        func_0x000250092a70(lVar4,_httppackage_appendCustomHeaderField,param_1);
        uVar13 = *_DAT_2681041b8;
        uVar8 = func_0x000250090180();
        lVar5 = func_0x0002500a4560(lVar4,uVar13,uVar8,0);
        if (lVar5 != 0) {
          uVar8 = func_0x000250090160();
          uVar13 = func_0x000250090140(lVar5);
          iVar1 = func_0x0002500ef150(plVar3[3],pcVar9,uVar13,uVar8);
          if (iVar1 != 0) {
            _APTransportPackageHTTPGetHTTPMessage_cold_8();
            goto LAB_24fda67e8;
          }
        }
LAB_24fda655c:
        bVar7 = true;
      }
      iVar1 = func_0x0002500a7510();
      if (((iVar1 != 0) || ((int)plVar3[1] == 0x7464776e)) || ((int)plVar3[1] == 0x73747570)) {
        if (bVar7) {
          _httpPackage_computeMessageTypeString(param_1,0,0,&local_b0);
        }
        if ((char)local_b0 != '\0') {
          func_0x0002500ef160(plVar3[3],&local_b0);
        }
      }
      lVar5 = plVar3[3];
      goto LAB_24fda66bc;
    }
    _APTransportPackageHTTPGetHTTPMessage_cold_7();
  }
  else {
    _APTransportPackageHTTPGetHTTPMessage_cold_4();
  }
LAB_24fda67e8:
  lVar5 = 0;
LAB_24fda66bc:
  if (local_f8 != (char *)0x0) {
    func_0x0002500911b0();
    local_f8 = (char *)0x0;
  }
  if (local_100 != 0) {
    func_0x0002500903d0();
  }
  if (lVar4 != 0) {
    func_0x0002500903d0(lVar4);
  }
  if (*_DAT_2681b4ee0 == local_68) {
    return lVar5;
  }
  lVar4 = func_0x000250090ec0();
  return lVar4;
}


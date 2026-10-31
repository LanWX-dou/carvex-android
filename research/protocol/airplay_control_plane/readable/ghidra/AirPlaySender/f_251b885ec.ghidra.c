/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b885ec
 * original code SHA256: 1331b897c2c2d3d78e8a112b7802471fd473657cd04e351160d8b5a83c312872
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined *
_coreUtilsPairing_sendPairingRequest
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4,long param_5,
          int param_6,int param_7,long param_8,long param_9,undefined8 *param_10,
          undefined8 *param_11,undefined8 *param_12)

{
  undefined1 auVar1 [16];
  undefined1 in_ZR;
  int iVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  undefined *puVar7;
  long lVar8;
  undefined8 extraout_x1;
  undefined8 extraout_x1_00;
  undefined8 extraout_x1_01;
  ulong extraout_x1_02;
  ulong uVar9;
  undefined8 extraout_x8;
  undefined8 uVar10;
  bool bVar11;
  undefined *puVar12;
  undefined1 auVar13 [16];
  undefined *local_130;
  long local_128;
  long local_120;
  ulong local_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
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
  undefined1 auStack_90 [32];
  undefined8 local_70;
  
  _OUTLINED_FUNCTION_13();
  local_70 = extraout_x8;
  lVar3 = func_0x00025810ac50();
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
  uStack_108 = 0;
  local_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  local_128 = 0;
  local_120 = 0;
  local_130 = (undefined *)0x0;
  uVar10 = *_DAT_2680d3150;
  _OUTLINED_FUNCTION_1();
  lVar4 = func_0x000258101820(uVar10,0);
  if (lVar4 == 0) {
    uVar10 = 0x5eb;
LAB_251b88b4c:
    func_0x000258109a30(0,"coreUtilsPairing_sendPairingRequest",uVar10,0);
    puVar7 = (undefined *)0xfffee7a6;
    goto LAB_251b88a8c;
  }
  lVar5 = lVar4;
  if (param_6 != 0) {
    lVar5 = _OUTLINED_FUNCTION_21(lVar4,_kAPPairingClientHeader_PairDerive);
  }
  if ((param_7 != 0) && (param_8 != 0)) {
    _OUTLINED_FUNCTION_21(lVar5,_kAPPairingClientHeader_UsingNANDiversifiedPINAsSetupCode);
    func_0x0002580f7000(lVar4,_kAPPairingClientHeader_NANMACAddress,param_8);
  }
  if (param_9 != 0) {
    func_0x0002580f7000(lVar4,_kAPPairingClientHeader_SupportedPINLengths,param_9);
  }
  func_0x00025810d4e0(&local_110,0x80);
  func_0x00025810a760(lVar4,_kAPPairingClientHeader_ClientName,&local_110,0xffffffffffffffff);
  func_0x000258109610(&local_120);
  func_0x00025810b180(lVar4,_kAPPairingClientHeader_ClientID,local_120);
  func_0x0002580f6900(auStack_90,0x20,"%d");
  uVar6 = func_0x00025810a760(lVar4,_kAPPairingClientHeader_CoreUtilsPairing,auStack_90,
                              0xffffffffffffffff);
  if (param_12 != (undefined8 *)0x0) {
    _OUTLINED_FUNCTION_21(uVar6,&cfstringStruct_276136470);
    in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x32;
    if ((_gLogCategory_APPairingClientCoreUtils < 0x33) &&
       ((in_ZR = _gLogCategory_APPairingClientCoreUtils == -1, !(bool)in_ZR ||
        (iVar2 = _OUTLINED_FUNCTION_7(), iVar2 != 0)))) {
      uVar6 = _OUTLINED_FUNCTION_8();
      _OUTLINED_FUNCTION_10
                (uVar6,
                 "OSStatus coreUtilsPairing_sendPairingRequest(APPairingClientRef, APPairingType, OSType, const uint8_t *, size_t, Boolean, Boolean, CFStringRef, CFStringRef, CFNumberRef *, CMBlockBufferRef *, CFDictionaryRef *)"
                );
    }
  }
  auVar13 = func_0x00025810fe60();
  if (auVar13._0_4_ != 0) {
    func_0x0002580f5410();
    func_0x00025810a1a0(&local_128,"%lld");
    if (local_128 == 0) {
      uVar10 = 0x616;
      goto LAB_251b88b4c;
    }
    auVar13 = func_0x00025810a760(lVar4,_kAPPairingClientHeader_AbsoluteTime,local_128,
                                  0xffffffffffffffff);
  }
  if ((param_4 != 0) && (param_5 != 0)) {
    auVar13 = func_0x00025810a770(lVar4,*_DAT_2681041b8,param_4,param_5);
  }
  in_ZR = _gLogCategory_APPairingClientCoreUtils == 10;
  if (_gLogCategory_APPairingClientCoreUtils < 0xb) {
    in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
    if ((bool)in_ZR) {
      _OUTLINED_FUNCTION_8(auVar13._0_8_,0x200000a);
      auVar13 = func_0x000258101e40();
      if (auVar13._0_4_ == 0) goto LAB_251b88858;
    }
    uVar6 = _OUTLINED_FUNCTION_8(auVar13._0_8_,auVar13._8_8_,0x200000a);
    func_0x000258101eb0(uVar6,
                        "OSStatus coreUtilsPairing_sendPairingRequest(APPairingClientRef, APPairingType, OSType, const uint8_t *, size_t, Boolean, Boolean, CFStringRef, CFStringRef, CFNumberRef *, CMBlockBufferRef *, CFDictionaryRef *)"
                       );
  }
LAB_251b88858:
  puVar7 = (undefined *)func_0x00025810e4f0(*(undefined8 *)(lVar3 + 0x30),param_3,lVar4,&local_130);
  puVar12 = local_130;
  if ((int)puVar7 != 0) goto LAB_251b88a8c;
  local_118 = 0;
  if ((local_130 == (undefined *)0x0) ||
     (func_0x00025810f2b0(uVar10,local_130,0,0,&local_118), local_118 == 0)) {
    lVar3 = 0;
joined_r0x000251b88af4:
    if (param_10 != (undefined8 *)0x0) {
      uVar10 = func_0x0002580f6a60(&DAT_276141a48);
      *param_10 = uVar10;
    }
    if (param_12 != (undefined8 *)0x0) {
      *param_12 = 0;
    }
    if (param_11 == (undefined8 *)0x0) {
LAB_251b88a68:
      puVar12 = (undefined *)0x0;
    }
    else {
      if (puVar12 == (undefined *)0x0) {
        uVar10 = 0;
      }
      else {
        uVar10 = func_0x0002580f6a60(puVar12);
      }
      puVar12 = (undefined *)0x0;
      *param_11 = uVar10;
    }
  }
  else {
    lVar5 = func_0x00025810a9a0(uVar10,local_118,0,0,0);
    if (lVar5 == 0) {
LAB_251b88afc:
      lVar3 = 0;
      bVar11 = true;
    }
    else {
      lVar3 = func_0x0002580f6a50(lVar5);
      lVar8 = func_0x000258102670();
      in_ZR = lVar3 == lVar8;
      if (!(bool)in_ZR) goto LAB_251b88afc;
      bVar11 = false;
      lVar3 = lVar5;
      lVar5 = 0;
    }
    if (local_118 != 0) {
      func_0x0002580f5830();
    }
    if (lVar5 != 0) {
      func_0x0002580f5830(lVar5);
    }
    if (bVar11) goto joined_r0x000251b88af4;
    if (param_10 != (undefined8 *)0x0) {
      local_118 = local_118 & 0xffffffff00000000;
      iVar2 = func_0x00025810b0b0(lVar3,*_DAT_268104108,&local_118);
      if (iVar2 == 0) {
        puVar12 = &DAT_276141a48;
        in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x32;
        if ((_gLogCategory_APPairingClientCoreUtils < 0x33) &&
           ((in_ZR = _gLogCategory_APPairingClientCoreUtils == -1, !(bool)in_ZR ||
            (iVar2 = _OUTLINED_FUNCTION_7(), iVar2 != 0)))) {
          uVar6 = _OUTLINED_FUNCTION_8();
          _OUTLINED_FUNCTION_10
                    (uVar6,
                     "CFNumberRef coreUtilsPairing_copyPINLengthFromResponse(APPairingClientRef, CFDictionaryRef)"
                    );
        }
      }
      else {
        uVar9 = local_118 & 0xffffffff;
        if ((int)local_118 - 0xffU < 0xffffff02) {
          in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x5a;
          if (_gLogCategory_APPairingClientCoreUtils < 0x5b) {
            in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
            if ((bool)in_ZR) {
              uVar6 = _OUTLINED_FUNCTION_8();
              iVar2 = func_0x000258101e40(uVar6,0x200005a);
              if (iVar2 == 0) {
                puVar12 = &DAT_276141a48;
                goto LAB_251b889b4;
              }
            }
            uVar6 = _OUTLINED_FUNCTION_8();
            func_0x000258101eb0(uVar6,
                                "CFNumberRef coreUtilsPairing_copyPINLengthFromResponse(APPairingClientRef, CFDictionaryRef)"
                                ,0x200005a,
                                "[%{ptr}] Invalid PIN length %\'d received. Defaulting to %d.");
          }
          puVar12 = &DAT_276141a48;
        }
        else {
          in_ZR = _gLogCategory_APPairingClientCoreUtils == 0x32;
          uVar6 = extraout_x1;
          if (_gLogCategory_APPairingClientCoreUtils < 0x33) {
            in_ZR = _gLogCategory_APPairingClientCoreUtils == -1;
            if ((bool)in_ZR) {
              iVar2 = _OUTLINED_FUNCTION_7();
              uVar9 = local_118 & 0xffffffff;
              uVar6 = extraout_x1_00;
              if (iVar2 == 0) goto LAB_251b889a4;
            }
            uVar6 = _OUTLINED_FUNCTION_8();
            _OUTLINED_FUNCTION_10
                      (uVar6,
                       "CFNumberRef coreUtilsPairing_copyPINLengthFromResponse(APPairingClientRef, CFDictionaryRef)"
                      );
            uVar9 = local_118 & 0xffffffff;
            uVar6 = extraout_x1_01;
          }
LAB_251b889a4:
          puVar12 = (undefined *)func_0x0002580012b0(_DAT_2680df5a0,uVar6,uVar9);
        }
      }
LAB_251b889b4:
      func_0x0002580f6a60(puVar12);
      *param_10 = puVar12;
    }
    if (param_12 != (undefined8 *)0x0) {
      lVar5 = func_0x00025810f140(lVar3,*_DAT_268104118);
      uVar6 = 0;
      if (lVar5 != 0) {
        uVar6 = func_0x0002580f6a60();
      }
      *param_12 = uVar6;
    }
    iVar2 = func_0x00025810a700(lVar3,*_DAT_268104120,0xffffffff80000000,0x7fffffff,0);
    if (iVar2 != 0) {
      in_ZR = iVar2 - 300U == 0xffffff9c;
      if (iVar2 - 300U < 0xffffff9c) {
        func_0x000258109a30(0,
                            "coreUtilsPairing_copyReceiverInfoAndPairingPayloadFromCombinedResponse"
                            ,0x58b,0);
        in_ZR = iVar2 + 200000U == 0;
        puVar12 = (undefined *)(ulong)(iVar2 + 200000U);
        if (!(bool)in_ZR) goto LAB_251b88c48;
        goto LAB_251b88a7c;
      }
      if (param_11 != (undefined8 *)0x0) {
        lVar5 = func_0x00025810f130(lVar3,*_DAT_268104110);
        if (lVar5 == 0) {
          auVar13 = _OUTLINED_FUNCTION_25();
          uVar10 = 0x591;
        }
        else {
          puVar12 = (undefined *)func_0x00025810f290(uVar10,lVar5,0,0,param_11);
          if ((int)puVar12 == 0) goto LAB_251b88a7c;
          auVar13._8_8_ = "coreUtilsPairing_copyReceiverInfoAndPairingPayloadFromCombinedResponse";
          auVar13._0_8_ = puVar12;
          uVar10 = 0x595;
        }
        goto LAB_251b88c40;
      }
      goto LAB_251b88a68;
    }
    _OUTLINED_FUNCTION_25();
    auVar1._8_8_ = 0;
    auVar1._0_8_ = extraout_x1_02;
    auVar13 = auVar1 << 0x40;
    uVar10 = 0x58a;
LAB_251b88c40:
    func_0x000258109a30(auVar13._0_8_,auVar13._8_8_,uVar10,0);
LAB_251b88c48:
    func_0x000258109a30(puVar12,"coreUtilsPairing_handlePairingResponse",0x5be,0);
  }
LAB_251b88a7c:
  if (lVar3 != 0) {
    func_0x0002580f5830(lVar3);
  }
  puVar7 = puVar12;
  if ((int)puVar12 != 0) {
    func_0x000258109a30(puVar12,"coreUtilsPairing_sendPairingRequest",0x62c,0);
  }
LAB_251b88a8c:
  if (local_128 != 0) {
    func_0x0002580f4d30();
    local_128 = 0;
  }
  if (local_120 != 0) {
    func_0x0002580f5830();
  }
  if (lVar4 != 0) {
    func_0x0002580f5830(lVar4);
  }
  if (local_130 != (undefined *)0x0) {
    func_0x0002580f5830();
  }
  _OUTLINED_FUNCTION_10(local_70);
  if (!(bool)in_ZR) {
    puVar7 = (undefined *)func_0x0002580f4380();
    return puVar7;
  }
  return puVar7;
}


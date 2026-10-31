/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b88c94
 * original code SHA256: e60abba36f6a976dfc10e710c4b62bc8ea5f6edb8c1033a452c52b778267dc0d
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _coreUtilsPairing_performSetupInternal
               (undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5,undefined8 param_6,long *param_7,undefined8 *param_8,
               undefined8 param_9,undefined8 *param_10,undefined8 param_11)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  bool bVar1;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  ulong uVar10;
  undefined8 uVar11;
  int extraout_w8;
  int extraout_w8_00;
  int extraout_w8_01;
  int extraout_w8_02;
  int extraout_w8_03;
  int extraout_w8_04;
  int extraout_w8_05;
  int extraout_w8_06;
  int extraout_w8_07;
  int extraout_w8_08;
  int extraout_w8_09;
  int extraout_w8_10;
  undefined8 extraout_x8;
  long lVar12;
  long lVar13;
  long lVar14;
  undefined1 auVar15 [16];
  long local_138;
  long local_130;
  char local_121;
  undefined8 local_120;
  long local_118;
  undefined8 local_110;
  uint local_104;
  undefined8 local_100;
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
  undefined8 local_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 local_78;
  
  _OUTLINED_FUNCTION_13();
  local_104 = 0;
  local_78 = extraout_x8;
  lVar8 = func_0x00025810ac50();
  local_118 = 0;
  local_110 = 0;
  local_120 = 0;
  local_121 = '\0';
  uStack_98 = 0;
  local_a0 = 0;
  uStack_88 = 0;
  uStack_90 = 0;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_f8 = 0;
  local_100 = 0;
  local_138 = 0;
  local_130 = 0;
  _OUTLINED_FUNCTION_9();
  if (((bool)in_ZR || in_NG != in_OV) &&
     ((extraout_w8 != -1 || (iVar6 = _OUTLINED_FUNCTION_7(), iVar6 != 0)))) {
    _OUTLINED_FUNCTION_5();
    _OUTLINED_FUNCTION_10();
  }
  iVar6 = (int)param_3;
  cVar2 = SBORROW4(iVar6,4);
  cVar3 = iVar6 + -4 < 0;
  uVar4 = iVar6 == 4;
  local_104 = _coreUtilsPairing_createAirPlayPairingSession(param_1,1,uVar4,param_4,&local_138);
  if (local_104 == 0) {
    _OUTLINED_FUNCTION_9();
    lVar9 = local_138;
    if ((bool)uVar4 || cVar3 != cVar2) {
      cVar2 = SCARRY4(extraout_w8_00,1);
      cVar3 = extraout_w8_00 + 1 < 0;
      uVar4 = extraout_w8_00 == -1;
      if ((!(bool)uVar4) || (iVar7 = _OUTLINED_FUNCTION_7(), lVar9 = local_138, iVar7 != 0)) {
        _OUTLINED_FUNCTION_5();
        _OUTLINED_FUNCTION_10();
        lVar9 = local_138;
      }
    }
    local_138 = lVar9;
    if (param_2 != 0) {
      _OUTLINED_FUNCTION_23(param_2,&local_100);
      lVar9 = local_138;
      if (((char)local_100 != '\0') &&
         (local_104 = func_0x00025810ba70(local_138,&local_100,0xffffffffffffffff), local_104 != 0))
      {
        auVar15 = _OUTLINED_FUNCTION_14();
        uVar11 = 0x225;
        goto LAB_251b89180;
      }
    }
    _OUTLINED_FUNCTION_23(*(undefined8 *)(lVar8 + 0x10),&local_100);
    local_104 = func_0x00025810fd60(lVar9,&local_100,0xffffffffffffffff);
    if (local_104 == 0) {
      local_110 = 0;
      local_120 = 0;
      local_121 = '\0';
      local_104 = 0;
LAB_251b88e4c:
      do {
        local_104 = func_0x00025810ba20(lVar9,local_110,local_120,&local_118,&local_120,&local_121);
        bVar1 = local_104 + 0x1185f < 3;
        bVar5 = local_104 == 0xfffeea04;
        cVar2 = (!bVar1 && !bVar5) && SBORROW4(local_104,-0x115e9);
        uVar4 = (bVar1 || bVar5) || local_104 == 0xfffeea17;
        cVar3 = (!bVar1 && !bVar5) && (int)(local_104 + 0x115e9) < 0;
        if ((bVar1 || bVar5) || local_104 == 0xfffeea17) {
          _OUTLINED_FUNCTION_3();
          if ((bool)uVar4 || cVar3 != cVar2) {
            cVar2 = SCARRY4(extraout_w8_01,1);
            cVar3 = extraout_w8_01 + 1 < 0;
            uVar4 = extraout_w8_01 == -1;
            if ((bool)uVar4) {
              _OUTLINED_FUNCTION_16();
              iVar7 = func_0x000258101e40(&_gLogCategory_APPairingClientCoreUtils,
                                          extraout_w8_02 + 0x28);
              if (iVar7 != 0) goto LAB_251b88ea4;
            }
            else {
LAB_251b88ea4:
              _OUTLINED_FUNCTION_16();
              func_0x000258101eb0(&_gLogCategory_APPairingClientCoreUtils,
                                  "OSStatus coreUtilsPairing_performSetupInternal(APPairingClientRef, const CFStringRef, APPairingType, Boolean, Boolean, CFStringRef, CFStringRef *, CFDataRef *, CFDataRef *, CFTypeRef *, CFDictionaryRef *)"
                                  ,extraout_w8_03 + 0x28,
                                  "### [%{ptr}] Error in pairing session exchange: %#m\n");
            }
            if (local_104 == 0) goto LAB_251b88ed0;
          }
          auVar15 = _OUTLINED_FUNCTION_14();
          uVar11 = 0x23b;
          goto LAB_251b89180;
        }
        if (local_104 != 0) {
          lVar14 = 0;
          lVar13 = 0;
          local_104 = 0x30ed1;
          goto LAB_251b890b8;
        }
LAB_251b88ed0:
        if (local_121 != '\0') {
          _OUTLINED_FUNCTION_9();
          if (((bool)uVar4 || cVar3 != cVar2) &&
             ((extraout_w8_04 != -1 || (iVar7 = _OUTLINED_FUNCTION_7(), iVar7 != 0)))) {
            uVar11 = _OUTLINED_FUNCTION_4();
            _OUTLINED_FUNCTION_10
                      (uVar11,
                       "OSStatus coreUtilsPairing_performSetupInternal(APPairingClientRef, const CFStringRef, APPairingType, Boolean, Boolean, CFStringRef, CFStringRef *, CFDataRef *, CFDataRef *, CFTypeRef *, CFDictionaryRef *)"
                      );
          }
          cVar2 = SBORROW4(iVar6,4);
          cVar3 = iVar6 + -4 < 0;
          uVar4 = iVar6 == 4;
          if ((bool)uVar4) {
            lVar13 = *(long *)(lVar8 + 8);
            *(long *)(lVar8 + 8) = lVar9;
            if (lVar9 != 0) {
              func_0x0002580f6a60(lVar9);
            }
            if (lVar13 != 0) {
              func_0x0002580f5830(lVar13);
            }
            lVar14 = 0;
            lVar13 = 0;
            *(undefined1 *)(lVar8 + 0x3a) = 1;
          }
          else {
            lVar13 = func_0x00025810fd10(lVar9,0,&local_104);
            if (local_104 != 0) {
              auVar15 = _OUTLINED_FUNCTION_14();
              func_0x000258109a30(auVar15._0_8_,auVar15._8_8_,0x265,0);
              lVar14 = 0;
              goto LAB_251b890b8;
            }
            lVar14 = func_0x000258101860(*_DAT_2680d3150,lVar13,0x8000100);
            if (lVar14 == 0) {
              auVar15 = _OUTLINED_FUNCTION_14();
              func_0x000258109a30(auVar15._0_8_,auVar15._8_8_,0x267,0);
              local_104 = 0xfffee7a6;
              goto LAB_251b890b8;
            }
            lVar12 = *(long *)(lVar8 + 0x18);
            *(long *)(lVar8 + 0x18) = lVar14;
            func_0x0002580f6a60(lVar14);
            if (lVar12 != 0) {
              func_0x0002580f5830(lVar12);
            }
            if (param_7 != (long *)0x0) {
              *param_7 = lVar14;
              lVar14 = 0;
            }
          }
          if (param_8 != (undefined8 *)0x0) {
            *param_8 = 0;
          }
          if (((int)param_4 == 0) ||
             (local_104 = _coreUtilsPairing_validateMFiCertificate(param_1,lVar9,param_9),
             local_104 == 0)) {
            if (param_10 != (undefined8 *)0x0) {
              lVar9 = func_0x00025810fd50(lVar9,0);
              uVar11 = 0;
              if (lVar9 != 0) {
                uVar11 = func_0x0002580f6a60();
              }
              *param_10 = uVar11;
            }
            *(char *)(lVar8 + 0x42) = (char)param_4;
          }
          else {
            _OUTLINED_FUNCTION_3();
            if (!(bool)uVar4 && cVar3 == cVar2) goto LAB_251b890b8;
            cVar2 = SCARRY4(extraout_w8_08,1);
            cVar3 = extraout_w8_08 + 1 < 0;
            uVar4 = extraout_w8_08 == -1;
            if ((bool)uVar4) {
              _OUTLINED_FUNCTION_8();
              uVar11 = _OUTLINED_FUNCTION_16();
              iVar6 = func_0x000258101e40(uVar11,extraout_w8_09 + 0x28);
              if (iVar6 == 0) goto LAB_251b890b8;
            }
            uVar11 = _OUTLINED_FUNCTION_4();
            auVar15 = _OUTLINED_FUNCTION_16
                                (uVar11,
                                 "OSStatus coreUtilsPairing_performSetupInternal(APPairingClientRef, const CFStringRef, APPairingType, Boolean, Boolean, CFStringRef, CFStringRef *, CFDataRef *, CFDataRef *, CFTypeRef *, CFDictionaryRef *)"
                                );
            func_0x000258101eb0(auVar15._0_8_,auVar15._8_8_,extraout_w8_10 + 0x28);
          }
          goto LAB_251b890b8;
        }
        if (local_130 != 0) {
          func_0x0002580f5830();
          local_130 = 0;
        }
        local_104 = _coreUtilsPairing_sendPairingRequest
                              (param_1,param_3,0x70617365,local_118,local_120,0,param_5,param_6,0,0,
                               &local_130,param_11);
        if (local_104 != 0) goto LAB_251b89188;
        if (local_118 != 0) {
          func_0x0002580f4d30();
          local_118 = 0;
        }
        param_11 = 0;
        local_120 = 0;
        local_110 = 0;
      } while (local_130 == 0);
      local_104 = func_0x00025810eae0(local_130,0,&local_120,0,&local_110);
      if (local_104 == 0) {
        param_11 = 0;
        local_104 = 0;
        goto LAB_251b88e4c;
      }
      auVar15 = _OUTLINED_FUNCTION_14();
      uVar11 = 0x259;
    }
    else {
      auVar15 = _OUTLINED_FUNCTION_14();
      uVar11 = 0x22d;
    }
  }
  else {
    auVar15 = _OUTLINED_FUNCTION_14();
    uVar11 = 0x21b;
  }
LAB_251b89180:
  func_0x000258109a30(auVar15._0_8_,auVar15._8_8_,uVar11,0);
LAB_251b89188:
  lVar14 = 0;
  lVar13 = 0;
LAB_251b890b8:
  if (local_138 != 0) {
    func_0x0002580f5830();
  }
  if (local_130 != 0) {
    func_0x0002580f5830();
  }
  if (lVar14 != 0) {
    func_0x0002580f5830(lVar14);
  }
  if (local_118 != 0) {
    func_0x0002580f4d30();
    local_118 = 0;
  }
  if (lVar13 != 0) {
    func_0x0002580f4d30(lVar13);
  }
  uVar10 = (ulong)local_104;
  if ((local_104 != 0) && (uVar10 = _OUTLINED_FUNCTION_3(), (bool)uVar4 || cVar3 != cVar2)) {
    uVar4 = extraout_w8_05 == -1;
    if ((bool)uVar4) {
      _OUTLINED_FUNCTION_8();
      uVar11 = _OUTLINED_FUNCTION_16();
      iVar6 = func_0x000258101e40(uVar11,extraout_w8_06 + 0x28);
      uVar10 = (ulong)local_104;
      if (iVar6 == 0) goto LAB_251b8914c;
    }
    _OUTLINED_FUNCTION_5();
    auVar15 = _OUTLINED_FUNCTION_16();
    func_0x000258101eb0(auVar15._0_8_,auVar15._8_8_,extraout_w8_07 + 0x28);
    uVar10 = (ulong)local_104;
  }
LAB_251b8914c:
  _OUTLINED_FUNCTION_10(local_78,uVar10);
  if ((bool)uVar4) {
    return;
  }
  func_0x0002580f4380();
  return;
}


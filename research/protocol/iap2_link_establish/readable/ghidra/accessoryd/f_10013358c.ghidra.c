/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10013358c
 * original code SHA256: ee68b13faab4e8bbff5395a8cc3bff022a98d89df37ea8d8c3d1eec91b862cec
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_protocol_handle_AuthenticationSucceeded(long param_1)

{
  byte bVar1;
  undefined1 in_ZR;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  void *pvVar6;
  long extraout_x1;
  ulong extraout_x1_00;
  ulong extraout_x1_01;
  uint uVar7;
  long lVar8;
  long extraout_x8;
  long extraout_x8_00;
  byte bVar9;
  byte bVar10;
  ulong uVar11;
  undefined8 uVar12;
  undefined1 auVar13 [16];
  undefined4 local_40;
  undefined4 local_3c;
  undefined2 local_38;
  uint local_36;
  
  if (param_1 == 0) {
    uVar12 = _logObjectForModule();
    iVar5 = _OUTLINED_FUNCTION_7(uVar12);
    if (iVar5 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_2();
LAB_100133990:
    _OUTLINED_FUNCTION_21();
    __os_log_error_impl();
    return 1;
  }
  _OUTLINED_FUNCTION_34();
  if ((bool)in_ZR) {
    uVar12 = _logObjectForModule();
    iVar5 = _OUTLINED_FUNCTION_7(uVar12);
    if (iVar5 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_2();
    goto LAB_100133990;
  }
  if (extraout_x1 == 0) {
    uVar12 = _logObjectForModule();
    iVar5 = _OUTLINED_FUNCTION_7(uVar12);
    if (iVar5 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_2();
    goto LAB_100133990;
  }
  bVar1 = *(byte *)(param_1 + 0x90);
  if ((bVar1 & 3) == 1) {
    bVar9 = 2;
    bVar10 = 0xfc;
LAB_100133604:
    *(byte *)(param_1 + 0x90) = bVar1 & bVar10 | bVar9;
  }
  else {
    if ((bVar1 & 0xc) == 4) {
      bVar9 = 8;
      bVar10 = 0xf3;
      goto LAB_100133604;
    }
    if ((bVar1 & 0x30) == 0x10) {
      bVar9 = 0x20;
      bVar10 = 0xcf;
      goto LAB_100133604;
    }
  }
  auVar13 = _mfi4Auth_protocol_handle_AuthState(param_1,2);
  uVar12 = auVar13._0_8_;
  uVar7 = *(int *)(param_1 + 0x58) - 1;
  uVar11 = (ulong)uVar7;
  if (0xc < uVar7) goto switchD_100133648_caseD_1;
  cVar2 = SBORROW8(uVar11,0xc);
  cVar3 = (long)(uVar11 - 0xc) < 0;
  uVar4 = uVar11 == 0xc;
  switch(uVar11) {
  default:
    pvVar6 = (void *)_malloc_type_malloc(0x12,0x1000040bdfb0063);
    if (pvVar6 == (void *)0x0) {
      return 0xffffffff;
    }
    lVar8 = 0;
    do {
      *(short *)((long)pvVar6 + lVar8 * 2) = (short)lVar8 + 0x5202;
      lVar8 = lVar8 + 1;
    } while (lVar8 != 9);
    auVar13 = _OUTLINED_FUNCTION_26();
    uVar12 = _mfi4Auth_protocol_initMessage_RequestVendorNVMRead
                       (auVar13._0_8_,auVar13._8_8_,pvVar6,9);
    _free(pvVar6);
    iVar5 = (int)uVar12;
    break;
  case 1:
  case 2:
  case 0xb:
    goto switchD_100133648_caseD_1;
  case 3:
  case 0xc:
    _OUTLINED_FUNCTION_29(uVar12,*(undefined2 *)(param_1 + 0x150));
    goto LAB_1001337a8;
  case 4:
    if (*(char *)(param_1 + 0xd0) == '\x02') {
      _OUTLINED_FUNCTION_29(uVar12,*(undefined2 *)(param_1 + 0x150));
      uVar12 = _mfi4Auth_protocol_initMessage_RequestNVMPublicKeyChallenge();
    }
    else {
      local_40 = CONCAT22(local_40._2_2_,0x5100);
      _OUTLINED_FUNCTION_26(uVar12,auVar13._8_8_,&local_40);
      uVar12 = _mfi4Auth_protocol_initMessage_RequestManufacturerNVMRead();
    }
    iVar5 = (int)uVar12;
    break;
  case 5:
    if (*(int *)(param_1 + 0x5c) == 0) {
      return 0xffffffff;
    }
    if (*(long *)(param_1 + 0x60) == 0) {
      return 0xffffffff;
    }
    if (*(long *)(param_1 + 0x68) == 0) {
      return 0xffffffff;
    }
    if (*(long *)(param_1 + 0x70) == 0) {
      return 0xffffffff;
    }
    _OUTLINED_FUNCTION_29(uVar12,*(undefined2 *)(param_1 + 0x150));
    uVar12 = _mfi4Auth_protocol_initMessage_RequestUserNVMWrite();
    iVar5 = (int)uVar12;
    break;
  case 6:
    if (*(uint *)(param_1 + 0x5c) == 0) {
      return 0xffffffff;
    }
    lVar8 = *(long *)(param_1 + 0x60);
    if (lVar8 == 0) {
      return 0xffffffff;
    }
    uVar7 = *(uint *)(param_1 + 0x5c) & 0xff;
    goto LAB_10013383c;
  case 7:
    if (*(int *)(param_1 + 0x5c) == 0) {
      return 0xffffffff;
    }
    if (*(long *)(param_1 + 0x60) == 0) {
      return 0xffffffff;
    }
    _OUTLINED_FUNCTION_29(uVar12,*(undefined2 *)(param_1 + 0x150));
    _OUTLINED_FUNCTION_24();
    uVar12 = _mfi4Auth_protocol_initMessage_RequestUserNVMErase();
    iVar5 = (int)uVar12;
    break;
  case 8:
    if (*(int *)(param_1 + 0x5c) == 0) {
      return 0xffffffff;
    }
    if (*(long *)(param_1 + 0x60) == 0) {
      return 0xffffffff;
    }
    if (*(long *)(param_1 + 0x68) == 0) {
      return 0xffffffff;
    }
    if (*(long *)(param_1 + 0x70) == 0) {
      return 0xffffffff;
    }
    _OUTLINED_FUNCTION_18();
    if ((extraout_x8 == 0) || (uVar12 = _OUTLINED_FUNCTION_9(), cVar3 != cVar2)) {
      _OUTLINED_FUNCTION_8();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_3();
        _dispatch_once();
      }
      uVar12 = _OUTLINED_FUNCTION_19();
    }
    iVar5 = _os_log_type_enabled(uVar12,0);
    if (iVar5 != 0) {
      local_3c = *(undefined4 *)(param_1 + 0x5c);
      local_40 = (undefined4)DAT_1001b3108;
      local_38 = 0x400;
      local_36 = (uint)**(ushort **)(param_1 + 0x60);
      _OUTLINED_FUNCTION_6();
      auVar13 = _OUTLINED_FUNCTION_36();
      __os_log_impl(auVar13._0_8_,auVar13._8_8_,0);
    }
    if (*(char *)(param_1 + 0xd0) == '\x02') {
      _OUTLINED_FUNCTION_29(0,*(undefined2 *)(param_1 + 0x150));
      _mfi4Auth_protocol_initMessage_RequestUserNVMWrite();
    }
    else {
      auVar13 = _OUTLINED_FUNCTION_26(0);
      _mfi4Auth_protocol_initMessage_RequestNVMAuthStart(auVar13._0_8_,auVar13._8_8_,0x5300);
    }
    goto switchD_100133648_caseD_1;
  case 9:
    _OUTLINED_FUNCTION_18();
    if ((extraout_x8_00 == 0) || (uVar12 = _OUTLINED_FUNCTION_9(), cVar3 != cVar2)) {
      _OUTLINED_FUNCTION_8();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_3();
        _dispatch_once();
      }
      uVar12 = _OUTLINED_FUNCTION_19();
    }
    iVar5 = _os_log_type_enabled(uVar12,0);
    uVar11 = extraout_x1_00;
    if (iVar5 != 0) {
      _OUTLINED_FUNCTION_2();
      auVar13 = _OUTLINED_FUNCTION_36();
      __os_log_impl(auVar13._0_8_,auVar13._8_8_,0);
      uVar11 = extraout_x1_01;
    }
    auVar13._8_8_ = 0;
    auVar13._0_8_ = uVar11;
    auVar13 = auVar13 << 0x40;
    lVar8 = *(long *)(param_1 + 0x60);
    uVar7 = (uint)*(byte *)(param_1 + 0x5c);
LAB_10013383c:
    _OUTLINED_FUNCTION_26(auVar13._0_8_,auVar13._8_8_,lVar8,uVar7);
    _OUTLINED_FUNCTION_24();
    uVar12 = _mfi4Auth_protocol_initMessage_RequestUserNVMRead();
    iVar5 = (int)uVar12;
    break;
  case 10:
    _OUTLINED_FUNCTION_29(uVar12,*(undefined2 *)(param_1 + 0x150));
LAB_1001337a8:
    uVar12 = _mfi4Auth_protocol_initMessage_RequestNVMPublicKeyChallenge();
    iVar5 = (int)uVar12;
  }
  if (iVar5 == 0) {
switchD_100133648_caseD_1:
    uVar12 = 0;
  }
  return uVar12;
}


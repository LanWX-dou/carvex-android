/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100132acc
 * original code SHA256: 50feb1bc26036e9c10b61263d8126964e10ffa8b8648d8c19fcca28057c357de
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x26 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_protocol_encryptPayload(long param_1)

{
  undefined8 *puVar1;
  undefined1 in_ZR;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  void *pvVar5;
  ID IVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  long extraout_x1;
  undefined8 extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long lVar9;
  size_t sVar10;
  
  _OUTLINED_FUNCTION_3();
  lVar9 = *(long *)(extraout_x1 + 0x18);
  uVar3 = _iAP2MsgGetMsgLen(extraout_x1);
  *(ushort *)(lVar9 + 2) =
       (ushort)(uVar3 + 0x10 >> 8) & 0xff | (ushort)((uVar3 + 0x10 & 0xff00ff) << 8);
  sVar10 = (ulong)uVar3 - 6;
  pvVar5 = (void *)_malloc_type_malloc(sVar10,0x4a46df5d);
  if (pvVar5 == (void *)0x0) {
    uVar7 = 0xffffffff;
    goto LAB_100132d40;
  }
  if (param_1 == 0) {
    uVar7 = _logObjectForModule();
    iVar4 = _OUTLINED_FUNCTION_8(uVar7);
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_2();
LAB_100132e10:
      _OUTLINED_FUNCTION_31();
      __os_log_error_impl();
    }
LAB_100132da8:
    uVar7 = 1;
  }
  else {
    in_ZR = *(char *)(param_1 + 0x1e) == '\x01';
    if ((bool)in_ZR) {
      uVar7 = _logObjectForModule();
      iVar4 = _OUTLINED_FUNCTION_8(uVar7);
      if (iVar4 != 0) {
        _OUTLINED_FUNCTION_2();
        goto LAB_100132e10;
      }
      goto LAB_100132da8;
    }
    IVar6 = _OUTLINED_FUNCTION_38();
    objc_stub::dataWithBytes_length_(IVar6,lVar9 + 6,sVar10);
    __dumpSimpleHex();
    uVar7 = _OUTLINED_FUNCTION_18();
    if ((extraout_x8_00 == 0) || (uVar2 = _gNumLogObjects == 0x3b, _gNumLogObjects < 0x3b)) {
      uVar2 = _logObjectForModule_onceToken == -1;
      if (!(bool)uVar2) {
        _OUTLINED_FUNCTION_3();
        _dispatch_once();
      }
      uVar7 = _OUTLINED_FUNCTION_19();
    }
    iVar4 = _os_log_type_enabled(uVar7,0);
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_31();
      __os_log_impl();
    }
    uVar7 = _OUTLINED_FUNCTION_18(0);
    if ((extraout_x8_01 == 0) || (uVar2 = _gNumLogObjects == 0x3b, _gNumLogObjects < 0x3b)) {
      _OUTLINED_FUNCTION_8();
      if (!(bool)uVar2) {
        _OUTLINED_FUNCTION_3();
        _dispatch_once();
      }
      uVar7 = _OUTLINED_FUNCTION_19();
    }
    iVar4 = _os_log_type_enabled(uVar7,0);
    if (iVar4 != 0) {
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_31();
      __os_log_impl();
    }
    in_ZR = *(byte *)(param_1 + 0xd0) == 3;
    if (*(byte *)(param_1 + 0xd0) < 3) {
      _OUTLINED_FUNCTION_35(*(undefined8 *)(param_1 + 0x98));
    }
    else {
      _OUTLINED_FUNCTION_35(*(undefined8 *)(param_1 + 0x98));
    }
    uVar7 = _ccsigma_seal();
    if ((int)uVar7 == 0) {
      _memcpy((void *)(lVar9 + 6),pvVar5,sVar10);
      puVar1 = (undefined8 *)(lVar9 + (ulong)uVar3);
      puVar1[1] = &DAT_aaaaaaaaaaaaaaaa;
      *puVar1 = &DAT_aaaaaaaaaaaaaaaa;
      IVar6 = _OUTLINED_FUNCTION_38();
      objc_stub::dataWithBytes_length_(IVar6,pvVar5,sVar10);
      __dumpSimpleHex();
      uVar7 = _OUTLINED_FUNCTION_18(0);
      if ((extraout_x8_02 == 0) || (in_ZR = _gNumLogObjects == 0x3b, _gNumLogObjects < 0x3b)) {
        _OUTLINED_FUNCTION_8();
        if (!(bool)in_ZR) {
          _OUTLINED_FUNCTION_3();
          _dispatch_once();
        }
        uVar7 = _OUTLINED_FUNCTION_19();
      }
      iVar4 = _os_log_type_enabled(uVar7,0);
      if (iVar4 != 0) {
        uVar8 = _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_78(uVar8,uVar7);
      }
      uVar7 = 0;
    }
    else {
      uVar8 = _logObjectForModule();
      iVar4 = _OUTLINED_FUNCTION_24(uVar8);
      if (iVar4 != 0) {
        _OUTLINED_FUNCTION_2();
        _OUTLINED_FUNCTION_36();
        _OUTLINED_FUNCTION_31();
        __os_log_error_impl();
      }
    }
  }
  _free(pvVar5);
LAB_100132d40:
  _OUTLINED_FUNCTION_34(extraout_x8);
  if (!(bool)in_ZR) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return uVar7;
}


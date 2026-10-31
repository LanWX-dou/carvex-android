/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100132318
 * original code SHA256: 34a801e6ba2089a1d0888d8de2994e287ea8d0051f75c3017264673232e40f70
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x27 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x28 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */

undefined8
_mfi4Auth_protocol_decryptPayload(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  byte bVar2;
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  char cVar3;
  char cVar4;
  int iVar5;
  long lVar6;
  ulong uVar7;
  void *pvVar8;
  ID IVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  long extraout_x1;
  undefined8 extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  long extraout_x8_02;
  long extraout_x8_03;
  long extraout_x8_04;
  size_t sVar13;
  long lVar14;
  undefined4 local_90;
  undefined8 local_8c;
  undefined1 *local_80;
  undefined1 *puStack_78;
  undefined8 local_68;
  
  lVar6 = _OUTLINED_FUNCTION_3();
  local_80 = &DAT_aaaaaaaaaaaaaaaa;
  puStack_78 = &DAT_aaaaaaaaaaaaaaaa;
  local_68 = extraout_x8;
  if (lVar6 == 0) {
    uVar10 = _logObjectForModule();
    iVar5 = _os_log_type_enabled(uVar10,0x10);
    if (iVar5 != 0) {
      uVar11 = _OUTLINED_FUNCTION_13();
LAB_1001327b8:
      _OUTLINED_FUNCTION_31(uVar11,uVar10);
      __os_log_error_impl();
    }
  }
  else {
    _OUTLINED_FUNCTION_34();
    if ((bool)in_ZR) {
      uVar10 = _logObjectForModule();
      iVar5 = _os_log_type_enabled(uVar10,0x10);
      if (iVar5 != 0) {
        uVar11 = _OUTLINED_FUNCTION_13();
        goto LAB_1001327b8;
      }
    }
    else {
      if (extraout_x1 != 0) {
        uVar7 = _iAP2MsgGetMsgLen(extraout_x1);
        uVar7 = uVar7 & 0xffffffff;
        lVar14 = *(long *)(extraout_x1 + 0x18);
        sVar13 = uVar7 - 0x16;
        pvVar8 = (void *)_malloc_type_calloc(sVar13,1,0x12b301a1);
        if (pvVar8 == (void *)0x0) {
          uVar10 = 0xffffffff;
        }
        else {
          lVar14 = lVar14 + 6;
          lVar1 = lVar14 + uVar7;
          puStack_78 = *(undefined1 **)(lVar1 + -0xe);
          local_80 = *(undefined1 **)(lVar1 + -0x16);
          IVar9 = _OUTLINED_FUNCTION_38();
          objc_stub::dataWithBytes_length_(IVar9,lVar14,sVar13);
          uVar10 = __dumpSimpleHex();
          _OUTLINED_FUNCTION_18();
          if ((extraout_x8_00 == 0) || (uVar11 = _OUTLINED_FUNCTION_23(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_8();
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_3();
              _dispatch_once();
            }
            uVar11 = _OUTLINED_FUNCTION_19();
          }
          iVar5 = _os_log_type_enabled(uVar11,0);
          if (iVar5 != 0) {
            local_90 = (undefined4)DAT_1001b3088;
            local_8c = uVar10;
            uVar10 = _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_78(uVar10,uVar11);
          }
          IVar9 = _OUTLINED_FUNCTION_38(0);
          objc_stub::dataWithBytes_length_(IVar9,&local_80,0x10);
          uVar10 = __dumpSimpleHex();
          _OUTLINED_FUNCTION_18(0);
          if ((extraout_x8_01 == 0) || (uVar11 = _OUTLINED_FUNCTION_23(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_8();
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_3();
              _dispatch_once();
            }
            uVar11 = _OUTLINED_FUNCTION_19();
          }
          iVar5 = _os_log_type_enabled(uVar11,0);
          if (iVar5 != 0) {
            local_90 = (undefined4)DAT_1001b3088;
            local_8c = uVar10;
            _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_32();
            __os_log_impl();
          }
          _OUTLINED_FUNCTION_18(0);
          if ((extraout_x8_02 == 0) || (uVar10 = _OUTLINED_FUNCTION_23(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_8();
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_3();
              _dispatch_once();
            }
            uVar10 = _OUTLINED_FUNCTION_19();
          }
          iVar5 = _os_log_type_enabled(uVar10,0);
          if (iVar5 != 0) {
            local_90 = (undefined4)DAT_1001b30a8;
            local_8c = param_3;
            _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_32();
            __os_log_impl();
          }
          _OUTLINED_FUNCTION_18(0);
          if ((extraout_x8_03 == 0) || (uVar10 = _OUTLINED_FUNCTION_23(), in_NG != in_OV)) {
            _OUTLINED_FUNCTION_8();
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_3();
              _dispatch_once();
            }
            uVar10 = _OUTLINED_FUNCTION_19();
          }
          iVar5 = _os_log_type_enabled(uVar10,0);
          if (iVar5 != 0) {
            local_90 = (undefined4)DAT_1001b30b0;
            local_8c = CONCAT44(local_8c._4_4_,(uint)*(byte *)(lVar6 + 0xd0));
            _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_32();
            __os_log_impl();
          }
          bVar2 = *(byte *)(lVar6 + 0xd0);
          cVar3 = SBORROW4((uint)bVar2,3);
          cVar4 = (int)(bVar2 - 3) < 0;
          in_ZR = bVar2 == 3;
          if (bVar2 < 3) {
            _OUTLINED_FUNCTION_42(*(undefined8 *)(lVar6 + 0x98));
          }
          else {
            _OUTLINED_FUNCTION_42(*(undefined8 *)(lVar6 + 0x98));
          }
          uVar10 = _ccsigma_open();
          IVar9 = _OUTLINED_FUNCTION_38();
          objc_stub::dataWithBytes_length_(IVar9,pvVar8,sVar13);
          uVar11 = __dumpSimpleHex();
          _OUTLINED_FUNCTION_18(0);
          if ((extraout_x8_04 == 0) || (uVar12 = _OUTLINED_FUNCTION_23(), cVar4 != cVar3)) {
            _OUTLINED_FUNCTION_8();
            if (!(bool)in_ZR) {
              _OUTLINED_FUNCTION_3();
              _dispatch_once();
            }
            uVar12 = _OUTLINED_FUNCTION_19();
          }
          iVar5 = _os_log_type_enabled(uVar12,0);
          if (iVar5 != 0) {
            local_90 = (undefined4)DAT_1001b3088;
            local_8c = uVar11;
            uVar11 = _OUTLINED_FUNCTION_6();
            _OUTLINED_FUNCTION_78(uVar11,uVar12);
          }
          if ((int)uVar10 == 0) {
            _memcpy((void *)(*(long *)(extraout_x1 + 0x18) + 6),pvVar8,sVar13);
            *(char *)(*(long *)(extraout_x1 + 0x18) + 2) = (char)(uVar7 - 0x10 >> 8);
            *(char *)(*(long *)(extraout_x1 + 0x18) + 3) = (char)(uVar7 - 0x10);
          }
          else {
            uVar11 = _logObjectForModule(0);
            iVar5 = _OUTLINED_FUNCTION_8(uVar11);
            if (iVar5 != 0) {
              local_90 = (undefined4)DAT_1001b30b0;
              local_8c = CONCAT44(local_8c._4_4_,(int)uVar10);
              uVar11 = _OUTLINED_FUNCTION_6();
              __os_log_error_impl(uVar11,extraout_x1,0x10,"decryptPayload: ccsigma_open failed: %d",
                                  &local_90,8);
            }
          }
          _free(pvVar8);
        }
        goto LAB_100132680;
      }
      uVar10 = _logObjectForModule();
      iVar5 = _os_log_type_enabled(uVar10,0x10);
      if (iVar5 != 0) {
        uVar11 = _OUTLINED_FUNCTION_13();
        goto LAB_1001327b8;
      }
    }
  }
  uVar10 = 1;
LAB_100132680:
  _OUTLINED_FUNCTION_34(local_68,0);
  if (!(bool)in_ZR) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return uVar10;
}


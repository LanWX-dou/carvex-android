/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001330e0
 * original code SHA256: d8d111a2741850cfb91d3ab4437d1c558d8fb8606f13a1ffec3dc9d259571319
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x26 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined8
_mfi4Auth_protocol_initMessage_AuthCert(undefined8 param_1,undefined8 param_2,uint param_3)

{
  char *pcVar1;
  undefined2 uVar2;
  undefined1 in_ZR;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  int iVar6;
  undefined8 *puVar7;
  long lVar8;
  undefined8 uVar9;
  void *pvVar10;
  undefined8 uVar11;
  long *plVar12;
  long extraout_x8;
  long lVar13;
  long lVar14;
  undefined1 auVar15 [16];
  undefined1 *local_58;
  
  local_58 = &DAT_aaaaaaaaaaaaaaaa;
  auVar15 = _OUTLINED_FUNCTION_34();
  plVar12 = auVar15._8_8_;
  puVar7 = auVar15._0_8_;
  if ((bool)in_ZR) {
    uVar9 = _logObjectForModule();
    iVar6 = _OUTLINED_FUNCTION_7(uVar9);
    if (iVar6 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_2();
  }
  else {
    if (plVar12 != (long *)0x0) {
      uVar2 = *(undefined2 *)(puVar7 + 0x2a);
      lVar8 = _OUTLINED_FUNCTION_13();
      *plVar12 = lVar8;
      if (lVar8 != 0) {
        cVar3 = SBORROW4(param_3,6);
        cVar4 = (int)(param_3 - 6) < 0;
        uVar5 = param_3 == 6;
        lVar8 = 0x1e8;
        if (!(bool)uVar5) {
          lVar8 = 0x1f8;
        }
        lVar13 = 0x1e0;
        if (!(bool)uVar5) {
          lVar13 = 0x1f0;
        }
        lVar14 = *(long *)((long)puVar7 + lVar13);
        lVar13 = *(long *)((long)puVar7 + lVar8);
        lVar8 = puVar7[0x25];
        if (lVar8 != 0) {
          cVar3 = SBORROW4(param_3,6);
          cVar4 = (int)(param_3 - 6) < 0;
          uVar5 = param_3 == 6;
          pcVar1 = "MFi40Attestation-Certificate";
          if (!(bool)uVar5) {
            pcVar1 = "MFi40Attestation-Intermediate";
          }
          (**(code **)(lVar8 + 0x10))(lVar8,*puVar7,0,0,0,0,lVar14,lVar13,pcVar1,"MFi4Auth");
        }
        if ((lVar13 == 0) || (lVar14 == 0)) {
          uVar9 = _logObjectForModule();
          iVar6 = _OUTLINED_FUNCTION_8(uVar9);
          if (iVar6 == 0) {
            return 1;
          }
          _OUTLINED_FUNCTION_6();
          __os_log_error_impl();
          return 1;
        }
        uVar9 = _CTCompressComputeBufferSize(lVar14,lVar13,&local_58);
        if ((int)uVar9 != 0) {
          uVar11 = _logObjectForModule();
          iVar6 = _OUTLINED_FUNCTION_24(uVar11);
          if (iVar6 != 0) {
            _OUTLINED_FUNCTION_6();
            auVar15 = _OUTLINED_FUNCTION_36();
            __os_log_error_impl(auVar15._0_8_,auVar15._8_8_,0x10);
            return uVar9;
          }
          return uVar9;
        }
        pvVar10 = (void *)_malloc_type_malloc(local_58,0x3269adb7);
        if (pvVar10 != (void *)0x0) {
          uVar9 = _CTCompress(lVar14,lVar13,pvVar10,local_58);
          if ((int)uVar9 == 0) {
            _OUTLINED_FUNCTION_18();
            if ((extraout_x8 == 0) || (uVar11 = _OUTLINED_FUNCTION_9(), cVar4 != cVar3)) {
              _OUTLINED_FUNCTION_8();
              if (!(bool)uVar5) {
                _OUTLINED_FUNCTION_3();
                _dispatch_once();
              }
              uVar11 = _OUTLINED_FUNCTION_19();
            }
            iVar6 = _os_log_type_enabled(uVar11,0);
            if (iVar6 != 0) {
              _OUTLINED_FUNCTION_6();
              _OUTLINED_FUNCTION_31();
              __os_log_impl();
            }
            _OUTLINED_FUNCTION_24(*plVar12,uVar2,0x5113,puVar7[2],*(undefined4 *)(puVar7 + 3));
            _iAP2MsgInitWithSom();
            _iAP2MsgAddU8Param(*plVar12,0,0,param_3 & 0xff);
            _iAP2MsgAddDataParam(*plVar12,0,1,pvVar10,(ulong)local_58 & 0xffff);
            if (param_3 == 6) {
              _iAP2MsgAddArrayU8Param(*plVar12,0,2,puVar7 + 0x33,0x10);
            }
            *(undefined2 *)((long)puVar7 + 0x1c) = 0x5113;
          }
          else {
            uVar11 = _logObjectForModule();
            iVar6 = _OUTLINED_FUNCTION_24(uVar11);
            if (iVar6 != 0) {
              _OUTLINED_FUNCTION_6();
              auVar15 = _OUTLINED_FUNCTION_36();
              __os_log_error_impl(auVar15._0_8_,auVar15._8_8_,0x10);
            }
          }
          _free(pvVar10);
          return uVar9;
        }
      }
      return 0xffffffff;
    }
    uVar9 = _logObjectForModule();
    iVar6 = _OUTLINED_FUNCTION_7(uVar9);
    if (iVar6 == 0) {
      return 1;
    }
    _OUTLINED_FUNCTION_2();
  }
  _OUTLINED_FUNCTION_21();
  __os_log_error_impl();
  return 1;
}


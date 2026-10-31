/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10017a64c
 * original code SHA256: a58b7b291f1260712f9c3fc264ee47a61eacd54e487b7b2464f53128872affca
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_acc_protocolRouter_routeOutgoingSecureTunnelDataForClient
          (long param_1,undefined8 param_2,long param_3)

{
  undefined1 in_ZR;
  undefined1 uVar1;
  int iVar2;
  undefined8 uVar3;
  ulong uVar4;
  long extraout_x8;
  int extraout_w9;
  undefined8 unaff_x20;
  long unaff_x22;
  long unaff_x23;
  
  uVar3 = 0;
  if ((param_1 != 0) && (param_3 != 0)) {
    _OUTLINED_FUNCTION_14(*(undefined4 *)(param_1 + 0x1c),0);
    if ((bool)in_ZR) {
      uVar4 = _mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient
                        (*(undefined8 *)(param_1 + 0x38));
      if ((uVar4 & 1) != 0) {
        return 1;
      }
    }
    else {
      _OUTLINED_FUNCTION_12();
      uVar1 = !(bool)in_ZR && extraout_w9 == 0x14;
      if ((bool)in_ZR || extraout_w9 < 0x14) {
        _OUTLINED_FUNCTION_11();
        if (!(bool)uVar1) {
          _OUTLINED_FUNCTION_1();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
        in_ZR = uVar1;
      }
      else {
        unaff_x20 = *(undefined8 *)(extraout_x8 + 0x98);
        in_ZR = uVar1;
      }
      iVar2 = _OUTLINED_FUNCTION_71();
      if (iVar2 != 0) {
        _OUTLINED_FUNCTION_11(*(undefined4 *)(param_1 + 0x1c),DAT_1001b30b0);
        _OUTLINED_FUNCTION_5();
      }
    }
    if ((*(long *)(unaff_x23 + 0xa28) == 0) ||
       (in_ZR = *(int *)(unaff_x22 + 0xa30) == 0x14, *(int *)(unaff_x22 + 0xa30) < 0x14)) {
      _OUTLINED_FUNCTION_11();
      if (!(bool)in_ZR) {
        _OUTLINED_FUNCTION_1();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    else {
      unaff_x20 = *(undefined8 *)(*(long *)(unaff_x23 + 0xa28) + 0x98);
    }
    uVar3 = _os_log_type_enabled(unaff_x20,0x10);
    if ((int)uVar3 != 0) {
      _OUTLINED_FUNCTION_4(*(undefined8 *)(param_1 + 0x10),DAT_1001b30f0);
      _OUTLINED_FUNCTION_8();
      __os_log_error_impl();
      uVar3 = 0;
    }
  }
  return uVar3;
}


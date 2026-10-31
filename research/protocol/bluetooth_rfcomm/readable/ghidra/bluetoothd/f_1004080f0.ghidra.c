/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1004080f0
 * original code SHA256: fd0448ab67898609ffca6bc9e1940d19132941e0a7acd13dcaf178c3739b552e
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 phone_fn_1004080f0(undefined8 param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 in_x6;
  undefined8 in_x7;
  char *pcVar4;
  code *pcVar5;
  long *plVar6;
  char *pcVar7;
  code *pcVar8;
  undefined8 *puVar9;
  char *pcVar10;
  code *pcVar11;
  undefined8 *puVar12;
  char *pcVar13;
  code *pcVar14;
  undefined8 *puVar15;
  char *pcVar16;
  code *pcVar17;
  undefined8 *puVar18;
  undefined8 uVar19;
  undefined4 uStack_90;
  int iStack_8c;
  undefined2 uStack_88;
  undefined2 uStack_86;
  undefined6 uStack_84;
  undefined2 uStack_7e;
  long lStack_7c;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  long lStack_48;
  
  uStack_50 = 0;
  lStack_48 = 0;
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_68 = 0;
  _xpc_dictionary_get_value(param_2,"kCBMsgArgs");
  lVar2 = param_2;
  FUN_100134bcc();
  puVar18 = &uStack_68;
  uVar19 = 0;
  pcVar16 = "kCBMsgArgRFCOMMStopBit";
  pcVar17 = FUN_1000345c4;
  puVar15 = &uStack_60;
  pcVar14 = FUN_1000345c4;
  puVar12 = &uStack_58;
  pcVar13 = "kCBMsgArgRFCOMMParityBit";
  pcVar10 = "kCBMsgArgRFCOMMDataBit";
  pcVar11 = FUN_1000345c4;
  puVar9 = &uStack_50;
  pcVar8 = FUN_1000345c4;
  plVar6 = &lStack_48;
  pcVar7 = "kCBMsgArgRFCOMMBaudRate";
  pcVar4 = "kCBMsgArgRFCOMMChannelID";
  pcVar5 = FUN_1000345c4;
  FUN_1000344a8(param_2,1);
  lStack_7c = lStack_48;
  uVar1 = uRam0000000100cae4b8;
  if ((((int)param_2 == 0) && (lVar2 != 0)) && (lStack_48 - 1U < 0x1e)) {
    uVar19 = uRam0000000100cae4b8;
    _os_log_type_enabled(uRam0000000100cae4b8,0);
    if ((int)uVar19 != 0) {
      uStack_90 = (undefined4)_UNK_100930ae8;
      iStack_8c = (int)lStack_7c;
      uStack_88 = (undefined2)((ulong)lStack_7c >> 0x20);
      uStack_86 = (undefined2)((ulong)lStack_7c >> 0x30);
      __os_log_impl(0x100000000,uVar1,0,"handleRFCOMMPortConfiguration rfcommChannelID: %lld",
                    &uStack_90,0xc);
    }
    FUN_1000070cc();
    FUN_10002f5ac();
  }
  else {
    uVar3 = uRam0000000100cae4b8;
    _os_log_type_enabled(uRam0000000100cae4b8,0x10);
    if ((int)uVar3 != 0) {
      uStack_90 = (undefined4)_UNK_100932b90;
      uStack_88 = 0x840;
      uStack_86 = (undefined2)lVar2;
      uStack_84 = (undefined6)((ulong)lVar2 >> 0x10);
      uStack_7e = 0x800;
      iStack_8c = (int)param_2;
      __os_log_error_impl(0x100000000,uVar1,0x10,
                          "handleRFCOMMPortConfiguration failed with result 0x%x, identifier: %@, rfcommChannelID: %lld"
                          ,&uStack_90,0x1c,in_x6,in_x7,pcVar4,pcVar5,plVar6,pcVar7,pcVar8,puVar9,
                          pcVar10,pcVar11,puVar12,pcVar13,pcVar14,puVar15,pcVar16,pcVar17,puVar18,
                          uVar19);
    }
  }
  return 0;
}


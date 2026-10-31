/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100407e38
 * original code SHA256: feaba5c02c59946769b590d4be3a39358920d46df402afde74637187cdb6d545
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 phone_fn_100407e38(undefined8 param_1,long param_2)

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
  undefined *puVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  undefined4 uStack_60;
  int iStack_5c;
  undefined2 uStack_58;
  undefined2 uStack_56;
  undefined6 uStack_54;
  undefined2 uStack_4e;
  long lStack_4c;
  undefined8 uStack_40;
  long lStack_38;
  
  uStack_40 = 0;
  lStack_38 = 0;
  _xpc_dictionary_get_value(param_2,"kCBMsgArgs");
  lVar2 = param_2;
  FUN_100134bcc();
  puVar9 = &uStack_40;
  uVar10 = 0;
  pcVar7 = "kCBMsgArgOptions";
  puVar8 = &DAT_100034644;
  plVar6 = &lStack_38;
  pcVar5 = FUN_1000345c4;
  pcVar4 = "kCBMsgArgRFCOMMChannelID";
  FUN_1000344a8(param_2,1);
  lStack_4c = lStack_38;
  uVar1 = uRam0000000100cae4b8;
  if ((((int)param_2 == 0) && (lVar2 != 0)) && (lStack_38 - 1U < 0x1e)) {
    uVar10 = uRam0000000100cae4b8;
    _os_log_type_enabled(uRam0000000100cae4b8,0);
    if ((int)uVar10 != 0) {
      uStack_60 = (undefined4)_UNK_100930ae8;
      iStack_5c = (int)lStack_4c;
      uStack_58 = (undefined2)((ulong)lStack_4c >> 0x20);
      uStack_56 = (undefined2)((ulong)lStack_4c >> 0x30);
      __os_log_impl(0x100000000,uVar1,0,"handleOpenRFCOMMChannel rfcommChannelID: %lld",&uStack_60,
                    0xc);
    }
    FUN_1000070cc();
    FUN_10002f5ac();
  }
  else {
    uVar3 = uRam0000000100cae4b8;
    _os_log_type_enabled(uRam0000000100cae4b8,0x10);
    if ((int)uVar3 != 0) {
      uStack_60 = (undefined4)_UNK_100932b90;
      uStack_58 = 0x840;
      uStack_56 = (undefined2)lVar2;
      uStack_54 = (undefined6)((ulong)lVar2 >> 0x10);
      uStack_4e = 0x800;
      iStack_5c = (int)param_2;
      __os_log_error_impl(0x100000000,uVar1,0x10,
                          "handleOpenRFCOMMChannel failed with result 0x%x, identifier: %@, rfcommChannelID: %lld"
                          ,&uStack_60,0x1c,in_x6,in_x7,pcVar4,pcVar5,plVar6,pcVar7,puVar8,puVar9,
                          uVar10);
    }
  }
  return 0;
}


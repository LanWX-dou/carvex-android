/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100407fd4
 * original code SHA256: fddb6ba4d2095a2e47759c80c2ac5635968899cd47a2265d15db6d891cd25a7b
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 phone_fn_100407fd4(undefined8 param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 in_x6;
  undefined8 in_x7;
  char *pcVar4;
  code *pcVar5;
  long *plVar6;
  undefined8 uVar7;
  undefined4 uStack_50;
  long lStack_4c;
  long lStack_38;
  
  lStack_38 = 0;
  _xpc_dictionary_get_value(param_2,"kCBMsgArgs");
  lVar2 = param_2;
  FUN_100134bcc();
  plVar6 = &lStack_38;
  uVar7 = 0;
  pcVar4 = "kCBMsgArgRFCOMMChannelID";
  pcVar5 = FUN_1000345c4;
  FUN_1000344a8(param_2,1);
  uVar1 = uRam0000000100cae4b8;
  uVar3 = uRam0000000100cae4b8;
  _os_log_type_enabled(uRam0000000100cae4b8,0);
  if ((int)uVar3 != 0) {
    uStack_50 = (undefined4)_UNK_100930ae8;
    lStack_4c = lStack_38;
    __os_log_impl(0x100000000,uVar1,0,"handleCloseRFCOMMChannel rfcommChannelID: %lld",&uStack_50,
                  0xc,in_x6,in_x7,pcVar4,pcVar5,plVar6,uVar7);
  }
  if ((((int)param_2 == 0) && (lStack_38 - 1U < 0x1e)) && (lVar2 != 0)) {
    FUN_1000070cc();
    FUN_10002f5ac();
  }
  return 0;
}


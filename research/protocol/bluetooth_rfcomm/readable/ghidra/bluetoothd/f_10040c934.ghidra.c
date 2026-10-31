/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10040c934
 * original code SHA256: 9e8d8aca18de597c17076dd1945b1cdbec124deb91c9d90a58d34c6d63a07c75
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_retain_x1 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x19 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void phone_fn_10040c934(undefined8 param_1,undefined8 param_2,int param_3,undefined4 param_4,
                       undefined4 param_5,undefined4 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 uVar1;
  ID self;
  undefined8 uVar2;
  ID IVar3;
  ID IVar4;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  undefined2 uStack_7c;
  undefined4 uStack_7a;
  undefined2 uStack_76;
  undefined4 uStack_74;
  undefined2 uStack_70;
  undefined4 uStack_6e;
  long lStack_68;
  
  uVar2 = uRam0000000100cae4b8;
  lStack_68 = *(long *)PTR____stack_chk_guard_100bfc980;
  uVar1 = uRam0000000100cae4b8;
  _os_log_type_enabled(uRam0000000100cae4b8,0);
  if ((int)uVar1 != 0) {
    uStack_90 = CONCAT44(param_3,(int)_UNK_100930f08);
    uStack_88 = CONCAT26(0x400,CONCAT42(param_4,0x400));
    uStack_7c = 0x400;
    uStack_76 = 0x400;
    uStack_74 = (undefined4)param_7;
    uStack_70 = 0x400;
    uStack_6e = (undefined4)param_8;
    uStack_80 = param_5;
    uStack_7a = param_6;
    __os_log_impl(0x100000000,uVar2,0,
                  "RFCOMM Channel connected: result: 0x%x, rfcommChannelID: 0x%x, frameSize: 0x%x, link handle: 0x%x, incoming?: %d, sock: 0x%x"
                  ,&uStack_90,0x26);
  }
  self = 0;
  _xpc_dictionary_create(0,0,0);
  if (self != 0) {
    uStack_90 = 0;
    uStack_88 = 0;
    objc_stub::FUN_100917860(self,&uStack_90);
    _xpc_dictionary_set_uuid(self,"kCBMsgArgDeviceUUID",&uStack_90);
  }
  _xpc_dictionary_set_int64(self,"kCBMsgArgResult",(long)param_3);
  _xpc_dictionary_set_int64(self,"kCBMsgArgRFCOMMChannelID",param_4);
  _xpc_dictionary_set_int64(self,"kCBMsgArgMTU",param_5);
  _xpc_dictionary_set_bool(self,"kCBMsgArgIsIncoming",param_7);
  _xpc_dictionary_set_fd(self,"kCBMsgArgSocket",param_8);
  if (lRam0000000100c1b218 != -1) {
    FUN_1008bc640();
  }
  uVar2 = uRam0000000100c1b210;
  FUN_10002d028(uRam0000000100c1b210,self,0);
  if (lRam0000000100c1b238 != -1) {
    FUN_1008bc658();
  }
  IVar4 = IRam0000000100c1b230;
  FUN_10002d680(IRam0000000100c1b230,uVar2,0);
  if ((IVar4 != 0) && (FUN_1005fc690(), IVar4 != 0)) {
    _objc_retainAutorelease(IVar4);
    IVar3 = objc_stub::FUN_100913420(IVar4);
    IVar4 = objc_stub::FUN_100919c80(IVar4);
    _xpc_dictionary_set_data(self,"kCBMsgArgServiceUUID",IVar3,IVar4);
  }
  FUN_100028e88(param_1,0x3e,self,1);
  if (*(long *)PTR____stack_chk_guard_100bfc980 != lStack_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10040cbf8
 * original code SHA256: 6a6a382235a5ea8b89e10edfeed697db8e87c9dadef0db939047aa09003d02cd
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_retain_x1 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x19 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void phone_fn_10040cbf8(undefined8 param_1,undefined8 param_2,int param_3,undefined4 param_4,
                       undefined4 param_5)

{
  undefined8 uVar1;
  undefined8 uVar2;
  ID self;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined4 uStack_50;
  long lStack_48;
  
  uVar1 = uRam0000000100cae4b8;
  lStack_48 = *(long *)PTR____stack_chk_guard_100bfc980;
  uVar2 = uRam0000000100cae4b8;
  _os_log_type_enabled(uRam0000000100cae4b8,0);
  if ((int)uVar2 != 0) {
    uStack_60 = CONCAT44(param_3,(int)_UNK_100930b08);
    uStack_58 = CONCAT26(0x400,CONCAT42(param_4,0x400));
    uStack_50 = param_5;
    __os_log_impl(0x100000000,uVar1,0,
                  "RFCOMM Channel disconnected: result: 0x%x, rfcommChannelID: 0x%x, link handle: 0x%x"
                  ,&uStack_60,0x14);
  }
  self = 0;
  _xpc_dictionary_create(0,0,0);
  if (self != 0) {
    uStack_60 = 0;
    uStack_58 = 0;
    objc_stub::FUN_100917860(self,&uStack_60);
    _xpc_dictionary_set_uuid(self,"kCBMsgArgDeviceUUID",&uStack_60);
  }
  _xpc_dictionary_set_int64(self,"kCBMsgArgResult",(long)param_3);
  _xpc_dictionary_set_int64(self,"kCBMsgArgRFCOMMChannelID",param_4);
  FUN_100028e88(param_1,0x3f,self,1);
  if (*(long *)PTR____stack_chk_guard_100bfc980 == lStack_48) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail(0);
}


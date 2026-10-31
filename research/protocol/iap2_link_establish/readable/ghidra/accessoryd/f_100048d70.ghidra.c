/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100048d70
 * original code SHA256: c46bab998fc6d5727e373d0857255158c5cdee7bba47cc839042350967ee791a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined8
_mfi4Auth_protocol_handle_AuthenticationReset(long param_1,long param_2,undefined8 param_3)

{
  code *pcVar1;
  int iVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined *puVar5;
  ulong unaff_x30;
  undefined2 local_30 [8];
  
  if (param_1 == 0) {
    _mfi4Auth_protocol_handle_AuthenticationReset_cold_4();
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    _mfi4Auth_protocol_handle_AuthenticationReset_cold_3();
  }
  else {
    if (param_2 != 0) {
      uVar3 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_IgnoreAuthReset);
      if ((uVar3 & 1) != 0) {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar5 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            uVar3 = _mfi4Auth_protocol_handleAuthSessionClose_cold_1();
            puVar5 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar2 = _os_log_type_enabled(puVar5,uVar3,0);
        if (iVar2 != 0) {
          local_30[0] = 0;
          __os_log_impl(0x100000000,uVar3,0,"AuthenticationReset: Ignored",local_30,2);
        }
        return 0;
      }
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100048e68);
        (*pcVar1)();
      }
      uVar4 = _mfi4Auth_protocol_initMessage_RequestAuthSetup(param_1,param_3);
      return uVar4;
    }
    _mfi4Auth_protocol_handle_AuthenticationReset_cold_2();
  }
  return 1;
}


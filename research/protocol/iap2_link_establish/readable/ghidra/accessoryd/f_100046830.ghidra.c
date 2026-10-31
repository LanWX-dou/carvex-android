/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100046830
 * original code SHA256: ce8965e756fb87b011d3e474d6770a00c4d3865456d1b5a5f7824db7f22241fa
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_protocol_handle_AuthStart(long param_1,long param_2)

{
  int iVar1;
  undefined8 uVar2;
  
  if (param_1 == 0) {
    uVar2 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar2,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_handle_AuthStart_cold_3(uVar2);
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    uVar2 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar2,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_handle_AuthStart_cold_2(uVar2);
    }
  }
  else {
    if (param_2 != 0) {
      return 0;
    }
    uVar2 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar2,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_handle_AuthStart_cold_1(uVar2);
    }
  }
  return 1;
}


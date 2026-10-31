/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100084ce8
 * original code SHA256: c86c899344f8c5aff06e91937fdd8d0af26fec2f3618fd660d8b32d80522f6df
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x2 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retainBlock replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x9 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_protocol_setSecureTunnelDataReceiveTypeHandler(long param_1,ulong param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_setSecureTunnelDataReceiveTypeHandler_cold_3();
    }
  }
  else if (param_1 == 0) {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_setSecureTunnelDataReceiveTypeHandler_cold_2();
    }
  }
  else if ((uint)param_2 < 3) {
    *(long *)(param_1 + 0xe8 + (param_2 & 0xffffffff) * 8) = param_1;
  }
  else {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_processOutgoingSecureTunnelDataForClient_cold_1(param_2);
    }
  }
  return 0;
}


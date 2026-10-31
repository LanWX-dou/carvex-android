/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100084a40
 * original code SHA256: 03cc739bc437f073e485a15a3282b9737e94c29229d92cdcbb0b115a552d23ba
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _mfi4Auth_relay_handle_iAP2RelayFailed(long param_1,long param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_relay_handle_iAP2RelayFailed_cold_3();
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_relay_handle_iAP2RelayFailed_cold_2();
    }
  }
  else if (param_2 == 0) {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_relay_handle_iAP2RelayFailed_cold_1();
    }
  }
  else {
    _mfi4Auth_protocol_handle_AuthState(param_1,1);
  }
  return 0;
}


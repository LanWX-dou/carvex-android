/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000467e4
 * original code SHA256: 5ad44e04e587dd6cded0c9ffcc17150b686fb03498e5e37db2da98defd3b45ec
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _mfi4Auth_protocol_handle_AuthSetupFailed(long param_1,long param_2)

{
  if (param_1 == 0) {
    _mfi4Auth_protocol_handle_AuthSetupFailed_cold_3();
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    _mfi4Auth_protocol_handle_AuthSetupFailed_cold_2();
  }
  else if (param_2 == 0) {
    _mfi4Auth_protocol_handle_AuthSetupFailed_cold_1();
  }
  else {
    _mfi4Auth_protocol_handle_AuthState(param_1,1);
  }
  return 0;
}


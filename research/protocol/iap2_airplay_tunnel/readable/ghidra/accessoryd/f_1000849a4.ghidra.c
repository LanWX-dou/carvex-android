/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000849a4
 * original code SHA256: 2d69c7bcc01307c1c7ab3581079a13f6048ab71d086c54894ecf03f2eaf04d71
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _mfi4Auth_relay_handle_iAP2RelaySucceeded(long param_1,long param_2,undefined8 param_3)

{
  code *pcVar1;
  int iVar2;
  undefined8 uVar3;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_relay_handle_iAP2RelaySucceeded_cold_3();
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_relay_handle_iAP2RelaySucceeded_cold_2();
    }
  }
  else {
    if (param_2 != 0) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100084a14);
        (*pcVar1)();
      }
      uVar3 = _mfi4Auth_relay_initMessage_RequestiAP2RelayRead(param_1,param_3);
      return uVar3;
    }
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_relay_handle_iAP2RelaySucceeded_cold_1();
    }
  }
  return 1;
}


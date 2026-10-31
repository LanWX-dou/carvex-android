/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100044ee4
 * original code SHA256: 62f33597e53e7d5d7bdcbfbd0d537db2d9caf44ad921b3e2658fc03cbc65817f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _mfi4Auth_protocol_authSetupStart(long param_1,long param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    _mfi4Auth_protocol_authSetupStart_cold_3();
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    _mfi4Auth_protocol_authSetupStart_cold_2();
  }
  else {
    if (param_2 != 0) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100044f18);
        (*pcVar1)();
      }
      uVar2 = _mfi4Auth_protocol_initMessage_RequestAuthSetup();
      return uVar2;
    }
    _mfi4Auth_protocol_authSetupStart_cold_1();
  }
  return 1;
}


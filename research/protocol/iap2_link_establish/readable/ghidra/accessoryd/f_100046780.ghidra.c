/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100046780
 * original code SHA256: 6fde2db62cdff292bd2b5cf61429615927e23cf5d7914fdc31ffd1d1258371e4
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _mfi4Auth_protocol_handle_AuthState(undefined8 *param_1,undefined8 param_2)

{
  code *pcVar1;
  long lVar2;
  ulong unaff_x30;
  
  if (param_1 == (undefined8 *)0x0) {
    _mfi4Auth_protocol_handle_AuthState_cold_2();
  }
  else if (*(char *)((long)param_1 + 0x1e) == '\x01') {
    _mfi4Auth_protocol_handle_AuthState_cold_1();
  }
  else {
    lVar2 = param_1[0x22];
    if (lVar2 != 0) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x1000467cc);
        (*pcVar1)();
      }
                    /* WARNING: Could not recover jumptable at 0x0001000467cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(lVar2 + 0x10))(lVar2,*param_1,param_2);
      return;
    }
  }
  return;
}


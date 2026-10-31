/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100037e68
 * original code SHA256: ad47a44609afb55752f9e86fe0d224f3e4e7f438804ec8dde1c77260ef0363bb
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _mfi4Auth_protocol_setStartRelayHandler(long param_1,void *param_2)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1 == 0) {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_setSessionCloseHandler_cold_1();
    }
  }
  else {
    if (*(void **)(param_1 + 0x140) != (void *)0x0) {
      __Block_release(*(void **)(param_1 + 0x140));
    }
    if (param_2 != (void *)0x0) {
      pvVar2 = __Block_copy(param_2);
      *(void **)(param_1 + 0x140) = pvVar2;
    }
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034db4
 * original code SHA256: 1658fb25e1830fdd639b43c7e44d74986f8521a7c1e01db5ff4d802999ea4ce6
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkHandleSuspend(long param_1)

{
  int iVar1;
  undefined *puVar2;
  
  if ((__iAP2LogEnableMask >> 2 & 1) != 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar2 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_1();
        puVar2 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar2 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar1 = _os_log_type_enabled(puVar2,2);
    if (iVar1 != 0) {
      _iAP2LinkHandleSuspend_cold_2(param_1,puVar2);
      goto LAB_100034e28;
    }
  }
  if (param_1 == 0) {
    return;
  }
LAB_100034e28:
  if ((*(long *)(param_1 + 8) != 0) && (*(int *)(param_1 + 0xb8) == 1)) {
    _iAP2FSMHandleEvent(*(long *)(param_1 + 8),0x1b);
  }
  return;
}


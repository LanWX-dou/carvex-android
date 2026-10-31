/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100008590
 * original code SHA256: b32d0213cade91546b184e470013fd64ecaa428e2366985dae6db2a1f8ee0a59
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 _iAP2LinkIsNoRetransmit(long param_1)

{
  undefined8 uVar1;
  undefined *puVar2;
  
  if ((((*(short *)(param_1 + 6) == 0) && (*(short *)(param_1 + 8) == 0)) &&
      (*(char *)(param_1 + 2) == '\0')) && (*(char *)(param_1 + 3) == '\0')) {
    uVar1 = 1;
  }
  else {
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
      uVar1 = _os_log_type_enabled(puVar2,2);
      if ((int)uVar1 == 0) {
        return uVar1;
      }
      _iAP2LinkIsNoRetransmit_cold_2((short *)(param_1 + 6),param_1,puVar2);
    }
    uVar1 = 0;
  }
  return uVar1;
}


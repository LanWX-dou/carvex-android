/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000331d4
 * original code SHA256: c425bf235ce8717f4afbceda61585a6e212d8dccb0b7c7b5ed0f9b1fe35ff044
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool ___iAP2LinkIsValidSynParamCumAckTimeout(long param_1)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  
  sVar1 = *(short *)(param_1 + 8);
  if ((sVar1 < 10) && ((__iAP2LogEnableMask >> 2 & 1) != 0)) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar3 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_1();
        puVar3 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar3 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar2 = _os_log_type_enabled(puVar3,2);
    if (iVar2 != 0) {
      ___iAP2LinkIsValidSynParamCumAckTimeout_cold_2((short *)(param_1 + 8),puVar3);
    }
  }
  return 9 < sVar1;
}


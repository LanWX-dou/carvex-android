/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100033284
 * original code SHA256: b574e2f12c1dbe083fcfd519b68001a7fb84861c56fd30860f1bf9ca9c68b293
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool ___iAP2LinkIsValidSynParamMaxRetransmissions(long param_1)

{
  uint uVar1;
  int iVar2;
  undefined *puVar3;
  
  uVar1 = *(byte *)(param_1 + 2) - 1;
  if ((0x1d < uVar1) && ((__iAP2LogEnableMask >> 2 & 1) != 0)) {
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
      ___iAP2LinkIsValidSynParamMaxRetransmissions_cold_2((byte *)(param_1 + 2),puVar3);
    }
  }
  return uVar1 < 0x1e;
}


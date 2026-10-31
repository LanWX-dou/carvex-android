/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100033338
 * original code SHA256: 4e6c679bf2cd4e3c495a71119ece2d09cc6f89f038233cf9e7c367a9b7974386
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 ___iAP2LinkIsValidSynParamMaxCumAck(long param_1)

{
  byte bVar1;
  undefined8 uVar2;
  undefined *puVar3;
  
  bVar1 = *(byte *)(param_1 + 3);
  if (((char)bVar1 < '\0') || (*(byte *)(param_1 + 1) < bVar1)) {
    if ((__iAP2LogEnableMask >> 2 & 1) != 0) {
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
      uVar2 = _os_log_type_enabled(puVar3,2);
      if ((int)uVar2 == 0) {
        return uVar2;
      }
      ___iAP2LinkIsValidSynParamMaxCumAck_cold_2((byte *)(param_1 + 3),puVar3);
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}


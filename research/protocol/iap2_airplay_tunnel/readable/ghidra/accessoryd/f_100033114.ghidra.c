/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100033114
 * original code SHA256: 7be110310565d3364b4fccab1291f5f519527b68a2ca887e70997490c62db13a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 ___iAP2LinkIsValidSynParamMaxOutstandingPackets(long param_1)

{
  ulong uVar1;
  undefined8 uVar2;
  char cVar3;
  char *pcVar4;
  undefined *puVar5;
  
  pcVar4 = (char *)(param_1 + 1);
  cVar3 = *pcVar4;
  if (cVar3 == '\0') {
    uVar1 = _iAP2LinkIsNoRetransmit();
    if ((uVar1 & 1) != 0) {
      return 1;
    }
    cVar3 = *pcVar4;
  }
  if ('\0' < cVar3) {
    return 1;
  }
  if ((__iAP2LogEnableMask >> 2 & 1) != 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar5 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_1();
        puVar5 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar5 = *(undefined **)(_gLogObjects + 0xb0);
    }
    uVar2 = _os_log_type_enabled(puVar5,2);
    if ((int)uVar2 == 0) {
      return uVar2;
    }
    ___iAP2LinkIsValidSynParamMaxOutstandingPackets_cold_2(pcVar4,puVar5);
  }
  return 0;
}


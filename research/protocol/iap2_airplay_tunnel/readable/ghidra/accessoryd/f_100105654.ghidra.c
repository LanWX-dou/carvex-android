/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100105654
 * original code SHA256: 4b68be681cbd6cc54601831b29d2b1a4800fea450ce4f2d27852a9219e0b89e9
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */

void _acc_manager2_getTransportTypeStringFromTransportType(undefined8 param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined *puVar3;
  
  uVar2 = param_1;
  if (_gLogObjects == 0 || _gNumLogObjects < 0x10) {
    puVar3 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      uVar2 = _acc_manager2_getProtocolStringFromProtocol_cold_1();
      puVar3 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar3 = *(undefined **)(_gLogObjects + 0x78);
  }
  iVar1 = _os_log_type_enabled(puVar3,uVar2,2);
  if (iVar1 != 0) {
    _acc_manager2_getTransportTypeStringFromTransportType_cold_2(param_1,uVar2);
  }
  _acc_endpoint2_getTransportTypeStringWithTransportType(param_1);
  return;
}


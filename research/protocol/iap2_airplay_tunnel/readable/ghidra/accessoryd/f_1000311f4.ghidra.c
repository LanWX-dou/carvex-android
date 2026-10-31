/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000311f4
 * original code SHA256: f774a94b6010173b2765a60aa6aee57822c0c73a824c057d555580bb4601c831
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_endpoint_linkStateChanged(long param_1,uint param_2)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 local_40;
  uint local_3c;
  
  if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
    puVar4 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      __iap2_endpoint_dispatchQueueFinalizer_cold_1();
      puVar4 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar4 = *(undefined **)(_gLogObjects + 0xb0);
  }
  iVar3 = _os_log_type_enabled(puVar4,0);
  if (iVar3 != 0) {
    local_40 = (undefined4)DAT_1001b30b0;
    local_3c = param_2;
    __os_log_impl(0x100000000,puVar4,0,"Link state changed! (Connected: %d)",&local_40,8);
  }
  bVar2 = *(byte *)(param_1 + 0x68);
  *(char *)(param_1 + 0x68) = (char)param_2;
  uVar1 = bVar2 ^ 1;
  if ((param_2 == 0) || ((uVar1 & 1) == 0)) {
    if (((param_2 | uVar1) & 1) == 0) {
      _iap2_sessionControl_cleanup(param_1);
      _iap2_sessionFileTransfer_cleanup(param_1);
      _iap2_sessionLog_cleanup(param_1);
    }
  }
  else {
    _iap2_endpoint_configUSBHost(param_1);
    _iap2_sessionControl_init(param_1);
    _iap2_sessionControl_start(param_1);
    _iap2_sessionFileTransfer_init(param_1);
    _iap2_sessionFileTransfer_start(param_1);
    _iap2_sessionLog_init(param_1);
    _iap2_sessionLog_start(param_1);
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100084acc
 * original code SHA256: 891122bf437f5434147c814d52f7e14c50849b622af90c94a4073cb38cc8138b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote_RequestAccessoryInfoUpdate
          (long param_1,long param_2)

{
  int iVar1;
  void *pvVar2;
  long lVar3;
  undefined8 uVar4;
  
  if (param_2 != 0) {
    pvVar2 = (void *)_malloc_type_malloc(0x48,0x109004066c3afe2);
    if (pvVar2 != (void *)0x0) {
      lVar3 = _malloc_type_malloc(0xffff,0xe1e96da8);
      if (lVar3 == 0) {
        iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
        if (iVar1 != 0) {
          _mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote_RequestAccessoryInfoUpdate_cold_1();
        }
        uVar4 = 1;
      }
      else {
        _iAP2MsgInit(pvVar2,0x5502,lVar3,0xffff,0,0);
        _mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote(param_1,param_2,pvVar2);
        *(undefined2 *)(param_1 + 0x1c) = 0x5164;
        _iAP2MsgCleanup(pvVar2,1);
        if (*(void **)((long)pvVar2 + 0x18) != (void *)0x0) {
          _free(*(void **)((long)pvVar2 + 0x18));
        }
        uVar4 = 0;
      }
      _free(pvVar2);
      return uVar4;
    }
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote_RequestAccessoryInfoUpdate_cold_2();
    }
  }
  return 1;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100084ef4
 * original code SHA256: 37e30bc7ba91244c4317459183da308e32e79ce3472805693790277593a1d4bc
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote_TypeData
          (long param_1,long param_2,undefined8 param_3,long param_4)

{
  int iVar1;
  undefined8 uVar2;
  void *pvVar3;
  
  uVar2 = 1;
  if ((param_2 != 0) && (param_4 != 0)) {
    pvVar3 = (void *)_mfi4Auth_util_packIntoTunnelDataiAP2Msg(param_3,param_4,0);
    if (pvVar3 == (void *)0x0) {
      iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
      if (iVar1 != 0) {
        _mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote_TypeData_cold_1();
      }
      uVar2 = 1;
    }
    else {
      _mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote(param_1,param_2,pvVar3);
      *(undefined2 *)(param_1 + 0x1c) = 0x5164;
      _iAP2MsgCleanup(pvVar3,1);
      if (*(void **)((long)pvVar3 + 0x18) != (void *)0x0) {
        _free(*(void **)((long)pvVar3 + 0x18));
      }
      _free(pvVar3);
      uVar2 = 0;
    }
  }
  return uVar2;
}


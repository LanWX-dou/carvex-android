/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000858a0
 * original code SHA256: 7ab44526b97ab65e8033985e90b015af265b0cec600e8bb2a2ac40d3d652dcf1
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote(long param_1,long *param_2,long param_3)

{
  undefined2 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  
  uVar2 = 1;
  if ((param_2 != (long *)0x0) && (param_3 != 0)) {
    uVar1 = *(undefined2 *)(param_1 + 0x150);
    lVar3 = _malloc_type_malloc(0x48,0x109004066c3afe2);
    *param_2 = lVar3;
    if (lVar3 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      _iAP2MsgInitWithSom(lVar3,uVar1,0x5164,*(undefined8 *)(param_1 + 0x10),
                          *(undefined4 *)(param_1 + 0x18),0,0);
      lVar3 = *param_2;
      uVar4 = *(undefined8 *)(param_3 + 0x18);
      uVar2 = _iAP2MsgGetMsgLen(param_3);
      _iAP2MsgAddDataParam(lVar3,0,0,uVar4,uVar2);
      uVar2 = 0;
      *(undefined2 *)(param_1 + 0x1c) = 0x5164;
    }
  }
  return uVar2;
}


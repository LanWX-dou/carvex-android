/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100084fa4
 * original code SHA256: d68b78968a213a47b3e877f4b0bec2a71a25b06938aa910f349424a8a2fd9c21
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _mfi4Auth_relay_initMessage_RequestiAP2RelayRead(long param_1,long *param_2)

{
  undefined2 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  if (param_2 != (long *)0x0) {
    uVar1 = *(undefined2 *)(param_1 + 0x150);
    lVar2 = _malloc_type_malloc(0x48,0x109004066c3afe2);
    *param_2 = lVar2;
    if (lVar2 == 0) {
      uVar3 = 0xffffffff;
    }
    else {
      _iAP2MsgInitWithSom(lVar2,uVar1,0x5163,*(undefined8 *)(param_1 + 0x10),
                          *(undefined4 *)(param_1 + 0x18),0,0);
      uVar3 = 0;
      *(undefined2 *)(param_1 + 0x1c) = 0x5163;
    }
    return uVar3;
  }
  return 1;
}


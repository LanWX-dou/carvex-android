/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100129738
 * original code SHA256: 9d9797063d0c124d7f7d26914ff6edf5c424a30beb403986e1b69806f43d639f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined2 _iap2_endpoint_getMaxSendPayloadSize(long param_1)

{
  undefined2 uVar1;
  long lVar2;
  
  uVar1 = 0;
  if (param_1 != 0) {
    if ((*(char *)(param_1 + 0x68) == '\x01') && (*(long *)(param_1 + 0x28) != 0)) {
      lVar2 = *(long *)(*(long *)(param_1 + 0x28) + 0x18);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = _iAP2LinkGetMaxSendPayloadSize(lVar2,0);
      }
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}


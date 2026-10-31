/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001298b0
 * original code SHA256: 2d247e5680b0feb53de82498263ab91f76430fe3da4dc9ab935010f6e5abd157
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1 _iap2_endpoint_getLinkMaxCumAck(long param_1)

{
  long lVar1;
  
  if ((((param_1 != 0) && (*(char *)(param_1 + 0x68) == '\x01')) && (*(long *)(param_1 + 0x28) != 0)
      ) && (lVar1 = *(long *)(*(long *)(param_1 + 0x28) + 0x18), lVar1 != 0)) {
    return *(undefined1 *)(lVar1 + 0x16b);
  }
  return 0;
}


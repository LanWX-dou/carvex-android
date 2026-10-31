/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100005274
 * original code SHA256: 818349e495682a2c56e05ce3a477be9f35d076ba0baf7a1a1981668a55fd6419
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ushort _iAP2MsgGetMsgLen(long param_1)

{
  ushort uVar1;
  
  if (param_1 != 0) {
    if (*(long *)(param_1 + 0x18) == 0) {
      return 0;
    }
    if (5 < *(uint *)(param_1 + 0x10)) {
      uVar1 = *(ushort *)(*(long *)(param_1 + 0x18) + 2);
      return uVar1 >> 8 | uVar1 << 8;
    }
  }
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034a28
 * original code SHA256: e7cbf6f4d86cf2ef3460ffd30c09f6b31cf4899c5e1814cc01fc07c5a4f52f43
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ushort _iAP2LinkGetMaxSendPacketSize(long param_1)

{
  ushort uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(ushort *)(param_1 + 0x1a6);
    if (*(ushort *)(param_1 + 0xc0) <= *(ushort *)(param_1 + 0x1a6)) {
      uVar1 = *(ushort *)(param_1 + 0xc0);
    }
  }
  return uVar1;
}


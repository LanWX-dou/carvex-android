/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100004b44
 * original code SHA256: 8e31dd13cb5e058adbe34e6af03d1d6a13c598117f27df6bbb36ba4a1e1f33c4
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ushort _iAP2MsgGetMsgID(long param_1)

{
  ushort uVar1;
  
  if (param_1 != 0) {
    if (*(long *)(param_1 + 0x18) == 0) {
      return 0;
    }
    if (5 < *(uint *)(param_1 + 0x10)) {
      uVar1 = *(ushort *)(*(long *)(param_1 + 0x18) + 4);
      return uVar1 >> 8 | uVar1 << 8;
    }
  }
  return 0;
}


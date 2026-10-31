/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100067694
 * original code SHA256: bf4106806bf48bca463ea4dc5c5ae417fdefbe0382240a5bc93ece8c09797131
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ushort _iAP2MsgGetSom(long param_1)

{
  ushort uVar1;
  
  if (param_1 != 0) {
    if (*(ushort **)(param_1 + 0x18) == (ushort *)0x0) {
      return 0;
    }
    if (5 < *(uint *)(param_1 + 0x10)) {
      uVar1 = **(ushort **)(param_1 + 0x18);
      return uVar1 >> 8 | uVar1 << 8;
    }
  }
  return 0;
}


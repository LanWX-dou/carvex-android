/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000b3bc
 * original code SHA256: 5b321ea3140d7b1c12a7c59710119f3dd6b4a2c4168af1b229d5b6ce65493fe3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



byte _iAP2PacketIsEAK(long param_1)

{
  return *(byte *)(*(long *)(param_1 + 0x40) + 4) >> 5 & 1;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100067710
 * original code SHA256: 7e3c233001bc38b698b2bee560462dd8f42f647e9cc0b5a9f0c00a51a39550c2
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ushort _iAP2MsgGetParamID(long param_1)

{
  return *(ushort *)(param_1 + 2) >> 8 | *(ushort *)(param_1 + 2) << 8;
}


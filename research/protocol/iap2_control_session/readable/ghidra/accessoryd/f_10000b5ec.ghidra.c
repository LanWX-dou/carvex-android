/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000b5ec
 * original code SHA256: 23c8cd26d5ae71e2b941a005fab14d9165cc525ac58267621bb0e69e4a263bb3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 _iAP2LinkGetMainTimer(long param_1)

{
  return *(undefined8 *)(param_1 + 200);
}


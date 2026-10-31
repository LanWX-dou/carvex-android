/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034778
 * original code SHA256: 141fccbf54379950ff8c564960fe49f875154177970c936c8fef2a3ce7a0d67f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkShuttingDown(long param_1)

{
  if ((param_1 != 0) && (*(long *)(param_1 + 200) != 0)) {
    _iAP2TimeDelete();
    *(undefined8 *)(param_1 + 200) = 0;
  }
  return;
}


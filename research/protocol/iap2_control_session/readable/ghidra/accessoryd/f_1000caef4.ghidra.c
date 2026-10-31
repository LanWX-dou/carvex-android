/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000caef4
 * original code SHA256: f6dc4aa03c333d2009dbb1b0f86001b270e73b02ed37a2eb3a6c2b4f95f72e5f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkRunLoopShuttingDown(long param_1)

{
  if (param_1 != 0) {
    *(undefined1 *)(param_1 + 0x2c) = 1;
    _iAP2LinkShuttingDown(*(undefined8 *)(param_1 + 0x18));
    return;
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100035144
 * original code SHA256: f4723137cdf4ea7f8ec1cbc53d901305169d3f9421f6d252630fccc859fe0878
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkSetUseiAP2LinkRunLoop(long param_1)

{
  *(byte *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) | 0x10;
  return;
}


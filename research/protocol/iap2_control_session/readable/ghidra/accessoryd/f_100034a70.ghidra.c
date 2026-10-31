/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034a70
 * original code SHA256: 15df4ed30df35c9adecbc6f0690b513a7c5e2b9adf893410073bc6b7dfd23d17
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkStart(long param_1)

{
  _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),0);
  return;
}


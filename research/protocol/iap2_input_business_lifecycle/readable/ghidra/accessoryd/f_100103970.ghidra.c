/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100103970
 * original code SHA256: 4e82f16242e6f7da57cc58ff1bfed5e5da77e45cdc2a522d06496107c7843a81
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkConnectedCB(long param_1)

{
  _iap2_endpoint_linkStateChanged(*(undefined8 *)(*(long *)(param_1 + 0xb0) + 0x10));
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10017b6a8
 * original code SHA256: 439c0ebe9e4c9f3d050d4f2f23dd1e7df80707468bb4f6234e7303996afe02a4
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


bool _acc_protocolParser_iAP2_destroy(undefined8 *param_1)

{
  if ((param_1 != (undefined8 *)0x0) && ((void *)*param_1 != (void *)0x0)) {
    _free((void *)*param_1);
    *param_1 = 0;
  }
  return param_1 != (undefined8 *)0x0;
}


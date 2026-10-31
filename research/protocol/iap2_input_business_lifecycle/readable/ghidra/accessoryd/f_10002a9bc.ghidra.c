/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002a9bc
 * original code SHA256: e16504ac8ec07288c26df992ff934483e44261c8eb6dd07808e629821c7916b9
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_sessionControl_sendOutgoingMessageAndCallbackOnACK(undefined8 param_1,undefined8 param_2)

{
  __sendOutgoingMessage(param_1,param_2,1);
  return;
}


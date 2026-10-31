/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000084d0
 * original code SHA256: 403df47aed8d4d93040ed3f8060ab925e87e97a09e346c8ad8371a542338a49e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkGetSessSendPckListCount(long param_1,uint param_2)

{
  _iAP2ListArrayGetCount(*(undefined8 *)(param_1 + 0x130 + (ulong)param_2 * 8));
  return;
}


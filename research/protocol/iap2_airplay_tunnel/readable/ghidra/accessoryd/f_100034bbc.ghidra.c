/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034bbc
 * original code SHA256: e73297e547fc3a9595973f1f80aaffa7203ff966c37c723e9ff1d3e9b8a382fb
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkDetached(long param_1)

{
  if (param_1 != 0) {
    _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),0xe);
    *(undefined4 *)(param_1 + 0x19e) = 0x3e8ffff;
    *(undefined2 *)(param_1 + 0x1a2) = 10;
    *(int *)(param_1 + 0x19a) = (int)DAT_1001b3348;
    *(undefined4 *)(param_1 + 0x1a4) = 0xffff0100;
  }
  return;
}


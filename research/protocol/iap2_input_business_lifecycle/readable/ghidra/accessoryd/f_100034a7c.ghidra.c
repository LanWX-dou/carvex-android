/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034a7c
 * original code SHA256: 8337f2332c46f59a96df915a634852f98ab58219d63122b7078787fd0a333380
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkAttached(long param_1)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x19e) = 0x3e8ffff;
    *(undefined2 *)(param_1 + 0x1a2) = 10;
    *(int *)(param_1 + 0x19a) = (int)DAT_1001b3348;
    *(undefined4 *)(param_1 + 0x1a4) = 0xffff0100;
    _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),1);
    return;
  }
  return;
}


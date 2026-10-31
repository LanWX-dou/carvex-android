/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000c2d7c
 * original code SHA256: 4853f8c3b04b68b95790910fd6e97457a2c4af42f615b4eff2c44ff93753cc74
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_power_sleepUpdateHandler(long param_1)

{
  if ((param_1 != 0) && (*(long *)(param_1 + 0x28) != 0)) {
    _iAP2LinkRunLoopHandleSuspend();
    _usleep(100000);
  }
  return 1;
}


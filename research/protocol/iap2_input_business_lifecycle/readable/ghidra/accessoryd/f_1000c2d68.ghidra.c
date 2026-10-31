/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000c2d68
 * original code SHA256: c6c9adae7898a14a38658f0d68075c89d4a812a0cfe7e6661e8aaf1c1c91e01e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_power_unregisterForSleepNotification(long param_1)

{
  if ((param_1 != 0) && (*(long *)(param_1 + 8) != 0)) {
    _platform_power_unregisterForSleepWakeUpdate();
    return;
  }
  return;
}


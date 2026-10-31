/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000c2c58
 * original code SHA256: e40a61fa68b7eea658ad71147a513f3109bce06814a24806f30c66bbaac54d91
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iap2_power_registerForSleepNotification(long *param_1)

{
  long lVar1;
  undefined *local_50;
  undefined8 local_48;
  code *local_40;
  undefined *puStack_38;
  undefined8 local_30;
  undefined8 uStack_28;
  
  if ((param_1 != (long *)0x0) && (param_1[1] != 0)) {
    local_30 = _CFRetain();
    if ((*param_1 == 0) || (lVar1 = *(long *)(*param_1 + 0x40), lVar1 == 0)) {
      uStack_28 = 0;
    }
    else {
      uStack_28 = 0;
      if (*(long *)(lVar1 + 0x10) != 0) {
        uStack_28 = _CFRetain();
      }
    }
    local_50 = PTR___NSConcreteStackBlock_10022bb78;
    local_48 = DAT_1001b3118;
    local_40 = ___iap2_power_registerForSleepNotification_block_invoke;
    puStack_38 = &___block_descriptor_tmp_26;
    _acc_manager2_performPlatformWorkAsync(&local_40,&local_50);
  }
  return;
}


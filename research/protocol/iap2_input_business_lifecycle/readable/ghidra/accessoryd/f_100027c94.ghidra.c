/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100027c94
 * original code SHA256: 293e9c8afd4dd987b6b12538aeeaed2212f2c3b909a36a4f836b2094cb4de069
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */

byte _platform_power_sendSleepUpdate(long param_1)

{
  dispatch_queue_t pdVar1;
  byte bVar2;
  undefined *local_70;
  undefined8 local_68;
  code *local_60;
  undefined *puStack_58;
  undefined8 *local_50;
  long lStack_48;
  undefined8 local_40;
  undefined8 *local_38;
  undefined8 local_30;
  undefined1 local_28;
  
  local_38 = &local_40;
  local_40 = 0;
  local_30 = DAT_1001b3120;
  bVar2 = 1;
  local_28 = 1;
  if (param_1 != 0) {
    _CFRetain();
    pdVar1 = _dispatch_get_global_queue(0,0);
    local_70 = PTR___NSConcreteStackBlock_10022bb78;
    local_68 = DAT_1001b3078;
    local_60 = ___platform_power_sendSleepUpdate_block_invoke;
    puStack_58 = &DAT_1002184b0;
    local_50 = &local_40;
    lStack_48 = param_1;
    _dispatch_async(pdVar1,&local_70);
    bVar2 = *(byte *)(local_38 + 3);
  }
  __Block_object_dispose(&local_40,8);
  return bVar2 & 1;
}


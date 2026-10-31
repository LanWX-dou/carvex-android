/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000fc9f0
 * original code SHA256: 0f32b3e9e3f54b90bff71b9b5fd733afbf23448e55048132d559e93b019e0e3c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined4 _acc_connection2_getTransportTypeForEndpoint(long param_1,long param_2)

{
  undefined4 uVar1;
  undefined *local_78;
  undefined8 local_70;
  code *local_68;
  undefined *puStack_60;
  undefined8 *local_58;
  long lStack_50;
  long local_48;
  undefined8 local_40;
  undefined8 *local_38;
  undefined8 local_30;
  undefined4 local_28;
  
  local_38 = &local_40;
  local_40 = 0;
  local_30 = DAT_1001b3120;
  uVar1 = 0x13;
  local_28 = 0x13;
  if ((param_1 != 0) && (param_2 != 0)) {
    local_78 = PTR___NSConcreteStackBlock_10022bb78;
    local_70 = DAT_1001b3078;
    local_68 = ___acc_connection2_getTransportTypeForEndpoint_block_invoke;
    puStack_60 = &DAT_100220db0;
    local_58 = &local_40;
    lStack_50 = param_1;
    local_48 = param_2;
    _acc_connection2_performSyncWithCleanup(param_1,&local_78,0);
    uVar1 = *(undefined4 *)(local_38 + 3);
  }
  __Block_object_dispose(&local_40,8);
  return uVar1;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000f6244
 * original code SHA256: 91f367af02c4590c9848901f96ad5ee9fb0c0bd0627279f7795af98b91c04607
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */

undefined8
_acc_manager2_createEndpointForConnection
          (long param_1,undefined4 param_2,undefined4 param_3,long param_4)

{
  int iVar1;
  long lVar2;
  undefined *puVar3;
  undefined8 uVar4;
  undefined *local_a0;
  undefined8 local_98;
  code *local_90;
  undefined *puStack_88;
  undefined8 *local_80;
  long lStack_78;
  long local_70;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined8 local_60;
  undefined8 *local_58;
  undefined8 local_50;
  undefined8 local_48;
  
  local_58 = &local_60;
  local_60 = 0;
  local_50 = DAT_1001b3120;
  local_48 = 0;
  lVar2 = param_1;
  if (_gLogObjects == 0 || _gNumLogObjects < 0x10) {
    puVar3 = PTR___os_log_default_10022bbb0;
    if (DAT_10023eef8 != -1) {
      lVar2 = ___acc_manager2_removeConnection_block_invoke_cold_3();
      puVar3 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar3 = *(undefined **)(_gLogObjects + 0x78);
  }
  iVar1 = _os_log_type_enabled(puVar3,lVar2,2);
  if (iVar1 != 0) {
    _acc_manager2_createEndpointForConnection_cold_2(param_1,lVar2);
  }
  if (param_1 != 0) {
    _CFRetain(param_1);
    if (param_4 != 0) {
      _CFRetain(param_4);
    }
    local_a0 = PTR___NSConcreteStackBlock_10022bb78;
    local_98 = DAT_1001b3078;
    local_90 = ___acc_manager2_createEndpointForConnection_block_invoke;
    puStack_88 = &DAT_100218488;
    local_80 = &local_60;
    lStack_78 = param_1;
    local_70 = param_4;
    local_68 = param_2;
    uStack_64 = param_3;
    _acc_manager2_performSync(&local_a0);
  }
  uVar4 = local_58[3];
  __Block_object_dispose(&local_60,8);
  return uVar4;
}


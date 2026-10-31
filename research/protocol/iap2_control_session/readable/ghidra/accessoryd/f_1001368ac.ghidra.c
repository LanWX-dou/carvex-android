/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001368ac
 * original code SHA256: cce616d94729122f98f58d18c1dd2afae877ef758b51c86f839b16ef01e76f70
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1 _iap2_sessionLog_sendOutgoingMessage(long param_1,long param_2,undefined2 param_3)

{
  undefined1 uVar1;
  long lVar2;
  long *plVar3;
  undefined *local_88;
  undefined8 local_80;
  code *local_78;
  undefined *puStack_70;
  undefined8 *local_68;
  long lStack_60;
  undefined2 local_58;
  undefined8 local_50;
  undefined8 *local_48;
  undefined8 local_40;
  undefined1 local_38;
  
  local_48 = &local_50;
  local_50 = 0;
  local_40 = DAT_1001b3260;
  local_38 = 0;
  if ((((param_1 != 0) && (param_2 != 0)) &&
      (plVar3 = *(long **)(param_1 + 0x20), plVar3 != (long *)0x0)) &&
     (((*plVar3 != 0 && (*(long *)(*plVar3 + 8) != 0)) &&
      (lVar2 = _acc_manager2_copyConnectionUUIDFromEndpointUUID(), lVar2 != 0)))) {
    local_88 = PTR___NSConcreteStackBlock_10022bb78;
    local_80 = DAT_1001b3118;
    local_78 = ___iap2_sessionLog_sendOutgoingMessage_block_invoke;
    puStack_70 = &DAT_10021a330;
    local_68 = &local_50;
    lStack_60 = param_2;
    local_58 = param_3;
    _acc_manager2_performBlockForConnectionEndpoint(lVar2,*(undefined8 *)(*plVar3 + 8),&local_88);
    _CFRelease(lVar2);
  }
  uVar1 = *(undefined1 *)(local_48 + 3);
  __Block_object_dispose(&local_50,8);
  return uVar1;
}


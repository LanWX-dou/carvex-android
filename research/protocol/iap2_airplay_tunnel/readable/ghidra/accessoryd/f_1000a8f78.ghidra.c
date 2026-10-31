/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000a8f78
 * original code SHA256: d49d014d3a07b6afb5e854f8d046d523ab26b85d04ea0a2855c6183a268e724c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1 _mfi4Auth_endpoint_processIncomingData(long *param_1,long param_2)

{
  int iVar1;
  ulong uVar2;
  undefined *puVar3;
  undefined *puVar4;
  uint local_90;
  char *local_8c;
  undefined2 local_84;
  undefined4 local_82;
  undefined *local_70;
  undefined8 local_68;
  code *local_60;
  undefined *puStack_58;
  long *local_50;
  long lStack_48;
  
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
    puVar4 = PTR___os_log_default_10022bbb0;
    if (DAT_10023eb40 != -1) {
      _logObjectForModule_cold_1();
      puVar4 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar4 = *(undefined **)(_gLogObjects + 0x1d0);
  }
  iVar1 = _os_log_type_enabled(puVar4,0);
  if (iVar1 != 0) {
    local_90 = local_90 & 0xffff0000;
    __os_log_impl(0x100000000,puVar4,0,"mfi4Auth_endpoint_processIncomingData",&local_90,2);
  }
  puVar4 = _kCFACCUserDefaultsKey_PretendNoNFCResponse;
  if (param_1 == (long *)0x0) {
    _mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_cold_4(&local_90);
  }
  else if (*param_1 == 0) {
    _mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_cold_3(&local_90);
  }
  else {
    if (param_2 != 0) {
      if ((*(int *)(*param_1 + 0x18) == 0xd) &&
         (uVar2 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_PretendNoNFCResponse),
         (uVar2 & 1) != 0)) {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
          puVar3 = PTR___os_log_default_10022bbb0;
          if (DAT_10023eb40 != -1) {
            __mfi4Auth_endpoint_initSession_cold_2();
            puVar3 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar3 = *(undefined **)(_gLogObjects + 0x1d0);
        }
        iVar1 = _os_log_type_enabled(puVar3,0);
        if (iVar1 != 0) {
          local_82 = _acc_userDefaults_boolForKey(puVar4);
          local_90 = (uint)DAT_1001b3098;
          local_8c = "mfi4Auth_endpoint_processIncomingData";
          local_84 = 0x400;
          __os_log_impl(0x100000000,puVar3,0,"%s: PretendNoNFCResponse %d, ignore incomingData!",
                        &local_90,0x12);
        }
      }
      else {
        _CFRetain(param_2);
        local_70 = PTR___NSConcreteStackBlock_10022bb78;
        local_68 = DAT_1001b3118;
        local_60 = ___mfi4Auth_endpoint_processIncomingData_block_invoke;
        puStack_58 = &___block_descriptor_tmp_27;
        local_50 = param_1;
        lStack_48 = param_2;
        _acc_protocolEndpoint_performAsync(&local_60,*param_1,(char)param_1[3],param_1[2],&local_70)
        ;
      }
      return 1;
    }
    _mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_cold_2(&local_90);
  }
  return (undefined1)local_90;
}


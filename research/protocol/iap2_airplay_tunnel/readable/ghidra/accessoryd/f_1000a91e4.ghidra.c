/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000a91e4
 * original code SHA256: 1d4ad41ce0f8cba013474bc05533eed5b73860390ddf4aafc23bd5c4b9b7094c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1
_mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient
          (long *param_1,undefined4 param_2,long param_3)

{
  int iVar1;
  undefined *puVar2;
  undefined *local_88;
  undefined8 local_80;
  code *local_78;
  undefined *puStack_70;
  long *local_68;
  long lStack_60;
  undefined1 local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined2 local_48;
  undefined8 local_46;
  
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
    puVar2 = PTR___os_log_default_10022bbb0;
    if (DAT_10023eb40 != -1) {
      _logObjectForModule_cold_1();
      puVar2 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar2 = *(undefined **)(_gLogObjects + 0x1d0);
  }
  iVar1 = _os_log_type_enabled(puVar2,0);
  if (iVar1 != 0) {
    local_46 = _CFDataGetLength(param_3);
    local_50 = (undefined4)DAT_1001b3108;
    local_48 = 0x800;
    local_4c = param_2;
    __os_log_impl(0x100000000,puVar2,0,
                  "mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient: type %d, dataOut %ld bytes"
                  ,&local_50,0x12);
  }
  if (param_1 == (long *)0x0) {
    _mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_cold_4(&local_50);
  }
  else if (*param_1 == 0) {
    _mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_cold_3(&local_50);
  }
  else {
    if (param_3 != 0) {
      _CFRetain(param_3);
      local_88 = PTR___NSConcreteStackBlock_10022bb78;
      local_80 = DAT_1001b3118;
      local_78 = ___mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_block_invoke;
      puStack_70 = &___block_descriptor_tmp_28;
      local_58 = (undefined1)param_2;
      local_68 = param_1;
      lStack_60 = param_3;
      _acc_protocolEndpoint_performAsync(*param_1,(char)param_1[3],param_1[2],&local_88);
      return 1;
    }
    _mfi4Auth_endpoint_processOutgoingSecureTunnelDataForClient_cold_2(&local_50);
  }
  return (undefined1)local_50;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000ab3ac
 * original code SHA256: 3a5971035c6d5c563fcea9aadde032f6aacb30f531b9022fd3e53211daeab080
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void ____mfi4Auth_endpoint_startRelayForT56_block_invoke
               (long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined *puVar2;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  undefined8 local_42;
  undefined2 local_3a;
  undefined8 local_38;
  
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
    local_50 = (undefined4)DAT_1001b3080;
    local_4c = "_mfi4Auth_endpoint_startRelayForT56_block_invoke";
    local_44 = 0x840;
    local_3a = 0x840;
    local_42 = param_2;
    local_38 = param_3;
    __os_log_impl(0x100000000,puVar2,0,"%s: processOutgoingSecureTunnelDataForClient: %@, data %@",
                  &local_50,0x20);
  }
  _acc_manager2_processIncomingDataForConnectionEndpoint
            (*(undefined8 *)(param_1 + 0x20),*(undefined8 *)(param_1 + 0x28),param_3);
  return;
}


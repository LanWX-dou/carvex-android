/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100084bd4
 * original code SHA256: 85026a760061689141b33ae06149d01c862767b37d046c508591975d90acb58f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _mfi4Auth_relay_StartRelayForType(undefined8 *param_1,undefined8 param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  int iVar2;
  long lVar3;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  uint local_42;
  
  if (param_1 == (undefined8 *)0x0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_setSecureTunnelDataReceiveTypeHandler_cold_3();
LAB_100084cdc:
      uVar1 = 0;
      goto joined_r0x000100084ce0;
    }
  }
  else if ((uint)param_2 < 3) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
    if (iVar2 != 0) {
      local_50 = (undefined4)DAT_1001b3098;
      local_4c = "mfi4Auth_relay_StartRelayForType";
      local_44 = 0x400;
      local_42 = (uint)param_2;
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,"%s: secureTunnelType %d",&local_50
                    ,0x12);
    }
    lVar3 = param_1[0x28];
    if (lVar3 != 0) {
      uVar1 = (**(code **)(lVar3 + 0x10))(lVar3,*param_1,param_2);
      goto joined_r0x000100084ce0;
    }
  }
  else {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_setEndpointSecureTunnelDataReceiveTypeHandler_cold_1
                (param_2);
      goto LAB_100084cdc;
    }
  }
  uVar1 = 0;
joined_r0x000100084ce0:
  if (param_3 != (undefined1 *)0x0) {
    *param_3 = uVar1;
  }
  return;
}


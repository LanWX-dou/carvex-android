/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100004f14
 * original code SHA256: e0a1fd619584485259ad14c67c9defe61b915eac1f8ee9b915bbf5b25b78bd1d
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 __sendOutgoingMessage(long *param_1,long param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  ulong uVar4;
  undefined *puVar5;
  undefined4 local_60;
  undefined4 local_5c;
  undefined2 local_58;
  undefined4 local_56;
  undefined2 local_52;
  long local_50;
  
  if (((param_1 != (long *)0x0) && (param_2 != 0)) && (*param_1 != 0)) {
    uVar3 = _iAP2MsgGetMsgID(param_2);
    uVar1 = _iAP2MsgGetMsgLen(param_2);
    uVar4 = _iap2_identification_isIdentifiedForOutgoingMessageID(param_1,uVar3);
    if ((uVar4 & 1) != 0) {
      if (param_3 == 0) {
        _iAP2MsgSendControl(param_1[5],param_2);
      }
      else {
        _iAP2MsgSendControlAndCallbackOnAck();
      }
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x18)) {
        puVar5 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          __sendOutgoingMessage_cold_2();
          puVar5 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar5 = *(undefined **)(_gLogObjects + 0xb8);
      }
      iVar2 = _os_log_type_enabled(puVar5,1);
      if (iVar2 == 0) {
        return 1;
      }
      local_50 = param_1[1];
      local_60 = (undefined4)DAT_1001b3150;
      local_5c = (undefined4)uVar3;
      local_58 = 0x400;
      local_52 = 0x840;
      local_56 = uVar1;
      __os_log_impl(0x100000000,puVar5,1,"Outgoing Message ID: 0x%04X (%d bytes) for endpoint %@",
                    &local_60,0x18);
      return 1;
    }
    __sendOutgoingMessage_cold_1(uVar3,param_1);
  }
  if (_gLogObjects == 0 || _gNumLogObjects < 0x18) {
    puVar5 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      ____requestAuthorization_block_invoke_cold_2();
      puVar5 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar5 = *(undefined **)(_gLogObjects + 0xb8);
  }
  iVar2 = _os_log_type_enabled(puVar5,1);
  if (iVar2 != 0) {
    uVar1 = _iAP2MsgGetMsgID(param_2);
    local_56 = _iAP2MsgGetMsgLen(param_2);
    if (param_1 == (long *)0x0) {
      local_50 = 0;
    }
    else {
      local_50 = 0;
      if (*param_1 != 0) {
        local_50 = param_1[1];
      }
    }
    local_60 = (undefined4)DAT_1001b3150;
    local_58 = 0x400;
    local_52 = 0x840;
    local_5c = uVar1;
    __os_log_impl(0x100000000,puVar5,1,
                  "Failed to send, Outgoing Message ID: 0x%04X (%d bytes) for endpoint %@",&local_60
                  ,0x18);
  }
  return 0;
}


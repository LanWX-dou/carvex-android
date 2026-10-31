/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000fec30
 * original code SHA256: fff132a59bf6d4e88d82ffe0898737e67633f5fe8e4bc74a9958218f0598aa89
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x0001000fee90) */

undefined8 _mfi4Auth_protocol_messageHandler_receiveIncomingData(undefined8 *param_1,long param_2)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  ushort uVar6;
  undefined8 uVar7;
  uint local_a0;
  uint local_9c;
  undefined1 *local_90;
  undefined1 *puStack_88;
  undefined1 *puStack_80;
  undefined1 *puStack_78;
  undefined1 *local_70;
  undefined1 *puStack_68;
  undefined1 *puStack_60;
  undefined1 *puStack_58;
  undefined1 *local_50;
  byte local_41;
  void *local_40 [2];
  
  iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
  if (iVar2 != 0) {
    local_40[0] = (void *)((ulong)local_40[0] & 0xffffffffffff0000);
    __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                  "mfi4Auth_protocol_messageHandler_receiveIncomingData",local_40,2);
  }
  local_40[0] = (void *)0x0;
  local_41 = 0;
  if (param_1 == (undefined8 *)0x0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_receiveIncomingData_cold_5();
    }
  }
  else if (*(char *)((long)param_1 + 0x1e) == '\x01') {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_receiveIncomingData_cold_4();
    }
  }
  else if (param_2 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_receiveIncomingData_cold_3();
    }
  }
  else {
    _CFRetain(param_2);
    puStack_88 = &DAT_aaaaaaaaaaaaaaaa;
    local_90 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_78 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_80 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_68 = &DAT_aaaaaaaaaaaaaaaa;
    local_70 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_58 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_60 = &DAT_aaaaaaaaaaaaaaaa;
    local_50 = &DAT_aaaaaaaaaaaaaaaa;
    uVar6 = *(ushort *)(param_1 + 0x2a);
    lVar3 = _mfi4Auth_util_parseMessage(param_1[1],&local_90,param_2,uVar6);
    if (lVar3 == 0) {
      iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
      if (iVar2 != 0) {
        local_a0 = (uint)DAT_1001b30b0;
        local_9c = (uint)uVar6;
        __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                      "mfi4Auth_protocol_messageHandler_receiveIncomingData: Found no message starting with: %x"
                      ,&local_a0,8);
      }
      lVar3 = _mfi4Auth_util_parseMessage(param_1[1],&local_90,param_2,0);
      if (lVar3 == 0) {
        iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
        if (iVar2 != 0) {
          _mfi4Auth_protocol_messageHandler_receiveIncomingData_cold_2();
        }
        goto LAB_1000fef10;
      }
      uVar6 = 0;
    }
    iVar2 = _mfi4Auth_util_packetLoggingEncryptedData();
    if ((iVar2 != 0) && (lVar4 = param_1[0x25], lVar4 != 0)) {
      (**(code **)(lVar4 + 0x10))(lVar4,*param_1,uVar6,lVar3,1,1,0,0,0,0);
    }
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
    if (iVar2 != 0) {
      local_a0 = local_a0 & 0xffff0000;
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                    "mfi4Auth_protocol_messageHandler_receiveIncomingData: Found message",&local_a0,
                    2);
    }
    uVar5 = _mfi4Auth_protocol_decryptIncomingData(param_1,uVar6,lVar3);
    if ((uVar5 & 1) != 0) {
      lVar4 = param_1[0x25];
      if (lVar4 != 0) {
        (**(code **)(lVar4 + 0x10))(lVar4,*param_1,uVar6,lVar3,1,0,0,0,0,0);
      }
      uVar5 = _mfi4Auth_protocol_processIncomingMessage(param_1,uVar6,lVar3,local_40);
      if ((((uVar5 & 1) == 0) &&
          (iVar2 = _mfi4Auth_protocol_processIncomingMessageExtra
                             (param_1,uVar6,lVar3,local_40,&local_41), iVar2 == 0)) ||
         (local_40[0] == (void *)0x0)) {
        uVar7 = _mfi4Auth_protocol_processIncomingMessageRelay
                          (param_1,uVar6,lVar3,local_40,&local_41);
      }
      else {
        uVar7 = 1;
      }
      goto LAB_1000fef14;
    }
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_protocol_messageHandler_receiveIncomingData_cold_1();
    }
  }
LAB_1000fef10:
  uVar7 = 0;
LAB_1000fef14:
  iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
  if (iVar2 != 0) {
    local_a0 = (uint)DAT_1001b30b0;
    local_9c = (uint)uVar7;
    __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                  "receiveIncomingData: processIncomingData returned:%d",&local_a0,8);
  }
  iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
  if (iVar2 != 0) {
    local_a0 = (uint)DAT_1001b30b0;
    local_9c = (uint)(local_40[0] != (void *)0x0);
    __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                  "receiveIncomingData: outMessage:(%d)",&local_a0,8);
  }
  iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
  if (iVar2 != 0) {
    local_a0 = (uint)DAT_1001b30b0;
    local_9c = (uint)local_41;
    __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,"receiveIncomingData: keepOpen:%d",
                  &local_a0,8);
  }
  uVar1 = 0;
  if (local_40[0] != (void *)0x0) {
    uVar1 = (uint)uVar7;
  }
  if (uVar1 == 1) {
    _mfi4Auth_protocol_messageHandler_sendOutgoingData(param_1);
    if (local_40[0] != (void *)0x0) {
      _free(local_40[0]);
      local_40[0] = (void *)0x0;
    }
  }
  else {
    _mfi4Auth_protocol_handleAuthSessionClose(param_1,local_41);
  }
  if (param_2 != 0) {
    _CFRelease(param_2);
  }
  return uVar7;
}


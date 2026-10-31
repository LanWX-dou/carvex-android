/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10003fcbc
 * original code SHA256: fe71c4a5ceb4cfbfebf75ffabd013c439481089aa40e1eef84d098a023823280
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _t56_protocol_processIncomingData(long param_1,byte *param_2,undefined8 param_3)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined *puVar10;
  uint *puVar11;
  uint uVar12;
  undefined8 uVar13;
  undefined4 local_c0;
  char *local_bc;
  undefined2 local_b4;
  undefined4 local_b2;
  undefined2 local_ae;
  uint local_ac;
  undefined2 local_a8;
  uint local_a6;
  undefined2 local_a2;
  uint local_a0;
  undefined2 local_9c;
  uint local_9a;
  undefined2 uStack_96;
  undefined2 uStack_94;
  undefined2 local_92;
  int local_90;
  undefined2 local_8c;
  uint local_8a;
  undefined2 local_86;
  uint local_84;
  undefined2 local_80;
  undefined8 local_7e;
  undefined2 local_76;
  uint local_74;
  ushort local_62;
  
  uVar12 = 0;
  local_62 = 0;
  uVar13 = 0xfffffffe;
  iVar7 = (int)param_3;
  if ((param_1 == 0) || (param_2 == (byte *)0x0)) {
    uVar8 = 0;
    goto LAB_100040084;
  }
  uVar8 = 0;
  if (iVar7 == 0) goto LAB_100040084;
  puVar11 = (uint *)(param_1 + 8);
  if (1 < *puVar11) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
      puVar10 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _logObjectForModule_cold_1();
        puVar10 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar10 = *(undefined **)(_gLogObjects + 0x1f8);
    }
    iVar3 = _os_log_type_enabled(puVar10,0x10);
    if (iVar3 != 0) {
      _t56_protocol_processIncomingData_cold_2(puVar11,param_3,puVar10);
    }
    uVar8 = 0;
LAB_10003feec:
    uVar12 = 0;
    uVar13 = 0xffffffff;
    goto LAB_100040084;
  }
  bVar1 = *param_2;
  uVar8 = (uint)bVar1;
  pbVar6 = *(byte **)(param_1 + 0x18);
  uVar2 = *(ushort *)(param_1 + 0x20);
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
    puVar10 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      _logObjectForModule_cold_1();
      puVar10 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar10 = *(undefined **)(_gLogObjects + 0x1f8);
  }
  iVar3 = _os_log_type_enabled(puVar10,1);
  uVar9 = (uint)bVar1;
  if (iVar3 != 0) {
    uVar12 = *puVar11;
    uVar13 = _t56_protocol_msgTypeString(uVar8);
    local_c0 = (undefined4)DAT_1001b3370;
    local_bc = "t56_protocol_processIncomingData";
    local_b4 = 0x400;
    local_b2 = 0xfb;
    local_ae = 0x400;
    local_a8 = 0x400;
    local_a6 = 0;
    local_a2 = 0x400;
    local_9c = 0x820;
    local_9a = (uint)uVar13;
    uStack_96 = (undefined2)((ulong)uVar13 >> 0x20);
    uStack_94 = (undefined2)((ulong)uVar13 >> 0x30);
    local_92 = 0x400;
    local_8c = 0x400;
    local_8a = (uint)(pbVar6 != (byte *)0x0);
    local_86 = 0x400;
    local_ac = uVar12;
    local_a0 = uVar9;
    local_90 = iVar7;
    local_84 = (uint)uVar2;
    __os_log_impl(0x100000000,puVar10,1,
                  "%s:%d role %d, ver %d, msgType %d(%s), dataInLen %d, _dataOut(%d), _dataOutSize %d"
                  ,&local_c0,0x40);
  }
  uVar12 = 0;
  uVar13 = 0xfffffffe;
  if ((pbVar6 == (byte *)0x0) || (uVar2 == 0)) goto LAB_100040084;
  iVar3 = _t56_protocol_checkValidMessageHeaderAndSize(param_1,*param_2,param_3);
  if (iVar3 != 0) {
    *(undefined1 *)(param_1 + 0x28) = 0;
    if (*(int *)(param_1 + 8) == 0) {
      if (-1 < *(int *)(param_1 + 0x2c)) {
        _t56_util_cancelTimer(param_1);
        *(undefined4 *)(param_1 + 0x2c) = 0xffffffff;
      }
      if (uVar9 == 5 || bVar1 < 5) {
        if (uVar9 == 2) {
          uVar13 = __t56_protocol_handleResponse_SESSION_RSP
                             (param_1,param_2,param_3,pbVar6,uVar2,&local_62);
        }
        else if (bVar1 == 4) {
          uVar13 = __t56_protocol_handleResponse_DISCOVER_RSP
                             (param_1,param_2,param_3,pbVar6,uVar2,&local_62);
        }
        else {
LAB_10003ff38:
          uVar13 = _logObjectForModule();
          iVar3 = _os_log_type_enabled(uVar13,0x10);
          if (iVar3 != 0) {
            _t56_protocol_processIncomingData_cold_4(uVar8,param_3,uVar13);
          }
          uVar13 = 0xffffffff;
        }
      }
      else if (uVar9 == 6) {
        uVar13 = __t56_protocol_handleResponse_DATA(param_1,param_2,param_3,pbVar6,uVar2,&local_62);
      }
      else {
        if (uVar9 != 8) goto LAB_10003ff38;
        uVar13 = __t56_protocol_handleResponse_STATUS
                           (param_1,param_2,param_3,pbVar6,uVar2,&local_62);
      }
    }
    iVar3 = _t56_protocol_checkValidMessageHeaderAndSize(param_1,*param_2,param_3);
    if ((iVar3 != 0) && (*puVar11 == 1)) {
      if (bVar1 < 5) {
        if (uVar9 != 1) {
          if (bVar1 != 3) {
LAB_100040294:
            uVar13 = _logObjectForModule();
            iVar3 = _os_log_type_enabled(uVar13,0x10);
            if (iVar3 != 0) {
              _t56_protocol_processIncomingData_cold_6(uVar8,param_3,uVar13);
            }
            goto LAB_10003feec;
          }
          __t56_protocol_handleRequest_DISCOVER(param_1,param_2,param_3);
          goto LAB_100040030;
        }
        uVar13 = __t56_protocol_handleRequest_SESSION
                           (param_1,param_2,param_3,pbVar6,uVar2,&local_62);
      }
      else {
        if (bVar1 == 5) {
          __t56_protocol_handleRequest_POLL(param_1,param_2,param_3);
LAB_100040030:
          uVar12 = 0;
          uVar13 = 0xfffffffe;
          goto LAB_100040084;
        }
        if (uVar9 == 6) {
          uVar13 = __t56_protocol_handleRequest_DATA(param_1,param_2,param_3,pbVar6,uVar2,&local_62)
          ;
        }
        else {
          if (uVar9 != 7) goto LAB_100040294;
          uVar13 = __t56_protocol_handleRequest_TERMINATE
                             (param_1,param_2,param_3,pbVar6,uVar2,&local_62);
        }
      }
    }
    uVar2 = local_62;
    if ((int)uVar13 == 0) {
      *(ushort *)(param_1 + 0x22) = local_62;
      if (local_62 == 0) {
        uVar12 = 0;
      }
      else {
        bVar1 = *pbVar6;
        uVar12 = (uint)bVar1;
        if (*puVar11 == 0) {
          uVar13 = _t56_protocol_timeoutForRequest(param_1,uVar12);
          uVar5 = _logObjectForModule();
          iVar3 = _os_log_type_enabled(uVar5,0);
          if (iVar3 != 0) {
            local_c0 = (undefined4)DAT_1001b30e0;
            local_bc = "t56_protocol_processIncomingData";
            local_b4 = 0x400;
            local_b2 = 0x15a;
            local_ae = 0x400;
            local_ac = (uint)uVar13;
            local_a8 = 0x400;
            local_a6 = (uint)bVar1;
            __os_log_impl(0x100000000,uVar5,0,"%s:%d Start responseTimer, %u ms, outMsgType %u",
                          &local_c0,0x1e);
          }
          uVar4 = _t56_util_callbackOnTimer(param_1,uVar13,__T56Protocol_timeoutCallback,0);
          *(undefined4 *)(param_1 + 0x2c) = uVar4;
        }
        uVar13 = _logObjectForModule();
        iVar3 = _os_log_type_enabled(uVar13,2);
        if (iVar3 != 0) {
          _t56_protocol_processIncomingData_cold_5(uVar12,uVar13);
        }
        _t56_protocol_sendData(param_1,pbVar6,uVar2);
      }
      uVar13 = 0;
      goto LAB_100040084;
    }
  }
  uVar12 = 0;
LAB_100040084:
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
    puVar10 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      _t56_protocol_cleanup_cold_2();
      puVar10 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar10 = *(undefined **)(_gLogObjects + 0x1f8);
  }
  iVar3 = _os_log_type_enabled(puVar10,0);
  if (iVar3 != 0) {
    uVar4 = *(undefined4 *)(param_1 + 8);
    uVar5 = _t56_protocol_msgTypeString(uVar8);
    local_7e = _t56_protocol_msgTypeString(uVar12);
    local_c0 = (undefined4)DAT_1001b3458;
    local_bc = "t56_protocol_processIncomingData";
    local_b4 = 0x400;
    local_b2 = 0x166;
    local_ae = 0x400;
    local_ac = (uint)uVar13;
    local_a8 = 0x400;
    local_a2 = 0x400;
    local_a0 = 0;
    local_9c = 0x400;
    uStack_96 = 0x820;
    uStack_94 = (undefined2)uVar5;
    local_92 = (undefined2)((ulong)uVar5 >> 0x10);
    local_90 = (int)((ulong)uVar5 >> 0x20);
    local_8c = 0x400;
    local_86 = 0x400;
    local_80 = 0x820;
    local_76 = 0x400;
    local_74 = (uint)local_62;
    local_a6 = uVar4;
    local_9a = uVar8;
    local_8a = iVar7;
    local_84 = uVar12;
    __os_log_impl(0x100000000,puVar10,0,
                  "%s:%d result %d, role %d, ver %d, msgType %d(%s), dataInLen %d, outMsgType %d(%s), dataOutLen %d"
                  ,&local_c0,0x50);
  }
  return uVar13;
}


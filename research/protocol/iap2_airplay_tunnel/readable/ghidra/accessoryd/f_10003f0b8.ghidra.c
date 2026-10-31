/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10003f0b8
 * original code SHA256: 6d11a35893110d7c858d09d11efb138f5cf62634dd7016d1bb869631060d89e7
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _t56_protocol_start(long param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined *puVar6;
  undefined4 local_70;
  char *local_6c;
  undefined2 local_64;
  undefined4 local_62;
  undefined2 local_5e;
  undefined4 local_5c;
  undefined2 local_58;
  uint local_56;
  undefined2 local_52;
  undefined8 local_50;
  
  if (((param_1 == 0) || (*(long *)(param_1 + 0x18) == 0)) || (*(short *)(param_1 + 0x20) == 0)) {
    iVar3 = -2;
  }
  else {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _logObjectForModule_cold_1();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0x1f8);
    }
    uVar4 = _os_log_type_enabled(puVar6,0);
    if ((int)uVar4 != 0) {
      local_5c = *(undefined4 *)(param_1 + 8);
      local_70 = (undefined4)DAT_1001b30e0;
      local_6c = "t56_protocol_start";
      local_64 = 0x400;
      local_62 = 0xaf;
      local_5e = 0x400;
      local_58 = 0x400;
      local_56 = (uint)*(ushort *)(param_1 + 0x20);
      uVar4 = __os_log_impl(0x100000000,puVar6,0,"%s:%d role %d, outMsgBufferSize %d",&local_70,0x1e
                           );
    }
    if (((*(int *)(param_1 + 8) == 0) && (*(long *)(param_1 + 0x18) != 0)) &&
       (6 < *(ushort *)(param_1 + 0x20))) {
      iVar2 = _t56_protocol_initMsg_SESSION
                        (uVar4,0,1,0,*(long *)(param_1 + 0x18),*(ushort *)(param_1 + 0x20),
                         param_1 + 0x22);
      if (iVar2 == 0) {
        uVar4 = _t56_protocol_timeoutForRequest(param_1,**(undefined1 **)(param_1 + 0x18));
        if (-1 < *(int *)(param_1 + 0x2c)) {
          uVar5 = _logObjectForModule();
          iVar3 = _os_log_type_enabled(uVar5,0);
          if (iVar3 != 0) {
            uVar1 = *(uint *)(param_1 + 0x24);
            local_50 = _t56_protocol_msgTypeString(uVar1);
            local_70 = (undefined4)DAT_1001b3110;
            local_6c = "t56_protocol_start";
            local_64 = 0x400;
            local_62 = 0xc2;
            local_5e = 0x400;
            local_58 = 0x400;
            local_52 = 0x820;
            local_5c = (int)uVar4;
            local_56 = uVar1;
            __os_log_impl(0x100000000,uVar5,0,"%s:%d Cancel responseTimer, %u ms, outMsgType %u(%s)"
                          ,&local_70,0x28);
          }
          _t56_util_cancelTimer(param_1,*(undefined4 *)(param_1 + 0x2c));
        }
        uVar5 = _logObjectForModule();
        iVar3 = _os_log_type_enabled(uVar5,0);
        if (iVar3 != 0) {
          local_70 = (undefined4)DAT_1001b30e0;
          local_6c = "t56_protocol_start";
          local_64 = 0x400;
          local_62 = 0xc6;
          local_5e = 0x400;
          local_58 = 0x400;
          local_56 = (uint)**(byte **)(param_1 + 0x18);
          local_5c = (int)uVar4;
          __os_log_impl(0x100000000,uVar5,0,"%s:%d Start responseTimer, %u ms, outMsgType %u",
                        &local_70,0x1e);
        }
        iVar3 = _t56_util_callbackOnTimer(param_1,uVar4,__T56Protocol_timeoutCallback,0);
        if (iVar3 < 0) {
          uVar4 = _logObjectForModule();
          iVar2 = _os_log_type_enabled(uVar4,0);
          iVar3 = 0;
          if (iVar2 != 0) {
            local_70 = (undefined4)DAT_1001b3098;
            local_6c = "t56_protocol_start";
            local_64 = 0x400;
            local_62 = 0xc9;
            __os_log_impl(0x100000000,uVar4,0,"%s:%d Failed to start timer!!!",&local_70,0x12);
            iVar3 = 0;
          }
          goto LAB_10003f1c4;
        }
        *(int *)(param_1 + 0x2c) = iVar3;
        _t56_protocol_sendData
                  (param_1,*(undefined8 *)(param_1 + 0x18),*(undefined2 *)(param_1 + 0x22));
        iVar2 = 0;
      }
    }
    else {
      iVar2 = -2;
    }
    iVar3 = 0;
    if (*(uint *)(param_1 + 8) != 1) {
      iVar3 = iVar2;
    }
    if (1 < *(uint *)(param_1 + 8)) {
      iVar3 = -1;
    }
  }
LAB_10003f1c4:
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
    puVar6 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      _t56_protocol_cleanup_cold_2();
      puVar6 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar6 = *(undefined **)(_gLogObjects + 0x1f8);
  }
  iVar2 = _os_log_type_enabled(puVar6,2);
  if (iVar2 != 0) {
    _t56_protocol_start_cold_3(param_1,iVar3,puVar6);
  }
  return iVar3;
}


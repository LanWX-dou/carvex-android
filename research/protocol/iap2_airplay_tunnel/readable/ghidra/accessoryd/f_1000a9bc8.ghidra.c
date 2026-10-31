/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000a9bc8
 * original code SHA256: 65cf20fd843c61f2e0c24809a8cb298f19947d5f7fab6bad0170ae0595b5c360
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong ____mfi4Auth_endpoint_initSession_block_invoke_7
                (long param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  ulong uVar4;
  long lVar5;
  undefined *puVar6;
  long *plVar7;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined2 uStack_74;
  undefined2 uStack_72;
  undefined2 uStack_70;
  undefined6 uStack_6e;
  undefined *puStack_68;
  undefined8 local_60;
  undefined8 uStack_58;
  
  plVar7 = *(long **)(param_1 + 0x20);
  if (plVar7 == (long *)0x0) {
    ____mfi4Auth_endpoint_initSession_block_invoke_7_cold_9(&local_80);
  }
  else if ((uint)param_3 < 3) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
      puVar6 = PTR___os_log_default_10022bbb0;
      if (DAT_10023eb40 != -1) {
        _logObjectForModule_cold_1();
        puVar6 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar6 = *(undefined **)(_gLogObjects + 0x1d0);
    }
    iVar1 = _os_log_type_enabled(puVar6,0);
    if (iVar1 != 0) {
      local_80 = (undefined4)DAT_1001b3098;
      uStack_7c = 0x1d38c4;
      uStack_78 = 1;
      uStack_74 = 0x400;
      uStack_72 = (undefined2)param_3;
      uStack_70 = (undefined2)((ulong)param_3 >> 0x10);
      __os_log_impl(0x100000000,puVar6,0,"%s: secureTunnelType %d",&local_80,0x12);
    }
    if ((uint)param_3 != 2) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
        puVar6 = PTR___os_log_default_10022bbb0;
        if (DAT_10023eb40 != -1) {
          __mfi4Auth_endpoint_initSession_cold_2();
          puVar6 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar6 = *(undefined **)(_gLogObjects + 0x1d0);
      }
      uVar4 = _os_log_type_enabled(puVar6,0x10);
      if ((int)uVar4 != 0) {
        ____mfi4Auth_endpoint_initSession_block_invoke_7_cold_3(param_3,puVar6);
        return 0;
      }
      return uVar4;
    }
    lVar5 = *plVar7;
    if (lVar5 == 0) {
      ____mfi4Auth_endpoint_initSession_block_invoke_7_cold_7(&local_80);
    }
    else {
      plVar7 = (long *)_acc_endpoint2_getParentConnection(lVar5);
      if (plVar7 != (long *)0x0) {
        if (*plVar7 == 0) {
          local_60 = 0;
        }
        else {
          local_60 = _CFStringCreateCopy(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0);
        }
        uVar2 = _acc_connection2_createEndpoint_internal
                          (plVar7,0xf,0x11,*(undefined8 *)(lVar5 + 0x10));
        lVar3 = _acc_connection2_getEndpointStruct_internal(plVar7,uVar2);
        if (lVar3 == 0) {
          return 0;
        }
        if (*(long *)(lVar3 + 0x10) == 0) {
          return 0;
        }
        local_80 = SUB84(PTR___NSConcreteStackBlock_10022bb78,0);
        uStack_7c = (undefined4)((ulong)PTR___NSConcreteStackBlock_10022bb78 >> 0x20);
        uStack_78 = (undefined4)DAT_1001b3118;
        uStack_74 = (undefined2)((ulong)DAT_1001b3118 >> 0x20);
        uStack_72 = (undefined2)((ulong)DAT_1001b3118 >> 0x30);
        uStack_70 = 0xb3ac;
        uStack_6e = 0x1000a;
        puStack_68 = &___block_descriptor_tmp_57;
        uStack_58 = uVar2;
        _acc_endpoint2_setEndpointSecureTunnelDataReceiveTypeHandler(&uStack_70,lVar5,2,&local_80);
        _acc_endpoint2_setParentEndpointUUID(lVar3,*(undefined8 *)(lVar5 + 0x10));
        uVar4 = _acc_endpoint2_publish(lVar3);
        if ((uVar4 & 1) == 0) {
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
            puVar6 = PTR___os_log_default_10022bbb0;
            if (DAT_10023eb40 != -1) {
              __mfi4Auth_endpoint_initSession_cold_2();
              puVar6 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar6 = *(undefined **)(_gLogObjects + 0x1d0);
          }
          uVar4 = _os_log_type_enabled(puVar6,0x10);
          if ((int)uVar4 != 0) {
            ____mfi4Auth_endpoint_initSession_block_invoke_7_cold_5((long *)(lVar3 + 0x10),puVar6);
            return 0;
          }
          return uVar4;
        }
        return 1;
      }
      ____mfi4Auth_endpoint_initSession_block_invoke_7_cold_6(lVar5,&local_80);
    }
  }
  else {
    ____mfi4Auth_endpoint_initSession_block_invoke_7_cold_8(param_3,&local_80);
  }
  return (ulong)(byte)local_80;
}


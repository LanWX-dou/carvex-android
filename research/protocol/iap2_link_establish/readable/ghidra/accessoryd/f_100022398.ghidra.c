/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100022398
 * original code SHA256: 66e6429ef04370767d8df7b602515577687284bd41f2ab9fab45bfebff2071de
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long _mfi4Auth_util_unpackFromTunnelDataiAP2Msg
               (undefined8 param_1,undefined1 *param_2,undefined2 *param_3)

{
  undefined *puVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  void *pvVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  long lVar11;
  undefined8 uVar12;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined2 local_c8;
  undefined4 local_c6;
  undefined2 local_c2;
  undefined8 local_c0;
  undefined4 local_b4;
  undefined1 *local_b0;
  undefined1 *puStack_a8;
  undefined1 *puStack_a0;
  undefined1 *puStack_98;
  undefined1 *local_90;
  undefined1 *puStack_88;
  undefined1 *puStack_80;
  undefined1 *puStack_78;
  undefined1 *local_70;
  
  local_70 = &DAT_aaaaaaaaaaaaaaaa;
  puStack_88 = &DAT_aaaaaaaaaaaaaaaa;
  local_90 = &DAT_aaaaaaaaaaaaaaaa;
  puStack_78 = &DAT_aaaaaaaaaaaaaaaa;
  puStack_80 = &DAT_aaaaaaaaaaaaaaaa;
  puStack_a8 = &DAT_aaaaaaaaaaaaaaaa;
  local_b0 = &DAT_aaaaaaaaaaaaaaaa;
  puStack_98 = &DAT_aaaaaaaaaaaaaaaa;
  puStack_a0 = &DAT_aaaaaaaaaaaaaaaa;
  pvVar6 = (void *)_malloc_type_calloc(1,0x1001f,0x1090040daa7631a);
  lVar7 = _mfi4Auth_util_parseMessage(pvVar6,&local_b0,param_1,0x4040);
  iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,2);
  if (iVar3 != 0) {
    _mfi4Auth_util_unpackFromTunnelDataiAP2Msg_cold_1(lVar7);
  }
  if (param_3 != (undefined2 *)0x0) {
    uVar2 = _iAP2MsgGetMsgID(lVar7);
    *param_3 = uVar2;
  }
  iVar3 = _iAP2MsgGetMsgID(lVar7);
  if (iVar3 == 0x5503) {
    uVar10 = *(undefined8 *)(lVar7 + 0x18);
    uVar12 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
    uVar4 = _iAP2MsgGetMsgLen(lVar7);
    lVar11 = _CFDataCreate(uVar12,uVar10,uVar4);
    iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
    if (iVar3 != 0) {
      uVar4 = _iAP2MsgGetMsgID(lVar7);
      local_c0 = _CFDataGetLength(lVar11);
      local_d0 = (undefined4)DAT_1001b3100;
      local_c8 = 0x400;
      local_c6 = 0;
      local_c2 = 0x800;
      local_cc = uVar4;
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                    "mfi4Auth_util_unpackFromTunnelDataiAP2Msg: message 0x%04X, type %d, unpackedMessage %ld bytes"
                    ,&local_d0,0x18);
    }
  }
  else if (iVar3 == 0x5501) {
    lVar8 = _iAP2MsgGetFirstParam(lVar7,0);
    puVar1 = PTR___os_log_default_10022bbb0;
    uVar10 = DAT_1001b3100;
    if (lVar8 == 0) {
      uVar4 = 0;
      lVar11 = 0;
    }
    else {
      lVar11 = 0;
      uVar4 = 0;
      uVar12 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
      do {
        iVar3 = _iAP2MsgGetParamID(lVar8);
        if (iVar3 == 1) {
          local_b4 = 0;
          uVar9 = _iAP2MsgGetDataAsData(lVar8,&local_b4);
          if (lVar11 != 0) {
            iVar3 = _os_log_type_enabled(puVar1,0x10);
            if (iVar3 != 0) {
              uVar5 = _iAP2MsgGetMsgID(lVar7);
              local_c0 = _CFDataGetLength(lVar11);
              local_d0 = (undefined4)uVar10;
              local_c8 = 0x400;
              local_c2 = 0x800;
              local_cc = uVar5;
              local_c6 = uVar4;
              __os_log_error_impl(0x100000000,puVar1,0x10,
                                  "mfi4Auth_util_unpackFromTunnelDataiAP2Msg: message 0x%04X, type %d, Already have unpackedMessage %ld bytes !!!, release and create new one"
                                  ,&local_d0,0x18);
            }
            _CFRelease(lVar11);
          }
          uVar5 = _iAP2MsgGetParamValueLen(lVar8);
          lVar11 = _CFDataCreate(uVar12,uVar9,uVar5);
        }
        else if (iVar3 == 0) {
          local_d0 = 0;
          uVar4 = _iAP2MsgGetDataAsU8(lVar8,&local_d0);
        }
        lVar8 = _iAP2MsgGetNextParam(lVar7,0,lVar8);
      } while (lVar8 != 0);
    }
    iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
    if (iVar3 != 0) {
      uVar5 = _iAP2MsgGetMsgID(lVar7);
      local_c0 = _CFDataGetLength(lVar11);
      local_d0 = (undefined4)DAT_1001b3100;
      local_c8 = 0x400;
      local_c2 = 0x800;
      local_cc = uVar5;
      local_c6 = uVar4;
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                    "mfi4Auth_util_unpackFromTunnelDataiAP2Msg: message 0x%04X, type %d, unpackedMessage %ld bytes"
                    ,&local_d0,0x18);
    }
    if (param_2 != (undefined1 *)0x0) {
      *param_2 = (char)uVar4;
    }
  }
  else {
    iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
    if (iVar3 != 0) {
      local_cc = _iAP2MsgGetMsgID(lVar7);
      local_d0 = (undefined4)DAT_1001b30b0;
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                    "mfi4Auth_util_unpackFromTunnelDataiAP2Msg: Unrecognized message 0x%04X !!!",
                    &local_d0,8);
    }
    lVar11 = 0;
  }
  if (pvVar6 != (void *)0x0) {
    _free(pvVar6);
  }
  return lVar11;
}


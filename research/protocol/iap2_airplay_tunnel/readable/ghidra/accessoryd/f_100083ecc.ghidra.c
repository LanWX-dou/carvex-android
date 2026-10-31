/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100083ecc
 * original code SHA256: 2356869f941ba8d517926a0210759ce93b0c6bcce7a6cb7d8e822cf1800ab42f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _mfi4Auth_protocol_processIncomingMessageRelay
               (long param_1,int param_2,long param_3,undefined8 param_4,undefined1 *param_5)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  bool bVar7;
  uint local_70;
  uint local_6c;
  undefined2 uStack_68;
  undefined2 uStack_66;
  undefined2 uStack_64;
  undefined4 local_62;
  undefined2 uStack_5e;
  undefined2 uStack_5c;
  undefined6 uStack_5a;
  
  if (param_1 == 0) {
    iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar3 != 0) {
      _mfi4Auth_protocol_processIncomingMessageRelay_cold_6();
    }
    goto LAB_100084338;
  }
  if (param_3 == 0) {
    iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar3 != 0) {
      _mfi4Auth_protocol_processIncomingMessageRelay_cold_5();
    }
LAB_100084018:
    bVar1 = false;
    bVar7 = false;
LAB_100084090:
    iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0);
    if (iVar3 != 0) {
      local_6c = *(uint *)(param_1 + 0x58);
      local_70 = (uint)DAT_1001b30b0;
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,0,
                    "processIncomingMessageRelay: action %d",&local_70,8);
    }
    uVar5 = *(ulong *)(param_1 + 0x80);
    iVar3 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ForceAccInfoUpdateRelaySupport);
    if (iVar3 != 0) {
      iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
      if (iVar3 != 0) {
        local_70 = (uint)DAT_1001b30b8;
        local_6c = (uint)uVar5;
        uStack_68 = (undefined2)(uVar5 >> 0x20);
        uStack_66 = (undefined2)(uVar5 >> 0x30);
        uStack_64 = 0x400;
        local_62 = 1;
        __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                      "processIncomingMessageRelay: override supportedSecureTunnelCapabilitiesMask 0x%llx |= 0x%x"
                      ,&local_70,0x12);
      }
      uVar5 = uVar5 | 1;
    }
    iVar3 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_IgnoreAccInfoUpdateRelaySupport);
    if (iVar3 != 0) {
      iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
      if (iVar3 != 0) {
        local_70 = (uint)DAT_1001b30b8;
        local_6c = (uint)uVar5;
        uStack_68 = (undefined2)(uVar5 >> 0x20);
        uStack_66 = (undefined2)(uVar5 >> 0x30);
        uStack_64 = 0x400;
        local_62 = 0xfffffffe;
        __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                      "processIncomingMessageRelay: override supportedSecureTunnelCapabilitiesMask 0x%llx &= 0x%x"
                      ,&local_70,0x12);
      }
      uVar5 = uVar5 & 0xfffffffffffffffe;
    }
    iVar3 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_ForceT56RelaySupport);
    if (iVar3 != 0) {
      iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
      if (iVar3 != 0) {
        local_70 = (uint)DAT_1001b30b8;
        local_6c = (uint)uVar5;
        uStack_68 = (undefined2)(uVar5 >> 0x20);
        uStack_66 = (undefined2)(uVar5 >> 0x30);
        uStack_64 = 0x400;
        local_62 = 4;
        __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                      "processIncomingMessageRelay: override supportedSecureTunnelCapabilitiesMask 0x%llx |= 0x%x"
                      ,&local_70,0x12);
      }
      uVar5 = uVar5 | 4;
    }
    iVar3 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_DisableT56Support);
    if (iVar3 != 0) {
      iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
      if (iVar3 != 0) {
        local_70 = (uint)DAT_1001b30b8;
        local_6c = (uint)uVar5;
        uStack_68 = (undefined2)(uVar5 >> 0x20);
        uStack_66 = (undefined2)(uVar5 >> 0x30);
        uStack_64 = 0x400;
        local_62 = 0xfffffffb;
        __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                      "processIncomingMessageRelay: override supportedSecureTunnelCapabilitiesMask 0x%llx &= 0x%x"
                      ,&local_70,0x12);
      }
      uVar5 = uVar5 & 0xfffffffffffffffb;
    }
    iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
    if (iVar3 != 0) {
      uVar4 = *(undefined8 *)(param_1 + 0x88);
      local_70 = (uint)DAT_1001b30b8;
      uStack_68 = (undefined2)(uVar5 >> 0x20);
      uStack_66 = (undefined2)(uVar5 >> 0x30);
      uStack_64 = 0x800;
      local_62 = (undefined4)uVar4;
      uStack_5e = (undefined2)((ulong)uVar4 >> 0x20);
      uStack_5c = (undefined2)((ulong)uVar4 >> 0x30);
      local_6c = (uint)uVar5;
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                    "processIncomingMessageRelay: supportedSecureTunnelCapabilitiesMask 0x%llx, processed 0x%llx"
                    ,&local_70,0x16);
    }
    if (((*(int *)(param_1 + 0x58) == 0) && (uVar5 != 0)) &&
       (uVar6 = *(ulong *)(param_1 + 0x88), uVar5 != uVar6)) {
      if (((uVar5 & 1) == 0) || ((uVar6 & 1) != 0)) {
        uVar6 = uVar5 & 0xfffffffffffffffc;
        if (uVar6 != 0) {
          iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
          if (iVar3 != 0) {
            local_70 = (uint)DAT_1001b3c10;
            local_6c = (uint)uVar6;
            uStack_68 = (undefined2)(uVar6 >> 0x20);
            uStack_66 = (undefined2)(uVar6 >> 0x30);
            uStack_64 = 0x400;
            local_62 = 2;
            uStack_5e = 0x800;
            uStack_5c = 4;
            uStack_5a = 0;
            __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                          "processIncomingMessageRelay: supportedSecureTunnelCapabilitiesMask 0x%llx, currentType/Mask %d/0x%llx"
                          ,&local_70,0x1c);
          }
          if ((((uint)uVar5 >> 2 & 1) != 0) && (((uint)*(ulong *)(param_1 + 0x88) >> 2 & 1) == 0)) {
            *(ulong *)(param_1 + 0x88) = *(ulong *)(param_1 + 0x88) | 4;
            _mfi4Auth_relay_StartRelayForType(param_1,2,param_5);
          }
        }
      }
      else {
        *(ulong *)(param_1 + 0x88) = uVar6 | 1;
        iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
        if (iVar3 != 0) {
          local_70 = local_70 & 0xffff0000;
          __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                        "processIncomingMessageRelay: initMessage RequestAccessoryInfoUpdate",
                        &local_70,2);
        }
        *(undefined4 *)(param_1 + 0x58) = 0xf;
        _mfi4Auth_relay_initMessage_DeviceiAP2RelayRemote_RequestAccessoryInfoUpdate
                  (param_1,param_4);
      }
    }
    else if (!bVar7) goto LAB_100084338;
    uVar2 = 1;
    if (!bVar1) {
      return;
    }
  }
  else {
    uVar4 = _iAP2MsgGetMsgID(param_3);
    iVar3 = (int)uVar4;
    if (iVar3 == 0) {
      iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
      if (iVar3 != 0) {
        _mfi4Auth_protocol_processIncomingMessageRelay_cold_4();
      }
      goto LAB_100084018;
    }
    uVar5 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
    if ((uVar5 & 1) != 0) {
      local_70 = (uint)DAT_1001b3108;
      local_6c = (uint)*(ushort *)(param_1 + 0x1c);
      uStack_68 = 0x400;
      uStack_66 = (undefined2)uVar4;
      uStack_64 = (undefined2)((ulong)uVar4 >> 0x10);
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                    "processIncomingMessageRelay: cmd:0x%x  rsp:0x%x",&local_70,0xe);
    }
    if (iVar3 != 0x5266) {
      if (iVar3 == 0x5265) {
        if (param_2 != 0) {
          _mfi4Auth_relay_handle_iAP2RelayFailed(param_1,param_3);
          goto LAB_100084080;
        }
        goto LAB_100084338;
      }
      if (iVar3 == 0x5264) {
        if (param_2 != 0) {
          iVar3 = _mfi4Auth_relay_handle_iAP2RelayRemote(param_1,param_3,param_4);
          if (iVar3 == 0) goto LAB_100084088;
          iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
          if (iVar3 != 0) {
            _mfi4Auth_protocol_processIncomingMessageRelay_cold_2();
          }
        }
        goto LAB_100084338;
      }
      iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
      if (iVar3 != 0) {
        _mfi4Auth_protocol_processIncomingMessageRelay_cold_3(uVar4);
      }
LAB_100084080:
      bVar1 = false;
LAB_10008408c:
      bVar7 = true;
      goto LAB_100084090;
    }
    if (param_2 != 0) {
      iVar3 = _mfi4Auth_relay_handle_iAP2RelaySucceeded(param_1,param_3,param_4);
      if (iVar3 == 0) {
LAB_100084088:
        bVar1 = true;
        goto LAB_10008408c;
      }
      iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
      if (iVar3 != 0) {
        _mfi4Auth_protocol_processIncomingMessageRelay_cold_1();
      }
    }
LAB_100084338:
    iVar3 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar3 != 0) {
      _mfi4Auth_protocol_processIncomingMessageRelay_cold_7();
    }
    uVar2 = 0;
    if (param_5 == (undefined1 *)0x0) {
      return;
    }
  }
  *param_5 = uVar2;
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008449c
 * original code SHA256: 602320efc4b71e87e7c0174583fa92218b7c4aeb0213ae8ad1dd15e7c65d992c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined4
_mfi4Auth_relay_handle_iAP2RelayRemote(undefined8 *param_1,long param_2,undefined8 param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  long lVar4;
  undefined8 uVar5;
  ulong uVar6;
  ID IVar7;
  void *pvVar8;
  long lVar9;
  undefined4 local_80;
  uint uStack_7c;
  undefined2 uStack_78;
  undefined2 uStack_76;
  undefined2 uStack_74;
  undefined2 uStack_72;
  undefined2 uStack_70;
  undefined6 uStack_6e;
  undefined1 *puStack_68;
  undefined1 *local_60;
  undefined1 *puStack_58;
  undefined1 *puStack_50;
  undefined1 *puStack_48;
  undefined1 *local_40;
  ushort local_38;
  byte local_35;
  undefined4 local_34;
  
  local_34 = 1;
  local_35 = 0;
  local_38 = 0;
  if (param_1 == (undefined8 *)0x0) {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_relay_handle_iAP2RelayRemote_cold_11();
    }
  }
  else if (*(char *)((long)param_1 + 0x1e) == '\x01') {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_relay_handle_iAP2RelayRemote_cold_10();
    }
  }
  else if (param_2 == 0) {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_relay_handle_iAP2RelayRemote_cold_9();
    }
  }
  else {
    iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
    if (iVar1 != 0) {
      uVar2 = _iAP2MsgGetMsgID(param_2);
      uVar3 = _iAP2MsgGetMsgLen(param_2);
      local_80 = (undefined4)DAT_1001b3108;
      uStack_78 = 0x400;
      uStack_76 = (undefined2)uVar3;
      uStack_74 = (undefined2)((uint)uVar3 >> 0x10);
      uStack_7c = uVar2;
      __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                    "mfi4Auth_protocol_handle_iAP2RelayRemote: msgID 0x%04x, len %d",&local_80,0xe);
    }
    lVar4 = _iAP2MsgGetFirstParam(param_2,0);
    if (lVar4 == 0) {
      uVar5 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_MFi4RelayReadRetryDelayMs);
      if ((int)uVar5 != 0) {
        iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
        if (iVar1 != 0) {
          _mfi4Auth_relay_handle_iAP2RelayRemote_cold_8(uVar5);
        }
        _usleep(1000);
        uVar3 = _mfi4Auth_relay_initMessage_RequestiAP2RelayRead(param_1,param_3);
        return uVar3;
      }
    }
    else {
      uVar5 = _iAP2MsgGetDataAsData(lVar4,&local_34);
      uVar6 = _iAP2MsgGetParamValueLen(lVar4);
      IVar7 = NSData::dataWithBytes_length_
                        ((ID)PTR__OBJC_CLASS___NSData_10022bc38,uVar5,uVar6 & 0xffffffff);
      iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
      if (iVar1 != 0) {
        uStack_7c = _iAP2MsgGetParamID(lVar4);
        local_80 = (undefined4)DAT_1001b3108;
        uStack_78 = 0x400;
        uStack_76 = (undefined2)uVar6;
        uStack_74 = (undefined2)(uVar6 >> 0x10);
        __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                      "mfi4Auth_protocol_handle_iAP2RelayRemote: paramID %d, dataLen %d",&local_80,
                      0xe);
      }
      iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
      if (iVar1 != 0) {
        local_80 = (undefined4)DAT_1001b3088;
        uStack_7c = (uint)IVar7;
        uStack_78 = (undefined2)(IVar7 >> 0x20);
        uStack_76 = (undefined2)(IVar7 >> 0x30);
        __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                      "mfi4Auth_protocol_handle_iAP2RelayRemote: %@",&local_80,0xc);
      }
      lVar4 = _mfi4Auth_util_unpackFromTunnelDataiAP2Msg(IVar7,&local_35,&local_38);
      if (lVar4 == 0) {
        iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
        if (iVar1 != 0) {
          _mfi4Auth_relay_handle_iAP2RelayRemote_cold_7();
        }
      }
      else {
        uVar6 = _CFDataGetLength();
        if (uVar6 < 6) {
          iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
          if (iVar1 != 0) {
            _mfi4Auth_relay_handle_iAP2RelayRemote_cold_1(uVar6);
          }
        }
        else {
          iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
          if (iVar1 != 0) {
            local_80 = (undefined4)DAT_1001b3108;
            uStack_7c = (uint)local_38;
            uStack_78 = 0x800;
            uStack_76 = (undefined2)uVar6;
            uStack_74 = (undefined2)(uVar6 >> 0x10);
            uStack_72 = (undefined2)(uVar6 >> 0x20);
            uStack_70 = (undefined2)(uVar6 >> 0x30);
            __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                          "mfi4Auth_relay_handle_iAP2RelayRemote: msgID 0x%04x, len %zu",&local_80,
                          0x12);
          }
          if (local_38 == 0x5503) {
            local_40 = &DAT_aaaaaaaaaaaaaaaa;
            puStack_58 = &DAT_aaaaaaaaaaaaaaaa;
            local_60 = &DAT_aaaaaaaaaaaaaaaa;
            puStack_48 = &DAT_aaaaaaaaaaaaaaaa;
            puStack_50 = &DAT_aaaaaaaaaaaaaaaa;
            uStack_78 = 0xaaaa;
            uStack_76 = 0xaaaa;
            uStack_74 = 0xaaaa;
            uStack_72 = 0xaaaa;
            local_80 = 0xaaaaaaaa;
            uStack_7c = 0xaaaaaaaa;
            puStack_68 = &DAT_aaaaaaaaaaaaaaaa;
            uStack_70 = 0xaaaa;
            uStack_6e = 0xaaaaaaaaaaaa;
            pvVar8 = (void *)_malloc_type_calloc(1,0x1001f,0x1090040daa7631a);
            if (pvVar8 == (void *)0x0) {
              iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_relay_handle_iAP2RelayRemote_cold_3();
              }
            }
            else {
              lVar9 = _mfi4Auth_util_parseMessage(pvVar8,&local_80,lVar4,0x4040);
              if (lVar9 != 0) {
                local_34 = __mfi4Auth_relay_handle_AccessoryInformationUpdate(param_1,lVar9);
                _free(pvVar8);
LAB_1000848bc:
                _CFRelease(lVar4);
                return local_34;
              }
              iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_relay_handle_iAP2RelayRemote_cold_2();
              }
              _free(pvVar8);
            }
          }
          else if (local_38 == 0x5501) {
            if ((ulong)local_35 < 3) {
              if (param_1[(ulong)local_35 + 0x1d] != 0) {
                iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,1);
                if (iVar1 != 0) {
                  local_80 = (undefined4)DAT_1001b3138;
                  uStack_7c = (uint)local_35;
                  uStack_78 = 0x840;
                  uStack_76 = (undefined2)lVar4;
                  uStack_74 = (undefined2)((ulong)lVar4 >> 0x10);
                  uStack_72 = (undefined2)((ulong)lVar4 >> 0x20);
                  uStack_70 = (undefined2)((ulong)lVar4 >> 0x30);
                  __os_log_impl(0x100000000,PTR___os_log_default_10022bbb0,1,
                                "mfi4Auth_relay_handle_iAP2RelayRemote: type %d, data %@",&local_80,
                                0x12);
                }
                (**(code **)(param_1[(ulong)local_35 + 0x1d] + 0x10))
                          (param_1[(ulong)local_35 + 0x1d],*param_1,lVar4);
                local_34 = 0;
                goto LAB_1000848bc;
              }
              iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_relay_handle_iAP2RelayRemote_cold_5(&local_35);
              }
            }
            else {
              iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_relay_handle_iAP2RelayRemote_cold_4();
              }
            }
          }
          else {
            iVar1 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
            if (iVar1 != 0) {
              _mfi4Auth_relay_handle_iAP2RelayRemote_cold_6(&local_38);
            }
          }
        }
        _CFRelease(lVar4);
      }
    }
  }
  return 0xffffffff;
}


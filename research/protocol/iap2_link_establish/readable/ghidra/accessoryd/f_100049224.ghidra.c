/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100049224
 * original code SHA256: 4577cacf5fdf907d3fa57369e7118ebc1f0bc321366492433350112a81b73121
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x24 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */

undefined1
_mfi4Auth_protocol_processIncomingMessage(long param_1,int param_2,long param_3,undefined8 param_4)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  undefined8 uVar4;
  undefined *puVar5;
  uint local_60;
  uint uStack_5c;
  undefined2 local_58;
  int local_56;
  undefined1 local_51;
  
  if (param_1 == 0) {
    uVar2 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar2,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_processIncomingMessage_cold_29(uVar2);
    }
  }
  else if (*(char *)(param_1 + 0x1e) == '\x01') {
    uVar2 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar2,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_processIncomingMessage_cold_28(uVar2);
    }
  }
  else if (param_3 == 0) {
    uVar2 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar2,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_processIncomingMessage_cold_27(uVar2);
    }
  }
  else {
    uVar2 = _iAP2MsgGetMsgID(param_3);
    iVar1 = (int)uVar2;
    if (iVar1 == 0) {
      uVar2 = _logObjectForModule();
      iVar1 = _os_log_type_enabled(uVar2,0x10);
      if (iVar1 != 0) {
        _mfi4Auth_protocol_processIncomingMessageExtra_cold_5(uVar2);
      }
    }
    else {
      uVar4 = uVar2;
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
        puVar5 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          uVar4 = _mfi4Auth_protocol_handleAuthSessionClose_cold_1();
          puVar5 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
      }
      uVar3 = _os_log_type_enabled(puVar5,uVar4,0);
      if ((uVar3 & 1) != 0) {
        local_60 = (uint)DAT_1001b3108;
        uStack_5c = (uint)*(ushort *)(param_1 + 0x1c);
        local_58 = 0x400;
        local_56 = iVar1;
        __os_log_impl(0x100000000,uVar4,0,"processIncomingData: cmd:0x%x  rsp:0x%x",&local_60,0xe);
      }
      uVar4 = 0;
      if (iVar1 < 0x5216) {
        if (iVar1 < 0x5212) {
          if (iVar1 == 0x5201) {
            if ((param_2 == 0) && (*(short *)(param_1 + 0x1c) == 0x5100)) {
              uVar2 = _mfi4Auth_protocol_handle_AuthSetup(param_1,param_3,param_4);
              if ((int)uVar2 == 0) goto LAB_1000497d4;
              uVar2 = _logObjectForModule();
              iVar1 = _os_log_type_enabled(uVar2,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_protocol_processIncomingMessage_cold_21(uVar2);
              }
            }
            goto LAB_10004990c;
          }
          if (iVar1 == 0x5202) {
            if ((param_2 == 0) && (*(short *)(param_1 + 0x1c) == 0x5100)) {
              uVar2 = _mfi4Auth_protocol_handle_AuthSetupFailed(param_1,param_3);
LAB_1000497d4:
              if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
                puVar5 = PTR___os_log_default_10022bbb0;
                if (_logObjectForModule_onceToken != -1) {
                  uVar2 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                  puVar5 = PTR___os_log_default_10022bbb0;
                }
              }
              else {
                puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
              }
              iVar1 = _os_log_type_enabled(puVar5,uVar2,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_protocol_processIncomingMessage_cold_23(uVar2);
              }
              return 1;
            }
            goto LAB_10004990c;
          }
          if (iVar1 == 0x5211) {
            if (((param_2 == 0) && (*(int *)(param_1 + 0xe0) == 1)) &&
               (*(short *)(param_1 + 0x1c) == 0x5110)) {
              uVar2 = _mfi4Auth_protocol_handle_AuthStart(param_1,param_3);
              if ((int)uVar2 == 0) goto LAB_1000497d4;
              uVar2 = _logObjectForModule();
              iVar1 = _os_log_type_enabled(uVar2,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_protocol_processIncomingMessage_cold_18(uVar2);
              }
            }
            goto LAB_10004990c;
          }
        }
        else {
          if (iVar1 == 0x5212) {
            if (param_2 != 0) {
              if (*(int *)(param_1 + 0xe0) - 3U < 0xfffffffe) {
                uVar2 = _logObjectForModule();
                iVar1 = _os_log_type_enabled(uVar2,0x10);
                if (iVar1 != 0) {
                  _mfi4Auth_protocol_processIncomingMessage_cold_16(uVar2);
                }
              }
              else {
                if (*(int *)(param_1 + 0xe0) == 1) {
                  if (*(ushort *)(param_1 + 0x1c) - 0x5115 < 0xfffffffe) {
                    uVar2 = _logObjectForModule();
                    iVar1 = _os_log_type_enabled(uVar2,0x10);
                    if (iVar1 != 0) {
                      _mfi4Auth_protocol_processIncomingMessage_cold_16(uVar2);
                    }
                    goto LAB_10004990c;
                  }
                }
                else if ((*(ushort *)(param_1 + 0x1c) & 0xfffffffd) != 0x5111) {
                  uVar2 = _logObjectForModule();
                  iVar1 = _os_log_type_enabled(uVar2,0x10);
                  if (iVar1 != 0) {
                    _mfi4Auth_protocol_processIncomingMessage_cold_16(uVar2);
                  }
                  goto LAB_10004990c;
                }
                uVar2 = _mfi4Auth_protocol_handle_RequestAuthCert(param_1,param_3,param_4);
                if ((int)uVar2 == 0) goto LAB_1000497d4;
                uVar2 = _logObjectForModule();
                iVar1 = _os_log_type_enabled(uVar2,0x10);
                if (iVar1 != 0) {
                  _mfi4Auth_protocol_processIncomingMessage_cold_15(uVar2);
                }
              }
            }
            goto LAB_10004990c;
          }
          if (iVar1 == 0x5213) {
            if (((param_2 != 0) || (*(int *)(param_1 + 0xe0) == 0)) &&
               (*(short *)(param_1 + 0x1c) == 0x5112)) {
              uVar2 = _mfi4Auth_protocol_handle_AuthCert(param_1,param_3,param_4);
              if ((int)uVar2 == 0) goto LAB_1000497d4;
              uVar2 = _logObjectForModule();
              iVar1 = _os_log_type_enabled(uVar2,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_protocol_processIncomingMessage_cold_13(uVar2);
              }
            }
            goto LAB_10004990c;
          }
          if (iVar1 == 0x5214) {
            if (((param_2 != 0) && (*(int *)(param_1 + 0xe0) == 2)) &&
               ((*(ushort *)(param_1 + 0x1c) & 0xfffd) == 0x5111)) {
              uVar2 = _mfi4Auth_protocol_handle_AuthFinish(param_1,param_3,param_4);
              if ((int)uVar2 == 0) goto LAB_1000497d4;
              uVar2 = _logObjectForModule();
              iVar1 = _os_log_type_enabled(uVar2,0x10);
              if (iVar1 != 0) {
                _mfi4Auth_protocol_processIncomingMessage_cold_12(uVar2);
              }
            }
            goto LAB_10004990c;
          }
        }
      }
      else if (iVar1 < 0x52fe) {
        if (iVar1 == 0x5216) {
          if ((param_2 == 0) && (*(int *)(param_1 + 0xe0) == 0)) {
            uVar2 = _mfi4Auth_protocol_handle_AuthChallengeResponse(param_1,param_3,param_4);
            if ((int)uVar2 == 0) goto LAB_1000497d4;
            uVar2 = _logObjectForModule();
            iVar1 = _os_log_type_enabled(uVar2,0x10);
            if (iVar1 != 0) {
              _mfi4Auth_protocol_processIncomingMessage_cold_11(uVar2);
            }
          }
          goto LAB_10004990c;
        }
        if (iVar1 == 0x52fa) {
          if (param_2 == 0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar5 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar4 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar5 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar1 = _os_log_type_enabled(puVar5,uVar4,0x10);
            if (iVar1 != 0) {
              _mfi4Auth_protocol_processIncomingMessage_cold_20(uVar4);
            }
            uVar2 = 0;
            goto LAB_1000497d4;
          }
          goto LAB_10004990c;
        }
        if (iVar1 == 0x52fd) {
          if (param_2 == 0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar5 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar4 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar5 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar1 = _os_log_type_enabled(puVar5,uVar4,0x10);
            if (iVar1 != 0) {
              _mfi4Auth_protocol_processIncomingMessage_cold_9(uVar4);
            }
            uVar2 = _mfi4Auth_protocol_handle_AuthenticationReset(param_1,param_3,param_4);
            if ((int)uVar2 == 0) goto LAB_1000497d4;
            uVar2 = _logObjectForModule();
            iVar1 = _os_log_type_enabled(uVar2,0x10);
            if (iVar1 != 0) {
              _mfi4Auth_protocol_processIncomingMessage_cold_10(uVar2);
            }
          }
          goto LAB_10004990c;
        }
      }
      else {
        if (iVar1 == 0x52fe) {
          if (param_2 == 0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar5 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar4 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar5 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar1 = _os_log_type_enabled(puVar5,uVar4,0x10);
            if (iVar1 != 0) {
              _mfi4Auth_protocol_processIncomingMessage_cold_7(uVar4);
            }
            uVar2 = _mfi4Auth_protocol_handle_AuthenticationFailed(param_1,param_3,param_4);
            goto LAB_1000497d4;
          }
          goto LAB_10004990c;
        }
        if (iVar1 == 0x5491) {
          if (param_2 == 0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar5 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar4 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar5 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar1 = _os_log_type_enabled(puVar5,uVar4,0);
            if (iVar1 != 0) {
              local_60 = local_60 & 0xffff0000;
              __os_log_impl(0x100000000,uVar4,0,"Received RefreshAccessStateResponse",&local_60,2);
            }
            uVar2 = _mfi4Auth_protocol_handle_RefreshAccessStateResponse(param_1,param_3);
            if ((int)uVar2 == 0) goto LAB_1000497d4;
            uVar2 = _logObjectForModule();
            iVar1 = _os_log_type_enabled(uVar2,0x10);
            if (iVar1 != 0) {
              _mfi4Auth_protocol_processIncomingMessage_cold_3(uVar2);
            }
          }
          goto LAB_10004990c;
        }
        if (iVar1 == 0x52ff) {
          if ((param_2 != 0) && (0xfffffffd < *(int *)(param_1 + 0xe0) - 3U)) {
            if (*(int *)(param_1 + 0xe0) == 1) {
              if (*(ushort *)(param_1 + 0x1c) - 0x5115 < 0xfffffffe) goto LAB_10004990c;
            }
            else if (*(ushort *)(param_1 + 0x1c) != 0x51ff) goto LAB_10004990c;
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
              puVar5 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                uVar4 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
                puVar5 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
            }
            iVar1 = _os_log_type_enabled(puVar5,uVar4,0);
            if (iVar1 != 0) {
              local_60 = local_60 & 0xffff0000;
              __os_log_impl(0x100000000,uVar4,0,"Received AuthenticationSucceeded",&local_60,2);
            }
            uVar2 = _mfi4Auth_protocol_handle_AuthenticationSucceeded(param_1,param_3,param_4);
            if ((int)uVar2 == 0) goto LAB_1000497d4;
            uVar2 = _logObjectForModule();
            iVar1 = _os_log_type_enabled(uVar2,0x10);
            if (iVar1 != 0) {
              _mfi4Auth_protocol_processIncomingMessage_cold_5(uVar2);
            }
          }
          goto LAB_10004990c;
        }
      }
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3b)) {
        puVar5 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          uVar4 = _mfi4Auth_protocol_handle_AuthSetup_cold_15();
          puVar5 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar5 = *(undefined **)(_gLogObjects + 0x1d0);
      }
      iVar1 = _os_log_type_enabled(puVar5,uVar4,0x10);
      if (iVar1 != 0) {
        _mfi4Auth_protocol_processIncomingMessageExtra_cold_4(uVar2,uVar4);
      }
    }
  }
LAB_10004990c:
  _mfi4Auth_protocol_processIncomingMessage_cold_30(&local_60,&local_51);
  return local_51;
}


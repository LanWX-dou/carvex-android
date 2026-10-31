/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000328dc
 * original code SHA256: d21744c91b4085e0a26d32d9874eb7e76dd691ab49a03681b0a93dd54f4b4901
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iAP2LinkIsValidSynParam(byte *param_1,uint param_2,long param_3,long param_4)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  undefined8 uVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  long lVar8;
  ulong uVar9;
  uint uVar10;
  undefined *puVar11;
  ulong uVar12;
  undefined1 *local_a0;
  undefined1 auStack_98 [6];
  undefined2 uStack_92;
  uint local_90;
  undefined2 uStack_8c;
  ushort uStack_8a;
  undefined2 uStack_88;
  undefined2 uStack_86;
  undefined4 uStack_84;
  undefined8 local_80;
  undefined1 *local_78;
  undefined2 local_70;
  
  if (param_1 == (byte *)0x0) {
    return 0;
  }
  if (2 < param_2 - 1) {
    return 0;
  }
  if (*param_1 < param_2 || 3 < *param_1) {
    if ((__iAP2LogEnableMask >> 2 & 1) != 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
        puVar11 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_1(0);
          puVar11 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar11 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar5 = _os_log_type_enabled(puVar11,2);
      if (iVar5 != 0) {
        _iAP2LinkIsValidSynParam_cold_2(param_1,puVar11);
      }
    }
  }
  else {
    iVar5 = ___iAP2LinkIsValidSynParamMaxOutstandingPackets(param_1);
    if (iVar5 != 0) {
      if (*(ushort *)(param_1 + 4) < 0x18) {
        if ((__iAP2LogEnableMask >> 2 & 1) != 0) {
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
            puVar11 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              _iAP2LinkEventNotify_cold_1();
              puVar11 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar11 = *(undefined **)(_gLogObjects + 0xb0);
          }
          iVar5 = _os_log_type_enabled(puVar11,2);
          if (iVar5 != 0) {
            _iAP2LinkIsValidSynParam_cold_4(param_1 + 4,puVar11);
          }
        }
      }
      else {
        uVar12 = _iAP2LinkIsNoRetransmit(param_1);
        if ((uVar12 & 1) == 0) {
          if (*(ushort *)(param_1 + 6) < 0x14) {
            if ((__iAP2LogEnableMask >> 2 & 1) != 0) {
              if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
                puVar11 = PTR___os_log_default_10022bbb0;
                if (_logObjectForModule_onceToken != -1) {
                  _iAP2LinkEventNotify_cold_1();
                  puVar11 = PTR___os_log_default_10022bbb0;
                }
              }
              else {
                puVar11 = *(undefined **)(_gLogObjects + 0xb0);
              }
              iVar5 = _os_log_type_enabled(puVar11,2);
              if (iVar5 != 0) {
                _iAP2LinkIsValidSynParam_cold_6(param_1 + 6,puVar11);
              }
            }
            goto LAB_100032c04;
          }
          iVar5 = ___iAP2LinkIsValidSynParamCumAckTimeout(param_1);
          if (((iVar5 == 0) ||
              (iVar5 = ___iAP2LinkIsValidSynParamMaxRetransmissions(param_1), iVar5 == 0)) ||
             (iVar5 = ___iAP2LinkIsValidSynParamMaxCumAck(param_1), iVar5 == 0)) goto LAB_100032c04;
        }
        if (((*param_1 < 2) || (param_1[0x18] == 0)) ||
           (iVar5 = _iAP2LinkCommandIsFeatureSetValid(param_1), iVar5 != 0)) {
          local_70 = 0xaaaa;
          uStack_88 = 0xaaaa;
          uStack_86 = 0xaaaa;
          uStack_84 = 0xaaaaaaaa;
          local_90 = 0xaaaaaaaa;
          uStack_8c = 0xaaaa;
          uStack_8a = 0xaaaa;
          local_78 = &DAT_aaaaaaaaaaaaaaaa;
          local_80 = &DAT_aaaaaaaaaaaaaaaa;
          local_a0 = &DAT_aaaaaaaaaaaaaaaa;
          _auStack_98 = 0xaaaaaaaaaa00aaaa;
          if (param_1[10] != 0) {
            bVar6 = 0;
            uVar12 = 0;
            bVar3 = false;
            do {
              pbVar1 = param_1 + uVar12 * 4 + 0x1e;
              if (bVar6 == 0) {
                bVar2 = *pbVar1;
              }
              else {
                lVar8 = 0;
                bVar2 = *pbVar1;
                uVar9 = (ulong)bVar6;
                do {
                  if ((*(byte *)((long)&uStack_84 + lVar8 * 4 + 2) == bVar2) ||
                     (*(byte *)((long)&uStack_84 + lVar8 * 4 + 3) == pbVar1[1])) goto LAB_100032c04;
                  lVar8 = lVar8 + 1;
                  uVar9 = uVar9 - 1;
                } while (uVar9 != 0);
              }
              if (((bVar2 == 0) || (4 < pbVar1[1])) || ((pbVar1[3] & 1) != 0)) goto LAB_100032c04;
              _iAP2PacketCopySessionInfo((long)&uStack_84 + (ulong)bVar6 * 4 + 2,pbVar1);
              bVar6 = auStack_98[2] + 1;
              auStack_98._0_3_ = CONCAT12(bVar6,auStack_98._0_2_);
              if ((((*pbVar1 == 0) || (4 < pbVar1[1])) ||
                  (((pbVar1[3] & 1) != 0 ||
                   ((uVar7 = (uint)pbVar1[1], param_3 != 0 &&
                    (*(byte *)(param_3 + (ulong)uVar7) < pbVar1[2])))))) ||
                 ((param_4 != 0 && (pbVar1[2] < *(byte *)(param_4 + (ulong)uVar7)))))
              goto LAB_100032c04;
              if (uVar7 == 0) {
                bVar3 = true;
              }
              uVar12 = uVar12 + 1;
            } while (uVar12 < param_1[10]);
            if (bVar3) {
              return 1;
            }
          }
        }
      }
    }
  }
LAB_100032c04:
  if ((__iAP2LogEnableMask & 1) != 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar11 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_2();
        puVar11 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar11 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar5 = _os_log_type_enabled(puVar11,0);
    if (iVar5 != 0) {
      local_a0 = (undefined1 *)((ulong)local_a0 & 0xffffffffffff0000);
      __os_log_impl(0x100000000,puVar11,0,"ERROR: Invalid SYN Params detected:",&local_a0,2);
    }
  }
  if ((__iAP2LogEnableMask & 1) != 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar11 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_2();
        puVar11 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar11 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar5 = _os_log_type_enabled(puVar11,0);
    if (iVar5 != 0) {
      local_a0 = (undefined1 *)(ulong)CONCAT14(*param_1,(int)DAT_1001b30b0);
      __os_log_impl(0x100000000,puVar11,0,"ERROR:     version=%d",&local_a0,8);
    }
  }
  if ((__iAP2LogEnableMask & 1) != 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar11 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_2();
        puVar11 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar11 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar5 = _os_log_type_enabled(puVar11,0);
    if (iVar5 != 0) {
      local_a0 = (undefined1 *)(ulong)CONCAT14(param_1[1],(int)DAT_1001b3108);
      auStack_98 = (undefined1  [6])CONCAT24(0,CONCAT22(*(undefined2 *)(param_1 + 4),0x400));
      __os_log_impl(0x100000000,puVar11,0,"ERROR:     maxOutstanding=%d maxPacketSize=%d",&local_a0,
                    0xe);
    }
  }
  if ((__iAP2LogEnableMask & 1) != 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar11 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_2();
        puVar11 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar11 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar5 = _os_log_type_enabled(puVar11,0);
    if (iVar5 != 0) {
      local_a0 = (undefined1 *)(ulong)CONCAT24(*(undefined2 *)(param_1 + 6),(int)DAT_1001b3108);
      auStack_98 = (undefined1  [6])CONCAT24(0,CONCAT22(*(undefined2 *)(param_1 + 8),0x400));
      __os_log_impl(0x100000000,puVar11,0,"ERROR:     retransmitTimeout=%d cumAckTimeout=%d",
                    &local_a0,0xe);
    }
  }
  if ((__iAP2LogEnableMask & 1) != 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar11 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_2();
        puVar11 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar11 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar5 = _os_log_type_enabled(puVar11,0);
    if (iVar5 != 0) {
      local_a0 = (undefined1 *)(ulong)CONCAT14(param_1[2],(int)DAT_1001b3108);
      auStack_98 = (undefined1  [6])CONCAT33(0,CONCAT12(param_1[3],0x400));
      __os_log_impl(0x100000000,puVar11,0,"ERROR:     maxRetransmissions=%d maxCumAck=%d",&local_a0,
                    0xe);
    }
  }
  if ((__iAP2LogEnableMask & 1) != 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar11 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_2();
        puVar11 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar11 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar5 = _os_log_type_enabled(puVar11,0);
    if (iVar5 != 0) {
      local_a0 = (undefined1 *)(ulong)CONCAT14(param_1[10],(int)DAT_1001b30b0);
      __os_log_impl(0x100000000,puVar11,0,"ERROR:     numSessionInfo=%u",&local_a0,8);
    }
  }
  uVar4 = DAT_1001b3350;
  if (param_1[10] != 0) {
    uVar12 = 0;
    do {
      if ((__iAP2LogEnableMask & 1) != 0) {
        if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
          puVar11 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            _iAP2LinkEventNotify_cold_2();
            puVar11 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar11 = *(undefined **)(_gLogObjects + 0xb0);
        }
        iVar5 = _os_log_type_enabled(puVar11,0);
        if (iVar5 != 0) {
          pbVar1 = param_1 + uVar12 * 4 + 0x1e;
          bVar6 = pbVar1[1];
          uVar7 = 0;
          if (param_4 != 0) {
            uVar7 = (uint)*(byte *)(param_4 + (ulong)bVar6);
          }
          uVar10 = 0;
          if (param_3 != 0) {
            uVar10 = (uint)*(byte *)(param_3 + (ulong)bVar6);
          }
          local_a0 = (undefined1 *)CONCAT44((int)uVar12,(int)uVar4);
          auStack_98 = (undefined1  [6])CONCAT33(0,CONCAT12(*pbVar1,0x400));
          _auStack_98 = CONCAT26(0x400,auStack_98);
          local_90 = (uint)bVar6;
          uStack_8c = 0x400;
          uStack_8a = (ushort)pbVar1[2];
          uStack_88 = 0;
          uStack_86 = 0x400;
          uStack_84 = (uint)pbVar1[3];
          local_80 = (undefined1 *)CONCAT26(0x400,CONCAT42(uVar7,0x400));
          local_78 = (undefined1 *)CONCAT44(local_78._4_4_,uVar10);
          __os_log_impl(0x100000000,puVar11,0,
                        "ERROR:     session %u [id=%u type=%u ver=%u unrel=%d (min=%u max=%u)]",
                        &local_a0,0x2c);
        }
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < param_1[10]);
  }
  return 0;
}


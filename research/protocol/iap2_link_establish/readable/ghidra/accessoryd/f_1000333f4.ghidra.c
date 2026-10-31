/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000333f4
 * original code SHA256: ef40f0d0fc538c3863d6646880eb52e8c5d6ccce93cadda4d0b369e8e2fb34d3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined4 _iAP2LinkValidateSynParam(long param_1,byte *param_2)

{
  byte *pbVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  bool bVar7;
  undefined8 uVar8;
  int iVar9;
  ulong uVar10;
  undefined *puVar11;
  char *pcVar12;
  undefined8 in_x6;
  undefined8 in_x7;
  undefined4 uVar13;
  uint uVar14;
  char cVar15;
  long lVar16;
  ulong uVar17;
  ulong uVar18;
  uint uVar19;
  uint uVar20;
  byte bVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined4 local_d0;
  uint local_cc;
  undefined2 local_c8;
  uint local_c6;
  undefined2 local_c2;
  uint local_c0;
  undefined2 local_bc;
  uint local_ba;
  undefined2 local_b6;
  uint local_b4;
  undefined2 local_b0;
  uint local_ae;
  undefined1 *local_a0;
  undefined8 uStack_98;
  undefined1 *local_90;
  undefined6 uStack_88;
  undefined2 uStack_82;
  undefined6 uStack_80;
  undefined2 uStack_7a;
  undefined6 uStack_78;
  undefined2 local_72;
  undefined2 uStack_70;
  
  if (((*(byte *)(param_1 + 0xd4) >> 6 & 1) == 0) && (*(int *)(param_1 + 0xb8) == 0)) {
    return 1;
  }
  if (param_2 == (byte *)0x0) {
    return 0;
  }
  uStack_70 = 0xaaaa;
  uStack_88 = 0xaaaaaaaaaaaa;
  uStack_82 = 0xaaaa;
  local_90 = &DAT_aaaaaaaaaaaaaaaa;
  uStack_78 = 0xaaaaaaaaaaaa;
  local_72 = 0xaaaa;
  uStack_80 = 0xaaaaaaaaaaaa;
  uStack_7a = 0xaaaa;
  uStack_98 = &DAT_aaaaaaaaaaaaaaaa;
  local_a0 = &DAT_aaaaaaaaaaaaaaaa;
  uVar14 = (uint)*param_2;
  if (2 < uVar14) {
    uVar14 = 3;
  }
  uVar19 = (uint)*param_2;
  uVar20 = (uint)*(byte *)(param_1 + 0xd7);
  if (*(byte *)(param_1 + 0xd7) <= uVar19) {
    uVar20 = uVar14;
  }
  if (uVar20 != uVar19) {
    if ((__iAP2LogEnableMask & 1) != 0) {
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
      iVar9 = _os_log_type_enabled(puVar11,0);
      if (iVar9 != 0) {
        local_d0 = (undefined4)DAT_1001b3108;
        local_cc = (uint)*param_2;
        local_c8 = 0x400;
        local_c6 = uVar20;
        __os_log_impl(0x100000000,puVar11,0,"ERROR: Invalid SYN Params detected: linkVersion=%d->%d"
                      ,&local_d0,0xe);
      }
    }
    *param_2 = (byte)uVar20;
  }
  bVar3 = param_2[1];
  uVar10 = ___iAP2LinkIsValidSynParamMaxOutstandingPackets(param_2);
  if ((uVar10 & 1) == 0) {
    bVar21 = param_2[1];
    uVar14 = 0x7f;
    if (-1 < (char)bVar21) {
      uVar14 = (uint)bVar3;
    }
    if (bVar21 == 0) {
      uVar14 = 1;
    }
    if (uVar14 == bVar21) goto LAB_100033554;
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
      iVar9 = _os_log_type_enabled(puVar11,0);
      if (iVar9 != 0) {
        local_d0 = (undefined4)DAT_1001b3108;
        local_cc = (uint)param_2[1];
        local_c8 = 0x400;
        local_c6 = uVar14;
        __os_log_impl(0x100000000,puVar11,0,
                      "ERROR: Invalid SYN Params detected: maxOutstandingPackets=%d->%d",&local_d0,
                      0xe);
      }
    }
    uVar13 = 0;
    param_2[1] = (byte)uVar14;
  }
  else {
LAB_100033554:
    uVar13 = 1;
  }
  uVar2 = 0;
  if (uVar20 == uVar19) {
    uVar2 = uVar13;
  }
  uVar20 = (uint)*(ushort *)(param_2 + 4);
  uVar14 = uVar20;
  if (*(ushort *)(param_2 + 4) < 0x19) {
    uVar14 = 0x18;
  }
  if (uVar20 < 0x18) {
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
      iVar9 = _os_log_type_enabled(puVar11,0);
      if (iVar9 != 0) {
        local_d0 = (undefined4)DAT_1001b3108;
        local_cc = (uint)*(ushort *)(param_2 + 4);
        local_c8 = 0x400;
        local_c6 = uVar14;
        __os_log_impl(0x100000000,puVar11,0,
                      "ERROR: Invalid SYN Params detected: maxPacketSize=%d->%d",&local_d0,0xe);
      }
    }
    *(short *)(param_2 + 4) = (short)uVar14;
  }
  uVar13 = 0;
  if (0x17 < uVar20) {
    uVar13 = uVar2;
  }
  uVar10 = _iAP2LinkIsNoRetransmit(param_2);
  if ((uVar10 & 1) == 0) {
    uVar20 = (uint)*(ushort *)(param_2 + 6);
    uVar14 = uVar20;
    if (*(ushort *)(param_2 + 6) < 0x15) {
      uVar14 = 0x14;
    }
    if (uVar20 < 0x14) {
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
        iVar9 = _os_log_type_enabled(puVar11,0);
        if (iVar9 != 0) {
          local_d0 = (undefined4)DAT_1001b3108;
          local_cc = (uint)*(ushort *)(param_2 + 6);
          local_c8 = 0x400;
          local_c6 = uVar14;
          __os_log_impl(0x100000000,puVar11,0,
                        "ERROR: Invalid SYN Params detected: retransmitTimeout=%d->%d",&local_d0,0xe
                       );
        }
      }
      *(short *)(param_2 + 6) = (short)uVar14;
    }
    uVar2 = 0;
    if (0x13 < uVar20) {
      uVar2 = uVar13;
    }
    uVar20 = (uint)*(ushort *)(param_2 + 8);
    uVar14 = uVar20;
    if (*(ushort *)(param_2 + 8) < 0xb) {
      uVar14 = 10;
    }
    if (0x7ffe < uVar14) {
      uVar14 = 0x7fff;
    }
    if (uVar14 != uVar20) {
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
        iVar9 = _os_log_type_enabled(puVar11,0);
        if (iVar9 != 0) {
          local_d0 = (undefined4)DAT_1001b3108;
          local_cc = (uint)*(ushort *)(param_2 + 8);
          local_c8 = 0x400;
          local_c6 = uVar14;
          __os_log_impl(0x100000000,puVar11,0,
                        "ERROR: Invalid SYN Params detected: cumAckTimeout=%d->%d",&local_d0,0xe);
        }
      }
      *(short *)(param_2 + 8) = (short)uVar14;
    }
    uVar13 = 0;
    if (uVar14 == uVar20) {
      uVar13 = uVar2;
    }
    uVar14 = (uint)param_2[2];
    if (0x1d < uVar14) {
      uVar14 = 0x1e;
    }
    uVar20 = (uint)param_2[2];
    if (uVar20 == 0) {
      uVar14 = 1;
    }
    if (uVar14 != uVar20) {
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
        iVar9 = _os_log_type_enabled(puVar11,0);
        if (iVar9 != 0) {
          local_d0 = (undefined4)DAT_1001b3108;
          local_cc = (uint)param_2[2];
          local_c8 = 0x400;
          local_c6 = uVar14;
          __os_log_impl(0x100000000,puVar11,0,
                        "ERROR: Invalid SYN Params detected: maxRetransmissions=%d->%d",&local_d0,
                        0xe);
        }
      }
      param_2[2] = (byte)uVar14;
    }
    uVar2 = 0;
    if (uVar14 == uVar20) {
      uVar2 = uVar13;
    }
    bVar3 = param_2[3];
    if ((char)bVar3 < '\0') {
      uVar14 = 0x7f;
    }
    else {
      uVar14 = (uint)bVar3;
      if ((uint)param_2[1] <= (uint)bVar3) {
        uVar14 = (uint)param_2[1];
      }
    }
    if (uVar14 != bVar3) {
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
        iVar9 = _os_log_type_enabled(puVar11,0);
        if (iVar9 != 0) {
          local_d0 = (undefined4)DAT_1001b3108;
          local_cc = (uint)param_2[3];
          local_c8 = 0x400;
          local_c6 = uVar14;
          __os_log_impl(0x100000000,puVar11,0,"ERROR: Invalid SYN Params detected: maxCumAck=%d->%d"
                        ,&local_d0,0xe);
        }
      }
      param_2[3] = (byte)uVar14;
    }
    uVar13 = 0;
    if (uVar14 == bVar3) {
      uVar13 = uVar2;
    }
  }
  *(undefined4 *)(param_1 + 0x110) = 0;
  if (param_2[0x18] != 0) {
    _iAP2LinkCommandValidateFeatureSets(param_1,param_2);
  }
  uVar8 = DAT_1001b3358;
  uStack_98._0_3_ = (uint3)(ushort)uStack_98;
  if (param_2[10] == 0) {
    uVar14 = 0;
  }
  else {
    uVar10 = 0;
    bVar7 = false;
    uVar23 = 0;
    uVar22 = DAT_1001b3360;
    do {
      pbVar1 = param_2 + uVar10 * 4 + 0x1e;
      bVar3 = pbVar1[1];
      uVar14 = (uint)bVar3;
      puVar11 = PTR___os_log_default_10022bbb0;
      if ((*pbVar1 == 0 || 4 < bVar3) || ((pbVar1[3] & 1) != 0)) {
        if ((__iAP2LogEnableMask & 1) != 0) {
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
            if (_logObjectForModule_onceToken != -1) {
              _iAP2LinkEventNotify_cold_2();
              puVar11 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar11 = *(undefined **)(_gLogObjects + 0xb0);
          }
          iVar9 = _os_log_type_enabled(puVar11,0);
          if (iVar9 != 0) {
            bVar21 = *pbVar1;
            bVar4 = pbVar1[1];
            bVar5 = pbVar1[2];
            bVar6 = pbVar1[3];
            pcVar12 = 
            "ERROR: Invalid SYN Params detected: session %u [id=%u type=%u ver=%u unrel=%d]";
LAB_100033bb8:
            local_b4 = (uint)bVar6;
            local_ba = (uint)bVar5;
            local_c0 = (uint)bVar4;
            local_c6 = (uint)bVar21;
            local_b6 = 0x400;
            local_bc = 0x400;
            local_c2 = 0x400;
            local_c8 = 0x400;
            local_d0 = (int)uVar8;
            local_cc = (uint)uVar10;
            __os_log_impl(0x100000000,puVar11,0,pcVar12,&local_d0,0x20,in_x6,in_x7,uVar22,uVar23);
          }
        }
LAB_100033bc0:
        uVar13 = 0;
      }
      else if ((*(byte *)(*(long *)(param_1 + 0x160) + 0xe + (ulong)uVar14) < pbVar1[2]) ||
              (pbVar1[2] < *(byte *)(*(long *)(param_1 + 0x160) + 0x13 + (ulong)uVar14))) {
        _iAP2PacketCopySessionInfo(&uStack_82 + (ulong)uStack_98._2_1_ * 2,pbVar1);
        bVar21 = *(byte *)(*(long *)(param_1 + 0x160) + (ulong)pbVar1[1] + 0xe);
        if (pbVar1[2] <= bVar21) {
          bVar21 = *(byte *)(*(long *)(param_1 + 0x160) + 0x13 + (ulong)pbVar1[1]);
        }
        uVar18 = (ulong)uStack_98._2_1_;
        *(byte *)((long)&uStack_82 + (uVar18 << 2 | 2)) = bVar21;
        bVar21 = uStack_98._2_1_;
        if ((__iAP2LogEnableMask & 1) != 0) {
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
            if (_logObjectForModule_onceToken != -1) {
              _iAP2LinkEventNotify_cold_2();
            }
            uVar18 = (ulong)uStack_98 >> 0x10 & 0xff;
            puVar11 = PTR___os_log_default_10022bbb0;
          }
          else {
            puVar11 = *(undefined **)(_gLogObjects + 0xb0);
          }
          iVar9 = _os_log_type_enabled(puVar11,0);
          if (iVar9 != 0) {
            local_d0 = (undefined4)uVar22;
            local_c8 = 0x400;
            local_c6 = (uint)*pbVar1;
            local_c2 = 0x400;
            local_c0 = (uint)pbVar1[1];
            local_bc = 0x400;
            local_ba = (uint)pbVar1[2];
            local_b6 = 0x400;
            local_b4 = (uint)*(byte *)((long)&uStack_82 + (uVar18 << 2 | 2));
            local_b0 = 0x400;
            local_ae = (uint)pbVar1[3];
            local_cc = (uint)uVar10;
            __os_log_impl(0x100000000,puVar11,0,
                          "ERROR: Invalid SYN Params session version detected: session %u [id=%u type=%u ver=%u->%u unrel=%d]"
                          ,&local_d0,0x26);
            uVar18 = (ulong)uStack_98 >> 0x10 & 0xff;
          }
          bVar21 = (byte)uVar18;
        }
        uStack_98._0_3_ = CONCAT12(bVar21 + 1,(ushort)uStack_98);
      }
      else {
        uVar18 = (ulong)uStack_98._2_1_;
        if (uVar18 != 0) {
          lVar16 = 0;
          uVar17 = uVar18;
          do {
            if ((*(byte *)(&uStack_82 + lVar16 * 2) == *pbVar1) ||
               (*(byte *)((long)&uStack_82 + lVar16 * 4 + 1) == uVar14)) {
              if ((__iAP2LogEnableMask & 1) == 0) goto LAB_100033bc0;
              if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
                if (_logObjectForModule_onceToken != -1) {
                  _iAP2LinkEventNotify_cold_2();
                  puVar11 = PTR___os_log_default_10022bbb0;
                }
              }
              else {
                puVar11 = *(undefined **)(_gLogObjects + 0xb0);
              }
              iVar9 = _os_log_type_enabled(puVar11,0);
              if (iVar9 == 0) goto LAB_100033bc0;
              bVar21 = *pbVar1;
              bVar4 = pbVar1[1];
              bVar5 = pbVar1[2];
              bVar6 = pbVar1[3];
              pcVar12 = 
              "ERROR: Duplicate session id/type detected: session %u [id=%u type=%u ver=%u unrel=%d]"
              ;
              goto LAB_100033bb8;
            }
            lVar16 = lVar16 + 1;
            uVar17 = uVar17 - 1;
          } while (uVar17 != 0);
        }
        _iAP2PacketCopySessionInfo(&uStack_82 + uVar18 * 2,pbVar1);
        uStack_98._0_3_ = CONCAT12(uStack_98._2_1_ + '\x01',(ushort)uStack_98);
      }
      bVar7 = (bool)(bVar3 == 0 | bVar7);
      uVar10 = uVar10 + 1;
    } while (uVar10 < param_2[10]);
    uVar14 = (uint)uStack_98._2_1_;
    if (bVar7) goto LAB_100033e68;
  }
  if (uVar14 < 5) {
    uVar10 = (ulong)uVar14;
    cVar15 = '\x01';
    do {
      if (uVar14 == 0) {
        uVar18 = 0;
      }
      else {
        uVar18 = 0;
        while (*(char *)(&uStack_82 + uVar18 * 2) != cVar15) {
          uVar18 = uVar18 + 1;
          if (uVar10 == uVar18) goto LAB_100033e34;
        }
        cVar15 = cVar15 + '\x01';
      }
    } while ((uint)uVar18 != uVar14);
LAB_100033e34:
    *(char *)(&uStack_82 + uVar10 * 2) = cVar15;
    *(undefined1 *)((long)&uStack_82 + (uVar10 << 2 | 1)) = 0;
    *(undefined1 *)((long)&uStack_82 + (uVar10 << 2 | 2)) = 1;
    uVar14 = uVar14 + 1;
    *(undefined1 *)((long)&uStack_82 + (uVar10 << 2 | 3)) = 0;
  }
LAB_100033e68:
  param_2[10] = (byte)uVar14;
  *(ulong *)(param_2 + 0x26) = CONCAT62(uStack_78,uStack_7a);
  *(ulong *)(param_2 + 0x1e) = CONCAT62(uStack_80,uStack_82);
  *(uint *)(param_2 + 0x2e) = CONCAT22(uStack_70,local_72);
  return uVar13;
}


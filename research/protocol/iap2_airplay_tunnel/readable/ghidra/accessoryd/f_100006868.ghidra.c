/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100006868
 * original code SHA256: 24fc223afb1a81dca683146de18ceb4b21ee8a161737e38d61458542b3439e68
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_iAP2LinkQueueSendDataWithSentCallback
          (long param_1,long param_2,ulong param_3,undefined8 param_4,undefined8 param_5,
          long param_6,undefined8 param_7,code *param_8,undefined1 param_9)

{
  byte *pbVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  undefined *puVar6;
  char *pcVar7;
  code *pcVar8;
  undefined1 uVar9;
  ulong uVar10;
  long lVar11;
  ulong uVar12;
  undefined8 uVar13;
  uint uVar14;
  uint uVar15;
  ulong uVar16;
  uint uVar17;
  uint uVar18;
  byte *pbVar19;
  uint uVar20;
  undefined4 local_a0;
  char *local_9c;
  undefined2 local_94;
  undefined4 local_92;
  undefined2 local_8e;
  uint local_8c;
  undefined2 local_88;
  uint local_86;
  undefined2 local_82;
  uint local_80;
  undefined2 local_7c;
  uint local_7a;
  undefined2 local_76;
  uint local_74;
  undefined2 local_70;
  uint local_6e;
  
  uVar18 = (uint)param_3;
  uVar20 = (uint)param_2;
  puVar6 = PTR___os_log_default_10022bbb0;
  if (((param_1 == 0) || (param_2 == 0)) || (uVar18 == 0)) {
    if ((__iAP2LogEnableMask & 1) != 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_1();
          puVar6 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar6 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar5 = _os_log_type_enabled(puVar6,0);
      if (iVar5 != 0) {
        local_8c = (uint)param_1 & 0xffff;
        local_a0 = (undefined4)DAT_1001b3110;
        local_86 = uVar20 & 0xffff;
        local_92 = 0x1140;
        local_88 = 0x400;
        local_82 = 0x400;
        pcVar7 = "ERROR: %s:%d NULL link(%hx) or payload(%hx) or no payload (len=%u)!";
        uVar13 = 0x24;
        local_80 = uVar18;
        goto LAB_100006af8;
      }
    }
  }
  else {
    uVar10 = (ulong)*(byte *)(param_1 + 0x1a4);
    uVar14 = (uint)param_4;
    if (uVar10 != 0) {
      lVar11 = 0;
      pbVar19 = (byte *)0x0;
      do {
        pbVar1 = (byte *)(param_1 + 0x1b8 + lVar11 * 4);
        if (*pbVar1 != uVar14) {
          pbVar1 = pbVar19;
        }
        lVar11 = lVar11 + 1;
        uVar10 = uVar10 - 1;
        pbVar19 = pbVar1;
      } while (uVar10 != 0);
      if (pbVar1 != (byte *)0x0) {
        uVar17 = (uint)*(ushort *)(param_1 + 0x1a6);
        if ((uint)*(ushort *)(param_1 + 0xc0) <= (uint)*(ushort *)(param_1 + 0x1a6)) {
          uVar17 = (uint)*(ushort *)(param_1 + 0xc0);
        }
        iVar5 = -0xc;
        if (*(char *)(param_1 + 0xd5) != '\x02') {
          iVar5 = -10;
        }
        uVar17 = iVar5 + uVar17;
        uVar10 = param_3;
        if (uVar18 < uVar17) {
LAB_100006b40:
          lVar11 = _iAP2PacketCreateACKPacket
                             (param_1,*(undefined1 *)(param_1 + 0xbe),
                              *(undefined1 *)(param_1 + 0xbc),param_2,uVar10,param_4);
          bVar4 = lVar11 == 0;
          if (lVar11 != 0) {
            uVar17 = 0;
            uVar16 = uVar10;
            do {
              uVar12 = uVar10;
              if ((uint)uVar16 < (uint)param_3) {
                uVar13 = 0;
                pcVar8 = (code *)0x0;
                uVar9 = 0;
              }
              else {
                uVar13 = param_7;
                pcVar8 = param_8;
                uVar9 = param_9;
                if (param_6 != 0) {
                  _iAP2PacketSetCallbackOnSentToTransport(lVar11,param_6);
                }
              }
              uVar13 = _iAP2LinkQueueSendDataPacketInternal
                                 (param_1,lVar11,param_4,param_5,uVar13,pcVar8,uVar9);
              _iAP2PacketRelease(lVar11);
              bVar3 = false;
              if ((int)uVar13 == 0) goto LAB_100006df0;
              uVar15 = (uint)uVar12;
              uVar17 = uVar15 + uVar17;
              uVar2 = uVar18 - uVar17;
              param_3 = (ulong)uVar2;
              if (uVar18 < uVar17 || uVar2 == 0) goto LAB_100006df0;
              param_2 = param_2 + (uVar12 & 0xffffffff);
              if (uVar2 <= uVar15) {
                uVar15 = uVar2;
              }
              uVar10 = (ulong)uVar15;
              lVar11 = _iAP2PacketCreateACKPacket
                                 (param_1,*(undefined1 *)(param_1 + 0xbe),
                                  *(undefined1 *)(param_1 + 0xbc),param_2,uVar10,param_4);
              uVar16 = uVar12;
            } while (lVar11 != 0);
          }
          if ((__iAP2LogEnableMask & 1) != 0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
              puVar6 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                _iAP2LinkEventNotify_cold_1();
                puVar6 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar6 = *(undefined **)(_gLogObjects + 0xb0);
            }
            iVar5 = _os_log_type_enabled(puVar6,0);
            if (iVar5 != 0) {
              local_8c = _iAP2ListArrayGetCount
                                   (*(undefined8 *)(param_1 + 0x130 + (ulong)pbVar1[1] * 8));
              local_a0 = (undefined4)DAT_1001b3368;
              local_7a = (uint)param_2 & 0xffff;
              local_9c = "iAP2LinkQueueSendDataWithSentCallback";
              local_94 = 0x400;
              local_92 = 0x112f;
              local_8e = 0x400;
              local_88 = 0x400;
              local_82 = 0x400;
              local_7c = 0x400;
              local_76 = 0x400;
              local_74 = (uint)uVar10;
              local_70 = 0x400;
              local_86 = uVar20 & 0xffff;
              local_80 = uVar18;
              local_6e = uVar14;
              __os_log_impl(0x100000000,puVar6,0,
                            "ERROR: %s:%d ERROR: Ran out of Send Packets! listCount=%u payload=%hx payloadLen=%u data=%hx dataLen=%u session=%u"
                            ,&local_a0,0x36);
            }
          }
          uVar13 = 0;
          bVar3 = bVar4;
        }
        else {
          uVar15 = 0;
          if (uVar17 != 0) {
            uVar15 = ((uVar18 + uVar17) - 1) / uVar17;
          }
          iVar5 = _iAP2ListArrayGetAvailSpace
                            (*(undefined8 *)(param_1 + 0x130 + (ulong)pbVar1[1] * 8));
          uVar10 = (ulong)uVar17;
          if ((int)uVar15 <= iVar5) goto LAB_100006b40;
          if ((__iAP2LogEnableMask & 1) != 0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
              puVar6 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                _iAP2LinkEventNotify_cold_1();
                puVar6 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar6 = *(undefined **)(_gLogObjects + 0xb0);
            }
            iVar5 = _os_log_type_enabled(puVar6,0);
            if (iVar5 != 0) {
              local_8c = _iAP2ListArrayGetCount
                                   (*(undefined8 *)(param_1 + 0x130 + (ulong)pbVar1[1] * 8));
              local_a0 = (undefined4)DAT_1001b3368;
              local_86 = uVar20 & 0xffff;
              local_9c = "iAP2LinkQueueSendDataWithSentCallback";
              local_94 = 0x400;
              local_92 = 0x10f1;
              local_8e = 0x400;
              local_88 = 0x400;
              local_82 = 0x400;
              local_7c = 0x400;
              local_76 = 0x400;
              local_70 = 0x400;
              local_80 = uVar18;
              local_7a = local_86;
              local_74 = uVar17;
              local_6e = uVar14;
              __os_log_impl(0x100000000,puVar6,0,
                            "ERROR: %s:%d No space in session send queue! listCount=%u payload=%hx payloadLen=%u data=%hx dataLen=%u session=%u"
                            ,&local_a0,0x36);
            }
          }
          uVar13 = 0;
          bVar3 = true;
        }
LAB_100006df0:
        _iAP2LinkSignalSendBuffCB(param_1);
        goto joined_r0x000100006b04;
      }
    }
    if ((__iAP2LogEnableMask & 1) != 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_1();
          puVar6 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar6 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar5 = _os_log_type_enabled(puVar6,0);
      if (iVar5 != 0) {
        local_a0 = (undefined4)DAT_1001b3080;
        local_92 = 0x113a;
        pcVar7 = "ERROR: %s:%d ERROR: Invalid session(%u)!";
        uVar13 = 0x18;
        local_8c = uVar14;
LAB_100006af8:
        local_8e = 0x400;
        local_94 = 0x400;
        local_9c = "iAP2LinkQueueSendDataWithSentCallback";
        __os_log_impl(0x100000000,puVar6,0,pcVar7,&local_a0,uVar13);
      }
    }
  }
  uVar13 = 0;
  bVar3 = true;
joined_r0x000100006b04:
  if ((param_8 != (code *)0x0) && (bVar3)) {
    (*param_8)(param_1,param_5);
  }
  return uVar13;
}


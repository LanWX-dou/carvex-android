/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000ada0
 * original code SHA256: 663071d03988fd3d381b71fad3dc66edcc58a9e7ae6c90dc2f0f9bf5c4d9543e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkHandleReadyPacket(long param_1,long param_2)

{
  char *pcVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  code *pcVar5;
  char cVar6;
  undefined1 uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  ulong uVar11;
  long lVar12;
  undefined *puVar13;
  char *pcVar14;
  undefined8 uVar15;
  long lVar16;
  ulong unaff_x30;
  undefined4 local_70;
  uint local_6c;
  undefined2 local_68;
  uint local_66;
  undefined2 local_62;
  uint local_60;
  undefined1 local_51;
  
  if (0x12 < *(byte *)(param_2 + 0x3d)) {
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar5 = (code *)SoftwareBreakpoint(0xc471,0x10000ae04);
      (*pcVar5)();
    }
    _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),*(byte *)(param_2 + 0x3d) + 4);
    return;
  }
  lVar16 = *(long *)(param_2 + 0x40);
  puVar13 = PTR___os_log_default_10022bbb0;
  if (*(ushort *)(param_1 + 0x19e) < *(ushort *)(param_2 + 0x36)) {
    if ((__iAP2LogEnableMask & 1) == 0) {
      return;
    }
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      if (_logObjectForModule_onceToken != -1) goto LAB_10000b2f8;
    }
    else {
      puVar13 = *(undefined **)(_gLogObjects + 0xb0);
    }
  }
  else {
    if (*(char *)(*(long *)(param_1 + 8) + 10) == '\x06') {
      if ((__iAP2LogEnableMask & 1) == 0) {
        return;
      }
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_1();
          puVar13 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar13 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar9 = _os_log_type_enabled(puVar13,0);
      if (iVar9 == 0) {
        return;
      }
      bVar3 = *(byte *)(lVar16 + 5);
      uVar4 = *(ushort *)(param_2 + 0x36);
      local_70 = (undefined4)DAT_1001b3108;
      pcVar14 = "ERROR: Packet seq:0x%x length:%d received while link state = SUSPEND !";
      uVar15 = 0xe;
      goto LAB_10000afd4;
    }
    *(int *)(param_1 + 0x210) = *(int *)(param_1 + 0x210) + 1;
    _iAP2PacketRetain(param_2);
    if (*(long *)(param_1 + 0x118) != 0) {
      _iAP2PacketRelease();
    }
    *(long *)(param_1 + 0x118) = param_2;
    cVar6 = *(char *)(param_1 + 0xbc);
    cVar2 = *(char *)(lVar16 + 5);
    uVar8 = _iAP2PacketCalcSeqGap(cVar6,cVar2);
    if (((*(byte *)(param_1 + 0xd4) >> 2 & 1) == 0) || ((*(byte *)(lVar16 + 4) >> 6 & 1) == 0)) {
      uVar10 = 0;
    }
    else {
      uVar10 = _iAP2PacketCalcSeqGap(*(undefined1 *)(lVar16 + 6),*(undefined1 *)(param_1 + 0xbe));
    }
    uVar11 = _iAP2LinkIsNoRetransmit(param_1 + 0x19a);
    if (((uVar11 & 1) == 0) && (*(byte *)(param_1 + 0x1a5) < uVar10)) {
      _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),0x13);
LAB_10000b0e8:
      *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 1;
    }
    else {
      bVar3 = *(byte *)(lVar16 + 4);
      if ((bVar3 >> 2 & 1) == 0) {
        if ((char)bVar3 < '\0') {
          if (0xbf < bVar3) goto LAB_10000b068;
          goto LAB_10000b094;
        }
        if (((*(byte *)(param_1 + 0xd4) & 1) == 0) || (uVar8 == 1)) {
LAB_10000b068:
          __AddRecvPckItem(param_1,param_2);
LAB_10000b074:
          iVar9 = 0;
        }
        else {
          if (uVar8 <= *(byte *)(param_1 + 0x19b)) {
            uVar11 = _iAP2PacketIsEAK(param_2);
            if (((uVar11 & 1) != 0) || (uVar11 = _iAP2PacketIsACKOnly(param_2), (uVar11 & 1) != 0))
            goto LAB_10000b094;
            uVar11 = (ulong)*(byte *)(param_1 + 0x1a4);
            if (uVar11 != 0) {
              lVar12 = 0;
              pcVar14 = (char *)0x0;
              do {
                pcVar1 = (char *)(param_1 + 0x1b8 + lVar12 * 4);
                if (*pcVar1 != *(char *)(*(long *)(param_2 + 0x40) + 7)) {
                  pcVar1 = pcVar14;
                }
                lVar12 = lVar12 + 1;
                uVar11 = uVar11 - 1;
                pcVar14 = pcVar1;
              } while (uVar11 != 0);
              if ((pcVar1 != (char *)0x0) && ((pcVar1[3] & 1U) != 0)) goto LAB_10000b094;
            }
            if (uVar8 != 0) goto LAB_10000b03c;
LAB_10000b2b4:
            if (((cVar6 != cVar2) || (uVar11 = _iAP2PacketIsACKOnly(param_2), (uVar11 & 1) != 0)) ||
               (uVar11 = _iAP2LinkIsNoRetransmit(param_1 + 0x19a), (uVar11 & 1) != 0))
            goto LAB_10000b0e8;
            _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),0x10);
            goto LAB_10000b074;
          }
LAB_10000b03c:
          iVar9 = _iAP2LinkIsNoRetransmit(param_1 + 0x19a);
          if (iVar9 != 0) {
            *(int *)(param_1 + 0x230) = *(int *)(param_1 + 0x230) + 1;
            _iAP2LinkSendRST(param_1);
            goto LAB_10000b0e8;
          }
          if (*(byte *)(param_1 + 0x19b) < uVar8) goto LAB_10000b2b4;
          iVar9 = _iAP2PacketRequireACK(param_2);
          if (iVar9 != 0) {
            uVar11 = __IsReceivedPacket(param_1,param_2);
            if ((uVar11 & 1) == 0) {
              *(int *)(param_1 + 0x230) = *(int *)(param_1 + 0x230) + 1;
              __AddRecvPckItem(param_1,param_2);
              if (*(char *)(param_1 + 0xc2) == -1) {
                uVar7 = _iAP2TimeCallbackAfter
                                  (*(undefined8 *)(param_1 + 200),0xd,
                                   *(undefined2 *)(param_1 + 0x1a2));
                iVar9 = 0;
                *(undefined1 *)(param_1 + 0xc2) = uVar7;
                goto LAB_10000b098;
              }
            }
            goto LAB_10000b074;
          }
          iVar9 = _iAP2PacketIsACKOnly(param_2);
        }
      }
      else {
LAB_10000b094:
        iVar9 = 1;
      }
LAB_10000b098:
      if ((*(byte *)(lVar16 + 4) >> 6 & 1) != 0) {
        cVar6 = _iAP2PacketCalcSeqGap(*(undefined1 *)(param_1 + 0xbd),*(undefined1 *)(lVar16 + 6));
        if (((*(byte *)(param_1 + 0xd4) >> 1 & 1) == 0) || (-1 < cVar6)) {
          *(undefined1 *)(param_1 + 0xbd) = *(undefined1 *)(lVar16 + 6);
          *(byte *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) | 2;
          __CleanupAckedPackets(param_1);
        }
      }
      if ((iVar9 != 0) &&
         (uVar11 = _iAP2LinkProcessInOrderPacket(param_1,param_2), (uVar11 & 1) == 0))
      goto LAB_10000b0e8;
    }
    if (*(long *)(param_1 + 0x118) != 0) {
      _iAP2PacketRelease();
    }
    *(undefined8 *)(param_1 + 0x118) = 0;
    param_2 = __GetRecvPckFirstItem(param_1,&local_70);
    while( true ) {
      while( true ) {
        uVar7 = (undefined1)local_70;
        if (param_2 == 0) {
          return;
        }
        lVar12 = __GetRecvPckNextItem(param_1,uVar7,&local_51);
        if ((((*(byte *)(param_1 + 0xd4) & 1) == 0) ||
            (uVar8 = _iAP2PacketCalcSeqGap
                               (*(undefined1 *)(param_1 + 0xbc),
                                *(undefined1 *)(*(long *)(param_2 + 0x40) + 5)),
            (*(byte *)(param_1 + 0xd4) & 1) == 0)) || (uVar8 == 1)) break;
        param_2 = lVar12;
        local_70._0_1_ = local_51;
        if (*(byte *)(param_1 + 0x19b) < uVar8) {
          _iAP2ListArrayDeleteItem(*(undefined8 *)(param_1 + 0x120),uVar7,__DeletePckCB);
          local_70._0_1_ = local_51;
        }
      }
      _iAP2PacketRetain(param_2);
      _iAP2ListArrayDeleteItem(*(undefined8 *)(param_1 + 0x120),uVar7,__DeletePckCB);
      if (*(long *)(param_1 + 0x118) != 0) break;
      *(long *)(param_1 + 0x118) = param_2;
      _iAP2LinkProcessInOrderPacket(param_1,param_2);
      *(undefined8 *)(param_1 + 0x118) = 0;
      _iAP2PacketRelease(param_2);
      param_2 = __GetRecvPckFirstItem(param_1,&local_51);
      local_70._0_1_ = local_51;
    }
    _iAP2LinkHandleReadyPacket_cold_1();
LAB_10000b2f8:
    _iAP2LinkEventNotify_cold_1();
    puVar13 = PTR___os_log_default_10022bbb0;
  }
  iVar9 = _os_log_type_enabled(puVar13,0);
  if (iVar9 == 0) {
    return;
  }
  bVar3 = *(byte *)(lVar16 + 5);
  uVar4 = *(ushort *)(param_2 + 0x36);
  local_70 = (undefined4)DAT_1001b3100;
  local_62 = 0x400;
  local_60 = (uint)*(ushort *)(param_1 + 0x19e);
  pcVar14 = "ERROR: Packet 0x%x has length = %d bytes > maxPacketLength (%d bytes)";
  uVar15 = 0x14;
LAB_10000afd4:
  local_66 = (uint)uVar4;
  local_6c = (uint)bVar3;
  local_68 = 0x400;
  __os_log_impl(0x100000000,puVar13,0,pcVar14,&local_70,uVar15);
  return;
}


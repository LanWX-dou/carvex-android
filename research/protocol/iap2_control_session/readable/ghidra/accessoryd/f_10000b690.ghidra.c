/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000b690
 * original code SHA256: 6297759e11815a9be74f9d60b3768dd1a36e5999301665b8ea8707ea241cf7ca
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 _iAP2LinkProcessInOrderPacket(long param_1,long param_2)

{
  char *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  undefined8 uVar8;
  ulong uVar9;
  undefined4 uVar10;
  char *pcVar11;
  ushort uVar12;
  bool bVar13;
  undefined *puVar14;
  undefined8 uVar15;
  long lVar16;
  undefined8 uVar17;
  char local_80;
  undefined1 uStack_7f;
  char cStack_7e;
  char cStack_7d;
  ushort uStack_7c;
  short sStack_7a;
  short sStack_78;
  char cStack_76;
  undefined1 uStack_75;
  ushort uStack_74;
  undefined2 uStack_72;
  undefined2 uStack_70;
  undefined2 uStack_6e;
  uint uStack_6c;
  undefined8 uStack_68;
  uint local_60;
  undefined2 local_5c;
  ushort local_5a;
  undefined2 uStack_58;
  undefined2 local_56;
  uint local_54;
  undefined2 local_50;
  uint local_4e;
  
  lVar16 = *(long *)(param_2 + 0x40);
  bVar5 = *(byte *)(lVar16 + 4);
  if ((char)bVar5 < '\0') {
    bVar5 = *(byte *)(param_1 + 0xd4);
    if ((bVar5 & 1) == 0) {
      cVar3 = *(char *)(lVar16 + 5);
      uVar10 = 2;
    }
    else {
      cVar3 = *(char *)(lVar16 + 5);
      uVar10 = 2;
      if (*(char *)(param_1 + 0xbc) == cVar3) {
        uVar10 = 3;
      }
    }
    *(char *)(param_1 + 0xbc) = cVar3;
    *(byte *)(param_1 + 0xd4) = bVar5 | 1;
    bVar4 = *(byte *)(lVar16 + 4);
    uVar6 = *(int *)(param_1 + 0x1cc) + 1;
    *(uint *)(param_1 + 0x1cc) = uVar6;
    if ((bVar4 >> 6 & 1) == 0) {
      *(int *)(param_1 + 0x1dc) = *(int *)(param_1 + 0x1dc) + 1;
      *(int *)(param_1 + 0x1e4) = *(int *)(param_1 + 0x1e4) + 1;
    }
    else {
      *(int *)(param_1 + 0x1e0) = *(int *)(param_1 + 0x1e0) + 1;
      *(int *)(param_1 + 0x1e8) = *(int *)(param_1 + 0x1e8) + 1;
    }
    if (((bVar5 >> 5 & 1) == 0) && (10 < uVar6)) {
      _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),0x14);
      goto LAB_10000b8e4;
    }
    uVar12 = 0x16;
    if (*(char *)(param_1 + 0xd5) != '\x02') {
      uVar12 = 0x14;
    }
    if (*(ushort *)(param_2 + 0x36) < uVar12) goto LAB_10000b8e4;
    local_50 = 0xaaaa;
    uStack_68 = &DAT_aaaaaaaaaaaaaaaa;
    uStack_70 = 0xaaaa;
    uStack_6e = 0xaaaa;
    uStack_6c = 0xaaaaaaaa;
    uStack_58 = 0xaaaa;
    local_56 = 0xaaaa;
    local_54 = 0xaaaaaaaa;
    local_60 = 0xaaaaaaaa;
    local_5c = 0xaaaa;
    local_5a = 0xaaaa;
    sStack_78 = -0x5556;
    cStack_76 = -0x56;
    uStack_75 = 0xaa;
    uStack_74 = 0xaaaa;
    uStack_72 = 0xaaaa;
    local_80 = -0x56;
    uStack_7f = 0xaa;
    cStack_7e = -0x56;
    cStack_7d = -0x56;
    uStack_7c = 0xaaaa;
    sStack_7a = -0x5556;
    uVar15 = *(undefined8 *)(param_2 + 0x48);
    uVar8 = _iAP2PacketGetPayloadLen(param_2);
    uVar9 = _iAP2PacketParseSYNData(uVar15,uVar8,&local_80);
    if ((uVar9 & 1) == 0) {
      _iAP2LinkIsNoRetransmit(param_1 + 0x168);
    }
    else {
      iVar7 = _iAP2LinkIsValidSynParam
                        (&local_80,*(undefined1 *)(param_1 + 0xd7),*(long *)(param_1 + 0x160) + 0xe,
                         *(long *)(param_1 + 0x160) + 0x13);
      if (iVar7 != 0) {
        if ((*(byte *)(lVar16 + 4) >> 6 & 1) == 0) {
          uVar8 = *(undefined8 *)(param_1 + 8);
          goto LAB_10000bbb0;
        }
        if ((((local_80 == *(char *)(param_1 + 0x168)) && (sStack_7a == *(short *)(param_1 + 0x16e))
             ) && (sStack_78 == *(short *)(param_1 + 0x170))) &&
           (((cStack_7e == *(char *)(param_1 + 0x16a) && (cStack_7d == *(char *)(param_1 + 0x16b)))
            && (cStack_76 == *(char *)(param_1 + 0x172))))) {
          uVar8 = *(undefined8 *)(param_1 + 8);
          if (*(char *)(lVar16 + 6) == *(char *)(param_1 + 0xbe)) {
            uVar10 = 4;
          }
          else {
            uVar10 = 5;
          }
          goto LAB_10000bbb0;
        }
      }
      iVar7 = _iAP2LinkIsNoRetransmit(param_1 + 0x168);
      if ((iVar7 != 0) && (uVar9 = _iAP2LinkIsNoRetransmit(&local_80), (uVar9 & 1) == 0)) {
        uVar8 = *(undefined8 *)(param_1 + 8);
        uVar10 = 7;
        goto LAB_10000bbb0;
      }
    }
    uVar8 = *(undefined8 *)(param_1 + 8);
    uVar10 = 6;
LAB_10000bbb0:
    _iAP2FSMHandleEvent(uVar8,uVar10);
    return 1;
  }
  if ((bVar5 >> 5 & 1) != 0) {
    uVar12 = 0xc;
    if (*(char *)(param_1 + 0xd5) != '\x02') {
      uVar12 = 10;
    }
    if (uVar12 < *(ushort *)(param_2 + 0x36)) {
      *(int *)(param_1 + 0x234) = *(int *)(param_1 + 0x234) + 1;
      uVar8 = *(undefined8 *)(param_1 + 8);
      uVar10 = 0x11;
      goto LAB_10000bbb0;
    }
LAB_10000b8e4:
    if ((__iAP2LogEnableMask & 1) != 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
        puVar14 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_1();
          puVar14 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar14 = *(undefined **)(_gLogObjects + 0xb0);
      }
      uVar8 = _os_log_type_enabled(puVar14,0);
      if ((int)uVar8 == 0) {
        return uVar8;
      }
      local_80 = (char)DAT_1001b3368;
      uStack_7f = (undefined1)((ulong)DAT_1001b3368 >> 8);
      cStack_7e = (char)((ulong)DAT_1001b3368 >> 0x10);
      cStack_7d = (char)((ulong)DAT_1001b3368 >> 0x18);
      uStack_7c = 0xd143;
      sStack_7a = 0x1c;
      sStack_78 = 1;
      cStack_76 = 0;
      uStack_75 = 0;
      uStack_74 = 0x400;
      uStack_72 = 0x14b8;
      uStack_70 = 0;
      uStack_6e = 0x400;
      uStack_6c = (uint)*(byte *)(lVar16 + 4);
      uStack_68 = (undefined1 *)CONCAT26(0x400,(uint6)CONCAT12(*(undefined1 *)(lVar16 + 5),0x400));
      local_60 = (uint)*(byte *)(param_1 + 0xbe);
      local_5c = 0x400;
      local_5a = (ushort)*(byte *)(param_1 + 0xbd);
      uStack_58 = 0;
      local_56 = 0x400;
      local_54 = (uint)*(byte *)(param_1 + 0xbc);
      local_50 = 0x400;
      local_4e = (uint)*(byte *)(param_1 + 0xbf);
      __os_log_impl(0x100000000,puVar14,0,
                    "ERROR: %s:%d Received Invalid Packet (control=0x%x seq=%u sentSeq=%u recvAck=%u recvSeq=%u sentAck=%u)"
                    ,&local_80,0x36);
    }
    return 0;
  }
  if ((bVar5 >> 2 & 1) != 0) {
    uVar9 = _iAP2LinkProcessInOrderPacketCMD(param_1,param_2);
    if ((uVar9 & 1) != 0) {
      return 1;
    }
    goto LAB_10000b8e4;
  }
  if (bVar5 < 0x40) goto LAB_10000b8e4;
  uVar12 = 0xc;
  if (*(char *)(param_1 + 0xd5) != '\x02') {
    uVar12 = 10;
  }
  if (*(ushort *)(param_2 + 0x36) <= uVar12) {
    uVar12 = 9;
    if (*(char *)(param_1 + 0xd5) == '\x02') {
      uVar12 = 10;
    }
    if (*(ushort *)(param_2 + 0x36) != uVar12) goto LAB_10000b8e4;
    *(int *)(param_1 + 0x23c) = *(int *)(param_1 + 0x23c) + 1;
    local_50 = *(undefined2 *)(param_1 + 0x198);
    uStack_68 = *(undefined1 **)(param_1 + 0x180);
    uVar17 = *(undefined8 *)(param_1 + 0x178);
    uVar15 = *(undefined8 *)(param_1 + 400);
    uVar8 = *(undefined8 *)(param_1 + 0x188);
    uStack_70 = (undefined2)uVar17;
    uStack_6e = (undefined2)((ulong)uVar17 >> 0x10);
    uStack_6c = (uint)((ulong)uVar17 >> 0x20);
    uStack_58 = (undefined2)uVar15;
    local_56 = (undefined2)((ulong)uVar15 >> 0x10);
    local_54 = (uint)((ulong)uVar15 >> 0x20);
    local_60 = (uint)uVar8;
    local_5c = (undefined2)((ulong)uVar8 >> 0x20);
    local_5a = (ushort)((ulong)uVar8 >> 0x30);
    uVar15 = *(undefined8 *)(param_1 + 0x170);
    uVar8 = *(undefined8 *)(param_1 + 0x168);
    sStack_78 = (short)uVar15;
    cStack_76 = (char)((ulong)uVar15 >> 0x10);
    uStack_75 = (undefined1)((ulong)uVar15 >> 0x18);
    uStack_74 = (ushort)((ulong)uVar15 >> 0x20);
    uStack_72 = (undefined2)((ulong)uVar15 >> 0x30);
    local_80 = (char)uVar8;
    cStack_7e = (char)((ulong)uVar8 >> 0x10);
    cStack_7d = (char)((ulong)uVar8 >> 0x18);
    sStack_7a = (short)((ulong)uVar8 >> 0x30);
    uStack_7f = uStack_75;
    uStack_7c = uStack_74;
    lVar16 = *(long *)(param_1 + 8);
    if (*(byte *)(lVar16 + 10) < 5) {
      iVar7 = _iAP2LinkIsValidSynParam
                        (&local_80,*(undefined1 *)(param_1 + 0xd7),*(long *)(param_1 + 0x160) + 0xe,
                         *(long *)(param_1 + 0x160) + 0x13);
      if ((iVar7 != 0) && (uStack_7c <= *(ushort *)(*(long *)(param_1 + 0x160) + 0xc))) {
        lVar16 = *(long *)(param_1 + 8);
        goto LAB_10000bbe0;
      }
      lVar16 = *(long *)(param_1 + 8);
      uVar8 = 0x16;
    }
    else {
LAB_10000bbe0:
      uVar8 = 0x15;
    }
    _iAP2FSMHandleEvent(lVar16,uVar8);
    goto LAB_10000bbe8;
  }
  *(undefined1 *)(param_1 + 0xbc) = *(undefined1 *)(lVar16 + 5);
  *(byte *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) | 1;
  *(int *)(param_1 + 0x240) = *(int *)(param_1 + 0x240) + 1;
  _iAP2FSMHandleEvent(*(undefined8 *)(param_1 + 8),0xf);
  uVar6 = _iAP2PacketCalcSeqGap(*(undefined1 *)(param_1 + 0xbf),*(undefined1 *)(param_1 + 0xbc));
  uVar9 = (ulong)*(byte *)(param_1 + 0x1a4);
  if (uVar9 == 0) {
LAB_10000ba80:
    bVar13 = false;
  }
  else {
    lVar16 = 0;
    pcVar11 = (char *)0x0;
    do {
      pcVar1 = (char *)(param_1 + 0x1b8 + lVar16 * 4);
      if (*pcVar1 != *(char *)(*(long *)(param_2 + 0x40) + 7)) {
        pcVar1 = pcVar11;
      }
      lVar16 = lVar16 + 1;
      uVar9 = uVar9 - 1;
      pcVar11 = pcVar1;
    } while (uVar9 != 0);
    if ((pcVar1 == (char *)0x0) || ((pcVar1[3] & 1U) == 0)) goto LAB_10000ba80;
    bVar13 = true;
  }
  if (4 < *(byte *)(*(long *)(param_1 + 8) + 10)) {
    bVar2 = false;
    if (uVar6 == 0) {
      bVar2 = bVar13;
    }
    if ((('\0' < (char)uVar6) || (bVar2)) &&
       (uVar9 = _iAP2LinkIsNoRetransmit(param_1 + 0x19a), (uVar9 & 1) == 0)) {
      if (uVar6 < *(byte *)(param_1 + 0x19d)) {
        bVar13 = true;
      }
      if (!bVar13) {
        uVar8 = _iAP2PacketCreateACKPacket
                          (param_1,*(undefined1 *)(param_1 + 0xbe),*(undefined1 *)(param_1 + 0xbc),0
                           ,0,0);
        *(int *)(param_1 + 0x24c) = *(int *)(param_1 + 0x24c) + 1;
        __iAP2LinkSendPacketCommon(param_1,uVar8,0,0);
        _iAP2PacketRelease(uVar8);
      }
    }
  }
LAB_10000bbe8:
  _iAP2LinkSignalSendBuffCB(param_1);
  return 1;
}


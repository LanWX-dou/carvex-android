/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100007914
 * original code SHA256: fcded225f787a147e02309452042a5faf85f5b529baed4e4564f9bc5ec091944
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 __iAP2LinkSendPacketCommon(long param_1,long param_2,uint param_3,uint param_4)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  ulong uVar7;
  undefined *puVar8;
  undefined8 uVar9;
  long lVar10;
  undefined8 uVar11;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined2 local_94;
  undefined4 local_92;
  undefined2 uStack_8e;
  undefined2 uStack_8c;
  undefined2 uStack_8a;
  undefined2 local_88;
  undefined2 uStack_86;
  undefined2 local_84;
  uint local_82;
  undefined2 local_7e;
  uint local_7c;
  undefined2 local_78;
  undefined8 local_76;
  undefined2 local_6e;
  uint local_6c;
  undefined2 local_68;
  uint local_66;
  undefined2 local_62;
  uint local_60;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    if ((__iAP2LogEnableMask & 1) != 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        puVar8 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_1();
          puVar8 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar8 = *(undefined **)(_gLogObjects + 0xb0);
      }
      uVar11 = _os_log_type_enabled(puVar8,0);
      if ((int)uVar11 == 0) {
        return uVar11;
      }
      local_a0 = (undefined4)DAT_1001b30e0;
      uStack_9c = 0x1cd286;
      uStack_98 = 1;
      local_94 = 0x400;
      local_92 = 0x1586;
      uStack_8e = 0x400;
      uStack_8c = (undefined2)param_1;
      uStack_8a = 0;
      local_88 = 0x400;
      uStack_86 = (undefined2)param_2;
      local_84 = 0;
      __os_log_impl(0x100000000,puVar8,0,"ERROR: %s:%d Invalid link(%hx) or packet(%hx)",&local_a0,
                    0x1e);
    }
    return 0;
  }
  lVar10 = *(long *)(param_2 + 0x40);
  *(int *)(param_1 + 0x20c) = *(int *)(param_1 + 0x20c) + 1;
  *(uint *)(param_1 + 0x204) = *(int *)(param_1 + 0x204) + (uint)*(ushort *)(param_2 + 0x36);
  if ((*(byte *)(lVar10 + 4) >> 6 & 1) != 0) {
    cVar2 = *(char *)(param_1 + 0xbc);
    cVar3 = *(char *)(lVar10 + 6);
    if (*(char *)(lVar10 + 6) != cVar2) {
      *(char *)(lVar10 + 6) = cVar2;
      cVar3 = cVar2;
    }
    *(char *)(param_1 + 0xbf) = cVar3;
    *(byte *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) | 8;
  }
  iVar6 = _iAP2TimeGetCurTimeMs();
  if (param_3 != 0) {
    uVar11 = *(undefined8 *)(param_1 + 0x254);
    *(undefined8 *)(param_1 + 0x254) =
         CONCAT44((int)((ulong)uVar11 >> 0x20) + 1,(iVar6 - *(int *)(param_2 + 0x30)) + (int)uVar11)
    ;
  }
  *(int *)(param_2 + 0x30) = iVar6;
  if ((*(byte *)(lVar10 + 4) >> 6 & 1) != 0) {
    _iAP2TimeCancelTimer(*(undefined8 *)(param_1 + 200),*(undefined1 *)(param_1 + 0xc2));
    *(undefined1 *)(param_1 + 0xc2) = 0xff;
  }
  if ((param_4 & 1) == 0) {
    _iAP2LinkSendPacketCB(param_1,param_2);
  }
  else {
    _iAP2LinkSendPacketWaitCB();
  }
  uVar7 = _iAP2LinkIsNoRetransmit(param_1 + 0x19a);
  if ((param_3 & 1) != 0) {
    if ((uVar7 & 1) == 0) {
      uVar11 = _iAP2TimeCallbackAfter
                         (*(undefined8 *)(param_1 + 200),0xc,*(undefined2 *)(param_1 + 0x1a0));
      _iAP2PacketAssignTimer(param_2,uVar11);
    }
    return 1;
  }
  if (((uVar7 & 1) == 0) && (iVar6 = _iAP2PacketRequireACK(param_2), iVar6 != 0)) {
    uStack_9c = (undefined4)((ulong)param_2 >> 0x20);
    uVar9 = *(undefined8 *)(param_1 + 0x128);
    local_a0 = (int)param_2;
    uVar11 = _iAP2ListArrayGetLastItemIndex(uVar9);
    iVar6 = _iAP2LinkAddPacketAfter(uVar9,uVar11,&local_a0);
    if (iVar6 == 0xff) {
      if ((__iAP2LogEnableMask & 1) != 0) {
        uVar9 = _logObjectForModule();
        uVar11 = _os_log_type_enabled(uVar9,0);
        if ((int)uVar11 == 0) goto LAB_100007ad0;
        pcVar1 = "Accessory";
        if (*(int *)(param_1 + 0xb8) != 0) {
          pcVar1 = "Device";
        }
        bVar4 = *(byte *)(lVar10 + 5);
        bVar5 = *(byte *)(lVar10 + 4);
        local_76 = _iAP2PacketName(param_2);
        local_a0 = (undefined4)DAT_1001b3370;
        uStack_9c = SUB84(pcVar1,0);
        uStack_98 = (undefined4)((ulong)pcVar1 >> 0x20);
        local_94 = 0x820;
        local_92 = 0x1cd286;
        uStack_8e = 1;
        uStack_8c = 0;
        uStack_8a = 0x400;
        local_88 = 0x1551;
        uStack_86 = 0;
        local_84 = 0x400;
        local_82 = (uint)bVar4;
        local_7e = 0x400;
        local_7c = (uint)bVar5;
        local_78 = 0x820;
        local_6e = 0x400;
        local_6c = (uint)*(byte *)(lVar10 + 6);
        local_68 = 0x400;
        local_66 = (uint)*(ushort *)(param_2 + 0x36);
        local_62 = 0x400;
        local_60 = param_4;
        __os_log_impl(0x100000000,uVar9,0,
                      "ERROR: %s:%s:%d FAILED to add packet to sendPckList, sentSeq(%u) control=%xh(%s) ack=%u len=%u bWaitSend=%d"
                      ,&local_a0,0x44);
      }
      uVar11 = 0;
      goto LAB_100007ad0;
    }
    uVar11 = _iAP2TimeCallbackAfter
                       (*(undefined8 *)(param_1 + 200),0xc,*(undefined2 *)(param_1 + 0x1a0));
    _iAP2PacketAssignTimer(param_2,uVar11);
  }
  uVar11 = 1;
LAB_100007ad0:
  *(undefined1 *)(param_1 + 0xbe) = *(undefined1 *)(lVar10 + 5);
  *(byte *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) | 4;
  return uVar11;
}


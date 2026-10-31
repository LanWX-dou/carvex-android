/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100030054
 * original code SHA256: a486f03f1f3ae3d12fc169d74f45938c8edf525dd1dc85c32b398069f36e0338
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000100030324) */
/* WARNING: Removing unreachable block (ram,0x000100030290) */
/* WARNING: Removing unreachable block (ram,0x00010003020c) */
/* WARNING: Removing unreachable block (ram,0x000100030118) */

void _iAP2LinkDeviceActionHandleMaxRetries(long param_1,undefined1 *param_2)

{
  code *pcVar1;
  int iVar2;
  undefined8 uVar3;
  undefined1 *puVar4;
  undefined8 in_x6;
  undefined8 in_x7;
  undefined8 *puVar5;
  long lVar6;
  undefined8 unaff_x20;
  ulong unaff_x30;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined1 auVar12 [16];
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionHandleMaxRetries_cold_2();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100030090);
      (*pcVar1)();
    }
    _iAP2LinkEventNotify(*(undefined8 *)(param_1 + 0x10),6,0);
    return;
  }
  auVar12 = _iAP2LinkDeviceActionHandleMaxRetries_cold_1();
  if (auVar12._0_8_ == 0) {
    _iAP2LinkDeviceActionNotifyConnection_cold_2();
  }
  else if (auVar12._8_8_ != (undefined1 *)0x0) {
    *auVar12._8_8_ = 0x1d;
    lVar6 = *(long *)(auVar12._0_8_ + 0x10);
    *(undefined2 *)(lVar6 + 0x1ca) = *(undefined2 *)(lVar6 + 0x198);
    *(undefined8 *)(lVar6 + 0x1a2) = *(undefined8 *)(lVar6 + 0x170);
    *(undefined8 *)(lVar6 + 0x19a) = *(undefined8 *)(lVar6 + 0x168);
    *(undefined8 *)(lVar6 + 0x1b2) = *(undefined8 *)(lVar6 + 0x180);
    *(undefined8 *)(lVar6 + 0x1aa) = *(undefined8 *)(lVar6 + 0x178);
    *(undefined8 *)(lVar6 + 0x1c2) = *(undefined8 *)(lVar6 + 400);
    *(undefined8 *)(lVar6 + 0x1ba) = *(undefined8 *)(lVar6 + 0x188);
    *(undefined1 *)(lVar6 + 0xd6) = *(undefined1 *)(lVar6 + 0xd5);
    *(undefined1 *)(lVar6 + 0xd5) = *(undefined1 *)(lVar6 + 0x19a);
    _iAP2LinkEventNotify(lVar6,2);
    _iAP2LinkConnectedCB(lVar6,1);
    return;
  }
  auVar12 = _iAP2LinkDeviceActionNotifyConnection_cold_1();
  puVar4 = auVar12._8_8_;
  if (auVar12._0_8_ == 0) {
    _iAP2LinkDeviceActionSendRSTWithNewChecksumEnabled_cold_2();
  }
  else {
    unaff_x20 = 0;
    if (puVar4 != (undefined1 *)0x0) {
      *puVar4 = 0x1d;
      lVar6 = *(long *)(auVar12._0_8_ + 0x10);
      *(undefined1 *)(lVar6 + 0xd6) = *(undefined1 *)(lVar6 + 0xd5);
      *(undefined1 *)(lVar6 + 0xd5) = *(undefined1 *)(lVar6 + 0x19a);
      _iAP2LinkResetSeqAck(lVar6,0,0);
      _iAP2LinkSetDefaultSYNParam(lVar6 + 0x19a);
      puVar5 = *(undefined8 **)(lVar6 + 0x160);
      uVar9 = puVar5[3];
      uVar8 = puVar5[2];
      uVar7 = puVar5[5];
      uVar3 = puVar5[4];
      uVar11 = puVar5[1];
      uVar10 = *puVar5;
      *(undefined2 *)(lVar6 + 0x198) = *(undefined2 *)(puVar5 + 6);
      *(undefined8 *)(lVar6 + 0x180) = uVar9;
      *(undefined8 *)(lVar6 + 0x178) = uVar8;
      *(undefined8 *)(lVar6 + 400) = uVar7;
      *(undefined8 *)(lVar6 + 0x188) = uVar3;
      *(undefined8 *)(lVar6 + 0x170) = uVar11;
      *(undefined8 *)(lVar6 + 0x168) = uVar10;
      if (((*(byte *)(lVar6 + 0xd4) >> 5 & 1) == 0) && (10 < *(uint *)(lVar6 + 0x1d0))) {
        *puVar4 = 0x14;
        return;
      }
      uVar3 = _iAP2PacketCreateRSTPacket(lVar6,*(undefined1 *)(lVar6 + 0xbe));
      *(int *)(lVar6 + 0x248) = *(int *)(lVar6 + 0x248) + 1;
      _iAP2LinkSendPacket(lVar6,uVar3,0,"Device:SendRST");
      _iAP2PacketRelease(uVar3);
      return;
    }
  }
  auVar12 = _iAP2LinkDeviceActionSendRSTWithNewChecksumEnabled_cold_1();
  if (auVar12._0_8_ == 0) {
    _iAP2LinkDeviceActionSendSuspend_cold_2();
  }
  else if (auVar12._8_8_ != (undefined1 *)0x0) {
    *auVar12._8_8_ = 0x1d;
    lVar6 = *(long *)(auVar12._0_8_ + 0x10);
    _iAP2LinkEventNotify(lVar6,7,lVar6 + 0x168);
    uVar3 = _iAP2PacketCreateSUSPacket(lVar6,*(undefined1 *)(lVar6 + 0xbe));
    _iAP2LinkSendPacketWaitSend(lVar6,uVar3,0,"Device:SendSuspend");
    _iAP2PacketRelease(uVar3);
    return;
  }
  auVar12 = _iAP2LinkDeviceActionSendSuspend_cold_1();
  if (auVar12._0_8_ == 0) {
    _iAP2LinkDeviceActionSendResume_cold_2();
  }
  else if (auVar12._8_8_ != (undefined1 *)0x0) {
    *auVar12._8_8_ = 0x1d;
    lVar6 = *(long *)(auVar12._0_8_ + 0x10);
    _iAP2LinkEventNotify(lVar6,8,lVar6 + 0x168);
    uVar3 = _iAP2PacketCreateACKPacket
                      (lVar6,*(undefined1 *)(lVar6 + 0xbe),*(undefined1 *)(lVar6 + 0xbc),0,0,0,in_x6
                       ,in_x7,unaff_x20);
    _iAP2LinkSendPacket(lVar6,uVar3,0,"Device:SendACK(Resume)");
    _iAP2PacketRelease(uVar3);
    return;
  }
  _iAP2LinkDeviceActionSendResume_cold_1();
  iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
  if (iVar2 != 0) {
    ___logObjectForModule_block_invoke_cold_1();
  }
  return;
}


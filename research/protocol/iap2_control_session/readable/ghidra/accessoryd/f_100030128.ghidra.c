/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100030128
 * original code SHA256: e67e44fe6ab54f100ef018f17a49de09444d1d3cb6484ce16ea298d5f4944fee
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000100030324) */
/* WARNING: Removing unreachable block (ram,0x000100030290) */

void _iAP2LinkDeviceActionSendRSTWithNewChecksumEnabled(long param_1,undefined1 *param_2)

{
  code *pcVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 in_x6;
  undefined8 in_x7;
  undefined8 *puVar4;
  long lVar5;
  undefined8 unaff_x20;
  ulong unaff_x30;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined1 auVar11 [16];
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionSendRSTWithNewChecksumEnabled_cold_2();
  }
  else {
    unaff_x20 = 0;
    if (param_2 != (undefined1 *)0x0) {
      *param_2 = 0x1d;
      lVar5 = *(long *)(param_1 + 0x10);
      *(undefined1 *)(lVar5 + 0xd6) = *(undefined1 *)(lVar5 + 0xd5);
      *(undefined1 *)(lVar5 + 0xd5) = *(undefined1 *)(lVar5 + 0x19a);
      _iAP2LinkResetSeqAck(lVar5,0,0);
      _iAP2LinkSetDefaultSYNParam(lVar5 + 0x19a);
      puVar4 = *(undefined8 **)(lVar5 + 0x160);
      uVar8 = puVar4[3];
      uVar7 = puVar4[2];
      uVar6 = puVar4[5];
      uVar3 = puVar4[4];
      uVar10 = puVar4[1];
      uVar9 = *puVar4;
      *(undefined2 *)(lVar5 + 0x198) = *(undefined2 *)(puVar4 + 6);
      *(undefined8 *)(lVar5 + 0x180) = uVar8;
      *(undefined8 *)(lVar5 + 0x178) = uVar7;
      *(undefined8 *)(lVar5 + 400) = uVar6;
      *(undefined8 *)(lVar5 + 0x188) = uVar3;
      *(undefined8 *)(lVar5 + 0x170) = uVar10;
      *(undefined8 *)(lVar5 + 0x168) = uVar9;
      if (((*(byte *)(lVar5 + 0xd4) >> 5 & 1) == 0) && (10 < *(uint *)(lVar5 + 0x1d0))) {
        *param_2 = 0x14;
        return;
      }
      uVar3 = _iAP2PacketCreateRSTPacket(lVar5,*(undefined1 *)(lVar5 + 0xbe));
      *(int *)(lVar5 + 0x248) = *(int *)(lVar5 + 0x248) + 1;
      _iAP2LinkSendPacket(lVar5,uVar3,0,"Device:SendRST");
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100030210);
        (*pcVar1)();
      }
      _iAP2PacketRelease(uVar3);
      return;
    }
  }
  auVar11 = _iAP2LinkDeviceActionSendRSTWithNewChecksumEnabled_cold_1();
  if (auVar11._0_8_ == 0) {
    _iAP2LinkDeviceActionSendSuspend_cold_2();
  }
  else if (auVar11._8_8_ != (undefined1 *)0x0) {
    *auVar11._8_8_ = 0x1d;
    lVar5 = *(long *)(auVar11._0_8_ + 0x10);
    _iAP2LinkEventNotify(lVar5,7,lVar5 + 0x168);
    uVar3 = _iAP2PacketCreateSUSPacket(lVar5,*(undefined1 *)(lVar5 + 0xbe));
    _iAP2LinkSendPacketWaitSend(lVar5,uVar3,0,"Device:SendSuspend");
    _iAP2PacketRelease(uVar3);
    return;
  }
  auVar11 = _iAP2LinkDeviceActionSendSuspend_cold_1();
  if (auVar11._0_8_ == 0) {
    _iAP2LinkDeviceActionSendResume_cold_2();
  }
  else if (auVar11._8_8_ != (undefined1 *)0x0) {
    *auVar11._8_8_ = 0x1d;
    lVar5 = *(long *)(auVar11._0_8_ + 0x10);
    _iAP2LinkEventNotify(lVar5,8,lVar5 + 0x168);
    uVar3 = _iAP2PacketCreateACKPacket
                      (lVar5,*(undefined1 *)(lVar5 + 0xbe),*(undefined1 *)(lVar5 + 0xbc),0,0,0,in_x6
                       ,in_x7,unaff_x20);
    _iAP2LinkSendPacket(lVar5,uVar3,0,"Device:SendACK(Resume)");
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


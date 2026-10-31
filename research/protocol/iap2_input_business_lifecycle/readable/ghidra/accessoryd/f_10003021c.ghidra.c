/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10003021c
 * original code SHA256: de94733fbd209a797e8f4f3985a348029563b1da5d315eb8058234bc2c89c83d
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000100030324) */

void _iAP2LinkDeviceActionSendSuspend(long param_1,undefined1 *param_2)

{
  code *pcVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  ulong unaff_x30;
  undefined1 auVar5 [16];
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionSendSuspend_cold_2();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    lVar4 = *(long *)(param_1 + 0x10);
    _iAP2LinkEventNotify(lVar4,7,lVar4 + 0x168);
    uVar3 = _iAP2PacketCreateSUSPacket(lVar4,*(undefined1 *)(lVar4 + 0xbe));
    _iAP2LinkSendPacketWaitSend(lVar4,uVar3,0,"Device:SendSuspend");
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
      _iAP2PacketRelease(uVar3);
      return;
    }
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100030294);
    (*pcVar1)();
  }
  auVar5 = _iAP2LinkDeviceActionSendSuspend_cold_1();
  if (auVar5._0_8_ == 0) {
    _iAP2LinkDeviceActionSendResume_cold_2();
  }
  else if (auVar5._8_8_ != (undefined1 *)0x0) {
    *auVar5._8_8_ = 0x1d;
    lVar4 = *(long *)(auVar5._0_8_ + 0x10);
    _iAP2LinkEventNotify(lVar4,8,lVar4 + 0x168);
    uVar3 = _iAP2PacketCreateACKPacket
                      (lVar4,*(undefined1 *)(lVar4 + 0xbe),*(undefined1 *)(lVar4 + 0xbc),0,0,0);
    _iAP2LinkSendPacket(lVar4,uVar3,0,"Device:SendACK(Resume)");
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


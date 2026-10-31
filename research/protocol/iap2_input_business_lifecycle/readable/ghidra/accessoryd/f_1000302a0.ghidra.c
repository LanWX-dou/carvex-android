/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000302a0
 * original code SHA256: c66bc54a90a19dadca39e2b53536bfae0f8a7ac7ad5bcca9075a9f20f608421c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkDeviceActionSendResume(long param_1,undefined1 *param_2)

{
  code *pcVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  ulong unaff_x30;
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionSendResume_cold_2();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    lVar4 = *(long *)(param_1 + 0x10);
    _iAP2LinkEventNotify(lVar4,8,lVar4 + 0x168);
    uVar3 = _iAP2PacketCreateACKPacket
                      (lVar4,*(undefined1 *)(lVar4 + 0xbe),*(undefined1 *)(lVar4 + 0xbc),0,0,0);
    _iAP2LinkSendPacket(lVar4,uVar3,0,"Device:SendACK(Resume)");
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100030328);
      (*pcVar1)();
    }
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


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002feb0
 * original code SHA256: 2913796d158dd6965c9e4247715328638569a5d69b3a3fe5f548d183811d9e3b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkDeviceActionResendSYNACK(long param_1,undefined1 *param_2)

{
  int iVar1;
  ulong uVar2;
  undefined1 *unaff_x19;
  long unaff_x20;
  long unaff_x21;
  undefined *puVar3;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  uint local_42;
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionResendSYNACK_cold_3();
LAB_100030048:
    _iAP2LinkDeviceActionResendSYNACK_cold_2();
LAB_10003004c:
    _iAP2LinkDeviceActionSendSYNACK_cold_1();
    puVar3 = PTR___os_log_default_10022bbb0;
LAB_10002ffc4:
    iVar1 = _os_log_type_enabled(puVar3,0);
    if (iVar1 != 0) {
      local_50 = (undefined4)DAT_1001b3098;
      local_4c = "Device:ResendSYNACK";
      local_44 = 0x400;
      local_42 = (uint)*(byte *)(unaff_x21 + 0x19c);
      __os_log_impl(0x100000000,puVar3,0,"ERROR: %s Resend too many times! max=%d",&local_50,0x12);
    }
  }
  else {
    unaff_x19 = param_2;
    if (param_2 == (undefined1 *)0x0) goto LAB_100030048;
    *param_2 = 0x1d;
    unaff_x21 = *(long *)(param_1 + 0x10);
    if ((*(byte *)(unaff_x21 + 0xd4) >> 2 & 1) == 0) {
      uVar2 = _iAP2LinkGetNewSeqNum(unaff_x21);
      *(char *)(unaff_x21 + 0xbe) = (char)uVar2;
      *(byte *)(unaff_x21 + 0xd4) = *(byte *)(unaff_x21 + 0xd4) | 4;
    }
    else {
      uVar2 = (ulong)*(byte *)(unaff_x21 + 0xbe);
    }
    unaff_x20 = _iAP2PacketCreateSYNPacket(unaff_x21,uVar2,unaff_x21 + 0xbc,unaff_x21 + 0x168);
    if (((*(byte *)(unaff_x21 + 0xd4) >> 5 & 1) != 0) ||
       (*(uint *)(unaff_x21 + 0x1d8) < (uint)*(byte *)(unaff_x21 + 0x19c))) {
      iVar1 = *(uint *)(unaff_x21 + 0x1d8) + 1;
      *(int *)(unaff_x21 + 0x1d8) = iVar1;
      *(int *)(unaff_x21 + 0x200) = *(int *)(unaff_x21 + 0x200) + 1;
      *(int *)(unaff_x21 + 0x224) = *(int *)(unaff_x21 + 0x224) + 1;
      *(char *)(unaff_x20 + 0x3a) = (char)iVar1;
      _iAP2LinkSendPacket(unaff_x21,unaff_x20,0,"Device:ResendSYNACK");
      goto LAB_100030028;
    }
    if ((__iAP2LogEnableMask & 1) != 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
        puVar3 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken == -1) goto LAB_10002ffc4;
        goto LAB_10003004c;
      }
      puVar3 = *(undefined **)(_gLogObjects + 0xb0);
      goto LAB_10002ffc4;
    }
  }
  *unaff_x19 = 0x14;
LAB_100030028:
  _iAP2PacketRelease(unaff_x20);
  return;
}


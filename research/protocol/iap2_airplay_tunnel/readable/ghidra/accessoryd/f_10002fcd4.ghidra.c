/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002fcd4
 * original code SHA256: 1acc6ed15a8523c36882bde87af30dbd78a8fd9bc4aca0e9ac1d0484ffe3dff8
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkDeviceActionSendSYNACK(long param_1,undefined1 *param_2)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  undefined1 *unaff_x19;
  long unaff_x20;
  undefined8 uVar5;
  undefined *puVar6;
  undefined2 local_80 [8];
  undefined1 *local_70;
  undefined1 *puStack_68;
  undefined1 *local_60;
  undefined1 *puStack_58;
  undefined1 *local_50;
  undefined1 *puStack_48;
  undefined2 local_40;
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionSendSYNACK_cold_3();
LAB_10002fea4:
    _iAP2LinkDeviceActionSendSYNACK_cold_2();
LAB_10002fea8:
    _iAP2LinkDeviceActionSendSYNACK_cold_1();
    puVar6 = PTR___os_log_default_10022bbb0;
LAB_10002fd98:
    iVar3 = _os_log_type_enabled(puVar6,0);
    if (iVar3 != 0) {
      local_80[0] = 0;
      __os_log_impl(0x100000000,puVar6,0,
                    "ERROR: Expected recvPck, just use previous negotiatedParam for now.",local_80,2
                   );
    }
  }
  else {
    unaff_x19 = param_2;
    if (param_2 == (undefined1 *)0x0) goto LAB_10002fea4;
    local_40 = 0xaaaa;
    puStack_58 = &DAT_aaaaaaaaaaaaaaaa;
    local_60 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_48 = &DAT_aaaaaaaaaaaaaaaa;
    local_50 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_68 = &DAT_aaaaaaaaaaaaaaaa;
    local_70 = &DAT_aaaaaaaaaaaaaaaa;
    *param_2 = 0x1d;
    unaff_x20 = *(long *)(param_1 + 0x10);
    if (*(long *)(unaff_x20 + 0x118) != 0) {
      uVar5 = *(undefined8 *)(*(long *)(unaff_x20 + 0x118) + 0x48);
      uVar4 = _iAP2PacketGetPayloadLen();
      iVar3 = _iAP2PacketParseSYNData(uVar5,uVar4,&local_70);
      if (iVar3 != 0) {
        _iAP2LinkCheckNegotiation(unaff_x20,&local_70);
      }
      goto LAB_10002fdec;
    }
    if ((__iAP2LogEnableMask & 1) != 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
        puVar6 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken == -1) goto LAB_10002fd98;
        goto LAB_10002fea8;
      }
      puVar6 = *(undefined **)(_gLogObjects + 0xb0);
      goto LAB_10002fd98;
    }
  }
  local_40 = *(undefined2 *)(unaff_x20 + 0x198);
  puStack_68 = *(undefined1 **)(unaff_x20 + 0x170);
  local_70 = *(undefined1 **)(unaff_x20 + 0x168);
  puStack_58 = *(undefined1 **)(unaff_x20 + 0x180);
  local_60 = *(undefined1 **)(unaff_x20 + 0x178);
  puStack_48 = *(undefined1 **)(unaff_x20 + 400);
  local_50 = *(undefined1 **)(unaff_x20 + 0x188);
LAB_10002fdec:
  if ((*(byte *)(unaff_x20 + 0xd4) >> 2 & 1) == 0) {
    cVar2 = _iAP2LinkGetNewSeqNum(unaff_x20);
    *(char *)(unaff_x20 + 0xbe) = cVar2;
    *(byte *)(unaff_x20 + 0xd4) = *(byte *)(unaff_x20 + 0xd4) | 4;
  }
  else {
    cVar2 = *(char *)(unaff_x20 + 0xbe);
  }
  uVar4 = _iAP2PacketCreateSYNPacket(unaff_x20,cVar2 + '\x01',unaff_x20 + 0xbc,unaff_x20 + 0x168);
  uVar1 = *(int *)(unaff_x20 + 0x1d0) + 1;
  *(uint *)(unaff_x20 + 0x1d0) = uVar1;
  *(int *)(unaff_x20 + 0x1f0) = *(int *)(unaff_x20 + 0x1f0) + 1;
  *(int *)(unaff_x20 + 0x1f8) = *(int *)(unaff_x20 + 0x1f8) + 1;
  if (((*(byte *)(unaff_x20 + 0xd4) >> 5 & 1) == 0) && (10 < uVar1)) {
    *unaff_x19 = 0x14;
  }
  _iAP2LinkSendPacket(unaff_x20,uVar4,0,"Device:SendSYNACK");
  _iAP2PacketRelease(uVar4);
  return;
}


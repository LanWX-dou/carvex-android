/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002f920
 * original code SHA256: 2351a8e9ede055cea604c1bbe391937bbdbb00508eccf511e1e0effc0ec827d6
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x00010002fb44) */

void _iAP2LinkDeviceActionSendResetSYNACK(long param_1,undefined1 *param_2)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  long lVar6;
  long lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined1 auVar13 [16];
  undefined1 *local_80;
  undefined1 *puStack_78;
  undefined1 *local_70;
  undefined1 *puStack_68;
  undefined1 *local_60;
  undefined1 *puStack_58;
  undefined2 local_50;
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionSendResetSYNACK_cold_2();
  }
  else if (param_2 != (undefined1 *)0x0) {
    local_50 = 0xaaaa;
    puStack_68 = &DAT_aaaaaaaaaaaaaaaa;
    local_70 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_58 = &DAT_aaaaaaaaaaaaaaaa;
    local_60 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_78 = &DAT_aaaaaaaaaaaaaaaa;
    local_80 = &DAT_aaaaaaaaaaaaaaaa;
    *param_2 = 0x1d;
    lVar6 = *(long *)(param_1 + 0x10);
    cVar2 = _iAP2LinkGetNewSeqNum(lVar6);
    _iAP2LinkConnectedCB(lVar6,0);
    lVar7 = *(long *)(lVar6 + 0x118);
    if (lVar7 == 0) {
      local_50 = *(undefined2 *)(lVar6 + 0x198);
      puStack_78 = *(undefined1 **)(lVar6 + 0x170);
      local_80 = *(undefined1 **)(lVar6 + 0x168);
      puStack_68 = *(undefined1 **)(lVar6 + 0x180);
      local_70 = *(undefined1 **)(lVar6 + 0x178);
      puStack_58 = *(undefined1 **)(lVar6 + 400);
      local_60 = *(undefined1 **)(lVar6 + 0x188);
    }
    else {
      _iAP2LinkSetDefaultSYNParam(lVar6 + 0x19a);
      _iAP2LinkResetSeqAck(lVar6,1,0);
      puVar5 = *(undefined8 **)(lVar6 + 0x160);
      uVar10 = puVar5[3];
      uVar9 = puVar5[2];
      uVar8 = puVar5[5];
      uVar4 = puVar5[4];
      uVar12 = puVar5[1];
      uVar11 = *puVar5;
      *(undefined2 *)(lVar6 + 0x198) = *(undefined2 *)(puVar5 + 6);
      *(undefined8 *)(lVar6 + 0x180) = uVar10;
      *(undefined8 *)(lVar6 + 0x178) = uVar9;
      *(undefined8 *)(lVar6 + 400) = uVar8;
      *(undefined8 *)(lVar6 + 0x188) = uVar4;
      *(undefined8 *)(lVar6 + 0x170) = uVar12;
      *(undefined8 *)(lVar6 + 0x168) = uVar11;
      uVar8 = *(undefined8 *)(lVar7 + 0x48);
      uVar4 = _iAP2PacketGetPayloadLen(lVar7);
      iVar3 = _iAP2PacketParseSYNData(uVar8,uVar4,&local_80);
      if (iVar3 != 0) {
        _iAP2LinkCheckNegotiation(lVar6,&local_80);
      }
    }
    _iAP2LinkResetSend(lVar6);
    if ((*(byte *)(lVar6 + 0xd4) >> 2 & 1) == 0) {
      *(char *)(lVar6 + 0xbe) = cVar2;
      *(byte *)(lVar6 + 0xd4) = *(byte *)(lVar6 + 0xd4) | 4;
    }
    else {
      cVar2 = *(char *)(lVar6 + 0xbe);
    }
    uVar4 = _iAP2PacketCreateSYNPacket(lVar6,cVar2 + '\x01',lVar6 + 0xbc,lVar6 + 0x168);
    uVar1 = *(int *)(lVar6 + 0x1d0) + 1;
    *(uint *)(lVar6 + 0x1d0) = uVar1;
    *(int *)(lVar6 + 0x1f0) = *(int *)(lVar6 + 0x1f0) + 1;
    *(int *)(lVar6 + 0x1f8) = *(int *)(lVar6 + 0x1f8) + 1;
    if (((*(byte *)(lVar6 + 0xd4) >> 5 & 1) == 0) && (10 < uVar1)) {
      *param_2 = 0x14;
    }
    _iAP2LinkSendPacket(lVar6,uVar4,0,"Device:SendSYNACK");
    _iAP2PacketRelease(uVar4);
    return;
  }
  auVar13 = _iAP2LinkDeviceActionSendResetSYNACK_cold_1();
  if (auVar13._0_8_ == 0) {
    _iAP2LinkDeviceActionSendDetect_cold_2();
  }
  else if (auVar13._8_8_ != (undefined1 *)0x0) {
    *auVar13._8_8_ = 0x1d;
    lVar6 = *(long *)(auVar13._0_8_ + 0x10);
    _iAP2LinkResetSeqAck(lVar6,0,1);
    puVar5 = *(undefined8 **)(lVar6 + 0x160);
    uVar10 = puVar5[3];
    uVar9 = puVar5[2];
    uVar8 = puVar5[5];
    uVar4 = puVar5[4];
    uVar12 = puVar5[1];
    uVar11 = *puVar5;
    *(undefined2 *)(lVar6 + 0x198) = *(undefined2 *)(puVar5 + 6);
    *(undefined8 *)(lVar6 + 0x180) = uVar10;
    *(undefined8 *)(lVar6 + 0x178) = uVar9;
    *(undefined8 *)(lVar6 + 400) = uVar8;
    *(undefined8 *)(lVar6 + 0x188) = uVar4;
    *(undefined8 *)(lVar6 + 0x170) = uVar12;
    *(undefined8 *)(lVar6 + 0x168) = uVar11;
    _iAP2LinkConnectedCB(lVar6,0);
    _iAP2LinkSendDetectCB(lVar6,0);
    return;
  }
                    /* WARNING: Subroutine does not return */
  _iAP2LinkDeviceActionSendDetect_cold_1();
}


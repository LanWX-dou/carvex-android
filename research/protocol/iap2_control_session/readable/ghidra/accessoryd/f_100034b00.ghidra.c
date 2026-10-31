/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034b00
 * original code SHA256: b8ebe7f5f8f1a87fb68899563df475ce8e872bf767c127c9792f667274191a8e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkSendRST(long param_1)

{
  code *pcVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  ulong unaff_x30;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  
  _iAP2LinkConnectedCB(param_1,0);
  _iAP2LinkResetSeqAck(param_1,0,0);
  *(undefined4 *)(param_1 + 0x19e) = 0x3e8ffff;
  *(undefined2 *)(param_1 + 0x1a2) = 10;
  *(int *)(param_1 + 0x19a) = (int)DAT_1001b3348;
  *(undefined4 *)(param_1 + 0x1a4) = 0xffff0100;
  puVar3 = *(undefined8 **)(param_1 + 0x160);
  uVar6 = puVar3[3];
  uVar5 = puVar3[2];
  uVar4 = puVar3[5];
  uVar2 = puVar3[4];
  uVar8 = puVar3[1];
  uVar7 = *puVar3;
  *(undefined2 *)(param_1 + 0x198) = *(undefined2 *)(puVar3 + 6);
  *(undefined8 *)(param_1 + 0x180) = uVar6;
  *(undefined8 *)(param_1 + 0x178) = uVar5;
  *(undefined8 *)(param_1 + 400) = uVar4;
  *(undefined8 *)(param_1 + 0x188) = uVar2;
  *(undefined8 *)(param_1 + 0x170) = uVar8;
  *(undefined8 *)(param_1 + 0x168) = uVar7;
  uVar2 = _iAP2PacketCreateRSTPacket(param_1,*(undefined1 *)(param_1 + 0xbe));
  __iAP2LinkSendPacketCommon(param_1,uVar2,0,0);
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100034bb8);
    (*pcVar1)();
  }
  _iAP2PacketRelease(uVar2);
  return;
}


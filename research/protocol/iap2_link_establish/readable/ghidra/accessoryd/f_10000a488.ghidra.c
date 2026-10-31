/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000a488
 * original code SHA256: 1816308f944c7b4938e68199d8fea66d8fee0a8cf881cbd54034391c0a56bdaf
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


long * _iAP2PacketCreateEmptyRecvPacket(long param_1)

{
  undefined4 uVar1;
  long *plVar2;
  undefined8 uVar3;
  
  uVar3 = *(undefined8 *)(param_1 + 0xf0);
  uVar1 = _iAP2LinkGetMaxRecvPayloadSize(param_1,0);
  plVar2 = (long *)_iAP2BuffPoolGetPacketBuffer(uVar3,uVar1);
  if (plVar2 != (long *)0x0) {
    *(undefined2 *)((long)plVar2 + 0x3b) = 0x1ff;
    *(undefined1 *)((long)plVar2 + 0x3f) = 0;
    plVar2[1] = 0;
    plVar2[2] = 0;
    *plVar2 = param_1;
    *(ushort *)((long)plVar2 + 0x3d) = *(ushort *)((long)plVar2 + 0x3d) & 0xf5ff;
    plVar2[4] = 0;
    ___iAP2PacketResetPacket(plVar2);
  }
  return plVar2;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000626c
 * original code SHA256: 993796977463e21526fc6596cdc7535e7ae7485f503ad5422da3e911de82b9ea
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long * _iAP2PacketCreateEmptySendPacket(long param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  
  plVar4 = (long *)0x0;
  if ((param_1 != 0) && (param_2 != (uint *)0x0)) {
    uVar2 = _iAP2LinkGetMaxSendPayloadSize(param_1,0);
    uVar1 = *param_2;
    if (((uVar1 == 0) || (uVar3 = uVar1, uVar2 <= uVar1)) && (uVar3 = uVar2, uVar2 < uVar1)) {
      *param_2 = uVar2;
    }
    plVar4 = (long *)_iAP2BuffPoolGetPacketBuffer(*(undefined8 *)(param_1 + 0xf8),uVar3);
    if (plVar4 != (long *)0x0) {
      *(undefined2 *)((long)plVar4 + 0x3b) = 0x1ff;
      *(undefined1 *)((long)plVar4 + 0x3f) = 0;
      plVar4[1] = 0;
      plVar4[2] = 0;
      *plVar4 = param_1;
      *(ushort *)((long)plVar4 + 0x3d) = *(ushort *)((long)plVar4 + 0x3d) & 0xf7ff | 0x200;
      plVar4[4] = 0;
      ___iAP2PacketResetPacket(plVar4);
    }
  }
  return plVar4;
}


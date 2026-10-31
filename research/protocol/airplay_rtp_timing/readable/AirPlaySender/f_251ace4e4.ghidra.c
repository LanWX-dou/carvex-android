/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ace4e4
 * original code SHA256: baefb14e31dbf082d378c2282f7d894b4d3d516f419e5dfd31bab509229685c5
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _APSRTPPacketHandlerGetExtendedHeaderOfPacket(long param_1,uint param_2,uint *param_3)

{
  long lVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  
  if (*(long *)(param_1 + 0xa8) == 0) {
    _APSRTPPacketHandlerGetExtendedHeaderOfPacket_cold_1();
    return;
  }
  lVar1 = *(long *)(param_1 + 0xa8) + 0xc;
  bVar3 = *(byte *)(lVar1 + (ulong)param_2 * 4);
  *param_3 = (uint)bVar3;
  if (-1 < (char)bVar3) {
    return;
  }
  uVar2 = *(uint *)(lVar1 + (ulong)param_2 * 4);
  uVar2 = (uVar2 & 0xff00ff00) >> 8 | (uVar2 & 0xff00ff) << 8;
  uVar4 = uVar2 >> 0x10;
  *param_3 = (uVar4 | uVar2 << 0x10) >> 2 & 0x3fff00 | uVar4 << 0x16 | (uint)bVar3;
  return;
}


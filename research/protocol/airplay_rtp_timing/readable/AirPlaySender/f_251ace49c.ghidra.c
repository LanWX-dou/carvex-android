/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ace49c
 * original code SHA256: 57dd2c264ddbae4fe48afdc7774267bfbeda16cb193c43802b8f792a606f92ed
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



uint _APSRTPPacketHandlerGetSeqNumOfPacket(long param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  
  if (*(long *)(param_1 + 0xa8) == 0) {
    _APSRTPPacketHandlerGetSeqNumOfPacket_cold_1();
    uVar2 = 0;
  }
  else {
    uVar1 = *(ushort *)(*(long *)(param_1 + 0xa8) + 2);
    uVar2 = (param_2 - *(int *)(param_1 + 0x678)) + ((uint)(uVar1 >> 8) | (uVar1 & 0xff00ff) << 8) +
            1;
  }
  return uVar2 & 0xffff;
}


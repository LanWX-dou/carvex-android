/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ace454
 * original code SHA256: 886b483d09d3cca34b602e3da22b55719ae8f20e79cfc02822f1407ed90a7e07
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _APSRTPPacketHandlerReadExtendedHeader(uint *param_1,uint *param_2,long *param_3)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = *param_1;
  uVar4 = (uint)(byte)uVar3;
  *param_2 = uVar4;
  if ((char)(byte)uVar3 < '\0') {
    uVar3 = (*param_1 & 0xff00ff00) >> 8 | (*param_1 & 0xff00ff) << 8;
    uVar2 = uVar3 >> 0x10;
    uVar4 = (uVar2 | uVar3 << 0x10) >> 2 & 0x3fff00 | uVar2 << 0x16 | uVar4;
    *param_2 = uVar4;
  }
  if (param_3 != (long *)0x0) {
    lVar1 = 4;
    if ((uVar4 & 0x80) == 0) {
      lVar1 = 1;
    }
    *param_3 = (long)param_1 + lVar1;
  }
  return;
}


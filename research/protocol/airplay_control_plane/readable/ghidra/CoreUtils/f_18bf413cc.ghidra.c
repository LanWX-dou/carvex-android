/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18bf413cc
 * original code SHA256: c388eeb48a5e22f7b844d34c76ce59d47b9e10f33a8e0e323a3ab1bcd18f2c57
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_TLV8Get(byte *param_1,byte *param_2,uint param_3,long *param_4,ulong *param_5,ulong *param_6)

{
  byte *pbVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  
  while( true ) {
    if (param_1 == param_2) {
      return 0xffffe5b9;
    }
    if (param_2 <= param_1) {
      return 0xffffe5cf;
    }
    if ((ulong)((long)param_2 - (long)param_1) < 2) {
      return 0xffffe5b9;
    }
    pbVar1 = param_1 + 2;
    bVar3 = param_1[1];
    pbVar2 = pbVar1 + bVar3;
    if (param_2 < pbVar2) break;
    bVar4 = *param_1;
    param_1 = pbVar2;
    if (bVar4 == param_3) {
      if (param_4 != (long *)0x0) {
        *param_4 = (long)pbVar1;
      }
      if (param_5 != (ulong *)0x0) {
        *param_5 = (ulong)bVar3;
      }
      if (param_6 != (ulong *)0x0) {
        *param_6 = (ulong)pbVar2;
      }
      return 0;
    }
  }
  return 0xffffe5a2;
}


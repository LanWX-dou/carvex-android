/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000053a4
 * original code SHA256: 056b8cd16d39a4c06df6496a39af8ce30f402530f60e311cc57037b0e72e08de
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _iAP2MsgCalcMessageLen(long param_1)

{
  ushort *puVar1;
  ushort *puVar2;
  long lVar3;
  int iVar4;
  
  lVar3 = *(long *)(param_1 + 0x18);
  puVar1 = *(ushort **)(param_1 + 0x20);
  puVar2 = (ushort *)(lVar3 + 6);
  if ((puVar1 == (ushort *)0x0 || puVar1 <= puVar2) || ((long)puVar1 - (long)puVar2 < 4)) {
    iVar4 = 6;
  }
  else {
    iVar4 = 6;
    if ((ulong)((long)puVar1 - (long)puVar2) <
        (ulong)((uint)(*(ushort *)(lVar3 + 6) >> 8) | (*(ushort *)(lVar3 + 6) & 0xff00ff) << 8))
    goto LAB_100005428;
    do {
      iVar4 = iVar4 + ((uint)(*puVar2 >> 8) | (*puVar2 & 0xff00ff) << 8);
      puVar2 = (ushort *)_iAP2MsgGetNextParamWithError(param_1,0,puVar2,0);
    } while (puVar2 != (ushort *)0x0);
    lVar3 = *(long *)(param_1 + 0x18);
  }
  if (lVar3 == 0) {
    return 0;
  }
LAB_100005428:
  *(char *)(lVar3 + 2) = (char)((uint)iVar4 >> 8);
  *(char *)(*(long *)(param_1 + 0x18) + 3) = (char)iVar4;
  return iVar4;
}


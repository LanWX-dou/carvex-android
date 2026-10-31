/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100003a68
 * original code SHA256: c81d4d9e5d099d27a42a05d81b4d27bfbb9777881b167513a6ca98eaa13c72fa
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2MsgInitParam(long param_1,undefined1 *param_2,undefined4 param_3,int param_4,uint param_5,
                      undefined1 *param_6)

{
  long lVar1;
  char cVar2;
  uint uVar3;
  
  if (param_6 != (undefined1 *)0x0) {
    uVar3 = 4;
    if (param_4 != 0xc) {
      uVar3 = param_5;
    }
    *param_6 = (char)(CONCAT11(*param_6,param_6[1]) + uVar3 >> 8);
    param_6[1] = param_6[1] + (char)uVar3;
  }
  *(ulong *)(param_1 + 0x20) = *(long *)(param_1 + 0x20) + (ulong)param_5;
  *param_2 = (char)(param_5 >> 8);
  param_2[1] = (char)param_5;
  param_2[2] = (char)((uint)param_3 >> 8);
  param_2[3] = (char)param_3;
  lVar1 = *(long *)(param_1 + 0x18);
  if ((lVar1 == 0) || (*(uint *)(param_1 + 0x10) < 6)) {
    uVar3 = 0;
  }
  else {
    uVar3 = (uint)(*(ushort *)(lVar1 + 2) >> 8) | (*(ushort *)(lVar1 + 2) & 0xff00ff) << 8;
  }
  *(char *)(lVar1 + 2) = (char)(uVar3 + param_5 >> 8);
  lVar1 = *(long *)(param_1 + 0x18);
  if ((lVar1 == 0) || (*(uint *)(param_1 + 0x10) < 6)) {
    cVar2 = '\0';
  }
  else {
    cVar2 = *(char *)(lVar1 + 3);
  }
  *(char *)(lVar1 + 3) = cVar2 + (char)param_5;
  return;
}


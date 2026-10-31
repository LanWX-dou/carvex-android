/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519fa054
 * original code SHA256: 5e8ccbd712377c62f74a8adcd9103f5d40720b8ed56882139f286ce74a9e477a
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _IPaI1oem5iL(void)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  uint *puVar5;
  uint *puVar6;
  undefined1 auStack_88 [8];
  int local_80;
  int local_7c;
  undefined8 local_68;
  
  local_68 = *_DAT_2681b4ee0;
  uVar1 = ((uint)DAT_26e7db410 + DAT_26e7f16d8 ^ 0x6d3cb4fa) * -0x2c10e087;
  puVar5 = (uint *)(*(long *)(&DAT_27612b8f0 +
                             (ulong)(((uVar1 ^ (byte)(&UNK_251c71070)
                                                     [(byte)(&DAT_251c6fb60)[(byte)uVar1] ^ 0x4a]) &
                                     0xff) + 0x11) * 8) + -4);
  lVar4 = *(long *)puVar5;
  uVar1 = ((uint)DAT_26e7db410 + (int)lVar4 ^ 0x6d3cb4fa) * -0x2c10e087;
  puVar6 = *(uint **)(&DAT_27612b8f0 +
                     (long)(int)(((*(byte *)(DAT_27612bcf8 + -4 +
                                            (ulong)(*(byte *)(DAT_27612beb0 + -0xc +
                                                             (ulong)(byte)uVar1) ^ 0xfe)) ^ uVar1) &
                                 0xff) - 0x26) * 8);
  lVar3 = *(long *)puVar6;
  *(long *)puVar5 = (long)(auStack_88 + lVar3 + lVar4) * 0xd3ef1f79 + -0x375b2a546d3cb4fa;
  *(ulong *)puVar6 = ((ulong)(auStack_88 + lVar3 + lVar4) ^ 0x375b2a546d3cb4fa) * 0xd3ef1f79;
  uVar1 = (uint)&local_80 ^ 0xb902409d;
  local_7c = (((uVar1 << 1 | 0xa435a84c) - uVar1) + 0xade52bda ^ 0xd63051d2) * -0x6c839f29 +
             -0x24acda04;
  uVar1 = (*puVar5 ^ 0x6d3cb4fa ^ *puVar6) * -0x2c10e087;
  uVar2 = (DAT_26e7f16d8 ^ 0x6d3cb4fa ^ (uint)DAT_26e7db410) * -0x2c10e087;
  lVar3 = *(long *)(&DAT_27612b8f0 +
                   (long)(int)(((uVar2 ^ (byte)(&DAT_251c70b70)
                                               [(byte)(&DAT_251c6fa60)[(byte)uVar2] ^ 0x18]) & 0xff)
                              - 0x27) * 8);
  (**(code **)(lVar3 + -0xc +
              (ulong)(((*(byte *)(DAT_27612bf28 +
                                  (ulong)(*(byte *)(DAT_27612ba18 + (ulong)(byte)uVar1 + -8) ^ 0xb9)
                                 + -4) ^ uVar1) & 0xff) + 0x3fc) * 8))(&local_80);
                    /* WARNING: Could not recover jumptable at 0x0002519fa278. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar3 + -0xc + (ulong)((uint)(local_80 == 0x145514f8) * 0x199 ^ 0x28a) * 8))();
  return;
}


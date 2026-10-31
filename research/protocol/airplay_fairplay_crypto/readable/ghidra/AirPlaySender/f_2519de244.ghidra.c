/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519de244
 * original code SHA256: 172c1002c13a99a10108eea759d1393e0f31622c1754062669e7c46d0b22ae12
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _Mib5yocT(void)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;
  long *plVar5;
  undefined1 auStack_d98 [3288];
  int local_c0;
  int local_bc;
  undefined8 local_78;
  
  local_78 = *_DAT_2681b4ee0;
  uVar1 = ((uint)DAT_26e7db410 + DAT_26e7db418 ^ 0x6d3cb4fa) * -0x2c10e087;
  plVar4 = (long *)(*(long *)(&DAT_27612b8f0 +
                             (long)(int)(((uVar1 ^ (byte)(&UNK_251c71070)
                                                         [(byte)(&DAT_251c6fb60)[(byte)uVar1] ^ 0xcd
                                                         ]) & 0xff) - 0x58) * 8) + -4);
  uVar1 = ((uint)*plVar4 ^ (uint)DAT_26e7db410 ^ 0x6d3cb4fa) * -0x2c10e087;
  plVar5 = *(long **)(&DAT_27612b8f0 +
                     (ulong)(((uVar1 ^ (byte)(&DAT_251c70b70)
                                             [(byte)(&DAT_251c6fa60)[(byte)uVar1] ^ 0xb4]) & 0xff) +
                            0x42) * 8);
  lVar3 = ((*plVar5 - *plVar4) - (long)auStack_d98 ^ 0x375b2a546d3cb4faU) * 0xd3ef1f79;
  *plVar4 = lVar3;
  *plVar5 = lVar3;
  local_bc = ((int)&stack0xfffffffffffffff0 - 0xb0U ^ 0x3d28c569) * -0x6c839f29 + -0x24acda04;
  uVar1 = ((int)*plVar5 - *(int *)plVar4 ^ 0x6d3cb4faU) * -0x2c10e087;
  uVar2 = (DAT_26e7db418 ^ 0x6d3cb4fa ^ (uint)DAT_26e7db410) * -0x2c10e087;
  lVar3 = *(long *)(&DAT_27612b8f0 +
                   (long)(int)(((uVar2 ^ (byte)(&DAT_251c6d290)
                                               [(byte)(&DAT_251c70e70)[(byte)uVar2] ^ 0x3b]) & 0xff)
                              - 0x75) * 8);
  (**(code **)(lVar3 + -0xc +
              (ulong)(((*(byte *)(DAT_27612bae8 + -4 +
                                 (ulong)(*(byte *)(DAT_27612ba48 + -0xc + (ulong)(byte)uVar1) ^ 0xcd
                                        )) ^ uVar1) & 0xff) + 0x387) * 8))(&local_c0);
                    /* WARNING: Could not recover jumptable at 0x0002519de454. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar3 + -0xc + (ulong)((uint)(local_c0 != 0x145514f8) * 0x1d ^ 0x12f) * 8))();
  return;
}


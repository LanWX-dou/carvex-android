/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519fa410
 * original code SHA256: d6911bc3a59a4e0dc63d276893603dc17c0043d8cecb5333301112cfffd257f8
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _cp2g1b9ro(void)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;
  long *plVar5;
  long *plVar6;
  undefined1 auStack_90 [8];
  int local_88;
  int local_84;
  undefined8 local_68;
  
  local_68 = *_DAT_2681b4ee0;
  uVar3 = (DAT_26e7db508 ^ 0x6d3cb4fa ^ (uint)DAT_26e7db410) * -0x2c10e087;
  plVar5 = (long *)(*(long *)(&DAT_27612b8f0 +
                             (long)(int)(((uVar3 ^ (byte)(&DAT_251c6d190)
                                                         [(byte)(&DAT_251c70d70)[(byte)uVar3] ^ 0x99
                                                         ]) & 0xff) - 0x98) * 8) + -4);
  uVar3 = ((uint)*plVar5 ^ (uint)DAT_26e7db410 ^ 0x6d3cb4fa) * -0x2c10e087;
  plVar6 = *(long **)(&DAT_27612b8f0 +
                     (long)(int)(((*(byte *)(DAT_27612be00 +
                                            (ulong)(*(byte *)(DAT_27612bba0 + (ulong)(byte)uVar3 +
                                                             -8) ^ 0x1a)) ^ uVar3) & 0xff) - 0x40) *
                     8);
  uVar4 = (*plVar6 - *plVar5) - (long)auStack_90;
  *plVar5 = uVar4 * 0xd3ef1f79 + 0x4f123ff8ff01d02a;
  *plVar6 = (uVar4 ^ 0x375b2a546d3cb4fa) * 0xd3ef1f79;
  uVar3 = (uint)&local_88;
  local_84 = (((uVar3 | 0x848bdf) - uVar3) + (uVar3 & 0xff7b7420) ^ 0x3dac4eb6) * -0x6c839f29 +
             -0x24acda04;
  uVar3 = ((int)*plVar6 + *(int *)plVar5 ^ 0x6d3cb4faU) * -0x2c10e087;
  uVar1 = ((uint)DAT_26e7db410 - DAT_26e7db508 ^ 0x6d3cb4fa) * -0x2c10e087;
  lVar2 = *(long *)(&DAT_27612b8f0 +
                   (long)(int)(((uVar1 ^ (byte)(&DAT_251c6d290)
                                               [(byte)(&DAT_251c70e70)[(byte)uVar1] ^ 0x3b]) & 0xff)
                              - 0x75) * 8);
  (**(code **)(lVar2 + -0xc +
              (ulong)(((*(byte *)(DAT_27612bb20 +
                                  (ulong)(*(byte *)(DAT_27612ba70 + (ulong)(byte)uVar3 + -8) ^ 0x3b)
                                 + -8) ^ uVar3) & 0xff) + 0x3bb) * 8))(&local_88);
                    /* WARNING: Could not recover jumptable at 0x0002519fa62c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar2 + -0xc + (ulong)((uint)(local_88 == 0x145514f8) * 0x3d1 ^ 0x172) * 8))();
  return;
}


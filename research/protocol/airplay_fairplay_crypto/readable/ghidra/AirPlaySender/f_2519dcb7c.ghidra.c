/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519dcb7c
 * original code SHA256: b46ee46e93771de0d9d180b71cd81d875fb87afc22021429fa809907fa5e177a
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _U4HBs(void)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  long *plVar6;
  undefined1 auStack_a8 [8];
  int local_a0;
  int local_9c;
  undefined8 local_70;
  
  local_70 = *_DAT_2681b4ee0;
  uVar2 = (DAT_26e7db4e8 ^ 0x6d3cb4fa ^ (uint)DAT_26e7db410) * -0x2c10e087;
  plVar5 = (long *)(*(long *)(&DAT_27612b8f0 +
                             (long)(int)(((uVar2 ^ (byte)(&DAT_251c6d090)
                                                         [(byte)(&DAT_251c70c70)[(byte)uVar2] ^ 0x69
                                                         ]) & 0xff) - 0x2b) * 8) + -4);
  lVar3 = *plVar5;
  uVar2 = ((uint)DAT_26e7db410 - (int)lVar3 ^ 0x6d3cb4fa) * -0x2c10e087;
  plVar6 = *(long **)(&DAT_27612b8f0 +
                     (ulong)(((uVar2 ^ (byte)(&DAT_251c70b70)
                                             [(byte)(&DAT_251c6fa60)[(byte)uVar2] ^ 0x18]) & 0xff) +
                            0x69) * 8);
  lVar4 = *plVar6;
  *plVar5 = (long)(auStack_a8 + (lVar4 - lVar3)) * 0xd3ef1f79 + 0x375b2a546d3cb4fa;
  *plVar6 = ((ulong)(auStack_a8 + (lVar4 - lVar3)) ^ 0x375b2a546d3cb4fa) * 0xd3ef1f79;
  uVar2 = (int)&stack0xfffffffffffffff0 - 0x90;
  local_9c = ((0x6bb4fd11 - (uVar2 | 0x6bb4fd11)) + (uVar2 | 0x944b02ee) ^ 0xa963c787) * -0x6c839f29
             + -0x24acda04;
  uVar2 = ((int)*plVar6 - *(int *)plVar5 ^ 0x6d3cb4faU) * -0x2c10e087;
  uVar1 = ((uint)DAT_26e7db410 - DAT_26e7db4e8 ^ 0x6d3cb4fa) * -0x2c10e087;
  lVar3 = *(long *)(&DAT_27612b8f0 +
                   (long)(int)(((uVar1 ^ (byte)(&DAT_251c6d190)
                                               [(byte)(&DAT_251c70d70)[(byte)uVar1] ^ 0x99]) & 0xff)
                              - 0x9c) * 8);
  (**(code **)(lVar3 + -0xc +
              (ulong)(((*(byte *)(DAT_27612bae8 + -4 +
                                 (ulong)(*(byte *)(DAT_27612ba48 + -0xc + (ulong)(byte)uVar2) ^ 0xe4
                                        )) ^ uVar2) & 0xff) + 0x3c8) * 8))(&local_a0);
                    /* WARNING: Could not recover jumptable at 0x0002519dcdb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar3 + -0xc + (ulong)((uint)(local_a0 == 0x145514f8) * 0x4b ^ 0x8f) * 8))();
  return;
}


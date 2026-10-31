/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519fb3a4
 * original code SHA256: e0bd7a38035accc1989a4eba296fd8f35f812914fa4bc926ea0ca1ca3a3f2f2b
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _jEHf8Xzsv8K(long param_1)

{
  uint uVar1;
  uint uVar2;
  long *plVar3;
  long lVar4;
  undefined1 auStack_18 [8];
  
  uVar1 = (DAT_26e7db538 ^ 0x6d3cb4fa ^ (uint)DAT_26e7db410) * -0x2c10e087;
  lVar4 = *(long *)(*(long *)(&DAT_27612b8f0 +
                             (long)(int)(((uVar1 ^ (byte)(&DAT_251c70b70)
                                                         [(byte)(&DAT_251c6fa60)[(byte)uVar1] ^ 0x18
                                                         ]) & 0xff) - 0x32) * 8) + -4);
  uVar2 = ((uint)DAT_26e7db410 + (int)lVar4 ^ 0x6d3cb4fa) * -0x2c10e087;
  plVar3 = *(long **)(&DAT_27612b8f0 +
                     (ulong)(((uVar2 ^ (byte)(&DAT_251c70b70)
                                             [(byte)(&DAT_251c6fa60)[(byte)uVar2] ^ 0xb4]) & 0xff) +
                            0x42) * 8);
  lVar4 = (*plVar3 - lVar4 ^ (ulong)auStack_18 ^ 0x375b2a546d3cb4fa) * 0xd3ef1f79;
  *(long *)(*(long *)(&DAT_27612b8f0 +
                     (long)(int)(((uVar1 ^ (byte)(&DAT_251c70b70)
                                                 [(byte)(&DAT_251c6fa60)[(byte)uVar1] ^ 0x18]) &
                                 0xff) - 0x32) * 8) + -4) = lVar4;
  *plVar3 = lVar4;
  uVar1 = ((uint)DAT_26e7db410 + DAT_26e7db538 ^ 0x6d3cb4fa) * -0x2c10e087;
                    /* WARNING: Could not recover jumptable at 0x0002519fb4d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(&DAT_27612b8f0 +
                        (long)(int)(((uVar1 ^ (byte)(&DAT_251c70b70)
                                                    [(byte)(&DAT_251c6fa60)[(byte)uVar1] ^ 0xb3]) &
                                    0xff) - 0x82) * 8) + -0xc +
              (ulong)((uint)(param_1 != 0) * 0xd8 ^ 0x249) * 8))();
  return;
}


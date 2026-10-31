/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519f2904
 * original code SHA256: a0f90f018989b7c28f2cbe40f5ee063a3a0f1bd4d8708a7bf74f26023ac59ae0
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _zxcm2Qme0x(undefined8 param_1,undefined8 param_2,long param_3)

{
  uint uVar1;
  uint uVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  undefined1 auStack_80 [24];
  undefined8 local_68;
  
  local_68 = *_DAT_2681b4ee0;
  uVar1 = (DAT_26e7e65e0 ^ 0x6d3cb4fa ^ (uint)DAT_26e7db410) * -0x2c10e087;
  lVar4 = **(long **)(&DAT_27612b8f0 +
                     (ulong)(((uVar1 ^ (byte)(&DAT_251c6d290)
                                             [(byte)(&DAT_251c70e70)[(byte)uVar1] ^ 0x3b]) & 0xff) +
                            4) * 8);
  uVar2 = ((uint)lVar4 ^ (uint)DAT_26e7db410 ^ 0x6d3cb4fa) * -0x2c10e087;
  plVar3 = *(long **)(&DAT_27612b8f0 +
                     (long)(int)(((*(byte *)(DAT_27612bcf8 +
                                             (ulong)(*(byte *)(DAT_27612beb0 + (ulong)(byte)uVar2 +
                                                              -0xc) ^ 0xfe) + -4) ^ uVar2) & 0xff) -
                                0x26) * 8);
  uVar5 = *plVar3 + lVar4 ^ (ulong)auStack_80;
  **(long **)(&DAT_27612b8f0 +
             (ulong)(((uVar1 ^ (byte)(&DAT_251c6d290)[(byte)(&DAT_251c70e70)[(byte)uVar1] ^ 0x3b]) &
                     0xff) + 4) * 8) = uVar5 * 0xd3ef1f79 + 0x4f123ff8ff01d02a;
  *plVar3 = (uVar5 ^ 0x375b2a546d3cb4fa) * 0xd3ef1f79;
  uVar1 = (DAT_26e7e65e0 ^ 0x6d3cb4fa ^ (uint)DAT_26e7db410) * -0x2c10e087;
                    /* WARNING: Could not recover jumptable at 0x0002519f2a78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(&DAT_27612b8f0 +
                        (long)(int)(((uVar1 ^ (byte)(&DAT_251c6d190)
                                                    [(byte)(&DAT_251c70d70)[(byte)uVar1] ^ 0x9f]) &
                                    0xff) - 0x8f) * 8) + -0xc +
              (ulong)((uint)(param_3 != 0) * 0x3b ^ 0x29e) * 8))(0xffff5bd9);
  return;
}


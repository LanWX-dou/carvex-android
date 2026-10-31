/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519ffebc
 * original code SHA256: 0d7e4be63a9d3915d7c020f6ed9af04584a6997694c8708ee1e906e846e39cb2
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _OowSGu(void)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;
  ulong *puVar5;
  ulong *puVar6;
  undefined1 auStack_a0 [8];
  int local_98;
  int local_94;
  undefined8 local_68;
  
  local_68 = *_DAT_2681b4ee0;
  uVar3 = ((uint)DAT_26e7db410 - DAT_26e7e65c0 ^ 0x6d3cb4fa) * -0x2c10e087;
  puVar5 = (ulong *)(*(long *)(&DAT_27612b8f0 +
                              (long)(int)(((uVar3 ^ (byte)(&DAT_251c70b70)
                                                          [(byte)(&DAT_251c6fa60)[(byte)uVar3] ^
                                                           0x18]) & 0xff) - 0x20) * 8) + -4);
  uVar3 = ((uint)DAT_26e7db410 + (int)*puVar5 ^ 0x6d3cb4fa) * -0x2c10e087;
  puVar6 = *(ulong **)
            (&DAT_27612b8f0 +
            (long)(int)(((*(byte *)(DAT_27612bae8 +
                                    (ulong)(*(byte *)(DAT_27612ba48 + (ulong)(byte)uVar3 + -0xc) ^
                                           0xcd) + -4) ^ uVar3) & 0xff) - 0x19) * 8);
  uVar4 = *puVar6 ^ *puVar5;
  *puVar5 = (long)(&stack0xc8a4d5ab92c34a66 + uVar4) * 0xd3ef1f79;
  *puVar6 = ((ulong)(auStack_a0 + uVar4) ^ 0x375b2a546d3cb4fa) * 0xd3ef1f79;
  uVar3 = (uint)&local_98;
  local_94 = (((uVar3 | 0x609e27f1) - uVar3) + (uVar3 & 0x9f61d808) ^ 0x5db6e298) * -0x6c839f29 +
             -0x24acda04;
  uVar3 = ((int)*puVar6 - *(int *)puVar5 ^ 0x6d3cb4faU) * -0x2c10e087;
  uVar1 = (DAT_26e7e65c0 ^ 0x6d3cb4fa ^ (uint)DAT_26e7db410) * -0x2c10e087;
  lVar2 = *(long *)(&DAT_27612b8f0 +
                   (long)(int)(((uVar1 ^ (byte)(&DAT_251c6d090)
                                               [(byte)(&DAT_251c70c70)[(byte)uVar1] ^ 0x69]) & 0xff)
                              - 0xdd) * 8);
  (**(code **)(lVar2 + -0xc +
              (ulong)(((*(byte *)(DAT_27612bf28 +
                                  (ulong)(*(byte *)(DAT_27612ba18 + (ulong)(byte)uVar3 + -8) ^ 0xb9)
                                 + -4) ^ uVar3) & 0xff) + 0x3fc) * 8))(&local_98);
                    /* WARNING: Could not recover jumptable at 0x000251a000e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(lVar2 + -0xc + (ulong)((uint)(local_98 == 0x145514f8) * 0x26 ^ 0x1de) * 8))();
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100102fdc
 * original code SHA256: 00390949ee63999b1a46b390a878c057c612ae627a5371418f0cd4f28dbe96bc
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2PacketCreateSYNPacket
               (undefined8 param_1,undefined8 param_2,undefined1 *param_3,byte *param_4)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  undefined8 uVar4;
  undefined1 uVar5;
  int iVar6;
  uint uVar7;
  ulong uVar8;
  ulong uVar9;
  uint uVar10;
  long lVar11;
  uint uVar12;
  undefined1 auVar13 [16];
  byte abStack_10057 [6];
  undefined1 uStack_10051;
  undefined1 uStack_10050;
  undefined2 uStack_1004f;
  byte bStack_1004d;
  undefined1 auStack_1004c [65524];
  long local_58;
  
  auVar13 = (*(code *)PTR____chkstk_darwin_10022be18)();
  local_58 = *(long *)PTR____stack_chk_guard_10022bb80;
  _memset(&bStack_1004d,0xaa,0xfff5);
  abStack_10057[0] = *param_4;
  abStack_10057[1] = param_4[1];
  uStack_1004f = *(undefined2 *)(param_4 + 2);
  bVar2 = param_4[0x18];
  bVar3 = param_4[10];
  abStack_10057[2] = (byte)((ushort)*(undefined2 *)(param_4 + 4) >> 8);
  abStack_10057[3] = (byte)*(undefined2 *)(param_4 + 4);
  abStack_10057[4] = (byte)((ushort)*(undefined2 *)(param_4 + 6) >> 8);
  abStack_10057[5] = (byte)*(undefined2 *)(param_4 + 6);
  uStack_10051 = (undefined1)((ushort)*(undefined2 *)(param_4 + 8) >> 8);
  uStack_10050 = (undefined1)*(undefined2 *)(param_4 + 8);
  uVar12 = (uint)bVar3;
  if (abStack_10057[0] == 0) {
    uVar8 = 0;
  }
  else {
    if (abStack_10057[0] != 1) {
      bStack_1004d = bVar2;
      if (bVar2 == 0) {
        iVar6 = 0xb;
      }
      else {
        _memcpy(auStack_1004c,param_4 + 0x19,(ulong)bVar2);
        iVar6 = bVar2 + 0xb;
      }
      abStack_10057[(byte)iVar6] = bVar3;
      uVar7 = iVar6 + 1;
      uVar8 = (ulong)(bVar2 + 0xc) & 0xff;
      goto LAB_1001030fc;
    }
    uVar8 = 10;
  }
  uVar7 = 10;
LAB_1001030fc:
  uVar10 = uVar12;
  if (4 < uVar12) {
    uVar10 = 5;
  }
  uVar9 = (ulong)uVar10;
  if (uVar12 != 0) {
    lVar11 = 0;
    do {
      pbVar1 = param_4 + lVar11 * 4 + 0x1e;
      abStack_10057[uVar8] = *pbVar1;
      abStack_10057[uVar8 + 1] = pbVar1[1] | pbVar1[3] << 7;
      abStack_10057[uVar8 + 2] = pbVar1[2];
      lVar11 = lVar11 + 1;
      uVar8 = uVar8 + 3;
      uVar9 = uVar9 - 1;
    } while (uVar9 != 0);
    uVar7 = uVar7 + uVar10 * 3;
  }
  if (param_3 == (undefined1 *)0x0) {
    uVar5 = 0;
    uVar4 = 0x80;
  }
  else {
    uVar5 = *param_3;
    uVar4 = 0xc0;
  }
  _iAP2PacketCreate(auVar13._0_8_,uVar4,auVar13._8_8_,uVar5,abStack_10057,uVar7 & 0xff,0,1);
  if (*(long *)PTR____stack_chk_guard_10022bb80 == local_58) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be4d5fc
 * original code SHA256: 774b89947adb42b3068c398f2f93242eeb33143908600b0bf80c49f0cab68cc7
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __NetTransportWriteV(ulong *param_1,int *param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  long lVar3;
  undefined4 **ppuVar4;
  undefined4 *puVar5;
  undefined8 *puVar6;
  bool bVar7;
  undefined8 uVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  long lVar14;
  long lVar15;
  undefined4 **ppuVar16;
  undefined4 **local_98;
  undefined4 local_8c;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined4 *local_78;
  long local_70;
  long local_68;
  
  local_68 = *_DAT_1e016af28;
  puVar2 = param_3 + 0x105e;
  lVar3 = (long)param_3 + 0x417a;
  ppuVar16 = (undefined4 **)*param_1;
  ppuVar4 = ppuVar16 + (long)*param_2 * 2;
  puVar5 = param_3 + 0x11b0;
  puVar12 = *(undefined4 **)(param_3 + 0x1164);
  do {
    while (lVar15 = *(long *)(param_3 + 0x1166) - (long)puVar12, lVar15 != 0) {
      local_8c = 1;
      local_98 = &local_78;
      local_78 = puVar12;
      local_70 = lVar15;
      uVar8 = _SocketWriteData(*param_3,&local_98,&local_8c);
      puVar12 = (undefined4 *)(*(long *)(param_3 + 0x1164) + (lVar15 - local_70));
      *(undefined4 **)(param_3 + 0x1164) = puVar12;
      if ((int)uVar8 != 0) {
LAB_18be4d858:
        *param_1 = (ulong)ppuVar16;
        *param_2 = (int)((ulong)((long)ppuVar4 - (long)ppuVar16) >> 4);
        if (*_DAT_1e016af28 == local_68) {
          return;
        }
        func_0x0001900cc180(uVar8);
        return;
      }
    }
    local_98 = ppuVar16;
    if (ppuVar16 < ppuVar4) {
      lVar15 = 0;
      lVar14 = lVar3;
      do {
        puVar13 = (undefined4 *)((long)param_3 + (0x457a - lVar14));
        puVar12 = local_98[1];
        if (puVar13 < puVar12) {
          lVar15 = (long)puVar13 + lVar15;
          if (lVar15 != 0) goto LAB_18be4d724;
          goto LAB_18be4d854;
        }
        lVar15 = (long)puVar12 + lVar15;
        lVar14 = lVar14 + (long)puVar12;
        local_98 = local_98 + 2;
      } while (local_98 < ppuVar4);
    }
    else {
      lVar15 = 0;
    }
    if (lVar15 == 0) {
LAB_18be4d854:
      uVar8 = 0;
      goto LAB_18be4d858;
    }
LAB_18be4d724:
    _chacha20_poly1305_init_64x64(param_3 + 0x1168,param_3 + 0x11a8,puVar5);
    *(short *)(param_3 + 0x105e) = (short)lVar15;
    _poly1305_update(param_3 + 0x118a,puVar2,2);
    *(long *)(param_3 + 0x11a2) = *(long *)(param_3 + 0x11a2) + 2;
    if (ppuVar16 < ppuVar4) {
      lVar14 = 0x417a;
      lVar9 = lVar3;
      lVar10 = lVar3;
      do {
        puVar12 = (undefined4 *)((long)param_3 + (0x457a - lVar10));
        if (puVar12 < ppuVar16[1]) {
          lVar10 = _chacha20_poly1305_encrypt(param_3 + 0x1168,*ppuVar16,puVar12,lVar9);
          *ppuVar16 = (undefined4 *)((long)*ppuVar16 + (long)puVar12);
          ppuVar16[1] = (undefined4 *)((long)ppuVar16[1] - (long)puVar12);
          lVar14 = lVar10 + lVar14;
          break;
        }
        lVar9 = _chacha20_poly1305_encrypt(param_3 + 0x1168,*ppuVar16,ppuVar16[1],lVar9);
        lVar10 = lVar10 + (long)ppuVar16[1];
        lVar14 = lVar9 + lVar14;
        ppuVar16 = ppuVar16 + 2;
        lVar9 = (long)param_3 + lVar14;
      } while (ppuVar16 < ppuVar4);
    }
    else {
      lVar14 = 0x417a;
    }
    lVar10 = _chacha20_poly1305_final(param_3 + 0x1168,(long)param_3 + lVar14,&local_88);
    puVar6 = (undefined8 *)((long)param_3 + lVar10 + lVar14);
    if (0x457a < lVar10 + lVar14 || puVar6 != (undefined8 *)(lVar3 + lVar15)) {
      uVar8 = 0xffffe596;
      goto LAB_18be4d858;
    }
    uVar11 = 0;
    puVar6[1] = uStack_80;
    *puVar6 = local_88;
    do {
      uVar1 = *(byte *)((long)puVar5 + uVar11) + 1;
      *(char *)((long)puVar5 + uVar11) = (char)uVar1;
      if (uVar1 >> 8 == 0) break;
      bVar7 = uVar11 < 7;
      uVar11 = uVar11 + 1;
    } while (bVar7);
    *(undefined4 **)(param_3 + 0x1164) = puVar2;
    *(undefined8 **)(param_3 + 0x1166) = puVar6 + 2;
    puVar12 = puVar2;
  } while( true );
}


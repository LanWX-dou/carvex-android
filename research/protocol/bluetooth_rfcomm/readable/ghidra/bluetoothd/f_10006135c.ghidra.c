/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10006135c
 * original code SHA256: d67fe7461d9f34c5d4e6d6e57ce9b033c1be7834d6db265e8ce5914e17eecc3a
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 FUN_10006135c(long param_1,short *param_2,undefined8 param_3,uint *param_4)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  undefined8 uVar6;
  uint uVar7;
  undefined1 *puVar8;
  short sVar9;
  ulong uVar10;
  uint uVar11;
  long *plVar12;
  uint uVar13;
  
  if (puRam0000000100c39fb0 == (undefined1 *)0x0) {
    FUN_1000f9438();
  }
  if (param_1 == 0) {
    FUN_1000f9438();
  }
  if (((uint)param_3 >> 0xf & 1) == 0) {
    uVar4 = 0x65;
    if ((param_1 != 0) && (puRam0000000100c39fb0 != (undefined1 *)0x0)) {
      if ((uint)param_3 == 0) {
        uRam0000000100c39fa9 = 1;
      }
      uVar7 = (uint)uRam0000000100c39fac;
      if (uRam0000000100c39fac == 0) {
        sVar9 = 0;
        uVar13 = 0;
        puVar8 = (undefined1 *)0x0;
        uVar11 = 0;
      }
      else {
        plVar12 = (long *)(puRam0000000100c39fb0 + 8);
        puVar8 = puRam0000000100c39fb0;
        if (*plVar12 == 0) {
          uVar13 = 0;
          sVar9 = 0;
        }
        else {
          uVar10 = 0;
          do {
            uVar11 = (int)uVar10 + 1;
            uVar10 = (ulong)uVar11;
            sVar9 = (short)uVar11;
            uVar13 = (uint)sVar9;
            if ((int)(uint)uRam0000000100c39fac <= (int)uVar13) {
              uVar11 = 0;
              goto LAB_1000614b8;
            }
            puVar8 = puRam0000000100c39fb0 +
                     ((-((ulong)(uVar11 >> 0xf) & 1) & 0xfffffffffffe0000 | (uVar10 & 0xffff) << 1)
                     + (long)sVar9) * 8;
          } while (*(long *)(puVar8 + 8) != 0);
          plVar12 = (long *)(puVar8 + 8);
        }
        if ((sRam0000000100c39faa < sVar9) &&
           (sRam0000000100c39faa = sVar9, (int)uRam0000000100c39fc0 < (int)uVar13)) {
          uRam0000000100c39fc0 = uVar13;
        }
        FUN_1000615dc(puVar8,param_3);
        *puVar8 = 2;
        *plVar12 = param_1;
        uVar1 = *(ushort *)(puVar8 + 4);
        uVar7 = uVar1 + 2;
        if ((uVar1 + 1 & 0x10000) == 0) {
          uVar7 = uVar1 + 1;
        }
        *(short *)(puVar8 + 4) = (short)uVar7;
        uVar11 = uVar7 & 0xffff | uVar13 << 0x10;
        uVar7 = (uint)uRam0000000100c39fac;
      }
LAB_1000614b8:
      if ((int)uVar7 <= (int)uVar13) {
        FUN_1000f9438();
        uVar7 = (uint)uRam0000000100c39fac;
      }
      if ((puVar8 == (undefined1 *)0x0) || (uVar13 == uVar7)) {
        iVar3 = 2;
        FUN_10000d938(2,0x2a);
        if (iVar3 != 0) {
          FUN_10000d120("Dispatch table of size %d overflow: timeout %d, cbFunc0x %x");
          uVar6 = 0x2a;
          FUN_10000e9d4();
          uVar4 = uVar6;
          _os_log_type_enabled();
          if ((int)uVar4 != 0) {
            FUN_10018f150(uVar6);
          }
        }
        FUN_1000f9438();
        uVar4 = 0x3ea;
      }
      else {
        if (param_2 == (short *)0x0) {
          sVar2 = 0;
        }
        else {
          sVar2 = *param_2;
          lVar5 = (long)sVar2;
          if (lVar5 < 9) {
            if (0 < sVar2) {
              lVar5 = 0;
              do {
                puVar8[lVar5 + 0x10] = *(undefined1 *)(*(long *)(param_2 + 4) + lVar5);
                lVar5 = lVar5 + 1;
                sVar2 = *param_2;
              } while (lVar5 < sVar2);
            }
          }
          else {
            FUN_10000d0cc(lVar5,0x1c4f2fe);
            *(long *)(puVar8 + 0x10) = lVar5;
            if (lVar5 == 0) {
              FUN_100060b80((int)sVar9);
              return 0x6a;
            }
            _memmove();
            sVar2 = *param_2;
          }
        }
        *(short *)(puVar8 + 6) = sVar2;
        uVar4 = 0;
        if (param_4 != (uint *)0x0) {
          *param_4 = uVar11;
        }
      }
    }
  }
  else {
    FUN_1000f9438();
    uVar4 = 0x65;
  }
  return uVar4;
}


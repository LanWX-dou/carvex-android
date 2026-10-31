/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005fc024
 * original code SHA256: 0dc4d58209be8a8adae018bff4535f9e3d119242d55979f077b38cbf2592ee22
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_1005fc024(long param_1,undefined8 param_2)

{
  ushort uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  bool bVar4;
  char *pcVar5;
  ulong uVar6;
  undefined8 ***pppuVar7;
  long *plVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  int iVar11;
  undefined8 *puVar12;
  long lVar13;
  long *plVar14;
  long *plVar15;
  ulong uVar16;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  char cStack_119;
  undefined8 **ppuStack_110;
  long lStack_108;
  long lStack_100;
  undefined8 **ppuStack_f0;
  ulong uStack_e8;
  ulong uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  long lStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  long lStack_b0;
  undefined8 *puStack_a8;
  undefined8 *puStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  ulong uStack_88;
  undefined8 uStack_78;
  undefined8 uStack_70;
  
  uStack_78 = 0;
  uStack_70 = 0;
  FUN_100006ef8(&uStack_78,param_1);
  uVar2 = _UNK_100930b00;
  plVar14 = *(long **)(param_1 + 0x2c8);
  if (plVar14 == (long *)(param_1 + 0x2d0)) {
    iVar11 = 0;
  }
  else {
    iVar11 = 0;
    do {
      uStack_88 = ((undefined8 *)plVar14[4])[1];
      uStack_90 = *(undefined8 *)plVar14[4];
      puStack_a8 = (undefined8 *)0x0;
      puStack_a0 = (undefined8 *)0x0;
      uStack_98 = 0;
      lVar13 = param_1;
      FUN_1005ebdf0(param_1,&uStack_90,4,&puStack_a8);
      if ((int)lVar13 != 0) {
        puVar10 = puStack_a0;
        puVar12 = puStack_a8;
        if (puStack_a8 != puStack_a0) {
          do {
            uVar1 = *(ushort *)((long)puVar12 + 2);
            if (((uVar1 & 1) == 0) && (uVar1 != 0)) {
              uVar16 = 0;
              lVar13 = puVar12[1];
              do {
                if (*(int *)(lVar13 + uVar16 * 0x10 + 8) == 3) {
                  uStack_c0 = 0;
                  uStack_b8 = 0;
                  lStack_b0 = 0;
                  pcVar5 = (char *)&uStack_c0;
                  FUN_1001ec44c(pcVar5,0x15);
                  uVar3 = s_RFCOMM_ServiceClass__100a68c0a._0_8_;
                  *(ulong *)(pcVar5 + 8) =
                       CONCAT35(s_RFCOMM_ServiceClass__100a68c0a._13_3_,
                                s_RFCOMM_ServiceClass__100a68c0a._8_5_);
                  *(undefined8 *)pcVar5 = uVar3;
                  *(ulong *)(pcVar5 + 0xd) =
                       CONCAT53(s_RFCOMM_ServiceClass__100a68c0a._16_5_,
                                s_RFCOMM_ServiceClass__100a68c0a._13_3_);
                  pcVar5[0x15] = '\0';
                  uStack_d8 = 0;
                  uStack_d0 = 0;
                  lStack_c8 = 0;
                  if ((char)uStack_90 == '\x03') {
                    if (uStack_90._2_2_ < 5) {
                      uVar6 = uStack_88 & 0xffffffff;
                      FUN_1003d59f8(uVar6);
                    }
                    else {
                      uVar6 = uStack_88;
                      FUN_1003d56fc(uStack_88);
                    }
                    FUN_1003e9cbc(&uStack_d8,uVar6);
                  }
                  ppuStack_f0 = (undefined8 ***)0x0;
                  uStack_e8 = 0;
                  uStack_e0 = 0;
                  pppuVar7 = &ppuStack_f0;
                  FUN_1001ec44c(pppuVar7,1);
                  *(undefined2 *)pppuVar7 = 10;
                  ppuStack_110 = (undefined8 **)0x0;
                  lStack_108 = 0;
                  lStack_100 = 0;
                  FUN_1005eb214(&uStack_130,&uStack_c0,&uStack_d8);
                  uVar6 = uStack_e8;
                  pppuVar7 = (undefined8 ***)ppuStack_f0;
                  if (-1 < (long)uStack_e0) {
                    uVar6 = uStack_e0 >> 0x38;
                    pppuVar7 = &ppuStack_f0;
                  }
                  plVar8 = (long *)&uStack_130;
                  __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6appendEPKcm
                            (plVar8,pppuVar7,uVar6);
                  lStack_108 = plVar8[1];
                  ppuStack_110 = (undefined8 **)*plVar8;
                  lStack_100 = plVar8[2];
                  plVar8[1] = 0;
                  plVar8[2] = 0;
                  *plVar8 = 0;
                  if (cStack_119 < '\0') {
                    __ZdlPv(CONCAT44(uStack_12c,uStack_130));
                  }
                  uVar3 = uRam0000000100cae440;
                  uVar9 = uRam0000000100cae440;
                  _os_log_type_enabled(uRam0000000100cae440,0);
                  if ((int)uVar9 != 0) {
                    pppuVar7 = (undefined8 ***)ppuStack_110;
                    if (-1 < lStack_100) {
                      pppuVar7 = &ppuStack_110;
                    }
                    uStack_130 = (undefined4)uVar2;
                    uStack_12c = SUB84(pppuVar7,0);
                    uStack_128 = (undefined4)((ulong)pppuVar7 >> 0x20);
                    __os_log_impl(0x100000000,uVar3,0,"%s",&uStack_130,0xc);
                  }
                  FUN_1005fc3fc(param_2,&uStack_90);
                  if (lStack_100 < 0) {
                    __ZdlPv(ppuStack_110);
                  }
                  if ((long)uStack_e0 < 0) {
                    __ZdlPv(ppuStack_f0);
                  }
                  if (lStack_c8 < 0) {
                    __ZdlPv(uStack_d8);
                  }
                  if (lStack_b0 < 0) {
                    __ZdlPv(uStack_c0);
                  }
                  iVar11 = iVar11 + 1;
                }
                uVar16 = uVar16 + 2;
                puVar10 = puStack_a0;
              } while (uVar16 < uVar1);
            }
            puVar12 = puVar12 + 2;
          } while (puVar12 != puVar10);
        }
        puVar12 = puStack_a8;
        if (puStack_a8 != puVar10) {
          do {
            puVar10 = puVar12 + 2;
            uStack_b8 = puVar12[1];
            uStack_c0 = *puVar12;
            FUN_100457214(&uStack_c0);
            puVar12 = puVar10;
          } while (puVar10 != puStack_a0);
        }
      }
      if (puStack_a8 != (undefined8 *)0x0) {
        puStack_a0 = puStack_a8;
        __ZdlPv(puStack_a8);
      }
      plVar8 = (long *)plVar14[1];
      plVar15 = plVar14;
      if ((long *)plVar14[1] == (long *)0x0) {
        do {
          plVar14 = (long *)plVar15[2];
          bVar4 = plVar15 != (long *)*plVar14;
          plVar15 = plVar14;
        } while (bVar4);
      }
      else {
        do {
          plVar14 = plVar8;
          plVar8 = (long *)*plVar14;
        } while ((long *)*plVar14 != (long *)0x0);
      }
    } while (plVar14 != (long *)(param_1 + 0x2d0));
  }
  FUN_100006ec0(&uStack_78);
  return iVar11;
}


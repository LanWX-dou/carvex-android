/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001479fc
 * original code SHA256: 1a23c91beeeb9fd9b178f8dc60439e8b0e938c5c0ecc324d61d7396fd376ce72
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x00010014822c) */
/* WARNING: Removing unreachable block (ram,0x000100147db0) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1001479fc(long *param_1,uint param_2,ulong param_3,undefined8 param_4,int param_5)

{
  undefined4 *puVar1;
  char *pcVar2;
  undefined2 *puVar3;
  char cVar4;
  mach_header *pmVar5;
  ulong uVar6;
  ulong uVar7;
  long *plVar8;
  mach_header *pmVar9;
  char *pcVar10;
  long *plVar11;
  int iVar12;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined2 uStack_a4;
  undefined4 uStack_a2;
  char cStack_99;
  undefined8 uStack_90;
  undefined2 uStack_88;
  short sStack_86;
  short sStack_84;
  char *pcStack_82;
  undefined1 uStack_7a;
  char cStack_79;
  undefined6 uStack_78;
  undefined2 uStack_72;
  ulong uStack_68;
  
  plVar11 = param_1;
  uStack_68 = param_3;
  FUN_1000071b8();
  (**(code **)(*plVar11 + 0x2c0))();
  pmVar9 = pmRam0000000100cae458;
  if ((int)plVar11 == 0) {
    return;
  }
  pmVar5 = pmRam0000000100cae458;
  _os_log_type_enabled(pmRam0000000100cae458,0);
  if ((int)pmVar5 != 0) {
    pcVar10 = "unknown";
    if (param_2 < 3) {
      pcVar10 = (&PTR_s_DEVICE_ADV_RECEIVED_EVENT_100bc05f0)[param_2];
    }
    pcVar2 = "SCAN_CORE_PAGE_SCAN_ENABLE";
    if ((int)param_1[0x3d] != 1) {
      pcVar2 = "unknown";
    }
    pcStack_82 = "SCAN_CORE_PAGE_SCAN_IDLE";
    if ((int)param_1[0x3d] != 0) {
      pcStack_82 = pcVar2;
    }
    uStack_90._0_2_ = (undefined2)_UNK_100930b18;
    uStack_90._2_2_ = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
    uStack_90._4_4_ = (int)pcVar10;
    uStack_88 = (undefined2)((ulong)pcVar10 >> 0x20);
    sStack_86 = (short)((ulong)pcVar10 >> 0x30);
    sStack_84 = 0x820;
    __os_log_impl(0x100000000,pmVar9,0,
                  "Received Scan Core Page Scan Request for event: %s, scanCorePageScanState: %s",
                  &uStack_90,0x16);
  }
  uVar7 = uStack_68;
  pmVar9 = pmRam0000000100cae458;
  if ((int)param_1[0x3d] == 1) {
    if (param_2 == 2) {
      pmVar5 = pmRam0000000100cae458;
      _os_log_type_enabled(pmRam0000000100cae458,0);
      if ((int)pmVar5 != 0) {
        uStack_90._0_2_ = 0;
        __os_log_impl(0x100000000,pmVar9,0,
                      "Scan Core Page Scan timer expired. Clearing Scan Core Page Scan device set.",
                      &uStack_90,2);
      }
      plVar11 = param_1 + 0x3b;
      uStack_90._0_2_ = SUB82(plVar11,0);
      uStack_90._2_2_ = (undefined2)((ulong)plVar11 >> 0x10);
      uStack_90._4_4_ = (int)((ulong)plVar11 >> 0x20);
      plVar8 = &uStack_90;
      FUN_10020eda4(plVar8,param_1[0x3b]);
      param_1[0x3b] = 0;
      param_1[0x3c] = 0;
      param_1[0x3a] = (long)plVar11;
      FUN_1000071f0();
      (**(code **)(*plVar8 + 0x1198))(*plVar8 + 0x1198);
LAB_100147df8:
      FUN_10013dc38(param_1);
      FUN_100136f98(param_1,0);
      return;
    }
    if (param_2 == 1) {
      FUN_1001070b4(uStack_68,0xc);
      if ((int)uVar7 == 0) {
        return;
      }
      FUN_100137068(uStack_68);
      uVar7 = uStack_68;
      FUN_100136bd8();
      if ((int)uVar7 != 0) {
        FUN_1001370ac(uStack_68);
        *(short *)(uStack_68 + 0x666) = *(short *)(uStack_68 + 0x666) + 1;
      }
      uVar7 = uStack_68;
      pmVar9 = pmRam0000000100cae458;
      plVar11 = (long *)param_1[0x3b];
      if (plVar11 == (long *)0x0) {
        return;
      }
      while( true ) {
        while (uStack_68 < (ulong)plVar11[4]) {
          plVar11 = (long *)*plVar11;
          if (plVar11 == (long *)0x0) {
            return;
          }
        }
        if (uStack_68 <= (ulong)plVar11[4]) break;
        plVar11 = (long *)plVar11[1];
        if (plVar11 == (long *)0x0) {
          return;
        }
      }
      if (plVar11 == param_1 + 0x3b) {
        return;
      }
      pmVar5 = pmRam0000000100cae458;
      _os_log_type_enabled(pmRam0000000100cae458,0);
      if ((int)pmVar5 != 0) {
        FUN_10010aa84(&uStack_90,uVar7);
        puVar3 = (undefined2 *)
                 CONCAT44(uStack_90._4_4_,CONCAT22(uStack_90._2_2_,(undefined2)uStack_90));
        if (-1 < cStack_79) {
          puVar3 = (undefined2 *)&uStack_90;
        }
        uStack_b0 = (undefined4)_UNK_100930b00;
        uStack_ac = SUB84(puVar3,0);
        uStack_a8 = (undefined4)((ulong)puVar3 >> 0x20);
        __os_log_impl(0x100000000,pmVar9,0,
                      "\'%s\' connected. Removing it from Scan Core Page Scan device set.",
                      &uStack_b0,0xc);
        if (cStack_79 < '\0') {
          __ZdlPv(CONCAT44(uStack_90._4_4_,CONCAT22(uStack_90._2_2_,(undefined2)uStack_90)));
        }
      }
      FUN_100043e60(param_1 + 0x3a,plVar11);
      __ZdlPv(plVar11);
      *(short *)(uStack_68 + 0x66a) = *(short *)(uStack_68 + 0x66a) + 1;
      pmVar9 = pmRam0000000100cae458;
      if (param_1[0x3c] != 0) {
        return;
      }
      pmVar5 = pmRam0000000100cae458;
      _os_log_type_enabled(pmRam0000000100cae458,0);
      if ((int)pmVar5 != 0) {
        uStack_90._0_2_ = 0;
        pmVar5 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar9,0,"Scan Core Page Scan device list is empty.",&uStack_90,2)
        ;
      }
      FUN_1000071f0();
      (**(code **)(*(long *)pmVar5 + 0x1198))();
      goto LAB_100147df8;
    }
    if (param_2 != 0) {
      return;
    }
    FUN_1000cbaf4();
    if ((int)uVar7 == 0) {
      return;
    }
    uVar7 = uStack_68;
    FUN_1000cb9c8();
    if ((uVar7 & 1) != 0) {
      return;
    }
    uVar6 = uStack_68;
    FUN_1001070b4(uStack_68,0xc);
    uVar7 = uStack_68;
    pmVar9 = pmRam0000000100cae458;
    if ((int)uVar6 == 0) {
      return;
    }
    plVar11 = (long *)param_1[0x3b];
    if (plVar11 != (long *)0x0) {
      do {
        while (uStack_68 < (ulong)plVar11[4]) {
          plVar11 = (long *)*plVar11;
          if (plVar11 == (long *)0x0) goto LAB_1001483d0;
        }
        if (uStack_68 <= (ulong)plVar11[4]) {
          if (plVar11 != param_1 + 0x3b) {
            pmVar5 = pmRam0000000100cae458;
            _os_log_type_enabled(pmRam0000000100cae458,0);
            if ((int)pmVar5 == 0) {
              return;
            }
            FUN_10010aa84(&uStack_90,uVar7);
            puVar3 = (undefined2 *)
                     CONCAT44(uStack_90._4_4_,CONCAT22(uStack_90._2_2_,(undefined2)uStack_90));
            if (-1 < cStack_79) {
              puVar3 = (undefined2 *)&uStack_90;
            }
            uStack_b0 = (undefined4)_UNK_100930b00;
            uStack_ac = SUB84(puVar3,0);
            uStack_a8 = (undefined4)((ulong)puVar3 >> 0x20);
            __os_log_impl(0x100000000,pmVar9,0,
                          "\'%s\' already present in Scan Core Page Scan device set.",&uStack_b0,0xc
                         );
            if (-1 < cStack_79) {
              return;
            }
            __ZdlPv(CONCAT44(uStack_90._4_4_,CONCAT22(uStack_90._2_2_,(undefined2)uStack_90)));
            return;
          }
          break;
        }
        plVar11 = (long *)plVar11[1];
      } while (plVar11 != (long *)0x0);
    }
LAB_1001483d0:
    FUN_1005fcaf8();
    pmVar9 = pmRam0000000100cae458;
    if ((uint)uVar7 < 5) {
      pmVar5 = pmRam0000000100cae458;
      _os_log_type_enabled(pmRam0000000100cae458,0);
      if ((int)pmVar5 != 0) {
        FUN_10010aa84(&uStack_90,uStack_68);
        puVar3 = (undefined2 *)
                 CONCAT44(uStack_90._4_4_,CONCAT22(uStack_90._2_2_,(undefined2)uStack_90));
        if (-1 < cStack_79) {
          puVar3 = (undefined2 *)&uStack_90;
        }
        uStack_b0 = (undefined4)_UNK_100930b18;
        uStack_ac = SUB84(puVar3,0);
        uStack_a8 = (undefined4)((ulong)puVar3 >> 0x20);
        uStack_a4 = 0x400;
        uStack_a2 = 0x3c;
        __os_log_impl(0x100000000,pmVar9,0,
                      "\'%s\' not present in Scan Core Page Scan device set. Inserting it and resetting timer for %d seconds."
                      ,&uStack_b0,0x12);
        if (cStack_79 < '\0') {
          __ZdlPv(CONCAT44(uStack_90._4_4_,CONCAT22(uStack_90._2_2_,(undefined2)uStack_90)));
        }
      }
      uVar7 = uStack_68;
      FUN_1005fcaf8();
      if ((uint)uVar7 < 4) {
        *(char *)(param_1 + 0x3f) = (char)param_5;
      }
    }
    else {
      cVar4 = (char)param_1[0x3f];
      pmVar5 = pmRam0000000100cae458;
      _os_log_type_enabled(pmRam0000000100cae458,0);
      if (param_5 - cVar4 < 10) {
        if ((int)pmVar5 != 0) {
          FUN_10010aa84(&uStack_b0,uStack_68);
          puVar1 = (undefined4 *)CONCAT44(uStack_ac,uStack_b0);
          if (-1 < cStack_99) {
            puVar1 = &uStack_b0;
          }
          pcVar10 = "SCAN_CORE_PAGE_SCAN_ENABLE";
          if ((int)param_1[0x3d] != 1) {
            pcVar10 = "unknown";
          }
          uStack_90._0_2_ = (undefined2)_UNK_100930f98;
          uStack_90._2_2_ = (undefined2)((ulong)_UNK_100930f98 >> 0x10);
          uStack_90._4_4_ = (int)puVar1;
          uStack_88 = (undefined2)((ulong)puVar1 >> 0x20);
          sStack_86 = (short)((ulong)puVar1 >> 0x30);
          pcVar2 = "SCAN_CORE_PAGE_SCAN_IDLE";
          if ((int)param_1[0x3d] != 0) {
            pcVar2 = pcVar10;
          }
          uStack_78 = SUB86(pcVar2,0);
          pcVar10 = 
          "Reached maximum Scan Core Page Scan retries for Device \'%s\', Event: %s, State: %s.";
          goto LAB_100148618;
        }
        goto LAB_100148634;
      }
      if ((int)pmVar5 != 0) {
        FUN_10010aa84(&uStack_b0,uStack_68);
        puVar1 = (undefined4 *)CONCAT44(uStack_ac,uStack_b0);
        if (-1 < cStack_99) {
          puVar1 = &uStack_b0;
        }
        uStack_90._0_2_ = (undefined2)_UNK_1009356d0;
        uStack_90._2_2_ = (undefined2)((ulong)_UNK_1009356d0 >> 0x10);
        uStack_88 = 0x400;
        sStack_86 = (short)cVar4;
        sStack_84 = (short)(cVar4 >> 7);
        pcStack_82 = (char *)0x8200000000a0400;
        uStack_7a = SUB81(puVar1,0);
        cStack_79 = (char)((ulong)puVar1 >> 8);
        uStack_78 = (undefined6)((ulong)puVar1 >> 0x10);
        uStack_90._4_4_ = param_5;
        __os_log_impl(0x100000000,pmVar9,0,
                      "Difference between currentLEAdvRSSI: %d and previousLEAdvRSSI:%d is greater than %d dB for device \'%s\'"
                      ,&uStack_90,0x1e);
        if (cStack_99 < '\0') {
          __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
        }
      }
      uVar7 = uStack_68;
      FUN_100136bd8();
      if ((int)uVar7 != 0) {
        FUN_1001370ac(uStack_68);
        *(short *)(uStack_68 + 0x666) = *(short *)(uStack_68 + 0x666) + 1;
      }
      FUN_100137068();
    }
    FUN_10044d9f8(param_1 + 0x3a,&uStack_68);
    FUN_10013dc38(param_1);
    FUN_100139d70(param_1,0x3c);
    FUN_1005fcaac(uStack_68);
  }
  else {
    if ((int)param_1[0x3d] != 0) {
      return;
    }
    if (param_2 == 2) {
      pmVar5 = pmRam0000000100cae458;
      _os_log_type_enabled(pmRam0000000100cae458,0x11);
      if ((int)pmVar5 == 0) {
        return;
      }
      FUN_1008e2754(pmVar9);
      return;
    }
    if (param_2 == 1) {
      plVar11 = (long *)param_1[0x3b];
      if (plVar11 != (long *)0x0) {
        do {
          while ((ulong)plVar11[4] <= uStack_68) {
            if (uStack_68 <= (ulong)plVar11[4]) {
              if ((plVar11 != param_1 + 0x3b) &&
                 (pmVar5 = pmRam0000000100cae458, _os_log_type_enabled(pmRam0000000100cae458,0x11),
                 (int)pmVar5 != 0)) {
                FUN_10010aa84(&uStack_b0,uVar7);
                puVar1 = (undefined4 *)CONCAT44(uStack_ac,uStack_b0);
                if (-1 < cStack_99) {
                  puVar1 = &uStack_b0;
                }
                pcVar10 = "SCAN_CORE_PAGE_SCAN_ENABLE";
                if ((int)param_1[0x3d] != 1) {
                  pcVar10 = "unknown";
                }
                uStack_90._0_2_ = (undefined2)_UNK_100930f98;
                uStack_90._2_2_ = (undefined2)((ulong)_UNK_100930f98 >> 0x10);
                uStack_90._4_4_ = (int)puVar1;
                uStack_88 = (undefined2)((ulong)puVar1 >> 0x20);
                sStack_86 = (short)((ulong)puVar1 >> 0x30);
                sStack_84 = 0x820;
                pcStack_82 = "DEVICE_CONNECTED_EVENT";
                pcVar2 = "SCAN_CORE_PAGE_SCAN_IDLE";
                if ((int)param_1[0x3d] != 0) {
                  pcVar2 = pcVar10;
                }
                uStack_7a = 0x20;
                cStack_79 = '\b';
                uStack_78 = SUB86(pcVar2,0);
                uStack_72 = 0;
                __os_log_fault_impl(0x100000000,pmVar9,0x11,
                                    "\'%s\' present in Scan Core Page Scan device set. Event: %s, State: %s."
                                    ,&uStack_90,0x20);
                uVar7 = uStack_68;
                if (cStack_99 < '\0') {
                  __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
                  uVar7 = uStack_68;
                }
              }
              goto LAB_100147e2c;
            }
            plVar11 = (long *)plVar11[1];
            if (plVar11 == (long *)0x0) goto LAB_100147e2c;
          }
          plVar11 = (long *)*plVar11;
        } while (plVar11 != (long *)0x0);
      }
LAB_100147e2c:
      FUN_100137068(uVar7);
      *(short *)(uStack_68 + 0x66c) = *(short *)(uStack_68 + 0x66c) + 1;
      uVar7 = uStack_68;
      FUN_100136bd8();
      if ((int)uVar7 == 0) {
        return;
      }
      FUN_1001370ac(uStack_68);
      *(short *)(uStack_68 + 0x666) = *(short *)(uStack_68 + 0x666) + 1;
      return;
    }
    if (param_2 != 0) {
      return;
    }
    plVar11 = (long *)param_1[0x3b];
    if (plVar11 != (long *)0x0) {
      do {
        while ((ulong)plVar11[4] <= uStack_68) {
          if (uStack_68 <= (ulong)plVar11[4]) {
            if ((plVar11 != param_1 + 0x3b) &&
               (pmVar5 = pmRam0000000100cae458, _os_log_type_enabled(pmRam0000000100cae458,0x11),
               (int)pmVar5 != 0)) {
              FUN_10010aa84(&uStack_b0,uVar7);
              puVar1 = (undefined4 *)CONCAT44(uStack_ac,uStack_b0);
              if (-1 < cStack_99) {
                puVar1 = &uStack_b0;
              }
              pcVar10 = "SCAN_CORE_PAGE_SCAN_ENABLE";
              if ((int)param_1[0x3d] != 1) {
                pcVar10 = "unknown";
              }
              uStack_90._0_2_ = (undefined2)_UNK_100930f98;
              uStack_90._2_2_ = (undefined2)((ulong)_UNK_100930f98 >> 0x10);
              uStack_90._4_4_ = (int)puVar1;
              uStack_88 = (undefined2)((ulong)puVar1 >> 0x20);
              sStack_86 = (short)((ulong)puVar1 >> 0x30);
              sStack_84 = 0x820;
              pcStack_82 = "DEVICE_ADV_RECEIVED_EVENT";
              pcVar2 = "SCAN_CORE_PAGE_SCAN_IDLE";
              if ((int)param_1[0x3d] != 0) {
                pcVar2 = pcVar10;
              }
              uStack_7a = 0x20;
              cStack_79 = '\b';
              uStack_78 = SUB86(pcVar2,0);
              uStack_72 = 0;
              __os_log_fault_impl(0x100000000,pmVar9,0x11,
                                  "\'%s\' present in Scan Core Page Scan device set. Event: %s, State: %s."
                                  ,&uStack_90,0x20);
              uVar7 = uStack_68;
              if (cStack_99 < '\0') {
                __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
                uVar7 = uStack_68;
              }
            }
            goto LAB_100147e84;
          }
          plVar11 = (long *)plVar11[1];
          if (plVar11 == (long *)0x0) goto LAB_100147e84;
        }
        plVar11 = (long *)*plVar11;
      } while (plVar11 != (long *)0x0);
    }
LAB_100147e84:
    iVar12 = (int)uVar7;
    FUN_1000cbaf4();
    if (iVar12 == 0) {
      return;
    }
    uVar7 = uStack_68;
    FUN_1000cb9c8();
    if ((uVar7 & 1) != 0) {
      return;
    }
    uVar7 = uStack_68;
    FUN_1001070b4(uStack_68,0xc);
    if ((int)uVar7 == 0) {
      return;
    }
    uVar7 = uStack_68;
    FUN_1005fcaf8();
    pmVar9 = pmRam0000000100cae458;
    if ((uint)uVar7 < 5) {
      pmVar5 = pmRam0000000100cae458;
      _os_log_type_enabled(pmRam0000000100cae458,0);
      if ((int)pmVar5 != 0) {
        FUN_10010aa84(&uStack_90,uStack_68);
        puVar3 = (undefined2 *)
                 CONCAT44(uStack_90._4_4_,CONCAT22(uStack_90._2_2_,(undefined2)uStack_90));
        if (-1 < cStack_79) {
          puVar3 = (undefined2 *)&uStack_90;
        }
        uStack_b0 = (undefined4)_UNK_100930b00;
        uStack_ac = SUB84(puVar3,0);
        uStack_a8 = (undefined4)((ulong)puVar3 >> 0x20);
        __os_log_impl(0x100000000,pmVar9,0,"Adding \'%s\' into Scan Core Page Scan device set.",
                      &uStack_b0,0xc);
        if (cStack_79 < '\0') {
          __ZdlPv(CONCAT44(uStack_90._4_4_,CONCAT22(uStack_90._2_2_,(undefined2)uStack_90)));
        }
      }
      uVar7 = uStack_68;
      FUN_1005fcaf8();
      if ((uint)uVar7 < 4) {
        *(char *)(param_1 + 0x3f) = (char)param_5;
      }
      plVar11 = param_1 + 0x3a;
      FUN_10044d9f8(plVar11,&uStack_68);
      FUN_1000071f0();
      (**(code **)(*plVar11 + 0x1198))();
      FUN_100139d70(param_1,0x3c);
      FUN_100136f98(param_1,1);
      FUN_1005fcaac(uStack_68);
      *(short *)(uStack_68 + 0x654) = *(short *)(uStack_68 + 0x654) + 1;
      return;
    }
    cVar4 = (char)param_1[0x3f];
    pmVar5 = pmRam0000000100cae458;
    _os_log_type_enabled(pmRam0000000100cae458,0);
    if (9 < param_5 - cVar4) {
      if ((int)pmVar5 != 0) {
        FUN_10010aa84(&uStack_b0,uStack_68);
        puVar1 = (undefined4 *)CONCAT44(uStack_ac,uStack_b0);
        if (-1 < cStack_99) {
          puVar1 = &uStack_b0;
        }
        uStack_90._0_2_ = (undefined2)_UNK_1009356d0;
        uStack_90._2_2_ = (undefined2)((ulong)_UNK_1009356d0 >> 0x10);
        uStack_88 = 0x400;
        sStack_86 = (short)cVar4;
        sStack_84 = (short)(cVar4 >> 7);
        pcStack_82 = (char *)0x8200000000a0400;
        uStack_7a = SUB81(puVar1,0);
        cStack_79 = (char)((ulong)puVar1 >> 8);
        uStack_78 = (undefined6)((ulong)puVar1 >> 0x10);
        uStack_90._4_4_ = param_5;
        __os_log_impl(0x100000000,pmVar9,0,
                      "Difference between currentLEAdvRSSI: %d and previousLEAdvRSSI:%d is greater than %d dB for device \'%s\'"
                      ,&uStack_90,0x1e);
        if (cStack_99 < '\0') {
          __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
        }
      }
      uVar7 = uStack_68;
      FUN_100136bd8();
      if ((int)uVar7 != 0) {
        FUN_1001370ac(uStack_68);
        *(short *)(uStack_68 + 0x666) = *(short *)(uStack_68 + 0x666) + 1;
      }
      FUN_100137068();
      plVar11 = param_1 + 0x3a;
      FUN_10044d9f8(plVar11,&uStack_68);
      FUN_1000071f0();
      (**(code **)(*plVar11 + 0x1198))(*plVar11 + 0x1198);
      FUN_100139d70(param_1,0x3c);
      FUN_100136f98(param_1,1);
      FUN_1005fcaac(uStack_68);
      *(short *)(uStack_68 + 0x654) = *(short *)(uStack_68 + 0x654) + 1;
      *(short *)(uStack_68 + 0x662) = *(short *)(uStack_68 + 0x662) + 1;
      return;
    }
    if ((int)pmVar5 != 0) {
      FUN_10010aa84(&uStack_b0,uStack_68);
      puVar1 = (undefined4 *)CONCAT44(uStack_ac,uStack_b0);
      if (-1 < cStack_99) {
        puVar1 = &uStack_b0;
      }
      pcVar10 = "SCAN_CORE_PAGE_SCAN_ENABLE";
      if ((int)param_1[0x3d] != 1) {
        pcVar10 = "unknown";
      }
      uStack_90._0_2_ = (undefined2)_UNK_100930f98;
      uStack_90._2_2_ = (undefined2)((ulong)_UNK_100930f98 >> 0x10);
      uStack_90._4_4_ = (int)puVar1;
      uStack_88 = (undefined2)((ulong)puVar1 >> 0x20);
      sStack_86 = (short)((ulong)puVar1 >> 0x30);
      pcVar2 = "SCAN_CORE_PAGE_SCAN_IDLE";
      if ((int)param_1[0x3d] != 0) {
        pcVar2 = pcVar10;
      }
      uStack_78 = SUB86(pcVar2,0);
      pcVar10 = "Reached max Scan Core Page Scan retries for Device \'%s\', Event: %s, State: %s.";
LAB_100148618:
      uStack_72 = 0;
      cStack_79 = '\b';
      uStack_7a = 0x20;
      pcStack_82 = "DEVICE_ADV_RECEIVED_EVENT";
      sStack_84 = 0x820;
      __os_log_impl(0x100000000,pmVar9,0,pcVar10,&uStack_90,0x20);
      if (cStack_99 < '\0') {
        __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
      }
    }
LAB_100148634:
    uVar7 = uStack_68;
    FUN_100136bd8();
    if ((uVar7 & 1) == 0) {
      FUN_1005fcb40(uStack_68);
    }
  }
  return;
}


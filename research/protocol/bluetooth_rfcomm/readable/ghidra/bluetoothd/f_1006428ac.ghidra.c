/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1006428ac
 * original code SHA256: b3b44e7197ef18f41375f68d0b9affa7b146635b34f60771eb110b39995d4fe3
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1006428ac(long *param_1,ulong param_2,int param_3)

{
  undefined8 *******pppppppuVar1;
  bool bVar2;
  long *plVar3;
  ulong uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  ulong *puVar7;
  ulong uVar8;
  ulong *puVar9;
  long lVar10;
  undefined8 ******appppppuStack_b8 [2];
  char cStack_a1;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined2 uStack_94;
  undefined2 uStack_92;
  undefined6 uStack_90;
  undefined1 uStack_8a;
  char cStack_89;
  undefined4 uStack_88;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined8 uStack_70;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  plVar3 = param_1;
  FUN_1000071b8();
  (**(code **)(*plVar3 + 0x38))();
  if ((int)plVar3 == 0) {
    return;
  }
  uVar8 = param_2;
  FUN_1000731bc(param_2,0x80000);
  if ((int)uVar8 != 4) {
    return;
  }
  if (lRam0000000100c1ed10 != -1) {
    thunk_FUN_1000b0540();
  }
  plVar3 = plRam0000000100c1ed08;
  (**(code **)(*plRam0000000100c1ed08 + 0x88))(plRam0000000100c1ed08,param_2);
  if (((ulong)plVar3 & 1) != 0) {
    return;
  }
  if (lRam0000000100c1ed10 != -1) {
    thunk_FUN_1000b0540();
  }
  plVar3 = plRam0000000100c1ed08;
  (**(code **)(*plRam0000000100c1ed08 + 0x78))(plRam0000000100c1ed08,param_2);
  if (param_3 == 0x80000) {
    return;
  }
  if (((ulong)plVar3 & 1) != 0) {
    return;
  }
  if (lRam0000000100c1ed10 != -1) {
    thunk_FUN_1000b0540(0);
  }
  plVar3 = plRam0000000100c1ed08;
  FUN_10040e8a8(plRam0000000100c1ed08,param_2);
  uVar8 = uRam0000000100cae440;
  if ((int)plVar3 != 0) {
    uVar4 = uRam0000000100cae440;
    _os_log_type_enabled(uRam0000000100cae440,0);
    if ((int)uVar4 != 0) {
      FUN_10010aa84(&uStack_a0,param_2);
      puVar5 = (undefined4 *)CONCAT44(uStack_9c,uStack_a0);
      if (-1 < cStack_89) {
        puVar5 = &uStack_a0;
      }
      uStack_80 = (undefined4)_UNK_100930b20;
      uStack_7c = SUB84(puVar5,0);
      uStack_78 = (undefined4)((ulong)puVar5 >> 0x20);
      __os_log_impl(0x100000000,uVar8,0,
                    "Remove %{public}s from stale AACP connection device list and return false",
                    &uStack_80,0xc);
      if (cStack_89 < '\0') {
        __ZdlPv(CONCAT44(uStack_9c,uStack_a0));
      }
    }
    if (lRam0000000100c1ed10 != -1) {
      FUN_1008df45c();
    }
    FUN_10040e8d4(plRam0000000100c1ed08,param_2);
    return;
  }
  uStack_60 = 0;
  uStack_58 = 0;
  FUN_100006ef8(&uStack_60,param_1 + 0x1a);
  lVar10 = param_1[0x23];
  uVar8 = param_1[0x26];
  plVar3 = (long *)(lVar10 + (uVar8 / 0x66) * 8);
  if (param_1[0x24] == lVar10) {
    puVar9 = (ulong *)0x0;
  }
  else {
    puVar9 = (ulong *)(*plVar3 + (uVar8 % 0x66) * 0x28);
  }
  while( true ) {
    if (param_1[0x24] == lVar10) {
      puVar7 = (ulong *)0x0;
    }
    else {
      puVar7 = (ulong *)(*(long *)(lVar10 + ((param_1[0x27] + uVar8) / 0x66) * 8) +
                        ((param_1[0x27] + uVar8) % 0x66) * 0x28);
    }
    if (puVar9 == puVar7) goto LAB_100642bf4;
    if ((*puVar9 == param_2) && ((*(byte *)((long)puVar9 + 0x1a) >> 3 & 1) != 0)) break;
    puVar9 = puVar9 + 5;
    if ((long)puVar9 - *plVar3 == 0xff0) {
      plVar3 = plVar3 + 1;
      puVar9 = (ulong *)*plVar3;
    }
  }
  if (lRam0000000100c1b990 != -1) {
    FUN_1008df5ec();
  }
  uVar8 = uRam0000000100c1b988;
  FUN_1005e0944(uRam0000000100c1b988,param_2);
  if (((uint)uVar8 >> 0x13 & 1) == 0) {
    if (lRam0000000100c1b990 != -1) {
      FUN_1008df5ec();
    }
    uVar4 = uRam0000000100c1b988;
    FUN_1005e08bc(uRam0000000100c1b988,param_2,0x80000);
    uVar8 = uRam0000000100cae440;
    if ((uVar4 & 1) != 0) {
      uVar4 = uRam0000000100cae440;
      _os_log_type_enabled(uRam0000000100cae440,0);
      if ((int)uVar4 != 0) {
        FUN_10010aa84(&uStack_a0,param_2);
        puVar5 = (undefined4 *)CONCAT44(uStack_9c,uStack_a0);
        if (-1 < cStack_89) {
          puVar5 = &uStack_a0;
        }
        uStack_80 = (undefined4)_UNK_100930b20;
        uStack_7c = SUB84(puVar5,0);
        uStack_78 = (undefined4)((ulong)puVar5 >> 0x20);
        __os_log_impl(0x100000000,uVar8,0,
                      "Connection request list for %{public}s has AACP -- Condition for waiting not met"
                      ,&uStack_80,0xc);
        if (cStack_89 < '\0') {
          __ZdlPv(CONCAT44(uStack_9c,uStack_a0));
        }
      }
LAB_100642bf4:
      bVar2 = false;
      goto LAB_100642bf8;
    }
  }
  uVar8 = uRam0000000100cae440;
  uVar4 = uRam0000000100cae440;
  _os_log_type_enabled(uRam0000000100cae440,0);
  if ((int)uVar4 != 0) {
    FUN_10010aa84(&uStack_a0,param_2);
    puVar5 = (undefined4 *)CONCAT44(uStack_9c,uStack_a0);
    if (-1 < cStack_89) {
      puVar5 = &uStack_a0;
    }
    uStack_80 = (undefined4)_UNK_100930b20;
    uStack_7c = SUB84(puVar5,0);
    uStack_78 = (undefined4)((ulong)puVar5 >> 0x20);
    __os_log_impl(0x100000000,uVar8,0,
                  "Connection request list for %{public}s has AACP pending -- Wait for it to complete"
                  ,&uStack_80,0xc);
    if (cStack_89 < '\0') {
      __ZdlPv(CONCAT44(uStack_9c,uStack_a0));
    }
  }
  bVar2 = true;
LAB_100642bf8:
  if (param_1[0x24] == param_1[0x23]) {
    puVar7 = (ulong *)0x0;
  }
  else {
    puVar7 = (ulong *)(*(long *)(param_1[0x23] + ((ulong)(param_1[0x27] + param_1[0x26]) / 0x66) * 8
                                ) + ((ulong)(param_1[0x27] + param_1[0x26]) % 0x66) * 0x28);
  }
  if (puVar9 == puVar7) {
    uStack_80 = 0;
    uStack_7c = 0;
    uStack_78 = 0;
    uStack_74 = 0;
    uStack_70 = 0;
    if (lRam0000000100c1ed40 != -1) {
      FUN_1008df7bc();
    }
    FUN_1007dfb24(uRam0000000100c1ed38,&uStack_80);
    puVar5 = &uStack_80;
    FUN_10010c330(puVar5,param_2);
    uVar8 = uRam0000000100cae440;
    uVar6 = 0x10;
    if (((ulong)puVar5 & 1) == 0) {
      lVar10 = param_1[0x27];
      uVar6 = 8;
      if (lVar10 != 0) {
        uVar6 = 0x10;
      }
      uVar4 = uRam0000000100cae440;
      _os_log_type_enabled(uRam0000000100cae440,0);
      if ((uVar4 & 1) != 0) {
        FUN_10010aa84(appppppuStack_b8,param_2);
        pppppppuVar1 = (undefined8 *******)appppppuStack_b8[0];
        if (-1 < cStack_a1) {
          pppppppuVar1 = appppppuStack_b8;
        }
        uStack_a0 = (undefined4)_UNK_100930500;
        uStack_9c = (undefined4)lVar10;
        uStack_98 = (undefined4)((ulong)lVar10 >> 0x20);
        uStack_94 = 0x822;
        uStack_92 = SUB82(pppppppuVar1,0);
        uStack_90 = (undefined6)((ulong)pppppppuVar1 >> 0x10);
        uStack_8a = 0;
        cStack_89 = 4;
        uStack_88 = uVar6;
        __os_log_impl(0x100000000,uVar8,0,
                      "Connection request queue size is %luu. Initite AACP client connection request for %{public}s using watchdog stall timeout as %d seconds"
                      ,&uStack_a0,0x1c);
        if (cStack_a1 < '\0') {
          __ZdlPv(appppppuStack_b8[0]);
        }
      }
      uStack_a0 = 0;
      uStack_9c = 0;
      uStack_98 = 0;
      uStack_94 = 0;
      uStack_92 = 0;
      uStack_90 = 0;
      uStack_8a = 0;
      cStack_89 = '\0';
      FUN_100641d2c(param_1,param_2,0x80000,&uStack_a0,2);
      if (cStack_89 < '\0') {
        __ZdlPv(CONCAT44(uStack_9c,uStack_a0));
      }
      if ((int)param_1 == 0) {
        bVar2 = true;
      }
    }
    if (CONCAT44(uStack_7c,uStack_80) != 0) {
      uStack_78 = uStack_80;
      uStack_74 = uStack_7c;
      __ZdlPv();
    }
    FUN_100006ec0(&uStack_60);
    if (!bVar2) {
      return;
    }
  }
  else {
    FUN_100006ec0(&uStack_60);
    if (!bVar2) {
      return;
    }
    uVar6 = 0x10;
  }
  uVar8 = param_2;
  FUN_1005fd18c();
  if ((uVar8 & 1) == 0) {
    FUN_1005fcd8c(param_2,uVar6);
  }
  return;
}


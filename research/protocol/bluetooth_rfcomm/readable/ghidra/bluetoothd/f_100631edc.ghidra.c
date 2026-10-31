/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100631edc
 * original code SHA256: 905d021d5dd3e6edbd69462b52dac371b4256a239e7553779c892ffb3693ba79
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_100631edc(long param_1,int param_2)

{
  undefined8 uVar1;
  undefined *puVar2;
  long *plVar3;
  char *pcVar4;
  int iVar5;
  long lVar6;
  undefined8 uVar7;
  long lVar8;
  uint uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined2 uStack_84;
  undefined2 uStack_82;
  undefined6 uStack_80;
  char cStack_79;
  undefined4 uStack_70;
  char *pcStack_6c;
  undefined2 uStack_64;
  undefined1 *puStack_62;
  
  if (plRam0000000100c3de88 == (long *)0x0) {
    plVar3 = (long *)0xd8;
    _malloc_type_malloc(0xd8,0x1020040c4bbd58b);
    lVar8 = *(long *)(param_1 + 0x70);
    plRam0000000100c3de88 = plVar3;
    *plVar3 = lVar8;
    *(undefined4 *)(plVar3 + 0x1a) = 0;
    *(undefined1 *)((long)plVar3 + 0xd4) = 0;
  }
  else {
    lVar8 = *plRam0000000100c3de88;
    plVar3 = plRam0000000100c3de88;
  }
  uVar7 = uRam0000000100cae4a0;
  if (lVar8 == 0) {
    uVar1 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0x10);
    if ((int)uVar1 != 0) {
      FUN_1008de588(uVar7);
    }
  }
  else {
    uVar1 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar1 != 0) {
      pcVar4 = "Connecting to";
      if ((int)plVar3[0x1a] != 0) {
        pcVar4 = "Retrying connection to";
      }
      FUN_10010aa84(&uStack_90,lVar8);
      puStack_62 = (undefined1 *)CONCAT44(uStack_8c,uStack_90);
      if (-1 < cStack_79) {
        puStack_62 = (undefined1 *)&uStack_90;
      }
      uStack_70 = (undefined4)_UNK_1009316b0;
      uStack_64 = 0x822;
      pcStack_6c = pcVar4;
      __os_log_impl(0x100000000,uVar7,0,"%{public}s SDP server for device %{public}s",&uStack_70,
                    0x16);
      uVar7 = uRam0000000100cae4a0;
      if (cStack_79 < '\0') {
        __ZdlPv(CONCAT44(uStack_8c,uStack_90));
        uVar7 = uRam0000000100cae4a0;
      }
    }
    uVar1 = uVar7;
    _os_log_type_enabled(uVar7,0);
    if ((int)uVar1 != 0) {
      if (*(uint *)(lRam0000000100cae158 + 0x84) < 0xb) {
        pcVar4 = (&PTR_s_SDP_IDLE_STATE_100bbde30)[*(uint *)(lRam0000000100cae158 + 0x84)];
      }
      else {
        pcVar4 = "unknown sdp state";
      }
      uStack_90 = (uint)_UNK_100930b18;
      uStack_8c = SUB84(pcVar4,0);
      uStack_88 = (undefined4)((ulong)pcVar4 >> 0x20);
      uStack_84 = 0x820;
      uStack_82 = 0xbaeb;
      uStack_80 = 0x100a6;
      __os_log_impl(0x100000000,uVar7,0,"SDP Client State Change: %s -> %s\n",&uStack_90,0x16);
    }
    *(undefined4 *)(lRam0000000100cae158 + 0x84) = 1;
    iVar5 = (int)*plRam0000000100c3de88;
    FUN_1005e8f14();
    uVar7 = uRam0000000100cae4a0;
    if (iVar5 != 0) {
      uVar1 = uRam0000000100cae4a0;
      _os_log_type_enabled(uRam0000000100cae4a0,0);
      if ((int)uVar1 != 0) {
        FUN_10010aa84(&uStack_90,*plRam0000000100c3de88);
        pcStack_6c = (char *)CONCAT44(uStack_8c,uStack_90);
        if (-1 < cStack_79) {
          pcStack_6c = (char *)&uStack_90;
        }
        uStack_70 = (undefined4)_UNK_100930b20;
        __os_log_impl(0x100000000,uVar7,0,
                      "Applying SDP workaround for Type S Game Controllers to device %{public}s",
                      &uStack_70,0xc);
        if (cStack_79 < '\0') {
          __ZdlPv(CONCAT44(uStack_8c,uStack_90));
        }
      }
      FUN_1003c8ef8();
    }
    if (param_2 == 0) {
      uStack_90 = uStack_90 & 0xffffff00;
      FUN_100061a60(&uStack_90);
      puVar2 = &DAT_100632354;
      FUN_1003c8f08(&DAT_100632354,&LAB_1006323dc,*plRam0000000100c3de88 + 0x80);
      FUN_10006b538(&uStack_90);
      iVar5 = (int)puVar2;
      uVar7 = uRam0000000100cae4a0;
    }
    else {
      puVar2 = &DAT_100632354;
      FUN_1003c8f08(&DAT_100632354,&LAB_1006323dc,*plRam0000000100c3de88 + 0x80);
      iVar5 = (int)puVar2;
      uVar7 = uRam0000000100cae4a0;
    }
    if (iVar5 == 0) {
      uRam0000000100cae4a0 = uVar7;
      return 0;
    }
    uVar1 = uVar7;
    uRam0000000100cae4a0 = uVar7;
    _os_log_type_enabled(uVar7,0x10);
    if ((int)uVar1 != 0) {
      FUN_1008de48c(puVar2,uVar7);
    }
    uStack_90 = 0;
    uStack_8c = 0;
    uStack_88 = 0;
    uStack_84 = 0;
    uStack_82 = 0;
    FUN_100006ef8(&uStack_90,0x100cae118);
    lVar8 = lRam0000000100cae158;
    if (lRam0000000100cae158 == 0) {
      FUN_1000f9438();
      lVar8 = lRam0000000100cae158;
    }
    lRam0000000100cae158 = 0;
    if (lRam0000000100cae188 != 0) {
      lVar6 = *(long *)(*(long *)(lRam0000000100cae168 +
                                 (uRam0000000100cae180 >> 6 & 0x3fffffffffffff8)) +
                       (uRam0000000100cae180 & 0x1ff) * 8);
      FUN_100600fe8();
      lRam0000000100cae158 = lVar6;
    }
    lVar6 = lRam0000000100cae158;
    FUN_100006f28(&uStack_90);
    plVar3 = *(long **)(lVar8 + 0x78);
    if (plVar3 != (long *)0x0) {
      (**(code **)(*plVar3 + 0x10))(plVar3,lVar8,0x135);
    }
    thunk_FUN_1000936c8(lVar8 + 0x30);
    FUN_1005ab890(lVar8);
    __ZdlPvSt19__type_descriptor_t();
    uVar7 = uRam0000000100cae4a0;
    if (lVar6 != 0) {
      if ((*(char *)((long)plRam0000000100c3de88 + 0xd4) == '\x01') &&
         (uVar1 = uRam0000000100cae4a0, _os_log_type_enabled(uRam0000000100cae4a0,0x11),
         (int)uVar1 != 0)) {
        FUN_1008de534(uVar7);
      }
      FUN_100631edc(lVar6,1);
    }
    FUN_100006ec0(&uStack_90);
  }
  return 1;
}


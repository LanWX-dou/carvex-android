/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10063240c
 * original code SHA256: 0d82214fd2b41053a25667594176147dd62c8c92a596f95b549cf6fec59660be
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10063240c(void)

{
  byte bVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  undefined1 *puVar6;
  undefined *puVar7;
  undefined4 uVar8;
  char *pcVar9;
  short sStack_a2;
  undefined8 uStack_a0;
  undefined *puStack_98;
  uint uStack_90;
  char *pcStack_8c;
  undefined2 uStack_84;
  uint uStack_82;
  undefined2 uStack_7e;
  undefined2 uStack_7c;
  undefined2 uStack_7a;
  undefined2 uStack_78;
  undefined4 uStack_76;
  undefined2 uStack_72;
  uint uStack_70;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  uStack_58 = _UNK_10093a288;
  uStack_60 = _UNK_10093a280;
  lVar3 = *plRam0000000100c3de88;
  FUN_1005ec078(lVar3,&uStack_60);
  uVar2 = uRam0000000100cae4a0;
  uVar4 = uRam0000000100cae4a0;
  _os_log_type_enabled(uRam0000000100cae4a0,0);
  if ((int)uVar4 != 0) {
    if (lRam0000000100cae158 == 0) {
      pcVar9 = "";
    }
    else if (*(uint *)(lRam0000000100cae158 + 0x84) < 0xb) {
      pcVar9 = (&PTR_s_SDP_IDLE_STATE_100bbde30)[*(uint *)(lRam0000000100cae158 + 0x84)];
    }
    else {
      pcVar9 = "unknown sdp state";
    }
    lVar5 = *plRam0000000100c3de88;
    bVar1 = *(byte *)(lVar5 + 0x390);
    FUN_1005ea118();
    uStack_90 = (uint)_UNK_100930ef8;
    uStack_84 = 0x400;
    uStack_82 = (uint)bVar1;
    uStack_7e = 0x400;
    uStack_7c = (undefined2)lVar3;
    uStack_7a = (undefined2)((ulong)lVar3 >> 0x10);
    uStack_78 = 0x400;
    uStack_76 = (undefined4)lVar5;
    uStack_72 = 0x400;
    uStack_70 = (uint)*(byte *)(*plRam0000000100c3de88 + 0x2bf);
    pcStack_8c = pcVar9;
    __os_log_impl(0x100000000,uVar2,0,
                  "Statemachine start: %s, d2d %d, isLocalServiceDiscoveryClassExist %d, AppleBT %d isFullSDPRequired %d"
                  ,&uStack_90,0x24);
  }
  lVar5 = *plRam0000000100c3de88;
  if (*(char *)(lVar5 + 0x390) == '\x01') {
    *(undefined1 *)(lVar5 + 0x390) = 0;
    puStack_98 = PTR_DAT_100bbdbf8;
    uStack_a0 = _UNK_100bbdbf0;
    puVar6 = &LAB_100632924;
    FUN_1003c9720(&LAB_100632924,0x30,&uStack_a0);
    uVar2 = uRam0000000100cae4a0;
    if ((int)puVar6 != 0) goto LAB_1006327d0;
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar4 != 0) {
      if (*(uint *)(lRam0000000100cae158 + 0x84) < 0xb) {
        pcStack_8c = (&PTR_s_SDP_IDLE_STATE_100bbde30)[*(uint *)(lRam0000000100cae158 + 0x84)];
      }
      else {
        pcStack_8c = "unknown sdp state";
      }
      uStack_90 = (uint)_UNK_100930b18;
      uStack_84 = 0x820;
      uStack_82 = 0xa6bb0e;
      uStack_7e = 1;
      uStack_7c = 0;
      __os_log_impl(0x100000000,uVar2,0,"SDP Client State Change: %s -> %s\n",&uStack_90,0x16);
    }
    uVar8 = 3;
  }
  else if (((((int)lVar3 == 0) ||
            (FUN_1005ea150(lVar5,&uStack_60,0x201), uVar2 = uRam0000000100cae4a0, (int)lVar5 == 0))
           || (*(int *)(lRam0000000100cae158 + 0x84) == 7)) ||
          ((*(byte *)(*plRam0000000100c3de88 + 0x2bf) & 1) != 0)) {
    uVar2 = uRam0000000100cae4a0;
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar4 != 0) {
      uStack_90 = uStack_90 & 0xffff0000;
      __os_log_impl(0x100000000,uVar2,0,"Executing full SDP",&uStack_90,2);
    }
    *(undefined1 *)(*plRam0000000100c3de88 + 0x2bf) = 0;
    uStack_a0 = 0;
    puStack_98 = (undefined *)0x0;
    sStack_a2 = 0;
    lVar5 = *(long *)(lRam0000000100cae158 + 0x70);
    lVar3 = lVar5 + 0x80;
    FUN_1003197dc(lVar3,&sStack_a2);
    puVar7 = &DAT_10093a148;
    if (((int)lVar3 == 0) && (sStack_a2 == 0x61)) {
      FUN_1005e8f14();
      uVar2 = uRam0000000100cae4a0;
      if ((int)lVar5 == 0) {
        puVar7 = &DAT_10093a148;
      }
      else {
        uVar4 = uRam0000000100cae4a0;
        _os_log_type_enabled(uRam0000000100cae4a0,0);
        if ((int)uVar4 != 0) {
          uStack_90 = uStack_90 & 0xffff0000;
          __os_log_impl(0x100000000,uVar2,0,
                        "Overriding SDP search for unauthorized Type S controller",&uStack_90,2);
        }
        puVar7 = &UNK_10093a138;
      }
    }
    uVar2 = uStack_a0;
    uStack_a0 = CONCAT71(uStack_a0._1_7_,6);
    uVar4 = uStack_a0;
    uStack_a0._4_4_ = SUB84(uVar2,4);
    uStack_a0._0_4_ = CONCAT22(1,(short)uVar4);
    puVar6 = &LAB_100632924;
    puStack_98 = puVar7;
    FUN_1003c9720(&LAB_100632924,0x30,&uStack_a0);
    uVar2 = uRam0000000100cae4a0;
    if ((int)puVar6 != 0) goto LAB_1006327d0;
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar4 != 0) {
      if (*(uint *)(lRam0000000100cae158 + 0x84) < 0xb) {
        pcStack_8c = (&PTR_s_SDP_IDLE_STATE_100bbde30)[*(uint *)(lRam0000000100cae158 + 0x84)];
      }
      else {
        pcStack_8c = "unknown sdp state";
      }
      uStack_90 = (uint)_UNK_100930b18;
      uStack_84 = 0x820;
      uStack_82 = 0xa6bafd;
      uStack_7e = 1;
      uStack_7c = 0;
      __os_log_impl(0x100000000,uVar2,0,"SDP Client State Change: %s -> %s\n",&uStack_90,0x16);
    }
    uVar8 = 2;
  }
  else {
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar4 != 0) {
      uStack_90 = uStack_90 & 0xffff0000;
      __os_log_impl(0x100000000,uVar2,0,"Executing Service Database State lookup",&uStack_90,2);
    }
    puStack_98 = PTR_DAT_100bbdc08;
    uStack_a0 = _UNK_100bbdc00;
    puVar6 = &LAB_100632af4;
    FUN_1003c9ab8(&LAB_100632af4,0,&uStack_a0);
    uVar2 = uRam0000000100cae4a0;
    if ((int)puVar6 != 0) {
      uVar4 = uRam0000000100cae4a0;
      _os_log_type_enabled(uRam0000000100cae4a0,0x10);
      if ((int)uVar4 != 0) {
        FUN_1008de5d0(puVar6,uVar2);
      }
      goto LAB_1006327d0;
    }
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar4 != 0) {
      pcVar9 = (char *)(ulong)*(uint *)(lRam0000000100cae158 + 0x84);
      FUN_100632330();
      uStack_90 = (uint)_UNK_100930b18;
      uStack_84 = 0x820;
      uStack_82 = 0xa6bb31;
      uStack_7e = 1;
      uStack_7c = 0;
      pcStack_8c = pcVar9;
      __os_log_impl(0x100000000,uVar2,0,"SDP Client State Change: %s -> %s\n",&uStack_90,0x16);
    }
    uVar8 = 5;
  }
  *(undefined4 *)(lRam0000000100cae158 + 0x84) = uVar8;
LAB_1006327d0:
  uVar2 = uRam0000000100cae4a0;
  if ((int)puVar6 != 0) {
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0x10);
    if ((int)uVar4 != 0) {
      FUN_1008de60c(puVar6,uVar2);
    }
    *(undefined4 *)(lRam0000000100cae158 + 0x80) = 0;
    FUN_1006332cc();
  }
  return;
}


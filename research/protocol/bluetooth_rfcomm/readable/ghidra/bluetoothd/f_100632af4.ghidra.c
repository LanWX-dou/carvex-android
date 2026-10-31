/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100632af4
 * original code SHA256: a8e17a32d7b26cbdaf37bc842617884519971a44d32af9107a1dee33f255f822
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void phone_fn_100632af4(byte *param_1,undefined4 param_2,undefined8 param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  ulong uVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  long lVar10;
  undefined8 uVar11;
  undefined4 uStack_90;
  int iStack_8c;
  undefined2 uStack_88;
  undefined2 uStack_86;
  undefined2 uStack_84;
  undefined2 uStack_82;
  undefined6 uStack_80;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined2 uStack_60;
  undefined2 uStack_5e;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined2 uStack_54;
  undefined2 uStack_52;
  undefined2 uStack_50;
  undefined2 uStack_4e;
  undefined2 uStack_4c;
  undefined2 uStack_4a;
  
  uVar11 = uRam0000000100cae4a0;
  uVar4 = uRam0000000100cae4a0;
  _os_log_type_enabled(uRam0000000100cae4a0,0);
  if ((int)uVar4 != 0) {
    if (*(uint *)(lRam0000000100cae158 + 0x84) < 0xb) {
      pcVar7 = (&PTR_s_SDP_IDLE_STATE_100bbde30)[*(uint *)(lRam0000000100cae158 + 0x84)];
    }
    else {
      pcVar7 = "unknown sdp state";
    }
    uStack_60 = (undefined2)_UNK_100930f98;
    uStack_5e = (undefined2)((ulong)_UNK_100930f98 >> 0x10);
    uStack_5c = SUB84(pcVar7,0);
    uStack_58 = (undefined4)((ulong)pcVar7 >> 0x20);
    uStack_54 = 0x400;
    uStack_52 = (undefined2)param_2;
    uStack_50 = (undefined2)((uint)param_2 >> 0x10);
    uStack_4e = 0x400;
    uStack_4c = (undefined2)param_3;
    uStack_4a = (undefined2)((ulong)param_3 >> 0x10);
    __os_log_impl(0x100000000,uVar11,0,
                  "Service database state response with state %s, more %d, status %{bluetooth:OI_STATUS}u"
                  ,&uStack_60,0x18);
  }
  uVar11 = uRam0000000100cae4a0;
  lVar10 = lRam0000000100cae158;
  if ((int)param_3 != 0) {
    if (((int)param_3 == 0x322) && (*(int *)(lRam0000000100cae158 + 0x84) == 5)) {
      uVar4 = uRam0000000100cae4a0;
      _os_log_type_enabled(uRam0000000100cae4a0,0);
      if ((int)uVar4 != 0) {
        uStack_60 = 0;
        __os_log_impl(0x100000000,uVar11,0,
                      "Remote device does not support ServiceDataBaseState restarting full SDP",
                      &uStack_60,2);
        uVar11 = uRam0000000100cae4a0;
        lVar10 = lRam0000000100cae158;
      }
      uVar4 = uVar11;
      _os_log_type_enabled(uVar11,0);
      if ((int)uVar4 != 0) {
        if (*(uint *)(lVar10 + 0x84) < 0xb) {
          pcVar7 = (&PTR_s_SDP_IDLE_STATE_100bbde30)[*(uint *)(lVar10 + 0x84)];
        }
        else {
          pcVar7 = "unknown sdp state";
        }
        uStack_60 = (undefined2)_UNK_100930b18;
        uStack_5e = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
        uStack_5c = SUB84(pcVar7,0);
        uStack_58 = (undefined4)((ulong)pcVar7 >> 0x20);
        uStack_54 = 0x820;
        uStack_52 = 0xbb91;
        uStack_50 = 0xa6;
        uStack_4e = 1;
        uStack_4c = 0;
        __os_log_impl(0x100000000,uVar11,0,"SDP Client State Change: %s -> %s\n",&uStack_60,0x16);
        lVar10 = lRam0000000100cae158;
      }
      *(undefined4 *)(lVar10 + 0x84) = 7;
      FUN_100017938();
      FUN_100007104();
      return;
    }
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0x10);
    if ((int)uVar4 != 0) {
      FUN_1008de714(param_3,uVar11);
    }
    *(undefined4 *)(lRam0000000100cae158 + 0x80) = 1;
    FUN_1006332cc();
    return;
  }
  if ((*param_1 & 0xfe) != 6) {
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0x10);
    if ((int)uVar4 == 0) {
      return;
    }
    FUN_1008de684(uVar11);
    return;
  }
  if (*(int *)(lRam0000000100cae158 + 0x84) != 5) goto LAB_100633128;
  uStack_68 = _UNK_10093a288;
  uStack_70 = _UNK_10093a280;
  uVar4 = uRam0000000100cae4a0;
  _os_log_type_enabled(uRam0000000100cae4a0,0);
  if ((int)uVar4 != 0) {
    uStack_60 = 0;
    __os_log_impl(0x100000000,uVar11,0,"Starting SDP database state matching",&uStack_60,2);
  }
  FUN_1006347c0(param_1);
  uVar11 = uRam0000000100cae4a0;
  lVar10 = lRam0000000100cae158;
  if (*(int *)(lRam0000000100cae158 + 0x8c) == -1) {
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar4 != 0) {
      uVar5 = (ulong)*(uint *)(lVar10 + 0x84);
      FUN_100632330();
      uStack_60 = (undefined2)_UNK_100930b18;
      uStack_5e = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
      uStack_5c = (undefined4)uVar5;
      uStack_58 = (undefined4)(uVar5 >> 0x20);
      uStack_54 = 0x820;
      uStack_52 = 0xbb4a;
      uStack_50 = 0xa6;
      uStack_4e = 1;
      uStack_4c = 0;
      __os_log_impl(0x100000000,uVar11,0,"SDP Client State Change: %s -> %s\n",&uStack_60,0x16);
      lVar10 = lRam0000000100cae158;
    }
    uVar5 = 6;
    *(undefined4 *)(lVar10 + 0x84) = 6;
LAB_100632fc8:
    uVar11 = uRam0000000100cae4a0;
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar4 != 0) {
      FUN_100632330();
      uStack_60 = (undefined2)_UNK_100930b18;
      uStack_5e = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
      uStack_5c = (undefined4)uVar5;
      uStack_58 = (undefined4)(uVar5 >> 0x20);
LAB_100633020:
      uStack_4c = 0;
      uStack_4e = 1;
      uStack_50 = 0xa6;
      uStack_52 = 0xbbb4;
      uStack_54 = 0x820;
      __os_log_impl(0x100000000,uVar11,0,"SDP Client State Change: %s -> %s\n",&uStack_60,0x16);
      lVar10 = lRam0000000100cae158;
    }
LAB_100633030:
    *(undefined4 *)(lVar10 + 0x84) = 9;
  }
  else {
    uStack_60 = 0;
    uStack_5e = 0;
    uStack_5c = 0;
    uStack_58 = 0;
    uStack_54 = 0;
    uStack_52 = 0;
    uStack_50 = 0;
    uStack_4e = 0;
    uStack_4c = 0;
    uStack_4a = 0;
    uVar4 = *(undefined8 *)(lRam0000000100cae158 + 0x70);
    FUN_1005ebdf0(uVar4,&uStack_70,0x201,&uStack_60);
    uVar11 = uRam0000000100cae4a0;
    if (((int)uVar4 != 0) &&
       (pcVar7 = (char *)CONCAT44(uStack_5c,CONCAT22(uStack_5e,uStack_60)), *pcVar7 == '\x01')) {
      iVar3 = *(int *)(pcVar7 + 8);
      uVar4 = uRam0000000100cae4a0;
      _os_log_type_enabled(uRam0000000100cae4a0,0);
      if ((int)uVar4 != 0) {
        uStack_90 = (undefined4)_UNK_1009304c8;
        uStack_88 = 0x400;
        uStack_86 = (undefined2)*(undefined4 *)(lRam0000000100cae158 + 0x8c);
        uStack_84 = (undefined2)((uint)*(undefined4 *)(lRam0000000100cae158 + 0x8c) >> 0x10);
        iStack_8c = iVar3;
        __os_log_impl(0x100000000,uVar11,0,"SdpServiceDataBaseState [local 0x%x, remote 0x%x]",
                      &uStack_90,0xe);
      }
      uVar11 = uRam0000000100cae4a0;
      lVar10 = lRam0000000100cae158;
      iVar1 = *(int *)(lRam0000000100cae158 + 0x8c);
      uVar4 = uRam0000000100cae4a0;
      _os_log_type_enabled(uRam0000000100cae4a0,0);
      if (iVar3 == iVar1) {
        if ((int)uVar4 != 0) {
          uVar5 = (ulong)*(uint *)(lVar10 + 0x84);
          FUN_100632330();
          uStack_90 = (undefined4)_UNK_100930b18;
          iStack_8c = (int)uVar5;
          uStack_88 = (undefined2)(uVar5 >> 0x20);
          uStack_86 = (undefined2)(uVar5 >> 0x30);
          uStack_84 = 0x820;
          uStack_82 = 0xbb6e;
          uStack_80 = 0x100a6;
          __os_log_impl(0x100000000,uVar11,0,"SDP Client State Change: %s -> %s\n",&uStack_90,0x16);
          lVar10 = lRam0000000100cae158;
        }
        uVar6 = 8;
      }
      else {
        if ((int)uVar4 != 0) {
          uVar5 = (ulong)*(uint *)(lVar10 + 0x84);
          FUN_100632330();
          uStack_90 = (undefined4)_UNK_100930b18;
          iStack_8c = (int)uVar5;
          uStack_88 = (undefined2)(uVar5 >> 0x20);
          uStack_86 = (undefined2)(uVar5 >> 0x30);
          uStack_84 = 0x820;
          uStack_82 = 0xbb91;
          uStack_80 = 0x100a6;
          __os_log_impl(0x100000000,uVar11,0,"SDP Client State Change: %s -> %s\n",&uStack_90,0x16);
          lVar10 = lRam0000000100cae158;
        }
        uVar6 = 7;
      }
      *(undefined4 *)(lVar10 + 0x84) = uVar6;
    }
    puVar9 = (undefined8 *)CONCAT44(uStack_5c,CONCAT22(uStack_5e,uStack_60));
    if (puVar9 != (undefined8 *)CONCAT26(uStack_52,CONCAT24(uStack_54,uStack_58))) {
      do {
        puVar8 = puVar9 + 2;
        uVar11 = puVar9[1];
        uStack_88 = (undefined2)uVar11;
        uStack_86 = (undefined2)((ulong)uVar11 >> 0x10);
        uStack_84 = (undefined2)((ulong)uVar11 >> 0x20);
        uStack_82 = (undefined2)((ulong)uVar11 >> 0x30);
        uStack_90 = (undefined4)*puVar9;
        iStack_8c = (int)((ulong)*puVar9 >> 0x20);
        FUN_100457214(&uStack_90);
        puVar9 = puVar8;
      } while (puVar8 != (undefined8 *)CONCAT26(uStack_52,CONCAT24(uStack_54,uStack_58)));
      puVar9 = (undefined8 *)CONCAT44(uStack_5c,CONCAT22(uStack_5e,uStack_60));
    }
    if (puVar9 != (undefined8 *)0x0) {
      uStack_58 = SUB84(puVar9,0);
      uStack_54 = (undefined2)((ulong)puVar9 >> 0x20);
      uStack_52 = (undefined2)((ulong)puVar9 >> 0x30);
      __ZdlPv(puVar9);
    }
    uVar11 = uRam0000000100cae4a0;
    lVar10 = lRam0000000100cae158;
    uVar2 = *(uint *)(lRam0000000100cae158 + 0x84);
    uVar5 = (ulong)uVar2;
    if ((int)uVar2 < 7) {
      if (uVar2 == 5) {
        iVar3 = *(int *)(lRam0000000100cae158 + 0x8c);
        uVar4 = uRam0000000100cae4a0;
        _os_log_type_enabled(uRam0000000100cae4a0,0);
        if (iVar3 == -1) {
          if ((int)uVar4 != 0) {
            uStack_60 = 0;
            __os_log_impl(0x100000000,uVar11,0,
                          "Local database state not found and remote state does not exist, move onto RFCOMM"
                          ,&uStack_60,2);
            uVar11 = uRam0000000100cae4a0;
            lVar10 = lRam0000000100cae158;
          }
          uVar4 = uVar11;
          _os_log_type_enabled(uVar11,0);
          if ((int)uVar4 != 0) {
            uVar5 = (ulong)*(uint *)(lVar10 + 0x84);
            FUN_100632330();
            uStack_60 = (undefined2)_UNK_100930b18;
            uStack_5e = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
            uStack_5c = (undefined4)uVar5;
            uStack_58 = (undefined4)(uVar5 >> 0x20);
            goto LAB_100633020;
          }
          goto LAB_100633030;
        }
        if ((int)uVar4 != 0) {
          uStack_60 = 0;
          __os_log_impl(0x100000000,uVar11,0,
                        "Local database state not found, but remote state exists, full SDP",
                        &uStack_60,2);
          uVar11 = uRam0000000100cae4a0;
          lVar10 = lRam0000000100cae158;
        }
        uVar4 = uVar11;
        _os_log_type_enabled(uVar11,0);
        if ((int)uVar4 != 0) {
          uVar5 = (ulong)*(uint *)(lVar10 + 0x84);
          FUN_100632330();
          uStack_60 = (undefined2)_UNK_100930b18;
          uStack_5e = (undefined2)((ulong)_UNK_100930b18 >> 0x10);
          uStack_5c = (undefined4)uVar5;
          uStack_58 = (undefined4)(uVar5 >> 0x20);
          uStack_54 = 0x820;
          uStack_52 = 0xbb91;
          uStack_50 = 0xa6;
          uStack_4e = 1;
          uStack_4c = 0;
          __os_log_impl(0x100000000,uVar11,0,"SDP Client State Change: %s -> %s\n",&uStack_60,0x16);
          lVar10 = lRam0000000100cae158;
        }
        *(undefined4 *)(lVar10 + 0x84) = 7;
        FUN_100017938();
        FUN_100007104();
      }
      else {
        if (uVar2 == 6) goto LAB_100632fc8;
LAB_1006330c8:
        uVar4 = uRam0000000100cae4a0;
        _os_log_type_enabled(uRam0000000100cae4a0,0x10);
        if ((int)uVar4 != 0) {
          FUN_1008de6b8(uVar5,uVar11);
        }
      }
    }
    else {
      if (uVar2 != 7) {
        if (uVar2 != 8) goto LAB_1006330c8;
        goto LAB_100632fc8;
      }
      FUN_10063240c();
    }
  }
  if (*(int *)(lRam0000000100cae158 + 0x84) == 9) {
    iVar3 = (int)*(undefined8 *)(lRam0000000100cae158 + 0x70);
    FUN_1005fc024();
    uVar11 = uRam0000000100cae4a0;
    uVar4 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if (iVar3 == 0) {
      if ((int)uVar4 != 0) {
        uStack_60 = 0;
        __os_log_impl(0x100000000,uVar11,0,"No RFCOMM services, we\'re done",&uStack_60,2);
      }
      *(undefined4 *)(lRam0000000100cae158 + 0x80) = 0;
      FUN_1006332cc();
    }
    else {
      if ((int)uVar4 != 0) {
        uStack_60 = (undefined2)_UNK_100930ae8;
        uStack_5e = (undefined2)((ulong)_UNK_100930ae8 >> 0x10);
        uStack_5c = (undefined4)*(undefined8 *)(lRam0000000100cae158 + 0x28);
        uStack_58 = (undefined4)((ulong)*(undefined8 *)(lRam0000000100cae158 + 0x28) >> 0x20);
        __os_log_impl(0x100000000,uVar11,0,
                      "Found %lu services supported RFCOMM, starting channel query",&uStack_60,0xc);
      }
      uRam0000000100c1f619 = 0;
      FUN_100634b7c();
    }
  }
LAB_100633128:
  *(undefined4 *)(lRam0000000100cae158 + 0x8c) = 0xffffffff;
  return;
}


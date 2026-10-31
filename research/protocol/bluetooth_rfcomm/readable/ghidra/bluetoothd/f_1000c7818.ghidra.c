/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000c7818
 * original code SHA256: 3fb93c535291d278dfcdae44b5c26b4b6d52bc4d1642b89c38e7593cca84195f
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0001000c8db8) */
/* WARNING: Removing unreachable block (ram,0x0001000c8d80) */
/* WARNING: Removing unreachable block (ram,0x0001000c8e08) */
/* WARNING: Removing unreachable block (ram,0x0001000c8c18) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000c7818(ulong param_1,ulong param_2)

{
  long lVar1;
  byte *pbVar2;
  long lVar3;
  undefined *puVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  ushort uVar7;
  undefined1 uVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  undefined2 uVar13;
  undefined1 uVar14;
  undefined2 uVar15;
  code *pcVar16;
  bool bVar17;
  bool bVar18;
  uint uVar19;
  int iVar20;
  ID IVar21;
  long *plVar22;
  mach_header *pmVar23;
  byte *pbVar24;
  byte *pbVar25;
  undefined8 **ppuVar26;
  undefined1 *puVar27;
  byte *pbVar28;
  ulong uVar29;
  long lVar30;
  ulong uVar31;
  long lVar32;
  undefined8 *puVar33;
  undefined8 *puVar34;
  char *pcVar35;
  undefined4 uVar36;
  undefined8 **ppuVar37;
  undefined8 uVar38;
  char *pcVar39;
  int iVar40;
  long lVar41;
  ulong uVar42;
  ulong uVar43;
  undefined8 *puVar44;
  undefined8 **ppuVar45;
  ulong uVar46;
  uint uVar47;
  mach_header *pmVar48;
  undefined8 *puVar49;
  double dVar50;
  undefined *puStack_5198;
  undefined8 uStack_5190;
  undefined *puStack_5188;
  undefined *puStack_5180;
  ulong uStack_5178;
  undefined4 uStack_5170;
  undefined4 uStack_516c;
  undefined4 uStack_5168;
  undefined4 uStack_5164;
  byte bStack_5159;
  undefined1 uStack_5158;
  undefined7 uStack_5157;
  ulong uStack_5150;
  byte bStack_5141;
  undefined8 uStack_5140;
  undefined2 uStack_5138;
  ushort uStack_5136;
  undefined2 uStack_5134;
  ushort uStack_5132;
  undefined2 uStack_5130;
  undefined2 uStack_512e;
  ushort uStack_512c;
  undefined1 uStack_512a;
  char cStack_5129;
  undefined2 uStack_5128;
  ushort uStack_5126;
  undefined2 uStack_5124;
  undefined2 uStack_5122;
  byte *pbStack_5120;
  uint6 auStack_5118 [30];
  undefined8 *puStack_5028;
  undefined8 uStack_5020;
  undefined8 uStack_5018;
  undefined8 *puStack_5010;
  undefined8 uStack_5008;
  undefined8 uStack_5000;
  undefined8 *puStack_4ff8;
  undefined8 uStack_4ff0;
  undefined8 uStack_4fe8;
  undefined8 *puStack_4fe0;
  undefined8 uStack_4fd8;
  undefined8 uStack_4fd0;
  undefined8 *puStack_4fc8;
  undefined8 uStack_4fc0;
  undefined8 uStack_4fb8;
  undefined8 *puStack_4fb0;
  undefined8 uStack_4fa8;
  undefined8 uStack_4fa0;
  undefined8 *puStack_4f98;
  undefined8 uStack_4f90;
  undefined8 uStack_4f88;
  undefined4 uStack_4f80;
  undefined4 uStack_4f7c;
  undefined4 uStack_4f78;
  undefined4 uStack_4f74;
  ulong uStack_4f70;
  undefined8 *puStack_4f68;
  undefined8 uStack_4f60;
  undefined8 uStack_4f58;
  undefined *puStack_4f50;
  undefined8 uStack_4f48;
  undefined *puStack_4f40;
  undefined *puStack_4f38;
  ulong uStack_4f30;
  long lStack_4f28;
  undefined8 uStack_4f20;
  byte abStack_4f18 [2];
  ushort uStack_4f16;
  byte abStack_4f13 [1651];
  ushort uStack_48a0;
  byte abStack_489e [1650];
  ushort uStack_422c;
  byte abStack_422a [10];
  char acStack_4220 [16];
  long alStack_4210 [1678];
  undefined1 auStack_d9f [1655];
  undefined1 auStack_728 [1652];
  undefined1 auStack_b4 [44];
  long lStack_88;
  
  (*(code *)PTR____chkstk_darwin_100bfcf20)();
  lStack_88 = *(long *)PTR____stack_chk_guard_100bfc980;
  IVar21 = objc_stub::FUN_100917800(0x100c1a3b0);
  _bzero(abStack_4f18,0x4e90);
  uStack_4f20 = 0;
  lStack_4f28 = 0;
  plVar22 = &lStack_4f28;
  FUN_100006ef8(plVar22,param_1 + 0x40);
  uVar42 = uRam0000000100cae510;
  if ((*(byte *)(param_1 + 0x31) & 1) == 0) {
    uVar46 = uRam0000000100cae510;
    _os_log_type_enabled(uRam0000000100cae510,0);
    if ((int)uVar46 == 0) goto LAB_1000c9430;
    pcVar39 = "Stack is not started, updateAdvertisement returning";
LAB_1000c7924:
    uStack_5140._1_1_ = 0;
    uStack_5140._0_1_ = 0;
    __os_log_impl(0x100000000,uVar42,0,pcVar39,&uStack_5140,2);
    goto LAB_1000c9430;
  }
  pcVar39 = (char *)(param_1 + 0x4fa0);
  if (((param_2 & 1) == 0) && (*(char *)(param_1 + 0x4fa1) == '\x01')) {
    uVar46 = uRam0000000100cae510;
    _os_log_type_enabled(uRam0000000100cae510,2);
    if ((int)uVar46 != 0) {
      FUN_1008f9ca0(uVar42);
    }
    goto LAB_1000c9430;
  }
  if (*(char *)(param_1 + 0x502c) == '\x01') {
    FUN_1000071b8();
    (**(code **)(*plVar22 + 0x440))();
    uVar42 = uRam0000000100cae510;
    if ((int)plVar22 != 0) {
      lVar41 = *(long *)(param_1 + 0x4fe8);
      uVar46 = uRam0000000100cae510;
      _os_log_type_enabled(uRam0000000100cae510,0);
      if (lVar41 == 0) {
        if ((int)uVar46 == 0) goto LAB_1000c9430;
        pcVar39 = 
        "LeBroadcaster::updateAdvertisement System about to go to sleep, will try again later";
        goto LAB_1000c7924;
      }
      if ((int)uVar46 != 0) {
        uStack_5140._0_1_ = 0;
        uStack_5140._1_1_ = 0;
        __os_log_impl(0x100000000,uVar42,0,
                      "LeBroadcaster::updateAdvertisement System about to go to sleep, but in the middle of reconfig"
                      ,&uStack_5140,2);
      }
    }
  }
  uVar42 = uRam0000000100cae510;
  uVar19 = *(uint *)(param_1 + 0x80);
  if ((uVar19 & 0xfffffffd) != 0) {
    uVar46 = uRam0000000100cae510;
    _os_log_type_enabled(uRam0000000100cae510,2);
    if ((int)uVar46 != 0) {
      FUN_1008f9e70(uVar19,uVar42);
    }
    *(undefined1 *)(param_1 + 0x4fa1) = 1;
    puStack_4f50 = PTR___NSConcreteStackBlock_100bfc978;
    uStack_4f48 = _UNK_100930070;
    puStack_4f40 = &DAT_1000ce4b0;
    puStack_4f38 = &UNK_100b9c4b8;
    uStack_4f30 = param_1;
    FUN_1000c68d4(*(undefined8 *)(param_1 + 0x38),200,&puStack_4f50);
    goto LAB_1000c9430;
  }
  if (*pcVar39 == '\x01') {
    uVar46 = uRam0000000100cae510;
    _os_log_type_enabled(uRam0000000100cae510,0);
    if ((int)uVar46 != 0) {
      uStack_5140._0_1_ = 0;
      uStack_5140._1_1_ = 0;
      __os_log_impl(0x100000000,uVar42,0,
                    "updateAdvertisement busy with address change, will try again later",
                    &uStack_5140,2);
    }
    FUN_1000d6510(param_1,0);
    goto LAB_1000c9430;
  }
  uVar46 = uRam0000000100cae510;
  _os_log_type_enabled(uRam0000000100cae510,2);
  if ((int)uVar46 != 0) {
    FUN_1008f9cd4(param_2,param_1,uVar42);
  }
  FUN_1000c6e38(param_1,0);
  *(undefined1 *)(param_1 + 0x4fa1) = 0;
  uStack_4f60 = 0;
  puStack_4f68 = (undefined8 *)0x0;
  uStack_4f58 = 0;
  FUN_1001136e0(&puStack_4f68,param_1 + 0x4f28);
  uVar38 = _UNK_100930b20;
  uVar42 = param_1;
  if (puStack_4f68 == &uStack_4f60) {
    uVar19 = 0;
LAB_1000c7cbc:
    FUN_1000d77c0();
  }
  else {
    uVar19 = 0;
    bVar18 = false;
    puVar33 = puStack_4f68;
    do {
      if (lRam0000000100c1bd20 != -1) {
        FUN_1008f9d5c();
      }
      uVar46 = uRam0000000100c1bd18;
      FUN_10008c82c(uRam0000000100c1bd18,puVar33[4]);
      if (lRam0000000100c1bd20 != -1) {
        FUN_1008f9d5c();
      }
      uVar29 = uRam0000000100c1bd18;
      FUN_1000785ec(uRam0000000100c1bd18,puVar33[4]);
      uVar43 = uRam0000000100cae510;
      if (((uVar46 & 0x30) != 0 || (int)uVar46 == 1) || (uVar29 & 1) != 0) {
        uVar19 = 1;
        break;
      }
      iVar40 = *(int *)(puVar33[6] + 0x128);
      if (*(char *)(puVar33[6] + 0x188) == '\x01') {
        uVar46 = uRam0000000100cae510;
        _os_log_type_enabled(uRam0000000100cae510,0);
        if ((int)uVar46 != 0) {
          FUN_10001c8f8(&uStack_5140,puVar33[4]);
          puVar34 = (undefined8 *)
                    CONCAT44(uStack_5140._4_4_,
                             CONCAT22(uStack_5140._2_2_,
                                      CONCAT11(uStack_5140._1_1_,(undefined1)uStack_5140)));
          if (-1 < cStack_5129) {
            puVar34 = &uStack_5140;
          }
          uStack_4f80 = (undefined4)uVar38;
          uStack_4f7c = SUB84(puVar34,0);
          uStack_4f78 = (undefined4)((ulong)puVar34 >> 0x20);
          __os_log_impl(0x100000000,uVar43,0,"Session \"%{public}s\" requires power assertion",
                        &uStack_4f80,0xc);
          if (cStack_5129 < '\0') {
            __ZdlPv(CONCAT44(uStack_5140._4_4_,
                             CONCAT22(uStack_5140._2_2_,
                                      CONCAT11(uStack_5140._1_1_,(undefined1)uStack_5140))));
          }
        }
        bVar18 = true;
      }
      puVar34 = (undefined8 *)puVar33[1];
      puVar49 = puVar33;
      if ((undefined8 *)puVar33[1] == (undefined8 *)0x0) {
        do {
          puVar33 = (undefined8 *)puVar49[2];
          bVar17 = puVar49 != (undefined8 *)*puVar33;
          puVar49 = puVar33;
        } while (bVar17);
      }
      else {
        do {
          puVar33 = puVar34;
          puVar34 = (undefined8 *)*puVar33;
        } while ((undefined8 *)*puVar33 != (undefined8 *)0x0);
      }
      uVar19 = iVar40 == 4 | uVar19;
    } while (puVar33 != &uStack_4f60);
    if ((!bVar18) || (uVar19 == 0)) goto LAB_1000c7cbc;
    FUN_1007ce968();
    uVar19 = 1;
  }
  uVar46 = uRam0000000100cae510;
  if (*(int *)(param_1 + 0x90) == 0) {
    uVar42 = uRam0000000100cae510;
    _os_log_type_enabled(uRam0000000100cae510,0x10);
    if ((int)uVar42 != 0) {
      FUN_1008f9e3c(uVar46);
    }
  }
  else {
    thunk_FUN_1000c780c();
    if ((int)uVar42 == 0) {
      uVar42 = 1;
    }
    else {
      thunk_FUN_1000c780c();
    }
    uStack_4f78 = 0;
    uStack_4f74 = 0;
    uStack_4f80 = 0;
    uStack_4f7c = 0;
    uStack_4f70 = 0;
    uStack_4f88 = 0;
    uStack_4f90 = 0;
    uStack_4fa0 = 0;
    uStack_4fa8 = 0;
    uStack_4fb8 = 0;
    uStack_4fc0 = 0;
    uStack_4fd0 = 0;
    uStack_4fd8 = 0;
    uStack_4fe8 = 0;
    uStack_4ff0 = 0;
    uStack_5000 = 0;
    uStack_5008 = 0;
    uStack_5018 = 0;
    uStack_5020 = 0;
    puStack_5028 = &uStack_5020;
    puStack_5010 = &uStack_5008;
    puStack_4ff8 = &uStack_4ff0;
    puStack_4fe0 = &uStack_4fd8;
    puStack_4fc8 = &uStack_4fc0;
    puStack_4fb0 = &uStack_4fa8;
    puStack_4f98 = &uStack_4f90;
    FUN_1001137b8(param_1,&puStack_4f68,abStack_4f18,uVar42,&uStack_4f80,&puStack_4f98,&puStack_4fb0
                  ,&puStack_4fc8,&puStack_4ff8,&puStack_5010,&puStack_5028);
    uVar6 = _UNK_100936778;
    uVar5 = _UNK_100935848;
    uVar10 = _UNK_100930510;
    uVar38 = _UNK_1009304c8;
    iVar40 = (int)uVar42;
    if (iVar40 == 0) {
      uVar47 = 0;
    }
    else {
      uVar46 = 0;
      uVar47 = 0;
      lVar41 = -0x3460;
      do {
        lVar30 = uVar46 * 0xd18;
        lVar32 = param_1 + 0x98 + lVar30;
        uVar43 = param_1;
        FUN_1000ca5a8(param_1,abStack_4f18 + lVar30,lVar32);
        pmVar48 = pmRam0000000100cae518;
        Hint_Prefetch(param_1 + lVar41 + 0x4efc,0,0,0);
        Hint_Prefetch(auStack_b4 + lVar41,0,0,0);
        if ((uint)uVar43 == 0) {
LAB_1000c7fd4:
          uVar31 = (ulong)abStack_422a[lVar30 + 1] << 0x28 | (ulong)abStack_422a[lVar30 + 2] << 0x20
                   | (ulong)abStack_422a[lVar30 + 3] << 0x18 |
                   (ulong)abStack_422a[lVar30 + 4] << 0x10 | (ulong)abStack_422a[lVar30 + 5] << 8 |
                   (ulong)abStack_422a[lVar30 + 6];
          uVar29 = uVar31 | (ulong)abStack_422a[lVar30] << 0x30;
          if (uVar31 != 0 &&
              uVar29 != ((ulong)*(byte *)(lVar32 + 0xcef) << 0x28 |
                         (ulong)*(byte *)(lVar32 + 0xcf0) << 0x20 |
                         (ulong)*(byte *)(lVar32 + 0xcf1) << 0x18 |
                         (ulong)*(byte *)(lVar32 + 0xcf2) << 0x10 |
                         (ulong)*(byte *)(lVar32 + 0xcf3) << 8 | (ulong)*(byte *)(lVar32 + 0xcf4) |
                        (ulong)*(byte *)(lVar32 + 0xcee) << 0x30)) {
            FUN_1007cf2d4(param_1,uVar29,uVar46);
          }
        }
        else {
          pmVar23 = pmRam0000000100cae518;
          _os_log_type_enabled(pmRam0000000100cae518,2);
          if ((int)pmVar23 != 0) {
            uStack_5140._0_1_ = (undefined1)uVar10;
            uStack_5140._1_1_ = (undefined1)((ulong)uVar10 >> 8);
            uStack_5140._2_2_ = (undefined2)((ulong)uVar10 >> 0x10);
            uStack_5140._4_4_ = (uint)uVar46;
            __os_log_debug_impl(0x100000000,pmVar48,2,"Advertising instance %d changed:",
                                &uStack_5140,8);
            pmVar48 = pmRam0000000100cae518;
          }
          pmVar23 = pmVar48;
          _os_log_type_enabled(pmVar48,2);
          if ((int)pmVar23 != 0) {
            Hint_Prefetch(param_1 + lVar41 + 0x4211,0,0,0);
            Hint_Prefetch(auStack_d9f + lVar41,0,0,0);
            uStack_5130 = *(undefined2 *)(lVar32 + 2);
            uStack_5140._0_1_ = 0;
            uStack_5140._1_1_ = 4;
            uStack_5140._2_2_ = 0x400;
            uStack_5140._4_4_ = (uint)*(byte *)(lVar32 + 1);
            uStack_5138 = 0x400;
            uStack_5136 = (ushort)abStack_4f18[lVar30 + 1];
            uStack_5134 = 0;
            uStack_5132 = 0x400;
            uStack_512e = 0;
            uStack_512c = 0x400;
            uStack_512a = (undefined1)*(undefined2 *)(abStack_4f18 + lVar30 + 2);
            cStack_5129 = (char)((ushort)*(undefined2 *)(abStack_4f18 + lVar30 + 2) >> 8);
            uStack_5128 = 0;
            __os_log_debug_impl(0x100000000,pmVar48,2,"\ttype:%d-->%d interval:%d-->%d",&uStack_5140
                                ,0x1a);
            pmVar48 = pmRam0000000100cae518;
          }
          pbVar28 = abStack_4f18 + lVar30 + 5;
          lVar1 = lVar32 + 5;
          pbVar24 = pbVar28;
          _memcmp(pbVar28,lVar1,0x672);
          acStack_4220[lVar30] = (int)pbVar24 != 0;
          pbVar2 = abStack_489e + lVar30;
          lVar3 = lVar32 + 0x67a;
          pbVar25 = pbVar2;
          _memcmp(pbVar2,lVar3,0x672);
          acStack_4220[lVar30 + 1] = (int)pbVar25 != 0;
          pmVar23 = pmVar48;
          _os_log_type_enabled(pmVar48,2);
          if ((int)pmVar23 != 0) {
            uStack_5140._0_1_ = (undefined1)uVar38;
            uStack_5140._1_1_ = (undefined1)((ulong)uVar38 >> 8);
            uStack_5140._2_2_ = (undefined2)((ulong)uVar38 >> 0x10);
            uStack_5140._4_4_ = (uint)((int)pbVar24 != 0);
            uStack_5138 = 0x400;
            uStack_5136 = (ushort)((int)pbVar25 != 0);
            uStack_5134 = 0;
            pmVar23 = &__mh_execute_header;
            __os_log_debug_impl(0x100000000,pmVar48,2,"AdvDataChanged:%d scanDataChanged:%d",
                                &uStack_5140,0xe);
          }
          if (lVar41 != 0) {
LAB_1000c7f98:
            pmVar48 = pmRam0000000100cae518;
            pmVar23 = pmRam0000000100cae518;
            _os_log_type_enabled(pmRam0000000100cae518,2);
            uVar15 = uStack_5140._2_2_;
            uVar14 = uStack_5140._1_1_;
            uVar8 = (undefined1)uStack_5140;
            uStack_5140._2_2_ = (undefined2)((ulong)uVar5 >> 0x10);
            uVar13 = uStack_5140._2_2_;
            uStack_5140._0_1_ = (undefined1)uVar5;
            uVar11 = (undefined1)uStack_5140;
            uStack_5140._1_1_ = (undefined1)((ulong)uVar5 >> 8);
            uVar12 = uStack_5140._1_1_;
            if ((int)pmVar23 != 0) {
              Hint_Prefetch(param_1 + lVar41 + 0x4888,0,0,0);
              uStack_512c = *(ushort *)(lVar32 + 0x678);
              Hint_Prefetch(auStack_728 + lVar41,0,0,0);
              uStack_5126 = (&uStack_48a0)[uVar46 * 0x68c];
              uStack_5140._4_4_ = (uint)uStack_512c;
              uStack_5138 = 0x830;
              uStack_5136 = (ushort)lVar1;
              uStack_5134 = (undefined2)((ulong)lVar1 >> 0x10);
              uStack_5132 = (ushort)((ulong)lVar1 >> 0x20);
              uStack_5130 = (undefined2)((ulong)lVar1 >> 0x30);
              uStack_512e = 0x400;
              uStack_512a = 0;
              cStack_5129 = '\0';
              uStack_5128 = 0x410;
              uStack_5124 = 0;
              uStack_5122 = 0x830;
              auStack_5118[0] = (uint6)CONCAT22(uStack_5126,0x400);
              pbStack_5120 = pbVar28;
              __os_log_debug_impl(0x100000000,pmVar48,2,"\tAdvertising Data:%.*P(%d)-->%.*P(%d)",
                                  &uStack_5140,0x2e);
              pmVar48 = pmRam0000000100cae518;
              uVar8 = (undefined1)uStack_5140;
              uVar14 = uStack_5140._1_1_;
              uVar15 = uStack_5140._2_2_;
            }
            uStack_5140._2_2_ = uVar15;
            uStack_5140._1_1_ = uVar14;
            uStack_5140._0_1_ = uVar8;
            pmVar23 = pmVar48;
            _os_log_type_enabled(pmVar48,2);
            if ((int)pmVar23 != 0) {
              uStack_512c = *(ushort *)(lVar32 + 0xcec);
              uStack_5126 = (&uStack_422c)[uVar46 * 0x68c];
              uStack_5140._4_4_ = (uint)uStack_512c;
              uStack_5138 = 0x830;
              uStack_5136 = (ushort)lVar3;
              uStack_5134 = (undefined2)((ulong)lVar3 >> 0x10);
              uStack_5132 = (ushort)((ulong)lVar3 >> 0x20);
              uStack_5130 = (undefined2)((ulong)lVar3 >> 0x30);
              uStack_512e = 0x400;
              uStack_512a = 0;
              cStack_5129 = '\0';
              uStack_5128 = 0x410;
              uStack_5124 = 0;
              uStack_5122 = 0x830;
              auStack_5118[0] = (uint6)CONCAT22(uStack_5126,0x400);
              uStack_5140._0_1_ = uVar11;
              uStack_5140._1_1_ = uVar12;
              uStack_5140._2_2_ = uVar13;
              pbStack_5120 = pbVar2;
              __os_log_debug_impl(0x100000000,pmVar48,2,"\tScan Response:%.*P(%d)-->%.*P(%d)",
                                  &uStack_5140,0x2e);
              pmVar48 = pmRam0000000100cae518;
            }
            pmVar23 = pmVar48;
            _os_log_type_enabled(pmVar48,2);
            if ((int)pmVar23 != 0) {
              lVar1 = lVar32 + 0xcef;
              uStack_5140._0_1_ = (undefined1)uVar6;
              uStack_5140._1_1_ = (undefined1)((ulong)uVar6 >> 8);
              uStack_5140._2_2_ = (undefined2)((ulong)uVar6 >> 0x10);
              uStack_5140._4_4_ = 6;
              uStack_5138 = 0x830;
              uStack_5136 = (ushort)lVar1;
              uStack_5134 = (undefined2)((ulong)lVar1 >> 0x10);
              uStack_5132 = (ushort)((ulong)lVar1 >> 0x20);
              uStack_5130 = (undefined2)((ulong)lVar1 >> 0x30);
              uStack_512e = 0x400;
              uStack_512c = (ushort)*(byte *)(lVar32 + 0xcee);
              uStack_512a = 0;
              cStack_5129 = '\0';
              uStack_5128 = 0x400;
              uStack_5126 = (ushort)*(byte *)(lVar32 + 0xcf5);
              uStack_5124 = 0;
              __os_log_debug_impl(0x100000000,pmVar48,2,
                                  "\tadvertising address:%.6P type:%d override:%d",&uStack_5140,0x1e
                                 );
            }
            goto LAB_1000c7fd4;
          }
          FUN_1000110f0();
          (**(code **)(*(long *)pmVar23 + 0xb8))();
          if ((int)pmVar23 != 0) goto LAB_1000c7f98;
        }
        uVar47 = uVar47 | (uint)uVar43;
        uVar46 = uVar46 + 1;
        lVar41 = lVar41 + 0xd18;
      } while ((uVar42 & 0xffffffff) != uVar46);
    }
    uVar46 = uRam0000000100cae510;
    uVar43 = uRam0000000100cae510;
    _os_log_type_enabled(uRam0000000100cae510,2);
    if ((uVar43 & 1) != 0) {
      if (*(uint *)(param_1 + 0x80) < 4) {
        pcVar35 = (&PTR_s_Idle_100bcb6b8)[*(uint *)(param_1 + 0x80)];
      }
      else {
        pcVar35 = "UNKNOWN";
      }
      uStack_5132 = (ushort)uVar47 & 1;
      uStack_5140._0_1_ = (undefined1)_UNK_100930fa8;
      uStack_5140._1_1_ = (undefined1)((ulong)_UNK_100930fa8 >> 8);
      uStack_5140._2_2_ = (undefined2)((ulong)_UNK_100930fa8 >> 0x10);
      uStack_5140._4_4_ = (uint)pcVar35;
      uStack_5138 = (undefined2)((ulong)pcVar35 >> 0x20);
      uStack_5136 = (ushort)((ulong)pcVar35 >> 0x30);
      uStack_5134 = 0x400;
      uStack_5130 = 0;
      uStack_512e = 0x400;
      uStack_512c = (ushort)uVar19;
      uStack_512a = 0;
      cStack_5129 = '\0';
      __os_log_debug_impl(0x100000000,uVar46,2,
                          "fAdvertisementState:%{public}s dataChanged:%d validSession:%d",
                          &uStack_5140,0x18);
    }
    uVar46 = uRam0000000100cae510;
    uVar38 = _UNK_100930b20;
    if ((*(int *)(param_1 + 0x80) == 0 & uVar19) == 1) {
      uVar10 = _UNK_100932b90;
      puVar33 = puStack_5028;
      puVar34 = puStack_4f68;
      if (iVar40 != 0) {
        uVar46 = 0;
        lVar41 = *(long *)
                  PTR___ZTTNSt3__118basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc750
        ;
        uVar5 = *(undefined8 *)
                 (
                 PTR___ZTTNSt3__118basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc750
                 + 0x40);
        uVar6 = *(undefined8 *)
                 (
                 PTR___ZTTNSt3__118basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc750
                 + 0x48);
        do {
          lVar32 = uVar46 * 0xd18;
          uVar7 = *(ushort *)(abStack_4f18 + lVar32 + 2);
          auStack_5118[0x1d]._0_8_ = 0;
          auStack_5118[0x1a]._0_8_ = 0;
          auStack_5118[0x19]._0_8_ = 0;
          auStack_5118[0x1c]._0_8_ = 0;
          auStack_5118[0x1b]._0_8_ = 0;
          auStack_5118[0x16]._0_8_ = 0;
          auStack_5118[0x15]._0_8_ = 0;
          auStack_5118[0x18]._0_8_ = 0;
          auStack_5118[0x17]._0_8_ = 0;
          auStack_5118[0x12]._0_8_ = 0;
          auStack_5118[0x11]._0_8_ = 0;
          auStack_5118[0x14]._0_8_ = 0;
          auStack_5118[0x13]._0_8_ = 0;
          auStack_5118[0xe]._0_8_ = 0;
          auStack_5118[0xd]._0_8_ = 0;
          auStack_5118[0x10]._0_8_ = 0;
          auStack_5118[0xf]._0_8_ = 0;
          auStack_5118[10]._0_8_ = 0;
          auStack_5118[9]._0_8_ = 0;
          auStack_5118[0xc]._0_8_ = 0;
          auStack_5118[0xb]._0_8_ = 0;
          auStack_5118[6]._0_8_ = 0;
          auStack_5118[5]._0_8_ = 0;
          auStack_5118[8]._0_8_ = 0;
          auStack_5118[7]._0_8_ = 0;
          auStack_5118[2]._0_8_ = 0;
          auStack_5118[1]._0_8_ = 0;
          auStack_5118[4]._0_8_ = 0;
          auStack_5118[3]._0_8_ = 0;
          uStack_5128 = 0;
          uStack_5126 = 0;
          uStack_5124 = 0;
          uStack_5122 = 0;
          uStack_5130 = 0;
          uStack_512e = 0;
          uStack_512c = 0;
          uStack_512a = 0;
          cStack_5129 = 0;
          auStack_5118[0]._0_8_ = 0;
          pbStack_5120 = (byte *)0x0;
          uStack_5138 = 0;
          uStack_5136 = 0;
          uStack_5134 = 0;
          uStack_5132 = 0;
          uStack_5140._0_1_ = 0;
          uStack_5140._1_1_ = 0;
          uStack_5140._2_2_ = 0;
          uStack_5140._4_4_ = 0;
          FUN_1003e93d0(&uStack_5140);
          FUN_1003e9824(&uStack_5130,"[",1);
          __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi();
          FUN_1003e9824();
          FUN_1003e9824();
          FUN_1003e9824();
          FUN_1003e9824();
          FUN_1003e9824();
          FUN_1003e9824();
          FUN_1003e9824();
          if (uVar46 == 0) {
            uVar43 = CONCAT44(uStack_4f74,uStack_4f78);
            if (-1 < (long)uStack_4f70) {
              uVar43 = uStack_4f70 >> 0x38;
            }
            if (uVar43 != 0) {
              FUN_1003e9824(&uStack_5130,"name \"",6);
              FUN_1003e9824();
              FUN_1003e9824();
            }
          }
          uVar8 = (undefined1)uVar46;
          ppuVar45 = &puStack_4f98;
          uStack_5158 = uVar8;
          FUN_10014f918(ppuVar45,&uStack_5158);
          if (ppuVar45[1] != *ppuVar45) {
            FUN_1003e9824(&uStack_5130,"UUID(s) [ ",10);
            uVar43 = 0;
            while( true ) {
              ppuVar45 = &puStack_4f98;
              uStack_5158 = uVar8;
              FUN_10014f918(ppuVar45,&uStack_5158);
              uVar29 = ((long)ppuVar45[1] - (long)*ppuVar45 >> 2) * -0x3333333333333333;
              if (uVar29 < uVar43 || uVar29 - uVar43 == 0) break;
              uStack_5170 = CONCAT31(uStack_5170._1_3_,uVar8);
              ppuVar45 = &puStack_4f98;
              FUN_10014f918(ppuVar45,&uStack_5170);
              uVar29 = ((long)ppuVar45[1] - (long)*ppuVar45 >> 2) * -0x3333333333333333;
              if (uVar29 < uVar43 || uVar29 - uVar43 == 0) goto LAB_1000c91a0;
              FUN_100042690(&uStack_5158,(long)*ppuVar45 + uVar43 * 0x14);
              uVar29 = uStack_5150;
              puVar27 = (undefined1 *)CONCAT71(uStack_5157,uStack_5158);
              if (-1 < (char)bStack_5141) {
                uVar29 = (ulong)bStack_5141;
                puVar27 = &uStack_5158;
              }
              FUN_1003e9824(&uStack_5130,puVar27,uVar29);
              FUN_1003e9824();
              if ((char)bStack_5141 < '\0') {
                __ZdlPv(CONCAT71(uStack_5157,uStack_5158));
              }
              uVar43 = (ulong)((int)uVar43 + 1);
            }
            FUN_1003e9824(&uStack_5130,"], ",3);
          }
          ppuVar45 = &puStack_5010;
          uStack_5158 = uVar8;
          FUN_100125228(ppuVar45,&uStack_5158);
          uVar43 = 0xff;
          ppuVar26 = ppuVar45;
          do {
            if (*ppuVar26 != (undefined8 *)0x0) goto LAB_1000c867c;
            uVar43 = uVar43 - 0x40;
            ppuVar26 = ppuVar26 + 1;
          } while (0x3f < uVar43);
          if (((ulong)ppuVar45[3] & 0x7fffffffffffffff) != 0) {
LAB_1000c867c:
            FUN_1003e9824(&uStack_5130,"Apple Types [ ",0xe);
            for (uVar43 = 0; uStack_5158 = uVar8, FUN_100125228(&puStack_5010,&uStack_5158),
                uVar43 != 0xff; uVar43 = uVar43 + 1) {
              ppuVar45 = &puStack_5010;
              uStack_5158 = uVar8;
              FUN_100125228(ppuVar45,&uStack_5158);
              if ((*(ulong *)((long)ppuVar45 + (uVar43 >> 3 & 0x1ffffffffffffff8)) >>
                   (uVar43 & 0x3f) & 1) != 0) {
                __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEm(&uStack_5130,uVar43);
                FUN_1003e9824();
              }
            }
            FUN_1003e9824(&uStack_5130,"], ",3);
          }
          ppuVar45 = &puStack_4fb0;
          uStack_5158 = uVar8;
          FUN_10014f918(ppuVar45,&uStack_5158);
          if (ppuVar45[1] != *ppuVar45) {
            FUN_1003e9824(&uStack_5130,"hashed UUID(s) [ ",0x11);
            uVar43 = 0;
            while( true ) {
              ppuVar45 = &puStack_4fb0;
              uStack_5158 = uVar8;
              FUN_10014f918(ppuVar45,&uStack_5158);
              uVar29 = ((long)ppuVar45[1] - (long)*ppuVar45 >> 2) * -0x3333333333333333;
              if (uVar29 < uVar43 || uVar29 - uVar43 == 0) break;
              uStack_5170 = CONCAT31(uStack_5170._1_3_,uVar8);
              ppuVar45 = &puStack_4fb0;
              FUN_10014f918(ppuVar45,&uStack_5170);
              uVar29 = ((long)ppuVar45[1] - (long)*ppuVar45 >> 2) * -0x3333333333333333;
              if (uVar29 < uVar43 || uVar29 - uVar43 == 0) goto LAB_1000c91a0;
              FUN_100042690(&uStack_5158,(long)*ppuVar45 + uVar43 * 0x14);
              uVar29 = uStack_5150;
              puVar27 = (undefined1 *)CONCAT71(uStack_5157,uStack_5158);
              if (-1 < (char)bStack_5141) {
                uVar29 = (ulong)bStack_5141;
                puVar27 = &uStack_5158;
              }
              FUN_1003e9824(&uStack_5130,puVar27,uVar29);
              FUN_1003e9824();
              if ((char)bStack_5141 < '\0') {
                __ZdlPv(CONCAT71(uStack_5157,uStack_5158));
              }
              uVar43 = (ulong)((int)uVar43 + 1);
            }
            FUN_1003e9824(&uStack_5130,"], ",3);
          }
          ppuVar45 = &puStack_4fc8;
          uStack_5158 = uVar8;
          FUN_10014f918(ppuVar45,&uStack_5158);
          if (ppuVar45[1] != *ppuVar45) {
            FUN_1003e9824(&uStack_5130,"solicited UUID(s) [ ",0x14);
            uVar43 = 0;
            while( true ) {
              ppuVar45 = &puStack_4fc8;
              uStack_5158 = uVar8;
              FUN_10014f918(ppuVar45,&uStack_5158);
              uVar29 = ((long)ppuVar45[1] - (long)*ppuVar45 >> 2) * -0x3333333333333333;
              if (uVar29 < uVar43 || uVar29 - uVar43 == 0) break;
              uStack_5170 = CONCAT31(uStack_5170._1_3_,uVar8);
              ppuVar45 = &puStack_4fc8;
              FUN_10014f918(ppuVar45,&uStack_5170);
              uVar29 = ((long)ppuVar45[1] - (long)*ppuVar45 >> 2) * -0x3333333333333333;
              if (uVar29 < uVar43 || uVar29 - uVar43 == 0) {
LAB_1000c91a0:
                    /* WARNING: Does not return */
                pcVar16 = (code *)SoftwareBreakpoint(1,0x1000c91a4);
                (*pcVar16)();
              }
              FUN_100042690(&uStack_5158,(long)*ppuVar45 + uVar43 * 0x14);
              uVar29 = uStack_5150;
              puVar27 = (undefined1 *)CONCAT71(uStack_5157,uStack_5158);
              if (-1 < (char)bStack_5141) {
                uVar29 = (ulong)bStack_5141;
                puVar27 = &uStack_5158;
              }
              FUN_1003e9824(&uStack_5130,puVar27,uVar29);
              FUN_1003e9824();
              if ((char)bStack_5141 < '\0') {
                __ZdlPv(CONCAT71(uStack_5157,uStack_5158));
              }
              uVar43 = (ulong)((int)uVar43 + 1);
            }
            FUN_1003e9824(&uStack_5130,"], ",3);
          }
          ppuVar45 = &puStack_4ff8;
          uStack_5158 = uVar8;
          FUN_100125158(ppuVar45,&uStack_5158);
          if (ppuVar45[2] != (undefined8 *)0x0) {
            FUN_1003e9824(&uStack_5130,"service Data [ ",0xf);
            ppuVar45 = &puStack_4ff8;
            uStack_5158 = uVar8;
            FUN_100125158(ppuVar45,&uStack_5158);
            ppuVar45 = (undefined8 **)*ppuVar45;
            while( true ) {
              ppuVar26 = &puStack_4ff8;
              uStack_5158 = uVar8;
              FUN_100125158(ppuVar26,&uStack_5158);
              if (ppuVar45 == ppuVar26 + 1) break;
              FUN_100042690(&uStack_5158,ppuVar45 + 4);
              uVar43 = uStack_5150;
              puVar27 = (undefined1 *)CONCAT71(uStack_5157,uStack_5158);
              if (-1 < (char)bStack_5141) {
                uVar43 = (ulong)bStack_5141;
                puVar27 = &uStack_5158;
              }
              ppuVar26 = (undefined8 **)&uStack_5130;
              FUN_1003e9824(&uStack_5130,puVar27,uVar43);
              FUN_1003e9824();
              FUN_10001ef38(&uStack_5170,ppuVar45 + 7);
              uVar43 = CONCAT44(uStack_5164,uStack_5168);
              puVar9 = (undefined4 *)CONCAT44(uStack_516c,uStack_5170);
              if (-1 < (char)bStack_5159) {
                uVar43 = (ulong)bStack_5159;
                puVar9 = &uStack_5170;
              }
              FUN_1003e9824(ppuVar26,puVar9,uVar43);
              FUN_1003e9824();
              if ((char)bStack_5159 < '\0') {
                __ZdlPv(CONCAT44(uStack_516c,uStack_5170));
              }
              if ((char)bStack_5141 < '\0') {
                __ZdlPv(CONCAT71(uStack_5157,uStack_5158));
              }
              ppuVar26 = (undefined8 **)ppuVar45[1];
              ppuVar37 = ppuVar45;
              if ((undefined8 **)ppuVar45[1] == (undefined8 **)0x0) {
                do {
                  ppuVar45 = (undefined8 **)ppuVar37[2];
                  bVar18 = ppuVar37 != (undefined8 **)*ppuVar45;
                  ppuVar37 = ppuVar45;
                } while (bVar18);
              }
              else {
                do {
                  ppuVar45 = ppuVar26;
                  ppuVar26 = (undefined8 **)*ppuVar45;
                } while ((undefined8 **)*ppuVar45 != (undefined8 **)0x0);
              }
            }
            ppuVar45 = (undefined8 **)&uStack_5130;
            FUN_1003e9824(&uStack_5130,"], ",3);
          }
          FUN_1000071b8();
          (*(code *)(*ppuVar45)[0x80])();
          uVar19 = 0;
          if (uVar46 == 2) {
            uVar19 = (uint)ppuVar45;
          }
          pcVar35 = "NonConnectable2 Data, ";
          if (((uVar19 & 1) != 0) || (pcVar35 = "ObjectDiscovery Data, ", uVar46 == 3)) {
            FUN_1003e9824(&uStack_5130,pcVar35,0x16);
          }
          if ((uVar7 & 0xc000) == 0) {
            ppuVar45 = (undefined8 **)&uStack_5130;
            FUN_1003e9824(&uStack_5130,"interval=",9);
            iVar20 = (int)ppuVar45;
            dVar50 = (double)NEON_ucvtf((ulong)*(ushort *)(abStack_4f18 + lVar32 + 2));
            __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEd(dVar50 * 0.625);
            FUN_1003e9824();
            if (acStack_4220[lVar32 + 3] != '\0') {
              ppuVar45 = (undefined8 **)&uStack_5130;
              FUN_1003e9824(&uStack_5130,"primaryPHY ",0xb);
              iVar20 = (int)ppuVar45;
              __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi();
            }
            if (acStack_4220[lVar32 + 4] != '\0') {
              ppuVar45 = (undefined8 **)&uStack_5130;
              FUN_1003e9824(&uStack_5130,"secondaryPHY ",0xd);
              iVar20 = (int)ppuVar45;
              __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi();
            }
            if (acStack_4220[lVar32 + 5] != '\0') {
              ppuVar45 = (undefined8 **)&uStack_5130;
              FUN_1003e9824(&uStack_5130,"primaryPhyOptions ",0x12);
              iVar20 = (int)ppuVar45;
              __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi();
            }
            if (acStack_4220[lVar32 + 6] != '\0') {
              ppuVar45 = (undefined8 **)&uStack_5130;
              FUN_1003e9824(&uStack_5130,"secondaryPhyOptions ",0x14);
              iVar20 = (int)ppuVar45;
              __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi();
            }
            FUN_1000071f0();
            FUN_1000c9bb0();
            if (iVar20 != 0) {
              iVar20 = 0x9c8510;
              __os_feature_enabled_impl("BluetoothFeatures","LeDecisionBasedAdvFiltering");
              if ((iVar20 != 0) && (acStack_4220[lVar32 + 7] != '\0')) {
                FUN_1003e9824(&uStack_5130," useDecisionBasedAdvPayload ",0x1c);
                __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi();
                FUN_1003e9824(&uStack_5130," DBAFDecisionTypeFlags ",0x17);
                __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi();
                FUN_1003e9824(&uStack_5130," DBAFDecisionDataLength ",0x18);
                __ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi();
                if (acStack_4220[lVar32 + 9] != '\0') {
                  ppuVar45 = (undefined8 **)&uStack_5130;
                  FUN_1003e9824(&uStack_5130," DBAFDecisionData ",0x12);
                  puVar33 = *ppuVar45;
                  lVar30 = puVar33[-3];
                  *(uint *)((long)ppuVar45 + lVar30 + 8) =
                       *(uint *)((long)ppuVar45 + lVar30 + 8) & 0xffffffb5 | 8;
                  lVar30 = puVar33[-3];
                  *(uint *)((long)ppuVar45 + lVar30 + 8) =
                       *(uint *)((long)ppuVar45 + lVar30 + 8) | 0x4000;
                  uStack_5158 = 0x30;
                  FUN_1007d151c();
                  if (acStack_4220[lVar32 + 9] != '\0') {
                    uVar43 = 0;
                    do {
                      *(undefined8 *)
                       ((long)auStack_5118 +
                       *(long *)(CONCAT17(cStack_5129,
                                          CONCAT16(uStack_512a,
                                                   CONCAT24(uStack_512c,
                                                            CONCAT22(uStack_512e,uStack_5130)))) +
                                -0x18)) = 2;
                      uStack_5158 = *(undefined1 *)(alStack_4210[uVar46 * 0x1a3] + uVar43);
                      FUN_1003e9824(&uStack_5130,&uStack_5158,1);
                      FUN_1003e9824();
                      uVar43 = uVar43 + 1;
                    } while (uVar43 < (byte)acStack_4220[lVar32 + 9]);
                  }
                }
              }
            }
          }
          uVar43 = uRam0000000100cae510;
          lVar32 = 1;
          uVar29 = uRam0000000100cae510;
          _os_log_type_enabled();
          if ((int)uVar29 != 0) {
            FUN_1003e9b14(&uStack_5128);
            puVar27 = &uStack_5158;
            FUN_1001ec44c();
            _memmove();
            puVar27[lVar32] = 0;
            puVar27 = (undefined1 *)CONCAT71(uStack_5157,uStack_5158);
            if (-1 < (char)bStack_5141) {
              puVar27 = &uStack_5158;
            }
            uStack_5170 = (undefined4)uVar38;
            uStack_516c = SUB84(puVar27,0);
            uStack_5168 = (undefined4)((ulong)puVar27 >> 0x20);
            __os_log_impl(0x100000000,uVar43,1,"%{public}s",&uStack_5170,0xc);
            if ((char)bStack_5141 < '\0') {
              __ZdlPv(CONCAT71(uStack_5157,uStack_5158));
            }
          }
          uStack_5140._0_1_ = (undefined1)lVar41;
          uStack_5140._1_1_ = (undefined1)((ulong)lVar41 >> 8);
          uStack_5140._2_2_ = (undefined2)((ulong)lVar41 >> 0x10);
          uStack_5140._4_4_ = (uint)((ulong)lVar41 >> 0x20);
          *(undefined8 *)((long)&uStack_5140 + *(long *)(lVar41 + -0x18)) = uVar5;
          uStack_5130 = (undefined2)uVar6;
          uStack_512e = (undefined2)((ulong)uVar6 >> 0x10);
          uStack_512c = (ushort)((ulong)uVar6 >> 0x20);
          uStack_512a = (undefined1)((ulong)uVar6 >> 0x30);
          cStack_5129 = (char)((ulong)uVar6 >> 0x38);
          puVar4 = PTR___ZTVNSt3__115basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc778
                   + 0x10;
          uStack_5128 = SUB82(puVar4,0);
          uStack_5126 = (ushort)((ulong)puVar4 >> 0x10);
          uStack_5124 = (undefined2)((ulong)puVar4 >> 0x20);
          uStack_5122 = (undefined2)((ulong)puVar4 >> 0x30);
          if ((long)(undefined8)auStack_5118[8] < 0) {
            __ZdlPv((undefined8)auStack_5118[6]);
          }
          puVar4 = PTR___ZTVNSt3__115basic_streambufIcNS_11char_traitsIcEEEE_100bfc770 + 0x10;
          uStack_5128 = SUB82(puVar4,0);
          uStack_5126 = (ushort)((ulong)puVar4 >> 0x10);
          uStack_5124 = (undefined2)((ulong)puVar4 >> 0x20);
          uStack_5122 = (undefined2)((ulong)puVar4 >> 0x30);
          __ZNSt3__16localeD1Ev
                    ((ulong)&uStack_5128 & 0xffffffffffff | 0x1be8000000000000,&pbStack_5120);
          __ZNSt3__114basic_iostreamIcNS_11char_traitsIcEEED2Ev
                    (&uStack_5140,
                     PTR___ZTTNSt3__118basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc750
                     + 8);
          __ZNSt3__19basic_iosIcNS_11char_traitsIcEEED2Ev(auStack_5118 + 0xb);
          uVar46 = uVar46 + 1;
          uVar10 = _UNK_100932b90;
          puVar33 = puStack_5028;
          puVar34 = puStack_4f68;
        } while (uVar46 != (uVar42 & 0xffffffff));
      }
      while (_UNK_100932b90 = uVar10, puStack_5028 = puVar33, puVar34 != &uStack_4f60) {
        objc_stub::FUN_100921c20(*(ID *)(puVar34[6] + 0x10),IVar21);
        puVar49 = (undefined8 *)puVar34[1];
        puVar44 = puVar34;
        uVar10 = _UNK_100932b90;
        puVar33 = puStack_5028;
        if ((undefined8 *)puVar34[1] == (undefined8 *)0x0) {
          do {
            puVar34 = (undefined8 *)puVar44[2];
            bVar18 = puVar44 != (undefined8 *)*puVar34;
            puVar44 = puVar34;
          } while (bVar18);
        }
        else {
          do {
            puVar34 = puVar49;
            puVar49 = (undefined8 *)*puVar34;
          } while ((undefined8 *)*puVar34 != (undefined8 *)0x0);
        }
      }
      if (puVar33 != &uStack_5020) {
        do {
          uVar46 = uRam0000000100cae510;
          uVar43 = uRam0000000100cae510;
          _os_log_type_enabled(uRam0000000100cae510,0);
          if ((int)uVar43 != 0) {
            uVar19 = *(uint *)(puVar33 + 4);
            FUN_10001ea24(&uStack_5158,puVar33[5]);
            puVar27 = (undefined1 *)CONCAT71(uStack_5157,uStack_5158);
            if (-1 < (char)bStack_5141) {
              puVar27 = &uStack_5158;
            }
            uVar38 = puVar33[6];
            uStack_5140._0_1_ = (undefined1)uVar10;
            uStack_5140._1_1_ = (undefined1)((ulong)uVar10 >> 8);
            uStack_5140._2_2_ = (undefined2)((ulong)uVar10 >> 0x10);
            uStack_5138 = 0x820;
            uStack_5136 = (ushort)puVar27;
            uStack_5134 = (undefined2)((ulong)puVar27 >> 0x10);
            uStack_5132 = (ushort)((ulong)puVar27 >> 0x20);
            uStack_5130 = (undefined2)((ulong)puVar27 >> 0x30);
            uStack_512e = 0x840;
            uStack_512c = (ushort)uVar38;
            uStack_512a = (undefined1)((ulong)uVar38 >> 0x10);
            cStack_5129 = (char)((ulong)uVar38 >> 0x18);
            uStack_5128 = (undefined2)((ulong)uVar38 >> 0x20);
            uStack_5126 = (ushort)((ulong)uVar38 >> 0x30);
            uStack_5140._4_4_ = uVar19;
            __os_log_impl(0x100000000,uVar46,0,
                          "LeBroadcaster::updateAdvertisement setting instance %d address:%s LTK:%@"
                          ,&uStack_5140,0x1c);
            if ((char)bStack_5141 < '\0') {
              __ZdlPv(CONCAT71(uStack_5157,uStack_5158));
            }
          }
          if (lRam0000000100c1b208 != -1) {
            FUN_1008f9d78();
          }
          FUN_100870e34(uRam0000000100c1b200,puVar33[5],*(undefined4 *)(puVar33 + 4),puVar33[6]);
          puVar34 = (undefined8 *)puVar33[1];
          puVar49 = puVar33;
          if ((undefined8 *)puVar33[1] == (undefined8 *)0x0) {
            do {
              puVar33 = (undefined8 *)puVar49[2];
              bVar18 = puVar49 != (undefined8 *)*puVar33;
              puVar49 = puVar33;
            } while (bVar18);
          }
          else {
            do {
              puVar33 = puVar34;
              puVar34 = (undefined8 *)*puVar33;
            } while ((undefined8 *)*puVar33 != (undefined8 *)0x0);
          }
        } while (puVar33 != &uStack_5020);
      }
      FUN_1000d7530(param_1);
      uStack_5140._0_1_ = 0;
      FUN_100061a60(&uStack_5140);
      pbVar28 = abStack_4f18;
      FUN_1000c6f74(pbVar28,iVar40,0,&LAB_1000dbfa4,0,&DAT_100110f6c);
      iVar20 = (int)pbVar28;
      if (iVar20 == 0x76) {
        FUN_1000d403c(1);
      }
      FUN_10006433c(&uStack_5140);
      uVar46 = uRam0000000100cae510;
      if (iVar20 == 0) {
        FUN_1000dc020(param_1,1);
        if (iVar40 != 0) {
          _memcpy(param_1 + 0x98,abStack_4f18,(uVar42 & 0xffffffff) * 0xd18);
        }
      }
      else {
        uVar42 = uRam0000000100cae510;
        _os_log_type_enabled(uRam0000000100cae510,0x10);
        if ((int)uVar42 != 0) {
          FUN_1008f9dcc(pbVar28,uVar46);
        }
        uVar42 = uRam0000000100cae510;
        if (iVar20 == 0xfe9) {
          *pcVar39 = '\x01';
        }
        else if (iVar20 == 0x76) {
          uVar46 = uRam0000000100cae510;
          _os_log_type_enabled(uRam0000000100cae510,0x10);
          if ((int)uVar46 != 0) {
            FUN_1008f9e08(uVar42);
          }
          puStack_5198 = PTR___NSConcreteStackBlock_100bfc978;
          uStack_5190 = _UNK_100930070;
          puStack_5188 = &DAT_1007d35d4;
          puStack_5180 = &UNK_100b9c4b8;
          uStack_5178 = param_1;
          FUN_1000c68d4(*(undefined8 *)(param_1 + 0x38),200,&puStack_5198);
        }
      }
LAB_1000c9378:
      FUN_10006b538(&uStack_5140);
    }
    else {
      if ((*(int *)(param_1 + 0x80) == 2) && (((uVar47 ^ 1) & uVar19) == 0)) {
        uVar43 = uRam0000000100cae510;
        _os_log_type_enabled(uRam0000000100cae510,1);
        if ((uVar47 & uVar19) == 0) {
          if ((int)uVar43 != 0) {
            uStack_5140._0_1_ = 0;
            uStack_5140._1_1_ = 0;
            __os_log_impl(0x100000000,uVar46,1,
                          "Stopping advertisement as there are no more advertising sessions",
                          &uStack_5140,2);
          }
          if (iVar40 != 0) {
            _bzero(param_1 + 0x98,(uVar42 & 0xffffffff) * 0xd18);
          }
        }
        else if ((int)uVar43 != 0) {
          uStack_5140._0_1_ = 0;
          uStack_5140._1_1_ = 0;
          __os_log_impl(0x100000000,uVar46,1,"Restarting advertisement as data has changed!",
                        &uStack_5140,2);
        }
        FUN_1000d7530(param_1);
        uVar42 = uRam0000000100cae510;
        uVar46 = uRam0000000100cae510;
        _os_log_type_enabled(uRam0000000100cae510,0);
        if ((int)uVar46 != 0) {
          uStack_5140._0_1_ = 0;
          uStack_5140._1_1_ = 0;
          __os_log_impl(0x100000000,uVar42,0,
                        "[IncomingLTK] LeBroadcaster::updateAdvertisement clearAdvInstanceIdentities"
                        ,&uStack_5140,2);
        }
        if (lRam0000000100c1b208 != -1) {
          FUN_1008f9d78();
        }
        FUN_10012752c(uRam0000000100c1b200);
        uStack_5140._0_1_ = 0;
        FUN_100061a60(&uStack_5140);
        uVar38 = 0;
        FUN_1000d403c();
        FUN_10006433c(&uStack_5140);
        if ((int)uVar38 == 0xfe9) {
          *pcVar39 = '\x01';
        }
        else if ((int)uVar38 == 0) {
          FUN_1000dc020(param_1,3);
          goto LAB_1000c9378;
        }
        uVar42 = uRam0000000100cae510;
        uVar46 = uRam0000000100cae510;
        _os_log_type_enabled(uRam0000000100cae510,0x10);
        if ((int)uVar46 != 0) {
          FUN_1008f9d90(uVar38,uVar42);
        }
        goto LAB_1000c9378;
      }
      FUN_1000d765c(param_1);
      uVar42 = uRam0000000100cae510;
      uVar46 = uRam0000000100cae510;
      _os_log_type_enabled(uRam0000000100cae510,1);
      if ((int)uVar46 != 0) {
        uVar36 = 0x59;
        uStack_5140._4_4_ = uVar36;
        if ((uVar47 & 1) == 0) {
          uStack_5140._4_4_ = 0x4e;
        }
        if (uVar19 == 0) {
          uVar36 = 0x4e;
        }
        uVar19 = *(uint *)(param_1 + 0x80);
        if (uVar19 < 4) {
          pcVar39 = (&PTR_s_Idle_100bcb6b8)[uVar19];
        }
        else {
          pcVar39 = "UNKNOWN";
        }
        uStack_5140._0_1_ = (undefined1)_UNK_1009356d0;
        uStack_5140._1_1_ = (undefined1)((ulong)_UNK_1009356d0 >> 8);
        uStack_5140._2_2_ = (undefined2)((ulong)_UNK_1009356d0 >> 0x10);
        uStack_5138 = 0x400;
        uStack_5136 = (ushort)uVar36;
        uStack_5134 = 0;
        uStack_5132 = 0x400;
        uStack_5130 = (undefined2)uVar19;
        uStack_512e = (undefined2)(uVar19 >> 0x10);
        uStack_512c = 0x820;
        uStack_512a = SUB81(pcVar39,0);
        cStack_5129 = (char)((ulong)pcVar39 >> 8);
        uStack_5128 = (undefined2)((ulong)pcVar39 >> 0x10);
        uStack_5126 = (ushort)((ulong)pcVar39 >> 0x20);
        uStack_5124 = (undefined2)((ulong)pcVar39 >> 0x30);
        __os_log_impl(0x100000000,uVar42,1,
                      "updateAdvertisement not doing anything dataChanged:%c validSessions:%c state:%d(%s)"
                      ,&uStack_5140,0x1e);
      }
    }
    uStack_5140._0_1_ = SUB81(&uStack_5020,0);
    uStack_5140._1_1_ = (undefined1)((ulong)&uStack_5020 >> 8);
    uStack_5140._2_2_ = (undefined2)((ulong)&uStack_5020 >> 0x10);
    uStack_5140._4_4_ = (uint)((ulong)&uStack_5020 >> 0x20);
    FUN_1007d6d6c(&uStack_5140,uStack_5020);
    uStack_5140._0_1_ = SUB81(&uStack_5008,0);
    uStack_5140._1_1_ = (undefined1)((ulong)&uStack_5008 >> 8);
    uStack_5140._2_2_ = (undefined2)((ulong)&uStack_5008 >> 0x10);
    uStack_5140._4_4_ = (uint)((ulong)&uStack_5008 >> 0x20);
    FUN_10020eda4(&uStack_5140,uStack_5008);
    uStack_5140._0_1_ = SUB81(&uStack_4ff0,0);
    uStack_5140._1_1_ = (undefined1)((ulong)&uStack_4ff0 >> 8);
    uStack_5140._2_2_ = (undefined2)((ulong)&uStack_4ff0 >> 0x10);
    uStack_5140._4_4_ = (uint)((ulong)&uStack_4ff0 >> 0x20);
    FUN_1007d6cfc(&uStack_5140,uStack_4ff0);
    uStack_5140._0_1_ = SUB81(&uStack_4fd8,0);
    uStack_5140._1_1_ = (undefined1)((ulong)&uStack_4fd8 >> 8);
    uStack_5140._2_2_ = (undefined2)((ulong)&uStack_4fd8 >> 0x10);
    uStack_5140._4_4_ = (uint)((ulong)&uStack_4fd8 >> 0x20);
    FUN_1005ab82c(&uStack_5140,uStack_4fd8);
    uStack_5140._0_1_ = SUB81(&uStack_4fc0,0);
    uStack_5140._1_1_ = (undefined1)((ulong)&uStack_4fc0 >> 8);
    uStack_5140._2_2_ = (undefined2)((ulong)&uStack_4fc0 >> 0x10);
    uStack_5140._4_4_ = (uint)((ulong)&uStack_4fc0 >> 0x20);
    FUN_1005ab82c(&uStack_5140,uStack_4fc0);
    uStack_5140._0_1_ = SUB81(&uStack_4fa8,0);
    uStack_5140._1_1_ = (undefined1)((ulong)&uStack_4fa8 >> 8);
    uStack_5140._2_2_ = (undefined2)((ulong)&uStack_4fa8 >> 0x10);
    uStack_5140._4_4_ = (uint)((ulong)&uStack_4fa8 >> 0x20);
    FUN_1005ab82c(&uStack_5140,uStack_4fa8);
    uStack_5140._0_1_ = SUB81(&uStack_4f90,0);
    uStack_5140._1_1_ = (undefined1)((ulong)&uStack_4f90 >> 8);
    uStack_5140._2_2_ = (undefined2)((ulong)&uStack_4f90 >> 0x10);
    uStack_5140._4_4_ = (uint)((ulong)&uStack_4f90 >> 0x20);
    FUN_1005ab82c(&uStack_5140,uStack_4f90);
    if ((long)uStack_4f70 < 0) {
      __ZdlPv(CONCAT44(uStack_4f7c,uStack_4f80));
    }
  }
  uStack_5140._0_1_ = SUB81(&uStack_4f60,0);
  uStack_5140._1_1_ = (undefined1)((ulong)&uStack_4f60 >> 8);
  uStack_5140._2_2_ = (undefined2)((ulong)&uStack_4f60 >> 0x10);
  uStack_5140._4_4_ = (uint)((ulong)&uStack_4f60 >> 0x20);
  FUN_1007d6210(&uStack_5140,uStack_4f60);
LAB_1000c9430:
  FUN_100006ec0(&lStack_4f28);
  if (*(long *)PTR____stack_chk_guard_100bfc980 == lStack_88) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}


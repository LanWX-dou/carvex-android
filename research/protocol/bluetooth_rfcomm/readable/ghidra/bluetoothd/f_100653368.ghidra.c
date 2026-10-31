/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100653368
 * original code SHA256: faba9099abf300d98325456b05f28f6088b29576673014b14bc1171c6066fee5
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000100653b1c) */
/* WARNING: Removing unreachable block (ram,0x000100653b58) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100653368(void)

{
  uint uVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  mach_header *pmVar6;
  mach_header *pmVar7;
  undefined8 uVar8;
  long lVar9;
  long lVar10;
  uint uVar11;
  ulong uVar12;
  uint uVar13;
  uint uStack_290;
  undefined4 uStack_28c;
  undefined2 uStack_288;
  uint uStack_286;
  char cStack_282;
  undefined1 uStack_281;
  uint uStack_280;
  undefined2 uStack_27c;
  undefined4 uStack_27a;
  undefined2 uStack_272;
  mach_header *pmStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 uStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  long lStack_68;
  
  lStack_68 = *(long *)PTR____stack_chk_guard_100bfc980;
  _bzero(0x100c3e2d0,(long)(int)uRam0000000100c3e408);
  iVar5 = 0;
  _strlen();
  uRam0000000100c3e2d0 = (undefined1)(iVar5 + 1U);
  uRam0000000100c3e2d1 = 9;
  uVar12 = (ulong)(iVar5 + 1U) & 0xff;
  pmVar6 = (mach_header *)0x100c3e2d2;
  _memcpy(0x100c3e2d2,0x100c1f700,uVar12 - 1);
  uRam0000000100c3e408 = (int)uVar12 + 1;
  uStack_272 = (ushort)uStack_272._1_1_ << 8;
  FUN_1000110f0();
  uStack_260 = CONCAT17(4,(undefined7)uStack_260);
  pmStack_270 = (mach_header *)CONCAT35(pmStack_270._5_3_,0x50416957);
  uStack_27a._0_2_ = CONCAT11(10,(undefined1)uStack_27a);
  uStack_288 = 0x6b6e;
  uStack_290 = (uint)s_enableSink_100a6c02e._0_8_;
  uStack_28c = SUB84(s_enableSink_100a6c02e._0_8_,4);
  uStack_286 = uStack_286 & 0xffffff00;
  (**(code **)(*(long *)pmVar6 + 0x48))();
  if (uStack_27a._1_1_ < '\0') {
    pmVar6 = (mach_header *)CONCAT44(uStack_28c,uStack_290);
    __ZdlPv();
  }
  if (uStack_260 < 0) {
    pmVar6 = pmStack_270;
    __ZdlPv();
  }
  if ((byte)uStack_272 == '\x01') {
    FUN_1000110f0();
    uStack_260 = CONCAT17(7,(undefined7)uStack_260);
    pmStack_270 = (mach_header *)0x79616c50726143;
    uStack_27a._0_2_ = CONCAT11(0xf,(undefined1)uStack_27a);
    uStack_290 = (uint)s_enableLeCarPlay_100a6d17b._0_7_;
    uStack_28c = CONCAT13(s_enableLeCarPlay_100a6d17b[7],SUB73(s_enableLeCarPlay_100a6d17b._0_7_,4))
    ;
    uStack_288 = (undefined2)s_enableLeCarPlay_100a6d17b._8_7_;
    uStack_286 = SUB74(s_enableLeCarPlay_100a6d17b._8_7_,2);
    cStack_282 = SUB71(s_enableLeCarPlay_100a6d17b._8_7_,6);
    uStack_281 = 0;
    (**(code **)(*(long *)pmVar6 + 0x48))();
    if (uStack_27a._1_1_ < '\0') {
      pmVar6 = (mach_header *)CONCAT44(uStack_28c,uStack_290);
      __ZdlPv();
    }
    if (uStack_260 < 0) {
      pmVar6 = pmStack_270;
      __ZdlPv();
    }
  }
  *(int *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = (int)_UNK_10093a568;
  uRam0000000100c3e408 = uRam0000000100c3e408 + 4;
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d1) = 0x11;
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = 0x1f;
    pmVar7 = pmRam0000000100cae440;
    uRam0000000100c3e408 = uRam0000000100c3e408 + 2;
    pmVar6 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,1);
    if ((int)pmVar6 != 0) {
      pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
      pmVar6 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar7,1,"Advertising HFP AG",&pmStack_270,2);
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d1) = 0x11;
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = 0x2f;
    pmVar7 = pmRam0000000100cae440;
    uRam0000000100c3e408 = uRam0000000100c3e408 + 2;
    pmVar6 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,1);
    if ((int)pmVar6 != 0) {
      pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
      pmVar6 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar7,1,"Advertising PBAP Server",&pmStack_270,2);
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d1) = 0x11;
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = 10;
    pmVar7 = pmRam0000000100cae440;
    uRam0000000100c3e408 = uRam0000000100c3e408 + 2;
    pmVar6 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,1);
    if ((int)pmVar6 != 0) {
      pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
      pmVar6 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar7,1,"Advertising A2DP Source",&pmStack_270,2);
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d1) = 0x11;
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = 0xc;
    pmVar7 = pmRam0000000100cae440;
    uRam0000000100c3e408 = uRam0000000100c3e408 + 2;
    pmVar6 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,1);
    if ((int)pmVar6 != 0) {
      pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
      pmVar6 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar7,1,"Advertising AVRCP Target",&pmStack_270,2);
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    uStack_290 = uStack_290 & 0xffffff00;
    FUN_100017860();
    (**(code **)(*(long *)pmVar6 + 0x20))();
    if ((char)uStack_290 == '\x01') {
      *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d1) = 0x11;
      *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = 0x16;
      pmVar7 = pmRam0000000100cae440;
      uRam0000000100c3e408 = uRam0000000100c3e408 + 2;
      pmVar6 = pmRam0000000100cae440;
      _os_log_type_enabled(pmRam0000000100cae440,1);
      if ((int)pmVar6 != 0) {
        pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
        pmVar6 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar7,1,"Advertising PAN-NAP",&pmStack_270,2);
      }
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    if (lRam0000000100c1b1e8 != -1) {
      FUN_1008e0330();
    }
    lVar9 = lRam0000000100c1b1e0;
    FUN_100621b58();
    pmVar6 = (mach_header *)0x0;
    if (lVar9 != 0) {
      *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d1) = 0x11;
      *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = 0x15;
      pmVar7 = pmRam0000000100cae440;
      uRam0000000100c3e408 = uRam0000000100c3e408 + 2;
      pmVar6 = pmRam0000000100cae440;
      _os_log_type_enabled(pmRam0000000100cae440,1);
      if ((int)pmVar6 != 0) {
        pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
        pmVar6 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar7,1,"Advertising PAN-U",&pmStack_270,2);
      }
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d1) = 0x11;
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = 0x32;
    pmVar7 = pmRam0000000100cae440;
    uRam0000000100c3e408 = uRam0000000100c3e408 + 2;
    pmVar6 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,1);
    if ((int)pmVar6 != 0) {
      pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
      pmVar6 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar7,1,"Advertising MAP Server",&pmStack_270,2);
    }
  }
  FUN_1000110f0();
  (**(code **)(*(long *)pmVar6 + 8))();
  if ((int)pmVar6 != 0) {
    FUN_1000110f0();
    uStack_260 = CONCAT17(4,(undefined7)uStack_260);
    pmStack_270 = (mach_header *)CONCAT35(pmStack_270._5_3_,0x54544143);
    uStack_27a._0_2_ = CONCAT11(10,(undefined1)uStack_27a);
    uStack_288 = 0x7064;
    uStack_290 = (uint)s_DisableSdp_100a6750c._0_8_;
    uStack_28c = SUB84(s_DisableSdp_100a6750c._0_8_,4);
    uStack_286 = uStack_286 & 0xffffff00;
    (**(code **)(*(long *)pmVar6 + 0x48))();
    if (uStack_27a._1_1_ < '\0') {
      pmVar6 = (mach_header *)CONCAT44(uStack_28c,uStack_290);
      __ZdlPv();
    }
    if (uStack_260 < 0) {
      pmVar6 = pmStack_270;
      __ZdlPv();
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d1) = 0x18;
    *(undefined1 *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = 1;
    pmVar7 = pmRam0000000100cae440;
    uRam0000000100c3e408 = uRam0000000100c3e408 + 2;
    pmVar6 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,1);
    if ((int)pmVar6 != 0) {
      pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
      pmVar6 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar7,1,"Advertising GATT Source",&pmStack_270,2);
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  iVar4 = uRam0000000100c3e408;
  cVar2 = (char)uRam0000000100c3e408;
  *(char *)(uVar12 + 0x100c3e2d1) = (cVar2 - (char)iVar5) + -3;
  *(int *)((long)(int)uRam0000000100c3e408 + 0x100c3e2d0) = (int)_UNK_10093a570;
  uRam0000000100c3e408 = uRam0000000100c3e408 + 4;
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if (((int)pmVar6 != 0) && ((uStack_272 & 1) == 0)) {
    FUN_1000110f0();
    uStack_260 = CONCAT17(3,(undefined7)uStack_260);
    pmStack_270 = (mach_header *)CONCAT44(pmStack_270._4_4_,0x504149);
    uStack_27a._0_2_ = CONCAT11(9,(undefined1)uStack_27a);
    uStack_288 = 0x50;
    uStack_290 = (uint)s_enableIAP_100a63f05._0_8_;
    uStack_28c = SUB84(s_enableIAP_100a63f05._0_8_,4);
    (**(code **)(*(long *)pmVar6 + 0x48))();
    if (uStack_27a._1_1_ < '\0') {
      pmVar6 = (mach_header *)CONCAT44(uStack_28c,uStack_290);
      __ZdlPv();
    }
    if (uStack_260 < 0) {
      pmVar6 = pmStack_270;
      __ZdlPv();
    }
    FUN_1000071b8();
    (**(code **)(*(long *)pmVar6 + 0x1b0))();
    if (((ulong)pmVar6 & 1) == 0) {
      lVar9 = 0;
      lVar10 = 0x10;
      uVar11 = uRam0000000100c3e408;
      do {
        *(undefined *)((ulong)uVar11 + 0x100c3e2d0) = (&UNK_10093a5d5)[-lVar9];
        lVar9 = lVar9 + 1;
        uVar11 = uVar11 + 1;
        lVar10 = lVar10 + -1;
      } while (lVar10 != 0);
      lVar9 = 0;
      uVar11 = uRam0000000100c3e408 + 0x10;
      lVar10 = 0x10;
      do {
        *(undefined *)((ulong)uVar11 + 0x100c3e2d0) = (&UNK_10093a5e5)[-lVar9];
        pmVar7 = pmRam0000000100cae440;
        lVar9 = lVar9 + 1;
        uVar11 = uVar11 + 1;
        lVar10 = lVar10 + -1;
      } while (lVar10 != 0);
      uRam0000000100c3e408 = uRam0000000100c3e408 + 0x20;
      pmVar6 = pmRam0000000100cae440;
      _os_log_type_enabled(pmRam0000000100cae440,1);
      if ((int)pmVar6 != 0) {
        pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
        pmVar6 = &__mh_execute_header;
        __os_log_impl(0x100000000,pmVar7,1,"Advertising WiAP",&pmStack_270,2);
      }
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if (((uint)pmVar6 & (uint)(byte)uStack_272) == 1) {
    lVar9 = 0;
    lVar10 = 0x10;
    uVar11 = uRam0000000100c3e408;
    do {
      *(undefined *)((ulong)uVar11 + 0x100c3e2d0) = (&UNK_10093a5f5)[-lVar9];
      lVar9 = lVar9 + 1;
      uVar11 = uVar11 + 1;
      lVar10 = lVar10 + -1;
    } while (lVar10 != 0);
    lVar9 = 0;
    uVar11 = uRam0000000100c3e408 + 0x10;
    lVar10 = 0x10;
    do {
      *(undefined *)((ulong)uVar11 + 0x100c3e2d0) = (&UNK_10093a605)[-lVar9];
      pmVar7 = pmRam0000000100cae440;
      lVar9 = lVar9 + 1;
      uVar11 = uVar11 + 1;
      lVar10 = lVar10 + -1;
    } while (lVar10 != 0);
    uRam0000000100c3e408 = uRam0000000100c3e408 + 0x20;
    pmVar6 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,1);
    if ((int)pmVar6 != 0) {
      pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
      pmVar6 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar7,1,"Advertising WiAP Sink and Classic CarPlay",&pmStack_270,2)
      ;
    }
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar6 + 0x38))();
  if ((int)pmVar6 != 0) {
    uStack_290 = uStack_290 & 0xffffff00;
    FUN_100017860();
    (**(code **)(*(long *)pmVar6 + 0x98))();
    if (((int)pmVar6 == 0) && ((uStack_290 & 1) != 0)) {
      lVar9 = 0;
      lVar10 = 0x10;
      uVar11 = uRam0000000100c3e408;
      do {
        *(undefined *)((ulong)uVar11 + 0x100c3e2d0) = (&UNK_10093a615)[-lVar9];
        pmVar6 = pmRam0000000100cae440;
        lVar9 = lVar9 + 1;
        uVar11 = uVar11 + 1;
        lVar10 = lVar10 + -1;
      } while (lVar10 != 0);
      uRam0000000100c3e408 = uRam0000000100c3e408 + 0x10;
      pmVar7 = pmRam0000000100cae440;
      _os_log_type_enabled(pmRam0000000100cae440,1);
      if ((int)pmVar7 != 0) {
        pmStack_270 = (mach_header *)((ulong)pmStack_270 & 0xffffffffffff0000);
        __os_log_impl(0x100000000,pmVar6,1,"Advertising  CarPlay Gateway",&pmStack_270,2);
      }
    }
  }
  lVar9 = (long)(int)uRam0000000100c3e408;
  bVar3 = (byte)uRam0000000100c3e408;
  *(byte *)((long)iVar4 + 0x100c3e2d2) = (bVar3 - cVar2) + -3;
  uStack_88 = 0;
  uStack_90 = 0;
  uStack_78 = 0;
  uStack_80 = 0;
  uStack_a8 = 0;
  uStack_b0 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  uStack_c8 = 0;
  uStack_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  uStack_e8 = 0;
  uStack_f0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_108 = 0;
  uStack_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  uStack_128 = 0;
  uStack_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_148 = 0;
  uStack_150 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_168 = 0;
  uStack_170 = 0;
  uStack_158 = 0;
  uStack_160 = 0;
  uStack_188 = 0;
  uStack_190 = 0;
  uStack_178 = 0;
  uStack_180 = 0;
  uStack_1a8 = 0;
  uStack_1b0 = 0;
  uStack_198 = 0;
  uStack_1a0 = 0;
  uStack_1c8 = 0;
  uStack_1d0 = 0;
  uStack_1b8 = 0;
  uStack_1c0 = 0;
  uStack_1e8 = 0;
  uStack_1f0 = 0;
  uStack_1d8 = 0;
  uStack_1e0 = 0;
  uStack_208 = 0;
  uStack_210 = 0;
  uStack_1f8 = 0;
  uStack_200 = 0;
  uStack_228 = 0;
  uStack_230 = 0;
  uStack_218 = 0;
  uStack_220 = 0;
  uStack_248 = 0;
  uStack_250 = 0;
  uStack_238 = 0;
  uStack_240 = 0;
  uStack_268 = 0;
  pmStack_270 = (mach_header *)0x0;
  uStack_258 = 0;
  uStack_260 = 0;
  uStack_272 = 0;
  *(int *)(lVar9 + 0x100c3e2d0) = (int)_UNK_10093a578;
  uRam0000000100c3e408 = uRam0000000100c3e408 + 4;
  if (lRam0000000100c1b1e8 != -1) {
    FUN_1008e0330();
  }
  lVar10 = lRam0000000100c1b1e0;
  FUN_100621a94(lRam0000000100c1b1e0,&pmStack_270,&uStack_272);
  pmVar6 = pmRam0000000100cae440;
  uVar11 = uRam0000000100c3e408;
  iVar5 = 0;
  if (uStack_272 != 0) {
    iVar5 = (int)lVar10;
  }
  if (iVar5 == 1) {
    uVar13 = (uint)uStack_272;
    uVar1 = uRam0000000100c3e408 + uVar13;
    if ((int)uVar1 < 0xf1) {
      _memcpy((long)(int)uRam0000000100c3e408 + 0x100c3e2d0,&pmStack_270,uStack_272);
      uRam0000000100c3e408 = uVar1;
    }
    else {
      pmVar7 = pmRam0000000100cae440;
      _os_log_type_enabled(pmRam0000000100cae440,0x10);
      if ((int)pmVar7 != 0) {
        uStack_290 = 0x4000400;
        uStack_288 = 0x400;
        uStack_286 = uVar11;
        cStack_282 = '\0';
        uStack_281 = 4;
        uStack_27c = 0x400;
        uStack_27a = 0xf0;
        uStack_28c = uVar13;
        uStack_280 = uVar1;
        __os_log_error_impl(0x100000000,pmVar6,0x10,
                            "EIR data length: %d + constEirLen: %d = %d > %d",&uStack_290,0x1a);
      }
    }
  }
  if (lRam0000000100c1b4d8 != -1) {
    FUN_1008e02f0();
  }
  uVar8 = uRam0000000100c1b4d0;
  FUN_1006476a8(uRam0000000100c1b4d0,&pmStack_270,&uStack_272);
  pmVar6 = pmRam0000000100cae440;
  uVar11 = uRam0000000100c3e408;
  iVar5 = 0;
  if (uStack_272 != 0) {
    iVar5 = (int)uVar8;
  }
  if (iVar5 == 1) {
    uVar13 = (uint)uStack_272;
    uVar1 = uRam0000000100c3e408 + uVar13;
    if ((int)uVar1 < 0xf1) {
      _memcpy((long)(int)uRam0000000100c3e408 + 0x100c3e2d0,&pmStack_270,uStack_272);
      uVar11 = uVar1;
      uRam0000000100c3e408 = uVar1;
    }
    else {
      pmVar7 = pmRam0000000100cae440;
      _os_log_type_enabled(pmRam0000000100cae440,0x10);
      if ((int)pmVar7 != 0) {
        uStack_290 = 0x4000400;
        uStack_288 = 0x400;
        uStack_286 = uVar11;
        cStack_282 = '\0';
        uStack_281 = 4;
        uStack_27c = 0x400;
        uStack_27a = 0xf0;
        uStack_28c = uVar13;
        uStack_280 = uVar1;
        __os_log_error_impl(0x100000000,pmVar6,0x10,
                            "Service specific EIR data length: %d + constEirLen: %d = %d > %d",
                            &uStack_290,0x1a);
        uVar11 = uRam0000000100c3e408;
      }
    }
  }
  *(byte *)(lVar9 + 0x100c3e2d0) = (char)uVar11 + ~bVar3;
  pmVar6 = pmRam0000000100cae440;
  if ((0xef < (int)uVar11) &&
     (pmVar7 = pmRam0000000100cae440, _os_log_type_enabled(pmRam0000000100cae440,0x11),
     (int)pmVar7 != 0)) {
    FUN_1008e0808(pmVar6);
  }
  if (*(long *)PTR____stack_chk_guard_100bfc980 != lStack_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005e3ae0
 * original code SHA256: 76a6b0b6efca94e6e73a5a02558c4889efb40081900898961f28e5a58445b83c
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0001005e3f6c) */
/* WARNING: Removing unreachable block (ram,0x0001005e3fb8) */
/* WARNING: Removing unreachable block (ram,0x0001005e3f30) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1005e3ae0(mach_header *param_1)

{
  undefined *puVar1;
  undefined1 uVar2;
  undefined8 *******pppppppuVar3;
  char *pcVar4;
  undefined8 uVar5;
  ushort uVar6;
  undefined *puVar7;
  char cVar8;
  code *pcVar9;
  mach_header *pmVar10;
  mach_header *pmVar11;
  dword *pdVar12;
  undefined2 *puVar13;
  undefined8 *******pppppppuVar14;
  mach_header **ppmVar15;
  mach_header *pmVar16;
  undefined4 *puVar17;
  mach_header **ppmVar18;
  byte bVar19;
  undefined2 uVar20;
  dword dVar21;
  long *plVar22;
  ulong uVar23;
  long *plVar24;
  long lVar25;
  dword dVar26;
  long lVar27;
  long lVar28;
  ulong uVar29;
  mach_header mStack_388;
  undefined2 uStack_368;
  int iStack_366;
  char cStack_359;
  undefined4 uStack_350;
  long lStack_34c;
  undefined2 uStack_344;
  mach_header *pmStack_342;
  dword dStack_338;
  byte bStack_331;
  dword dStack_330;
  dword dStack_32c;
  dword dStack_328;
  byte bStack_322;
  byte bStack_321;
  long lStack_320;
  long lStack_318;
  undefined8 uStack_310;
  dword dStack_304;
  dword dStack_300;
  dword dStack_2fc;
  mach_header mStack_2f8;
  ulong uStack_2d8;
  undefined8 uStack_2d0;
  dword dStack_2c4;
  undefined1 uStack_2bd;
  dword dStack_2bc;
  undefined8 uStack_2b8;
  undefined1 uStack_2a9;
  dword dStack_2a8;
  undefined1 uStack_2a1;
  dword dStack_2a0;
  dword dStack_29c;
  dword dStack_298;
  dword dStack_294;
  dword dStack_290;
  dword dStack_28c;
  dword dStack_288;
  dword dStack_284;
  byte bStack_27d;
  dword dStack_27c;
  dword dStack_278;
  undefined1 uStack_272;
  byte bStack_271;
  undefined1 uStack_270;
  undefined1 uStack_26f;
  char cStack_26e;
  undefined1 uStack_26d;
  dword dStack_26c;
  int iStack_268;
  byte bStack_261;
  undefined4 uStack_260;
  undefined4 uStack_25c;
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined8 uStack_250;
  byte bStack_23f;
  undefined2 uStack_23e;
  undefined2 uStack_23c;
  undefined2 uStack_23a;
  undefined2 uStack_238;
  undefined2 uStack_236;
  undefined2 uStack_234;
  undefined2 uStack_232;
  undefined2 uStack_230;
  undefined2 uStack_22e;
  undefined2 uStack_22c;
  undefined2 uStack_22a;
  undefined2 uStack_228;
  undefined2 uStack_226;
  undefined2 uStack_224;
  undefined2 uStack_222;
  undefined2 uStack_220;
  undefined2 uStack_21e;
  undefined2 uStack_21c;
  undefined2 uStack_21a;
  ushort uStack_218;
  undefined1 uStack_215;
  dword dStack_214;
  undefined4 uStack_210;
  undefined4 uStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined8 uStack_200;
  dword dStack_1f8;
  dword dStack_1f4;
  undefined8 *******pppppppuStack_1f0;
  undefined8 ******ppppppuStack_1e8;
  undefined8 uStack_1e0;
  undefined1 auStack_1d8 [28];
  dword dStack_1bc;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  long lStack_1b0;
  mach_header mStack_1a0;
  undefined2 uStack_180;
  undefined1 uStack_17e;
  undefined1 uStack_17d;
  undefined1 uStack_17c;
  undefined1 uStack_17b;
  undefined1 uStack_17a;
  char cStack_179;
  undefined4 uStack_178;
  undefined2 uStack_174;
  undefined2 uStack_172;
  undefined2 uStack_170;
  undefined4 uStack_16e;
  undefined2 uStack_16a;
  undefined2 uStack_168;
  undefined5 uStack_166;
  char cStack_161;
  ulong uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  long lStack_148;
  ulong uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined7 uStack_128;
  undefined4 uStack_121;
  undefined1 uStack_11d;
  undefined4 uStack_11c;
  undefined1 uStack_118;
  undefined5 uStack_117;
  undefined2 uStack_112;
  mach_header mStack_110;
  undefined1 auStack_f0 [8];
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
  long lStack_78;
  
  lStack_78 = *(long *)PTR____stack_chk_guard_100bfc980;
  mStack_1a0.magic = 0;
  mStack_1a0.cputype = 0;
  mStack_1a0.cpusubtype = 0;
  mStack_1a0.filetype = 0;
  FUN_100006ef8(&mStack_1a0,param_1);
  if (lRam0000000100c1b238 != -1) {
    FUN_1008da738();
  }
  uVar23 = uRam0000000100c1b230;
  FUN_1000c6c18();
  pmVar11 = pmRam0000000100cae440;
  if ((uVar23 & 1) == 0) {
    pmVar10 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0x10);
    if ((int)pmVar10 != 0) {
      FUN_1008da754(pmVar11);
    }
    goto LAB_1005e6504;
  }
  if (lRam0000000100c1b258 != -1) {
    FUN_1008da788();
  }
  uVar23 = uRam0000000100c1b250;
  FUN_10066c0fc();
  pmVar11 = pmRam0000000100cae440;
  pmVar10 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar10 == 0) {
LAB_1005e3be4:
    if ((uVar23 & 1) != 0) goto LAB_1005e3c2c;
LAB_1005e3be8:
    if (*(char *)((long)&param_1[0x24].flags + 2) == '\x01') goto LAB_1005e3c2c;
  }
  else {
    FUN_10010aa84(&mStack_1a0.ncmds,param_1);
    pdVar12 = (dword *)CONCAT26(mStack_1a0.sizeofcmds._2_2_,
                                CONCAT24((short)mStack_1a0.sizeofcmds,mStack_1a0.ncmds));
    if (-1 < cStack_179) {
      pdVar12 = &mStack_1a0.ncmds;
    }
    auStack_1d8._24_4_ = (undefined4)_UNK_100930b20;
    dStack_1bc = (dword)pdVar12;
    uStack_1b8 = (undefined4)((ulong)pdVar12 >> 0x20);
    __os_log_impl(0x100000000,pmVar11,0,"Read device %{public}s settings",auStack_1d8 + 0x18,0xc);
    if (-1 < cStack_179) goto LAB_1005e3be4;
    __ZdlPv(CONCAT26(mStack_1a0.sizeofcmds._2_2_,
                     CONCAT24((short)mStack_1a0.sizeofcmds,mStack_1a0.ncmds)));
    if ((uVar23 & 1) == 0) goto LAB_1005e3be8;
LAB_1005e3c2c:
    *(undefined2 *)&param_1[0x1b].cputype = 0;
    pmVar10 = pmRam0000000100cae440;
    pmVar11 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar11 != 0) {
      mStack_1a0.ncmds = (dword)_UNK_1009304c8;
      mStack_1a0.sizeofcmds._0_2_ = (short)uVar23;
      mStack_1a0.sizeofcmds._2_2_ = (undefined2)(uVar23 >> 0x10);
      mStack_1a0.flags._0_2_ = 0x400;
      mStack_1a0.flags._2_2_ = (ushort)*(byte *)((long)&param_1[0x24].flags + 2);
      mStack_1a0.reserved._0_2_ = 0;
      pmVar11 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar10,0,
                    "Identification - wiping ID cache due to build version update %d, override %d",
                    &mStack_1a0.ncmds,0xe);
    }
    FUN_1000c6a1c();
    (**(code **)(*(long *)pmVar11 + 0x38))();
    pmVar10 = pmRam0000000100cae440;
    if (((int)pmVar11 != 0) &&
       (pmVar11 = pmRam0000000100cae440, _os_log_type_enabled(pmRam0000000100cae440,0x10),
       (int)pmVar11 != 0)) {
      FUN_1008da7a0();
      pmVar11 = pmVar10;
    }
    FUN_1000c6a1c();
    (**(code **)(*(long *)pmVar11 + 0x48))();
    pmVar10 = pmRam0000000100cae440;
    if (((int)pmVar11 != 0) &&
       (pmVar11 = pmRam0000000100cae440, _os_log_type_enabled(pmRam0000000100cae440,0x10),
       (int)pmVar11 != 0)) {
      FUN_1008da7d4(pmVar10);
    }
  }
  mStack_1a0.ncmds = 0;
  mStack_1a0.sizeofcmds._0_2_ = 0;
  mStack_1a0.sizeofcmds._2_2_ = 0;
  pdVar12 = &mStack_1a0.ncmds;
  FUN_100035440();
  lVar28 = (long)(int)mStack_1a0.ncmds;
  lVar27 = (long)(short)mStack_1a0.sizeofcmds;
  auStack_1d8._24_4_ = 0;
  dStack_1bc = 0;
  uStack_1b8 = 0;
  uStack_1b4 = 0;
  lStack_1b0 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pdVar12 + 0x20))();
  pmVar11 = pmRam0000000100cae440;
  if ((int)pdVar12 == 0) {
    pmVar10 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar10 != 0) {
      FUN_1000c6c24(auStack_1d8,param_1 + 4);
      pmVar10 = (mach_header *)auStack_1d8._0_8_;
      if (-1 < (long)auStack_1d8._16_8_) {
        pmVar10 = (mach_header *)auStack_1d8;
      }
      ppmVar18 = (mach_header **)CONCAT44(dStack_1bc,auStack_1d8._24_4_);
      if (-1 < lStack_1b0) {
        ppmVar18 = (mach_header **)(auStack_1d8 + 0x18);
      }
      mStack_1a0.ncmds = (dword)_UNK_100935808;
      mStack_1a0.sizeofcmds._0_2_ = 0x6168;
      mStack_1a0.sizeofcmds._2_2_ = 0x6873;
      mStack_1a0.flags._0_2_ = 0;
      mStack_1a0.flags._2_2_ = 0;
      mStack_1a0.reserved._0_2_ = 0x821;
      mStack_1a0.reserved._2_2_ = SUB82(pmVar10,0);
      uStack_180 = (undefined2)((ulong)pmVar10 >> 0x10);
      uStack_17e = (undefined1)((ulong)pmVar10 >> 0x20);
      uStack_17d = (undefined1)((ulong)pmVar10 >> 0x28);
      uStack_17c = (undefined1)((ulong)pmVar10 >> 0x30);
      uStack_17b = (undefined1)((ulong)pmVar10 >> 0x38);
      uStack_17a = 0x70;
      cStack_179 = '\b';
      uStack_178 = 0x68736168;
      uStack_174 = 0;
      uStack_172 = 0;
      uStack_170 = 0x821;
      uStack_16e = SUB84(ppmVar18,0);
      uStack_16a = (undefined2)((ulong)ppmVar18 >> 0x20);
      uStack_168 = (undefined2)((ulong)ppmVar18 >> 0x30);
      __os_log_impl(0x100000000,pmVar11,0,
                    "Read name result success, device address = %{private, mask.hash}s, value = %{private, mask.hash}s"
                    ,&mStack_1a0.ncmds,0x2a);
      if (auStack_1d8[0x17] < '\0') {
        __ZdlPv(auStack_1d8._0_8_);
      }
    }
    pmVar11 = (mach_header *)&param_1[0xb].cpusubtype;
    __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSERKS5_
              (pmVar11,auStack_1d8 + 0x18);
    param_1[0xc].magic = (int)lVar28;
    param_1[0xc].cputype = (int)((ulong)lVar28 >> 0x20);
    param_1[0xc].cpusubtype = (int)lVar27;
    param_1[0xc].filetype = (int)((ulong)lVar27 >> 0x20);
    *(undefined1 *)((long)&param_1[0x32].magic + 1) = 1;
LAB_1005e4128:
    FUN_10003ba88();
    (**(code **)(*(long *)pmVar11 + 0x1d8))();
  }
  else {
    pmVar11 = param_1;
    FUN_1000cbaf4();
    if ((int)pmVar11 != 0) {
      _IsAppleInternalBuild();
      pmVar10 = pmRam0000000100cae440;
      if ((int)pmVar11 == 0) {
        pmVar11 = pmRam0000000100cae440;
        _os_log_type_enabled(pmRam0000000100cae440,0x11);
        if ((int)pmVar11 != 0) {
          FUN_1000c6c24(auStack_1d8,param_1 + 4);
          pmVar11 = (mach_header *)auStack_1d8._0_8_;
          if (-1 < (long)auStack_1d8._16_8_) {
            pmVar11 = (mach_header *)auStack_1d8;
          }
          ppmVar18 = (mach_header **)CONCAT44(dStack_1bc,auStack_1d8._24_4_);
          if (-1 < lStack_1b0) {
            ppmVar18 = (mach_header **)(auStack_1d8 + 0x18);
          }
          mStack_1a0.ncmds = (dword)_UNK_100935860;
          mStack_1a0.sizeofcmds._0_2_ = (short)pdVar12;
          mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pdVar12 >> 0x10);
          mStack_1a0.flags._0_2_ = 0x870;
          mStack_1a0.flags._2_2_ = 0x6168;
          mStack_1a0.reserved._0_2_ = 0x6873;
          mStack_1a0.reserved._2_2_ = 0;
          uStack_180 = 0;
          uStack_17e = 0x21;
          uStack_17d = 8;
          uStack_17c = SUB81(pmVar11,0);
          uStack_17b = (undefined1)((ulong)pmVar11 >> 8);
          uStack_17a = (undefined1)((ulong)pmVar11 >> 0x10);
          cStack_179 = (char)((ulong)pmVar11 >> 0x18);
          uStack_178 = (undefined4)((ulong)pmVar11 >> 0x20);
          uStack_174 = 0x870;
          uStack_172 = 0x6168;
          uStack_170 = 0x6873;
          uStack_16e = 0;
          uStack_16a = 0x821;
          uStack_168 = SUB82(ppmVar18,0);
          uStack_166 = (undefined5)((ulong)ppmVar18 >> 0x10);
          cStack_161 = (char)((ulong)ppmVar18 >> 0x38);
          pmVar11 = &__mh_execute_header;
          __os_log_fault_impl(0x100000000,pmVar10,0x11,
                              "Read name result failure = %d, device address = %{private, mask.hash}s, value = %{private, mask.hash}s"
                              ,&mStack_1a0.ncmds,0x30);
          if (auStack_1d8[0x17] < '\0') {
            __ZdlPv();
            pmVar11 = (mach_header *)auStack_1d8._0_8_;
          }
        }
      }
      else {
        uStack_80 = 0;
        uStack_98 = 0;
        uStack_a0 = 0;
        uStack_88 = 0;
        uStack_90 = 0;
        uStack_b8 = 0;
        uStack_c0 = 0;
        uStack_a8 = 0;
        uStack_b0 = 0;
        uStack_d8 = 0;
        uStack_e0 = 0;
        uStack_c8 = 0;
        uStack_d0 = 0;
        mStack_110.flags = 0;
        mStack_110.reserved = 0;
        mStack_110.ncmds = 0;
        mStack_110.sizeofcmds = 0;
        uStack_e8 = 0;
        auStack_f0 = (undefined1  [8])0x0;
        uStack_118 = 0;
        uStack_117 = 0;
        uStack_112 = 0;
        uStack_11d = 0;
        uStack_11c = 0;
        mStack_110.cpusubtype = 0;
        mStack_110.filetype = 0;
        mStack_110.magic._0_1_ = 0;
        mStack_110._1_5_ = 0;
        mStack_110.cputype._2_2_ = 0;
        uStack_138 = 0;
        uStack_140 = 0;
        uStack_128 = 0;
        uStack_121 = 0;
        uStack_130 = 0;
        uStack_158 = 0;
        uStack_160 = 0;
        lStack_148 = 0;
        uStack_150 = 0;
        uStack_178 = 0;
        uStack_174 = 0;
        uStack_172 = 0;
        uStack_180 = 0;
        uStack_17e = 0;
        uStack_17d = 0;
        uStack_17c = 0;
        uStack_17b = 0;
        uStack_17a = 0;
        cStack_179 = 0;
        uStack_168 = 0;
        uStack_166 = 0;
        cStack_161 = '\0';
        uStack_170 = 0;
        uStack_16e = 0;
        uStack_16a = 0;
        mStack_1a0.flags._0_2_ = 0;
        mStack_1a0.flags._2_2_ = 0;
        mStack_1a0.reserved._0_2_ = 0;
        mStack_1a0.reserved._2_2_ = 0;
        mStack_1a0.ncmds = 0;
        mStack_1a0.sizeofcmds._0_2_ = 0;
        mStack_1a0.sizeofcmds._2_2_ = 0;
        FUN_1003e93d0(&mStack_1a0.ncmds);
        puVar13 = &uStack_180;
        FUN_1003e9824(puVar13,"Read name result failure = ",0x1b);
        __ZNSt3__19to_stringEi(auStack_1d8,pdVar12);
        pmVar11 = (mach_header *)auStack_1d8._0_8_;
        if (-1 < (long)auStack_1d8._16_8_) {
          auStack_1d8._8_8_ = (ulong)auStack_1d8._16_8_ >> 0x38;
          pmVar11 = (mach_header *)auStack_1d8;
        }
        FUN_1003e9824(puVar13,pmVar11,auStack_1d8._8_8_);
        FUN_1003e9824();
        FUN_1000c6c24(&pppppppuStack_1f0,param_1 + 4);
        pppppppuVar3 = pppppppuStack_1f0;
        if (-1 < uStack_1e0) {
          pppppppuVar3 = &pppppppuStack_1f0;
        }
        pppppppuVar14 = pppppppuVar3;
        _strlen(pppppppuVar3);
        FUN_1003e9824(puVar13,pppppppuVar3,pppppppuVar14);
        FUN_1003e9824();
        ppmVar18 = (mach_header **)CONCAT44(dStack_1bc,auStack_1d8._24_4_);
        if (-1 < lStack_1b0) {
          ppmVar18 = (mach_header **)(auStack_1d8 + 0x18);
        }
        lVar25 = (long)ppmVar18;
        _strlen(ppmVar18);
        FUN_1003e9824(puVar13,ppmVar18,lVar25);
        if (uStack_1e0._7_1_ < '\0') {
          __ZdlPv(pppppppuStack_1f0);
        }
        if ((long)auStack_1d8._16_8_ < 0) {
          __ZdlPv(auStack_1d8._0_8_);
        }
        FUN_1003e9b14(&uStack_178);
        ppmVar15 = (mach_header **)auStack_1d8;
        FUN_1001ec44c();
        _memmove();
        *(undefined1 *)((long)ppmVar15 + (long)ppmVar18) = 0;
        pmVar11 = (mach_header *)auStack_1d8._0_8_;
        if (-1 < (long)auStack_1d8._16_8_) {
          pmVar11 = (mach_header *)auStack_1d8;
        }
        FUN_1002a2e3c(pmVar11);
        if (auStack_1d8[0x17] < '\0') {
          __ZdlPv(auStack_1d8._0_8_);
        }
        puVar7 = 
        PTR___ZTTNSt3__118basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc750;
        lVar25 = *(long *)
                  PTR___ZTTNSt3__118basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc750
        ;
        mStack_1a0.ncmds = (dword)lVar25;
        mStack_1a0.sizeofcmds._0_2_ = (short)((ulong)lVar25 >> 0x20);
        mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)lVar25 >> 0x30);
        uVar5 = *(undefined8 *)
                 (
                 PTR___ZTTNSt3__118basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc750
                 + 0x48);
        *(undefined8 *)((long)&mStack_1a0.ncmds + *(long *)(lVar25 + -0x18)) =
             *(undefined8 *)
              (
              PTR___ZTTNSt3__118basic_stringstreamIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc750
              + 0x40);
        uStack_180 = (undefined2)uVar5;
        uStack_17e = (undefined1)((ulong)uVar5 >> 0x10);
        uStack_17d = (undefined1)((ulong)uVar5 >> 0x18);
        uStack_17c = (undefined1)((ulong)uVar5 >> 0x20);
        uStack_17b = (undefined1)((ulong)uVar5 >> 0x28);
        uStack_17a = (undefined1)((ulong)uVar5 >> 0x30);
        cStack_179 = (char)((ulong)uVar5 >> 0x38);
        puVar1 = PTR___ZTVNSt3__115basic_stringbufIcNS_11char_traitsIcEENS_9allocatorIcEEEE_100bfc778
                 + 0x10;
        uStack_178 = SUB84(puVar1,0);
        uStack_174 = (undefined2)((ulong)puVar1 >> 0x20);
        uStack_172 = (undefined2)((ulong)puVar1 >> 0x30);
        if ((char)uStack_121 < '\0') {
          __ZdlPv(uStack_138);
        }
        puVar1 = PTR___ZTVNSt3__115basic_streambufIcNS_11char_traitsIcEEEE_100bfc770 + 0x10;
        uStack_178 = SUB84(puVar1,0);
        uStack_174 = (undefined2)((ulong)puVar1 >> 0x20);
        uStack_172 = (undefined2)((ulong)puVar1 >> 0x30);
        __ZNSt3__16localeD1Ev(&uStack_170);
        __ZNSt3__114basic_iostreamIcNS_11char_traitsIcEEED2Ev(&mStack_1a0.ncmds,puVar7 + 8);
        pmVar11 = &mStack_110;
        __ZNSt3__19basic_iosIcNS_11char_traitsIcEEED2Ev();
      }
      goto LAB_1005e4128;
    }
  }
  auStack_1d8._0_8_ = (mach_header *)0x0;
  auStack_1d8._8_8_ = 0;
  auStack_1d8._16_8_ = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0xd0))();
  if ((int)pmVar11 == 0) {
    pmVar11 = (mach_header *)&param_1[0xc].ncmds;
    __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSERKS5_(pmVar11,auStack_1d8);
  }
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0xe0))();
  if ((int)pmVar11 == 0) {
    pmVar11 = param_1 + 10;
    __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSERKS5_
              (pmVar11,auStack_1d8 + 0x18);
    param_1[10].flags = (int)lVar28;
    param_1[10].reserved = (int)((ulong)lVar28 >> 0x20);
    param_1[0xb].magic = (int)lVar27;
    param_1[0xb].cputype = (int)((ulong)lVar27 >> 0x20);
  }
  dStack_1f4 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x100))();
  if ((int)pmVar11 == 0) {
    param_1[0xd].cpusubtype = dStack_1f4;
    param_1[0xd].ncmds = (int)lVar28;
    param_1[0xd].sizeofcmds = (int)((ulong)lVar28 >> 0x20);
    param_1[0xd].flags = (int)lVar27;
    param_1[0xd].reserved = (int)((ulong)lVar27 >> 0x20);
    if (lRam0000000100c1b238 != -1) {
      FUN_1008da738();
    }
    uVar23 = uRam0000000100c1b230;
    FUN_100619aa4(uRam0000000100c1b230,&param_1[0xd].cpusubtype,param_1);
    param_1[9].cpusubtype = (dword)uVar23;
    param_1[9].ncmds = (int)lVar28;
    param_1[9].sizeofcmds = (int)((ulong)lVar28 >> 0x20);
    param_1[9].flags = (int)lVar27;
    param_1[9].reserved = (int)((ulong)lVar27 >> 0x20);
  }
  pmVar16 = pmRam0000000100cae440;
  pmVar10 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar10 != 0) {
    mStack_1a0.ncmds = (dword)_UNK_1009304c8;
    mStack_1a0.sizeofcmds._0_2_ = (short)pmVar11;
    mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pmVar11 >> 0x10);
    mStack_1a0.flags._0_2_ = 0x400;
    mStack_1a0.flags._2_2_ = (ushort)dStack_1f4;
    mStack_1a0.reserved._0_2_ = (undefined2)(dStack_1f4 >> 0x10);
    pmVar10 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"Read classOfDevice result %d, value = 0x%x",
                  &mStack_1a0.ncmds,0xe);
  }
  ppppppuStack_1e8 = (undefined8 ******)0x0;
  uStack_1e0 = 0;
  pppppppuStack_1f0 = &ppppppuStack_1e8;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0xf0))();
  if ((int)pmVar10 == 0) {
    pmVar10 = param_1 + 0xe;
    FUN_1005ff968(pmVar10,&pppppppuStack_1f0);
    param_1[0xe].flags = (int)lVar28;
    param_1[0xe].reserved = (int)((ulong)lVar28 >> 0x20);
    param_1[0xf].magic = (int)lVar27;
    param_1[0xf].cputype = (int)((ulong)lVar27 >> 0x20);
  }
  *(undefined2 *)&param_1[0x27].filetype = 0;
  *(undefined1 *)((long)&param_1[0x27].filetype + 3) = 0;
  param_1[0x28].magic = 0;
  param_1[0x28].cpusubtype = 0;
  param_1[0x28].filetype = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x5e8))();
  dStack_1f8 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x618))();
  pmVar16 = pmRam0000000100cae440;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  dVar26 = dStack_1f8;
  if ((int)pmVar11 != 0) {
    FUN_10010aa84(&uStack_210,param_1);
    puVar17 = (undefined4 *)CONCAT44(uStack_20c,uStack_210);
    if (-1 < uStack_200) {
      puVar17 = &uStack_210;
    }
    mStack_1a0.ncmds = (dword)_UNK_100932b90;
    mStack_1a0.sizeofcmds._0_2_ = (short)pmVar10;
    mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pmVar10 >> 0x10);
    mStack_1a0.flags._0_2_ = 0x400;
    mStack_1a0.flags._2_2_ = (ushort)dVar26;
    mStack_1a0.reserved._0_2_ = (undefined2)(dVar26 >> 0x10);
    mStack_1a0.reserved._2_2_ = 0x822;
    uStack_180 = SUB82(puVar17,0);
    uStack_17e = (undefined1)((ulong)puVar17 >> 0x10);
    uStack_17d = (undefined1)((ulong)puVar17 >> 0x18);
    uStack_17c = (undefined1)((ulong)puVar17 >> 0x20);
    uStack_17b = (undefined1)((ulong)puVar17 >> 0x28);
    uStack_17a = (undefined1)((ulong)puVar17 >> 0x30);
    cStack_179 = (char)((ulong)puVar17 >> 0x38);
    pmVar11 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"readGAPA result %d, value = 0x%x for %{public}s",
                  &mStack_1a0.ncmds,0x18);
    if (uStack_200 < 0) {
      pmVar11 = (mach_header *)CONCAT44(uStack_20c,uStack_210);
      __ZdlPv();
    }
  }
  dVar26 = dStack_1f8;
  if ((int)pmVar10 != 0) {
    dVar26 = 0;
  }
  param_1[0x15].flags = dVar26;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x120))();
  if ((int)pmVar11 == 0) {
    if (lRam0000000100c1f468 != -1) {
      FUN_1008da808();
    }
    FUN_1006bb6bc(uRam0000000100c1f460,param_1);
    FUN_100006f28(&mStack_1a0);
    if (lRam0000000100c1b238 != -1) {
      FUN_1008da738();
    }
    FUN_100618e08(uRam0000000100c1b230,param_1,4);
    pmVar11 = &mStack_1a0;
    FUN_100006db4();
  }
  dStack_214 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x130))();
  if ((int)pmVar11 == 0) {
    uVar20 = (undefined2)dStack_214;
    bVar19 = (byte)dStack_214 & 1;
    uVar23 = CONCAT62((int6)(((ulong)CONCAT22(uVar20,uVar20) << 0x20) >> 0x10),uVar20) &
             0xffffffffffff00ff;
    uVar29 = CONCAT44((int)(uVar23 >> 0x20),CONCAT22(uVar20,(short)uVar23)) & 0xffffffff00ffffff;
    uVar23 = NEON_ushl(CONCAT26((short)(uVar29 >> 0x30),
                                CONCAT24((short)(uVar23 >> 0x20),(int)uVar29)) & 0xff00ffffffffff,
                       _UNK_100939e38,2);
    uVar29 = uVar23 & 0xffffffffffffff01;
    uVar23 = CONCAT44((int)(uVar29 >> 0x20),CONCAT22((short)(uVar23 >> 0x10),(short)uVar29)) &
             0xffffffffff01ffff;
    uVar23 = CONCAT26((short)(uVar23 >> 0x30),CONCAT24((short)(uVar29 >> 0x20),(int)uVar23)) &
             0xff01ff01ffffffff;
    dVar26 = dStack_214;
  }
  else {
    bVar19 = 0;
    uVar23 = _UNK_100939e30;
    dVar26 = 0;
  }
  *(byte *)((long)&param_1[0x18].magic + 2) = bVar19;
  *(uint *)((long)&param_1[0x18].magic + 3) =
       CONCAT13((char)(uVar23 >> 0x30),
                CONCAT12((char)(uVar23 >> 0x20),CONCAT11((char)(uVar23 >> 0x10),(char)uVar23)));
  param_1[0x2f].flags = dVar26;
  pmVar16 = pmRam0000000100cae440;
  pmVar10 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar10 != 0) {
    mStack_1a0.ncmds = (dword)_UNK_1009304c8;
    mStack_1a0.sizeofcmds._0_2_ = (short)pmVar11;
    mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pmVar11 >> 0x10);
    mStack_1a0.flags._0_2_ = 0x400;
    mStack_1a0.flags._2_2_ = (ushort)dStack_214;
    mStack_1a0.reserved._0_2_ = (undefined2)(dStack_214 >> 0x10);
    pmVar10 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"Read PhonebookSyncSettings result %d, settings 0x%x",
                  &mStack_1a0.ncmds,0xe);
  }
  uStack_215 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x1a0))();
  uVar2 = uStack_215;
  if ((int)pmVar10 != 0) {
    uVar2 = 0;
  }
  *(undefined1 *)((long)&param_1[0x18].cputype + 3) = uVar2;
  uStack_218 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x1b0))();
  uVar6 = uStack_218;
  if ((int)pmVar10 != 0) {
    uVar6 = 0;
  }
  *(ushort *)((long)&param_1[0x18].filetype + 2) = uVar6;
  pmVar16 = pmRam0000000100cae440;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if (((ulong)pmVar11 & 1) != 0) {
    mStack_1a0.ncmds = (dword)_UNK_1009304c8;
    mStack_1a0.sizeofcmds._0_2_ = (short)pmVar10;
    mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pmVar10 >> 0x10);
    mStack_1a0.flags._0_2_ = 0x400;
    mStack_1a0.reserved._0_2_ = 0;
    pmVar11 = &__mh_execute_header;
    mStack_1a0.flags._2_2_ = uVar6;
    __os_log_impl(0x100000000,pmVar16,0,"Read lastAVRCPVersion result %d, version %d",
                  &mStack_1a0.ncmds,0xe);
  }
  uStack_21a = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x1c0))();
  uVar20 = uStack_21a;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x18].ncmds = uVar20;
  uStack_21c = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x1d0))();
  uVar20 = uStack_21c;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x18].ncmds + 2) = uVar20;
  uStack_21e = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x1e0))();
  uVar20 = uStack_21e;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x18].sizeofcmds = uVar20;
  uStack_220 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x1f0))();
  uVar20 = uStack_220;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x18].sizeofcmds + 2) = uVar20;
  uStack_222 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x200))();
  uVar20 = uStack_222;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x18].flags = uVar20;
  uStack_224 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x210))();
  uVar20 = uStack_224;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x18].flags + 2) = uVar20;
  uStack_226 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x220))();
  uVar20 = uStack_226;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x18].reserved = uVar20;
  uStack_228 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x230))();
  uVar20 = uStack_228;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x18].reserved + 2) = uVar20;
  uStack_22a = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x240))();
  uVar20 = uStack_22a;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x19].magic = uVar20;
  uStack_22c = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x250))();
  uVar20 = uStack_22c;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x19].magic + 2) = uVar20;
  uStack_22e = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x260))();
  uVar20 = uStack_22e;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x19].cputype = uVar20;
  uStack_230 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x270))();
  uVar20 = uStack_230;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x19].cputype + 2) = uVar20;
  uStack_232 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x280))();
  uVar20 = uStack_232;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x19].cpusubtype = uVar20;
  uStack_234 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x290))();
  uVar20 = uStack_234;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x19].cpusubtype + 2) = uVar20;
  uStack_236 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x2a0))();
  uVar20 = uStack_236;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x19].filetype = uVar20;
  uStack_238 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x2b0))();
  uVar20 = uStack_238;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x19].filetype + 2) = uVar20;
  uStack_23a = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x2c0))();
  uVar20 = uStack_23a;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x19].ncmds = uVar20;
  uStack_23c = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x2d0))();
  uVar20 = uStack_23c;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)((long)&param_1[0x19].ncmds + 2) = uVar20;
  uStack_23e = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x2e0))();
  uVar20 = uStack_23e;
  if ((int)pmVar11 != 0) {
    uVar20 = 0;
  }
  *(undefined2 *)&param_1[0x19].sizeofcmds = uVar20;
  param_1[0x19].flags = 0;
  FUN_1000c6a1c();
  pdVar12 = &param_1[0x19].reserved;
  (**(code **)(*(long *)pmVar11 + 0x30))();
  if ((int)pmVar11 == 0) {
    *(undefined1 *)&param_1[0x1b].cputype = 1;
    pmVar10 = pmRam0000000100cae440;
    pmVar11 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar11 != 0) {
      FUN_10010aa84(&uStack_210,param_1);
      puVar17 = (undefined4 *)CONCAT44(uStack_20c,uStack_210);
      if (-1 < uStack_200) {
        puVar17 = &uStack_210;
      }
      mStack_1a0.ncmds = (dword)_UNK_100930fa8;
      mStack_1a0.sizeofcmds._0_2_ = (short)puVar17;
      mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)puVar17 >> 0x10);
      mStack_1a0.flags._0_2_ = (undefined2)((ulong)puVar17 >> 0x20);
      mStack_1a0.flags._2_2_ = (ushort)((ulong)puVar17 >> 0x30);
      mStack_1a0.reserved._0_2_ = 0x412;
      mStack_1a0.reserved._2_2_ = 0x14;
      uStack_180 = 0;
      uStack_17e = 0x32;
      uStack_17d = 8;
      uStack_17c = SUB81(pdVar12,0);
      uStack_17b = (undefined1)((ulong)pdVar12 >> 8);
      uStack_17a = (undefined1)((ulong)pdVar12 >> 0x10);
      cStack_179 = (char)((ulong)pdVar12 >> 0x18);
      uStack_178 = (undefined4)((ulong)pdVar12 >> 0x20);
      pmVar11 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar10,0,
                    "Primary Identification - persisted {device %{public}s, %{public}.20P}",
                    &mStack_1a0.ncmds,0x1c);
      if (uStack_200 < 0) {
        pmVar11 = (mach_header *)CONCAT44(uStack_20c,uStack_210);
        __ZdlPv();
      }
    }
  }
  else {
    *(undefined1 *)&param_1[0x1b].cputype = 0;
  }
  FUN_1000c6a1c();
  pdVar12 = &param_1[0x1a].ncmds;
  (**(code **)(*(long *)pmVar11 + 0x40))();
  if ((int)pmVar11 == 0) {
    *(undefined1 *)((long)&param_1[0x1b].cputype + 1) = 1;
    pmVar11 = pmRam0000000100cae440;
    pmVar10 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar10 != 0) {
      FUN_10010aa84(&uStack_210,param_1);
      puVar17 = (undefined4 *)CONCAT44(uStack_20c,uStack_210);
      if (-1 < uStack_200) {
        puVar17 = &uStack_210;
      }
      mStack_1a0.ncmds = (dword)_UNK_100930fa8;
      mStack_1a0.sizeofcmds._0_2_ = (short)puVar17;
      mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)puVar17 >> 0x10);
      mStack_1a0.flags._0_2_ = (undefined2)((ulong)puVar17 >> 0x20);
      mStack_1a0.flags._2_2_ = (ushort)((ulong)puVar17 >> 0x30);
      mStack_1a0.reserved._0_2_ = 0x412;
      mStack_1a0.reserved._2_2_ = 0x14;
      uStack_180 = 0;
      uStack_17e = 0x32;
      uStack_17d = 8;
      uStack_17c = SUB81(pdVar12,0);
      uStack_17b = (undefined1)((ulong)pdVar12 >> 8);
      uStack_17a = (undefined1)((ulong)pdVar12 >> 0x10);
      cStack_179 = (char)((ulong)pdVar12 >> 0x18);
      uStack_178 = (undefined4)((ulong)pdVar12 >> 0x20);
      __os_log_impl(0x100000000,pmVar11,0,
                    "Secondary Identification  - persisted {device %{public}s, %{public}.20P}",
                    &mStack_1a0.ncmds,0x1c);
      if (uStack_200 < 0) {
        __ZdlPv(CONCAT44(uStack_20c,uStack_210));
      }
    }
  }
  else {
    *(undefined1 *)((long)&param_1[0x1b].cputype + 1) = 0;
  }
  pmVar10 = pmRam0000000100cae440;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar11 != 0) {
    FUN_10010aa84(&mStack_1a0.ncmds,param_1);
    pdVar12 = (dword *)CONCAT26(mStack_1a0.sizeofcmds._2_2_,
                                CONCAT24((short)mStack_1a0.sizeofcmds,mStack_1a0.ncmds));
    if (-1 < cStack_179) {
      pdVar12 = &mStack_1a0.ncmds;
    }
    uStack_210 = (undefined4)_UNK_100930b20;
    uStack_20c = SUB84(pdVar12,0);
    uStack_208 = (undefined4)((ulong)pdVar12 >> 0x20);
    pmVar11 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar10,0,"Read SDP mirroring state for device %{public}s",&uStack_210
                  ,0xc);
    if (cStack_179 < '\0') {
      pmVar11 = (mach_header *)
                CONCAT26(mStack_1a0.sizeofcmds._2_2_,
                         CONCAT24((short)mStack_1a0.sizeofcmds,mStack_1a0.ncmds));
      __ZdlPv();
    }
  }
  bStack_23f = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x2f0))();
  if ((int)pmVar11 == 0) {
    auStack_f0 = (undefined1  [8])0x0;
    mStack_110.cpusubtype = 0;
    mStack_110.filetype = 0;
    mStack_110.magic._0_1_ = 0;
    mStack_110._1_5_ = 0;
    mStack_110.cputype._2_2_ = 0;
    mStack_110.flags = 0;
    mStack_110.reserved = 0;
    mStack_110.ncmds = 0;
    mStack_110.sizeofcmds = 0;
    uStack_128 = 0;
    uStack_130 = 0;
    uStack_118 = 0;
    uStack_117 = 0;
    uStack_112 = 0;
    uStack_121 = 0;
    uStack_11d = 0;
    uStack_11c = 0;
    lStack_148 = 0;
    uStack_150 = 0;
    uStack_138 = 0;
    uStack_140 = 0;
    uStack_168 = 0;
    uStack_166 = 0;
    cStack_161 = 0;
    uStack_170 = 0;
    uStack_16e = 0;
    uStack_16a = 0;
    uStack_158 = 0;
    uStack_160 = 0;
    mStack_1a0.flags._0_2_ = 0;
    mStack_1a0.flags._2_2_ = 0;
    mStack_1a0.reserved._0_2_ = 0;
    mStack_1a0.reserved._2_2_ = 0;
    mStack_1a0.ncmds = 0;
    mStack_1a0.sizeofcmds._0_2_ = 0;
    mStack_1a0.sizeofcmds._2_2_ = 0;
    uStack_178 = 0;
    uStack_174 = 0;
    uStack_172 = 0;
    uStack_180 = 0;
    uStack_17e = 0;
    uStack_17d = 0;
    uStack_17c = 0;
    uStack_17b = 0;
    uStack_17a = 0;
    cStack_179 = '\0';
    FUN_100101334((ulong)&mStack_1a0.ncmds | 1);
    uVar23 = uStack_160;
    uStack_17e = 0;
    uStack_17c = 0;
    uStack_160._0_3_ = (uint3)(ushort)uStack_160;
    uVar29 = uStack_160;
    uStack_160._5_3_ = SUB83(uVar23,5);
    uStack_160._0_5_ = (uint5)(uint)uVar29;
    uStack_11c = 0;
    uStack_168 = 0;
    uStack_166 = 0;
    cStack_161 = '\0';
    uStack_178 = 0;
    uStack_174 = 0;
    uStack_172 = 0;
    uStack_170 = 0;
    uStack_16e = 0;
    uStack_16a = 0;
    uStack_160 = uStack_160 & 0xffffffffffffff00;
    lStack_148 = 0;
    uStack_158 = 0;
    uStack_150 = 0;
    uStack_140 = uStack_140 & 0xffffffffffffff00;
    uStack_128 = 0;
    uStack_138 = 0;
    uStack_130 = 0;
    uStack_121 = 0;
    uStack_118 = 1;
    mStack_110._1_5_ = 0;
    uStack_117 = 0;
    uStack_112 = 0;
    mStack_110.magic._0_1_ = 0;
    mStack_110.flags = 0;
    mStack_110.reserved = 0;
    mStack_110.cpusubtype = 0;
    mStack_110.filetype = 0;
    mStack_110.ncmds = 0;
    mStack_110.sizeofcmds = 0;
    uVar20 = auStack_f0._6_2_;
    uVar6 = auStack_f0._0_2_;
    auStack_f0._0_6_ = CONCAT42(0,uVar6 & 0xff00);
    auStack_f0 = (undefined1  [8])CONCAT26(uVar20,auStack_f0._0_6_);
    pmVar11 = param_1;
    FUN_1005e6bec(param_1,&mStack_1a0.ncmds);
    FUN_1000071f0();
    FUN_10008c49c();
    bVar19 = bStack_23f;
    if (((uint)pmVar11 & (uint)auStack_f0[4]) == 1) {
      if ((bStack_23f & 1) == 0) {
        mStack_2f8._24_8_ = mStack_2f8._24_8_ & 0xffffffffffffff00;
        FUN_1000110f0();
        FUN_1002274a0(&uStack_210,"SDPMirroring");
        FUN_1002274a0(&uStack_260,"DisableSDPMirroring");
        (**(code **)(*(long *)pmVar11 + 0x48))(pmVar11,&uStack_210,&uStack_260,&mStack_2f8.flags);
        if (uStack_250._7_1_ < '\0') {
          __ZdlPv(CONCAT44(uStack_25c,uStack_260));
        }
        if (uStack_200 < 0) {
          __ZdlPv(CONCAT44(uStack_20c,uStack_210));
        }
        pmVar10 = pmRam0000000100cae440;
        pmVar16 = pmRam0000000100cae440;
        _os_log_type_enabled(pmRam0000000100cae440,0);
        if ((int)pmVar11 == 0) {
          if ((int)pmVar16 != 0) {
            FUN_10010aa84(&uStack_210,param_1);
            puVar17 = (undefined4 *)CONCAT44(uStack_20c,uStack_210);
            if (-1 < uStack_200) {
              puVar17 = &uStack_210;
            }
            uStack_260 = (undefined4)_UNK_100930b20;
            uStack_25c = SUB84(puVar17,0);
            uStack_258 = (undefined4)((ulong)puVar17 >> 0x20);
            __os_log_impl(0x100000000,pmVar10,0,
                          "SDP mirroring state for device %{public}s is incorrect as key isn\'t present. Resetting."
                          ,&uStack_260,0xc);
            if (uStack_200 < 0) {
              __ZdlPv(CONCAT44(uStack_20c,uStack_210));
            }
          }
          bVar19 = 1;
        }
        else {
          if ((int)pmVar16 != 0) {
            FUN_10010aa84(&uStack_210,param_1);
            puVar17 = (undefined4 *)CONCAT44(uStack_20c,uStack_210);
            if (-1 < uStack_200) {
              puVar17 = &uStack_210;
            }
            uStack_260 = (undefined4)_UNK_100930b20;
            uStack_25c = SUB84(puVar17,0);
            uStack_258 = (undefined4)((ulong)puVar17 >> 0x20);
            __os_log_impl(0x100000000,pmVar10,0,
                          "SDP mirroring state for device %{public}s is correct as key is present. Updating."
                          ,&uStack_260,0xc);
            if (uStack_200 < 0) {
              __ZdlPv(CONCAT44(uStack_20c,uStack_210));
            }
          }
          bVar19 = (byte)mStack_2f8.flags ^ 1;
        }
        goto LAB_1005e4ff8;
      }
    }
    else {
LAB_1005e4ff8:
      *(byte *)&param_1[0x18].filetype = bVar19;
    }
    if ((char)uStack_121 < '\0') {
      __ZdlPv(uStack_138);
    }
    if (lStack_148 < 0) {
      __ZdlPv(uStack_158);
    }
    if (cStack_161 < '\0') {
      __ZdlPv(CONCAT26(uStack_172,CONCAT24(uStack_174,uStack_178)));
    }
    FUN_100043ed4((ulong)&mStack_1a0.ncmds | 1);
  }
  else {
    *(undefined1 *)&param_1[0x18].filetype = 1;
  }
  param_1[0x1b].ncmds = param_1[0x1b].cpusubtype;
  pmVar10 = pmRam0000000100cae440;
  param_1[0x1b].sizeofcmds = param_1[0x1b].filetype;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar11 != 0) {
    FUN_10010aa84(&mStack_1a0.ncmds,param_1);
    pdVar12 = (dword *)CONCAT26(mStack_1a0.sizeofcmds._2_2_,
                                CONCAT24((short)mStack_1a0.sizeofcmds,mStack_1a0.ncmds));
    if (-1 < cStack_179) {
      pdVar12 = &mStack_1a0.ncmds;
    }
    uStack_210 = (undefined4)_UNK_100930b20;
    uStack_20c = SUB84(pdVar12,0);
    uStack_208 = (undefined4)((ulong)pdVar12 >> 0x20);
    pmVar11 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar10,0,"Read group list for %{public}s",&uStack_210,0xc);
    if (cStack_179 < '\0') {
      pmVar11 = (mach_header *)
                CONCAT26(mStack_1a0.sizeofcmds._2_2_,
                         CONCAT24((short)mStack_1a0.sizeofcmds,mStack_1a0.ncmds));
      __ZdlPv();
    }
  }
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x140))();
  if ((int)pmVar11 != 0) {
    mStack_1a0.ncmds = 0xffffffff;
    puVar17 = *(undefined4 **)&param_1[0x1b].ncmds;
    if (puVar17 < *(undefined4 **)&param_1[0x1b].flags) {
      pmVar11 = (mach_header *)(puVar17 + 1);
      *puVar17 = 0xffffffff;
    }
    else {
      pmVar11 = (mach_header *)&param_1[0x1b].cpusubtype;
      FUN_1001c0898(pmVar11,&mStack_1a0.ncmds);
    }
    *(mach_header **)&param_1[0x1b].ncmds = pmVar11;
  }
  bStack_261 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x180))();
  if ((int)pmVar11 == 0) {
    *(byte *)((long)&param_1[0x1b].cputype + 3) = bStack_261;
    param_1[0x2f].flags =
         param_1[0x2f].flags & 0xffffffc0 | param_1[0x2f].flags & 0x1f | (bStack_261 & 1) << 5;
    pmVar11 = param_1;
    FUN_1000cbaf4();
    pmVar10 = pmRam0000000100cae440;
    if ((((ulong)pmVar11 & 1) == 0) &&
       (pmVar11 = pmRam0000000100cae440, _os_log_type_enabled(pmRam0000000100cae440,0x10),
       (int)pmVar11 != 0)) {
      FUN_1008da830();
      pmVar11 = pmVar10;
    }
  }
  iStack_268 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 400))();
  if ((int)pmVar11 == 0) {
    *(bool *)((long)&param_1[0x1c].ncmds + 2) = iStack_268 != 0;
  }
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x168))();
  dStack_26c = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x170))();
  if ((int)pmVar11 == 0) {
    param_1[0xf].cpusubtype = dStack_26c;
  }
  uStack_26d = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x4e0))();
  *(undefined1 *)&param_1[0x23].flags = uStack_26d;
  cStack_26e = '\0';
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x4e0))();
  cVar8 = cStack_26e;
  *(char *)&param_1[0x24].cpusubtype = cStack_26e;
  pmVar10 = pmRam0000000100cae440;
  if ((char)param_1[0x23].flags == '\x01') {
    pmVar11 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar11 != 0) {
      pcVar4 = "is";
      if (cVar8 == '\0') {
        pcVar4 = "is not";
      }
      mStack_1a0.ncmds = (dword)_UNK_100930b00;
      mStack_1a0.sizeofcmds._0_2_ = (short)pcVar4;
      mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pcVar4 >> 0x10);
      mStack_1a0.flags._0_2_ = (undefined2)((ulong)pcVar4 >> 0x20);
      mStack_1a0.flags._2_2_ = 0;
      pmVar11 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar10,0,
                    "Wireless Splitter this is a guest device that %s in contacts",&mStack_1a0.ncmds
                    ,0xc);
    }
    mStack_1a0.ncmds = 0;
    FUN_1000c6a1c();
    (**(code **)(*(long *)pmVar11 + 0x4f8))();
    if ((int)pmVar11 == 0) {
      param_1[0x23].reserved = mStack_1a0.ncmds;
    }
  }
  uStack_26f = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x510))();
  *(undefined1 *)((long)&param_1[0x24].ncmds + 1) = uStack_26f;
  uStack_270 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x520))();
  *(undefined1 *)&param_1[0x24].sizeofcmds = uStack_270;
  bStack_271 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x530))();
  if ((int)pmVar11 == 0) {
    *(byte *)((long)&param_1[0x24].sizeofcmds + 1) = bStack_271;
  }
  pmVar16 = pmRam0000000100cae440;
  pmVar10 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar10 != 0) {
    mStack_1a0.ncmds = (dword)_UNK_1009304c8;
    mStack_1a0.sizeofcmds._0_2_ = (short)pmVar11;
    mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pmVar11 >> 0x10);
    mStack_1a0.flags._0_2_ = 0x400;
    mStack_1a0.flags._2_2_ = (ushort)bStack_271;
    mStack_1a0.reserved._0_2_ = 0;
    pmVar10 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"Read Temporary Managed Pairing Mode result %d, value = %d",
                  &mStack_1a0.ncmds,0xe);
  }
  uStack_272 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x540))();
  *(undefined1 *)((long)&param_1[0x24].sizeofcmds + 2) = uStack_272;
  dStack_278 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x340))();
  if ((int)pmVar10 == 0) {
    param_1[0x1c].sizeofcmds = dStack_278;
  }
  dStack_27c = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x350))();
  if ((int)pmVar10 == 0) {
    param_1[0x1c].flags = dStack_27c;
  }
  pmVar16 = pmRam0000000100cae440;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar11 != 0) {
    mStack_1a0.ncmds = (dword)_UNK_1009304c8;
    mStack_1a0.sizeofcmds._0_2_ = (short)pmVar10;
    mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pmVar10 >> 0x10);
    mStack_1a0.flags._0_2_ = 0x400;
    mStack_1a0.flags._2_2_ = (ushort)dStack_27c;
    mStack_1a0.reserved._0_2_ = (undefined2)(dStack_27c >> 0x10);
    pmVar11 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"Read doubleTapAction result %d, value = %d",
                  &mStack_1a0.ncmds,0xe);
  }
  bStack_27d = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x360))();
  if ((int)pmVar11 == 0) {
    *(byte *)&param_1[0x1c].reserved = bStack_27d;
  }
  pmVar16 = pmRam0000000100cae440;
  pmVar10 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar10 != 0) {
    mStack_1a0.ncmds = (dword)_UNK_1009304c8;
    mStack_1a0.sizeofcmds._0_2_ = (short)pmVar11;
    mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)pmVar11 >> 0x10);
    mStack_1a0.flags._0_2_ = 0x400;
    mStack_1a0.flags._2_2_ = (ushort)bStack_27d;
    mStack_1a0.reserved._0_2_ = 0;
    pmVar10 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"Read InEarDetectionEnabled result %d, value = %d",
                  &mStack_1a0.ncmds,0xe);
  }
  dStack_284 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x370))();
  if ((int)pmVar10 == 0) {
    param_1[0x1d].magic = dStack_284;
  }
  pmVar16 = pmRam0000000100cae440;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar11 != 0) {
    FUN_10010aa84(&uStack_210,param_1);
    puVar17 = (undefined4 *)CONCAT44(uStack_20c,uStack_210);
    if (-1 < uStack_200) {
      puVar17 = &uStack_210;
    }
    mStack_1a0.ncmds = (dword)_UNK_100930fa8;
    mStack_1a0.sizeofcmds._0_2_ = (short)puVar17;
    mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)puVar17 >> 0x10);
    mStack_1a0.flags._0_2_ = (undefined2)((ulong)puVar17 >> 0x20);
    mStack_1a0.flags._2_2_ = (ushort)((ulong)puVar17 >> 0x30);
    mStack_1a0.reserved._0_2_ = 0x400;
    mStack_1a0.reserved._2_2_ = SUB82(pmVar10,0);
    uStack_180 = (undefined2)((ulong)pmVar10 >> 0x10);
    uStack_17e = 0;
    uStack_17d = 4;
    uStack_17c = (undefined1)dStack_284;
    uStack_17b = (undefined1)(dStack_284 >> 8);
    uStack_17a = (undefined1)(dStack_284 >> 0x10);
    cStack_179 = (char)(dStack_284 >> 0x18);
    pmVar11 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"[%{public}s] Read smart route result %d, mode = %d",
                  &mStack_1a0.ncmds,0x18);
    if (uStack_200._7_1_ < '\0') {
      pmVar11 = (mach_header *)CONCAT44(uStack_20c,uStack_210);
      __ZdlPv();
    }
  }
  dStack_288 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x398))();
  if ((int)pmVar11 == 0) {
    param_1[0x1d].cpusubtype = dStack_288;
  }
  uStack_210 = 0;
  uStack_20c = 0;
  uStack_208 = 0;
  uStack_204 = 0;
  uStack_200 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x3a8))();
  if ((int)pmVar11 == 0) {
    if (&param_1[0x2a].flags != &uStack_210) {
      FUN_1005ffbe0();
    }
    pmVar10 = pmRam0000000100cae440;
    pmVar11 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar11 != 0) {
      lVar27 = *(long *)&param_1[0x2a].flags;
      uVar23 = (*(long *)(param_1 + 0x2b) - lVar27 >> 3) * -0x5555555555555555;
      if (uVar23 < 4) {
LAB_1005e6628:
                    /* WARNING: Does not return */
        pcVar9 = (code *)SoftwareBreakpoint(1,0x1005e662c);
        (*pcVar9)();
      }
      plVar22 = (long *)(lVar27 + 0x48);
      if (*(char *)(lVar27 + 0x5f) < '\0') {
        plVar22 = (long *)*plVar22;
      }
      if (uVar23 < 0xb) goto LAB_1005e6628;
      plVar24 = (long *)(lVar27 + 0xf0);
      if (*(char *)(lVar27 + 0x107) < '\0') {
        plVar24 = (long *)*plVar24;
      }
      mStack_1a0.ncmds = (dword)_UNK_1009357e8;
      mStack_1a0.sizeofcmds._0_2_ = 0x6168;
      mStack_1a0.sizeofcmds._2_2_ = 0x6873;
      mStack_1a0.flags._0_2_ = 0;
      mStack_1a0.flags._2_2_ = 0;
      mStack_1a0.reserved._0_2_ = 0x821;
      mStack_1a0.reserved._2_2_ = SUB82(plVar22,0);
      uStack_180 = (undefined2)((ulong)plVar22 >> 0x10);
      uStack_17e = (undefined1)((ulong)plVar22 >> 0x20);
      uStack_17d = (undefined1)((ulong)plVar22 >> 0x28);
      uStack_17c = (undefined1)((ulong)plVar22 >> 0x30);
      uStack_17b = (undefined1)((ulong)plVar22 >> 0x38);
      uStack_17a = 0x22;
      cStack_179 = '\b';
      uStack_178 = SUB84(plVar24,0);
      uStack_174 = (undefined2)((ulong)plVar24 >> 0x20);
      uStack_172 = (undefined2)((ulong)plVar24 >> 0x30);
      pmVar11 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar10,0,
                    "AACPVersionInfo initialized: serial number %{private, mask.hash}s firmware version %{public}s"
                    ,&mStack_1a0.ncmds,0x20);
    }
  }
  uStack_260 = 0;
  uStack_25c = 0;
  uStack_258 = 0;
  uStack_254 = 0;
  uStack_250 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x3b8))();
  if ((int)pmVar11 == 0) {
    pmVar11 = (mach_header *)&param_1[0x2b].ncmds;
    __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSERKS5_(pmVar11,&uStack_260);
  }
  uStack_160 = 0;
  uStack_178 = 0;
  uStack_174 = 0;
  uStack_172 = 0;
  uStack_180 = 0;
  uStack_17e = 0;
  uStack_17d = 0;
  uStack_17c = 0;
  uStack_17b = 0;
  uStack_17a = 0;
  cStack_179 = '\0';
  uStack_168 = 0;
  uStack_166 = 0;
  cStack_161 = '\0';
  uStack_170 = 0;
  uStack_16e = 0;
  uStack_16a = 0;
  mStack_1a0.flags._0_2_ = 0;
  mStack_1a0.flags._2_2_ = 0;
  mStack_1a0.reserved._0_2_ = 0;
  mStack_1a0.reserved._2_2_ = 0;
  mStack_1a0.ncmds = 0;
  mStack_1a0.sizeofcmds._0_2_ = 0;
  mStack_1a0.sizeofcmds._2_2_ = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x3c8))();
  if ((int)pmVar11 == 0) {
    param_1[0x2c].ncmds = CONCAT22(mStack_1a0.flags._2_2_,(undefined2)mStack_1a0.flags);
    param_1[0x2c].sizeofcmds =
         (int)(CONCAT26(mStack_1a0.reserved._2_2_,
                        CONCAT24((undefined2)mStack_1a0.reserved,
                                 CONCAT22(mStack_1a0.flags._2_2_,(undefined2)mStack_1a0.flags))) >>
              0x20);
    param_1[0x2c].cpusubtype = mStack_1a0.ncmds;
    param_1[0x2c].filetype =
         (int)(CONCAT26(mStack_1a0.sizeofcmds._2_2_,
                        CONCAT24((short)mStack_1a0.sizeofcmds,mStack_1a0.ncmds)) >> 0x20);
    *(ulong *)&param_1[0x2c].reserved =
         CONCAT44(uStack_178,
                  CONCAT13(cStack_179,CONCAT12(uStack_17a,CONCAT11(uStack_17b,uStack_17c))));
    param_1[0x2c].sizeofcmds = CONCAT22(mStack_1a0.reserved._2_2_,(undefined2)mStack_1a0.reserved);
    param_1[0x2c].flags =
         (int)(CONCAT17(uStack_17d,
                        CONCAT16(uStack_17e,
                                 CONCAT24(uStack_180,
                                          CONCAT22(mStack_1a0.reserved._2_2_,
                                                   (undefined2)mStack_1a0.reserved)))) >> 0x20);
    pmVar11 = (mach_header *)&param_1[0x2d].cpusubtype;
    __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSERKS5_(pmVar11,&uStack_170);
  }
  dStack_28c = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x3d8))();
  if ((int)pmVar11 == 0) {
    param_1[0x1d].filetype = dStack_28c;
  }
  dStack_290 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 1000))();
  if ((int)pmVar11 == 0) {
    param_1[0x1d].sizeofcmds = dStack_290;
  }
  dStack_294 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x3f8))();
  if ((int)pmVar11 == 0) {
    param_1[0x1d].flags = dStack_294;
  }
  dStack_298 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x408))();
  if ((int)pmVar11 == 0) {
    param_1[0x1d].reserved = dStack_298;
  }
  dStack_29c = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x418))();
  if ((int)pmVar11 == 0) {
    param_1[0x1e].cputype = dStack_29c;
  }
  dStack_2a0 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x428))();
  if ((int)pmVar11 == 0) {
    param_1[0x1e].cpusubtype = dStack_2a0;
  }
  uStack_2a1 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x448))();
  if ((int)pmVar11 == 0) {
    *(undefined1 *)&param_1[0x1e].reserved = uStack_2a1;
  }
  dStack_2a8 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x458))();
  if ((int)pmVar11 == 0) {
    param_1[0x1f].magic = dStack_2a8;
  }
  uStack_2a9 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x488))();
  if ((int)pmVar11 == 0) {
    *(undefined1 *)&param_1[0x1f].cpusubtype = uStack_2a9;
  }
  uStack_2b8 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x478))();
  if ((int)pmVar11 == 0) {
    param_1[0x35].cpusubtype = (undefined4)uStack_2b8;
    param_1[0x35].filetype = uStack_2b8._4_4_;
  }
  dStack_2bc = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x468))();
  if ((int)pmVar11 == 0) {
    param_1[0x1f].cputype = dStack_2bc;
  }
  uStack_2bd = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x438))();
  if ((int)pmVar11 == 0) {
    *(undefined1 *)&param_1[0x1e].filetype = uStack_2bd;
  }
  dStack_2c4 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x498))();
  if ((int)pmVar11 == 0) {
    param_1[0x21].ncmds = dStack_2c4;
  }
  mStack_2f8.flags = 0;
  mStack_2f8.reserved = 0;
  uStack_2d8 = 0;
  uStack_2d0 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x4a8))();
  if (((int)pmVar11 == 0) &&
     (pmVar11 = (mach_header *)&param_1[0x22].cpusubtype,
     pmVar11 != (mach_header *)&mStack_2f8.flags)) {
    FUN_1005ffd8c();
  }
  mStack_2f8.magic = 0;
  mStack_2f8.cputype = 0;
  mStack_2f8.cpusubtype = 0;
  mStack_2f8.filetype = 0;
  mStack_2f8.ncmds = 0;
  mStack_2f8.sizeofcmds = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x4b8))();
  if (((int)pmVar11 == 0) && (pmVar11 = param_1 + 0x23, pmVar11 != &mStack_2f8)) {
    FUN_10047d5e0();
  }
  dStack_2fc = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x548))();
  if ((int)pmVar11 == 0) {
    param_1[0x11].magic = dStack_2fc;
  }
  dStack_300 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x558))();
  if ((int)pmVar11 == 0) {
    param_1[0x11].cputype = dStack_300;
  }
  dStack_304 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x568))();
  dVar26 = dStack_304;
  if ((int)pmVar11 != 0) {
    dVar26 = 0xbf800000;
  }
  param_1[0x29].cputype = dVar26;
  FUN_1000c6a1c();
  lStack_320 = 0;
  lStack_318 = 0;
  uStack_310 = 0;
  (**(code **)(*(long *)pmVar11 + 0x578))();
  if (lStack_320 != 0) {
    lStack_318 = lStack_320;
    __ZdlPv();
  }
  pdVar12 = &param_1[0x29].cpusubtype;
  FUN_10047d5e0(pdVar12,0,0,0);
  param_1[0xf].ncmds = 0;
  param_1[0xf].sizeofcmds = 0;
  param_1[0xf].flags = 0;
  param_1[0xf].reserved = 0;
  bStack_321 = 0xff;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pdVar12 + 0x588))();
  pmVar10 = pmRam0000000100cae440;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar11 != 0) {
    mStack_388.flags = (dword)_UNK_1009304c8;
    mStack_388.reserved = (dword)bStack_321;
    uStack_368 = 0x400;
    pmVar11 = &__mh_execute_header;
    iStack_366 = (int)pdVar12;
    __os_log_impl(0x100000000,pmVar10,0,"readEncryptionKeySize: %d, result: %d",
                  (long)&mStack_388 + 0x18,0xe);
  }
  if ((int)pdVar12 == 0) {
    *(byte *)((long)&param_1[0x24].reserved + 1) = bStack_321;
  }
  bStack_322 = 0xff;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x598))();
  pmVar16 = pmRam0000000100cae440;
  pmVar10 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar10 != 0) {
    mStack_388.flags = (dword)_UNK_1009304c8;
    mStack_388.reserved = (dword)bStack_322;
    uStack_368 = 0x400;
    pmVar10 = &__mh_execute_header;
    iStack_366 = (int)pmVar11;
    __os_log_impl(0x100000000,pmVar16,0,"readEncryptionMode: %d, result: %d",
                  (long)&mStack_388 + 0x18,0xe);
  }
  if ((int)pmVar11 == 0) {
    *(byte *)((long)&param_1[0x24].reserved + 2) = bStack_322;
  }
  dStack_328 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x628))();
  pmVar16 = pmRam0000000100cae440;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar11 != 0) {
    mStack_388.flags = (dword)_UNK_1009304c8;
    mStack_388.reserved = dStack_328;
    uStack_368 = 0x400;
    pmVar11 = &__mh_execute_header;
    iStack_366 = (int)pmVar10;
    __os_log_impl(0x100000000,pmVar16,0,"readRSSIDuringPairing: %d, result: %d",
                  (long)&mStack_388 + 0x18,0xe);
  }
  if (((int)pmVar10 == 0) && (dStack_328 != 0)) {
    param_1[0x25].cpusubtype = dStack_328;
  }
  dStack_32c = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x5a8))();
  if ((int)pmVar11 == 0) {
    param_1[0x25].magic = dStack_32c;
  }
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar11 + 0x1b0))();
  if ((int)pmVar11 != 0) {
    pmVar16 = param_1;
    FUN_1005e6ce0();
    pmVar10 = pmRam0000000100cae440;
    pmVar11 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar11 != 0) {
      mStack_388.flags = (dword)_UNK_100930510;
      mStack_388.reserved = (dword)pmVar16;
      pmVar11 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar10,0,"Number of services %d supporting PSM/RFCOMM",
                    (long)&mStack_388 + 0x18,8);
    }
  }
  dStack_330 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x5b8))();
  pmVar16 = pmRam0000000100cae440;
  pmVar10 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar10 != 0) {
    mStack_388.reserved = param_1[0x30].reserved;
    mStack_388.flags = (dword)_UNK_100930510;
    pmVar10 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"Read hidDeviceBehavior : %d",(long)&mStack_388 + 0x18,8);
  }
  pmVar16 = pmRam0000000100cae440;
  if ((int)pmVar11 == 0) {
    param_1[0x30].reserved = dStack_330;
  }
  else {
    pmVar10 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar10 != 0) {
      mStack_388.reserved = param_1[0x30].reserved;
      mStack_388.flags = (dword)_UNK_100930510;
      pmVar10 = &__mh_execute_header;
      __os_log_impl(0x100000000,pmVar16,0,"Failed to read hidDeviceBehavior : %d",
                    (long)&mStack_388 + 0x18,8);
    }
  }
  bStack_331 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x5d8))();
  pmVar16 = pmRam0000000100cae440;
  pmVar11 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  if ((int)pmVar11 != 0) {
    mStack_388.flags = (dword)_UNK_100930510;
    mStack_388.reserved = (dword)bStack_331;
    pmVar11 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"Read userSelectedDeviceType : %d",(long)&mStack_388 + 0x18,
                  8);
  }
  pmVar16 = pmRam0000000100cae440;
  if ((dword)pmVar10 == 0) {
    dVar26 = (dword)bStack_331;
  }
  else {
    pmVar11 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    dVar26 = 0;
    if ((int)pmVar11 != 0) {
      mStack_388.flags = (dword)_UNK_100930510;
      pmVar11 = &__mh_execute_header;
      mStack_388.reserved = (dword)pmVar10;
      __os_log_impl(0x100000000,pmVar16,0,"Failed to read userSelectedDeviceType due to error: %d",
                    (long)&mStack_388 + 0x18,8);
      dVar26 = 0;
    }
  }
  param_1[0x33].sizeofcmds = dVar26;
  dStack_338 = 0;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar11 + 0x5f8))();
  pmVar16 = pmRam0000000100cae440;
  pmVar10 = pmRam0000000100cae440;
  _os_log_type_enabled(pmRam0000000100cae440,0);
  dVar26 = (dword)pmVar11;
  if ((int)pmVar10 == 0) {
LAB_1005e6360:
    dVar21 = dStack_338;
    if (dVar26 == 0) goto LAB_1005e63e0;
LAB_1005e6364:
    pmVar11 = pmRam0000000100cae440;
    pmVar10 = pmRam0000000100cae440;
    _os_log_type_enabled(pmRam0000000100cae440,0);
    if ((int)pmVar10 != 0) {
      mStack_388.flags = (dword)_UNK_100930510;
      mStack_388.reserved = dVar26;
      __os_log_impl(0x100000000,pmVar11,0,"Failed to read CarPlayType due to error: %d",
                    (long)&mStack_388 + 0x18,8);
    }
    pmVar10 = param_1;
    FUN_1000731bc(param_1,0x40000);
    if ((int)pmVar10 == 4) {
      dVar21 = 1;
      goto LAB_1005e63e0;
    }
    param_1[0x36].filetype = 0;
  }
  else {
    FUN_1005e7a0c((long)&mStack_388 + 0x18);
    cVar8 = cStack_359;
    lVar27 = CONCAT44(mStack_388.reserved,mStack_388.flags);
    FUN_10010aa84(&mStack_388,param_1);
    lStack_34c = lVar27;
    if (-1 < cVar8) {
      lStack_34c = (long)&mStack_388 + 0x18;
    }
    pmStack_342 = (mach_header *)mStack_388._0_8_;
    if (-1 < mStack_388.sizeofcmds._3_1_) {
      pmStack_342 = &mStack_388;
    }
    uStack_350 = (undefined4)_UNK_100930b18;
    uStack_344 = 0x822;
    pmVar10 = &__mh_execute_header;
    __os_log_impl(0x100000000,pmVar16,0,"Read CarPlayType : %s for %{public}s",&uStack_350,0x16);
    if (mStack_388.sizeofcmds._3_1_ < '\0') {
      __ZdlPv();
      pmVar10 = (mach_header *)mStack_388._0_8_;
    }
    if (-1 < cStack_359) goto LAB_1005e6360;
    pmVar10 = (mach_header *)CONCAT44(mStack_388.reserved,mStack_388.flags);
    __ZdlPv();
    dVar21 = dStack_338;
    if (dVar26 != 0) goto LAB_1005e6364;
LAB_1005e63e0:
    param_1[0x36].filetype = dVar21;
  }
  mStack_388.flags = mStack_388.flags & 0xffffff00;
  FUN_1000c6a1c();
  (**(code **)(*(long *)pmVar10 + 0x608))();
  uVar2 = (undefined1)mStack_388.flags;
  if ((int)pmVar10 != 0) {
    uVar2 = 0;
  }
  *(undefined1 *)&param_1[0x36].ncmds = uVar2;
  FUN_1000071b8();
  (**(code **)(*(long *)pmVar10 + 0x388))();
  if ((int)pmVar10 != 0) {
    FUN_1000c6a1c();
    (**(code **)(*(long *)pmVar10 + 0x5c8))();
  }
  if (mStack_2f8._0_8_ != 0) {
    mStack_2f8.cpusubtype = mStack_2f8.magic;
    mStack_2f8.filetype = mStack_2f8.cputype;
    __ZdlPv();
  }
  if (mStack_2f8._24_8_ != 0) {
    uStack_2d8._0_4_ = mStack_2f8.flags;
    uStack_2d8._4_4_ = mStack_2f8.reserved;
    __ZdlPv();
  }
  if ((long)uStack_160 < 0) {
    __ZdlPv(CONCAT26(uStack_16a,CONCAT42(uStack_16e,uStack_170)));
  }
  if (uStack_250 < 0) {
    __ZdlPv(CONCAT44(uStack_25c,uStack_260));
  }
  mStack_1a0.ncmds = (dword)&uStack_210;
  mStack_1a0.sizeofcmds._0_2_ = (short)((ulong)&uStack_210 >> 0x20);
  mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)&uStack_210 >> 0x30);
  FUN_1001ec4dc(&mStack_1a0.ncmds);
  mStack_1a0.ncmds = (dword)&ppppppuStack_1e8;
  mStack_1a0.sizeofcmds._0_2_ = (short)((ulong)&ppppppuStack_1e8 >> 0x20);
  mStack_1a0.sizeofcmds._2_2_ = (undefined2)((ulong)&ppppppuStack_1e8 >> 0x30);
  FUN_10020eda4(&mStack_1a0.ncmds,ppppppuStack_1e8);
  if ((long)auStack_1d8._16_8_ < 0) {
    __ZdlPv(auStack_1d8._0_8_);
  }
  if (lStack_1b0 < 0) {
    __ZdlPv(CONCAT44(dStack_1bc,auStack_1d8._24_4_));
  }
LAB_1005e6504:
  FUN_100006ec0(&mStack_1a0);
  if (*(long *)PTR____stack_chk_guard_100bfc980 == lStack_78) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  ___stack_chk_fail();
}


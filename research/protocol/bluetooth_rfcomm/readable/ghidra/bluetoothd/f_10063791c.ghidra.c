/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10063791c
 * original code SHA256: 05602da28acbdbdcef06fb40314d709ea5e1ed2dd0a45c90dfa1d38281ea3093
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_10063791c(undefined8 param_1,long *param_2)

{
  undefined8 *******pppppppuVar1;
  undefined2 uVar2;
  ushort uVar3;
  undefined8 uVar4;
  ulong uVar5;
  ulong uVar6;
  long *plVar7;
  undefined8 uVar8;
  char *pcVar9;
  long **pplVar10;
  long *plVar11;
  byte bVar12;
  long *plVar13;
  long *aplStack_138 [2];
  char cStack_121;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined2 uStack_114;
  undefined4 uStack_112;
  char cStack_109;
  byte bStack_106;
  undefined1 uStack_105;
  undefined4 uStack_104;
  undefined8 *******pppppppuStack_100;
  undefined8 uStack_f8;
  uint5 uStack_f0;
  undefined3 uStack_eb;
  char cStack_e9;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  long lStack_d8;
  ulong uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  long lStack_b8;
  ulong uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined7 uStack_98;
  undefined4 uStack_91;
  undefined1 uStack_8d;
  undefined4 uStack_8c;
  undefined1 uStack_88;
  undefined5 uStack_87;
  undefined2 uStack_82;
  undefined1 uStack_80;
  undefined5 uStack_7f;
  undefined2 uStack_7a;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined1 auStack_60 [8];
  long lStack_58;
  
  uVar4 = uRam0000000100cae440;
  lStack_58 = *(long *)PTR____stack_chk_guard_100bfc980;
  plVar13 = (long *)param_2[1];
  if (plVar13 == (long *)0x0) {
    uVar8 = uRam0000000100cae440;
    _os_log_type_enabled(uRam0000000100cae440,0x11);
    if ((int)uVar8 != 0) {
      FUN_1008deb84(uVar4);
    }
    goto LAB_100637f50;
  }
  uVar8 = uRam0000000100cae440;
  _os_log_type_enabled(uRam0000000100cae440,0);
  if ((int)uVar8 != 0) {
    FUN_10010aa84(&pppppppuStack_100,plVar13);
    pppppppuVar1 = pppppppuStack_100;
    if (-1 < _uStack_f0) {
      pppppppuVar1 = &pppppppuStack_100;
    }
    uStack_112 = (undefined4)param_2[3];
    uStack_120 = (undefined4)_UNK_1009316b0;
    uStack_11c = SUB84(pppppppuVar1,0);
    uStack_118 = (undefined4)((ulong)pppppppuVar1 >> 0x20);
    uStack_114 = 0x400;
    __os_log_impl(0x100000000,uVar4,0,"SDP query has completed for device %{public}s with status %d"
                  ,&uStack_120,0x12);
    if (_uStack_f0 < 0) {
      __ZdlPv(pppppppuStack_100);
    }
  }
  uStack_104 = 0;
  FUN_1005e7cb8(plVar13,&uStack_104);
  if ((int)param_2[3] == 0) {
    FUN_1005fca64(plVar13,1);
    plVar7 = plVar13;
    FUN_1000cbaf4();
    uVar4 = uRam0000000100cae440;
    if ((int)plVar7 != 0) {
      uVar8 = uRam0000000100cae440;
      _os_log_type_enabled(uRam0000000100cae440,0);
      if ((int)uVar8 != 0) {
        FUN_10010aa84(&pppppppuStack_100,plVar13);
        pppppppuVar1 = pppppppuStack_100;
        if (-1 < _uStack_f0) {
          pppppppuVar1 = &pppppppuStack_100;
        }
        uStack_120 = (undefined4)_UNK_100930b20;
        uStack_11c = SUB84(pppppppuVar1,0);
        uStack_118 = (undefined4)((ulong)pppppppuVar1 >> 0x20);
        __os_log_impl(0x100000000,uVar4,0,
                      "Identification - SDP query complete. Checking if we need to generate hash for device %{public}s"
                      ,&uStack_120,0xc);
        if (_uStack_f0 < 0) {
          __ZdlPv(pppppppuStack_100);
        }
      }
      FUN_1005e8af8(plVar13);
      FUN_1005f5618(plVar13);
    }
  }
  uStack_105 = 0;
  FUN_100061a60(&uStack_105);
  plVar7 = plVar13;
  FUN_1005f0f20();
  if ((int)plVar7 != 0) {
    plVar7 = plVar13;
    FUN_1005f0fb0();
    uVar4 = uRam0000000100cae440;
    uVar8 = uRam0000000100cae440;
    _os_log_type_enabled(uRam0000000100cae440,0);
    if ((int)uVar8 != 0) {
      FUN_10010aa84(&pppppppuStack_100,plVar13);
      pppppppuVar1 = pppppppuStack_100;
      if (-1 < _uStack_f0) {
        pppppppuVar1 = &pppppppuStack_100;
      }
      uStack_120 = (undefined4)_UNK_1009316b0;
      uStack_11c = SUB84(pppppppuVar1,0);
      uStack_118 = (undefined4)((ulong)pppppppuVar1 >> 0x20);
      uStack_114 = 0x400;
      uStack_112 = SUB84(plVar7,0);
      __os_log_impl(0x100000000,uVar4,0,
                    "We have a stalled incoming SDP request from device %{public}s with cid: %d. Responding to stalled request"
                    ,&uStack_120,0x12);
      if (cStack_e9 < '\0') {
        __ZdlPv(pppppppuStack_100);
      }
    }
    FUN_1003cd684((int)param_2[3] == 0,plVar7);
    FUN_1005f0ed8(plVar13,0);
    FUN_1005f0f68(plVar13,0);
  }
  plVar7 = plVar13 + 0x10;
  FUN_10031c0b8(plVar7,uStack_104);
  uVar4 = uRam0000000100cae440;
  if (((int)plVar7 != 0) &&
     (uVar8 = uRam0000000100cae440, _os_log_type_enabled(uRam0000000100cae440,0), (int)uVar8 != 0))
  {
    pppppppuStack_100 = (undefined8 *******)CONCAT44((int)plVar7,(int)_UNK_100930510);
    __os_log_impl(0x100000000,uVar4,0,"Set Remote Device class failed with %{bluetooth:OI_STATUS}u",
                  &pppppppuStack_100,8);
  }
  if (lRam0000000100c1b4b8 != -1) {
    FUN_1008deb50();
  }
  FUN_100658324(uRam0000000100c1b4b0,plVar13 + 0x10);
  FUN_10006433c(&uStack_105);
  bStack_106 = 0;
  auStack_60 = (undefined1  [8])0x0;
  uStack_78 = 0;
  uStack_80 = 0;
  uStack_7f = 0;
  uStack_7a = 0;
  uStack_68 = 0;
  uStack_70 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  uStack_88 = 0;
  uStack_87 = 0;
  uStack_82 = 0;
  uStack_91 = 0;
  uStack_8d = 0;
  uStack_8c = 0;
  uStack_a8 = 0;
  uStack_b0 = 0;
  uStack_c8 = 0;
  uStack_d0 = 0;
  lStack_b8 = 0;
  uStack_c0 = 0;
  uStack_e8 = 0;
  _uStack_f0 = 0;
  lStack_d8 = 0;
  uStack_e0 = 0;
  uStack_f8 = 0;
  pppppppuStack_100 = (undefined8 *******)0x0;
  FUN_100101334((ulong)&pppppppuStack_100 | 1);
  uVar5 = uStack_d0;
  uVar4 = _uStack_f0;
  uStack_f0._0_3_ = (uint3)(ushort)uStack_f0;
  uVar8 = _uStack_f0;
  uStack_eb = SUB83(uVar4,5);
  uStack_f0 = (uint5)(uint)uVar8;
  uStack_d0._0_3_ = (uint3)(ushort)uStack_d0;
  uVar6 = uStack_d0;
  uStack_d0._5_3_ = SUB83(uVar5,5);
  uStack_d0._0_5_ = (uint5)(uint)uVar6;
  uStack_8c = 0;
  uStack_e0 = 0;
  lStack_d8 = 0;
  uStack_e8 = 0;
  uStack_d0 = uStack_d0 & 0xffffffffffffff00;
  uStack_c0 = 0;
  lStack_b8 = 0;
  uStack_c8 = 0;
  uStack_b0 = uStack_b0 & 0xffffffffffffff00;
  uStack_a0 = 0;
  uStack_98 = 0;
  uStack_a8 = 0;
  uStack_91 = 0;
  uStack_88 = 1;
  uStack_7f = 0;
  uStack_87 = 0;
  uStack_82 = 0;
  uStack_80 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_78 = 0;
  uVar2 = auStack_60._6_2_;
  uVar3 = auStack_60._0_2_;
  auStack_60._0_6_ = CONCAT42(0,uVar3 & 0xff00);
  auStack_60 = (undefined1  [8])CONCAT26(uVar2,auStack_60._0_6_);
  plVar7 = plVar13;
  FUN_1005e6bec(plVar13,&pppppppuStack_100);
  FUN_1000071f0();
  FUN_10008c49c();
  if (((uint)plVar7 & (uint)auStack_60[4]) == 1) {
    FUN_1000110f0();
    pcVar9 = (char *)&uStack_120;
    FUN_1001ec44c(pcVar9,0xc);
    pcVar9[8] = 'r';
    pcVar9[9] = 'i';
    pcVar9[10] = 'n';
    pcVar9[0xb] = 'g';
    *(undefined8 *)pcVar9 = s_SDPMirroring_100a68730._0_8_;
    pcVar9[0xc] = '\0';
    pplVar10 = aplStack_138;
    FUN_1001ec44c(pplVar10,0x13);
    builtin_strncpy((char *)((long)pplVar10 + 0xf),"ring",4);
    uVar4 = s_DisableSDPMirroring_100a6873d._0_8_;
    pplVar10[1] = (long *)s_DisableSDPMirroring_100a6873d._8_8_;
    *pplVar10 = (long *)uVar4;
    *(char *)((long)pplVar10 + 0x13) = '\0';
    (**(code **)(*plVar7 + 0x48))(plVar7,&uStack_120,aplStack_138,&bStack_106);
    plVar11 = plVar7;
    if (cStack_121 < '\0') {
      __ZdlPv();
      plVar11 = aplStack_138[0];
    }
    if (cStack_109 < '\0') {
      plVar11 = (long *)CONCAT44(uStack_11c,uStack_120);
      __ZdlPv();
    }
    if ((int)plVar7 != 0) {
      bVar12 = bStack_106 ^ 1;
LAB_100637e38:
      plVar11 = plVar13;
      FUN_1005f5508(plVar13,bVar12 & 1);
    }
  }
  else {
    FUN_1000110f0();
    pcVar9 = (char *)&uStack_120;
    FUN_1001ec44c(pcVar9,0xc);
    pcVar9[8] = 'r';
    pcVar9[9] = 'i';
    pcVar9[10] = 'n';
    pcVar9[0xb] = 'g';
    *(undefined8 *)pcVar9 = s_SDPMirroring_100a68730._0_8_;
    pcVar9[0xc] = '\0';
    pplVar10 = aplStack_138;
    FUN_1001ec44c(pplVar10,0x13);
    builtin_strncpy((char *)((long)pplVar10 + 0xf),"ring",4);
    uVar4 = s_DisableSDPMirroring_100a6873d._0_8_;
    pplVar10[1] = (long *)s_DisableSDPMirroring_100a6873d._8_8_;
    *pplVar10 = (long *)uVar4;
    *(char *)((long)pplVar10 + 0x13) = '\0';
    (**(code **)(*plVar7 + 0x48))(plVar7,&uStack_120,aplStack_138,&bStack_106);
    plVar11 = plVar7;
    if (cStack_121 < '\0') {
      __ZdlPv();
      plVar11 = aplStack_138[0];
    }
    if (cStack_109 < '\0') {
      plVar11 = (long *)CONCAT44(uStack_11c,uStack_120);
      __ZdlPv();
    }
    if ((bStack_106 & 1) == 0) {
      bVar12 = 0;
      goto LAB_100637e38;
    }
  }
  FUN_1000071b8();
  (**(code **)(*plVar11 + 0x1b0))();
  if ((int)plVar11 != 0) {
    FUN_1005e6ce0();
    uVar4 = uRam0000000100cae440;
    uVar8 = uRam0000000100cae440;
    _os_log_type_enabled(uRam0000000100cae440,0);
    if ((int)uVar8 != 0) {
      uStack_120 = (undefined4)_UNK_100930510;
      uStack_11c = SUB84(plVar13,0);
      __os_log_impl(0x100000000,uVar4,0,"Number of services %d found using PSM/RFCOMM",&uStack_120,8
                   );
    }
  }
  plVar13 = (long *)param_2[2];
  if (plVar13 != (long *)0x0) {
    (**(code **)(*plVar13 + 0x10))(plVar13,param_2[1],(int)param_2[3]);
  }
  (**(code **)(*param_2 + 8))(param_2);
  if ((char)uStack_91 < '\0') {
    __ZdlPv(uStack_a8);
  }
  if (lStack_b8 < 0) {
    __ZdlPv(uStack_c8);
  }
  if (lStack_d8 < 0) {
    __ZdlPv(uStack_e8);
  }
  FUN_100043ed4((ulong)&pppppppuStack_100 | 1);
  FUN_10006b538(&uStack_105);
LAB_100637f50:
  if (*(long *)PTR____stack_chk_guard_100bfc980 != lStack_58) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return;
}


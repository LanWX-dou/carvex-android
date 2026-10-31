/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100139490
 * original code SHA256: 9a85fbc7f6d8eb2345b8121ba00b5b75e867f0de499948285541d2fb771a583d
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong FUN_100139490(ulong param_1,long param_2,uint *param_3,int param_4)

{
  char *******pppppppcVar1;
  char cVar2;
  short sVar3;
  ushort uVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  undefined8 uVar8;
  char *pcVar9;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  char cStack_99;
  undefined4 uStack_90;
  undefined1 *puStack_8c;
  byte bStack_81;
  undefined8 uStack_80;
  undefined8 uStack_78;
  char *******pppppppcStack_68;
  char ******ppppppcStack_60;
  undefined8 uStack_58;
  
  if (*(int *)(param_1 + 0xc) != 0x800) {
    if (*(int *)(param_1 + 0xc) != -1) {
      return 0;
    }
    FUN_100101c34(&pppppppcStack_68,param_2);
    if (uStack_58._7_1_ < '\0') {
      __ZdlPv(pppppppcStack_68);
      if (ppppppcStack_60 != (char ******)0x0) {
        return 1;
      }
    }
    else if (uStack_58._7_1_ != '\0') {
      return 1;
    }
    *param_3 = *param_3 | 4;
    return 1;
  }
  lVar6 = param_2;
  FUN_1005ec154();
  if ((int)lVar6 == 0) {
    uVar7 = param_1;
    FUN_100148a38(param_1,param_2);
    if (((uVar7 & 1) == 0) && (*(char *)(param_2 + 0x391) != '\x01')) {
      return 0;
    }
    FUN_100148a38(param_1,param_2);
    uVar5 = uRam0000000100cae458;
    uVar8 = uRam0000000100cae458;
    _os_log_type_enabled(uRam0000000100cae458,0);
    if ((int)param_1 == 0) {
      if ((int)uVar8 == 0) goto LAB_10013980c;
      FUN_10010aa84(&pppppppcStack_68,param_2);
      pppppppcVar1 = pppppppcStack_68;
      if (-1 < uStack_58) {
        pppppppcVar1 = (char *******)&pppppppcStack_68;
      }
      uStack_b0 = (undefined4)_UNK_100930b20;
      uStack_ac = SUB84(pppppppcVar1,0);
      uStack_a8 = (undefined4)((ulong)pppppppcVar1 >> 0x20);
      pcVar9 = 
      "EIR previously matched for device %{public}s, requesting SDP for deadvertised service(s)";
    }
    else {
      if ((int)uVar8 == 0) goto LAB_10013980c;
      FUN_10010aa84(&pppppppcStack_68,param_2);
      pppppppcVar1 = pppppppcStack_68;
      if (-1 < uStack_58) {
        pppppppcVar1 = (char *******)&pppppppcStack_68;
      }
      uStack_b0 = (undefined4)_UNK_100930b20;
      uStack_ac = SUB84(pppppppcVar1,0);
      uStack_a8 = (undefined4)((ulong)pppppppcVar1 >> 0x20);
      pcVar9 = "EIR matched for device %{public}s, requesting SDP";
    }
    __os_log_impl(0x100000000,uVar5,0,pcVar9,&uStack_b0,0xc);
    if (uStack_58._7_1_ < '\0') {
      __ZdlPv(pppppppcStack_68);
    }
LAB_10013980c:
    *param_3 = *param_3 | 0x10;
    return 0;
  }
  uStack_78 = _UNK_100939eb8;
  uStack_80 = _UNK_100939eb0;
  bStack_81 = 0;
  pppppppcStack_68 = (char *******)0x0;
  ppppppcStack_60 = (char ******)0x0;
  uStack_58 = 0;
  lVar6 = param_2;
  FUN_1005ebdf0(param_2,&uStack_80,0xf000,&pppppppcStack_68);
  uVar5 = uRam0000000100cae458;
  if (((int)lVar6 == 0) || ((long)ppppppcStack_60 - (long)pppppppcStack_68 != 0x10)) {
LAB_100139580:
    uVar5 = uRam0000000100cae458;
    uVar8 = uRam0000000100cae458;
    _os_log_type_enabled(uRam0000000100cae458,1);
    if ((int)uVar8 != 0) {
      FUN_10010aa84(&uStack_b0,param_2);
      puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
      if (-1 < cStack_99) {
        puStack_8c = (undefined1 *)&uStack_b0;
      }
      uStack_90 = (undefined4)_UNK_100930b20;
      __os_log_impl(0x100000000,uVar5,1,"Device %{public}s does not support SDP dirty byte caching",
                    &uStack_90,0xc);
      if (cStack_99 < '\0') {
        __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
      }
    }
    lVar6 = param_2;
    FUN_1005fb8c8(param_2,&bStack_81);
    uVar5 = uRam0000000100cae458;
    if ((int)lVar6 == 0) {
      uVar8 = uRam0000000100cae458;
      _os_log_type_enabled(uRam0000000100cae458,1);
      if ((int)uVar8 != 0) {
        FUN_10010aa84(&uStack_b0,param_2);
        puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
        if (-1 < cStack_99) {
          puStack_8c = (undefined1 *)&uStack_b0;
        }
        uStack_90 = (undefined4)_UNK_100930b20;
        pcVar9 = "We have SDP but not EIR for device %{public}s";
LAB_10013986c:
        __os_log_impl(0x100000000,uVar5,1,pcVar9,&uStack_90,0xc);
        if (cStack_99 < '\0') {
          __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
        }
      }
    }
    else {
      if (param_4 != 0) {
        uVar8 = uRam0000000100cae458;
        _os_log_type_enabled(uRam0000000100cae458,0);
        if ((int)uVar8 != 0) {
          FUN_10010aa84(&uStack_b0,param_2);
          puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
          if (-1 < cStack_99) {
            puStack_8c = (undefined1 *)&uStack_b0;
          }
          uStack_90 = (undefined4)_UNK_100930b20;
          __os_log_impl(0x100000000,uVar5,0,
                        "EIR is newer than SDP for device %{public}s, re-requesting SDP",&uStack_90,
                        0xc);
          if (cStack_99 < '\0') {
            __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
          }
        }
        FUN_1005e6928(param_2);
        goto LAB_100139694;
      }
      uVar8 = uRam0000000100cae458;
      _os_log_type_enabled(uRam0000000100cae458,1);
      if ((int)uVar8 != 0) {
        FUN_10010aa84(&uStack_b0,param_2);
        puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
        if (-1 < cStack_99) {
          puStack_8c = (undefined1 *)&uStack_b0;
        }
        uStack_90 = (undefined4)_UNK_100930b20;
        pcVar9 = "Both EIR and SDP are up-to-date for device %{public}s";
        goto LAB_10013986c;
      }
    }
    FUN_10014102c(param_1,param_2);
  }
  else {
    cVar2 = *(char *)pppppppcStack_68;
    sVar3 = *(short *)((long)pppppppcStack_68 + 2);
    if (cVar2 != '\x01' || sVar3 != 1) {
      uVar8 = uRam0000000100cae458;
      _os_log_type_enabled(uRam0000000100cae458,0x10);
      if ((int)uVar8 != 0) {
        FUN_1008e2404(cVar2,sVar3,uVar5);
      }
      goto LAB_100139580;
    }
    uVar4 = *(ushort *)(pppppppcStack_68 + 1);
    uVar8 = uRam0000000100cae458;
    _os_log_type_enabled(uRam0000000100cae458,1);
    if ((int)uVar8 != 0) {
      FUN_10010aa84(&uStack_b0,param_2);
      puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
      if (-1 < cStack_99) {
        puStack_8c = (undefined1 *)&uStack_b0;
      }
      uStack_90 = (undefined4)_UNK_100930b20;
      __os_log_impl(0x100000000,uVar5,1,"Device %{public}s supports SDP dirty byte caching",
                    &uStack_90,0xc);
      if (cStack_99 < '\0') {
        __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
      }
    }
    lVar6 = param_2;
    FUN_1005fb8c8(param_2,&bStack_81);
    uVar5 = uRam0000000100cae458;
    if ((int)lVar6 == 0) {
      uVar8 = uRam0000000100cae458;
      _os_log_type_enabled(uRam0000000100cae458,1);
      if ((int)uVar8 != 0) {
        FUN_10010aa84(&uStack_b0,param_2);
        puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
        if (-1 < cStack_99) {
          puStack_8c = (undefined1 *)&uStack_b0;
        }
        uStack_90 = (undefined4)_UNK_100930b20;
        pcVar9 = "We have SDP but not EIR for device %{public}s";
LAB_100139a20:
        __os_log_impl(0x100000000,uVar5,1,pcVar9,&uStack_90,0xc);
        if (cStack_99 < '\0') {
          __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
        }
      }
LAB_100139b38:
      FUN_10014102c(param_1,param_2);
      goto LAB_1001398a0;
    }
    if (uVar4 == bStack_81) {
      uVar8 = uRam0000000100cae458;
      _os_log_type_enabled(uRam0000000100cae458,1);
      if ((int)uVar8 != 0) {
        FUN_10010aa84(&uStack_b0,param_2);
        puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
        if (-1 < cStack_99) {
          puStack_8c = (undefined1 *)&uStack_b0;
        }
        uStack_90 = (undefined4)_UNK_100930b20;
        pcVar9 = "Both EIR and SDP are up-to-date for device %{public}s";
        goto LAB_100139a20;
      }
      goto LAB_100139b38;
    }
    if (param_4 == 0) {
      uVar8 = uRam0000000100cae458;
      _os_log_type_enabled(uRam0000000100cae458,1);
      if ((int)uVar8 != 0) {
        FUN_10010aa84(&uStack_b0,param_2);
        puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
        if (-1 < cStack_99) {
          puStack_8c = (undefined1 *)&uStack_b0;
        }
        uStack_90 = (undefined4)_UNK_100930b20;
        __os_log_impl(0x100000000,uVar5,1,
                      "SDP is newer than EIR for device %{public}s, clearing EIR",&uStack_90,0xc);
        if (cStack_99 < '\0') {
          __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
        }
      }
      FUN_1005fae44(param_2);
      goto LAB_100139b38;
    }
    uVar8 = uRam0000000100cae458;
    _os_log_type_enabled(uRam0000000100cae458,0);
    if ((int)uVar8 != 0) {
      FUN_10010aa84(&uStack_b0,param_2);
      puStack_8c = (undefined1 *)CONCAT44(uStack_ac,uStack_b0);
      if (-1 < cStack_99) {
        puStack_8c = (undefined1 *)&uStack_b0;
      }
      uStack_90 = (undefined4)_UNK_100930b20;
      __os_log_impl(0x100000000,uVar5,0,
                    "EIR is newer than SDP for device %{public}s, re-requesting SDP",&uStack_90,0xc)
      ;
      if (cStack_99 < '\0') {
        __ZdlPv(CONCAT44(uStack_ac,uStack_b0));
      }
    }
    FUN_1005e6928(param_2);
LAB_100139694:
    param_1 = 0;
    *param_3 = *param_3 | 0x10;
  }
LAB_1001398a0:
  if (pppppppcStack_68 != (char *******)0x0) {
    ppppppcStack_60 = (char ******)pppppppcStack_68;
    __ZdlPv();
  }
  return param_1;
}


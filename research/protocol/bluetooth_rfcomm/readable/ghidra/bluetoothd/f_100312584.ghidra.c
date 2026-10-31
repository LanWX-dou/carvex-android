/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100312584
 * original code SHA256: f8a051a219e74d627530feac9d7d75c08e040edc23e9142c8f880e3abbc9746c
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

code * FUN_100312584(long param_1,undefined8 param_2,code *param_3,code *param_4)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  code *pcVar6;
  undefined8 uVar7;
  char *pcVar8;
  undefined4 uStack_50;
  char *pcStack_4c;
  
  lRam0000000100cadae8 = 0;
  lVar2 = param_1;
  FUN_1003d83e4();
  iVar1 = (int)lVar2;
  FUN_1003d7a04();
  if (param_3 != (code *)0x0) {
    uVar3 = 0x5c;
    FUN_10000e9d4();
    uVar4 = uVar3;
    _os_log_type_enabled();
    iVar1 = 0;
    if ((int)uVar4 != 0) {
      uStack_50 = (undefined4)_UNK_100930b20;
      pcStack_4c = "Invoking customization callback\n";
      iVar1 = 0;
      __os_log_impl(0x100000000,uVar3,0,"%{public}s",&uStack_50,0xc);
    }
    (*param_3)();
  }
  FUN_1003d7c70();
  if (iVar1 != 0) {
    uVar3 = 0x5c;
    FUN_10000e9d4();
    uVar4 = uVar3;
    _os_log_type_enabled();
    if ((int)uVar4 != 0) {
      uStack_50 = (undefined4)_UNK_100930b20;
      pcStack_4c = "Support code initialization failed\n";
      __os_log_impl(0x100000000,uVar3,0,"%{public}s",&uStack_50,0xc);
    }
  }
  uVar4 = 0x30;
  FUN_1003d7a1c();
  FUN_100299a8c();
  if ((int)uVar4 != 0) {
    uVar7 = 0x5c;
    FUN_10000e9d4();
    uVar3 = uVar7;
    _os_log_type_enabled();
    if ((int)uVar3 != 0) {
      uStack_50 = (undefined4)_UNK_100930b20;
      pcStack_4c = "Memory Manager initialization failed\n";
      __os_log_impl(0x100000000,uVar7,0,"%{public}s",&uStack_50,0xc);
    }
                    /* WARNING: Subroutine does not return */
    FUN_1000e3dcc(uVar4);
  }
  FUN_1003d7f28(0,param_2);
  uVar5 = 0;
  FUN_1002a1bd8();
  if ((uVar5 & 1) == 0) {
    uVar3 = 0x5c;
    FUN_10000e9d4();
    uVar4 = uVar3;
    _os_log_type_enabled();
    if ((int)uVar4 != 0) {
      uStack_50 = (undefined4)_UNK_100930b20;
      pcStack_4c = "Sniffer initialization failed\n";
      __os_log_impl(0x100000000,uVar3,0,"%{public}s",&uStack_50,0xc);
    }
  }
  pcVar6 = (code *)0x0;
  FUN_10031622c();
  if ((int)pcVar6 == 0) {
    FUN_10030830c();
    if (param_1 == 0) {
      iVar1 = (int)pcVar6;
      while (iVar1 == 0x6d) {
        FUN_100010fe8();
        pcVar6 = (code *)0x64;
        FUN_100298e34();
        FUN_100003a30();
        FUN_1003083ac();
        iVar1 = (int)pcVar6;
      }
    }
    if ((int)pcVar6 != 0) {
      uVar3 = 0x5c;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        uStack_50 = (undefined4)_UNK_100930b20;
        pcStack_4c = "Transport layer initialization failed\n";
        __os_log_impl(0x100000000,uVar3,0,"%{public}s",&uStack_50,0xc);
      }
      if (param_4 != (code *)0x0) {
        pcVar8 = "Transport layer initialization failed";
LAB_100312874:
        (*param_4)(pcVar6,pcVar8);
        return pcVar6;
      }
      goto LAB_1003129e0;
    }
    pcVar6 = (code *)0x0;
    FUN_1003272cc();
    if ((int)pcVar6 == 0) {
      FUN_100377dec();
      if ((int)pcVar6 == 0) {
        if (param_1 == 0) {
          pcVar6 = (code *)0x0;
          FUN_100327678();
          while ((int)pcVar6 == 0x6d) {
            FUN_100010fe8();
            pcVar6 = (code *)0xa;
            FUN_100298e34();
            FUN_100003a30();
            FUN_100327730();
          }
          if ((int)pcVar6 == 0) {
            FUN_1003129f0(0);
            return pcVar6;
          }
        }
        else {
          pcVar6 = FUN_1003129f0;
          lRam0000000100cadae8 = param_1;
          FUN_100327678();
          if ((int)pcVar6 == 0) {
            return pcVar6;
          }
        }
        uVar3 = 0x5c;
        FUN_10000e9d4();
        uVar4 = uVar3;
        _os_log_type_enabled();
        if ((int)uVar4 != 0) {
          uStack_50 = (undefined4)_UNK_100930b20;
          pcStack_4c = "HCI initialization failed\n";
          __os_log_impl(0x100000000,uVar3,0,"%{public}s",&uStack_50,0xc);
        }
        pcVar8 = "HCI initialization failed";
        if (param_4 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
          FUN_1002989cc(pcVar6,"HCI initialization failed");
        }
        goto LAB_100312874;
      }
      uVar3 = 0x5c;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 == 0) goto LAB_1003129e0;
      uStack_50 = (undefined4)_UNK_100930b20;
      pcStack_4c = "BT VSC init failed\n";
    }
    else {
      uVar3 = 0x5c;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 == 0) goto LAB_1003129e0;
      uStack_50 = (undefined4)_UNK_100930b20;
      pcStack_4c = "OI_HCIAPI_Init_Vars failed\n";
    }
  }
  else {
    uVar3 = 0x5c;
    FUN_10000e9d4();
    uVar4 = uVar3;
    _os_log_type_enabled();
    if ((int)uVar4 == 0) goto LAB_1003129e0;
    uStack_50 = (undefined4)_UNK_100930b20;
    pcStack_4c = "Device Manager initialization failed\n";
  }
  __os_log_impl(0x100000000,uVar3,0,"%{public}s",&uStack_50,0xc);
LAB_1003129e0:
                    /* WARNING: Subroutine does not return */
  FUN_1000e3dcc(pcVar6);
}


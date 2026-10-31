/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005fcd8c
 * original code SHA256: 82007479d17f220673c0f2b12dc31b5ec1094888836572fbc07114d2eea73904
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1005fcd8c(long param_1,ulong param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined8 **appuStack_98 [2];
  char cStack_81;
  undefined4 uStack_80;
  undefined8 **ppuStack_7c;
  undefined *puStack_68;
  undefined8 uStack_60;
  undefined *puStack_58;
  undefined *puStack_50;
  long lStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  uStack_40 = 0;
  uStack_38 = 0;
  puVar1 = &uStack_40;
  FUN_100006ef8(puVar1,param_1);
  lVar5 = *(long *)(param_1 + 0x678);
  if (lVar5 == 0) {
    FUN_100017938();
    puVar2 = PTR___dispatch_source_type_timer_100bfc9c0;
    _dispatch_source_create(PTR___dispatch_source_type_timer_100bfc9c0,0,0,puVar1[1]);
    *(undefined **)(param_1 + 0x678) = puVar2;
    puStack_68 = PTR___NSConcreteStackBlock_100bfc978;
    uStack_60 = _UNK_100930070;
    puStack_58 = &DAT_1005fcf24;
    puStack_50 = &UNK_100b9c4b8;
    lStack_48 = param_1;
    _dispatch_source_set_event_handler();
    lVar5 = *(long *)(param_1 + 0x678);
    if (lVar5 == 0) goto LAB_1005fcef0;
  }
  uVar4 = uRam0000000100cae440;
  uVar3 = uRam0000000100cae440;
  _os_log_type_enabled(uRam0000000100cae440,0);
  if ((int)uVar3 != 0) {
    FUN_10010aa84(appuStack_98,param_1);
    ppuStack_7c = appuStack_98[0];
    if (-1 < cStack_81) {
      ppuStack_7c = appuStack_98;
    }
    uStack_80 = (undefined4)_UNK_100930b20;
    __os_log_impl(0x100000000,uVar4,0,"Starting connection request watchdog timer for %{public}s",
                  &uStack_80,0xc);
    if (cStack_81 < '\0') {
      __ZdlPv(appuStack_98[0]);
    }
    lVar5 = *(long *)(param_1 + 0x678);
  }
  uVar4 = 0;
  _dispatch_time(0,(param_2 & 0xffffffff) * 1000000000);
  _dispatch_source_set_timer(lVar5,uVar4,0xffffffffffffffff,0);
  _dispatch_resume(*(undefined8 *)(param_1 + 0x678));
LAB_1005fcef0:
  FUN_100006ec0(&uStack_40);
  return;
}


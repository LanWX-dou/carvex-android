/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005fcb40
 * original code SHA256: 9abc94672eba5ac4984b0a04aa01270206c24cb43f747f0de015f6deba2d0ff1
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1005fcb40(long param_1)

{
  undefined8 *puVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined8 **appuStack_98 [2];
  char cStack_81;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined2 uStack_78;
  undefined8 **ppuStack_76;
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
  lVar5 = *(long *)(param_1 + 0x648);
  if (lVar5 == 0) {
    FUN_100017938();
    puVar2 = PTR___dispatch_source_type_timer_100bfc9c0;
    _dispatch_source_create(PTR___dispatch_source_type_timer_100bfc9c0,0,0,puVar1[1]);
    *(undefined **)(param_1 + 0x648) = puVar2;
    puStack_68 = PTR___NSConcreteStackBlock_100bfc978;
    uStack_60 = _UNK_100930070;
    puStack_58 = &DAT_1005fccfc;
    puStack_50 = &UNK_100b9c4b8;
    lStack_48 = param_1;
    _dispatch_source_set_event_handler();
    lVar5 = *(long *)(param_1 + 0x648);
    if (lVar5 == 0) goto LAB_1005fccc8;
  }
  *(short *)(param_1 + 0x660) = *(short *)(param_1 + 0x660) + 1;
  *(char *)(param_1 + 0x650) = *(char *)(param_1 + 0x650) + '\x01';
  uVar4 = uRam0000000100cae440;
  uVar3 = uRam0000000100cae440;
  _os_log_type_enabled(uRam0000000100cae440,0);
  if ((int)uVar3 != 0) {
    FUN_10010aa84(appuStack_98,param_1);
    ppuStack_76 = appuStack_98[0];
    if (-1 < cStack_81) {
      ppuStack_76 = appuStack_98;
    }
    uStack_80 = (undefined4)_UNK_1009304f0;
    uStack_7c = 300;
    uStack_78 = 0x822;
    __os_log_impl(0x100000000,uVar4,0,
                  "Start Scan Core Page Scan backoff timer of %d seconds for device %{public}s",
                  &uStack_80,0x12);
    if (cStack_81 < '\0') {
      __ZdlPv(appuStack_98[0]);
    }
    lVar5 = *(long *)(param_1 + 0x648);
  }
  uVar4 = 0;
  _dispatch_time(0,300000000000);
  _dispatch_source_set_timer(lVar5,uVar4,0xffffffffffffffff,0);
  _dispatch_resume(*(undefined8 *)(param_1 + 0x648));
LAB_1005fccc8:
  FUN_100006ec0(&uStack_40);
  return;
}


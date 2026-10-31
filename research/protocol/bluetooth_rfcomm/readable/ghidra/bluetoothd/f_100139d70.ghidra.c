/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100139d70
 * original code SHA256: 0b9a6b415079267ea5ebb9ef9a54a006cee0b292a538c9f1ed723938b979b6eb
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100139d70(long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined4 uStack_50;
  long lStack_4c;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  uStack_40 = 0;
  uStack_38 = 0;
  puVar1 = &uStack_40;
  FUN_100006ef8(puVar1,param_1 + 400);
  lVar5 = *(long *)(param_1 + 0x1f0);
  if (lVar5 == 0) {
    FUN_100017938();
    puVar2 = PTR___dispatch_source_type_timer_100bfc9c0;
    _dispatch_source_create(PTR___dispatch_source_type_timer_100bfc9c0,0,0,puVar1[1]);
    *(undefined **)(param_1 + 0x1f0) = puVar2;
    _dispatch_source_set_event_handler();
    lVar5 = *(long *)(param_1 + 0x1f0);
    if (lVar5 == 0) goto LAB_100139e60;
  }
  uVar4 = uRam0000000100cae458;
  uVar3 = uRam0000000100cae458;
  _os_log_type_enabled(uRam0000000100cae458,0);
  if ((int)uVar3 != 0) {
    uStack_50 = (undefined4)_UNK_100930ae8;
    lStack_4c = param_2;
    __os_log_impl(0x100000000,uVar4,0,"Start Scan Core Page Scan timer of %llu seconds",&uStack_50,
                  0xc);
    lVar5 = *(long *)(param_1 + 0x1f0);
  }
  uVar4 = 0;
  _dispatch_time(0,param_2 * 1000000000);
  _dispatch_source_set_timer(lVar5,uVar4,0xffffffffffffffff,0);
  _dispatch_resume(*(undefined8 *)(param_1 + 0x1f0));
LAB_100139e60:
  FUN_100006ec0(&uStack_40);
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000020f0
 * original code SHA256: b7b5ad47221cd5c10a24b97a1ed7648f2172d8042876432d9f1e0218ea77f8be
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x20 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x21 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x22 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

void _platform_navigation_routeGuidanceUpdateHandler(long param_1)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  undefined *puVar4;
  undefined8 uVar5;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined2 local_64;
  undefined2 local_62;
  undefined6 uStack_60;
  undefined2 local_5a;
  long local_58;
  long local_48;
  
  local_48 = *(long *)PTR____stack_chk_guard_10022bb80;
  lVar3 = param_1;
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x32)) {
    puVar4 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      lVar3 = _platform_navigation_accessoryDetached_cold_1();
      puVar4 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar4 = *(undefined **)(_gLogObjects + 0x188);
  }
  iVar1 = _os_log_type_enabled(puVar4,lVar3,1);
  if (iVar1 != 0) {
    local_70 = (undefined4)DAT_1001b30f8;
    uStack_6c = (undefined4)param_1;
    uStack_68 = (undefined4)((ulong)param_1 >> 0x20);
    local_64 = 0x840;
    local_62 = (undefined2)param_1;
    uStack_60 = (undefined6)((ulong)param_1 >> 0x10);
    local_5a = 0x840;
    local_58 = param_1;
    __os_log_impl(0x100000000,lVar3,1,
                  "navigation routeGuidanceUpdateHandler: %@, componentIdList=%@, updateInfo=%@",
                  &local_70,0x20);
  }
  local_74 = 0;
  uVar5 = *(undefined8 *)PTR__kCFAllocatorDefault_10022bce0;
  uVar2 = _CFNumberCreate(uVar5,3,&local_74);
  lVar3 = *(long *)PTR__kCFNull_10022bd18;
  if (param_1 != 0) {
    lVar3 = param_1;
  }
  local_70 = (undefined4)uVar2;
  uStack_6c = (undefined4)((ulong)uVar2 >> 0x20);
  uStack_68 = (undefined4)lVar3;
  local_64 = (undefined2)((ulong)lVar3 >> 0x20);
  local_62 = (undefined2)((ulong)lVar3 >> 0x30);
  lVar3 = *(long *)PTR__kCFNull_10022bd18;
  if (param_1 != 0) {
    lVar3 = param_1;
  }
  uStack_60 = (undefined6)lVar3;
  local_5a = (undefined2)((ulong)lVar3 >> 0x30);
  uVar5 = _CFArrayCreate(uVar5,&local_70,3,PTR__kCFTypeArrayCallBacks_10022bd38);
  _accFeatureHandlers_invokeHandler(param_1,0x6a4,uVar5);
  _CFRelease(uVar5);
  _CFRelease(uVar2);
  if (*(long *)PTR____stack_chk_guard_10022bb80 != local_48) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return;
}


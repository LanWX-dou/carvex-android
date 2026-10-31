/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000438d0
 * original code SHA256: 57f54e80068f727c13d5b558140ea5fb6ad9d12ab90130dbbc2b97cfd9814aa3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void __validateHIDComponent(long param_1,uint param_2)

{
  undefined *puVar1;
  undefined1 uVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  size_t sVar6;
  int *piVar7;
  void *pvVar8;
  undefined *puVar9;
  undefined8 uStack_70;
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_10022bb80;
  uVar2 = 0;
  if (param_1 != 0) {
    lVar4 = _iap2_feature_getFeature(param_1,0xb);
    if (lVar4 == 0) {
      __validateHIDComponent_cold_3((long)&uStack_70 + 7);
      uVar2 = uStack_70._7_1_;
    }
    else {
      lVar4 = *(long *)(lVar4 + 8);
      if (lVar4 == 0) {
        uVar2 = 0;
      }
      else {
        lVar5 = _CFDictionaryGetCount(lVar4);
        uVar2 = 0;
        if (lVar5 != 0) {
          sVar6 = lVar5 << 3;
          (*(code *)PTR____chkstk_darwin_10022bdb0)();
          pvVar8 = (void *)((long)&uStack_70 - (sVar6 + 0xf & 0xfffffffffffffff0));
          _memset(pvVar8,0xaa,sVar6);
          _CFDictionaryGetKeysAndValues(lVar4,0,pvVar8);
          puVar1 = PTR___os_log_default_10022bbb0;
          if (0 < lVar5) {
            lVar4 = 0;
            do {
              piVar7 = *(int **)((long)pvVar8 + lVar4 * 8);
              if (piVar7 == (int *)0x0) {
                if ((_gLogObjects == 0) || (_gNumLogObjects < 0x24)) {
                  puVar9 = puVar1;
                  if (_logObjectForModule_onceToken != -1) {
                    __validateHIDComponent_cold_1();
                  }
                }
                else {
                  puVar9 = *(undefined **)(_gLogObjects + 0x118);
                }
                iVar3 = _os_log_type_enabled(puVar9,0x10);
                if (iVar3 != 0) {
                  __validateHIDComponent_cold_2(&uStack_70,(ulong)&uStack_70 | 1,puVar9);
                }
              }
              else if (((*piVar7 == 0) && ((uint)piVar7[4] < 0xb)) &&
                      (*(ushort *)(piVar7 + 1) == param_2)) {
                uVar2 = 1;
                goto LAB_100043a44;
              }
              lVar4 = lVar4 + 1;
              lVar5 = lVar5 + -1;
            } while (lVar5 != 0);
          }
          uVar2 = 0;
        }
      }
    }
  }
LAB_100043a44:
  if (*(long *)PTR____stack_chk_guard_10022bb80 != local_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(uVar2);
  }
  return;
}


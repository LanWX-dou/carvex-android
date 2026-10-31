/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100043704
 * original code SHA256: 79367d0e6cd3eb3223d4bdea85dc9b4ea987ab0fac4e902aa64b024dc2b0e08b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void __hidComponentFunctionType(long param_1,uint param_2)

{
  undefined *puVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  size_t sVar5;
  int *piVar6;
  void *pvVar7;
  undefined *puVar8;
  uint local_70 [2];
  long local_68;
  
  local_68 = *(long *)PTR____stack_chk_guard_10022bb80;
  if (param_1 != 0) {
    lVar3 = _iap2_feature_getFeature(param_1,0xb);
    if (lVar3 == 0) {
      __hidComponentFunctionType_cold_4(local_70);
      goto LAB_100043878;
    }
    if (*(long *)(lVar3 + 8) == 0) {
      __hidComponentFunctionType_cold_3(local_70);
      goto LAB_100043878;
    }
    lVar4 = _CFDictionaryGetCount();
    if (lVar4 != 0) {
      sVar5 = lVar4 << 3;
      (*(code *)PTR____chkstk_darwin_10022bdb0)();
      pvVar7 = (void *)((long)local_70 - (sVar5 + 0xf & 0xfffffffffffffff0));
      _memset(pvVar7,0xaa,sVar5);
      _CFDictionaryGetKeysAndValues(*(undefined8 *)(lVar3 + 8),0,pvVar7);
      puVar1 = PTR___os_log_default_10022bbb0;
      if (0 < lVar4) {
        lVar3 = 0;
        do {
          piVar6 = *(int **)((long)pvVar7 + lVar3 * 8);
          if (piVar6 == (int *)0x0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x24)) {
              puVar8 = puVar1;
              if (_logObjectForModule_onceToken != -1) {
                __validateHIDComponent_cold_1();
              }
            }
            else {
              puVar8 = *(undefined **)(_gLogObjects + 0x118);
            }
            iVar2 = _os_log_type_enabled(puVar8,0x10);
            if (iVar2 != 0) {
              __validateHIDComponent_cold_2(local_70,(ulong)local_70 | 1,puVar8);
            }
          }
          else if (((*piVar6 == 0) && (local_70[0] = piVar6[4], local_70[0] < 0xb)) &&
                  (*(ushort *)(piVar6 + 1) == param_2)) goto LAB_100043878;
          lVar3 = lVar3 + 1;
          lVar4 = lVar4 + -1;
        } while (lVar4 != 0);
      }
      local_70[0] = 0xb;
      goto LAB_100043878;
    }
  }
  local_70[0] = 0xb;
LAB_100043878:
  if (*(long *)PTR____stack_chk_guard_10022bb80 != local_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(local_70[0]);
  }
  return;
}


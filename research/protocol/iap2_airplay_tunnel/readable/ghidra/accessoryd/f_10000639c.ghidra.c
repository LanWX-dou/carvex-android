/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000639c
 * original code SHA256: e0c2e4531df4aed8ebc3debad945fca980a20888458e8fda06682dcdba00ed24
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2FSMHandleEvent(long *param_1,uint param_2)

{
  ulong *puVar1;
  undefined8 *puVar2;
  byte bVar3;
  int iVar4;
  long lVar5;
  code *pcVar6;
  undefined8 *puVar7;
  ulong uVar8;
  undefined *puVar9;
  long lVar10;
  undefined4 local_70;
  char *local_6c;
  undefined2 local_64;
  long *local_62;
  undefined2 local_5a;
  uint local_58;
  undefined2 local_54;
  char *local_52;
  undefined2 local_4a;
  uint local_48;
  undefined2 local_44;
  char *local_42;
  byte local_31;
  
  local_31 = (byte)param_2;
  local_62 = param_1;
  if ((param_1 == (long *)0x0) || (*(byte *)((long)param_1 + 9) <= param_2)) {
    if ((__iAP2LogEnableMask & 1) != 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        puVar9 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
LAB_100006670:
          _iAP2FSMHandleEvent_cold_4();
          puVar9 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar9 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar4 = _os_log_type_enabled(puVar9,0);
      if (iVar4 != 0) {
        local_52 = "";
        local_6c = local_52;
        if (param_1 != (long *)0x0) {
          if ((char *)param_1[3] != (char *)0x0) {
            local_6c = (char *)param_1[3];
          }
          if (param_1[5] != 0) {
            local_52 = *(char **)(param_1[5] + (ulong)param_2 * 8);
          }
        }
        local_70 = (undefined4)DAT_1001b30e0;
        local_64 = 0x800;
        local_5a = 0x400;
        local_54 = 0x820;
        local_58 = param_2;
        __os_log_impl(0x100000000,puVar9,0,
                      "ERROR: \'%s\': NULL fsm(%p) pointer or invalid event(%d:%s)!",&local_70,0x26)
        ;
      }
    }
  }
  else {
    do {
      lVar5 = *param_1;
      puVar1 = (ulong *)(lVar5 + (ulong)*(byte *)((long)param_1 + 10) * 0x10);
      puVar7 = (undefined8 *)*puVar1;
      uVar8 = (ulong)(byte)puVar1[1];
      puVar2 = puVar7 + uVar8 * 2;
      if (uVar8 == 0) {
LAB_1000064a0:
        if ((__iAP2LogEnableMask & 1) != 0) {
          if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
            puVar9 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              _iAP2FSMHandleEvent_cold_3();
              puVar9 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar9 = *(undefined **)(_gLogObjects + 0xb0);
          }
          iVar4 = _os_log_type_enabled(puVar9,0);
          if (iVar4 != 0) {
            local_52 = "";
            local_6c = local_52;
            if ((char *)param_1[3] != (char *)0x0) {
              local_6c = (char *)param_1[3];
            }
            if (param_1[5] != 0) {
              local_52 = *(char **)(param_1[5] + (ulong)local_31 * 8);
            }
            if (param_1[4] == 0) {
              local_42 = "";
            }
            else {
              local_42 = *(char **)(param_1[4] + (ulong)*(byte *)((long)param_1 + 10) * 8);
            }
            local_70 = (undefined4)DAT_1001b30e8;
            local_64 = 0x800;
            local_5a = 0x400;
            local_58 = (uint)local_31;
            local_54 = 0x820;
            local_4a = 0x400;
            local_48 = (uint)*(byte *)((long)param_1 + 10);
            local_44 = 0x820;
            __os_log_impl(0x100000000,puVar9,0,
                          "ERROR: \'%s\'(%p): No handler for event(%d:%s) for state(%d:%s)",
                          &local_70,0x36);
          }
        }
        bVar3 = *(byte *)((long)param_1 + 9);
        break;
      }
      lVar10 = (long)puVar7 + 9;
      while (*(byte *)((long)puVar7 + 9) != param_2) {
        puVar7 = puVar7 + 2;
        lVar10 = lVar10 + 0x10;
        if (puVar2 <= puVar7) {
          if (lVar5 != 0) goto LAB_1000064a0;
          goto LAB_100006668;
        }
      }
      if (lVar5 == 0) {
LAB_100006668:
        _iAP2FSMHandleEvent_cold_2();
LAB_10000666c:
        _iAP2FSMHandleEvent_cold_1();
        goto LAB_100006670;
      }
      pcVar6 = (code *)*puVar7;
      if (pcVar6 == (code *)0x0) goto LAB_1000064a0;
      *(char *)((long)param_1 + 0xb) = (char)param_2;
      (*pcVar6)(param_1,&local_31);
      bVar3 = *(byte *)(lVar10 + -1);
      *(byte *)((long)param_1 + 10) = bVar3;
      if (*(byte *)(param_1 + 1) <= bVar3) goto LAB_10000666c;
      param_2 = (uint)local_31;
      bVar3 = *(byte *)((long)param_1 + 9);
    } while (local_31 < bVar3);
    *(byte *)((long)param_1 + 0xb) = bVar3;
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000cf5b8
 * original code SHA256: e03d30f543ee9dfb7f0c46e9895f5bbac8bccb92601c9c598cdb10f45f330fb4
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _acc_protocolParser_iAP2_run(long param_1,int *param_2,byte *param_3)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  undefined *puVar4;
  undefined2 *puVar5;
  uint uVar6;
  byte *pbVar7;
  uint *puVar8;
  uint *puVar9;
  undefined2 local_90 [8];
  undefined2 local_80 [8];
  undefined2 local_70 [8];
  undefined2 local_60 [8];
  
  if (*param_2 != 4) {
    return;
  }
  puVar5 = local_90;
  puVar9 = *(uint **)(param_2 + 2);
  uVar1 = *puVar9;
  uVar6 = uVar1;
  if (10 < uVar1) goto LAB_1000cfb24;
  switch(uVar1) {
  default:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_29(puVar4);
    }
    uVar6 = (uint)(*param_3 == 0xff);
    *(byte *)((long)puVar9 + 6) = *(char *)((long)puVar9 + 6) + *param_3;
    break;
  case 1:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_27(puVar4);
    }
    uVar6 = 2;
    if (*param_3 != 0x5a) {
      uVar6 = 0xc;
    }
    *(byte *)((long)puVar9 + 6) = *(char *)((long)puVar9 + 6) + *param_3;
    goto LAB_1000cfb24;
  case 2:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_25(puVar4);
    }
    *(ushort *)(puVar9 + 1) = (ushort)*param_3 << 8;
    *(byte *)((long)puVar9 + 6) = *(char *)((long)puVar9 + 6) + *param_3;
    uVar6 = 3;
    break;
  case 3:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_19(puVar4);
    }
    puVar8 = puVar9 + 1;
    uVar2 = (ushort)*puVar8 | (ushort)*param_3;
    *(ushort *)puVar8 = uVar2;
    if (8 < uVar2) {
      *(ushort *)(puVar9 + 4) = uVar2 - 9;
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x13)) {
        puVar4 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _acc_protocolParser_iAP2_run_cold_4();
          puVar4 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0x90);
      }
      iVar3 = _os_log_type_enabled(puVar4,2);
      if (iVar3 != 0) {
        _acc_protocolParser_iAP2_run_cold_21(puVar8,puVar4);
      }
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x13)) {
        puVar4 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _acc_protocolParser_iAP2_run_cold_4();
          puVar4 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0x90);
      }
      iVar3 = _os_log_type_enabled(puVar4,2);
      if (iVar3 != 0) {
        _acc_protocolParser_iAP2_run_cold_23(puVar9 + 4,puVar4);
      }
      *(byte *)((long)puVar9 + 6) = *(char *)((long)puVar9 + 6) + *param_3;
      uVar6 = 4;
      break;
    }
    goto LAB_1000cfb20;
  case 4:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_17(puVar4);
    }
    *(byte *)((long)puVar9 + 6) = *(char *)((long)puVar9 + 6) + *param_3;
    uVar6 = 5;
    break;
  case 5:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_15(puVar4);
    }
    *(byte *)((long)puVar9 + 6) = *(char *)((long)puVar9 + 6) + *param_3;
    uVar6 = 6;
    break;
  case 6:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_13(puVar4);
    }
    *(byte *)((long)puVar9 + 6) = *(char *)((long)puVar9 + 6) + *param_3;
    uVar6 = 7;
    break;
  case 7:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_11(puVar4);
    }
    *(byte *)((long)puVar9 + 6) = *(char *)((long)puVar9 + 6) + *param_3;
    uVar6 = 8;
    break;
  case 8:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_8(puVar4);
    }
    if (*(char *)((long)puVar9 + 6) == (byte)-*param_3) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x13)) {
        puVar4 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _acc_protocolParser_iAP2_run_cold_4();
          puVar4 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0x90);
      }
      iVar3 = _os_log_type_enabled(puVar4,1);
      if (iVar3 != 0) {
        local_60[0] = 0;
        __os_log_impl(0x100000000,puVar4,1,"iAP2 header checksum validated!",local_60,2);
      }
      if ((short)puVar9[4] == 1) {
        uVar6 = 10;
        break;
      }
      if ((short)puVar9[4] != 0) {
        uVar6 = 9;
        break;
      }
      *(int *)(param_1 + 0x1c) = *param_2;
      puVar4 = (undefined *)_logObjectForModule();
      iVar3 = _os_log_type_enabled(puVar4,1);
      if (iVar3 != 0) {
        local_70[0] = 0;
        puVar5 = local_70;
        goto LAB_1000cfd58;
      }
LAB_1000cfd68:
      uVar6 = 0xb;
      break;
    }
    goto LAB_1000cfb20;
  case 9:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_6(puVar4);
    }
    pbVar7 = *(byte **)(puVar9 + 2);
    if (*(byte **)(puVar9 + 2) == (byte *)0x0) {
      *(byte **)(puVar9 + 2) = param_3;
      pbVar7 = param_3;
    }
    if (1 < (ushort)puVar9[4]) {
      uVar6 = 9;
      if ((ushort)puVar9[4] - 2 == ((int)param_3 - (int)pbVar7 & 0xffffU)) {
        uVar6 = 10;
      }
      *(byte *)((long)puVar9 + 0x12) = *(char *)((long)puVar9 + 0x12) + *param_3;
      break;
    }
    goto LAB_1000cfb20;
  case 10:
    if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _acc_protocolParser_iAP2_run_cold_5();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0x90);
    }
    iVar3 = _os_log_type_enabled(puVar4,2);
    if (iVar3 != 0) {
      _acc_protocolParser_iAP2_run_cold_2(puVar4);
    }
    if (*(char *)((long)puVar9 + 0x12) == (byte)-*param_3) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x13)) {
        puVar4 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _acc_protocolParser_iAP2_run_cold_4();
          puVar4 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0x90);
      }
      iVar3 = _os_log_type_enabled(puVar4,1);
      if (iVar3 != 0) {
        local_80[0] = 0;
        __os_log_impl(0x100000000,puVar4,1,"iAP2 payload checksum validated!",local_80,2);
      }
      *(int *)(param_1 + 0x1c) = *param_2;
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x13)) {
        puVar4 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _acc_protocolParser_iAP2_run_cold_4();
          puVar4 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0x90);
      }
      iVar3 = _os_log_type_enabled(puVar4,1);
      if (iVar3 != 0) {
        local_90[0] = 0;
LAB_1000cfd58:
        __os_log_impl(0x100000000,puVar4,1,"iAP2 detected!",puVar5,2);
      }
      goto LAB_1000cfd68;
    }
LAB_1000cfb20:
    uVar6 = 0xc;
LAB_1000cfb24:
    if (uVar1 != 0xc && uVar6 == 0xc) {
      *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
      if (_gLogObjects == 0 || _gNumLogObjects < 0x13) {
        puVar4 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _acc_protocolParser_iAP2_run_cold_4();
          puVar4 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0x90);
      }
      iVar3 = _os_log_type_enabled(puVar4,2);
      if (iVar3 != 0) {
        _acc_protocolParser_iAP2_run_cold_31(puVar4);
      }
      uVar6 = 0xc;
    }
  }
  *puVar9 = uVar6;
  return;
}


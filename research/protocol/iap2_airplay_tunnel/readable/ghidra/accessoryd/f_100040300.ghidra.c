/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100040300
 * original code SHA256: 9eca1047107a6672446828aad5149aebde1b4be3a4d0b4ed93a72ca1dd791ae3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _t56_protocol_checkValidMessageHeaderAndSize(long param_1,undefined8 param_2,ulong param_3)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  ulong uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  undefined *puVar14;
  undefined4 local_90;
  char *local_8c;
  undefined2 local_84;
  undefined4 local_82;
  undefined2 local_7e;
  int local_7c;
  undefined2 local_78;
  int local_76;
  undefined2 uStack_72;
  undefined2 uStack_70;
  undefined2 uStack_6e;
  undefined2 local_6c;
  undefined2 uStack_6a;
  undefined2 uStack_68;
  uint uStack_66;
  undefined2 local_62;
  uint local_60;
  undefined2 local_5c;
  uint local_5a;
  
  iVar13 = (int)param_2;
  uVar12 = (uint)param_3;
  if (param_1 == 0) {
    iVar7 = -2;
    goto LAB_100040608;
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
    puVar14 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      _logObjectForModule_cold_1();
      puVar14 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar14 = *(undefined **)(_gLogObjects + 0x1f8);
  }
  iVar7 = _os_log_type_enabled(puVar14,1);
  uVar4 = uStack_6a;
  uVar3 = local_6c;
  local_6c = (undefined2)param_2;
  uVar1 = local_6c;
  uStack_6a = (undefined2)((ulong)param_2 >> 0x10);
  uVar2 = uStack_6a;
  if (iVar7 != 0) {
    uVar9 = _t56_protocol_msgTypeString(param_2);
    local_90 = (undefined4)DAT_1001b30e8;
    local_8c = "t56_protocol_checkValidMessageHeaderAndSize";
    local_84 = 0x400;
    local_82 = 400;
    local_7e = 0x400;
    local_78 = 0x820;
    local_76 = (int)uVar9;
    uStack_72 = (undefined2)((ulong)uVar9 >> 0x20);
    uStack_70 = (undefined2)((ulong)uVar9 >> 0x30);
    uStack_6e = 0x400;
    uStack_68 = 0x400;
    local_7c = iVar13;
    uStack_66 = uVar12;
    __os_log_impl(0x100000000,puVar14,1,"%s:%d msgType %d(%s), msgHeader 0x%02X, msgDataLen %d",
                  &local_90,0x2e);
    uVar3 = local_6c;
    uVar4 = uStack_6a;
  }
  uStack_6a = uVar4;
  local_6c = uVar3;
  iVar8 = *(int *)(param_1 + 8);
  if (iVar8 == 0) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
      puVar14 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _t56_protocol_cleanup_cold_2();
        puVar14 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar14 = *(undefined **)(_gLogObjects + 0x1f8);
    }
    uVar10 = _os_log_type_enabled(puVar14,2);
    if ((uVar10 & 1) != 0) {
      uVar9 = _t56_protocol_msgTypeString(param_2);
      local_90 = (undefined4)DAT_1001b30e8;
      local_8c = "t56_protocol_checkValidMessageHeaderAndSize";
      local_84 = 0x400;
      local_82 = 0x196;
      local_7e = 0x400;
      local_78 = 0x820;
      local_76 = (int)uVar9;
      uStack_72 = (undefined2)((ulong)uVar9 >> 0x20);
      uStack_70 = (undefined2)((ulong)uVar9 >> 0x30);
      uStack_6e = 0x400;
      uStack_68 = 0x400;
      local_7c = iVar13;
      local_6c = uVar1;
      uStack_6a = uVar2;
      uStack_66 = uVar12;
      __os_log_debug_impl(0x100000000,puVar14,2,
                          "%s:%d Device, msgType %d(%s), msgHeader 0x%02X, msgDataLen %d",&local_90,
                          0x2e);
    }
    if (iVar13 < 6) {
      if (iVar13 == 2) {
        bVar5 = 0xb < uVar12;
        bVar6 = uVar12 == 0xc;
      }
      else {
        if (iVar13 != 4) {
LAB_10004049c:
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
            puVar14 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              _t56_protocol_cleanup_cold_2();
              puVar14 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar14 = *(undefined **)(_gLogObjects + 0x1f8);
          }
          iVar7 = _os_log_type_enabled(puVar14,0x10);
          if (iVar7 != 0) {
            _t56_protocol_checkValidMessageHeaderAndSize_cold_4(param_2,param_3,puVar14);
          }
          iVar11 = -2;
          goto LAB_1000404fc;
        }
        bVar6 = (param_3 & 0xffffffff) - 0x11 < 0xfffffffffffffff6;
        bVar5 = bVar6 && 5 < uVar12;
        bVar6 = bVar6 && uVar12 == 6;
      }
LAB_1000404c4:
      iVar11 = 0;
      if (!bVar5 || bVar6) {
        iVar11 = -2;
      }
    }
    else {
      if (iVar13 == 6) {
        bVar5 = 7 < uVar12;
        bVar6 = uVar12 == 8;
        goto LAB_1000404c4;
      }
      if (iVar13 != 8) goto LAB_10004049c;
      iVar11 = 0;
      if (uVar12 != 9) {
        iVar11 = -2;
      }
    }
LAB_1000404fc:
    iVar8 = *(int *)(param_1 + 8);
  }
  else {
    iVar11 = -2;
  }
  iVar7 = iVar11;
  if (iVar8 == 1) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
      puVar14 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _t56_protocol_cleanup_cold_2();
        puVar14 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar14 = *(undefined **)(_gLogObjects + 0x1f8);
    }
    uVar10 = _os_log_type_enabled(puVar14,2);
    if ((uVar10 & 1) != 0) {
      uVar9 = _t56_protocol_msgTypeString(param_2);
      local_90 = (undefined4)DAT_1001b30e8;
      local_8c = "t56_protocol_checkValidMessageHeaderAndSize";
      local_84 = 0x400;
      local_82 = 0x1c2;
      local_7e = 0x400;
      local_78 = 0x820;
      local_76 = (int)uVar9;
      uStack_72 = (undefined2)((ulong)uVar9 >> 0x20);
      uStack_70 = (undefined2)((ulong)uVar9 >> 0x30);
      uStack_6e = 0x400;
      uStack_68 = 0x400;
      local_7c = iVar13;
      local_6c = uVar1;
      uStack_6a = uVar2;
      uStack_66 = uVar12;
      __os_log_debug_impl(0x100000000,puVar14,2,
                          "%s:%d Accessory, msgType %d(%s), msgHeader 0x%02X, msgDataLen %d",
                          &local_90,0x2e);
    }
    if (iVar13 < 5) {
      if (iVar13 != 1) {
        if (iVar13 == 3) goto LAB_10004056c;
LAB_100040584:
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
          puVar14 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            _t56_protocol_cleanup_cold_2();
            puVar14 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar14 = *(undefined **)(_gLogObjects + 0x1f8);
        }
        iVar8 = _os_log_type_enabled(puVar14,0x10);
        if (iVar8 != 0) {
          _t56_protocol_checkValidMessageHeaderAndSize_cold_7(param_2,param_3,puVar14);
        }
        goto LAB_1000405b8;
      }
      bVar5 = 5 < uVar12;
      bVar6 = uVar12 == 6;
    }
    else if (iVar13 == 5) {
      bVar5 = 3 < uVar12;
      bVar6 = uVar12 == 4;
    }
    else if (iVar13 == 6) {
      bVar5 = 7 < uVar12;
      bVar6 = uVar12 == 8;
    }
    else {
      if (iVar13 != 7) goto LAB_100040584;
LAB_10004056c:
      bVar5 = 1 < uVar12;
      bVar6 = uVar12 == 2;
    }
    iVar7 = 0;
    if (!bVar5 || bVar6) {
      iVar7 = iVar11;
    }
  }
LAB_1000405b8:
  if (1 < *(uint *)(param_1 + 8)) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
      puVar14 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _t56_protocol_cleanup_cold_2();
        puVar14 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar14 = *(undefined **)(_gLogObjects + 0x1f8);
    }
    iVar8 = _os_log_type_enabled(puVar14,0x10);
    if (iVar8 != 0) {
      iVar8 = *(int *)(param_1 + 8);
      uVar9 = _t56_protocol_msgTypeString(param_2);
      local_90 = (undefined4)DAT_1001b3368;
      local_8c = "t56_protocol_checkValidMessageHeaderAndSize";
      local_84 = 0x400;
      local_82 = 500;
      local_7e = 0x400;
      local_78 = 0x400;
      uStack_72 = 0x400;
      local_6c = 0x820;
      uStack_6a = (undefined2)uVar9;
      uStack_68 = (undefined2)((ulong)uVar9 >> 0x10);
      uStack_66 = (uint)((ulong)uVar9 >> 0x20);
      local_62 = 0x400;
      local_5c = 0x400;
      local_7c = iVar8;
      local_76 = iVar7;
      uStack_70 = uVar1;
      uStack_6e = uVar2;
      local_60 = iVar13;
      local_5a = uVar12;
      __os_log_error_impl(0x100000000,puVar14,0x10,
                          "%s:%d Unknown Role! %d, result %d, msgType %d(%s), msgHeader 0x%02X, msgDataLen %d"
                          ,&local_90,0x3a);
    }
  }
LAB_100040608:
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x40)) {
    puVar14 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      _t56_protocol_cleanup_cold_2();
      puVar14 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar14 = *(undefined **)(_gLogObjects + 0x1f8);
  }
  iVar8 = _os_log_type_enabled(puVar14,1);
  if (iVar8 != 0) {
    uVar9 = _t56_protocol_msgTypeString(param_2);
    local_90 = (undefined4)DAT_1001b3128;
    local_8c = "t56_protocol_checkValidMessageHeaderAndSize";
    local_84 = 0x400;
    local_82 = 0x1f9;
    local_7e = 0x400;
    local_78 = 0x400;
    uStack_72 = 0x820;
    uStack_70 = (undefined2)uVar9;
    uStack_6e = (undefined2)((ulong)uVar9 >> 0x10);
    local_6c = (undefined2)((ulong)uVar9 >> 0x20);
    uStack_6a = (undefined2)((ulong)uVar9 >> 0x30);
    uStack_68 = 0x400;
    local_62 = 0x400;
    local_7c = iVar7;
    local_76 = iVar13;
    uStack_66 = iVar13;
    local_60 = uVar12;
    __os_log_impl(0x100000000,puVar14,1,
                  "%s:%d result %d, msgType %d(%s), msgHeader 0x%02X, msgDataLen %d",&local_90,0x34)
    ;
  }
  return iVar7 == 0;
}


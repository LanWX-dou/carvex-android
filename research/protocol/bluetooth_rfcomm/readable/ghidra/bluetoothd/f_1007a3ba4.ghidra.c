/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1007a3ba4
 * original code SHA256: bfb997ca07ae992fd0481edd812966b8ab437fd1e87c19b8990d3eec7ddb32c0
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 phone_fn_1007a3ba4(undefined8 param_1,ulong param_2)

{
  undefined1 *puVar1;
  ulong uVar2;
  ulong uVar3;
  code *pcVar4;
  char *pcVar5;
  char *pcVar6;
  undefined8 uVar7;
  uint uVar8;
  undefined8 uVar9;
  undefined1 local_d0;
  undefined7 uStack_cf;
  char local_b9;
  undefined2 local_b0;
  undefined2 uStack_ae;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined2 uStack_a4;
  undefined2 uStack_a2;
  undefined2 uStack_a0;
  undefined2 local_9e;
  char *local_9c;
  char *local_88;
  char *local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined *puStack_68;
  undefined8 local_60;
  undefined *puStack_58;
  
  uVar7 = uRam0000000100cae430;
  if (param_2 == 0) {
    uVar9 = uRam0000000100cae430;
    _os_log_type_enabled(uRam0000000100cae430,0x10);
    if ((int)uVar9 != 0) {
      FUN_1008f6108(uVar7);
    }
    return 1;
  }
  puStack_58 = PTR_DAT_100bca680;
  local_60 = _UNK_100bca678;
  puStack_68 = PTR_DAT_100bca690;
  local_70 = _UNK_100bca688;
  local_88 = (char *)0x0;
  local_80 = (char *)0x0;
  local_78 = 0;
  uVar2 = param_2;
  FUN_1005ebdf0(param_2,&local_70,4,&local_88);
  if (((uVar2 & 1) == 0) &&
     (uVar3 = param_2, FUN_1005ebdf0(param_2,&local_60,4,&local_88), uVar7 = uRam0000000100cae430,
     (int)uVar3 == 0)) {
    uVar9 = uRam0000000100cae430;
    _os_log_type_enabled(uRam0000000100cae430,0x10);
    if ((int)uVar9 != 0) {
      FUN_10010aa84(&local_b0,param_2);
      FUN_1008f6028(&local_b0,&local_d0,uVar7);
    }
  }
  else {
    pcVar5 = local_88;
    if (local_88 != local_80) {
      do {
        if ((((*pcVar5 == '\x06') && (*(short *)(pcVar5 + 2) == 2)) &&
            (pcVar6 = *(char **)(pcVar5 + 8), *pcVar6 == '\x03')) &&
           ((*(int *)(pcVar6 + 8) == 3 && (pcVar6[0x10] == '\x01')))) {
          uVar8 = *(uint *)(pcVar6 + 0x18);
          pcVar5 = local_88;
          goto LAB_1007a3c8c;
        }
        pcVar5 = pcVar5 + 0x10;
      } while (pcVar5 != local_80);
      uVar8 = 0xffffffff;
      pcVar5 = local_88;
LAB_1007a3c8c:
      do {
        pcVar6 = pcVar5 + 0x10;
        uVar9 = *(undefined8 *)(pcVar5 + 8);
        uVar7 = *(undefined8 *)pcVar5;
        uStack_a8 = (undefined4)uVar9;
        uStack_a4 = (undefined2)((ulong)uVar9 >> 0x20);
        uStack_a2 = (undefined2)((ulong)uVar9 >> 0x30);
        local_b0 = (undefined2)uVar7;
        uStack_ae = (undefined2)((ulong)uVar7 >> 0x10);
        uStack_ac = (undefined4)((ulong)uVar7 >> 0x20);
        FUN_100457214(&local_b0);
        uVar7 = uRam0000000100cae430;
        pcVar5 = pcVar6;
      } while (pcVar6 != local_80);
      if (uVar8 != 0xffffffff) {
        uVar9 = uRam0000000100cae430;
        _os_log_type_enabled(uRam0000000100cae430,0);
        if ((int)uVar9 != 0) {
          FUN_10010aa84(&local_d0,param_2);
          puVar1 = (undefined1 *)CONCAT71(uStack_cf,local_d0);
          if (-1 < local_b9) {
            puVar1 = &local_d0;
          }
          local_b0 = (undefined2)_UNK_100930fa8;
          uStack_ae = (undefined2)((ulong)_UNK_100930fa8 >> 0x10);
          local_9c = "New WiAP UUID";
          if ((int)uVar2 == 0) {
            local_9c = "Old WiAP UUID";
          }
          uStack_ac = SUB84(puVar1,0);
          uStack_a8 = (undefined4)((ulong)puVar1 >> 0x20);
          uStack_a4 = 0x400;
          uStack_a2 = (undefined2)uVar8;
          uStack_a0 = (undefined2)(uVar8 >> 0x10);
          local_9e = 0x822;
          __os_log_impl(0x100000000,uVar7,0,
                        "Initiating outgoing Wireless IAP connection request to device %{public}s on rfcomm channel %d, %{public}s"
                        ,&local_b0,0x1c);
          if (local_b9 < '\0') {
            __ZdlPv(CONCAT71(uStack_cf,local_d0));
          }
        }
        local_d0 = 0;
        FUN_100061a60(&local_d0);
        local_b0 = 0;
        pcVar4 = phone_fn_1007a3f08;
        FUN_1003c2b00(phone_fn_1007a3f08,&PTR_phone_fn_1007a58e0_100bca590,param_2 + 0x80,
                      uVar8 & 0xff,0x3ef,0x3b01,&local_b0,&UNK_100bca5b8);
        uVar7 = uRam0000000100cae430;
        if ((int)pcVar4 == 0) {
          FUN_10062cb94(param_1,param_2,local_b0);
          uVar7 = 0;
        }
        else {
          uVar9 = uRam0000000100cae430;
          _os_log_type_enabled(uRam0000000100cae430,0x10);
          if ((int)uVar9 != 0) {
            FUN_1008f6098(pcVar4,uVar7);
          }
          uVar7 = 0x131;
        }
        FUN_10006b538(&local_d0);
        goto LAB_1007a3e58;
      }
    }
    uVar7 = uRam0000000100cae430;
    uVar9 = uRam0000000100cae430;
    _os_log_type_enabled(uRam0000000100cae430,0x10);
    if ((int)uVar9 != 0) {
      FUN_1008f60d4(uVar7);
    }
  }
  uVar7 = 0x131;
LAB_1007a3e58:
  if (local_88 != (char *)0x0) {
    local_80 = local_88;
    __ZdlPv();
  }
  return uVar7;
}


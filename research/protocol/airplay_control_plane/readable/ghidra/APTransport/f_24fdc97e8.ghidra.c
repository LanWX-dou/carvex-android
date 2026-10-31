/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fdc97e8
 * original code SHA256: e12833e789ad1a0d9f5a631d3c48130ed7274aaa7a3d40cc4a4caec5d13895b6
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x00024fdc9898) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_httpconnection_configureEncryptionInternal
          (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  code *pcVar7;
  undefined8 *puVar8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined *local_b0;
  undefined *puStack_a8;
  long local_a0;
  undefined8 local_98;
  undefined8 local_90;
  undefined *local_88;
  undefined *puStack_80;
  long local_78;
  undefined8 local_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 local_50;
  long local_40;
  long local_38;
  
  puVar6 = &local_c0;
  lVar2 = func_0x0002500e5a60();
  local_40 = 0;
  local_38 = 0;
  local_50 = 0;
  uStack_68 = 0;
  local_70 = 0;
  uStack_58 = 0;
  uStack_60 = 0;
  if ((_gLogCategory_APTransportConnectionHTTP < 0x1f) &&
     ((_gLogCategory_APTransportConnectionHTTP != -1 ||
      (iVar1 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x200001e), iVar1 != 0))
     )) {
    _httpconnection_configureEncryptionInternal_cold_1(param_1);
  }
  lVar3 = func_0x0002500b5820(param_2);
  puVar8 = (undefined8 *)(*(long *)(lVar3 + 0x10) + 0x40);
  pcVar7 = (code *)*puVar8;
  if ((pcVar7 == (code *)0x0) || (pcVar7 == (code *)0x0)) {
    uVar4 = 0xffffce12;
  }
  else {
    uVar4 = (*pcVar7)((ulong)puVar8 & 0xffffffffffff | 0xa10b000000000000,param_2,param_3,0,
                      &local_38,0,&local_40);
    if ((int)uVar4 == 0) {
      lVar3 = func_0x000250090160(local_38);
      if (lVar3 < 0x20) {
        uVar4 = 0xfffee57e;
        _httpconnection_configureEncryptionInternal_cold_7();
        goto LAB_24fdc9a3c;
      }
      lVar3 = func_0x000250090160(local_40);
      if (lVar3 < 0x20) {
        uVar4 = 0xfffee57e;
        _httpconnection_configureEncryptionInternal_cold_6();
        goto LAB_24fdc9a3c;
      }
      if (*(char *)(lVar2 + 0x100) == '\0') {
        if (*(long *)(lVar2 + 0x108) == 0) {
          _httpconnection_configureEncryptionInternal_cold_5();
          goto LAB_24fdc9ab0;
        }
        uVar4 = func_0x000250090140(local_38);
        uVar5 = func_0x000250090140(local_40);
        uVar4 = func_0x0002500ef300(&local_70,&_gLogCategory_APTransportConnectionHTTP,uVar4,0,uVar5
                                    ,0);
        if ((int)uVar4 != 0) {
          _httpconnection_configureEncryptionInternal_cold_4(uVar4);
          goto LAB_24fdc9a3c;
        }
        local_c0 = _DAT_2681b4ed0;
        local_b8 = DAT_24fe44b40;
        local_b0 = &___httpconnection_configureEncryptionInternal_block_invoke_2;
        puStack_a8 = &___block_descriptor_tmp_118;
        local_a0 = lVar2;
      }
      else {
        if (*(long *)(lVar2 + 0x108) == 0) {
          _httpconnection_configureEncryptionInternal_cold_3();
LAB_24fdc9ab0:
          uVar4 = 0xfffee57f;
          goto LAB_24fdc9a3c;
        }
        uVar4 = func_0x000250090140(local_40);
        uVar5 = func_0x000250090140(local_38);
        uVar4 = func_0x0002500ef300(&local_70,&_gLogCategory_APTransportConnectionHTTP,uVar4,0,uVar5
                                    ,0);
        if ((int)uVar4 != 0) {
          _httpconnection_configureEncryptionInternal_cold_2(uVar4);
          goto LAB_24fdc9a3c;
        }
        local_98 = _DAT_2681b4ed0;
        local_90 = DAT_24fe44b40;
        local_88 = &___httpconnection_configureEncryptionInternal_block_invoke;
        puStack_80 = &___block_descriptor_tmp_117;
        puVar6 = &local_98;
        local_78 = lVar2;
      }
      _httpConnectionCapture_setEncryptionDelegate(param_1,&local_70,puVar6);
      goto LAB_24fdc9a3c;
    }
  }
  func_0x0002500ee220(uVar4,"httpconnection_configureEncryptionInternal",0x4a2,0);
LAB_24fdc9a3c:
  if (local_38 != 0) {
    func_0x0002500903d0();
  }
  if (local_40 != 0) {
    func_0x0002500903d0();
  }
  return uVar4;
}


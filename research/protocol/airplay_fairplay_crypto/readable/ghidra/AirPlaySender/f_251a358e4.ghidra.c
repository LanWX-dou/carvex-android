/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a358e4
 * original code SHA256: e5a835cb9eaa3ce17f83efcee88e83b87721ab2c4bcf61da5021b6bcd2c77571
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251a35ad4) */
/* WARNING: Removing unreachable block (ram,0x000251a35a60) */

undefined8
_coreUtilsKeyHolder_CreateEncryptionKeysForContext
          (undefined8 param_1,undefined8 param_2,long param_3,long *param_4,long param_5,
          long *param_6)

{
  long lVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  code *pcVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  char *pcVar11;
  char *pcVar12;
  char *local_98;
  long local_90;
  long local_88;
  undefined8 local_80;
  undefined8 local_78;
  long local_70;
  undefined8 local_68;
  
  local_90 = 0;
  local_88 = 0;
  lVar5 = 0x20;
  if (param_3 != 0) {
    lVar5 = param_3;
  }
  lVar1 = 0x20;
  if (param_5 != 0) {
    lVar1 = param_5;
  }
  lVar4 = func_0x000258102330(param_2,&cfstringStruct_27612c250,0);
  if (lVar4 == 0) {
    local_98 = "Control-Write-Encryption-Key";
    pcVar12 = "Control-Read-Encryption-Key";
    uVar9 = 0x1c;
    uVar8 = 0x1b;
    uVar10 = 0xc;
    pcVar11 = "Control-Salt";
  }
  else {
    lVar4 = func_0x000258102330(param_2,&cfstringStruct_27612c270,0);
    if (lVar4 != 0) {
      local_70 = 0;
      local_68 = 0;
      local_80 = 0;
      local_78 = 0;
      iVar3 = func_0x00025810e9f0(param_2,&local_68,&local_70,&local_78);
      if (iVar3 == 0) {
        iVar3 = func_0x00025810bb30(local_68,local_78,"DataStream(seed: %llu)");
        bVar2 = iVar3 != 1;
        uVar8 = 0;
        if (!bVar2) {
          uVar8 = local_80;
        }
      }
      else {
        _coreUtilsKeyHolder_CreateEncryptionKeysForContext_cold_1();
        bVar2 = true;
        uVar8 = 0;
      }
      if (local_70 != 0) {
        func_0x0002580f4d30();
      }
      if (bVar2) {
        uVar8 = 0xfffee7d7;
      }
      else {
        uVar8 = _coreUtilsKeyHolder_CreateEncryptionKeysForStream
                          (param_1,uVar8,lVar5,param_4,lVar1,param_6);
      }
      goto LAB_251a35b84;
    }
    local_98 = "Events-Write-Encryption-Key";
    pcVar12 = "Events-Read-Encryption-Key";
    uVar9 = 0x1b;
    uVar8 = 0x1a;
    uVar10 = 0xb;
    pcVar11 = "Events-Salt";
  }
  lVar4 = func_0x000258109150(param_1);
  puVar7 = (undefined8 *)(*(long *)(lVar4 + 0x10) + 0x30);
  pcVar6 = (code *)*puVar7;
  if ((pcVar6 == (code *)0x0) || (pcVar6 == (code *)0x0)) {
    uVar8 = 0xffffce12;
LAB_251a35b30:
    uVar9 = 0x167;
  }
  else {
    uVar8 = (*pcVar6)((ulong)puVar7 & 0xffffffffffff | 0xfe03000000000000,param_1,pcVar11,uVar10,
                      pcVar12,uVar8,lVar5,&local_88);
    if ((int)uVar8 != 0) goto LAB_251a35b30;
    lVar5 = func_0x000258109150(param_1);
    puVar7 = (undefined8 *)(*(long *)(lVar5 + 0x10) + 0x30);
    pcVar6 = (code *)*puVar7;
    if ((pcVar6 == (code *)0x0) || (pcVar6 == (code *)0x0)) {
      uVar8 = 0xffffce12;
    }
    else {
      uVar8 = (*pcVar6)((ulong)puVar7 & 0xffffffffffff | 0xfe03000000000000,param_1,pcVar11,uVar10,
                        local_98,uVar9,lVar1,&local_90);
      if ((int)uVar8 == 0) {
        if (param_4 != (long *)0x0) {
          *param_4 = local_88;
          local_88 = 0;
        }
        uVar8 = 0;
        if (param_6 != (long *)0x0) {
          *param_6 = local_90;
          local_90 = 0;
        }
        goto LAB_251a35b84;
      }
    }
    uVar9 = 0x16a;
  }
  func_0x000258109a30(uVar8,"coreUtilsKeyHolder_CreateEncryptionKeysForContext",uVar9,0);
LAB_251a35b84:
  if (local_88 != 0) {
    func_0x0002580f5830();
  }
  if (local_90 != 0) {
    func_0x0002580f5830();
  }
  return uVar8;
}


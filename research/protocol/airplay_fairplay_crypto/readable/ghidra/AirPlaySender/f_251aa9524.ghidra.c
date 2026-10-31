/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa9524
 * original code SHA256: 21ae6df569a7470626cb46e02a68eaea8aa8f790756d1ebcca3d2377e4f42c81
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251aa95bc) */

undefined8
_legacyKeyHolder_CreateEncryptedMasterAESKeyAndIV(undefined8 param_1,long *param_2,long *param_3)

{
  long lVar1;
  long lVar2;
  long lVar3;
  code *pcVar4;
  undefined8 *puVar5;
  long lVar6;
  undefined8 uVar7;
  long local_48;
  
  local_48 = 0;
  lVar1 = func_0x00025810ac50();
  lVar2 = func_0x0002580f6ff0(*(undefined8 *)(lVar1 + 0x30),lVar1 + 0x10,0x10);
  if (lVar2 == 0) {
    uVar7 = 0xfffee7d8;
    _legacyKeyHolder_CreateEncryptedMasterAESKeyAndIV_cold_2();
  }
  else {
    lVar6 = *(long *)(lVar1 + 8);
    if (lVar6 == 0) {
      lVar3 = 0;
      local_48 = lVar2;
    }
    else {
      uVar7 = *(undefined8 *)(lVar1 + 0x30);
      lVar3 = func_0x000258109150(lVar6);
      puVar5 = (undefined8 *)(*(long *)(lVar3 + 0x10) + 0x18);
      pcVar4 = (code *)*puVar5;
      lVar3 = lVar2;
      if ((pcVar4 != (code *)0x0) && (pcVar4 != (code *)0x0)) {
        (*pcVar4)((ulong)puVar5 & 0xffffffffffff | 0xa2e6000000000000,lVar6,lVar2,uVar7,&local_48);
      }
    }
    lVar1 = func_0x0002580f6ff0(*(undefined8 *)(lVar1 + 0x30),lVar1 + 0x20,0x10);
    if (lVar1 == 0) {
      uVar7 = 0xfffee7d8;
      _legacyKeyHolder_CreateEncryptedMasterAESKeyAndIV_cold_1();
    }
    else {
      uVar7 = 0;
      *param_2 = local_48;
      local_48 = 0;
      *param_3 = lVar1;
    }
    if (lVar3 != 0) {
      func_0x0002580f5830(lVar3);
    }
  }
  if (local_48 != 0) {
    func_0x0002580f5830();
  }
  return uVar7;
}


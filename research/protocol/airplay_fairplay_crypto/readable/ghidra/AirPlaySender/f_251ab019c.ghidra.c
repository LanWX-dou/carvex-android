/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ab019c
 * original code SHA256: a49f4c22929604e07411524f177821b0b961101bc25767e41eeaf9170008958c
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251ab0234) */

undefined8
_sharedKeyHolder_CreateEncryptedMasterAESKeyAndIV(undefined8 param_1,long *param_2,long *param_3)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  code *pcVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  long lVar7;
  long lVar8;
  long local_48;
  
  local_48 = 0;
  plVar1 = (long *)func_0x00025810ac50();
  lVar2 = func_0x0002580f6ff0(plVar1[5],plVar1 + 1,0x10);
  if (lVar2 == 0) {
    uVar6 = 0xfffee7d8;
    _sharedKeyHolder_CreateEncryptedMasterAESKeyAndIV_cold_2();
  }
  else {
    lVar7 = *plVar1;
    if (lVar7 == 0) {
      lVar3 = 0;
      local_48 = lVar2;
    }
    else {
      lVar8 = plVar1[5];
      lVar3 = func_0x000258109150(lVar7);
      puVar5 = (undefined8 *)(*(long *)(lVar3 + 0x10) + 0x18);
      pcVar4 = (code *)*puVar5;
      lVar3 = lVar2;
      if ((pcVar4 != (code *)0x0) && (pcVar4 != (code *)0x0)) {
        (*pcVar4)((ulong)puVar5 & 0xffffffffffff | 0xa2e6000000000000,lVar7,lVar2,lVar8,&local_48);
      }
    }
    lVar2 = func_0x0002580f6ff0(plVar1[5],plVar1 + 3,0x10);
    if (lVar2 == 0) {
      uVar6 = 0xfffee7d8;
      _sharedKeyHolder_CreateEncryptedMasterAESKeyAndIV_cold_1();
    }
    else {
      uVar6 = 0;
      *param_2 = local_48;
      local_48 = 0;
      *param_3 = lVar2;
    }
    if (lVar3 != 0) {
      func_0x0002580f5830(lVar3);
    }
  }
  if (local_48 != 0) {
    func_0x0002580f5830();
  }
  return uVar6;
}


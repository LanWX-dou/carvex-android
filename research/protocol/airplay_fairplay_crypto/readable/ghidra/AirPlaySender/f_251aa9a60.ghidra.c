/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa9a60
 * original code SHA256: b0b8a71eb94972043ac042cbe5d188e07b4c4566f0f79c777acf682c1b5542db
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _legacyKeyHolder_createDerivedKeyLegacy
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,long *param_4)

{
  bool bVar1;
  long lVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  undefined8 local_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_88;
  undefined8 uStack_80;
  long local_48;
  
  local_48 = *_DAT_2681b4ee0;
  lVar2 = func_0x00025810ac50();
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  uStack_e8 = 0;
  local_f0 = 0;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_108 = 0;
  local_110 = 0;
  uStack_f8 = 0;
  uStack_100 = 0;
  uStack_128 = 0;
  local_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_148 = 0;
  local_150 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_158 = 0;
  local_160 = 0;
  lVar3 = func_0x00025810e760(*(undefined8 *)(lVar2 + 0x30),0x10);
  if (lVar3 == 0) {
    _legacyKeyHolder_createDerivedKeyLegacy_cold_1();
    uVar5 = 0xfffee7d8;
  }
  else {
    func_0x00025810e790(lVar3,0x10);
    func_0x00025810e690(&local_160);
    func_0x00025810e6a0(&local_160,param_2,param_3);
    func_0x00025810e6a0(&local_160,lVar2 + 0x10,0x10);
    func_0x00025810e680(&local_88,&local_160);
    puVar4 = (undefined8 *)func_0x00025810e780(lVar3);
    puVar4[1] = uStack_80;
    *puVar4 = local_88;
    lVar2 = -0x40;
    puVar4 = &local_88;
    do {
      *(undefined1 *)puVar4 = 0;
      bVar1 = lVar2 != -1;
      lVar2 = lVar2 + 1;
      puVar4 = (undefined8 *)((long)puVar4 + 1);
    } while (bVar1);
    uVar5 = 0;
    *param_4 = lVar3;
  }
  if (*_DAT_2681b4ee0 == local_48) {
    return;
  }
  func_0x0002580f4380(uVar5);
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa98fc
 * original code SHA256: 23ee74228c1646cf7c90196f8b929fc51adec866187a5b3dc0381c5e7cac21f7
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251aa99b0) */

undefined8
_legacyKeyHolder_CreateDerivedKey
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,long *param_7)

{
  long *plVar1;
  long lVar2;
  undefined8 uVar3;
  long lVar4;
  code *pcVar5;
  undefined8 *puVar6;
  long lVar7;
  
  plVar1 = (long *)func_0x00025810ac50();
  lVar2 = func_0x00025810e760(plVar1[6],param_6);
  if (lVar2 == 0) {
    _legacyKeyHolder_CreateDerivedKey_cold_2();
    return 0xfffee7d8;
  }
  func_0x00025810e790(lVar2,param_6);
  lVar7 = *plVar1;
  if (lVar7 == 0) {
    uVar3 = 0xfffee7d7;
    _legacyKeyHolder_CreateDerivedKey_cold_1();
  }
  else {
    uVar3 = func_0x00025810e780(lVar2);
    lVar4 = func_0x000258109150(lVar7);
    puVar6 = (undefined8 *)(*(long *)(lVar4 + 0x10) + 8);
    pcVar5 = (code *)*puVar6;
    if ((pcVar5 == (code *)0x0) || (pcVar5 == (code *)0x0)) {
      uVar3 = 0xffffce12;
    }
    else {
      uVar3 = (*pcVar5)((ulong)puVar6 & 0xffffffffffff | 0x2d6f000000000000,lVar7,param_2,param_3,
                        param_4,param_5,param_6,uVar3);
      if ((int)uVar3 == 0) {
        uVar3 = 0;
        if (param_7 != (long *)0x0) {
          *param_7 = lVar2;
          return 0;
        }
        goto LAB_251aa9a0c;
      }
    }
    func_0x000258109a30(uVar3,"legacyKeyHolder_CreateDerivedKey",0x167,0);
  }
LAB_251aa9a0c:
  func_0x0002580f5830(lVar2);
  return uVar3;
}


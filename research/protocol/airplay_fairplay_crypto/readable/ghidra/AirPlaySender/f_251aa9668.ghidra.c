/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa9668
 * original code SHA256: 306311dd919e85e0c57365e5c70084ecbbce4b7a593d7b61b94a9f751a678d6d
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251aa9734) */
/* WARNING: Removing unreachable block (ram,0x000251aa96cc) */

undefined8 _legacyKeyHolder_UpdateMasterAESKeyAfterSharing(void)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  undefined8 uVar4;
  code *pcVar5;
  undefined8 *puVar6;
  long lVar7;
  
  plVar2 = (long *)func_0x00025810ac50();
  lVar7 = plVar2[1];
  if (lVar7 != 0) {
    lVar3 = func_0x000258109150(lVar7);
    puVar6 = (undefined8 *)(*(long *)(lVar3 + 0x10) + 8);
    pcVar5 = (code *)*puVar6;
    if ((((pcVar5 != (code *)0x0) && (pcVar5 != (code *)0x0)) &&
        (iVar1 = (*pcVar5)((ulong)puVar6 & 0xffffffffffff | 0xd6e6000000000000,lVar7), iVar1 == 4))
       && (lVar7 = *plVar2, lVar7 != 0)) {
      lVar3 = func_0x000258109150(lVar7);
      puVar6 = (undefined8 *)(*(long *)(lVar3 + 0x10) + 8);
      pcVar5 = (code *)*puVar6;
      if ((pcVar5 == (code *)0x0) || (pcVar5 == (code *)0x0)) {
        uVar4 = 0xffffce12;
      }
      else {
        uVar4 = (*pcVar5)((ulong)puVar6 & 0xffffffffffff | 0x2d6f000000000000,lVar7,plVar2 + 2,0x10,
                          0,0,0x10,plVar2 + 2);
        if ((int)uVar4 == 0) {
          return uVar4;
        }
      }
      func_0x000258109a30(uVar4,"legacyKeyHolder_UpdateMasterAESKeyAfterSharing",0x14a,0);
      return uVar4;
    }
  }
  return 0;
}


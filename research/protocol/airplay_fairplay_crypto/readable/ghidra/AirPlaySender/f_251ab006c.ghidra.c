/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ab006c
 * original code SHA256: 2ea17e4c0c96282d92fd1ae742861e5e9bc0f8de2d0e11932ecd87df34d9114a
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251ab00cc) */

undefined8 _sharedKeyHolder_GetAuthenticationType(void)

{
  long *plVar1;
  long lVar2;
  undefined8 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar4;
  long lVar5;
  ulong unaff_x30;
  
  plVar1 = (long *)func_0x00025810ac50();
  lVar5 = *plVar1;
  if (lVar5 != 0) {
    lVar2 = func_0x000258109150(lVar5);
    puVar4 = (undefined8 *)(*(long *)(lVar2 + 0x10) + 8);
    UNRECOVERED_JUMPTABLE = (code *)*puVar4;
    if ((UNRECOVERED_JUMPTABLE != (code *)0x0) && (UNRECOVERED_JUMPTABLE != (code *)0x0)) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x000251ab00f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = (*UNRECOVERED_JUMPTABLE)(lVar5,(ulong)puVar4 & 0xffffffffffff | 0xd6e6000000000000);
        return uVar3;
      }
                    /* WARNING: Does not return */
      UNRECOVERED_JUMPTABLE = (code *)SoftwareBreakpoint(0xc471,0x251ab00f4);
      (*UNRECOVERED_JUMPTABLE)();
    }
  }
  return 0;
}


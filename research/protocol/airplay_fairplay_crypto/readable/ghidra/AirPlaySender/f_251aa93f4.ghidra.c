/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa93f4
 * original code SHA256: 4f10361b7a3671001699a60726446737970bf130d826b52c597bbbff5edfde70
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251aa9454) */

undefined8 _legacyKeyHolder_GetAuthenticationType(void)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar4;
  ulong unaff_x30;
  
  lVar1 = func_0x00025810ac50();
  lVar1 = *(long *)(lVar1 + 8);
  if (lVar1 != 0) {
    lVar2 = func_0x000258109150(lVar1);
    puVar4 = (undefined8 *)(*(long *)(lVar2 + 0x10) + 8);
    UNRECOVERED_JUMPTABLE = (code *)*puVar4;
    if ((UNRECOVERED_JUMPTABLE != (code *)0x0) && (UNRECOVERED_JUMPTABLE != (code *)0x0)) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x000251aa947c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = (*UNRECOVERED_JUMPTABLE)(lVar1,(ulong)puVar4 & 0xffffffffffff | 0xd6e6000000000000);
        return uVar3;
      }
                    /* WARNING: Does not return */
      UNRECOVERED_JUMPTABLE = (code *)SoftwareBreakpoint(0xc471,0x251aa947c);
      (*UNRECOVERED_JUMPTABLE)();
    }
  }
  return 0;
}


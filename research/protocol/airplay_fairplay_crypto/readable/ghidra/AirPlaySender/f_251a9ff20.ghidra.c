/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a9ff20
 * original code SHA256: 34a41c73e67d0230391e3f8663689a8eb96a07d6f6137e812383d8c93219e2c9
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251a9ff74) */

undefined8 _APSKeyHolderGetAuthenticationType(undefined8 param_1)

{
  long lVar1;
  undefined8 uVar2;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar3;
  ulong unaff_x30;
  
  lVar1 = func_0x000258109150();
  puVar3 = (undefined8 *)(*(long *)(lVar1 + 0x10) + 8);
  UNRECOVERED_JUMPTABLE = (code *)*puVar3;
  if ((UNRECOVERED_JUMPTABLE != (code *)0x0) && (UNRECOVERED_JUMPTABLE != (code *)0x0)) {
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x000251a9ff9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (*UNRECOVERED_JUMPTABLE)(param_1,(ulong)puVar3 & 0xffffffffffff | 0x36eb000000000000);
      return uVar2;
    }
                    /* WARNING: Does not return */
    UNRECOVERED_JUMPTABLE = (code *)SoftwareBreakpoint(0xc471,0x251a9ff9c);
    (*UNRECOVERED_JUMPTABLE)();
  }
  return 0;
}


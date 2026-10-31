/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a52a68
 * original code SHA256: 298997476984d0b18fe204ced881c441b44ce25c192de79f97e5c8f65068d93d
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251a52acc) */

undefined8
_APSenderSessionCreateTransportStreamWithID
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  long lVar1;
  undefined8 uVar2;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar3;
  ulong unaff_x30;
  
  lVar1 = func_0x000258109150();
  puVar3 = (undefined8 *)(*(long *)(lVar1 + 0x10) + 0x40);
  UNRECOVERED_JUMPTABLE = (code *)*puVar3;
  if ((UNRECOVERED_JUMPTABLE != (code *)0x0) && (UNRECOVERED_JUMPTABLE != (code *)0x0)) {
    if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) == 0) {
                    /* WARNING: Could not recover jumptable at 0x000251a52b04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (*UNRECOVERED_JUMPTABLE)
                        (param_1,param_2,param_3,param_4,
                         (ulong)puVar3 & 0xffffffffffff | 0xb90f000000000000);
      return uVar2;
    }
                    /* WARNING: Does not return */
    UNRECOVERED_JUMPTABLE = (code *)SoftwareBreakpoint(0xc471,0x251a52b04);
    (*UNRECOVERED_JUMPTABLE)();
  }
  return 0xffffce12;
}


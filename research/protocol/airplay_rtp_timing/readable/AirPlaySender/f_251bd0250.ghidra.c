/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251bd0250
 * original code SHA256: 41625f04b82c232d659bff3651d271efef02c56a965d7b8d92c05483cc807f34
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _endpoint_getCurrentRTPTime(long *param_1)

{
  long *plVar1;
  code *pcVar2;
  long lVar3;
  undefined8 uVar4;
  ulong unaff_x30;
  long lVar5;
  undefined1 auStack_24 [4];
  
  lVar3 = func_0x00025810ac50();
  plVar1 = _DAT_2680d46b8;
  lVar5 = *_DAT_2680d46b8;
  param_1[1] = _DAT_2680d46b8[1];
  *param_1 = lVar5;
  param_1[2] = plVar1[2];
  func_0x00025810b430(*(undefined8 *)(lVar3 + 0x78));
  if (*(int *)(lVar3 + 0x98) == 2) {
    uVar4 = func_0x000258102680(*(undefined8 *)(lVar3 + 0xa8),*_DAT_2680d57e0);
    _endpoint_getCurrentRTPTimeFromStream(param_1,uVar4,auStack_24);
    if (*param_1 == 0) {
      _OUTLINED_FUNCTION_35(*(undefined8 *)(lVar3 + 0xa8));
      uVar4 = func_0x000258102680();
      _endpoint_getCurrentRTPTimeFromStream(param_1,uVar4,auStack_24);
    }
  }
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(0xc471,0x251bd02fc);
    (*pcVar2)();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


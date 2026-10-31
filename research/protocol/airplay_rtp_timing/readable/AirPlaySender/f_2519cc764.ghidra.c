/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519cc764
 * original code SHA256: 63841b451cbae71a5dce6897869688578c8f68fc4ae70873b49e3657a0842873
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_jitterBuffer_CopyProperty(undefined8 param_1,undefined8 param_2,undefined8 param_3,long *param_4)

{
  undefined8 *puVar1;
  code *pcVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  ulong unaff_x30;
  
  lVar4 = func_0x00025810ac50();
  iVar3 = func_0x000258101830(param_2,&cfstringStruct_27613e290);
  if (iVar3 == 0) {
    iVar3 = func_0x000258101830(param_2,*_DAT_2680d4870);
    if (iVar3 == 0) {
      iVar3 = func_0x000258101830(param_2,*_DAT_2680d4878);
      if (iVar3 == 0) {
        uVar5 = 0xffffce10;
      }
      else {
        puVar1 = _DAT_2680d3188;
        if (*(char *)(lVar4 + 0x70) != '\0') {
          puVar1 = _DAT_2680d3198;
        }
        lVar4 = func_0x0002580f6a60(*puVar1);
        uVar5 = 0;
        *param_4 = lVar4;
      }
    }
    else {
      lVar4 = func_0x0002580f7010(param_3,3,lVar4 + 0x10);
      *param_4 = lVar4;
      if (lVar4 == 0) {
        _jitterBuffer_CopyProperty_cold_2();
        uVar5 = 0xffffbe6a;
      }
      else {
        uVar5 = 0;
      }
    }
  }
  else {
    if (*(long *)(lVar4 + 8) != 0) {
      if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
        pcVar2 = (code *)SoftwareBreakpoint(0xc471,0x2519cc7c8);
        (*pcVar2)();
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    _jitterBuffer_CopyProperty_cold_1();
    uVar5 = 0xffffbe67;
  }
  return uVar5;
}


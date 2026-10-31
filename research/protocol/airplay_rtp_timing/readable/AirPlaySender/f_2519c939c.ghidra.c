/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519c939c
 * original code SHA256: a8a6e13739871232b16be967c714b96079b2215c66f5f6de01035e110c00ea61
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _jitterBuffer_SetProperty(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  int local_34;
  
  local_34 = 0;
  lVar3 = func_0x00025810ac50();
  iVar1 = func_0x000258101830(param_2,*_DAT_2680d4870);
  if (iVar1 == 0) {
    iVar1 = func_0x000258101830(param_2,*_DAT_2680d4878);
    if (iVar1 == 0) {
      local_34 = -0x31f0;
    }
    else {
      lVar4 = func_0x00025810a7d0(param_3,&local_34);
      *(bool *)(lVar3 + 0x70) = lVar4 != 0;
      if (local_34 != 0) {
        _jitterBuffer_SetProperty_cold_2();
      }
    }
  }
  else {
    uVar2 = func_0x00025810a7d0(param_3,&local_34);
    *(undefined4 *)(lVar3 + 0x10) = uVar2;
    if (local_34 != 0) {
      _jitterBuffer_SetProperty_cold_1();
    }
  }
  return local_34;
}


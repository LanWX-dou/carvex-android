/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ab1780
 * original code SHA256: ce620776ad97f9d29396fd81c11a4a8312f77e6224e1a6dc3762bc6e534ad409
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_APSenderSessionCreateStreamDescriptor(int param_1,int param_2,undefined8 param_3,long *param_4)

{
  long lVar1;
  
  if (param_1 == 0) {
    lVar1 = 0;
  }
  else {
    lVar1 = func_0x000258101820(*_DAT_2680d3150,0,_DAT_2680d3340,_DAT_2680d3358);
    if (lVar1 == 0) {
      _APSenderSessionCreateStreamDescriptor_cold_1();
      return 0xffffe5b8;
    }
    func_0x00025810a790(lVar1,&cfstringStruct_27612fb30,param_1);
    if (param_2 != 0) {
      func_0x00025810a790(lVar1,&cfstringStruct_276132150,param_3);
    }
  }
  *param_4 = lVar1;
  return 0;
}


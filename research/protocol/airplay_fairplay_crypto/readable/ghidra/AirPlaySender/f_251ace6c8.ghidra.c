/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ace6c8
 * original code SHA256: b598e754160772f3b879f47a95419919fdf6abc342e9ebd03977060c970cd24f
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _fpAuthentication_CopyDebugDescription(void)

{
  undefined8 uVar1;
  
  uVar1 = func_0x00025810aa90(*_DAT_2680d3150,0);
  func_0x00025810aa50(uVar1,0,&cfstringStruct_276139050);
  return uVar1;
}


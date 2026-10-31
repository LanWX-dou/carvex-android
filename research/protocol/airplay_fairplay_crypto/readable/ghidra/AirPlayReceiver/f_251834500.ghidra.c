/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251834500
 * original code SHA256: 10a6a5f52685065270813e80d6e26d1e0dbdb23cfe2a13c931015a50747c1100
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251834548) */
/* WARNING: Removing unreachable block (ram,0x000251834570) */
/* WARNING: Removing unreachable block (ram,0x0002518345c0) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoDictionary(void)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 *in_x3;
  
  if (in_x3 == (undefined8 *)0x0) {
    func_0x000258109a30(0,"APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoDictionary",0x139);
    uVar2 = 0;
  }
  else {
    uVar2 = _apReceiverFairPlayHelper_CopyPICResponseData();
    if ((int)uVar2 == 0) {
      lVar3 = func_0x000258101860(*_DAT_2680d3150,&_gFairPlayPlayerGUID,0x8000100);
      func_0x000258101810(*in_x3,&cfstringStruct_27610f070,lVar3);
      if (lVar3 != 0) {
        func_0x0002580f5830(lVar3);
      }
      return 0;
    }
    func_0x000258109a30(uVar2,"APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoDictionary",
                        0x13c,0);
    uVar2 = 0xfffee706;
  }
  if ((_gLogCategory_APReceiverFairPlayHelper < 0x5b) &&
     ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
      (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200005a), iVar1 != 0)))
     ) {
    func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                        "APSTransportMessageProcessingStatus APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoDictionary(APReceiverFairPlayHelperRef, CFDictionaryRef, CFStringRef, CFMutableDictionaryRef *)"
                        ,0x200005a,"### Authorize transport failed: %#m\n");
  }
  return uVar2;
}


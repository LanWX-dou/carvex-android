/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251833a74
 * original code SHA256: 0ade0a4ea13fcda20dfa41276fffb3e0abc993ae4e52f708b8822b213c99e94f
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoBuffer(void)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 in_x3;
  undefined8 in_x4;
  ulong *in_x5;
  long local_48;
  undefined8 local_40;
  long local_38;
  
  local_38 = 0;
  local_48 = 0;
  local_40 = 0;
  uVar3 = _apReceiverFairPlayHelper_CopyPICResponseData();
  if ((int)uVar3 == 0) {
    if (local_38 == 0) {
      uVar1 = func_0x0002580f6900(in_x3,in_x4,"%s:\n%s: %s\n");
      if ((0 < (int)uVar1) && ((int)uVar1 < (int)in_x4)) {
LAB_251833b78:
        uVar3 = 0;
        if (in_x5 != (ulong *)0x0) {
          *in_x5 = (ulong)uVar1;
        }
        goto LAB_251833b88;
      }
      uVar4 = 0x114;
    }
    else {
      uVar4 = func_0x00025810a3a0(local_38,local_40,0,&local_48,0);
      if ((int)uVar4 != 0) {
        uVar3 = 0xfffee702;
        func_0x000258109a30(uVar4,"APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoBuffer",0xf7
                            ,0);
        goto LAB_251833c28;
      }
      uVar1 = func_0x0002580f6900(in_x3,in_x4,"%s: %s\n%s: %s\n");
      if ((0 < (int)uVar1) && ((int)uVar1 < (int)in_x4)) goto LAB_251833b78;
      uVar4 = 0x108;
    }
    uVar3 = 0xfffee702;
    func_0x000258109a30(0,"APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoBuffer",uVar4,0);
  }
  else {
    func_0x000258109a30(uVar3,"APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoBuffer",0xef,0);
    uVar3 = 0xfffee706;
  }
LAB_251833c28:
  if ((_gLogCategory_APReceiverFairPlayHelper < 0x5b) &&
     ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
      (iVar2 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200005a), iVar2 != 0)))
     ) {
    func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                        "APSTransportMessageProcessingStatus APReceiverFairPlayHelperCopyAuthorizeItemResponseIntoBuffer(APReceiverFairPlayHelperRef, CFDictionaryRef, CFStringRef, uint8_t *, size_t, size_t *)"
                        ,0x200005a,"### Authorize transport failed: %#m\n");
  }
LAB_251833b88:
  if (local_38 != 0) {
    _jEHf8Xzsv8K();
  }
  if (local_48 != 0) {
    func_0x0002580f4d30();
  }
  return uVar3;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251834678
 * original code SHA256: f1835e1a8f83eb50a6ee0033baa5da07af9e86100599d2e35ba15873b0bac130
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_APReceiverFairPlayHelperProcessFPInfo(long param_1,undefined8 param_2,undefined8 *param_3)

{
  bool bVar1;
  cfstringStruct *pcVar2;
  int iVar3;
  undefined8 uVar4;
  cfstringStruct *pcVar5;
  long lVar6;
  undefined8 uVar7;
  long lVar8;
  long lVar9;
  char *pcVar10;
  undefined4 local_6c;
  undefined8 local_68;
  
  uVar4 = func_0x0002581018a0();
  pcVar5 = (cfstringStruct *)func_0x00025810a710(param_2,&cfstringStruct_27610f110,uVar4,0);
  pcVar2 = &cfstringStruct_27610f130;
  if (pcVar5 != (cfstringStruct *)0x0) {
    pcVar2 = pcVar5;
  }
  if (*(long *)(param_1 + 0x10) == 0) {
    bVar1 = false;
    lVar9 = -1;
  }
  else {
    lVar6 = func_0x0002581017d0();
    lVar9 = lVar6 + -1;
    if (lVar6 < 1) {
      bVar1 = false;
    }
    else {
      do {
        lVar6 = lVar6 + -1;
        uVar4 = func_0x0002581017e0(*(undefined8 *)(param_1 + 0x10),lVar6);
        uVar7 = func_0x0002581018a0();
        lVar8 = func_0x00025810a710(uVar4,&cfstringStruct_27610f110,uVar7,0);
        if ((lVar8 != 0) && (iVar3 = func_0x000258101830(lVar8,pcVar2), iVar3 != 0)) {
          lVar6 = func_0x00025810a6f0(uVar4,&cfstringStruct_27610f030,0);
          if (lVar6 != 0) goto LAB_251834878;
          break;
        }
      } while (0 < lVar6);
      bVar1 = true;
    }
  }
  if ((_gLogCategory_APReceiverFairPlayHelper < 0x15) &&
     ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
      (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x2000014), iVar3 != 0)))
     ) {
    func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                        "OSStatus apReceiverFairPlayHelper_AddFPSessionInfo(APReceiverFairPlayHelperRef, CFMutableDictionaryRef, uint64_t *)"
                        ,0x2000014,"Searching for fallback FP session for %@\n");
  }
  if (bVar1) {
    do {
      uVar4 = func_0x0002581017e0(*(undefined8 *)(param_1 + 0x10),lVar9);
      uVar7 = func_0x0002581018a0();
      lVar6 = func_0x00025810a710(uVar4,&cfstringStruct_27610f110,uVar7,0);
      if ((lVar6 != 0) && (iVar3 = func_0x000258101830(lVar6,&cfstringStruct_27610f130), iVar3 != 0)
         ) {
        lVar6 = func_0x00025810a6f0(uVar4,&cfstringStruct_27610f030,0);
        if (lVar6 != 0) goto LAB_251834878;
        break;
      }
      bVar1 = 0 < lVar9;
      lVar9 = lVar9 + -1;
    } while (bVar1);
  }
  if ((_gLogCategory_APReceiverFairPlayHelper < 0x15) &&
     ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
      (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x2000014), iVar3 != 0)))
     ) {
    func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                        "OSStatus apReceiverFairPlayHelper_AddFPSessionInfo(APReceiverFairPlayHelperRef, CFMutableDictionaryRef, uint64_t *)"
                        ,0x2000014,"FP session for %@ not found\n");
  }
  lVar6 = 0;
LAB_251834908:
  uVar4 = func_0x0002581064c0();
  lVar9 = func_0x00025810a710(param_2,&cfstringStruct_27610f090,uVar4,0);
  if (lVar9 == 0) {
    uVar4 = func_0x0002581064c0();
    lVar9 = func_0x00025810a710(param_2,&cfstringStruct_27610f0b0,uVar4,0);
    if (lVar9 == 0) {
      uVar4 = 0;
      pcVar10 = "(N-D)";
    }
    else {
      local_68 = 0;
      local_6c = 0;
      lVar8 = func_0x0002580f6a40();
      pcVar10 = "(C-Cloud-D)";
      if (lVar8 != 0) {
        pcVar10 = "(NC-Cloud-D)";
      }
      if (lVar6 == 0) {
        func_0x000258109a30(0,"APReceiverFairPlayHelperProcessFPInfo",0x17a,0);
        uVar4 = 0xffffe590;
      }
      else {
        uVar4 = func_0x0002580f6a30(lVar9);
        uVar4 = _nXJ7Amk1zyK93(lVar6,uVar4,lVar8,&local_68,&local_6c);
        if ((int)uVar4 == 0) {
          uVar4 = func_0x00025810a770(param_2,&cfstringStruct_27610f0d0,local_68,local_6c);
          _jEHf8Xzsv8K(local_68);
          if ((int)uVar4 == 0) {
            func_0x00025810a750(param_2,&cfstringStruct_27610f0b0);
            goto LAB_251834a08;
          }
          uVar7 = 0x180;
        }
        else {
          uVar7 = 0x17c;
        }
        func_0x000258109a30(uVar4,"APReceiverFairPlayHelperProcessFPInfo",uVar7,0);
      }
      if ((_gLogCategory_APReceiverFairPlayHelper < 0x5b) &&
         ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
          (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200005a),
          iVar3 != 0)))) {
        func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                            "OSStatus APReceiverFairPlayHelperProcessFPInfo(APReceiverFairPlayHelperRef, CFMutableDictionaryRef, const char **)"
                            ,0x200005a,"### FP-Info failed: %#m\n");
      }
    }
  }
  else {
    lVar9 = func_0x0002580f6a40();
    uVar4 = 0;
    pcVar10 = "(C-D)";
    if (lVar9 != 0) {
      pcVar10 = "(NC-D)";
    }
  }
LAB_251834a08:
  if (param_3 != (undefined8 *)0x0) {
    *param_3 = pcVar10;
  }
  return uVar4;
LAB_251834878:
  if ((_gLogCategory_APReceiverFairPlayHelper < 0x1f) &&
     ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
      (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200001e), iVar3 != 0)))
     ) {
    func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                        "OSStatus apReceiverFairPlayHelper_AddFPSessionInfo(APReceiverFairPlayHelperRef, CFMutableDictionaryRef, uint64_t *)"
                        ,0x200001e,"Using FP session ID %llu for %@\n");
  }
  func_0x00025810a790(param_2,&cfstringStruct_27610f150,lVar6);
  goto LAB_251834908;
}


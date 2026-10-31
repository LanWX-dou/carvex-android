/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251833c88
 * original code SHA256: 8836cd128c6b79e42000d833d2a089827238b48d047ba782fbbbc6a9e44806dc
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_apReceiverFairPlayHelper_CopyPICResponseData
          (long param_1,undefined8 param_2,long param_3,long *param_4,ulong *param_5)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  ulong uVar10;
  long *plVar11;
  long local_e0;
  char *local_a8;
  uint local_9c;
  long local_98;
  long local_90;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  long local_70;
  
  local_70 = *_DAT_2681b4ee0;
  local_a8 = (char *)0x0;
  lVar5 = 0;
  if (param_3 == 0) {
LAB_251833cf8:
    local_90 = 0;
    local_88 = 0;
    local_98 = 0;
    lVar6 = func_0x000258102680(param_2,&cfstringStruct_27610f170);
    if (lVar6 == 0) {
      lVar8 = 0;
      lVar7 = 0;
    }
    else {
      func_0x0002580f6a60();
      lVar7 = func_0x0002580f6a50(lVar6);
      lVar8 = func_0x0002581018a0();
      if (lVar7 == lVar8) {
        uVar4 = func_0x00025810aa60(lVar6,&local_88);
        if ((int)uVar4 == 0) {
          uVar4 = func_0x000258101890(lVar6);
          uVar4 = func_0x00025810a390(local_88,uVar4,&local_90,&local_98);
          lVar7 = local_90;
          lVar8 = local_98;
          if ((int)uVar4 == 0) goto LAB_251833dd8;
          uVar9 = 0x287;
        }
        else {
          uVar9 = 0x284;
        }
        func_0x000258109a30(uVar4,"apReceiverFairPlayHelper_CopyPICRequest",uVar9,0);
        if ((_gLogCategory_APReceiverFairPlayHelper < 0x5b) &&
           ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
            (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200005a),
            iVar3 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                              "OSStatus apReceiverFairPlayHelper_CopyPICRequest(CFDictionaryRef, uint8_t **, size_t *)"
                              ,0x200005a,"### Copy PIC Request failed: %#m\n");
        }
        lVar7 = 0;
        lVar8 = 0;
      }
      else {
        lVar7 = func_0x0002580f6a50(lVar6);
        lVar8 = func_0x0002581064c0();
        if (lVar7 == lVar8) {
          lVar8 = func_0x0002580f6a40(lVar6);
          local_98 = lVar8;
          lVar7 = func_0x0002580f6290(lVar8,0x100004077774924);
          local_90 = lVar7;
          func_0x000258101800(lVar6,0,lVar8,lVar7);
        }
        else {
          lVar7 = 0;
          lVar8 = 0;
        }
        uVar4 = 0;
      }
LAB_251833dd8:
      func_0x0002580f5830(lVar6);
      if (local_88 != 0) {
        func_0x0002580f4d30();
      }
      if ((int)uVar4 != 0) {
        func_0x000258109a30(uVar4,"apReceiverFairPlayHelper_CopyPICResponseData",0x2c5,0);
        goto LAB_251834400;
      }
    }
    pcVar2 = local_a8;
    local_98 = 0;
    local_90 = 0;
    local_9c = 0;
    plVar11 = (long *)(param_1 + 0x10);
    if ((*plVar11 == 0) || (lVar6 = func_0x0002581017d0(), lVar6 < 10)) {
      local_e0 = 0;
    }
    else {
      local_e0 = func_0x0002581017e0(*plVar11,0);
      lVar6 = func_0x00025810a6f0(local_e0,&cfstringStruct_27610f030,0);
      if ((_gLogCategory_APReceiverFairPlayHelper < 0x1f) &&
         ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
          (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200001e),
          iVar3 != 0)))) {
        func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                            "OSStatus apReceiverFairPlayHelper_SetupFPSession(APReceiverFairPlayHelperRef, const char *, size_t, uint8_t *, size_t, uint8_t **, size_t *)"
                            ,0x200001e,"Delete oldest FP session ID %llu\n");
      }
      if (lVar6 != 0) {
        _h5eRUOOOhxuaBmELCqQZZEcx(lVar6);
      }
      func_0x000258102610(*plVar11,0);
      local_90 = 0;
    }
    lVar6 = 10;
    do {
      iVar3 = _df35957c4e0(_gFairPlayContextID);
      if (iVar3 == 0) {
        uVar4 = _woqRTqq9PL5McfBs891(_gFairPlayContextID,lVar7,lVar8,&local_98,&local_9c,&local_90);
        iVar3 = (int)uVar4;
        if (iVar3 != -0xa430 && iVar3 != -0xa4c4) goto joined_r0x000251834214;
      }
      local_88 = 0;
      uStack_80 = 0;
      local_78 = 0;
      if ((_gLogCategory_APReceiverFairPlayHelper < 0x29) &&
         ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
          (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x2000028),
          iVar3 != 0)))) {
        func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                            "OSStatus apReceiverFairPlayHelper_SetupFPSession(APReceiverFairPlayHelperRef, const char *, size_t, uint8_t *, size_t, uint8_t **, size_t *)"
                            ,0x2000028,"### Re-initing FP\n");
      }
      uVar4 = _zxcm2Qme0x(0,0,&local_88);
      if ((int)uVar4 == 0) {
        func_0x00025810aee0((long)&local_88 + 4,local_88 & 0xffffffff,&_gFairPlayPlayerGUID,
                            "0123456789abcdef");
        uVar4 = _XtCqEf5X(0,&local_88,"/var/mobile/Media/iTunes_Control/iTunes/AirTunes/",
                          &_gFairPlayContextID);
        if ((_gLogCategory_APReceiverFairPlayHelper < 0x33) &&
           ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
            (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x2000032),
            iVar3 != 0)))) {
          func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                              "OSStatus apReceiverFairPlayHelper_SetupFPSession(APReceiverFairPlayHelperRef, const char *, size_t, uint8_t *, size_t, uint8_t **, size_t *)"
                              ,0x2000032,"Re-init FP: %#m\n");
        }
        if ((int)uVar4 != 0) goto LAB_251834014;
      }
      else {
LAB_251834014:
        func_0x000258101780(200000);
      }
      lVar6 = lVar6 + -1;
    } while (lVar6 != 0);
    iVar3 = (int)uVar4;
joined_r0x000251834214:
    if (iVar3 == 0) {
      local_e0 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
      if (local_e0 != 0) {
        lVar6 = 0x24;
        if (lVar5 != 0 && pcVar2 != (char *)0x0) {
          lVar6 = lVar5;
        }
        pcVar1 = "00000000-0000-0000-0000-000000000000";
        if (lVar5 != 0 && pcVar2 != (char *)0x0) {
          pcVar1 = pcVar2;
        }
        func_0x00025810a760(local_e0,&cfstringStruct_27610f110,pcVar1,lVar6);
        func_0x00025810a790(local_e0,&cfstringStruct_27610f030,local_90);
        uVar4 = func_0x00025810a590(plVar11,local_e0);
        if ((int)uVar4 == 0) {
          if (_gLogCategory_APReceiverFairPlayHelper < 0x1f) {
            if ((_gLogCategory_APReceiverFairPlayHelper != -1) ||
               (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200001e),
               iVar3 != 0)) {
              func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                                  "OSStatus apReceiverFairPlayHelper_SetupFPSession(APReceiverFairPlayHelperRef, const char *, size_t, uint8_t *, size_t, uint8_t **, size_t *)"
                                  ,0x200001e,"Created FP session ID %llu for %.*s\n");
            }
            local_90 = 0;
            if ((_gLogCategory_APReceiverFairPlayHelper < 0xb) &&
               (((_gLogCategory_APReceiverFairPlayHelper != -1 ||
                 (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,10),
                 iVar3 != 0)) && (lVar5 = func_0x0002581017d0(*plVar11), 0 < lVar5)))) {
              lVar6 = 0;
              do {
                local_e0 = func_0x0002581017e0(*plVar11,lVar6);
                if ((_gLogCategory_APReceiverFairPlayHelper < 0xb) &&
                   ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
                    (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200000a),
                    iVar3 != 0)))) {
                  func_0x000258102680(local_e0,&cfstringStruct_27610f110);
                  func_0x000258102680(local_e0,&cfstringStruct_27610f030);
                  func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                                      "OSStatus apReceiverFairPlayHelper_SetupFPSession(APReceiverFairPlayHelperRef, const char *, size_t, uint8_t *, size_t, uint8_t **, size_t *)"
                                      ,0x200000a,"Cached FP Session %2d of %2d: %@: %@\n");
                }
                lVar6 = lVar6 + 1;
              } while (lVar5 != lVar6);
            }
          }
          else {
            local_90 = 0;
          }
          lVar5 = local_98;
          uVar4 = 0;
          uVar10 = (ulong)local_9c;
          local_98 = 0;
          goto LAB_251834264;
        }
        func_0x000258109a30(uVar4,"apReceiverFairPlayHelper_SetupFPSession",0x20f,0);
        lVar5 = 0;
        uVar10 = 0;
        goto LAB_251834268;
      }
      func_0x000258109a30(0,"apReceiverFairPlayHelper_SetupFPSession",0x205,0);
      lVar5 = 0;
      uVar10 = 0;
      uVar4 = 0xffffe5b8;
LAB_251834274:
      if ((_gLogCategory_APReceiverFairPlayHelper < 0x5b) &&
         ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
          (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200005a),
          iVar3 != 0)))) {
        func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                            "OSStatus apReceiverFairPlayHelper_SetupFPSession(APReceiverFairPlayHelperRef, const char *, size_t, uint8_t *, size_t, uint8_t **, size_t *)"
                            ,0x200005a,"### Authorize setup failed: %#m\n");
      }
    }
    else {
      func_0x000258109a30(uVar4,"apReceiverFairPlayHelper_SetupFPSession",0x200,0);
      lVar5 = 0;
      uVar10 = 0;
LAB_251834264:
      if (local_e0 != 0) {
LAB_251834268:
        func_0x0002580f5830(local_e0);
      }
      if ((int)uVar4 != 0) goto LAB_251834274;
    }
    if (local_98 != 0) {
      _jEHf8Xzsv8K();
    }
    if (local_90 != 0) {
      _h5eRUOOOhxuaBmELCqQZZEcx();
    }
    if ((int)uVar4 == 0) {
      *param_4 = lVar5;
      *param_5 = uVar10;
      goto LAB_251834300;
    }
    func_0x000258109a30(uVar4,"apReceiverFairPlayHelper_CopyPICResponseData",0x2ca,0);
  }
  else {
    uVar4 = func_0x00025810aa60(param_3,&local_a8);
    if ((int)uVar4 == 0) {
      lVar5 = func_0x000258101890(param_3);
      goto LAB_251833cf8;
    }
    func_0x000258109a30(uVar4,"apReceiverFairPlayHelper_CopyPICResponseData",0x2be,0);
    lVar7 = 0;
  }
LAB_251834400:
  if ((_gLogCategory_APReceiverFairPlayHelper < 0x5b) &&
     ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
      (iVar3 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200005a), iVar3 != 0)))
     ) {
    func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                        "OSStatus apReceiverFairPlayHelper_CopyPICResponseData(APReceiverFairPlayHelperRef, CFDictionaryRef, CFStringRef, uint8_t **, size_t *)"
                        ,0x200005a,"### Copy PIC Data failed: %#m\n");
  }
LAB_251834300:
  if (local_a8 != (char *)0x0) {
    func_0x0002580f4d30();
  }
  if (lVar7 != 0) {
    func_0x0002580f4d30(lVar7);
  }
  if (*_DAT_2681b4ee0 != local_70) {
    uVar4 = func_0x0002580f4380();
    return uVar4;
  }
  return uVar4;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a76374
 * original code SHA256: 0bd5b09a419d7d3420d494a71d44d5f152768413ec1323eed39db53fdeba725f
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
__APEndpointStreamScreenAVCWrapper_initializeNegotiatorWithMode_presentationMode_hdrMirroringSupported__
          (long param_1,undefined8 param_2,undefined8 param_3,uint param_4,int param_5,
          undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  code *pcVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 extraout_x1;
  undefined8 uVar4;
  long lVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  long local_90;
  undefined8 local_88;
  undefined8 local_80;
  code *local_78;
  undefined *puStack_70;
  undefined8 *local_68;
  undefined8 local_60;
  undefined8 *local_58;
  undefined8 local_50;
  long local_48;
  
  local_90 = 0;
  if (((param_4 & 1) == 0) && (param_5 == 0)) {
    uVar4 = 0;
  }
  else {
    uVar4 = func_0x0002580308c0(param_1);
  }
  auVar6 = func_0x0002580f48d0(_DAT_2680df5a0);
  lVar2 = func_0x000258012730(auVar6._0_8_,auVar6._8_8_,uVar4);
  uVar4 = _DAT_2680d2e90;
  if (lVar2 == 0) {
    __APEndpointStreamScreenAVCWrapper_initializeNegotiatorWithMode_presentationMode_hdrMirroringSupported___cold_2
              ();
  }
  else {
    local_58 = &local_60;
    local_60 = 0;
    local_50 = DAT_251c6b010;
    local_48 = _getAVCMediaStreamNegotiatorHDRModeSymbolLoc_ptr;
    lVar5 = _getAVCMediaStreamNegotiatorHDRModeSymbolLoc_ptr;
    if (_getAVCMediaStreamNegotiatorHDRModeSymbolLoc_ptr == 0) {
      local_88 = _DAT_2681b4ed0;
      local_80 = DAT_251c6b008;
      local_78 = ___getAVCMediaStreamNegotiatorHDRModeSymbolLoc_block_invoke;
      puStack_70 = &DAT_2693e4e70;
      local_68 = local_58;
      uVar3 = _AVConferenceLibrary();
      uVar3 = func_0x0002580f4d20(uVar3,"AVCMediaStreamNegotiatorHDRMode");
      *(undefined8 *)(local_68[1] + 0x18) = uVar3;
      _getAVCMediaStreamNegotiatorHDRModeSymbolLoc_ptr = *(long *)(local_68[1] + 0x18);
      lVar5 = local_58[3];
    }
    func_0x0002580f4ba0(&local_60,8);
    if (lVar5 == 0) {
      auVar6 = func_0x0002580152c0(_DAT_2680df2b0);
      uVar4 = func_0x000258012310(_DAT_2680df6a8,auVar6._8_8_,
                                  "NSString *getAVCMediaStreamNegotiatorHDRMode(void)");
      auVar7 = func_0x0002580f4d10();
      func_0x0002580156e0(auVar6._0_8_,auVar7._8_8_,uVar4,&cfstringStruct_2761318d0,0x4d,
                          &cfstringStruct_27612d510,param_7,param_8,auVar7._0_8_);
                    /* WARNING: Does not return */
      pcVar1 = (code *)SoftwareBreakpoint(1,0x251a7655c);
      (*pcVar1)();
    }
    lVar2 = func_0x000258015440(uVar4,extraout_x1,lVar2);
    if (lVar2 != 0) {
      _getAVCMediaStreamNegotiatorClass();
      auVar6 = func_0x0002580f48d0();
      uVar4 = func_0x000258030b30(auVar6._0_8_,auVar6._8_8_,2,lVar2,&local_90);
      lVar2 = 0x28;
      if (param_4 == 0) {
        lVar2 = 0x20;
      }
      *(undefined8 *)(param_1 + lVar2) = uVar4;
      if (local_90 == 0) {
        uVar4 = 0;
      }
      else {
        func_0x000258109a30(0,
                            "-[APEndpointStreamScreenAVCWrapper initializeNegotiatorWithMode:presentationMode:hdrMirroringSupported:]"
                            ,0x705,0);
        uVar4 = func_0x0002580028d0(local_90);
      }
      goto LAB_251a764e0;
    }
    __APEndpointStreamScreenAVCWrapper_initializeNegotiatorWithMode_presentationMode_hdrMirroringSupported___cold_1
              ();
  }
  uVar4 = 0xffffbe87;
LAB_251a764e0:
  func_0x0002580f4460();
  return uVar4;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2518336b8
 * original code SHA256: 22c7996d3eeaeab7374ce4eabd6d16f194491e9a0d498f98d583f244cd82b8da
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long _APReceiverFairPlayHelperCreate(void)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 local_78;
  undefined8 local_70;
  code *local_68;
  undefined *puStack_60;
  undefined8 *local_58;
  undefined8 local_50;
  undefined8 *local_48;
  undefined8 local_40;
  undefined4 local_38;
  
  if ((_gLogCategory_APReceiverFairPlayHelper < 0x1f) &&
     ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
      (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200001e), iVar1 != 0)))
     ) {
    func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                        "APReceiverFairPlayHelperRef APReceiverFairPlayHelperCreate(void)",0x200001e
                        ,"Creating APReceiverFairPlayHelper\n");
  }
  uVar3 = *_DAT_2680d3150;
  if (_APReceiverFairPlayHelperGetTypeID_once != -1) {
    func_0x0002580f48c0(&_APReceiverFairPlayHelperGetTypeID_once,&___block_literal_global);
  }
  lVar2 = func_0x000258106640(uVar3,_APReceiverFairPlayHelperGetTypeID_typeID,8,0);
  if (lVar2 == 0) {
    func_0x000258109a30(0,"APReceiverFairPlayHelperCreate",0xaf,0);
  }
  else {
    if (_gLogCategory_APReceiverFairPlayHelper < 0x1f) {
      if ((_gLogCategory_APReceiverFairPlayHelper != -1) ||
         (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200001e), iVar1 != 0
         )) {
        func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                            "APReceiverFairPlayHelperRef APReceiverFairPlayHelperCreate(void)",
                            0x200001e,"Created FairPlay helper %{ptr}\n");
      }
      if ((_gLogCategory_APReceiverFairPlayHelper < 0x1f) &&
         ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200001e),
          iVar1 != 0)))) {
        func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                            "APReceiverFairPlayHelperRef APReceiverFairPlayHelperCreate(void)",
                            0x200001e,"Initializing FairPlay context");
      }
    }
    local_58 = &local_50;
    local_50 = 0;
    local_40 = DAT_251913150;
    local_38 = 0;
    local_78 = _DAT_2681b4ed0;
    local_70 = DAT_251913158;
    local_68 = ___apReceiverFairPlayHelper_InitContext_block_invoke;
    puStack_60 = &DAT_2693df0c0;
    local_48 = local_58;
    if (_apReceiverFairPlayHelper_InitContext_onceToken != -1) {
      func_0x0002580f48c0(&_apReceiverFairPlayHelper_InitContext_onceToken,&local_78);
    }
    iVar1 = *(int *)(local_48 + 3);
    func_0x0002580f4ba0(&local_50,8);
    if (iVar1 == 0) {
      return lVar2;
    }
  }
  if ((_gLogCategory_APReceiverFairPlayHelper < 0x5b) &&
     ((_gLogCategory_APReceiverFairPlayHelper != -1 ||
      (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverFairPlayHelper,0x200005a), iVar1 != 0)))
     ) {
    func_0x000258101eb0(&_gLogCategory_APReceiverFairPlayHelper,
                        "APReceiverFairPlayHelperRef APReceiverFairPlayHelperCreate(void)",0x200005a
                        ,"### APReceiverFairPlayHelperCreate failed, error: %#m\n");
  }
  if (lVar2 != 0) {
    func_0x0002580f5830(lVar2);
  }
  return 0;
}


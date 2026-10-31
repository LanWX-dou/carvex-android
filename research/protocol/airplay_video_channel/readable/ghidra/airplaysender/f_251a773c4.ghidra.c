/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251a773c4
 * original code SHA256: 438bc35cbaba311f7ee8fe710ead39cf6fe9dd7cb6613817706e0890fb47d621
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
__APEndpointStreamScreenAVCWrapper_createVideoStreamConfig_withDirection_screenOptions_previousConfig__
          (long param_1,undefined8 param_2,undefined8 *param_3,undefined8 param_4,long param_5,
          long param_6)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 extraout_x1;
  undefined8 extraout_x1_00;
  undefined8 extraout_x1_01;
  undefined8 extraout_x1_02;
  undefined8 extraout_x1_03;
  undefined8 extraout_x1_04;
  char *pcVar4;
  undefined8 uVar5;
  long lVar6;
  undefined1 auVar7 [16];
  undefined8 local_c0;
  undefined8 local_b8;
  long local_b0;
  undefined8 local_a8;
  undefined8 local_a0;
  code *local_98;
  undefined *puStack_90;
  undefined8 *local_88;
  undefined8 local_80;
  undefined8 *local_78;
  undefined8 local_70;
  undefined *local_68;
  undefined *local_60;
  long local_58;
  
  local_b8 = 0;
  local_b0 = 0;
  local_c0 = 0;
  pcVar4 = (char *)(param_5 + 0x28);
  lVar6 = 0x20;
  if (*pcVar4 != '\0') {
    lVar6 = 0x28;
  }
  auVar7 = func_0x0002580309b0(*(undefined8 *)(param_1 + lVar6),param_2,&local_b0);
  uVar5 = auVar7._0_8_;
  if (local_b0 == 0) {
    func_0x000258030a10(param_1,auVar7._8_8_,param_5,&local_b8,&local_c0);
    auVar7 = func_0x0002580312d0(uVar5);
    func_0x0002580311b0(auVar7._0_8_,auVar7._8_8_,0xc);
    uVar3 = local_b8;
    auVar7 = func_0x0002580312d0(uVar5);
    func_0x000258030fb0(auVar7._0_8_,auVar7._8_8_,uVar3);
    uVar3 = local_c0;
    auVar7 = func_0x0002580312d0(uVar5);
    func_0x000258030fa0(auVar7._0_8_,auVar7._8_8_,uVar3);
    func_0x0002580052b0(uVar5,extraout_x1,param_4);
    iVar1 = *(int *)(param_5 + 0x10);
    if (iVar1 != 0) {
      auVar7 = func_0x0002580312d0(uVar5);
      func_0x000258030fe0(auVar7._0_8_,auVar7._8_8_,(long)iVar1);
    }
    if ((*(char *)(param_1 + 0x78) != '\0') && (*pcVar4 == '\0')) {
      auVar7 = func_0x0002580312d0(uVar5);
      func_0x000258031170(auVar7._0_8_,auVar7._8_8_,4);
    }
    iVar1 = func_0x000258109e20(&cfstringStruct_2761315d0,40000000);
    iVar2 = func_0x000258109e20(&cfstringStruct_2761315f0,5000000);
    auVar7 = func_0x0002580312d0(uVar5);
    func_0x000258031180(auVar7._0_8_,auVar7._8_8_,(long)iVar1);
    auVar7 = func_0x0002580312d0(uVar5);
    func_0x000258031190(auVar7._0_8_,auVar7._8_8_,(long)iVar2);
    func_0x000258031110(uVar5,extraout_x1_00,1);
    func_0x000258031100(0x3ff0000000000000,uVar5);
    func_0x000258031120(0x403e000000000000,uVar5);
    func_0x000258031140(uVar5,extraout_x1_01,5);
    func_0x000258031130(uVar5,extraout_x1_02,5);
    if (param_6 == 0) {
      func_0x0002580310b0(uVar5,extraout_x1_03,*(undefined8 *)(param_5 + 0x20));
      auVar7._8_8_ = extraout_x1_04;
      auVar7._0_8_ = *(undefined8 *)(param_5 + 0x18);
    }
    else {
      auVar7 = func_0x000258030d80(param_6);
      func_0x0002580310b0(uVar5,auVar7._8_8_,auVar7._0_8_);
      auVar7 = func_0x000258030ea0(param_6);
    }
    func_0x000258031160(uVar5,auVar7._8_8_,auVar7._0_8_);
    if ((*(long *)(param_5 + 0x48) != 0) && (*(long *)(param_5 + 0x50) != 0)) {
      local_78 = &local_80;
      local_80 = 0;
      local_70 = DAT_251c6b000;
      local_68 = &___Block_byref_object_copy_;
      local_60 = &___Block_byref_object_dispose_;
      local_58 = _getAVCProtectedContentEncryptionContextClass_softClass;
      lVar6 = _getAVCProtectedContentEncryptionContextClass_softClass;
      if (_getAVCProtectedContentEncryptionContextClass_softClass == 0) {
        local_a8 = _DAT_2681b4ed0;
        local_a0 = DAT_251c6b008;
        local_98 = ___getAVCProtectedContentEncryptionContextClass_block_invoke;
        puStack_90 = &DAT_2693e4e70;
        local_88 = local_78;
        ___getAVCProtectedContentEncryptionContextClass_block_invoke(&local_a8);
        lVar6 = local_78[5];
      }
      func_0x0002580f4ba0(&local_80,8);
      auVar7 = func_0x0002580f48d0(lVar6);
      lVar6 = func_0x000258030ac0(auVar7._0_8_,auVar7._8_8_,*(undefined8 *)(param_5 + 0x48),
                                  *(undefined8 *)(param_5 + 0x50));
      if (lVar6 == 0) {
        __APEndpointStreamScreenAVCWrapper_createVideoStreamConfig_withDirection_screenOptions_previousConfig___cold_1
                  ();
        uVar5 = 0xffffbe87;
        goto LAB_251a776b4;
      }
      auVar7 = func_0x0002580312d0(uVar5);
      func_0x000258031060(auVar7._0_8_,auVar7._8_8_,lVar6);
    }
    if ((_gLogCategory_APEndpointStreamScreenUDP < 0x33) &&
       ((_gLogCategory_APEndpointStreamScreenUDP != -1 ||
        (iVar1 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreenUDP,0x2000032), iVar1 != 0
        )))) {
      __APEndpointStreamScreenAVCWrapper_createVideoStreamConfig_withDirection_screenOptions_previousConfig___cold_2
                (pcVar4,uVar5);
    }
    uVar3 = func_0x0002580f4a40();
    uVar5 = 0;
    *param_3 = uVar3;
  }
  else {
    func_0x000258109a30(0,
                        "-[APEndpointStreamScreenAVCWrapper createVideoStreamConfig:withDirection:screenOptions:previousConfig:]"
                        ,0x7f7,0);
    uVar5 = func_0x0002580028d0(local_b0);
  }
LAB_251a776b4:
  func_0x0002580f4490();
  return uVar5;
}


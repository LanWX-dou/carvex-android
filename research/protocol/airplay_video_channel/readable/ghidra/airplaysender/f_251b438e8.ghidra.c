/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b438e8
 * original code SHA256: 06b2a5663c5934436491f3c2653de50e23473b23ccb393a7461c006bf20a2ff2
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 _screenstream_Control(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  undefined8 local_198;
  undefined8 local_190;
  code *local_188;
  undefined *puStack_180;
  undefined8 *local_178;
  undefined8 uStack_170;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  code *local_150;
  undefined *puStack_148;
  undefined8 *local_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 local_128;
  undefined8 local_120;
  code *local_118;
  undefined *puStack_110;
  undefined8 *local_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 local_f0;
  code *local_e8;
  undefined *puStack_e0;
  undefined8 *local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  code *local_b8;
  undefined *puStack_b0;
  undefined8 *local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 local_90;
  code *local_88;
  undefined *puStack_80;
  undefined8 *local_78;
  undefined8 uStack_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 *local_58;
  undefined8 local_50;
  undefined4 local_48;
  
  local_60 = 0;
  local_50 = DAT_251c6aff0;
  local_48 = 0;
  local_58 = &local_60;
  puVar3 = (undefined8 *)func_0x00025810ac50();
  iVar2 = func_0x00025810b1a0(param_2,_kAPEndpointStreamControlCommand_SetMode);
  if (iVar2 == 0) {
    iVar2 = func_0x00025810b1a0(param_2,&cfstringStruct_27613fb90);
    if (iVar2 == 0) {
      iVar2 = func_0x00025810b1a0(param_2,&cfstringStruct_27613fbb0);
      if (iVar2 == 0) {
        iVar2 = func_0x00025810b1a0(param_2,&cfstringStruct_27613fbd0);
        if (iVar2 == 0) {
          iVar2 = func_0x00025810b1a0(param_2,&cfstringStruct_27613fbf0);
          if (iVar2 == 0) {
            iVar2 = func_0x00025810b1a0(param_2,&cfstringStruct_27612ceb0);
            if (iVar2 == 0) {
              if ((_gLogCategory_APEndpointStreamScreen < 0x5b) &&
                 ((_gLogCategory_APEndpointStreamScreen != -1 ||
                  (iVar2 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x200005a),
                  iVar2 != 0)))) {
                func_0x000258101eb0(&_gLogCategory_APEndpointStreamScreen,
                                    "OSStatus screenstream_Control(FigEndpointStreamRef, CFStringRef, CFDictionaryRef)"
                                    ,0x200005a,"%@ ### invalid control command \'%@\'\n");
              }
              *(undefined4 *)(local_58 + 3) = 0xffffbe88;
              goto LAB_251b43bc4;
            }
            uVar4 = *puVar3;
            local_198 = _DAT_2681b4ed0;
            local_190 = DAT_251c6aff8;
            local_188 = ___screenstream_Control_block_invoke_6;
            puStack_180 = &DAT_2693ebd18;
            local_178 = &local_60;
            puVar3 = &local_198;
            uStack_170 = param_1;
            local_168 = param_3;
          }
          else {
            uVar4 = *puVar3;
            local_160 = _DAT_2681b4ed0;
            local_158 = DAT_251c6aff8;
            local_150 = ___screenstream_Control_block_invoke_5;
            puStack_148 = &DAT_2693ebcf0;
            local_140 = &local_60;
            puVar3 = &local_160;
            uStack_138 = param_1;
            local_130 = param_3;
          }
        }
        else {
          uVar4 = *puVar3;
          local_128 = _DAT_2681b4ed0;
          local_120 = DAT_251c6aff8;
          local_118 = ___screenstream_Control_block_invoke_4;
          puStack_110 = &DAT_2693ebcc8;
          local_108 = &local_60;
          puVar3 = &local_128;
          uStack_100 = param_1;
        }
      }
      else {
        uVar4 = *puVar3;
        local_f8 = _DAT_2681b4ed0;
        local_f0 = DAT_251c6aff8;
        local_e8 = ___screenstream_Control_block_invoke_3;
        puStack_e0 = &DAT_2693ebca0;
        local_d8 = &local_60;
        puVar3 = &local_f8;
        uStack_d0 = param_1;
      }
    }
    else {
      uVar4 = *puVar3;
      local_c8 = _DAT_2681b4ed0;
      local_c0 = DAT_251c6aff8;
      local_b8 = ___screenstream_Control_block_invoke_2;
      puStack_b0 = &DAT_2693ebc78;
      local_a8 = &local_60;
      puVar3 = &local_c8;
      uStack_a0 = param_1;
    }
  }
  else {
    uVar4 = *puVar3;
    local_98 = _DAT_2681b4ed0;
    local_90 = DAT_251c6aff8;
    local_88 = ___screenstream_Control_block_invoke;
    puStack_80 = &DAT_2693ebc50;
    puVar3 = &local_98;
    local_78 = &local_60;
    uStack_70 = param_1;
    local_68 = param_3;
  }
  func_0x0002580f54f0(uVar4,puVar3);
LAB_251b43bc4:
  uVar1 = *(undefined4 *)(local_58 + 3);
  func_0x0002580f4ba0(&local_60,8);
  return uVar1;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000464e8
 * original code SHA256: 259b6fde9cc8deb698eb631ca035101a9882abc1b3f3e53d86c6ae7ead0ddb8a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */

undefined8 _mfi4Auth_protocol_initMessage_AuthStart(long param_1,long *param_2)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined1 *local_1d0;
  undefined1 *puStack_1c8;
  undefined1 *puStack_1c0;
  undefined1 *puStack_1b8;
  undefined1 *local_1b0;
  undefined1 *puStack_1a8;
  undefined1 *puStack_1a0;
  undefined1 *puStack_198;
  undefined1 *local_190;
  undefined1 *puStack_188;
  undefined1 *puStack_180;
  undefined1 *puStack_178;
  undefined1 *local_170;
  undefined1 *puStack_168;
  undefined1 *local_160;
  undefined1 *puStack_158;
  undefined1 *local_150;
  undefined1 *puStack_148;
  undefined1 *puStack_140;
  undefined1 *puStack_138;
  undefined1 *local_130;
  undefined1 *puStack_128;
  undefined1 *puStack_120;
  undefined1 *puStack_118;
  undefined1 *local_110;
  undefined1 *puStack_108;
  undefined1 *puStack_100;
  undefined1 *puStack_f8;
  undefined1 *local_f0;
  undefined1 *puStack_e8;
  undefined1 *puStack_e0;
  undefined1 *puStack_d8;
  undefined1 *local_d0;
  undefined1 *puStack_c8;
  undefined1 *puStack_c0;
  undefined1 *puStack_b8;
  undefined1 *local_b0;
  undefined1 *puStack_a8;
  undefined1 *puStack_a0;
  undefined1 *puStack_98;
  undefined1 *local_90;
  undefined1 *puStack_88;
  undefined1 *puStack_80;
  undefined1 *puStack_78;
  undefined1 *local_70;
  undefined1 *puStack_68;
  undefined1 *puStack_60;
  undefined1 *puStack_58;
  long local_48;
  
  local_48 = *(long *)PTR____stack_chk_guard_10022bb80;
  if (param_1 == 0) {
    uVar2 = _logObjectForModule();
    iVar1 = _os_log_type_enabled(uVar2,0x10);
    if (iVar1 != 0) {
      _mfi4Auth_protocol_handle_AuthStart_cold_3(uVar2);
    }
LAB_100046710:
    uVar2 = 1;
  }
  else {
    if (*(char *)(param_1 + 0x1e) == '\x01') {
      uVar2 = _logObjectForModule();
      iVar1 = _os_log_type_enabled(uVar2,0x10);
      if (iVar1 != 0) {
        _mfi4Auth_protocol_initMessage_AuthStart_cold_4(uVar2);
      }
      goto LAB_100046710;
    }
    if (param_2 == (long *)0x0) {
      uVar2 = _logObjectForModule();
      iVar1 = _os_log_type_enabled(uVar2,0x10);
      if (iVar1 != 0) {
        _mfi4Auth_protocol_initMessage_AuthStart_cold_3(uVar2);
      }
      goto LAB_100046710;
    }
    puStack_68 = (undefined1 *)0x0;
    local_70 = (undefined1 *)0x0;
    puStack_58 = (undefined1 *)0x0;
    puStack_60 = (undefined1 *)0x0;
    puStack_88 = (undefined1 *)0x0;
    local_90 = (undefined1 *)0x0;
    puStack_78 = (undefined1 *)0x0;
    puStack_80 = (undefined1 *)0x0;
    puStack_e8 = &DAT_aaaaaaaaaaaaaaaa;
    local_f0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_d8 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_e0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_c8 = &DAT_aaaaaaaaaaaaaaaa;
    local_d0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_b8 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_c0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_a8 = &DAT_aaaaaaaaaaaaaaaa;
    local_b0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_98 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_a0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_148 = &DAT_aaaaaaaaaaaaaaaa;
    local_150 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_138 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_140 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_128 = &DAT_aaaaaaaaaaaaaaaa;
    local_130 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_118 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_120 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_108 = &DAT_aaaaaaaaaaaaaaaa;
    local_110 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_f8 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_100 = &DAT_aaaaaaaaaaaaaaaa;
    local_160 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_158 = &DAT_aaaaaaaaaaaaaaaa;
    uVar4 = *(undefined8 *)(param_1 + 0x98);
    uVar2 = _ccsigma_sign(uVar4,&local_90,0x20,(undefined8 *)(param_1 + 0x1bc),
                          *(undefined8 *)(param_1 + 0xa0));
    if ((int)uVar2 == 0) {
      puStack_e8 = *(undefined1 **)(param_1 + 0x1c4);
      local_f0 = *(undefined1 **)(param_1 + 0x1bc);
      puStack_d8 = *(undefined1 **)(param_1 + 0x1d4);
      puStack_e0 = *(undefined1 **)(param_1 + 0x1cc);
      puStack_c8 = puStack_88;
      local_d0 = local_90;
      puStack_b8 = puStack_78;
      puStack_c0 = puStack_80;
      puStack_a8 = puStack_68;
      local_b0 = local_70;
      puStack_98 = puStack_58;
      puStack_a0 = puStack_60;
      uVar2 = _ccsigma_seal(uVar4,0,1,0,0,0x60,&local_f0,&local_150,&local_160);
      if ((int)uVar2 == 0) {
        puStack_1a8 = puStack_128;
        local_1b0 = local_130;
        puStack_198 = puStack_118;
        puStack_1a0 = puStack_120;
        puStack_188 = puStack_108;
        local_190 = local_110;
        puStack_178 = puStack_f8;
        puStack_180 = puStack_100;
        puStack_1c8 = puStack_148;
        local_1d0 = local_150;
        puStack_1b8 = puStack_138;
        puStack_1c0 = puStack_140;
        puStack_168 = puStack_158;
        local_170 = local_160;
        lVar3 = _malloc_type_malloc(0x48,0x109004066c3afe2);
        *param_2 = lVar3;
        if (lVar3 != 0) {
          _iAP2MsgInitWithSom(lVar3,0,0x5111,*(undefined8 *)(param_1 + 0x10),
                              *(undefined4 *)(param_1 + 0x18),0,0);
          _iAP2MsgAddU16Param(*param_2,0,0,*(undefined2 *)(param_1 + 0x154));
          _iAP2MsgAddArrayU8Param(*param_2,0,1,param_1 + 0x177,0x21);
          _iAP2MsgAddArrayU8Param(*param_2,0,2,&local_1d0,0x70);
          uVar2 = 0;
          *(undefined2 *)(param_1 + 0x1c) = 0x5111;
          goto LAB_100046674;
        }
        uVar2 = 0xffffffff;
      }
      else {
        uVar4 = _logObjectForModule();
        iVar1 = _os_log_type_enabled(uVar4,0x10);
        if (iVar1 != 0) {
          _mfi4Auth_protocol_initMessage_AuthStart_cold_2(uVar4);
        }
      }
    }
    else {
      uVar4 = _logObjectForModule();
      iVar1 = _os_log_type_enabled(uVar4,0x10);
      if (iVar1 != 0) {
        _mfi4Auth_protocol_initMessage_AuthStart_cold_1(uVar4);
      }
    }
  }
  _mfi4Auth_protocol_initMessage_AuthStart_cold_6(uVar2);
LAB_100046674:
  if (*(long *)PTR____stack_chk_guard_10022bb80 != local_48) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail();
  }
  return uVar2;
}


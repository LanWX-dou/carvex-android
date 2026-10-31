/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008e434
 * original code SHA256: 958c55a0d4046d7526ece6d6fdd8034002a509bc865c559e45c37e3de140f968
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Function: _objc_retain_x8 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */

undefined4
__acc_auth_protocol_generateChallenge(long param_1,long param_2,void *param_3,uint param_4)

{
  int iVar1;
  long extraout_x0;
  undefined *puVar2;
  undefined4 uVar3;
  undefined4 local_40;
  uint local_3c;
  undefined2 local_38;
  undefined4 local_36;
  
  uVar3 = 1;
  if ((((param_1 != 0) && (param_2 != 0)) && (param_3 != (void *)0x0)) && (param_4 != 0)) {
    _arc4random_buf(param_3,(ulong)param_4);
    uVar3 = 0;
    param_1 = extraout_x0;
  }
  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x3a)) {
    puVar2 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken != -1) {
      param_1 = _logObjectForModule_cold_1();
      puVar2 = PTR___os_log_default_10022bbb0;
    }
  }
  else {
    puVar2 = *(undefined **)(_gLogObjects + 0x1c8);
  }
  iVar1 = _os_log_type_enabled(puVar2);
  if (iVar1 != 0) {
    local_40 = (undefined4)DAT_1001b3108;
    local_38 = 0x400;
    local_3c = param_4;
    local_36 = uVar3;
    __os_log_impl(0x100000000,param_1,1,
                  "[AccAuth] _generateChallenge: outChallengeLen %d, errorNo %d \n",&local_40,0xe);
  }
  return uVar3;
}


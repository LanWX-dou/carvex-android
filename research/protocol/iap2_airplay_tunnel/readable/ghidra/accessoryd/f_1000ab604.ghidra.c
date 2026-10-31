/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000ab604
 * original code SHA256: 488f368851d3ac957b6e2fd7fe78c05c9aaaa5151c0d70d7092ede84c21c1928
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
____mfi4Auth_endpoint_setupAuthSetupStartTimer_block_invoke_58
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  int iVar1;
  ulong uVar2;
  dispatch_time_t start;
  dispatch_source_t source;
  long lVar3;
  void *local_28;
  
  local_28 = (void *)0x0;
  if (param_4 == 0) {
    uVar2 = ____mfi4Auth_endpoint_setupAuthSetupStartTimer_block_invoke_58_cold_4(param_3);
    if ((uVar2 & 1) != 0) {
      return 1;
    }
  }
  else if (*(int *)(param_4 + 0x1c) == 0xe) {
    lVar3 = *(long *)(param_4 + 0x38);
    if (lVar3 == 0) {
      ____mfi4Auth_endpoint_setupAuthSetupStartTimer_block_invoke_58_cold_3(param_3);
    }
    else {
      iVar1 = _mfi4Auth_protocol_authSetupStart(*(undefined8 *)(lVar3 + 8),&local_28);
      if (iVar1 == 0) {
        _mfi4Auth_protocol_messageHandler_sendOutgoingData(*(undefined8 *)(lVar3 + 8),local_28);
        if ((*(int *)(param_4 + 0x18) == 0xd) &&
           (uVar2 = _acc_userDefaults_boolForKey(_kCFACCUserDefaultsKey_DisableNFCAuthTimer),
           (uVar2 & 1) == 0)) {
          source = *(dispatch_source_t *)(lVar3 + 0x28);
          start = _dispatch_time(0,3000000000);
          _dispatch_source_set_timer(source,start,0xffffffffffffffff,0);
        }
      }
      else {
        ____mfi4Auth_endpoint_setupAuthSetupStartTimer_block_invoke_58_cold_2();
      }
    }
  }
  else {
    ____mfi4Auth_endpoint_setupAuthSetupStartTimer_block_invoke_58_cold_1
              ((int *)(param_4 + 0x1c),param_3);
  }
  if (local_28 != (void *)0x0) {
    _free(local_28);
  }
  return 1;
}


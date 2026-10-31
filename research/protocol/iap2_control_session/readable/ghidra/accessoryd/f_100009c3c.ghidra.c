/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100009c3c
 * original code SHA256: 5e06d2aa63094b08c61abced4690dc33ccd25f145819a739f565004937383513
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_endpoint_processIncomingData(undefined8 *param_1,long param_2)

{
  undefined8 uVar1;
  undefined *local_50;
  undefined8 local_48;
  code *local_40;
  undefined *puStack_38;
  undefined8 *local_30;
  long lStack_28;
  
  uVar1 = 0;
  if (param_1 != (undefined8 *)0x0) {
    uVar1 = 0;
    if ((param_2 != 0) && (param_1[5] != 0)) {
      if (param_1[3] == 0) {
        uVar1 = 0;
      }
      else {
        _CFRetain(param_2);
        local_50 = PTR___NSConcreteStackBlock_10022bb78;
        local_48 = DAT_1001b3118;
        local_40 = ___iap2_endpoint_processIncomingData_block_invoke;
        puStack_38 = &___block_descriptor_tmp_10;
        local_30 = param_1;
        lStack_28 = param_2;
        _acc_protocolEndpoint_performAsync
                  (&local_40,*param_1,*(undefined1 *)(param_1 + 4),param_1[3],&local_50);
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}


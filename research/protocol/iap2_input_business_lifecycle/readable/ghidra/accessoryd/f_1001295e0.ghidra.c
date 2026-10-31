/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001295e0
 * original code SHA256: d515d94d0f58048b1a55d4774b0ccc272ab79e2bdcdd8872ee59d1806835b55e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_endpoint_setInitialized(long *param_1,int param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  if (param_1 != (long *)0x0) {
    *(char *)(param_1 + 0x38) = (char)param_2;
    lVar1 = *param_1;
    if (lVar1 != 0) {
      if (param_2 != 0) {
        uVar2 = _acc_endpoint2_setProperty
                          (lVar1,*(undefined8 *)
                                  PTR__kCFACCProperties_Endpoint_iAP2_Initialized_10022b978,0);
        return uVar2;
      }
      uVar2 = _acc_endpoint2_removeProperty
                        (lVar1,*(undefined8 *)
                                PTR__kCFACCProperties_Endpoint_iAP2_Initialized_10022b978);
      return uVar2;
    }
  }
  return 0;
}


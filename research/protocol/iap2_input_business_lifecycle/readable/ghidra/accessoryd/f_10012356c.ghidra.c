/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10012356c
 * original code SHA256: f7c12460c6f51926e47ae5ea925686dceefd1e063afa44bb77c870b093a1101b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_deviceAuthentication_DeviceAuthenticationFailed(long param_1,long param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if ((param_1 != 0) && (param_2 != 0)) {
    lVar1 = _iap2_feature_getFeature(param_1,7);
    if (lVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
      __setDeviceAuthState(param_1,1);
    }
  }
  return uVar2;
}


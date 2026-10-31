/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100123690
 * original code SHA256: 2ef6edbf7064aca1ad56f212c52e9b6eecc15dc9a92376ebea62aff0a1918c3b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_deviceAuthentication_DeviceAuthenticationSucceeded(long param_1,long param_2)

{
  undefined8 uVar1;
  long lVar2;
  
  uVar1 = 0;
  if (((param_1 != 0) && (param_2 != 0)) &&
     (lVar2 = _iap2_feature_getFeature(param_1,7), uVar1 = 0, lVar2 != 0)) {
    __setDeviceAuthState(param_1,2);
    uVar1 = 1;
  }
  return uVar1;
}


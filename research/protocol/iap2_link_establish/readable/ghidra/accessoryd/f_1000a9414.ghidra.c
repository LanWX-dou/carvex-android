/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000a9414
 * original code SHA256: 94374a3bfbc4a005ae90a3cf63663ab0ab06adc295906eafe3bcbaa41426f23b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



uint _mfi4Auth_endpoint_timeoutForTransportInSeconds(int param_1)

{
  long lVar1;
  uint uVar2;
  
  uVar2 = 10;
  if (param_1 != 3) {
    uVar2 = 0;
  }
  lVar1 = _acc_userDefaults_copyIntegerForKey(_kCFACCUserDefaultsKey_MFi4AuthTimeoutValueS);
  if (lVar1 != 0) {
    uVar2 = (uint)lVar1 & ((uint)(lVar1 >> 0x3f) ^ 0xffffffff);
  }
  return uVar2;
}


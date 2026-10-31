/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000059a0
 * original code SHA256: 7c20df4beaffbd82f9b368c2ac41f7fb53198d614f157dfd7dce7fed841f5cfd
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _iap2_endpoint_sendOutgoingData(undefined8 *param_1,undefined8 param_2,undefined4 param_3)

{
  long lVar1;
  ulong uVar2;
  byte local_31;
  
  if (param_1 == (undefined8 *)0x0) {
    _iap2_endpoint_sendOutgoingData_cold_1(&local_31);
    uVar2 = (ulong)local_31;
  }
  else {
    _kdebug_trace(0x2b940010,0,0,0,0);
    lVar1 = _CFDataCreate(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,param_2,param_3);
    uVar2 = _acc_endpoint2_sendOutgoingData(*param_1,lVar1);
    if (lVar1 != 0) {
      _CFRelease(lVar1);
    }
  }
  return uVar2;
}


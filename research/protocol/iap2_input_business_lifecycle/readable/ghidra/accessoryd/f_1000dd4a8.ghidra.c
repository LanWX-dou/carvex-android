/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000dd4a8
 * original code SHA256: d5c184a32e48a4ae5b275f0e728bebeceeb17cc0fbd6e08195fd5509af986120
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _platform_navigation_displayComponentAddLaneGuidanceCapacity(long param_1,undefined2 param_2)

{
  undefined8 uVar1;
  undefined2 local_22;
  
  if (param_1 != 0) {
    local_22 = param_2;
    uVar1 = _CFNumberCreate(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,2,&local_22);
    _CFDictionarySetValue(param_1,_ACCNav_DispComp_MaxLaneGuidanceStorageCapacity,uVar1);
    _CFRelease(uVar1);
  }
  return;
}


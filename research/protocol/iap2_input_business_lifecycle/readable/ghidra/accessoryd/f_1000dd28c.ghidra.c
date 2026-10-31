/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000dd28c
 * original code SHA256: ff62f7e4b8ed85b45773ca211b166f981710c74d7bcd0af705109bbf23fddcc3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _platform_navigation_displayComponentAddMaxDestinationNameLength
               (long param_1,undefined2 param_2)

{
  undefined8 uVar1;
  undefined2 local_22;
  
  if (param_1 != 0) {
    local_22 = param_2;
    uVar1 = _CFNumberCreate(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,2,&local_22);
    _CFDictionarySetValue(param_1,_ACCNav_DispComp_MaxDestinationNameLength,uVar1);
    _CFRelease(uVar1);
  }
  return;
}


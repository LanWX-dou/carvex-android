/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000b2f94
 * original code SHA256: 525ffc8b0cea870587392a9744cc114ff7fa54a5f37f35bcd9a770f31ee726c8
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_platform_hid_send_component_update(undefined8 param_1,undefined8 param_2,undefined1 param_3)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 local_31;
  
  local_31 = param_3;
  lVar1 = _CFDictionaryCreateMutable
                    (0,0,PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,
                     PTR__kCFTypeDictionaryValueCallBacks_10022bd48);
  lVar2 = _CFNumberCreate(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,7,&local_31);
  _CFDictionaryAddValue(lVar1,_kCFAccessoryHID_ComponentID,param_2);
  _CFDictionaryAddValue(lVar1,_kCFAccessoryHID_ComponentEnabled,lVar2);
  uVar3 = _accFeatureHandlers_invokeHandler(param_1,0x12e,lVar1);
  if (lVar2 != 0) {
    _CFRelease(lVar2);
  }
  if (lVar1 != 0) {
    _CFRelease(lVar1);
  }
  return uVar3;
}


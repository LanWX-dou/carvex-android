/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000b2ed0
 * original code SHA256: a393bca26ba3348a909847bb304d7c515a4e2e3a0f2edf0d4ab76636a0c98020
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_platform_hid_send_get_report
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = _CFDictionaryCreateMutable
                    (0,0,PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,
                     PTR__kCFTypeDictionaryValueCallBacks_10022bd48);
  _CFDictionaryAddValue(lVar1,_kCFAccessoryHID_ComponentID,param_2);
  _CFDictionaryAddValue(lVar1,_kCFAccessoryHID_ReportType,param_3);
  _CFDictionaryAddValue(lVar1,_kCFAccessoryHID_ReportID,param_4);
  uVar2 = _accFeatureHandlers_invokeHandler(param_1,0x12d,lVar1);
  if (lVar1 != 0) {
    _CFRelease(lVar1);
  }
  return uVar2;
}


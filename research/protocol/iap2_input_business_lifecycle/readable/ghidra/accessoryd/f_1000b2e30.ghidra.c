/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000b2e30
 * original code SHA256: 719aad36001c04211c4574e48b0b89a936f59e825c4b75cdfbf2d5152b4271b3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _platform_hid_send_out_report(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = _CFDictionaryCreateMutable
                    (0,0,PTR__kCFTypeDictionaryKeyCallBacks_10022bd40,
                     PTR__kCFTypeDictionaryValueCallBacks_10022bd48);
  _CFDictionaryAddValue(lVar1,_kCFAccessoryHID_ComponentID,param_2);
  _CFDictionaryAddValue(lVar1,_kCFAccessoryHID_Report,param_3);
  uVar2 = _accFeatureHandlers_invokeHandler(param_1,300,lVar1);
  if (lVar1 != 0) {
    _CFRelease(lVar1);
  }
  return uVar2;
}


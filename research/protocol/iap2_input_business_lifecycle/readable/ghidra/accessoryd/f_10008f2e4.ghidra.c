/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008f2e4
 * original code SHA256: 1d301bb6641cb91c36c5f1e82eda79954048342573de2bc272a5c41ed0afd567
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _platform_nowPlaying_playbackQueueListChanged(undefined1 param_1)

{
  long lVar1;
  undefined8 uVar2;
  undefined1 local_21;
  
  local_21 = param_1;
  lVar1 = _CFNumberCreate(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,7,&local_21);
  uVar2 = _accFeatureHandlers_invokeHandler(0,0xcb,lVar1);
  if (lVar1 != 0) {
    _CFRelease(lVar1);
  }
  return uVar2;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519c1d5c
 * original code SHA256: 21c27b643c782c01575aa1002035d2b21702be9157d945268f417e6b5f7a2ac0
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _carAudioStream_getRTPPayloadType(undefined8 param_1)

{
  int iVar1;
  
  iVar1 = (int)param_1;
  if (iVar1 < 0x6d61696e) {
    if (iVar1 < 0x6175786f) {
      if (iVar1 == 0x616c7420) {
        return 0x65;
      }
      if (iVar1 == 0x61726564) {
        return 0x69;
      }
    }
    else {
      if (iVar1 == 0x6175786f) {
        return 0x6a;
      }
      if (iVar1 == 0x61787264) {
        return 0x6c;
      }
    }
  }
  else if (iVar1 < 0x6f6f7663) {
    if (iVar1 == 0x6d61696e) {
      return 100;
    }
    if (iVar1 == 0x6d726564) {
      return 0x68;
    }
  }
  else {
    if (iVar1 == 0x6f6f7663) {
      return 0x6b;
    }
    if (iVar1 == 0x6f767264) {
      return 0x6d;
    }
  }
  if ((_gLogCategory_APEndpointStreamCarPlayAudio < 0x5b) &&
     ((_gLogCategory_APEndpointStreamCarPlayAudio != -1 ||
      (iVar1 = func_0x000258101e40(&_gLogCategory_APEndpointStreamCarPlayAudio,0x200005a),
      iVar1 != 0)))) {
    _carAudioStream_getRTPPayloadType_cold_1(param_1);
  }
  return 0x6d61696e;
}


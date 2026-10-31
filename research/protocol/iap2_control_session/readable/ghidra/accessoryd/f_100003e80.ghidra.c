/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100003e80
 * original code SHA256: 008696a5fe64eb2bb4ecbc2d42ae37b299f1075f2866da109cab3c9b16e03f32
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long _iAP2MsgAddU8Param(long param_1,undefined8 param_2,undefined8 param_3,undefined1 param_4)

{
  long lVar1;
  long lVar2;
  
  lVar2 = *(long *)(param_1 + 0x20);
  lVar1 = 0;
  if ((lVar2 - *(long *)(param_1 + 0x18)) + 5 <= (long)(ulong)*(uint *)(param_1 + 0x10)) {
    lVar1 = lVar2;
  }
  if (lVar1 != 0) {
    _iAP2MsgInitParam(param_1,lVar2,param_3,3,5,param_2);
    *(undefined1 *)(lVar2 + 4) = param_4;
  }
  return lVar1;
}


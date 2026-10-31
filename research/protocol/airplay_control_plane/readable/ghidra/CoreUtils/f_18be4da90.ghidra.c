/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x18be4da90
 * original code SHA256: b99674978f7ee898195a283a4c613af9a7d7ae4fb1ac707363ca8ede8663c8c2
 * source SHA256: 3968b52b962def4ac94d0c6e2e3451dda29a468b00ea67d6d4bd6e12a8d71083
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _HTTPMessageSetBody(long param_1,long param_2,long param_3,undefined8 param_4)

{
  ulong uVar1;
  
  uVar1 = (ulong)*(uint *)(param_1 + 0x2134);
  if (*(uint *)(param_1 + 0x2134) == 0) {
    uVar1 = _HTTPMessageSetBodyLength(param_1,param_4);
    if ((int)uVar1 == 0) {
      if ((param_3 != 0) && (param_3 != *(long *)(param_1 + 0x2148))) {
        func_0x0001900cc490(*(long *)(param_1 + 0x2148),param_3,param_4);
      }
      _HTTPHeader_SetField(param_1 + 0x18,"Content-Length","%zu");
      if (param_2 != 0) {
        _HTTPHeader_SetField(param_1 + 0x18,"Content-Type","%s");
      }
      uVar1 = 0;
    }
    else if (*(int *)(param_1 + 0x2134) == 0) {
      *(int *)(param_1 + 0x2134) = (int)uVar1;
    }
  }
  return uVar1;
}


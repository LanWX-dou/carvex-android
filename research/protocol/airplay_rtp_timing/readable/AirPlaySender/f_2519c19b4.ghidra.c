/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519c19b4
 * original code SHA256: 0e0392bbec1c028185de0182fb3766168d771ff73801a1a9eabd493969d5df78
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_jitterBuffer_CommitBuffer
          (undefined8 param_1,long param_2,ulong param_3,undefined8 param_4,undefined8 param_5,
          double *param_6)

{
  long lVar1;
  long lVar2;
  
  lVar1 = func_0x00025810ac50();
  lVar2 = *(long *)(lVar1 + 0x68);
  if (lVar2 == 0) {
    _jitterBuffer_CommitBuffer_cold_3();
  }
  else {
    if (param_2 == lVar2 + 0xc) {
      if (param_3 == 0) {
        func_0x00025810da90(*(undefined8 *)(lVar1 + 8));
        return 0;
      }
      if (((ulong)param_6[7] & 1) != 0) {
        *(int *)(lVar2 + 4) = (int)(long)*param_6;
        *(ulong *)(*(long *)(lVar1 + 0x68) + 0x5c0) = param_3 & 0xffffffff;
        func_0x00025810daa0(*(undefined8 *)(lVar1 + 8));
        *(undefined8 *)(lVar1 + 0x68) = 0;
        return 0;
      }
      _jitterBuffer_CommitBuffer_cold_2();
      return 0xffffbe68;
    }
    _jitterBuffer_CommitBuffer_cold_1();
  }
  return 0xffffbe67;
}


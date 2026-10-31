/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519c0aec
 * original code SHA256: 79d858ab66a6b168284ce5fa75f22a028bcd3b1cb9f80c257b83fd3fac92c903
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _jitterBuffer_AcquireBuffer(undefined8 param_1,long *param_2,undefined8 *param_3)

{
  long lVar1;
  long lVar2;
  int local_34;
  
  local_34 = 0;
  lVar1 = func_0x00025810ac50();
  if (*(long *)(lVar1 + 0x68) == 0) {
    lVar2 = func_0x00025810dab0(*(undefined8 *)(lVar1 + 8),&local_34);
    *(long *)(lVar1 + 0x68) = lVar2;
    if (local_34 == 0) {
      *param_2 = lVar2 + 0xc;
      *param_3 = 0x5b4;
    }
    else {
      func_0x000258109a30(local_34,"jitterBuffer_AcquireBuffer",0xdd,0);
    }
  }
  else {
    _jitterBuffer_AcquireBuffer_cold_1();
    local_34 = -0x4199;
  }
  return local_34;
}


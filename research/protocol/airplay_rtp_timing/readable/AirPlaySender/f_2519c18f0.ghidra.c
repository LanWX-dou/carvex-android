/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519c18f0
 * original code SHA256: 9d1bfefda338a82544a13ed9ff305b33535889fcfb232eecd9ffbee1cec949ed
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_jitterBuffer_ReadPackets
          (undefined8 param_1,long param_2,undefined8 param_3,ulong param_4,long param_5,int param_6
          ,ulong *param_7,int *param_8)

{
  long lVar1;
  undefined8 uVar2;
  ulong uVar3;
  
  lVar1 = func_0x00025810ac50();
  if ((*(byte *)(param_2 + 0x88) & 1) == 0) {
    _jitterBuffer_ReadPackets_cold_4();
  }
  else if (param_5 == 0) {
    uVar3 = (ulong)(uint)(*(int *)(lVar1 + 0x50) * param_6);
    if (uVar3 <= param_4) {
      uVar2 = func_0x00025810dac0(*(undefined8 *)(lVar1 + 8),(long)*(double *)(param_2 + 0x50),
                                  param_3,uVar3);
      if ((int)uVar2 == 0) {
        *param_7 = uVar3;
        *param_8 = param_6;
        return uVar2;
      }
      _jitterBuffer_ReadPackets_cold_2(uVar2);
      return uVar2;
    }
    _jitterBuffer_ReadPackets_cold_3();
  }
  else {
    _jitterBuffer_ReadPackets_cold_1();
  }
  return 0xffffbe68;
}


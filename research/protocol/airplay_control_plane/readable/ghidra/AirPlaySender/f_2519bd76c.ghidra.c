/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519bd76c
 * original code SHA256: 94bb78c5545b3333890dcb5dc3d113459024207db463295a02a534f4534beb4a
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_coreUtilsPairing_DeriveKey
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = func_0x00025810ac50();
  if (*(long *)(lVar1 + 8) == 0) {
    _coreUtilsPairing_DeriveKey_cold_2();
    uVar2 = 0xfffee7a4;
  }
  else {
    uVar2 = func_0x00025810ba10(*(long *)(lVar1 + 8),param_2,param_3,param_4,param_5,param_6,param_7
                               );
    if ((int)uVar2 != 0) {
      _coreUtilsPairing_DeriveKey_cold_1(uVar2);
    }
  }
  return uVar2;
}


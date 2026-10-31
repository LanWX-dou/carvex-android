/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ab0108
 * original code SHA256: a20adb6047f9ab911c0ab4387f17bda204b4666d4910a443ca7243c80c0880b1
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _sharedKeyHolder_CopyMasterAESKeyAndIV(undefined8 param_1,long *param_2,long *param_3)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  
  lVar1 = func_0x00025810ac50();
  lVar2 = func_0x0002580f6ff0(*(undefined8 *)(lVar1 + 0x28),lVar1 + 8,0x10);
  if (lVar2 == 0) {
    uVar3 = 0xfffee7d8;
    _sharedKeyHolder_CopyMasterAESKeyAndIV_cold_2();
  }
  else {
    lVar1 = func_0x0002580f6ff0(*(undefined8 *)(lVar1 + 0x28),lVar1 + 0x18,0x10);
    if (lVar1 == 0) {
      uVar3 = 0xfffee7d8;
      _sharedKeyHolder_CopyMasterAESKeyAndIV_cold_1(lVar2);
    }
    else {
      uVar3 = 0;
      *param_2 = lVar2;
      *param_3 = lVar1;
    }
  }
  return uVar3;
}


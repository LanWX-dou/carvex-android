/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251aa9490
 * original code SHA256: e9c182bac8e28229c9c056e7b9b69ca5068d2be25a81d7ec0fa99e4ec3544f22
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _legacyKeyHolder_CopyMasterAESKeyAndIV(undefined8 param_1,long *param_2,long *param_3)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  
  lVar1 = func_0x00025810ac50();
  lVar2 = func_0x0002580f6ff0(*(undefined8 *)(lVar1 + 0x30),lVar1 + 0x10,0x10);
  if (lVar2 == 0) {
    uVar3 = 0xfffee7d8;
    _legacyKeyHolder_CopyMasterAESKeyAndIV_cold_2();
  }
  else {
    lVar1 = func_0x0002580f6ff0(*(undefined8 *)(lVar1 + 0x30),lVar1 + 0x20,0x10);
    if (lVar1 == 0) {
      uVar3 = 0xfffee7d8;
      _legacyKeyHolder_CopyMasterAESKeyAndIV_cold_1(lVar2);
    }
    else {
      uVar3 = 0;
      *param_2 = lVar2;
      *param_3 = lVar1;
    }
  }
  return uVar3;
}


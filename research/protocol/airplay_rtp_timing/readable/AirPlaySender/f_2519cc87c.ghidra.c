/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519cc87c
 * original code SHA256: ccd5146711f671c5c23fc47d6b7a8c7a294bbca4d6b832cb5f908d4f47f7683e
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _APAudioSinkJitterBufferCreate(undefined8 param_1,undefined8 *param_2,long *param_3)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  long local_38;
  
  local_38 = 0;
  if (param_3 == (long *)0x0) {
    _APAudioSinkJitterBufferCreate_cold_2();
    uVar2 = 0xffffbe68;
  }
  else {
    uVar2 = func_0x00025810f370();
    uVar2 = func_0x00025810acc0(param_1,&_kAPAudioSinkJitterBufferVTable,uVar2,&local_38);
    if ((int)uVar2 == 0) {
      lVar3 = func_0x00025810ac50(local_38);
      uVar2 = param_2[4];
      uVar6 = *param_2;
      uVar5 = param_2[3];
      uVar4 = param_2[2];
      *(undefined8 *)(lVar3 + 0x48) = param_2[1];
      *(undefined8 *)(lVar3 + 0x40) = uVar6;
      *(undefined8 *)(lVar3 + 0x58) = uVar5;
      *(undefined8 *)(lVar3 + 0x50) = uVar4;
      *(undefined8 *)(lVar3 + 0x60) = uVar2;
      uVar6 = param_2[1];
      uVar5 = *param_2;
      uVar4 = param_2[3];
      uVar2 = param_2[2];
      *(undefined8 *)(lVar3 + 0x38) = param_2[4];
      *(undefined8 *)(lVar3 + 0x20) = uVar6;
      *(undefined8 *)(lVar3 + 0x18) = uVar5;
      *(undefined8 *)(lVar3 + 0x30) = uVar4;
      *(undefined8 *)(lVar3 + 0x28) = uVar2;
      *(undefined4 *)(lVar3 + 0x10) = 0x32;
      *(undefined1 *)(lVar3 + 0x70) = 0;
      if ((_gLogCategory_APAudioSinkJitterBuffer < 0x1f) &&
         ((_gLogCategory_APAudioSinkJitterBuffer != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APAudioSinkJitterBuffer,0x200001e), iVar1 != 0
          )))) {
        _APAudioSinkJitterBufferCreate_cold_1();
      }
      uVar2 = 0;
      *param_3 = local_38;
    }
    else {
      func_0x000258109a30(uVar2,"APAudioSinkJitterBufferCreate",0x179,0);
      if (local_38 != 0) {
        func_0x0002580f5830();
      }
    }
  }
  return uVar2;
}


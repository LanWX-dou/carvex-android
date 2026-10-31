/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251abe4c8
 * original code SHA256: eed75584793286303aa5d1af3b1b7a01bbee4e1b06f987366a75944931a3403d
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251abe550) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_bufferedAudioEngine_generateEncryptionKeyAndCryptor(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  code *pcVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  long lVar7;
  long local_70;
  undefined1 auStack_68 [32];
  long local_48;
  
  local_48 = *_DAT_2681b4ee0;
  lVar2 = func_0x00025810ac50();
  local_70 = 0;
  uVar6 = *(undefined8 *)(lVar2 + 0x208);
  lVar3 = func_0x000258109150(uVar6);
  puVar5 = (undefined8 *)(*(long *)(lVar3 + 0x10) + 0x20);
  pcVar4 = (code *)*puVar5;
  if ((pcVar4 != (code *)0x0) && (pcVar4 != (code *)0x0)) {
    (*pcVar4)((ulong)puVar5 & 0xffffffffffff | 0xbb77000000000000,uVar6);
  }
  func_0x000258101e80(auStack_68,0x20);
  uVar6 = *_DAT_2680d3150;
  lVar3 = func_0x0002580f6ff0(uVar6,auStack_68,0x20);
  lVar7 = *(long *)(lVar2 + 0x360);
  *(long *)(lVar2 + 0x360) = lVar3;
  if (lVar3 != 0) {
    func_0x0002580f6a60(lVar3);
  }
  if (lVar7 != 0) {
    func_0x0002580f5830(lVar7);
  }
  if ((int)param_2 != 0) {
    param_2 = func_0x000258109690(uVar6,lVar3,1,&local_70);
    if ((int)param_2 == 0) {
      if ((_gLogCategory_APAudioEngineBuffered < 0x29) &&
         ((_gLogCategory_APAudioEngineBuffered != -1 ||
          (iVar1 = func_0x000258101e40(&_gLogCategory_APAudioEngineBuffered,0x2000028), iVar1 != 0))
         )) {
        _bufferedAudioEngine_generateEncryptionKeyAndCryptor_cold_2(param_1);
      }
      lVar7 = *(long *)(lVar2 + 0x218);
      *(long *)(lVar2 + 0x218) = local_70;
      if (local_70 != 0) {
        func_0x0002580f6a60();
      }
      if (lVar7 != 0) {
        func_0x0002580f5830(lVar7);
      }
      param_2 = 0;
    }
    else {
      _bufferedAudioEngine_generateEncryptionKeyAndCryptor_cold_1();
    }
  }
  if (lVar3 != 0) {
    func_0x0002580f5830(lVar3);
  }
  if (local_70 != 0) {
    func_0x0002580f5830();
  }
  if (*_DAT_2681b4ee0 == local_48) {
    return param_2;
  }
  uVar6 = func_0x0002580f4380();
  return uVar6;
}


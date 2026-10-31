/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x25185ba2c
 * original code SHA256: 7ee000ab86fa7d211af601f71268556d770655ef00b8c15d2d357d115ba42837
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _aprscreen_decryptBuffer(undefined8 param_1,long param_2,uint *param_3)

{
  char cVar1;
  long lVar2;
  bool bVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  uint uVar7;
  ulong uVar8;
  uint local_44;
  
  lVar5 = func_0x00025810ac50();
  local_44 = 0;
  if (param_2 == 0) {
    return 0;
  }
  if (*(char *)(lVar5 + 4) != '\0') {
    return 0;
  }
  uVar7 = *param_3;
  if (*(char *)(lVar5 + 0x160) == '\0') {
    if (*(char *)(lVar5 + 0x2c0) != '\0') {
      uVar8 = func_0x0002581091d0(lVar5 + 0x290,param_2,uVar7,param_2);
      local_44 = (uint)uVar8;
      if (local_44 != 0) {
        func_0x000258109a30(uVar8,"aprscreen_decryptBuffer",0x261,0);
        goto LAB_25185bbc4;
      }
    }
LAB_25185bb3c:
    uVar8 = 0;
    *param_3 = uVar7;
  }
  else {
    bVar3 = uVar7 < 0x10;
    uVar7 = uVar7 - 0x10;
    uVar8 = (ulong)uVar7;
    if (bVar3) {
      return 0;
    }
    lVar2 = lVar5 + 0x288;
    func_0x00025810be90(lVar5 + 0x168,lVar5 + 0x268,lVar2);
    func_0x00025810be70(lVar5 + 0x168,lVar5,0x80);
    lVar6 = func_0x00025810be80(lVar5 + 0x168,param_2,uVar8,param_2);
    lVar5 = func_0x00025810bea0(lVar5 + 0x168,param_2 + lVar6,param_2 + uVar8,&local_44);
    if (local_44 == 0) {
      if (lVar5 + lVar6 == uVar8) {
        lVar5 = 0;
        lVar6 = 7;
        do {
          cVar1 = *(char *)(lVar2 + lVar5) + '\x01';
          *(char *)(lVar2 + lVar5) = cVar1;
          lVar5 = lVar5 + 1;
          bVar3 = lVar6 != 0;
          lVar6 = lVar6 + -1;
        } while (cVar1 == '\0' && bVar3);
        goto LAB_25185bb3c;
      }
      func_0x000258109a30(0,"aprscreen_decryptBuffer",599,0);
      uVar8 = 0xffffe596;
      local_44 = 0xffffe596;
    }
    else {
      func_0x000258109a30(local_44,"aprscreen_decryptBuffer",0x256,0);
      uVar8 = (ulong)local_44;
      if (local_44 == 0) {
        return 0;
      }
    }
LAB_25185bbc4:
    if (_gLogCategory_APReceiverScreenSession < 0x5b) {
      if (_gLogCategory_APReceiverScreenSession == -1) {
        iVar4 = func_0x000258101e40(&_gLogCategory_APReceiverScreenSession,0x200005a);
        if (iVar4 == 0) {
          return (ulong)local_44;
        }
      }
      func_0x000258101eb0(&_gLogCategory_APReceiverScreenSession,
                          "OSStatus aprscreen_decryptBuffer(APReceiverScreenSessionRef, uint8_t *, uint32_t *)"
                          ,0x200005a,"### Decrypt frame error: %#m\n");
      uVar8 = (ulong)local_44;
    }
  }
  return uVar8;
}


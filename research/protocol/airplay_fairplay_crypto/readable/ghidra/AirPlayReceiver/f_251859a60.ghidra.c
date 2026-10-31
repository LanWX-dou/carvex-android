/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251859a60
 * original code SHA256: d72e408b258be98e49e1df91a062f8c95f3a48d36a6653d9dfbf3e63c0a09408
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _aprscreen_SetSecurityInfoChaCha(undefined8 param_1,undefined8 *param_2,long param_3)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  undefined1 *puVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  lVar3 = func_0x00025810ac50();
  if ((param_2 == (undefined8 *)0x0) || (param_3 != 0x20)) {
    func_0x000258109a30(0,"aprscreen_SetSecurityInfoChaCha",0x209,0);
    uVar6 = 0xfffee647;
  }
  else {
    func_0x00025810b430(*(undefined8 *)(lVar3 + 200));
    if ((*(char *)(lVar3 + 0xb9) == '\0') && (*(char *)(lVar3 + 0xb8) == '\0')) {
      lVar5 = -0x130;
      puVar4 = (undefined1 *)(lVar3 + 0x160);
      do {
        *puVar4 = 0;
        bVar1 = lVar5 != -1;
        lVar5 = lVar5 + 1;
        puVar4 = puVar4 + 1;
      } while (bVar1);
      uVar6 = 0;
      uVar7 = *param_2;
      uVar9 = param_2[3];
      uVar8 = param_2[2];
      *(undefined8 *)(lVar3 + 0x270) = param_2[1];
      *(undefined8 *)(lVar3 + 0x268) = uVar7;
      *(undefined8 *)(lVar3 + 0x280) = uVar9;
      *(undefined8 *)(lVar3 + 0x278) = uVar8;
      *(undefined1 *)(lVar3 + 0x160) = 1;
    }
    else {
      uVar6 = 0xfffee645;
      if ((_gLogCategory_APReceiverScreenSession < 0x5b) &&
         ((_gLogCategory_APReceiverScreenSession != -1 ||
          (iVar2 = func_0x000258101e40(&_gLogCategory_APReceiverScreenSession,0x200005a), iVar2 != 0
          )))) {
        func_0x000258101eb0(&_gLogCategory_APReceiverScreenSession,
                            "OSStatus aprscreen_SetSecurityInfoChaCha(APReceiverScreenSessionRef, const uint8_t *, size_t)"
                            ,0x200005a,
                            "### Screen session %{ptr}: can\'t set ChaCha security info in this state\n"
                           );
      }
    }
    func_0x00025810b440(*(undefined8 *)(lVar3 + 200));
  }
  return uVar6;
}


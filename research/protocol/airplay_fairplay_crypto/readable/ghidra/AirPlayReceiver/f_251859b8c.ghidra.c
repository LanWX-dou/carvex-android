/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251859b8c
 * original code SHA256: ef26b2fcb090958f4e6a95d4d48fb9390d4fdb8844b01c0be68912fe3f1ab0f3
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _aprscreen_SetSecurityInfoAES(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  
  lVar2 = func_0x00025810ac50();
  func_0x00025810b430(*(undefined8 *)(lVar2 + 200));
  if ((*(char *)(lVar2 + 0xb9) == '\0') && (*(char *)(lVar2 + 0xb8) == '\0')) {
    if (*(char *)(lVar2 + 0x2c0) != '\0') {
      func_0x0002581091b0(lVar2 + 0x290);
      *(undefined1 *)(lVar2 + 0x2c0) = 0;
    }
    uVar3 = func_0x0002581091c0(lVar2 + 0x290,param_2,param_3);
    *(bool *)(lVar2 + 0x2c0) = (int)uVar3 == 0;
  }
  else {
    uVar3 = 0xfffee645;
    if ((_gLogCategory_APReceiverScreenSession < 0x5b) &&
       ((_gLogCategory_APReceiverScreenSession != -1 ||
        (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverScreenSession,0x200005a), iVar1 != 0))
       )) {
      func_0x000258101eb0(&_gLogCategory_APReceiverScreenSession,
                          "OSStatus aprscreen_SetSecurityInfoAES(APReceiverScreenSessionRef, const uint8_t *, const uint8_t *)"
                          ,0x200005a,
                          "### Screen session %{ptr}: can\'t set AES security info in this state\n")
      ;
    }
  }
  func_0x00025810b440(*(undefined8 *)(lVar2 + 200));
  return uVar3;
}


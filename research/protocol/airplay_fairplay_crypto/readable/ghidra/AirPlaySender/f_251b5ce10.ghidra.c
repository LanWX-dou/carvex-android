/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b5ce10
 * original code SHA256: 82c2c3485d8146c1535e837d77bb4784cfff92714cbe8821f05ad534690fb880
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _apsession_ensureKeyHolderSetUp(undefined8 param_1)

{
  char in_NG;
  undefined1 in_ZR;
  char in_OV;
  bool bVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  int extraout_w8;
  int extraout_w8_00;
  int extraout_w8_01;
  undefined1 auVar8 [16];
  long local_38;
  
  lVar3 = func_0x00025810ac50();
  func_0x00025810b430(*(undefined8 *)(lVar3 + 200));
  if (*(long *)(lVar3 + 0x150) != 0) {
    uVar6 = 0;
    goto LAB_251b5cf6c;
  }
  lVar4 = func_0x00025810ac50(param_1);
  local_38 = 0;
  _OUTLINED_FUNCTION_131
            (&_kAPEndpointDescriptionProperty_SupportsCoreUtilsPairingAndEncryption,
             *(undefined8 *)(lVar4 + 0x30));
  lVar5 = func_0x000258109860();
  if ((*(char *)(lVar4 + 0x40) == '\0') || (lVar5 != 0)) {
    if (lVar5 == 0) {
      _OUTLINED_FUNCTION_13(0,*(undefined8 *)(lVar4 + 0x140),*(undefined8 *)(lVar4 + 0x138));
      uVar6 = _APKeyHolderLegacyCreate();
      if ((int)uVar6 == 0) {
        _OUTLINED_FUNCTION_5();
        lVar4 = local_38;
        if ((bool)in_ZR || in_NG != in_OV) {
          if (extraout_w8_01 == -1) {
            iVar2 = _OUTLINED_FUNCTION_3();
            goto joined_r0x000251b5cf3c;
          }
          goto LAB_251b5cf48;
        }
        goto LAB_251b5cf64;
      }
      uVar7 = 0x1721;
LAB_251b5cfd4:
      func_0x000258109a30(uVar6,"apsession_createKeyHolder",uVar7,0);
      goto LAB_251b5cec0;
    }
    auVar8 = _OUTLINED_FUNCTION_13(lVar5,*(undefined8 *)(lVar4 + 0x140));
    uVar6 = _APKeyHolderCoreUtilsCreate(auVar8._0_8_,auVar8._8_8_,&local_38);
    if ((int)uVar6 != 0) {
      uVar7 = 0x171b;
      goto LAB_251b5cfd4;
    }
    _OUTLINED_FUNCTION_5();
    lVar4 = local_38;
    if ((bool)in_ZR || in_NG != in_OV) {
      if (extraout_w8_00 == -1) {
        iVar2 = _OUTLINED_FUNCTION_3();
joined_r0x000251b5cf3c:
        lVar4 = local_38;
        if (iVar2 == 0) goto LAB_251b5cf64;
      }
LAB_251b5cf48:
      uVar6 = _OUTLINED_FUNCTION_11(local_38);
      _OUTLINED_FUNCTION_10
                (uVar6,"OSStatus apsession_createKeyHolder(APSenderSessionRef, APSKeyHolderRef *)");
      func_0x000258101eb0();
      lVar4 = local_38;
    }
  }
  else {
    _OUTLINED_FUNCTION_31();
    bVar1 = extraout_w8 == 0x5a;
    if (extraout_w8 < 0x5b) {
      _OUTLINED_FUNCTION_85();
      if (bVar1) {
        uVar6 = _OUTLINED_FUNCTION_19();
        iVar2 = func_0x000258101e40(uVar6,0x5a);
        if (iVar2 == 0) goto LAB_251b5cebc;
      }
      auVar8 = _OUTLINED_FUNCTION_19();
      func_0x000258101eb0(auVar8._0_8_,auVar8._8_8_,0x5a,
                          "*** [%{ptr}] %###s: Authentication/encryption disabled ***\n");
    }
LAB_251b5cebc:
    uVar6 = 0;
LAB_251b5cec0:
    if (local_38 != 0) {
      func_0x0002580f5830();
    }
    if ((int)uVar6 != 0) {
      func_0x000258109a30(uVar6,"apsession_ensureKeyHolderSetUp",0x173d,0);
      goto LAB_251b5cf6c;
    }
    lVar4 = 0;
  }
LAB_251b5cf64:
  uVar6 = 0;
  *(long *)(lVar3 + 0x150) = lVar4;
LAB_251b5cf6c:
  func_0x00025810b440(*(undefined8 *)(lVar3 + 200));
  return uVar6;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100183690
 * original code SHA256: be8d508e933ea3c8153c4003fe8ca51c34b59bd44d1def4583d29ab95977aa63
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_sessionFileTransfer_cleanup(long param_1)

{
  char cVar1;
  undefined1 uVar2;
  char cVar3;
  bool bVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 unaff_x20;
  undefined8 *puVar7;
  undefined1 auVar8 [16];
  
  uVar6 = 0;
  if (param_1 != 0) {
    puVar7 = *(undefined8 **)(param_1 + 0x1b8);
    if (puVar7 == (undefined8 *)0x0) {
      uVar6 = 0;
    }
    else {
      bVar4 = _gLogObjects == 0;
      cVar3 = !bVar4 && SBORROW4(_gNumLogObjects,0x1b);
      uVar2 = !bVar4 && _gNumLogObjects == 0x1b;
      cVar1 = bVar4 || _gNumLogObjects + -0x1b < 0;
      if (bVar4 || _gNumLogObjects < 0x1b) {
        _OUTLINED_FUNCTION_9();
        if (!(bool)uVar2) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_27();
      }
      else {
        unaff_x20 = *(undefined8 *)(_gLogObjects + 0xd0);
      }
      iVar5 = _os_log_type_enabled(unaff_x20,1);
      if (iVar5 != 0) {
        _iAP2ListArrayGetCount(*puVar7);
        _iAP2ListArrayGetCount(puVar7[1]);
        _iAP2ListArrayGetCount(puVar7[2]);
        _OUTLINED_FUNCTION_6();
        auVar8 = _OUTLINED_FUNCTION_44();
        __os_log_impl(auVar8._0_8_,auVar8._8_8_,1);
      }
      _iap2_sessionFileTransfer_cleanUpRemoveTransferList(param_1);
      iVar5 = _iAP2ListArrayGetCount(*puVar7);
      if (((iVar5 != 0) || (iVar5 = _iAP2ListArrayGetCount(puVar7[1]), iVar5 != 0)) ||
         (iVar5 = _iAP2ListArrayGetCount(puVar7[2]), iVar5 != 0)) {
        if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_13(), cVar1 != cVar3)) {
          _OUTLINED_FUNCTION_9();
          if (!(bool)uVar2) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
          }
          _OUTLINED_FUNCTION_27();
        }
        iVar5 = _OUTLINED_FUNCTION_71();
        if (iVar5 != 0) {
          _iAP2ListArrayGetCount(*puVar7);
          _iAP2ListArrayGetCount(puVar7[1]);
          _iAP2ListArrayGetCount(puVar7[2]);
          _OUTLINED_FUNCTION_6();
          auVar8 = _OUTLINED_FUNCTION_44();
          __os_log_impl(auVar8._0_8_,auVar8._8_8_,0);
        }
      }
      if ((void *)*puVar7 != (void *)0x0) {
        _free((void *)*puVar7);
        *puVar7 = 0;
      }
      if ((void *)puVar7[1] != (void *)0x0) {
        _free((void *)puVar7[1]);
        puVar7[1] = 0;
      }
      if ((void *)puVar7[2] != (void *)0x0) {
        _free((void *)puVar7[2]);
        puVar7[2] = 0;
      }
      if (*(void **)(param_1 + 0x1b8) != (void *)0x0) {
        _free(*(void **)(param_1 + 0x1b8));
        *(undefined8 *)(param_1 + 0x1b8) = 0;
      }
      uVar6 = 1;
    }
  }
  return uVar6;
}


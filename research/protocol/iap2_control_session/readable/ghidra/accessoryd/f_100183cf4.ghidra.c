/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100183cf4
 * original code SHA256: 80d30568c1ce7d2a15e7c0ea10956ab97b316949cfcb6fed21de8fa58ba114c0
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_sessionFileTransfer_findTransferEntry(long param_1,uint param_2)

{
  int iVar1;
  undefined8 uVar2;
  char *pcVar3;
  long lVar4;
  undefined *puVar5;
  long *plVar6;
  undefined1 local_88;
  undefined7 uStack_87;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined4 local_70;
  uint local_6c;
  uint local_62;
  
  if (param_1 == 0) {
    return 0;
  }
  plVar6 = *(long **)(param_1 + 0x1b8);
  if (plVar6 == (long *)0x0) {
    return 0;
  }
  puVar5 = PTR___os_log_default_10022bbb0;
  if ((param_2 >> 7 & 1) == 0) {
    plVar6 = plVar6 + 1;
    if (*plVar6 == 0) {
      return 0;
    }
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1b)) {
      if (_logObjectForModule_onceToken != -1) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
        puVar5 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar5 = *(undefined **)(_gLogObjects + 0xd0);
    }
    iVar1 = _os_log_type_enabled(puVar5,2);
    if (iVar1 == 0) goto LAB_100183dec;
    _OUTLINED_FUNCTION_2(*(undefined8 *)(param_1 + 8),DAT_1001b30f0);
    local_62 = param_2;
    uVar2 = _OUTLINED_FUNCTION_6();
    pcVar3 = "iap2_sessionFileTransfer_findTransferEntry: %@ bufferID=%u, use inTransferList";
  }
  else {
    if (*plVar6 == 0) {
      return 0;
    }
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1b)) {
      if (_logObjectForModule_onceToken != -1) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
        puVar5 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar5 = *(undefined **)(_gLogObjects + 0xd0);
    }
    iVar1 = _os_log_type_enabled(puVar5,2);
    if (iVar1 == 0) goto LAB_100183dec;
    _OUTLINED_FUNCTION_2(*(undefined8 *)(param_1 + 8),DAT_1001b30f0);
    local_62 = param_2;
    uVar2 = _OUTLINED_FUNCTION_6();
    pcVar3 = "iap2_sessionFileTransfer_findTransferEntry: %@ bufferID=%u, use outTransferList";
  }
  __os_log_debug_impl(uVar2,puVar5,2,pcVar3,&local_70,0x12);
LAB_100183dec:
  lVar4 = *plVar6;
  uStack_80 = 0;
  _local_88 = CONCAT71(0xaaaaaaaaaaaaaa,(char)param_2);
  local_78 = 0;
  uVar2 = _iAP2ListArrayFindItem(lVar4,&local_88,__compareBufferID);
  if ((int)uVar2 == 0xff) {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1b)) {
      if (_logObjectForModule_onceToken != -1) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_27();
    }
    iVar1 = _OUTLINED_FUNCTION_71();
    if (iVar1 != 0) {
      local_70 = (undefined4)DAT_1001b30b0;
      local_6c = param_2;
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_11();
      __os_log_impl();
    }
    return 0;
  }
  uVar2 = _iAP2ListArrayItemForIndex(lVar4,uVar2);
  return uVar2;
}


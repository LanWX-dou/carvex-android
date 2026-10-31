/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100152520
 * original code SHA256: fbfb9a9912c7a41d80d15e24db2e45a865f2744dbba537455bc6974f2f62d6db
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void __appLinksiAP2LinkEventNotifyHandler(long param_1,int param_2,long param_3)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  long lVar8;
  byte *pbVar9;
  
  if (param_1 == 0) {
    return;
  }
  cVar1 = SBORROW4(param_2,1);
  cVar2 = param_2 + -1 < 0;
  uVar3 = param_2 == 1;
  if (!(bool)uVar3) {
    return;
  }
  if (param_3 == 0) {
    pbVar9 = (byte *)0x0;
  }
  else {
    pbVar9 = *(byte **)(param_3 + 0x40);
  }
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_25();
    if (!(bool)uVar3) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  iVar5 = _OUTLINED_FUNCTION_15();
  if (iVar5 != 0) {
    _obfuscatedPointer(param_3);
    if (param_3 == 0) {
      uVar3 = 0;
    }
    else {
      _obfuscatedPointer(*(undefined8 *)(param_3 + 0x40));
      uVar3 = *(undefined1 *)(param_3 + 0x6d);
    }
    _OUTLINED_FUNCTION_21(uVar3);
    _OUTLINED_FUNCTION_39();
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_14();
    __os_log_debug_impl();
  }
  if (param_3 == 0) {
    return;
  }
  if (*(long *)(param_3 + 0x40) == 0) {
    return;
  }
  if (*(short *)(param_3 + 0x70) != 8) {
    return;
  }
  if (*(long *)(param_1 + 0xb0) == 0) {
    return;
  }
  lVar8 = *(long *)(*(long *)(param_1 + 0xb0) + 0x10);
  if (lVar8 == 0) {
    return;
  }
  if (pbVar9 == (byte *)0x0) {
    return;
  }
  iVar5 = *(int *)(param_3 + 0x68);
  if (iVar5 == 2) {
    uVar7 = (uint)pbVar9[2];
    cVar1 = SBORROW4(uVar7,1);
    cVar2 = (int)(uVar7 - 1) < 0;
    uVar4 = uVar7 == 1;
    uVar3 = 0;
    if (!(bool)uVar4) goto LAB_100152714;
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar2 != cVar1)) {
      _OUTLINED_FUNCTION_25();
      if (!(bool)uVar4) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      iVar5 = *(int *)(param_3 + 0x68);
      _OUTLINED_FUNCTION_15();
    }
    else {
      iVar5 = 2;
    }
    iVar6 = _OUTLINED_FUNCTION_15();
    if (iVar6 != 0) {
      _OUTLINED_FUNCTION_1(*(undefined1 *)(param_3 + 0x6d),DAT_1001b3358);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_14();
      __os_log_debug_impl();
      iVar5 = *(int *)(param_3 + 0x68);
    }
    pbVar9[3] = 1;
  }
  cVar1 = SBORROW4(iVar5,3);
  cVar2 = iVar5 + -3 < 0;
  uVar3 = 0;
  if (iVar5 == 3) {
    uVar7 = (uint)pbVar9[1];
    cVar1 = SBORROW4(uVar7,1);
    cVar2 = (int)(uVar7 - 1) < 0;
    uVar3 = uVar7 == 1;
    if ((bool)uVar3) {
      if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar2 != cVar1)) {
        _OUTLINED_FUNCTION_25();
        if (!(bool)uVar3) {
          _OUTLINED_FUNCTION_0();
          _dispatch_once();
        }
        _OUTLINED_FUNCTION_15();
      }
      iVar5 = _OUTLINED_FUNCTION_15();
      if (iVar5 != 0) {
        _OUTLINED_FUNCTION_8();
        _OUTLINED_FUNCTION_1(DAT_1001b3358);
        _OUTLINED_FUNCTION_6();
        _OUTLINED_FUNCTION_14();
        __os_log_debug_impl();
      }
      pbVar9[2] = 1;
    }
  }
LAB_100152714:
  if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar2 != cVar1)) {
    _OUTLINED_FUNCTION_25();
    if (!(bool)uVar3) {
      _OUTLINED_FUNCTION_0();
      _dispatch_once();
    }
    _OUTLINED_FUNCTION_15();
  }
  iVar6 = _OUTLINED_FUNCTION_15();
  iVar5 = *(int *)(param_3 + 0x68);
  if (iVar6 != 0) {
    _OUTLINED_FUNCTION_6();
    _OUTLINED_FUNCTION_14();
    __os_log_debug_impl();
    iVar5 = *(int *)(param_3 + 0x68);
  }
  pbVar9[1] = iVar5 == 1;
  uVar7 = (uint)*pbVar9;
  cVar1 = SBORROW4(uVar7,1);
  cVar2 = (int)(uVar7 - 1) < 0;
  uVar3 = uVar7 == 1;
  if ((bool)uVar3) {
    if ((_gLogObjects == 0) || (_OUTLINED_FUNCTION_12(), cVar2 != cVar1)) {
      _OUTLINED_FUNCTION_25();
      if (!(bool)uVar3) {
        _OUTLINED_FUNCTION_0();
        _dispatch_once();
      }
      _OUTLINED_FUNCTION_15();
    }
    _OUTLINED_FUNCTION_13();
    iVar5 = _os_log_type_enabled();
    if (iVar5 != 0) {
      _OUTLINED_FUNCTION_8();
      _OUTLINED_FUNCTION_1(DAT_1001b3100);
      _OUTLINED_FUNCTION_6();
      _OUTLINED_FUNCTION_10();
      __os_log_impl();
    }
    *pbVar9 = 0;
    _iAP2FileTransferCancel(param_3);
    _iap2_sessionFileTransfer_removeTransferForFeature(lVar8,0x18,param_3);
    if (*(void **)(param_3 + 0x40) != (void *)0x0) {
      _free(*(void **)(param_3 + 0x40));
      *(undefined8 *)(param_3 + 0x40) = 0;
    }
  }
  return;
}


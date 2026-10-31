/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10004f254
 * original code SHA256: 74c679edc3d6d765f09bfada51a9ef24fa1a44e94c1cb260f2842d5f5049cf03
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _cbIdentificationInfoSerialTransportComponentParams
              (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined2 *param_4)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  undefined *puVar5;
  undefined4 local_40;
  uint local_3c;
  int local_34;
  
  local_34 = 0;
  uVar2 = _iAP2MsgGetParamID(param_3);
  if (uVar2 == 2) {
    iVar3 = _iAP2MsgIsDataVoid(param_3);
    if (iVar3 == 0) {
      *(undefined1 *)(param_4 + 8) = 0xff;
      local_34 = 1;
    }
    else {
      *(undefined1 *)(param_4 + 8) = 1;
    }
  }
  else if (uVar2 == 1) {
    lVar4 = _iAP2MsgCopyDataAsCFString(param_3,&local_34);
    if (local_34 == 0) {
      if (*(long *)(param_4 + 4) != 0) {
        _CFRelease();
      }
      *(long *)(param_4 + 4) = lVar4;
    }
    else if (lVar4 != 0) {
      _CFRelease(lVar4);
    }
  }
  else if (uVar2 == 0) {
    uVar1 = _iAP2MsgGetDataAsU16(param_3,&local_34);
    if (local_34 == 0) {
      *param_4 = uVar1;
    }
  }
  else {
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1d)) {
      puVar5 = PTR___os_log_default_10022bbb0;
      if (DAT_10023e660 != -1) {
        __addRejectParam_cold_1();
        puVar5 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar5 = *(undefined **)(_gLogObjects + 0xe0);
    }
    iVar3 = _os_log_type_enabled(puVar5,1);
    if (iVar3 != 0) {
      local_40 = (undefined4)DAT_1001b30b0;
      local_3c = uVar2;
      __os_log_impl(0x100000000,puVar5,1,
                    "iAP2MsgIdentificationInfo SerialTransportComponent unhandled sub-paramID:%04X\n"
                    ,&local_40,8);
    }
  }
  if (uVar2 < *(uint *)(*(long **)(param_4 + 0x24) + 1)) {
    lVar4 = **(long **)(param_4 + 0x24);
    *(int *)(lVar4 + (ulong)uVar2 * 4) = *(int *)(lVar4 + (ulong)uVar2 * 4) + 1;
  }
  return local_34;
}


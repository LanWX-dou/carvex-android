/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000512e8
 * original code SHA256: 1ffe2ab259762fcd0fccfa69489e707e34a58980a0405bf6b63fb1a05751bfb1
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool __parseIdentificationParams(long param_1,undefined8 param_2,undefined8 param_3)

{
  undefined1 *puVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uVar7;
  ulong uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  code *pcVar11;
  undefined *puVar12;
  long *plVar13;
  undefined1 *local_50;
  int local_44;
  
  local_44 = 0;
  if ((param_1 == 0) || (lVar4 = _iap2_identification_getIdentificationInfo(), lVar4 == 0)) {
    local_44 = 1;
    goto LAB_10005160c;
  }
  uVar5 = _iAP2MsgGetParamID(param_3);
  uVar2 = (uint)uVar5;
  if (0x22 < uVar2) {
switchD_100051358_caseD_8:
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1d)) {
      puVar12 = PTR___os_log_default_10022bbb0;
      if (DAT_10023e660 != -1) {
        __addRejectParam_cold_1();
        puVar12 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar12 = *(undefined **)(_gLogObjects + 0xe0);
    }
    iVar3 = _os_log_type_enabled(puVar12,0);
    uVar8 = uVar5;
    if (iVar3 != 0) {
      local_50 = (undefined1 *)CONCAT44(uVar2,(int)DAT_1001b30b0);
      __os_log_impl(0x100000000,puVar12,0,"iAP2MsgIdentificationInfo unhandled paramID:%04X\n",
                    &local_50,8);
    }
LAB_100051698:
    __addRejectParam(lVar4,uVar8,1);
    local_44 = 1;
    goto LAB_1000515ec;
  }
  switch(uVar5 & 0xffffffff) {
  default:
    plVar13 = (long *)(lVar4 + 8);
    lVar6 = *plVar13;
    break;
  case 1:
    plVar13 = (long *)(lVar4 + 0x10);
    lVar6 = *plVar13;
    break;
  case 2:
    plVar13 = (long *)(lVar4 + 0x18);
    lVar6 = *plVar13;
    break;
  case 3:
    plVar13 = (long *)(lVar4 + 0x20);
    lVar6 = *plVar13;
    break;
  case 4:
    plVar13 = (long *)(lVar4 + 0x28);
    lVar6 = *plVar13;
    break;
  case 5:
    plVar13 = (long *)(lVar4 + 0x30);
    lVar6 = *plVar13;
    break;
  case 6:
    uVar10 = _iAP2MsgGetDataAsData(param_3,&local_44);
    if (local_44 != 0) {
      *(undefined1 *)(lVar4 + 0xb8) = 1;
      _CFStringAppendFormat(*(undefined8 *)(lVar4 + 0xd8),0,&cf__msgID_0x_04xReason__s_);
      uVar10 = 0;
      goto LAB_10005152c;
    }
    uVar7 = _iAP2MsgGetParamValueLen(param_3);
    uVar9 = 1;
LAB_100051754:
    local_44 = _iap2_identification_processMessagesSet(lVar4,uVar10,uVar7,uVar9);
    goto LAB_1000515ec;
  case 7:
    uVar10 = _iAP2MsgGetDataAsData(param_3,&local_44);
    if (local_44 == 0) {
      uVar7 = _iAP2MsgGetParamValueLen(param_3);
      uVar9 = 0;
      goto LAB_100051754;
    }
    *(undefined1 *)(lVar4 + 0xb9) = 1;
    _CFStringAppendFormat(*(undefined8 *)(lVar4 + 0xe0),0,&cf__msgID_0x_04xReason__s_);
    uVar10 = 1;
LAB_10005152c:
    _iap2_identification_addMsgListParamWithDirection(lVar4,uVar10);
    goto LAB_1000515ec;
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0x12:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x19:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
    goto switchD_100051358_caseD_8;
  case 0xc:
    plVar13 = (long *)(lVar4 + 0x50);
    lVar6 = *plVar13;
    break;
  case 0xd:
    local_50 = &DAT_aaaaaaaaaaaaaaaa;
    local_44 = _iap2_identification_processStringParam(lVar4,param_3,&local_50);
    if (local_44 == 0) {
      lVar6 = *(long *)(lVar4 + 0x58);
      if (lVar6 == 0) {
        lVar6 = _CFSetCreateMutable(*(undefined8 *)PTR__kCFAllocatorDefault_10022bce0,1,
                                    PTR__kCFTypeSetCallBacks_10022bd50);
        *(long *)(lVar4 + 0x58) = lVar6;
      }
      puVar1 = local_50;
      iVar3 = _CFSetContainsValue(lVar6,local_50);
      if (iVar3 == 0) {
        _CFSetAddValue(*(undefined8 *)(lVar4 + 0x58),puVar1);
      }
      else {
        __addRejectParam(lVar4,0xd,4);
        local_44 = 1;
      }
      if (puVar1 != (undefined1 *)0x0) {
        _CFRelease(puVar1);
      }
    }
    else {
      __addRejectParam(lVar4,0xd,8);
    }
    goto LAB_1000515ec;
  case 0xe:
    pcVar11 = _cbIdentificationInfoSerialTransportComponentParams;
    uVar10 = 0;
    goto LAB_1000515e4;
  case 0xf:
    pcVar11 = _cbIdentificationInfoUSBDeviceTransportComponentParams;
    uVar10 = 1;
    goto LAB_1000515e4;
  case 0x10:
    pcVar11 = _cbIdentificationInfoUSBHostTransportComponentParams;
    uVar10 = 2;
    goto LAB_1000515e4;
  case 0x11:
    pcVar11 = _cbIdentificationInfoBluetoothTransportComponentParams;
    uVar10 = 3;
    goto LAB_1000515e4;
  case 0x13:
    uVar8 = 0x13;
    goto LAB_100051698;
  case 0x18:
    pcVar11 = _cbIdentificationInfoWirelessCarPlayTransportComponentParams;
    uVar10 = 4;
    goto LAB_1000515e4;
  case 0x1a:
    pcVar11 = _cbIdentificationInfoBluetoothLETransportComponentParams;
    uVar10 = 5;
LAB_1000515e4:
    local_44 = _iap2_identification_parseTransportComponent
                         (param_1,lVar4,param_2,param_3,uVar10,pcVar11);
    goto LAB_1000515ec;
  case 0x22:
    plVar13 = (long *)(lVar4 + 0x40);
    lVar6 = *plVar13;
  }
  if (lVar6 != 0) {
    _CFRelease();
    *plVar13 = 0;
  }
  local_44 = _iap2_identification_processStringParam(lVar4,param_3,plVar13);
LAB_1000515ec:
  if (uVar2 < *(uint *)(*(long **)(lVar4 + 0xe8) + 1)) {
    lVar4 = **(long **)(lVar4 + 0xe8);
    *(int *)(lVar4 + (uVar5 & 0xffffffff) * 4) = *(int *)(lVar4 + (uVar5 & 0xffffffff) * 4) + 1;
  }
LAB_10005160c:
  return local_44 == 0;
}


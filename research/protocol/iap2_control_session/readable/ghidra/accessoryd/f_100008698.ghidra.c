/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100008698
 * original code SHA256: 6eff63dd9f12d8230c89f55ddeb6e6ffe10d5c7f5367b3c154a83190cdfa1c8d
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Type propagation algorithm not settling */

bool _iAP2LinkRunLoopRunOnce(long param_1,long param_2,byte *param_3)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined *puVar7;
  undefined2 local_40 [8];
  
  if (param_1 == 0) {
    return false;
  }
  if ((*(byte *)(param_1 + 0x2c) & 1) != 0) {
    return false;
  }
  uVar3 = _iAP2LinkRunLoopGetResetEventMask(param_1);
  if (*(long *)(param_1 + 0x18) == 0) {
    _iAP2LinkRunLoopRunOnce_cold_2();
LAB_10000889c:
    _iAP2LinkRunLoopRunOnce_cold_1();
    puVar7 = PTR___os_log_default_10022bbb0;
  }
  else {
    if ((uVar3 & 1) != 0) {
      _iAP2LinkAttached();
    }
    if ((uVar3 >> 1 & 1) != 0) {
      _iAP2LinkDetached(*(undefined8 *)(param_1 + 0x18));
    }
    if ((uVar3 >> 2 & 1) != 0) {
      _iAP2LinkHandleSuspend(*(undefined8 *)(param_1 + 0x18));
    }
    if ((uVar3 >> 3 & 1) != 0) {
      _iAP2LinkHandleResume(*(undefined8 *)(param_1 + 0x18));
    }
    if ((uVar3 >> 0xc & 1) == 0) goto LAB_1000087d0;
    if (param_3 != (byte *)0x0) {
      bVar1 = *param_3;
      *param_3 = bVar1 & 0x7f;
      _iAP2LinkRenegotiate(*(undefined8 *)(param_1 + 0x18),param_3,bVar1 >> 7);
      goto LAB_1000087d0;
    }
    if ((__iAP2LogEnableMask & 1) == 0) goto LAB_1000087d0;
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar7 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) goto LAB_10000889c;
    }
    else {
      puVar7 = *(undefined **)(_gLogObjects + 0xb0);
    }
  }
  iVar4 = _os_log_type_enabled(puVar7,0);
  if (iVar4 != 0) {
    local_40[0] = 0;
    __os_log_impl(0x100000000,puVar7,0,"ERROR: syn == NULL!",local_40,2);
  }
LAB_1000087d0:
  if (param_2 != 0) {
    _iAP2LinkHandleReadyPacket(*(undefined8 *)(param_1 + 0x18),param_2);
    _iAP2PacketRelease(param_2);
  }
  if ((uVar3 & 0x1f0) != 0) {
    uVar6 = _iAP2TimeGetCurTimeMs();
    if ((uVar3 >> 6 & 1) != 0) {
      _iAP2LinkHandleTimeout(*(undefined8 *)(param_1 + 0x18),uVar6,0x1a);
    }
    if ((uVar3 >> 4 & 1) != 0) {
      _iAP2LinkHandleTimeout(*(undefined8 *)(param_1 + 0x18),uVar6,0xc);
    }
    if ((uVar3 >> 5 & 1) != 0) {
      _iAP2LinkHandleTimeout(*(undefined8 *)(param_1 + 0x18),uVar6,0xd);
    }
    if ((uVar3 >> 7 & 1) != 0) {
      _iAP2LinkHandleTimeout(*(undefined8 *)(param_1 + 0x18),uVar6,0xb);
    }
  }
  _iAP2LinkProcessSendBuff(*(undefined8 *)(param_1 + 0x18));
  iVar4 = 0;
  do {
    iVar5 = _iAP2LinkGetSessSendPckListCount(*(undefined8 *)(param_1 + 0x18),iVar4);
    bVar2 = iVar4 != 4;
    iVar4 = iVar4 + 1;
  } while (iVar5 == 0 && bVar2);
  return iVar5 != 0;
}


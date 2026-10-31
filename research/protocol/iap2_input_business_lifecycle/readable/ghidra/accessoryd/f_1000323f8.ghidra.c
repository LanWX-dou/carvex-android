/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000323f8
 * original code SHA256: 911b9c55871242540b5dd8f2ce63931fbd9286ddef34f963747bebd8a3ad966f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkActionResendData(long param_1,undefined1 *param_2)

{
  ushort uVar1;
  undefined8 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  undefined1 uVar10;
  undefined *puVar11;
  bool bVar12;
  undefined4 local_80;
  char *local_7c;
  undefined2 local_74;
  undefined4 local_72;
  undefined2 local_6e;
  char *local_6c;
  undefined1 local_62;
  undefined1 local_61;
  
  if (param_1 == 0) {
    _iAP2LinkActionResendData_cold_3();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    lVar9 = *(long *)(param_1 + 0x10);
    iVar3 = _iAP2TimeGetCurTimeMs();
    uVar1 = *(ushort *)(lVar9 + 0x1a0);
    iVar4 = _iAP2ListArrayGetCount(*(undefined8 *)(lVar9 + 0x128));
    if ((iVar4 != 0) &&
       (lVar6 = __GetSendPckFirstItem(lVar9,&local_61), uVar2 = DAT_1001b3080, lVar6 != 0)) {
      bVar12 = false;
      uVar10 = local_61;
LAB_100032488:
      do {
        lVar7 = __GetSendPckNextItem(lVar9,uVar10,&local_62);
        if (*(uint *)(lVar6 + 0x30) <= iVar3 + (uint)uVar1) {
          if ((*(byte *)(lVar9 + 0xd4) & 1) == 0) {
            uVar5 = 0x80;
LAB_1000324d0:
            if ((uVar5 <= *(byte *)(lVar9 + 0x19b)) &&
               (uVar8 = _iAP2PacketIsACKOnly(lVar6), (uVar8 & 1) == 0)) {
              if (*(byte *)(lVar9 + 0x19c) <= *(byte *)(lVar6 + 0x3a)) {
                if ((__iAP2LogEnableMask & 1) != 0) {
                  if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
                    puVar11 = PTR___os_log_default_10022bbb0;
                    if (_logObjectForModule_onceToken != -1) {
                      _iAP2LinkEventNotify_cold_2();
                      puVar11 = PTR___os_log_default_10022bbb0;
                    }
                  }
                  else {
                    puVar11 = *(undefined **)(_gLogObjects + 0xb0);
                  }
                  iVar4 = _os_log_type_enabled(puVar11,0);
                  if (iVar4 != 0) {
                    local_6c = "Accessory:ResendData";
                    if (*(int *)(lVar9 + 0xb8) != 0) {
                      local_6c = "Device:ResendData";
                    }
                    local_80 = (undefined4)uVar2;
                    local_7c = "iAP2LinkActionResendData";
                    local_74 = 0x400;
                    local_72 = 0x863;
                    local_6e = 0x820;
                    __os_log_impl(0x100000000,puVar11,0,"ERROR: %s:%d %s: Resend too many times!",
                                  &local_80,0x1c);
                  }
                }
                *param_2 = 0x14;
                goto LAB_100032504;
              }
              *(byte *)(lVar6 + 0x3a) = *(byte *)(lVar6 + 0x3a) + 1;
              *(int *)(lVar9 + 0x224) = *(int *)(lVar9 + 0x224) + 1;
              *(int *)(lVar9 + 0x260) = *(int *)(lVar9 + 0x260) + 1;
              bVar12 = true;
              __iAP2LinkSendPacketCommon(lVar9,lVar6,1,0);
              lVar6 = lVar7;
              uVar10 = local_62;
              if (lVar7 == 0) goto LAB_100032638;
              goto LAB_100032488;
            }
          }
          else {
            uVar5 = _iAP2PacketCalcSeqGap
                              (*(undefined1 *)(lVar9 + 0xbd),
                               *(undefined1 *)(*(long *)(lVar6 + 0x40) + 5));
            if (uVar5 != 0) goto LAB_1000324d0;
          }
          _iAP2ListArrayDeleteItem(*(undefined8 *)(lVar9 + 0x128),uVar10,__DeletePckCB);
        }
LAB_100032504:
        lVar6 = lVar7;
        uVar10 = local_62;
      } while (lVar7 != 0);
      if (bVar12) {
LAB_100032638:
        _iAP2LinkEventNotify(lVar9,5,0);
      }
    }
    return;
  }
                    /* WARNING: Subroutine does not return */
  _iAP2LinkActionResendData_cold_2();
}


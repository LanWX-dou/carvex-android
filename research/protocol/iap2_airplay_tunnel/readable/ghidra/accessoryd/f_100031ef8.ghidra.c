/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100031ef8
 * original code SHA256: 021822fe3cef32592de059ed677f330aea2c87d9f1db89f7490a1378aa9416e9
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkActionResendMissing(long param_1,undefined1 *param_2)

{
  bool bVar1;
  undefined8 uVar2;
  int iVar3;
  undefined1 *puVar4;
  long *plVar5;
  undefined8 uVar6;
  long *plVar7;
  ulong uVar8;
  ulong uVar9;
  long lVar10;
  undefined1 *puVar11;
  undefined *puVar12;
  long lVar13;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined2 local_84;
  undefined4 local_82;
  undefined2 local_7e;
  char *local_7c;
  undefined4 local_68;
  uint local_64;
  
  if (param_1 == 0) {
    _iAP2LinkActionResendMissing_cold_3();
  }
  else if (param_2 != (undefined1 *)0x0) {
    *param_2 = 0x1d;
    lVar10 = *(long *)(param_1 + 0x10);
    local_64 = 0;
    puVar4 = (undefined1 *)
             _iAP2PacketGetMissingSeqFromEAK
                       (*(undefined8 *)(lVar10 + 0x118),*(undefined1 *)(lVar10 + 0x1a5),&local_64);
    uVar9 = (ulong)local_64;
    if (puVar4 != (undefined1 *)0x0 && local_64 != 0) {
      local_68 = 1;
      plVar5 = (long *)_iAP2PacketCreateEmptySendPacket(lVar10,&local_68);
      bVar1 = false;
      *plVar5 = lVar10;
      uVar2 = DAT_1001b3080;
      puVar11 = puVar4;
      do {
        while( true ) {
          *(undefined1 *)(plVar5[8] + 5) = *puVar11;
          local_90 = SUB84(plVar5,0);
          uStack_8c = (undefined4)((ulong)plVar5 >> 0x20);
          uVar6 = _iAP2ListArrayFindItem
                            (*(undefined8 *)(lVar10 + 0x128),&local_90,__iAP2LinkComparePacketSeq);
          plVar7 = (long *)_iAP2ListArrayItemForIndex(*(undefined8 *)(lVar10 + 0x128),uVar6);
          if ((plVar7 != (long *)0x0) && (lVar13 = *plVar7, lVar13 != 0)) break;
LAB_1000320ec:
          puVar11 = puVar11 + 1;
          if (puVar4 + uVar9 <= puVar11) {
            _iAP2PacketRelease(plVar5);
            if (bVar1) goto LAB_100032164;
            goto LAB_100032174;
          }
        }
        uVar8 = _iAP2PacketIsACKOnly(lVar13);
        if ((uVar8 & 1) != 0) {
          _iAP2ListArrayDeleteItem(*(undefined8 *)(lVar10 + 0x128),uVar6,__DeletePckCB);
          goto LAB_1000320ec;
        }
        if (*(byte *)(lVar10 + 0x19c) <= *(byte *)(lVar13 + 0x3a)) {
          if ((__iAP2LogEnableMask & 1) != 0) {
            if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
              puVar12 = PTR___os_log_default_10022bbb0;
              if (_logObjectForModule_onceToken != -1) {
                _iAP2LinkEventNotify_cold_2();
                puVar12 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar12 = *(undefined **)(_gLogObjects + 0xb0);
            }
            iVar3 = _os_log_type_enabled(puVar12,0);
            if (iVar3 != 0) {
              local_7c = "Accessory:ResendMissing";
              if (*(int *)(lVar10 + 0xb8) != 0) {
                local_7c = "Device:ResendMissing";
              }
              local_90 = (undefined4)uVar2;
              uStack_8c = 0x1ccf38;
              uStack_88 = 1;
              local_84 = 0x400;
              local_82 = 0x7ec;
              local_7e = 0x820;
              __os_log_impl(0x100000000,puVar12,0,"ERROR: %s:%d %s Resend too many times!",&local_90
                            ,0x1c);
            }
          }
          *param_2 = 0x14;
          goto LAB_1000320ec;
        }
        *(byte *)(lVar13 + 0x3a) = *(byte *)(lVar13 + 0x3a) + 1;
        *(int *)(lVar10 + 0x228) = *(int *)(lVar10 + 0x228) + 1;
        *(int *)(lVar10 + 0x260) = *(int *)(lVar10 + 0x260) + 1;
        bVar1 = true;
        __iAP2LinkSendPacketCommon(lVar10,lVar13,1,0);
        puVar11 = puVar11 + 1;
      } while (puVar11 < puVar4 + uVar9);
      _iAP2PacketRelease(plVar5);
LAB_100032164:
      _iAP2LinkEventNotify(lVar10,5,0);
    }
LAB_100032174:
    if (puVar4 != (undefined1 *)0x0) {
      _free(puVar4);
    }
    return;
  }
                    /* WARNING: Subroutine does not return */
  _iAP2LinkActionResendMissing_cold_2();
}


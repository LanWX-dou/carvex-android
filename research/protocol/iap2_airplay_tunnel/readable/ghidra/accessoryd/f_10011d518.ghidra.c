/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10011d518
 * original code SHA256: beea7baee1446a49c12f2234cbbd239140f9f05fce7f069b91b057347e113362
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_sessionControl_parseIncomingMessage(long *param_1,long param_2,uint param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined1 in_ZR;
  undefined4 uVar4;
  int iVar5;
  long lVar6;
  undefined8 uVar7;
  ulong uVar8;
  code *pcVar9;
  char *pcVar10;
  undefined8 extraout_x8;
  undefined8 extraout_x8_00;
  undefined8 extraout_x8_01;
  undefined8 uVar11;
  undefined *puVar12;
  long lVar13;
  ulong uVar14;
  undefined1 *local_d0;
  undefined1 *puStack_c8;
  undefined1 *puStack_c0;
  undefined1 *puStack_b8;
  undefined1 *local_b0;
  undefined1 *puStack_a8;
  undefined1 *puStack_a0;
  undefined1 *puStack_98;
  undefined1 *local_90;
  undefined2 local_78;
  undefined4 local_76;
  undefined2 uStack_72;
  undefined2 uStack_70;
  undefined6 uStack_6e;
  
  uVar11 = 0;
  if ((param_1 != (long *)0x0) && (param_2 != 0)) {
    local_90 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_a8 = &DAT_aaaaaaaaaaaaaaaa;
    local_b0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_98 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_a0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_c8 = &DAT_aaaaaaaaaaaaaaaa;
    local_d0 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_b8 = &DAT_aaaaaaaaaaaaaaaa;
    puStack_c0 = &DAT_aaaaaaaaaaaaaaaa;
    _iAP2MsgInit(&local_d0,0,0,0,0,0);
    uVar3 = DAT_1001b3150;
    uVar2 = DAT_1001b3138;
    uVar1 = DAT_1001b30b0;
    if (param_3 == 0) {
      uVar11 = 0;
    }
    else {
      lVar13 = 0;
      uVar11 = 0;
      uVar14 = (ulong)param_3;
      do {
        lVar6 = _iAP2MsgParserConsumeByte(param_1[0xf],*(undefined1 *)(param_2 + lVar13),&local_d0);
        if (lVar6 != 0) {
          if (*param_1 == 0) {
LAB_10011d76c:
            uVar11 = 0;
          }
          else {
            uVar11 = _iAP2MsgGetMsgID(lVar6);
            uVar4 = _iAP2MsgGetMsgLen(lVar6);
            if ((_gLogObjects == 0) || (in_ZR = _gNumLogObjects == 0x18, _gNumLogObjects < 0x18)) {
              _OUTLINED_FUNCTION_9();
              puVar12 = PTR___os_log_default_10022bbb0;
              if (!(bool)in_ZR) {
                _OUTLINED_FUNCTION_1();
                _dispatch_once();
                puVar12 = PTR___os_log_default_10022bbb0;
              }
            }
            else {
              puVar12 = *(undefined **)(_gLogObjects + 0xb8);
            }
            iVar5 = _os_log_type_enabled(puVar12,1);
            if (iVar5 != 0) {
              _OUTLINED_FUNCTION_13(param_1[1],uVar3);
              local_78 = 0x400;
              uStack_72 = 0x840;
              uStack_70 = (undefined2)extraout_x8;
              uStack_6e = (undefined6)((ulong)extraout_x8 >> 0x10);
              local_76 = uVar4;
              uVar7 = _OUTLINED_FUNCTION_6();
              __os_log_impl(uVar7,puVar12,1,"Incoming Message ID: 0x%04X (%d bytes) for endpoint %@"
                           );
            }
            uVar8 = _iap2_identification_isIdentifiedForIncomingMessageID(param_1,uVar11);
            if ((uVar8 & 1) == 0) {
              uVar11 = _logObjectForModule(0x19);
              iVar5 = _os_log_type_enabled(uVar11,0x10);
              if (iVar5 != 0) {
                _OUTLINED_FUNCTION_13(param_1[1],uVar2);
                local_78 = 0x840;
                local_76 = (undefined4)extraout_x8_00;
                uStack_72 = (undefined2)((ulong)extraout_x8_00 >> 0x20);
                uStack_70 = (undefined2)((ulong)extraout_x8_00 >> 0x30);
                uVar7 = _OUTLINED_FUNCTION_6();
                pcVar10 = "Not identified for incoming message ID: 0x%04X! (endpoint %@)";
LAB_10011d7b4:
                __os_log_error_impl(uVar7,uVar11,0x10,pcVar10);
              }
              goto LAB_10011d76c;
            }
            pcVar9 = (code *)_iap2_messageHandlers_getHandler(uVar11);
            if (pcVar9 == (code *)0x0) {
              uVar11 = _logObjectForModule(0x19);
              iVar5 = _os_log_type_enabled(uVar11,0x10);
              if (iVar5 != 0) {
                _OUTLINED_FUNCTION_13(uVar1);
                uVar7 = _OUTLINED_FUNCTION_6();
                pcVar10 = "No message handler found for incoming message ID: 0x%04X!";
                goto LAB_10011d7b4;
              }
              goto LAB_10011d76c;
            }
            uVar8 = (*pcVar9)(param_1,lVar6);
            if ((uVar8 & 1) == 0) {
              uVar11 = _logObjectForModule(0x19);
              iVar5 = _os_log_type_enabled(uVar11,0x10);
              if (iVar5 != 0) {
                _OUTLINED_FUNCTION_13(param_1[1],uVar2);
                local_78 = 0x840;
                local_76 = (undefined4)extraout_x8_01;
                uStack_72 = (undefined2)((ulong)extraout_x8_01 >> 0x20);
                uStack_70 = (undefined2)((ulong)extraout_x8_01 >> 0x30);
                uVar7 = _OUTLINED_FUNCTION_6();
                pcVar10 = "Message handler returned false! (0x%04X for endpoint %@)";
                goto LAB_10011d7b4;
              }
              goto LAB_10011d76c;
            }
            uVar11 = 1;
          }
          _iAP2MsgCleanup(lVar6,0);
        }
        lVar13 = lVar13 + 1;
        uVar14 = uVar14 - 1;
        in_ZR = uVar14 == 0;
      } while (!(bool)in_ZR);
    }
  }
  return uVar11;
}


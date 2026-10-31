/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100032670
 * original code SHA256: 18254a93bd00327fa12559f066f0ac55e9be2c4f6444aca2d60e59a24806770b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkActionHandleData(long param_1,undefined1 *param_2)

{
  char *pcVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  ulong uVar5;
  char *pcVar6;
  long lVar7;
  long unaff_x19;
  long lVar8;
  undefined *puVar9;
  undefined8 uVar10;
  long unaff_x22;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  undefined4 local_42;
  undefined2 local_3e;
  uint local_3c;
  
  if (param_1 == 0) {
    _iAP2LinkActionHandleData_cold_3();
LAB_10003281c:
    _iAP2LinkActionHandleData_cold_2();
LAB_100032820:
    _iAP2LinkEventNotify_cold_1();
    puVar9 = PTR___os_log_default_10022bbb0;
  }
  else {
    if (param_2 == (undefined1 *)0x0) goto LAB_10003281c;
    *param_2 = 0x1d;
    unaff_x19 = *(long *)(param_1 + 0x10);
    lVar8 = *(long *)(unaff_x19 + 0x118);
    unaff_x22 = *(long *)(lVar8 + 0x40);
    iVar3 = _iAP2PacketGetPayloadLen(lVar8);
    *(int *)(unaff_x19 + 0x218) = *(int *)(unaff_x19 + 0x218) + iVar3;
    *(int *)(unaff_x19 + 0x220) = *(int *)(unaff_x19 + 0x220) + 1;
    uVar5 = (ulong)*(byte *)(unaff_x19 + 0x1a4);
    if (uVar5 != 0) {
      lVar7 = 0;
      pcVar6 = (char *)0x0;
      do {
        pcVar1 = (char *)(unaff_x19 + 0x1b8 + lVar7 * 4);
        if (*pcVar1 != *(char *)(unaff_x22 + 7)) {
          pcVar1 = pcVar6;
        }
        lVar7 = lVar7 + 1;
        uVar5 = uVar5 - 1;
        pcVar6 = pcVar1;
      } while (uVar5 != 0);
      if (pcVar1 != (char *)0x0) {
        uVar10 = *(undefined8 *)(lVar8 + 0x48);
        uVar4 = _iAP2PacketGetPayloadLen(lVar8);
        _iAP2LinkDataReadyCB(unaff_x19,uVar10,uVar4,lVar8,*(undefined1 *)(unaff_x22 + 7));
        goto LAB_1000327d8;
      }
    }
    if ((__iAP2LogEnableMask & 1) == 0) goto LAB_1000327d8;
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar9 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken == -1) goto LAB_100032770;
      goto LAB_100032820;
    }
    puVar9 = *(undefined **)(_gLogObjects + 0xb0);
  }
LAB_100032770:
  iVar3 = _os_log_type_enabled(puVar9,0);
  if (iVar3 != 0) {
    local_50 = (undefined4)DAT_1001b3080;
    local_4c = "iAP2LinkActionHandleData";
    local_44 = 0x400;
    local_42 = 0x8ad;
    local_3e = 0x400;
    local_3c = (uint)*(byte *)(unaff_x22 + 7);
    __os_log_impl(0x100000000,puVar9,0,"ERROR: %s:%d Invalid session(%u)!",&local_50,0x18);
  }
LAB_1000327d8:
  uVar5 = _iAP2LinkIsNoRetransmit(unaff_x19 + 0x19a);
  if (((uVar5 & 1) == 0) && (*(char *)(unaff_x19 + 0xc2) == -1)) {
    uVar2 = _iAP2TimeCallbackAfter
                      (*(undefined8 *)(unaff_x19 + 200),0xd,*(undefined2 *)(unaff_x19 + 0x1a2));
    *(undefined1 *)(unaff_x19 + 0xc2) = uVar2;
  }
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10002fb54
 * original code SHA256: 8a6debb4ee14c89a2c1ba92fd1e1a1ed6bdfad2bec6e86350eb69964600be8c6
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _iAP2LinkDeviceActionSendRST(long param_1,undefined1 *param_2)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  undefined1 *unaff_x19;
  long unaff_x20;
  long lVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined4 local_40;
  uint local_3c;
  
  if (param_1 == 0) {
    _iAP2LinkDeviceActionSendRST_cold_3();
LAB_10002fcc8:
    _iAP2LinkDeviceActionSendRST_cold_2();
LAB_10002fccc:
    _iAP2LinkDeviceActionSendSYNACK_cold_1();
    param_2 = unaff_x19;
    param_1 = unaff_x20;
    puVar5 = PTR___os_log_default_10022bbb0;
  }
  else {
    unaff_x19 = param_2;
    if (param_2 == (undefined1 *)0x0) goto LAB_10002fcc8;
    if ((__iAP2LogEnableMask & 1) == 0) goto LAB_10002fc10;
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      unaff_x20 = param_1;
      puVar5 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken == -1) goto LAB_10002fbc8;
      goto LAB_10002fccc;
    }
    puVar5 = *(undefined **)(_gLogObjects + 0xb0);
  }
LAB_10002fbc8:
  iVar1 = _os_log_type_enabled(puVar5,0);
  if (iVar1 != 0) {
    local_40 = (undefined4)DAT_1001b30b0;
    local_3c = (uint)*(byte *)(param_1 + 10);
    __os_log_impl(0x100000000,puVar5,0,
                  "ERROR: iAP2LinkDeviceActionSendRST: iAP2 Link Layer reset triggered! (state: %d)"
                  ,&local_40,8);
  }
LAB_10002fc10:
  *param_2 = 0x1d;
  lVar4 = *(long *)(param_1 + 0x10);
  _iAP2LinkResetSeqAck(lVar4,0,0);
  _iAP2LinkSetDefaultSYNParam(lVar4 + 0x19a);
  puVar3 = *(undefined8 **)(lVar4 + 0x160);
  uVar8 = puVar3[3];
  uVar7 = puVar3[2];
  uVar6 = puVar3[5];
  uVar2 = puVar3[4];
  uVar10 = puVar3[1];
  uVar9 = *puVar3;
  *(undefined2 *)(lVar4 + 0x198) = *(undefined2 *)(puVar3 + 6);
  *(undefined8 *)(lVar4 + 0x180) = uVar8;
  *(undefined8 *)(lVar4 + 0x178) = uVar7;
  *(undefined8 *)(lVar4 + 400) = uVar6;
  *(undefined8 *)(lVar4 + 0x188) = uVar2;
  *(undefined8 *)(lVar4 + 0x170) = uVar10;
  *(undefined8 *)(lVar4 + 0x168) = uVar9;
  if (((*(byte *)(lVar4 + 0xd4) >> 5 & 1) == 0) && (10 < *(uint *)(lVar4 + 0x1d0))) {
    *param_2 = 0x14;
  }
  else {
    uVar2 = _iAP2PacketCreateRSTPacket(lVar4,*(undefined1 *)(lVar4 + 0xbe));
    *(int *)(lVar4 + 0x248) = *(int *)(lVar4 + 0x248) + 1;
    _iAP2LinkSendPacket(lVar4,uVar2,0,"Device:SendRST");
    _iAP2PacketRelease(uVar2);
  }
  return;
}


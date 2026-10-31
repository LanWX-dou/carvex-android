/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000088b8
 * original code SHA256: 12b8123ebe515c1c5f20f00aec2806aa79e3506c8eb96725f06a9e7038b8e34c
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 _iAP2PacketGenerateBuffer(undefined8 *param_1)

{
  ushort uVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined *puVar6;
  undefined2 *puVar7;
  long lVar8;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  undefined4 local_42;
  
  if (param_1 == (undefined8 *)0x0) {
    if ((__iAP2LogEnableMask & 1) == 0) {
      return 0;
    }
    if (_gLogObjects != 0 && 0x16 < _gNumLogObjects) {
      puVar6 = *(undefined **)(_gLogObjects + 0xb0);
      goto LAB_1000089c4;
    }
    puVar6 = PTR___os_log_default_10022bbb0;
    if (_logObjectForModule_onceToken == -1) goto LAB_1000089c4;
  }
  else {
    uVar1 = *(ushort *)((long)param_1 + 0x36);
    puVar7 = (undefined2 *)param_1[8];
    uVar3 = _iAP2LinkGetChecksumType(*param_1);
    *puVar7 = 0x5aff;
    *(char *)(puVar7 + 1) = (char)(uVar1 >> 8);
    *(char *)((long)puVar7 + 3) = (char)uVar1;
    if (*(uint *)((long)param_1 + 0x2c) == (uint)*(ushort *)((long)param_1 + 0x36)) {
      if ((uint)uVar1 <= *(uint *)((long)param_1 + 0x2c)) {
        lVar8 = param_1[9];
        uVar4 = _iAP2PacketGetPayloadLen(param_1);
        uVar5 = _iAP2PacketCalcChecksum(param_1[8],8,uVar3);
        _iAP2PacketSetHdrChecksum(param_1,uVar3,uVar5);
        if ((lVar8 != 0) && ((int)uVar4 != 0)) {
          uVar3 = _iAP2PacketCalcChecksum(lVar8,uVar4,uVar3);
          *(short *)((long)param_1 + 0x34) = (short)uVar4;
          _iAP2PacketSetPayloadChecksum(param_1,uVar3);
        }
      }
      return param_1[8];
    }
    _iAP2PacketGenerateBuffer_cold_1();
  }
  _iAP2PacketCalcChecksum_cold_1();
  puVar6 = PTR___os_log_default_10022bbb0;
LAB_1000089c4:
  iVar2 = _os_log_type_enabled(puVar6,0);
  if (iVar2 != 0) {
    local_50 = (undefined4)DAT_1001b3098;
    local_4c = "iAP2PacketGenerateBuffer";
    local_44 = 0x400;
    local_42 = 0x68e;
    __os_log_impl(0x100000000,puVar6,0,"ERROR: %s:%d NULL packet pointer!",&local_50,0x12);
  }
  return 0;
}


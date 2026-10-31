/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10008eb68
 * original code SHA256: 49a914f721c2a06a6729519475705a2235b0d0dee2c636f0a815d5bc3076b001
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iAP2MsgParserConsumeByte(ushort *param_1,undefined1 param_2,undefined8 param_3)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  undefined8 uVar6;
  byte *pbVar7;
  undefined *puVar8;
  undefined4 local_40;
  char *local_3c;
  undefined2 local_34;
  undefined4 local_32;
  undefined2 local_2e;
  uint local_2c;
  undefined2 local_28;
  uint local_26;
  
  if ((uint)*param_1 < (uint)param_1[1]) {
    *(undefined1 *)(*(long *)(param_1 + 4) + (ulong)(uint)*param_1) = param_2;
    uVar3 = *param_1;
    uVar1 = uVar3 + 1;
    uVar2 = uVar1 & 0xffff;
    *param_1 = (ushort)uVar1;
    if (uVar2 != uVar1) {
      return 0;
    }
    uVar4 = param_1[0xc];
    pbVar7 = *(byte **)(param_1 + 4);
    if ((ushort)*pbVar7 == uVar4 >> 8) {
      if (uVar3 == 0) {
        return 0;
      }
      if ((ushort)pbVar7[1] == (uVar4 & 0xff)) {
        if (uVar2 < 4) {
          return 0;
        }
        if (uVar2 != ((uint)(*(ushort *)(pbVar7 + 2) >> 8) |
                     (*(ushort *)(pbVar7 + 2) & 0xff00ff) << 8)) {
          return 0;
        }
        uVar6 = _parseMessage(param_3,uVar4,pbVar7,param_1[1]);
        goto LAB_10008eccc;
      }
    }
  }
  else if ((__iAP2LogEnableMask & 1) != 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar8 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2MsgParserConsumeByte_cold_1();
        puVar8 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar8 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar5 = _os_log_type_enabled(puVar8,0);
    if (iVar5 != 0) {
      local_40 = (undefined4)DAT_1001b30e0;
      local_3c = "_consumeByteInternal";
      local_34 = 0x400;
      local_32 = 0x86;
      local_2e = 0x400;
      local_2c = (uint)*param_1;
      local_28 = 0x400;
      local_26 = (uint)param_1[1];
      __os_log_impl(0x100000000,puVar8,0,
                    "ERROR: %s:%d ERROR: message parse error, length (%u) passed allocated buffer length (%u)"
                    ,&local_40,0x1e);
    }
  }
  uVar6 = 0;
LAB_10008eccc:
  *param_1 = 0;
  return uVar6;
}


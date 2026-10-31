/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100008ae8
 * original code SHA256: a46fff0c269e0aa30fec5520c4dc2ef26b68c9db5b4b48977e2362b299a2f235
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



uint _iAP2PacketCalcChecksum(byte *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  undefined *puVar3;
  char *pcVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  undefined4 local_42;
  undefined2 local_3e;
  uint local_3c;
  undefined2 local_38;
  uint local_36;
  
  puVar3 = PTR___os_log_default_10022bbb0;
  if ((param_1 == (byte *)0x0) || (param_2 == 0)) {
    if ((__iAP2LogEnableMask & 1) != 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        if (_logObjectForModule_onceToken != -1) {
          _iAP2PacketCalcChecksum_cold_1();
          puVar3 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar3 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar2 = _os_log_type_enabled(puVar3,0);
      if (iVar2 != 0) {
        local_3c = (uint)param_1 & 0xffff;
        local_50 = (undefined4)DAT_1001b30e0;
        local_42 = 0x7ed;
        local_38 = 0x400;
        pcVar4 = "ERROR: %s:%d NULL buffer(%hx) pointer or nothing to copy (len=%u)!";
        uVar5 = 0x1e;
        local_36 = param_2;
LAB_100008d18:
        local_3e = 0x400;
        local_44 = 0x400;
        local_4c = "iAP2PacketCalcChecksum";
        __os_log_impl(0x100000000,puVar3,0,pcVar4,&local_50,uVar5);
      }
    }
  }
  else {
    if (param_3 == 0) {
      iVar2 = 0;
      pbVar9 = param_1;
      do {
        pbVar10 = pbVar9 + 1;
        iVar2 = (uint)*pbVar9 + iVar2;
        pbVar9 = pbVar10;
      } while (pbVar10 != param_1 + param_2);
      uVar7 = -iVar2 & 0xff;
      goto LAB_100008d20;
    }
    if (param_3 == 1) {
      uVar6 = 0xff;
      uVar7 = 0xff;
      do {
        pbVar9 = param_1;
        uVar8 = param_2;
        uVar1 = param_2;
        if (0x13 < param_2) {
          uVar8 = 0x14;
          uVar1 = uVar8;
        }
        do {
          uVar8 = uVar8 - 1;
          uVar7 = uVar7 + *pbVar9;
          uVar6 = uVar7 + uVar6;
          pbVar9 = pbVar9 + 1;
        } while ((uVar8 & 0xffff) != 0);
        param_1 = param_1 + uVar1;
        uVar7 = (uVar7 >> 8 & 0xff) + (uVar7 & 0xff);
        uVar6 = (uVar6 >> 8 & 0xff) + (uVar6 & 0xff);
        param_2 = param_2 - uVar1;
      } while (param_2 != 0);
      uVar7 = -(uVar6 * 0x101 & 0x3ff00 | (uVar7 >> 8) + (uVar7 & 0xff));
      goto LAB_100008d20;
    }
    if ((__iAP2LogEnableMask & 1) != 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
        if (_logObjectForModule_onceToken != -1) {
          _iAP2PacketCalcChecksum_cold_1();
          puVar3 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar3 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar2 = _os_log_type_enabled(puVar3,0);
      if (iVar2 != 0) {
        local_50 = (undefined4)DAT_1001b3080;
        local_42 = 0x7e5;
        pcVar4 = "ERROR: %s:%d Unknown checksumType(%d)!";
        uVar5 = 0x18;
        local_3c = param_3;
        goto LAB_100008d18;
      }
    }
  }
  uVar7 = 0;
LAB_100008d20:
  return uVar7 & 0xffff;
}


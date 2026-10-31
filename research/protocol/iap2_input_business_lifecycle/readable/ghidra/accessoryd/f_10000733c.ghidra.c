/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000733c
 * original code SHA256: 4b91dedb3eb209067735619e19fa501d0d7d5c485ced4179e764588bc961e840
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_iAP2LinkQueueSendDataPacketInternal
          (long param_1,long param_2,uint param_3,undefined8 param_4,undefined8 param_5,
          code *param_6,undefined8 param_7)

{
  byte *pbVar1;
  int iVar2;
  undefined8 uVar3;
  undefined *puVar4;
  char *pcVar5;
  ulong uVar6;
  long lVar7;
  undefined8 uVar8;
  uint uVar9;
  byte *pbVar10;
  uint local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined2 local_64;
  undefined4 local_62;
  undefined2 local_5e;
  uint local_5c;
  undefined2 local_58;
  uint local_56;
  
  uVar9 = (uint)param_2;
  if ((param_1 == 0) || (iVar2 = _iAP2PacketIsDataPacket(param_2), iVar2 == 0)) {
    if ((__iAP2LogEnableMask & 1) == 0) goto LAB_100007584;
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_1();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar2 = _os_log_type_enabled(puVar4,0);
    if (iVar2 == 0) goto LAB_100007584;
    local_5c = (uint)param_1 & 0xffff;
    local_56 = uVar9 & 0xffff;
    local_70 = (uint)DAT_1001b30e0;
    local_62 = 0x1028;
    local_58 = 0x400;
    pcVar5 = "ERROR: %s:%d NULL link(%hx) or invalid packet (%hx)!";
    uVar3 = 0x1e;
  }
  else {
    uVar6 = (ulong)*(byte *)(param_1 + 0x1a4);
    if (uVar6 != 0) {
      lVar7 = 0;
      pbVar10 = (byte *)0x0;
      do {
        pbVar1 = (byte *)(param_1 + 0x1b8 + lVar7 * 4);
        if (*pbVar1 != param_3) {
          pbVar1 = pbVar10;
        }
        lVar7 = lVar7 + 1;
        uVar6 = uVar6 - 1;
        pbVar10 = pbVar1;
      } while (uVar6 != 0);
      if (pbVar1 != (byte *)0x0) {
        *(char *)(*(long *)(param_2 + 0x40) + 7) = (char)param_3;
        *(undefined8 *)(param_2 + 8) = param_4;
        _iAP2PacketSetCallbacks(param_2,param_5,param_6,param_7);
        uStack_6c = (undefined4)((ulong)param_2 >> 0x20);
        uVar8 = *(undefined8 *)(param_1 + 0x130 + (ulong)pbVar1[1] * 8);
        local_70 = uVar9;
        uVar3 = _iAP2ListArrayGetLastItemIndex(uVar8);
        iVar2 = _iAP2LinkAddPacketAfter(uVar8,uVar3,&local_70);
        if (iVar2 != 0xff) {
          return 1;
        }
        if ((__iAP2LogEnableMask & 1) == 0) {
          return 0;
        }
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
          puVar4 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            _iAP2LinkEventNotify_cold_2();
            puVar4 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar4 = *(undefined **)(_gLogObjects + 0xb0);
        }
        uVar3 = _os_log_type_enabled(puVar4,0);
        if ((int)uVar3 != 0) {
          local_5c = _iAP2ListArrayGetCount(*(undefined8 *)(param_1 + 0x130 + (ulong)pbVar1[1] * 8))
          ;
          local_56 = uVar9 & 0xffff;
          local_70 = (uint)DAT_1001b30e0;
          uStack_6c = 0x1cd0ce;
          uStack_68 = 1;
          local_64 = 0x400;
          local_62 = 0x101d;
          local_5e = 0x400;
          local_58 = 0x400;
          __os_log_impl(0x100000000,puVar4,0,
                        "ERROR: %s:%d Could not queue packet to session send list! listCount=%u packet=%hx"
                        ,&local_70,0x1e);
          return 0;
        }
        return uVar3;
      }
    }
    if ((__iAP2LogEnableMask & 1) == 0) goto LAB_100007584;
    if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkEventNotify_cold_1();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar2 = _os_log_type_enabled(puVar4,0);
    if (iVar2 == 0) goto LAB_100007584;
    local_70 = (uint)DAT_1001b3080;
    local_62 = 0x1022;
    pcVar5 = "ERROR: %s:%d Invalid session(%u)!";
    uVar3 = 0x18;
    local_5c = param_3;
  }
  local_5e = 0x400;
  local_64 = 0x400;
  uStack_68 = 1;
  uStack_6c = 0x1cd0ce;
  __os_log_impl(0x100000000,puVar4,0,pcVar5,&local_70,uVar3);
LAB_100007584:
  if (param_6 != (code *)0x0) {
    (*param_6)(param_1,param_4);
  }
  return 0;
}


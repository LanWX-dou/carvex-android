/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000d4c94
 * original code SHA256: 534f03bb40e30dac0ae51b30988878859aa20a803558cc2a0ce12436976ed30e
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iAP2LinkProcessInOrderPacketCMD(long param_1,long param_2)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined *puVar5;
  undefined4 local_70;
  char *local_6c;
  undefined2 local_64;
  undefined4 local_62;
  undefined2 local_5e;
  uint local_5c;
  undefined2 local_58;
  uint local_56;
  undefined2 local_52;
  uint local_50;
  
  bVar1 = **(byte **)(param_2 + 0x48);
  if ((__iAP2LogEnableMask >> 1 & 1) != 0) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar5 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2LinkProcessInOrderPacketCMD_cold_1();
        puVar5 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar5 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar2 = _os_log_type_enabled(puVar5,1);
    if (iVar2 != 0) {
      local_70 = (undefined4)DAT_1001b3110;
      local_6c = "iAP2LinkProcessInOrderPacketCMD";
      local_64 = 0x400;
      local_62 = 0x5f;
      local_5e = 0x400;
      local_5c = (uint)*(byte *)(param_1 + 0xd5);
      local_58 = 0x400;
      local_56 = (uint)bVar1;
      local_52 = 0x400;
      local_50 = local_56;
      __os_log_impl(0x100000000,puVar5,1,"%s:%d linkVer=%d cmdID=%xh(%d)",&local_70,0x24);
    }
  }
  if (*(char *)(param_1 + 0xd5) == '\x01') {
    if ((__iAP2LogEnableMask >> 2 & 1) != 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        puVar5 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkProcessInOrderPacketCMD_cold_4();
          puVar5 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar5 = *(undefined **)(_gLogObjects + 0xb0);
      }
      uVar3 = _os_log_type_enabled(puVar5,2);
      if ((int)uVar3 == 0) {
        return uVar3;
      }
      _iAP2LinkProcessInOrderPacketCMD_cold_5((char *)(param_1 + 0xd5),bVar1,puVar5);
    }
LAB_1000d4e24:
    uVar3 = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0xbc) = *(undefined1 *)(*(long *)(param_2 + 0x40) + 5);
    *(byte *)(param_1 + 0xd4) = *(byte *)(param_1 + 0xd4) | 1;
    if (bVar1 == 0x55) {
      uVar3 = *(undefined8 *)(param_1 + 8);
      uVar4 = 10;
    }
    else {
      if (bVar1 != 0x54) {
        if ((__iAP2LogEnableMask >> 2 & 1) != 0) {
          if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
            puVar5 = PTR___os_log_default_10022bbb0;
            if (_logObjectForModule_onceToken != -1) {
              _iAP2LinkProcessInOrderPacketCMD_cold_4();
              puVar5 = PTR___os_log_default_10022bbb0;
            }
          }
          else {
            puVar5 = *(undefined **)(_gLogObjects + 0xb0);
          }
          uVar3 = _os_log_type_enabled(puVar5,2);
          if ((int)uVar3 == 0) {
            return uVar3;
          }
          _iAP2LinkProcessInOrderPacketCMD_cold_3(bVar1,puVar5);
        }
        goto LAB_1000d4e24;
      }
      uVar3 = *(undefined8 *)(param_1 + 8);
      uVar4 = 9;
    }
    _iAP2FSMHandleEvent(uVar3,uVar4);
    uVar3 = 1;
  }
  return uVar3;
}


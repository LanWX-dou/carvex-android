/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100022264
 * original code SHA256: b92730d13cd5d4b01ef670606d08a56e1a7125e927e32160f47530e7de0b83b3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long _mfi4Auth_util_packIntoTunnelDataiAP2Msg(undefined8 param_1,undefined8 param_2,int param_3)

{
  undefined2 uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined4 uVar6;
  
  lVar3 = _CFDataGetBytePtr(param_2);
  if (lVar3 == 0) {
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_util_packIntoTunnelDataiAP2Msg_cold_3();
    }
  }
  else {
    lVar4 = _malloc_type_malloc(0x48,0x109004066c3afe2);
    if (lVar4 != 0) {
      lVar5 = _malloc_type_malloc(0xffff,0xdbec333c);
      if (lVar5 != 0) {
        uVar6 = 0x5500;
        if (param_3 != 0) {
          uVar6 = 0x5501;
        }
        _iAP2MsgInit(lVar4,uVar6,lVar5,0xffff,0,0);
        _iAP2MsgAddU8Param(lVar4,0,0,param_1);
        uVar1 = _CFDataGetLength(param_2);
        _iAP2MsgAddDataParam(lVar4,0,1,lVar3,uVar1);
        return lVar4;
      }
      iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
      if (iVar2 == 0) {
        return lVar4;
      }
      _mfi4Auth_util_packIntoTunnelDataiAP2Msg_cold_1();
      return lVar4;
    }
    iVar2 = _os_log_type_enabled(PTR___os_log_default_10022bbb0,0x10);
    if (iVar2 != 0) {
      _mfi4Auth_util_packIntoTunnelDataiAP2Msg_cold_2();
    }
  }
  return 0;
}


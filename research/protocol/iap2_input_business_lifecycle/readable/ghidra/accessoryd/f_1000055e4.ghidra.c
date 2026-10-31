/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000055e4
 * original code SHA256: 0e8306624b02b0e50a3ce846c1618572eacf7a01ab86f59f88bb45f7fc5fb2bb
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



ulong _iAP2MsgSendCtlDataWithSentCallback
                (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined4 param_8)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  undefined *puVar4;
  undefined4 local_80;
  undefined4 local_7c;
  undefined2 local_78;
  undefined4 local_76;
  undefined2 local_72;
  undefined4 local_70;
  
  uVar2 = _iAP2LinkGetSessionForService(*(undefined8 *)(param_1 + 0x18),0);
  uVar3 = _iAP2LinkRunLoopQueueSendDataWithSentCallback
                    (param_1,param_2,param_3,uVar2,param_4,param_5,param_6,param_7,(char)param_8);
  if (((uVar3 & 1) == 0) && ((__iAP2LogEnableMask & 1) != 0)) {
    if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
      puVar4 = PTR___os_log_default_10022bbb0;
      if (_logObjectForModule_onceToken != -1) {
        _iAP2MsgSendCtlDataWithSentCallback_cold_1();
        puVar4 = PTR___os_log_default_10022bbb0;
      }
    }
    else {
      puVar4 = *(undefined **)(_gLogObjects + 0xb0);
    }
    iVar1 = _os_log_type_enabled(puVar4,0);
    if (iVar1 != 0) {
      local_80 = (undefined4)DAT_1001b3100;
      local_7c = (undefined4)param_3;
      local_78 = 0x400;
      local_72 = 0x400;
      local_70 = (undefined4)uVar2;
      local_76 = param_8;
      __os_log_impl(0x100000000,puVar4,0,
                    "ERROR: Error sending message data !!!!!! dataLen=%u dataSentCBonACK=%d session=%u\n"
                    ,&local_80,0x14);
    }
  }
  return uVar3;
}


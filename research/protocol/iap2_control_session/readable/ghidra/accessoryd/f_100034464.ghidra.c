/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034464
 * original code SHA256: c089004e6c6782e6093c50560891d92bdc47e07a1d82a5b10520adbb862838e3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkResetSend(long param_1)

{
  code *pcVar1;
  int iVar2;
  undefined *puVar3;
  long lVar4;
  long lVar5;
  ulong unaff_x30;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  undefined4 local_42;
  
  if (param_1 == 0) {
    if ((__iAP2LogEnableMask & 1) != 0) {
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        puVar3 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_1();
          puVar3 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar3 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar2 = _os_log_type_enabled(puVar3,0);
      if (iVar2 != 0) {
        local_50 = (undefined4)DAT_1001b3098;
        local_4c = "iAP2LinkResetSend";
        local_44 = 0x400;
        local_42 = 0xcf9;
        __os_log_impl(0x100000000,puVar3,0,"ERROR: %s:%d NULL link!",&local_50,0x12);
      }
    }
    return;
  }
  __CleanupSendPckList();
  lVar4 = 0;
  lVar5 = 5;
  do {
    _iAP2ListArrayCleanup(*(undefined8 *)(param_1 + 0x130 + lVar4 * 8),__DeletePckCB);
    lVar4 = lVar4 + 1;
    lVar5 = lVar5 + -1;
  } while (lVar5 != 0);
  *(undefined4 *)(param_1 + 0x19e) = 0x3e8ffff;
  *(undefined2 *)(param_1 + 0x1a2) = 10;
  *(int *)(param_1 + 0x19a) = (int)DAT_1001b3348;
  *(undefined4 *)(param_1 + 0x1a4) = 0xffff0100;
  if (((unaff_x30 ^ unaff_x30 << 1) >> 0x3e & 1) != 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)SoftwareBreakpoint(0xc471,0x100034510);
    (*pcVar1)();
  }
  _iAP2LinkResetSeqAck(param_1,1,0);
  return;
}


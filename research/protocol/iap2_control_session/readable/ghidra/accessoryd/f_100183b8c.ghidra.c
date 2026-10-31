/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100183b8c
 * original code SHA256: ead92cc6559f23e203f4fc52a370324192918a5c1b2ad85729610209aceff532
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _iap2_sessionFileTransfer_handleDatagram(long param_1,byte *param_2,undefined8 param_3)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  undefined *puVar5;
  undefined4 local_80;
  char *local_7c;
  undefined2 local_74;
  undefined4 local_72;
  undefined2 local_6e;
  undefined8 local_6c;
  undefined2 local_64;
  long local_62;
  undefined2 local_5a;
  undefined8 local_58;
  undefined2 local_50;
  uint local_4e;
  undefined2 local_4a;
  uint local_48;
  
  uVar3 = 0;
  if ((param_1 != 0) && (param_2 != (byte *)0x0)) {
    bVar1 = *param_2;
    lVar4 = _iap2_sessionFileTransfer_findTransferEntry(param_1,bVar1);
    uVar3 = 0;
    if (lVar4 != 0) {
      lVar4 = *(long *)(lVar4 + 8);
      if (lVar4 == 0) {
        uVar3 = 0;
      }
      else {
        if ((_gLogObjects == 0) || (_gNumLogObjects < 0x1b)) {
          puVar5 = PTR___os_log_default_10022bbb0;
          if (_logObjectForModule_onceToken != -1) {
            _OUTLINED_FUNCTION_0();
            _dispatch_once();
            puVar5 = PTR___os_log_default_10022bbb0;
          }
        }
        else {
          puVar5 = *(undefined **)(_gLogObjects + 0xd0);
        }
        iVar2 = _os_log_type_enabled(puVar5,2);
        if (iVar2 != 0) {
          local_6c = *(undefined8 *)(param_1 + 8);
          local_58 = *(undefined8 *)(lVar4 + 0x10);
          local_80 = (undefined4)DAT_1001b3128;
          local_7c = "iap2_sessionFileTransfer_handleDatagram";
          local_74 = 0x400;
          local_72 = 0x9e;
          local_6e = 0x840;
          local_64 = 0x800;
          local_5a = 0x800;
          local_50 = 0x400;
          local_4e = (uint)*(byte *)(lVar4 + 0x6d);
          local_4a = 0x400;
          local_48 = (uint)bVar1;
          local_62 = lVar4;
          uVar3 = _OUTLINED_FUNCTION_6();
          __os_log_debug_impl(uVar3,puVar5,2,
                              "%s:%d pEndpoint %@, fileXfer %p (buffer %p, id 0x%x), bufferID 0x%x",
                              &local_80,0x3c);
        }
        _iAP2FileTransferHandleRecv(lVar4,param_2,param_3);
        _iap2_sessionFileTransfer_cleanUpRemoveTransferList(param_1);
        uVar3 = 1;
      }
    }
  }
  return uVar3;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10029ead0
 * original code SHA256: 56eb0b2e9c91f591798f823d228cecd4dd3b572f76c00af800aa01652c08a0d0
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


ushort * FUN_10029ead0(uint param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ushort *puVar4;
  long lVar5;
  long lVar6;
  
  lVar5 = 0;
  lVar6 = 0x10;
  while ((puVar4 = *(ushort **)(lVar5 * 8 + 0x100c27638), puVar4 == (ushort *)0x0 ||
         (*puVar4 != param_1))) {
    lVar5 = lVar5 + 1;
    lVar6 = lVar6 + -1;
    if (lVar6 == 0) {
      iVar1 = 2;
      FUN_10000d938(2,0x18);
      if (iVar1 != 0) {
        FUN_10000d120("GetContextByRfcommHandle - context not found");
        uVar2 = 0x18;
        FUN_10000e9d4();
        uVar3 = uVar2;
        _os_log_type_enabled();
        if ((int)uVar3 != 0) {
          FUN_10018f150(uVar2);
        }
      }
      return (ushort *)0x0;
    }
  }
  return puVar4;
}


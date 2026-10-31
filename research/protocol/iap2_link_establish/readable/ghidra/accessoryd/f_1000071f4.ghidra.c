/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000071f4
 * original code SHA256: 7749b468905afc002c5655d80a428f54cef9301e9f52e488368d62b2786bbbd5
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2PacketSetHdrChecksum(long param_1,int param_2,uint param_3)

{
  int iVar1;
  ushort uVar2;
  undefined *puVar3;
  undefined4 local_40;
  char *local_3c;
  undefined2 local_34;
  undefined4 local_32;
  undefined2 local_2e;
  int local_2c;
  
  if (param_2 == 1) {
    *(ushort *)(*(long *)(param_1 + 0x40) + 8) =
         (ushort)(param_3 >> 8) & 0xff | (ushort)((param_3 & 0xff00ff) << 8);
    if ((*(ushort *)(param_1 + 0x3d) & 0x3000) == 0) {
      *(long *)(param_1 + 0x48) = *(long *)(param_1 + 0x48) + 1;
    }
    uVar2 = *(ushort *)(param_1 + 0x3d) & 0xdfff | 0x1000;
  }
  else {
    if (param_2 != 0) {
      if ((__iAP2LogEnableMask & 1) == 0) {
        return;
      }
      if (_gLogObjects == 0 || _gNumLogObjects < 0x17) {
        puVar3 = PTR___os_log_default_10022bbb0;
        if (_logObjectForModule_onceToken != -1) {
          _iAP2PacketCalcChecksum_cold_1();
          puVar3 = PTR___os_log_default_10022bbb0;
        }
      }
      else {
        puVar3 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar1 = _os_log_type_enabled(puVar3,0);
      if (iVar1 == 0) {
        return;
      }
      local_40 = (undefined4)DAT_1001b3080;
      local_3c = "iAP2PacketSetHdrChecksum";
      local_34 = 0x400;
      local_32 = 0x837;
      local_2e = 0x400;
      local_2c = param_2;
      __os_log_impl(0x100000000,puVar3,0,"ERROR: %s:%d Unknown checksumType(%d)!",&local_40,0x18);
      return;
    }
    *(char *)(*(long *)(param_1 + 0x40) + 8) = (char)param_3;
    if ((*(ushort *)(param_1 + 0x3d) & 0x3000) == 0x1000) {
      *(long *)(param_1 + 0x48) = *(long *)(param_1 + 0x48) + -1;
    }
    uVar2 = *(ushort *)(param_1 + 0x3d) & 0xcfff;
  }
  *(ushort *)(param_1 + 0x3d) = uVar2;
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100035154
 * original code SHA256: 7f7a65c955d0970217dc74887fe841b58f2ac45b49224f71e248c42ccc2a0c5d
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2LinkCheckNegotiation(long param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  ulong uVar3;
  undefined *puVar4;
  uint uVar5;
  undefined4 local_50;
  char *local_4c;
  undefined2 local_44;
  undefined4 local_42;
  undefined2 local_3e;
  uint local_3c;
  undefined2 local_38;
  uint local_36;
  
  if (*(int *)(param_1 + 0xb8) == 1) {
    uVar3 = _iAP2LinkValidateSynParam(param_1,param_2);
    if ((uVar3 & 1) == 0) {
      _iAP2LinkEventNotify(param_1,3,param_2);
    }
  }
  else if (((*(byte *)(param_1 + 0xd4) >> 6 & 1) != 0) &&
          (_iAP2LinkValidateSynParam(param_1,param_2), (*(byte *)(param_1 + 0xd4) >> 6 & 1) == 0))
  goto LAB_100035334;
  iVar2 = _iAP2LinkIsNoRetransmit(param_1 + 0x168);
  if ((iVar2 != 0) && (uVar3 = _iAP2LinkIsNoRetransmit(param_2), (uVar3 & 1) == 0)) {
    *(undefined2 *)(param_1 + 0x169) = 0x1e01;
    *(undefined4 *)(param_1 + 0x16c) = 0x3e8ffff;
    *(undefined2 *)(param_1 + 0x170) = 10;
    *(undefined1 *)(param_1 + 0x16b) = 0;
  }
  uVar5 = (uint)*param_2;
  if (*param_2 < *(byte *)(param_1 + 0x168)) {
    if ((__iAP2LogEnableMask >> 1 & 1) != 0) {
      if ((_gLogObjects == 0) || (_gNumLogObjects < 0x17)) {
        if (_logObjectForModule_onceToken != -1) {
          _iAP2LinkEventNotify_cold_1();
        }
        uVar5 = (uint)*param_2;
        puVar4 = PTR___os_log_default_10022bbb0;
      }
      else {
        puVar4 = *(undefined **)(_gLogObjects + 0xb0);
      }
      iVar2 = _os_log_type_enabled(puVar4,1);
      if (iVar2 != 0) {
        local_50 = (undefined4)DAT_1001b30e0;
        local_4c = "iAP2LinkCheckNegotiation";
        local_44 = 0x400;
        local_42 = 0x18f6;
        local_3e = 0x400;
        local_3c = (uint)*(byte *)(param_1 + 0x168);
        local_38 = 0x400;
        local_36 = uVar5;
        __os_log_impl(0x100000000,puVar4,1,
                      "%s:%d Older protocol Version detected on the accessory (%d->%d)",&local_50,
                      0x1e);
        uVar5 = (uint)*param_2;
      }
    }
    *(char *)(param_1 + 0x168) = (char)uVar5;
  }
  if (param_2[2] < *(byte *)(param_1 + 0x16a)) {
    *(byte *)(param_1 + 0x16a) = param_2[2];
  }
  if (param_2[3] < *(byte *)(param_1 + 0x16b)) {
    *(byte *)(param_1 + 0x16b) = param_2[3];
  }
  if (*(ushort *)(param_2 + 6) < *(ushort *)(param_1 + 0x16e)) {
    *(ushort *)(param_1 + 0x16e) = *(ushort *)(param_2 + 6);
  }
  if (*(ushort *)(param_2 + 8) < *(ushort *)(param_1 + 0x170)) {
    *(ushort *)(param_1 + 0x170) = *(ushort *)(param_2 + 8);
  }
  iVar2 = _iAP2LinkIsNoRetransmit(param_2);
  if (iVar2 != 0) {
    *(byte *)(param_1 + 0x169) = param_2[1];
  }
LAB_100035334:
  *(byte *)(param_1 + 0x173) = param_2[1];
  *(undefined2 *)(param_1 + 0x174) = *(undefined2 *)(param_2 + 4);
  if ((*(int *)(param_1 + 0xb8) == 1) &&
     (bVar1 = param_2[0x18], *(byte *)(param_1 + 0x180) = bVar1, bVar1 != 0)) {
    uVar3 = 0;
    do {
      *(byte *)(param_1 + 0x181 + uVar3) = param_2[uVar3 + 0x19];
      uVar3 = uVar3 + 1;
    } while (uVar3 < param_2[0x18]);
  }
  bVar1 = param_2[10];
  *(byte *)(param_1 + 0x172) = bVar1;
  _memcpy((void *)(param_1 + 0x186),param_2 + 0x1e,(ulong)bVar1 << 2);
  return;
}


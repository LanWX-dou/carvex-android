/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100006e24
 * original code SHA256: 92cf0aa250e8bce2959f0cb9fc4e0d88030673f72699d067b7e6cfb2d54456fa
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



long _iAP2PacketCreate(undefined8 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                      void *param_5,uint param_6,undefined1 param_7,int param_8)

{
  uint uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  undefined2 *puVar7;
  ushort uVar8;
  ulong uVar9;
  uint local_64;
  
  local_64 = param_6;
  iVar3 = _iAP2LinkCurPckHdrSize();
  iVar4 = 0;
  if (param_6 != 0) {
    iVar4 = _iAP2LinkCurPckChksumSize(param_1);
  }
  if (param_8 == 0) {
    lVar5 = _iAP2PacketCreateEmptyRecvPacket(param_1);
  }
  else {
    lVar5 = _iAP2PacketCreateEmptySendPacket(param_1,&local_64);
  }
  uVar1 = local_64;
  if (lVar5 != 0) {
    puVar7 = *(undefined2 **)(lVar5 + 0x40);
    uVar9 = (ulong)local_64;
    iVar4 = iVar4 + iVar3 + local_64;
    *(short *)(lVar5 + 0x36) = (short)iVar4;
    *puVar7 = 0x5aff;
    *(char *)(puVar7 + 1) = (char)((uint)iVar4 >> 8);
    *(char *)((long)puVar7 + 3) = (char)iVar4;
    *(undefined1 *)(puVar7 + 2) = param_2;
    *(undefined1 *)((long)puVar7 + 5) = param_3;
    *(undefined1 *)(puVar7 + 3) = param_4;
    *(undefined1 *)((long)puVar7 + 7) = param_7;
    uVar6 = _iAP2LinkGetChecksumType(param_1);
    _iAP2PacketSetHdrChecksum(lVar5,uVar6,0);
    uVar8 = 0x200;
    if (param_8 == 0) {
      uVar8 = 0;
    }
    *(ushort *)(lVar5 + 0x3d) = *(ushort *)(lVar5 + 0x3d) & 0xfdff | uVar8;
    *(undefined1 *)(lVar5 + 0x3f) = 0;
    *(uint *)(lVar5 + 0x2c) = (uint)*(ushort *)(lVar5 + 0x36);
    if ((param_5 != (void *)0x0) && (uVar1 != 0)) {
      _memcpy(*(void **)(lVar5 + 0x48),param_5,uVar9);
    }
    uVar2 = _iAP2PacketGetPayloadLen(lVar5);
    *(undefined2 *)(lVar5 + 0x34) = uVar2;
    *(undefined4 *)(lVar5 + 0x38) = 0xff000000;
    *(undefined8 *)(lVar5 + 8) = 0;
    *(undefined8 *)(lVar5 + 0x10) = 0;
    *(ushort *)(lVar5 + 0x3d) = *(ushort *)(lVar5 + 0x3d) & 0xf600 | 0x12;
  }
  return lVar5;
}


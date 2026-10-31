/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100006120
 * original code SHA256: a2c9dc586cd9d863cb4d9d9dcad3c0a5fc1eaedfe238451148d53045e939be60
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



uint _iAP2PacketGetPayloadLen(undefined8 *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  
  uVar4 = *param_1;
  iVar2 = _iAP2LinkCurPckHdrSize(uVar4);
  iVar3 = _iAP2LinkCurPckChksumSize(uVar4);
  uVar1 = (uint)*(ushort *)((long)param_1 + 0x36) - (iVar3 + iVar2);
  if ((uint)*(ushort *)((long)param_1 + 0x36) < (uint)(iVar3 + iVar2) || uVar1 == 0) {
    uVar1 = 0;
  }
  return uVar1 & 0xffff;
}


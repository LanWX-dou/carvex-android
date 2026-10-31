/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000b368
 * original code SHA256: 6ef9b582ff5275f031303ec2e1b5c4294d9151eeec7762c8d1391dea68a25884
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


bool _iAP2PacketIsACKOnly(undefined8 *param_1)

{
  ushort uVar1;
  uint uVar2;
  
  if ((*(byte *)(param_1[8] + 4) & 0xf0) == 0x40) {
    uVar1 = *(ushort *)((long)param_1 + 0x36);
    uVar2 = _iAP2LinkCurPckHdrSize(*param_1);
    return uVar1 == uVar2;
  }
  return false;
}


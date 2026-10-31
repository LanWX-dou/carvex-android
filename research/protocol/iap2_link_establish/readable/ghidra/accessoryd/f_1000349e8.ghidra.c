/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1000349e8
 * original code SHA256: e5ba706b71f1495090c5714424f587d717640259cb261170eeea0102cd4bdd64
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


int _iAP2LinkGetMaxSendPayloadSize(long param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  if (param_1 != 0) {
    uVar1 = (uint)*(ushort *)(param_1 + 0x1a6);
    if ((uint)*(ushort *)(param_1 + 0xc0) <= (uint)*(ushort *)(param_1 + 0x1a6)) {
      uVar1 = (uint)*(ushort *)(param_1 + 0xc0);
    }
    uVar2 = uVar1;
    if ((param_2 != 0) && (uVar2 = *(uint *)(param_2 + 0x28), uVar1 <= *(uint *)(param_2 + 0x28))) {
      uVar2 = uVar1;
    }
    iVar3 = -0xc;
    if (*(char *)(param_1 + 0xd5) != '\x02') {
      iVar3 = -10;
    }
    iVar3 = iVar3 + uVar2;
  }
  return iVar3;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100034a40
 * original code SHA256: c25b76fb30080649af5790fa3617717b6527073515ced847fdd887408770bf4b
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _iAP2LinkGetMaxRecvPayloadSize(long param_1,long param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_1 != 0) {
    if (param_2 == 0) {
      iVar1 = 0xffff;
    }
    else {
      iVar1 = *(int *)(param_2 + 0x28);
    }
    iVar2 = -0xc;
    if (*(char *)(param_1 + 0xd5) != '\x02') {
      iVar2 = -10;
    }
    iVar2 = iVar2 + iVar1;
  }
  return iVar2;
}


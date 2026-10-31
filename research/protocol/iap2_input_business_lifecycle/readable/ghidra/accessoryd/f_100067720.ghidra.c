/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100067720
 * original code SHA256: b0771292ad94521fb16a70fbab8c3bc45e96616bb524a371f37876b9251b464a
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _iAP2MsgGetParamValueLen(ushort *param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)(*param_1 >> 8) | (*param_1 & 0xff00ff) << 8;
  iVar1 = 0;
  if (3 < uVar2) {
    iVar1 = uVar2 - 4;
  }
  return iVar1;
}


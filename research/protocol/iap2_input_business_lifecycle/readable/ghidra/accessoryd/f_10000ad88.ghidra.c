/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000ad88
 * original code SHA256: bc3bfb31bf9ccf3329c8a4ea1803d6c2b01d0aa537f8a913acdc729193a0192f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _iAP2PacketIsComplete(long param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 != 0) {
    bVar1 = 0x11 < (*(ushort *)(param_1 + 0x3d) & 0xfe);
  }
  return bVar1;
}


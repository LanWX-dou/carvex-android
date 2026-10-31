/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100067e4c
 * original code SHA256: b88854d880d67d4b43e346414807565faad8b9a7c3c6130c3bbac177398cfcd4
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined1 _iAP2MsgGetDataAsU8(ushort *param_1,uint *param_2)

{
  bool bVar1;
  
  bVar1 = (ushort)(*param_1 >> 8 | *param_1 << 8) != 5;
  *param_2 = (uint)bVar1;
  if (bVar1) {
    return 0;
  }
  return (char)param_1[2];
}


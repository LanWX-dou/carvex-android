/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10000b5c0
 * original code SHA256: ef30e42b769a6572415d41a5485fee19b2d09341452c3c23136809a1241c601f
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


bool _iAP2PacketIsSeqACKd(int param_1,int param_2,uint param_3)

{
  return (param_2 - param_1 & 0xffU) <= param_3;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100008e80
 * original code SHA256: 35d617c84ec7868c4b29fe11963b0608db9e428dde312cd3265d60f3183422e1
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2PacketGetHdrChecksum(long param_1)

{
  _iAP2PacketGetChecksum(*(long *)(param_1 + 0x40) + 8,*(ushort *)(param_1 + 0x3d) >> 0xc & 3);
  return;
}


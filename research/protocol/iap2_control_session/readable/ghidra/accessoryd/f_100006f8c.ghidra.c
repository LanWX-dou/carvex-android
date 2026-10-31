/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100006f8c
 * original code SHA256: 2b8f888621580f7874bdea4b5bf70214746fdde8023507e9f19e104348f3029d
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void _iAP2PacketCreateACKPacket
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6)

{
  _iAP2PacketCreate(param_1,0x40,param_2,param_3,param_4,param_5,param_6,1);
  return;
}


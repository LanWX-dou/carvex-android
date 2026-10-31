/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11e7c0
 * original code SHA256: 1d935ebb8d88cd5719863baf28208c502a3c027734a33e7f43a8a79a2c3dc298
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* IpodPacket::IpodPacket(IpodPacket const&) */

void __thiscall IpodPacket::IpodPacket(IpodPacket *this,IpodPacket *param_1)

{
  *this = *param_1;
  *(undefined2 *)(this + 2) = *(undefined2 *)(param_1 + 2);
  memcpy(this + 4,param_1 + 4,0xfffc);
  this[0x10000] = param_1[0x10000];
  return;
}


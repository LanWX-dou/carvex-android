/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11e818
 * original code SHA256: e282e309c2c5375d6cc79735d4275d113f4e6f7083746627949e6710758e1ac9
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* IpodPacket::clear() */

void __thiscall IpodPacket::clear(IpodPacket *this)

{
  *this = (IpodPacket)0x0;
  *(undefined2 *)(this + 2) = 0;
  memset(this + 4,0,0xfffc);
  this[0x10000] = (IpodPacket)0x0;
  return;
}


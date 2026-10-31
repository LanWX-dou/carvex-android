/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x128cb0
 * original code SHA256: 2edb08a13bcf8129103ee8a24efadda405f1bc78b265d64063660560591a7e61
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodIap2::sendAckPacket() */

void __thiscall CIpodIap2::sendAckPacket(CIpodIap2 *this)

{
  ushort uVar1;
  uchar auStack_10000 [65536];
  
  uVar1 = createLinkPacket(this,0x40,this[0x10],this[0x11],0,0,0,auStack_10000);
  write(this,auStack_10000,uVar1);
  return;
}


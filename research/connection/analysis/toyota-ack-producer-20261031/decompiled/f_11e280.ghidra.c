/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11e280
 * original code SHA256: 2f3b6f6686fd51e88030785bd4646403cb57ac71a5cbf077e500a85bdf0afab3
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::getHandle() */

undefined4 __thiscall CIpodDevice::getHandle(CIpodDevice *this)

{
  return *(undefined4 *)(this + 8);
}


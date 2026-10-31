/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x138370
 * original code SHA256: 997255f120eff7dae8b30933397f177f40663337e81b72d35d0d3ea7e8192ba6
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodIap2::packetProc(unsigned char const*, unsigned short, bool) */

undefined8 __thiscall
CIpodIap2::packetProc(CIpodIap2 *this,uchar *param_1,ushort param_2,bool param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  if (!param_3) {
    uVar2 = FUN_00137d60(this,param_1,param_2);
    return uVar2;
  }
  uVar1 = CIpodProtocol::getHandle((CIpodProtocol *)this);
  CIpodEvent::sendEvent(0xb,uVar1,param_2,param_1);
  return 0;
}


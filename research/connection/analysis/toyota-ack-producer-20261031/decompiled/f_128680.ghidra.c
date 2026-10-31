/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x128680
 * original code SHA256: a6beb70e6b7d51f1f780102fd188e5e7699f9c0d2358ed914e1c57fc35c0c887
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodIap2::write(unsigned char const*, unsigned short) */

undefined8 __thiscall CIpodIap2::write(CIpodIap2 *this,uchar *param_1,ushort param_2)

{
  char cVar1;
  undefined8 uVar2;
  
  cVar1 = CIpodProtocol::isExiting((CIpodProtocol *)this);
  if ((cVar1 == '\0') &&
     (cVar1 = CIpodProtocol::isDeviceExist((CIpodProtocol *)this), cVar1 != '\0')) {
    uVar2 = CIpodProtocol::send((CIpodProtocol *)this,param_1,param_2,false);
    return uVar2;
  }
  CIpodLog::i("CIpodIap2::write, ipod is destroyed, exiting...!\n");
  return 0xffffffff;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11e738
 * original code SHA256: 419c1df51d813df7c0be77e85ed18b750fff410de47cc1de571fa447a66be56d
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::send(unsigned char const*, unsigned short, bool) */

ulong __thiscall CIpodDevice::send(CIpodDevice *this,uchar *param_1,ushort param_2,bool param_3)

{
  int __fd;
  ulong uVar1;
  ulong uVar2;
  
  if (this[0x118] == (CIpodDevice)0x0) {
    if (!param_3) {
      uVar1 = FUN_0011e368(this,param_1,(ulong)param_2);
      return uVar1;
    }
    __fd = CIpodNative::getHandle();
    uVar2 = write(__fd,param_1,(ulong)param_2);
    uVar1 = uVar2 & 0xffffffff;
    if ((int)uVar2 < 0) {
      CIpodLog::e("CIpodDevice::send, write native error!\n");
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


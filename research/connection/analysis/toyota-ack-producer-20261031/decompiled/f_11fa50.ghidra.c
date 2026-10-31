/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11fa50
 * original code SHA256: 68750c9185a493035904619179f882bf5b478fb8f2676986167d2d082c5f5bba
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::packetProc(unsigned char const*, unsigned short, bool) */

undefined8 __thiscall
CIpodDevice::packetProc(CIpodDevice *this,uchar *param_1,ushort param_2,bool param_3)

{
  long *plVar1;
  undefined8 uVar2;
  
  plVar1 = *(long **)(this + 0x110);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0011fa68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(*plVar1 + 0x20))(plVar1,param_1,param_2,param_3);
    return uVar2;
  }
  return 0xffffffff;
}


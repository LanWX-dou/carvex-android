/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11f8b0
 * original code SHA256: 63a2fa32ec00e468a2947936174c575d2d426cf01a232b7586ce88f111cee1fd
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::connectIap2() */

ulong __thiscall CIpodDevice::connectIap2(CIpodDevice *this)

{
  int iVar1;
  CIpodIap2 *this_00;
  ulong uVar2;
  
  CIpodLog::i("iAP2 Link Initialization start.\n");
  iVar1 = CIpodConfig::getProtocol();
  if (iVar1 == 1) {
    this_00 = operator_new(0x374f0);
    CIpodIap1::CIpodIap1((CIpodIap1 *)this_00);
    *(CIpodIap2 **)(this + 0x110) = this_00;
    *(undefined4 *)(this + 0xa8) = 2;
    goto LAB_0011f92c;
  }
  iVar1 = checkIap2Support(this);
  if (iVar1 == -1) goto LAB_0011f924;
  if (this[0xac] != (CIpodDevice)0x0) {
    this_00 = operator_new(0x998);
    CIpodIap2::CIpodIap2(this_00);
    *(CIpodIap2 **)(this + 0x110) = this_00;
    goto LAB_0011f92c;
  }
  CIpodLog::e("iAP2 Link Initialization Detect, but not support iAP2.\n");
  iVar1 = CIpodConfig::getProtocol();
  if (iVar1 == 2) {
    if (*(code **)(*(long *)this + 0x18) != send) {
      (**(code **)(*(long *)this + 0x18))(this,&DAT_001427e0,0x12,0);
      goto LAB_0011f924;
    }
    if (this[0x118] != (CIpodDevice)0x0) goto LAB_0011f924;
    FUN_0011e368(this,&DAT_001427e0,0x12);
    this_00 = *(CIpodIap2 **)(this + 0x110);
  }
  else {
    iVar1 = CIpodConfig::getProtocol();
    if (iVar1 == 0) {
      this_00 = operator_new(0x374f0);
      CIpodIap1::CIpodIap1((CIpodIap1 *)this_00);
      *(CIpodIap2 **)(this + 0x110) = this_00;
      goto LAB_0011f92c;
    }
LAB_0011f924:
    this_00 = *(CIpodIap2 **)(this + 0x110);
  }
  if (this_00 == (CIpodIap2 *)0x0) {
    CIpodLog::e("CIpodDevice::create, ipod protocol is null!\n");
    return 0xffffffff;
  }
LAB_0011f92c:
  CIpodProtocol::registerProxy((CIpodProtocol *)this_00,(CIpodProxy *)this);
  uVar2 = (**(code **)(**(long **)(this + 0x110) + 0x10))
                    (*(long **)(this + 0x110),*(undefined4 *)(this + 0x30));
  if ((int)uVar2 == 0) {
    CIpodEvent::sendEvent(uVar2,*(undefined4 *)(this + 8),1);
  }
  return uVar2 & 0xffffffff;
}


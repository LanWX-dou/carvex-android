/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11f698
 * original code SHA256: 45f84e716f35b62e49b9b83bb382e1ee05d7754f99e3c05ffc24cf9f503dcc1d
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::create() */

int __thiscall CIpodDevice::create(CIpodDevice *this)

{
  int iVar1;
  long lVar2;
  
  CIpodLog::i("create iAP device and iAP2 support: %d.\n",(ulong)(byte)this[0xac]);
  iVar1 = openDevice(this);
  if (iVar1 == -1) {
    CIpodLog::e("CIpodDevice::create, device open failed!\n");
    return -1;
  }
  lVar2 = CIpodConfig::getIdentification();
  if ((*(short *)(lVar2 + 0xfc) != 0) && (iVar1 = CIpodConfig::getMode(), iVar1 == 1)) {
    iVar1 = CIpodNative::init();
    if (iVar1 != 0) {
      CIpodLog::e("CIpodDevice::create, native device open failed!\n");
      return iVar1;
    }
    iVar1 = pthread_create((pthread_t *)(this + 0x48),(pthread_attr_t *)0x0,
                           (__start_routine *)PTR_nativeThread_0016ff60,this);
    if (iVar1 != 0) {
      CIpodLog::e("CIpodDevice::create, native thread create failed!\n");
      return iVar1;
    }
    CIpodNative::registerSigioHandle();
  }
  iVar1 = pthread_create((pthread_t *)(this + 0x38),(pthread_attr_t *)0x0,
                         (__start_routine *)PTR_procThread_0016ff00,this);
  if (iVar1 == 0) {
    if ((*(int *)(this + 0x30) - 1U < 2) &&
       (iVar1 = pthread_create((pthread_t *)(this + 0x40),(pthread_attr_t *)0x0,
                               (__start_routine *)PTR_recvThread_0016ff40,this), iVar1 != 0)) {
      CIpodLog::e("CIpodDevice::create, recv thread create failed!\n");
    }
    else {
      this[0x34] = (CIpodDevice)0x1;
      iVar1 = 0;
    }
    return iVar1;
  }
  CIpodLog::e("CIpodDevice::create, proc thread create failed!\n");
  return iVar1;
}


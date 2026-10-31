/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x13c820
 * original code SHA256: 2503f7f98a0da105ee90c1ef3bddc7ce7fbd6a0cbb33df9e6cdd6e7e599381a8
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodLib::connect(int*, char const*) */

int __thiscall CIpodLib::connect(CIpodLib *this,int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  CIpodDevice *this_00;
  pthread_t local_8;
  
  CIpodLog::i("CIpodLib::connect, path = %s\n",param_2);
  CIpodSync::lock();
  cVar1 = CIpodList::isDeviceExist(param_2);
  if (cVar1 != '\0') {
    CIpodLog::e("iAP2 Device has already exist.\n");
    CIpodSync::unlock();
    return 0;
  }
  this_00 = operator_new(0x120);
  CIpodDevice::CIpodDevice(this_00,param_2);
  iVar2 = CIpodDevice::create(this_00);
  if (iVar2 == 0) {
    CIpodList::push(this_00);
    uVar3 = (**(code **)(*(long *)this_00 + 0x10))(this_00);
    *param_1 = uVar3;
    CIpodLog::i("An new device has been pushed into list successfully. handle: %d.\n",(ulong)uVar3);
    iVar2 = CIpodDevice::getConnMode(this_00);
    if ((iVar2 == 3) || (iVar2 = CIpodDevice::getConnMode(this_00), iVar2 == 4)) {
      pthread_create(&local_8,(pthread_attr_t *)0x0,
                     (__start_routine *)PTR_startIPodConnFunc_0016fee8,this_00);
      pthread_detach(local_8);
      CIpodSync::unlock();
      return 0;
    }
    iVar2 = CIpodDevice::connectIap2(this_00);
  }
  else {
    CIpodDevice::destroy(this_00);
    CIpodConfig::deinit();
    (**(code **)(*(long *)this_00 + 8))(this_00);
    CIpodLog::i("CIpodLib::connect, ipod create failed!\n");
  }
  CIpodSync::unlock();
  return iVar2;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11ea88
 * original code SHA256: 9be0fb9a44434849e402187fc2ad948c53d9839cf3bfef3845e8ebd66d528f3c
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::destroy() */

undefined4 __thiscall CIpodDevice::destroy(CIpodDevice *this)

{
  undefined4 uVar1;
  long lVar2;
  pthread_t pVar3;
  
  CIpodLog::i("CIpodDevice::destroy start handle: %d\n",(ulong)*(uint *)(this + 8));
  if ((*(int *)(this + 0x30) - 1U < 2) && (*(long **)(this + 0x110) != (long *)0x0)) {
    uVar1 = (**(code **)(**(long **)(this + 0x110) + 0x18))();
  }
  else {
    uVar1 = 0xffffffff;
  }
  this[0x118] = (CIpodDevice)0x1;
  if (0 < *(int *)(this + 8)) {
    close(*(int *)(this + 8));
    *(undefined4 *)(this + 8) = 0;
  }
  CIpodLog::i("CIpodDevice::destroy exit handle successfully.\n");
  if (*(int *)(this + 0x30) == 3) {
    CIpodVehicle::setbtSppConnStatus(0);
    lVar2 = *(long *)(this + 0x38);
  }
  else {
    CIpodVehicle::setWiFiConnStatus();
    lVar2 = *(long *)(this + 0x38);
  }
  if (lVar2 == 0) {
    CIpodLog::i("iAP2 ProcessThread has already terminated.\n");
    pVar3 = *(pthread_t *)(this + 0x40);
  }
  else {
    sem_post((sem_t *)(this + 0x68));
    if (*(pthread_t *)(this + 0x38) == 0) {
      *(undefined8 *)(this + 0x38) = 0;
    }
    else {
      pthread_join(*(pthread_t *)(this + 0x38),(void **)0x0);
      *(undefined8 *)(this + 0x38) = 0;
    }
    CIpodLog::i("iAP2 ProcessThread has already terminated.\n");
    pVar3 = *(pthread_t *)(this + 0x40);
  }
  if (pVar3 == 0) {
    CIpodLog::i("iAP2 ReceiveThread has already terminated.\n");
    pVar3 = *(pthread_t *)(this + 0x48);
  }
  else {
    pthread_join(pVar3,(void **)0x0);
    *(undefined8 *)(this + 0x40) = 0;
    CIpodLog::i("iAP2 ReceiveThread has already terminated.\n");
    pVar3 = *(pthread_t *)(this + 0x48);
  }
  if (pVar3 != 0) {
    pthread_join(pVar3,(void **)0x0);
    *(undefined8 *)(this + 0x48) = 0;
  }
  CIpodLog::i("iAP2 NativeThread has already terminated.\n");
  usleep(2000);
  if (*(long *)(this + 0x110) != 0) {
    CIpodProtocol::unregisterProxy();
    if (*(long **)(this + 0x110) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x110) + 8))();
    }
    *(undefined8 *)(this + 0x110) = 0;
  }
  CIpodLog::i("CIpodDevice::destroy successfully.\n");
  return uVar1;
}


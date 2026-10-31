/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11fa78
 * original code SHA256: b761a51199bbae3db4bc76ea13a9f3729db8dd3427de07378a0a66c437a058e0
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::procThread(void*) */

undefined8 CIpodDevice::procThread(void *param_1)

{
  pthread_mutex_t *__mutex;
  code *pcVar1;
  uint uVar2;
  IpodPacket *this;
  undefined8 *puVar3;
  
  if (*(code **)(*(long *)param_1 + 0x10) == getHandle) {
    uVar2 = *(uint *)((long)param_1 + 8);
  }
  else {
    uVar2 = (**(code **)(*(long *)param_1 + 0x10))();
  }
  __mutex = (pthread_mutex_t *)((long)param_1 + 0xe0);
  CIpodLog::w("==================== ProcessThread Start fd: %d ====================\n",(ulong)uVar2)
  ;
  while (sem_wait((sem_t *)((long)param_1 + 0x68)), *(char *)((long)param_1 + 0x118) == '\0') {
    while( true ) {
      pthread_mutex_lock(__mutex);
      puVar3 = *(undefined8 **)((long)param_1 + 0x50);
      if (puVar3 == (undefined8 *)((long)param_1 + 0x50)) break;
      this = (IpodPacket *)puVar3[2];
      if (this == (IpodPacket *)0x0) {
                    /* WARNING: Does not return */
        pcVar1 = (code *)SoftwareBreakpoint(1000,0x11fb98);
        (*pcVar1)();
      }
      if ((*this != (IpodPacket)0x0) || (*(char *)((long)param_1 + 0x118) != '\0')) {
        CIpodLog::i("packet->exit = %d, device->m_Exiting = %d\n");
        *(long *)((long)param_1 + 0x60) = *(long *)((long)param_1 + 0x60) + -1;
        std::__detail::_List_node_base::_M_unhook();
        operator_delete(puVar3);
        IpodPacket::~IpodPacket(this);
        operator_delete(this);
        pthread_mutex_unlock(__mutex);
        goto LAB_0011fbd8;
      }
      packetProc(param_1,(uchar *)(this + 4),*(ushort *)(this + 2),(bool)this[0x10000]);
      usleep(1000);
      *(long *)((long)param_1 + 0x60) = *(long *)((long)param_1 + 0x60) + -1;
      std::__detail::_List_node_base::_M_unhook();
      operator_delete(puVar3);
      IpodPacket::~IpodPacket(this);
      operator_delete(this);
      usleep(1000);
      pthread_mutex_unlock(__mutex);
      sem_wait((sem_t *)((long)param_1 + 0x68));
      if (*(char *)((long)param_1 + 0x118) != '\0') goto LAB_0011fb7c;
    }
    CIpodLog::i("CIpodDevice::procThread, m_Packets is empty! continue...\n");
    pthread_mutex_unlock(__mutex);
  }
LAB_0011fb7c:
  CIpodLog::i("ProcessThread exiting because iAP2 Device has been exited.\n");
LAB_0011fbd8:
  *(undefined8 *)((long)param_1 + 0x38) = 0;
  CIpodLog::w("==================== ProcessThread end fd: %d   ====================\n",(ulong)uVar2)
  ;
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11fc30
 * original code SHA256: 57cd23e91d7e6ac3e2244254b461939bb96ca8ee87b8ba742621b6a9db643c78
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::packetAdd(IpodPacket*) */

int __thiscall CIpodDevice::packetAdd(CIpodDevice *this,IpodPacket *param_1)

{
  int iVar1;
  _List_node_base *p_Var2;
  
  pthread_mutex_lock((pthread_mutex_t *)(this + 0xe0));
  p_Var2 = operator_new(0x18);
  *(IpodPacket **)(p_Var2 + 0x10) = param_1;
  std::__detail::_List_node_base::_M_hook(p_Var2);
  *(long *)(this + 0x60) = *(long *)(this + 0x60) + 1;
  pthread_mutex_unlock((pthread_mutex_t *)(this + 0xe0));
  iVar1 = sem_post((sem_t *)(this + 0x68));
  return iVar1;
}


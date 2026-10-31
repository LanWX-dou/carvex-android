/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11fc90
 * original code SHA256: eb6d944917a3dc20067af709df8b3e4349ed0f54e751005e6d9e675686e95028
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodDevice::ipod_BT_spp_data_pro(int, char const*) */

undefined8 __thiscall CIpodDevice::ipod_BT_spp_data_pro(CIpodDevice *this,int param_1,char *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  char *__src;
  IpodPacket *pIVar4;
  ulong __n;
  ulong __n_00;
  
  if (this[0x118] != (CIpodDevice)0x0) {
    return 0;
  }
  if (((this[0xac] == (CIpodDevice)0x0) && (DAT_001427d0 == *(int *)param_2)) &&
     (DAT_001427d4 == *(short *)(param_2 + 4))) {
    CIpodLog::i("[  Device   ] step 2:  DETECT over Rfcomm.\n");
    *(undefined4 *)(this + 0xa8) = 2;
    this[0xac] = (CIpodDevice)0x1;
    sem_post((sem_t *)(this + 0x88));
  }
  else {
    uVar1 = (uint)(byte)param_2[2] * 0x100 + (uint)(byte)param_2[3];
    __n = (ulong)uVar1;
    pIVar4 = operator_new(0x10002);
    IpodPacket::IpodPacket(pIVar4);
    *(short *)(pIVar4 + 2) = (short)uVar1;
    pIVar4[0x10000] = (IpodPacket)0x0;
    memcpy(pIVar4 + 4,param_2,__n);
    packetAdd(this,pIVar4);
    if ((int)uVar1 < param_1) {
      __src = param_2 + __n;
      uVar2 = (uint)(byte)__src[2] * 0x100 + (uint)(byte)__src[3];
      __n_00 = (ulong)uVar2;
      CIpodLog::w("Rfcomm data ( Device -> Accessory ) size: %d, First iAP2 Packet size: %d, Second iAP2 Packet size: %d\n"
                  ,(ulong)(uint)param_1,(ulong)uVar1,__n_00);
      pIVar4 = operator_new(0x10002);
      IpodPacket::IpodPacket(pIVar4);
      *(short *)(pIVar4 + 2) = (short)uVar2;
      pIVar4[0x10000] = (IpodPacket)0x0;
      memcpy(pIVar4 + 4,__src,__n_00);
      packetAdd(this,pIVar4);
      iVar3 = uVar1 + uVar2;
      if (iVar3 < param_1) {
        uVar2 = (uint)(byte)param_2[(long)iVar3 + 2] * 0x100 + (uint)(byte)param_2[(long)iVar3 + 3];
        CIpodLog::w("Rfcomm data ( Device -> Accessory ) size: %d, First iAP2 Packet size: %d, Second iAP2 Packet size: %d, Third iAP2 Packet size: %d\n"
                    ,(ulong)(uint)param_1,(ulong)uVar1,__n_00,(ulong)uVar2);
        pIVar4 = operator_new(0x10002);
        IpodPacket::IpodPacket(pIVar4);
        *(short *)(pIVar4 + 2) = (short)uVar2;
        pIVar4[0x10000] = (IpodPacket)0x0;
        memcpy(pIVar4 + 4,param_2 + __n + __n_00,(ulong)uVar2);
        packetAdd(this,pIVar4);
        return 0;
      }
    }
  }
  return 0;
}


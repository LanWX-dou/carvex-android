/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x120010
 * original code SHA256: d2776eba7b2483cc0834d2f4890bb8ac6c501af017bd090fb4779885204730ed
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CIpodDevice::recvThread(void*) */

undefined8 CIpodDevice::recvThread(void *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  short sVar5;
  code *pcVar6;
  int iVar7;
  int iVar8;
  uint __fd;
  ssize_t sVar9;
  IpodPacket *this;
  uint *puVar10;
  char *pcVar11;
  ulong uVar12;
  timeval tStack_200a0;
  fd_set fStack_20090;
  undefined1 uStack_20008;
  byte bStack_20007;
  undefined1 auStack_20006 [65534];
  IpodPacket aIStack_10008 [2];
  ushort uStack_10006;
  int iStack_10004;
  short local_10000;
  char local_fffe;
  undefined1 local_8;
  
  tStack_200a0.tv_usec = _UNK_00142798;
  tStack_200a0.tv_sec = _DAT_00142790;
  memset(&uStack_20008,0,0xfffc);
  IpodPacket::IpodPacket(aIStack_10008);
  local_8 = 0;
  if (param_1 == (void *)0x0) {
    CIpodLog::i("CIpodDevice::recvThread, device is null !!!!!!!!!!!!!!!\n");
    uRam0000000000000040 = 0;
                    /* WARNING: Does not return */
    pcVar6 = (code *)SoftwareBreakpoint(1000,0x1203c0);
    (*pcVar6)();
  }
  if (*(code **)(*(long *)param_1 + 0x10) == getHandle) {
    __fd = *(uint *)((long)param_1 + 8);
  }
  else {
    __fd = (**(code **)(*(long *)param_1 + 0x10))(param_1);
  }
  CIpodLog::i("==================== ReceiveThread start fd: %d ====================\n",(ulong)__fd);
  uVar3 = __fd + 0x3f;
  if (-1 < (int)__fd) {
    uVar3 = __fd;
  }
  uVar1 = __fd & 0x3f;
  if (-1 < (int)-__fd) {
    uVar1 = -(-__fd & 0x3f);
  }
  iVar2 = (int)uVar3 >> 6;
  uVar12 = 1L << ((ulong)uVar1 & 0x3f);
LAB_001200e4:
  do {
    do {
      do {
        cVar4 = *(char *)((long)param_1 + 0x118);
        while( true ) {
          if (cVar4 != '\0') {
            CIpodLog::w("ReceiveThread exiting because iAP2 Device has been exited.\n");
            goto LAB_00120280;
          }
          tStack_200a0.tv_sec = 2;
          fStack_20090.fds_bits[1] = 0;
          fStack_20090.fds_bits[0] = 0;
          fStack_20090.fds_bits[3] = 0;
          fStack_20090.fds_bits[2] = 0;
          fStack_20090.fds_bits[5] = 0;
          fStack_20090.fds_bits[4] = 0;
          fStack_20090.fds_bits[7] = 0;
          fStack_20090.fds_bits[6] = 0;
          fStack_20090.fds_bits[9] = 0;
          fStack_20090.fds_bits[8] = 0;
          fStack_20090.fds_bits[0xb] = 0;
          fStack_20090.fds_bits[10] = 0;
          fStack_20090.fds_bits[0xd] = 0;
          fStack_20090.fds_bits[0xc] = 0;
          fStack_20090.fds_bits[0xf] = 0;
          fStack_20090.fds_bits[0xe] = 0;
          fStack_20090.fds_bits[iVar2] = fStack_20090.fds_bits[iVar2] | uVar12;
          iVar7 = select(__fd + 1,&fStack_20090,(fd_set *)0x0,(fd_set *)0x0,&tStack_200a0);
          if (iVar7 < 0) {
            CIpodLog::i("iAP2 ReceiveThread select error\n");
            iVar2 = *(int *)((long)param_1 + 0xa8);
            goto joined_r0x0012038c;
          }
          if (iVar7 != 0) break;
          CIpodLog::i("iAP2 ReceiveThread select timeout(no message), continue select.\n");
          cVar4 = *(char *)((long)param_1 + 0x118);
        }
      } while ((uVar12 & fStack_20090.fds_bits[iVar2]) == 0);
      sVar9 = read(__fd,&uStack_20008,0xfffc);
      iVar7 = (int)sVar9;
      if (iVar7 < 0) {
        puVar10 = (uint *)__errno_location();
        uVar3 = *puVar10;
        pcVar11 = strerror(uVar3);
        CIpodLog::e("iAP2 ReceiveThread read error. errno is %d, strerror is %s.\n",(ulong)uVar3,
                    pcVar11);
LAB_00120280:
        iVar2 = *(int *)((long)param_1 + 0xa8);
joined_r0x0012038c:
        if (iVar2 == 1) {
          *(undefined4 *)((long)param_1 + 0xa8) = 3;
          sem_post((sem_t *)((long)param_1 + 0x88));
        }
        *(undefined1 *)((long)param_1 + 0x34) = 0;
        *(undefined8 *)((long)param_1 + 0x40) = 0;
        CIpodEvent::sendEvent(0,__fd,0);
        CIpodLog::w("==================== ReceiveThread end fd: %d   ====================\n",
                    (ulong)__fd);
        IpodPacket::~IpodPacket(aIStack_10008);
        return 0;
      }
    } while (iVar7 == 0);
    iVar8 = CIpodConfig::getMode();
    sVar5 = (short)sVar9;
    if (iVar8 == 0) {
      if (1 < bStack_20007) {
        memcpy((void *)((long)&iStack_10004 + (ulong)uStack_10006),auStack_20006,(long)(iVar7 + -2))
        ;
        uStack_10006 = sVar5 + (uStack_10006 - 2);
        goto LAB_001200e4;
      }
      memcpy((void *)((long)&iStack_10004 + (ulong)uStack_10006),auStack_20006,(long)(iVar7 + -2));
      uStack_10006 = sVar5 + (uStack_10006 - 2);
LAB_001201d4:
      if (*(int *)((long)param_1 + 0xa8) == 1) goto LAB_001201e0;
LAB_00120348:
      this = operator_new(0x10002);
      IpodPacket::IpodPacket(this,aIStack_10008);
      packetAdd(param_1,this);
    }
    else {
      iVar8 = CIpodConfig::getMode();
      if ((iVar8 != 1) && (iVar8 = CIpodConfig::getMode(), iVar8 != 2)) goto LAB_001201d4;
      memcpy((void *)((long)&iStack_10004 + (ulong)uStack_10006),&uStack_20008,(long)iVar7);
      uStack_10006 = uStack_10006 + sVar5;
      if (*(int *)((long)param_1 + 0xa8) != 1) goto LAB_00120348;
LAB_001201e0:
      if ((DAT_001427d0 == iStack_10004) && (DAT_001427d4 == local_10000)) {
        CIpodLog::i("[  Device   ] step 2:  DETECT over USB.\n");
        *(undefined4 *)((long)param_1 + 0xa8) = 2;
        *(undefined1 *)((long)param_1 + 0xac) = 1;
        sem_post((sem_t *)((long)param_1 + 0x88));
      }
      else if (((DAT_001427f8 == iStack_10004) && (DAT_001427fc == (char)local_10000)) ||
              (((DAT_00142800 == iStack_10004 && (DAT_00142804 == local_10000)) &&
               (DAT_00142806 == local_fffe)))) {
        CIpodLog::i("CIpodDevice::recvThread, support iap1!\n");
        *(undefined1 *)((long)param_1 + 0xac) = 0;
        *(undefined4 *)((long)param_1 + 0xa8) = 2;
        sem_post((sem_t *)((long)param_1 + 0x88));
      }
    }
    IpodPacket::clear(aIStack_10008);
  } while( true );
}


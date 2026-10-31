/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11e368
 * original code SHA256: af8601c40281c02a11f242d67f17331241d7e011d79ef74c6503a7af166bd0e9
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined4 FUN_0011e368(long param_1,void *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  ssize_t sVar5;
  uint *puVar6;
  char *pcVar7;
  code *pcVar8;
  ulong __n;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  uint local_414;
  undefined2 local_400;
  undefined1 auStack_3fe [1022];
  
  param_3 = param_3 & 0xffff;
  __n = (ulong)param_3;
  if (*(int *)(param_1 + 0x30) == 3) {
    pcVar8 = *(code **)PTR_bt_send_data_0016ff90;
    if (pcVar8 == (code *)0x0) {
      CIpodLog::e("CIpodDevice::send, bt_send_data is null!\n");
      return 0;
    }
  }
  else {
    if (*(int *)(param_1 + 0x30) != 4) {
      iVar4 = CIpodConfig::getMode();
      if (iVar4 == 0) {
        if (0 < *(int *)(param_1 + 8)) {
          pthread_mutex_lock((pthread_mutex_t *)(param_1 + 0xb0));
          local_414 = 0;
          uVar2 = param_3 / 0x3fe;
          if (param_3 % 0x3fe != 0) {
            uVar2 = uVar2 + 1;
          }
          uVar3 = uVar2 - 1;
          if (uVar2 == 1) goto LAB_0011e5d8;
LAB_0011e47c:
          if (uVar2 == 0) goto LAB_0011e53c;
          uVar11 = 0;
          uVar10 = 0;
          do {
            while( true ) {
              if (uVar10 != 0) break;
              local_400 = 0x201;
              if (uVar3 != 0) goto LAB_0011e494;
LAB_0011e4e0:
              uVar1 = uVar10 + 1;
              memcpy(auStack_3fe,(void *)((long)param_2 + (ulong)(ushort)uVar11),
                     (long)(int)(param_3 + uVar10 * -0x3fe));
              sVar5 = write(*(int *)(param_1 + 8),&local_400,
                            (long)(int)(param_3 + 2 + uVar10 * -0x3fe));
              iVar4 = (int)sVar5;
              uVar11 = (param_3 + ((uVar3 & 0x7f) * 0x200 - uVar3) * -2 & 0xffff) + uVar11 & 0xffff;
              uVar10 = uVar1;
              if (uVar2 <= (uVar1 & 0xffff)) goto joined_r0x0011e538;
            }
            if (uVar10 == uVar3) {
              local_400 = 0x101;
              goto LAB_0011e4e0;
            }
            local_400 = 0x301;
LAB_0011e494:
            uVar10 = uVar10 + 1;
            memcpy(auStack_3fe,(void *)((long)param_2 + (ulong)(ushort)uVar11),0x3fe);
            sVar5 = write(*(int *)(param_1 + 8),&local_400,0x400);
            iVar4 = (int)sVar5;
            uVar11 = uVar11 + 0x3fe & 0xffff;
          } while ((uVar10 & 0xffff) < uVar2);
joined_r0x0011e538:
          do {
            uVar9 = 0;
            if (-1 < iVar4) {
LAB_0011e60c:
              pthread_mutex_unlock((pthread_mutex_t *)(param_1 + 0xb0));
              return uVar9;
            }
LAB_0011e53c:
            puVar6 = (uint *)__errno_location();
            uVar10 = *puVar6;
            local_414 = local_414 + 1;
            pcVar7 = strerror(uVar10);
            CIpodLog::w("CIpodDevice::send, send error in device mode (%d)--%s\n",(ulong)uVar10,
                        pcVar7);
            usleep(200000);
            CIpodLog::e("CIpodDevice::send failed, retryCount:%d m_DeviceExist:%d m_Exiting:%d!\n",
                        (ulong)local_414,(ulong)*(byte *)(param_1 + 0x34),
                        (ulong)*(byte *)(param_1 + 0x118));
            if ((local_414 == 3) || (*(char *)(param_1 + 0x34) == '\0')) {
              uVar9 = 0xffffffff;
              goto LAB_0011e60c;
            }
            uVar10 = *puVar6;
            pcVar7 = strerror(uVar10);
            CIpodLog::w("CIpodDevice::send, send error in device mode (%d)--%s --- retryCount:(%d)\n"
                        ,(ulong)uVar10,pcVar7,(ulong)local_414);
            if (uVar2 != 1) goto LAB_0011e47c;
LAB_0011e5d8:
            local_400 = (undefined2)uVar2;
            memcpy(auStack_3fe,param_2,__n);
            sVar5 = write(*(int *)(param_1 + 8),&local_400,(long)(int)(param_3 + 2));
            iVar4 = (int)sVar5;
          } while( true );
        }
      }
      else {
        iVar4 = CIpodConfig::getMode();
        if (((iVar4 == 1) || (iVar4 = CIpodConfig::getMode(), iVar4 == 2)) &&
           (0 < *(int *)(param_1 + 8))) {
          pthread_mutex_lock((pthread_mutex_t *)(param_1 + 0xb0));
          sVar5 = write(*(int *)(param_1 + 8),param_2,__n);
          if ((int)sVar5 < 0) {
            puVar6 = (uint *)__errno_location();
            uVar2 = *puVar6;
            pcVar7 = strerror(uVar2);
            CIpodLog::w("write gadget_transfer error. errno: %d, errorstr: %s\n",(ulong)uVar2,pcVar7
                       );
          }
          pthread_mutex_unlock((pthread_mutex_t *)(param_1 + 0xb0));
          return 0;
        }
      }
      return 0xffffffff;
    }
    pcVar8 = *(code **)PTR_wifiDataCallback_0016fec0;
    if (pcVar8 == (code *)0x0) {
      CIpodLog::e("CIpodDevice::send, wifiDataCallback is null!\n");
      return 0;
    }
  }
  (*pcVar8)(__n);
  return 0;
}


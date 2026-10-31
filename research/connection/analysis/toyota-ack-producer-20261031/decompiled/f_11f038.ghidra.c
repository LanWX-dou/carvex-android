/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x11f038
 * original code SHA256: d54bfc421e07972f03112a8ec6ef5dc51f7b08f80910dbc9c65d552cd0807c33
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Type propagation algorithm not settling */
/* CIpodDevice::openDevice() */

undefined8 __thiscall CIpodDevice::openDevice(CIpodDevice *this)

{
  uint uVar1;
  _List_node_base *__src;
  uint uVar2;
  char cVar3;
  int iVar4;
  FILE *__stream;
  char *pcVar5;
  size_t __n;
  _List_node_base *p_Var6;
  long *******ppppppplVar7;
  _List_node_base *p_Var8;
  ulong *puVar9;
  int *piVar10;
  long lVar11;
  long *******ppppppplVar12;
  ulong uVar13;
  long *******ppppppplVar14;
  int iVar15;
  size_t local_4c8;
  long *******local_4c0;
  long *******ppppppplStack_4b8;
  long local_4b0;
  ulong *local_4a0;
  size_t local_498;
  ulong local_490;
  undefined8 uStack_488;
  undefined8 local_480;
  undefined8 uStack_478;
  undefined8 local_470;
  undefined8 uStack_468;
  undefined8 local_460;
  undefined8 uStack_458;
  undefined8 local_450;
  undefined8 uStack_448;
  undefined8 local_440;
  undefined8 uStack_438;
  undefined8 local_430;
  undefined8 uStack_428;
  undefined8 local_420;
  undefined8 uStack_418;
  undefined8 local_410;
  undefined8 uStack_408;
  ulong local_400 [128];
  
  iVar4 = CIpodConfig::getMode();
  if ((iVar4 != 0) &&
     ((iVar4 = CIpodConfig::getMode(), iVar4 != 2 || (iVar4 = CIpodConfig::connMode(), iVar4 != 2)))
     ) {
    iVar4 = CIpodConfig::getMode();
    if ((iVar4 == 1) ||
       ((iVar4 = CIpodConfig::getMode(), iVar4 == 2 && (iVar4 = CIpodConfig::connMode(), iVar4 == 1)
        ))) {
      iVar4 = open("/dev/gadget_transfer",2);
      if (iVar4 < 1) {
        CIpodLog::i("ipod usb host device open failed!\n");
        return 0xffffffff;
      }
      CIpodLog::i("open iAP2 over HostUsb device success.\n");
      *(undefined4 *)(this + 0x30) = 1;
    }
    else {
      iVar4 = CIpodConfig::getMode();
      if ((iVar4 == 2) && (iVar4 = CIpodConfig::connMode(), iVar4 == 3)) {
        CIpodLog::i("iAP2 over bluetooth for wireless CarPlay.\n");
        iVar4 = CIpodVehicle::getbtSppConnStatus();
        if (iVar4 != 3) {
          CIpodLog::i("ipod over buletooth device open failed!\n");
          return 0xffffffff;
        }
        iVar4 = 0xff;
        *(undefined4 *)(this + 0x30) = 3;
      }
      else {
        iVar4 = CIpodConfig::getMode();
        if (iVar4 != 2) {
          return 0xffffffff;
        }
        iVar4 = CIpodConfig::connMode();
        if (iVar4 != 4) {
          return 0xffffffff;
        }
        CIpodVehicle::setWiFiConnStatus(0);
        *(undefined4 *)(this + 0x30) = 4;
        iVar4 = 0xfe;
        CIpodLog::i("iAP2 over Wi-Fi for wireless CarPlay.\n");
      }
    }
LAB_0011f2c0:
    *(int *)(this + 8) = iVar4;
    return 0;
  }
  *(undefined4 *)(this + 0x30) = 2;
  lVar11 = *(long *)(this + 0x18);
  local_4b0 = 0;
  local_4c0 = (long *******)&local_4c0;
  ppppppplStack_4b8 = (long *******)&local_4c0;
  CIpodLog::i("CIpodDevice::openDevice --- isEmpty == %d",(ulong)(lVar11 == 0));
  if (lVar11 == 0) {
    memset(local_400,0,0x400);
    __stream = popen("ls /dev/hidraw* |grep -c \'hidraw\'","r");
    if (__stream == (FILE *)0x0) {
      piVar10 = __errno_location();
      pcVar5 = strerror(*piVar10);
      CIpodLog::e("CIpodDevice::openDevice, execute command failed: %s",pcVar5);
      ppppppplVar12 = local_4c0;
    }
    else {
      pcVar5 = fgets((char *)local_400,0x400,__stream);
      if (pcVar5 != (char *)0x0) {
        pclose(__stream);
        if (((byte)local_400[0] - 0x31 & 0xff) < 9) {
          uVar2 = (byte)local_400[0] - 0x30;
          uVar13 = 0;
LAB_0011f11c:
          do {
            local_480 = 0;
            uStack_478 = 0;
            local_470 = 0;
            uStack_468 = 0;
            local_460 = 0;
            uStack_458 = 0;
            local_450 = 0;
            uStack_448 = 0;
            local_440 = 0;
            uStack_438 = 0;
            local_430 = 0;
            uStack_428 = 0;
            local_420 = 0;
            uStack_418 = 0;
            local_410 = 0;
            uStack_408 = 0;
            sprintf((char *)&local_480,"/dev/hidraw%d",uVar13);
            local_4a0 = &local_490;
            __n = strlen((char *)&local_480);
            local_4c8 = __n;
            if (__n < 0x10) {
              puVar9 = &local_490;
              if (__n == 1) {
                local_490 = CONCAT71(local_490._1_7_,(char)local_480);
              }
              else if (__n != 0) goto LAB_0011f484;
            }
            else {
              local_4a0 = (ulong *)std::__cxx11::string::_M_create
                                             ((ulong *)&local_4a0,(ulong)&local_4c8);
              local_490 = local_4c8;
              puVar9 = local_4a0;
LAB_0011f484:
              memcpy(puVar9,&local_480,__n);
              puVar9 = local_4a0;
            }
            *(undefined1 *)((long)puVar9 + local_4c8) = 0;
            local_498 = local_4c8;
            p_Var6 = operator_new(0x30);
            *(_List_node_base **)(p_Var6 + 0x10) = p_Var6 + 0x20;
            if (local_4a0 == &local_490) {
              *(ulong *)(p_Var6 + 0x20) = local_490;
              *(undefined8 *)(p_Var6 + 0x28) = uStack_488;
            }
            else {
              *(ulong **)(p_Var6 + 0x10) = local_4a0;
              *(ulong *)(p_Var6 + 0x20) = local_490;
            }
            uVar1 = (int)uVar13 + 1;
            uVar13 = (ulong)uVar1;
            *(size_t *)(p_Var6 + 0x18) = local_498;
            local_490 = local_490 & 0xffffffffffffff00;
            local_498 = 0;
            local_4a0 = &local_490;
            std::__detail::_List_node_base::_M_hook(p_Var6);
            local_4b0 = local_4b0 + 1;
            if (local_4a0 != &local_490) {
              operator_delete(local_4a0);
              if (uVar2 == uVar1) break;
              goto LAB_0011f11c;
            }
          } while (uVar1 != uVar2);
        }
        goto LAB_0011f1ec;
      }
      CIpodLog::e("CIpodDevice::openDevice, execute command buf is null\n");
      pclose(__stream);
      ppppppplVar12 = local_4c0;
    }
    while ((long ********)ppppppplVar12 != &local_4c0) {
      ppppppplVar7 = (long *******)*ppppppplVar12;
      if ((long *******)ppppppplVar12[2] == ppppppplVar12 + 4) {
        operator_delete(ppppppplVar12);
        ppppppplVar12 = ppppppplVar7;
      }
      else {
        operator_delete(ppppppplVar12[2]);
        operator_delete(ppppppplVar12);
        ppppppplVar12 = ppppppplVar7;
      }
    }
  }
  else {
    p_Var8 = operator_new(0x30);
    __src = *(_List_node_base **)(this + 0x10);
    uVar13 = *(ulong *)(this + 0x18);
    p_Var6 = p_Var8 + 0x20;
    *(_List_node_base **)(p_Var8 + 0x10) = p_Var6;
    if (__src + uVar13 != (_List_node_base *)0x0 && __src == (_List_node_base *)0x0) {
                    /* WARNING: Subroutine does not return */
      std::__throw_logic_error("basic_string::_M_construct null not valid");
    }
    local_400[0] = uVar13;
    if (uVar13 < 0x10) {
      if (uVar13 == 1) {
        p_Var8[0x20] = *__src;
      }
      else if (uVar13 != 0) goto LAB_0011f55c;
    }
    else {
      p_Var6 = (_List_node_base *)
               std::__cxx11::string::_M_create((ulong *)(p_Var8 + 0x10),(ulong)local_400);
      *(_List_node_base **)(p_Var8 + 0x10) = p_Var6;
      *(ulong *)(p_Var8 + 0x20) = local_400[0];
LAB_0011f55c:
      memcpy(p_Var6,__src,uVar13);
      p_Var6 = *(_List_node_base **)(p_Var8 + 0x10);
    }
    *(ulong *)(p_Var8 + 0x18) = local_400[0];
    p_Var6[local_400[0]] = (_List_node_base)0x0;
    std::__detail::_List_node_base::_M_hook(p_Var8);
    local_4b0 = local_4b0 + 1;
LAB_0011f1ec:
    ppppppplVar12 = local_4c0;
    if ((long ********)local_4c0 != &local_4c0) {
      do {
        while (iVar4 = open((char *)ppppppplVar12[2],2), 0 < iVar4) {
          cVar3 = isIpodDevice(this,iVar4);
          if (cVar3 != '\0') {
            if ((long ********)local_4c0 == &local_4c0) goto LAB_0011f2c0;
            iVar15 = 0;
            goto LAB_0011f25c;
          }
          close(iVar4);
          ppppppplVar12 = (long *******)*ppppppplVar12;
          if ((long ********)ppppppplVar12 == &local_4c0) goto LAB_0011f24c;
        }
        ppppppplVar12 = (long *******)*ppppppplVar12;
      } while ((long ********)ppppppplVar12 != &local_4c0);
LAB_0011f24c:
      iVar15 = -1;
      if ((long ********)local_4c0 != &local_4c0) {
LAB_0011f25c:
        ppppppplVar14 = (long *******)*local_4c0;
        ppppppplVar7 = (long *******)local_4c0[2];
        ppppppplVar12 = local_4c0;
        if (ppppppplVar7 == local_4c0 + 4) goto LAB_0011f2a4;
        do {
          operator_delete(ppppppplVar7);
          operator_delete(ppppppplVar12);
          ppppppplVar12 = ppppppplVar14;
          while( true ) {
            if ((long ********)ppppppplVar12 == &local_4c0) {
              if (iVar15 != 0) {
                return 0xffffffff;
              }
              goto LAB_0011f2c0;
            }
            ppppppplVar14 = (long *******)*ppppppplVar12;
            ppppppplVar7 = (long *******)ppppppplVar12[2];
            if (ppppppplVar7 != ppppppplVar12 + 4) break;
LAB_0011f2a4:
            operator_delete(ppppppplVar12);
            ppppppplVar12 = ppppppplVar14;
          }
        } while( true );
      }
    }
  }
  return 0xffffffff;
}


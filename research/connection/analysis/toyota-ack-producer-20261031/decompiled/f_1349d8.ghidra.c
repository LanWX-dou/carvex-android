/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1349d8
 * original code SHA256: f582af355dc4064f1ed7d9beeb6fa2ada5b178a420e4a819f00fc188cf52e847
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* CIpodIap2::init(int) */

ulong __thiscall CIpodIap2::init(CIpodIap2 *this,int param_1)

{
  long *plVar1;
  byte bVar2;
  ushort uVar3;
  char cVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  long lVar8;
  ulong uVar9;
  long *plVar10;
  
  initMessages(this,param_1);
  uVar6 = syncLink(this,param_1);
  if (uVar6 != 0) {
    if (param_1 == 3) {
      return (ulong)uVar6;
    }
    CIpodConfig::getIdentification();
    return (ulong)uVar6;
  }
  if (param_1 - 1U < 2) {
    while (cVar4 = CIpodProtocol::isDeviceExist((CIpodProtocol *)this), cVar4 != '\0') {
      if (*(int *)(this + 0x14) == 1) {
        iVar7 = *(int *)(this + 0x18);
        if (iVar7 == 1) goto LAB_00134a6c;
      }
      else {
        if (*(int *)(this + 0x14) == 2) goto LAB_00134bb8;
        iVar7 = *(int *)(this + 0x18);
      }
      if (iVar7 == 2) goto LAB_00134be0;
      usleep(100000);
    }
  }
  else if (param_1 == 3) {
    while (iVar7 = CIpodVehicle::getbtSppConnStatus(), iVar7 == 3) {
      if (*(int *)(this + 0x14) == 1) {
        iVar7 = *(int *)(this + 0x18);
        if (iVar7 == 1) {
          CIpodLog::w("iAP2 Control Session AuthenticationSucceeded and IdentificationAccepted\n");
          return 0;
        }
      }
      else {
        if (*(int *)(this + 0x14) == 2) {
          CIpodLog::i("IpodIap2::init, authentication failed!\n");
          return 0xffffffff;
        }
        iVar7 = *(int *)(this + 0x18);
      }
      if (iVar7 == 2) {
        CIpodLog::i("IpodIap2::init, identification rejected!\n");
        return 0xffffffff;
      }
      usleep(100000);
    }
  }
  else if (param_1 == 4) {
    while (iVar7 = CIpodVehicle::getWiFiConnStatus(), iVar7 == 0) {
      if (*(int *)(this + 0x14) == 1) {
        iVar7 = *(int *)(this + 0x18);
        if (iVar7 == 1) goto LAB_00134a6c;
      }
      else {
        if (*(int *)(this + 0x14) == 2) {
LAB_00134bb8:
          CIpodLog::i("IpodIap2::init, authentication failed!\n");
          CIpodConfig::getIdentification();
          return 0xffffffff;
        }
        iVar7 = *(int *)(this + 0x18);
      }
      if (iVar7 == 2) {
LAB_00134be0:
        CIpodLog::i("IpodIap2::init, identification rejected!\n");
        CIpodConfig::getIdentification();
        return 0xffffffff;
      }
      usleep(100000);
    }
  }
  CIpodLog::i("IpodIap2::init, connect exit!\n");
  return 0xffffffff;
LAB_00134a6c:
  CIpodLog::w("iAP2 Control Session AuthenticationSucceeded and IdentificationAccepted\n");
  lVar8 = CIpodConfig::getIdentification();
  bVar2 = *(byte *)(lVar8 + 0xc0);
  if ((bVar2 >> 2 & 1) != 0) {
    bVar5 = (bool)CIpodVehicle::getBtStatus();
    uVar6 = bluetoothComponentInformation(this,bVar5);
    if ((uVar6 != 0) || (uVar6 = startBluetoothConnectionUpdates(this), uVar6 != 0))
    goto LAB_00134c3c;
    bVar2 = *(byte *)(lVar8 + 0xc0);
  }
  if ((char)bVar2 < '\0') {
    plVar1 = (long *)(lVar8 + 0x230);
    uVar6 = 0;
    plVar10 = *(long **)(lVar8 + 0x230);
    if (plVar10 != plVar1) {
      do {
        while ((int)plVar10[7] != 1) {
          plVar10 = (long *)*plVar10;
          if (plVar10 == plVar1) {
            if (uVar6 == 0) goto LAB_00134a90;
            goto LAB_00134d50;
          }
        }
        uVar3 = *(ushort *)(plVar10 + 2);
        *(ushort *)(this + 0x588) = uVar3;
        uVar6 = startHID(this,uVar3,1,0xff,&DAT_00146960,0x25);
        plVar10 = (long *)*plVar10;
      } while (plVar10 != plVar1);
      if (uVar6 != 0) {
LAB_00134d50:
        return (ulong)uVar6;
      }
    }
  }
LAB_00134a90:
  bVar2 = *(byte *)(lVar8 + 0xc1);
  if ((bVar2 >> 1 & 1) != 0) {
    uVar6 = initMedia();
    if (uVar6 != 0) goto LAB_00134c3c;
    bVar2 = *(byte *)(lVar8 + 0xc1);
  }
  if ((bVar2 >> 2 & 1) != 0) {
    uVar6 = startNowPlayingUpdates(this);
    if (uVar6 != 0) goto LAB_00134c3c;
    bVar2 = *(byte *)(lVar8 + 0xc1);
  }
  if ((bVar2 >> 3 & 1) != 0) {
    uVar6 = startPowerUpdates(this);
    if ((uVar6 != 0) || (uVar6 = powerSourceUpdate(this,1000), uVar6 != 0)) goto LAB_00134c3c;
    bVar2 = *(byte *)(lVar8 + 0xc1);
  }
  if ((((bVar2 >> 4 & 1) == 0) || (uVar6 = startUSBDeviceModeAudio(this), uVar6 == 0)) &&
     (((*(byte *)(lVar8 + 0xc0) >> 3 & 1) == 0 || (uVar6 = startCallStateUpdates(this), uVar6 == 0))
     )) {
    if (*(short *)(lVar8 + 0x368) == 0) {
      return 0;
    }
    uVar9 = startRouteGuidanceUpdate(this);
    return uVar9;
  }
LAB_00134c3c:
  return (ulong)uVar6;
}


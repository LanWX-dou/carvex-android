/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x137d60
 * original code SHA256: 9a547dcc775660dfa38a25ed14c606692eed41b14213f59a87956711beb85edb
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 FUN_00137d60(CIpodIap2 *param_1,void *param_2,ulong param_3)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined1 auStack_10000 [2];
  ushort local_fffe;
  char local_fffc;
  CIpodIap2 local_fffb;
  char local_fff9;
  uchar auStack_fff7 [4];
  char local_fff3;
  char local_fff2;
  
  memcpy(auStack_10000,param_2,param_3 & 0xffff);
  sVar1 = (local_fffe >> 8) + local_fffe * 0x100;
  if (local_fff9 == '\0') {
    if (sVar1 == 9) {
      if (local_fffc == '\x10') {
        CIpodLog::i("CIpodIap2::gaosheng -RST-- controlByte == %2x\n");
        uVar2 = CIpodProtocol::getHandle((CIpodProtocol *)param_1);
        CIpodEvent::sendEvent(0,uVar2,2);
      }
    }
    else {
      param_1[0x11] = local_fffb;
      CIpodIap2::sendAckPacket(param_1);
      if (local_fffc == -0x40) {
        CIpodIap2::syncLinkResult((uchar *)param_1);
      }
    }
  }
  else {
    param_1[0x11] = local_fffb;
    CIpodIap2::sendAckPacket(param_1);
    if (local_fff9 == '\n') {
      if (local_fff3 == -0x56) {
        if (local_fff2 == '\0') {
          uVar3 = CIpodIap2::requestAuthenticationCertificate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\x02') {
          uVar3 = CIpodIap2::requestAuthenticationChallengeResponse(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\x04') {
          uVar3 = CIpodIap2::authenticationFailed(param_1);
          return uVar3;
        }
        if (local_fff2 == '\x05') {
          uVar3 = CIpodIap2::authenticationSucceeded(param_1);
          return uVar3;
        }
        if (local_fff2 == '\x11') {
          uVar3 = CIpodIap2::deviceAuthenticationCertificate((uchar *)param_1);
          return uVar3;
        }
        if (local_fff2 == '\x13') {
          uVar3 = CIpodIap2::deviceAuthenticationResponse((uchar *)param_1);
          return uVar3;
        }
      }
      else if (local_fff3 == '\x1d') {
        if (local_fff2 == '\0') {
          uVar3 = CIpodIap2::startIdentification(param_1);
          return uVar3;
        }
        if (local_fff2 == '\x02') {
          uVar3 = CIpodIap2::identificationAccepted(param_1);
          return uVar3;
        }
        if (local_fff2 == '\x03') {
          uVar3 = CIpodIap2::identificationRejected(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == 'T') {
        if (local_fff2 == '\x03') {
          uVar3 = CIpodIap2::assistiveTouchInformation(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == 'N') {
        if (local_fff2 == '\x04') {
          uVar3 = CIpodIap2::bluetoothConnectionUpdate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\t') {
          uVar3 = CIpodIap2::deviceInformationUpdate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\n') {
          uVar3 = CIpodIap2::deviceLanguageUpdate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\v') {
          uVar3 = CIpodIap2::deviceTimeUpdate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\f') {
          uVar3 = CIpodIap2::deviceUUIDUpdate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\r') {
          uVar3 = CIpodIap2::wirelessCarPlayUpdate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\x0e') {
          uVar3 = CIpodIap2::deviceTransportIdentifierNotification(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == 'A') {
        if (local_fff2 == 'U') {
          uVar3 = CIpodIap2::callStateUpdate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == 'X') {
          uVar3 = CIpodIap2::communicationsUpdate((uchar *)param_1);
          return uVar3;
        }
        if (local_fff2 == 'q') {
          uVar3 = CIpodIap2::listUpdate((uchar *)param_1);
          return uVar3;
        }
      }
      else if (local_fff3 == 'C') {
        if (local_fff2 == '\0') {
          uVar3 = CIpodIap2::carPlayAvailability(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == -0x16) {
        if (local_fff2 == '\0') {
          uVar3 = CIpodIap2::startExternalAccessoryProtocol(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\x01') {
          uVar3 = CIpodIap2::stopExternalAccessoryProtocol(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == 'h') {
        if (local_fff2 == '\x01') {
          uVar3 = CIpodIap2::deviceHIDReport((uchar *)param_1);
          return uVar3;
        }
        if (local_fff2 == '\x06') {
          uVar3 = CIpodIap2::startNativeHID();
          return uVar3;
        }
      }
      else if (local_fff3 == -1) {
        if (local_fff2 == -6) {
          uVar3 = CIpodIap2::startLocationInformation(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == -4) {
          uVar3 = CIpodIap2::stopLocationInformation(param_1);
          return uVar3;
        }
      }
      else if (local_fff3 == 'L') {
        if (local_fff2 == '\x01') {
          uVar3 = CIpodIap2::mediaLibraryInformation(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\x04') {
          uVar3 = CIpodIap2::mediaLibraryUpdate(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == 'P') {
        if (local_fff2 == '\x01') {
          uVar3 = CIpodIap2::nowPlayingUpdate(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == '\v') {
        if (local_fff2 == '\0') {
          uVar3 = CIpodIap2::startBluetoothPairing(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\x03') {
          uVar3 = CIpodIap2::stopBluetoothPairing(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == '\0') {
        if (local_fff2 == -0x50) {
          uVar3 = CIpodIap2::startOOBBTPairing((uchar *)param_1);
          return uVar3;
        }
        if (local_fff2 == -0x4e) {
          uVar3 = CIpodIap2::oOBBTPairingLinkKeyInformation(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == -0x4c) {
          uVar3 = CIpodIap2::stopOOBBTPairing((uchar *)param_1);
          return uVar3;
        }
      }
      else if (local_fff3 == -0x52) {
        if (local_fff2 == '\x01') {
          uVar3 = CIpodIap2::powerUpdate(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == 'R') {
        if (local_fff2 == '\x01') {
          uVar3 = CIpodIap2::routeGuidanceUpdate(param_1,auStack_fff7);
          return uVar3;
        }
        if (local_fff2 == '\x02') {
          uVar3 = CIpodIap2::routeGuidanceManeuverInformation(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == -0x26) {
        if (local_fff2 == '\x01') {
          uVar3 = CIpodIap2::usbDeviceModeAudioInformatin(param_1,auStack_fff7);
          return uVar3;
        }
      }
      else if (local_fff3 == -0x5f) {
        if (local_fff2 == '\0') {
          uVar3 = CIpodIap2::startVehicleStatusUpdates((uchar *)param_1);
          return uVar3;
        }
        if (local_fff2 == '\x02') {
          uVar3 = CIpodIap2::stopVehicleStatusUpdates();
          return uVar3;
        }
      }
      else if (local_fff3 == 'V') {
        if (local_fff2 == '\f') {
          uVar3 = CIpodIap2::voiceOverUpdate((uchar *)param_1);
          return uVar3;
        }
        if (local_fff2 == '\x10') {
          uVar3 = CIpodIap2::voiceOverCursorUpdate((uchar *)param_1);
          return uVar3;
        }
      }
      else if (local_fff3 == 'W') {
        if (local_fff2 == '\x01') {
          uVar3 = CIpodIap2::wifiInformation((uchar *)param_1);
          return uVar3;
        }
        if (local_fff2 == '\x02') {
          uVar3 = CIpodIap2::requestAccessoryWiFiConfigurationInformation(param_1);
          return uVar3;
        }
      }
    }
    else {
      if (local_fff9 == '\v') {
        uVar3 = CIpodIap2::parseFileTransfer(param_1,auStack_fff7,sVar1 - 10);
        return uVar3;
      }
      if (local_fff9 == '\f') {
        uVar3 = CIpodIap2::parseEAData(param_1,auStack_fff7,sVar1 - 10);
        return uVar3;
      }
    }
  }
  return 0;
}


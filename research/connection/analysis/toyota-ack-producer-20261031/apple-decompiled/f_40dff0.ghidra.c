/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x40dff0
 * original code SHA256: 5e1e869d496bc500e047a967c01282f574164dbbe4babe2590d58050cb07534d
 * source SHA256: bb8a5b0d9fa57eafa8a9358341db3c9661d210ec778620e52e8d3b9fa4fd9f5e
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void AirPlaySessionControlDisableBluetooth(void)

{
  char cVar1;
  int local_4;
  
  if (0 < DAT_004258c0) {
    local_4 = DAT_004258c0;
    if (DAT_004258c0 == DAT_00425890) {
      DAT_00425898 = 0;
      DAT_00425890 = -1;
      iap2Disconnect(&local_4);
      if (0x32 < gLogCategory_iAP2AppStubErr) {
        return;
      }
      if ((gLogCategory_iAP2AppStubErr != -1) ||
         (cVar1 = _LogCategory_Initialize(&gLogCategory_iAP2AppStubErr,0x32), cVar1 != '\0')) {
        LogPrintF(&gLogCategory_iAP2AppStubErr,"TearDowniAP2",0x32,"finalize iAP2 Over Usb.\n");
      }
    }
    else {
      DAT_004258c0 = -1;
      DAT_004258c8 = 0;
      iap2Disconnect(&local_4);
      if (0x32 < gLogCategory_iAP2AppStubErr) {
        return;
      }
      if ((gLogCategory_iAP2AppStubErr != -1) ||
         (cVar1 = _LogCategory_Initialize(&gLogCategory_iAP2AppStubErr,0x32), cVar1 != '\0')) {
        LogPrintF(&gLogCategory_iAP2AppStubErr,"TearDowniAP2",0x32,"finalize iAP2 Over Bluetooth.\n"
                 );
      }
    }
    if ((gLogCategory_iAP2AppStubErr < 0x33) &&
       ((gLogCategory_iAP2AppStubErr != -1 ||
        (cVar1 = _LogCategory_Initialize(&gLogCategory_iAP2AppStubErr,0x32), cVar1 != '\0')))) {
      LogPrintF(&gLogCategory_iAP2AppStubErr,"TearDowniAP2",0x32,
                "iAP2 is still running Usb: %d, Bluetooth: %d, WiFi: %d.\n",DAT_00425898,
                DAT_004258c8,DAT_004258f8);
    }
  }
  return;
}


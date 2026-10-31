/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x40a5e0
 * original code SHA256: c62694ab1a5882ea3c33f263d219f89d870534ba2f79a23ba2bb815017be82ef
 * source SHA256: bb8a5b0d9fa57eafa8a9358341db3c9661d210ec778620e52e8d3b9fa4fd9f5e
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _CarPlayAvailability(undefined4 param_1,int *param_2)

{
  char cVar1;
  
  if (gLogCategory_iAP2AppStub < 0x33) {
    if ((gLogCategory_iAP2AppStub != -1) ||
       (cVar1 = _LogCategory_Initialize(&gLogCategory_iAP2AppStub,0x32), cVar1 != '\0')) {
      LogPrintF(&gLogCategory_iAP2AppStub,"_CarPlayAvailability",0x32,
                "CarPlayAvailability WireAvailable: %d, WirelessAvailable: %d.\n",*param_2,
                param_2[1]);
    }
    if (DAT_004258fc == 1) {
      if (0x32 < gLogCategory_iAP2AppStub) {
        return;
      }
      if ((gLogCategory_iAP2AppStub == -1) &&
         (cVar1 = _LogCategory_Initialize(&gLogCategory_iAP2AppStub,0x32), cVar1 == '\0')) {
        return;
      }
      LogPrintF(&gLogCategory_iAP2AppStub,"_CarPlayAvailability",0x32,
                "CarPlayAvailability CarPlay has already been started.\n");
      return;
    }
  }
  else if (DAT_004258fc == 1) {
    return;
  }
  if (giAP2TransportType == 1) {
    if ((gLogCategory_iAP2AppStubErr < 0x33) &&
       ((gLogCategory_iAP2AppStubErr != -1 ||
        (cVar1 = _LogCategory_Initialize(&gLogCategory_iAP2AppStubErr,0x32), cVar1 != '\0')))) {
      LogPrintF(&gLogCategory_iAP2AppStubErr,"_CarPlayAvailability",0x32,
                "CarPlayAvailability over USB connect directly.\n");
    }
    if (*param_2 == 1) {
      iap2CarPlayStartSession(param_1,0);
    }
  }
  if (giAP2TransportType != 3) {
    DAT_00425904 = 2;
    return;
  }
  DAT_00425904 = 2;
  handleCarPlayAvailable(param_2[1]);
  return;
}


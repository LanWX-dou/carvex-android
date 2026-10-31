/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x40d640
 * original code SHA256: 7c875703d60c3be1ca7b1416e356a68c2ed09b1804fbeffc1604161ae0b27425
 * source SHA256: bb8a5b0d9fa57eafa8a9358341db3c9661d210ec778620e52e8d3b9fa4fd9f5e
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _getBluetoothAddress(char *param_1)

{
  char cVar1;
  FILE *__stream;
  char *pcVar2;
  char acStack_40 [64];
  
  __stream = fopen("/data/bluetooth/deviceinfo.ini","r");
  if (__stream == (FILE *)0x0) {
    if ((gLogCategory_iAP2AppStubErr < 0x33) &&
       ((gLogCategory_iAP2AppStubErr != -1 ||
        (cVar1 = _LogCategory_Initialize(&gLogCategory_iAP2AppStubErr,0x32), cVar1 != '\0')))) {
      LogPrintF(&gLogCategory_iAP2AppStubErr,"_getBluetoothAddress",0x32,
                "open file deviceinfo.ini failed.\n");
    }
    return 0xffffffff;
  }
  do {
    pcVar2 = fgets(acStack_40,0x3f,__stream);
    if (pcVar2 == (char *)0x0) {
      fclose(__stream);
      return 0;
    }
    pcVar2 = strstr(acStack_40,"bt_addr");
  } while (pcVar2 == (char *)0x0);
  pcVar2 = strchr(pcVar2,0x3d);
  strcpy(param_1,pcVar2 + 1);
  param_1[0x11] = '\0';
  fclose(__stream);
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100102f58
 * original code SHA256: e5ebc888fa9c5feee72c51bd5f834365c6fe9b0ab95fac5199eac4535d514ce8
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


bool _iAP2PacketCheckRequestIdentify(long param_1)

{
  long lVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  
  pcVar4 = *(char **)(param_1 + 0x40);
  cVar3 = *pcVar4;
  pcVar2 = pcVar4;
  if (cVar3 == -1) {
    pcVar2 = pcVar4 + 1;
  }
  if (*pcVar2 == 'U') {
    lVar1 = 1;
    if (cVar3 == -1) {
      lVar1 = 2;
    }
    if (pcVar4[lVar1] == '\x02') {
      lVar1 = 2;
      if (cVar3 == -1) {
        lVar1 = 3;
      }
      if (pcVar4[lVar1] == '\0') {
        lVar1 = 3;
        if (cVar3 == -1) {
          lVar1 = 4;
        }
        if (pcVar4[lVar1] == '\0') {
          lVar1 = 4;
          if (cVar3 == -1) {
            lVar1 = 5;
          }
          return pcVar4[lVar1] == -2;
        }
      }
    }
  }
  return false;
}


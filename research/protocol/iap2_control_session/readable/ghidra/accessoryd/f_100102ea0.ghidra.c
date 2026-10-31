/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100102ea0
 * original code SHA256: b3ac1673302698604519711dfad9ca3b36f387aef85e7b88f2c5c218e8c895b3
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


bool _iAP2PacketCheckDetectNACK(long param_1)

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
    if (pcVar4[lVar1] == '\x04') {
      lVar1 = 2;
      if (cVar3 == -1) {
        lVar1 = 3;
      }
      if (pcVar4[lVar1] == '\0') {
        lVar1 = 3;
        if (cVar3 == -1) {
          lVar1 = 4;
        }
        if (pcVar4[lVar1] == '\x02') {
          lVar1 = 4;
          if (cVar3 == -1) {
            lVar1 = 5;
          }
          if (pcVar4[lVar1] == '\x04') {
            lVar1 = 5;
            if (cVar3 == -1) {
              lVar1 = 6;
            }
            if (pcVar4[lVar1] == -0x12) {
              lVar1 = 6;
              if (cVar3 == -1) {
                lVar1 = 7;
              }
              return pcVar4[lVar1] == '\b';
            }
          }
        }
      }
    }
  }
  return false;
}


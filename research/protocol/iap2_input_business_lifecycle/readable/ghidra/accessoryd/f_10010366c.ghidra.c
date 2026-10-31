/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x10010366c
 * original code SHA256: edcec07b4e98aecbb3543cd0a4fdad7da8b083c6c52a15c50578eca05ada3121
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



char * _iAP2PacketName(undefined8 *param_1)

{
  char *pcVar1;
  ushort uVar2;
  byte bVar3;
  uint uVar4;
  
  bVar3 = *(byte *)(param_1[8] + 4);
  if ((char)bVar3 < '\0') {
    pcVar1 = "SYN";
    if ((bVar3 & 0x40) != 0) {
      pcVar1 = "SYN-ACK";
    }
    return pcVar1;
  }
  if ((bVar3 >> 5 & 1) != 0) {
    return "EAK";
  }
  if ((bVar3 >> 4 & 1) != 0) {
    return "RST";
  }
  if ((bVar3 >> 3 & 1) == 0) {
    if (bVar3 < 0x40) {
      return "UNKNOWN";
    }
    uVar2 = *(ushort *)((long)param_1 + 0x36);
    uVar4 = _iAP2LinkCurPckHdrSize(*param_1);
    pcVar1 = "DATA";
    if (uVar2 <= uVar4) {
      pcVar1 = "ACK";
    }
    return pcVar1;
  }
  return "SUS";
}


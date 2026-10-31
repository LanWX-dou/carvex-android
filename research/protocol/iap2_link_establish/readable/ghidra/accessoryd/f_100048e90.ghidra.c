/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100048e90
 * original code SHA256: 64545fd67954cbb2e68624b66974b78ac4917ced76352c61b85af93fa06543e4
 * source SHA256: 2b0a2010e6d2605e07d87f05659c932e03de34476a76431196a9bb58da7dc4fe
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8
_mfi4Auth_protocol_handle_AuthenticationFailed(long param_1,long param_2,undefined8 param_3)

{
  byte bVar1;
  byte bVar2;
  
  if (param_1 == 0) {
    _mfi4Auth_protocol_handle_AuthenticationFailed_cold_3();
    return 0;
  }
  if (*(char *)(param_1 + 0x1e) == '\x01') {
    _mfi4Auth_protocol_handle_AuthenticationFailed_cold_2();
    return 0;
  }
  if (param_2 == 0) {
    _mfi4Auth_protocol_handle_AuthenticationFailed_cold_1();
    return 0;
  }
  bVar1 = *(byte *)(param_1 + 0x90);
  if ((bVar1 & 3) == 1) {
    bVar2 = 3;
  }
  else if ((bVar1 & 0xc) == 4) {
    bVar2 = 0xc;
  }
  else {
    if ((bVar1 & 0x30) != 0x10) goto LAB_100048ef4;
    bVar2 = 0x30;
  }
  bVar1 = bVar1 | bVar2;
  *(byte *)(param_1 + 0x90) = bVar1;
LAB_100048ef4:
  if ((((bVar1 ^ 0xff) & 0xf) == 0) || ((bVar1 & 0x30) == 0x30)) {
    _mfi4Auth_protocol_handle_AuthState(param_1,1);
  }
  else {
    _mfi4Auth_protocol_initMessage_RequestAuthSetup(param_1,param_3);
  }
  return 0;
}


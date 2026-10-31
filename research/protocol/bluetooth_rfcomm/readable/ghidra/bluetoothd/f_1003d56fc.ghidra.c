/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1003d56fc
 * original code SHA256: c98e909e1aff89006691c1f23b35c163c8c5a542ebf25bbef934f3a334195302
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


char * FUN_1003d56fc(uint *param_1)

{
  char *pcVar1;
  
  if (param_1 == (uint *)0x0) {
    return "invalid";
  }
  if (*(long *)param_1 == 0x10000000000001 && *(long *)(param_1 + 2) == 0x20000ee02000080) {
    return "SyncMLServer";
  }
  if (*(long *)param_1 == 0x10000000000002 && *(long *)(param_1 + 2) == 0x20000ee02000080) {
    return "SyncMLClient";
  }
  if (*(long *)param_1 == -0x135352200000000 && *(long *)(param_1 + 2) == -0x135352101353522) {
    return "D2D";
  }
  if (*(long *)param_1 == -0x2105352200000000 && *(long *)(param_1 + 2) == -0x135352150213522) {
    return "WiapGateWay";
  }
  if (*(long *)param_1 == -0x2105352200000000 && *(long *)(param_1 + 2) == -0x35352150213522) {
    return "WiapSink";
  }
  if (*(long *)param_1 == 0x5f41191dc327ed08 && *(long *)(param_1 + 2) == 0x770a6a10a222f286) {
    return "WiapGateWay_v2";
  }
  if (*(long *)param_1 == 0x5f41191dc327ed08 && *(long *)(param_1 + 2) == 0x780a6a10a222f286) {
    return "WiapSink_v2";
  }
  if (*(long *)param_1 == 0x14dad0b74ec2172 && *(long *)(param_1 + 2) == 0x2a72e02b7b99778f) {
    return "AapServer";
  }
  if (*(long *)param_1 == -0x21b60bf8b48390b5 && *(long *)(param_1 + 2) == 0x298f720443abb9b0) {
    return "AapService";
  }
  if (*(long *)param_1 == 0x364b2e573619f31f && *(long *)(param_1 + 2) == -0xb59e564bf4d405e) {
    return "AapClient";
  }
  if (*(long *)param_1 == 0x2a43b1001e0de104 && *(long *)(param_1 + 2) == 0x41f93a98badd64b7) {
    return "Magnet";
  }
  if (*(long *)param_1 == -0x5dbfbe32b7bc7714 && *(long *)(param_1 + 2) == -0x2ce040afa2a8d869) {
    return "Carplay";
  }
  if (*(long *)param_1 == 0x1c454de166248d2d && *(long *)(param_1 + 2) == 0x1a29eaab0173bc88) {
    return "CarplayGateway";
  }
  if (*(long *)(param_1 + 1) != -0x7fffff7ffff00000 || param_1[3] != 0xfb349b5f) {
    return "unknown";
  }
  pcVar1 = (char *)(ulong)*param_1;
  FUN_1003d59f8(pcVar1);
  return pcVar1;
}


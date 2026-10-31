/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda25cc
 * original code SHA256: 41fce7b287127e9fa4f8f012e4f93b2a001812a4120ebc758c13d423f422359c
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



bool _httppackage_matchIncomingMessageMethodAndURL
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,char *param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = func_0x0002500efc20();
  iVar2 = func_0x0002500efc10(param_1,param_2,param_3);
  iVar3 = func_0x0002500efc20(param_4,param_5,param_6);
  iVar4 = func_0x0002500efc10(param_4,param_5,param_6);
  if (iVar1 == 0) {
    if (iVar3 == 0 || iVar4 == 0) {
      return true;
    }
    if (iVar2 != 0) {
      return false;
    }
  }
  else if (iVar2 != 0) {
    return false;
  }
  return *param_6 == '\0';
}


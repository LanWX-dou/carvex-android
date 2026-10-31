/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda858c
 * original code SHA256: e081a1383be8f4fb48d645c6f1de342222a812d507f31520bc61356134cb0134
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



void _session_CreateStreamWithID
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 uStack_48;
  
  lVar2 = func_0x0002500e5a60();
  local_60 = param_1;
  local_58 = param_2;
  local_50 = param_3;
  uStack_48 = param_4;
  lVar3 = _APTransportStreamIDGetStreamCategory(param_2);
  if (lVar3 != 0) {
    uVar4 = _APTransportStreamIDInsertStreamCategory(param_2,3);
    local_58 = uVar4;
    iVar1 = _APCarPlayHelperGetCMBaseObject();
    if (iVar1 == 0) {
      *(int *)(lVar2 + 0xb4) = *(int *)(lVar2 + 0xb4) + 1;
      local_58 = _APTransportStreamIDInsertIdentifier(uVar4);
    }
  }
  func_0x0002500edf10(*(undefined8 *)(lVar2 + 0x18),_session_createStreamWithIDInternal,&local_60);
  return;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fdc8688
 * original code SHA256: 121e89cfa673203e547c1833ba575a7b0be0eb25a05180a09bf71a1a3bc3029a
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



undefined8 _httpconnection_ConfigureEncryption(undefined8 param_1,long param_2,long param_3)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 local_48;
  long lStack_40;
  long local_38;
  
  lVar1 = func_0x0002500e5a60();
  local_48 = param_1;
  lStack_40 = param_2;
  local_38 = param_3;
  if (param_2 == 0) {
    uVar2 = 0xfffee57e;
    _httpconnection_ConfigureEncryption_cold_2();
  }
  else if (param_3 == 0) {
    uVar2 = 0xfffee57e;
    _httpconnection_ConfigureEncryption_cold_1();
  }
  else {
    func_0x0002500903e0(param_1);
    func_0x0002500903e0(param_2);
    func_0x0002500903e0(param_3);
    func_0x0002500edec0(*(undefined8 *)(lVar1 + 8),_httpconnection_deferConfigureEncryption,
                        &local_48,0x18);
    uVar2 = 0;
  }
  return uVar2;
}


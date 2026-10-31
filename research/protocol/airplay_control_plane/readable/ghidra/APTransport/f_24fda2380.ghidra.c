/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda2380
 * original code SHA256: 34bc13658a23ba75ce60d2b565d9f12286288f19ca140b5eb274af414ae0119d
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x00024fda2454) */
/* WARNING: Removing unreachable block (ram,0x00024fda23ec) */

undefined8 _httpconnection_SendPackage(undefined8 param_1,long param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  code *pcVar5;
  undefined8 *puVar6;
  undefined8 local_40;
  long lStack_38;
  
  lVar2 = func_0x0002500e5a60();
  lVar3 = func_0x0002500b5820(param_2);
  puVar6 = (undefined8 *)(*(long *)(lVar3 + 0x10) + 0x60);
  pcVar5 = (code *)*puVar6;
  if (((pcVar5 == (code *)0x0) || (pcVar5 == (code *)0x0)) ||
     (iVar1 = (*pcVar5)((ulong)puVar6 & 0xffffffffffff | 0xcf23000000000000,param_2),
     iVar1 != 0x72706c79)) {
    local_40 = param_1;
    lStack_38 = param_2;
    func_0x0002500903e0(param_1);
    func_0x0002500903e0(param_2);
    func_0x0002500edec0(*(undefined8 *)(lVar2 + 8),_httpconnection_sendPackageInternal,&local_40,
                        0x10);
  }
  else {
    lVar3 = func_0x0002500b5820(param_2);
    puVar6 = (undefined8 *)(*(long *)(lVar3 + 0x10) + 0xa8);
    pcVar5 = (code *)*puVar6;
    if ((pcVar5 == (code *)0x0) || (pcVar5 == (code *)0x0)) {
      iVar1 = 0;
    }
    else {
      iVar1 = (*pcVar5)((ulong)puVar6 & 0xffffffffffff | 0xe460000000000000,param_2);
    }
    func_0x0002500eae70(*(undefined8 *)(lVar2 + 0x110));
    lVar3 = *(long *)(lVar2 + 0x118);
    if ((lVar3 == 0) || (*(int *)(lVar2 + 0x128) != iVar1)) {
      if ((_gLogCategory_APTransportConnectionHTTP < 0x33) &&
         ((_gLogCategory_APTransportConnectionHTTP != -1 ||
          (iVar1 = func_0x0002500a8720(&_gLogCategory_APTransportConnectionHTTP,0x2000032),
          iVar1 != 0)))) {
        func_0x0002500ef250(&_gLogCategory_APTransportConnectionHTTP,
                            "OSStatus httpconnection_SendPackage(APTransportConnectionRef, APTransportPackageRef)"
                            ,0x2000032,"[%{ptr}] Ignoring late response for event 0x%04X");
      }
    }
    else {
      if (param_2 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = func_0x0002500903e0(param_2);
        lVar3 = *(long *)(lVar2 + 0x118);
      }
      *(undefined8 *)(lVar2 + 0x120) = uVar4;
      func_0x000250092240(lVar3);
    }
    func_0x0002500eae80(*(undefined8 *)(lVar2 + 0x110));
  }
  return 0;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x24fda1e78
 * original code SHA256: 192ea847dfdeb966c160445028f2f7d8c37035e4c64fe1ab3cbe4a53157538f3
 * source SHA256: e277719a95de258399d7843f9d9822e6178e50fba466658193ba11ebc6844a8d
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



int _httppackage_createWithHTTPMessage(undefined8 param_1,long param_2,long *param_3)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  ulong uVar5;
  undefined4 uVar6;
  long lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long local_50;
  int local_44;
  
  local_50 = 0;
  uVar2 = _APTransportPackageGetClassID();
  local_44 = func_0x0002500e5ab0(param_1,&_kAPTransportPackageHTTPVTable,uVar2,&local_50);
  if (local_44 != 0) {
    _httppackage_createWithHTTPMessage_cold_1();
LAB_24fda218c:
    if (local_50 != 0) {
      func_0x0002500903d0();
    }
    return local_44;
  }
  lVar3 = func_0x0002500e5a60(local_50);
  if (param_2 == 0) {
    local_44 = func_0x0002500ef130(lVar3 + 0x18);
    if (local_44 != 0) {
      _httppackage_createWithHTTPMessage_cold_3();
      goto LAB_24fda218c;
    }
    lVar4 = *(long *)(lVar3 + 0x18);
    local_44 = 0;
  }
  else {
    lVar4 = func_0x0002500ef120(param_2,&local_44);
    *(long *)(lVar3 + 0x18) = lVar4;
    if (local_44 != 0) {
      _httppackage_createWithHTTPMessage_cold_2();
      goto LAB_24fda218c;
    }
    *(undefined8 *)(lVar4 + 0x25c8) = *(undefined8 *)(param_2 + 0x25c8);
    uVar2 = *(undefined8 *)(param_2 + 0x25d0);
    *(undefined8 *)(lVar4 + 0x25d8) = *(undefined8 *)(param_2 + 0x25d8);
    *(undefined8 *)(lVar4 + 0x25d0) = uVar2;
    *(undefined8 *)(lVar4 + 0x25e0) = *(undefined8 *)(param_2 + 0x25e0);
  }
  *(undefined4 *)(lVar3 + 0x28) = 0x6173796e;
  lVar7 = *(long *)(lVar4 + 0x2038);
  if (lVar7 == 0) {
    if (*(long *)(lVar4 + 0x2050) != 0) {
      if (0x3c < _gLogCategory_APTransportPackageHTTP) goto LAB_24fda20c4;
      if ((_gLogCategory_APTransportPackageHTTP != -1) ||
         (iVar1 = func_0x0002500a8720(&_gLogCategory_APTransportPackageHTTP,0x200003c), iVar1 != 0))
      {
        func_0x0002500ef250(&_gLogCategory_APTransportPackageHTTP,
                            "OSStatus httppackage_createWithHTTPMessage(CFAllocatorRef, HTTPMessageRef, APTransportPackageRef *)"
                            ,0x200003c,"### Unrecognized incoming message URL: \'%.*s\' %s\n");
      }
    }
  }
  else {
    uVar2 = *(undefined8 *)(lVar4 + 0x2030);
    uVar8 = *(undefined8 *)(lVar4 + 0x2098);
    uVar9 = *(undefined8 *)(lVar4 + 0x20a0);
    uVar5 = _httppackage_matchIncomingMessageMethodAndURL(uVar2,lVar7,"SETUP",uVar8,uVar9,"");
    if ((uVar5 & 1) == 0) {
      uVar5 = _httppackage_matchIncomingMessageMethodAndURL(uVar2,lVar7,"TEARDOWN",uVar8,uVar9,"");
      if ((uVar5 & 1) == 0) {
        uVar5 = _httppackage_matchIncomingMessageMethodAndURL
                          (uVar2,lVar7,"POST",uVar8,uVar9,"/event");
        if ((uVar5 & 1) == 0) {
          uVar5 = _httppackage_matchIncomingMessageMethodAndURL
                            (uVar2,lVar7,"POST",uVar8,uVar9,"/command");
          if ((uVar5 & 1) == 0) {
            func_0x0002500ee220(0,"httppackage_getIncomingMessageType",0x1e9,0);
            if ((_gLogCategory_APTransportPackageHTTP < 0x33) &&
               ((_gLogCategory_APTransportPackageHTTP != -1 ||
                (iVar1 = func_0x0002500a8720(&_gLogCategory_APTransportPackageHTTP,0x2000032),
                iVar1 != 0)))) {
              func_0x0002500ef250(&_gLogCategory_APTransportPackageHTTP,
                                  "OSStatus httppackage_getIncomingMessageType(const char *, size_t, const char *, size_t, OSType *)"
                                  ,0x2000032,
                                  "Message type not found for method/URL pair %.*s %.*s.\n");
            }
            local_44 = -0x4103;
            func_0x0002500ee220(0xffffbefd,"httppackage_createWithHTTPMessage",0x112,0);
            goto LAB_24fda218c;
          }
          uVar6 = 0x636d6e64;
        }
        else {
          uVar6 = 0x65766e74;
        }
      }
      else {
        uVar6 = 0x7464776e;
      }
    }
    else {
      uVar6 = 0x73747570;
    }
    *(undefined4 *)(lVar3 + 8) = uVar6;
    local_44 = 0;
  }
  if ((_gLogCategory_APTransportPackageHTTP < 0x1f) &&
     ((_gLogCategory_APTransportPackageHTTP != -1 ||
      (iVar1 = func_0x0002500a8720(&_gLogCategory_APTransportPackageHTTP,0x200001e), iVar1 != 0))))
  {
    _httppackage_createWithHTTPMessage_cold_4(&local_50);
  }
LAB_24fda20c4:
  *param_3 = local_50;
  return local_44;
}


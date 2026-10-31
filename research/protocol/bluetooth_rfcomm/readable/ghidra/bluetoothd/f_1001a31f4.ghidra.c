/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1001a31f4
 * original code SHA256: 7d6191e0a5a7b8df7e0c756a044834ec412d0383dff245449272ee208c5006d2
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void phone_fn_1001a31f4(ulong param_1,undefined8 param_2,int param_3)

{
  int iVar1;
  ulong uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  undefined4 uStack_40;
  undefined8 uStack_3c;
  
  uVar5 = param_1;
  FUN_100374448();
  if (param_3 == 6) {
    if (lRam0000000100cadd58 == 0) {
      iVar1 = 2;
      FUN_10000d938(2,0x43);
      if (iVar1 != 0) {
        FUN_10000d120("Local device does not support BR/EDR SMP");
        uVar3 = 0x43;
        FUN_10000e9d4();
        uVar4 = uVar3;
        _os_log_type_enabled();
        if ((int)uVar4 != 0) {
          FUN_100105b50(uVar3);
        }
      }
    }
    else if ((bRam0000000100c2a9d0 & 1) == 0) {
      iVar1 = 2;
      FUN_10000d938(2,0x43);
      if (iVar1 != 0) {
        FUN_10000d120("Controller does not support Secured Connections");
        uVar3 = 0x43;
        FUN_10000e9d4();
        uVar4 = uVar3;
        _os_log_type_enabled();
        if ((int)uVar4 != 0) {
          FUN_100105b50(uVar3);
        }
      }
    }
    else {
      uVar2 = param_1;
      FUN_1000c0ddc();
      if ((uVar2 & 1) == 0) {
        iVar1 = 2;
        FUN_10000d938(2,0x43);
        if (iVar1 == 0) {
          return;
        }
        FUN_10000d120("Connection is invalid");
        uVar3 = 0x43;
        FUN_10000e9d4();
        uVar4 = uVar3;
        _os_log_type_enabled();
        if ((int)uVar4 == 0) {
          return;
        }
        FUN_100105b50(uVar3);
        return;
      }
      if (*(char *)(param_1 + 0x99) == '\x02') {
        *(undefined1 *)(param_1 + 0x130) = 1;
        if (*(char *)(param_1 + 0x90) == '\0') {
          iVar1 = 2;
          FUN_10000d938(2,0x43);
          if (iVar1 != 0) {
            FUN_10000d120("You cannot send this command when peripheral.");
            uVar3 = 0x43;
            FUN_10000e9d4();
            uVar4 = uVar3;
            _os_log_type_enabled();
            if ((int)uVar4 != 0) {
              FUN_100105b50(uVar3);
            }
          }
        }
        else {
          if (uVar5 != 0) {
            iVar1 = 2;
            FUN_10000d938(2,0x43);
            if (iVar1 != 0) {
              FUN_10000d120("Classic SMP pairing is already in progress");
              uVar3 = 0x43;
              FUN_10000e9d4();
              uVar4 = uVar3;
              _os_log_type_enabled();
              if ((int)uVar4 != 0) {
                FUN_100105b50(uVar3);
              }
            }
            uVar4 = 0xd;
            goto LAB_1001a33e4;
          }
          uVar5 = param_1;
          FUN_100374774();
          if (uVar5 == 0) {
            iVar1 = 2;
            FUN_10000d938(2,0x43);
            if (iVar1 != 0) {
              FUN_10000d120("Could not allocate new device...");
              uVar3 = 0x43;
              FUN_10000e9d4();
              uVar4 = uVar3;
              _os_log_type_enabled();
              if ((int)uVar4 != 0) {
                FUN_100105b50(uVar3);
              }
            }
            uVar5 = 0;
          }
          else {
            FUN_100374824();
            if ((7 < *(byte *)(uVar5 + 0x52)) || (7 < *(byte *)(uVar5 + 0x53))) {
              iVar1 = 2;
              FUN_10000d938(2,0x43);
              if (iVar1 != 0) {
                FUN_10000d120("Invalid key distribution parameters initiator:0x%x, responder:0xx");
                uVar3 = 0x43;
                FUN_10000e9d4();
                uVar4 = uVar3;
                _os_log_type_enabled();
                if ((int)uVar4 != 0) {
                  FUN_100105b50(uVar3);
                }
              }
              goto LAB_1001a33e0;
            }
            *(byte *)(uVar5 + 0x4a) = *(byte *)(uVar5 + 0x52) & 3;
            *(undefined1 *)(uVar5 + 0x4b) = 0;
            *(byte *)(uVar5 + 0x4c) = *(byte *)(uVar5 + 0x53) & 3;
            *(undefined1 *)(uVar5 + 0x4d) = 0;
            FUN_100374994(uVar5,0x11);
            *(undefined1 *)(uVar5 + 0x48) = 0;
            if (((bRam0000000100c2a9d1 & 1) == 0) && ((*(byte *)(uVar5 + 0x50) >> 5 & 1) != 0)) {
              *(undefined1 *)(uVar5 + 0x48) = 0x20;
              *(undefined1 *)(uVar5 + 0x251) = 1;
            }
            if ((cRam0000000100c2a9d2 == '\x01') && ((*(byte *)(uVar5 + 0x251) & 1) == 0)) {
              iVar1 = 0;
              FUN_10000d938(0,0x43);
              if (iVar1 != 0) {
                FUN_10000d120("Force replying with CT2=1");
                uVar3 = 0x43;
                FUN_10000e9d4();
                uVar4 = uVar3;
                _os_log_type_enabled();
                if ((int)uVar4 != 0) {
                  FUN_10000ea80();
                  uStack_40 = (undefined4)_UNK_100930b20;
                  uStack_3c = uVar4;
                  __os_log_impl(0x100000000,uVar3,0," %{public}s",&uStack_40,0xc);
                }
              }
              *(byte *)(uVar5 + 0x48) = *(byte *)(uVar5 + 0x48) | 0x20;
              *(undefined1 *)(uVar5 + 0x251) = 1;
            }
            iVar1 = 0;
            FUN_10000d938(0,0x43);
            if (iVar1 != 0) {
              FUN_10000d120(
                           "authReq=%x isSecuredConnectionControllerSupported=%d expectedKeys=%x requestedKeys=%x"
                           );
              uVar3 = 0x43;
              FUN_10000e9d4();
              uVar4 = uVar3;
              _os_log_type_enabled();
              if ((int)uVar4 != 0) {
                FUN_10000ea80();
                uStack_40 = (undefined4)_UNK_100930b20;
                uStack_3c = uVar4;
                __os_log_impl(0x100000000,uVar3,0," %{public}s",&uStack_40,0xc);
              }
            }
            uVar2 = param_1;
            FUN_100326954(param_1,*(undefined1 *)(uVar5 + 0x48),*(undefined1 *)(uVar5 + 0x4a),
                          *(undefined1 *)(uVar5 + 0x4c));
            if ((int)uVar2 == 0) {
              if ((*(byte *)(uVar5 + 0x4c) >> 1 & 1) != 0) {
                FUN_100326b54(uVar5);
                FUN_100326cd0(uVar5);
                *(byte *)(uVar5 + 0x4d) = *(byte *)(uVar5 + 0x4d) | 2;
                FUN_100374994(uVar5,0x43);
              }
              if ((*(byte *)(uVar5 + 0x4a) >> 1 & 1) != 0) {
                return;
              }
              FUN_100374994(uVar5,0x41);
              FUN_1001992d0(uVar5,0,1);
              return;
            }
            iVar1 = 2;
            FUN_10000d938(2,0x43);
            if (iVar1 != 0) {
              FUN_10000d120("smpSendPairingResponse failed with error %!");
              uVar3 = 0x43;
              FUN_10000e9d4();
              uVar4 = uVar3;
              _os_log_type_enabled();
              if ((int)uVar4 != 0) {
                FUN_100105b50(uVar3);
              }
            }
          }
        }
        goto LAB_1001a32e4;
      }
      iVar1 = 2;
      FUN_10000d938(2,0x43);
      if (iVar1 != 0) {
        FUN_10000d120("Rejected SMP/BR-EDR pairing request: link not AES-CCM/P-256 encrypted");
        uVar3 = 0x43;
        FUN_10000e9d4();
        uVar4 = uVar3;
        _os_log_type_enabled();
        if ((int)uVar4 != 0) {
          FUN_100105b50(uVar3);
        }
      }
    }
LAB_1001a33e0:
    uVar4 = 0xe;
  }
  else {
    iVar1 = 2;
    FUN_10000d938(2,0x43);
    if (iVar1 != 0) {
      FUN_10000d120("Invalid Pairing Request size %d.");
      uVar3 = 0x43;
      FUN_10000e9d4();
      uVar4 = uVar3;
      _os_log_type_enabled();
      if ((int)uVar4 != 0) {
        FUN_100105b50(uVar3);
      }
    }
LAB_1001a32e4:
    uVar4 = 8;
  }
LAB_1001a33e4:
  FUN_100326dc8(param_1,uVar4,uVar5);
  return;
}


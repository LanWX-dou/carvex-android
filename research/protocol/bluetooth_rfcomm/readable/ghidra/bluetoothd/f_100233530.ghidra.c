/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100233530
 * original code SHA256: 0db66f95d346b8124bc822aefffa7292e32c5cc160800f7ff7f80816da632acc
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Function: _objc_retain_x2 replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_claimAutoreleasedReturnValue replaced with injection: _objc_retain_fixup
    */
/* WARNING: Function: _objc_autorelease replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release_x23 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x21 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x20 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x19 replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_release_x26 replaced with injection: _objc_release_fixup */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Function Stack Size: 0x20 bytes */

bool CBStackControllerBTStack::pairingContinueWithPairingInfo_error_
               (ID param_1,SEL param_2,ID param_3,ID *param_4)

{
  uint uVar1;
  ID IVar2;
  long lVar3;
  ID IVar4;
  ulong uVar5;
  ID IVar6;
  bool bVar7;
  undefined1 auStack_79 [17];
  long lStack_68;
  
  lStack_68 = *(long *)PTR____stack_chk_guard_100bfc980;
  IVar2 = objc_stub::FUN_1009151c0(param_1);
  if (IVar2 == 0) {
    if (param_4 == (ID *)0x0) {
      bVar7 = 0;
    }
    else {
      IVar2 = 0xffffe5cf;
      _CBErrorF(0xffffe5cf,"No pairing device");
      bVar7 = 0;
      *param_4 = IVar2;
    }
    goto LAB_1002336f8;
  }
  IVar2 = objc_stub::FUN_100918180(IVar2);
  IVar2 = objc_stub::FUN_10090d480(param_1,IVar2,param_4);
  bVar7 = 0;
  if (IVar2 == 0) goto LAB_1002336f8;
  if (*(long *)(param_1 + 0x40) == 0) {
    if (param_4 == (ID *)0x0) {
LAB_1002337b4:
      bVar7 = 0;
      goto LAB_1002336f8;
    }
    IVar2 = 0xffffe5a7;
    _CBErrorF(0xffffe5a7,"No pairing agent handle to continue");
  }
  else {
    if (lRam0000000100c1b9b0 != -1) {
      thunk_FUN_1000885ec();
    }
    lVar3 = lRam0000000100c1b9a8;
    FUN_1007807e8(lRam0000000100c1b9a8,*(undefined8 *)(param_1 + 0x40));
    if (lVar3 != 0) {
      IVar4 = objc_stub::FUN_1009166a0(param_1);
      if (IVar4 == 0) {
        IVar6 = objc_stub::FUN_10091bb20(param_1);
        _objc_retainAutorelease();
        IVar6 = objc_stub::FUN_10090cba0(IVar6);
        if (IVar6 == 0) goto LAB_1002335f0;
        FUN_10078ac1c(auStack_79,IVar6);
        FUN_10077dca8(lVar3,IVar2,auStack_79);
        FUN_100043ed4(auStack_79);
        bVar7 = 1;
        if (((int)lVar3 == 0) || (uVar1 = (int)lVar3 + 310000, uVar5 = (ulong)uVar1, uVar1 == 0))
        goto LAB_1002336f8;
        if (param_4 != (ID *)0x0) {
          _CBErrorF(uVar5,"Set pairing pincode failed");
          goto LAB_1002337d8;
        }
      }
      else {
LAB_1002335f0:
        IVar4 = objc_stub::FUN_100913be0(IVar4);
        if (IVar4 == 0xffffffffffffe5bd) {
          FUN_10077dc50();
          bVar7 = 1;
          if (((int)lVar3 == 0) || (uVar1 = (int)lVar3 + 310000, uVar5 = (ulong)uVar1, uVar1 == 0))
          goto LAB_1002336f8;
          if (param_4 != (ID *)0x0) {
            _CBErrorF(uVar5,"Cancel pairing failed");
LAB_1002337d8:
            bVar7 = 0;
            *param_4 = uVar5;
            goto LAB_1002336f8;
          }
        }
        else {
          IVar4 = objc_stub::FUN_1009166a0(param_1);
          FUN_10077ded8(lVar3,IVar2,IVar4 != 0);
          bVar7 = 1;
          if (((int)lVar3 == 0) || (uVar1 = (int)lVar3 + 310000, uVar5 = (ulong)uVar1, uVar1 == 0))
          goto LAB_1002336f8;
          if (param_4 != (ID *)0x0) {
            _CBErrorF(uVar5,"Accept/Reject pairing failed");
            goto LAB_1002337d8;
          }
        }
      }
      bVar7 = 0;
      goto LAB_1002336f8;
    }
    if (param_4 == (ID *)0x0) goto LAB_1002337b4;
    IVar2 = 0xffffe596;
    _CBErrorF(0xffffe596,"No pairing agent to continue");
  }
  bVar7 = 0;
  *param_4 = IVar2;
LAB_1002336f8:
  if (*(long *)PTR____stack_chk_guard_100bfc980 != lStack_68) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(0);
  }
  return bVar7;
}


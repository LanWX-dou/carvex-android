/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1004f2730
 * original code SHA256: 19f24f7d448655c0ece4ea06f2e707a718fbda02d7c41614d20c36f5489364f7
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined8 phone_fn_1004f2730(undefined8 param_1,undefined8 param_2,long *param_3)

{
  int iVar1;
  long *plVar2;
  bool bVar3;
  long *plVar4;
  long *plVar5;
  undefined8 auStack_78 [2];
  char cStack_61;
  
  plVar4 = (long *)*param_3;
  do {
    if (plVar4 == param_3 + 1) {
      return 0;
    }
    iVar1 = *(int *)((long)plVar4 + 0x1c);
    if (iVar1 < 0x200) {
      if (iVar1 < 0x10) {
        if (iVar1 == 1) {
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServiceHandsfree",auStack_78);
        }
        else if (iVar1 == 2) {
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServicePhoneBook",auStack_78);
        }
        else {
          if (iVar1 != 8) goto LAB_1004f2a90;
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServiceRemote",auStack_78);
        }
      }
      else if (iVar1 < 0x80) {
        if (iVar1 == 0x10) {
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServiceA2DP",auStack_78);
        }
        else {
          if (iVar1 != 0x20) goto LAB_1004f2a90;
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServiceHID",auStack_78);
        }
      }
      else if (iVar1 == 0x80) {
        FUN_1004f2b40(auStack_78);
        FUN_1004f1c3c(param_1,param_2,"ServiceWiAP",auStack_78);
      }
      else {
        if (iVar1 != 0x100) goto LAB_1004f2a90;
        FUN_1004f2b40(auStack_78);
        FUN_1004f1c3c(param_1,param_2,"ServiceNetSharing",auStack_78);
      }
LAB_1004f2a80:
      if (cStack_61 < '\0') {
        __ZdlPv(auStack_78[0]);
      }
    }
    else {
      if (0x1ffff < iVar1) {
        if (iVar1 < 0x80000) {
          if (iVar1 == 0x20000) {
            FUN_1004f2b40(auStack_78);
            FUN_1004f1c3c(param_1,param_2,"ServiceWiAPSink",auStack_78);
          }
          else {
            if (iVar1 != 0x40000) goto LAB_1004f2a90;
            FUN_1004f2b40(auStack_78);
            FUN_1004f1c3c(param_1,param_2,"ServiceWirelessCarPlay",auStack_78);
          }
        }
        else if (iVar1 == 0x80000) {
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServiceAACP",auStack_78);
        }
        else {
          if (iVar1 != 0x100000) goto LAB_1004f2a90;
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServiceGATT",auStack_78);
        }
        goto LAB_1004f2a80;
      }
      if (0xfff < iVar1) {
        if (iVar1 == 0x1000) {
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServiceNetSharingUser",auStack_78);
        }
        else {
          if (iVar1 != 0x2000) goto LAB_1004f2a90;
          FUN_1004f2b40(auStack_78);
          FUN_1004f1c3c(param_1,param_2,"ServiceBraille",auStack_78);
        }
        goto LAB_1004f2a80;
      }
      if (iVar1 == 0x200) {
        FUN_1004f2b40(auStack_78);
        FUN_1004f1c3c(param_1,param_2,"ServiceMAP",auStack_78);
        goto LAB_1004f2a80;
      }
      if (iVar1 == 0x800) {
        FUN_1004f2b40(auStack_78);
        FUN_1004f1c3c(param_1,param_2,"ServiceGaming",auStack_78);
        goto LAB_1004f2a80;
      }
    }
LAB_1004f2a90:
    plVar2 = (long *)plVar4[1];
    plVar5 = plVar4;
    if ((long *)plVar4[1] == (long *)0x0) {
      do {
        plVar4 = (long *)plVar5[2];
        bVar3 = plVar5 != (long *)*plVar4;
        plVar5 = plVar4;
      } while (bVar3);
    }
    else {
      do {
        plVar4 = plVar2;
        plVar2 = (long *)*plVar4;
      } while ((long *)*plVar4 != (long *)0x0);
    }
  } while( true );
}


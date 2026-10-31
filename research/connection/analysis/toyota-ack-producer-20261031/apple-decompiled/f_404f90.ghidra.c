/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x404f90
 * original code SHA256: 9b8fd9404e1a6dfc8871ba90d2e40ac72b92f2f488dd480e6722131804beef72
 * source SHA256: bb8a5b0d9fa57eafa8a9358341db3c9661d210ec778620e52e8d3b9fa4fd9f5e
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool main(int param_1,long param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  long lVar6;
  int local_d4;
  undefined1 auStack_d0 [8];
  char local_c8 [8];
  code *local_c0;
  code *pcStack_b8;
  code *local_b0;
  code *pcStack_a8;
  code *local_a0;
  undefined8 uStack_98;
  code *local_90;
  code *local_80;
  code *pcStack_78;
  code *local_70;
  code *pcStack_68;
  code *local_60;
  code *pcStack_58;
  code *local_50;
  code *pcStack_48;
  code *local_40;
  code *pcStack_38;
  code *local_30;
  code *pcStack_28;
  code *local_20;
  code *pcStack_18;
  code *local_10;
  code *pcStack_8;
  
  local_c8[0] = '\0';
  local_c8[1] = '\0';
  local_c8[2] = '\0';
  local_c8[3] = '\0';
  local_c8[4] = '\0';
  local_c8[5] = '\0';
  local_c8[6] = '\0';
  local_c8[7] = '\0';
  system("echo 0 > /proc/sys/net/ipv6/conf/ncm0/accept_dad");
  iVar2 = _GetUsbRoleStatus(local_c8);
  if (iVar2 == 0) {
    if (gLogCategory_CarPlayDemoApp < 0x33) {
      if ((gLogCategory_CarPlayDemoApp != -1) ||
         (cVar1 = _LogCategory_Initialize(&gLogCategory_CarPlayDemoApp,0x32), cVar1 != '\0')) {
        LogPrintF(&gLogCategory_CarPlayDemoApp,&DAT_0040f698,0x32,"Usb RoleStatus %s",local_c8);
      }
      iVar2 = strncasecmp(local_c8,"gadget",6);
      if (iVar2 != 0) goto LAB_00405040;
    }
    else {
      iVar2 = strncasecmp(local_c8,"gadget",6);
      if (iVar2 != 0) goto LAB_00405050;
    }
    system("echo tp25830_ctl1=1 > /dev/hsaegpio");
    usleep(500000);
    system("echo tp25830_ctl1=0 > /dev/hsaegpio");
    if ((gLogCategory_CarPlayDemoAppErr < 0x33) &&
       ((gLogCategory_CarPlayDemoAppErr != -1 ||
        (cVar1 = _LogCategory_Initialize(&gLogCategory_CarPlayDemoAppErr,0x32), cVar1 != '\0')))) {
      LogPrintF(&gLogCategory_CarPlayDemoAppErr,&DAT_0040f698,0x32,
                "Usb role is gadget, so role switch back.\n");
    }
    system("echo usb_otg1_id=0 > /dev/hsaegpio");
  }
LAB_00405040:
  if ((gLogCategory_CarPlayDemoApp < 0x33) &&
     ((gLogCategory_CarPlayDemoApp != -1 ||
      (cVar1 = _LogCategory_Initialize(&gLogCategory_CarPlayDemoApp,0x32), cVar1 != '\0')))) {
    LogPrintF(&gLogCategory_CarPlayDemoApp,&DAT_0040f698,0x32,"AirPlay starting version %s, %s\n",
              "450.14","Aug 19 2023");
  }
LAB_00405050:
  signal(0xd,(__sighandler_t)0x1);
  DAT_004256f0 = 0;
  DAT_004256f8 = 0;
  DAT_00425700 = 0;
  DAT_00425708 = 0;
  DAT_00425710 = 0;
  DAT_00425718 = 0;
  _DAT_00425720 = 0;
  _DAT_00425728 = 0;
  _DAT_00425730 = 0;
  DAT_00425738 = 0;
  DAT_00425740 = 0;
  DAT_00425748 = 0;
  DAT_00425750 = 0;
  DAT_00425758 = 0;
  DAT_00425760 = 0;
  if (1 < param_1) {
    iVar2 = 1;
    do {
      while( true ) {
        iVar4 = iVar2 + 1;
        lVar6 = (long)iVar2 * 8;
        pcVar5 = *(char **)(param_2 + (long)iVar2 * 8);
        iVar3 = strcmp(pcVar5,"--no-knob");
        if (iVar3 != 0) break;
        DAT_004257d8 = 0;
LAB_004050c4:
        iVar2 = iVar4;
        if (param_1 <= iVar4) goto LAB_0040511c;
      }
      iVar3 = strcmp(pcVar5,"--no-hi-fi-touch");
      if (iVar3 != 0) {
        iVar3 = strcmp(pcVar5,"--no-lo-fi-touch");
        if (iVar3 == 0) {
          DAT_004257dc = 0;
        }
        else {
          iVar3 = strcmp(pcVar5,"--no-touchpad");
          if (iVar3 == 0) {
            DAT_004257e0 = 0;
          }
          else {
            iVar3 = strcmp(pcVar5,"--no-proxsensor");
            if (iVar3 == 0) {
              DAT_004257e8 = 0;
            }
            else {
              iVar3 = strcmp(pcVar5,"--btid");
              if (iVar3 == 0) {
                if (param_1 <= iVar4) {
LAB_00405788:
                  fprintf(stderr,"error: %s requires a value\n",pcVar5);
LAB_004057a0:
                    /* WARNING: Subroutine does not return */
                  exit(1);
                }
                iVar4 = iVar2 + 2;
                local_d4 = CFArrayEnsureCreatedAndAppendCString
                                     (&DAT_004257a8,*(undefined8 *)(param_2 + lVar6 + 8),
                                      0xffffffffffffffff);
              }
              else {
                iVar3 = strcmp(pcVar5,"--width");
                if (iVar3 == 0) {
                  if (param_1 <= iVar4) goto LAB_00405788;
                  iVar4 = iVar2 + 2;
                  lVar6 = strtol(*(char **)(param_2 + lVar6 + 8),(char **)0x0,10);
                  DAT_004255e8 = (undefined4)lVar6;
                }
                else {
                  iVar3 = strcmp(pcVar5,"--heigh");
                  if (iVar3 == 0) {
                    if (param_1 <= iVar4) goto LAB_00405788;
                    iVar4 = iVar2 + 2;
                    lVar6 = strtol(*(char **)(param_2 + lVar6 + 8),(char **)0x0,10);
                    DAT_004255ec = (undefined4)lVar6;
                  }
                  else {
                    iVar3 = strcmp(pcVar5,"--widthMM");
                    if (iVar3 == 0) {
                      if (param_1 <= iVar4) goto LAB_00405788;
                      iVar4 = iVar2 + 2;
                      lVar6 = strtol(*(char **)(param_2 + lVar6 + 8),(char **)0x0,10);
                      DAT_004257d0 = (undefined4)lVar6;
                    }
                    else {
                      iVar3 = strcmp(pcVar5,"--heightMM");
                      if (iVar3 == 0) {
                        if (param_1 <= iVar4) goto LAB_00405788;
                        iVar4 = iVar2 + 2;
                        lVar6 = strtol(*(char **)(param_2 + lVar6 + 8),(char **)0x0,10);
                        DAT_004257d4 = (undefined4)lVar6;
                      }
                      else {
                        iVar3 = strcmp(pcVar5,"--modes");
                        if (iVar3 == 0) {
                          if (param_1 <= iVar4) {
                            fprintf(stderr,"error: %s requires a value. For example:\n",pcVar5);
                            fwrite("    --modes screen=userInitiated,anytime\n",1,0x29,stderr);
                            fwrite("    --modes mainAudio=anytime,anytime\n",1,0x26,stderr);
                            fwrite("    --modes phoneCall\n",1,0x16,stderr);
                            fwrite("    --modes speech=speaking\n",1,0x1c,stderr);
                            fwrite("    --modes turnByTurn\n",1,0x17,stderr);
                    /* WARNING: Subroutine does not return */
                            exit(1);
                          }
                          iVar4 = iVar2 + 2;
                          local_d4 = FUN_00406b40(*(undefined8 *)(param_2 + lVar6 + 8));
                          if (local_d4 != 0) goto LAB_004057a0;
                          DAT_00425808 = 1;
                        }
                        else {
                          iVar3 = strcmp(pcVar5,"--right-hand-drive");
                          if (iVar3 == 0) {
                            if (param_1 <= iVar4) goto LAB_00405788;
                            iVar4 = iVar2 + 2;
                            pcVar5 = *(char **)(param_2 + lVar6 + 8);
                            iVar2 = strcmp(pcVar5,"true");
                            if (iVar2 == 0) {
                              DAT_004257b0 = kCFLBooleanTrue;
                            }
                            else {
                              iVar2 = strcmp(pcVar5,"false");
                              if (iVar2 == 0) {
                                DAT_004257b0 = kCFLBooleanFalse;
                              }
                            }
                          }
                          else {
                            iVar3 = strcmp(pcVar5,"--enable-etc");
                            if (iVar3 == 0) {
                              DAT_004257c8 = 1;
                            }
                            else {
                              iVar3 = strcmp(pcVar5,"--primary-input-device");
                              if (iVar3 == 0) {
                                if (param_1 <= iVar4) goto LAB_00405788;
                                iVar4 = iVar2 + 2;
                                lVar6 = strtol(*(char **)(param_2 + lVar6 + 8),(char **)0x0,10);
                                DAT_004255f4 = (undefined4)lVar6;
                              }
                              else {
                                iVar3 = strcmp(pcVar5,"--enhanced-requestcarui");
                                if (iVar3 == 0) {
                                  DAT_004257cc = 1;
                                }
                                else {
                                  iVar3 = strcmp(pcVar5,"--deviceid");
                                  if (iVar3 == 0) {
                                    if (param_1 <= iVar4) goto LAB_00405788;
                                    iVar4 = iVar2 + 2;
                                    DAT_004257f8 = CFStringCreateWithCString
                                                             (0,*(undefined8 *)(param_2 + lVar6 + 8)
                                                              ,0x8000100);
                                  }
                                  else {
                                    iVar3 = strcmp(pcVar5,"--iOSVersionMin");
                                    if (iVar3 == 0) {
                                      if (param_1 <= iVar4) goto LAB_00405788;
                                      iVar4 = iVar2 + 2;
                                      DAT_004257f0 = CFStringCreateWithCString
                                                               (0,*(undefined8 *)
                                                                   (param_2 + lVar6 + 8),0x8000100);
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        goto LAB_004050c4;
      }
      DAT_004255f0 = 0;
      iVar2 = iVar4;
    } while (iVar4 < param_1);
  }
LAB_0040511c:
  GetInterfaceMACAddress("wlan0",auStack_d0);
  HardwareAddressToCString(auStack_d0,6,gDeviceIDCString);
  DAT_004257f8 = CFStringCreateWithCString(0,gDeviceIDCString,0x8000100);
  if (DAT_004257f8 == 0) {
    local_d4 = -0x1a3a;
  }
  else {
    if (DAT_00425808 != 0) {
      DAT_00425768 = AirPlayCreateModesDictionary(&DAT_004256f0,0,&local_d4);
    }
    InitStreamPlayer(FUN_00409610);
    local_d4 = 0;
    if ((DAT_004255f0 != 0) || (DAT_004257dc != 0)) {
      DAT_004257e4 = DAT_0042580c;
      DAT_0042580c = DAT_0042580c + '\x01';
    }
    if (DAT_004257d8 != 0) {
      DAT_004257e5 = DAT_0042580c;
      DAT_0042580c = DAT_0042580c + '\x01';
    }
    if (DAT_004257e8 != 0) {
      DAT_004257ec = DAT_0042580c;
      DAT_0042580c = DAT_0042580c + '\x01';
    }
    DAT_004257ee = DAT_0042580c + '\x01';
    DAT_004257ed = DAT_0042580c;
    pcStack_78 = FUN_00409cc0;
    local_80 = FUN_00408c70;
    pcStack_68 = FUN_00409380;
    local_70 = FUN_004063a0;
    pcStack_58 = FUN_00409190;
    local_60 = FUN_00409250;
    pcStack_48 = FUN_00409040;
    local_50 = FUN_00409100;
    pcStack_38 = FUN_00406300;
    local_40 = FUN_00409520;
    pcStack_28 = FUN_00408fa0;
    local_30 = FUN_00409bb0;
    pcStack_18 = FUN_00408e40;
    local_20 = FUN_00408ee0;
    pcStack_8 = FUN_00408d10;
    local_10 = FUN_00408da0;
    DAT_0042580c = DAT_0042580c + '\x02';
    CarPlayInterfaceSetDelegate(&local_80);
    iAP2InterfaceInitial();
    local_a0 = FUN_00409850;
    uStack_98 = 0;
    local_90 = FUN_004096f0;
    pcStack_b8 = FUN_00408a20;
    local_c0 = FUN_00408a60;
    pcStack_a8 = FUN_00409930;
    local_b0 = FUN_00408d10;
    CarPlay2iAP2InterfaceSetDelegate(&local_c0);
    CarPlayInterfaceInitialized();
  }
  return local_d4 != 0;
}


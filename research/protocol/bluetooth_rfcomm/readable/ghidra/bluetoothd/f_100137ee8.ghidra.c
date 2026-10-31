/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100137ee8
 * original code SHA256: 0c13cf806986d5984a6e5cb23a8b974e1f136634a7170e0879dc77bca5dbcf74
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


void phone_fn_100137ee8(long param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  long *plVar6;
  char *pcVar7;
  long *plVar8;
  undefined8 uVar9;
  char cStack_68;
  undefined7 uStack_67;
  char cStack_51;
  undefined2 uStack_50;
  undefined6 uStack_4e;
  char cStack_39;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  if (lRam0000000100c1b990 != -1) {
    FUN_1008e25ec();
  }
  FUN_100209558(lRam0000000100c1b988 + 0x20,param_1 + 0x18);
  if (lRam0000000100c1baa0 != -1) {
    FUN_1008e2600();
  }
  FUN_1000fe520(lRam0000000100c1ba98 + 0x130,param_1 + 0x28);
  uStack_30 = 0;
  uStack_28 = 0;
  FUN_100006ef8(&uStack_30,param_1 + 0x38);
  *(undefined1 *)(param_1 + 0x78) = 1;
  FUN_100006f28();
  lVar5 = param_1;
  FUN_100137874();
  FUN_100017860();
  plVar6 = (long *)(lVar5 + 0x188);
  FUN_1001386dc(plVar6,param_1 + 0x30);
  FUN_1000071b8();
  (**(code **)(*plVar6 + 0x2c0))();
  if ((int)plVar6 != 0) {
    FUN_1000110f0();
    pcVar7 = (char *)&uStack_50;
    FUN_1001ec44c(pcVar7,0x10);
    uVar2 = s_ScanCorePageScan_100a6dfdf._8_8_;
    uVar9 = s_ScanCorePageScan_100a6dfdf._0_8_;
    *(undefined8 *)(pcVar7 + 8) = s_ScanCorePageScan_100a6dfdf._8_8_;
    *(undefined8 *)pcVar7 = uVar9;
    pcVar7[0x10] = '\0';
    pcVar7 = &cStack_68;
    FUN_1001ec44c(pcVar7,0x1c);
    uVar1 = CONCAT44(s_ScanCorePageScanDebugEnabled_100a6dff0._16_4_,
                     s_ScanCorePageScanDebugEnabled_100a6dff0._12_4_);
    *(undefined8 *)(pcVar7 + 0x14) = s_ScanCorePageScanDebugEnabled_100a6dff0._20_8_;
    *(undefined8 *)(pcVar7 + 0xc) = uVar1;
    uVar1 = s_ScanCorePageScanDebugEnabled_100a6dff0._0_8_;
    *(ulong *)(pcVar7 + 8) =
         CONCAT44(s_ScanCorePageScanDebugEnabled_100a6dff0._12_4_,
                  s_ScanCorePageScanDebugEnabled_100a6dff0._8_4_);
    *(undefined8 *)pcVar7 = uVar1;
    pcVar7[0x1c] = '\0';
    (**(code **)(*plVar6 + 0x48))(plVar6,&uStack_50,&cStack_68,param_1 + 0x1f9);
    plVar8 = plVar6;
    if (cStack_51 < '\0') {
      plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
      __ZdlPv();
    }
    if (cStack_39 < '\0') {
      plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
      __ZdlPv();
    }
    if (((int)plVar6 != 0) && (*(char *)(param_1 + 0x1f9) == '\x01')) {
      FUN_1000110f0();
      pcVar7 = (char *)&uStack_50;
      FUN_1001ec44c(pcVar7,0x10);
      *(undefined8 *)(pcVar7 + 8) = uVar2;
      *(undefined8 *)pcVar7 = uVar9;
      pcVar7[0x10] = '\0';
      pcVar7 = &cStack_68;
      FUN_1001ec44c(pcVar7,0x18);
      *(undefined8 *)(pcVar7 + 0x10) = s_ScanCorePageScanInterval_100a6e00d._16_8_;
      uVar1 = s_ScanCorePageScanInterval_100a6e00d._0_8_;
      *(undefined8 *)(pcVar7 + 8) = s_ScanCorePageScanInterval_100a6e00d._8_8_;
      *(undefined8 *)pcVar7 = uVar1;
      pcVar7[0x18] = '\0';
      (**(code **)(*plVar8 + 0x80))(plVar8,&uStack_50,&cStack_68,param_1 + 0x1fc);
      if (cStack_51 < '\0') {
        plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
        __ZdlPv();
      }
      if (cStack_39 < '\0') {
        plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
        __ZdlPv();
      }
      FUN_1000110f0();
      pcVar7 = (char *)&uStack_50;
      FUN_1001ec44c(pcVar7,0x10);
      *(undefined8 *)(pcVar7 + 8) = uVar2;
      *(undefined8 *)pcVar7 = uVar9;
      pcVar7[0x10] = '\0';
      pcVar7 = &cStack_68;
      FUN_1001ec44c(pcVar7,0x16);
      *(ulong *)(pcVar7 + 0xe) =
           CONCAT62(s_ScanCorePageScanWindow_100a6e026._16_6_,
                    s_ScanCorePageScanWindow_100a6e026._14_2_);
      uVar1 = s_ScanCorePageScanWindow_100a6e026._0_8_;
      *(ulong *)(pcVar7 + 8) =
           CONCAT26(s_ScanCorePageScanWindow_100a6e026._14_2_,
                    s_ScanCorePageScanWindow_100a6e026._8_6_);
      *(undefined8 *)pcVar7 = uVar1;
      pcVar7[0x16] = '\0';
      (**(code **)(*plVar8 + 0x80))(plVar8,&uStack_50,&cStack_68,param_1 + 0x200);
      if (cStack_51 < '\0') {
        plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
        __ZdlPv();
      }
      if (cStack_39 < '\0') {
        plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
        __ZdlPv();
      }
      FUN_1000110f0();
      pcVar7 = (char *)&uStack_50;
      FUN_1001ec44c(pcVar7,0x10);
      *(undefined8 *)(pcVar7 + 8) = uVar2;
      *(undefined8 *)pcVar7 = uVar9;
      pcVar7[0x10] = '\0';
      pcVar7 = &cStack_68;
      FUN_1001ec44c(pcVar7,0x1a);
      uVar1 = CONCAT26(s_ScanCorePageScanInterlaced_100a6e03d._16_2_,
                       s_ScanCorePageScanInterlaced_100a6e03d._10_6_);
      *(undefined8 *)(pcVar7 + 0x12) = s_ScanCorePageScanInterlaced_100a6e03d._18_8_;
      *(undefined8 *)(pcVar7 + 10) = uVar1;
      uVar1 = s_ScanCorePageScanInterlaced_100a6e03d._0_8_;
      *(ulong *)(pcVar7 + 8) =
           CONCAT62(s_ScanCorePageScanInterlaced_100a6e03d._10_6_,
                    s_ScanCorePageScanInterlaced_100a6e03d._8_2_);
      *(undefined8 *)pcVar7 = uVar1;
      pcVar7[0x1a] = '\0';
      (**(code **)(*plVar8 + 0x48))(plVar8,&uStack_50,&cStack_68,param_1 + 0x204);
      if (cStack_51 < '\0') {
        plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
        __ZdlPv();
      }
      if (cStack_39 < '\0') {
        plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
        __ZdlPv();
      }
      FUN_1000110f0();
      pcVar7 = (char *)&uStack_50;
      FUN_1001ec44c(pcVar7,0x10);
      *(undefined8 *)(pcVar7 + 8) = uVar2;
      *(undefined8 *)pcVar7 = uVar9;
      pcVar7[0x10] = '\0';
      pcVar7 = &cStack_68;
      FUN_1001ec44c(pcVar7,0x1d);
      uVar1 = CONCAT53(s_ScanCorePageScanDebugElnaMode_100a6e058._16_5_,
                       s_ScanCorePageScanDebugElnaMode_100a6e058._13_3_);
      *(undefined8 *)(pcVar7 + 0x15) = s_ScanCorePageScanDebugElnaMode_100a6e058._21_8_;
      *(undefined8 *)(pcVar7 + 0xd) = uVar1;
      uVar1 = s_ScanCorePageScanDebugElnaMode_100a6e058._0_8_;
      *(ulong *)(pcVar7 + 8) =
           CONCAT35(s_ScanCorePageScanDebugElnaMode_100a6e058._13_3_,
                    s_ScanCorePageScanDebugElnaMode_100a6e058._8_5_);
      *(undefined8 *)pcVar7 = uVar1;
      pcVar7[0x1d] = '\0';
      (**(code **)(*plVar8 + 0x48))(plVar8,&uStack_50,&cStack_68,param_1 + 0x205);
      if (cStack_51 < '\0') {
        plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
        __ZdlPv();
      }
      if (cStack_39 < '\0') {
        plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
        __ZdlPv();
      }
      FUN_1000110f0();
      pcVar7 = (char *)&uStack_50;
      FUN_1001ec44c(pcVar7,0x10);
      *(undefined8 *)(pcVar7 + 8) = uVar2;
      *(undefined8 *)pcVar7 = uVar9;
      pcVar7[0x10] = '\0';
      pcVar7 = &cStack_68;
      FUN_1001ec44c(pcVar7,0x20);
      uVar4 = s_ScanCorePageScanUseAuxScanParams_100a6e076._24_8_;
      uVar3 = s_ScanCorePageScanUseAuxScanParams_100a6e076._16_8_;
      uVar1 = s_ScanCorePageScanUseAuxScanParams_100a6e076._0_8_;
      *(undefined8 *)(pcVar7 + 8) = s_ScanCorePageScanUseAuxScanParams_100a6e076._8_8_;
      *(undefined8 *)pcVar7 = uVar1;
      *(undefined8 *)(pcVar7 + 0x18) = uVar4;
      *(undefined8 *)(pcVar7 + 0x10) = uVar3;
      pcVar7[0x20] = '\0';
      (**(code **)(*plVar8 + 0x48))(plVar8,&uStack_50,&cStack_68,param_1 + 0x206);
      if (cStack_51 < '\0') {
        plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
        __ZdlPv();
      }
      if (cStack_39 < '\0') {
        plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
        __ZdlPv();
      }
      FUN_1000110f0();
      pcVar7 = (char *)&uStack_50;
      FUN_1001ec44c(pcVar7,0x10);
      *(undefined8 *)(pcVar7 + 8) = uVar2;
      *(undefined8 *)pcVar7 = uVar9;
      pcVar7[0x10] = '\0';
      pcVar7 = &cStack_68;
      FUN_1001ec44c(pcVar7,0x1d);
      uVar1 = CONCAT53(s_ScanCorePageScanEnableAuxScan_100a6e097._16_5_,
                       s_ScanCorePageScanEnableAuxScan_100a6e097._13_3_);
      *(undefined8 *)(pcVar7 + 0x15) = s_ScanCorePageScanEnableAuxScan_100a6e097._21_8_;
      *(undefined8 *)(pcVar7 + 0xd) = uVar1;
      uVar1 = s_ScanCorePageScanEnableAuxScan_100a6e097._0_8_;
      *(ulong *)(pcVar7 + 8) =
           CONCAT35(s_ScanCorePageScanEnableAuxScan_100a6e097._13_3_,
                    s_ScanCorePageScanEnableAuxScan_100a6e097._8_5_);
      *(undefined8 *)pcVar7 = uVar1;
      pcVar7[0x1d] = '\0';
      (**(code **)(*plVar8 + 0x48))(plVar8,&uStack_50,&cStack_68,param_1 + 0x207);
      if (cStack_51 < '\0') {
        plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
        __ZdlPv();
      }
      if (cStack_39 < '\0') {
        plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
        __ZdlPv();
      }
      FUN_1000110f0();
      pcVar7 = (char *)&uStack_50;
      FUN_1001ec44c(pcVar7,0x10);
      *(undefined8 *)(pcVar7 + 8) = uVar2;
      *(undefined8 *)pcVar7 = uVar9;
      pcVar7[0x10] = '\0';
      pcVar7 = &cStack_68;
      FUN_1001ec44c(pcVar7,0x1e);
      uVar1 = CONCAT62(s_ScanCorePageScanPreemptAuxScan_100a6e0b5._16_6_,
                       s_ScanCorePageScanPreemptAuxScan_100a6e0b5._14_2_);
      *(undefined8 *)(pcVar7 + 0x16) = s_ScanCorePageScanPreemptAuxScan_100a6e0b5._22_8_;
      *(undefined8 *)(pcVar7 + 0xe) = uVar1;
      uVar1 = s_ScanCorePageScanPreemptAuxScan_100a6e0b5._0_8_;
      *(ulong *)(pcVar7 + 8) =
           CONCAT26(s_ScanCorePageScanPreemptAuxScan_100a6e0b5._14_2_,
                    s_ScanCorePageScanPreemptAuxScan_100a6e0b5._8_6_);
      *(undefined8 *)pcVar7 = uVar1;
      pcVar7[0x1e] = '\0';
      (**(code **)(*plVar8 + 0x48))(plVar8,&uStack_50,&cStack_68,param_1 + 0x208);
      if (cStack_51 < '\0') {
        plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
        __ZdlPv();
      }
      if (cStack_39 < '\0') {
        plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
        __ZdlPv();
      }
      FUN_1000110f0();
      pcVar7 = (char *)&uStack_50;
      FUN_1001ec44c(pcVar7,0x10);
      *(undefined8 *)(pcVar7 + 8) = uVar2;
      *(undefined8 *)pcVar7 = uVar9;
      pcVar7[0x10] = '\0';
      pcVar7 = &cStack_68;
      FUN_1001ec44c(pcVar7,0x23);
      pcVar7[0x1f] = 'I';
      uVar2 = s_ScanCorePageScanAuxScanDurationI_100a6e0d4._24_8_;
      uVar9 = s_ScanCorePageScanAuxScanDurationI_100a6e0d4._16_8_;
      uVar1 = s_ScanCorePageScanAuxScanDurationI_100a6e0d4._0_8_;
      pcVar7[0x20] = 'n';
      pcVar7[0x21] = 'M';
      pcVar7[0x22] = 's';
      *(undefined8 *)(pcVar7 + 8) = s_ScanCorePageScanAuxScanDurationI_100a6e0d4._8_8_;
      *(undefined8 *)pcVar7 = uVar1;
      *(undefined8 *)(pcVar7 + 0x18) = uVar2;
      *(undefined8 *)(pcVar7 + 0x10) = uVar9;
      pcVar7[0x23] = '\0';
      (**(code **)(*plVar8 + 0x80))(plVar8,&uStack_50,&cStack_68,param_1 + 0x20c);
      if (cStack_51 < '\0') {
        plVar8 = (long *)CONCAT71(uStack_67,cStack_68);
        __ZdlPv();
      }
      if (cStack_39 < '\0') {
        plVar8 = (long *)CONCAT62(uStack_4e,uStack_50);
        __ZdlPv();
      }
    }
    FUN_1000110f0();
    (**(code **)(*plVar8 + 0x280))();
    if ((int)plVar8 != 0) {
      cStack_68 = '\0';
      FUN_100061a60(&cStack_68);
      uVar1 = uRam0000000100cae458;
      uVar9 = uRam0000000100cae458;
      _os_log_type_enabled(uRam0000000100cae458,0);
      if ((int)uVar9 != 0) {
        uStack_50 = 0;
        __os_log_impl(0x100000000,uVar1,0,"Disabling BT Page Scans",&uStack_50,2);
      }
      FUN_1000648b8(0x47,0);
      FUN_10006b538(&cStack_68);
    }
  }
  FUN_100006ec0(&uStack_30);
  return;
}


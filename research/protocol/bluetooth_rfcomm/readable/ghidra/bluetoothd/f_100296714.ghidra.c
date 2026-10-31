/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100296714
 * original code SHA256: 3b6696650fe88219f57c653b6de20c92bee0d78f12881718a422c47c789cf6a5
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


undefined1 * FUN_100296714(ushort *param_1)

{
  int iVar1;
  ushort *puVar2;
  undefined1 *puVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uStack_80;
  ushort *puStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  puVar2 = param_1;
  FUN_100295f6c();
  if (puVar2 == (ushort *)0x0) {
    FUN_1000f9438();
  }
  uStack_40 = 0;
  uStack_58 = 0;
  uStack_60 = 0;
  uStack_48 = 0;
  uStack_50 = 0;
  uStack_68 = 0;
  uStack_70 = 0;
  if ((char)puVar2[0x11] == '\x05') {
    if (*(char *)((long)puVar2 + 0x23) == '\0') {
      puVar3 = (undefined1 *)0x0;
      *(undefined1 *)(puVar2 + 0x11) = 0;
      goto LAB_10029683c;
    }
  }
  else if ((char)puVar2[0x11] == '\x04') {
    if (*(char *)((long)puVar2 + 0x23) == '\x03') {
      puVar3 = *(undefined1 **)(puVar2 + 4);
      FUN_100322bf4();
      if ((int)puVar3 == 0) {
        *(undefined1 *)((long)puVar2 + 0x23) = 4;
        goto LAB_10029683c;
      }
      iVar1 = 2;
      FUN_10000d938(2,0xf);
      if (iVar1 != 0) {
        FUN_10000d120("ScoDisconnect failed - %!, forcing disconnect!\n");
        uVar4 = 0xf;
        FUN_10000e9d4();
        uVar5 = uVar4;
        _os_log_type_enabled();
        if ((int)uVar5 != 0) {
          FUN_10018f150(uVar4);
        }
      }
    }
    else {
      puVar3 = (undefined1 *)(ulong)*puVar2;
      if (*puVar2 == 0) goto LAB_100296838;
      FUN_1003c31b4(puVar3,0x3a7);
      if ((int)puVar3 == 0) goto LAB_10029683c;
      iVar1 = 2;
      FUN_10000d938(2,0xf);
      if (iVar1 != 0) {
        FUN_10000d120("RFCOMM_Disconnect failed - %!, forcing disconnect!\n");
        uVar4 = 0xf;
        FUN_10000e9d4();
        uVar5 = uVar4;
        _os_log_type_enabled();
        if ((int)uVar5 != 0) {
          FUN_10018f150(uVar4);
        }
      }
    }
    FUN_10029697c(*puVar2);
    goto LAB_10029683c;
  }
LAB_100296838:
  puVar3 = (undefined1 *)0x0;
LAB_10029683c:
  if ((*(char *)((long)puVar2 + 0x23) == '\0') && ((char)puVar2[0x11] == '\0')) {
    if (*(int *)(puVar2 + 0xc) != 0) {
      FUN_1000609fc();
      puVar2[0xc] = 0;
      puVar2[0xd] = 0;
    }
    FUN_100295f6c();
    if (param_1 != (ushort *)0x0) {
      *(undefined1 *)(param_1 + 0x11) = 0;
    }
    FUN_100322ae4(puVar2 + 0xe);
    uStack_68 = CONCAT44((int)((ulong)(puVar2 + 0xe) >> 0x20),*(undefined4 *)(puVar2 + 2));
    uStack_70._0_6_ = CONCAT24(*puVar2,2);
    (**(code **)(lRam0000000100c26298 + 0x18))(&uStack_70);
    FUN_1003d84bc(puVar2 + 0x14);
    FUN_1000110b8(puVar2);
    *(char *)(lRam0000000100c26298 + 0x10) = *(char *)(lRam0000000100c26298 + 0x10) + -1;
  }
  else if (*(int *)(puVar2 + 0xc) == 0) {
    uStack_80 = 2;
    puVar3 = &LAB_100296a2c;
    puStack_78 = puVar2;
    FUN_10006135c(&LAB_100296a2c,&uStack_80,100);
    if ((int)puVar3 != 0) {
      iVar1 = 2;
      FUN_10000d938(2,0xf);
      if (iVar1 != 0) {
        FUN_10000d120("Register disconnect timeout handler failed %!\n");
        uVar4 = 0xf;
        FUN_10000e9d4();
        uVar5 = uVar4;
        _os_log_type_enabled();
        if ((int)uVar5 != 0) {
          FUN_10018f150(uVar4);
        }
      }
    }
  }
  return puVar3;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x1005fbae8
 * original code SHA256: c26766701ba6452eea5efa5447ee46f4249744fb2bb318b4cd07ea918cd17a5d
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * FUN_1005fbae8(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  byte bVar5;
  char cVar6;
  undefined8 uVar7;
  char *pcVar8;
  undefined2 uStack_80;
  undefined6 uStack_7e;
  char cStack_69;
  undefined4 uStack_60;
  undefined1 *puStack_5c;
  undefined8 uStack_50;
  undefined8 uStack_48;
  byte bStack_39;
  char *pcStack_38;
  
  pcStack_38 = (char *)0x0;
  bStack_39 = 0;
  uStack_50 = 0;
  uStack_48 = 0;
  FUN_100006ef8(&uStack_50,param_1 + 0x228);
  lVar3 = param_1 + 0x268;
  FUN_100006f84();
  uVar7 = uRam0000000100cae440;
  if (lVar3 == 0) {
    uVar4 = uRam0000000100cae440;
    _os_log_type_enabled(uRam0000000100cae440,1);
    if ((int)uVar4 == 0) goto LAB_1005fbd48;
    FUN_10010aa84(&uStack_80,param_1);
    puStack_5c = (undefined1 *)CONCAT62(uStack_7e,uStack_80);
    if (-1 < cStack_69) {
      puStack_5c = (undefined1 *)&uStack_80;
    }
    uStack_60 = (undefined4)_UNK_100930b20;
    pcVar8 = "No EIR for device %{public}s";
  }
  else {
    iVar2 = (int)param_1 + 0x268;
    FUN_1000110dc();
    FUN_10032541c();
    uVar7 = uRam0000000100cae440;
    if (((iVar2 != 0) || (pcStack_38 == (char *)0x0)) || (bStack_39 == 0)) {
      uVar4 = uRam0000000100cae440;
      _os_log_type_enabled(uRam0000000100cae440,1);
      if ((int)uVar4 != 0) {
        uStack_80 = 0;
        __os_log_impl(0x100000000,uVar7,1,"Could not get the EIR manufacturer data",&uStack_80,2);
      }
      goto LAB_1005fbd48;
    }
    cVar6 = *pcStack_38;
    if (((cVar6 == '\0') || (cVar6 == 'L')) || (pcStack_38[1] == 'L')) {
      bVar5 = 0;
      lVar3 = 1;
      if (cVar6 != 'L') {
        lVar3 = 2;
      }
      pcStack_38 = pcStack_38 + lVar3;
      cVar6 = *pcStack_38;
      do {
        bVar1 = bVar5;
        if (cVar6 != '\x01') {
          if (((cVar6 == '\x02') && (2 < (byte)pcStack_38[(ulong)bVar5 + 1])) &&
             (pcStack_38[(byte)(bVar5 + 2)] == '\x02')) {
            pcVar8 = pcStack_38 + (byte)(bVar5 + 4);
            FUN_10061e314(pcVar8,pcStack_38[(ulong)bVar5 + 1] - 4,param_2,param_3);
            goto LAB_1005fbd4c;
          }
          break;
        }
        do {
          bVar5 = bVar1;
          bVar1 = bVar5 + 1;
        } while (pcStack_38[bVar5] != '\0');
        cVar6 = '\0';
      } while (bVar5 < bStack_39);
      goto LAB_1005fbd48;
    }
    uVar4 = uRam0000000100cae440;
    _os_log_type_enabled(uRam0000000100cae440,1);
    if ((int)uVar4 == 0) goto LAB_1005fbd48;
    FUN_10010aa84(&uStack_80,param_1);
    puStack_5c = (undefined1 *)CONCAT62(uStack_7e,uStack_80);
    if (-1 < cStack_69) {
      puStack_5c = (undefined1 *)&uStack_80;
    }
    uStack_60 = (undefined4)_UNK_100930b20;
    pcVar8 = "Device %{public}s is not an Apple device";
  }
  __os_log_impl(0x100000000,uVar7,1,pcVar8,&uStack_60,0xc);
  if (cStack_69 < '\0') {
    __ZdlPv(CONCAT62(uStack_7e,uStack_80));
  }
LAB_1005fbd48:
  pcVar8 = (char *)0x0;
LAB_1005fbd4c:
  FUN_100006ec0(&uStack_50);
  return pcVar8;
}


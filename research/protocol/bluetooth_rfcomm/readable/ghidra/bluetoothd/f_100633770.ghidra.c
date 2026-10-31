/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x100633770
 * original code SHA256: 9e49b51e9e7d7f0d2b580084cc274b1ffaf4ff54a5eaca33ac33c764e1af410e
 * source SHA256: cfd94854d0a2efd3ca4a2de6e55349f43fd0d274a4b8bfa9937f29d9f7208cb1
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void phone_fn_100633770(void)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 **appuStack_88 [2];
  char cStack_71;
  uint uStack_70;
  undefined8 **ppuStack_6c;
  undefined2 uStack_64;
  undefined4 uStack_62;
  undefined2 uStack_5e;
  undefined2 uStack_5c;
  undefined2 uStack_5a;
  undefined2 uStack_58;
  char *pcStack_56;
  
  uVar1 = uRam0000000100cae4a0;
  uVar2 = uRam0000000100cae4a0;
  _os_log_type_enabled(uRam0000000100cae4a0,0);
  if ((int)uVar2 != 0) {
    FUN_10010aa84(appuStack_88,*puRam0000000100c3de88);
    ppuStack_6c = appuStack_88[0];
    if (-1 < cStack_71) {
      ppuStack_6c = appuStack_88;
    }
    uStack_62 = *(undefined4 *)(lRam0000000100cae158 + 0x80);
    if (*(uint *)(lRam0000000100cae158 + 0x84) < 0xb) {
      pcStack_56 = (&PTR_s_SDP_IDLE_STATE_100bbde30)[*(uint *)(lRam0000000100cae158 + 0x84)];
    }
    else {
      pcStack_56 = "unknown sdp state";
    }
    uStack_70 = (uint)_UNK_1009357e0;
    uStack_64 = 0x400;
    uStack_5e = 0x400;
    uStack_5c = (undefined2)*(undefined4 *)(puRam0000000100c3de88 + 0x1a);
    uStack_5a = (undefined2)((uint)*(undefined4 *)(puRam0000000100c3de88 + 0x1a) >> 0x10);
    uStack_58 = 0x820;
    __os_log_impl(0x100000000,uVar1,0,
                  "SDP disconnected from device %{public}s with result %d, outstanding attempts %d, state %s"
                  ,&uStack_70,0x22);
    if (cStack_71 < '\0') {
      __ZdlPv(appuStack_88[0]);
    }
  }
  uVar1 = uRam0000000100cae4a0;
  lVar3 = lRam0000000100cae158;
  if (*(int *)(lRam0000000100cae158 + 0x84) - 2U < 3) {
    uVar2 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar2 != 0) {
      uStack_70 = (uint)_UNK_100930510;
      ppuStack_6c = (undefined8 **)
                    CONCAT44(ppuStack_6c._4_4_,*(undefined4 *)(*(long *)(lVar3 + 0x70) + 0x2e0));
      __os_log_impl(0x100000000,uVar1,0,"SDP disconnected during query states, version %d",
                    &uStack_70,8);
      lVar3 = lRam0000000100cae158;
    }
    if (*(int *)(*(long *)(lVar3 + 0x70) + 0x2e0) == 0) {
      FUN_1005e6928();
      lVar3 = lRam0000000100cae158;
    }
  }
  uVar1 = uRam0000000100cae4a0;
  uVar2 = uRam0000000100cae4a0;
  _os_log_type_enabled(uRam0000000100cae4a0,0);
  if ((int)uVar2 != 0) {
    if (*(uint *)(lVar3 + 0x84) < 0xb) {
      ppuStack_6c = (undefined8 **)(&PTR_s_SDP_IDLE_STATE_100bbde30)[*(uint *)(lVar3 + 0x84)];
    }
    else {
      ppuStack_6c = (undefined8 **)0x100a6bbea;
    }
    uStack_70 = (uint)_UNK_100930b18;
    uStack_64 = 0x820;
    uStack_62 = 0xa6badc;
    uStack_5e = 1;
    uStack_5c = 0;
    __os_log_impl(0x100000000,uVar1,0,"SDP Client State Change: %s -> %s\n",&uStack_70,0x16);
    lVar3 = lRam0000000100cae158;
  }
  *(undefined4 *)(lVar3 + 0x84) = 0;
  uVar1 = uRam0000000100cae4a0;
  if ((*(byte *)((long)puRam0000000100c3de88 + 0xd4) & 1) == 0) {
    uStack_70 = uStack_70 & 0xffffff00;
    FUN_100061a60(&uStack_70);
    FUN_1006333a4();
    FUN_10006b538(&uStack_70);
  }
  else {
    uVar2 = uRam0000000100cae4a0;
    _os_log_type_enabled(uRam0000000100cae4a0,0);
    if ((int)uVar2 != 0) {
      uStack_70 = uStack_70 & 0xffff0000;
      __os_log_impl(0x100000000,uVar1,0,
                    "SDPClient Disconnect dispatch called during system shut down, clean up",
                    &uStack_70,2);
    }
    FUN_1006333a4();
  }
  return;
}


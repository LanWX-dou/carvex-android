/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251ace728
 * original code SHA256: cf530e4f1e75d59a261d78826076496213fd23b7c9f83bbe08fb8931d44c5e95
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x000251ace8bc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulong _fpAuthentication_AuthenticateEndpoint(void)

{
  long lVar1;
  int iVar2;
  long *plVar3;
  ulong uVar4;
  long lVar5;
  code *pcVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  long lVar9;
  long local_90;
  long local_88;
  byte local_7d;
  undefined4 local_7c;
  long local_78;
  ulong local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  long local_48;
  
  local_48 = *_DAT_2681b4ee0;
  local_70 = 0;
  local_68 = 0;
  local_7c = 0;
  local_7d = 0xff;
  local_90 = 0;
  local_88 = 0;
  plVar3 = (long *)func_0x00025810ac50();
  local_78 = 0;
  if ((_gLogCategory_APAuthenticationClientFairPlay < 0x29) &&
     ((_gLogCategory_APAuthenticationClientFairPlay != -1 ||
      (iVar2 = func_0x000258101e40(&_gLogCategory_APAuthenticationClientFairPlay,0x2000028),
      iVar2 != 0)))) {
    _fpAuthentication_AuthenticateEndpoint_cold_1();
  }
  local_60 = 0;
  uStack_58 = 0;
  local_50 = 0;
  uVar4 = func_0x000258109260(&local_60,0,0);
  if ((int)uVar4 == 0) {
    if (*plVar3 != 0) {
      _IPaI1oem5iL();
      *plVar3 = 0;
    }
    uVar4 = _cp2g1b9ro(plVar3,&local_60);
    if ((int)uVar4 == 0) {
      local_70 = 0;
      local_68 = 0;
      uVar4 = _Mib5yocT(3,&local_60,*plVar3,0,0,&local_78,&local_7c,&local_7d);
      if ((int)uVar4 == 0) {
        uVar8 = *_DAT_2680d3150;
        do {
          uVar4 = (ulong)local_7d;
          if (local_7d == 0) goto LAB_251ace954;
          if (local_7d != 1) {
            func_0x000258109a30(0,"fpAuthentication_AuthenticateEndpoint",0xc4,0);
            uVar4 = 0xfffee786;
            goto LAB_251ace954;
          }
          if (local_88 != 0) {
            func_0x0002580f5830();
            local_88 = 0;
          }
          if (local_90 != 0) {
            func_0x0002580f5830();
            local_90 = 0;
          }
          uVar4 = func_0x00025810f280(uVar8,local_78,local_7c,&local_88);
          if ((int)uVar4 != 0) {
            _fpAuthentication_AuthenticateEndpoint_cold_4();
            goto LAB_251ace954;
          }
          if (local_78 != 0) {
            _jEHf8Xzsv8K();
            local_78 = 0;
          }
          lVar1 = local_88;
          lVar9 = plVar3[1];
          lVar5 = func_0x000258109150(lVar9);
          puVar7 = (undefined8 *)(*(long *)(lVar5 + 0x10) + 0x38);
          pcVar6 = (code *)*puVar7;
          if ((pcVar6 == (code *)0x0) || (pcVar6 == (code *)0x0)) {
            uVar4 = 0xffffce12;
LAB_251ace93c:
            uVar8 = 0xd0;
            goto LAB_251ace94c;
          }
          uVar4 = (*pcVar6)((ulong)puVar7 & 0xffffffffffff | 0x164a000000000000,lVar9,0x66703235,
                            lVar1,&local_90);
          if ((int)uVar4 != 0) goto LAB_251ace93c;
          func_0x00025810eae0(local_90,0,&local_70,0,&local_68);
          uVar4 = _Mib5yocT(3,&local_60,*plVar3,local_68,local_70 & 0xffffffff,&local_78,&local_7c,
                            &local_7d);
        } while ((int)uVar4 == 0);
      }
      uVar8 = 0xc2;
LAB_251ace94c:
      func_0x000258109a30(uVar4,"fpAuthentication_AuthenticateEndpoint",uVar8,0);
    }
    else {
      _fpAuthentication_AuthenticateEndpoint_cold_3();
    }
  }
  else {
    _fpAuthentication_AuthenticateEndpoint_cold_2();
  }
LAB_251ace954:
  if (local_88 != 0) {
    func_0x0002580f5830();
  }
  if (local_90 != 0) {
    func_0x0002580f5830();
  }
  if (local_78 != 0) {
    _jEHf8Xzsv8K();
    local_78 = 0;
  }
  if ((int)uVar4 != 0) {
    if (*plVar3 != 0) {
      _IPaI1oem5iL();
      *plVar3 = 0;
    }
    if ((_gLogCategory_APAuthenticationClientFairPlay < 0x3d) &&
       ((_gLogCategory_APAuthenticationClientFairPlay != -1 ||
        (iVar2 = func_0x000258101e40(&_gLogCategory_APAuthenticationClientFairPlay,0x200003c),
        iVar2 != 0)))) {
      _fpAuthentication_AuthenticateEndpoint_cold_5(uVar4);
    }
  }
  if (*_DAT_2681b4ee0 == local_48) {
    return uVar4;
  }
  uVar4 = func_0x0002580f4380();
  return uVar4;
}


/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2518d3704
 * original code SHA256: 5a042b3f44140c1375faf802d182a9dfc1cfb7a90ab75ec6e7e7c4ada80fae7b
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x0002518d39c8) */
/* WARNING: Removing unreachable block (ram,0x0002518d37c0) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _AirPlayReceiverSessionSetSecurityInfo
               (long param_1,undefined8 param_2,long param_3,long *param_4,int param_5,long param_6,
               long param_7)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uVar7;
  undefined1 *puVar8;
  code *pcVar9;
  undefined8 *puVar10;
  long lVar11;
  uint local_a0;
  int local_9c;
  undefined8 *local_98;
  ulong local_90;
  uint local_84;
  undefined1 auStack_80 [16];
  undefined8 local_70;
  undefined8 uStack_68;
  long local_58;
  
  local_58 = *_DAT_2681b4ee0;
  local_a0 = 0;
  lVar11 = *(long *)(param_1 + 0x1f0);
  if (param_3 != 0) {
    func_0x0002580f6a60(param_3);
  }
  *(long *)(param_1 + 0x1f0) = param_3;
  if (lVar11 != 0) {
    func_0x0002580f5830(lVar11);
    param_3 = *(long *)(param_1 + 0x1f0);
  }
  if (param_3 != 0) {
    lVar11 = func_0x000258109150(param_3);
    puVar10 = (undefined8 *)(*(long *)(lVar11 + 0x10) + 0x20);
    pcVar9 = (code *)*puVar10;
    if (((pcVar9 != (code *)0x0) && (pcVar9 != (code *)0x0)) &&
       (iVar2 = (*pcVar9)((ulong)puVar10 & 0xffffffffffff | 0xb441000000000000,param_3), iVar2 != 0)
       ) {
      uVar3 = 0;
      goto LAB_2518d3ad8;
    }
  }
  if ((param_6 == 0) || (param_7 == 0)) {
    iVar2 = func_0x00025810a6f0(param_2,&cfstringStruct_276118e70,&local_a0);
    if ((local_a0 == 0) && (iVar2 != 1)) {
      local_84 = 0;
      local_90 = 0;
      uVar4 = func_0x00025810a6b0(param_2,&cfstringStruct_2761199f0,0,0,&local_90,&local_84);
      uVar5 = (ulong)local_84;
      if (local_84 != 0) {
        uVar4 = 0x1571;
        goto LAB_2518d3a5c;
      }
      if ((iVar2 != 0x20) && (iVar2 != 8)) {
        if ((_gLogCategory_AirPlayReceiverCore < 0x3d) &&
           ((_gLogCategory_AirPlayReceiverCore != -1 ||
            (iVar2 = func_0x000258101e40(&_gLogCategory_AirPlayReceiverCore,0x200003c), iVar2 != 0))
           )) {
          func_0x000258101eb0(&_gLogCategory_AirPlayReceiverCore,
                              "OSStatus _GetDecryptKey(AirPlayReceiverSessionRef, CFDictionaryRef, FPSAPContextRef *, int, AirPlayEncryptionType, uint8_t *, uint8_t *)"
                              ,0x200003c,"Bad ET: %d\n");
        }
        local_a0 = 0xffffe5cf;
LAB_2518d3b2c:
        func_0x000258109a30(local_a0,"AirPlayReceiverSessionSetSecurityInfo",0x5e0,0);
        uVar3 = 0xffffe59e;
        goto LAB_2518d3ad8;
      }
      local_98 = (undefined8 *)0x0;
      local_9c = 0;
      if ((param_4 == (long *)0x0) || (*param_4 == 0)) {
        func_0x000258109a30(0,"_GetDecryptKey",0x157a,0);
        local_84 = 0xffffe59e;
LAB_2518d3a64:
        local_a0 = local_84;
        if (local_84 != 0) goto LAB_2518d3b2c;
      }
      else {
        uVar5 = _OowSGu(*param_4,uVar4,local_90 & 0xffffffff,&local_98,&local_9c);
        local_84 = (uint)uVar5;
        if (local_84 != 0) {
          if (*param_4 != 0) {
            _IPaI1oem5iL(*param_4);
            *param_4 = 0;
            uVar5 = (ulong)local_84;
            if (local_84 == 0) goto LAB_2518d38c4;
          }
          uVar4 = 0x157d;
LAB_2518d3a5c:
          func_0x000258109a30(uVar5,"_GetDecryptKey",uVar4,0);
          goto LAB_2518d3a64;
        }
LAB_2518d38c4:
        if (local_9c == 0x10) {
          local_84 = 0;
          uStack_68 = local_98[1];
          local_70 = *local_98;
        }
        else {
          local_84 = 0xffffe5a9;
        }
        _jEHf8Xzsv8K();
        uVar5 = (ulong)local_84;
        if (local_84 != 0) {
          uVar4 = 0x1589;
          goto LAB_2518d3a5c;
        }
        lVar11 = func_0x00025810a8d0(*(undefined8 *)(*(long *)(param_1 + 0x28) + 0xa0),0,
                                     _APReceiverSystemInfoCopyProperty,1,&cfstringStruct_276114350,0
                                     ,0);
        iVar2 = local_9c;
        if (((param_5 != 0) || (lVar11 != 0)) && (lVar11 = *(long *)(param_1 + 0x1f0), lVar11 != 0))
        {
          lVar6 = func_0x000258109150(lVar11);
          puVar10 = (undefined8 *)(*(long *)(lVar6 + 0x10) + 0x18);
          pcVar9 = (code *)*puVar10;
          if ((pcVar9 == (code *)0x0) || (pcVar9 == (code *)0x0)) {
            uVar5 = 0xffffce12;
            local_84 = 0xffffce12;
          }
          else {
            uVar5 = (*pcVar9)((ulong)puVar10 & 0xffffffffffff | 0x71e1000000000000,lVar11,&local_70,
                              iVar2,0,0,0x10,&local_70);
            local_84 = (uint)uVar5;
            if (local_84 == 0) goto LAB_2518d39fc;
          }
          uVar4 = 0x1590;
          goto LAB_2518d3a5c;
        }
LAB_2518d39fc:
        func_0x00025810a6b0(param_2,&cfstringStruct_276119a10,auStack_80,0x10,&local_90,&local_84);
        uVar5 = (ulong)local_84;
        if (local_84 != 0) {
          uVar4 = 0x159d;
          goto LAB_2518d3a5c;
        }
        if (local_90 != 0x10) {
          func_0x000258109a30(0,"_GetDecryptKey",0x159e,0);
          local_a0 = 0xffffe5a9;
          goto LAB_2518d3b2c;
        }
        local_a0 = 0;
      }
      uVar4 = __SetSecurityInfoAES(param_1,&local_70,auStack_80);
      local_a0 = (uint)uVar4;
      lVar11 = -0x10;
      puVar10 = &local_70;
      do {
        *(undefined1 *)puVar10 = 0;
        bVar1 = lVar11 != -1;
        lVar11 = lVar11 + 1;
        puVar10 = (undefined8 *)((long)puVar10 + 1);
      } while (bVar1);
      lVar11 = -0x10;
      puVar8 = auStack_80;
      do {
        *puVar8 = 0;
        bVar1 = lVar11 != -1;
        lVar11 = lVar11 + 1;
        puVar8 = puVar8 + 1;
      } while (bVar1);
      if (local_a0 != 0) {
        uVar7 = 0x5e4;
        goto LAB_2518d3b88;
      }
    }
    local_a0 = 0;
  }
  else {
    uVar4 = __SetSecurityInfoAES(param_1,param_6,param_7);
    local_a0 = (uint)uVar4;
    if (local_a0 != 0) {
      uVar7 = 0x5d6;
LAB_2518d3b88:
      func_0x000258109a30(uVar4,"AirPlayReceiverSessionSetSecurityInfo",uVar7,0);
      uVar3 = 0xffffe596;
      goto LAB_2518d3ad8;
    }
  }
  func_0x00025810a750(param_2,&cfstringStruct_2761199f0);
  func_0x00025810a750(param_2,&cfstringStruct_276119a10);
  uVar3 = local_a0;
LAB_2518d3ad8:
  if (*_DAT_2681b4ee0 == local_58) {
    return;
  }
  func_0x0002580f4380(uVar3);
  return;
}


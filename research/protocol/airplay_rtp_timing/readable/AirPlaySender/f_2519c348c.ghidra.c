/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519c348c
 * original code SHA256: a7b8d9332428672e2f99e64749eac347f047352358426c4d2a003dfb8c86199e
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
_APSRTPPacketHandlerComposeRTPPacketWithBBuf
          (long param_1,byte *param_2,ulong param_3,int *param_4,int *param_5,int *param_6)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  int *piVar8;
  ulong uVar9;
  uint uVar10;
  int iVar11;
  ulong uVar12;
  uint *puVar13;
  uint *puVar14;
  ulong local_a8;
  long local_a0;
  int local_98;
  int local_94;
  undefined8 local_90;
  undefined2 local_88;
  undefined8 local_80;
  uint *local_78;
  ulong local_70;
  ulong local_68;
  
  local_80 = 0;
  local_78 = (uint *)0x0;
  uVar4 = func_0x00025810ecd0(*(undefined8 *)(param_1 + 0x60));
  local_88 = 0;
  local_90 = 0;
  local_94 = 0;
  if ((*(byte *)(param_1 + 0x18) & 1) == 0) {
    _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_17();
    uVar7 = 0xffffe5b1;
    goto LAB_2519c3984;
  }
  if (param_4 == (int *)0x0) {
    _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_16();
  }
  else if (param_2 == (byte *)0x0) {
    _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_15();
  }
  else {
    if (param_5 != (int *)0x0) {
      *param_5 = 0;
      uVar7 = func_0x00025810dfc0(*(undefined8 *)(param_2 + 0x10),&local_90);
      if ((int)uVar7 == 0) {
        uVar7 = func_0x00025810e050(*(undefined8 *)(param_4 + 2),&local_90);
        if ((int)uVar7 == 0) {
          *param_4 = *(int *)param_2;
          uVar7 = func_0x00025810dff0(*(undefined8 *)(param_2 + 0x10),&local_94);
          if ((int)uVar7 == 0) {
            uVar7 = func_0x00025810dfd0(*(undefined8 *)(param_4 + 2),&local_78,&local_80);
            puVar14 = local_78;
            if ((int)uVar7 == 0) {
              if (*(uint *)(param_1 + 0x1c) < 2) {
                iVar6 = 1;
                iVar11 = 10;
              }
              else {
                iVar6 = *(int *)param_2;
                if (iVar6 < 0x65) {
                  if (iVar6 == 0x60) {
                    iVar6 = 0x61;
                  }
                  else if (iVar6 == 100) {
                    iVar6 = 0x68;
                  }
                }
                else if (iVar6 == 0x65) {
                  iVar6 = 0x69;
                }
                else if (iVar6 == 0x6a) {
                  iVar6 = 0x6c;
                }
                *param_4 = iVar6;
                if (*(int *)(param_1 + 0x98) == 0) {
                  iVar11 = 0;
                }
                else {
                  local_68 = 0;
                  local_70 = 0;
                  func_0x00025810dfd0(*(undefined8 *)(param_2 + 8),0,&local_68);
                  func_0x00025810dfd0(*(undefined8 *)(param_2 + 0x10),0,&local_70);
                  uVar9 = local_70;
                  uVar10 = *(uint *)(param_1 + 0x94);
                  if (*(int *)(param_1 + 0x98) != 0) {
                    uVar10 = (*(int *)(param_1 + 0x98) + uVar10) - 1;
                    uVar1 = *(uint *)(param_1 + 0x90);
                    uVar2 = 0;
                    if (uVar1 != 0) {
                      uVar2 = uVar10 / uVar1;
                    }
                    uVar10 = uVar10 - uVar2 * uVar1;
                  }
                  uVar12 = (ulong)uVar10;
                  _QueueIsIndexInRange(param_1 + 0x68,uVar12);
                  local_70 = (ulong)*(uint *)(*(long *)(param_1 + 0x88) + uVar12 * 4);
                  uVar9 = (param_3 & 0xffffffff) + uVar9 + local_70 + 5;
                  if (local_68 < uVar9) {
                    iVar11 = 0;
                  }
                  else {
                    iVar6 = 1;
                    do {
                      iVar11 = iVar6;
                      iVar6 = (int)uVar12;
                      iVar5 = _QueueIsIndexInRange(param_1 + 0x68,uVar12);
                      if ((iVar5 == 0) || (iVar6 == *(int *)(param_1 + 0x94))) break;
                      if (iVar6 == 0) {
                        iVar6 = *(int *)(param_1 + 0x90);
                      }
                      uVar12 = (ulong)(iVar6 - 1);
                      _QueueIsIndexInRange(param_1 + 0x68,uVar12);
                      local_70 = (ulong)*(uint *)(*(long *)(param_1 + 0x88) + uVar12 * 4);
                      uVar9 = uVar9 + local_70 + 4;
                      iVar6 = iVar11 + 1;
                    } while (uVar9 <= local_68);
                  }
                }
                iVar6 = 1;
                uVar9 = (ulong)(iVar11 << 2 | 1);
                param_3 = param_3 + uVar9;
                local_78 = (uint *)((long)local_78 + uVar9);
                if (uVar4 != 0) {
                  uVar10 = 0;
                  puVar13 = puVar14;
                  do {
                    piVar8 = (int *)func_0x00025810ecb0(*(undefined8 *)(param_1 + 0x60));
                    if (piVar8 == (int *)0x0) {
                      _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_7();
                      return 0;
                    }
                    puVar14 = puVar13;
                    if (uVar4 - iVar11 <= uVar10) {
                      local_68 = 0;
                      local_70 = 0;
                      local_98 = 0;
                      uVar7 = func_0x00025810dfd0(*(undefined8 *)(piVar8 + 4),&local_70,&local_68);
                      if ((int)uVar7 != 0) {
                        _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_5();
                        goto LAB_2519c3984;
                      }
                      uVar7 = func_0x00025810dff0(*(undefined8 *)(piVar8 + 4),&local_98);
                      if ((int)uVar7 != 0) {
                        _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_6();
                        goto LAB_2519c3984;
                      }
                      uVar1 = (local_94 - local_98 & 0x3fffU) << 10 | *piVar8 << 0x18 |
                              (uint)local_68 & 0x3ff;
                      uVar1 = (uVar1 & 0xff00ff00 | 0x80000000) >> 8 | (uVar1 & 0xff00ff) << 8;
                      puVar14 = puVar13 + 1;
                      *puVar13 = uVar1 >> 0x10 | uVar1 << 0x10;
                      func_0x0002580f43e0(local_78,local_70);
                      local_78 = (uint *)((long)local_78 + local_68);
                      param_3 = local_68 + param_3;
                      iVar6 = iVar6 + 1;
                    }
                    if ((uVar10 == 0) && (uVar4 == *(int *)(param_1 + 0x1c) - 1U)) {
                      _APSRTPPacketHandlerReturnBBuf(param_1,piVar8);
                      uVar1 = *(uint *)(param_1 + 0x98);
                      if ((uVar1 != 0) && (uVar1 == *(uint *)(param_1 + 0x90))) {
                        uVar2 = *(int *)(param_1 + 0x94) + 1;
                        uVar3 = 0;
                        if (uVar1 != 0) {
                          uVar3 = uVar2 / uVar1;
                        }
                        *(uint *)(param_1 + 0x94) = uVar2 - uVar3 * uVar1;
                        *(uint *)(param_1 + 0x98) = uVar1 - 1;
                      }
                    }
                    else {
                      func_0x00025810ecc0(*(undefined8 *)(param_1 + 0x60),piVar8);
                    }
                    uVar10 = uVar10 + 1;
                    puVar13 = puVar14;
                  } while (uVar4 != uVar10);
                }
                iVar11 = iVar11 * 4 + 0xb;
                *(byte *)puVar14 = *param_2 & 0x7f;
              }
              local_a8 = 0;
              local_a0 = 0;
              uVar7 = func_0x00025810dfd0(*(undefined8 *)(param_2 + 0x10),&local_a0,&local_a8);
              if ((int)uVar7 == 0) {
                if (local_a0 == 0) {
                  _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_13();
                }
                else {
                  if (local_a8 != 0) {
                    func_0x0002580f43e0(local_78);
                    uVar7 = func_0x00025810dfa0(*_DAT_2680d3150,*(undefined8 *)(param_4 + 2),
                                                local_a8 + param_3,param_4 + 4);
                    if ((int)uVar7 == 0) {
                      if (*(long *)(param_4 + 4) != 0) {
                        *param_5 = iVar11;
                        if (*(uint *)(param_1 + 0x1c) < 2) {
                          _APSRTPPacketHandlerReturnBBuf(param_1,param_2);
                        }
                        else {
                          uVar7 = func_0x00025810ecc0(*(undefined8 *)(param_1 + 0x60),param_2);
                          if ((int)uVar7 != 0) {
                            _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_10();
                            goto LAB_2519c3984;
                          }
                          _QueueAddEntry(param_1 + 0x68,local_a8 & 0xffffffff);
                        }
                        if (param_6 == (int *)0x0) {
                          return 0;
                        }
                        *param_6 = iVar6;
                        return 0;
                      }
                      _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_11();
                      uVar7 = 0xffffe5b8;
                    }
                    else {
                      _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_9();
                    }
                    goto LAB_2519c3984;
                  }
                  _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_12();
                }
                uVar7 = 0xffffe5b9;
              }
              else {
                _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_8();
              }
            }
            else {
              _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_4();
            }
          }
          else {
            _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_3();
          }
        }
        else {
          _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_2();
        }
      }
      else {
        _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_1();
      }
      goto LAB_2519c3984;
    }
    _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_14();
  }
  uVar7 = 0xffffe5cf;
LAB_2519c3984:
  if ((_gLogCategory_APSRTPPacketHandler < 0x5b) &&
     ((_gLogCategory_APSRTPPacketHandler != -1 ||
      (iVar6 = func_0x000258101e40(&_gLogCategory_APSRTPPacketHandler,0x5a), iVar6 != 0)))) {
    _APSRTPPacketHandlerComposeRTPPacketWithBBuf_cold_18(uVar7);
  }
  if (param_2 != (byte *)0x0) {
    _APSRTPPacketHandlerReturnBBuf(param_1,param_2);
  }
  return uVar7;
}


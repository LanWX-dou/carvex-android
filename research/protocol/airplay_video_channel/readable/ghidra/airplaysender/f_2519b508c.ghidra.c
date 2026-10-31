/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2519b508c
 * original code SHA256: bf74ed3511dceffa8be66a9e35c94e18d9b3aba4922163b80dfc01f6f8c4aeae
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x0002519b5190) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _sbpd_encryptBBuf(long param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  undefined8 extraout_x1;
  undefined8 extraout_x1_00;
  undefined8 extraout_x1_01;
  undefined8 uVar7;
  code *pcVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  undefined8 unaff_x30;
  undefined1 auVar11 [16];
  long local_90;
  long local_88;
  long local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 uStack_68;
  
  local_70 = 0;
  uStack_68 = 0;
  local_80 = 0;
  local_78 = 0;
  local_90 = 0;
  local_88 = 0;
  if (*(long *)(param_1 + 0x198) == 0) {
    uVar4 = 0;
    goto LAB_2519b5268;
  }
  uVar4 = func_0x00025810eae0(param_2,0,&local_70,0,&uStack_68);
  if ((int)uVar4 == 0) {
    uVar4 = func_0x00025810eae0(param_3,0,&local_80,&local_88,&local_78);
    if ((int)uVar4 != 0) {
      auVar11 = _OUTLINED_FUNCTION_30();
      uVar7 = 0x3b2;
      goto LAB_2519b52a4;
    }
    if (local_80 != local_88) {
      _OUTLINED_FUNCTION_30();
      func_0x000258109a30(0,extraout_x1_01,0x3b4,0);
      uVar4 = 0xffffbe88;
      goto LAB_2519b525c;
    }
    if (*(long *)(param_1 + 0x1a0) == 0) {
      uVar4 = 0;
      lVar5 = 0;
    }
    else {
      lVar5 = func_0x0002580f6280(1,*(long *)(param_1 + 0x1a0),0x7b0dff91);
      uVar4 = *(undefined8 *)(param_1 + 0x1a0);
    }
    uVar3 = uStack_68;
    uVar2 = local_70;
    uVar7 = local_78;
    lVar1 = local_80;
    uVar10 = *(undefined8 *)(param_1 + 0x198);
    lVar6 = func_0x000258109150(uVar10);
    puVar9 = (undefined8 *)(*(long *)(lVar6 + 0x10) + 0x10);
    pcVar8 = (code *)*puVar9;
    if ((pcVar8 == (code *)0x0) || (pcVar8 == (code *)0x0)) {
      uVar4 = 0xffffce12;
LAB_2519b5234:
      _OUTLINED_FUNCTION_30();
      func_0x000258109a30(uVar4,extraout_x1_00,0x3bc,0);
      if (lVar5 != 0) {
LAB_2519b524c:
        func_0x0002580f4d30(lVar5);
      }
    }
    else {
      uVar4 = (*pcVar8)((ulong)puVar9 & 0xffffffffffff | 0xd5d000000000000,uVar10,uVar3,uVar2,uVar7,
                        lVar1,uVar7,lVar1,lVar5,uVar4);
      if ((int)uVar4 != 0) goto LAB_2519b5234;
      if (lVar5 != 0) {
        uVar4 = _OUTLINED_FUNCTION_13();
        uVar4 = func_0x00025810ac90(uVar4,lVar5,*(undefined8 *)(param_1 + 0x1a0),*_DAT_2680d3160,0,0
                                    ,*(undefined8 *)(param_1 + 0x1a0),0,&local_90);
        if ((int)uVar4 == 0) {
          _OUTLINED_FUNCTION_100(param_3,local_90);
          uVar4 = func_0x00025810eab0();
          if ((int)uVar4 != 0) {
            _OUTLINED_FUNCTION_30();
            auVar11._8_8_ = extraout_x1;
            auVar11._0_8_ = uVar4;
            uVar7 = 0x3c5;
            goto LAB_2519b52a4;
          }
          goto LAB_2519b525c;
        }
        auVar11 = _OUTLINED_FUNCTION_30();
        func_0x000258109a30(auVar11._0_8_,auVar11._8_8_,0x3c1,0);
        goto LAB_2519b524c;
      }
      uVar4 = 0;
    }
  }
  else {
    auVar11 = _OUTLINED_FUNCTION_30();
    uVar7 = 0x3af;
LAB_2519b52a4:
    func_0x000258109a30(auVar11._0_8_,auVar11._8_8_,uVar7,0);
  }
LAB_2519b525c:
  if (local_90 != 0) {
    func_0x0002580f5830();
  }
LAB_2519b5268:
  _OUTLINED_FUNCTION_55(uVar4,unaff_x30);
  return;
}


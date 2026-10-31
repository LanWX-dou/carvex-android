/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x251b43fcc
 * original code SHA256: c706decdcd0e1212d9edf7b01eecf6e8e08fe728bfa95420288f8903a67ba38a
 * source SHA256: 304b8a4a688028f58fc851ec700c905a49f17132aaa9dc04acd93a8bd50cd63f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */


/* WARNING: Removing unreachable block (ram,0x000251b4413c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 _sbpd_createConfigBBuf(long *param_1,long *param_2)

{
  undefined8 *puVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  undefined4 *puVar5;
  long lVar6;
  byte bVar7;
  long lVar8;
  ulong uVar9;
  long lVar10;
  code *pcVar11;
  ulong uVar12;
  undefined8 *puVar13;
  long lVar14;
  long local_78;
  long local_70;
  undefined8 local_68;
  ulong local_60;
  ulong local_58;
  
  puVar1 = _DAT_2680d3150;
  local_78 = 0;
  local_70 = 0;
  if (*param_1 == 0) {
    if (param_1[1] == 0) {
      lVar3 = 0;
    }
    else {
      uVar4 = func_0x00025810e0d0(param_1[1],&local_78);
      if ((int)uVar4 != 0) {
        _sbpd_createConfigBBuf_cold_2();
        goto LAB_251b44290;
      }
      lVar3 = func_0x00025810aca0(local_78);
    }
  }
  else {
    lVar3 = func_0x0002580f6a40();
    uVar4 = func_0x00025810f290(*puVar1,*param_1,0,lVar3,&local_78);
    if ((int)uVar4 != 0) {
      _sbpd_createConfigBBuf_cold_1();
      goto LAB_251b44290;
    }
  }
  puVar5 = (undefined4 *)func_0x0002580f6280(1,0x80,0x9329c86f);
  *puVar5 = (int)lVar3;
  *(undefined1 *)(puVar5 + 1) = 1;
  *(char *)((long)puVar5 + 5) = (char)(int)param_1[0xc];
  *(undefined1 *)((long)puVar5 + 6) = 0x12;
  bVar7 = 0x12;
  if (*(char *)((long)param_1 + 0x1bc) != '\0') {
    bVar7 = 0x13;
  }
  *(byte *)((long)puVar5 + 6) = bVar7;
  if (param_1[0x33] != 0) {
    bVar7 = bVar7 | 4;
    *(byte *)((long)puVar5 + 6) = bVar7;
  }
  if (*(char *)((long)param_1 + 100) != '\0') {
    bVar7 = bVar7 | 0x40;
    *(byte *)((long)puVar5 + 6) = bVar7;
  }
  if (param_1[1] != 0) {
    *(byte *)((long)puVar5 + 6) = bVar7 | 8;
  }
  *(undefined1 *)((long)puVar5 + 7) = 1;
  lVar8 = param_1[0x3a];
  lVar10 = param_1[0x36];
  local_60 = 0;
  local_58 = 0;
  local_68 = 0;
  if (lVar10 + lVar8 == 0) {
LAB_251b4416c:
    uVar9 = 0;
    uVar12 = 0;
  }
  else {
    lVar14 = param_1[0x39];
    lVar6 = func_0x000258109150(lVar14);
    puVar13 = (undefined8 *)(*(long *)(lVar6 + 0x10) + 0x10);
    pcVar11 = (code *)*puVar13;
    if (pcVar11 == (code *)0x0) {
      uVar9 = 0;
      uVar12 = 0;
    }
    else {
      if (pcVar11 == (code *)0x0) goto LAB_251b4416c;
      (*pcVar11)((ulong)puVar13 & 0xffffffffffff | 0xea2e000000000000,lVar14,lVar10 + lVar8,
                 &local_68);
      uVar9 = local_58 & 0xffffffff;
      uVar12 = local_60;
    }
  }
  *(ulong *)(puVar5 + 2) = uVar12 >> 0x20 | uVar9 << 0x20;
  puVar5[4] = (float)(double)param_1[2];
  puVar5[5] = (float)(double)param_1[3];
  puVar5[8] = (float)(double)param_1[4];
  puVar5[9] = (float)(double)param_1[5];
  puVar5[10] = (float)(double)param_1[6];
  puVar5[0xb] = (float)(double)param_1[7];
  puVar5[0xc] = (float)(double)param_1[8];
  puVar5[0xd] = (float)(double)param_1[9];
  puVar5[0xe] = (float)(double)param_1[10];
  puVar5[0xf] = (float)(double)param_1[0xb];
  uVar4 = func_0x00025810ac90(*puVar1,puVar5,0x80,*_DAT_2680d3160,0,0,0x80,0,&local_70);
  if ((int)uVar4 == 0) {
    if (((*(char *)((long)param_1 + 100) != '\0') && (_gLogCategory_APEndpointStreamScreen < 0x29))
       && ((_gLogCategory_APEndpointStreamScreen != -1 ||
           (iVar2 = func_0x000258101e40(&_gLogCategory_APEndpointStreamScreen,0x2000028), iVar2 != 0
           )))) {
      _sbpd_createConfigBBuf_cold_4(param_1 + 0x35);
    }
    if ((lVar3 == 0) || (uVar4 = func_0x00025810eab0(local_70,local_78,0,0,0), (int)uVar4 == 0)) {
      uVar4 = 0;
      *param_2 = local_70;
      local_70 = 0;
    }
    else {
      _sbpd_createConfigBBuf_cold_5();
    }
  }
  else {
    _sbpd_createConfigBBuf_cold_3(uVar4,puVar5);
  }
LAB_251b44290:
  if (local_78 != 0) {
    func_0x0002580f5830();
  }
  if (local_70 != 0) {
    func_0x0002580f5830();
  }
  return uVar4;
}


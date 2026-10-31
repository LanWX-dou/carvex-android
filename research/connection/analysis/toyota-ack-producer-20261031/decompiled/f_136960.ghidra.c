/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x136960
 * original code SHA256: 94de56fb82bf9bf29a0bbeffb4073ef6c0c6cb68703485ccf97ce071de69fff0
 * source SHA256: f7f28e152d1791a38c91ee4495297c5ea078bd6f30386dcde121413f21d9a29f
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Type propagation algorithm not settling */
/* CIpodIap2::mediaLibraryUpdate(unsigned char const*) */

undefined8 __thiscall CIpodIap2::mediaLibraryUpdate(CIpodIap2 *this,uchar *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uchar *__src;
  undefined8 ******ppppppuVar4;
  undefined8 ******ppppppuVar5;
  long ******__n;
  int iVar6;
  bool bVar7;
  bool bVar8;
  long lVar9;
  char cVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  uchar *puVar14;
  _List_node_base *p_Var15;
  undefined8 uVar16;
  FILE *__s;
  undefined1 *puVar17;
  long lVar18;
  undefined8 ******ppppppuVar19;
  long ******pppppplVar20;
  ulong __size;
  char *pcVar21;
  long lVar22;
  undefined8 *******pppppppuVar23;
  char *pcVar24;
  undefined8 *******pppppppuVar25;
  long *******ppppppplVar26;
  long *******ppppppplVar27;
  ulong uVar28;
  long *******ppppppplVar29;
  char *pcVar30;
  CIap2Sqlite *this_00;
  undefined8 ******local_600;
  undefined8 ******local_5f8;
  undefined8 ******local_5f0;
  long ******local_5e8;
  undefined8 *******local_5e0;
  undefined8 *******pppppppuStack_5d8;
  long local_5d0;
  long *******local_5c8;
  long *******ppppppplStack_5c0;
  long local_5b8;
  long *******local_5b0;
  long *******local_5a8;
  long local_5a0;
  undefined8 *******pppppppuStack_598;
  undefined8 *******local_590;
  long local_588;
  undefined1 *local_580;
  char *local_578;
  undefined1 local_570 [16];
  undefined1 *local_560;
  undefined8 uStack_558;
  undefined1 local_550 [16];
  undefined4 local_540;
  undefined1 *local_538;
  char *local_530;
  undefined1 local_528 [16];
  CIpodIap2 local_518;
  undefined1 uStack_517;
  CIpodIap2 CStack_516;
  long ******local_510;
  long ******local_508;
  long ******local_500;
  long ******local_4f8 [2];
  long ******local_4e8;
  undefined8 ******local_4e0;
  undefined8 ******ppppppuStack_4d8;
  undefined1 *local_4d0 [2];
  undefined1 auStack_4c0 [16];
  undefined8 ******local_4b0;
  undefined8 ******local_4a8;
  undefined1 *local_4a0 [2];
  undefined1 auStack_490 [16];
  undefined8 ******local_480;
  undefined8 ******local_478;
  undefined8 ******local_470;
  undefined8 ******local_468 [2];
  undefined8 ******local_458;
  undefined8 ******local_450;
  undefined8 ******local_448;
  undefined8 ******local_440 [2];
  undefined8 ******local_430;
  undefined8 ******local_428;
  undefined8 ******local_420;
  undefined8 ******local_418 [2];
  undefined1 local_408;
  undefined1 local_407;
  undefined1 local_406;
  undefined1 local_405;
  undefined1 local_404;
  undefined1 local_403;
  undefined2 local_402;
  undefined8 local_400;
  undefined1 *local_3f8;
  long local_3f0;
  undefined1 local_3e8 [16];
  undefined8 local_3d8;
  undefined8 local_3d0;
  undefined8 uStack_3c8;
  undefined1 *local_3c0;
  long local_3b8;
  undefined1 local_3b0 [16];
  undefined8 local_3a0;
  undefined8 local_398;
  undefined1 *local_390;
  long local_388;
  undefined1 local_380 [16];
  undefined8 local_370;
  undefined1 *local_368;
  long local_360;
  undefined1 local_358 [16];
  undefined8 local_348;
  undefined1 *local_340;
  long local_338;
  undefined1 local_330 [16];
  undefined8 local_320;
  undefined1 *local_318;
  long local_310;
  undefined1 local_308 [16];
  _List_node_base local_2f8;
  _List_node_base local_2f7;
  _List_node_base local_2f6;
  _List_node_base local_2f5;
  _List_node_base local_2f4;
  _List_node_base local_2f3;
  undefined2 local_2f2;
  
  puVar17 = local_570;
  local_560 = local_550;
  local_538 = local_528;
  local_570[0] = 0;
  local_550[0] = 0;
  uVar1 = (uint)param_1[2] * 0x100 + (uint)param_1[3];
  local_528[0] = 0;
  local_518 = (CIpodIap2)0x0;
  uStack_517 = 0;
  local_5d0 = 0;
  local_578 = (char *)0x0;
  uStack_558 = 0;
  local_540 = 0;
  local_530 = (char *)0x0;
  CStack_516 = (CIpodIap2)0x1;
  local_5b8 = 0;
  local_5a0 = 0;
  local_588 = 0;
  local_5e0 = &local_5e0;
  pppppppuStack_5d8 = &local_5e0;
  local_5c8 = (long *******)&local_5c8;
  ppppppplStack_5c0 = (long *******)&local_5c8;
  local_5b0 = (long *******)&local_5b0;
  local_5a8 = (long *******)&local_5b0;
  pppppppuStack_598 = &pppppppuStack_598;
  local_590 = &pppppppuStack_598;
  local_580 = puVar17;
  if (uVar1 < 7) {
    pcVar30 = (char *)0x0;
    pcVar21 = *(char **)(this + 0x808);
    bVar7 = false;
    bVar8 = false;
    iVar6 = 0;
LAB_00136c08:
    lVar22 = (long)pcVar30 - (long)pcVar21;
    iVar11 = 0x7fffffff;
    if ((lVar22 < 0x80000000) &&
       ((iVar11 = -0x80000000, -0x80000001 < lVar22 && (iVar11 = (int)lVar22, iVar11 == 0)))) {
      this_00 = (CIap2Sqlite *)(this + 0x870);
      local_540 = 0;
      if ((this[0x868] != (CIpodIap2)0x64) ||
         (((((long ********)local_5b0 != &local_5b0 ||
            ((undefined8 ********)pppppppuStack_598 != &pppppppuStack_598)) ||
           ((long ********)local_5c8 != &local_5c8)) || (bVar8)))) {
LAB_00136c40:
        this[0x868] = local_518;
        uVar12 = CIpodProtocol::getHandle((CIpodProtocol *)this);
        CIpodEvent::sendEvent(10,uVar12,this[0x868]);
      }
      else {
        if ((undefined8 ********)local_5e0 != &local_5e0) {
          pppppppuVar23 = local_5e0;
          do {
            IAP2MediaItem::IAP2MediaItem
                      ((IAP2MediaItem *)&local_400,(IAP2MediaItem *)(pppppppuVar23 + 2));
            cVar10 = CIap2Sqlite::isItemExist(this_00,(IAP2MediaItem *)&local_400);
            IAP2MediaItem::~IAP2MediaItem((IAP2MediaItem *)&local_400);
            if (cVar10 == '\0') goto LAB_00136c40;
            pppppppuVar23 = (undefined8 *******)*pppppppuVar23;
          } while ((undefined8 ********)pppppppuVar23 != &local_5e0);
        }
        this[0x868] = local_518;
      }
      std::__cxx11::string::_M_assign((string *)(this + 0x848));
      if (bVar7) {
        this[0x86a] = CStack_516;
      }
      goto LAB_00136c80;
    }
  }
  else {
    uVar28 = 6;
    bVar7 = false;
    bVar8 = false;
    iVar6 = 0;
    do {
      while( true ) {
        iVar11 = (int)uVar28;
        __src = param_1 + uVar28;
        uVar2 = (uint)__src[2] * 0x100 + (uint)param_1[(long)(iVar11 + 2) + 1];
        uVar3 = (uint)__src[1] + (uint)param_1[uVar28] * 0x100;
        __size = (ulong)uVar3;
        if (uVar2 != 4) break;
        if ((int)(uVar3 - 4) < 1) {
          lVar22 = 0;
        }
        else {
          lVar22 = 0;
          lVar18 = 0;
          do {
            lVar9 = lVar18 + (iVar11 + 4);
            lVar18 = lVar18 + 1;
            lVar22 = (ulong)param_1[lVar9] + lVar22 * 0x100;
          } while (lVar18 < (int)(uVar3 - 4));
        }
        p_Var15 = operator_new(0x18);
        *(long *)(p_Var15 + 0x10) = lVar22;
        std::__detail::_List_node_base::_M_hook(p_Var15);
        local_5a0 = local_5a0 + 1;
LAB_00136a5c:
        uVar2 = uVar3 + iVar11 & 0xffff;
        uVar28 = (ulong)uVar2;
        if (uVar1 <= uVar2) goto LAB_00136be0;
      }
      if (4 < uVar2) {
        if (uVar2 == 7) {
          local_518 = *(CIpodIap2 *)(__src + 4);
        }
        else if (uVar2 < 8) {
          if (uVar2 == 5) {
            if ((int)(uVar3 - 4) < 1) {
              lVar22 = 0;
            }
            else {
              lVar22 = 0;
              lVar18 = 0;
              do {
                lVar9 = lVar18 + (iVar11 + 4);
                lVar18 = lVar18 + 1;
                lVar22 = (ulong)param_1[lVar9] + lVar22 * 0x100;
              } while (lVar18 < (int)(uVar3 - 4));
            }
            p_Var15 = operator_new(0x18);
            *(long *)(p_Var15 + 0x10) = lVar22;
            std::__detail::_List_node_base::_M_hook(p_Var15);
            local_588 = local_588 + 1;
          }
          else if (uVar2 == 6) {
            bVar8 = true;
          }
        }
        else if (uVar2 == 8) {
          uStack_517 = __src[4] != '\0';
        }
        else if (uVar2 == 9) {
          bVar7 = true;
          CStack_516 = (CIpodIap2)(__src[4] != '\0');
        }
        goto LAB_00136a5c;
      }
      if (uVar2 == 1) {
        if (4 < uVar3) {
          lVar22 = -((long)(int)(uVar3 - 4) + 0xfU & 0xfffffffffffffff0);
          memcpy(&stack0xfffffffffffff930 + lVar22,param_1 + uVar28 + 4,(long)(int)(uVar3 - 4));
          strlen(&stack0xfffffffffffff930 + lVar22);
          std::__cxx11::string::_M_replace
                    ((ulong)&local_538,0,local_530,(ulong)(&stack0xfffffffffffff930 + lVar22));
        }
        goto LAB_00136a5c;
      }
      if (uVar2 == 0) {
        if (4 < uVar3) {
          lVar22 = -((long)(int)(uVar3 - 4) + 0xfU & 0xfffffffffffffff0);
          memcpy(&stack0xfffffffffffff930 + lVar22,param_1 + uVar28 + 4,(long)(int)(uVar3 - 4));
          strlen(&stack0xfffffffffffff930 + lVar22);
          std::__cxx11::string::_M_replace
                    ((ulong)&local_580,0,local_578,(ulong)(&stack0xfffffffffffff930 + lVar22));
        }
        goto LAB_00136a5c;
      }
      if (uVar2 == 2) {
        puVar14 = malloc(__size);
        memcpy(puVar14,__src,__size);
        local_3e8[0] = 0;
        local_3c0 = local_3b0;
        local_390 = local_380;
        local_368 = local_358;
        local_340 = local_330;
        local_3b0[0] = 0;
        local_318 = local_308;
        local_380[0] = 0;
        local_358[0] = 0;
        local_330[0] = 0;
        local_308[0] = 0;
        uStack_3c8 = 0;
        local_3d0 = 0;
        local_2f8 = (_List_node_base)0x0;
        local_2f7 = (_List_node_base)0x0;
        local_2f6 = (_List_node_base)0x0;
        local_2f5 = (_List_node_base)0x0;
        local_400 = 0;
        local_3f0 = 0;
        local_3d8 = local_3d8 & 0xffffff0000000000;
        local_3b8 = 0;
        local_3a0 = 0;
        local_398 = 0;
        local_388 = 0;
        local_370 = 0;
        local_360 = 0;
        local_348 = 0;
        local_338 = 0;
        local_320 = 0;
        local_310 = 0;
        local_2f4 = (_List_node_base)0x0;
        local_2f3 = (_List_node_base)0x0;
        local_2f2 = 0;
        local_3f8 = local_3e8;
        parseMediaLibraryItem(this,puVar14,(ushort)uVar3,(IAP2MediaItem *)&local_400);
        p_Var15 = operator_new(0x120);
        *(undefined8 *)(p_Var15 + 0x10) = local_400;
        *(_List_node_base **)(p_Var15 + 0x18) = p_Var15 + 0x28;
        FUN_00128218(p_Var15 + 0x18,local_3f8,local_3f8 + local_3f0);
        *(undefined4 *)(p_Var15 + 0x38) = (undefined4)local_3d8;
        p_Var15[0x3c] = local_3d8._4_1_;
        *(_List_node_base **)(p_Var15 + 0x50) = p_Var15 + 0x60;
        *(undefined8 *)(p_Var15 + 0x48) = uStack_3c8;
        *(ulong *)(p_Var15 + 0x40) = local_3d0;
        FUN_00128218(p_Var15 + 0x50,local_3c0,local_3c0 + local_3b8);
        *(undefined8 *)(p_Var15 + 0x70) = local_3a0;
        *(undefined8 *)(p_Var15 + 0x78) = local_398;
        *(_List_node_base **)(p_Var15 + 0x80) = p_Var15 + 0x90;
        FUN_00128218(p_Var15 + 0x80,local_390,local_390 + local_388);
        *(undefined8 *)(p_Var15 + 0xa0) = local_370;
        *(_List_node_base **)(p_Var15 + 0xa8) = p_Var15 + 0xb8;
        FUN_00128218(p_Var15 + 0xa8,local_368,local_368 + local_360);
        *(undefined8 *)(p_Var15 + 200) = local_348;
        *(_List_node_base **)(p_Var15 + 0xd0) = p_Var15 + 0xe0;
        FUN_00128218(p_Var15 + 0xd0,local_340,local_340 + local_338);
        *(undefined8 *)(p_Var15 + 0xf0) = local_320;
        *(_List_node_base **)(p_Var15 + 0xf8) = p_Var15 + 0x108;
        FUN_00128218(p_Var15 + 0xf8,local_318,local_318 + local_310);
        p_Var15[0x118] = local_2f8;
        p_Var15[0x119] = local_2f7;
        p_Var15[0x11a] = local_2f6;
        p_Var15[0x11b] = local_2f5;
        p_Var15[0x11c] = local_2f4;
        p_Var15[0x11d] = local_2f3;
        *(undefined2 *)(p_Var15 + 0x11e) = local_2f2;
        std::__detail::_List_node_base::_M_hook(p_Var15);
        local_5d0 = local_5d0 + 1;
        free(puVar14);
        if (local_318 != local_308) {
          operator_delete(local_318);
        }
        if (local_340 != local_330) {
          operator_delete(local_340);
        }
        if (local_368 != local_358) {
          operator_delete(local_368);
        }
        if (local_390 != local_380) {
          operator_delete(local_390);
        }
        if (local_3c0 != local_3b0) {
          operator_delete(local_3c0);
        }
        if (local_3f8 != local_3e8) {
          operator_delete(local_3f8);
        }
        goto LAB_00136a5c;
      }
      if (uVar2 != 3) goto LAB_00136a5c;
      puVar14 = malloc(__size);
      memcpy(puVar14,__src,__size);
      local_3e8[0] = 0;
      local_3d0 = local_3d0 & 0xffffffff00000000;
      local_400 = 0;
      local_3f0 = 0;
      local_3d8 = 0;
      local_3f8 = local_3e8;
      parseMediaLibraryPlaylist(this,puVar14,(ushort)uVar3,(IAP2MediaPlaylist *)&local_400);
      p_Var15 = operator_new(0x48);
      *(undefined8 *)(p_Var15 + 0x10) = local_400;
      *(_List_node_base **)(p_Var15 + 0x18) = p_Var15 + 0x28;
      FUN_00128218(p_Var15 + 0x18,local_3f8,local_3f8 + local_3f0);
      *(ulong *)(p_Var15 + 0x38) = local_3d8;
      p_Var15[0x41] = local_3d0._1_1_;
      p_Var15[0x40] = local_3d0._0_1_;
      p_Var15[0x42] = local_3d0._2_1_;
      p_Var15[0x43] = local_3d0._3_1_;
      std::__detail::_List_node_base::_M_hook(p_Var15);
      local_5b8 = local_5b8 + 1;
      free(puVar14);
      if (local_3f8 != local_3e8) {
        operator_delete(local_3f8);
      }
      iVar6 = 1;
      uVar2 = uVar3 + iVar11 & 0xffff;
      uVar28 = (ulong)uVar2;
    } while (uVar2 < uVar1);
LAB_00136be0:
    pcVar30 = local_578;
    puVar17 = local_580;
    pcVar21 = *(char **)(this + 0x808);
    pcVar24 = local_578;
    if (pcVar21 < local_578) {
      pcVar24 = pcVar21;
    }
    if ((pcVar24 == (char *)0x0) ||
       (iVar11 = memcmp(local_580,*(void **)(this + 0x800),(size_t)pcVar24), iVar11 == 0))
    goto LAB_00136c08;
  }
  pcVar24 = *(char **)(this + 0x8b0);
  pcVar21 = pcVar24;
  if (pcVar30 < pcVar24) {
    pcVar21 = pcVar30;
  }
  if (((pcVar21 == (char *)0x0) ||
      (iVar13 = memcmp(puVar17,*(void **)(this + 0x8a8),(size_t)pcVar21), iVar13 == 0)) &&
     ((lVar22 = (long)pcVar30 - (long)pcVar24, lVar22 < 0x80000000 &&
      ((-0x80000001 < lVar22 && ((int)lVar22 == 0)))))) {
    local_540 = 2;
    this_00 = (CIap2Sqlite *)(this + 0x918);
    std::__cxx11::string::_M_assign((string *)(this + 0x8f0));
    this[0x910] = local_518;
    if (bVar7) {
      this[0x912] = CStack_516;
    }
  }
  else {
    this_00 = (CIap2Sqlite *)0x0;
    if (iVar11 == 1) {
      CIpodLog::i("CIpodIap2::mediaLibraryUpdate, ---m_LocalDeviceLibrary.id == library.id --- \n");
    }
  }
LAB_00136c80:
  uVar16 = CIpodVehicle::getCachePath();
  sprintf((char *)&local_400,"%s/%s/%s",uVar16,local_580,"library_revision");
  __s = fopen((char *)&local_400,"w+");
  if (__s != (FILE *)0x0) {
    fwrite(local_538,(size_t)(local_530 + 1),1,__s);
    fclose(__s);
  }
  pppppppuVar23 = pppppppuStack_598;
  if (this_00 != (CIap2Sqlite *)0x0) {
    CIap2Sqlite::beginTransaction(this_00);
    if (bVar8) {
      CIap2Sqlite::reset(this_00);
    }
    if ((undefined8 ********)local_5e0 != &local_5e0) {
      pppppppuVar23 = local_5e0;
LAB_00136d28:
      do {
        local_510 = pppppppuVar23[2];
        local_508 = (long ******)local_4f8;
        FUN_00128218(&local_508,pppppppuVar23[3],(long)pppppppuVar23[3] + (long)pppppppuVar23[4]);
        local_4d0[0] = auStack_4c0;
        local_4e8 = (long ******)CONCAT35(local_4e8._5_3_,*(undefined5 *)(pppppppuVar23 + 7));
        ppppppuStack_4d8 = pppppppuVar23[9];
        local_4e0 = pppppppuVar23[8];
        FUN_00128218(local_4d0,pppppppuVar23[10],(long)pppppppuVar23[10] + (long)pppppppuVar23[0xb])
        ;
        local_4b0 = pppppppuVar23[0xe];
        local_4a8 = pppppppuVar23[0xf];
        local_4a0[0] = auStack_490;
        FUN_00128218(local_4a0,pppppppuVar23[0x10],
                     (long)pppppppuVar23[0x10] + (long)pppppppuVar23[0x11]);
        local_480 = pppppppuVar23[0x14];
        local_478 = local_468;
        ppppppuVar19 = pppppppuVar23[0x15];
        ppppppuVar4 = pppppppuVar23[0x16];
        if ((undefined1 *)((long)ppppppuVar19 + (long)ppppppuVar4) != (undefined1 *)0x0 &&
            ppppppuVar19 == (undefined8 ******)0x0) {
                    /* WARNING: Subroutine does not return */
          std::__throw_logic_error("basic_string::_M_construct null not valid");
        }
        local_600 = ppppppuVar4;
        if (ppppppuVar4 < (undefined8 ******)0x10) {
          if (ppppppuVar4 == (undefined8 ******)0x1) {
            local_468[0] = (undefined8 ******)
                           CONCAT71(local_468[0]._1_7_,*(undefined1 *)ppppppuVar19);
          }
          else if (ppppppuVar4 != (undefined8 ******)0x0) goto LAB_0013785c;
        }
        else {
          local_478 = (undefined8 ******)
                      std::__cxx11::string::_M_create((ulong *)&local_478,(ulong)&local_600);
          local_468[0] = local_600;
LAB_0013785c:
          memcpy(local_478,ppppppuVar19,(size_t)ppppppuVar4);
        }
        ppppppuVar19 = local_440;
        *(undefined1 *)((long)local_478 + (long)local_600) = 0;
        local_458 = pppppppuVar23[0x19];
        ppppppuVar4 = pppppppuVar23[0x1a];
        ppppppuVar5 = pppppppuVar23[0x1b];
        local_470 = local_600;
        local_450 = ppppppuVar19;
        if ((undefined1 *)((long)ppppppuVar4 + (long)ppppppuVar5) != (undefined1 *)0x0 &&
            ppppppuVar4 == (undefined8 ******)0x0) {
                    /* WARNING: Subroutine does not return */
          std::__throw_logic_error("basic_string::_M_construct null not valid");
        }
        local_5f8 = ppppppuVar5;
        if (ppppppuVar5 < (undefined8 ******)0x10) {
          if (ppppppuVar5 == (undefined8 ******)0x1) {
            local_440[0] = (undefined8 ******)
                           CONCAT71(local_440[0]._1_7_,*(undefined1 *)ppppppuVar4);
          }
          else if (ppppppuVar5 != (undefined8 ******)0x0) goto LAB_001379bc;
        }
        else {
          ppppppuVar19 = (undefined8 ******)
                         std::__cxx11::string::_M_create((ulong *)&local_450,(ulong)&local_5f8);
          local_440[0] = local_5f8;
LAB_001379bc:
          local_450 = ppppppuVar19;
          memcpy(ppppppuVar19,ppppppuVar4,(size_t)ppppppuVar5);
        }
        ppppppuVar19 = local_418;
        *(undefined1 *)((long)local_450 + (long)local_5f8) = 0;
        local_430 = pppppppuVar23[0x1e];
        ppppppuVar4 = pppppppuVar23[0x1f];
        ppppppuVar5 = pppppppuVar23[0x20];
        local_448 = local_5f8;
        local_428 = ppppppuVar19;
        if ((undefined1 *)((long)ppppppuVar4 + (long)ppppppuVar5) != (undefined1 *)0x0 &&
            ppppppuVar4 == (undefined8 ******)0x0) {
                    /* WARNING: Subroutine does not return */
          std::__throw_logic_error("basic_string::_M_construct null not valid");
        }
        local_5f0 = ppppppuVar5;
        if (ppppppuVar5 < (undefined8 ******)0x10) {
          if (ppppppuVar5 == (undefined8 ******)0x1) {
            local_418[0] = (undefined8 ******)
                           CONCAT71(local_418[0]._1_7_,*(undefined1 *)ppppppuVar4);
          }
          else if (ppppppuVar5 != (undefined8 ******)0x0) goto LAB_00137988;
        }
        else {
          ppppppuVar19 = (undefined8 ******)
                         std::__cxx11::string::_M_create((ulong *)&local_428,(ulong)&local_5f0);
          local_418[0] = local_5f0;
LAB_00137988:
          local_428 = ppppppuVar19;
          memcpy(ppppppuVar19,ppppppuVar4,(size_t)ppppppuVar5);
        }
        *(undefined1 *)((long)local_428 + (long)local_5f0) = 0;
        local_408 = *(undefined1 *)(pppppppuVar23 + 0x23);
        local_407 = *(undefined1 *)((long)pppppppuVar23 + 0x119);
        local_406 = *(undefined1 *)((long)pppppppuVar23 + 0x11a);
        local_405 = *(undefined1 *)((long)pppppppuVar23 + 0x11b);
        local_404 = *(undefined1 *)((long)pppppppuVar23 + 0x11c);
        local_403 = *(undefined1 *)((long)pppppppuVar23 + 0x11d);
        local_402 = *(undefined2 *)((long)pppppppuVar23 + 0x11e);
        local_420 = local_5f0;
        CIap2Sqlite::insertMediaItem(this_00,&local_510);
        if ((undefined8 *******)local_428 != local_418) {
          operator_delete(local_428);
        }
        if ((undefined8 *******)local_450 != local_440) {
          operator_delete(local_450);
        }
        if ((undefined8 *******)local_478 != local_468) {
          operator_delete(local_478);
        }
        if (local_4a0[0] != auStack_490) {
          operator_delete(local_4a0[0]);
        }
        if (local_4d0[0] != auStack_4c0) {
          operator_delete(local_4d0[0]);
        }
        if ((long *******)local_508 == local_4f8) {
          pppppppuVar23 = (undefined8 *******)*pppppppuVar23;
          if ((undefined8 ********)pppppppuVar23 == &local_5e0) break;
          goto LAB_00136d28;
        }
        operator_delete(local_508);
        pppppppuVar23 = (undefined8 *******)*pppppppuVar23;
      } while ((undefined8 ********)pppppppuVar23 != &local_5e0);
    }
    CIpodLog::d("CIpodIap2::mediaLibraryUpdate, hasUpdatePlaylistName = %d \n",iVar6);
    ppppppplVar27 = local_5b0;
    if ((long ********)local_5c8 != &local_5c8) {
      ppppppplVar29 = local_5c8;
      do {
        ppppppplVar27 = ppppppplVar29 + 2;
        if (*(char *)((long)ppppppplVar29 + 0x42) != '\0') {
          puVar17 = calloc(0x30,1);
          *puVar17 = *(undefined1 *)((long)ppppppplVar29 + 0x42);
          *(undefined4 *)(puVar17 + 4) = 1;
          pppppplVar20 = ppppppplVar29[2];
          *(undefined4 *)(puVar17 + 0x20) = local_540;
          *(long *******)(puVar17 + 0x28) = pppppplVar20;
          p_Var15 = operator_new(0x18);
          *(undefined1 **)(p_Var15 + 0x10) = puVar17;
          std::__detail::_List_node_base::_M_hook(p_Var15);
          *(long *)(this + 0x7f8) = *(long *)(this + 0x7f8) + 1;
        }
        local_510 = *ppppppplVar27;
        pppppplVar20 = ppppppplVar29[3];
        __n = ppppppplVar29[4];
        local_508 = (long ******)local_4f8;
        if (pppppplVar20 == (long ******)0x0 &&
            (undefined1 *)((long)pppppplVar20 + (long)__n) != (undefined1 *)0x0) {
                    /* WARNING: Subroutine does not return */
          std::__throw_logic_error("basic_string::_M_construct null not valid");
        }
        local_5e8 = __n;
        if (__n < (long ******)0x10) {
          if (__n == (long ******)0x1) {
            local_4f8[0] = (long ******)CONCAT71(local_4f8[0]._1_7_,*(undefined1 *)pppppplVar20);
          }
          else if (__n != (long ******)0x0) goto LAB_001370cc;
        }
        else {
          local_508 = (long ******)
                      std::__cxx11::string::_M_create((ulong *)&local_508,(ulong)&local_5e8);
          local_4f8[0] = local_5e8;
LAB_001370cc:
          memcpy(local_508,pppppplVar20,(size_t)__n);
        }
        *(undefined1 *)((long)local_508 + (long)local_5e8) = 0;
        local_4e8 = ppppppplVar29[7];
        local_4e0 = (undefined8 ******)CONCAT44(local_4e0._4_4_,*(undefined4 *)(ppppppplVar29 + 8));
        local_500 = local_5e8;
        CIap2Sqlite::insertMediaPlaylist(this_00,&local_510);
        if ((long *******)local_508 != local_4f8) {
          operator_delete(local_508);
        }
        if (iVar6 != 0) {
          local_510 = *ppppppplVar27;
          local_508 = (long ******)local_4f8;
          FUN_00128218(&local_508,ppppppplVar29[3],(long)ppppppplVar29[3] + (long)ppppppplVar29[4]);
          local_4e8 = ppppppplVar29[7];
          local_4e0 = (undefined8 ******)
                      CONCAT44(local_4e0._4_4_,*(undefined4 *)(ppppppplVar29 + 8));
          cVar10 = CIap2Sqlite::isMediaPlaylistExist(this_00,&local_510);
          if ((long *******)local_508 != local_4f8) {
            operator_delete(local_508);
          }
          if (cVar10 != '\0') {
            local_510 = *ppppppplVar27;
            local_508 = (long ******)local_4f8;
            FUN_00128218(&local_508,ppppppplVar29[3],(long)ppppppplVar29[3] + (long)ppppppplVar29[4]
                        );
            local_4e8 = ppppppplVar29[7];
            local_4e0 = (undefined8 ******)
                        CONCAT44(local_4e0._4_4_,*(undefined4 *)(ppppppplVar29 + 8));
            uVar28 = CIap2Sqlite::updateMediaPlaylistName(this_00,&local_510);
            if ((long *******)local_508 != local_4f8) {
              operator_delete(local_508);
            }
            CIpodLog::i("update playlist result: %d\n",uVar28 & 0xffffffff);
          }
        }
        ppppppplVar29 = (long *******)*ppppppplVar29;
        iVar6 = 0;
        ppppppplVar27 = local_5b0;
      } while ((long ********)ppppppplVar29 != &local_5c8);
    }
    for (; pppppppuVar23 = pppppppuStack_598, (long ********)ppppppplVar27 != &local_5b0;
        ppppppplVar27 = (long *******)*ppppppplVar27) {
      CIap2Sqlite::deleteMediaItem(this_00,(ulonglong)ppppppplVar27[2]);
    }
    for (; (undefined8 ********)pppppppuVar23 != &pppppppuStack_598;
        pppppppuVar23 = (undefined8 *******)*pppppppuVar23) {
      CIap2Sqlite::deleteMediaPlaylist(this_00,(ulonglong)pppppppuVar23[2]);
    }
    CIap2Sqlite::commitTransaction(this_00);
    pppppppuVar23 = pppppppuStack_598;
  }
  while (ppppppplVar27 = local_5c8, ppppppplVar29 = local_5b0,
        (undefined8 ********)pppppppuVar23 != &pppppppuStack_598) {
    pppppppuVar25 = (undefined8 *******)*pppppppuVar23;
    operator_delete(pppppppuVar23);
    pppppppuVar23 = pppppppuVar25;
  }
  while (local_5c8 = ppppppplVar27, (long ********)ppppppplVar29 != &local_5b0) {
    ppppppplVar26 = (long *******)*ppppppplVar29;
    operator_delete(ppppppplVar29);
    ppppppplVar27 = local_5c8;
    ppppppplVar29 = ppppppplVar26;
  }
  pppppppuVar23 = local_5e0;
  if ((long ********)ppppppplVar27 == &local_5c8) {
joined_r0x00137724:
    while ((undefined8 ********)pppppppuVar23 != &local_5e0) {
      pppppppuVar25 = (undefined8 *******)*pppppppuVar23;
      if ((undefined8 *******)pppppppuVar23[0x1f] != pppppppuVar23 + 0x21) {
        operator_delete(pppppppuVar23[0x1f]);
      }
      if ((undefined8 *******)pppppppuVar23[0x1a] != pppppppuVar23 + 0x1c) {
        operator_delete(pppppppuVar23[0x1a]);
      }
      if ((undefined8 *******)pppppppuVar23[0x15] != pppppppuVar23 + 0x17) {
        operator_delete(pppppppuVar23[0x15]);
      }
      if ((undefined8 *******)pppppppuVar23[0x10] != pppppppuVar23 + 0x12) {
        operator_delete(pppppppuVar23[0x10]);
      }
      if ((undefined8 *******)pppppppuVar23[10] != pppppppuVar23 + 0xc) {
        operator_delete(pppppppuVar23[10]);
      }
      if ((undefined8 *******)pppppppuVar23[3] == pppppppuVar23 + 5) {
        operator_delete(pppppppuVar23);
        pppppppuVar23 = pppppppuVar25;
      }
      else {
        operator_delete(pppppppuVar23[3]);
        operator_delete(pppppppuVar23);
        pppppppuVar23 = pppppppuVar25;
      }
    }
    if (local_538 != local_528) {
      operator_delete(local_538);
    }
    if (local_560 != local_550) {
      operator_delete(local_560);
    }
    if (local_580 != local_570) {
      operator_delete(local_580);
    }
    return 0;
  }
  ppppppplVar29 = (long *******)ppppppplVar27[3];
  ppppppplVar26 = (long *******)*ppppppplVar27;
  if (ppppppplVar29 == ppppppplVar27 + 5) goto LAB_0013770c;
  do {
    operator_delete(ppppppplVar29);
    operator_delete(ppppppplVar27);
    ppppppplVar27 = ppppppplVar26;
    while( true ) {
      pppppppuVar23 = local_5e0;
      if ((long ********)ppppppplVar27 == &local_5c8) goto joined_r0x00137724;
      ppppppplVar29 = (long *******)ppppppplVar27[3];
      ppppppplVar26 = (long *******)*ppppppplVar27;
      if (ppppppplVar29 != ppppppplVar27 + 5) break;
LAB_0013770c:
      operator_delete(ppppppplVar27);
      ppppppplVar27 = ppppppplVar26;
    }
  } while( true );
}


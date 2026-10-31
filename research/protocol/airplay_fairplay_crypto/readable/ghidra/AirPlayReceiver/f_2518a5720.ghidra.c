/* RAW GHIDRA DECOMPILATION — NOT REVIEWED PROTOCOL PSEUDOCODE
 * original address: 0x2518a5720
 * original code SHA256: 833d016f8941622b1c923515e47499964c5895093ba180970b2bd8b79289b9ea
 * source SHA256: ad6eddbb9bedcb8f121699e7fc94702632c4acf30135564763a646ac472cc51a
 * Assembly/raw bytes: adjacent .s/.bin from the original firmware.
 * Types, signatures and indirect targets remain hypotheses until reviewed.
 */



/* WARNING: Removing unreachable block (ram,0x0002518a59cc) */
/* WARNING: Removing unreachable block (ram,0x0002518a594c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint _airplayReqProcessor_requestProcessFPSetup2
               (undefined8 param_1,undefined8 param_2,long *param_3)

{
  int iVar1;
  long *plVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  code *pcVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  long local_78;
  uint local_6c;
  long local_68;
  ulong local_60;
  uint local_54;
  
  local_54 = 0;
  plVar2 = (long *)func_0x00025810ac50();
  local_68 = 0;
  local_60 = 0;
  local_6c = 0;
  local_78 = 0;
  lVar3 = func_0x000258101820(0,0,_DAT_2680d3340,_DAT_2680d3358);
  if (lVar3 == 0) {
    func_0x000258109a30(0,"airplayReqProcessor_requestProcessFPSetup2",0xabb,0);
    iVar1 = 0;
    local_54 = 0xfffee6f2;
    goto LAB_2518a5b0c;
  }
  if ((_gLogCategory_APReceiverRequestProcessorAirPlay < 0x1f) &&
     ((_gLogCategory_APReceiverRequestProcessorAirPlay != -1 ||
      (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverRequestProcessorAirPlay,0x200001e),
      iVar1 != 0)))) {
    func_0x000258101eb0(&_gLogCategory_APReceiverRequestProcessorAirPlay,
                        "APSTransportMessageProcessingStatus airplayReqProcessor_requestProcessFPSetup2(APReceiverRequestProcessorRef, CFDictionaryRef, CFDictionaryRef *)"
                        ,0x200001e,"FP-Setup2\n");
  }
  uVar12 = *_DAT_2681041b8;
  uVar4 = func_0x00025810a6b0(param_2,uVar12,0,0,&local_60,&local_54);
  if (local_60 == 0) {
    func_0x000258109a30(0,"airplayReqProcessor_requestProcessFPSetup2",0xac0,0);
    lVar6 = 0;
    iVar1 = -0x118fa;
LAB_2518a5d0c:
    func_0x0002580f5830(lVar3);
  }
  else {
    _airplayReqProcessor_GetMCRPForMCSession(param_1,0,&local_78);
    local_54 = 0;
    if (local_78 == 0) {
      uVar5 = _airplayReqProcessor_createAndStoreMediaControlRequestProcessorForMCSession
                        (param_1,0,0);
      local_54 = (uint)uVar5;
      if (local_54 != 0) {
        func_0x000258109a30(uVar5,"airplayReqProcessor_requestProcessFPSetup2",0xac7,0);
        iVar1 = 0;
        lVar6 = 0;
        goto LAB_2518a5d0c;
      }
      if (plVar2[0x46] == 0) {
        lVar6 = func_0x0002580f7510();
        plVar2[0x46] = lVar6;
      }
      if (plVar2[0x4a] == 0) {
        lVar6 = func_0x0002580f7510();
        plVar2[0x4a] = lVar6;
        *(undefined4 *)(plVar2 + 0x4b) = 1;
      }
    }
    if (plVar2[0x24] == 0) {
      func_0x000258109a30(0,"airplayReqProcessor_requestProcessFPSetup2",0xad7,0);
      lVar6 = 0;
      local_54 = 0xffffe596;
      iVar1 = -0x11904;
    }
    else {
      uVar7 = _OowSGu(plVar2[0x24],uVar4,local_60 & 0xffffffff,&local_68,&local_6c);
      local_54 = (uint)uVar7;
      if (local_54 == 0) {
LAB_2518a58b0:
        if (local_6c < 0x40) {
          func_0x000258109a30(0,"airplayReqProcessor_requestProcessFPSetup2",0xadb,0);
          lVar6 = 0;
          iVar1 = -0x118fa;
        }
        else {
          lVar8 = func_0x00025810a8d0(*(undefined8 *)(*plVar2 + 0xa0),0,
                                      _APReceiverSystemInfoCopyProperty,1,&cfstringStruct_276114350,
                                      0,0);
          lVar6 = local_68;
          if ((lVar8 == 0) && (*(int *)((long)plVar2 + 0x144) == 0)) {
LAB_2518a5a00:
            lVar6 = func_0x0002580f6ff0(*_DAT_2680d3150,local_68,local_6c);
            if (lVar6 == 0) {
              func_0x000258109a30(0,"airplayReqProcessor_requestProcessFPSetup2",0xaeb,0);
              iVar1 = 0;
              local_54 = 0xfffee6f2;
              goto LAB_2518a5d0c;
            }
            uVar4 = func_0x00025810a760(lVar3,&cfstringStruct_2761122b0,"application/octet-stream",
                                        0xffffffffffffffff);
            local_54 = (uint)uVar4;
            if (local_54 == 0) {
              func_0x0002580f7000(lVar3,uVar12,lVar6);
              uVar4 = func_0x00025810a790(lVar3,*_DAT_2681041c8,0);
              local_54 = (uint)uVar4;
              if (local_54 == 0) {
                iVar1 = 0;
                local_54 = 0;
                goto LAB_2518a5adc;
              }
              uVar12 = 0xaf2;
            }
            else {
              uVar12 = 0xaef;
            }
            func_0x000258109a30(uVar4,"airplayReqProcessor_requestProcessFPSetup2",uVar12,0);
            iVar1 = 0;
            goto LAB_2518a5d0c;
          }
          lVar8 = plVar2[0x26];
          if (lVar8 != 0) {
            lVar9 = func_0x000258109150(lVar8);
            puVar11 = (undefined8 *)(*(long *)(lVar9 + 0x10) + 0x18);
            pcVar10 = (code *)*puVar11;
            if ((pcVar10 == (code *)0x0) || (pcVar10 == (code *)0x0)) {
              uVar7 = 0xffffce12;
              local_54 = 0xffffce12;
            }
            else {
              uVar7 = (*pcVar10)((ulong)puVar11 & 0xffffffffffff | 0x71e1000000000000,lVar8,lVar6,
                                 0x10,0,0,0x10,lVar6);
              lVar6 = local_68;
              local_54 = (uint)uVar7;
              if (local_54 == 0) {
                lVar9 = plVar2[0x26];
                lVar8 = func_0x000258109150(lVar9);
                puVar11 = (undefined8 *)(*(long *)(lVar8 + 0x10) + 0x18);
                pcVar10 = (code *)*puVar11;
                if ((pcVar10 == (code *)0x0) || (pcVar10 == (code *)0x0)) {
                  uVar7 = 0xffffce12;
                  local_54 = 0xffffce12;
                }
                else {
                  uVar7 = (*pcVar10)((ulong)puVar11 & 0xffffffffffff | 0x71e1000000000000,lVar9,
                                     lVar6 + 0x20,0x10,0,0,0x10,lVar6 + 0x20);
                  local_54 = (uint)uVar7;
                  if (local_54 == 0) goto LAB_2518a5a00;
                }
                uVar4 = 0xae4;
                goto LAB_2518a5ad0;
              }
            }
            uVar4 = 0xae2;
            goto LAB_2518a5ad0;
          }
          iVar1 = -0x118fe;
          func_0x000258109a30(0,"airplayReqProcessor_requestProcessFPSetup2",0xae0,0);
          lVar6 = 0;
          local_54 = 0xffffe596;
        }
      }
      else {
        if (plVar2[0x24] != 0) {
          _IPaI1oem5iL(plVar2[0x24]);
          plVar2[0x24] = 0;
          uVar7 = (ulong)local_54;
          if (local_54 == 0) goto LAB_2518a58b0;
        }
        uVar4 = 0xada;
LAB_2518a5ad0:
        iVar1 = -0x118fe;
        func_0x000258109a30(uVar7,"airplayReqProcessor_requestProcessFPSetup2",uVar4,0);
        lVar6 = 0;
      }
    }
LAB_2518a5adc:
    uVar4 = func_0x00025810a790(lVar3,*_DAT_2681041e0,(long)iVar1);
    local_54 = (uint)uVar4;
    if (local_54 != 0) {
      func_0x000258109a30(uVar4,"airplayReqProcessor_requestProcessFPSetup2",0xaf7,0);
      goto LAB_2518a5d0c;
    }
    *param_3 = lVar3;
  }
  if (lVar6 != 0) {
    func_0x0002580f5830(lVar6);
  }
LAB_2518a5b0c:
  if (local_68 != 0) {
    _jEHf8Xzsv8K();
  }
  if (((iVar1 != 0) && (_gLogCategory_APReceiverRequestProcessorAirPlay < 0x3d)) &&
     ((_gLogCategory_APReceiverRequestProcessorAirPlay != -1 ||
      (iVar1 = func_0x000258101e40(&_gLogCategory_APReceiverRequestProcessorAirPlay,0x200003c),
      iVar1 != 0)))) {
    func_0x000258101eb0(&_gLogCategory_APReceiverRequestProcessorAirPlay,
                        "APSTransportMessageProcessingStatus airplayReqProcessor_requestProcessFPSetup2(APReceiverRequestProcessorRef, CFDictionaryRef, CFDictionaryRef *)"
                        ,0x200003c,"### [%{ptr}] FP-Setup2 Failed: %d, %#m\n");
  }
  return local_54;
}

